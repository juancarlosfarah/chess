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

    // Test moving White Pawn E2 to E4.
    isValid = cb.submitMove("E2","E4");
    assert(isValid == true);
    cb.print();

    // Test moving Black Pawn E7 to E4.
    isValid = cb.submitMove("E7","E5");
    assert(isValid == true);
    cb.print();

    // Test moving White Bishop F1 to C4.
    isValid = cb.submitMove("F1","C4");
    assert(isValid == true);
    cb.print();

    // Test moving White Bishop back to F1.
    // Should fail because out of turn play.
    isValid = cb.submitMove("C4","F1");
    assert(isValid == false);

    // Test moving Black Pawn A7 to B6.
    // Should fail because pawns can only move to
    // diagonally adjacent square when attacking.
    isValid = cb.submitMove("A7","B6");
    assert(isValid == false);

    // Test moving Black Knight B8 to C6.
    isValid = cb.submitMove("B8","C6");
    assert(isValid == true);
    cb.print();

    // Test moving White Bishop C4 to C5.
    // Should fail because Bishop can't move vertically.
    isValid = cb.submitMove("C4","C5");
    assert(isValid == false);

    // Test moving White King E1 to E2.
    isValid = cb.submitMove("E1","E2");
    cb.print();
    assert(isValid == true);

    // Test moving Black Bishop F8 to A3.
    isValid = cb.submitMove("F8","A3");
    cb.print();
    assert(isValid == true);

    // Test moving White Queen D1 to C1.
    // Should fail because there is a White piece in C1.
    isValid = cb.submitMove("D1","C1");
    assert(isValid == false);

    // Test moving White Queen D1 to H5.
    isValid = cb.submitMove("D1","H5");
    cb.print();
    assert(isValid == true);

    // Test moving Black Queen D8 to E7.
    isValid = cb.submitMove("D8","E7");
    cb.print();
    assert(isValid == true);

    // Test moving White Queen H5 to E3.
    // Should fail because of invalid move dynamics.
    isValid = cb.submitMove("H5","E3");
    assert(isValid == false);

    // Test moving White Pawn F2 to G3.
    // Should fail because pawns can only move to
    // diagonally adjacent square when attacking.
    isValid = cb.submitMove("F2","G3");
    assert(isValid == false);

    // Test moving White Knight B1 to A5.
    // Should fail because of invalid move dynamics.
    isValid = cb.submitMove("B1","A5");
    assert(isValid == false);

    // Test moving White Knight B1 to A3, taking
    // Black Bishop. Ensure Black Bishop is left
    // with a nullptr square property.
    ChessSquare squareWithBishop("A3");
    ChessPiece* bishop = cb.getBoard()[squareWithBishop];
    isValid = cb.submitMove("B1","A3");
    cb.print();
    assert(bishop->getSquare() == nullptr);
    assert(isValid == true);

    // Test moving Black Queen E7 to A3, taking
    // White Knight. Ensure White Knight is left
    // with a nullptr square property.
    ChessSquare squareWithKnight("A3");
    ChessPiece* knight = cb.getBoard()[squareWithKnight];
    isValid = cb.submitMove("E7","A3");
    cb.print();
    assert(knight->getSquare() == nullptr);
    assert(isValid == true);

    return 0;
}
