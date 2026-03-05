#ifndef EDGE_H
#define EDGE_H

#include <cstdint>
typedef struct {
    float length;
    uint32_t id;
    uint32_t from;
    uint32_t to;
} Edge;

#endif // EDGE_H
