#include "network.hpp"


std::vector<Node> Network::loadFromFile()
{
    std::vector<Node> network = loadFromFileNodesOnly();
    // they're the same length
    std::ifstream incidFile("sr_test/SR_edges_incid.txt");
    std::ifstream lengthFile("sr_test/SR_edges.atr");
    uint32_t id;
    uint32_t from;
    uint32_t to;
    float length;
    while (incidFile >> id >> from >> to && lengthFile >> id >> length) {
        auto it = std::ranges::lower_bound(network, id, {}, &Node::id);
        it->addNeighEdge(length, id, from, to);
    }
    return network;
}

std::vector<Node> Network::loadFromFileNodesOnly()
{
    std::vector<Node> network{};
    std::ifstream posFile("sr_test/SR_nodes.vec");
    uint32_t id;
    char throwAway;
    double x;
    double y;
    while (posFile >> id >> throwAway >> x >> y) {
        network.emplace_back("", id, x, y);
    }
    return network;
}
