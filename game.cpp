/*
*	   PROJ2: 2048
*      game.cpp: Implements entire 2048 game
*      Author: Brooke Peterson
*      Date: December 6, 2018
*/


#include <string>
#include <cstdio>
#include <iostream>


//includes contents of header files 
#include "int-string.h"
#include "highScoresList.h"
#include "game.h"
#define RANDOMSEED time(NULL)


using namespace std;

/*
 * Game
 *
 * Default constructor–initializes private variables 
 */
Game::Game() {

	srand(RANDOMSEED);
	curr_score = 0; 
	//prompts user for array size 
	cout << "Enter desired dimension of board: ";
	cin >> arr_size; 

	//array size must be greater than 2 
	if (arr_size < 2) {
		cerr << "Error. Invalid input." << endl; 
		exit(1);
	}

	//creates a dynamically allocated 2D array of pointers in heap
	array = new int*[arr_size];
	for (int i = 0; i < arr_size; ++i)
	{
		array[i] = new int[arr_size];
	}
}

/*
* ~Game
*
* Frees heap-allocated memory associated with Game
*/
Game::~Game() {

	for (int i = 0; i < arr_size; ++i)
	{
		delete [] array[i];
	}
	delete [] array; 
	array = NULL; 
}

/*
* play
*
* Starts game and calls appropriate functions 
* args: nothing 
 *rets: nothing 
 */
void Game::play() {
	string user; 
	bool should_print = true; 

	initialize_board(); //fills board with initial 2's and 0's
	
	cout << "Starting game! High score is " << scores_list.highestScore() << endl; 

	//prints board and calls appropriate functions until user loses or quits
	do { 
		if (should_print == true)
		{
			cout << "Current Score: " << curr_score << endl;
			print_board();
		}
		cin >> user_input; 
		should_print = directory(user_input);
		add_tile();
	} while (user_input != QUIT && (user_lost() == false));

	cout << "Game over! Enter your name to record your score: ";
	cin >> user; 
	scores_list.insert(user, curr_score);
	scores_list.printTop5(); 


}

/*
* initialize_board
*
* Initializes board with two 2's and 0's 
* args: nothing 
 *rets: nothing 
 */
void Game::initialize_board() {
	//when index reaches one of the random numbers, set element at index to 2
	for (int i = 0; i < arr_size; ++i)
	{
		for (int j = 0; j < arr_size; ++j)
		{
			array[i][j] = 0; 
		}
	}

	//sets two random numbers within 0 to size of array
	int rand_num1 = rand() % arr_size; 
	int rand_num2 = rand() % arr_size;
	array[rand_num1][rand_num2] = 2; 


	int rand_num3 = rand() % arr_size;
	int rand_num4 = rand() % arr_size;

	//random numbers cannot be equal 
	while (array[rand_num3][rand_num4] != 0) { 
		rand_num3 = rand() % arr_size;
		rand_num4 = rand() % arr_size;
	}

	array[rand_num3][rand_num4] = 2; 
}

/*
* print_board
*
* Prints 2048 board
* args: nothing 
 *rets: nothing 
 */
void Game::print_board() {
	
	//loops through all elements in array 
	for (int i = 0; i < arr_size; ++i)
	{
		for (int j = 0; j < arr_size; ++j)
		{
			//if element is 0, print a dash, otherwise print the number 
			if (array[i][j] == 0) {
				print_number("-");
			} else { 
				print_number(int2string(array[i][j]));
			}
		}
		cout << endl;
	}
}

/*
* print_number
*
* Print a number with appropriate spaces 
* args: string num (number represented as a string)
 *rets: nothing 
 */
void Game::print_number(string num) {
    printf("%-6s", num.c_str());
}

/*
* directory 
*
* Calls appropriate functions based on user's input 
* args: char user_input (a, s, w, d) 
 *rets: nothing 
 */
bool Game::directory(string user_input) {
	//combines tiles left if user types 'a'
	if (user_input == LEFT) {
		combine_left(); 
		return true;
	//combines tiles left if user types 'd'
	} else if (user_input == RIGHT) {
		combine_right(); 
		return true; 
	//combines tiles up if user types 'w'
	} else if (user_input == UP) {
		combine_up();
		return true; 
	//combines tiles down if user types 's'
	} else if (user_input == DOWN) {
		combine_down();
		return true;
	//prints top 5 high scores if user types 'h'
	} else if (user_input == HIGH_SCORE) {
		scores_list.printTop5(); 
		return false;
	//clears high score list 
	} else if (user_input == CLEAR) {
		scores_list.clear();
		return false;
	//prints all scores from user name
	} else if (user_input == SHOW) { 
		string show_user;
		cin >> show_user; 
		scores_list.printUser(show_user);
		return false;
	//keeps only top 10 scores
	} else if (user_input == KEEP) {
		scores_list.keepTop10(); 
		return false;
	} else if (user_input == QUIT) {
		return false; 
	} else {
		cout << "Command not recognized. Please try again." << endl;
		return false;
	}
}

