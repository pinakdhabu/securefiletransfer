// This is a minimal generated UI header for MainWindow.ui
#pragma once
#include <QtWidgets>

namespace Ui {
class MainWindow {
public:
    QWidget *centralwidget = nullptr;
    QComboBox *modeCombo = nullptr;
    QStackedWidget *stackedWidget = nullptr;
    void setupUi(QMainWindow *MainWindow) {
        MainWindow->setObjectName("MainWindow");
        centralwidget = new QWidget(MainWindow);
        QVBoxLayout *verticalLayout = new QVBoxLayout(centralwidget);
        QHBoxLayout *topLayout = new QHBoxLayout();
        QLabel *modeLabel = new QLabel("Mode:", centralwidget);
        modeCombo = new QComboBox(centralwidget);
        modeCombo->addItems({"Client","Server"});
        topLayout->addWidget(modeLabel);
        topLayout->addWidget(modeCombo);
        verticalLayout->addLayout(topLayout);
        stackedWidget = new QStackedWidget(centralwidget);
        verticalLayout->addWidget(stackedWidget);
        MainWindow->setCentralWidget(centralwidget);
    }
};
}
