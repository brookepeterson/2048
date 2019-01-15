/*
*	   PROJ2: 2048
*      game.h: Header file for game.cpp
*      Author: Brooke Peterson
*      Date: December 6, 2018
*/

#ifndef GAME_H
#define GAME_H

#include <string>
#include "highScoresList.h"

class Game {
    public:
    	//Default constructor–initializes private variables
        Game();

        //Frees heap-allocated memory associated with Game
        ~Game();

        //Starts game and calls appropriate functions 
        void play();
    private:
    	//Initializes board with two 2's and 0's 
        void initialize_board();

        //Prints 2048 board
        void print_board();

        //Print a number with appropriate spaces 
        void print_number(std::string num);

        //Calls appropriate functions based on user's input 
        bool directory(std::string user_input);

        //Swaps contents of two indices in array 
        void swap(int elem1_x, int elem1_y, int elem2_x, int elem2_y);

        //Shifts all zeros to the right of the row of each column using swap 
        void shift_zeros_right();

        //Shifts all zeros to the left of the row of each column using swap 
        void shift_zeros_left();

        //Shifts all zeros to the top of the column of each row using swap 
        void shift_zeros_up();

        //Shifts all zeros to the bottom of the column of each row using swap
        void shift_zeros_down();

        //Combines two tiles by doubling the first element and setting the 
        //second element to zero 
        void combine(int elem1_x, int elem1_y, int elem2_x, int elem2_y);

        //Calls shift_zeros_left and combine to combine two tiles to the right 
		void combine_right();

		//Calls shift_zeros_right and combine to combine two tiles to the left
		void combine_left();

		//Calls shift_zeros_down and combine to combine two tiles to the top
		void combine_up();

		//Calls shift_zeros_up and combine to combine two tiles to the bottom 
		void combine_down();

		//Returns true if there are two identical tiles next to each other 
		//(up/down, right/left)
        bool dupe_tiles();

        //Returns true if there are two identical tiles next to each other or 
  		//there are empty spots in array
        bool user_lost();

        //Randomly adds a 2 or a 4 to any empty spot in array
        void add_tile();

        //declares all private variables and constants
        int **array;
        int arr_size;
        int curr_score;
        std::string user_input;
        HighScoresList scores_list; 
        const std::string UP = "w";
        const std::string DOWN = "s";
        const std::string LEFT = "a";
        const std::string RIGHT = "d";
        const std::string QUIT = "q";
        const std::string HIGH_SCORE = "h";
        const std::string CLEAR = "clear";
        const std::string SHOW = "show";
        const std::string KEEP = "keep";
};

#endif
