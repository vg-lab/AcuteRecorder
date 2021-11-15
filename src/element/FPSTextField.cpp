//
// Created by Gael Rial Costas on 1/9/21.
//

#include "FPSTextField.h"

#include <constant/Styles.h>

FPSTextField::FPSTextField( QWidget *parent , RecorderGeneralData *data )
  : QLineEdit( parent ) , data_( data )
{

  setProperty( "class" , styles::FPS );
  setText( QString::number( data->fps ));
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
