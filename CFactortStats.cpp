#include "CFactortStats.h"


CFactorStstas::CFactorStstas(QWidget *parent)
    : pAbsStats(nullptr)
{
    pParent = parent;
}

CFactorStstas::~CFactorStstas()
{

}

CAbsStats * CFactorStstas::create_map_stats(QString format)
{
    pAbsStats = nullptr;

    if ("GreenHills" == format)
    {
        CGHSStats * pGhsStats = new CGHSStats(pParent);
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
