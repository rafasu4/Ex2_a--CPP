#include "doctest.h"
#include "Board.hpp"

ariel::Board board;
TEST_CASE("compiling code"){
    Board board;
    //horizontal
    CHECK_NOTHROW(board.post(5, 5, Direction::Horizontal, ""));
	CHECK_NOTHROW(board.post(3, 0, Direction::Horizontal, "Hello!"));
	CHECK_NOTHROW(board.post(2, 0, Direction::Horizontal, "HelLo!"));
	CHECK_NOTHROW(board.post(1, 0, Direction::Horizontal, "1996"));
    //vertical
	CHECK_NOTHROW(board.post(5, 5, Direction::Vertical, ""));
	CHECK_NOTHROW(board.post(3, 0, Direction::Vertical, "Hello!"));
	CHECK_NOTHROW(board.post(2, 0, Direction::Vertical, "HelLo!"));
	CHECK_NOTHROW(board.post(1, 0, Direction::Vertical, "1996"));
}

TEST_CASE("working code"){
    Board board;
    board.post(/*row=*/0,/*column=*/0,Direction::Horizontal, "abcd");
    CHECK("abcd" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    CHECK("---" == board.read(/*row=*/2,/*column=*/2,Direction::Vertical, /*length=*/3));
    board.post(/*row=*/0,/*column=*/3,Direction::Horizontal, "x");
    CHECK("abcx" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    board.post(/*row=*/0,/*column=*/3,Direction::Vertical, "xy");
    CHECK("abcx" == board.read(/*row=*/0,/*column=*/0,Direction::Horizontal, /*length=*/4));
    CHECK("y" == board.read(/*row=*/1,/*column=*/3,Direction::Horizontal, /*length=*/1));
    CHECK("-y-" == board.read(/*row=*/1,/*column=*/2,Direction::Horizontal,/*length=*/3));
    board.post(/*row=*/100, /*column=*/200, Direction::Horizontal, "abcd");
    CHECK("abcd" == board.read(100,200, Direction::Horizontal, 4));
	board.post(/*row=*/100, /*column=*/202, Direction::Vertical, "xyzw");
	CHECK("-b-" == board.read(/*row=*/99, /*column=*/201, Direction::Vertical, /*length=*/3));
    CHECK("abxd" == board.read(100,200, Direction::Horizontal, 4));
    board.post(7,4,Direction::Vertical,"R");
    board.post(8,5,Direction::Vertical,"a");
    board.post(9,6,Direction::Vertical,"P");
    board.post(10,7,Direction::Vertical,"h");
    board.post(11,8,Direction::Vertical,"A");
    unsigned int i = 7;
    string ans;
    for (; i < 12; i++)
    {
        ans += board.read(i, i - 3, Direction::Vertical, 1);
    }
    
    CHECK("RaPhA" == ans);
    string empty;
    i = 7;
        for (; i < 12; i++)
    {
        board.post(i, i - 3, Direction::Vertical,"-" );
        empty += board.read(i, i - 3, Direction::Vertical, 1);
    }
    CHECK("-----" == empty);
}

TEST_CASE("throw exception"){
    CHECK_THROWS(board.read(10,10,Direction::Horizontal, -1));
}