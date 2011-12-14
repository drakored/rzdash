#ifndef CROME_H
#define CROME_H

#include <ecu/abstractdatalog.h>

class Crome : public AbstractDatalog
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

#endif // CROME_H
