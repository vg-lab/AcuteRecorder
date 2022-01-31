//
// Created by Gael Rial Costas on 08/11/2021.
//

#include "SelectionArea.h"

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>

#include <dialog/util/APIUtils.h>

constexpr int UPDATE_MILLIS = 50;

SelectionArea::SelectionArea( QWidget *parent ,
                              QWidget *rootWidget ,
                              SelectionMode selectionMode )
  : PixmapHolder( parent ) ,
    mode_( selectionMode ) ,
    input_( rootWidget ) ,
    selectedWidget_( rootWidget ) ,
    sourceViewport_( 0 , 0 , 1 , 1 ) ,
    band_( new QRubberBand( QRubberBand::Rectangle , this )) ,
    areaFrom_( 0 , 0 ) ,
    areaTo_( 0 , 0 ) ,
    dragging_( false )
{
  setAlignment( Qt::AlignCenter );

  auto timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(renderImage()));
  connect(this, SIGNAL(destroyed(QObject*)), timer, SLOT(deleteLater()));

  timer->setSingleShot(false);
  timer->setInterval(UPDATE_MILLIS);
  timer->start();
}

// region mouse events

void SelectionArea::mousePressEvent( QMouseEvent *event )
{
  // This method is only used by the AREA selection mode.
  // Here the widget has to grab the first point of the area.
  if ( mode_ != SelectionMode::AREA ) return;

  areaFrom_ = normalizePoint( event->pos( ));

  // If the point is outside the image, return.
  if (
    areaFrom_.x( ) < 0 || areaFrom_.y( ) < 0 ||
    areaFrom_.x( ) > 1 || areaFrom_.y( ) > 1 )
    return;

  areaTo_ = areaFrom_;
  band_->setGeometry( QRect( event->pos( ) , QSize( )));
  dragging_ = true;
}

void SelectionArea::mouseMoveEvent( QMouseEvent *event )
{

  auto clamp = [ ]( float x , float min , float max )
  {
    return std::min( std::max( x , min ) , max );
  };

  // Just like the press event, this method is only used by the AREA
  // selection mode. Here the widget calculates the second point.
  if ( mode_ != SelectionMode::AREA ) return;
  areaTo_ = normalizePoint( event->pos( ));

  // We have to clamp the point!
  areaTo_.setX( clamp( static_cast<float>(areaTo_.x( )) , 0 , 1 ));

  areaTo_.setY(
    clamp( static_cast<float>(areaTo_.y( )) , 0.0f , 1.0f )
  );

  // Update the viewport. Updating it here assures consistency with the
  // #refreshSelectionMode( ) method.+
  sourceViewport_ = QRectF( areaFrom_ , areaTo_ );

  const QRect rect(
    denormalizePoint( sourceViewport_.topLeft( )).toPoint( ) ,
    denormalizePoint( sourceViewport_.bottomRight( )).toPoint( )
  );
  band_->setGeometry( rect );
}

void SelectionArea::mouseReleaseEvent( QMouseEvent *event )
{
  switch ( mode_ )
  {
    case SelectionMode::AREA:
      if ( !dragging_ ) break;
      // We don't have to update the viewport: it was already been set
      // in the move event.
      dragging_ = false;
      break;
    case SelectionMode::WIDGET:
    {
      // Get the mouse position in normalized coordinates.
      const QPointF normalizedPoint = normalizePoint( event->pos( ));

      // Transforms the point to widget coordinates.
      const QSize ws = input_.getSize( );
      const QPoint widgetPoint(
        static_cast<int>(( normalizedPoint.x( ) * ws.width( ))) ,
        static_cast<int>(( normalizedPoint.y( ) * ws.height( )))
      );

      // Search the clicked widget, ignoring the already selected one.
      selectedWidget_ = api_utils::findDeepestChildWithPoint(
        input_.getWidget( ) ,
        widgetPoint ,
        selectedWidget_
      );
    }
      break;
    case SelectionMode::FULL:
      break;
  }
}

// endregion

