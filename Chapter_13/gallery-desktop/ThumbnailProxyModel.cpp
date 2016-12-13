#include "ThumbnailProxyModel.h"

#include "PictureModel.h"

const unsigned int THUMBNAIL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent) :
    QIdentityProxyModel(parent),
    mThumbnails()
{
}


QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DecorationRole) {
        return QIdentityProxyModel::data(index, role);
    }

    QString filepath = sourceModel()->data(index, PictureModel::Roles::FilePathRole).toString();
    return *mThumbnails[filepath];
}


void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if (!sourceModel) {
        return;
    }

    connect(sourceModel, &QAbstractItemModel::modelReset, [this] {
        reloadThumbnails(index(0, 0), rowCount());
    });

    connect(sourceModel, &QAbstractItemModel::rowsInserted, [this](const QModelIndex& parent, int first, int last) {
        generateThumbnails(index(first, 0), last - first + 1);
    });
}

void ThumbnailProxyModel::reloadThumbnails(const QModelIndex& startIndex, int count)
{
    qDeleteAll(mThumbnails);
    mThumbnails.clear();
    generateThumbnails(startIndex, count);
}

void ThumbnailProxyModel::generateThumbnails(const QModelIndex& startIndex, int count)
{
    if (!startIndex.isValid()) {
        return;
    }

    const QAbstractItemModel* model = startIndex.model();
    for(int row = startIndex.row(); row < count; row++) {
        QString filepath = model->data(model->index(row, 0), PictureModel::Roles::FilePathRole).toString();
        QPixmap pixmap(filepath);
        auto thumbnail = new QPixmap(pixmap
                                     .scaled(THUMBNAIL_SIZE, THUMBNAIL_SIZE,
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
        mThumbnails.insert(filepath, thumbnail);
    }
}
