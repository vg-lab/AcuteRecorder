#include <QApplication>

#include <region/MainWindowRegion.h>
#include <util/QtUtils.h>

namespace acute_recorder
{

  void initRecorder( QWidget *widgetToRender )
  {
    auto data = new RecorderGeneralData( );
    data->renderingWidget = widgetToRender;
    data->selectedWidget = widgetToRender;

    auto *window = new MainWindowRegion( nullptr , data );
    window->setWindowTitle("Acute Recorder");
    data->recorderWidget = window;
    window->setStyleSheet( qt_utils::readStyle( ));
    window->resize(600, 600);
    window->show( );

    QObject::connect(window, SIGNAL(terminated()), widgetToRender, SLOT(close()));
  }
}

int main( int argc , char **argv )
{
  QApplication app( argc , argv );

  QWidget dummy;
  dummy.setLayout( new QVBoxLayout( &dummy ));
  dummy.layout( )->addWidget( new QLabel( "Hello there!" ));
  dummy.layout( )->addWidget( new QLabel( "Hello there 2!" ));
  dummy.layout( )->addWidget( new QLabel( "Hello there 3!" ));
  dummy.layout( )->addWidget( new QLabel( "Hello there 4!" ));
  dummy.layout( )->addWidget( new QLabel( "Hello there 5!" ));
  dummy.layout( )->addWidget( new QLabel( "Hello there 6!" ));
  dummy.setProperty("dummyWidget", true);
  dummy.show( );

  acute_recorder::initRecorder( &dummy );

  const auto retValue = QApplication::exec();

  return retValue;
}
