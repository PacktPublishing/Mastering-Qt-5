#ifndef SOUNDEFFECTWIDGET_H
#define SOUNDEFFECTWIDGET_H

#include <QWidget>
#include <QSoundEffect>
#include <QPushButton>
#include <QLabel>

class SoundEffectWidget : public QWidget
{
    Q_OBJECT
public:
    SoundEffectWidget(QWidget* parent = 0);

    void loadSound(const QUrl& url);

    void setId(int id);
    void setName(const QString& name);
    Qt::Key triggerKey() const;
    void setTriggerKey(const Qt::Key& triggerKey);
signals:
    void soundPlayed(int soundId);

public slots:
    void play();
    void triggerPlayButton();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    int mId;
    QSoundEffect mSoundEffect;
    QPushButton* mPlayButton;
    QLabel* mFilenameLabel;
    Qt::Key mTriggerKey;
};

#endif // SOUNDEFFECTWIDGET_H
