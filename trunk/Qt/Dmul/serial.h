#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <qpointer.h>
#include <abstractserial.h>
#include <qdebug.h>
#include <qtimer.h>
#include <win32.h>

class Serial : public QObject
{
    Q_OBJECT
public:
    explicit Serial(QObject *parent = 0);
    enum enumValues {RPM, TPS, IAT, ECT, O2, MAP, VSS, BATT, FUELC, FUELSC, INJ, DUTY, IGN, VTEC, MIL, IGNCUT, FUELCUL};
    enum enumSettings {PortName, PortSpeed, DatalogType, DatalogRefreshRate};

signals:
    void startTimer();

public slots:
    void resetSerial();
    void setSettings(enumSettings settings, QString value);
    void setValues(enumValues valueName, float value);

private:
    QPointer<QTimer> timer;
    QPointer<AbstractSerial> port;
    QString m_portName, m_portSpeed, m_datalogType, m_datalogRefreshRate, m_injectorSize, m_fuelConsumption, m_speedFormat, m_speedTrim;
    bool m_portOK, m_busy;

    quint16 m_rpm, m_map, m_tps, m_vss, m_duty, m_ign, m_gear;
    float m_ect, m_iat, m_o2, m_batt, m_fuelc, m_fuelsc, m_inj;
    bool m_vtec, m_mil, m_igncut;

    int map(int x, int in_min, int in_max, int out_min, int out_max);
    float map(float x, float in_min, float in_max, float out_min, float out_max);
    int constrain(int x, int out_min, int out_max);
    float constrain(float x, float out_min, float out_max);

private slots:
    void refresh();
    bool portSetup();
    void readCommand();
    void sendData();
    char calcChecksum(QByteArray msg);

};

#endif // SERIAL_H
