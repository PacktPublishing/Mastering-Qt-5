#include "FilterLoader.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>

FilterLoader::FilterLoader() :
    mFilters()
{
}

void FilterLoader::loadFilters()
{
    QDir pluginsDir(QApplication::applicationDirPath());
#ifdef Q_OS_MAC
    pluginsDir.cdUp();
    pluginsDir.cdUp();
    pluginsDir.cdUp();
#endif
    pluginsDir.cd("plugins");

    for(QString fileName: pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject* plugin = pluginLoader.instance();
        if (plugin) {
            mFilters.push_back(std::unique_ptr<Filter>(qobject_cast<Filter*>(plugin)));
        }
    }
}

const std::vector<std::unique_ptr<Filter> >& FilterLoader::filters() const
{
    return mFilters;
}
