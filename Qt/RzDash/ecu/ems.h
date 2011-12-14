#ifndef EMS_H
#define EMS_H

#include <ecu/abstractdatalog.h>
#include <QBitArray>

class Ems : public AbstractDatalog
{
    Q_OBJECT

public:
    void run();

signals:

public slots:

private slots:
    void readData();
    void refresh();
    void processValues();

private:

};

#endif // EMS_H
