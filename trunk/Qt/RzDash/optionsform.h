#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H

#include <QWidget>
#include <QProcess>
#include <QPointer>
#include <QSettings>
#include <QDebug>

namespace Ui {
    class optionsForm;
}

class optionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit optionsForm(QWidget *parent = 0);
    ~optionsForm();
    enum enumSettings {PortName, PortSpeed, DatalogType, DatalogRefreshRate, InjectorSize, FuelConsumption, SpeedFormat, SpeedTrim};

public slots:
    QString getSettings(enumSettings setting);

signals:
    void settingsChanged();
    void portNameChanged(QString);

private:
    Ui::optionsForm *ui;
    QPointer<QProcess> myProcess;
    QPointer<QSettings> settings;

private slots:
    void reboot();
    void restartApp();
    void recalibrate();
    void setSettings();
    void saveSettings();
};

#endif // OPTIONSFORM_H
