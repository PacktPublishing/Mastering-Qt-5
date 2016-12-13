# Packaging

## Environment variables
To package the application, you should have the environment variables exported (e.g. in your `.bashrc`). Update the paths according to your machine installation:
### Common
```bash
export QTROOT=$HOME/qt/5.7
```
### Linux
```bash
export QTDIR=$QTROOT/gcc_64
```
### Windows
```bash
set QTDIR=C:\Qt\5.7\mingw49_32
set MINGWROOT=C:\Qt\Tools\mingw492_32
```
### MacOSX
```bash
export QTDIR=$QTROOT/clang_64
```

### Android
```bash
export QTDIR_ANDROID=$QTROOT/android_armv7
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export ANT_ROOT=/opt/apache-ant
export ANDROID_SDK_ROOT=$HOME/android-sdk
export ANDROID_NDK_ROOT=$HOME/android-ndk
```
### iOS
```bash
export QTDIR_IOS=$QTROOT/ios
```

## Linux and AppImage
AppImage packaging is done using the tool `linuxdeployqt`. You can download the linuxdeployqt AppImage [here](https://github.com/probonopd/linuxdeployqt/releases).
linuxdeployqt binary must be present in your $PATH variable.

