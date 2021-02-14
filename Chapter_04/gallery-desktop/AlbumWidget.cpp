#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"

#include <QInputDialog>
#include <QFileDialog>

#include "AlbumModel.h"
#include "PictureModel.h"
#include "ThumbnailProxyModel.h"

#include "PictureDelegate.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mAlbumSelectionModel(nullptr),
    mPictureModel(nullptr),
    mPictureSelectionModel(nullptr)
{
    ui->setupUi(this);
    clearUi();

    ui->thumbnailListView->setSpacing(5);
    ui->thumbnailListView->setResizeMode(QListView::Adjust);
    ui->thumbnailListView->setFlow(QListView::LeftToRight);
    ui->thumbnailListView->setWrapping(true);
    ui->thumbnailListView->setItemDelegate(new PictureDelegate(this));

    connect(ui->thumbnailListView, &QListView::doubleClicked,
            this, &AlbumWidget::pictureActivated);

    connect(ui->deleteButton, &QPushButton::clicked,
            this, &AlbumWidget::deleteAlbum);

    connect(ui->editButton, &QPushButton::clicked,
            this, &AlbumWidget::editAlbum);

    connect(ui->addPicturesButton, &QPushButton::clicked,
            this, &AlbumWidget::addPictures);
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel* albumModel)
{
    mAlbumModel = albumModel;

    connect(mAlbumModel, &QAbstractItemModel::dataChanged, [this] (const QModelIndex &topLeft) {
        if (topLeft == mAlbumSelectionModel->currentIndex()) {
            loadAlbum(topLeft);
        }
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel)
{
    mAlbumSelectionModel = albumSelectionModel;

    connect(mAlbumSelectionModel, &QItemSelectionModel::selectionChanged, [this](const QItemSelection &selected) {
        if (selected.isEmpty()) {
            clearUi();
            return;
        }
        loadAlbum(selected.indexes().first());
    });
}

void AlbumWidget::setPictureModel(ThumbnailProxyModel* pictureModel)
{
    mPictureModel = pictureModel;
    ui->thumbnailListView->setModel(pictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
    ui->thumbnailListView->setSelectionModel(selectionModel);
}

void AlbumWidget::deleteAlbum()
{
    if (mAlbumSelectionModel->selectedIndexes().isEmpty()) {
        return;
    }
    int row = mAlbumSelectionModel->currentIndex().row();
    mAlbumModel->removeRow(row);

    // Try to select the previous album
    QModelIndex previousModelIndex = mAlbumModel->index(row - 1, 0);
    if(previousModelIndex.isValid()) {
        mAlbumSelectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }

    // Try to select the next album
    QModelIndex nextModelIndex = mAlbumModel->index(row, 0);
    if(nextModelIndex.isValid()) {
        mAlbumSelectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }
}

void AlbumWidget::editAlbum()
{
    if (mAlbumSelectionModel->selectedIndexes().isEmpty()) {
        return;
    }
    QModelIndex currentAlbumIndex = mAlbumSelectionModel->selectedIndexes().first();
    QString oldAlbumName = mAlbumModel->data(currentAlbumIndex, AlbumModel::Roles::NameRole).toString();

    bool ok;
    QString newName = QInputDialog::getText(this,
                                            "Album's name",
                                            "Change Album name",
                                            QLineEdit::Normal,
                                            oldAlbumName,
                                            &ok);

    if (ok && !newName.isEmpty()) {
        mAlbumModel->setData(currentAlbumIndex, newName, AlbumModel::Roles::NameRole);
    }
}

void AlbumWidget::addPictures()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                          "Add pictures",
                                                          QDir::homePath(),
                                                          "Picture files (*.jpg *.png)");
    if (!filenames.isEmpty()) {
        QModelIndex lastModelIndex;
        for (auto filename : filenames) {
            Picture picture(filename);
            lastModelIndex = mPictureModel->pictureModel()->addPicture(picture);
        }
        lastModelIndex = mPictureModel->index(lastModelIndex.row(), 0);
        ui->thumbnailListView->setCurrentIndex(lastModelIndex);
    }
}

void AlbumWidget::clearUi()
{
    ui->albumName->setText("");
    ui->deleteButton->setVisible(false);
    ui->editButton->setVisible(false);
    ui->addPicturesButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex& albumIndex)
{
    mPictureModel->pictureModel()->setAlbumId(mAlbumModel->data(albumIndex, AlbumModel::Roles::IdRole).toInt());
    ui->albumName->setText(mAlbumModel->data(albumIndex, Qt::DisplayRole).toString());
    ui->deleteButton->setVisible(true);
    ui->editButton->setVisible(true);
    ui->addPicturesButton->setVisible(true);
}
