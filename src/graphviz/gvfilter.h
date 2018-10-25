/*
 * gvfilter.h
 */

#ifndef CDG_GVFILTER_H
#define CDG_GVFILTER_H

#include "../utility.h"


namespace cdg {


class GvFilter {
public:

  virtual void filter(GvNode* gvNode);
  virtual void filter(GvEdge* gvEdge);

};

} // namespace cdg

#endif
