/*
 * Some library agnostic eyeball integration testing.
 */


#include "test.h"


/*
 * Node stream operator
 */
ostream& operator<<(ostream& os, Node node) { return node.operator<<(os); }


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

NodeA::~NodeA() {
  delete mOutgoingB;
}

void NodeA::connect(Edge<NodeA, NodeB>* edge) { mOutgoingB = edge; }
void NodeA::disconnect(Edge<NodeA, NodeB>* edge) { mOutgoingB = nullptr; }

void NodeA::traverseB() {
  cout << *this << " -> ";
  if (mOutgoingB && mOutgoingB->getHead()) cout << *mOutgoingB->getHead();
  else cout << "nullptr";
}


/*
 * NodeB
 */
NodeB::NodeB(string name): MyNode(name) {}
NodeB::~NodeB() { delete mIncomingA; }

void NodeB::connect(Edge<NodeA, NodeB>* edge) { mIncomingA = edge; }
void NodeB::disconnect(Edge<NodeA, NodeB>* edge) { mIncomingA = nullptr; }



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
  NodeB* b0 = new NodeB("b0");
  MyEdge<NodeA, NodeB>* edge = new MyEdge<NodeA, NodeB>(a0, b0);
  a0->traverseB();
  cout << endl;
  delete b0;
  a0->traverseB();
  cout << endl;
}
