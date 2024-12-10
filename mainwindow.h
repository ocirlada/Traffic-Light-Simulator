#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSimulation();   // Start the traffic light simulation
    void stopSimulation();    // Stop the traffic light simulation
    void pedestrianRequest(); // Handle pedestrian crossing request
    void changeLight();       // Change traffic lights in sequence

    void on_pseudoButton_clicked();

    void on_openReport_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *trafficTimer;     // Timer for cycling through traffic lights
    int currentLight;         // Tracks the current active light
};

#endif // MAINWINDOW_H
