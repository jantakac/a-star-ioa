#ifndef NETWORK_H
#define NETWORK_H

#include "node.hpp"

#include <fstream>
#include <algorithm>

namespace Network {
    std::vector<Node> loadFromFile();
    std::vector<Node> loadFromFileNodesOnly();
    bool isContinuous(const std::vector<Node> &network);
}

#endif // NETWORK_H
