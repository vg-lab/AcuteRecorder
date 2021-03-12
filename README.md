# QtRecorder - Widget recorder for Qt
(c) 2021-2021. GMRV / URJC

## Introduction

QtRecorder is a module for Qt apps that allows to record Qt widgets.

## Dependencies

* Qt 5.X (Qt5Widgets)

## Building

QtRecorder has been successfully built and used on Ubuntu 20.04/18.04.

```bash
git clone --recursive https://gitlab.gmrv.es/degreestudents/qtrecorder.git QtRecorder
mkdir QtRecorder/build && cd QtRecorder/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCLONE_SUBPROJECTS=ON
make
```
