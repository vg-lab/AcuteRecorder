//
// Created by Gael Rial Costas on 16/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "OutputTextField.h"

#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

#include <constant/Styles.h>

OutputTextField::OutputTextField( QWidget *parent , RecorderGeneralData *d )
  : QLineEdit( parent ) , data_( d )
{
  setProperty( "class" , styles::OUTPUT_TEXT_FIELD );
  setText( d->output );


  QObject::connect( this , &QLineEdit::textChanged ,
                    [ this ]( const QString& text )
                    {
                      data_->output = text;
                    } );
}
