#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <memory>

#include <QWidget>
#include <QImage>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>

namespace Ui {
class FilterWidget;
}

class Filter;

class FilterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilterWidget(Filter& filter, QWidget *parent = 0);
    ~FilterWidget();

    void process();

    void setSourcePicture(const QImage& sourcePicture);
    void setSourceThumbnail(const QImage& sourceThumbnail);
    void updateThumbnail();

    QString title() const;
    QPropertyAnimation* colorAnimation();

signals:
    void pictureProcessed(const QImage& picture);

protected:
    void mousePressEvent(QMouseEvent*) override;

private:
    void initAnimations();
    void startSelectionAnimation();

private:
    Ui::FilterWidget *ui;
    Filter& mFilter;

    QImage mDefaultSourcePicture;
    QImage mSourcePicture;
    QImage mSourceThumbnail;

    QImage mFilteredPicture;
    QImage mFilteredThumbnail;

    QPropertyAnimation mSelectionAnimation;
    QPropertyAnimation* mColorAnimation;
    QGraphicsColorizeEffect mColorEffect;
};

#endif // FILTERWIDGET_H
