#!/usr/bin/env bash

set -e

TARGET=$1
[ -z $1 ] && TARGET=$(pwd)
echo $TARGET

if [ ! -d $TARGET ]; then
  echo $TARGET is not a directory. please put project root of nntrainer
  exit 1
fi

pushd $TARGET

if [ ! -d builddir ]; then
  #defualt value of openblas num threads is 1 for android
  meson builddir -Dplatform=android -Dopenblas-num-threads=1
else
  echo "warning: $TARGET/builddir has already been taken, this script tries to reconfigure and try building"
  pushd builddir
    #defualt value of openblas num threads is 1 for android
    meson configure -Dplatform=android -Dopenblas-num-threads=1
    meson --wipe
  popd
fi

pushd builddir
ninja install

tar -czvf $TARGET/nntrainer_for_android.tar.gz --directory=android_build_result .

popd
popd

