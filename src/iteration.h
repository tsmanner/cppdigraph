/*
 * iteration.h
 */

#ifndef CDG_ITERATION_H
#define CDG_ITERATION_H


#include <functional>
#include <list>


namespace cdg {


template <typename NodeType>
std::list<NodeType*> traverse(std::function<NodeType*(NodeType*)> iterationFunction, NodeType* start) {
  std::list<NodeType*> nodes;
  NodeType* node = start;
  while (node) {
    nodes.push_back(node);
    node = iterationFunction(node);
  }
  return nodes;
}


}


#endif
