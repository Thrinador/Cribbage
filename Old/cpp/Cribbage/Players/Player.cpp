/*--------------------------------------------------------------------
// file name:	Player.cpp
// authors:     Ben Clark, Polina Eremenko
// date:		07/02/2017
// description: A representation of a player in a Cribbage game. Player
//              is a pure abstract class and only serves as a mold for
//              board to call upon.
//--------------------------------------------------------------------*/

#pragma once
#include "Player.h"

using namespace std;

/*------------------------------------------------------------------
// name:		calculateHandScore
// description:	given a hand and a cut calculates the number of points
//              earned. returns a vector that contains where they recived
//              points in each catagory.
// parameters:	vector of cards thats the hand, and Card that represents the
//              cut.
// called by:	Board::play
//----------------------------------------------------------------*/
Score calculateHandScore(vector<Card> hand, Card cut, int pegging) {
    Score score;
    vector<Card> fullHand = hand;
    fullHand.push_back(cut);
    
    score.fifteens = score15(fullHand);
    score.flush = scoreFlush(hand, cut);
    score.runs = scoreRuns(fullHand);
    score.nubs = scoreNubs(hand, cut);
    score.ofAKind = scoreOfAKind(fullHand);
    score.pegging = pegging;
    return score;
}

/*------------------------------------------------------------------
// name:		find15
// description:	helper method for score15
// parameters:	A vector of Cards, the current index in the array we are
//              at. The current sum that has been scored, and the amount
//              of points they have recived.
// called by:	score15
//----------------------------------------------------------------*/
int find15(const vector<Card> numbers, int index, int sum, int score) {
    if (sum > 15) return score;
    if (sum == 15) return score + 2;
    if (index == numbers.size()) return score;

    //Left half is the inclusive. Right half is the exclusive.
    return find15(numbers, index + 1, sum + numbers[index].value, score) + find15(numbers, index + 1, sum, score);
}

/*------------------------------------------------------------------
// name:		score15
// description:	given a hand calculates the number of points earned from 15's.
// parameters:	vector of Cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int score15(const vector<Card> hand) {
    return find15(hand,0,0,0);
}

/*------------------------------------------------------------------
// name:		scoreflush
// description:	given a hand of Cards and a cut calculates the number of
//              points earned from a flush.
// parameters:	vector of cards and cut to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreFlush(const vector<Card> hand, Card cut) {
    for (int i = 1; i < hand.size(); i++) {
        if (hand[i - 1].suit != hand[i].suit) {
            return 0;
        }
    }
    return (hand[0].suit == cut.suit) ? 5 : 4;
}

/*------------------------------------------------------------------
// name:		scoreNubs
// description:	given a hand of Cards and a cut calculates the number of
//              points earned from runs.
// parameters:	vector of cards and cut to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreNubs(const vector<Card> hand, Card cut) {
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i].id == 11 && hand[i].suit == cut.suit) {
            return 1;
        }
    }
    return 0;
}

/*------------------------------------------------------------------
// name:		scoreOfAKind
// description:	given a hand of Cards calculates the number of points earned
//              from pairs, 3 of a kind, and 4 of a kind.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore, scoreRuns
//----------------------------------------------------------------*/
int scoreOfAKind(vector<Card> hand) {
    int s = 0;

    for (int i = 0; i < hand.size(); i++) {
        int counter = 0;
        for (int j = i + 1; j < hand.size(); j++) {
            if (hand[i].id == hand[j].id) {
                counter++;
            }
        }
        //Pair
        if (counter == 1) {
            s += 2;
        }
        //3-of a kind
        else if (counter == 2) {
            s += 4;
        }
        //4 of a kind
        else if(counter == 3) {
            return 12;
        }
        counter = 0;
    }
    return s;
}

/*------------------------------------------------------------------
// name:		scoreRuns
// description:	given a hand of Cards calculates the number of points earned
//              from runs.
// parameters:	vector of cards that is the hand to be scored.
// called by:	calculateHandScore
//----------------------------------------------------------------*/
int scoreRuns(vector<Card> hand) {
    sort(hand);

    int multipiler = 1;
    int runLength = 1;
    int maxRunLength = 0;
    for (int i = 1; i < hand.size(); i++) {
        if (hand[i - 1].id == hand[i].id)
            multipiler++;
        else if (hand[i - 1].id + 1 == hand[i].id)
            runLength++;
        else {
            if (runLength > 2) break;
            else {
                multipiler = 1;
                runLength = 1;
            }
        }
    }
    if (multipiler == 3 && runLength > 2 && scoreOfAKind(hand) == 4) {
        //2 pair run
        multipiler++;
    }
    return (runLength > 2) ? (runLength * multipiler) : 0;
}

/*------------------------------------------------------------------
// name:		sort
// description:	given an address to a vector of Cards. Sorts the vector
// parameters:	location of vector to be sorted.
// called by:	scoreRuns
//----------------------------------------------------------------*/
void sort(vector<Card>& v) {
    bool swapped = true;
    int n = v.size();
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (v[i - 1] > v[i]) {
                Card temp = v.at(i-1);
                v[i-1] = v[i];
                v[i] = temp;
                swapped = true;
            }
        }
        n = n-1;
    }
}

bool Player::canPlay(int sum)
{
    for (int i = 0; i < playingHand.size(); i++) {
        if (playingHand[i].value + sum <= 31) {
            return true;
        }
    }
    return false;
}

void Player::print() {
    for (int i = 0; i < name.size(); i++) {
        cout << name[i];
    }

    for (int i = name.size(); i <= 10; i++) {
        cout << " ";
    }

    cout << ((score > 99) ? to_string(score) : (score > 9)
        ? to_string(score) + " " : to_string(score) + "  ");
}

void Player::resetHand(vector<Card>* newHand) {
    holdingHand = *newHand;
    playingHand = *newHand;
}

void Player::reset() {
    score = 0;
}
