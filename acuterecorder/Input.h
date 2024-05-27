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

#ifndef ACUTERECORDER_OUTPUT_H
#define ACUTERECORDER_OUTPUT_H

#include <acuterecorder/api.h>
#include <memory>

class QWidget;

class QScreen;

class QRectF;

class QSize;

class QImage;

enum class InputType
{
  INVALID , SCREEN , WIDGET
};

/**
 * Represents an video source.
 *
 * Instances of this class may wrap a QWidget or a QScreen.
 *
 * Use Input::render() to take a screenshot.
 */
class ACUTERECORDER_API Input
{

  QWidget *widget_;
  QScreen *screen_;

public:

  /**
   * Creates an invalid input.
   *
   * This input cannot be used to take screenshots.
   * Use it only as a placeholder.
   */
  explicit Input( );

  /**
   * Creates an input that wraps a QWidget.
   * @param widget the widget.
   */
  explicit Input( QWidget *widget );

  /**
   * Creates an input tha wraps a QScreen.
   * @param screen the screen.
   */
  explicit Input( QScreen *screen );

  /**
   * Returns the type of this input.
   *
   * If the type is INVALID, this input can't be used to take screenshots.
   *
   * @return the input type.
   */
  InputType getType( ) const;

  /**
   * Returns whether this input represents a QWidget.
   *
   * @return whether this input represents a QWidget.
   */
  bool isWidget( ) const;

  /**
   * Returns whether this input represents a QScreen.
   *
   * @return whether this input represents a QScreen.
   */
  bool isScreen( ) const;

  /**
   * Returns the represented QWidget.
   * This method returns nullptr if this input doesn't represent a QWidget.
   * @return the QWidget.
   */
  QWidget *getWidget( ) const;

  /**
 * Returns the represented QScreen.
 * This method returns nullptr if this input doesn't represent a QScreen.
 * @return the QScreen.
 */
  QScreen *getScreen( ) const;

  /**
   * Returns the size of the represented element.
   *
   * @return the size.
   */
  QSize getSize( ) const;

  /**
   * Takes a screenshot of the represented QWidget or QScreen.
   *
   * @param inputArea the area of the element to render as a normalized
   *                  viewport.
   * @param outputSize the size of the output. The render will be stretched
   *                    to fit this size.
   * @return the QImage representing the screenshot.
   */
  std::shared_ptr< QImage >
  render( const QRectF& inputArea , const QSize& outputSize ) const;

};


#endif //ACUTERECORDER_OUTPUT_H
