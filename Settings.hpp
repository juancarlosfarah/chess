// ==========================================
// File:    Settings.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================
// This file defines all of the constants used
// by default for a game of chess. It follows
// standard guidelines for notation.

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// Board
// =====
// These constants define the board's dimensions.
// Following these guidelines, the board will
// always be square, which is in line with chess.
const int SIDE_LEN = 8;
const char LEFTMOST_FILE = 'A';
const char RIGHTMOST_FILE = LEFTMOST_FILE + SIDE_LEN - 1;
const int BOTTOM_RANK = 1;
const int TOP_RANK = BOTTOM_RANK + SIDE_LEN - 1;
const int NUM_SQUARES = SIDE_LEN * SIDE_LEN;

// Set
// ===
const int PIECES_PER_SIDE = 16;

// Pawns
// =====
const int T_PAWNS = 7;
const int B_PAWNS = 2;

// Knights
// =======
const char L_KNIGHT = 'B';
const char R_KNIGHT = 'G';

// Bishops
// =======
const char L_BISHOP = 'C';
const char R_BISHOP = 'F';

// Rooks
// =====
const char L_ROOK = 'A';
const char R_ROOK = 'H';

// Queen
// =====
const char QUEEN = 'D';

// King
// ====
const char KING = 'E';
const string WHITE_KING = "E1";
const string BLACK_KING = "E8";

// Formatting
// ==========
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
