#include "CGHSStats.h"


CGHSStats::CGHSStats(QWidget *parent)
    : CAbsStats(parent)
{

}

CGHSStats::~CGHSStats()
{

}

bool CGHSStats::get_size(const QString &lineStr, uint32_t &size)
{
    bool ret = false;

    QStringList lineStrSplit = lineStr.split(' ', QString::SkipEmptyParts);

    if (lineStrSplit.size()>1)
    {
        QStringList beginStrSplit = lineStrSplit.at(0).split('+', QString::SkipEmptyParts);
        uint32_t strSize = beginStrSplit.size();

        if (strSize > 1)
        {
            bool ok = false;
            size = beginStrSplit.at(strSize-1).toInt(&ok, 16);
            ret = true;
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool CGHSStats::get_section(const QString &lineStr, QString &section)
{
    bool ret = false;

    QStringList lineStrSplit = lineStr.split(' ', QString::SkipEmptyParts);
    uint32_t lineSize = lineStrSplit.size();

    if (3 == lineSize)
    {
        section = lineStrSplit.at(1);
        ret = true;
    }
    else if (5 == lineSize)
    {
        section = lineStrSplit.at(3);
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool CGHSStats::get_fileName(const QString &lineStr, QString &fileName)
{
    bool ret = false;

    QStringList lineStrSplit = lineStr.split(' ', QString::SkipEmptyParts);
    uint32_t lineSize = lineStrSplit.size();

    if (lineSize > 1)
    {
        fileName = lineStrSplit.at(lineStrSplit.size()-1);
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool CGHSStats::get_moduleName(const QString &lineStr, QString &moduleName)
{
    bool ret = false;

    QStringList lineStrSplit = lineStr.split(' ', QString::SkipEmptyParts);
    uint32_t lineSize = lineStrSplit.size();

    if (lineSize > 1)
    {
        QStringList endStrSplit = lineStrSplit.at(lineStrSplit.size()-1).split('_', QString::SkipEmptyParts);
        uint32_t size = endStrSplit.size();

        if (size > 1)
        {
            moduleName = endStrSplit.at(0);
            ret = true;
        }
        else
        {
            QStringList endStrSplit = lineStrSplit.at(lineStrSplit.size()-1).split('.', QString::SkipEmptyParts);
            uint32_t size = endStrSplit.size();

            if (size > 1)
            {
                moduleName = endStrSplit.at(0);
                ret = true;
            }
            else
            {
                ret = false;
            }

            ret = false;
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool CGHSStats::parse_map_file(QString filePath)
{
    bool ret = false;

    if (open_file(filePath))
    {
        ParserState_t parseStep = PARSER_WAITING;
        QFile * pFile = get_file();
        QTextStream mapFileStream(pFile);
        QString lineStr;

        while (!mapFileStream.atEnd())
        {
            lineStr = mapFileStream.readLine(1000);

            if (!lineStr.isEmpty())
            {
                if ((lineStr == '\f') && (PARSER_WAITING == parseStep))
                {
                    parseStep = PARSER_RUN;
                    lineStr = mapFileStream.readLine(1000);
                    lineStr = mapFileStream.readLine(1000);
                    lineStr = mapFileStream.readLine(1000);
                    lineStr = mapFileStream.readLine(1000);
                    lineStr = mapFileStream.readLine(1000);
                }
                else if ((lineStr == '\f') && (PARSER_RUN == parseStep))
                {
                    parseStep = PARSER_FINISH;
                    break;
                }

                if (PARSER_RUN == parseStep)
                {
                    uint32_t size;
                    QString section;
                    QString fileName;
                    QString moduleName;

                    if (get_size_section_fileName_ModuleName(lineStr, size, section, fileName, moduleName))
                    {
                        if (section_is_allwed(section))
                        {
//                            qDebug() << moduleName << ", " << fileName << ", "  << section << ", "  << size;
                            statistic(size, section, fileName, moduleName);
                        }
                    }
                    else
                    {
                    }
                }
            }
        }

        parseStep = PARSER_WAITING;
//        print_data();
        close_file();

        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}
