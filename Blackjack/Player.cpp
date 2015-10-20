/*
 *  Player.cpp
 *
 * Created by Pengyan Qin 
 * on 6/9/15.
 */

#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <stdlib.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
class SimplePlayer: public Player {
    //OVERVIEW: simple player plays a simplified version of basic strategy for blackjack
    
public:
    
    //EFFECTS: creates a simple player
    SimplePlayer();
    
    // REQUIRES: bankroll >= minimum
    //           bankroll >= 0
    //           minimum >= 0
    // EFFECTS: returns the player's bet, the simple player always palces t
    //           he minimum allowable wager
    virtual int bet(int bankroll, int minimum);
    
    // EFFECTS: returns true if the player wishes to be dealt another
    //          card, false otherwise.
    virtual bool draw(
                      Card dealer, // Dealer's "up card"
                      const Hand &player // Player's current hand
    );
    
    virtual void expose(Card c);
    virtual void shuffled();
    ~SimplePlayer();

};

/////////////////////////////////////////////////////////////////////////////////////////
class CountPlayer: public Player {
    //OVERVIEW: count player plays a developed strategy
    
public:
    
    //EFFECTS: creates a count player with count = 0
    CountPlayer();
    
    // REQUIRES: bankroll >= minimum
    //           bankroll >= 0
    //           minimum >= 0
    // EFFECTS: when the count is +2 or greater, bets double of minimum
    //          otherwise, bets the minimum
    virtual int bet(int bankroll, int minimum);
    
    // EFFECTS: returns true if the player wishes to be dealt another
    //          card, false otherwise.
    virtual bool draw(
                      Card dealer, // Dealer's "up card"
                      const Hand &player // Player's current hand
    );
    
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    virtual void expose(Card c);
    
    // EFFECTS: tells the player that the deck has been re-shuffled.
    virtual void shuffled();
    
    ~CountPlayer();
    
private:
    int count;
};

/////////////////////////////////////////////////////////////////////////////////////////
class CompetitorPlayer: public Player {
    //OVERVIEW: count player plays a basic strategy but with competitive wager
    
public:
    
    //EFFECTS: creates a competitor player
    CompetitorPlayer();
    
    // REQUIRES: bankroll >= minimum
    //           bankroll >= 0
    //           minimum >= 0
    // EFFECTS:returns the player's bet, the competitor player always places
    //         the double of the minimum, if the player does not have double
    //         the minimum in his bankroll, then he should bet all his entire bankroll
    virtual int bet(int bankroll, int minimum);
    
    // EFFECTS: returns true if the player wishes to be dealt another
    //          card, false otherwise.
    virtual bool draw(
                      Card dealer, // Dealer's "up card"
                      const Hand &player // Player's current hand
    );
    
    virtual void expose(Card c);
    
    virtual void shuffled();
    
    ~CompetitorPlayer();
    
};

/////////////////////////////////////////////////////////////////////////////////////////
// Simple Player Implementation

SimplePlayer::SimplePlayer(){}

int SimplePlayer::bet(int bankroll, int minimum){
    assert(bankroll >= minimum);
    assert(bankroll >= 0);
    assert(minimum >= 0);
    return minimum;
}

