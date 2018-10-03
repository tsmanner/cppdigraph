/*
 * utility.h
 */

#ifndef CDG_UTILITY_H
#define CDG_UTILITY_H


namespace cdg {


template<typename T>
struct NameCompare {
  bool operator()(T* lhs, T* rhs) {
    return lhs->getName() < rhs->getName();
  }
};


} // namespace cdg


#endif
