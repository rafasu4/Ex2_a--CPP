#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
 
 using namespace ariel;

int main()
{
    ariel::Board b();
    b.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");
    
}