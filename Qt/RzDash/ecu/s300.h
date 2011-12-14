#ifndef S300_H
#define S300_H

#include <ecu/abstractdatalog.h>

class S300 : public AbstractDatalog
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

#endif // S300_H
