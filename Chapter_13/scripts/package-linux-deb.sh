#!/bin/bash

DIST_DIR=dist/desktop-linux
BUILD_DIR=build
ROOT_DIR=root

BIN_DIR=$ROOT_DIR/usr/bin
LIB_DIR=$ROOT_DIR/usr/lib

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $BIN_DIR $LIB_DIR $BUILD_DIR

pushd $BUILD_DIR
$QTDIR/bin/qmake \
    -spec linux-g++ \
    "CONFIG += release" \
    ../../../ch13-gallery-packaging.pro

make qmake_all
pushd gallery-core && make && make install ; popd
pushd gallery-desktop && make && make install ; popd
popd

fpm --input-type dir \
    --output-type deb \
    --force \
    --name gallery-desktop \
    --version 1.0.0 \
    --vendor "Mastering Qt 5" \
    --description "A Qt gallery application to organize and manage your pictures in albums" \
    --depends qt5-default \
    --depends libsqlite3-dev \
    --chdir $ROOT_DIR \
    --package gallery-desktop_VERSION_ARCH.deb

