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

#ifndef SERIALNOTIFIER_H
#define SERIALNOTIFIER_H

#include <QtCore/QObject>

/* Serial::DESCRIPTOR - Serial Device descriptor namespace. */
namespace Serial {
#if defined (Q_OS_UNIX)
    typedef int DESCRIPTOR;
#elif defined(Q_OS_WIN32)
    typedef void *DESCRIPTOR;
#endif
}

class SerialNotifierPrivate;
class SerialNotifier : public QObject
{
    Q_OBJECT

Q_SIGNALS:
    void notifyRxReady();
    void notifyTxEmpty();
    void notifyException();
    void notifyCtsChanged(bool value);
    void notifyDsrChanged(bool value);
    void notifyRingChanged(bool value);

public:
    /*! \~english
        \enum NotifyModeFlag
        Modes of issuing notification.
        Enable/disable the appropriate mode is done by bitwise OR/AND-NOT.
    */
    enum NotifyModeFlag {
        Nothing     = 0x0000, /*!< \~english Disable all notifications. */
        Read        = 0x0001, /*!< \~english Notification that you can received the data,
                                             ie input buffer contains at least 1 character. */
        Write       = 0x0002, /*!< \~english Notification that you can transfer data,
                                             ie output buffer is empty. */
        Exception   = 0x0004, /*!< \~english Notification that there was some error or exception I/O. */
        Cts         = 0x0008, /*!< \~english Notification of changes in the state line CTS. */
        Dsr         = 0x0010, /*!< \~english Notification of changes in the state line DSR. */
        Ring        = 0x0020  /*!< \~english Notification of changes in the state line Ring. */
    };
    Q_DECLARE_FLAGS(NotifyMode, NotifyModeFlag)

    explicit SerialNotifier(Serial::DESCRIPTOR descriptor,
                            NotifyMode mode = SerialNotifier::Nothing,
                            QObject *parent = 0);
    virtual ~SerialNotifier();

    Serial::DESCRIPTOR descriptor() const;
    NotifyMode mode() const;
    bool isEnabled() const;

public Q_SLOTS:
    void setEnabled(bool enable);

protected:
    SerialNotifierPrivate * const d_ptr;

private:
    Q_DECLARE_PRIVATE(SerialNotifier)
    Q_DISABLE_COPY(SerialNotifier)
    Q_PRIVATE_SLOT(d_func(), void _q_updateNotifier())
};

Q_DECLARE_OPERATORS_FOR_FLAGS(SerialNotifier::NotifyMode)

#endif // SERIALNOTIFIER_H
