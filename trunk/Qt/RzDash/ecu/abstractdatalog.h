#ifndef ABSTRACTDATALOG_H
#define ABSTRACTDATALOG_H

#include <QObject>
#include <QThread>
#include <QPointer>
#include <QBitArray>
#include <abstractserial.h>
#include <QtCore/QDebug>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>
#include <win32.h>

class AbstractDatalog : public QObject
{
    Q_OBJECT

public:
    ~AbstractDatalog();
    virtual void run();

    enum enumValues {RPM, TPS, IAT, ECT, O2, MAP, VSS, BATT, FUELC, FUELSC, INJ, DUTY, IGN, VTEC, MIL, IGNCUT, FUELCUL};
    enum enumSettings {PortName, PortSpeed, DatalogType, DatalogRefreshRate, InjectorSize, FuelConsumption, SpeedFormat, SpeedTrim};

public slots:
    virtual void setSettings(enumSettings settings, QString value);
    virtual float getValues(enumValues selection);
    virtual void resetSerial();

signals:
    void startRefreshTimer();
    void stopRefreshTimer();
    void startTimeoutTimer();
    void stopTimeoutTimer();

private:


private slots:

protected:
    QPointer<AbstractSerial> port;
    QMutex refreshMutex, busyMutex, lockerMutex;
    QByteArray m_Data;

    quint16 m_rpm, m_map, m_tps, m_vss, m_duty, m_ign, m_gear;
    float m_ect, m_iat, m_o2, m_batt, m_fuelc, m_fuelsc, m_inj;
    bool m_vtec, m_mil, m_igncut;

    QTimer m_refreshTimer, m_timeoutTimer;
    bool m_handShakeStatus, m_portOK, m_busy;

    QString m_portName, m_portSpeed, m_datalogType, m_datalogRefreshRate, m_injectorSize, m_fuelConsumption, m_speedFormat, m_speedTrim;

    virtual int map(int x, int in_min, int in_max, int out_min, int out_max);
    virtual float map(float x, float in_min, float in_max, float out_min, float out_max);
    virtual int constrain(int x, int out_min, int out_max);
    virtual float constrain(float x, float out_min, float out_max);

protected slots:
     virtual bool portSetup(QObject *parent);
     virtual void serialTimeout();
     virtual void readData();
     virtual char calcChecksum(QByteArray msg);
     virtual int littleEndianToWord(quint8 lsb, quint8 msb);


};

#endif // ABSTRACTDATALOG_H
