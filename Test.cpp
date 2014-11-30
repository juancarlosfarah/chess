#include <iostream>
using namespace std;

#include "ChessBoard.hpp"

int main() {


    ChessBoard cb;

    map<ChessSquare, ChessPiece*> m = cb.getBoard();
    const ChessSquare* cs1_ptr = &(m.begin()->first);
    cout << cs1_ptr << endl;
    cout << (m.begin()->first).getRank() << (m.begin()->first).getFile() << endl;
    ChessSquare cs('A', 1);
    cout << "Address of ChessSquare on its own:" << endl;
    cout << &cs << endl;
    ChessPiece cp;
    m[cs] = &cp;
    const ChessSquare* cs2_ptr = &(m.begin()->first);
    cout << "Address of ChessSquare on in map: ";
    cout << cs2_ptr << endl;
    cout << "And its value: "; 
    cout << (m.begin()->first).getRank() << (m.begin()->first).getFile() << endl;
    cout << "Address of ChessSquare on its own: ";
    cout << &cs << endl;
    cout << "And its value: "; 
    cout << cs.getRank() << cs.getFile() << endl;
    cout << "Erasing entry from map." << endl;
    m.erase(cs);
    cout << "Now first ChessSquare in map is: ";
    cout << (m.begin()->first).getRank() << (m.begin()->first).getFile() << endl;
    const ChessSquare* cs3_ptr = &(m.begin()->first);
    cout << "And it's located at: ";
    cout << cs3_ptr << endl;
    cout << "And the address of ChessSquare on its own is: ";
    cout << &cs << endl;
    cout << "What happened to the address in the map from before? ";
    cout << cs2_ptr << endl;
    cout << "And its value? ";
    cout << cs2_ptr->getRank() << cs2_ptr->getFile() << endl;
    cout << "Can we delete it?" << endl;
// NO!    delete cs2_ptr;

    cout << "Printing Set" << endl;
    cb.getChessSet().print();

    cout << "Printing board!" << endl;
    cb.print();

    return 0;
}
