#include <QApplication>
#include "region/MainWindowRegion.h"
#include "constant/QtUtils.h"

namespace qt_recorder
{

  void initRecorder( QWidget *widgetToRender )
  {
    auto data = new RecorderGeneralData( );
    data->renderingWidget = widgetToRender;
    data->selectedWidget = widgetToRender;

    auto *window = new MainWindowRegion( nullptr , data );
    data->recorderWidget = window;
    window->setStyleSheet( qt_utils::readStyle( ));
    window->show( );
  }
}

int main( int argc , char **argv )
{
  QApplication app( argc , argv );

  auto dummy = new QWidget( );
  dummy->setLayout( new QVBoxLayout( dummy ));
  dummy->layout( )->addWidget( new QLabel( "Hello there!" ));
  dummy->layout( )->addWidget( new QLabel( "Hello there 2!" ));
  dummy->layout( )->addWidget( new QLabel( "Hello there 3!" ));
  dummy->layout( )->addWidget( new QLabel( "Hello there 4!" ));
  dummy->layout( )->addWidget( new QLabel( "Hello there 5!" ));
  dummy->layout( )->addWidget( new QLabel( "Hello there 6!" ));
  dummy->show( );

  qt_recorder::initRecorder( dummy );

  return QApplication::exec( );
}


