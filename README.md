# AcuteRecorder - Widget recorder for Qt

(c) 2021-2022 VG-LAB / URJC

![AcuteRecorderGui](https://user-images.githubusercontent.com/12167134/151855289-22cb478a-6e5a-4427-99e2-9fae234cacdc.png)

## Introduction

AcuteRecorder is a library for Qt apps that allows to record Qt widgets and Qt Screens.

## Dependencies

* Qt 5.X (Qt5Widgets)

## Documentation

- [English](docs/english.md)
- [Spanish](docs/spanish.md)

## Building

AcuteRecorder has been successfully built and used on Ubuntu 20.04/18.04, Windows 7, macOS Sierra
and Windows 11 using Ubuntu 20.04 on WSL/WSLg.

```bash
git clone --recursive https://github.com/vg-lab/AcuteRecorder.git AcuteRecorder
mkdir AcuteRecorder/build && cd AcuteRecorder/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCLONE_SUBPROJECTS=ON
make
```
