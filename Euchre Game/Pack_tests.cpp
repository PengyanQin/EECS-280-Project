/* Pack_test00.cpp
 * 
 * Unit tests for Card
 *
 */

#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {

  ////////////////////////////////////////
  // Pack_init() unit tests
  Pack pack;
  Pack_init(&pack, "pack.in");

  Card nine_spades = {NINE, SPADES};
  Card first_card = *(pack.next);
  assert(Card_compare(&first_card, &nine_spades) == 0);

  Card ace_diamonds = {ACE, DIAMONDS};
  Card last_card = *(pack.cards + PACK_SIZE - 1);
  assert(Card_compare(&last_card, &ace_diamonds) == 0);
    
  Card nine_hearts = {NINE, HEARTS};
  Card seventh_card = pack.cards[6];
  assert(Card_compare(&seventh_card, &nine_hearts) == 0);

  ////////////////////////////////////////
  // Pack_deal_one() unit tests
  Card c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &nine_spades) == 0 );
  assert(Card_compare(&first_card, &nine_spades) == 0);

  Card ten_spades = {TEN, SPADES};
  c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &ten_spades) == 0 );
    
  Card jack_spades = {JACK, SPADES};
  Card queen_spades = {QUEEN, SPADES};
  c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &jack_spades) == 0 );
  assert( Card_compare(pack.next, &queen_spades) == 0 );

  ////////////////////////////////////////
  // Pack_reset() unit tests
  Card cur_card = *(pack.next);
  assert(Card_compare(&cur_card, &nine_spades) != 0);
  Pack_reset(&pack);
  first_card = *(pack.next);
  assert(Card_compare(&first_card, &nine_spades) == 0);
    
  c = Pack_deal_one(&pack);
  c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &ten_spades) == 0 );


  ////////////////////////////////////////
  // Pack_shuffle() unit tests
  Pack_shuffle(&pack);

  first_card = *(pack.next);
  assert(Card_compare(&first_card, &queen_spades) == 0);

  last_card = *(pack.cards + PACK_SIZE - 1);
  assert(Card_compare(&last_card, &jack_spades) == 0);

 
  // if we got to the end without calling an assert(), the tests passed
  cout << "Pack_test PASS" << endl;

  return 0;
}
