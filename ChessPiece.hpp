// ==========================================
// File:    ChessPiece.hpp
// Author:  Juan Carlos Farah
// Email:   juancarlos.farah14@imperial.ac.uk
// ==========================================

#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include <iostream>
#include <string>
using namespace std;

#include "ChessSquare.hpp"

// Enum: Color
// ===========
// In each game of chess there are two sides, White
// and Black. These are represented by this enum.
enum Color {White, Black};

// Class: ChessPiece
// =================
// This class defines the data members and methods of the ChessPiece,
// which serves as a superclass for every type of ChessPiece used in
// a game of chess. This class defines how a ChessPiece can move, the
// name and symbol it is given, as well as its Color (indicating its
// side) and the ChessSquare it is currently on.
class ChessPiece {

    private:

        // Method: initSymbol
        // ==================
        // This method initialises the symbol property
        // of the ChessPiece given its Color.
        void initSymbol(Color color);

    protected:

        Color color;        // Color
        string name;        // English name.
        string symbol;      // Unicode symbol.

        // This points to the ChessSquare this ChessPiece
        // is currently on. If the piece has been captured,
        // it will be a nullptr.
        ChessSquare* square;

    public:

        // Constructor:
        // ============
        ChessPiece();                           // Default
        ChessPiece(const ChessPiece& other);    // Copy

        // Constructor:
        // ============
        // This constructor takes a Color and creates
        // a ChessPiece object of that Color.
        ChessPiece(Color color);

        // Constructor:
        // ============
        // This constructor takes a Color and a ChessSquare and
        // constructs a ChessPiece of that Color and sets its
        // square property to point to the given ChessSquare.
        ChessPiece(Color color, const ChessSquare& square);

        // Destructor:
        // ===========
        virtual ~ChessPiece();

        // Method: setSquare
        // =================
        // Takes a ChessSquare, creates a copy of it and sets a
        // pointer to it as the square attribute of this ChessPiece.
        void setSquare(ChessSquare& square);

        // Method: setSquare
        // =================
        // Takes a pointer to a ChessSquare and sets it
        // as the square property of this ChessPiece.
        void setSquare(ChessSquare* square);

        // Method: getSquare
        // =================
        // Returns the square attribute of this ChessPiece.
        ChessSquare* getSquare();

        // Method: isPossibleMove
        // ======================
        // This method takes a ChessSquare and a pointer to the ChessPiece
        // in that ChessSquare (or nullptr if its empty), and returns a
        // pair of booleans. The first bool indicates if the move is
        // possible given the rules of movement of each piece. The second
        // bool is true if the move requires the piece to go through one
        // or more squares. This indicates if the move needs to be checked
        // further by the ChessBoard for any potential obstructions. This
        // method is virtual and is overriden by each individual subclass.
        virtual pair<bool, bool> isPossibleMove(ChessSquare& square,
                                                ChessPiece* piece) const;

        // Method: getColor
        // ================
        // This method returns the color property of the ChessPiece.
        Color getColor() const;

        // Method: getSymbol
        // =================
        // This method returns the symbol property of the ChessPiece.
        string getSymbol() const;

        // Method: getName
        // ================
        // This method returns the name property of the ChessPiece.
        string getName() const;

        // Method: print
        // =============
        // This method prints the symbol property of the ChessPiece.
        void print() const;

        // Operator: <<
        // ============
        // Outputs the symbol property of the ChessPiece operand.
        friend ostream& operator<<(ostream& os, const ChessPiece& piece);
};

// Operator: <<
// ============
// The insertion operator for the Color enum
// outputs the string name of the given Color.
ostream& operator <<(ostream& os, const Color& color);

// Operator: !
// ===========
// The negation operator for the Color enum
// returns the Color that is not the operand.
Color operator !(const Color& color);

#endif
