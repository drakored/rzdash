#ifndef ECTUNE_H
#define ECTUNE_H

#include <ecu/abstractdatalog.h>

class eCtune : public AbstractDatalog
{
    Q_OBJECT

public:
    void run();


signals:

public slots:


private:

private slots:
    void readData();
    bool sendHandShake();
    bool checkHandShake();
    bool getRawValues();
    bool waitValues();
    void processValues();
    void refresh();

};

#endif // ECTUNE_H
