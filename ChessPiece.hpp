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

enum Color {White, Black};

class ChessPiece {

    private:
        // Method: initSymbol
        // ==================
        void initSymbol(Color color);

    protected:

        Color color;
        string name;
        string symbol;
        const ChessSquare* square;

    public:

        // Constructor:
        // ============
        ChessPiece();
        ChessPiece(Color color);
        ChessPiece(Color color, ChessSquare* square);

        // Copy Constructor:
        // =================
        //ChessPiece(ChessPiece& other);
        //TODO: IMPLEMENT!

        // Destructor:
        // ===========
        virtual ~ChessPiece();


        // Method: setSquare
        // =================
        // Takes a ChessSquare and sets it as the square
        // attribute of this ChessPiece.
        void setSquare(const ChessSquare* cs);

        // Method: getSquare
        // =================
        // Returns the square attribute of this ChessPiece.
        const ChessSquare* getSquare();

        // Method: print
        // =============
        void print();

        // Method: isPossibleMove
        // ======================
        virtual pair<bool, bool> isPossibleMove(const ChessSquare& square,
                                             ChessPiece* piece) const;

        // Method: getColor
        // ================
        Color getColor();

        // Method: getColor
        // ================
        virtual string getName();

        // Operator: <<
        // ============
        friend ostream& operator<<(ostream& os, ChessPiece piece);
};

// Operator: <<
// ============
// Define insertion operator for Color.
ostream& operator <<(ostream& os, const Color& color);

// Operator: <<
// ============
// Define insertion operator for Color.
Color operator !(const Color& color);

#endif
