#ifndef JOBRESULT_H
#define JOBRESULT_H

#include <QSize>
#include <QVector>
#include <QPointF>
#include <QDataStream>

struct JobResult
{
    JobResult(int valueCount = 1) :
        areaSize(0, 0),
        pixelPositionY(0),
        moveOffset(0, 0),
        scaleFactor(0.0),
        values(valueCount)
    {
    }

    QSize areaSize;
    int pixelPositionY;
    QPointF moveOffset;
    double scaleFactor;

    QVector<int> values;
};

inline QDataStream &operator<<(QDataStream& out, const JobResult& jobResult)
{
    out << jobResult.areaSize
        << jobResult.pixelPositionY
        << jobResult.moveOffset
        << jobResult.scaleFactor
        << jobResult.values;
    return out;
}

inline QDataStream &operator>>(QDataStream& in, JobResult& jobResult)
{
    in >> jobResult.areaSize;
    in >> jobResult.pixelPositionY;
    in >> jobResult.moveOffset;
    in >> jobResult.scaleFactor;
    in >> jobResult.values;
    return in;
}

Q_DECLARE_METATYPE(JobResult)

#endif // JOBRESULT_H
