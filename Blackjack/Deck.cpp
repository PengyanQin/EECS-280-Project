/*
 *  Deck.cpp
 *
 * Created by Pengyan Qin
 * on 6/8/15.
 */

#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <cassert>

using namespace std;

const int SUIT_SIZE = 4;
const int RANK_SIZE = 13;

////////////////////////////////////////////////////////////////////////////////

Deck::Deck(){
    int k = 0;
    for (int i = 0; i < SUIT_SIZE; ++i){
        for(int j = 0; j < RANK_SIZE; ++j){
            Card::Suit suit_n = static_cast <Card::Suit> (i);
            Card::Rank rank_n = static_cast <Card::Rank> (j);
            cards[k] = Card(rank_n, suit_n);
            ++k;
        }
    }
    next = &cards[0];
}

void Deck::reset(){
    int k = 0;
    for (int i = 0; i < SUIT_SIZE; ++i){
        for(int j = 0; j < RANK_SIZE; ++j){
            Card::Suit suit_n = static_cast <Card::Suit> (i);
            Card::Rank rank_n = static_cast <Card::Rank> (j);
            cards[k] = Card(rank_n, suit_n);
            ++k;
        }
    }
    next = &cards[0];
}

void Deck::shuffle(int n){
    assert(n >= 0);
    assert(n <= 52);
    
    if((n == 0) || (n == 52)){
        next = &cards[0];
        return;
    }
    int k = 0;
    Card *tmp = new Card[n];
    for(int i = 0; i < n; ++i){
        tmp[i] = cards[i];
    }
    
    if(n <= 26){
        for(int i = 0; i < n; ++i){
            cards[k++] = cards[i + n];
            cards[k++] = tmp[i];
        }
    }
    else{
        for(int i = 0; i < n; ++i){
            if((i + n) < 52){
                cards[k++] = cards[i + n];
                cards[k++] = tmp[i];
            }
            else{
                cards[k++] = tmp[i];
            }
        }
    }
    next = &cards[0];
    delete[] tmp;
}

Card Deck::deal(){
    assert(cards_remaining());
    Card dealt;
    int i = 0;
    for(; i < DECK_SIZE; ++i){
        if(&cards[i] == next){
            dealt = *next;
            break;
        }
    }
    if( i < 51)
        next = &cards[i + 1];
    else
        next = 0;
    
    return dealt;
}

int Deck::cards_remaining() const{
    int i = 0;
    for(; i < DECK_SIZE; ++i){
        if(&cards[i] == next){
            break;
        }
    }
    return (DECK_SIZE - i);
}







