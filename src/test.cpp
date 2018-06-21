/*
 * Some library agnostic eyeball integration testing.
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
    CDG_AUTO_DELETE_EDGES(mAATails);
    CDG_AUTO_DELETE_EDGES(mAAHeads);
    CDG_AUTO_DELETE_EDGES(mABTails);
    CDG_AUTO_DELETE_EDGES(mBAHeads);
  }

  void printUpstreamAs() {
    for (auto& head : mAAHeads) {
      head->traverse()->printUpstreamAs();
    }
    if (mAAHeads.size() > 0) cout << " -> ";
    this->operator<<(cout);
  }

  void printDownstreamAs() {
    this->operator<<(cout);
    if (mAATails.size() > 0) cout << " -> ";
    for (auto& tail : mAATails) {
      tail->traverse()->printDownstreamAs();
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
    CDG_AUTO_DELETE_EDGES(mBATails);
    CDG_AUTO_DELETE_EDGES(mABHeads);
    CDG_AUTO_DELETE_EDGES(mBBTails);
    CDG_AUTO_DELETE_EDGES(mBBHeads);
  }

  void printAs() {
    for (auto& head : mABHeads) {
      head->traverse()->printUpstreamAs();
    }
    if (mABHeads.size() > 0) cout << " -> ";
    this->operator<<(cout);
    if (mBATails.size() > 0) cout << " -> ";
    for (auto& tail : mBATails) {
      tail->traverse()->printDownstreamAs();
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
  // Nodes
  as["a0"] = new NodeA("a0");
  as["a1"] = new NodeA("a1");
  bs["b0"] = new NodeB("b0");
  bs["b1"] = new NodeB("b1");

  // Edges
  as["a0"]->connect(*bs["b0"]);
  bs["b0"]->connect(*as["a0"]);
  bs["b0"]->connect(*bs["b1"]);
  as["a0"]->connect(*as["a1"]);

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
