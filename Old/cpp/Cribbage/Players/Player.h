/*--------------------------------------------------------------------
// file name:	Player.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A representation of a player in a Cribbage game. Player
//              is a pure abstract class and only serves as a mold for
//              board to call upon.
//--------------------------------------------------------------------*/

#pragma once
#include "../Core/Card.h"
#include <string>
#include <vector>
#include "../Core/Score.h"

using namespace std;

class Player {

public:
    Player() : score(0), holdingHand(0), playingHand(0), name(""), turn(false) {};
    Player(bool turn) : score(0), holdingHand(0), playingHand(0), name(""), turn(turn) {};

    /*------------------------------------------------------------------
    // name:		addScore
    // description:	if the score they send is positive then it adds that to
    //              the computers total score.
    // parameters:	score to be added to total.
    // called by:	Board::play, Board::pegging
    //----------------------------------------------------------------*/
    void addScore(int newScore) { if (newScore > 0) score += newScore; }

    /*------------------------------------------------------------------
    // name:		canPlay
    // description:	checks to see if the player can play a card given
    //              what they have left in their playingHand and the current
    //              sum.
    // parameters:	int of the current pegging sum
    // called by:	playCard
    //----------------------------------------------------------------*/
    virtual bool canPlay(int sum);

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	gives the player a bool that represents whether or not it
    //              is their crib and asks them for a vector of cards to be
    //              put in the crib.
    // parameters:	bool of whoes crib it is.
    // called by:	Board::play
    //----------------------------------------------------------------*/
    virtual vector<Card> getCribCards(bool turn) = 0;

    /*------------------------------------------------------------------
    // name:		getHoldingHand
    // description:	gets the hand from the player.
    // parameters:	none
    // called by:	Board::play
    //----------------------------------------------------------------*/
    virtual vector<Card> getHoldingHand() { return holdingHand; }

    /*------------------------------------------------------------------
    // name:		getPlayingHand
    // description:	gets the hand from the player.
    // parameters:	none
    // called by:	Board::play
    //----------------------------------------------------------------*/
    virtual vector<Card> getPlayingHand() { return playingHand; }

    /*------------------------------------------------------------------
    // name:		getName
    // description:	Gets the name of the player.
    // parameters:	none
    // called by:	print
    //----------------------------------------------------------------*/
    string getName() { return name; }

    /*------------------------------------------------------------------
    // name:		getScore
    // description:	gets the players current score
    // parameters:	none
    // called by:	Board::hasWon, Board::play
    //----------------------------------------------------------------*/
    virtual int getScore() { return score; }

    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the player the past cards that have been played and
    //              the rounds current sum. Wants the player to choose a Card
    //              to play, if they can't play they return a default Card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    virtual Card playCard(vector<Card> pastCards, int sum) = 0;

    /*------------------------------------------------------------------
    // name:		print
    // description:	prints the name of the player and their score.
    // parameters:	none
    // called by:	Board::printRoundStart
    //----------------------------------------------------------------*/
    virtual void print();
    
    /*------------------------------------------------------------------
    // name:		resetHand
    // description:	resets the players hand by giving them a new vector.
    // parameters:	vector of Cards that is the players new hand.
    // called by:	Board::deal
    //----------------------------------------------------------------*/
    virtual void resetHand(vector<Card> *newHand);

    void reset();

protected:
    vector<Card> holdingHand;
    vector<Card> playingHand;
    int score;
    string name;
    bool turn;
};

/*------------------------------------------------------------------
// name:		calculateHandScore
// description:	given a hand and a cut calculates the number of points
//              earned. returns a vector that contains where they recived
//              points in each catagory.
// parameters:	vector of cards thats the hand, and Card that represents the
//              cut.
// called by:	Board::play
//----------------------------------------------------------------*/
Score calculateHandScore(vector<Card> hand, Card cut, int pegging);

/*------------------------------------------------------------------
// name:		find15
// description:	helper method for score15
// parameters:	A vector of Cards, the current index in the array we are
//              at. The current sum that has been scored, and the amount
//              of points they have recived.
// called by:	score15
//----------------------------------------------------------------*/
int find15(const vector<Card> numbers, int index, int sum, int score);

/*------------------------------------------------------------------
// name:		score15
// description:	given a hand calculates the number of points earned from 15's.
// parameters:	vector of Cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int score15(const vector<Card> hand);

/*------------------------------------------------------------------
// name:		scoreflush
// description:	given a hand of Cards and a cut calculates the number of
//              points earned from a flush.
// parameters:	vector of cards and cut to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreFlush(const vector<Card> hand, Card cut);

/*------------------------------------------------------------------
// name:		scoreNubs
// description:	given a hand of Cards and a cut calculates the number of 
//              points earned from runs.
// parameters:	vector of cards and cut to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreNubs(const vector<Card> hand, Card cut);

/*------------------------------------------------------------------
// name:		scoreOfAKind
// description:	given a hand of Cards calculates the number of points earned
//              from pairs, 3 of a kind, and 4 of a kind.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore, scoreRuns
//----------------------------------------------------------------*/
int scoreOfAKind(vector<Card> hand);

/*------------------------------------------------------------------
// name:		scoreRuns
// description:	given a hand of Cards calculates the number of points earned
//              from runs.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreRuns(vector<Card> hand);

/*------------------------------------------------------------------
// name:		sort
// description:	given an address to a vector of Cards. Sorts the vector
// parameters:	location of vector to be sorted.
// called by:	scoreRuns
//----------------------------------------------------------------*/
void sort(vector<Card> &v);