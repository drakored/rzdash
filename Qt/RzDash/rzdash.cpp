#include "rzdash.h"
#include "ui_cluster.h"

rzdash::rzdash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cluster)
{
    qDebug("Initialiazing...\n");

    ui->setupUi(this);
    m_refreshTimer = new QTimer();
    m_refreshTimer->setInterval(40);
    m_refreshTimer->start();
    connect(m_refreshTimer,SIGNAL(timeout()),this,SLOT(refresh()));

    x.resize(300);
    y.resize(300);
    for (int i = 0; i< x.size() ; i++)
    {
        x[i] = 1 * i;     // time axis
        y[i] = 0.0;
    }

    // add curves
    fuelcurve = new QwtPlotCurve("Fuel");
    fuelcurve->setPen(QPen(Qt::red, 2.0));
    fuelcurve->setRawData(x.data(), y.data(), x.size());
    fuelcurve->attach(ui->plot_fuel);
    fuelcurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    //ui->plot_fuel->setTitle("TPS");

    ui->plot_fuel->setAxisScale(QwtPlot::yLeft, 0, 100);
    ui->plot_fuel->setAxisTitle(QwtPlot::xTop, "Time/seconds");
    ui->plot_fuel->setAxisScale(QwtPlot::xBottom, 0, x.size());

    //this->splash();
    qDebug("Setting up...\n");
    this->setup();
    qDebug("Done, starting.\n");
    this->selectEngine();

}

rzdash::~rzdash()
{
    qDebug("Exiting...");
    //qDebug() << "Main Thread ID: " << QString::number(this->thread()->currentThreadId() , 16).prepend("0x");
    engineThread.quit();
    delete engine;
    delete m_refreshTimer;
    delete optionsform;
    delete ui;
}


void rzdash::updateDatalogSettings() {

    engine->setSettings(AbstractDatalog::PortName, optionsform->getSettings(optionsForm::PortName));
    engine->setSettings(AbstractDatalog::PortSpeed, optionsform->getSettings(optionsForm::PortSpeed));
    engine->setSettings(AbstractDatalog::DatalogType, optionsform->getSettings(optionsForm::DatalogType));
    engine->setSettings(AbstractDatalog::DatalogRefreshRate, optionsform->getSettings(optionsForm::DatalogRefreshRate));
    engine->setSettings(AbstractDatalog::InjectorSize, optionsform->getSettings(optionsForm::InjectorSize));
    engine->setSettings(AbstractDatalog::FuelConsumption, optionsform->getSettings(optionsForm::FuelConsumption));
    engine->setSettings(AbstractDatalog::SpeedFormat, optionsform->getSettings(optionsForm::SpeedFormat));
    engine->setSettings(AbstractDatalog::SpeedTrim, optionsform->getSettings(optionsForm::SpeedTrim));

}

void rzdash::refresh()
{
    QString temp;

    temp.setNum(engine->getValues(AbstractDatalog::RPM), 'f', 0);
    ui->l_rpm->setText(temp);

    temp.setNum(engine->getValues(AbstractDatalog::TPS), 'f', 0);
    temp.append(" %");
    ui->l_tps->setText(temp);

    temp.setNum(engine->getValues(AbstractDatalog::ECT), 'f', 2);
    temp.append(" C");
    ui->l_ect->setText(temp);

    temp.setNum(engine->getValues(AbstractDatalog::VSS), 'f', 0);
    ui->l_vss->setText(temp);

    temp.setNum(engine->getValues(AbstractDatalog::INJ), 'f', 3);
    temp.append(" ms");
    ui->l_inj->setText(temp);

    ui->th_ect->setValue(engine->getValues(AbstractDatalog::ECT));

    ui->th_tps->setValue(engine->getValues(AbstractDatalog::TPS));

    ui->th_rpm->setValue(engine->getValues(AbstractDatalog::RPM));

    y.prepend((double)engine->getValues(AbstractDatalog::TPS));
    y.resize(x.size());
    ui->plot_fuel->replot();

    //if ((bool)ectune->getValues(AbstractDatalog::VTEC))
    //    ui->l_vtec->show();

    //else
        ui->l_vtec->hide();     
}


void rzdash::showOptions()
{
    optionsform->show();
}

void rzdash::setup()
{
    //this->setWindowFlags(Qt::FramelessWindowHint); // Sets a frameless window

    optionsform = new optionsForm();
    ui->l_vtec->hide();

    connect(this->ui->b_options,SIGNAL(clicked()),this,SLOT(showOptions()));
    connect(this->ui->b_quit,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(optionsform,SIGNAL(settingsChanged()),this,SLOT(updateDatalogSettings()));
    connect(optionsform,SIGNAL(settingsChanged()),this,SLOT(selectEngine()));

}

void rzdash::splash()
{
    QSplashScreen *splash = new QSplashScreen(this, QPixmap(":/Rz_Splash.png"));

    splash->show();
    splash->repaint();

    splash->showMessage("mobyfab@gmail.com", Qt::AlignHCenter | Qt::AlignTop, Qt::white);

    splash->finish(this);
}


void rzdash::selectEngine()
{

    if (!engine.isNull()) {
       delete engine;
       engineThread.quit();
    }

    datalogType = optionsform->getSettings(optionsForm::DatalogType);

    if (datalogType == "Crome 1.4+")
        engine = new Crome;
    else if (datalogType == "eCtune")
        engine = new eCtune;
    else if (datalogType == "AEM ems")
        engine = new Ems;
    else if (datalogType == "Hondata Kpro")
        engine = new Kpro;
    else if (datalogType == "OBD II")
        engine = new Obd;
    else if (datalogType == "Hondata S300")
        engine = new S300;

    else
        engine = new AbstractDatalog; // Avoid null pointer

    engine.data()->moveToThread(&engineThread);
    engineThread.start();
    engine.data()->run();

    this->updateDatalogSettings();
}
