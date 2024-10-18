#include <iostream>
#include <cassert>

#include "MyMap.h"

int main()
{
    Map<int, std::string> map;
    
    // Insert nodes
    map.insert(3, "three");   // Root insertion
    map.insert(1, "one");     // Left child of root
    map.insert(0, "zero");    // Left-left case, triggers right rotation
    map.insert(5, "five");    // Right child of root
    map.insert(6, "six");     // Triggers recoloring (uncle is red)
    map.insert(4, "four");    // Left-right case, triggers left-right rotation

    map.insert(5, "five");    // test insertion of existing element

    map.insert(2, "two");     // Simple insertion, no rotation needed
    map.insert(7, "seven");   // Simple right child
    map.insert(8, "eight");   // Right-left case, rotation on right side
    map.insert(9, "nine");    // Right-right rotation on right

    map.print();

    // Perform deletions
    map.erase(0);  // Delete leaf node
    map.erase(7);  // Delete node with one child
    map.erase(5);  // Delete node with two children
    map.erase(3);  // Delete root (triggers root replacement)
    map.erase(10); // Attempt to delete non-existent key (graceful handling)
    map.erase(1);  // Delete a deeper node that requires rebalancing

    map.print();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
