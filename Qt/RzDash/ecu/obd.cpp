#include "obd.h"

void Obd::run() {

    qDebug("## OBD II dataloging engine started.\n");

    m_handShakeStatus = false;
    m_portOK = false;

    m_refreshTimer.setInterval(1);
    m_refreshTimer.setSingleShot(true);
    connect(this,SIGNAL(startRefreshTimer()),&m_refreshTimer,SLOT(start()));
    connect(this,SIGNAL(stopRefreshTimer()),&m_refreshTimer,SLOT(stop()));
    connect(&m_refreshTimer,SIGNAL(timeout()),this,SLOT(refresh()));

    m_timeoutTimer.setInterval(120);
    m_timeoutTimer.setSingleShot(true);
    connect(this,SIGNAL(startTimeoutTimer()),&m_timeoutTimer,SLOT(start()));
    connect(this,SIGNAL(stopTimeoutTimer()),&m_timeoutTimer,SLOT(stop()));
    connect(&m_timeoutTimer,SIGNAL(timeout()),this,SLOT(serialTimeout()));

    m_portOK = this->portSetup(this);

    this->m_refreshTimer.start();
}


void Obd::refresh() {

    refreshMutex.lock();

    if (!m_portOK) {
        m_portOK = this->portSetup(this);
        usleep(SLEEP);
    }

    refreshMutex.unlock();

    emit startRefreshTimer();
}

void Obd::readData() {


}



void Obd::processValues() {


}
