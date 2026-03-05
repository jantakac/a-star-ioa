#include "node.hpp"

Node::Node(std::string name, uint_fast32_t id, double x, double y)
    : m_name(std::move(name)), m_id(id), m_x(x), m_y(y)
{
}

uint32_t Node::id() const
{
    return m_id;
}

void Node::addNeighEdge(float length, uint32_t id, uint32_t from, uint32_t to)
{
    m_neighEdges.emplace_back(length, id, from, to);
}
