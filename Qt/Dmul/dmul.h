#ifndef DMUL_H
#define DMUL_H

#include <QWidget>
#include <QThread>
#include <serial.h>
#include <qdebug.h>

namespace Ui {
    class Dmul;
}

class Dmul : public QWidget
{
    Q_OBJECT

public:
    explicit Dmul(QWidget *parent = 0);
    ~Dmul();
    QString getSettings(Serial::enumSettings setting);

private:
    Ui::Dmul *ui;
    QPointer<QThread> m_serialThread;
    QPointer<Serial> m_serial;

private slots:
    void updateDatalogSettings();
    void updateValues();

};

#endif // DMUL_H
