#include "FilterWidget.h"
#include "ui_FilterWidget.h"

#include "Filter.h"

using namespace std;

FilterWidget::FilterWidget(Filter& filter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget),
    mFilter(filter),
    mDefaultSourcePicture(":/lenna.jpg"),
    mSourcePicture(),
    mSourceThumbnail(mDefaultSourcePicture.scaled(QSize(256, 256),
                     Qt::KeepAspectRatio,
                     Qt::SmoothTransformation)),
    mFilteredPicture(),
    mFilteredThumbnail(),
    mSelectionAnimation(),
    mColorAnimation(new QPropertyAnimation()),
    mColorEffect()
{
    ui->setupUi(this);
    ui->titleLabel->setText(mFilter.name());

    initAnimations();
    updateThumbnail();
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::process()
{
    mFilteredPicture = mFilter.process(mSourcePicture);
    emit pictureProcessed(mFilteredPicture);
}

void FilterWidget::setSourcePicture(const QImage& sourcePicture)
{
    mSourcePicture = sourcePicture;
}

void FilterWidget::setSourceThumbnail(const QImage& sourceThumbnail)
{
    mSourceThumbnail = sourceThumbnail;
}

void FilterWidget::updateThumbnail()
{
    mFilteredThumbnail = mFilter.process(mSourceThumbnail);
    QPixmap pixmap = QPixmap::fromImage(mFilteredThumbnail);
    ui->thumbnailLabel->setPixmap(pixmap);
}

QString FilterWidget::title() const
{
    return mFilter.name();
}

QPropertyAnimation* FilterWidget::colorAnimation()
{
    return mColorAnimation;
}

void FilterWidget::mousePressEvent(QMouseEvent*)
{
    process();
    startSelectionAnimation();
}

void FilterWidget::initAnimations()
{
    mSelectionAnimation.setTargetObject(ui->thumbnailLabel);
    mSelectionAnimation.setPropertyName("geometry");
    mSelectionAnimation.setDuration(200);

    mColorEffect.setColor(QColor(0, 150, 150));
    mColorEffect.setStrength(0.0);
    ui->thumbnailLabel->setGraphicsEffect(&mColorEffect);
    mColorAnimation->setTargetObject(&mColorEffect);
    mColorAnimation->setPropertyName("strength");
    mColorAnimation->setDuration(200);
    mColorAnimation->setStartValue(1.0);
    mColorAnimation->setEndValue(0.0);
    connect(mColorAnimation, &QPropertyAnimation::finished, [this] {
        updateThumbnail();
    });
}

void FilterWidget::startSelectionAnimation()
{
    if (mSelectionAnimation.state() == QAbstractAnimation::Stopped) {
        QRect currentGeometry = ui->thumbnailLabel->geometry();
        QRect targetGeometry = ui->thumbnailLabel->geometry();
        targetGeometry.setY(targetGeometry.y() - 50.0);

        mSelectionAnimation.setKeyValueAt(0, currentGeometry);
        mSelectionAnimation.setKeyValueAt(0.3, targetGeometry);
        mSelectionAnimation.setKeyValueAt(1, currentGeometry);
        mSelectionAnimation.start();
    }
}


