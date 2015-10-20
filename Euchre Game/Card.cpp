/* Card.cpp
 *
 * Represents a single playing card
 *
 */


#include "Card.h"
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
const char *const SUIT_NAMES[] = {"Spades", "Hearts", "Clubs", "Diamonds"};
const int SUIT_SIZE = 4;
const char *const RANK_NAMES[] = {"Two", "Three", "Four", "Five", "Six", 
                                  "Seven", "Eight", "Nine", "Ten", "Jack", 
                                  "Queen", "King", "Ace"};
const int RANK_SIZE = 13;
const int CHECK = 1000;

////////////////////////////////////////////////////////////////////////////////
void Suit_print(Suit suit) {
  cout << SUIT_NAMES[suit];
}

Suit Suit_next(Suit suit) {
  switch (suit) {
  case SPADES:   return CLUBS;
  case HEARTS:   return DIAMONDS;
  case CLUBS:    return SPADES;
  case DIAMONDS: return HEARTS;
  default:       assert(0); return SPADES; // should never get here
  }
}


////////////////////////////////////////////////////////////////////////////////
// Card

void Card_init(Card *card_ptr, Rank rank, Suit suit) {
  card_ptr->rank = rank;
  card_ptr->suit = suit;
}

void Card_print(const Card *card_ptr) {
  cout << RANK_NAMES[card_ptr->rank] << " of " << SUIT_NAMES[card_ptr->suit];
}

Suit Card_get_suit(const Card *card_ptr, Suit trump) {
  if (Card_is_left_bower(card_ptr, trump)) return trump;
  return card_ptr->suit;
}

bool Card_is_face(const Card *card_ptr) {
  return
    card_ptr->rank == JACK ||
    card_ptr->rank == QUEEN ||
    card_ptr->rank == KING ||
    card_ptr->rank == ACE;
}

bool Card_is_right_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK && card_ptr->suit == trump; // JACK of trump suit
}

bool Card_is_left_bower(const Card *card_ptr, Suit trump) {
  return card_ptr->rank == JACK && 
    card_ptr->suit == Suit_next(trump); // JACK of trump's color
}

bool Card_is_trump(const Card *card_ptr, Suit trump) {
  return card_ptr->suit == trump ||
    Card_is_left_bower(card_ptr,trump);
}

int Card_compare(const Card *a, const Card *b) {

  // sanity check for NULL pointers
  assert(a);
  assert(b);

  // To simplify debugging and ensure that every correct solution will get the
  // same output, we’ve added an additional rule here.  In addition to being
  // ordered by rank, cards are also ordered by suit.
  return (a->suit + a->rank*SUIT_SIZE)
    -  (b->suit + b->rank*SUIT_SIZE);
}

template <typename T>
T string2enum(const char* s, const char *const names[],int size){
    for(int i=0; i<size; ++i)
        if(strcmp(s,names[i]) == 0)
            return static_cast<T>(i);
    assert(0);
    exit(1);
}

void Card_init(Card *card_ptr, const char* rank, const char* suit) {
    Rank rank_n = string2enum<Rank>(rank, RANK_NAMES, RANK_SIZE);
    Suit suit_n = string2enum<Suit>(suit, SUIT_NAMES, SUIT_SIZE);
    card_ptr->rank = rank_n;
    card_ptr->suit = suit_n;
}

int Card_compare(const Card *a, const Card *b, Suit trump) {
    assert(a);
    assert(b);
    
    if(Card_is_trump(a, trump) && !Card_is_trump(b, trump))
        return 1;
    if(!Card_is_trump(a, trump) && Card_is_trump(b, trump))
        return -1;
    if(!Card_is_trump(a, trump) && !Card_is_trump(b, trump))
        return Card_compare(a, b);
    if(Card_is_trump(a, trump) && Card_is_trump(b, trump)){
        if(a->rank == JACK || b->rank == JACK){
            if(Card_is_right_bower(a, trump))
                return 1;
            if(Card_is_right_bower(b, trump))
                return -1;
            if(Card_is_left_bower(a, trump))
                return 1;
            if(Card_is_left_bower(b, trump))
                return -1;
        }
        else
            return Card_compare(a,b);
    }
    return CHECK;
}

int Card_compare(const Card *a, const Card *b, const Card *led_card, Suit trump) {
    assert(a);
    assert(b);
    assert(led_card);
    
    if(Card_is_trump(led_card, trump)){
        return Card_compare(a, b, trump);
    }
    else{
        if((a->suit != led_card->suit && b->suit != led_card->suit) ||(a->suit == led_card->suit && b->suit == led_card->suit) )
            return Card_compare(a, b, trump);
        else{
            if(a->suit == led_card->suit){
                if(Card_is_trump(b, trump))
                    return -1;
                else
                    return 1;
            }
            if(b->suit == led_card->suit){
                if(Card_is_trump(a, trump))
                    return 1;
                else
                    return -1;
            }
        }
    }
    return CHECK;
}
