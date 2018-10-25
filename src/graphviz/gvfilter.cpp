/*
 * gvfilter.h
 */

#ifndef CDG_GVFILTER_C
#define CDG_GVFILTER_C

#include "../edge.h"
#include "../node.h"


namespace cdg {


void GvFilter::filter(GvNode* gvNode) {
  gvNode->getObject()->applyFilter(this, gvNode);
};


void GvFilter::filter(GvEdge* gvEdge) {
  gvEdge->getObject()->applyFilter(this, gvEdge);
};


} // namespace cdg


#endif
