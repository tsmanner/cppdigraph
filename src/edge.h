/*
 * edge.h
 *
 * Types:
 *   EdgeBase
 *   Edge
 *   connector
 */
 
#ifndef CDG_EDGE_H
#define CDG_EDGE_H

#include <iostream>
#include <string>

#include "digraph.h"


namespace cdg {


class Node;


/*
 * EdgeBase
 *   Common base type for `Edge`, used by `Node` to track collections
 *   and enforce the `disconnect` api.
 */
class EdgeBase {
public:
  EdgeBase() {}
  virtual void disconnect(Node* node) = 0;
  virtual std::string to_graphviz() = 0;

};


/* 
 * Edge
 *   Connects two classes that implement the `Node` api together.
 *   When a node is disconnected, the `Edge` sets the head or tail
 *   pointer to `nullptr`.  If both nodes disconnect, the `Edge`
 *   deletes itself.
 */
template <typename tail_t, typename head_t>
class Edge: public EdgeBase {
public:
  Edge(DiGraph* digraph
     , tail_t* tail
     , head_t* head
    ): EdgeBase()
     , mDiGraph(digraph)
     , mTail(tail)
     , mHead(head)
  {
    if (mDiGraph) mDiGraph->add(this);
    if (getTail()) getTail()->addEdge(this);
    if (getHead()) getHead()->addEdge(this);
  }

  Edge(tail_t* tail
     , head_t* head
    ): Edge(nullptr, tail, head)
  {
  }

  virtual ~Edge() {
    if (mDiGraph) mDiGraph->remove(this);
    if (getTail()) getTail()->removeEdge(this);
    if (getHead()) getHead()->removeEdge(this);
  }

  tail_t* getTail() {
    return mTail;
  }

  head_t* getHead() {
    return mHead;
  }

  void setDiGraph(DiGraph* digraph) { mDiGraph = digraph; }

  virtual void disconnect(Node* node) {
    if (node == mTail) mTail = nullptr;
    if (node == mHead) mHead = nullptr;
    if (mTail == nullptr && mHead == nullptr) {
      delete this;
    }
  }

  virtual std::string to_graphviz() {
    if (getTail() && getHead()) {
      return getTail()->graphviz_name() + " -> " + getHead()->graphviz_name();
    }
    return "";
  }

  virtual std::string to_string() {
    std::string s = "";
    if (getTail()) s += getTail()->to_string();
    else s += "[nullptr]";
    s += "->";
    if (getHead()) s += getHead()->to_string();
    else s += "[nullptr]";
    return s;
  }

  std::ostream& operator<<(std::ostream& os) {
    return os << to_string();
  }

private:
  DiGraph* mDiGraph;
  tail_t* mTail;
  head_t* mHead;

};


/*
 * connector
 *   This object is templated with a type that itself expects two templates
 *   Example:
 *     Node* n0 = new Node();
 *     Node* n1 = new Node();
 *     Edge<Node, Node>* edge = connector<Edge>()(n0, n1);
 */
template <template<typename, typename> class edge_t = Edge>
struct connector {
  template <typename tail_t, typename head_t>
  edge_t<tail_t, head_t>* operator()(tail_t* tail, head_t* head) {
      return (*this)(nullptr, tail, head);
  }

  template <typename tail_t, typename head_t>
  edge_t<tail_t, head_t>* operator()(DiGraph* digraph, tail_t* tail, head_t* head) {
    if (tail and head) {
      if (!digraph) digraph = tail->getDiGraph();
      return new edge_t<tail_t, head_t>(digraph, tail, head);
    }
    return nullptr;
  }
};


/*
 * A default connector object
 * Example:
 *   Node* n0 = new Node();
 *   Node* n1 = new Node();
 *   Edge<Node, Node>* edge = connect(n0, n1);
 */
static connector<> connect = connector<>();


} // namespace cdg

#endif
