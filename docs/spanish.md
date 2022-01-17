# AcuteRecorder - Widget recorder for Qt

(c) 2021-2022. GMRV / URJC

## Índice

- [Arquitectura de la librería](#Arquitectura de la librería)
- [Creando una grabación](#Creando una grabación)
- [Creando un nuevo tipo de objeto de guardado](#Creando un nuevo tipo de objeto de guardado)

## Arquitectura de la librería

_AcuteRecorder_ está compuesto por tres componentes principales:

- Un objeto de configuración (_RecorderSettings_): informa al resto de componentes de todos los parámetros necesarios
  para la grabación.
- Un objeto de grabación (_Recorder_): actúa de núcleo entre los diferentes componentes. Es el encargado de empezar,
  parar y crear los frames de la grabación.
- Un objeto de guardado (_RecorderStorageWorker_): crea y gestiona un hilo que recibe los frames de la clase _Recorder_
  y los almacena de una manera concreta.

Cada tipo de *RecorderStorageWorker* es representado por un objeto _WorkerBuilder_. Este objeto es el encargado de crear
los _RecorderStorageWorker_ e indicar si estos se pueden crear en el contexto actual de la aplicación.

## Creando una grabación

### Paso 1: crear un objeto de configuración

Lo primero que hay que hacer para empezar una grabación es crear un objeto de configuración.

```c++
RecorderSettings config = RecorderSettings( )
  .input( screen )
  .inputArea( QRectF( 0 , 0 , 1 , 1 ))
  .fps( 60 )
  .outputPath( "output.mp4" )
  .outputSize( QSize( 1920 , 1080 ))
  .storageWorker( "FFMPEG" );
```

Es necesario configurar los siguientes parámetros:

- El objeto a grabar (_input_): puede ser un _QWidget_ o un _QScreen_.
- El área de grabación (_inputArea_): área normalizada (valores entre el 0 y el 1) que indica al grabador qué área del
  _QWidget_ o _QScreen_ debe grabar. Si se desea grabar todo el elemento, se debe introducir un
  _QRectF( 0 , 0 , 1 , 1 )_.
- Los frames por segundo (_fps_): le indica al objeto de guardado a cuantos FPS debe guardar el vídeo. Este valor **NO**
  le indica a la grabación cuantas veces por segundo debe invocar el método _takeFrame()_. Esto se verá más adelante.
- El archivo / carpeta de guardado (_outputPath_): el archivo o carpeta donde el vídeo va a ser guardado.
- El tamaño de los frames (_outputSize_): el tamaño de cada frame a guardar. El grabador escalará automáticamente la
  imagen si es necesario. Se puede asignar este valor con respecto al tamaño de la entrada usando el método
  _outputScaledSize(const QSizeF)_.
- El tipo de objeto de guardado (_storageWorker_): indica el objeto de guardado que se debe usar en la grabación.

Si deseas conocer cuáles son los objetos de guardado registrados en la librería, usa el método estático
_Recorder::getWorkerBuilders()_.

Una vez creada la configuración, se puede comprobar si se han añadido todos los parámetros necesarios usando el método
_isValid()_. Este método **NO** comprueba si el objeto de guardado es válido.

### Paso 2: crear un objeto de grabación

Una vez que se ha creado la configuración, se puede crear el objeto de grabación en una sola línea:

```c++
Recorder recorder = new Recorder( config );
```

El constructor creará el objeto de guardado y configurará toda la grabación automáticamente.

Por motivos de flexibilidad, el grabador no tomará frames automáticamente. Se debe llamar al método
_takeFrame()_ cada vez que se quiera tomar un frame. Se debe usar un _QTimer_ para que el grabador tome una imagen cada
cierto tiempo.

```c++
QTimer *timer = new QTimer( );
QObject::connect( timer, SIGNAL( timeout( )), recorder ,SLOT( takeFrame( )));
timer->start( 1000 / builder.getFPS( ));
```

### Paso 3: administrar la grabación

Una vez iniciada la grabación, se puede acceder a varios datos acerca de su estado.

La señal _bufferSizeChange(int)_ permite saber cuantos elementos hay en el buffer del objeto de guardado. La señal
_finished()_ es invocada cuando la grabación termina.

Para terminar la grabación, se debe utilizar el método _stop()_. Cabe destacar que la grabación no terminará
instantáneamente, ya que el buffer del objeto de guardado debe vaciarse. Usa la señal _finished()_ para realizar
acciones cuando todo el proceso de grabación haya terminado.

## Creando un nuevo tipo de objeto de guardado

Actualmente, _AcuteRecorder_ soporta dos tipos de objetos de guardado:

- _ffmpeg_: permite generar archivos _MP4_ usando la librería _FFMPEG_. Requiere que _FFMPEG_ esté instalado.
- _images_: guarda todos los frames del vídeo en una carpeta. Los frames son imágenes en formato _PNG_.

Si necesitas un objeto de guardado en concreto, puedes añadirlo de manera muy sencilla:

### Paso 1: crear una clase de guardado

Lo primero que se debe hacer es crear una clase hija de _RecorderStorageWorker_.

Los métodos que se han de sobreescribir son los siguientes:

- _push(QImage*)_: método usado por el grabador para enviar un frame al objeto de guardado. El objeto de guardado tendrá
  que eliminar la imagen una vez haya terminado de guardarla.
- _stop()_: le indica al objeto de guardado que la grabación ha terminado.
- _fileQueueSizeChanged(int)_: señal que permite exportar el número de frames dentro de la cola del objeto de guardado
  (si este tiene una). Simplemente se debe sobreescribir y dejar sin implementar.

### Paso 2: crear una clase constructora de objetos de guardado

Lo siguiente que se debe hacer es crear una clase hija de _WorkerBuilder_. Esta clase solo tendrá un objeto inicializado
que representará al tipo de objeto de guardado que has creado.

Los métodos que se han de sobreescribir son los siguientes:

- _isAvailable()_: devuelve verdadero si se pueden crear objetos de guardado del tipo representado en el contexto actual
  de la aplicación.
- _createWorker()_: crea un objeto de guardado del tipo representado.

### Paso 3: registrar la clase constructora

Ahora solo queda registrar la clase constructora en la librería.

```c++
Recorder::registerWorker("my_worker", new MyWorkerBuilder());
```