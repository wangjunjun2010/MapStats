#ifndef CABSSTATS_H
#define CABSSTATS_H


#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include <QDebug>
#include <QListWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSettings>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>


typedef enum
{
    PARSER_WAITING = 0,
    PARSER_RUN,
    PARSER_FINISH
} ParserState_t;

class SectionObj
{
public:
    uint32_t  size;
};

class FileObj
{
public:
    uint32_t  size;
    QMap<QString, SectionObj> sections;
};

class ModuleObj
{
public:
    uint32_t  size;
    QMap<QString, FileObj> files;
};

class CAbsStats : public QWidget
{
    Q_OBJECT

public:
    CAbsStats(QWidget * parent = nullptr);
    virtual ~CAbsStats();

    virtual bool get_size(const QString & lineStr, uint32_t & size) = 0;
    virtual bool get_section(const QString & lineStr, QString & section) = 0;
    virtual bool get_fileName(const QString & lineStr, QString & fileName) = 0;
    virtual bool get_moduleName(const QString & lineStr, QString & moduleName) = 0;
    virtual bool parse_map_file(QString filePath) = 0;

    bool open_file(QString filePath);
    void close_file(void);
    QFile * get_file(void);
    bool section_is_allwed(QString section);
    void print_data(void);
    void set_section_filter(QVector<QString> & filter);
    bool get_size_section_fileName_ModuleName(const QString & lineStr,
                                              uint32_t & size,
                                              QString & section,
                                              QString & fileName,
                                              QString & moduleName);
    void statistic(uint32_t & size,
                   QString & section,
                   QString & fileName,
                   QString & moduleName);
    void removeItem(QTreeWidgetItem *item);
    void remove_all_module(QTreeWidget * tree);
    void set_tree_model(QTreeWidget * tree);

private:
    QMap<QString, ModuleObj>  moduleMap;
    QVector<QString>          sectionFilter;
    QFile                   * pFile;
};


#endif // CABSSTATS_H
