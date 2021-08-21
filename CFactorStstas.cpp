#include "CFactorStstas.h"


CFactorStstas::CFactorStstas(QWidget *parent)
    : QWidget(parent),
      pAbsStats(nullptr)
{

}

CFactorStstas::~CFactorStstas()
{
    if (nullptr != pAbsStats)
    {
        delete pAbsStats;
        pAbsStats = nullptr;
    }
}

CAbsStats * CFactorStstas::create_map_stats(QString format)
{
    pAbsStats = nullptr;

    if ("GreenHills" == format)
    {
        CGHSStats * pGhsStats = new CGHSStats(this);
        pAbsStats = static_cast<CAbsStats*>(pGhsStats);
    }
    else if ("S32DS" == format)
    {

    }
    else if ("HighTec" == format)
    {

    }
    else //...
    {

    }

    return pAbsStats;
}
