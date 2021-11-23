//
// Created by gaelr on 18/11/2021.
//

#ifndef ACUTERECORDER_OUTPUT_H
#define ACUTERECORDER_OUTPUT_H


class QWidget;
class QScreen;
class QRectF;
class QSize;
class QImage;

enum class InputType
{
  INVALID , SCREEN , WIDGET
};

class Input
{

  QWidget *widget_;
  QScreen *screen_;

public:

  explicit Input( );

  explicit Input( QWidget *widget );

  explicit Input( QScreen *screen );

  InputType getType( ) const;

  bool isWidget( ) const;

  bool isScreen( ) const;

  QSize getSize () const;

  QImage * render( const QRectF& inputArea , const QSize& outputSize ) const;

};


#endif //ACUTERECORDER_OUTPUT_H
