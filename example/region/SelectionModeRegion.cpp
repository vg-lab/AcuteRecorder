//
// Created by Gael Rial Costas on 16/8/21.
//

#include "SelectionModeRegion.h"

#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

#include <constant/Styles.h>

SelectionModeRegion::SelectionModeRegion( QWidget *parent )
  : QWidget( parent ) ,
    fullButton_( new QRadioButton( "Full" , this )) ,
    areaButton_( new QRadioButton( "Area" , this )) ,
    widgetButton_( new QRadioButton( "Widget" , this )) ,
    fpsSpinBox_( new QSpinBox( this ))
{
  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignAbsolute );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_SELECTION_MODE );
  setLayout( layout );

  fullButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  areaButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  widgetButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );

  fullButton_->setChecked( true );

  auto label = new QLabel( "Source:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  auto fpsLabel = new QLabel( "FPS:" );
  fpsLabel->setProperty( "class" , styles::SECONDARY_INFO_LABEL );

  fpsSpinBox_->setProperty( "class" , styles::FPS );
  fpsSpinBox_->setMinimum( 1 );
  fpsSpinBox_->setMaximum( 1000 );
  fpsSpinBox_->setValue( 60 );

  layout->addWidget( label );
  layout->addWidget( fullButton_ );
  layout->addWidget( areaButton_ );
  layout->addWidget( widgetButton_ );
  layout->addSpacing( 10 );
  layout->addWidget( fpsLabel );
  layout->addWidget( fpsSpinBox_ );
  layout->addStretch( );

  QObject::connect(
    fullButton_ , &QRadioButton::toggled ,
    this , &SelectionModeRegion::refreshSelectionMode
  );
  QObject::connect(
    areaButton_ , &QRadioButton::toggled ,
    this , &SelectionModeRegion::refreshSelectionMode
  );
  QObject::connect(
    widgetButton_ , &QRadioButton::toggled ,
    this , &SelectionModeRegion::refreshSelectionMode
  );
}

SelectionMode SelectionModeRegion::getSelectionMode( ) const
{
  if ( fullButton_->isChecked( ))
  {
    return SelectionMode::FULL;
  }
  if ( areaButton_->isChecked( ))
  {
    return SelectionMode::AREA;
  }
  return SelectionMode::WIDGET;
}

int SelectionModeRegion::getFPS( ) const
{
  return fpsSpinBox_->value( );
}

void SelectionModeRegion::changeScreen( QScreen *screen )
{
  if ( screen == nullptr )
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

void SelectionModeRegion::refreshSelectionMode( )
{
  emit selectionModeChanged( getSelectionMode( ));
}