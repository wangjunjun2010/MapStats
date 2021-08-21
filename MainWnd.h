#ifndef MAINWND_H
#define MAINWND_H


#include "Stats/CFactortStats.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWnd; }
QT_END_NAMESPACE


class MainWnd : public QWidget
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

private slots:
    void on_selectBtn_clicked();
    void on_analyseBtn_clicked();
    void on_mapFormatComboBox_currentIndexChanged(const QString &arg1);
    void on_mapFilePathLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWnd    * ui;
    CFactorStstas  * pMapStatsFactory;
    QString          mapFormat;
    QString          mapFilePath;
    QVector<QString> mapFilter;
};


#endif // MAINWND_H
