//
// Created by Gael Rial Costas on 16/8/21.
//

#include "OutputTextField.h"
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include "../constant/Styles.h"

OutputTextField::OutputTextField( QWidget *parent , RecorderGeneralData *data )
  : QLineEdit( parent ) , data_( data )
{
  setProperty( "class" , styles::OUTPUT_TEXT_FIELD );
  setText( data->output );


  QObject::connect( this , &QLineEdit::textChanged ,
                    [ this ]( const QString& text )
                    {
                      data_->output = text;
                    } );
}