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
    mFilterLoader(),
    mCurrentFilter(nullptr),
    mFilters(),
    mLoadPictureAnimation(),
    mPictureOpacityEffect(),
    mFiltersGroupAnimation()
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
    initAnimations();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFilters()
{
    mFilterLoader.loadFilters();

    auto& filters = mFilterLoader.filters();
    for(auto& filter : filters) {
        FilterWidget* filterWidget = new FilterWidget(*filter);
        ui->filtersLayout->addWidget(filterWidget);
        mFilters.append(filterWidget);
    }

    for (int i = 0; i < mFilters.size(); ++i) {
        connect(mFilters[i], &FilterWidget::pictureProcessed,
                this, &MainWindow::displayPicture);
    }

    if (mFilters.length() > 0) {
        mCurrentFilter = mFilters[0];
    }
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
        mFilters[i]->setSourceThumbnail(mSourceThumbnail);
        //mFilters[i]->updateThumbnail(); // removed when using the group animation
    }

    mCurrentFilter->process();
    mLoadPictureAnimation.start();
    mFiltersGroupAnimation.start();
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

void MainWindow::initAnimations()
{
    ui->pictureLabel->setGraphicsEffect(&mPictureOpacityEffect);
    mLoadPictureAnimation.setTargetObject(&mPictureOpacityEffect);
    mLoadPictureAnimation.setPropertyName("opacity");
    mLoadPictureAnimation.setDuration(500);
    mLoadPictureAnimation.setStartValue(0);
    mLoadPictureAnimation.setEndValue(1);
    mLoadPictureAnimation.setEasingCurve(QEasingCurve::InCubic);

    for (FilterWidget* filterWidget : mFilters) {
        mFiltersGroupAnimation.addAnimation(filterWidget->colorAnimation());
    }
}
