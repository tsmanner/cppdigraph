/*
 * Some library agnostic eyeball integration testing.
 */


#include "integration.h"

#include <iostream>
#include <iomanip>


/*
 * Stream operators
 */
ostream& operator<<(ostream& os, Node node) {
  return node.operator<<(os);
}


template <typename tail_t, typename head_t>
ostream& operator<<(ostream& os, Edge<tail_t, head_t> edge) {
  return edge.Edge<tail_t, head_t>::operator<<(os);
}


/*
 * MyNode
 */
MyNode::MyNode(DiGraph* digraph, string name): Node(digraph, name) {
}

MyNode::MyNode(string name): Node(name) {
}


/*
 * NodeA
 */
NodeA::NodeA(DiGraph* digraph
           , string name
          ): MyNode(digraph, name)
           , Relationship<NodeA, NodeA>()
           , Relationship<NodeA, NodeB>()
           , Relationship<NodeB, NodeA>()
{
}

NodeA::NodeA(string name
          ): MyNode(name)
           , Relationship<NodeA, NodeA>()
           , Relationship<NodeA, NodeB>()
           , Relationship<NodeB, NodeA>()
{
}

void NodeA::traverseB() {
  cout << *this;
  auto b = Relationship<NodeA, NodeB>::getNext();
  if (b) {
    cout << " -> ";
    b->traverseB();
  }
}


/*
 * NodeB
 */
NodeB::NodeB(DiGraph* digraph
           , string name
          ): MyNode(digraph, name)
           , Relationship<NodeB, NodeB>()
           , Relationship<NodeA, NodeB>()
           , Relationship<NodeB, NodeA>()
{
}

NodeB::NodeB(string name
          ): MyNode(name)
           , Relationship<NodeB, NodeB>()
           , Relationship<NodeA, NodeB>()
           , Relationship<NodeB, NodeA>()
{
}

void NodeB::traverseB() {
  cout << *this;
  auto b = Relationship<NodeB, NodeB>::getNext();
  if (b) {
    cout << " -> ";
    b->traverseB();
  }
}

//
// Super rudimentary console logging
//
#define LOG(level, prefix, msg) if (level <= log_level) cout << log_prefix << prefix << msg << endl;
#define TRACE(msg) LOG(5, "(T): ", msg);
#define DEBUG(msg) LOG(4, "(D): ", msg);
#define INFO(msg) LOG(3, "(I): ", msg);
#define WARNING(msg) LOG(2, "(W): ", msg);
#define ERROR(msg) LOG(1, "(E): ", msg);
#define FATAL(msg) LOG(0, "(F): ", msg);
#define ALWAYS(msg) LOG(0, "(A): ", msg);


/*
 * main
 *   Simple test method that constructs a digraph and traverses it.
 *
 *       +----+   +----+
 *       | a0 |-->| a1 |
 *       +----+   +----+
 *        |  A
 *        |  |
 *        V  |
 *       +----+   +----+
 *       | b0 |-->| b1 |
 *       +----+   +----+
 */
int main(int argc, char* argv[]) {
  string log_prefix = "[intg] ";
  int log_level = 0;
  if (argc > 1) {
    log_level = atoi(argv[1]);
  }

  INFO("Starting Eyeball Integration Testing");

  DEBUG("Setting Up DiGraph");
  TRACE("  +----+   +----+");
  TRACE("  | a0 |-->| a1 |");
  TRACE("  +----+   +----+");
  TRACE("   |  A");
  TRACE("   |  |");
  TRACE("   V  |");
  TRACE("  +----+   +----+");
  TRACE("  | b0 |-->| b1 |");
  TRACE("  +----+   +----+");

  DEBUG("Constructing nodes");
  DiGraph* digraph = new DiGraph("TestGraph");

  DEBUG("Constructing nodes");
  NodeA* a0 = new NodeA(digraph, "a0");
  TRACE("  " << left << std::setw(10) << *a0 << " (" << a0 << ")");
  NodeA* a1 = new NodeA(digraph, "a1");
  TRACE("  " << left << std::setw(10) << *a1 << " (" << a1 << ")");
  NodeB* b0 = new NodeB(digraph, "b0");
  TRACE("  " << left << std::setw(10) << *b0 << " (" << b0 << ")");
  NodeB* b1 = new NodeB(digraph, "b1");
  TRACE("  " << left << std::setw(10) << *b1 << " (" << b1 << ")");

  DEBUG("Constructing edges");
  auto a0a1 = Relationship<NodeA, NodeA>::connector<Edge>()(digraph, a0, a1);
  TRACE("  " << left << std::setw(10) << *a0a1 << " (" << a0a1 << ")");
  auto a0b0 = Relationship<NodeA, NodeB>::connector<Edge>()(digraph, a0, b0);
  TRACE("  " << left << std::setw(10) << *a0b0 << " (" << a0b0 << ")");
  auto b0a0 = Relationship<NodeB, NodeA>::connector<Edge>()(digraph, b0, a0);
  TRACE("  " << left << std::setw(10) << *b0a0 << " (" << b0a0 << ")");
  auto b0b1 = Relationship<NodeB, NodeB>::connector<Edge>()(digraph, b0, b1);
  TRACE("  " << left << std::setw(10) << *b0b1 << " (" << b0b1 << ")");

  INFO("GraphViz Representation:");
  cout << endl;
  cout << digraph->to_graphviz() << endl;
  cout << endl;

  INFO("Graph Manipulation and traverseB()");
  cout << endl;
  a0->traverseB();
  cout << endl;
  delete b1;
  b1 = nullptr;
  a0->traverseB();
  cout << endl;
  delete b0;
  b0 = nullptr;
  a0->traverseB();
  cout << endl;
  delete a0;
  a0 = nullptr;
  delete a1;
  a1 = nullptr;


  delete digraph;

  cout << endl;
  INFO("Ending Eyeball Integration Testing");

}
