#ifndef FILTERGRAYSCALE_H
#define FILTERGRAYSCALE_H

#include "Filter.h"

class FilterGrayscale : public Filter
{
public:
    FilterGrayscale();
    ~FilterGrayscale();

    QImage process(const QImage& image) override;
};


#endif // FILTERGRAYSCALE_H
