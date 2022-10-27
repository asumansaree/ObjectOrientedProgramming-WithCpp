#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdbool.h>
#include <stdlib.h>     
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

enum class cell_stat{E=0, P, S, W}; //E: Empty, P: Peg, S: Space, W: Wall

class PegSolitaire
{
public:
	/* 
	   Constructors are designed considering that what they should contain when an object is created. Those are basically: 
	 1) Board type 
	 2) Computer/Human option, in other words one of the functions: play() or playgame() 
	 3) Move entry, save, load or turn back to board selection menu 
	*/
	PegSolitaire(int type_of_board, bool comp_human, string operation);
	PegSolitaire(int type_of_board, bool comp_human);
	PegSolitaire(int type_of_board);
	PegSolitaire();
	void set_board(int board_num);
	void print_board();
	int menu();
	void playGame();
	void play();	//No parameter means computer will automatically play one movement
	void play(int r, int c); //If play func takes cell position, that means user's selection will be applied one movement
	void find_space();
	bool right(int r, int c);
	int is_valid_mov_R(int r, int c);
	int is_valid_mov_L(int r, int c);
	int is_valid_mov_U(int r, int c);
	int is_valid_mov_D(int r, int c);
	bool is_P_available(int r, int c);
	void give_peg_info();
	void setAmountofPBeginning();
	static void set_total_peg_of_all_act_games();
	void save_file(string filename);
	int getAmount_of_P() {return amount_of_P;}
	/* 
		Aim of the cell class will be:
	   * Holding the position and row number 
	   * To chech whether values are valid 
	   * Making casting from char to enum 
	*/		
	class Cell	
	{
		public:
			Cell(char pos, int row_num, cell_stat cell_type);
			Cell(char pos, int row_num);
			Cell(char pos);
			Cell();
			void setPosition(char pos, char board_limit_pos);
			void setPositionInt() {position_int = position - 'A';}
			void setRowNumber(int row_num, int board_limit_row);
			void setCellType(cell_stat cell_type) {which_cell_type = cell_type;}
			void setDirection(char dir) {direction = dir;}
			void setSelectedRow(int r) {selected_row_index = r;}
			void setSelectedPos(int p) {selected_pos_index = p;}
			char getPosition() const {return position;}
			char getPositionInt() const {return position_int;}
			char getDirection() {return direction;}
			int getSelectedRow() {return selected_row_index;}
			int getSelectedPos() {return selected_pos_index;}
			int getRowNumber() const {return row_number;}
			cell_stat getCellType() const {return which_cell_type;}
	    	void output( ) const;
		private:
			char position;  //(A)
			int position_int;  
			int row_number; //(1)
			cell_stat which_cell_type = cell_stat::W; //a cell can be empty or contains a peg (enum)
			char direction;
			int selected_row_index;
			int selected_pos_index;
	};
private:
	int board_type=1;
	bool computer_or_human = true;
	string game_option = "hello";
	int amount_of_P = 0;
	int amount_of_P_beginning;
	int count_non_available = 0;
	//vector that has a base type "Cell class", a 2D vector of vector of Cell objects to represent the cells
	vector<vector<Cell>> board;
	static int total_peg_of_all_active_games;
	bool game_active_nonactive;
};

bool operator >(PegSolitaire &a, PegSolitaire &b);

int number_of_game = 0;
//global func for switching between games
int call_game(vector<PegSolitaire> V)
{
	int what_menu_returns, is_game_end=0;
	what_menu_returns = V[number_of_game].menu();
	if(what_menu_returns == 1)
	{
		number_of_game++;
		V[number_of_game].menu();
	}
	else if(what_menu_returns == -1)
		is_game_end = -1;
	else if(what_menu_returns == 8)
	{
		int ind1, ind2, bool_return_value;
		cout << "Select first game (Enter the order of the game in you played, like 1 for first game, 2 for second etc)\n";
		cin >> ind1;
		cout << "Select second game (Enter the order of the game in you played, like 1 for first game, 2 for second etc)\n";
		cin >> ind2;
		bool_return_value = V[ind1].getAmount_of_P() > V[ind2].getAmount_of_P();
		if(bool_return_value == true)
			cout << "First parameter has more peg then second parameter\n";
		else
			cout << "First parameter has less peg then second parameter\n";
	}
	else if(what_menu_returns == 9)
	{
		int ind;
		cout << "Select the game you want to return\n";
		cin >> ind;
		V[ind].menu();
	}
	else;
	return is_game_end;
}

int PegSolitaire:: total_peg_of_all_active_games = 0;

