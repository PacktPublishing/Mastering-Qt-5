#!/bin/bash

DIST_DIR=dist/mobile-ios
BUILD_DIR=build

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $BIN_DIR $LIB_DIR $BUILD_DIR

pushd $BUILD_DIR
$QTDIR_IOS/bin/qmake \
	-spec macx-ios-clang \
	"CONFIG += release iphoneos device" \
	../../../ch13-gallery-packaging.pro
make qmake_all
pushd gallery-core && make ; popd
pushd gallery-mobile && make ; popd

popd