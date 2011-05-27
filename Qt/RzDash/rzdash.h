#ifndef RZDASH_H
#define RZDASH_H

#include <QWidget>
#include <QThread>
#include <QSplashScreen>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <ecu/ectune.h>
#include <ecu/ems.h>
#include <ecu/crome.h>
#include <ecu/kpro.h>
#include <ecu/obd.h>
#include <ecu/s300.h>
#include <optionsform.h>

namespace Ui {
    class cluster;
}

class rzdash : public QWidget
{
    Q_OBJECT

public:
    explicit rzdash(QWidget *parent = 0);
    ~rzdash();

private:
    Ui::cluster *ui;
    QPointer<AbstractDatalog> engine;
    QPointer<optionsForm> optionsform;
    QPointer<QTimer> m_refreshTimer;
    QwtPlotCurve *fuelcurve;
    QVector<double> x;
    QVector<double> y;
    QString datalogType;
    QThread engineThread;


private slots:
    void showOptions();
    void refresh();
    void updateDatalogSettings();
    void setup();
    void splash();
    void selectEngine();
};

#endif // RZDASH_H
