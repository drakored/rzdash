#include "serial.h"

Serial::Serial(QObject *parent) :
    QObject(parent)
{
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->setSingleShot(true);

    connect(timer,SIGNAL(timeout()),this,SLOT(refresh()));
    connect(this,SIGNAL(startTimer()),timer,SLOT(start()));

    timer->start();

    m_portOK = false;

    m_busy = false;
}

void Serial::refresh() {

    //qDebug("Refresh");

    if (!m_portOK) m_portOK = this->portSetup();

    emit startTimer();
}

bool Serial::portSetup () {

    if (port.isNull()) {
        port = new AbstractSerial(this);
    }

    port->close();
    qDebug("Port closed.");

    port->setDeviceName(m_portName);
    port->close();

    /* 3. Third - open the device.
     */
     if (port->open(AbstractSerial::ReadWrite)) {

         qDebug() << "Serial device " << port->deviceName() << " open in " << port->openMode();

         if (!port->setBaudRate(m_portSpeed)) {
             qDebug() << "Set baud rate " <<  m_portSpeed << " error.";
             goto label;
         };

         if (!port->setDataBits(AbstractSerial::DataBits8)) {
             qDebug() << "Set data bits " <<  AbstractSerial::DataBits8 << " error.";
             goto label;
         }

         if (!port->setParity(AbstractSerial::ParityNone)) {
             qDebug() << "Set parity " <<  AbstractSerial::ParityNone << " error.";
             goto label;
         }

         if (!port->setStopBits(AbstractSerial::StopBits1)) {
             qDebug() << "Set stop bits " <<  AbstractSerial::StopBits1 << " error.";
             goto label;
         }

         if (!port->setFlowControl(AbstractSerial::FlowControlOff)) {
             qDebug() << "Set flow " <<  AbstractSerial::FlowControlOff << " error.";
             goto label;
         }

//         if (!port->setCharIntervalTimeout(1))
//         {
//             qDebug() << "Set char timeout error";
//             goto label;
//         }
         qDebug() << "= Parameters =";
         qDebug() << "Device name            : " << port->deviceName();
         qDebug() << "Baud rate              : " << port->baudRate();
         qDebug() << "Data bits              : " << port->dataBits();
         qDebug() << "Parity                 : " << port->parity();
         qDebug() << "Stop bits              : " << port->stopBits();
         qDebug() << "Flow                   : " << port->flowControl();
         qDebug() << "Char timeout, msec     : " << port->charIntervalTimeout();
         timer->start();
         qDebug() << "Port Setup done!";
         port->readAll();
         port->flush();
         connect(port,SIGNAL(readyRead()),this,SLOT(readCommand()));
         timer->stop();
         return true;
     }

         else {
             qDebug() << "Error opening serial device " << port->deviceName();
         }

    label:
     port->close();
     qDebug() << "Serial device " << port->deviceName() << " is closed";
     disconnect(port,SIGNAL(readyRead()),this,SLOT(readCommand()));
     delete port;
     return false;
 }

void Serial::setSettings(enumSettings setting, QString value) {

    switch(setting)
      {
          case PortName: m_portName = value;
                  break;
          case PortSpeed: m_portSpeed = value;
                  break;
          case DatalogType: m_datalogType = value;
                  break;
          case DatalogRefreshRate: m_datalogRefreshRate = value;
                  break;
          default: return;
                  break;
      }
}

void Serial::setValues(enumValues valueName, float value) {

    switch(valueName)
      {
          case RPM: m_rpm = (int)value;
                  break;
          case TPS: m_tps = (int)value;
                  break;
          case IAT: m_iat = value;
                  break;
          case ECT: m_ect = value;
                  break;
          case VSS: m_vss = (int)value;
                  break;
          default: return;
                  break;
      }
}

void Serial::readCommand() {

    static long hscount = 0;
    static long datacount = 0;

    m_busy = true;
    QByteArray rbuffer;
    QByteArray sbuffer;
    rbuffer = port->read(1);

    if (rbuffer[0] == (char)0x10) {

        sbuffer[0] = 0xCD;
        port->write(sbuffer);
        qDebug() << "Handshake response sent" << hscount++;
    }

    else if (rbuffer[0] == (char)0x20) {

        unsigned int rpm = (int)(1875600.0 / (float)m_rpm);
        unsigned char rpm_lsb, rpm_msb;

        rpm_lsb = (rpm & 0x00FF);
        rpm_msb = ((rpm >> 8) & 0x00FF);

        sbuffer.resize(0x34);
        sbuffer.fill(0);
        //sbuffer[0] = map((float)m_ect, 0.0, 500.0, 0.0, 255.0);
        //sbuffer[1] = map((float)m_iat, 0.0, 500.0, 0.0, 255.0);
        sbuffer[0] = m_ect;
        sbuffer[1] = m_iat;
        sbuffer[4] = m_map;
        sbuffer[5] = (m_tps * 2.04) + 25;
        sbuffer[6] = rpm_lsb;
        sbuffer[7] = rpm_msb;
        sbuffer[16] = m_vss;
        sbuffer[25] = m_batt;
        sbuffer[0x33] = this->calcChecksum(sbuffer);

        port->write(sbuffer);
        qDebug() << "Data sent 0x20" << datacount++;
        //qDebug() << QString::number(rpm) << QString::number(sbuffer[6]) << "+" << QString::number(sbuffer[7]);
    }

    else if (rbuffer[0] == (char)0x30) {

        sbuffer.resize(0x34);
        sbuffer.fill(0);
        port->write(sbuffer);
        qDebug() << "Data sent 0x30" << datacount++;
    }

    else if (rbuffer[0] == (char)0x40) {

        sbuffer.resize(0x34);
        sbuffer.fill(0);
        port->write(sbuffer);
        qDebug() << "Data sent 0x40" << datacount++;
    }

    else if (rbuffer[0] == (char)0x50) {

        sbuffer.resize(0x34);
        sbuffer.fill(0);
        port->write(sbuffer);
        qDebug() << "Data sent 0x50" << datacount++;
    }
    m_busy = false;
}

void Serial::sendData() {

    QByteArray sbuffer;
    sbuffer.resize(0x34);
    sbuffer.fill(m_tps);
    port->write(sbuffer);
}

void Serial::resetSerial() {
    m_portOK = false;
}

int Serial::map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float Serial::map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Serial::constrain(int x, int out_min, int out_max)
{
    if (x <= out_max && x >= out_min)
        return x;

    else if (x > out_max)
        return out_max;

    else
        return out_min;
}

float Serial::constrain(float x, float out_min, float out_max)
{
    if (x <= out_max && x >= out_min)
        return x;

    else if (x > out_max)
        return out_max;

    else
        return out_min;
}

char Serial::calcChecksum(QByteArray msg)
{
  char checksum = 0;
  for (int i = 0; i < (msg.count() - 1); i++)
    checksum += msg[i];
  return checksum;
}
