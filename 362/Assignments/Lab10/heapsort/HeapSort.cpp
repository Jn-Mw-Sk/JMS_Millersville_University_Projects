
/*
  Filename   : HeapSort.cpp
  Author     : Jingnan Xie, John Shenk
  Course     : CSCI 362
  Description: Implementation of Heap Sort
*/

#include <iostream>
#include <list>
#include <numeric>
#include <vector>
#include <set>

//'temp' is an arbitrary vector 
//temp[0] is meaningless and NOT used
//heapify the node with index 'i'
//'last' is the last index of the vector 'temp'
void heapifyNode(std::vector<int>& temp, int i, int last){
  //TO DO
  //Hint: use recursion
  //Base case: i is a leaf
  if(i > last/2) return;

  int left = 2 * i;
  int right = 2 * i + 1;
  int min = i;

  if(left <= last && temp[min] > temp[left]) min = left;
  if(right <= last && temp[min] > temp[right]) min = right; 
    
  if(i != min)
  {
    std::swap(temp[min], temp[i]);
    heapifyNode(temp, min, last);
  }
}

//heapify all the internal nodes to build a heap
//'temp' is an arbitrary vector, last is its last index
//first index of 'temp' is 1; temp[0] is meaningless and NOT used
void heapify(std::vector<int>& temp, int last){
  //TO DO
  for(int i = (temp.size() - 1) / 2; i >= 1; --i)
  {
    heapifyNode(temp, i, last);
  }
}

//A heapSort helper
//'heap' is a min heap and 'last' is its last index
//first index of 'heap' is 1
void heapSort(std::vector<int>& heap, int last){
  //TO DO 
  //step1: swap the minimum value in 'heap' (root) with the last value of 'heap'
  //step2: heapify the root (just heapify one node) 
  //       'last' should be changed
  //step3: repeat step 1 and 2 until the size of the heap is 1
  heapify(heap, last);

  while(heap.size() > 1)
  {
      std::swap(heap[1], heap[last]);
      heapifyNode(heap, 1, last);
      heap.pop_back();
      last = heap.size() - 1;
  }

  return;

}

//main heapSort function
//Heap Sort the vector 'sort' in ***non-ascending order***
//'sort' is an arbitrary vector
//first index of sort is 0
void heapSort(std::vector<int>& sort){
  //TO DO
  //Be Careful: The index of sort starts at 0
  //            The index of temp/heap in above functions starts at 1
  //            You MUST find a way to adjust this issue
  
  std::vector<int> heap(sort.size() + 1, 0);
  for(int i = 1; i < heap.size() - 1; ++i)
  {
      heap[i] = sort[i - 1];
  }

  heapSort(heap, heap.size() - 1);
}

int 
main ()  
{
 std::vector<int> myVect ={20, -13, 29, 3, 8 , 17, 13, 10, 26, 0, -11, -5, 7, 19, 8, -11, 36, -5, 49, 13};
 
 heapSort(myVect);
 for(int e: myVect){
   std::cout<<e<<" ";
 }
 return 0;
}
