#ifndef OBD_H
#define OBD_H

#include <ecu/abstractdatalog.h>

class Obd : public AbstractDatalog
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

#endif // OBD_H
