#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    virtual ~Filter() {}
    virtual QString name() const = 0;
    virtual QImage process(const QImage& image) = 0;
};

#define Filter_iid "org.masteringqt.imageanimation.filters.Filter"
Q_DECLARE_INTERFACE(Filter, Filter_iid)

#endif // FILTER_H
