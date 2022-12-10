#include<iostream>
#include "HashTable.hpp"

int main(){

    HashTable<std::string> myTable;

    myTable.insert(4, "Apple");
    myTable.insert(15, "Banana");
    myTable.insert(7, "Strawberry");
    myTable.insert(33, "Orange");
    myTable.insert(22, "Pear");
    myTable.insert(11, "Peach");
    myTable.insert(0, "Kiwi");

    std::cout<<myTable.find(15).first<<" "<<myTable.find(15).second<<std::endl;
    myTable.erase(15);
    std::cout<<myTable.find(15).first<<" "<<myTable.find(15).second<<std::endl;
    std::cout<<myTable.find(4).first<<" "<<myTable.find(4).second<<std::endl;
    std::cout<<myTable.find(7).first<<" "<<myTable.find(7).second<<std::endl;
    myTable.modify(7, "Cantalop");
    std::cout<<myTable.find(7).first<<" "<<myTable.find(7).second<<std::endl;

    std::cout<<myTable.find(33).first<<" "<<myTable.find(33).second<<std::endl;
    myTable.erase(33);
    std::cout<<myTable.find(33).first<<" "<<myTable.find(33).second<<std::endl;

    std::cout<<myTable.find(22).first<<" "<<myTable.find(22).second<<std::endl;
    std::cout<<myTable.find(11).first<<" "<<myTable.find(11).second<<std::endl;
    myTable.insert(0, "FireFox");
    std::cout<<myTable.find(0).first<<" "<<myTable.find(0).second<<std::endl;

    myTable.erase(0);
    std::cout<<myTable.find(0).first<<" "<<myTable.find(0).second<<std::endl;

    

    return 0;
}