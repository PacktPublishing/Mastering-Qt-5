@ECHO off

set DIST_DIR=dist\desktop-windows
set BUILD_DIR=build
set OUT_DIR=gallery

mkdir %DIST_DIR% && pushd %DIST_DIR%
mkdir %BUILD_DIR% %OUT_DIR%

pushd %BUILD_DIR%
%QTDIR%\bin\qmake.exe ^
	-spec win32-g++ ^
	"CONFIG += release" ^
	..\..\..\ch13-gallery-packaging.pro

%MINGWROOT%\bin\mingw32-make.exe qmake_all

pushd gallery-core
%MINGWROOT%\bin\mingw32-make.exe && popd

pushd gallery-desktop
%MINGWROOT%\bin\mingw32-make.exe && popd

popd
copy %BUILD_DIR%\gallery-core\release\gallery-core.dll %OUT_DIR%
copy %BUILD_DIR%\gallery-desktop\release\gallery-desktop.exe %OUT_DIR%
%QTDIR%\bin\windeployqt %OUT_DIR%\gallery-desktop.exe %OUT_DIR%\gallery-core.dll

popd
