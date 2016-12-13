#include "FilterPluginDesigner.h"

#include "FilterWidget.h"

FilterPluginDesigner::FilterPluginDesigner(QObject* parent) :
    QObject(parent),
    mInitialized(false)
{
}

QString FilterPluginDesigner::name() const
{
    return "FilterWidget";
}

QString FilterPluginDesigner::group() const
{
    return "Mastering Qt5";
}

QString FilterPluginDesigner::toolTip() const
{
    return "A filtered picture";
}

QString FilterPluginDesigner::whatsThis() const
{
    return "The filter widget applies an image effect";
}

QString FilterPluginDesigner::includeFile() const
{
    return "FilterWidget.h";
}

QIcon FilterPluginDesigner::icon() const
{
    return QIcon(":/icon.jpg");
}

bool FilterPluginDesigner::isContainer() const
{
    return false;
}

QWidget* FilterPluginDesigner::createWidget(QWidget* parent)
{
    return new FilterWidget(parent);
}

bool FilterPluginDesigner::isInitialized() const
{
    return mInitialized;
}

void FilterPluginDesigner::initialize(QDesignerFormEditorInterface* /*core*/)
{
    if (mInitialized)
        return;

    mInitialized = true;
}