int main()
{
	PegSolitaire::Cell my_cell;
	vector<PegSolitaire> games;
	//I define max game number as 10, it can be increment
	games.resize(10); 
	int game_end=0;
	do
	{
		game_end = call_game(games);
	}while(game_end == 0);
}

PegSolitaire::PegSolitaire(int type_of_board, bool comp_human, string operation) : board_type(type_of_board), computer_or_human(comp_human), game_option(operation)
{/*Body intentionally empty.*/}
PegSolitaire::PegSolitaire(int type_of_board, bool comp_human) : board_type(type_of_board), computer_or_human(comp_human), game_option("e4-D")
{/*Body intentionally empty.*/}
PegSolitaire::PegSolitaire(int type_of_board) : board_type(type_of_board), computer_or_human(true), game_option("e4-D")
{/*Body intentionally empty.*/}
PegSolitaire::PegSolitaire() : board_type(1), computer_or_human(true), game_option("e4-D")
{/*Body intentionally empty.*/}

PegSolitaire::Cell::Cell() : position('A'), row_number(5), which_cell_type(cell_stat::W)
{/*Body intentionally empty.*/}

PegSolitaire::Cell::Cell(char pos) : position(pos), row_number(5), which_cell_type(cell_stat::W)
{/*Body intentionally empty.*/}

PegSolitaire::Cell::Cell(char pos, int row_num) : position(pos), row_number(row_num), which_cell_type(cell_stat::W)
{/*Body intentionally empty.*/}

PegSolitaire::Cell::Cell(char pos, int row_num, cell_stat cell_type) : position(pos), row_number(row_num), which_cell_type(cell_type)
{/*Body intentionally empty.*/}

void PegSolitaire::Cell::setPosition(char pos, char board_limit_pos)
{
	if(pos < 'A' || pos > board_limit_pos)
	{
        cout << "Selected position is out of bounds! \n";
        exit(1);
    }
    position = pos;		// If there is not something wrong with the provided value, assign it to the member variable of the class.
}

void PegSolitaire::Cell::setRowNumber(int row_num, int board_limit_row)
{
	if(row_num < 0 || row_num > board_limit_row)
	{
        cout << "Selected row is out of bounds! \n";
        exit(1);
    }
    row_number = row_num;		// If there is not something wrong with the provided value, assign it to the member variable of the class.
}

bool operator >(PegSolitaire &a, PegSolitaire &b)
{
	//It returns true is the first game has more pegs, otherwise it returns false.
	return(a.getAmount_of_P() > b.getAmount_of_P());
}

//call this whenever a game is ended
void PegSolitaire::set_total_peg_of_all_act_games()
{
	int total, act_one;
	total = total_peg_of_all_active_games;
	//act_one = getAmount_of_P();
	act_one = 0;
	total_peg_of_all_active_games = total + act_one;
	cout << "total number of pegs in all active game boards: " << total + act_one << endl;
}

