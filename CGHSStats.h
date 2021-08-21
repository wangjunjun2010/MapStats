#ifndef CGHSSTATS_H
#define CGHSSTATS_H


#include "CAbsStats.h"


class CGHSStats : public CAbsStats
{
    Q_OBJECT

public:
    CGHSStats(QWidget * parent = nullptr);
    ~CGHSStats();

private:
    virtual bool get_size(const QString & lineStr, uint32_t & size);
    virtual bool get_section(const QString & lineStr, QString & section);
    virtual bool get_fileName(const QString & lineStr, QString & fileName);
    virtual bool get_moduleName(const QString & lineStr, QString & moduleName);
    virtual bool parse_map_file(QString filePath);
};


#endif // CGHSSTATS_H
