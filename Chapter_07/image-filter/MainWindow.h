#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QVector>

namespace Ui {
class MainWindow;
}

class FilterWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void loadPicture();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void displayPicture(const QImage& picture);
    void saveAsPicture();

private:
    void initFilters();
    void updatePicturePixmap();

private:
    Ui::MainWindow *ui;
    QImage mSourcePicture;
    QImage mSourceThumbnail;
    QImage& mFilteredPicture;
    QPixmap mCurrentPixmap;
    FilterWidget* mCurrentFilter;
    QVector<FilterWidget*> mFilters;
};

#endif // MAINWINDOW_H
