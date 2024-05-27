/*
 * Copyright (c) 2021-2024 VG-Lab/URJC.
 *
 * Authors: Gael Rial Costas <gael.rial.costas@urjc.es>
 *
 * This file is part of AcuteRecorder <https://github.com/vg-lab/AcuteRecorder>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

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
