/*
  Filename   : HashTable.hpp
  Author     : Jingnan Xie
  Course     : CSCI 362
  Description: A simple separate chaining Hash Table
              we learned in class with hash function:
              f(key) = key mod 11
*/


/*********************************************************/
//macro guard
#ifndef hash_table_h
#define hash_table_h
/*********************************************************/
//System includes
#include<vector>
#include<list>
#include<string>

/*********************************************************/
//local includes



template<typename T>
class HashTable{
    //data memeber: bucket array (a list vector) 
    //Each list is a <int, T> pair list
    std::vector<std::list<std::pair<int, T>>> table;

public:
    //constructor
    HashTable()
    {
        for(int i = 0; i < 11; ++i)
        {
            std::list<std::pair<int, T>> newList;
            table.push_back(newList);
        }
        
    }

    //Hash Function
    //Division Hashing with a prime number close to the data size
    int hash_function(const int& key){
        return key % 11;
    }

    //insert <key, value> into the table
    void insert(const int& key, const T& value){
        //TO DO
        //Hint: use 'std::make_pair(key, value)' to create a pair

    
        int index = hash_function(key);

        auto iter = table[index].begin();

        while(iter != table[index].end())
        {
            if((*iter).first == key)
                return;
            
            ++iter;
        }

        table[index].push_back(std::make_pair(key, value));
    }

    //erase the <key, value> with key = "key"
    //return true if "key" exists and the pair erased
    //return false if "key" does not exist
    bool erase(const int& key){
        //TO DO
        //Hint: use pair_obj.first to return the first value of a pair object
        //          pair_obj.secod to return the second value of a pair object

        int index = hash_function(key);

        auto iter = table[index].begin();

        
        while(iter != table[index].end())
        {
            if((*iter).first == key)
            {
                table[index].erase(iter);
                return true;
            }
                
            ++iter;
        }
        


        return false;

    }

    //find the value with key = "key"
    //If "key" exists, return true and the value
    //else return false and a default (meaningless) value 
    std::pair<bool, T> find(const int& key){
        //TO DO
        //Don't forget it should return a pair
        int index = hash_function(key);

        auto iter = table[index].begin();

        while(iter != table[index].end())
        {
            if((*iter).first == key)
                return std::make_pair(true, (*iter).second);
            ++iter;
        }
        
        return std::make_pair(false, "");
    }

    //modify the value with key = "key"
    //If "key" exists, modify it's value to "value", and return true
    //else, return false
    bool modify(const int& key, const T& value){
        //TO DO
        int index = hash_function(key);

        auto iter = table[index].begin();

        while(iter != table[index].end())
        {
            if((*iter).first == key)
                (*iter).second = value;
                return true;
        }

        return false;
    }

};
#endif