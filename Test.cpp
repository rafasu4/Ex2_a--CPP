#include "doctest.h"
#include "Board.hpp"

ariel::Board board;
TEST_CASE("working code"){
    board.post(/*row=*/0,/*column=*/0,Direction::Horizontal, "abcd");
    CHECK("abcd" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    CHECK("---" == board.read(/*row=*/2,/*column=*/2,Direction::Vertical, /*length=*/3));
    board.post(/*row=*/0,/*column=*/3,Direction::Horizontal, "x");
    CHECK("abcx" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    board.post(/*row=*/0,/*column=*/3,Direction::Vertical, "xy");
    CHECK("abcx" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    // for(char c: board.messageBoard[0].second){
    //     cout<<c;
    // }
    CHECK("y" == board.read(/*row=*/1,/*column=*/3,Direction::Horizontal, /*length=*/1));
    CHECK("-y-" == board.read(/*row=*/1,/*column=*/2,Direction::Horizontal,/*length=*/3));
    board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");
    CHECK("abcd" == board.read(100,200, Direction::Horizontal, 4));
	board.post(/*row=*/100, /*column=*/202, Direction::Vertical, "xyzw");
	CHECK("-b-" == board.read(/*row=*/99, /*column=*/201, Direction::Vertical, /*length=*/3));
    CHECK("abxd" == board.read(100,200, Direction::Horizontal, 4));
}