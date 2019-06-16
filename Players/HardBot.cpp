/*--------------------------------------------------------------------
// file name:	Computer.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A simple computer, that plays cribbage.
// variables:   holdingHand which is the hand that gets calculated at the
//              end of each round. playingHand which is a copy of
//              holdingHand used for pegging. score which is the computer's
//              current score.
//--------------------------------------------------------------------*/

#pragma once
#include "HardBot.h"

/*------------------------------------------------------------------
// name:		getCribCards
// description:	gives the computer a bool that represents whether or not it
//              is their crib and asks them for a vector of cards to be
//              put in the crib.
// parameters:	bool of whose crib it is.
// called by:	Board::play
//----------------------------------------------------------------*/
vector<Card> HardBot::getCribCards(bool turn) {
    vector<Card> cribCards;
    cribCards.push_back(holdingHand.at(0));
    cribCards.push_back(holdingHand.at(1));

    holdingHand.erase(holdingHand.begin());
    holdingHand.erase(holdingHand.begin());

    playingHand = holdingHand;
    return cribCards;
}

/*------------------------------------------------------------------
// name:		playCard
// description:	gives the computer the past cards that have been played and
//              the rounds current sum. Computer always plays the first card.
// parameters:	vector of cards that have been played, and int of current sum
// called by:	Board::pegging
//----------------------------------------------------------------*/
Card HardBot::playCard(vector<Card> pastCards, int sum) {
    for (unsigned int i = 0; i < playingHand.size(); i++) {
        Card choice = playingHand[i];
        if (choice.value + sum <= 31) {
            playingHand.erase(playingHand.begin() + i);
            return choice;
        }
    }
    //Can't Play
    return Card();
}