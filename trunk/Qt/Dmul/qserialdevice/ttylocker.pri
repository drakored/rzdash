#

HEADERS         += $$PWD/ttylocker.h

SOURCES         += $$PWD/ttylocker.cpp

INCLUDEPATH += $$PWD

#для HAVE_BAUDBOY_H ищем baudboy.h  и делаем defines
#для HAVE_LOCKDEV_H ищем lockdev.h и подключаем -llockdev и делаем defines


