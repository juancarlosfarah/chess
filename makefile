OBJ = ChessBoard.o ChessSet.o ChessPiece.o ChessSquare.o ChessMain.o
EXE = chess
INC = *.d
GCC = g++
CFLAGS = -Wall -g -MMD -std=c++11

$(EXE): $(OBJ)
	$(GCC) $(CFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(GCC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(INC) $(EXE)
