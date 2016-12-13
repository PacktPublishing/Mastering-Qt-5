#ifndef FILTERBLUR_H
#define FILTERBLUR_H

#include <QObject>

#include <Filter.h>

class FilterOriginal : public QObject, Filter
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.masteringqt.imageanimation.filters.Filter")
    Q_INTERFACES(Filter)

public:
    FilterOriginal(QObject* parent = 0);
    ~FilterOriginal();

    QString name() const override;
    QImage process(const QImage& image) override;
};

#endif // FILTERBLUR_H
