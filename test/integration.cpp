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


/*
 * NodeA
 */
NodeA::NodeA(DiGraph* digraph, string name): MyNode(digraph, name) {
}

GraphVizStatements NodeA::graphviz_statements() {
  GraphVizStatements gvs = MyNode::graphviz_statements();
  if (mOutgoingA) gvs.edges.insert(mOutgoingA->to_graphviz());
  if (mIncomingA) gvs.edges.insert(mIncomingA->to_graphviz());
  if (mOutgoingB) gvs.edges.insert(mOutgoingB->to_graphviz());
  if (mIncomingB) gvs.edges.insert(mIncomingB->to_graphviz());
  return gvs;
}

void NodeA::connect(Edge<NodeA, NodeB>* edge) {
  mOutgoingB = edge;
}

void NodeA::disconnect(Edge<NodeA, NodeB>* edge) {
  mOutgoingB = nullptr;
}

void NodeA::connect(Edge<NodeB, NodeA>* edge) {
  mIncomingB = edge;
}

void NodeA::disconnect(Edge<NodeB, NodeA>* edge) {
  mIncomingB = nullptr;
}

void NodeA::connect(Edge<NodeA, NodeA>* edge) {
  if (edge->getTail() == this) {
    mOutgoingA = edge;
  }
  if (edge->getHead() == this) {
    mIncomingA = edge;
  }
}

void NodeA::disconnect(Edge<NodeA, NodeA>* edge) {
  if (edge == mOutgoingA) {
    mOutgoingA = nullptr;
  }
  if (edge == mOutgoingA) {
    mIncomingA = nullptr;
  }
}

void NodeA::traverseB() {
  cout << *this;
  if (mOutgoingB && mOutgoingB->getHead()) {
    cout << " -> ";
    mOutgoingB->getHead()->traverseB();
  }
}


/*
 * NodeB
 */
NodeB::NodeB(DiGraph* digraph, string name): MyNode(digraph, name) {
}

GraphVizStatements NodeB::graphviz_statements() {
  GraphVizStatements gvs = MyNode::graphviz_statements();
  if (mOutgoingA) gvs.edges.insert(mOutgoingA->to_graphviz());
  if (mIncomingA) gvs.edges.insert(mIncomingA->to_graphviz());
  if (mOutgoingB) gvs.edges.insert(mOutgoingB->to_graphviz());
  if (mIncomingB) gvs.edges.insert(mIncomingB->to_graphviz());
  return gvs;
}

void NodeB::connect(Edge<NodeA, NodeB>* edge) {
  mIncomingA = edge;
}

void NodeB::disconnect(Edge<NodeA, NodeB>* edge) {
  mIncomingA = nullptr;
}

void NodeB::connect(Edge<NodeB, NodeA>* edge) {
  mOutgoingA = edge;
}

void NodeB::disconnect(Edge<NodeB, NodeA>* edge) {
  mOutgoingA = nullptr;
}

void NodeB::connect(Edge<NodeB, NodeB>* edge) {
  if (edge->getTail() == this) {
    mOutgoingB = edge;
  }
  if (edge->getHead() == this) {
    mIncomingB = edge;
  }
}

void NodeB::disconnect(Edge<NodeB, NodeB>* edge) {
  if (edge == mOutgoingB) {
    mOutgoingB = nullptr;
  }
  if (edge == mOutgoingB) {
    mIncomingB = nullptr;
  }
}

void NodeB::traverseB() {
  cout << *this;
  if (mOutgoingB && mOutgoingB->getHead()) {
    cout << " -> ";
    mOutgoingB->getHead()->traverseB();
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
  auto a0a1 = connector<MyEdge>()(a0, a1);
  TRACE("  " << left << std::setw(10) << *a0a1 << " (" << a0a1 << ")");
  auto a0b0 = connector<MyEdge>()(a0, b0);
  TRACE("  " << left << std::setw(10) << *a0b0 << " (" << a0b0 << ")");
  auto b0a0 = connector<MyEdge>()(b0, a0);
  TRACE("  " << left << std::setw(10) << *b0a0 << " (" << b0a0 << ")");
  auto b0b1 = connector<MyEdge>()(b0, b1);
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
