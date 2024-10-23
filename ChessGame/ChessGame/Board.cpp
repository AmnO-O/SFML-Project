#include<vector>
#include<array>
#include "Board.h" 

using namespace std; 

Move::Move(int oldX, int oldY, int neX, int neY) {
	oX = oldX; oY = oldY; 
	X = neX; Y = neY; 
}

void Board::wPawn(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 0 && y > 0) {

		if (myBoard.a[x][y - 1] == -1) {
			move.push_back(Move(x, y, x, y - 1)); 
			if (myBoard.a[x][y - 2] == -1 && y == 6)
				move.push_back(Move(x, y, x, y - 2)); 
		}

		if (x > 0 && myBoard.a[x - 1][y - 1] >= 6) 
			move.push_back(Move(x, y, x - 1, y - 1)); 

		if (x < 7 && myBoard.a[x + 1][y - 1] >= 6) 
			move.push_back(Move(x, y, x + 1, y - 1)); 
	}
}

void Board::bPawn(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 6 && y < 7) {
		
		if (myBoard.a[x][y + 1] == -1) {
			move.push_back(Move(x, y, x, y + 1)); 
			if (y == 1 && myBoard.a[x][y + 2] == -1)
				move.push_back(Move(x, y, x, y + 2));
		}

		if (x > 0 && myBoard.a[x - 1][y + 1] < 6 && myBoard.a[x - 1][y + 1] != -1)
			move.push_back(Move(x, y, x - 1, y + 1)); 

		if (x < 7 && myBoard.a[x + 1][y + 1] < 6 && myBoard.a[x + 1][y + 1] != -1)
			move.push_back(Move(x, y, x + 1, y + 1));
	}
}

const int Kx[] = { -1, 1, -1, 1, 0, 0, -1, 1}; 
const int Ky[] = { -1, 1, 1, -1, -1, 1, 0, 0};

const int Knx[] = {-1, -2, 1, 2, 2, 1, -1, -2}; 
const int Kny[] = {-2, -1, -2, -1, 1, 2, 2, 1}; 

void Board::King(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 4 || myBoard.a[x][y] == 10) {
		bool Turn = myBoard.a[x][y] < 6; 

		for (int i = 0; i < 8; i++) {
			int nx = x + Kx[i]; 
			int ny = y + Ky[i]; 
		
			if (nx < 0 || ny > 7 || nx > 7 || ny < 0) continue; 
			if ((Turn && (myBoard.a[nx][ny] > 5 || myBoard.a[nx][ny] == -1)) ||
				(!Turn && (myBoard.a[nx][ny] < 6 || myBoard.a[nx][ny] == -1)))
				move.push_back(Move(x, y, nx, ny));
		}

		//if (x > 0) {
		//	if ((Turn && (myBoard.a[x - 1][y] > 5 || myBoard.a[x - 1][y] == -1)) ||
		//		(!Turn && (myBoard.a[x - 1][y] < 6 || myBoard.a[x - 1][y] == -1))) 
		//		move.push_back(Move(x, y, x - 1, y)); 

		//}

		//if (x > 0 && y > 0) {
		//	if ((Turn && (myBoard.a[x - 1][y - 1] > 5 || myBoard.a[x - 1][y - 1] == -1)) ||
		//		(!Turn && (myBoard.a[x - 1][y - 1] < 6 || myBoard.a[x - 1][y - 1] == -1)))
		//		move.push_back(Move(x, y, x - 1, y - 1));
		//}

		//if (x > 0 && y < 7) {
		//	if ((Turn && (myBoard.a[x - 1][y + 1] > 5 || myBoard.a[x - 1][y + 1] == -1)) ||
		//		(!Turn && (myBoard.a[x - 1][y - 1] < 6 || myBoard.a[x - 1][y + 1] == -1)))
		//		move.push_back(Move(x, y, x - 1, y + 1));
		//}

		//if (y > 0) {
		//	if ((Turn && (myBoard.a[x][y - 1] > 5 || myBoard.a[x][y - 1] == -1)) ||
		//		(!Turn && (myBoard.a[x][y - 1] < 6 || myBoard.a[x][y - 1] == -1)))
		//		move.push_back(Move(x, y, x, y - 1));
		//}

		//if (y < 7) {
		//	if ((Turn && (myBoard.a[x][y + 1] > 5 || myBoard.a[x][y + 1] == -1)) ||
		//		(!Turn && (myBoard.a[x][y + 1] < 6 || myBoard.a[x][y + 1] == -1)))
		//		move.push_back(Move(x, y, x, y + 1));
		//}

		//if (x < 7) {
		//	if ((Turn && (myBoard.a[x + 1][y] > 5 || myBoard.a[x + 1][y] == -1)) ||
		//		(!Turn && (myBoard.a[x + 1][y] < 6 || myBoard.a[x + 1][y] == -1)))
		//		move.push_back(Move(x, y, x + 1, y));
		//}

		//if (x < 7 && y < 7) {
		//	if ((Turn && (myBoard.a[x + 1][y + 1] > 5 || myBoard.a[x + 1][y + 1] == -1)) ||
		//		(!Turn && (myBoard.a[x + 1][y + 1] < 6 || myBoard.a[x + 1][y + 1] == -1)))
		//		move.push_back(Move(x, y, x + 1, y + 1));
		//}

		//if (x < 7 && y > 0) {
		//	if ((Turn && (myBoard.a[x + 1][y - 1] > 5 || myBoard.a[x + 1][y - 1] == -1)) ||
		//		(!Turn && (myBoard.a[x + 1][y - 1] < 6 || myBoard.a[x + 1][y - 1] == -1)))
		//		move.push_back(Move(x, y, x + 1, y - 1));
		//}
	}
}

