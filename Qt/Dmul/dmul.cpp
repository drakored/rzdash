#include "dmul.h"
#include "ui_dmul.h"

Dmul::Dmul(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dmul)
{
    ui->setupUi(this);

    m_serialThread = new QThread;
    m_serial = new Serial;
    m_serial->moveToThread(m_serialThread);
    m_serialThread->start();

    this->updateValues();


    connect(ui->vs_tps,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_batt,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_iat,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_ect,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_tps,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_ign,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_map,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_rpm,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_vss,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_inj,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_O2,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_load,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->vs_baro,SIGNAL(valueChanged(int)),this,SLOT(updateValues()));
    connect(ui->b_update,SIGNAL(clicked()),this,SLOT(updateDatalogSettings()));

    updateDatalogSettings();
}

Dmul::~Dmul()
{
    delete ui;
}

QString Dmul::getSettings(Serial::enumSettings setting)
{
    switch(setting)
      {
          case Serial::PortName: return ui->c_portName->currentText();
                  break;
          case Serial::PortSpeed: return ui->c_portSpeed->currentText() ;
                  break;
          case Serial::DatalogType: return ui->c_dataType->currentText();
                  break;
          //case Serial::DatalogRefreshRate: return ui->sb_refreshRate->text();
          //        break;
          default: return QString("NULL");
                  break;
      }
}

void Dmul::updateDatalogSettings() {

    m_serial->setSettings(Serial::PortName, getSettings(Serial::PortName));
    m_serial->setSettings(Serial::PortSpeed, getSettings(Serial::PortSpeed));
    m_serial->setSettings(Serial::DatalogType, getSettings(Serial::DatalogType));
    m_serial->setSettings(Serial::DatalogRefreshRate, getSettings(Serial::DatalogRefreshRate));
    m_serial->resetSerial();
}

void Dmul::updateValues() {
    m_serial->setValues(Serial::TPS, (float)ui->vs_tps->value());
    m_serial->setValues(Serial::RPM, (float)ui->vs_rpm->value());
    m_serial->setValues(Serial::IAT, (float)ui->vs_iat->value());
    m_serial->setValues(Serial::ECT, (float)ui->vs_ect->value());
    m_serial->setValues(Serial::MAP, (float)ui->vs_map->value());
    m_serial->setValues(Serial::BATT, (float)ui->vs_batt->value());
    m_serial->setValues(Serial::IGN, (float)ui->vs_ign->value());
    m_serial->setValues(Serial::VSS, (float)ui->vs_vss->value());
    m_serial->setValues(Serial::INJ, (float)ui->vs_inj->value());
    m_serial->setValues(Serial::O2, (float)ui->vs_O2->value());

}
