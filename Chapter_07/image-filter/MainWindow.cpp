#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QPixmap>
#include <QDir>

#include "FilterWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mSourcePicture(),
    mSourceThumbnail(),
    mFilteredPicture(mSourcePicture),
    mCurrentPixmap(),
    mCurrentFilter(nullptr),
    mFilters()
{
    ui->setupUi(this);
    ui->actionSaveAs->setEnabled(false);
    ui->pictureLabel->setMinimumSize(1, 1);

    connect(ui->actionOpenPicture, &QAction::triggered,
            this, &MainWindow::loadPicture);
    connect(ui->actionSaveAs, &QAction::triggered,
            this, &MainWindow::saveAsPicture);
    connect(ui->actionExit, &QAction::triggered,
            this, &QMainWindow::close);
    initFilters();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFilters()
{
    mFilters.push_back(ui->filterWidgetOriginal);
    mFilters.push_back(ui->filterWidgetBlur);
    mFilters.push_back(ui->filterWidgetGrayscale);

    for (int i = 0; i < mFilters.size(); ++i) {
        connect(mFilters[i], &FilterWidget::pictureProcessed,
                this, &MainWindow::displayPicture);
    }
    mCurrentFilter = mFilters[0];
}

void MainWindow::loadPicture()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open Picture",
                                                    QDir::homePath(),
                                                    tr("Images (*.png *.jpg)"));
    if (filename.isEmpty()) {
        return;
    }

    ui->actionSaveAs->setEnabled(true);
    mSourcePicture = QImage(filename);
    mSourceThumbnail = mSourcePicture.scaled(QSize(256, 256),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);
    for (int i = 0; i <mFilters.size(); ++i) {
        mFilters[i]->setSourcePicture(mSourcePicture);
        mFilters[i]->updateThumbnail(mSourceThumbnail);
    }

    mCurrentFilter->process();
}

void MainWindow::resizeEvent(QResizeEvent* /*event*/)
{
    updatePicturePixmap();
}

void MainWindow::displayPicture(const QImage& picture)
{
    mFilteredPicture = picture;
    mCurrentPixmap = QPixmap::fromImage(picture);
    updatePicturePixmap();
}

void MainWindow::saveAsPicture()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Save Picture",
                                                    QDir::homePath(),
                                                    tr("Images (*.png *.jpg)"));
    if (filename.isEmpty()) {
        return;
    }
    mFilteredPicture.save(filename);
}

void MainWindow::updatePicturePixmap()
{
    if (mCurrentPixmap.isNull()) {
        return;
    }
    ui->pictureLabel->setPixmap(
                mCurrentPixmap.scaled(ui->pictureLabel->size(),
                                      Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation));
}