void Board::Knight(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 2 || myBoard.a[x][y] == 8) {
		bool Turn = myBoard.a[x][y] < 6; 
		for (int i = 0; i < 8; i++) {
			int u = x + Knx[i]; 
			int v = y + Kny[i]; 
			if (u < 0 || v < 0 || u > 7 || v > 7) continue; 
			if((Turn && (myBoard.a[u][v] > 5 || myBoard.a[u][v] == -1)) ||
				(!Turn && (myBoard.a[u][v] < 6 || myBoard.a[u][v] == -1)))
				move.push_back(Move(x, y, u, v)); 
		}
	}
}

void Board::Rook(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 1 || myBoard.a[x][y] == 7) {
		bool Turn = myBoard.a[x][y] < 6; 
		
		for (int i = x - 1; i >= 0; i--) {
			if (myBoard.a[i][y] == -1) {
				move.push_back(Move(x, y, i, y)); 
				continue; 
			}
			
			if((Turn && myBoard.a[i][y] > 5) ||
				(!Turn && myBoard.a[i][y] < 6)) {
				move.push_back(Move(x, y, i, y)); 
				continue; 
			}

			break; 
		}

		for (int i = x + 1; i < 8; i++) {
			if (myBoard.a[i][y] == -1) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			if ((Turn && myBoard.a[i][y] > 5) ||
				(!Turn && myBoard.a[i][y] < 6)) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			break;
		}

		for (int i = y - 1; i >= 0; i--) {
			if (myBoard.a[x][i] == -1) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			if ((Turn && myBoard.a[x][i] > 5) ||
				(!Turn && myBoard.a[x][i] < 6)) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			break;
		}

		for (int i = y + 1; i < 8; i++) {
			if (myBoard.a[x][i] == -1) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			if ((Turn && myBoard.a[x][i] > 5) ||
				(!Turn && myBoard.a[x][i] < 6)) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			break;
		}
	}
}

void Board::Bishop(vector <Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 3 || myBoard.a[x][y] == 9) {
		bool Turn = myBoard.a[x][y] < 6; 
		int i, j; i = x, j = y; 

		while (true) {
			i--; j--;
			if (i < 0 || j < 0) break; 
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j)); 
				continue; 
			}
			
			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j)); 
				continue; 
			}

			break; 
		}

		i = x, j = y; 

		while (true) {
			i--; j++;
			if (i < 0 || j > 7) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}


		i = x, j = y;

		while (true) {
			i++; j--;
			if (i > 7 || j < 0) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}

		i = x, j = y;

		while (true) {
			i++; j++;
			if (i > 7 || j > 7) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}
	}
}

