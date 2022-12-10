#ifndef DIVIDE_AND_CONQUER_HPP_
#define DIVIDE_AND_CONQUER_HPP_

#include <iterator>
#include <utility>
#include <algorithm> //!!!! ONLY USE FOR std::copy !!!!
#include <vector>

// NOTE: you are forbidden from using anything from <algorithm> for this assignment
//       EXCEPT for std::copy

namespace SortUtils
{

// [9]
// Given a RandomAccessRange [first, last), determine where the "midpoint"
// would be and perform the following steps:
// order *first, *mid, *std::prev(last) in such a way such that
//   *first <= *mid <= *std::prev(last)
//
// returns an iterator to mid -- a.k.a. the median
//
template<typename Iter>
Iter
median3 (Iter first, Iter last)
{
  auto mid = first + (std::distance(first, last) / 2); // Find the midpoint

  --last; //Decrement to last element

  
  if(*last <= *first)
    std::swap(*first, *last);
  if(*first >= *mid)
    std::swap(*first, *mid);
  if(*last <= *mid)
    std::swap(*last, *mid);

  return mid;
}

// [10]
// Takes two sorted ranges [first1, last1) and [first2, last2)
// and "merges" them by copying values into the iterator starting
// at "out". Uses operator< for comparing values
//
// Returns the iterator of one-past-the-last where we wrote to out
//
template<typename Iter1, typename Iter2, typename OIter>
OIter
merge (Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, OIter out)
{
  auto i = first1;
  auto j = first2;

  while( i != last1 && j != last2)
  {
    if(*i < *j)
    {
      *out = *i;
      ++i;
      ++out;
    }
    else
    {
      *out = *j;
      ++j;
      ++out;
    }
  }

  while(i != last1)
  {
    *out = *i;
    ++i;
    ++out;
  }

  while(j != last2)
  {
    *out = *j;
    ++j;
    ++out;
  }

  return out;
}

// [15]
// Takes a RandomAccessRange [first, last) and partitions the data into
// three groups -- this should be accomplished in a SINGLE PASS Big-O: O(N)
//
// Group 1: all values in [first, last) < pivot
// Group 2: all values in [first, last) == pivot
// Group 3: all values in [first, last) > pivot
//
// [ ... Group 1 ... | ... Group 2 ... | ... Group 3 ... ]
//                   ^                 ^
//                   p1                p2
//
// Returns a pair of iterators pointing to "p1" and "p2" above
//
template<typename Iter, typename Value>
std::pair<Iter, Iter>
partition (Iter first, Iter last, Value const& pivot)
{
  // TODO
  auto lo = first;
  auto eq = first;
  auto hi = last;

  while(eq != hi)
  {
    if(*eq == pivot)
    {
      ++eq;
    } 
    else if(*eq < pivot) 
    {
      ++lo;
      ++eq;
      std::swap(eq, hi);
    }
    else
    {
      std::swap(eq, lo);
      --hi;
      ++eq;
    }
  }

  while(*first < pivot)
  {
    ++first;
  }
  auto iter = first;
  while(*iter == pivot)
  {
    ++iter;
  }

  return std::make_pair(first, iter);
}

// [10]
// Given a RandomAccessRange, recursively call partition on either the
// left half or right half until you have found the nth largest element
//
// A call to nth_element (v.begin(), v.end(), 0) will return the min
// A call to nth_element (v.begin(), v.end(), v.size() - 1) will return the max
// A call to nth_element (v.begin(), v.end(), v.size() / 2) will return the median
//
// Precondition:
//   std::distance (begin, end) > n
//
// Hints:
//  - n will change if you need to recurse on the right half
//  - No recursion happens if "index of" n is between "index of" p1 and p2
//    remember: p1 and p2 are the return values to partition.
//  - call median3 to get a pivot value
//  - when calling partition, remember to dereference the iterator returns by median3
//
template<typename Iter>
Iter
nth_element (Iter first, Iter last, size_t n)
{
  // auto [p1, p2] = SortUtils::partition (...);
  auto pivot = *SortUtils::median3(first, last);
  auto [p1, p2] = SortUtils::partition(first, last, pivot);


  if(n < *p1){
    return SortUtils::nth_element(first, p1, n);
  }
  else if (n < pivot)
  {
    return first;
  }
  else
  {
    return SortUtils::nth_element(p2, last, n);
  }

}

// [10]
// Given a RandomAccessRange, sort using merge sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - You will need a vector to act as a temporary buffer.
//
template<typename Iter>
void
merge_sort (Iter first, Iter last)
{
  // T is the type of data we are sorting
  using T = std::remove_reference_t<decltype (*std::declval<Iter> ())>;
  std::vector<T> buffer(std::distance(first, last));

  //base case
  if(std::distance(first, last) <= 1)
  {
    return;
  }

  //Divide: Find iter to divide range [first, last) into two parts
  auto iter = SortUtils::median3(first, last);

  //Conquer: recursively sort the first half and second half
  SortUtils::merge_sort(first, iter);
  SortUtils::merge_sort(iter++, last);


  //Combine: Call merge. To do so, we need a buffer
  SortUtils::merge(first, iter,  iter, last, buffer.begin());
  std::copy(buffer.begin(), buffer.end()--, first);
}

// [10]
// Given a RandomAccessRange, sort using quick sort
//
// Precondition:
//   std::distance (begin, end) > 0
//
// Hints:
//   - median3 will be called to find the pivot
//   - remember to dereference the iterator returned by median3 to get the pivot value
//   - partition should be called
//
template<typename Iter>
void
quick_sort (Iter first, Iter last)
{
  // T is the type of data we are sorting
  using T = std::remove_reference_t<decltype (*std::declval<Iter> ())>;
  //base case
  if(std::distance(first, last) <= 1)
  {
    return;
  }

  //Divide: find pivot and partition
  auto pivot = *SortUtils::median3(first, last);
  auto [p1, p2] = SortUtils::partition(first, last, pivot);

  //Conquer: recursively sort the first group and recursively sort the last group
  SortUtils::quick_sort(first, p1);
  SortUtils::quick_sort(p2, last);

}

template<typename Iter>
void
insertion_sort (Iter first, Iter last)
{
  for (Iter i = first; i != last; ++i)
  {
    for (Iter j = i; j != first; --j)
    {
      if (*(j - 1) > *j)
      {
        std::iter_swap (j - 1, j);
      }
      else
      {
        break;
      }
    }
  }
}

} // end namespace util

#endif
