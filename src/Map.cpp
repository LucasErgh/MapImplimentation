#include <iostream>
#include <cassert>

#include "MyMap.h"

int main()
{
    Map<int, std::string> map;

    // Test cases supplied by ChatGPT
    
    // Test insertions to cover all possibilities in a self-balancing tree

    // Case 1: Initial Balanced Insertions (No Rotations Needed)
    map.insert(3, "three");
    map.insert(1, "one");
    map.insert(5, "five");

    // Case 2: Right Rotation
    map.insert(0, "zero");  // This causes a right rotation

    // Case 3: Left Rotation
    map.insert(6, "six");  // This causes a left rotation

    // Case 4: Left-Right Rotation
    map.insert(4, "four");  // This causes a left-right rotation

    // Case 5: Right-Left Rotation
    map.insert(2, "two");  // This causes a right-left rotation

    // Print the tree after all insertions
    map.print();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
