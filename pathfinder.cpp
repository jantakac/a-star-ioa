#include "pathfinder.hpp"

PathFinder::DistanceAndPath PathFinder::dijkstraFindPath(const std::vector<Node> &network,
                                                         uint32_t from,
                                                         uint32_t to)
{
    std::vector<Node> currNetwork = network;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry> > prQueue;

    auto itSource = std::ranges::lower_bound(currNetwork, from, {}, &Node::id);
    if (itSource->id() != from) {
        std::cout << "FromNode is not in the network\n";
        return {-1.0f, {}};
    }

    auto itTarget = std::ranges::lower_bound(currNetwork, to, {}, &Node::id);
    if (itTarget->id() != to) {
        std::cout << "ToNode is not in the network\n";
        return {-1.0f, {}};
    }

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
    DistanceAndPath solution{0.0f, {}};
    if (foundPath) {
        solution.first = itTarget->distance();
        while (itTarget->distance() != 0.0f) {
            solution.second.emplace_back(itTarget->id());
            uint32_t lastPredecessor = itTarget->predecessor();
            itTarget = std::ranges::lower_bound(currNetwork, itTarget->predecessor(), {}, &Node::id);
            if (itTarget->id() != lastPredecessor)
                return {-1.0f, {}};
        }
        solution.second.emplace_back(itTarget->id());
        return solution;
    } else
        return {-1.0f, {}};
}
