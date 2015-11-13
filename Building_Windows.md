# Introduction #
This guide will explain how to build RzDash and Dmul on the windows platform using the VC compiler.


# Prerequisites #

You need a few things:
  * QT 4.7.3 sources (here: http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.3.zip)
  * Visual Studio C++ 2010 (express edition works fine)
  * Statically Compiled Qt library
(Guide here: http://www.formortals.com/build-qt-static-small-microsoft-intel-gcc-compiler )
  * Qserialdevice (here: https://gitorious.org/qserialdevice/qserialdevice/trees/master)
  * Qwt 5.2.1 (here: http://sourceforge.net/projects/qwt/files/qwt/5.2.1/)

# Compiling #

Now that we have all prerequisites, we can compile RzDash.

Make sure the compiled libs are placed in the 'lib' folder of your Qt sources.

Using the VC command line (accessible from the start menu), go the the RzDash folder.
Run Qmake, and start the build using nmake.

This should take a few minutes.

The binary will be in the release folder.