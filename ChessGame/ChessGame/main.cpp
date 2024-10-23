#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ChessSetUp.h"
#include<string>
#include<iostream>

using namespace std;
using namespace sf;

const int Kx[] = { -1, 1, -1, 1, 0, 0, -1, 1 };
const int Ky[] = { -1, 1, 1, -1, -1, 1, 0, 0 };

const int Knx[] = { -1, -2, 1, 2, 2, 1, -1, -2 };
const int Kny[] = { -2, -1, -2, -1, 1, 2, 2, 1 };


const char* defaultTheme[12] = { "./Assets/Pieces/Resize/WhitePawn.png",
                                "./Assets/Pieces/Resize/WhiteRook.png",
                                "./Assets/Pieces/Resize/WhiteHorse.png",
                                "./Assets/Pieces/Resize/WhiteBishop.png",
                                "./Assets/Pieces/Resize/WhiteKing.png",
                                "./Assets/Pieces/Resize/WhiteQueen.png",
                                "./Assets/Pieces/Resize/BlackPawn.png",
                                "./Assets/Pieces/Resize/BlackRook.png",
                                "./Assets/Pieces/Resize/BlackHorse.png",
                                "./Assets/Pieces/Resize/BlackBishop.png",
                                "./Assets/Pieces/Resize/BlackKing.png",
                                "./Assets/Pieces/Resize/BlackQueen.png" };


const char* defaultSounds[4] = {
    "./Assets/Sounds/Default/move.wav",
    "./Assets/Sounds/Default/castle.wav",
    "./Assets/Sounds/Default/capture.wav",
    "./Assets/Sounds/Default/check.wav" };


int main() {
       ChessSetUp window(800, 800, "chess", defaultTheme, defaultSounds);
       while (window.Update()); 

    return 0;
}