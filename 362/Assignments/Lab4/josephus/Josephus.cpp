/*
  Filename   : Josephus.cpp
  Author     : John Shenk
  Course     : CSCI 362-01
  Assignment : Josephus
  Date       : September 24, 2021
  Description: Simulate the Josephus problem modeled as a std::list.
*/

/************************************************************/
// System includes
#include <iostream>
#include <list>
#include <iterator>

/************************************************************/
// Function prototypes

/* Simulate the Josephus problem modeled as a std::list.
 * This function will modify the passed list with only a
 * single survivor remaining.
 *
 * @param circle -- the linked list of people
 * @param k -- skip amount. NOTE: k > 0
 *
 * @return a list of those who are executed in chronological order
 */
template <typename T>
std::list<T>
execute (std::list<T>& circle, int k);

/* entry point to the Josephus problem from the autograder
 *
 * @param N -- number of people in the circle
 * @param k -- skip amount. NOTE: k > 0
 */
int
josephus (int N, int k);

/*
int 
main(int argc, char* argv[])
{
    int num, skip;

    std::cout<<"Enter the number of people: ";
    std::cin>>num;

    std::cout<<"\nEnter the skip amount: ";
    std::cin>>skip;
    
    std::cout<<"\nThe survivor is: "<<josephus(num, skip)<<std::endl;

    return 0;
}
*/


int 
josephus(int N, int k)
{
    std::list<int> toExecute;

    for(int i = 1; i <= N; i++)
    {
        toExecute.push_back(i);
    }
 
    toExecute = execute(toExecute, k);

    return toExecute.front();
}

/*
* T(N, k) = O(n) - linear time
* T(k((N - 1))
*
*/
template <typename T>
std::list<T>
execute (std::list<T>& circle, int k)
{
    auto iter = circle.begin(); 

    int count = 0;

    int count2 = 0;

    while(circle.size() > 1)
    {

        for (int i = 1; i < k; ++i)
        {
            iter++;
            count++;

            if(iter == circle.end())
            {
                iter = circle.begin();
            }
            
        }

        iter = circle.erase(iter);

        if(iter == circle.end())
        {
            iter = circle.begin();

        }
        count2++;
    }

    return circle;
}


