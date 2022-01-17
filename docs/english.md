# AcuteRecorder - Widget recorder for Qt

(c) 2021-2022. GMRV / URJC

## Index

- [API architecture](#API architecture)
- [Creating a recorder](#Creating a recorder)
- [Creating a new storage worker](#Creating a new storage worker)

## API architecture

_AcuteRecorder_ can be split into three main components:

- A settings object (_RecorderSettings_): contains all the user-set parameters used by the other components.
- A recorder (_Recorder_): it can be considered a core that connects the other two components. It is in charge of
  starting and stopping the recording and creating frames.
- A storage worker (_RecorderStorageWorker_): it creates and manages a thread that receives frames and stores them in a
  selected format.

Every storage worker is represented by a _WorkerBuilder_. This object is in charge of creating storage workers. They
also indicate whether storage workers of its type can be created in the application's current context.

## Creating a recorder

### Step 1: create a settings object

The first thing you have to do is create a _RecorderSettings_ object.

```c++
RecorderSettings config = RecorderSettings( )
  .input( screen )
  .inputArea( QRectF( 0 , 0 , 1 , 1 ))
  .fps( 60 )
  .outputPath( "output.mp4" )
  .outputSize( QSize( 1920 , 1080 ))
  .storageWorker( "FFMPEG" );
```

You have to set the following parameters:

- The input object (_input_): it can be a _QWidget_ or a _QScreen_.
- The input area (_inputArea_): a normalized area (an area whose values are between 0 and 1) that represents the area of
  the input to record. If you want to record all the element, you must set the value _QRectF( 0 , 0 , 1 , 1 )_.
- The frames per second (_fps_): the frames per seconds the storage worker will use to storage the video. This value **
  WON'T** be used by the recorder to invoke _takeFrame()_ automatically. This issue will be addressed later.
- The output file / folder (_outputPath_): the file or folder where the video will be stored.
- The size of the frames (_outputSize_): the size of the frames. The recorder will scale the frames to this size
  automatically. You can assign this value depending on the input size using _outputScaledSize(const QSizeF)_.
- The storage worker type (_storageWorker_): the name of the type of storage worker to use in the recording.

Use _Recorder::getWorkerBuilders()_ if you want to know the registered storage workers builders.

Once you finish setting the parameters, you can check if you have set all the required values using _isValid()_. This
method **WON'T** check if the set storage worker name is valid.

### Step 2: create a recorder

Now that you have your valid _RecorderSettings_, you can create the recorder in just one line:

```c++
Recorder recorder = new Recorder( config );
```

The constructor will create the storage worker and will configure all the recording automatically.

For flexibility reasons, the recorder won't take frames automatically. You must call _takeFrame()_ every time you want
to take a frame. You can use a _QTimer_ to make the recorder take a frame every amount of time.

```c++
QTimer *timer = new QTimer( );
QObject::connect( timer, SIGNAL( timeout( )), recorder ,SLOT( takeFrame( )));
timer->start( 1000 / builder.getFPS( ));
```

### Step 3: manage the recorder

Once started, you can manage different aspects of the recording.

Use the _bufferSizeChange(int)_ signal to know how many images the storage worker's buffer contains. Use the
_finished()_ signal to know when the recording has finished.

Use _stop()_ to stop the recording. This won't finish the recording instantaneously: the storage worker's buffer must be
depleted first. Use the _finished()_ signal to execute code after the recording has finished.

## Creating a new storage worker

Currently, _AcuteRecorder_ supports two types of storage workers:

- _ffmpeg_: allows creating _MP4_ videos using the _FFMPEG_ library. Requires _FFMPEG_ to be installed.
- _images_: saves the frames of the video in a folder. Each frame represented by a _PNG_ image.

You can create your custom storage worker in three easy steps:

### Step 1: create a storage worker class

The first thing you have to do is to create a new class that extends _RecorderStorageWorker_.

You must override the following methods:

- _push(QImage*)_: used by the recorder to send frames to the storage worker. The storage worker must delete the image
  after it has been stored.
- _stop()_: invoked when the recording must stop.
- _fileQueueSizeChanged(int)_: signal that notices about the amount of images inside the queue (if the worker contains
  one). You must override it and leave it without an implementation.

### Step 2: create a storage worker builder class

The next thing you have to do is to create a new class that extends _WorkerBuilder_. This class will have only one
instance that will represent the type of the storage builder you have created.

You must override the following methods:

- _isAvailable()_: returns whether storage workers of this type can be created in the application's current context.
- _createWorker()_: creates a new storage worker of the represented type.

### Step 3: register the storage worker builder.

Now you just have to register the builder:

```c++
Recorder::registerWorker("my_worker", new MyWorkerBuilder());
```