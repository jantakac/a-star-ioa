#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include "network.hpp"
#include "node.hpp"
#include "pathfinder.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    uint32_t from = ui->fromLineEdit->text().toUInt();
    uint32_t to = ui->toLineEdit->text().toUInt();
    ui->textOutput->appendPlainText("Loading files...");
    std::vector<Node> sr_network = Network::loadFromFile();

    if (!Network::isContinuous(sr_network)) {
        ui->textOutput->appendPlainText("The network is not continuous!");
    }

    ui->textOutput->appendPlainText("The network is continuous");

    // -- Dijkstra --
    uint_fast32_t visitedNodesCountD = 0u;
    auto startD = std::chrono::steady_clock::now();
    PathFinder::DistanceAndPath distanceAndPathD = PathFinder::dijkstraFindPath(sr_network,
                                                                                from,
                                                                                to,
                                                                                visitedNodesCountD);
    auto endD = std::chrono::steady_clock::now();
    ui->textOutput->appendPlainText(QString("distance: %1\npath:").arg(distanceAndPathD.first));
    for (auto &node : distanceAndPathD.second) {
        ui->textOutput->insertPlainText(QString("%1 <- ").arg(node));
    }
    ui->textOutput->appendPlainText("");
    // -- Dijkstra --

    // -- A* --
    uint_fast32_t visitedNodesCountA = 0u;
    auto startA = std::chrono::steady_clock::now();
    PathFinder::DistanceAndPath distanceAndPathA = PathFinder::aStarFindPath(sr_network,
                                                                             from,
                                                                             to,
                                                                             visitedNodesCountA);
    auto endA = std::chrono::steady_clock::now();

    ui->textOutput->appendPlainText(QString("distance: %1\npath:").arg(distanceAndPathA.first));
    for (auto &node : distanceAndPathA.second) {
        ui->textOutput->insertPlainText(QString("%1 <- ").arg(node));
    }
    ui->textOutput->appendPlainText("");
    // -- A* --

    auto diffD = std::chrono::duration_cast<std::chrono::microseconds>(endD - startD);
    auto diffA = std::chrono::duration_cast<std::chrono::microseconds>(endA - startA);
    ui->textOutput->appendPlainText("-----------------------");
    ui->textOutput->appendPlainText(
        QString("Dijkstra time taken: %1 microseconds").arg(diffD.count()));
    ui->textOutput->appendPlainText(QString("A* time taken: %1 microseconds").arg(diffA.count()));
    ui->textOutput->appendPlainText("-----------------------");
    ui->textOutput->appendPlainText(
        QString("Dijkstra visited nodes count: %1").arg(visitedNodesCountD));
    ui->textOutput->appendPlainText(QString("A* visited nodes count: %1").arg(visitedNodesCountA));
}
