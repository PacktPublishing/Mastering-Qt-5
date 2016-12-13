#!/bin/bash

DIST_DIR=dist/desktop-macosx
BUILD_DIR=build

mkdir -p $DIST_DIR && cd $DIST_DIR
mkdir -p $BUILD_DIR

pushd $BUILD_DIR
$QTDIR/bin/qmake \
	-spec macx-clang \
	"CONFIG += release x86_64" \
	../../../ch13-gallery-packaging.pro
make qmake_all
pushd gallery-core && make ; popd
pushd gallery-desktop && make ; popd

cp gallery-core/*.dylib \
    gallery-desktop/gallery-desktop.app/Contents/Frameworks/

install_name_tool -change \
	libgallery-core.1.dylib \
	@rpath/libgallery-core.1.dylib \
	gallery-desktop/gallery-desktop.app/Contents/MacOS/gallery-desktop
popd

$QTDIR/bin/macdeployqt \
    build/gallery-desktop/gallery-desktop.app \
    -dmg

mv build/gallery-desktop/gallery-desktop.dmg .
