#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "node.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

namespace PathFinder {
using DistanceAndPath = std::pair<float, std::vector<uint32_t>>;
using QueueEntry = std::pair<float, Node *>;
[[nodiscard]] DistanceAndPath dijkstraFindPath(const std::vector<Node> &network,
                                               uint32_t from,
                                               uint32_t to);
[[nodiscard]] DistanceAndPath aStarFindPath(const std::vector<Node> &network,
                                            uint32_t from,
                                            uint32_t to);
}; // namespace PathFinder

#endif // PATHFINDER_H
