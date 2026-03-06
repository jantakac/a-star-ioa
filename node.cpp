#include "node.hpp"

Node::Node(std::string name, uint_fast32_t id, double lat, double lon)
    : m_name(std::move(name))
    , m_id(id)
    , m_lat(lat)
    , m_lon(lon)
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

const std::vector<Edge>& Node::neighEdges() const
{
    return m_neighEdges;
}

float Node::distance() const
{
    return m_distance;
}

uint32_t Node::predecessor() const
{
    return m_predecessor;
}

float Node::airDistance() const
{
    return m_airDistance;
}

void Node::setDistance(float newDistance)
{
    m_distance = newDistance;
}

void Node::setPredecessor(uint32_t newPredecessor)
{
    m_predecessor = newPredecessor;
}

bool Node::marked() const
{
    return m_marked;
}

void Node::setMarked(bool newMarked)
{
    m_marked = newMarked;
}

void Node::setAirDistance(float newAirDistance)
{
    m_airDistance = newAirDistance;
}

double Node::lat() const
{
    return m_lat;
}

double Node::lon() const
{
    return m_lon;
}

float Node::combinedDistance() const
{
    return m_distance + m_airDistance;
}
