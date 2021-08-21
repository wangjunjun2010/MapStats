#include "MainWnd.h"
#include "ui_MainWnd.h"


MainWnd::MainWnd(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MainWnd),
      pMapStatsFactory(nullptr)
{
    ui->setupUi(this);
    pMapStatsFactory = new CFactorStstas(this);
    mapFormat = ui->mapFormatComboBox->currentText();
}

MainWnd::~MainWnd()
{
    delete ui;
    delete pMapStatsFactory;
}

void MainWnd::on_selectBtn_clicked()
{
    mapFilePath =
            QFileDialog::getOpenFileName(this,
                                         tr("Open map file."),
                                         tr("./"),
                                         tr("Map File (*.map)"));

    ui->mapFilePathLineEdit->setText(mapFilePath);
}

void MainWnd::on_analyseBtn_clicked()
{
    CAbsStats * pMapStats = pMapStatsFactory->create_map_stats(mapFormat);
    if (nullptr != pMapStats)
    {
        mapFilter << ".text" << ".bss" << ".data";
        pMapStats->set_section_filter(mapFilter);
        pMapStats->parse_map_file(mapFilePath);
        pMapStats->set_tree_model(ui->treeWidget);
        delete pMapStats;
    }
}

void MainWnd::on_mapFormatComboBox_currentIndexChanged(const QString &arg1)
{
    mapFormat = arg1;
}


void MainWnd::on_mapFilePathLineEdit_textChanged(const QString &arg1)
{
    mapFilePath = arg1;
}
