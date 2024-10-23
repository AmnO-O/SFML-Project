#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ChessSetUp.h"

using namespace std; 
using namespace sf;

void ChessSetUp::FitToHolder() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			squares[i][j].setPosition(sf::Vector2f(Holder.left + (i * Holder.width / 8), Holder.top + (j * Holder.height / 8)));
			squares[i][j].setSize(sf::Vector2f(Holder.width / 8, Holder.height / 8));
		}
	}
}

void ChessSetUp::DrawSquares() {
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) win.draw(squares[i][j]); 
}

void ChessSetUp::DrawPieces() {
	for (int i = 0; i < 64; i++) win.draw(pieces[i].shape);
}

void ChessSetUp::MapPieces() {
	for (int i = 0; i < 64; i++) {
		if (pieces[i].draw == 1) {
			pieces[i].shape.setPosition(sf::Vector2f(Holder.left + (pieces[i].x * Holder.width / 8), Holder.top + (pieces[i].y * Holder.height / 8)));
			pieces[i].shape.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
		}
	}
}

void ChessSetUp::MapPieces(Move cur) {
	ChessPiece* current = new ChessPiece(); 
	bool capture = 0;
	for (int i = 0; i < 64; i++) {
		if (pieces[i].draw) {
			if (pieces[i].x == cur.oX && pieces[i].y == cur.oY)	current = &pieces[i];

			if (pieces[i].x == cur.X && pieces[i].y == cur.Y) {
				pieces[i].draw = 0;
				sounds[2].play();
				capture = 1;
			}

			pieces[i].shape.setPosition(Vector2f(Holder.left + (pieces[i].x * Holder.width / 8), Holder.top + (pieces[i].y * Holder.height / 8)));
			pieces[i].shape.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
		}
	}

	current->x = cur.X;
	current->y = cur.Y;

	if (capture == 0) sounds[0].play();

	current->shape.setPosition(sf::Vector2f(Holder.left + (current->x * Holder.width / 8), Holder.top + (current->y * Holder.height / 8)));
	current->shape.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
}

ChessSetUp::ChessSetUp(int width, int height, const char* name, const char* imgPath[12], const char* soundsPath[4]) {
	bool Scolor = 1; 
	sColor[0].r = 118;
	sColor[0].g = 150;
	sColor[0].b = 86;
	sColor[1].r = 238;
	sColor[1].g = 238;
	sColor[1].b = 210;

	sX = width; 
	sY = height; 

	Holder.left = 0;
	Holder.top = 0;
	Holder.width = width;
	Holder.height = height;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			squares[i][j].setFillColor(sColor[Scolor]);
			Scolor = Scolor ^ 1;
		}
		Scolor = Scolor ^ 1; 
	}

	FitToHolder();
	IntRect blank; 

	for (int i = 0; i < 12; i++) 
		pieceTex[i].loadFromFile(imgPath[i], blank); 

	int index = 0; 

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pieces[index].pieceID = cBoard.myBoard.a[i][j]; 
			pieces[index].x = i; 
			pieces[index].y = j; 

			if (pieces[index].pieceID != -1) {
				pieces[index].shape.setTexture(pieceTex[pieces[index].pieceID], 1); 
				pieces[index].draw = 1; 
			}

			index++; 
		}
	}

	for (int i = 0; i < 4; i++) {
		sBuffer[i].loadFromFile(soundsPath[i]);
		sounds[i].setBuffer(sBuffer[i]); 
	}

	MapPieces(); 
	win.create(VideoMode(width, height), name); 
}

bool ChessSetUp::Update() {
	Event event; 
	
	while (win.pollEvent(event)) {
		if (event.type == Event::Resized) {
			sX = win.getSize().x; 
			sY = win.getSize().y; 
			win.setView(View(FloatRect(0, 0, sX, sY))); 

			if (sX > sY){
				Holder.width = sY;
				Holder.height = sY;
				Holder.left = sX / 2 - Holder.width / 2;
				Holder.top = 0;
			}
			else{
				Holder.width = sX;
				Holder.height = sX;
				Holder.top = sY / 2 - Holder.height / 2;
				Holder.left = 0;
			}

			MapPieces();
			FitToHolder();
		}

		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Button::Left) {
				int pX = event.mouseButton.x;
				int pY = event.mouseButton.y;
				int projX, projY;
				projX = ((pX - Holder.left) - ((pX - Holder.left) % (Holder.width / 8))) / (Holder.width / 8);
				projY = ((pY - Holder.top) - ((pY - Holder.top) % (Holder.height / 8))) / (Holder.height / 8);

				if (cSelect == 0) {
					if (pX >= Holder.left && pX <= Holder.left + Holder.width && pY > Holder.top && pY < Holder.top + Holder.height) {
						selected[0] = projX;
						selected[1] = projY;
						squares[selected[0]][selected[1]].setFillColor(Color(186, 202, 68));
						cSelect = 1;
					}
				}
				else {
					if (selected[0] == projX && selected[1] == projY) {
						squares[selected[0]][selected[1]].setFillColor(sColor[1 - ((selected[0] + selected[1]) % 2)]);
						cSelect = 0;
					}
					else {
						Move m(selected[0], selected[1], projX, projY);
						if (cBoard.playMove(m)) {
							MapPieces(m);
							cBoard.nextTurn();
						}
						squares[selected[0]][selected[1]].setFillColor(sColor[1 - ((selected[0] + selected[1]) % 2)]);
						cSelect = 0;
					}
				}
			}
			else if (event.mouseButton.button == Mouse::Button::Right) {
				squares[selected[0]][selected[1]].setFillColor(sColor[1 - ((selected[0] + selected[1]) % 2)]);
				cSelect = 0;
			}
		}

		if (event.type == Event::Closed) {
			win.close(); 
			return 0; 
		}
	}

	win.clear(); 
	DrawSquares(); 
	DrawPieces();
	win.display(); 
	return 1; 
}