void PegSolitaire::set_board(int board_num)
{
	vector<vector<Cell>> board1, board2, board3, board4, board5;
	switch(board_num)
	{
		case 1: board1 = {
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('A', 1, cell_stat::W), Cell('B', 1, cell_stat::W), Cell('C', 1, cell_stat::W), Cell('D', 1, cell_stat::W), Cell('E', 1, cell_stat::W), Cell('F', 1, cell_stat::W), Cell('G', 1, cell_stat::W), Cell('H', 1, cell_stat::W), Cell('I', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W)},
{Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('A', 2, cell_stat::W), Cell('B', 2, cell_stat::W), Cell('C', 2, cell_stat::W), Cell('D', 2, cell_stat::P), Cell('E', 2, cell_stat::P), Cell('F', 2, cell_stat::P), Cell('G', 2, cell_stat::W), Cell('H', 2, cell_stat::W), Cell('I', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W)},
{Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('A', 3, cell_stat::W), Cell('B', 3, cell_stat::W), Cell('C', 3, cell_stat::P), Cell('D', 3, cell_stat::P), Cell('E', 3, cell_stat::P), Cell('F', 3, cell_stat::P), Cell('G', 3, cell_stat::P), Cell('H', 3, cell_stat::W), Cell('I', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W)},
{Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('A', 4, cell_stat::W), Cell('B', 4, cell_stat::P), Cell('C', 4, cell_stat::P), Cell('D', 4, cell_stat::P), Cell('E', 4, cell_stat::E), Cell('F', 4, cell_stat::P), Cell('G', 4, cell_stat::P), Cell('H', 4, cell_stat::P), Cell('I', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W)},
{Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('A', 5, cell_stat::W), Cell('B', 5, cell_stat::P), Cell('C', 5, cell_stat::P), Cell('D', 5, cell_stat::P), Cell('E', 5, cell_stat::P), Cell('F', 5, cell_stat::P), Cell('G', 5, cell_stat::P), Cell('H', 5, cell_stat::P), Cell('I', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W)},
{Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('A', 6, cell_stat::W), Cell('B', 6, cell_stat::P), Cell('C', 6, cell_stat::P), Cell('D', 6, cell_stat::P), Cell('E', 6, cell_stat::P), Cell('F', 6, cell_stat::P), Cell('G', 6, cell_stat::P), Cell('H', 6, cell_stat::P), Cell('I', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W)},
{Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('A', 7, cell_stat::W), Cell('B', 7, cell_stat::W), Cell('C', 7, cell_stat::P), Cell('D', 7, cell_stat::P), Cell('E', 7, cell_stat::P), Cell('F', 7, cell_stat::P), Cell('G', 7, cell_stat::P), Cell('H', 7, cell_stat::W), Cell('I', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W)},
{Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('A', 8, cell_stat::W), Cell('B', 8, cell_stat::W), Cell('C', 8, cell_stat::W), Cell('D', 8, cell_stat::P), Cell('E', 8, cell_stat::P), Cell('F', 8, cell_stat::P), Cell('G', 8, cell_stat::W), Cell('H', 8, cell_stat::W), Cell('I', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W)},
{Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('A', 9, cell_stat::W), Cell('B', 9, cell_stat::W), Cell('C', 9, cell_stat::W), Cell('D', 9, cell_stat::W), Cell('E', 9, cell_stat::W), Cell('F', 9, cell_stat::W), Cell('G', 9, cell_stat::W), Cell('H', 9, cell_stat::W), Cell('I', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)}
    };	
		board = board1;
		break;
		case 2: board2 = {
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('A', 1, cell_stat::W), Cell('B', 1, cell_stat::W), Cell('C', 1, cell_stat::W), Cell('D', 1, cell_stat::P), Cell('E', 1, cell_stat::P), Cell('F', 1, cell_stat::P), Cell('G', 1, cell_stat::W), Cell('H', 1, cell_stat::W), Cell('I', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W)},
{Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('A', 2, cell_stat::W), Cell('B', 2, cell_stat::W), Cell('C', 2, cell_stat::W), Cell('D', 2, cell_stat::P), Cell('E', 2, cell_stat::P), Cell('F', 2, cell_stat::P), Cell('G', 2, cell_stat::W), Cell('H', 2, cell_stat::W), Cell('I', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W)},
{Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('A', 3, cell_stat::W), Cell('B', 3, cell_stat::W), Cell('C', 3, cell_stat::W), Cell('D', 3, cell_stat::P), Cell('E', 3, cell_stat::P), Cell('F', 3, cell_stat::P), Cell('G', 3, cell_stat::W), Cell('H', 3, cell_stat::W), Cell('I', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W)},
{Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('A', 4, cell_stat::P), Cell('B', 4, cell_stat::P), Cell('C', 4, cell_stat::P), Cell('D', 4, cell_stat::P), Cell('E', 4, cell_stat::P), Cell('F', 4, cell_stat::P), Cell('G', 4, cell_stat::P), Cell('H', 4, cell_stat::P), Cell('I', 4, cell_stat::P), Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W)},
{Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('A', 5, cell_stat::P), Cell('B', 5, cell_stat::P), Cell('C', 5, cell_stat::P), Cell('D', 5, cell_stat::P), Cell('E', 5, cell_stat::E), Cell('F', 5, cell_stat::P), Cell('G', 5, cell_stat::P), Cell('H', 5, cell_stat::P), Cell('I', 5, cell_stat::P), Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W)},
{Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('A', 6, cell_stat::P), Cell('B', 6, cell_stat::P), Cell('C', 6, cell_stat::P), Cell('D', 6, cell_stat::P), Cell('E', 6, cell_stat::P), Cell('F', 6, cell_stat::P), Cell('G', 6, cell_stat::P), Cell('H', 6, cell_stat::P), Cell('I', 6, cell_stat::P), Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W)},
{Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('A', 7, cell_stat::W), Cell('B', 7, cell_stat::W), Cell('C', 7, cell_stat::W), Cell('D', 7, cell_stat::P), Cell('E', 7, cell_stat::P), Cell('F', 7, cell_stat::P), Cell('G', 7, cell_stat::W), Cell('H', 7, cell_stat::W), Cell('I', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W)},
{Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('A', 8, cell_stat::W), Cell('B', 8, cell_stat::W), Cell('C', 8, cell_stat::W), Cell('D', 8, cell_stat::P), Cell('E', 8, cell_stat::P), Cell('F', 8, cell_stat::P), Cell('G', 8, cell_stat::W), Cell('H', 8, cell_stat::W), Cell('I', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W)},
{Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('A', 9, cell_stat::W), Cell('B', 9, cell_stat::W), Cell('C', 9, cell_stat::W), Cell('D', 9, cell_stat::P), Cell('E', 9, cell_stat::P), Cell('F', 9, cell_stat::P), Cell('G', 9, cell_stat::W), Cell('H', 9, cell_stat::W), Cell('I', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)}
    };	
		board = board2;
		break;
		case 3: board3 = {
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('A', 1, cell_stat::W), Cell('B', 1, cell_stat::W), Cell('C', 1, cell_stat::W), Cell('D', 1, cell_stat::P), Cell('E', 1, cell_stat::P), Cell('F', 1, cell_stat::P), Cell('G', 1, cell_stat::W), Cell('H', 1, cell_stat::W), Cell('I', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W)},
{Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('A', 2, cell_stat::W), Cell('B', 2, cell_stat::W), Cell('C', 2, cell_stat::W), Cell('D', 2, cell_stat::P), Cell('E', 2, cell_stat::P), Cell('F', 2, cell_stat::P), Cell('G', 2, cell_stat::W), Cell('H', 2, cell_stat::W), Cell('I', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W)},
{Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('A', 3, cell_stat::W), Cell('B', 3, cell_stat::W), Cell('C', 3, cell_stat::W), Cell('D', 3, cell_stat::P), Cell('E', 3, cell_stat::P), Cell('F', 3, cell_stat::P), Cell('G', 3, cell_stat::W), Cell('H', 3, cell_stat::W), Cell('I', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W)},
{Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('A', 4, cell_stat::W), Cell('B', 4, cell_stat::P), Cell('C', 4, cell_stat::P), Cell('D', 4, cell_stat::P), Cell('E', 4, cell_stat::P), Cell('F', 4, cell_stat::P), Cell('G', 4, cell_stat::P), Cell('H', 4, cell_stat::P), Cell('I', 4, cell_stat::P), Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W)},
{Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('A', 5, cell_stat::W), Cell('B', 5, cell_stat::P), Cell('C', 5, cell_stat::P), Cell('D', 5, cell_stat::P), Cell('E', 5, cell_stat::E), Cell('F', 5, cell_stat::P), Cell('G', 5, cell_stat::P), Cell('H', 5, cell_stat::P), Cell('I', 5, cell_stat::P), Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W)},
{Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('A', 6, cell_stat::W), Cell('B', 6, cell_stat::P), Cell('C', 6, cell_stat::P), Cell('D', 6, cell_stat::P), Cell('E', 6, cell_stat::P), Cell('F', 6, cell_stat::P), Cell('G', 6, cell_stat::P), Cell('H', 6, cell_stat::P), Cell('I', 6, cell_stat::P), Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W)},
{Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('A', 7, cell_stat::W), Cell('B', 7, cell_stat::W), Cell('C', 7, cell_stat::W), Cell('D', 7, cell_stat::P), Cell('E', 7, cell_stat::P), Cell('F', 7, cell_stat::P), Cell('G', 7, cell_stat::W), Cell('H', 7, cell_stat::W), Cell('I', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W)},
{Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('A', 8, cell_stat::W), Cell('B', 8, cell_stat::W), Cell('C', 8, cell_stat::W), Cell('D', 8, cell_stat::P), Cell('E', 8, cell_stat::P), Cell('F', 8, cell_stat::P), Cell('G', 8, cell_stat::W), Cell('H', 8, cell_stat::W), Cell('I', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W)},
{Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('A', 9, cell_stat::W), Cell('B', 9, cell_stat::W), Cell('C', 9, cell_stat::W), Cell('D', 9, cell_stat::W), Cell('E', 9, cell_stat::W), Cell('F', 9, cell_stat::W), Cell('G', 9, cell_stat::W), Cell('H', 9, cell_stat::W), Cell('I', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)}
    };	
		board = board3;
		break;
		case 4: board4 = {
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('A', 1, cell_stat::W), Cell('B', 1, cell_stat::W), Cell('C', 1, cell_stat::W), Cell('D', 1, cell_stat::W), Cell('E', 1, cell_stat::W), Cell('F', 1, cell_stat::W), Cell('G', 1, cell_stat::W), Cell('H', 1, cell_stat::W), Cell('I', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W)},
{Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('A', 2, cell_stat::W), Cell('B', 2, cell_stat::W), Cell('C', 2, cell_stat::W), Cell('D', 2, cell_stat::P), Cell('E', 2, cell_stat::P), Cell('F', 2, cell_stat::P), Cell('G', 2, cell_stat::W), Cell('H', 2, cell_stat::W), Cell('I', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W)},
{Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('A', 3, cell_stat::W), Cell('B', 3, cell_stat::W), Cell('C', 3, cell_stat::W), Cell('D', 3, cell_stat::P), Cell('E', 3, cell_stat::P), Cell('F', 3, cell_stat::P), Cell('G', 3, cell_stat::W), Cell('H', 3, cell_stat::W), Cell('I', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W)},
{Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('A', 4, cell_stat::W), Cell('B', 4, cell_stat::P), Cell('C', 4, cell_stat::P), Cell('D', 4, cell_stat::P), Cell('E', 4, cell_stat::P), Cell('F', 4, cell_stat::P), Cell('G', 4, cell_stat::P), Cell('H', 4, cell_stat::P), Cell('I', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W)},
{Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('A', 5, cell_stat::W), Cell('B', 5, cell_stat::P), Cell('C', 5, cell_stat::P), Cell('D', 5, cell_stat::P), Cell('E', 5, cell_stat::E), Cell('F', 5, cell_stat::P), Cell('G', 5, cell_stat::P), Cell('H', 5, cell_stat::P), Cell('I', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W)},
{Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('A', 6, cell_stat::W), Cell('B', 6, cell_stat::P), Cell('C', 6, cell_stat::P), Cell('D', 6, cell_stat::P), Cell('E', 6, cell_stat::P), Cell('F', 6, cell_stat::P), Cell('G', 6, cell_stat::P), Cell('H', 6, cell_stat::P), Cell('I', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W)},
{Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('A', 7, cell_stat::W), Cell('B', 7, cell_stat::W), Cell('C', 7, cell_stat::W), Cell('D', 7, cell_stat::P), Cell('E', 7, cell_stat::P), Cell('F', 7, cell_stat::P), Cell('G', 7, cell_stat::W), Cell('H', 7, cell_stat::W), Cell('I', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W)},
{Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('A', 8, cell_stat::W), Cell('B', 8, cell_stat::W), Cell('C', 8, cell_stat::W), Cell('D', 8, cell_stat::P), Cell('E', 8, cell_stat::P), Cell('F', 8, cell_stat::P), Cell('G', 8, cell_stat::W), Cell('H', 8, cell_stat::W), Cell('I', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W)},
{Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('A', 9, cell_stat::W), Cell('B', 9, cell_stat::W), Cell('C', 9, cell_stat::W), Cell('D', 9, cell_stat::W), Cell('E', 9, cell_stat::W), Cell('F', 9, cell_stat::W), Cell('G', 9, cell_stat::W), Cell('H', 9, cell_stat::W), Cell('I', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)}

    };	
		board = board4;
		break;
		case 5: board5 = {
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('A', 1, cell_stat::W), Cell('B', 1, cell_stat::W), Cell('C', 1, cell_stat::W), Cell('D', 1, cell_stat::W), Cell('E', 1, cell_stat::P), Cell('F', 1, cell_stat::W), Cell('G', 1, cell_stat::W), Cell('H', 1, cell_stat::W), Cell('I', 1, cell_stat::W), Cell('X', 1, cell_stat::W), Cell('X', 1, cell_stat::W)},
{Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('A', 2, cell_stat::W), Cell('B', 2, cell_stat::W), Cell('C', 2, cell_stat::W), Cell('D', 2, cell_stat::P), Cell('E', 2, cell_stat::P), Cell('F', 2, cell_stat::P), Cell('G', 2, cell_stat::W), Cell('H', 2, cell_stat::W), Cell('I', 2, cell_stat::W), Cell('X', 2, cell_stat::W), Cell('X', 2, cell_stat::W)},
{Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('A', 3, cell_stat::W), Cell('B', 3, cell_stat::W), Cell('C', 3, cell_stat::P), Cell('D', 3, cell_stat::P), Cell('E', 3, cell_stat::P), Cell('F', 3, cell_stat::P), Cell('G', 3, cell_stat::P), Cell('H', 3, cell_stat::W), Cell('I', 3, cell_stat::W), Cell('X', 3, cell_stat::W), Cell('X', 3, cell_stat::W)},
{Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('A', 4, cell_stat::W), Cell('B', 4, cell_stat::P), Cell('C', 4, cell_stat::P), Cell('D', 4, cell_stat::P), Cell('E', 4, cell_stat::P), Cell('F', 4, cell_stat::P), Cell('G', 4, cell_stat::P), Cell('H', 4, cell_stat::P), Cell('I', 4, cell_stat::W), Cell('X', 4, cell_stat::W), Cell('X', 4, cell_stat::W)},
{Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W), Cell('A', 5, cell_stat::P), Cell('B', 5, cell_stat::P), Cell('C', 5, cell_stat::P), Cell('D', 5, cell_stat::P), Cell('E', 5, cell_stat::E), Cell('F', 5, cell_stat::P), Cell('G', 5, cell_stat::P), Cell('H', 5, cell_stat::P), Cell('I', 5, cell_stat::P), Cell('X', 5, cell_stat::W), Cell('X', 5, cell_stat::W)},
{Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('A', 6, cell_stat::W), Cell('B', 6, cell_stat::P), Cell('C', 6, cell_stat::P), Cell('D', 6, cell_stat::P), Cell('E', 6, cell_stat::P), Cell('F', 6, cell_stat::P), Cell('G', 6, cell_stat::P), Cell('H', 6, cell_stat::P), Cell('I', 6, cell_stat::W), Cell('X', 6, cell_stat::W), Cell('X', 6, cell_stat::W)},
{Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('A', 7, cell_stat::W), Cell('B', 7, cell_stat::W), Cell('C', 7, cell_stat::P), Cell('D', 7, cell_stat::P), Cell('E', 7, cell_stat::P), Cell('F', 7, cell_stat::P), Cell('G', 7, cell_stat::P), Cell('H', 7, cell_stat::W), Cell('I', 7, cell_stat::W), Cell('X', 7, cell_stat::W), Cell('X', 7, cell_stat::W)},
{Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('A', 8, cell_stat::W), Cell('B', 8, cell_stat::W), Cell('C', 8, cell_stat::W), Cell('D', 8, cell_stat::P), Cell('E', 8, cell_stat::P), Cell('F', 8, cell_stat::P), Cell('G', 8, cell_stat::W), Cell('H', 8, cell_stat::W), Cell('I', 8, cell_stat::W), Cell('X', 8, cell_stat::W), Cell('X', 8, cell_stat::W)},
{Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('A', 9, cell_stat::W), Cell('B', 9, cell_stat::W), Cell('C', 9, cell_stat::W), Cell('D', 9, cell_stat::W), Cell('E', 9, cell_stat::P), Cell('F', 9, cell_stat::W), Cell('G', 9, cell_stat::W), Cell('H', 9, cell_stat::W), Cell('I', 9, cell_stat::W), Cell('X', 9, cell_stat::W), Cell('X', 9, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)},
{Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('A', 0, cell_stat::W), Cell('B', 0, cell_stat::W), Cell('C', 0, cell_stat::W), Cell('D', 0, cell_stat::W), Cell('E', 0, cell_stat::W), Cell('F', 0, cell_stat::W), Cell('G', 0, cell_stat::W), Cell('H', 0, cell_stat::W), Cell('I', 0, cell_stat::W), Cell('X', 0, cell_stat::W), Cell('X', 0, cell_stat::W)}
    };	
		board = board5;
		break;
	}
}

