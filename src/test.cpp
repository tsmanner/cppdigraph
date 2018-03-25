/*
 *
 */

#include <iostream>
#include <list>
#include <map>
#include <string>

#include "node.h"
#include "edge.h"


using namespace std;


class NodeA;
class NodeB;


class NodeA: public cdg::Node {
  CDG_NODE_CREATE_RELATIONSHIP(NodeA, NodeA, mAATails, mAAHeads);
  CDG_NODE_CREATE_RELATIONSHIP(NodeA, NodeB, mABTails, mBAHeads);

public:
  NodeA(string name): Node(name) {}

  ~NodeA() {
    CDG_NODE_DESTRUCT_RELATIONSHIP(mAATails);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mAAHeads);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mABTails);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mBAHeads);
  }

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

};


class NodeB: public cdg::Node {
  CDG_NODE_CREATE_RELATIONSHIP(NodeB, NodeA, mBATails, mABHeads);
  CDG_NODE_CREATE_RELATIONSHIP(NodeB, NodeB, mBBTails, mBBHeads);

public:
  NodeB(string name): Node(name) {}

  ~NodeB() {
    CDG_NODE_DESTRUCT_RELATIONSHIP(mBATails);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mABHeads);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mBBTails);
    CDG_NODE_DESTRUCT_RELATIONSHIP(mBBHeads);
  }

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

};


ostream& operator<<(ostream& os, NodeA& a) { return a.operator<<(os); }
ostream& operator<<(ostream& os, NodeB& b) { return b.operator<<(os); }

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
  map<string, NodeA*> as;
  map<string, NodeB*> bs;
  // Permanent nodes
  as["a0"] = new NodeA("a0");
  as["a1"] = new NodeA("a1");
  bs["b0"] = new NodeB("b0");
  bs["b1"] = new NodeB("b1");

  // Permanent edges
  new cdg::Edge<NodeA, NodeB>(*as["a0"], *bs["b0"]);  // a0 -> b0
  new cdg::Edge<NodeB, NodeA>(*bs["b0"], *as["a0"]);  // b0 -> a0
  new cdg::Edge<NodeB, NodeB>(*bs["b0"], *bs["b1"]);  // b0 -> b1
  new cdg::Edge<NodeA, NodeA>(*as["a0"], *as["a1"]);  // a0 -> a1

  // Print the graph traversal including `a1` ( a0 -> b0 -> a0 -> a1 )
  bs["b0"]->printAs();
  cout << endl;

  // Print the graph traversal excluding `a1` ( a0 -> b0 -> a0 )
  delete as["a1"];  // Should automatically delete edge a0 -> a1
  as.erase("a1");
  bs["b0"]->printAs();
  cout << endl;

  // Print the graph traversal excluding `a0` ( b0 )
  delete as["a0"];
  as.erase("a0");
  bs["b0"]->printAs();
  cout << endl;

  // Clean up the rest of our memory on the way out.
  delete bs["b0"];
  delete bs["b1"];
  bs.clear();
}
