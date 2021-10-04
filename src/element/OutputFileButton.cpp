//
// Created by Gael Rial Costas on 17/8/21.
//

#include <QFileDialog>
#include "OutputFileButton.h"
#include "../constant/Styles.h"

OutputFileButton::OutputFileButton( QWidget *parent ,
                                    OutputTextField *outputTextField )
  : QPushButton( "Select" , parent ) , outputTextField_( outputTextField )
{

  setProperty( "class" , styles::OUTPUT_FILE_BUTTON );

  QObject::connect( this , &QPushButton::pressed , [ this ]( )
  {
    auto result = QFileDialog::getSaveFileName(
      this ,
      "Select output" ,
      "~/" ,
      "*.mp4"
    );
    if ( result.isEmpty( )) return;
    outputTextField_->setText( result );
  } );

}
