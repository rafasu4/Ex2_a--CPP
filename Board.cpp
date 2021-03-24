#include "Board.hpp"

namespace ariel
{

    std::string Board::read(unsigned int row, unsigned int col, Direction d, int length)
    {
        if (length < 0)
        {
            throw std::logic_error("length of a word cann't be negative!");
        }
        string ans = "";

        if(d == Direction::Horizontal){
            
            ans = readH(row, col, length);
        }
        else{
            for(unsigned int i = 0; i < length; i++){
                ans += readV(row + i, col);
            }
            
        }
        
        return ans;
    }

    void Board::post(unsigned int row, unsigned int col, Direction d, std::string s)
    {
        //if the string is empty - nothing to be changed
        if (s == "")
            return;
        if (d == Direction::Horizontal)
        {
            if (messageBoard.count(row))
            {
                updateH(row, col, s);
            }
            else
            {
                pair<unsigned int, vector<char>> newRow = pair<unsigned int, vector<char>>();
                newRow.first = col;
                for (char c : s)
                {
                    newRow.second.push_back(c);
                }
                messageBoard[row] = newRow;
            }
        }
        //if the direction is vertical
        else
        {
            string::iterator it;
            unsigned int i = 0;
            for (it = s.begin(); it < s.end(); it++)
            {
                if (messageBoard.count(row + i))
                {
                    updateV(row + i, col, *it);
                }

                else
                {
                    pair<unsigned int, vector<char>> newPair = pair<unsigned int, vector<char>>();
                    newPair.first = col;
                    newPair.second.push_back(*it);
                    messageBoard[row + i] = newPair;
                }
                i++;
            }
        }
    }

}

void Board::show()
{
    map<unsigned int, pair<unsigned int, vector<char>>>::iterator it = messageBoard.begin();
    for (pair<unsigned int, pair<unsigned int, vector<char>>> it : messageBoard)
    {
        vector<char> line = it.second.second;
        for (char c : line)
        {
            cout << c;
        }
        cout << endl;
    }
}

void Board::updateH(unsigned int row, unsigned int col, string s)
{
    pair<unsigned int, vector<char>> currentLine = messageBoard[row];
    unsigned int startOfPost = currentLine.first;
    //In case the given post starts before the current post - updating the start in pair
    if (col < startOfPost)
    {
        vector<char> newPost = vector<char>();
        for (char c : s)
        {
            newPost.push_back(c);
        }
        unsigned int oldPostStart = col + s.length();
        //if there is a space between the two posts
        if (oldPostStart < currentLine.first)
        {
            while (oldPostStart < currentLine.first)
            {
                newPost.push_back('-');
            }
            for (char c : currentLine.second)
            {
                newPost.push_back(c);
            }
        }
        //if there is an overlap
        else
        {
            for (unsigned int i = oldPostStart - currentLine.first; i < currentLine.second.size(); i++)
            {
                newPost.push_back(currentLine.second.at(i));
            }
            pair<unsigned int, vector<char>> updatedLine = pair<unsigned int, vector<char>>();
            updatedLine.first = col;
            updatedLine.second = newPost;
            messageBoard[row] = updatedLine;
        }
    }

    else
    {
        unsigned int i = startOfPost + currentLine.second.size();
        unsigned int updatedCol = col;
        vector<char> updated = vector<char>();
        for (char c : currentLine.second)
        {
            updated.push_back(c);
        }
        if (i < col)
        {
            //adding spaces
            while (i < col)
            {
                updated.push_back('-');
                i++;
            }
            for (char c : s)
            {
                updated.push_back(c);
            }
            pair<unsigned int, vector<char>> updatedPair = {currentLine.first, updated};
            messageBoard[row] = updatedPair;
        }
        //if ther's an overlap
        else
        {
            unsigned int index = col - startOfPost;
            for (unsigned int i = 0; i < s.length(); i++)
            {
                if (index < updated.size())
                {
                    updated.at(index) = s.at(i);
                }
                else
                {
                    updated.push_back(s.at(i));
                }
                index++;
            }
            pair<unsigned int, vector<char>> updatedPair = {currentLine.first, updated};
            messageBoard[row] = updatedPair;
        }
    }
}

void Board::updateV(unsigned int row, unsigned int col, char c)
{
    pair<unsigned int, vector<char>> currentLine = messageBoard[row];
    unsigned int startOfPost = currentLine.first;
    vector<char> currentPost = currentLine.second;
    vector<char> updatedPost = vector<char>();
    unsigned int sizeOfCurrentPost = currentPost.size();
    if (startOfPost <= col && col <= startOfPost + sizeOfCurrentPost)
    {
        for(char c: currentPost){
            updatedPost.push_back(c);
        }
        updatedPost.at(col - startOfPost) = c;
        messageBoard[row] = {col, updatedPost};
    }
    else
    {
        if (col < startOfPost)
        {
            updatedPost.push_back(c);
            unsigned int newCol = col;
            while (newCol < startOfPost)
            {
                updatedPost.push_back('-');
                newCol++;
            }
            for (char ch : currentPost)
            {
                updatedPost.push_back(ch);
            }
            messageBoard[row] = {col,updatedPost };
        }
        else
        {
            for(char c: currentPost){
                updatedPost.push_back(c);
            }
            unsigned int newStartOfPost = startOfPost;
            while(newStartOfPost < col){
            updatedPost.push_back('-');
            newStartOfPost++;
            }
            updatedPost.push_back(c);
            messageBoard[row] = {startOfPost, updatedPost};
        }
    }
}

string Board::readH(unsigned int row, unsigned int col, int length){
    string ans = "";
        if (!messageBoard.count(row))
        {
            for (int i = 0; i < length; i++)
            {
                ans += '-';
            }
        }
        else
        {
            pair<unsigned int, vector<char>> line = messageBoard[row];
            if (col < line.first)
            {
                unsigned int i = 0;
                while (col < line.first)
                {
                    ans += '-';
                    col++;
                    i++;
                }
                if (i < length)
                {
                    unsigned int j = 0;
                    for (; i < length; i++)
                    {
                        if (j >= line.second.size())
                        {
                            ans += '-';
                        }
                        else
                        {
                            ans += line.second.at(j);
                            j++;
                        }
                    }
                }
            }
            else
            {
                unsigned int j = line.first + line.second.size();
                if (col > j)
                {
                    for (int i = 0; i < length; i++)
                    {
                        ans += '-';
                    }
                }
                else
                {

                    unsigned int startRead = col - line.first;
                     for (unsigned int i = 0; i < length; i++)
                     {
                        if (startRead > line.second.size)
                        {
                            ans += '-';
                        }
                    //     else
                    //     {
                    //         ans += line.second.at(startRead);
                    //     }
                    //     startRead++;
                    // }
                }
            }
        }
        return ans;
}

char Board::readV(unsigned int row, unsigned int col){
    if(messageBoard.count(row)){
        pair<unsigned int, vector<char> > currentLine = messageBoard[row];
        if(currentLine.first <= col && col <= currentLine.first + currentLine.second.size()){
            return currentLine.second.at(col - currentLine.first);
        }
        else{
            return '-';
        }
    }
    else{
        return  '-';
    }

}