//
// Created by Gael Rial Costas on 08/11/2021.
//

#ifndef QTRECORDER_SELECTIONAREA_H
#define QTRECORDER_SELECTIONAREA_H

#include <acuterecorder/api.h>

#include <QRubberBand>
#include <QRectF>

#include <acuterecorder/dialog/util/PixmapHolder.h>
#include <acuterecorder/dialog/util/SelectionMode.h>
#include <acuterecorder/Input.h>

class QScreen;
class QResizeEvent;

/**
 * Represents the area where the user can select the area to record.
 *
 * This area supports all three selection modes: FULL, AREA and WIDGET.
 */
class ACUTERECORDER_API SelectionArea : public PixmapHolder
{

Q_OBJECT

  SelectionMode mode_;
  Input input_;
  QWidget *selectedWidget_;
  QRectF sourceViewport_;

  QRubberBand *band_;
  QPointF areaFrom_ , areaTo_;
  bool dragging_;

private slots:

  /**
   * Renders a new screenshot of the target.
   *
   * This method is very expensive. Use it with caution!
   */
  void renderImage( );

protected:

  void mousePressEvent( QMouseEvent *event ) override;

  void mouseMoveEvent( QMouseEvent *event ) override;

  void mouseReleaseEvent( QMouseEvent *event ) override;

  void resizeEvent(QResizeEvent *e) override;

public:

  /**
   * Creates the selection area.
   * @param parent  the parent widget. Required by Qt. It may be null.
   * @param rootWidget the first widget to show.
   * @param selectionMode the default selection mode.
   */
  explicit SelectionArea( QWidget *parent ,
                          QWidget *rootWidget ,
                          SelectionMode selectionMode );

  /**
   * Returns the selected input.
   *
   * @return the selected input.
   */
  Input getSelectedInput( ) const;

  /**
   * Returns the viewport to use in the recording.
   *
   * @return the viewport.
   */
  QRectF getViewport( ) const;

  /**
   * Refresh the selection tool of this area.
   *
   * You have to use this after you change the selection mode!
   */
  void refreshSelectionMode( );

  /**
   * Transforms the given screen point into its normalized representation.
   *
   * A screen point is a point in this widget's coordinates.
   *
   * A normalized point is a point whose values vary between 0 and 1.
   * This type of point is used by the recorder data.
   *
   * @param point the point in screen coordinates.
   * @return the point in normalized coordinates.
   */
  QPointF normalizePoint( const QPointF& point );


  /**
   * Transforms the given normalized point into its screen representation.
   *
   * A screen point is a point in this widget's coordinates.
   *
   * A normalized point is a point whose values vary between 0 and 1.
   * This type of point is used by the recorder data.
   *
   * @param point the point in normalized coordinates.
   * @return the point in screen coordinates.
   */
  QPointF denormalizePoint( const QPointF& point );

public slots:

  void changeInput( Input input );

  void changeMode( SelectionMode mode );

};


#endif //QTRECORDER_SELECTIONAREA_H
