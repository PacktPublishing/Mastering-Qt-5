INCLUDEPATH += $$PWD/sdk
DEPENDPATH += $$PWD/sdk

windows {
    CONFIG(debug, debug|release) {
        target_install_path = $$OUT_PWD/../image-animation/debug/plugins/
    } else {
        target_install_path = $$OUT_PWD/../image-animation/release/plugins/
    }

} else {
    target_install_path = $$OUT_PWD/../image-animation/plugins/
}

# Check Qt file 'spec_post.prf' for more information about '$$QMAKE_MKDIR_CMD'
createPluginsDir.path = $$target_install_path
createPluginsDir.commands = $$QMAKE_MKDIR_CMD $$createPluginsDir.path
INSTALLS += createPluginsDir

target.path = $$target_install_path
INSTALLS += target
