//
// Created by Gael Rial Costas on 18/11/2021.
//

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