/*
* swap
*
* Swaps contents of two indices in array 
* args: index of first element, index of second element  
 *rets: nothing 
 */
void Game::swap(int elem1_x, int elem1_y, int elem2_x, int elem2_y) {
	//WILL LATER NEED FOUR PARAMETERS ROW, COL OF FIRST ELEMENT AND ROW, COL OF SECOND ELEMENT
	//sets a temporary integer to element at index1 
	int temp = array[elem1_x][elem1_y]; 
	//sets element at index1 to element at index2
	array[elem1_x][elem1_y] = array[elem2_x][elem2_y]; 
	//sets element at index2 to elenent that used to be at index1
	array[elem2_x][elem2_y] = temp; 
}

/*
* shift_zeros_right
*
* Shifts all zeros to the right of the row of each column using swap 
* args: nothing 
 *rets: nothing 
 */
void Game::shift_zeros_right() {

	//loops through every row
	for (int i = 0; i < arr_size; ++i)
	{
		//loops through every column
		for (int j = arr_size - 1; j >= 0; --j)
		{
			//if element is 0, shift it all the way to right
			if (array[i][j] == 0) 
			{
				for (int k = j; k < arr_size - 1; ++k) 
				{
					swap(i, k, i, k + 1);  
				}

			}
		}
	}
}


/*
* shift_zeros_left
*
* Shifts all zeros to the left of the row of each column using swap 
* args: nothing 
 *rets: nothing 
 */
void Game::shift_zeros_left() {

	//loops through every row
	for (int i = 0; i < arr_size; ++i)
	{
		//loops through every column
		for (int j = 0; j < arr_size; ++j)
		{
			//if element is 0, shift it all the way to left
			if (array[i][j] == 0) 
			{
				for (int k = j; k > 0; --k) 
				{
					swap(i, k, i, k - 1); 
				}
			}
		}
	}
}
	
/*
* shift_zeros_up
*
* Shifts all zeros to the top of the column of each row using swap 
* args: nothing 
 *rets: nothing 
 */
void Game::shift_zeros_up() {

	//loops through every row 
	for (int i = 0; i < arr_size; ++i)
	{
		//loops through every column
		for (int j = 0; j < arr_size; ++j)
		{
			//if element is 0, shift it all the way up
			if (array[i][j] == 0) 
			{
				for (int k = i; k > 0; --k) 
				{
					swap(k, j, k - 1, j);  
				}
			}
		}
	}
}

/*
* shift_zeros_down
*
* Shifts all zeros to the bottom of the column of each row using swap 
* args: nothing 
 *rets: nothing 
 */
void Game::shift_zeros_down() {
	
	//loops through every row 
	for (int i = arr_size - 1; i >= 0; --i)
	{
		//loops through every column
		for (int j = 0; j < arr_size; ++j)
		{
			//if element is 0, shift it all the way down
			if (array[i][j] == 0) 
			{
				for (int k = i; k < arr_size - 1; ++k) 
				{
					swap(k, j, k + 1, j);  
				}

			}
		}
	}
}


/*
* combine
*
* Combines two tiles by doubling the first element and setting the second element to zero 
* args: index of element 1, index of element 2 
 *rets: nothing 
 */
void Game::combine(int elem1_x, int elem1_y, int elem2_x, int elem2_y) {

	//doubles element at index1
	array[elem1_x][elem1_y] = array[elem1_x][elem1_y] * 2; 
	//sets element at index2 to zero
	array[elem2_x][elem2_y] = 0; 

	//calculates current score as score that was just doubled
	curr_score = curr_score + array[elem1_x][elem1_y];
}

/*
* combine_right
*
* Calls shift_zeros_left and combine to combine two tiles to the right 
* args: nothing
 *rets: nothing 
 */
