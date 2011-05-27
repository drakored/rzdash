/*
* This file is part of QSerialDevice, an open-source cross-platform library
* Copyright (C) 2009  Denis Shienkov
*
* This library is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Contact Denis Shienkov:
*          e-mail: <scapig2@yandex.ru>
*             ICQ: 321789831
*/

#ifndef SERIALNOTIFIER_P_H
#define SERIALNOTIFIER_P_H

#include "serialnotifier.h"

#if defined (Q_OS_WIN)
  #include <qt_windows.h>
  class QWinEventNotifier;
#else
  class QSocketNotifier;
  class LineNotifyThread;
#endif



class SerialNotifierPrivate
{
    Q_DECLARE_PUBLIC(SerialNotifier)
public:
    SerialNotifierPrivate();
    virtual ~SerialNotifierPrivate();

    void init(Serial::DESCRIPTOR descriptor, SerialNotifier::NotifyMode mode);

    SerialNotifier * q_ptr;

    SerialNotifier::NotifyMode mode;
    Serial::DESCRIPTOR descriptor;
    bool enabled;

    void setEnabled(bool enable);

private:
#if defined (Q_OS_WIN)
    QWinEventNotifier *notifier;
    ::DWORD eMask;
    ::OVERLAPPED o;
#else
    QSocketNotifier *readNotifier;
    QSocketNotifier *writeNotifier;
    QSocketNotifier *exceptNotifier;
    LineNotifyThread *notifyThread;
#endif
    void _q_updateNotifier();
    bool isValid() const;
};


#endif // SERIALNOTIFIER_P_H
