#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "node.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <queue>

namespace PathFinder {
using DistanceAndPath = std::pair<float, std::vector<uint32_t>>;
using QueueEntry = std::pair<float, Node *>;
using NodeIterator = std::ranges::borrowed_iterator_t<std::vector<Node, std::allocator<Node>> &>;
[[nodiscard]] DistanceAndPath dijkstraFindPath(const std::vector<Node> &network,
                                               uint32_t from,
                                               uint32_t to,
                                               uint_fast32_t &visitedNodesCount);
[[nodiscard]] DistanceAndPath aStarFindPath(const std::vector<Node> &network,
                                            uint32_t from,
                                            uint32_t to,
                                            uint_fast32_t &visitedNodesCount);
[[nodiscard]] DistanceAndPath backtrackSolution(const std::vector<Node> &currNetwork,
                                                uint32_t targetNodeId);
[[nodiscard]] float calcAirDistBetweenNodes(const Node &node1, const Node &node2);
[[nodiscard]] float calcHaversineDist(double lat1, double lon1, double lat2, double lon2);
[[nodiscard]] std::pair<PathFinder::NodeIterator, PathFinder::NodeIterator> startEndIterators(
    std::vector<Node> &network, uint32_t nodeFrom, uint32_t nodeTo);
}; // namespace PathFinder

#endif // PATHFINDER_H
