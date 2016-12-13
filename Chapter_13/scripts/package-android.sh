#!/bin/bash

DIST_DIR=dist/mobile-android
BUILD_DIR=build
APK_DIR=apk
KEYSTORE_PATH="$(pwd)/scripts/android-data"
ANDROID_BUILD_PATH="$(pwd)/$DIST_DIR/$BUILD_DIR/android-build"

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $APK_DIR $BUILD_DIR

pushd $BUILD_DIR
$QTDIR_ANDROID/bin/qmake \
    -spec android-g++ \
    "CONFIG += release" \
    ../../../ch13-gallery-packaging.pro
make qmake_all
pushd gallery-core && make ; popd
pushd gallery-mobile && make ; popd
pushd gallery-mobile && make INSTALL_ROOT=$ANDROID_BUILD_PATH install ; popd

$QTDIR_ANDROID/bin/androiddeployqt --input ./gallery-mobile/android-libgallery-mobile.so-deployment-settings.json \
    --output $ANDROID_BUILD_PATH \
    --deployment bundled \
    --android-platform android-23 \
    --jdk $JAVA_HOME \
    --ant $ANT_ROOT/ant \
    --sign $KEYSTORE_PATH/android.keystore myandroidkey \
    --storepass 'masteringqt'
    
cp $ANDROID_BUILD_PATH/bin/QtApp-release-signed.apk ../apk/cute-gallery.apk
popd
