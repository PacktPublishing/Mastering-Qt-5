#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "SoundEffectWidget.h"
#include "PlaybackWorker.h"
#include "JsonSerializer.h"
#include "XmlSerializer.h"
#include "BinarySerializer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mTrack(),
    mSoundEffectWidgets(),
    mPlaybackWorker(nullptr),
    mPlaybackThread(nullptr),
    mSerializer(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Drum Machine");
    installEventFilter(this);
    initSoundEffectWidgets();

    mSerializer = std::make_unique<JsonSerializer>();

    connect(ui->playButton, &QPushButton::clicked,
            &mTrack, &Track::play);

    connect(ui->recordButton, &QPushButton::clicked,
            &mTrack, &Track::record);

    connect(ui->stopButton, &QPushButton::clicked,
            &mTrack, &Track::stop);

    connect(ui->saveProjectAsAction, &QAction::triggered,
            this, &MainWindow::saveProject);

    connect(ui->loadProjectAction, &QAction::triggered,
            this, &MainWindow::loadProject);

    connect(ui->exitAction, &QAction::triggered,
            this, &MainWindow::close);

    connect(&mTrack, &Track::stateChanged,
            this, &MainWindow::updateState);

    connect(&mDisplayTimer, &QTimer::timeout,
            this, &MainWindow::updateDisplayTime);

    mTrack.stop();
}

MainWindow::~MainWindow()
{
    delete ui;
    clearPlayback();
}

void MainWindow::initSoundEffectWidgets()
{
    mSoundEffectWidgets.append(ui->kickWidget);
    mSoundEffectWidgets.append(ui->snareWidget);
    mSoundEffectWidgets.append(ui->hihatWidget);
    mSoundEffectWidgets.append(ui->crashWidget);

    for (int i = 0; i < 4; ++i) {
        SoundEffectWidget* widget = mSoundEffectWidgets[i];
        widget->setId(i);
        connect(widget, &SoundEffectWidget::soundPlayed,
                &mTrack, &Track::addSoundEvent);
    }

    ui->kickWidget->setName("Kick");
    ui->kickWidget->setTriggerKey(Qt::Key_H);
    ui->kickWidget->loadSound(QUrl("qrc:/sounds/kick.wav"));

    ui->snareWidget->setName("Snare");
    ui->snareWidget->setTriggerKey(Qt::Key_J);
    ui->snareWidget->loadSound(QUrl("qrc:/sounds/snare.wav"));

    ui->hihatWidget->setName("Hihat");
    ui->hihatWidget->setTriggerKey(Qt::Key_K);
    ui->hihatWidget->loadSound(QUrl("qrc:/sounds/hihat.wav"));

    ui->crashWidget->setName("Crash");
    ui->crashWidget->setTriggerKey(Qt::Key_L);
    ui->crashWidget->loadSound(QUrl("qrc:/sounds/crash.wav"));
}

void MainWindow::playSoundEffect(int soundId)
{
   mSoundEffectWidgets[soundId]->triggerPlayButton();
}

void MainWindow::updateState(const Track::State& state)
{
    bool playEnabled = false;
    bool recordEnabled = false;
    bool stopEnabled = false;
    QString statusText = "";

    switch (state) {
        case Track::State::STOPPED:
            playEnabled = true;
            recordEnabled = true;
            stopEnabled = false;
            statusText = "";

            if (mTrack.previousState() == Track::State::PLAYING) {
                stopPlayback();
            }
            stopDisplayTimer();
            break;

        case Track::State::PLAYING:
            playEnabled = false;
            recordEnabled = false;
            stopEnabled = true;
            statusText = "Playing...";
            startDisplayTimer();
            startPlayback();

            break;
        case Track::State::RECORDING:
            playEnabled = false;
            recordEnabled = false;
            stopEnabled = true;
            statusText = "Recording...";
            startDisplayTimer();
            break;
        default:
            break;
    }

    ui->playButton->setEnabled(playEnabled);
    ui->recordButton->setEnabled(recordEnabled);
    ui->stopButton->setEnabled(stopEnabled);
    ui->statusBar->showMessage(statusText);
}

void MainWindow::startDisplayTimer()
{
    mDisplayTimer.start(1000);
}

void MainWindow::updateDisplayTime()
{
    QString elapsedTimeFormated = formatTime(mTrack.elapsedTime());
    ui->currentTimeLabel->setText(elapsedTimeFormated);

    if (mTrack.state() == Track::State::RECORDING) {
        ui->totalTimeLabel->setText(elapsedTimeFormated);
    }
}

void MainWindow::stopDisplayTimer()
{
    mDisplayTimer.stop();
    ui->currentTimeLabel->setText(formatTime(0));
    ui->totalTimeLabel->setText(formatTime(mTrack.duration()));
}

void MainWindow::startPlayback()
{
    clearPlayback();

    mPlaybackThread = new QThread();

    mPlaybackWorker = new PlaybackWorker(mTrack);
    mPlaybackWorker->moveToThread(mPlaybackThread);

    connect(mPlaybackThread, &QThread::started,
            mPlaybackWorker, &PlaybackWorker::play);
    connect(mPlaybackThread, &QThread::finished,
            mPlaybackWorker, &QObject::deleteLater);

    connect(mPlaybackWorker, &PlaybackWorker::playSound,
            this, &MainWindow::playSoundEffect);

    connect(mPlaybackWorker, &PlaybackWorker::trackFinished,
            &mTrack, &Track::stop);

    mPlaybackThread->start(QThread::HighPriority);
}

QString MainWindow::formatTime(long ms)
{
   int seconds = ms / 1000;
   int minutes = (seconds / 60) % 60;
   seconds = seconds % 60;
   return QString()
           .sprintf("%02d:%02d", minutes, seconds);
}

void MainWindow::stopPlayback()
{
    mPlaybackWorker->stop();
    clearPlayback();
}

void MainWindow::saveProject()
{
    QString filename = QFileDialog::getSaveFileName(
                                 this,
                                 "Save Drum Machine project",
                                 QDir::homePath(),
                                 "Drum Projects (*.dp)");
    if (filename.isEmpty()) {
        return;
    }

    mSerializer->save(mTrack, filename, "track");
    ui->statusBar->showMessage("Project saved to " + filename);
}

void MainWindow::loadProject()
{
   QString filename = QFileDialog::getOpenFileName(this,
                                "Load Drum Machine project",
                                QDir::homePath(),
                                 "Drum Projects (*.dp)");

    if (filename.isEmpty()) {
        return;
    }
    mSerializer->load(mTrack, filename);
    ui->statusBar->showMessage("Project loaded from " + filename);
    mTrack.stop();
}

void MainWindow::clearPlayback()
{
    if (mPlaybackThread) {
        mPlaybackThread->quit();
        mPlaybackThread->wait(1000);
        mPlaybackThread = nullptr;
        mPlaybackWorker = nullptr;
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        for(SoundEffectWidget* widget : mSoundEffectWidgets) {
            if (keyEvent->key() == widget->triggerKey()) {
                widget->triggerPlayButton();
                return true;
            }
        }
    }
    return QObject::eventFilter(watched, event);
}
