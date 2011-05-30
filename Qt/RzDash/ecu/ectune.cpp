#include "ectune.h"

void eCtune::run() {

    qDebug("## eCtune dataloging engine started.\n");

    m_handShakeStatus = false;
    m_portOK = false;
    m_busy = false;

    m_refreshTimer.setInterval(10);
    m_refreshTimer.setSingleShot(true);
    connect(this,SIGNAL(startRefreshTimer()),&m_refreshTimer,SLOT(start()));
    connect(this,SIGNAL(stopRefreshTimer()),&m_refreshTimer,SLOT(stop()));
    connect(&m_refreshTimer,SIGNAL(timeout()),this,SLOT(refresh()));

    m_timeoutTimer.setInterval(200);
    m_timeoutTimer.setSingleShot(true);
    connect(this,SIGNAL(startTimeoutTimer()),&m_timeoutTimer,SLOT(start()));
    connect(this,SIGNAL(stopTimeoutTimer()),&m_timeoutTimer,SLOT(stop()));
    connect(&m_timeoutTimer,SIGNAL(timeout()),this,SLOT(serialTimeout()));

    m_portOK = this->portSetup(this);

    this->m_refreshTimer.start();

}

void eCtune::refresh() {

    refreshMutex.lock();

    //qDebug("refresh");

    if (!m_portOK) {
        m_portOK = this->portSetup(this);
        usleep(SLEEP);
    }

    else if (!m_handShakeStatus && m_portOK)
        this->sendHandShake();

    else if (m_handShakeStatus && m_portOK)
        this->getRawValues();

    refreshMutex.unlock();

    emit startRefreshTimer();
}

void eCtune::readData() {

    //qDebug("readData");

    if (!m_handShakeStatus && m_portOK)
        this->checkHandShake();

    else if (m_handShakeStatus && m_portOK)
        this->waitValues();
}

bool eCtune::sendHandShake() {

    /*
    if (!m_busy) busyMutex.unlock();
    if (!busyMutex.tryLock())
        return false;
    */
    if (m_busy) return false;
    m_busy = true;
    QByteArray sbuffer; //data to send
    sbuffer[0] = 0x10;
    port->flush();
    port->write(sbuffer);
    emit startTimeoutTimer();

    qDebug() << "Sent HandShake, Waiting for Response";

    //busyMutex.unlock();
    return true;
}

bool eCtune::checkHandShake() {

    m_busy = false;
    //busyMutex.unlock();
    emit stopTimeoutTimer();
    QByteArray rbuffer; //data received
    //rbuffer = port->read(1);
    rbuffer = port->readAll();

    if (rbuffer[0] == (char)0xCD) {
        qDebug() << "HandShake Success!";
        qDebug() << "Received Handshake:" << QString::number(rbuffer[0] , 16).right(2).prepend("0x");
        m_handShakeStatus = true;
        return true;
    }

    else {
        qDebug() << "HandShake Failed!";
        qDebug() << "Received Handshake:" << QString::number(rbuffer[0] , 16).right(2).prepend("0x");
        m_handShakeStatus = false;
        return false;
    }

}

bool eCtune::getRawValues() {
/*
    if (!busyMutex.tryLock())
        return false;
*/
    if (m_busy) return false;
    m_busy = true;
    QByteArray sbuffer; //data to send
    sbuffer[0] = 0x20;

    port->flush();

    //qDebug() << "Data Request" << QString::number(sbuffer[0], 16).prepend("0x");

    port->write(sbuffer);
    emit startTimeoutTimer();

    //busyMutex.unlock();

    return true;
}

bool eCtune::waitValues() {

    m_busy = false;
    //busyMutex.unlock();

    do {
       //qDebug() << "Bytes available: " << QString::number(port->bytesAvailable(), 16).prepend("0x");
       usleep(SLEEP/100);
    } while (port->bytesAvailable() < 0x34 && m_timeoutTimer.isActive());

    //qDebug() << "Bytes received:" << QString::number(port->bytesAvailable(), 16).prepend("0x");

    if (!m_timeoutTimer.isActive()) {
        qDebug() << "Data Request Timed out";
        //this->serialTimeout();
        return false;
    }

    //m_Data = port->read(0x34);
    m_Data = port->readAll();
    qDebug() << "Bytes read:" << QString::number(m_Data.size(), 16).prepend("0x");

/*
    int num, pos;
    pos = 0;
    foreach (num, m_ectuneData) {
        qDebug() << "buffer pos:" << pos << "Data:" << num;
        pos++;
    }
*/
    //port->flush();
    this->processValues();
    emit stopTimeoutTimer();
    return false;
}