void PegSolitaire::print_board()
{
	cout << endl << "     ABCDEFGHI" << endl;
	for(auto i=0; i<board.size(); i++)
	{
		if(i>1 && i<11)
			cout << i-1 << " ";
		else
			cout << ' ';
		for(int j=0; j<board.size(); j++)
		{	
			if(board[i][j].getCellType() == cell_stat::W || board[i][j].getCellType() == cell_stat::S)
				cout << ' ';
			else if(board[i][j].getCellType() == cell_stat::E)
				cout << '.';
			else
				cout << 'P';
		}
		cout << endl;
	}
}

int PegSolitaire::menu()
{
	int option, ret_val=0;
	string input;
	char col, row, dir;
	int col_int, row_int;
	cout << "\n\n\nNEW GAME TIME!\n""Choose the board type: \n" << "(You must made a selection between 1-5)\n";
	int board_num;
    cin >> board_num;
    board_type = board_num;
    set_board(board_num);
    //cout << "board_type : "<<board_type << endl;
	print_board();
	cout << "0- Exit\n"
		 << "1- Automatic game (computer plays all game)\n"
    	 << "2- Play one movement (computer plays)\n"
    	 << "3- Play one movement (human plays)\n"
    	 << "4- Return those:\n     * Number of pegs\n"<<"     * Number of empty cells\n"<<"     * Number of pegs taken out from the board\n"
    	 << "5- Display current board\n"
    	 << "6- Total number of pegs in all active game boards\n"
    	 << "7- Add new game\n"
    	 << "8- Compare two game\n"
    	 << "9- Switch to an existed game\n"
    	 << "10- Save file\n";
    cout << "\n\nMade your choice: ";
    cin >> option;
    switch(option)
    {
    	case 0: ret_val = -1;
    			break;
    	case 1: playGame();
    			break;
    	case 2: play();
    			break;
    	case 3: int control_st; //in case of error, control_St will be 1 and get input again
				do
				{
					control_st=0;
					cout << "Choose your peg in format xy-Direction. For example, C4-R\n""(direction should be uppercase due to pdf says that)" << endl; 
					getline(cin, input);
					if(input[2] == '-')
	                {
	                    col = input[0];
	                    row = input[1];
	                    dir = input[3];
	                    col_int = col - 'a';
	                    cout << "\ncol_int: " << col_int; 
	                    row_int = row - '0';
	                    cout << "\nrow_int: " << row_int;
	                    board[row_int+1][col_int+3].setDirection(dir);
	                    if(board[row_int+1][col_int+3].getCellType() != cell_stat::P || (row_int) < 0 || (row_int) > 12 || (col_int) < 0 || (col_int) > 12)
	                    {
	                            cout << "Invalid peg selection!!!\n";
	                            control_st = '1';
	                    }
	                }
	                else
					{
						control_st = 1;
						cerr << " Undetected Input\n";
					}
				}while(control_st == 1);
    			play(row_int+1, col_int+3);
    			break;
    		case 4: give_peg_info();
    				break;
    		case 5: print_board();
    				break;
    		case 6: set_total_peg_of_all_act_games();
    				break;
    		case 7: ret_val = 7;
    				break;
    		case 8: ret_val = 8; 
    				break;
    		case 9: ret_val = 9; 
    				break;
    		case 10: cout << "Enter the filename you want to save: " << endl;
    				string s;
    				cin >> s;
    				save_file(s);

    }
    return ret_val;
}

