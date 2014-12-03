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

    // ==========
    // Test Moves
    // ==========
    bool isValid;

    // Test moving Pawn E2 to E4.
    isValid = cb.submitMove("E2","E4");
    assert(isValid == true);
    cb.print();

    isValid = cb.submitMove("F1","C4");
    assert(isValid == true);
    cb.print();

    isValid = cb.submitMove("C4","C5");
    assert(isValid == false);

    isValid = cb.submitMove("E1","E2");
    cb.print();
    assert(isValid == true);

    isValid = cb.submitMove("E2","F3");
    cb.print();
    assert(isValid == true);

    isValid = cb.submitMove("F3","F5");
    assert(isValid == false);

    isValid = cb.submitMove("F3","F4");
    cb.print();
    assert(isValid == true);

    isValid = cb.submitMove("D1","H5");
    cb.print();
    assert(isValid == true);

    isValid = cb.submitMove("H5","E3");
    assert(isValid == false);

    isValid = cb.submitMove("F4","E4");
    assert(isValid == false);

    isValid = cb.submitMove("B1","A5");
    assert(isValid == false);

    isValid = cb.submitMove("B1","A3");
    cb.print();
    assert(isValid == true);

    return 0;
}
