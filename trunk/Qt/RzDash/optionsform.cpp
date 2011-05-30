#include "optionsform.h"
#include "ui_optionsform.h"

optionsForm::optionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optionsForm)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint); //Set a frameless window
    myProcess = new QProcess(this);

    settings  = new QSettings("RzCrew", "RzDash", this);

    this->setSettings();
    this->saveSettings();

    connect(ui->b_recalibrate,SIGNAL(clicked()),this,SLOT(recalibrate()));
    connect(ui->b_reboot,SIGNAL(clicked()),this,SLOT(reboot()));
    connect(ui->b_restartApp,SIGNAL(clicked()),this,SLOT(restartApp()));
    connect(ui->b_OK,SIGNAL(clicked()),this,SLOT(saveSettings()));
}

optionsForm::~optionsForm()
{
    delete ui;
    delete settings;
    delete myProcess;
}


void optionsForm::reboot()
{
    qDebug("Rebooting...");
    myProcess->start("/sbin/reboot");
}

void optionsForm::restartApp()
{
    qDebug("Restarting application...");
    myProcess->start("/home/root/restartApp.sh");
}

void optionsForm::recalibrate()
{
    qDebug("Re-calibrating...");
    myProcess->start("/home/root/recalibrate.sh");
}

void optionsForm::setSettings()
{
    qDebug() << "Settings will be saved in:" << settings->fileName() << "\n";
    if (!settings->isWritable())
        qDebug() << "Settings cannot be written!";

    ui->c_portName->setCurrentIndex(settings->value("PortName").toInt());
    ui->c_portSpeed->setCurrentIndex(settings->value("PortSpeed").toInt());
    ui->c_datalogType->setCurrentIndex(settings->value("DatalogType").toInt());
    ui->sb_refreshRate->setValue(settings->value("DatalogRefreshRate").toInt());
    ui->c_injectorSize->setCurrentIndex(settings->value("InjectorSize").toInt());
    ui->c_fuelConsumption->setCurrentIndex(settings->value("FuelConsumption").toInt());
    ui->c_speed->setCurrentIndex(settings->value("SpeedFormat").toInt());
    ui->dsb_speedTrim->setValue(settings->value("SpeedTrim").toDouble());

}

void optionsForm::saveSettings()
{
    this->hide();

    // Applying settings
    emit settingsChanged();

    // Saving settings.
    settings->setValue("PortName", ui->c_portName->currentIndex());
    settings->setValue("PortSpeed", ui->c_portSpeed->currentIndex());
    settings->setValue("DatalogType", ui->c_datalogType->currentIndex());
    settings->setValue("DatalogRefreshRate", ui->sb_refreshRate->value());
    settings->setValue("InjectorSize", ui->c_injectorSize->currentIndex());
    settings->setValue("FuelConsumption", ui->c_fuelConsumption->currentIndex());
    settings->setValue("SpeedFormat", ui->c_speed->currentIndex());
    settings->setValue("SpeedTrim", ui->dsb_speedTrim->value());

    settings->sync();
    qDebug() << "Settings saved.";

}

QString optionsForm::getSettings(enumSettings setting)
{
    switch(setting)
      {
          case PortName: return ui->c_portName->currentText();
                  break;
          case PortSpeed: return ui->c_portSpeed->currentText() ;
                  break;
          case DatalogType: return ui->c_datalogType->currentText();
                  break;
          case DatalogRefreshRate: return ui->sb_refreshRate->text();
                  break;
          case InjectorSize: return ui->c_injectorSize->currentText();
                  break;
          case FuelConsumption: return ui->c_fuelConsumption->currentText();
                  break;
          case SpeedFormat: return ui->c_speed->currentText();
                  break;
          case SpeedTrim: return ui->dsb_speedTrim->text();
                  break;
          default: return QString("NULL");
                  break;
      }
}
