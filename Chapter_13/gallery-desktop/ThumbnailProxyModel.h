#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>

class ThumbnailProxyModel : public QIdentityProxyModel
{
public:
    ThumbnailProxyModel(QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role) const override;
   void setSourceModel(QAbstractItemModel* sourceModel) override;

private:
    void reloadThumbnails(const QModelIndex& startIndex, int count);
    void generateThumbnails(const QModelIndex& startIndex, int count);

private:
   QHash<QString, QPixmap*> mThumbnails;

};

#endif // THUMBNAILPROXYMODEL_H
