#include "mainwindow.hpp"
#include "network.hpp"
#include "pathfinder.hpp"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<Node> sr_network = Network::loadFromFile();

    if (!Network::isContinuous(sr_network)) {
        std::cout << "The network is not continuous!\n";
        return 0;
    }

    std::cout << "The network is continuous\n";

    // -- Dijkstra --
    uint_fast32_t visitedNodesCountD = 0u;
    auto startD = std::chrono::steady_clock::now();
    PathFinder::DistanceAndPath distanceAndPathD = PathFinder::dijkstraFindPath(sr_network,
                                                                                1,
                                                                                9995,
                                                                                visitedNodesCountD);
    auto endD = std::chrono::steady_clock::now();

    std::cout << "distance: " << distanceAndPathD.first << "\n";
    std::cout << "path:\n";
    for (auto &node : distanceAndPathD.second) {
        std::cout << node << " <- ";
    }
    std::cout << "\n";
    // -- Dijkstra --

    // -- A* --
    uint_fast32_t visitedNodesCountA = 0u;
    auto startA = std::chrono::steady_clock::now();
    PathFinder::DistanceAndPath distanceAndPathA = PathFinder::aStarFindPath(sr_network,
                                                                             1,
                                                                             9995,
                                                                             visitedNodesCountA);
    auto endA = std::chrono::steady_clock::now();

    std::cout << "distance: " << distanceAndPathA.first << "\n";
    std::cout << "path:\n";
    for (auto &node : distanceAndPathA.second) {
        std::cout << node << " <- ";
    }
    std::cout << "\n";
    // -- A* --

    auto diffD = std::chrono::duration_cast<std::chrono::microseconds>(endD - startD);
    auto diffA = std::chrono::duration_cast<std::chrono::microseconds>(endA - startA);
    std::cout << "-----------------------\n";
    std::cout << "Dijkstra time taken: " << diffD.count() << " microseconds\n";
    std::cout << "A* time taken: " << diffA.count() << " microseconds\n";
    std::cout << "-----------------------\n";
    std::cout << "Dijkstra visited nodes count: " << visitedNodesCountD << "\n";
    std::cout << "A* visited nodes count: " << visitedNodesCountA << "\n";

    return 0;

    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
}
