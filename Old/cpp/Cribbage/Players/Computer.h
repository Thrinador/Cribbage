/*--------------------------------------------------------------------
// file name:	Computer.h
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A simple computer, that plays cribbage.
// variables:   holdingHand which is the hand that gets calculated at the 
//              end of each round. playingHand which is a copy of 
//              holdingHand used for pegging. score which is the computer's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"
#include "../Core/Deck.h"

class Computer : public Player {

public:
    Computer() { this->name = "Easy Bot"; }

    /*------------------------------------------------------------------
    // name:		getCribCards
    // description:	gives the computer a bool that represents whether or not it
    //              is their crib and asks them for a vector of cards to be
    //              put in the crib.
    // parameters:	bool of whose crib it is.
    // called by:	Board::play
    //----------------------------------------------------------------*/
    vector<Card> getCribCards(bool turn);

    /*------------------------------------------------------------------
    // name:		playCard
    // description:	gives the computer the past cards that have been played and
    //              the rounds current sum. Computer always plays the first card.
    // parameters:	vector of cards that have been played, and int of current sum
    // called by:	Board::pegging
    //----------------------------------------------------------------*/
    Card playCard(vector<Card> pastCards, int sum);

protected:
    vector<Card> getPartialHand(int i, int j);

    int calculatePartialHandScore(vector<Card> partialHand);

    double calculateCutValue(vector<Card> partialHand);

    double calculateCribCardValue(Card c1, Card c2);

    bool cardInHand(Card c, vector<Card> hand);

    Card pegRun(vector<Card> pastCards, int sum);

    Card pegPair(vector<Card> pastCards, int sum);

    Card peg15Or31(vector<Card> pastCards, int sum);

    Card pegAnyCard(vector<Card> pastCards, int sum);

    int checkCardsType(vector<Card> &partPastCards);
};



int scoreFlush(const vector<Card> hand);
