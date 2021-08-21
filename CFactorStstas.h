#ifndef CGHSSTATS_H
#define CGHSSTATS_H


#include "CAbsStats.h"
#include "CGHSStats.h"


class CFactorStstas : QWidget
{
    Q_OBJECT

public:
    CFactorStstas(QWidget * parent = nullptr);
    ~CFactorStstas();

public:
    CAbsStats * create_map_stats(QString format);

private:
    CAbsStats * pAbsStats;
};


#endif // CGHSSTATS_H
