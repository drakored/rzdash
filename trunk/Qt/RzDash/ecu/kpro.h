#ifndef KPRO_H
#define KPRO_H

#include <ecu/abstractdatalog.h>

class Kpro : virtual public AbstractDatalog
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

#endif // KPRO_H
