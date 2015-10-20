/* Card_test00.cpp
 * 
 * Unit tests for Card
 *
 */

#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;


int main() {

  ////////////////////////////////////////
  // Suit_next() unit tests
  Suit s = Suit_next(HEARTS);
  assert(s == DIAMONDS);

  ////////////////////////////////////////
  // Card_init() unit tests
  Card queen_diamonds;
  Card_init(&queen_diamonds, QUEEN, DIAMONDS);
  assert(queen_diamonds.rank == QUEEN && queen_diamonds.suit == DIAMONDS);

  ////////////////////////////////////////
  // Card_print() unit tests (unchecked)
  Card_print(&queen_diamonds);
  cout << endl;

  ////////////////////////////////////////
  // Card_is_right_bower() unit tests
  Card jack_spades, jack_clubs;
  Card_init(&jack_spades, JACK, SPADES);
  Card_init(&jack_clubs, JACK, CLUBS);
  assert(Card_is_right_bower(&jack_spades, SPADES));
  assert(!Card_is_right_bower(&jack_spades, HEARTS));

  ////////////////////////////////////////
  // Card_is_left_bower() unit tests
  assert(Card_is_left_bower(&jack_clubs, SPADES));
  assert(!Card_is_left_bower(&jack_clubs, HEARTS));

  ////////////////////////////////////////
  // Card_is_trump() unit tests
  assert(Card_is_trump(&jack_clubs, SPADES));
  assert(!Card_is_trump(&jack_clubs, HEARTS));

  ////////////////////////////////////////
  // Card_compare() unit tests
  Card ace_diamonds, ace_hearts, jack_diamonds;
  Card_init(&ace_diamonds, ACE, DIAMONDS);
  Card_init(&ace_hearts, ACE, HEARTS);
  Card_init(&jack_diamonds, JACK, DIAMONDS);
  assert(Card_compare(&ace_diamonds, &ace_hearts) > 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds) > 0);

  ////////////////////////////////////////
  // Card_is_face() unit tests
  Card two_spades;
  Card_init(&two_spades, TWO, SPADES);
  assert(Card_is_face(&two_spades) == false);
  assert(Card_is_face(&ace_diamonds) == true);

  ////////////////////////////////////////
  // Card_get_suit() unit tests
  assert(Card_get_suit(&ace_diamonds, HEARTS) == DIAMONDS);
  assert(Card_get_suit(&jack_spades, SPADES) == SPADES);
  assert(Card_get_suit(&jack_spades, CLUBS) ==  CLUBS);
  assert(Card_get_suit(&jack_spades, DIAMONDS) == SPADES);

  ////////////////////////////////////////
  // Card_init() unit tests
  Card_init(&two_spades, "Two", "Spades");
  assert(two_spades.rank == TWO && two_spades.suit == SPADES);

  ////////////////////////////////////////
  // Card_compare() unit tests
  
  assert(Card_compare(&ace_diamonds, &ace_hearts, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, HEARTS) < 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds, DIAMONDS) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, SPADES) > 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, DIAMONDS) < 0);
  assert(Card_compare(&jack_clubs, &jack_spades, CLUBS) > 0);
  assert(Card_compare(&jack_clubs, &jack_spades, SPADES) < 0);
    

  ////////////////////////////////////////
  // Card_compare() unit tests
  Card nine_clubs = {NINE, CLUBS};
  Card nine_hearts = {NINE, HEARTS};
  Card nine_diamonds = {NINE, DIAMONDS};
  Card jack_hearts = {JACK, HEARTS};
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_clubs, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_clubs, HEARTS) < 0);
  assert(Card_compare(&ace_hearts, &ace_diamonds, &nine_clubs, DIAMONDS) < 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, &nine_clubs, SPADES) > 0);
  assert(Card_compare(&ace_diamonds, &jack_diamonds, &nine_clubs, DIAMONDS) < 0);
  assert(Card_compare(&jack_clubs, &jack_spades, &nine_diamonds, CLUBS) > 0);
  assert(Card_compare(&jack_clubs, &jack_spades, &nine_diamonds, SPADES) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_hearts, DIAMONDS) > 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_diamonds, HEARTS) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_hearts, CLUBS) < 0);
  assert(Card_compare(&ace_diamonds, &ace_hearts, &nine_diamonds, CLUBS) > 0);

  // ADD YOUR TEST CASES HERE
    
  ////////////////////////////////////////
  // Card_init() unit tests
  Card ace_clubs;
  Card_init(&ace_clubs, "Ace", "Clubs");
  assert(ace_clubs.rank == ACE && ace_clubs.suit == CLUBS);
    
  ////////////////////////////////////////
  // Card_compare() unit tests
  assert(Card_compare(&jack_spades, &ace_clubs, CLUBS) > 0);
  assert(Card_compare(&ace_clubs, &jack_spades, CLUBS) < 0);
  assert(Card_compare(&nine_diamonds, &queen_diamonds, DIAMONDS) < 0);
  assert(Card_compare(&queen_diamonds, &nine_diamonds, DIAMONDS) > 0);
  assert(Card_compare(&jack_diamonds, &jack_hearts, DIAMONDS) > 0);
    
  ////////////////////////////////////////
  // Card_compare() unit tests
  assert(Card_compare(&jack_diamonds, &ace_hearts, &nine_hearts, HEARTS) > 0);
  assert(Card_compare(&jack_hearts, &ace_diamonds, &nine_diamonds, HEARTS) > 0);
  assert(Card_compare(&jack_diamonds, &jack_hearts, &jack_diamonds, DIAMONDS) > 0);
    
  // if we got to the end without calling an assert(), the tests passed
  cout << "Card_test PASS" << endl;

  return 0;
}
