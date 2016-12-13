#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>

namespace Ui {
class GalleryWidget;
}

class QItemSelectionModel;
class AlbumModel;
class PictureModel;

class ThumbnailProxyModel;

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryWidget(QWidget *parent = 0);
    ~GalleryWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);

    void setPictureModel(ThumbnailProxyModel* pictureModel);
    void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

signals:
    void pictureActivated(const QModelIndex& index);

private:
    Ui::GalleryWidget *ui;
};

#endif // GALLERYWIDGET_H
