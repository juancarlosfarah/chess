#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
using namespace std;

#include "ChessBoard.hpp"

int main() {

    // Test outputting White Pawn.
    cout << "Testing outputting White Pawn..." << endl;
    Pawn p = Pawn(White);
    stringstream ss;
    ss << p;
    assert(ss.str() == "\u2659");
    ss.str("");

    // Test outputting ChessSquare A1.
    cout << "Testing outputting A1..." << endl;
    ChessSquare cs('A', 1);
    ss << cs;
    assert(ss.str() == "A1");
    ss.str("");

    // Test case insensitivity for ChessSquare.
    cout << "Testing constructing square h8..." << endl;
    ChessSquare cs0("h8");
    ss << cs0;
    assert(ss.str() == "H8");
    ss.str("");

    // ==============
    // Test Distances
    // ==============
    cout << "Testing distances..." << endl;
    ChessSquare cs1('A', 5);
    ChessSquare cs2('C', 4);
    ChessSquare cs3('C', 5);
    ChessSquare cs4('A', 2);
    ChessSquare cs5('B', 7);
    ChessSquare cs6('D', 3);
    ChessSquare cs7('E', 4);
    ChessSquare cs8('F', 5);
    ChessSquare cs9('H', 1);
    ChessSquare cs10('A', 8);
    assert(cs1.distance(cs2) == 1);
    assert(cs2.distance(cs3) == 0);
    assert(cs1.distance(cs3) == 1);
    assert(cs1.distance(cs4) == 2);
    assert(cs7.distance(cs10) == 3);
    assert(cs8.distance(cs7) == 0);
    assert(cs8.distance(cs6) == 1);
    assert(cs4.distance(cs8) == 4);
    assert(cs9.distance(cs10) == 6);
    assert(cs5.distance(cs9) == 5);
    assert(cs5.distance(cs8) == 3);


    // Create ChessBoard
    cout << "Testing creating ChessBoard..." << endl;
    ChessBoard cb;

    Board board = cb.getBoard();
    // Test printing initialised board.
    cb.print();

    // ===================
    // Test Piece Dynamics
    // ===================
    bool isValid;

    cout << "Testing ChessPiece dynamics..." << endl;
    // Test if in theory Black Pawn can move E7 to D1.
    // Should fail given a Pawn's allowed moves.
    ChessSquare s1 = ChessSquare("D7");
    ChessSquare d1 = ChessSquare("E1");
    Pawn bp(Black, s1);
    isValid = bp.isPossibleMove(d1, nullptr).first;
    assert(isValid == false);

    // Test if in theory Black Pawn can move E7 to D1.
    // if there is an opponent on D1. Should fail given
    // a Pawn's allowed moves.
    King wk(White, d1);
    isValid = bp.isPossibleMove(d1, &wk).first;
    assert(isValid == false);

    // ==========
    // Test Moves
    // ==========
    cout << "Testing moves..." << endl;

    // Test moving White Pawn E2 to E4.
    isValid = cb.submitMove("E2","E4");
    assert(isValid == true);
    cb.print();

    // Test moving Black Pawn E7 to E6.
    isValid = cb.submitMove("E7","E6");
    assert(isValid == true);
    cb.print();

    // Test moving White Bishop F1 to C4.
    isValid = cb.submitMove("F1","C4");
    assert(isValid == true);
    cb.print();

    // Test that Black's KingTracker is unchanged
    ChessSquare bkt = cb.getKingSquare(Black);
    assert(bkt == cb.getKingStartSquare(Black));

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

    // Test that White's KingTracker is updated
    ChessSquare wkt = cb.getKingSquare(White);
    assert(wkt == ChessSquare("E2"));

    // Test moving Black Bishop F8 to A3.
    isValid = cb.submitMove("F8","A3");
    cb.print();
    assert(isValid == true);

    // Test moving White Queen D1 to C1.
    // Should fail because there is a White piece in C1.
    isValid = cb.submitMove("D1","C1");
    assert(isValid == false);

    // Test moving White Queen D1 to H5.
    // Should fail because the White King is in the way.
    isValid = cb.submitMove("D1","H5");
    assert(isValid == false);

    // Test moving White Queen D1 to E1.
    isValid = cb.submitMove("D1","E1");
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

    // Test moving White Knight G1 to H3.
    isValid = cb.submitMove("G1","H3");
    cb.print();
    assert(isValid == true);

    // Test moving Black Queen A3 to A6.
    isValid = cb.submitMove("A3","A6");
    cb.print();
    assert(isValid == true);

    // Test moving White Bishop C4 to D5.
    // Should fail because of revealed check.
    isValid = cb.submitMove("C4","D5");
    assert(isValid == false);

    // Test moving White Bishop C4 to D3.
    isValid = cb.submitMove("C4","D3");
    cb.print();
    assert(isValid == true);

    // Test moving Black Queen A6 to D3,
    // taking White Bishop. Ensure White
    // Bishop is left with a nullptr square.
    ChessSquare wbs("D3");
    ChessPiece* wb = cb.getBoard()[wbs];
    isValid = cb.submitMove("A6","D3");
    cb.print();
    assert(wb->getSquare() == nullptr);
    assert(isValid == true);

    // Test moving White King E2 to F1.
    // Should fail because King still in check.
    isValid = cb.submitMove("E2","F1");
    assert(isValid == false);

    // Test moving White King E2 to D1.
    isValid = cb.submitMove("E2","D1");
    cb.print();
    assert(isValid == true);

    // Test moving Black Queen D3 to D4.
    isValid = cb.submitMove("D3","D4");
    cb.print();
    assert(isValid == true);

    // Test moving White King D1 to E2.
    isValid = cb.submitMove("D1","E2");
    cb.print();
    assert(isValid == true);

    // Test moving Black Queen D4 to D3.
    isValid = cb.submitMove("D4","D3");
    cb.print();
    assert(isValid == true);

    // Test moving White Pawn C2 to D3,
    // taking Black Queen. Ensure Black
    // Queen is left with a nullptr square.
    ChessSquare bqs("D3");
    ChessPiece* bq = cb.getBoard()[bqs];
    isValid = cb.submitMove("C2","D3");
    cb.print();
    assert(bq->getSquare() == nullptr);
    assert(isValid == true);

    // Test moving White Pawn F7 to E6.
    isValid = cb.submitMove("F7","E6");
    cb.print();
    assert(isValid == false);

    // Reset Board
    cb.resetBoard();

    // Test Stalemate based on fastest known stalemate.
    cb.submitMove("E2","E3");
    cb.submitMove("A7","A5");
    cb.submitMove("D1","H5");
    cb.submitMove("A8","A6");
    cb.submitMove("H5","A5");
    cb.submitMove("H7","H5");
    cb.submitMove("H2","H4");
    cb.submitMove("A6","H6");
    cb.submitMove("A5","C7");
    cb.submitMove("F7","F6");
    cb.submitMove("C7","D7");
    cb.submitMove("E8","F7");
    cb.submitMove("D7","B7");
    cb.submitMove("D8","D3");
    cb.submitMove("B7","B8");
    cb.submitMove("D3","H7");
    cb.submitMove("B8","C8");
    cb.submitMove("F7","G6");
    cb.submitMove("C8","E6");

    return 0;
}
