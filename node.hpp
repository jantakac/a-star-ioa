#ifndef NODE_H
#define NODE_H

#include "edge.hpp"

#include <cstdint>
#include <string>
#include <vector>

class Node
{
public:
    Node(std::string name, uint32_t id, double x, double y);
    uint32_t id() const;
    void addNeighEdge(float length, uint32_t id, uint32_t from, uint32_t to);
private:
    std::vector<Edge> m_neighEdges{};
    std::string m_name;
    uint32_t m_id;
    double m_x;
    double m_y;
};

#endif // NODE_H
