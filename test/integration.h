#ifndef TEST_H
#define TEST_H

// STL
#include <iostream>
#include <string>

// CDG
#include "node.h"
#include "edge.h"

// Namespaces
using namespace cdg;
using namespace std;

// Forward Declarations
class NodeA;
class NodeB;


/*
 * MyNode
 */
class MyNode: public Node {
public:
  MyNode(string name);

  template <typename tail_t, typename head_t>
  void disconnect(Edge<tail_t, head_t>* edge);
};


/*
 * MyEdge
 */
template <typename tail_t, typename head_t>
class MyEdge: public Edge<tail_t, head_t> {
public:
  MyEdge(tail_t* tail, head_t* head): Edge<tail_t, head_t>(tail, head) {
    tail->connect(this);
    head->connect(this);
  }
  virtual ~MyEdge() {
    disconnect(Edge<tail_t, head_t>::getTail());
    disconnect(Edge<tail_t, head_t>::getHead());
  }

  virtual void disconnect(MyNode* node) {
    if (node) {
      if (node == Edge<tail_t, head_t>::getTail()) {
        Edge<tail_t, head_t>::getTail()->disconnect(this);
      }
      if (node == Edge<tail_t, head_t>::getHead()) {
        Edge<tail_t, head_t>::getHead()->disconnect(this);
      }
      Edge<tail_t, head_t>::disconnect(node);
    }
  }

};


/*
 * NodeA
 */
class NodeA: public MyNode {
public:
  NodeA(string name);

  // A->B Edges;
  void connect(Edge<NodeA, NodeB>* edge);
  void disconnect(Edge<NodeA, NodeB>* edge);
  // B->A Edges;
  void connect(Edge<NodeB, NodeA>* edge);
  void disconnect(Edge<NodeB, NodeA>* edge);
  // A->A Edges;
  void connect(Edge<NodeA, NodeA>* edge);
  void disconnect(Edge<NodeA, NodeA>* edge);

  void traverseB();

private:
  // A->B Edges;
  Edge<NodeA, NodeB>* mOutgoingB;
  // B->A Edges;
  Edge<NodeB, NodeA>* mIncomingB;
  // A->A Edges;
  Edge<NodeA, NodeA>* mOutgoingA;
  Edge<NodeA, NodeA>* mIncomingA;

};


/*
 * NodeB
 */
class NodeB: public MyNode {
public:
  NodeB(string name);

  // A->B Edges
  void connect(Edge<NodeA, NodeB>* edge);
  void disconnect(Edge<NodeA, NodeB>* edge);
  // B->A Edges
  void connect(Edge<NodeB, NodeA>* edge);
  void disconnect(Edge<NodeB, NodeA>* edge);
  // B->B Edges
  void connect(Edge<NodeB, NodeB>* edge);
  void disconnect(Edge<NodeB, NodeB>* edge);

  void traverseB();

private:
  // A->B Edges
  Edge<NodeA, NodeB>* mIncomingA;
  // B->A Edges
  Edge<NodeB, NodeA>* mOutgoingA;
  // B->B Edges
  Edge<NodeB, NodeB>* mOutgoingB;
  Edge<NodeB, NodeB>* mIncomingB;

};


#endif
