#pragma once
#include<vector>
using namespace std; 

struct Move {
	int oX, oY, X, Y; 
	Move() {}
	Move(int oldX, int oldY, int X, int Y); 
};

struct board{
    int a[8][8] = { {7, 6, -1, -1, -1, -1, 0, 1},
                     {8, 6, -1, -1, -1, -1, 0, 2},
                     {9, 6, -1, -1, -1, -1, 0, 3},
                     {11, 6, -1, -1, -1, -1, 0, 5},
                     {10, 6, -1, -1, -1, -1, 0, 4},
                     {9, 6, -1, -1, -1, -1, 0, 3},
                     {8, 6, -1, -1, -1, -1, 0, 2},
                     {7, 6, -1, -1, -1, -1, 0, 1} };
};

class Board {
private : 
    bool turn = 1; 
    const char* notation(int x, int y); 
    vector <board> history; 
    void wPawn(std::vector<Move>& moves, int x, int y);
    void bPawn(std::vector<Move>& moves, int x, int y);
    void King(std::vector<Move>& moves, int x, int y);
    void Queen(std::vector<Move>& moves, int x, int y);
    void Rook(std::vector<Move>& moves, int x, int y);
    void Bishop(std::vector<Move>& moves, int x, int y);
    void Knight(std::vector<Move>& moves, int x, int y);
    vector<Move> getLegalMoves(board b, bool color);
public: 
    board myBoard; 
    bool playMove(Move req); 
    bool nextTurn(); 
};