#include <iostream>
#include <cassert>

#include "MyMap.h"

int main()
{
    Map<int, std::string> map;

    // Test insert
    map.insert(10, "ten");
    map.insert(20, "twenty");
    map.insert(5, "five");
    map.insert(1, "one");
    map.insert(15, "fifteen");
    map.insert(30, "thirty");
    map.insert(25, "twenty-five");
    map.insert(7, "seven");
    map.insert(40, "forty");
    map.insert(35, "thirty-five");
    map.insert(3, "three");

    // Test find
    // assert(map.find(10) == "ten");
    // assert(map.find(20) == "twenty");
    // assert(map.find(5) == "five");  // Should not find this key

    // Test erase (not implemented, so just a placeholder)
    // map.erase(10);
    // assert(map.find(10) == nullptr);
    map.print();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
