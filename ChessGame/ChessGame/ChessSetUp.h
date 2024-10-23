#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Board.h"

using namespace sf; 

struct ChessPiece {
	Sprite shape; 
	int pieceID, x, y; 
	bool draw = 0; 
};


class ChessSetUp{
private: 
	RenderWindow win; 
	RectangleShape squares[8][8]; 
	IntRect Holder; 
	Color sColor[2]; 
	Texture pieceTex[12]; 
	SoundBuffer sBuffer[4]; 
	Sound sounds[4]; 
	ChessPiece pieces[64]; 

	Board cBoard; 
	int selected[2]; 
	bool cSelect = 0; 
	int sX, sY; 

	void FitToHolder();
	void DrawSquares();
	void DrawPieces();
	void MapPieces();
	void MapPieces(Move curr);
public: 
	ChessSetUp(int width, int height, const char* name, const char* imgPath[12], const char* soundsPath[4]);
	bool Update(); 
};
