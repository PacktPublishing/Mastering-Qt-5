#ifndef FILTER_H
#define FILTER_H

#include <QImage>

class Filter
{
public:
    Filter();
    virtual ~Filter();

    virtual QImage process(const QImage& image) = 0;
};

#endif // FILTER_H
