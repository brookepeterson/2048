x/*
*      PROJ2: 2048
*      highScoresList.h: Header file for highScoresList.cpp
*      Author: Brooke Peterson
*      Date: December 6, 2018
*/

#ifndef HIGHSCORESLIST_H
#define HIGHSCORESLIST_H

#include <string>

//initialize struct 
struct Node {
                std::string user; 
                int score; 
                Node *next; 
        };

class HighScoresList {
    public:
        //Default constructor–initializes private variables
        HighScoresList();

        //Frees heap-allocated memory associated with HighScoresList
        ~HighScoresList();

        //Writes the names and scores to the HIGH_SCORE_FILE, followed by the 
        //sentinel
        void save();

        //Returns highest score in the list 
        int highestScore();

        //Prints entire high score list 
        void print();

        //Prints top 5 high scores of high score list 
        void printTop5();

        //Keeps top 10 high scores in high score list and deletes rest 
        void keepTop10();

        //Inserts new user name and score into high score list in 
        //correct order 
        void insert(std::string user, int score);

        //Clears all scores in high score list  
        void clear();

        //Prints all scores associated with inputted user name 
        void printUser(std::string user);


        void deleteUser(std::string user);   // A JFFE, not required

    private:
        //initialize private variables and constants 
        Node *front;
        const std::string SENTINEL = "-1";
        const std::string HIGH_SCORE_FILE = "highScores.txt";

        //Reads the HIGH_SCORE_FILE and loads the contents of the file
        //into the linked list.
        void load();
    
};

#endif