void Game::combine_right() {
	
	//move zeros to the left to get out of the way
	shift_zeros_left();

	//loops through array up to second to last element
	for (int i = 0; i < arr_size; ++i)
	{
		for (int j = arr_size - 1; j > 0; --j)
		{
			//if two adjacent tiles are equal, combine them 
			if (array[i][j] == array[i][j - 1]) {
				combine(i, j, i, j - 1);
				shift_zeros_left();
				//shift zeros back to the left to get out of the way
			}
		}
		
	}
}

/*
* combine_left
*
* Calls shift_zeros_right and combine to combine two tiles to the left 
* args: nothing
 *rets: nothing 
 */
void Game::combine_left() {

	//move zeros to the right to get out of the way
	shift_zeros_right();

	//loops through array up to second to last element
	for (int i = arr_size - 1; i >= 0; --i)
	{
		for (int j = 0; j < arr_size - 1; ++j)
		{
			//if two adjacent tiles are equal, combine them 
			if (array[i][j] == array[i][j + 1]) {
				combine(i, j, i, j + 1);
				//shift zeros back to the right to get out of the way
				shift_zeros_right();
			}
		}
	}
}

/*
* combine_up
*
* Calls shift_zeros_down and combine to combine two tiles to the top 
* args: nothing
 *rets: nothing 
 */
void Game::combine_up() {

	//move zeros down to get out of the way
	shift_zeros_down();

	//loops through array up to second to last element
	for (int i = 0; i < arr_size - 1; ++i)
	{
		for (int j = 0; j < arr_size - 1; ++j)
		{
			//if two top and bottom tiles are equal, combine them 
			if (array[i][j] == array[i + 1][j]) {
				combine(i, j, i + 1, j);
				//shift zeros back down to get out of the way
				shift_zeros_down();
			}
		}
	}
}

/*
* combine_down
*
* Calls shift_zeros_up and combine to combine two tiles to the bottom 
* args: nothing
 *rets: nothing 
 */
void Game::combine_down() {
	
	//move zeros up to get out of the way
	shift_zeros_up();

	//loops through array up to second to last element
	for (int i = arr_size - 1; i > 0; --i)
	{
		for (int j = 0; j < arr_size; ++j)
		{
			//if two top and bottom tiles are equal, combine them 
			if (array[i][j] == array[i - 1][j]) {
				combine(i, j, i - 1, j);
				//shift zeros back up to get out of the way
				shift_zeros_up();
			}
		}
	}
}

/*
* dupe_tiles
*
* Returns true if there are two identical tiles next to each other (up/down, right/left)
* args: nothing
 *rets: true or false  
 */
bool Game::dupe_tiles() {
	
	//loops through array up to second to last element
	for (int i = 1; i < arr_size - 1; ++i)
	{
		for (int j = 0; j < arr_size - 1; ++j)
		{
			//check if number is same as the one to the right of it
			if (array[i][j] == array[i + 1][j]) {
				return true; 
			//check if number is same as the one to the left of it
			} else if (array[i][j] == array[i - 1][j]) {
				return true; 
			//check if number is same as the one above it
			} else if (array[i][j] == array[i][j + 1]) {
				return true; 
			//check if number is same as the one below it
			} else if (array[i][j] == array[i][j - 1]) {
				return true;
			}
		}
	}
 return false; //no duplicate adjacent tiles 
}

/*
* user_lost
*
* Returns true if there are two identical tiles next to each other or 
  there are empty spots in array
* args: nothing
 *rets: true or false  
 */
bool Game::user_lost() {
	
	//loops through array 
	for (int i = 0; i < arr_size; ++i)
	{	
		for (int j = 0; j < arr_size; ++j)
		{
			//user hasn't lost if any tiles are empty or there are any 
			//duplicate adjacent tiles
			if (array[i][j] == 0 || dupe_tiles() == true) {
				return false;
			}
		}
	}

	//print board one more time and loser has lost 
	print_board(); 
	return true; 
}

/*
* add_tile
*
* Randomly adds a 2 or a 4 to any empty spot in array  
* args: nothing
 *rets: nothing 
 */
void Game::add_tile() {  

	int tile_spot_row = rand() % arr_size; //create random number
	int tile_spot_col = rand() % arr_size;

		//element at random number index must be empty (0)
		while (array[tile_spot_row][tile_spot_col] != 0) {
			tile_spot_row = rand() % arr_size;
			tile_spot_col = rand() % arr_size;
		}
		
		//90% chance new tile is a 2 
		if (rand() % 10 < 9) {
       		array[tile_spot_row][tile_spot_col] = 2;
    	//10% chance new tile is a 4
    	} else {
       		array[tile_spot_row][tile_spot_col] = 4;
    	}
    }



