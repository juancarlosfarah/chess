// ==========================================
// File:    Settings.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================
// This file runs a series of tests for
// the chess program that ensure that it is
// running correctly.

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
    cb.submitMove("E2","E4");
    cb.print();

    // Test moving Black Pawn E7 to E6.
    cb.submitMove("E7","E6");
    cb.print();

    // Test moving White Bishop F1 to C4.
    cb.submitMove("F1","C4");
    cb.print();

    // Test that Black's KingTracker is unchanged
    ChessSquare bkt = cb.getKingSquare(Black);
    assert(bkt == cb.getKingStartSquare(Black));

    // Test moving White Bishop back to F1.
    // Should fail because out of turn play.
    cb.submitMove("C4","F1");

    // Test moving Black Pawn A7 to B6.
    // Should fail because pawns can only move to
    // diagonally adjacent square when attacking.
    cb.submitMove("A7","B6");

    // Test moving Black Knight B8 to C6.
    cb.submitMove("B8","C6");

    // Test moving White Bishop C4 to C5.
    // Should fail because Bishop can't move vertically.
    cb.submitMove("C4","C5");

    // Test moving White King E1 to E2.
    cb.submitMove("E1","E2");
    cb.print();

    // Test that White's KingTracker is updated
    ChessSquare wkt = cb.getKingSquare(White);
    assert(wkt == ChessSquare("E2"));

    // Test moving Black Bishop F8 to A3.
    cb.submitMove("F8","A3");
    cb.print();

    // Test moving White Queen D1 to C1.
    // Should fail because there is a White piece in C1.
    cb.submitMove("D1","C1");

    // Test moving White Queen D1 to H5.
    // Should fail because the White King is in the way.
    cb.submitMove("D1","H5");

    // Test moving White Queen D1 to E1.
    cb.submitMove("D1","E1");
    cb.print();

    // Test moving Black Queen D8 to E7.
    cb.submitMove("D8","E7");
    cb.print();

    // Test moving White Queen H5 to E3.
    // Should fail because of invalid move dynamics.
    cb.submitMove("H5","E3");

    // Test moving White Pawn F2 to G3.
    // Should fail because pawns can only move to
    // diagonally adjacent square when attacking.
    cb.submitMove("F2","G3");

    // Test moving White Knight B1 to A5.
    // Should fail because of invalid move dynamics.
    cb.submitMove("B1","A5");

    // Test moving White Knight B1 to A3, taking
    // Black Bishop. Ensure Black Bishop is left
    // with a nullptr square property.
    ChessSquare squareWithBishop("A3");
    ChessPiece* bishop = cb.getBoard()[squareWithBishop];
    cb.submitMove("B1","A3");
    cb.print();
    assert(bishop->getSquare() == nullptr);

    // Test moving Black Queen E7 to A3, taking
    // White Knight. Ensure White Knight is left
    // with a nullptr square property.
    ChessSquare squareWithKnight("A3");
    ChessPiece* knight = cb.getBoard()[squareWithKnight];
    cb.submitMove("E7","A3");
    cb.print();
    assert(knight->getSquare() == nullptr);

    // Test moving White Knight G1 to H3.
    cb.submitMove("G1","H3");
    cb.print();

    // Test moving Black Queen A3 to A6.
    cb.submitMove("A3","A6");
    cb.print();

    // Test moving White Bishop C4 to D5.
    // Should fail because of revealed check.
    cb.submitMove("C4","D5");

    // Test moving White Bishop C4 to D3.
    cb.submitMove("C4","D3");
    cb.print();

    // Test moving Black Queen A6 to D3,
    // taking White Bishop. Ensure White
    // Bishop is left with a nullptr square.
    ChessSquare wbs("D3");
    ChessPiece* wb = cb.getBoard()[wbs];
    cb.submitMove("A6","D3");
    cb.print();
    assert(wb->getSquare() == nullptr);

    // Test moving White King E2 to F1.
    // Should fail because King still in check.
    cb.submitMove("E2","F1");

    // Test moving White King E2 to D1.
    cb.submitMove("E2","D1");
    cb.print();

    // Test moving Black Queen D3 to D4.
    cb.submitMove("D3","D4");
    cb.print();

    // Test moving White King D1 to E2.
    cb.submitMove("D1","E2");
    cb.print();

    // Test moving Black Queen D4 to D3.
    cb.submitMove("D4","D3");
    cb.print();

    // Test moving White Pawn C2 to D3,
    // taking Black Queen. Ensure Black
    // Queen is left with a nullptr square.
    ChessSquare bqs("D3");
    ChessPiece* bq = cb.getBoard()[bqs];
    cb.submitMove("C2","D3");
    cb.print();
    assert(bq->getSquare() == nullptr);

    // Test moving Black Pawn F7 to E6.
    cb.submitMove("F7","E6");
    cb.print();

    // Test moving Black Rook H8 to H1.
    // This ensures that pieces cannot
    // wrap around the board.
    cb.submitMove("H8","H1");
    cb.print();

    // Test moving Black Bishop C8 to H3.
    // This ensures that pieces cannot
    // wrap around the board.
    cb.submitMove("C8","H3");
    cb.print();

    // Reset Board
    cb.resetBoard();

    // Stalemate Test
    // ==============
    // Test stalemate based on fastest known stalemate.
    cout << endl;
    cout << "Testing stalemate..." << endl;
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

    // Checkmate Test 1
    // ================
    cout << endl;
    cout << "Testing checkmate..." << endl;
    cb.resetBoard();
    cb.submitMove("A2","A4");
    cb.submitMove("D7","D5");
    cb.submitMove("A1","A3");
    cb.submitMove("D8","D6");
    cb.submitMove("B1","C3");
    cb.submitMove("C8","G4");
    cb.submitMove("A3","B3");
    cb.submitMove("G7","G6");
    cb.submitMove("E7","E5");
    cb.submitMove("F2","F4");
    cb.submitMove("E7","E5");
    cb.submitMove("D2","D4");
    cb.submitMove("F8","E6");
    cb.submitMove("F8","E7");
    cb.submitMove("E2","E4");
    cb.submitMove("E7","H4");
    cb.submitMove("G2","G3");
    cb.submitMove("D6","C6");
    cb.submitMove("H2","H3");
    cb.submitMove("H4","H3");
    cb.submitMove("H4","G3");
    cb.submitMove("E1","D2");
    cb.submitMove("C6","C4");
    cb.submitMove("A4","A5");
    cb.submitMove("C4","D4");
    cb.submitMove("F1","D3");
    cb.submitMove("B8","C6");
    cb.submitMove("C3","D5");
    cb.submitMove("C6","B4");
    cb.submitMove("F4","F5");
    cb.submitMove("B4","E4");
    cb.submitMove("B4","D3");
    cb.submitMove("B3","B6");
    cb.submitMove("D3","C1");
    cb.submitMove("D2","D1");
    cb.submitMove("D2","C1");
    cb.submitMove("A7","B6");
    cb.submitMove("D5","C7");
    cb.submitMove("D4","D1");
    cb.submitMove("E8","E7");
    cb.submitMove("D4","D1");
    cb.submitMove("A5","B6");
    cb.submitMove("D4","D1");

    // Checkmate Test 2
    // ================
    cout << endl;
    cout << "Testing checkmate..." << endl;
    cb.resetBoard();
    cb.submitMove("E2","E4");
    cb.submitMove("F7","F5");
    cb.submitMove("F1","B5");
    cb.submitMove("D7","D6");
    cb.submitMove("F5","E4");
    cb.submitMove("B8","C6");
    cb.submitMove("D1","H5");
    cb.submitMove("B8","C6");
    cb.submitMove("B8","C6");
    cb.submitMove("B8","A6");
    cb.submitMove("G7","G6");
    cb.submitMove("H2","H4");
    cb.submitMove("G8","H6");
    cb.submitMove("H1","H3");
    cb.submitMove("B8","C6");
    cb.submitMove("D7","D5");
    cb.submitMove("A2","A4");
    cb.submitMove("D7","D5");
    cb.submitMove("A2","A4");
    cb.submitMove("D7","D5");
    cb.submitMove("C2","C4");
    cb.submitMove("D5","C4");
    cb.submitMove("D2","D4");
    cb.submitMove("C1","G5");
    cb.submitMove("E7","E5");
    cb.submitMove("D4","D5");
    cb.submitMove("H6","G8");
    cb.submitMove("D5","C6");
    cb.submitMove("C1","G5");
    cb.submitMove("A8","B8");
    cb.submitMove("C6","B7");
    cb.submitMove("C8","D7");
    cb.submitMove("H3","G3");
    cb.submitMove("B8","A8");
    cb.submitMove("G3","G6");
    cb.submitMove("G8","H6");
    cb.submitMove("G6","E6");

    // Checkmate Test 3
    // ================
    cout << endl;
    cout << "Testing checkmate..." << endl;
    cb.resetBoard();
    cb.submitMove("E2","E4");
    cb.submitMove("E7","E5");
    cb.submitMove("F1","C4");
    cb.submitMove("A7","A5");
    cb.submitMove("D1","H5");
    cb.submitMove("H7","H6");
    cb.submitMove("H5","F7");

    // This move should not be allowed
    // as the game is now over.
    cb.submitMove("C7","C5");

    // Testing Revealed Check
    // ======================
    cout << endl;
    cout << "Testing revealed check..." << endl;
    cb.resetBoard();
    cb.submitMove("E2","E4");
    cb.submitMove("D7","D6");
    cb.submitMove("D1","G4");
    cb.submitMove("A7","A6");
    cb.submitMove("F2","F4");
    cb.submitMove("A6","A5");
    cb.submitMove("F4","F5");
    cb.submitMove("E8","D7");
    cb.submitMove("F5","F6");

    // Replay opening of Lopez and da Cutri (1560)
    // ===========================================
    cout << endl;
    cout << "Replaying opening of Lopez vs da Cutri..." << endl;
    cb.resetBoard();
    cb.submitMove("E2","E4");
    cb.submitMove("E7","E5");
    cb.submitMove("G1","F3");
    cb.submitMove("F7","F6");
    cb.submitMove("F3","E5");
    cb.submitMove("F6","E5");
    cb.submitMove("D1","H5");
    cb.submitMove("G7","G6");
    cb.submitMove("H5","E5");
    cb.submitMove("H5","E5");
    cb.submitMove("D8","E7");
    cb.submitMove("E5","H8");
    cb.submitMove("G8","F6");
    cb.submitMove("D2","D4");
    cb.submitMove("E8","F7");
    cb.submitMove("F1","C4");
    cb.submitMove("D7","D5");
    cb.submitMove("C4","D5");
    cb.submitMove("F6","D5");
    cb.print();

    // Hippopotamus Mate
    // =================
    cout << endl;
    cout << "Testing the Hippopotamus Mate..." << endl;
    cb.resetBoard();
    cb.submitMove("E2","E4");
    cb.submitMove("E7","E5");
    cb.submitMove("G1","E2");
    cb.submitMove("D8","H4");
    cb.submitMove("B1","C3");
    cb.submitMove("B8","C6");
    cb.submitMove("G2","G3");
    cb.submitMove("H4","G5");
    cb.submitMove("D2","D4");
    cb.submitMove("C6","D4");
    cb.submitMove("C1","G5");
    cb.submitMove("D4","F3");
    cb.print();

    return 0;
}
