#include <iostream>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsAnchorLayout>
#include <QLayout>
#include <thread>
#include "render/WidgetRenderThread.h"

int main( int argc , char **argv )
{
  // Lo primero que hay que hacer es encender la librería de Qt, para eso hay que crear un QApplication.
  // Esto configura nuestro thread actual para que pueda ser usado por una ventana.
  QApplication app( argc , argv );

  // Una ventana de Qt está compuesta por un conjunto de widgets ordenados en un árbol de herencias.
  // Aquí creamos el widget que contendrá todos nuestros elementos.
  QWidget window;

  // Lo mejor para crear aplicaciones de Qt es usar layouts. Un layout le dice a la aplicación cómo se van
  // a ordenar los elementos que están dentro. En este caso crearmos un layout que ordenará nuestros elementos
  // de manera horizontal: [Button1] [Button2]
  // Hay muchos más layouts: VBox, Grid...
  QHBoxLayout layout( &window );

  // Creamos nuestro primer botón. En este caso el texto que tendrá será "Button1" y tendrá un tamaño mínimo de 200x100.
  // También hemos hecho que al presionarlo se ponga de color rojo.
  // Como queremos que esté dentro del layout lo añadimos con layout.addWidget().
  QPushButton button( "Button1" );
  button.setMinimumWidth( 200 );
  button.setMinimumHeight( 100 );
  button.setStyleSheet( "QPushButton:pressed { background-color: red }" );
  layout.addWidget( &button );

  // A los objetos de Qt les asignamos acciones con el método QObject::connect.
  // El primer parámetro es el objeto que va a realizar la acción. En nuestro caso es el botón.
  // En el segundo parámetro indicamos el SIGNAL que queremos escuchar. En este caso queremos
  // que nuesta acción ocurra cuando le demos click. Recuerda la palabra SIGNAL: son los métodos de un objeto
  // que pueden ser conectados a acciones.
  // En el tercer parámetro asignamos una función lambda que imprime "Hi!". Se puede también llamar a un
  // método de otro objeto de Qt, pasándolo como tercer parámetro y el método como cuarto parámetro. Busca
  // en la guía de Qt más información sobre el connect si quieres saber más.
  QObject::connect( &button , &QPushButton::clicked , [ ]( )
  { std::cout << "Hi!" << std::endl; } );

  // Creamos un segundo botón para ver que el layout sí funciona. En este caso no le ponemos un tamaño mínimo
  // para que se vea la diferencia.
  QPushButton button2( "Button2" );
  layout.addWidget( &button2 );

  // También podemos crear widgets que no estén dentro de un layout. Para eso tenemos que pasarle el widget
  // padre como segundo parámetro. ESTO NO ES RECOMENDABLE, ya que este widget no respetará el tamaño de la ventana.
  QPushButton button3( "Button3" , &window );
  button3.setMinimumWidth( 300 );
  button3.setMinimumHeight( 300 );

  // Ahora tenemos que mostrar la ventana de Qt. Para ello simplemente llamamos al método show() del widget padre.
  window.show( );

  // Podemos mostrar más ventanas en un mismo hilo. En este caso la ventana será solo un botón. Esta ventana
  // compartirá thread con la ventana del widget "window".
  QPushButton button4( "AnotherWindow" );
  button4.show( );

  // Por último, le pasamos el control al manejador de ventanas de Qt. Cuando ejecutamos el método QApplication::exec
  // YA NO PODREMOS EJECUTAR MÁS CÓDIGO: el thread se quedará bloqueado y será usado por el controlador de Qt.
  // Cuando todas las ventanas se cierren el manejador devolverá 0 y el programa terminará.
  return QApplication::exec( );
}
