#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

#include "ChessBoard.hpp"

int main() {

    // Test outputting White Pawn.
    Pawn p = Pawn(White);
    stringstream ss;
    ss << p;
    assert(ss.str() == "\u2659");
    ss.str("");

    // Test outputting ChessSquare A1.
    ChessSquare cs('A', 1);
    ss << cs;
    assert(ss.str() == "A1");

    // Create ChessBoard
    ChessBoard cb;

    Board board = cb.getBoard();
    // Test printing initialised board.
    cb.print();

    // Test moving Pawn E2 to E3.
    cb.submitMove("E2","E3");
    cb.print();

    return 0;
}
