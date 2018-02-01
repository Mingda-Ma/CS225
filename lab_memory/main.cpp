#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "fileio.h"
#include "letter.h"
#include "room.h"
#include "allocator.h"

using namespace std;

/**
 * Main routine.
 * Creates an Allocator object and allocates the students.
 */
int main()
{
    fileio::init();
    Allocator theAllocator("students.txt", "rooms.txt");
    theAllocator.allocate();
    theAllocator.printRooms();
    fileio::halt();
    return 0;
}
