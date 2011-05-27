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


/*! \~english
    \class SerialNotifier

    The class is designed to track the status of the serial device and issuing the notification when it changes.\n
    This class is similar to the class QSocketNotifier, but extended and adapted for the serial device.
    This is an internal class that (in plans) must distinguish between the following events:
    - When the arrival at least one character in the receive buffer;
    - When withdrawing from the buffer the last character;
    - When an error occurs I/O, etc;
    - When change the line CTS;
    - When change the line DSR;
    - When change the line RING;
    .
*/

#include <QtCore/QStringList>

#include "serialnotifier.h"
#include "serialnotifier_p.h"

//#define SERIALNOTIFIER_DEBUG

#ifdef SERIALNOTIFIER_DEBUG
#include <QtCore/QDebug>
#endif


//

/*! \~english
    \fn SerialNotifier::SerialNotifier(Serial::DESCRIPTOR descriptor, NotifyMode mode, QObject *parent)
    Default constructor.
*/
SerialNotifier::SerialNotifier(Serial::DESCRIPTOR descriptor, NotifyMode mode, QObject *parent)
    : QObject(parent), d_ptr(new SerialNotifierPrivate())
{
    d_func()->q_ptr = this;
    d_func()->init(descriptor, mode);
}

/*! \~english
    \fn SerialNotifier::~SerialNotifier()
    Default destructor.
*/
SerialNotifier::~SerialNotifier()
{
    d_func()->setEnabled(false);
    delete d_ptr;
}

/*! \~english
    \fn Serial::DESCRIPTOR SerialNotifier::descriptor() const
    Get current device descriptor.
    \return Descriptor as SD::DESCRIPTOR.
*/
Serial::DESCRIPTOR SerialNotifier::descriptor() const
{
    return d_func()->descriptor;
}

/*! \~english
    \fn SerialNotifier::NotifyMode SerialNotifier::mode() const
    Get current type of class monitoring.
    \return Mode as SerialNotifier::NotifyMode.
*/
SerialNotifier::NotifyMode SerialNotifier::mode() const
{
    return d_func()->mode;
}

/*! \~english
    \fn bool SerialNotifier::isEnabled() const
    Get current work state.
    \return True if monitoring enabled.
*/
bool SerialNotifier::isEnabled() const
{
    return d_func()->enabled;
}

/*! \~english
    \fn void SerialNotifier::setEnabled(bool enable)
    Enabling or disabling monitoring depending on the parameter \a enable.
*/
void SerialNotifier::setEnabled(bool enable)
{
    d_func()->setEnabled(enable);
}

/*! \~english
    \fn void notifyRxReady()
    This signal is emitted when the in receiving buffer is available at least one symbol.
*/

/*! \~english
    \fn void notifyTxEmpty()
    This signal is emitted when the transmitting buffer is empty and can transmit data.
*/

/*! \~english
    \fn void notifyException()
    This signal is emitted when the error occurred or exception I/O.
*/

/*! \~english
    \fn void notifyCtsChanged(bool value)
    This signal is emitted when changing the status line CTS.
    \param value Current line state.
*/

/*! \~english
    \fn void notifyDsrChanged(bool value)
    This signal is emitted when changing the status line DSR.
    \param value Current line state.
*/

/*! \~english
    \fn void notifyRingChanged(bool value)
    This signal is emitted when changing the status line RING.
    \param value Current line state.
*/


#include "moc_serialnotifier.cpp"