bool SimplePlayer::draw(Card dealer, const Hand &player){
    if(!player.hand_is_soft()){
        if(player.hand_value() <= 11)
            return true;
        else if(player.hand_value() == 12){
            if(dealer.get_rank() >= Card::FOUR && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 13 && player.hand_value() <= 16){
            if(dealer.get_rank() >= Card::TWO && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 17)
            return false;
    
    }
    else{
        if(player.hand_value() <= 17)
            return true;
        else if(player.hand_value() == 18){
            if(dealer.get_rank() == Card::FOUR || dealer.get_rank() == Card::SEVEN || dealer.get_rank() == Card::EIGHT)
                return false;
            else
                return true;
        }
        if(player.hand_value() >= 19)
            return false;
    }
    return false;
}

void SimplePlayer::expose(Card c){
    
    return;
}

void SimplePlayer::shuffled(){
    
    return;
}

SimplePlayer::~SimplePlayer(){}

/////////////////////////////////////////////////////////////////////////////////////////
// Count Player Implementation
CountPlayer::CountPlayer():count(0){}

int CountPlayer::bet(int bankroll, int minimum){
    assert(bankroll >= minimum);
    assert(bankroll >= 0);
    assert(minimum >= 0);
    if(count >= 2){
        if(bankroll < 2*minimum)
            return bankroll;
        else
            return 2*minimum;
    }
    else{
        return minimum;
    }
}

bool CountPlayer::draw(Card dealer, const Hand &player){
    if(!player.hand_is_soft()){
        if(player.hand_value() <= 11)
            return true;
        else if(player.hand_value() == 12){
            if(dealer.get_rank() >= Card::FOUR && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 13 && player.hand_value() <= 16){
            if(dealer.get_rank() >= Card::TWO && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 17)
            return false;
        
    }
    else{
        if(player.hand_value() <= 17)
            return true;
        else if(player.hand_value() == 18){
            if(dealer.get_rank() == Card::FOUR || dealer.get_rank() == Card::SEVEN || dealer.get_rank() == Card::EIGHT)
                return false;
            else
                return true;
        }
        if(player.hand_value() >= 19)
            return false;
    }
    return false;
}

void CountPlayer::expose(Card c){
    if(c.get_rank() >= Card::TEN && c.get_rank() <= Card::ACE)
        count--;
    else if(c.get_rank() >= Card::TWO && c.get_rank() <= Card::SIX)
        count++;
    
    return;
}

void CountPlayer::shuffled(){
    count = 0;
    return;
    
}

CountPlayer::~CountPlayer(){}

/////////////////////////////////////////////////////////////////////////////////////////
// Competitor Player Implementation

CompetitorPlayer::CompetitorPlayer(){}

int CompetitorPlayer::bet(int bankroll, int minimum){
    assert(bankroll >= minimum);
    assert(bankroll >= 0);
    assert(minimum >= 0);
    if(bankroll > 2*minimum)
        return 2*minimum;
    else
        return bankroll;
}

bool CompetitorPlayer::draw(Card dealer, const Hand &player){
    if(!player.hand_is_soft()){
        if(player.hand_value() <= 11)
            return true;
        else if(player.hand_value() == 12){
            if(dealer.get_rank() >= Card::FOUR && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 13 && player.hand_value() <= 16){
            if(dealer.get_rank() >= Card::TWO && dealer.get_rank() <= Card::SIX)
                return false;
            else
                return true;
        }
        else if(player.hand_value() >= 17)
            return false;
        
    }
    else{
        if(player.hand_value() <= 17)
            return true;
        else if(player.hand_value() == 18){
            if(dealer.get_rank() == Card::FOUR || dealer.get_rank() == Card::SEVEN || dealer.get_rank() == Card::EIGHT)
                return false;
            else
                return true;
        }
        if(player.hand_value() >= 19)
            return false;
    }
    return false;
}

void CompetitorPlayer::expose(Card c){
    
    return;
}

void CompetitorPlayer::shuffled(){
    
    return;
}

CompetitorPlayer::~CompetitorPlayer(){}

/////////////////////////////////////////////////////////////////////////////////////////
// REQUIRES: s is a C-string: "simple" "counting" or "competitor"
// EFFECTS: returns a pointer to the specified Player

static SimplePlayer sp;
static CountPlayer cp;
static CompetitorPlayer cop;

Player * player_factory(const char * s){
    if(strcmp(s,"simple") != 0 && strcmp(s,"counting") != 0 && strcmp(s,"competitor") != 0 ){
        cout << "the input is not valid! " << endl;
        exit(EXIT_FAILURE);
    }
    
    if(!strcmp(s,"simple"))
        return &sp;
    else if(!strcmp(s,"counting"))
        return &cp;
    else
        return &cop;

}





