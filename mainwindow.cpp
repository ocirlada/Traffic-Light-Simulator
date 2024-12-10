#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentLight(0) // Initialize with the North-South green light
{
    ui->setupUi(this);

    // Initialize timer
    trafficTimer = new QTimer(this);
    connect(trafficTimer, &QTimer::timeout, this, &MainWindow::changeLight);

    // Connect buttons to their slots
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->pedestrianButton, &QPushButton::clicked, this, &MainWindow::pedestrianRequest);}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startSimulation()
{
    ui->statusLabel->setText("Status: Simulation Running");
    currentLight = 0; // Start with North-South direction
    trafficTimer->start(3000); // Timer interval for light cycling
    changeLight(); // Start the first light transition
}


void MainWindow::stopSimulation()
{
    ui->statusLabel->setText("Status: Simulation Stopped");
    trafficTimer->stop();
}




void MainWindow::changeLight()
{
    // Define styles
    const QString offStyle = "background-color: black; border-radius: 15px;";
    const QString redStyle = "background-color: red; border-radius: 15px;";
    const QString greenStyle = "background-color: green; border-radius: 15px;";
    const QString yellowStyle = "background-color: yellow; border-radius: 15px;";

    // Reset all lights to red/off
    ui->northRedLight->setStyleSheet(redStyle);
    ui->northYellowLight->setStyleSheet(offStyle);
    ui->northGreenLight->setStyleSheet(offStyle);

    ui->southRedLight->setStyleSheet(redStyle);
    ui->southYellowLight->setStyleSheet(offStyle);
    ui->southGreenLight->setStyleSheet(offStyle);

    ui->eastRedLight->setStyleSheet(redStyle);
    ui->eastYellowLight->setStyleSheet(offStyle);
    ui->eastGreenLight->setStyleSheet(offStyle);

    ui->westRedLight->setStyleSheet(redStyle);
    ui->westYellowLight->setStyleSheet(offStyle);
    ui->westGreenLight->setStyleSheet(offStyle);

    // Change light based on current direction
    switch (currentLight) {
    case 0: // North-South green
        ui->northRedLight->setStyleSheet(offStyle);
        ui->southRedLight->setStyleSheet(offStyle);
        ui->northGreenLight->setStyleSheet(greenStyle);
        ui->southGreenLight->setStyleSheet(greenStyle);
        break;

    case 1: // East-West green
        ui->eastRedLight->setStyleSheet(offStyle);
        ui->westRedLight->setStyleSheet(offStyle);
        ui->eastGreenLight->setStyleSheet(greenStyle);
        ui->westGreenLight->setStyleSheet(greenStyle);
        break;

    default:
        break;
    }

    // Schedule the yellow light after 2 seconds
    QTimer::singleShot(2000, [this, yellowStyle, offStyle]() {
        if (currentLight == 0) {
            ui->northGreenLight->setStyleSheet(offStyle);
            ui->southGreenLight->setStyleSheet(offStyle);
            ui->northYellowLight->setStyleSheet(yellowStyle);
            ui->southYellowLight->setStyleSheet(yellowStyle);
        } else if (currentLight == 1) {
            ui->eastGreenLight->setStyleSheet(offStyle);
            ui->westGreenLight->setStyleSheet(offStyle);
            ui->eastYellowLight->setStyleSheet(yellowStyle);
            ui->westYellowLight->setStyleSheet(yellowStyle);
        }
    });

    // Transition to red and move to the next state after 3 seconds
    QTimer::singleShot(3000, [this, redStyle]() {
        if (currentLight == 0) {
            ui->northYellowLight->setStyleSheet("background-color: black; border-radius: 15px;");
            ui->southYellowLight->setStyleSheet("background-color: black; border-radius: 15px;");
            ui->northRedLight->setStyleSheet(redStyle);
            ui->southRedLight->setStyleSheet(redStyle);
        } else if (currentLight == 1) {
            ui->eastYellowLight->setStyleSheet("background-color: black; border-radius: 15px;");
            ui->westYellowLight->setStyleSheet("background-color: black; border-radius: 15px;");
            ui->eastRedLight->setStyleSheet(redStyle);
            ui->westRedLight->setStyleSheet(redStyle);
        }

        // Move to the next state
        currentLight = (currentLight + 1) % 2; // 0 → 1 → 0 (cycling between states)
    });
}



void MainWindow::pedestrianRequest()
{
    // Stop the traffic timer
    trafficTimer->stop();

    // Turn all vehicle lights red
    ui->northRedLight->setStyleSheet("background-color: red;");
    ui->southRedLight->setStyleSheet("background-color: red;");
    ui->eastRedLight->setStyleSheet("background-color: red;");
    ui->westRedLight->setStyleSheet("background-color: red;");

    // Confirmation to turn all lights red
    ui->northGreenLight->setStyleSheet("background-color: black;");
    ui->southGreenLight->setStyleSheet("background-color: black;");
    ui->eastGreenLight->setStyleSheet("background-color: black;");
    ui->westGreenLight->setStyleSheet("background-color: black;");

    ui->northYellowLight->setStyleSheet("background-color: black;");
    ui->southYellowLight->setStyleSheet("background-color: black;");
    ui->eastYellowLight->setStyleSheet("background-color: black;");
    ui->westYellowLight->setStyleSheet("background-color: black;");

    // Turn on pedestrian lights
    ui->northPedestrianLight->setStyleSheet("background-color: green;");
    ui->southPedestrianLight->setStyleSheet("background-color: green;");
    ui->eastPedestrianLight->setStyleSheet("background-color: green;");
    ui->westPedestrianLight->setStyleSheet("background-color: green;");

    // Resume normal operation after 5 seconds
    QTimer::singleShot(5000, [this]() {
        ui->northPedestrianLight->setStyleSheet("background-color: black;");
        ui->southPedestrianLight->setStyleSheet("background-color: black;");
        ui->eastPedestrianLight->setStyleSheet("background-color: black;");
        ui->westPedestrianLight->setStyleSheet("background-color: black;");
        trafficTimer->start(3000);
    });
}

void MainWindow::on_pseudoButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Algorithm's Descripton");
    msgBox.setText("The program's algorithm is:");
    msgBox.setInformativeText("1. Initialize Lights: All lights are turned red at the start. \n"
                              "2. Cycle Directions: \n"
                              "         -> Lights transition in the order North & South → East & West. \n"
                              "3. For Each Direction:\n"
                              "         -> The green light is active for 3 seconds. \n"
                              "         -> Then, it transitions to yellow for 1 second. \n"
                              "         -> Finally, the light turns red, and the cycle moves to the next direction.\n"
                              "4. Repeat: Once the directions are complete, the cycle restarts.\n"
                              "5. Project Report: Takes you to the project report.");
    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();
}

void MainWindow::on_openReport_clicked()
{
    // URL of the Google Docs project report
    const QString reportUrl = "https://shorturl.at/JSNlV";
    QDesktopServices::openUrl(QUrl(reportUrl));
}

