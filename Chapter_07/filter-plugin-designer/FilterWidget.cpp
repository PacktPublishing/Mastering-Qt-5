#include "FilterWidget.h"
#include "ui_FilterWidget.h"

#include "FilterBlur.h"
#include "FilterGrayscale.h"
#include "FilterOriginal.h"

using namespace std;

FilterWidget::FilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget),
    mFilterType(Original),
    mDefaultSourcePicture(":/lenna.jpg"),
    mSourcePicture(),
    mSourceThumbnail(mDefaultSourcePicture.scaled(QSize(256, 256),
                     Qt::KeepAspectRatio,
                     Qt::SmoothTransformation)),
    mFilteredPicture(),
    mFilteredThumbnail()
{
    ui->setupUi(this);
    setFilterType(Original);
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::process()
{
    mFilteredPicture = mFilter->process(mSourcePicture);
    emit pictureProcessed(mFilteredPicture);
}

void FilterWidget::setSourcePicture(const QImage& sourcePicture)
{
    mSourcePicture = sourcePicture;
}

void FilterWidget::updateThumbnail(const QImage& sourceThumbnail)
{
    mSourceThumbnail = sourceThumbnail;
    mFilteredThumbnail = mFilter->process(mSourceThumbnail);
    QPixmap pixmap = QPixmap::fromImage(mFilteredThumbnail);
    ui->thumbnailLabel->setPixmap(pixmap);
}

void FilterWidget::setTitle(const QString& tile)
{
    ui->titleLabel->setText(tile);
}

void FilterWidget::setFilterType(FilterWidget::FilterType filterType)
{
    if (filterType == mFilterType && mFilter) {
        return;
    }
    mFilterType = filterType;

    switch (filterType) {
        case Original:
            mFilter = make_unique<FilterOriginal>();
            break;

        case Blur:
            mFilter = make_unique<FilterBlur>();
            break;

        case Grayscale:
            mFilter = make_unique<FilterGrayscale>();
            break;

        default:
            break;
    }

    updateThumbnail(mSourceThumbnail);
}

QString FilterWidget::title() const
{
    return ui->titleLabel->text();
}

FilterWidget::FilterType FilterWidget::filterType() const
{
    return mFilterType;
}

void FilterWidget::mousePressEvent(QMouseEvent*)
{
    process();
}
