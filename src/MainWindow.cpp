#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ClientWidget.h"
#include "ServerWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Create widgets
    ClientWidget *client = new ClientWidget(this);
    ServerWidget *server = new ServerWidget(this);
    ui->stackedWidget->addWidget(client);
    ui->stackedWidget->addWidget(server);
    connect(ui->modeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onModeChanged);
    ui->modeCombo->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onModeChanged(int index) {
    ui->stackedWidget->setCurrentIndex(index);
}