void PegSolitaire::playGame()
{
	srand (time(NULL));
	//PegSolitaire::Cell coordinate;
	int col, row, dir;
	bool exit_from_loop;
	//function plays the game by asking the user the board type first then automatically plays the game until it ends
	do
	{
		int flag=0;
		exit_from_loop = is_P_available(row, col);
		if(exit_from_loop==true)
		{
			do
			{
				// Control part for whether taken random coordinate shows a peg 
				do
				{
					col = rand() % 13;
					row = rand() % 13;
				}while(board[row][col].getCellType() != cell_stat::P);
				board[row][col].setSelectedRow(row);
				board[row][col].setSelectedPos(col);
				int getted_row = board[row][col].getSelectedRow();
				int getted_pos = board[row][col].getSelectedPos();
				dir = rand() % 4;
				switch(dir)
				{
					case 0: board[row][col].setDirection('R'); 
							break;
					case 1: board[row][col].setDirection('L'); 
							break;
					case 2: board[row][col].setDirection('U'); 
							break;
					case 3: board[row][col].setDirection('D');
							break; 
				}
				if(right(row, col) == true) 
					flag=1;
			}while(flag == 0);
			print_board();
		}
	}while(exit_from_loop == true);
}

void PegSolitaire::play()
{
	//plays the game for a single step, automatically (random)
	srand (time(NULL));
	//PegSolitaire::Cell coordinate;
	int col, row, dir;
	//function plays the game by asking the user the board type first then automatically plays the game until it ends
	int flag=0;
	do
	{
		// Control part for whether taken random coordinate shows a peg 
		do
		{
			col = rand() % 13;
			row = rand() % 13;
			//cout << "\n\nboard[" << getted_row << "][ "<< getted_pos << "].getCellType(): " << static_cast<char>(board[getted_row][getted_pos].getCellType()) << endl;
		}while(board[row][col].getCellType() != cell_stat::P);
		board[row][col].setSelectedRow(row);
		board[row][col].setSelectedPos(col);
		int getted_row = board[row][col].getSelectedRow();
		int getted_pos = board[row][col].getSelectedPos();
		//cout << "getted_row: " << getted_row << "\ngetted_pos: " << getted_pos << endl;
		dir = rand() % 4;
		switch(dir)
		{
			case 0: board[row][col].setDirection('R'); 
					break;
			case 1: board[row][col].setDirection('L'); 
					break;
			case 2: board[row][col].setDirection('U'); 
					break;
			case 3: board[row][col].setDirection('D');
					break; 
		}
		if(right(row, col) == true) 
			flag=1;
	}while(flag == 0);
	print_board();
}

