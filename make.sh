#!/bin/sh
export PATH="$PATH:/c/Qt/4.6.2/bin"
qmake -o w32_makefile_qvna       qvna.pro 
mingw32-make -f w32_makefile_qvna clean
mingw32-make -f w32_makefile_qvna release 
"c:\Program Files\Inno Setup 5\iscc" qvna.iss

