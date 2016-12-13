#include "FilterOriginal.h"

FilterOriginal::FilterOriginal(QObject* parent) :
    QObject(parent)
{
}

FilterOriginal::~FilterOriginal()
{
}

QString FilterOriginal::name() const
{
    return "Original";
}

QImage FilterOriginal::process(const QImage& image)
{
    return image;
}

