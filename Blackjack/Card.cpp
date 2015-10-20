/*
 *  Card.cpp
 *
 * Created by Pengyan Qin
 * on 6/8/15.
 */
 #include "Card.h"
 #include <iostream>
 #include <cassert>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
Card::Card():rank(Card::TWO), suit(Card::SPADES){}

Card::Card(Rank rank_in, Suit suit_in): rank(rank_in), suit(suit_in){}

Card::Rank Card::get_rank() const{
    return rank;
}

Card::Suit Card::get_suit() const{
    return suit;
}

////////////////////////////////////////////////////////////////////////////////
const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six",
                                "Seven", "Eight", "Nine", "Ten", "Jack",
                                "Queen", "King", "Ace"};
std::ostream& operator<< (std::ostream& os, const Card& c){
    os << RANK_NAMES[c.get_rank()] << " of " << SUIT_NAMES[c.get_suit()];
    return os;
}

