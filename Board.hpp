#include <iostream>
#include <vector>
#include <map>
#include "Direction.hpp"
using namespace ariel;
using namespace std;

namespace ariel{

class Board{

    public:
    std::map<unsigned int, pair<unsigned int, vector<char>> > messageBoard;

    
    public:
    Board(){ }
    std::string read(unsigned int row, unsigned int col, Direction d, int length );

    void post(unsigned int row, unsigned int col, Direction d, std::string s);

    void show();

    private:
    void updateH(unsigned int row, unsigned int col, string s);
    void updateV(unsigned int row, unsigned int col, char c);
    string readH(unsigned int row, unsigned int col, int length);
    char readV(unsigned int row, unsigned int col);
};
}