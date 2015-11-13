# Introduction #
This guide will explain how to build RzDash and Dmul on the linux platform using GCC.


# Prerequisites #

You need a few things:
  * QT 4.7.3 sources (here: http://get.qt.nokia.com/qt/source/qt-everywhere-opensource-src-4.7.3.zip)
  * gcc, g++
  * Statically Compiled Qt library
(Guide here: http://www.qtcentre.org/wiki/index.php?title=Building_static_Qt_on_Linux)
  * Qserialdevice (here: https://gitorious.org/qserialdevice/qserialdevice/trees/master)
  * Qwt 5.2.1 (here: http://sourceforge.net/projects/qwt/files/qwt/5.2.1/)

# Compiling #

Now that we have all prerequisites, we can compile RzDash.

Make sure the compiled libs (.a) are placed in the 'lib' folder of your Qt sources.

Using a terminal, cd the the RzDash folder.
Run Qmake, and start the build using make.

This should take a few seconds.

The binary will be in the release folder.