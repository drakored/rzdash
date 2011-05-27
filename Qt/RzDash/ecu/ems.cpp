#include "ems.h"

void Ems::run()
{
    qDebug("## AEM EMS dataloging engine started.\n");

    m_handShakeStatus = false;
    m_portOK = false;

    m_refreshTimer.setInterval(100);
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


void Ems::refresh() {

    refreshMutex.lock();

    if (!m_portOK)
        m_portOK = this->portSetup(this);

    refreshMutex.unlock();

    emit startRefreshTimer();
}

void Ems::readData() {

    if (!busyMutex.tryLock())
        return;

    QByteArray rbuffer; //data received
    emit startTimeoutTimer();

    do {
       qDebug() << "Bytes available: " << QString::number(port->bytesAvailable(), 16).prepend("0x");
       usleep(SLEEP/10);
    } while(port->bytesAvailable() < 21 && m_timeoutTimer.isActive());

    if (!m_timeoutTimer.isActive())
        return;

    qDebug() << "Bytes available:" << QString::number(port->bytesAvailable(), 16).prepend("0x");
    rbuffer.clear();
    rbuffer = port->read(21);
    qDebug() << "Bytes read:" << QString::number(rbuffer.count(), 16).prepend("0x");
    emit stopTimeoutTimer();

    int pos = 0;
    foreach (char i, rbuffer) {
        if (i == (char)0x55)
            break;
        pos++;
    }

    emit startTimeoutTimer();

    rbuffer = rbuffer.right(pos);

    do {
       usleep(SLEEP/10);
    } while(port->bytesAvailable() < pos && m_timeoutTimer.isActive());

    rbuffer.append(port->read(pos));
    m_Data = rbuffer;

    emit stopTimeoutTimer();

    int num;
    pos = 0;
    foreach (num, m_Data) {
        qDebug() << "buffer pos:" << pos << "Data:" << num;
        pos++;
    }


    this->processValues();
    busyMutex.unlock();
    return;
}


void Ems::processValues() {

    m_rpm = map(m_Data[0], 0, 254, 0, 12800);
    m_map = map(m_Data[1], 0, 254, 50, 1770);
    m_tps = map(m_Data[2], 0, 254, 0, 100);
    m_iat = map((float)m_Data[3], 0.0, 254.0, -198.0, 260.0);
    m_ect = map((float)m_Data[4], 0.0, 254.0, -198.0, 260.0);
    m_batt = map((float)m_Data[5], 0.0, 254.0, 0.0, 15.93);
    m_duty = map(m_Data[6], 0, 254, 0, 250);
    m_inj = map((float)m_Data[7], 0.0, 254.0, 0.0, 328675.0/1000);
    m_ign = map((float)m_Data[8], 0.0, 254.0, -17.0, 72.64);
    m_o2 = map((float)m_Data[12], 0.0, 254.0, 3.235, 9.6797);
    m_vss = map(m_Data[16], 0, 254, 0, 412);
    m_gear = m_Data[16];

    // Minutes needed to travel 100km
    float hundredkm = ((60.0 / ((float)m_vss / 60.0)) * 100.0) / 60.0;

    // Fuel consumption in Liters per 100km
    m_fuelc = (hundredkm * (((float)m_injectorSize.toInt() / 100.0) * m_duty)) / 1000.0;

    // Fuel consumption in Liters per hour
    m_fuelsc = (60.0 * (((float)m_injectorSize.toInt() / 100.0) * m_duty)) / 1000.0;
}

