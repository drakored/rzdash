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

#include <QtCore/QSocketNotifier>
#include <sys/ioctl.h>

#include "serialnotifier.h"
#include "serialnotifier_p.h"
#include "linenotifythread.h"

//#define SERIALNOTIFIER_UNIX_DEBUG

#ifdef SERIALNOTIFIER_UNIX_DEBUG
#include <QtCore/QDebug>
#endif

SerialNotifierPrivate::SerialNotifierPrivate()
        : enabled(false),
        readNotifier(0), writeNotifier(0), exceptNotifier(0),
        notifyThread(0)
{
}

SerialNotifierPrivate::~SerialNotifierPrivate()
{
    this->setEnabled(false);
    if (this->notifyThread) {
        this->notifyThread->stop();
        this->notifyThread->wait(1000);
    }
}

void SerialNotifierPrivate::init(Serial::DESCRIPTOR descriptor, SerialNotifier::NotifyMode mode)
{
    Q_Q(SerialNotifier);

    this->descriptor = descriptor;
    this->mode = mode;

    if (!this->isValid())
        return;

    if (SerialNotifier::Read & this->mode) {
        this->readNotifier = new QSocketNotifier(this->descriptor, QSocketNotifier::Read, q);
        QObject::connect(this->readNotifier, SIGNAL(activated(int)), q, SIGNAL(notifyRxReady()));
    }
    if (SerialNotifier::Write & this->mode) {
        this->writeNotifier = new QSocketNotifier(this->descriptor, QSocketNotifier::Write, q);
        QObject::connect(this->writeNotifier, SIGNAL(activated(int)), q, SIGNAL(notifyTxEmpty()));
    }
    if (SerialNotifier::Exception & this->mode) {
        this->exceptNotifier = new QSocketNotifier(this->descriptor, QSocketNotifier::Exception, q);
        QObject::connect(this->exceptNotifier, SIGNAL(activated(int)), q, SIGNAL(notifyException()));
    }

    if (SerialNotifier::Cts & this->mode) {
        if (!this->notifyThread)
            this->notifyThread = new LineNotifyThread(this->descriptor, this->mode, q);
        QObject::connect(this->notifyThread, SIGNAL(cts(bool)), q, SIGNAL(notifyCtsChanged(bool)));
    }
    if (SerialNotifier::Dsr & this->mode) {
        if (!this->notifyThread)
            this->notifyThread = new LineNotifyThread(this->descriptor, this->mode, q);
        QObject::connect(this->notifyThread, SIGNAL(dsr(bool)), q, SIGNAL(notifyDsrChanged(bool)));
    }
    if (SerialNotifier::Ring & this->mode) {
        if (!this->notifyThread)
            this->notifyThread = new LineNotifyThread(this->descriptor, this->mode, q);
        QObject::connect(this->notifyThread, SIGNAL(ring(bool)), q, SIGNAL(notifyRingChanged(bool)));
    }
    if (this->notifyThread)
        this->notifyThread->start();
}

void SerialNotifierPrivate::setEnabled(bool enable)
{
    if (this->readNotifier)
        this->readNotifier->setEnabled(enable);
    if (this->writeNotifier)
        this->writeNotifier->setEnabled(enable);
    if (this->exceptNotifier)
        this->exceptNotifier->setEnabled(enable);
    if (this->notifyThread)
        this->notifyThread->setEnabled(enable);

    this->enabled = enable;
}

void SerialNotifierPrivate::_q_updateNotifier()
{
    //Not use
}

bool SerialNotifierPrivate::isValid() const
{
    return (-1 != this->descriptor);
}
