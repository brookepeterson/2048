/*
*      PROJ2: 2048
*      highScoresList.cpp: Implements entire 2048 game
*      Author: Brooke Peterson
*      Date: December 6, 2018
*/

#include <iostream>
#include <fstream>

#include "highScoresList.h"

using namespace std;

/*
 * HighScoresList
 *
 * Default constructor–initializes private variables 
 */
HighScoresList::HighScoresList() {

    front = NULL; //define front pointer
    load(); //load list 
}

/*
* ~HighScoresList
*
* Frees heap-allocated memory associated with HighScoresList
*/
HighScoresList::~HighScoresList() {

    save(); //update high score list 
    clear(); //delete everything in heap 

}

/* 
 * load
 *
 * Reads the HIGH_SCORE_FILE and loads the contents of the file
 * into the linked list.
 * If the file does not exist, do nothing. 
 * args: nothing 
 * rets: nothing
 */
void HighScoresList::load() {
    
    ifstream inFile;
    inFile.open(HIGH_SCORE_FILE);
    if (not inFile) {
        return;
    }
    //declare variables 
    string user; 
    int score;

    //load file until gets to end 
    while (inFile >> user) {
        if (user == SENTINEL) 
            break;

        inFile >> score;
        insert(user, score);
    }

    inFile.close();
}

/* 
 * save
 * 
 * Writes the names and scores to the HIGH_SCORE_FILE, followed by the 
 * sentinel.
 * This will overwrite what was originally in HIGH_SCORE_FILE.
 * args: nothing 
 * returns: nothing 
 */
void HighScoresList::save() {
    
    Node *curr = front;    
    ofstream outFile;
    outFile.open(HIGH_SCORE_FILE);

    //update list to outFile and end with sentinel 
    while (curr != NULL) {
        outFile << curr->user << " " << curr->score << endl;
        curr = curr->next; 
    }

    outFile << SENTINEL << endl;
    outFile.close();
}   


/* 
 * highestScore
 * 
 * args: nothing 
 * returns: highest score in the list  
 */    
int HighScoresList::highestScore() {
    
    //if list is empty, return nothing 
    if (front == NULL)
    {
        return 0;
    //return first element of high score list (highest score)
    } else {
        return front->score; 
    }
}

/* 
 * print
 * 
 * Prints entire high score list 
 * args: nothing 
 * returns: nothing 
 */
void HighScoresList::print() {

    Node *curr = front;

    //loop through high score list 
    while (curr != NULL) {
        //print user's name and user's score
        cout << curr->user << " " << curr->score << endl;
        curr = curr->next; 
    }

}

/* 
 * printTop5
 * 
 * Prints top 5 high scores of high score list 
 * args: nothing 
 * returns: nothing 
 */
void HighScoresList::printTop5() {

   Node *curr = front; 
   int count = 0; 

   //print every user's name and score five times through 
    while (curr != NULL && count < 5) {
        cout << curr->user << " " << curr->score << endl;
        curr = curr->next; 
        count ++; 
    }

}

/* 
 * keepTop10
 * 
 * Keeps top 10 high scores in high score list and deletes rest 
 * args: nothing 
 * returns: nothing 
 */
void HighScoresList::keepTop10() {
//SOMETHING WRONG HERE
    Node *curr = front; 
    int count = 0; 
    Node *temp;
    Node *last_score;

    //find the 10th element in the high score list
    while (curr != NULL && count < 10) {
        last_score = curr;
        curr = curr->next; 
        count ++;
    }

    //delete everything after 10th element 
    while (curr != NULL) {
        temp = curr->next; 
        delete curr; 
        curr = temp; 
    }

    //set 10th element pointer to NULL 
    last_score->next = NULL;
}

/* 
 * insert
 * 
 * Inserts new user name and score into high score list in 
 * correct order 
 * args: user's name and user's score  
 * returns: nothing 
 */
void HighScoresList::insert(std::string user, int score) {
    Node *curr = front; 
    Node *input = new Node; //create new memory for new input
    Node *after = NULL; //pointer to element after input
    Node *prev = NULL; //pointer to element before input
    //initialize input name and score 
    input->user = user; 
    input->score = score;
    while (curr != NULL) 
    {
        //highest score less than input score
        if (curr->score < score) 
        {
            after = curr; 
            break;
        } else {
            prev = curr;
        }
    curr = curr->next; 
    }
    //if inputted score is new high score
    if (prev == NULL)
    {
        front = input; 
        input->next = after; 
    //update new pointers 
    } else {
        input->next = after; 
        prev->next = input;
    }
}

/* 
 * clear
 * 
 * Clears all scores in high score list  
 * args: nothing 
 * returns: nothing 
 */
void HighScoresList::clear() {

    while (front != NULL) {
        //create temporary node to delete each element
        Node *temp = front-> next; 
        delete front;
        front = temp;
    }

}

/* 
 * printUser
 * 
 * Prints all scores associated with inputted user name  
 * args: user's name  
 * returns: nothing 
 */
void HighScoresList::printUser(std::string user) {
    Node *curr = front; 

    //loop through high score list 
    while (curr != NULL) 
    {
        //if user matches input, print user's score 
        if (curr->user == user) 
        {
            cout << curr->score << endl;
        }
        curr = curr->next; 
    }

}
