/*
 *
 */

#include "node.h"
#include "edge.h"


// +----+         +----+
// | a0 |--a0a1-->| a1 |
// +----+         +----+
//  |  ^
//  a  |
//  0  b
//  b  0
//  0  a
//  |  b
//  V  |
// +----+         +----+
// | b0 |--b0b1-->| b1 |
// +----+         +----+


class NodeA: public cdg::Node {
};


class NodeB: public cdg::Node {
};


// EDGE(EdgeAA, NodeA, NodeA);
// EDGE(EdgeAB, NodeA, NodeB);
// EDGE(EdgeBA, NodeB, NodeA);
// EDGE(EdgeBB, NodeB, NodeB);

int main() {
  NodeA a0 = NodeA();
  NodeA a1 = NodeA();
  NodeB b0 = NodeB();
  NodeB b1 = NodeB();

//   EdgeAA a0a1 = EdgeAA(a0, a1);
//   EdgeAB a0b0 = EdgeAB(a0, b0);
//   EdgeBA b0a0 = EdgeBA(b0, a0);
//   EdgeBB b0b1 = EdgeBB(b0, b1);

//   a0.getThingOne();
//   a0.getThingTwo();

  cdg::Edge<NodeA, NodeB> eAB(a0, b0);
}
