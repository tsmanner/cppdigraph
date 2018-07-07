/*
 * Some library agnostic eyeball integration testing.
 */


#include "test.h"


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


/*
 * main
 *   Simple test method that constructs a digraph and traverses it.
 *
 *       +----+         +----+
 *       | a0 |--a0a1-->| a1 |
 *       +----+         +----+
 *        |  ^
 *        |  |
 *        | b0a0
 *        |  |
 *      a0b0 |
 *        |  |
 *        V  |
 *       +----+         +----+
 *       | b0 |--b0b1-->| b1 |
 *       +----+         +----+
 */
int main() {
  NodeA* a0 = new NodeA("a0");
  NodeA* a1 = new NodeA("a1");
  NodeB* b0 = new NodeB("b0");
  NodeB* b1 = new NodeB("b1");
  auto a0b0 = connector<MyEdge>()(a0, b0);
  auto b0b1 = connector<MyEdge>()(b0, b1);
  cout << "Constructing objects:" << endl;
  cout << "  n " << *a0 << ":       " << a0 << endl;
  cout << "  n " << *a1 << ":       " << a1 << endl;
  cout << "  n " << *b0 << ":       " << b0 << endl;
  cout << "  n " << *b1 << ":       " << b1 << endl;
  cout << "  e " << *a0b0 << ": " << a0b0 << endl;
  cout << "  e " << *b0b1 << ": " << b0b1 << endl;
  cout << endl;
  a0->traverseB();
  cout << endl;
  delete b1;
  a0->traverseB();
  cout << endl;
  delete b0;
  a0->traverseB();
  cout << endl;
  delete a0;
}
