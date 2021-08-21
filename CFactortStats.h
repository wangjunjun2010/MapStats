#ifndef CFACTORSTATS_H
#define CFACTORSTATS_H


#include "CAbsStats.h"
#include "CGHSStats.h"


class CFactorStstas
{
public:
    CFactorStstas(QWidget * parent = nullptr);
    ~CFactorStstas();

public:
    CAbsStats * create_map_stats(QString format);

private:
    CAbsStats * pAbsStats;
    QWidget   * pParent;
};


#endif // CFACTORSTATS_H
