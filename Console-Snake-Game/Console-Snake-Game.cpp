#include<iostream>
#include<vector>
#include<conio.h>
#include<Windows.h>

using namespace std;

bool gameOver, resume=true;
int score;
enum direction { STOP = 0, UP, LEFT, DOWN, RIGHT };
direction dir;
int h, w, x, y, fx, fy, tail=0;
vector<pair<int, int>> tacor;
void setup() {
	dir = STOP;
	tacor.clear();
	gameOver = false;
	tail = 1;
	score = 0;
	h = 20; w = 20;
	x = w/2; y = h/2;
	fx = rand() % w;
	fy = rand() % h;
}

void draw(){

	system("cls");
	cout << "-----------VEGETARIAN SNAKE GAME-----------"<<endl<<endl<<"Feed the Snake some fruits!"<<endl<<"Press P to pause. Press direction keys for movements." << endl<< "-------a small project by @ashuvssut-------"<<endl;
	for (int j = -1; j < h + 1; j++) {
		for (int i = -1; i < w + 1; i++) {
			if (i == -1 || i == h || j == -1 || j == w){
				cout << "# ";
			}
			
			else if (i == x && j == y) {  cout << "O "; }

			else if (i == fx && j == fy) { cout << "F "; }
			else {
				if (!(find(tacor.begin(), tacor.end(), make_pair(i, j)) == tacor.end())) {
					cout << "o ";
				}
				else cout << "  ";
			}
		}
		cout << endl;
	}	
	cout << "SCORE:" << score << endl;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'p':resume = false; break;
		case 72: if (dir == DOWN) { break; } else { dir = UP; break; }
		case 80: if (dir == UP) { break; } else { dir = DOWN; break; }
		case 75: if (dir == RIGHT) { break; } else{ dir = LEFT; break;}
		case 77: if (dir == LEFT) { break; } else { dir = RIGHT; break;}
		case 'c': dir = STOP; break;
		case 'x': gameOver = true; break;
		}
	}
}

void logic() {
	
	if (x == fx && y == fy) {
		tail++; 
		score += 10;
		fx = rand() % w;
		fy = rand() % h;
	}
	if (tail > 0) {
		tacor.insert(tacor.begin(), make_pair(x, y));
		if (tacor.size() > tail) { tacor.pop_back(); }
	}
	switch (dir) {
	case UP: y--; break;
	case LEFT: x--; break;
	case DOWN: y++;  break;
	case RIGHT: x++; break;
	case STOP: tail = 1; goto exePt;
	}

	if (!(find(tacor.begin(), tacor.end(), make_pair(x, y)) == tacor.end())) {
		gameOver = true;
	}
		
	if (x<0 || x>w - 1 || y<0 || y>h - 1) {
		gameOver = true;
	}
	exePt:{}
}

int main() {
	start:
	setup();

	while (!gameOver) {

		if (resume) {
			draw();
			input();
			logic();
			//Sleep(10);
		}
		else { 
			_getch(); 
			resume = true;
		}
	}
	if (gameOver) {
		cout << R"(GAME OVER)" <<endl<<"Press A or ` to Play again or else press X or / key to terminate console."<<endl;
		cout << "KEEP CAPSLOCK OFF" << endl;
		askKey:
		switch (_getch()) {
		case '`': gameOver = false; goto start;
		case 'a': gameOver = false; goto start;
		case '/': break;
		case 'x': break;
		default: goto askKey;
		
		}
	}
	return 0;
}