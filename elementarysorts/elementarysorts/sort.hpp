/*
  Filename:   sort.hpp
  Author:     John Shenk
  Course:     CSCI 362: Data Structures
  Date:       February 14, 2021
  Assignment: Elementary Sorts - Assignment 3
  
  Description:
  
    Header file for templated sorting algorithms, specifically bubble
    sort (optimized), insertion sort, and selection sort.  Includes a
    'Statistics' data type for aggregating counts for swaps and
    comparisons.
*/

#ifndef SORTING_ALGORITHMS_HPP_
#define SORTING_ALGORITHMS_HPP_

#include <vector>

/**********************************************************/

struct Statistics
{
  // Default constructs swaps and compares to zero
  size_t numSwaps { 0 };
  size_t numCompares { 0 };
};

/**********************************************************/

template <typename T>
void
bubbleSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  const size_t N = v.size();
  
  for (size_t i = N - 1; i >= 1; --i)
  {
    for (size_t j = 0; j < i; ++j)
    {
      if (v.at(j) > v.at(j + 1))
      {
        s.numCompares += 1;
        s.numSwaps += 1;
        std::swap (v.at(j), v.at(j + 1));
      }
    }
  }
}

/**********************************************************/

template <typename T>
void
insertionSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  const size_t N = v.size();

  for(size_t i = 1; i < N; ++i)
  {
    int n = v.at(i);
    int j = i;

    s.numCompares += 1;
    while (j >= 1 && n < v.at(j - 1)) 
    {
      v.at(j) = v.at(j - 1);
      --j;
    }

    v.at(j) = n;
  }
}

/**********************************************************/

template <typename T>
void
selectionSort (std::vector<T>& v, Statistics& s)
{
  s.numCompares = 0;
  s.numSwaps = 0;

  const size_t N = v.size();

  for(size_t i = 0; i < N - 1; ++i)
  {
      s.numSwaps += 1;
      size_t min = i;
      for(size_t j = i + 1; j < N; ++j)
      {
        if(v.at(j) < v.at(min))
        {
          
          min = j;
        }

        if (i != min)
        {
          std::swap(v.at(j), v.at(min));
        }
        s.numCompares += 1;
      }
  }

}

#endif
