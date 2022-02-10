//
// Created by Gael Rial Costas on 16/8/21.
//

#include "SelectionModeRegion.h"

#include <QHBoxLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

#include <acuterecorder/dialog/constant/Styles.h>
#include <acuterecorder/dialog/RSWParameters.h>

SelectionModeRegion::SelectionModeRegion( QWidget *parent ,
                                          const RSWParameters& parameters )
  : QWidget( parent )
  , fullButton_( new QRadioButton( "Full" , this ))
  , areaButton_( new QRadioButton( "Area" , this ))
  , widgetButton_( new QRadioButton( "Widget" , this ))
  , fpsSpinBox_( new QSpinBox( this ))
{
  auto layout = new QHBoxLayout( this );
  layout->setAlignment( Qt::AlignAbsolute );
  layout->setMargin( 0 );

  setProperty( "class" , styles::REGION_SELECTION_MODE );
  setLayout( layout );

  fullButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  areaButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );
  widgetButton_->setProperty( "class" , styles::SELECTION_RADIO_BUTTON );

  auto label = new QLabel( "Source:" );
  label->setProperty( "class" , styles::INFO_LABEL );

  auto fpsLabel = new QLabel( "FPS:" );
  fpsLabel->setProperty( "class" , styles::SECONDARY_INFO_LABEL );

  fpsSpinBox_->setProperty( "class" , styles::FPS );
  fpsSpinBox_->setMinimum( 1 );
  fpsSpinBox_->setMaximum( 1000 );
  fpsSpinBox_->setValue( parameters.defaultFPS );

  layout->addWidget( label );
  layout->addWidget( fullButton_ );
  layout->addWidget( areaButton_ );
  layout->addWidget( widgetButton_ );
  layout->addSpacing( 10 );
  layout->addWidget( fpsLabel );
  layout->addWidget( fpsSpinBox_ );
  layout->addStretch( );

  fullButton_->setVisible(
    parameters.showSourceParameters && parameters.showFullSourceMode );
  areaButton_->setVisible(
    parameters.showSourceParameters && parameters.showAreaSourceMode );
  widgetButton_->setVisible(
    parameters.showSourceParameters && parameters.showWidgetSourceMode );

  label->setVisible(
    parameters.showSourceParameters && (
      parameters.showFullSourceMode
      || parameters.showAreaSourceMode
      || parameters.showWidgetSourceMode ));

  fpsLabel->setVisible( parameters.showFPS );
  fpsSpinBox_->setVisible( parameters.showFPS );

  switch ( parameters.defaultSelectionMode )
  {
    case SelectionMode::FULL:
      fullButton_->setChecked( true );
      break;
    case SelectionMode::AREA:
      areaButton_->setChecked( true );
      break;
    case SelectionMode::WIDGET:
      widgetButton_->setChecked( true );
      break;
  }

  QString tooltip = "Here you can configure the area of the video to record.";

  if ( parameters.showFullSourceMode )
  {
    tooltip += "\nFull: records the full area of the input.";
  }

  if ( parameters.showAreaSourceMode )
  {
    tooltip += "\nArea: records a selected area of the input.";
  }

  if ( parameters.showWidgetSourceMode )
  {
    tooltip += "\nWidget: records a sub-widget of the input.";
  }

  label->setToolTip( tooltip );

  fpsLabel->setToolTip( "The frames per second of the output video." );

  QObject::connect(
    fullButton_ , SIGNAL( toggled( bool )) ,
    this , SLOT( refreshSelectionMode( ))
  );
  QObject::connect(
    areaButton_ , SIGNAL( toggled( bool )) ,
    this , SLOT( refreshSelectionMode( ))
  );
  QObject::connect(
    widgetButton_ , SIGNAL( toggled( bool )) ,
    this , SLOT( refreshSelectionMode( ))
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

void SelectionModeRegion::changeInput( Input input )
{
  if ( input.isWidget( ))
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