void PegSolitaire::play(int row, int col)
{
	//plays the game for a single step, by the user
	bool app;
    //loop that controls input validity
    do
    {
    	app = right(row, col);
		if(app == false)  
			cout << "You made a mistake but don't worry, I didn't change anything on board.\n";
    }while(app == false);
	print_board();	  
}

bool PegSolitaire::right(int r, int c)
{
	char d = static_cast<char>(board[r][c].getDirection());
	switch(d)
	{
		case 'R': 
		if(is_valid_mov_R(r, c) == 0)
		{
			/*
				After controling movement is valid, reflect the changes to the board
			*/
			board[r][c].setCellType(cell_stat::E);
			board[r][c+1].setCellType(cell_stat::E);
			board[r][c+2].setCellType(cell_stat::P);
		}
		else
			return false;
		break;

		case 'L': 
		if(is_valid_mov_L(r, c) == 0)
		{
			board[r][c].setCellType(cell_stat::E);
			board[r][c-1].setCellType(cell_stat::E);
			board[r][c-2].setCellType(cell_stat::P);
		}
		else
			return false;
		break;

		case 'U': 
		if(is_valid_mov_U(r, c) == 0)
		{
			board[r][c].setCellType(cell_stat::E);
			board[r-1][c].setCellType(cell_stat::E);
			board[r-2][c].setCellType(cell_stat::P);
		}
		else
			return false;
		break;

		case 'D': 
		if(is_valid_mov_D(r, c) == 0)
		{
			board[r][c].setCellType(cell_stat::E);
			board[r+1][c].setCellType(cell_stat::E);
			board[r+2][c].setCellType(cell_stat::P);
		}
		else
			return false;
		break;
	}
	return true;
}
 
