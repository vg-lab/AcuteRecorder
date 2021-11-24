//
// Created by Gael Rial Costas on 17/8/21.
//

#include "OutputRegion.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include <constant/Styles.h>

OutputRegion::OutputRegion( QWidget *p ) : QWidget( p )
{
  auto layout = new QHBoxLayout( this );

  setProperty( "class" , styles::REGION_OUTPUT );
  setLayout( layout );

  outputTextField_ = new QLineEdit( this );
  auto button = new QPushButton( "Select" , this );

  outputTextField_->setProperty( "class" , styles::OUTPUT_TEXT_FIELD );
  button->setProperty( "class" , styles::OUTPUT_FILE_BUTTON );

  outputTextField_->setText("output.mp4");

  auto label = new QLabel( "Output:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  layout->addWidget( label );
  layout->addWidget( outputTextField_ );
  layout->addWidget( button );

  QObject::connect(
    button , &QPushButton::pressed ,
    this , &OutputRegion::openFileDialog
  );
}

QString OutputRegion::getOutputPath( )
{
  return outputTextField_->text( );
}

void OutputRegion::openFileDialog( )
{
  auto result = QFileDialog::getSaveFileName(
    this ,
    "Select output" ,
    "~/" ,
    "*.mp4"
  );
  if ( result.isEmpty( )) return;
  outputTextField_->setText( result );
}