void SelectionArea::renderImage( )
{
  if ( input_.isScreen( ))
  {
    // It's stupid to scale a screen's image. Just send it to the holder! :)
    const auto screen = input_.getScreen( );
    setHolderPixmap( screen->grabWindow( 0 ));
  }
  else if ( input_.isWidget( ))
  {
    // First we have to find the optimal scale for the render.
    const QSize thisSize = size( );
    const QSize wSize = input_.getWidget( )->size( );
    const QSize size = QSize(
      thisSize.height( ) * wSize.width( ) / wSize.width( ) ,
      thisSize.height( )
    );
    QImage image( size , QImage::Format_RGB32 );
    QPainter painter( &image );

    // Now that we have the optimal scale, use it in the painter.
    painter.scale(
      static_cast<float>( size.width( )) / static_cast<float>( wSize.width( )) ,
      static_cast<float>( size.height( )) / static_cast<float>( wSize.height( ))
    );

    // Now we render it and send it to the holder.
    input_.getWidget( )->render( &painter );
    QPixmap map;
    map.convertFromImage( image , Qt::ColorOnly );
    setHolderPixmap( map );
  }

  // Just in case the rendering widget was resized, refresh the selection.
  refreshSelectionMode( );
}

void SelectionArea::refreshSelectionMode( )
{
  switch ( mode_ )
  {
    case SelectionMode::FULL:
      // The FULL mode just hides the selection.
      band_->hide( );
      break;
    case SelectionMode::AREA:
    {
      if ( dragging_ ) break;
      QPointF min = denormalizePoint( sourceViewport_.topLeft( ));
      QPointF max = denormalizePoint( sourceViewport_.bottomRight( ));
      band_->setGeometry( QRect( min.toPoint( ) , max.toPoint( )));
      band_->show( );
    }
      break;
    case SelectionMode::WIDGET:
    {
      auto widget = selectedWidget_;
      if ( widget != nullptr )
      {

        // We have to transform the size of the widget from
        // widget's coordinates to screen coordinates.
        const QSize s = input_.getSize( );
        QPointF min = widget->mapTo( input_.getWidget( ) , QPoint( ));
        QPointF max = min +
                      QPoint( widget->width( ) , widget->height( ));

        min.setX( min.x( ) / s.width( ));
        min.setY( min.y( ) / s.height( ));
        max.setX( max.x( ) / s.width( ));
        max.setY( max.y( ) / s.height( ));

        min = denormalizePoint( min );
        max = denormalizePoint( max );

        band_->setGeometry( QRect(
          min.toPoint( ) ,
          max.toPoint( )
        ));
        band_->show( );
      }
    }
      break;
  }
}

QPointF SelectionArea::normalizePoint( const QPointF& point )
{
  // ExtraX and extraY represents the blank space in this area.
  // We have to remove it from the normalized coordinates if we
  // want the algorithm to work properly!
  const auto w = static_cast<float>( width( ));
  const auto h = static_cast<float>(height( ));
  const float extraX = ( w - static_cast<float>( pixmap( )->width( ))) / w;
  const float extraY = ( h - static_cast<float>( pixmap( )->height( ))) / h;

  QPointF p = point;
  p = QPointF( p.x( ) / w , p.y( ) / h );
  p.setX(( p.x( ) - extraX / 2 ) / ( 1 - extraX ));
  p.setY(( p.y( ) - extraY / 2 ) / ( 1 - extraY ));
  return p;
}

QPointF SelectionArea::denormalizePoint( const QPointF& point )
{
  // ExtraX and extraY represents the blank space in this area.
  // We have to remove it from the normalized coordinates if we
  // want the algorithm to work properly!
  const auto w = static_cast<float>( width( ));
  const auto h = static_cast<float>( height( ));
  const float extraX = ( w - static_cast<float>(pixmap( )->width( ))) / w;
  const float extraY = ( h - static_cast<float>(pixmap( )->height( ))) / h;

  QPointF p = point;
  p.setX( p.x( ) * ( 1 - extraX ) + extraX / 2 );
  p.setY( p.y( ) * ( 1 - extraY ) + extraY / 2 );
  p = QPointF( p.x( ) * w , p.y( ) * h );
  return p;
}

void SelectionArea::changeInput( Input input )
{
  input_ = input;
  refreshSelectionMode( );
}

void SelectionArea::changeMode( SelectionMode mode )
{
  mode_ = mode;
  refreshSelectionMode( );
}

Input SelectionArea::getSelectedInput( ) const
{
  return mode_ == SelectionMode::WIDGET
         ? Input( selectedWidget_ )
         : input_;
}

QRectF SelectionArea::getViewport( ) const
{
  if ( mode_ == SelectionMode::AREA ) return sourceViewport_;
  return { 0 , 0 , 1 , 1 };
}

void SelectionArea::resizeEvent(QResizeEvent *e)
{
  PixmapHolder::resizeEvent(e);

  renderImage();

  refreshSelectionMode();
}
