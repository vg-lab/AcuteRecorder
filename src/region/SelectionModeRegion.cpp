//
// Created by Gael Rial Costas on 16/8/21.
//

#include <QHBoxLayout>
#include "SelectionModeRegion.h"
#include "../constant/Styles.h"
#include "../element/FPSTextField.h"

SelectionModeRegion::SelectionModeRegion( QWidget *parent ,
                                          RecorderGeneralData *data ,
                                          SelectionArea *selectionArea )
  : QWidget( parent ) , data_( data ) , selectionArea_( selectionArea )
{
  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignAbsolute );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_SELECTION_MODE );
  setLayout( layout );

  fullButton_ = new SelectionModeButton( "Full" , this , FULL , this );
  areaButton_ = new SelectionModeButton( "Area" , this , AREA , this );
  widgetButton_ = new SelectionModeButton( "Widget" , this , WIDGET , this );
  fullButton_->setChecked( true );

  auto label = new QLabel( "Source:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  auto fpsLabel = new QLabel( "FPS:" );
  fpsLabel->setProperty( "class" , styles::SECONDARY_INFO_LABEL );

  fpsTextField_ = new FPSTextField( this , data_ );
  fpsTextField_->setProperty( "class" , styles::FPS );

  layout->addWidget( label );
  layout->addWidget( fullButton_ );
  layout->addWidget( areaButton_ );
  layout->addWidget( widgetButton_ );
  layout->addSpacing( 10 );
  layout->addWidget( fpsLabel );
  layout->addWidget( fpsTextField_ );
  layout->addStretch( );
}

SelectionArea *SelectionModeRegion::selectionArea( ) const
{
  return selectionArea_;
}

RecorderGeneralData *SelectionModeRegion::data( ) const
{
  return data_;
}

void SelectionModeRegion::refreshWidget( )
{
  if ( data_->screen == nullptr )
  {
    widgetButton_->setEnabled( true );
  }
  else
  {
    if ( widgetButton_->isChecked( ))
    {
      fullButton_->setChecked( true );
    }
    widgetButton_->setEnabled( false );
  }
}
