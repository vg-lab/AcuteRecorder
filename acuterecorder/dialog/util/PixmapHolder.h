//
// Created by Gael Rial Costas on 08/11/2021.
//

#ifndef QTRECORDER_PIXMAPHOLDER_H
#define QTRECORDER_PIXMAPHOLDER_H

#include <acuterecorder/api.h>

#include <QLabel>

/**
 * Small helper node used to hold a Pixmap that will be resized
 * to match this label's bounds.
 */
class ACUTERECORDER_API PixmapHolder : public QLabel
{

Q_OBJECT

  QPixmap pixmap_;
  int width_;
  int height_;

public:

  /**
   * Creates the holder.
   * @param parent the parent of this node. Required by Qt. It may be null.
   */
  explicit PixmapHolder( QWidget *parent = nullptr );

  /**
   * Resizes the Pixmap to match this label's bounds.
   *
   * This method is expensive. Use it with caution!
   *
   * @return a scaled version of the Pixmap.
   */
  QPixmap getScaledPixmap( ) const;

public slots:

  /**
   * Sets the Pixmap to hold.
   * @param pixmap the Pixmap. It may be null.
   */
  void setHolderPixmap( const QPixmap& pixmap );

  /**
   * Returns the width of the scaled pixmap.
   * @return the width.
   */
  int getWidth( ) const;

  /**
   * Returns the height of the scaled pixmap.
   * @return the height.
   */
  int getHeight( ) const;

  void resizeEvent( QResizeEvent *resizeEvent ) override;

};


#endif //QTRECORDER_PIXMAPHOLDER_H
