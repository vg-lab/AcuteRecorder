//
// Created by Gael Rial Costas on 1/9/21.
//

#include <acuterecorder/acuterecorder.h>

#include <element/FPSTextField.h>

#include <constant/Styles.h>

FPSTextField::FPSTextField( QWidget *parent , RecorderGeneralData *d )
  : QLineEdit( parent ) , data_( d )
{

  setProperty( "class" , styles::FPS );
  setText( QString::number( d->fps ));
  QObject::connect( this , SIGNAL( editingFinished( )) ,
                    this , SLOT( onFPSChange( )));
}

void FPSTextField::onFPSChange( )
{
  bool ok;
  int value = text( ).toInt( &ok );
  if ( value == data_->fps ) return;
  if ( !ok || value < 1 )
    setText( QString::number( data_->fps ));
  else
    data_->fps = value;
}