void Board::Queen(vector<Move>& move, int x, int y) {
	if (myBoard.a[x][y] == 5 || myBoard.a[x][y] == 11) {
		bool Turn = myBoard.a[x][y] < 6; 
		for (int i = x - 1; i >= 0; i--) {
			if (myBoard.a[i][y] == -1) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			if ((Turn && myBoard.a[i][y] > 5) ||
				(!Turn && myBoard.a[i][y] < 6)) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			break;
		}

		for (int i = x + 1; i < 8; i++) {
			if (myBoard.a[i][y] == -1) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			if ((Turn && myBoard.a[i][y] > 5) ||
				(!Turn && myBoard.a[i][y] < 6)) {
				move.push_back(Move(x, y, i, y));
				continue;
			}

			break;
		}

		for (int i = y - 1; i >= 0; i--) {
			if (myBoard.a[x][i] == -1) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			if ((Turn && myBoard.a[x][i] > 5) ||
				(!Turn && myBoard.a[x][i] < 6)) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			break;
		}

		for (int i = y + 1; i < 8; i++) {
			if (myBoard.a[x][i] == -1) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			if ((Turn && myBoard.a[x][i] > 5) ||
				(!Turn && myBoard.a[x][i] < 6)) {
				move.push_back(Move(x, y, x, i));
				continue;
			}

			break;
		}

		int i, j; i = x, j = y;

		while (true) {
			i--; j--;
			if (i < 0 || j < 0) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}

		i = x, j = y;

		while (true) {
			i--; j++;
			if (i < 0 || j > 7) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}


		i = x, j = y;

		while (true) {
			i++; j--;
			if (i > 7 || j < 0) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}

		i = x, j = y;

		while (true) {
			i++; j++;
			if (i > 7 || j > 7) break;
			if (myBoard.a[i][j] == -1) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			if ((Turn && myBoard.a[i][j] > 5) ||
				(!Turn && myBoard.a[i][j] < 6)) {
				move.push_back(Move(x, y, i, j));
				continue;
			}

			break;
		}
	}
}

vector <Move> Board::getLegalMoves(board b, bool color) {
	vector <Move> move; 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (b.a[i][j] == -1) continue; 

			if (color && b.a[i][j] < 6) {
				if(b.a[i][j] == 0) wPawn(move, i, j);
				if(b.a[i][j] == 4) King(move, i, j);
				if(b.a[i][j] == 2) Knight(move, i, j); 
				if(b.a[i][j] == 1) Rook(move, i, j); 
				if(b.a[i][j] == 3) Bishop(move, i, j); 
				if(b.a[i][j] == 5) Queen(move, i, j); 
			}

			if (!color && b.a[i][j] > 5) {
				if (b.a[i][j] == 6) bPawn(move, i, j);
				if (b.a[i][j] == 10) King(move, i, j);
				if (b.a[i][j] == 8) Knight(move, i, j);

				if (b.a[i][j] == 7) Rook(move, i, j);
				if (b.a[i][j] == 9)	Bishop(move, i, j);

				if (b.a[i][j] == 11) Queen(move, i, j);

			}
		}
	}

	return move; 
}

bool Board::playMove(Move req) {
	vector<Move> move = getLegalMoves(myBoard, turn);
	Move tmp; 
	for (int i = 0; i < move.size(); i++) {
		tmp = move[i]; 
		if (tmp.oX == req.oX && tmp.oY == req.oY && tmp.X == req.X && tmp.Y == req.Y) {
			myBoard.a[req.X][req.Y] = myBoard.a[req.oX][req.oY];
			myBoard.a[req.oX][req.oY] = -1; 

			vector <Move> tmpMoves = getLegalMoves(myBoard, turn ^ 1); 
			bool check = 0; 
			for (int j = 0; j < tmpMoves.size(); j++) {
				Move move = tmpMoves[j]; 
				if (myBoard.a[move.X][move.Y] == 4 || myBoard.a[move.X][move.Y] == 10) {
					myBoard = history.back(); 
					check = 1; 
					break; 
				}
			}

			if (check == 0) {
				history.push_back(myBoard); 
				return 1; 
			}
		}
	}

	return 0; 
}

bool Board::nextTurn() {
	return turn = turn ^ 1; 
}