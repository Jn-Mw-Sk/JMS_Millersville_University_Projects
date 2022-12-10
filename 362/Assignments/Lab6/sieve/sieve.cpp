/*
  Filename   : sieve.cpp
  Author     : Gary M. Zoppetti
  Course     : CSCI 362: Data Structures
  Assignment : Sieve of Eratosthenes
  Description: A program using the Sieve of Eratosthenes
*/  

/*******************************************************/
// System Includes
#include <iostream>
#include "Timer.hpp"
#include <set>
#include <vector>
#include <cmath>


/*******************************************************/
// Function prototypes

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
std::set<unsigned>
sieveSet (unsigned N);

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
std::set<unsigned>
sieveVector (unsigned N);

int main (int argc, char* argv[])
{
    std::string version{argv[1]};
    unsigned int number = std::stoul (std::string{argv[2]});
    auto sieveVersion = (version == "set" ? &sieveSet : &sieveVector);
    Timer<> t;

    auto answer = sieveVersion( number );

    t.stop();
    std::cout << "Pi[" << number << "] = " << answer.size() << " (using a " << version << ")" << std::endl
              << "Time: " << t.getElapsedMs() << " ms" << std::endl;
    return 0;
}

// Return the set of primes between 2 and N.
// Use a set to implement the sieve.
std::set<unsigned>
sieveSet (unsigned N)
{
    // Populate set
    std::set<unsigned> primes;
    for(int i = 2; i <= N; ++i)
    {
        primes.insert(i);
    }

    auto iter = primes.begin();
    
    while (iter != primes.end())
    {
        for(auto i = *iter * *iter; i <= *--primes.end(); i += *iter)
        {
            primes.erase(i);
        }
        
        ++iter;
    }

    return primes;
}

// Return the set of primes between 2 and N.
// Use a vector to implement the sieve.
// After filtering out the composites, put the primes in a set
//   to return to the caller. 
std::set<unsigned>
sieveVector (unsigned N)
{
    std::set<unsigned> primes;

    std::vector<bool> vecPrimes(N, true);

    for(unsigned i = 2; i < N; ++i)
    {
        if(vecPrimes[i] == true)
        {
            for (unsigned j = i * i; j <= N; j += i)
            {
                vecPrimes[j] = false;
            }
        }
    }

    for (size_t n = 2; n <= N; ++n)
    {
        if( vecPrimes[n] == true)
        {
            primes.insert(n);
        }
    }

    return primes;

}

/**

N       10,000,000    20,000,000   40,000,000
=============================================
set        36809.1    78140.2      166296     ms
vector     2630.64    5299.54      10720.7    ms

The vector implementation by far outperforms the set implementation for each value of N.

Vectors have constant time  ( O(1) ) search operations, making them a little faster than sets. 
Sets have to iterate through the container to find the values, making them slower. 

**/

