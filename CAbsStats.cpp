#include "CAbsStats.h"


CAbsStats::CAbsStats(QWidget *parent)
    : QWidget(parent),
      pFile(nullptr)

{

}

CAbsStats::~CAbsStats()
{
    if (nullptr != pFile)
    {
        delete pFile;
        pFile = nullptr;
    }
}

bool CAbsStats::open_file(QString filePath)
{
    int ret = 0;

    if (filePath.isEmpty())
    {
        ret = QMessageBox::warning(this,
                                   tr("Warning"),
                                   tr("File path is empty.\n"
                                      "Please enter the map file path."),
                                   QMessageBox::Cancel);

        ret = false;
    }
    else
    {
        QFileInfo fileInfo;

        fileInfo.setFile(filePath);

        if (!fileInfo.exists())
        {
            ret = QMessageBox::warning(this,
                                       tr("Warning"),
                                       tr("The path is not exist.\n"
                                          "Please check the input path."),
                                       QMessageBox::Cancel);

            ret = false;
        }
        else if (!fileInfo.isFile())
        {
            ret = QMessageBox::warning(this,
                                       tr("Warning"),
                                       tr("The Path is not a file.\n"
                                          "Please check the input path."),
                                       QMessageBox::Cancel);

            ret = false;
        }
        else
        {
            pFile = new QFile(filePath);
            if (pFile->open(QFile::ReadOnly | QIODevice::ExistingOnly))
            {
                ret = true;
            }
            else
            {
                ret = QMessageBox::warning(this,
                                           tr("Warning"),
                                           tr("Failed to open the file.\n"
                                              "Please check the file path."),
                                           QMessageBox::Cancel);

                ret = false;
            }
        }
    }

    return ret;
}

void CAbsStats::close_file()
{
    if ((nullptr != pFile) && (pFile->isOpen()))
    {
        pFile->close();
    }
}

QFile *CAbsStats::get_file()
{
    return pFile;
}

bool CAbsStats::section_is_allwed(QString section)
{
    bool ret = false;
    uint32_t idx = 0;
    uint32_t sectionCnt = sectionFilter.size();

    for (idx=0; idx<sectionCnt; idx++)
    {
        if (section == sectionFilter.at(idx))
            ret = true;
    }

    return ret;
}

void CAbsStats::print_data()
{
    QMapIterator<QString, ModuleObj> moduleIter(moduleMap);

    while (moduleIter.hasNext())
    {
        moduleIter.next();
        qDebug() << moduleIter.key();
    }
}

void CAbsStats::set_section_filter(QVector<QString> &filter)
{
    sectionFilter = filter;
}

bool CAbsStats::get_size_section_fileName_ModuleName(const QString &lineStr,
                                                     uint32_t &size,
                                                     QString &section,
                                                     QString &fileName,
                                                     QString &moduleName)
{
    bool ret = false;

    if (get_size(lineStr, size) &&
        get_section(lineStr, section) &&
        get_fileName(lineStr, fileName) &&
        get_moduleName(lineStr, moduleName))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

void CAbsStats::statistic(uint32_t &size, QString &section, QString &fileName, QString &moduleName)
{
    moduleMap[moduleName].size += size;
    moduleMap[moduleName].files[fileName].size += size;
    moduleMap[moduleName].files[fileName].sections[section].size += size;
}

void CAbsStats::removeItem(QTreeWidgetItem *item)
{
    int count = item->childCount();
    if(count == 0)//没有子节点，直接删除
    {
        delete item;
        return;
    }

    for(int i=0; i<count; i++)
    {
        QTreeWidgetItem *childItem = item->child(0);//删除子节点
        removeItem(childItem);
    }
    delete item;//最后将自己删除

}

void CAbsStats::remove_all_module(QTreeWidget *tree)
{
    //通过删除根节点及其子节点来达到删除整个TreeWidget的目的
    QTreeWidgetItem *item;
    item = tree->topLevelItem(0);
    while(item)
    {
         removeItem(item);
         item = tree->topLevelItem(0);
    }
}

void CAbsStats::set_tree_model(QTreeWidget *tree)
{
    remove_all_module(tree);

    if (0 == tree->header()->count())
    {
        QStringList hdrLable;
        uint8_t size = sectionFilter.size();

        hdrLable << "modules";
        for (uint8_t i=0; i<size; i++)
        {
            hdrLable << sectionFilter.at(i);
        }
        tree->setHeaderLabels(hdrLable);
    }

    QMapIterator<QString, ModuleObj> moduleIter(moduleMap);
    while (moduleIter.hasNext())
    {
        moduleIter.next();

        QStringList module;
        QString moduleStr = moduleIter.key() + "(" + QString::number(moduleIter.value().size) + ")";
        module << moduleStr;
        QTreeWidgetItem * moduleItem = new QTreeWidgetItem(module);
        tree->addTopLevelItem(moduleItem);

        QMapIterator<QString, FileObj> fileIter(moduleIter.value().files);
        while (fileIter.hasNext())
        {
            fileIter.next();

            QStringList file;
            QString fileStr = fileIter.key() + "(" + QString::number(fileIter.value().size) + ")";
            file << fileStr;
            QTreeWidgetItem * fileIter = new QTreeWidgetItem(module);

            moduleItem->addChild(fileIter);
        }
    }
}