void PegSolitaire::give_peg_info()
{
	cout << "* Number of pegs: " << amount_of_P << endl;
	int empty, current, beginning;
	beginning = amount_of_P_beginning;
	current = amount_of_P;
	empty = beginning - current;
	cout << "* Number of empty cells: " << empty << endl;
	cout << "* Number of pegs taken out from the board: " << empty-1 << endl;
}

int PegSolitaire::is_valid_mov_R(int r, int c)
{
	if(board[r][c].getCellType() == cell_stat::P && board[r][c+1].getCellType() == cell_stat::P && board[r][c+2].getCellType() == cell_stat::E)	return 0;
	else																		return 1;
}
int PegSolitaire::is_valid_mov_L(int r, int c)
{
	int row_number = board[r][c].getSelectedRow();
	int position_int = board[r][c].getSelectedPos();
	//cout << "\n\nboard[" << r << "][ "<< c << "].getCellType(): " << static_cast<char>(board[r][c].getCellType()) << endl;
	if(board[r][c-1].getCellType() == cell_stat::P && board[r][c-2].getCellType() == cell_stat::E)							return 0;
	else																		return 1;
}
int PegSolitaire::is_valid_mov_U(int r, int c)
{
	if(board[r-1][c].getCellType() == cell_stat::P && board[r-2][c].getCellType() == cell_stat::E) 							return 0;
	else																		return 1;
}
int PegSolitaire::is_valid_mov_D(int r, int c)
{
	if(board[r+1][c].getCellType() == cell_stat::P && board[r+2][c].getCellType() == cell_stat::E)							return 0;
	else																		return 1;
}

