#!/bin/sh
COMPILER="i486-mingw32"
INCLUDE_DIR="/usr/${COMPILER}/include"
XERCESC_VER="3.1.1"
BUILD_THREADS="1"

#Compile Xerces-C using mingw32
if [ ! -f xercesc.alreadycompiled ]; then
  mkdir "xerces-c-${XERCESC_VER}/build"
  pushd "xerces-c-${XERCESC_VER}/build"
  ../configure --prefix=/ --host=${COMPILER}
  make -j${BUILD_THREADS} || (echo "Xerces-C ${XERCESC_VER} failed to compile"  && exit 1)
  make DESTDIR="$(pwd)/INSTALLROOT" install
  popd
  touch xercesc.alreadycompiled
fi

#Compile riivtodolph
${COMPILER}-g++ \
  -static \
  -DMINGW32 \
  -I${INCLUDE_DIR} \
  -Ixerces-c-${XERCESC_VER}/build/INSTALLROOT/include \
  -Lxerces-c-${XERCESC_VER}/build/INSTALLROOT/lib \
  -lxerces-c \
  -oriivtodolph.exe \
  riivtodolph.cpp
