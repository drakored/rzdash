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

#include <QtCore/private/qwineventnotifier_p.h>

#include "serialnotifier.h"
#include "serialnotifier_p.h"

//#define SERIALNOTIFIER_WIN_DEBUG

#ifdef SERIALNOTIFIER_WIN_DEBUG
#include <QtCore/QDebug>
#endif


SerialNotifierPrivate::SerialNotifierPrivate()
        : enabled(false), notifier(0), eMask(0)
{
}

SerialNotifierPrivate::~SerialNotifierPrivate()
{
    this->setEnabled(false);

    if (this->o.hEvent) {
        if ( 0 == ::CloseHandle(this->o.hEvent) ) {
        }
        this->o.hEvent = 0;
    }
}

void SerialNotifierPrivate::init(Serial::DESCRIPTOR descriptor, SerialNotifier::NotifyMode mode)
{
    Q_Q(SerialNotifier);

    this->descriptor = descriptor;
    this->mode = mode;

    if ( INVALID_HANDLE_VALUE == this->descriptor )
        return;

    ::memset(&this->o, 0, sizeof(this->o));
    this->o.hEvent = ::CreateEvent(0, false, false, 0);

    if ( 0 == this->o.hEvent )
        return;

    this->notifier = new QWinEventNotifier(this->o.hEvent, q);
    QObject::connect(this->notifier, SIGNAL(activated(HANDLE)), q, SLOT(_q_updateNotifier()));

    if ( 0 == ::GetCommMask(this->descriptor, &this->eMask) )
        return;

    if (SerialNotifier::Nothing == this->mode) {
        this->eMask = 0;
    }
    else {
        (SerialNotifier::Read & this->mode) ?
                (this->eMask |= EV_RXCHAR) : (this->eMask &= ~EV_RXCHAR);
        (SerialNotifier::Write & this->mode) ?
                (this->eMask |= EV_TXEMPTY) : (this->eMask &= ~EV_TXEMPTY);
        (SerialNotifier::Exception & this->mode) ?
                (this->eMask |= EV_ERR) : (this->eMask &= ~EV_ERR);
        (SerialNotifier::Cts & this->mode) ?
                (this->eMask |= EV_CTS) : (this->eMask &= ~EV_CTS);
        (SerialNotifier::Dsr & this->mode) ?
                (this->eMask |= EV_DSR) : (this->eMask &= ~EV_DSR);
        (SerialNotifier::Ring & this->mode) ?
                (this->eMask |= EV_RING) : (this->eMask &= ~EV_RING);
    }
    ::SetCommMask(this->descriptor, this->eMask);
}

void SerialNotifierPrivate::setEnabled(bool enable)
{
    if (!this->isValid())
        return;

    if (enable) {
        this->eMask = 0;
        ::WaitCommEvent(this->descriptor, &this->eMask, &this->o);
    }

    this->notifier->setEnabled(enable);
    this->enabled = enable;
}

void SerialNotifierPrivate::_q_updateNotifier()
{
    Q_Q(SerialNotifier);

    if (!this->isValid())
        return;

    ::DWORD status = 0;
    //check read notify
    if ((SerialNotifier::Read & this->mode)
        && (EV_RXCHAR & this->eMask)) {

        ::COMSTAT cs = {0};
        if ( (0 != ::ClearCommError(this->descriptor, &status, &cs))
            && (!status)
            && (cs.cbInQue) ) {

            emit q->notifyRxReady();
        }
    }
    //check write notify
    if ((SerialNotifier::Write & this->mode)
        && (EV_TXEMPTY & this->eMask)) {

        emit q->notifyTxEmpty();
    }
    //check error notify
    if ((SerialNotifier::Exception & this->mode)
        && (EV_ERR & this->eMask)) {

        emit q->notifyException();
    }

    if (0 != ::GetCommModemStatus(this->descriptor, &status)) {
        //check cts notify
        if ((SerialNotifier::Cts & this->mode)
            && (EV_CTS & this->eMask)) {

            emit q->notifyCtsChanged(MS_CTS_ON & status);
        }
        //check dsr notify
        if ((SerialNotifier::Dsr & this->mode)
            && (EV_DSR & this->eMask)) {

            emit q->notifyCtsChanged(MS_DSR_ON & status);
        }
        //check ring notify
        if ((SerialNotifier::Ring & this->mode)
            && (EV_RING & this->eMask)) {

            emit q->notifyCtsChanged(MS_RING_ON & status);
        }
    }

    this->eMask = 0;
    this->setEnabled(this->enabled);
}

bool SerialNotifierPrivate::isValid() const
{
    return ( (INVALID_HANDLE_VALUE != this->descriptor)
             && (0 != this->o.hEvent)
             && (0 != this->notifier) );
}
