#include "Job.h"

Job::Job(const JobRequest& jobRequest, QObject *parent) :
    QObject(parent),
    mAbort(false),
    mJobRequest(jobRequest)
{
}

void Job::run()
{
    JobResult jobResult(mJobRequest.areaSize.width());
    jobResult.areaSize = mJobRequest.areaSize;
    jobResult.pixelPositionY = mJobRequest.pixelPositionY;
    jobResult.moveOffset = mJobRequest.moveOffset;
    jobResult.scaleFactor = mJobRequest.scaleFactor;

    double imageHalfWidth = mJobRequest.areaSize.width() / 2.0;
    double imageHalfHeight = mJobRequest.areaSize.height() / 2.0;

    for (int imageX = 0; imageX < mJobRequest.areaSize.width(); ++imageX) {
        if (mAbort.load()) {
            return;
        }

        int iteration = 0;
        double x0 = (imageX - imageHalfWidth)
                * mJobRequest.scaleFactor + mJobRequest.moveOffset.x();

        double y0 = (mJobRequest.pixelPositionY - imageHalfHeight)
                * mJobRequest.scaleFactor - mJobRequest.moveOffset.y();
        double x = 0.0;
        double y = 0.0;
        do {
            double nextX = (x * x) - (y * y) + x0;
            y = 2.0 * x * y + y0;
            x = nextX;
            iteration++;

        } while(iteration < mJobRequest.iterationMax
                && (x * x) + (y * y) < 4.0);

        jobResult.values[imageX] = iteration;
    }

    emit jobCompleted(jobResult);
}

void Job::abort()
{
    mAbort.store(true);
}
