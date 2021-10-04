//
// Created by Gael Rial Costas on 6/3/21.
//

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>
#include "SelectionArea.h"
#include "../constant/QtUtils.h"

const double SCREEN_WIDTH = 800.0;

SelectionArea::SelectionArea( QWidget *parent , RecorderGeneralData *data )
  : QLabel( parent ) ,
    data_( data ) ,
    band_( new QRubberBand( QRubberBand::Rectangle , this )) ,
    dragging_( false )
{
  setAlignment( Qt::AlignCenter );

  resizeCheckTimer_ = new QTimer( this );

  QObject::connect( resizeCheckTimer_ , &QTimer::timeout ,
                    this , &SelectionArea::onTimerTick );

  resizeCheckTimer_->start( 50 );
}

void SelectionArea::mousePressEvent( QMouseEvent *event )
{
  dragging_ = false;
  if ( data_->selectionMode != AREA ) return;
  origin_ = event->pos( );

  auto pixmapPoint = toPixmapPoint( origin_ );
  if ( pixmapPoint.x( ) < 0
       || pixmapPoint.y( ) < 0
       || pixmapPoint.x( ) >= pixmap( )->width( )
       || pixmapPoint.y( ) >= pixmap( )->height( ))
    return;

  band_->setGeometry( QRect( origin_ , QSize( )));
  dragging_ = true;
}

void SelectionArea::mouseMoveEvent( QMouseEvent *event )
{
  if ( !dragging_ ) return;

  auto pmp = toPixmapPoint( event->pos( ));
  pmp.setX( std::min( std::max( pmp.x( ) , 0 ) , pixmap( )->width( ) - 1 ));
  pmp.setY( std::min( std::max( pmp.y( ) , 0 ) , pixmap( )->height( ) - 1 ));

  auto rect = QRect( origin_ , fromPixmapPoint( pmp )).normalized( );
  band_->setGeometry( rect );
}

void SelectionArea::mouseReleaseEvent( QMouseEvent *event )
{
  if ( data_->selectionMode == AREA )
  {
    if ( !dragging_ ) return;


    auto ratio = data_->screen == nullptr
                 ? 1
                 : data_->screen->size( ).width( ) / SCREEN_WIDTH;

    auto g = band_->geometry( );
    auto from = toPixmapPoint( g.topLeft( )) * ratio;
    auto gSize = g.size( ) * ratio;

    data_->sourceViewport =
      ViewportI( from.x( ) , from.y( ) , gSize.width( ) , gSize.height( ));

    dragging_ = false;
  }
  else if ( data_->selectionMode == WIDGET )
  {
    data_->selectedWidget = qt_utils::findDeepestChildWithPoint(
      data_->renderingWidget ,
      toPixmapPoint( event->pos( )) ,
      data_->selectedWidget );

    refreshSelectionMode( );
  }
}


void SelectionArea::resizeEvent( QResizeEvent *event )
{
  renderImage( );
}

void SelectionArea::refreshSelectionMode( )
{

  switch ( data_->selectionMode )
  {
    case FULL:
      band_->hide( );
      break;
    case AREA:
    {
      auto source = data_->sourceViewport;


      auto ratio = data_->screen == nullptr
                   ? 1
                   : data_->screen->size( ).width( ) / SCREEN_WIDTH;

      auto sourceStart = fromPixmapPoint(
        QPoint( source.x / ratio , source.y / ratio ));
      band_->setGeometry( sourceStart.x( ) ,
                          sourceStart.y( ) ,
                          source.width / ratio ,
                          source.height / ratio );
      band_->show( );
    }
      break;
    case WIDGET:
    {
      auto widget = data_->selectedWidget;
      if ( widget != nullptr )
      {
        auto global = fromPixmapPoint(
          widget->mapTo( data_->renderingWidget , QPoint( )));
        band_->setGeometry(
          global.x( ) , global.y( ) , widget->width( ) , widget->height( ));
        band_->show( );
      }
      break;
    }
  }
}

QPoint SelectionArea::toPixmapPoint( const QPoint& localPoint )
{
  int extra = ( width( ) - pixmap( )->width( )) / 2;
  return { localPoint.x( ) - extra , localPoint.y( ) };
}

QPoint SelectionArea::fromPixmapPoint( const QPoint& localPoint )
{
  int extra = ( width( ) - pixmap( )->width( )) / 2;
  return { localPoint.x( ) + extra , localPoint.y( ) };
}

void SelectionArea::onTimerTick( )
{
  renderImage( );
  checkRenderArea( );
}

void SelectionArea::renderImage( )
{

  if ( data_->screen != nullptr )
  {
    auto screen = data_->screen;
    auto map = screen->grabWindow( 0 );
    map = map.scaledToWidth( SCREEN_WIDTH , Qt::SmoothTransformation );
    setPixmap( map );
  }
  else
  {
    auto size = data_->renderingWidget->size( );
    QImage image( size , QImage::Format_RGB32 );
    QPainter painter( &image );
    data_->renderingWidget->render( &painter );
    QPixmap map;
    map.convertFromImage( image , Qt::ColorOnly );
    setPixmap( map );
  }

  if ( !dragging_ )
  {
    refreshSelectionMode( );
  }
}

void SelectionArea::checkRenderArea( )
{
  // Don't check when the source is a screen!
  if(data_->screen != nullptr) return;

  auto v = data_->sourceViewport;
  auto ps = pixmap( )->size( );

  v.x = std::min( v.x , ps.width( ));
  v.y = std::min( v.y , ps.height( ));
  v.width = std::min( v.width + v.x , ps.width( ) - 1 ) - v.x;
  v.height = std::min( v.height + v.y , ps.height( ) - 1 ) - v.y;
  data_->sourceViewport = v;
}