bool PegSolitaire::is_P_available(int r, int c)
{
	amount_of_P = 0;
	count_non_available=0;
	//This is the control func that whether is there any available movement for any peg (P), if not, end the game.
	for(int i=0; i<board.size(); i++)
	{
		for(int j=0; j<board[i].size(); j++)
		{	
			if(board[i][j].getCellType() == cell_stat::P)
			{
				amount_of_P++;
				// Here if==1 means there is not any available movement to 4 of the 4 direction
				if((is_valid_mov_R(i, j) && is_valid_mov_L(i, j) && is_valid_mov_U(i, j) && is_valid_mov_D(i, j)) == 1)
					count_non_available++;	
			}
		}
	}
	if(amount_of_P == count_non_available) // This means all the P values are non-appropriate and no moves left
	{
		cout << "\nEnd of the game!\nYour score is: " << amount_of_P << endl; 
		return false;
	}
	else
		return true;
}

void PegSolitaire::setAmountofPBeginning()
{
	amount_of_P_beginning = 0;
	for(int i=0; i<board.size(); i++)
	{
		for(int j=0; j<board[i].size(); j++)
		{	
			if(board[i][j].getCellType() == cell_stat::P)
				amount_of_P_beginning++;
		}
	}
}

void PegSolitaire::save_file(string filename)
{
	ofstream outStream;
	outStream.open(filename);
	for(int i=0; i<board.size(); i++)
	{
		for(int j=0; j<board.size(); j++)
		{	
			if(board[i][j].getCellType() == cell_stat::W || board[i][j].getCellType() == cell_stat::S)
				outStream << ' ';
			else if(board[i][j].getCellType() == cell_stat::E)
				outStream << '.';
			else
				outStream << 'P';
		}
		outStream << endl;
	}
	outStream.close();	
}

