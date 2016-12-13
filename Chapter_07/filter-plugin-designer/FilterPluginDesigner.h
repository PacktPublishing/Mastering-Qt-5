#ifndef FILTERPLUGINDESIGNER_H
#define FILTERPLUGINDESIGNER_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

class  FilterPluginDesigner : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.masteringqt.imagefilter.FilterWidgetPluginInterface")
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    FilterPluginDesigner(QObject* parent = 0);

    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget* createWidget(QWidget* parent) override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface* core) override;

private:
    bool mInitialized;
};

#endif // FILTERPLUGINDESIGNER_H
