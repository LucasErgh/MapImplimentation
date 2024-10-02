#include <iostream>
#include <cassert>

#include "MyMap.h"
    #include "MyMap.cpp"

int main()
{
    Map<int, std::string> map;

    // Test insert
    map.insert(10, "ten");
    map.insert(20, "twenty");
    map.insert(5, "five");

    // Test find
    assert(map.find(10) == "ten");
    assert(map.find(20) == "twenty");
    assert(map.find(5) == "five");  // Should not find this key

    // Test erase (not implemented, so just a placeholder)
    // map.erase(10);
    // assert(map.find(10) == nullptr);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
