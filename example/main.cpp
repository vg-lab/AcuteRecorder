#include <QApplication>

#include <QLabel>
#include <QDebug>

#include <region/MainWindowRegion.h>
#include <util/QtUtils.h>

#include <acuterecorder/acuterecorder.h>

namespace acute_recorder
{

  void initDummy( QWidget& dummy )
  {
    dummy.setLayout( new QVBoxLayout( &dummy ));
    dummy.layout( )->addWidget( new QLabel( "Hello there!" ));
    dummy.layout( )->addWidget( new QLabel( "Hello there 2!" ));
    dummy.layout( )->addWidget( new QLabel( "Hello there 3!" ));
    dummy.layout( )->addWidget( new QLabel( "Hello there 4!" ));
    dummy.layout( )->addWidget( new QLabel( "Hello there 5!" ));
    dummy.layout( )->addWidget( new QLabel( "Hello there 6!" ));
    dummy.setProperty( "dummyWidget" , true );
  }

  void initRecorder( QWidget *widgetToRender )
  {

    auto *window = new MainWindowRegion( nullptr , widgetToRender );
    window->setWindowTitle( "Acute Recorder" );
    window->setStyleSheet( qt_utils::readStyle( ));
    window->resize( 600 , 600 );
    window->show( );

    QObject::connect( window , SIGNAL( terminated( )) , widgetToRender ,
                      SLOT( close( )));
  }

  void testRecorderSettingsDialog( QWidget *widgetToRender )
  {

    RSWParameters parameters;
    parameters.widgetsToRecord.emplace_back("Test widget", widgetToRender );
    parameters.defaultSelectionMode = SelectionMode::AREA;
    parameters.showWorker = false;
    parameters.showSourceParameters = false;

    parameters.defaultOutputSizeScaled = true;
    parameters.showOutputSizeParameters = false;

    parameters.defaultFPS = 120;

    auto dialog = new RecorderSettingsDialog( nullptr , parameters );
    if ( dialog->exec( ))
    {
      qDebug( ) << "Dialog finished";
      RecorderSettings settings = dialog->getSettings( );
      qDebug( ) << "Input area: " << settings.getInputArea( );
      qDebug( ) << "Output area: " << settings.getOutputSize( );
      qDebug( ) << "Output FPS: " << settings.getFPS( );
      qDebug( ) << "Output path: " << settings.getOutputPath( );
      qDebug( ) << "Storage worker: " << settings.getStorageWorker( );

      qDebug() << "Settings valid: " << settings.isValid();

      if(!settings.isValid()) settings.invalidParametersDebug();
    }
    else
    {
      qDebug( ) << "Dialog cancelled.";
    }
  }

  void testRecorderDialog( QWidget *widgetToRender )
  {
    RSWParameters parameters;
    parameters.widgetsToRecord.emplace_back("Test widget", widgetToRender );
    auto dialog = new RecorderDialog( nullptr , parameters , false );
    if ( dialog->exec( ))
    {
      auto recorder = dialog->getRecorder( );
      qDebug( ) << "Test finished. Stopping recorder...";
      recorder->stop( );
    }
    else
    {
      qDebug( ) << "Dialog cancelled.";
    }
  }
}

int main( int argc , char **argv )
{
  QApplication app( argc , argv );

  QWidget dummy;
  acute_recorder::initDummy( dummy );
  dummy.show( );

  if ( argc > 1 )
  {
    if ( strcmp( argv[ 1 ] , "-help" ) == 0 )
    {
      qDebug( ) << "Commands:";
      qDebug( ) << argv[ 0 ] << " -help  Shows this menu";
      qDebug( ) << argv[ 0 ] << " -rsd   Shows the recorder settings dialog.";
      qDebug( ) << argv[ 0 ] << " -rd    Shows the recorder dialog.";
      return 0;
    }
    else if ( strcmp( argv[ 1 ] , "-rsd" ) == 0 )
    {
      acute_recorder::testRecorderSettingsDialog( &dummy );
      return 0;
    }
    else if ( strcmp( argv[ 1 ] , "-rd" ) == 0 )
    {
      acute_recorder::testRecorderDialog( &dummy );
      return 0;
    }
  }

  acute_recorder::initRecorder( &dummy );
  return QApplication::exec( );
}
