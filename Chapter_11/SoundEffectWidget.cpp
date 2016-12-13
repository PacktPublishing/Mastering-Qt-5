#include "SoundEffectWidget.h"

#include <QVBoxLayout>
#include <QDropEvent>
#include <QMimeData>
#include <QMimeDatabase>

SoundEffectWidget::SoundEffectWidget(QWidget* parent) :
    QWidget(parent),
    mId(-1),
    mSoundEffect(this),
    mPlayButton(new QPushButton()),
    mFilenameLabel(new QLabel()),
    mTriggerKey(Qt::Key_unknown)
{
    setAcceptDrops(true);
    mSoundEffect.setVolume(1.0f);

    mPlayButton->setSizePolicy(QSizePolicy::MinimumExpanding,
                               QSizePolicy::MinimumExpanding);
    QFont font = mPlayButton->font();
    font.setPointSize(15);
    mPlayButton->setFont(font);

    mFilenameLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(mPlayButton);
    layout->addWidget(mFilenameLabel);

    setLayout(layout);

    connect(mPlayButton, &QPushButton::clicked,
            this, &SoundEffectWidget::play);
}

void SoundEffectWidget::loadSound(const QUrl& url)
{
    mSoundEffect.setSource(url);
    mFilenameLabel->setText(url.fileName());
}

void SoundEffectWidget::play()
{
    mSoundEffect.play();
    emit soundPlayed(mId);
}

void SoundEffectWidget::triggerPlayButton()
{
   mPlayButton->animateClick();
}

void SoundEffectWidget::setId(int id)
{
    mId = id;
}

void SoundEffectWidget::setName(const QString& name)
{
    mPlayButton->setText(name);
}

void SoundEffectWidget::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void SoundEffectWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();
    if (!mimeData->hasUrls()) {
        return;
    }
    const QUrl url = mimeData->urls().first();
    QMimeType mime = QMimeDatabase().mimeTypeForUrl(url);
    if (mime.inherits("audio/wav")) {
        loadSound(url);
    }
}

Qt::Key SoundEffectWidget::triggerKey() const
{
    return mTriggerKey;
}

void SoundEffectWidget::setTriggerKey(const Qt::Key& triggerKey)
{
    mTriggerKey = triggerKey;
}
