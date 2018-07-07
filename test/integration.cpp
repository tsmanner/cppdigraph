/*
 * Some library agnostic eyeball integration testing.
 */


#include "integration.h"

// #include <boost/log/trivial.hpp>


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
MyNode::MyNode(string name): Node(name) {
}


/*
 * NodeA
 */
NodeA::NodeA(string name): MyNode(name) {
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
NodeB::NodeB(string name): MyNode(name) {
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
#define LOG(level, msg) if (level <= log_level) cout << "(" << level << ") " << log_prefix << msg << endl;

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
  string log_prefix = "[intg]: ";
  int log_level = 0;
  if (argc > 1) {
    log_level = atoi(argv[1]);
  }

  LOG(0, "Starting Eyeball Integration Testing");

  LOG(1, "Setting Up DiGraph");
  LOG(2, "  +----+   +----+");
  LOG(2, "  | a0 |-->| a1 |");
  LOG(2, "  +----+   +----+");
  LOG(2, "   |  A");
  LOG(2, "   |  |");
  LOG(2, "   V  |");
  LOG(2, "  +----+   +----+");
  LOG(2, "  | b0 |-->| b1 |");
  LOG(2, "  +----+   +----+");

  LOG(1, "Constructing nodes");
  NodeA* a0 = new NodeA("a0");
  LOG(2, "  " << *a0 << "         (" << a0 << ")");
  NodeA* a1 = new NodeA("a1");
  LOG(2, "  " << *a1 << "         (" << a1 << ")");
  NodeB* b0 = new NodeB("b0");
  LOG(2, "  " << *b0 << "         (" << b0 << ")");
  NodeB* b1 = new NodeB("b1");
  LOG(2, "  " << *b1 << "         (" << b1 << ")");
  LOG(1, "Constructing edges");
  auto a0a1 = connector<MyEdge>()(a0, a1);
  LOG(2, "  " << *a0a1 << "  (" << a0a1 << ")");
  auto a0b0 = connector<MyEdge>()(a0, b0);
  LOG(2, "  " << *a0b0 << "  (" << a0b0 << ")");
  auto b0a0 = connector<MyEdge>()(b0, a0);
  LOG(2, "  " << *b0a0 << "  (" << b0a0 << ")");
  auto b0b1 = connector<MyEdge>()(b0, b1);
  LOG(2, "  " << *b0b1 << "  (" << b0b1 << ")");

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

  LOG(0, "Ending Eyeball Integration Testing");
}
