#include "mainwindow.hpp"
#include "network.hpp"
#include "pathfinder.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    PathFinder::DistanceAndPath distanceAndPath
        = PathFinder::dijkstraFindPath(Network::loadFromFile(), 2, 9995);
    std::cout << "distance: " << distanceAndPath.first << "\n";
    std::cout << "path:\n";
    for (auto &node : distanceAndPath.second) {
        std::cout << node << " <- ";
    }
    std::cout << "\n";
    return 0;

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
