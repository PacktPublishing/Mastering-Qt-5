#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QVector>
#include <QThread>
#include <QTimer>

#include "Track.h"
#include "Serializer.h"

class SoundEffectWidget;
class PlaybackWorker;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject* watched, QEvent* event) override;
    void initSoundEffectWidgets();

private slots:
    void playSoundEffect(int soundId);
    void clearPlayback();
    void stopPlayback();

    void saveProject();
    void loadProject();

private:
    void updateState(const Track::State& state);
    void startDisplayTimer();
    void updateDisplayTime();
    void stopDisplayTimer();
    void startPlayback();

    QString formatTime(long ms);

private:
    Ui::MainWindow *ui;
    Track mTrack;
    QVector<SoundEffectWidget*> mSoundEffectWidgets;
    PlaybackWorker* mPlaybackWorker;
    QThread* mPlaybackThread;
    QTimer mDisplayTimer;
    std::unique_ptr<Serializer> mSerializer;
};

#endif // MAINWINDOW_H
