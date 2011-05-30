#include "abstractdatalog.h"

AbstractDatalog::AbstractDatalog(QObject *parent) :
        QObject(parent)
{
//qDebug() << "New Datalog Engine... ID:" << QString::number(this->thread()->currentThreadId() , 16).prepend("0x");
//qDebug() << "New Datalog Engine...";
}

AbstractDatalog::~AbstractDatalog()
{
    qDebug() << "Deleting Datalog Engine...";
    this->port->deleteLater();
    usleep(SLEEP);
    //delete port;
}

void AbstractDatalog::run()
{
    qDebug() << "AbstractDatalog::run";
    //QThread::moveToThread(this);
}

void AbstractDatalog::serialTimeout () {
    qDebug() << "Timeout";
    m_handShakeStatus = false;
    m_busy = false;
    //busyMutex.unlock();
}

void AbstractDatalog::readData () {

}

bool AbstractDatalog::portSetup (QObject *parent) {

    if (port.isNull())
        port = new AbstractSerial(parent);

    //qDebug() << port->thread()->currentThreadId();

    port->close();
    qDebug("Previous Port closed.");

    port->setDeviceName(m_portName);
    port->close();

    connect(port,SIGNAL(readyRead()),this,SLOT(readData()));

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

         qDebug() << "= Parameters =";
         qDebug() << "Device name            : " << port->deviceName();
         qDebug() << "Baud rate              : " << port->baudRate();
         qDebug() << "Data bits              : " << port->dataBits();
         qDebug() << "Parity                 : " << port->parity();
         qDebug() << "Stop bits              : " << port->stopBits();
         qDebug() << "Flow                   : " << port->flowControl();
         qDebug() << "Char timeout, msec     : " << port->charIntervalTimeout();
         port->flush();
         return true;
     }

         else {
             qDebug() << "Error opening serial device " << port->deviceName();
         }

    label:
        port->close();
        disconnect(port,SIGNAL(readyRead()),this,SLOT(readData()));
        //qDebug() << "Serial device " << port->deviceName() << " is closed";
        delete port;
        return false;
 }


float AbstractDatalog::getValues(enumValues selection) {

    if (m_portOK) {

            switch(selection)
              {
                  case RPM: return (float)m_rpm;
                          break;
                  case ECT: return m_ect;
                          break;
                  case IAT: return m_iat;
                          break;
                  case O2: return m_o2;
                          break;
                  case MAP: return (float)m_map;
                          break;
                  case TPS: return (float)m_tps;
                          break;
                  case VSS: return (float)m_vss;
                          break;
                  case BATT: return m_batt;
                          break;
                  case FUELC: return m_fuelc;
                          break;
                  case FUELSC: return m_fuelsc;
                          break;
                  case INJ: return m_inj;
                          break;
                  case DUTY: return m_duty;
                          break;
                  case IGN: return m_ign;
                          break;
                  case VTEC: return (float)m_ign;
                          break;
                  case MIL: return (float)m_ign;
                          break;
                  case IGNCUT: return (float)m_ign;
                          break;
                  case FUELCUL: return (float)m_ign;
                          break;

                  default: return 0.00;
                          break;
              }
    }

    else {
            return 0.00;
        }
}

void AbstractDatalog::setSettings(enumSettings setting, QString value) {

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
          case InjectorSize: m_injectorSize = value;
                  break;
          case FuelConsumption: m_fuelConsumption = value;
                  break;
          case SpeedFormat: m_speedFormat = value;
                  break;
          case SpeedTrim: m_speedTrim = value;
                  break;
          default: return;
                  break;
      }
}

int AbstractDatalog::map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float AbstractDatalog::map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int AbstractDatalog::constrain(int x, int out_min, int out_max)
{
    if (x <= out_max && x >= out_min)
        return x;

    else if (x > out_max)
        return out_max;

    else
        return out_min;
}

float AbstractDatalog::constrain(float x, float out_min, float out_max)
{
    if (x <= out_max && x >= out_min)
        return x;

    else if (x > out_max)
        return out_max;

    else
        return out_min;
}

void AbstractDatalog::resetSerial() {
    m_portOK = false;
}

char AbstractDatalog::calcChecksum(QByteArray msg)
{
  char checksum = 0;
  for (int i = 0; i < (msg.count() - 1); i++)
    checksum += msg[i];
  return checksum;
}

int AbstractDatalog::littleEndianToWord(quint8 lsb, quint8 msb)
{
    return (msb * 256) + lsb;
}
