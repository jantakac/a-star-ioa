#include "pathfinder.hpp"

PathFinder::DistanceAndPath PathFinder::dijkstraFindPath(const std::vector<Node> &network,
                                                         uint32_t from,
                                                         uint32_t to,
                                                         uint_fast32_t &visitedNodesCount)
{
    std::vector<Node> currNetwork = network;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry> > prQueue;

    auto [itSource, itTarget] = PathFinder::startEndIterators(currNetwork, from, to);
    if (itSource == itTarget)
        return {0.0f, {}};

    for (auto &node : currNetwork) {
        node.setMarked(false);
        node.setPredecessor(node.id());
        node.setDistance(std::numeric_limits<float>::max());
    }

    itSource->setDistance(0.0f);
    itSource->setPredecessor(itSource->id());
    prQueue.emplace(0, &(*itSource));

    QueueEntry currPtr;
    bool foundPath = false;
    while (!prQueue.empty()) {
        auto [distInPQ, nodePtr] = prQueue.top();
        prQueue.pop();

        if (distInPQ != nodePtr->distance())
            continue;
        ++visitedNodesCount;
        nodePtr->setMarked(true);
        if (nodePtr == &(*itTarget)) {
            foundPath = true;
            break;
        }

        for (auto &neighEdge : nodePtr->neighEdges()) {
            auto itPotentialNext = std::ranges::lower_bound(currNetwork,
                                                            neighEdge.to,
                                                            {},
                                                            &Node::id);
            float potentialNewDist = nodePtr->distance() + neighEdge.length;
            if (potentialNewDist < itPotentialNext->distance()) {
                itPotentialNext->setDistance(potentialNewDist);
                itPotentialNext->setPredecessor(nodePtr->id());
                prQueue.emplace(potentialNewDist, &(*itPotentialNext));
            }
        }
    }
    if (foundPath)
        return PathFinder::backtrackSolution(currNetwork, to);
    else
        return {-1.0f, {}};
}

PathFinder::DistanceAndPath PathFinder::aStarFindPath(const std::vector<Node> &network,
                                                      uint32_t from,
                                                      uint32_t to,
                                                      uint_fast32_t &visitedNodesCount)
{
    std::vector<Node> currNetwork = network;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry> > prQueue;

    auto [itSource, itTarget] = PathFinder::startEndIterators(currNetwork, from, to);
    if (itSource == itTarget)
        return {0.0f, {}};

    for (auto &node : currNetwork) {
        node.setMarked(false);
        node.setPredecessor(node.id());
        node.setDistance(std::numeric_limits<float>::max());
        node.setAirDistance(std::numeric_limits<float>::max());
    }

    itSource->setDistance(0.0f);
    itSource->setAirDistance(PathFinder::calcAirDistBetweenNodes(*itSource, *itTarget));
    itSource->setPredecessor(itSource->id());
    prQueue.emplace(itSource->combinedDistance(), &(*itSource));

    QueueEntry currPtr;
    bool foundPath = false;
    while (!prQueue.empty()) {
        auto [distInPQ, nodePtr] = prQueue.top();
        prQueue.pop();

        if (distInPQ != nodePtr->combinedDistance())
            continue;
        ++visitedNodesCount;
        nodePtr->setMarked(true);
        if (nodePtr == &(*itTarget)) {
            foundPath = true;
            break;
        }

        for (auto &neighEdge : nodePtr->neighEdges()) {
            auto itPotentialNext = std::ranges::lower_bound(currNetwork,
                                                            neighEdge.to,
                                                            {},
                                                            &Node::id);
            float potentialNewDist = nodePtr->distance() + neighEdge.length;
            if (itPotentialNext->airDistance() == std::numeric_limits<float>::max()) {
                itPotentialNext->setAirDistance(
                    PathFinder::calcAirDistBetweenNodes(*itPotentialNext, *itTarget));
            }
            float potentialNewCombinedDist = potentialNewDist + itPotentialNext->airDistance();
            if (potentialNewCombinedDist < itPotentialNext->combinedDistance()) {
                itPotentialNext->setDistance(potentialNewDist);
                itPotentialNext->setPredecessor(nodePtr->id());
                prQueue.emplace(potentialNewCombinedDist, &(*itPotentialNext));
            }
        }
    }

    if (foundPath)
        return PathFinder::backtrackSolution(currNetwork, to);
    else
        return {-1.0f, {}};
}

PathFinder::DistanceAndPath PathFinder::backtrackSolution(const std::vector<Node> &currNetwork,
                                                          uint32_t targetNodeId)
{
    auto itTarget = std::ranges::lower_bound(currNetwork, targetNodeId, {}, &Node::id);
    DistanceAndPath solution{0.0f, {}};
    solution.first = itTarget->distance();
    while (itTarget->distance() != 0.0f) {
        solution.second.emplace_back(itTarget->id());
        uint32_t lastPredecessor = itTarget->predecessor();
        itTarget = std::ranges::lower_bound(currNetwork, itTarget->predecessor(), {}, &Node::id);
        if (itTarget == currNetwork.end() || itTarget->id() != lastPredecessor)
            return {-1.0f, {}};
    }
    solution.second.emplace_back(itTarget->id());
    return solution;
}

float PathFinder::calcAirDistBetweenNodes(const Node &node1, const Node &node2)
{
    // equirectangular approximation
    constexpr double DEG_TO_RAD = M_PI / 180.0;
    constexpr double R = 6371.0;

    double dLat = (node2.lat() - node1.lat()) * DEG_TO_RAD;
    double dLon = (node2.lon() - node1.lon()) * DEG_TO_RAD;

    double avgLat = (node1.lat() + node2.lat()) * 0.5 * DEG_TO_RAD;

    double x = dLon * std::cos(avgLat);
    double y = dLat;

    return static_cast<float>(R * std::sqrt(x * x + y * y));
}

std::pair<PathFinder::NodeIterator, PathFinder::NodeIterator> PathFinder::startEndIterators(
    std::vector<Node> &network, uint32_t nodeFrom, uint32_t nodeTo)
{
    NodeIterator itSource = std::ranges::lower_bound(network, nodeFrom, {}, &Node::id);
    if (itSource == network.end() || itSource->id() != nodeFrom) {
        std::cout << "FromNode is not in the network\n";
        return {};
    }

    NodeIterator itTarget = std::ranges::lower_bound(network, nodeTo, {}, &Node::id);
    if (itTarget == network.end() || itTarget->id() != nodeTo) {
        std::cout << "ToNode is not in the network\n";
        return {};
    }
    return std::make_pair(itSource, itTarget);
}