void eCtune::processValues() {

    char checksumIn = this->calcChecksum(m_Data);
    char checksumByte = (char)m_Data[0x33];

    if (checksumIn != checksumByte) {
        qDebug() << "Checksum failed, calculated" << QString::number(checksumIn, 16).prepend("0x").right(2)
                << "expected" << QString::number(checksumByte, 16).prepend("0x").right(2);
        return;
    }

    //else
    //    qDebug() << "Checksum OK, Value:" << QString::number(checksumIn, 16).prepend("0x").right(2);

    QDataStream stream(m_Data);
    QBitArray bits_stream(36*8, false);
    stream >> bits_stream;
    //qDebug("Process...");

    //b stands for "byte"
    quint8 b_rpmlsb = m_Data[6];
    quint8 b_rpmmsb = m_Data[7];
    quint8 b_ect = m_Data[0];
    quint8 b_iat = m_Data[1];
    quint8 b_o2 = m_Data[2];
    quint8 b_map = m_Data[4];
    quint8 b_tps = m_Data[5];
    quint8 b_vss = m_Data[16];
    quint8 b_injlsb = m_Data[17];
    quint8 b_injmsb = m_Data[18];
    quint8 b_ign = m_Data[19];
    quint8 b_batt = m_Data[25];

    // lsb/msb = least/most significant byte (little endian)
    int rpm = 1875000.0 / (float)littleEndianToWord(b_rpmlsb, b_rpmmsb);

    // Injection time in ms
    float inj = (((float)littleEndianToWord(b_injlsb, b_injmsb)/* / 4.0*/) * 3.2) / 1000;

    // Injectors duty cycle
    float duty = ((float)rpm * inj) / 1200;

    // Minutes needed to travel 100km
    float hundredkm = ((60.0 / ((float)b_vss / 60.0)) * 100.0) / 60.0;

    // Fuel consumption in Liters per 100km
    float fuelc = (hundredkm * (((float)m_injectorSize.toInt() / 100.0) * duty)) / 1000.0;

    // Fuel consumption in Liters per hour
    float fuelsc = (60.0 * (((float)m_injectorSize.toInt() / 100.0) * duty)) / 1000.0;

    // Ignition advance
    int ign = ((float)b_ign * 0.25) - 6.0;

    float X;
    float TempF;

    X = b_ect * ( 5.00 / 256.00 );
    TempF = ( (0.1423 * X * X * X * X * X * X ) - (2.4938 * X * X * X * X * X) +
              (17.837 * X * X * X * X) - (68.698 * X * X * X) +
              (154.69 * X * X) - (232.75 * X) + 291.24);
    m_ect = (TempF - 32.0) * (5.0 / 9.0);

    X = b_iat * ( 5.00 / 256.00 );
    TempF = ( (0.1423 * X * X * X * X * X * X ) - (2.4938 * X * X * X * X * X) +
              (17.837 * X * X * X * X) - (68.698 * X * X * X) +
              (154.69 * X * X) - (232.75 * X) + 291.24);
    m_iat = (TempF - 32.0) * (5.0 / 9.0);

    m_map = ((1764.0 / 256.0) * b_map);

/*
    bool postfuel = bits_stream[9*8];
    bool scc = bits_stream[(9*8)+1];
*/
    //m_igncut = bits_stream[(9*8)+2];
/*
    bool vtsmap = bits_stream[(9*8)+3];
    bool fuelcut1 = bits_stream[(9*8)+4];
    bool fuelcut2 = bits_stream[(9*8)+5];
    bool at2 = bits_stream[(9*8)+6];
    bool at1 = bits_stream[(9*8)+7];
*/
    //m_vtec = bits_stream[(23*8)+7];
   // m_mil = bits_stream[(23*8)+5];

    m_rpm = rpm;
    m_o2 = b_o2 * ( 5.00 / 256.00 );
    m_tps = ((float)b_tps - 25.00) / 2.04;
    m_vss = ((float)b_vss + ((this->m_speedTrim.toFloat() * (float)b_vss) / 100.0));
    m_batt = (26.0 * b_batt) / 270.0;
    m_fuelc = fuelc;
    m_fuelsc = fuelsc;
    m_inj = inj;
    m_duty = duty;
    m_ign = ign;
}
