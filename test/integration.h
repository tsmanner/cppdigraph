#ifndef TEST_H
#define TEST_H

// STL
#include <string>

// CDG
#include "digraph.h"
#include "edge.h"
#include "node.h"
#include "relationship.h"

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
  MyNode(DiGraph* digraph, string name);
  MyNode(string name);
  virtual ~MyNode() {}

  // template <typename tail_t, typename head_t>
  // void disconnect(Edge<tail_t, head_t>* edge);
private:

};


/*
 * MyEdge
 */
template <typename tail_t, typename head_t>
class MyEdge: public Edge<tail_t, head_t> {
public:
  MyEdge(tail_t* tail, head_t* head): Edge<tail_t, head_t>(tail, head) {
    // tail->connect(this);
    // head->connect(this);
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
class NodeA:
    public MyNode
  , public Relationship<NodeA, NodeA>
  , public Relationship<NodeA, NodeB>
  , public Relationship<NodeB, NodeA>
{
public:
  NodeA(DiGraph* digraph, string name);
  NodeA(string name);
  virtual ~NodeA() {}

  void traverseB();

private:

};


/*
 * NodeB
 */
class NodeB:
    public MyNode
  , public Relationship<NodeB, NodeB>
  , public Relationship<NodeA, NodeB>
  , public Relationship<NodeB, NodeA>
{
public:
  NodeB(DiGraph* digraph, string name);
  NodeB(string name);
  virtual ~NodeB() {}

  void traverseB();

private:

};


#endif
