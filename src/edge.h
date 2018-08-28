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
  Edge(tail_t* tail, head_t* head): EdgeBase(), mTail(tail), mHead(head) {
    getTail()->addEdge(this);
    getHead()->addEdge(this);
  }

  virtual ~Edge() {
    if (getTail()) getTail()->removeEdge(this);
    if (getHead()) getHead()->removeEdge(this);
  }

  tail_t* getTail() {
    return mTail;
  }

  head_t* getHead() {
    return mHead;
  }

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
template <template<typename, typename> class edge_t>
struct connector {
  template <typename tail_t, typename head_t>
  edge_t<tail_t, head_t>* operator()(tail_t* tail, head_t* head) {
    return new edge_t<tail_t, head_t>(tail, head);
  }
};


/*
 * A connector object for `Edge`
 * Example:
 *   Node* n0 = new Node();
 *   Node* n1 = new Node();
 *   Edge<Node, Node>* edge = connect(n0, n1);
 */
static connector<Edge> connect = connector<Edge>();


} // namespace cdg

#endif
