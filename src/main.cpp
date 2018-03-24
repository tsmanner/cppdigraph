/*
 *
 */

#include <list>
#include <iostream>
#include <string>

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

using namespace std;


class NodeA;
class NodeB;


class NodeA: public cdg::Node {
public:
  NodeA(string name): Node(), mName(name) {}
  ~NodeA() {
    // for (auto& tail : mAATails) delete tail;
    // for (auto& head : mAAHeads) delete head;
  }

  const string getName() const { return mName; }

  void printUpstreamAs() {
    for (auto& edge : mAAHeads) {
      edge->getTail().printUpstreamAs();
    }
    if (mAAHeads.size() > 0) cout << " -> ";
    this->operator<<(cout);
  }

  void printDownstreamAs() {
    this->operator<<(cout);
    if (mAATails.size() > 0) cout << " -> ";
    for (auto& edge : mAATails) {
      edge->getHead().printDownstreamAs();
    }
  }

  ostream& operator<<(ostream& os) { return os << getName(); }

  CDG_NODE_RELATIONSHIP(NodeA, NodeA, mAATails, mAAHeads);
  CDG_NODE_RELATIONSHIP(NodeA, NodeB, mABTails, mBAHeads);

private:
  const string mName;

};


class NodeB: public cdg::Node {
public:
  NodeB(string name): Node(), mName(name) {}
  ~NodeB() {  }

  const string getName() const { return mName; }

  void printAs() {
    for (auto& edge : mABHeads) {
      edge->getTail().printUpstreamAs();
    }
    if (mABHeads.size() > 0) cout << " -> ";
    this->operator<<(cout);
    if (mBATails.size() > 0) cout << " -> ";
    for (auto& edge : mBATails) {
      edge->getHead().printDownstreamAs();
    }
  }

  ostream& operator<<(ostream& os) { return os << getName(); }

  CDG_NODE_RELATIONSHIP(NodeB, NodeA, mBATails, mABHeads);
  CDG_NODE_RELATIONSHIP(NodeB, NodeB, mBBTails, mBBHeads);

private:
  const string mName;

};


ostream& operator<<(ostream& os, NodeA& a) { return a.operator<<(os); }
ostream& operator<<(ostream& os, NodeB& b) { return b.operator<<(os); }


int main() {
  NodeA a0 = NodeA("a0");
  NodeA a1 = NodeA("a1");
  NodeB b0 = NodeB("b0");
  NodeB b1 = NodeB("b1");

  cdg::Edge<NodeA, NodeA> eAA(a0, a1);  // a0 -> a1
  cdg::Edge<NodeA, NodeB> eAB(a0, b0);  // a0 -> b0
  cdg::Edge<NodeB, NodeA> eBA(b0, a0);  // b0 -> a0
  cdg::Edge<NodeB, NodeB> eBB(b0, b1);  // b0 -> b1

  b0.printAs();
  cout << endl;

}
