//
// Created by Gael Rial Costas on 17/8/21.
//

#include <acuterecorder/acuterecorder.h>

#include "OutputRegion.h"

#include <QHBoxLayout>
#include <QLabel>

#include <constant/Styles.h>

OutputRegion::OutputRegion( QWidget *p , RecorderGeneralData *d )
: QWidget(p)
{
  auto layout = new QHBoxLayout( this );

  setProperty( "class" , styles::REGION_OUTPUT );
  setLayout( layout );

  outputTextField_ = new OutputTextField( this , d );
  outputFileButton_ = new OutputFileButton( this , outputTextField_ );

  auto label = new QLabel( "Output:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  layout->addWidget( label );
  layout->addWidget( outputTextField_ );
  layout->addWidget( outputFileButton_ );
}

OutputTextField *OutputRegion::outputTextField( ) const
{
  return outputTextField_;
}

OutputFileButton *OutputRegion::outputFileButton( ) const
{
  return outputFileButton_;
}
