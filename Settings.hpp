// ==========================================
// File:    Settings.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================
// This file defines all of the constants used
// by default for a game of chess. It follows
// standard guidelines for chess notation.

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// Constants: Board
// ================
// These constants define the board's dimensions.
// Following these guidelines, the board will
// always be square, which is in line with chess.
const int SIDE_LEN = 8;
const char LEFTMOST_FILE = 'A';
const char RIGHTMOST_FILE = LEFTMOST_FILE + SIDE_LEN - 1;
const int BOTTOM_RANK = 1;
const int TOP_RANK = BOTTOM_RANK + SIDE_LEN - 1;
const int NUM_SQUARES = SIDE_LEN * SIDE_LEN;

// Constants: Set
// ==============
const int PIECES_PER_SIDE = 16;
const string CHESS_PIECE_NAME = "Piece";
const string WHITE_SYMBOL = "W";
const string BLACK_SYMBOL = "B";

// Constants: Pawns
// ================
const int BLACK_PAWNS = 7;
const int WHITE_PAWNS = 2;
const string WHITE_PAWN = "\u2659";
const string BLACK_PAWN = "\u265F";
const string PAWN_NAME = "Pawn";

// Constants: Knights
// ==================
const char L_KNIGHT = 'B';
const char R_KNIGHT = 'G';
const string WHITE_KNIGHT = "\u2658";
const string BLACK_KNIGHT = "\u265E";
const string KNIGHT_NAME = "Knight";

// Constants: Bishops
// ==================
const char L_BISHOP = 'C';
const char R_BISHOP = 'F';
const string WHITE_BISHOP = "\u2657";
const string BLACK_BISHOP = "\u265D";
const string BISHOP_NAME = "Bishop";

// Constants: Rooks
// ================
const char L_ROOK = 'A';
const char R_ROOK = 'H';
const string WHITE_ROOK = "\u2656";
const string BLACK_ROOK = "\u265C";
const string ROOK_NAME = "Rook";

// Constants: Queen
// ================
const char QUEEN = 'D';
const string WHITE_QUEEN = "\u2655";
const string BLACK_QUEEN = "\u265B";
const string QUEEN_NAME = "Queen";

// Constants: King
// ===============
const char KING = 'E';
const string WHITE_KING = "\u2654";
const string BLACK_KING = "\u265A";
const string KING_NAME = "King";
const string WHITE_KING_SQUARE = "E1";
const string BLACK_KING_SQUARE = "E8";

// Constants: Formatting
// =====================
// This constants are used to print out the ChessBoard
// onto the console using nicely formatted Unicode.
const string LONG_BAR = "\u2500\u2500\u2500";
const string VERTICAL_BAR = "\u2502";
const string LEFT_JOIN = "\u251C";
const string RIGHT_JOIN = "\u2524";
const string INNER_JOIN = "\u253C";
const string TOP_LEFT_CORNER = "\u250C";
const string TOP_JOIN = "\u252C";
const string TOP_RIGHT_CORNER = "\u2510";
const string BOTTOM_LEFT_CORNER = "\u2514";
const string BOTTOM_RIGHT_CORNER = "\u2518";
const string BOTTOM_JOIN = "\u2534";
const string SMALL_SPACE = " ";
const string MEDIUM_SPACE = "  ";
const string LARGE_SPACE = "   ";

#endif
