#ifndef NODE_H
#define NODE_H

#include "edge.hpp"

#include <cstdint>
#include <string>
#include <vector>

class Node
{
public:
    Node(std::string name, uint32_t id, double lat, double lon);
    uint32_t id() const;
    void addNeighEdge(float length, uint32_t id, uint32_t from, uint32_t to);
    const std::vector<Edge>& neighEdges() const;
    float distance() const;
    uint32_t predecessor() const;
    float airDistance() const;

    void setDistance(float newDistance);

    void setPredecessor(uint32_t newPredecessor);

    bool marked() const;
    void setMarked(bool newMarked);

    void setAirDistance(float newAirDistance);

    double lat() const;

    double lon() const;

    float combinedDistance() const;

private:
    std::vector<Edge> m_neighEdges{};
    std::string m_name;
    uint32_t m_id;
    uint32_t m_predecessor;
    float m_distance;
    float m_airDistance;
    double m_lat;
    double m_lon;
    bool m_marked;
};

#endif // NODE_H
