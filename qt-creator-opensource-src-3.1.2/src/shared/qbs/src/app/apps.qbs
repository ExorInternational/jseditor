import qbs

Project {
    references: [
        "config/config.qbs",
        "config-ui/config-ui.qbs",
        "qbs/qbs.qbs",
        "qbs-qmltypes/qbs-qmltypes.qbs",
        "qbs-setup-qt/qbs-setup-qt.qbs",
        "qbs-setup-toolchains/qbs-setup-toolchains.qbs",
    ]
}
