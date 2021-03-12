#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsAnchorLayout>
#include <QLayout>
#include "MyRubberWindow.h"
#include "render/WidgetRenderThread.h"
#include <QtConcurrent/QtConcurrent>
#include <QMovie>
#include <QProgressBar>

void forEachNode( const QWidget *widget , int deep )
{
  std::cout << "Found " << typeid( *widget ).name( ) << " deep: " << deep
            << std::endl;

  auto& list = widget->children( );

    foreach( QObject *o , list )
    {
      if ( auto *w = dynamic_cast<QWidget *>(o))
      {
        forEachNode( w , deep + 1 );
      }
    }
}

QString readStyle( )
{
  QFile file( "style.css" );

  if ( !file.open( QFile::ReadOnly | QFile::Text )) return "";
  QTextStream in( &file );

  QString value = in.readAll( );

  file.close( );

  return value;
}

int main( int argc , char **argv )
{

  QApplication app( argc , argv );
  app.setStyleSheet( readStyle( ));

  auto *window = new QWidget( );
  QVBoxLayout mainLayout( window );

  QWidget bar;
  QHBoxLayout barLayout( &bar );
  mainLayout.addWidget( &bar );

  QPushButton button( "Start" );
  button.setMinimumWidth( 200 );
  button.setMinimumHeight( 100 );
  button.setProperty( "class" , "red-button" );
  barLayout.addWidget( &button );

  auto *manager = new WidgetRenderThread( QSize( 1920 , 1080 ) , 60 , window );

  QObject::connect( &button , &QPushButton::clicked , [ = ]( )
  {
    manager->start( );
  } );

  QPushButton button2( "Stop" );
  button2.setMinimumWidth( 200 );
  button2.setMinimumHeight( 100 );
  barLayout.addWidget( &button2 );

  QObject::connect( &button2 , &QPushButton::clicked , [ = ]( )
  {
    manager->stop( );
  } );

  QPushButton button3( "Screenshot" );
  button3.setMinimumWidth( 200 );
  button3.setMinimumHeight( 100 );
  button3.setProperty( "class" , "red-button" );
  button3.setIconSize( QSize( 400 , 400 ));
  barLayout.addWidget( &button3 );

  QObject::connect( &button3 , &QPushButton::clicked , [ = ]( )
  {
    QImage image( QSize( window->width( ) , window->height( )) ,
                  QImage::Format_RGB32 );

    QPainter painter( &image );
    window->render( &painter );

    auto *rubber = new MyRubberWindow( image );

    rubber->show( );
  } );


  auto store = manager->storeManager( );
  auto *progressBar = new QProgressBar( );
  progressBar->setProperty( "class" , "red-progress-bar" );
  mainLayout.addWidget( progressBar );

  QTimer timer( window );
  QObject::connect( &timer , &QTimer::timeout , [ = ]( )
  {
    progressBar->setValue( store->filesInQueue( ));
  } );

  timer.start( 100 );


  window->show( );

  forEachNode( window , 0 );

  return QApplication::exec( );
}