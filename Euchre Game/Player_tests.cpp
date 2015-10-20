/* Player_test00.cpp
 * 
 * Unit tests for Player
 *
 */

#include "Player.h"
#include "Card.h"
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

// REQUIRES: player_ptr->handsize == MAX_HAND_SIZE, since we don't know how 
//           discarded / played cards are being dealt with
// MODIFIES:
// EFFECTS: Returns true if *card_ptr is in player_ptr->hand, false otherwise
bool Player_has_card_in_hand(const Card* card_ptr, const Player* player_ptr) {
  for (int i = 0; i < player_ptr->hand_size; i++) {
    if (Card_compare(card_ptr, &player_ptr->hand[i]) == 0) {
      return true;
    }
  }
  return false;
}

void test_maketrump_first_leftbower_nofacecard(){
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = SPADES;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, CLUBS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {NINE, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == false);
    assert(order_up_suit == SPADES);
}

void test_maketrump_first_leftbower_king(){
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = CLUBS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, CLUBS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {KING, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == SPADES);
}

void test_maketrump_first_rightbower_nofacecard(){
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = SPADES;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, SPADES},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {NINE, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == false);
    assert(order_up_suit == SPADES);
}

void test_maketrump_first_rightbower_king(){
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, SPADES},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {KING, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == SPADES);
}

void test_maketrump_second_rightbower(){
    Player alice;
    Player_init(&alice, "Alice");

    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, CLUBS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {NINE, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &alice,            //Alice is the dealer
     2,               //second round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == CLUBS);
}

void test_maketrump_second_leftbower(){
    Player alice;
    Player_init(&alice, "Alice");
    
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, DIAMONDS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {JACK, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &alice,            //Alice is the dealer
     2,               //second round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == CLUBS);
}

void test_maketrump_second_nofacecard(){
    Player alice;
    Player_init(&alice, "Alice");
    
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, DIAMONDS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {KING, SPADES}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &alice,            //Alice is the dealer
     2,               //second round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == false);
    assert(order_up_suit == HEARTS);
}

void test_maketrump_second_facecard(){
    Player alice;
    Player_init(&alice, "Alice");
    
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, DIAMONDS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {KING, CLUBS}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &alice,            //Alice is the dealer
     2,               //second round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == CLUBS);
}

void test_maketrump_second_screwthedealer(){
    Card nine_spades;    // up card
    Card_init(&nine_spades, NINE, SPADES);
    Suit order_up_suit = HEARTS;
    
    Card in_hand[MAX_HAND_SIZE] =
    { {JACK, DIAMONDS},
        {JACK, HEARTS},
        {KING, HEARTS},
        {QUEEN, HEARTS},
        {NINE, CLUBS}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     2,               //second round
     &order_up_suit   //suit ordered up
     );
    
    assert(bob_response == true);
    assert(order_up_suit == CLUBS);
}

void test_add_and_discard_3_discard(){
    Card jack_hearts = {JACK, HEARTS};
    
    Card in_hand[3] =
    { {JACK, DIAMONDS},
        {NINE, HEARTS},
        {ACE, DIAMONDS}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<3; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Player_add_and_discard(&bob, &jack_hearts);
    assert(bob.hand_size == 3);
    assert(Player_has_card_in_hand(&jack_hearts, &bob)); //ensure he picked it up
    for (int i=0; i<bob.hand_size-1; ++i) //ignore that first Ten Spades
        assert(Player_has_card_in_hand(in_hand + i, &bob));
    
}

void test_lead_Card_nontrump(){
    Card in_hand[4] =
    { {JACK, DIAMONDS},
        {ACE, CLUBS},
        {QUEEN, CLUBS},
        {NINE, DIAMONDS}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<4; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card card_led = Player_lead_card(&bob, SPADES);
    Card ace_clubs = {ACE, CLUBS};
    assert(Card_compare(&card_led, &ace_clubs) == 0); //check led card
    assert(bob.hand_size == 3); //should have one less card
    assert(!Player_has_card_in_hand(&ace_clubs, &bob)); //check discarded
}
void test_lead_Card_both(){
    Card in_hand[5] =
    { {JACK, SPADES},
        {QUEEN, SPADES},
        {TEN, DIAMONDS},
        {JACK, CLUBS},
        {TEN, HEARTS},};
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<5; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card card_led = Player_lead_card(&bob, SPADES);
    Card ten_diamonds = {TEN, DIAMONDS};
    assert(Card_compare(&card_led, &ten_diamonds) == 0); //check led card
    assert(bob.hand_size == 4); //should have one less card
    assert(!Player_has_card_in_hand(&ten_diamonds, &bob)); //check discarded
}

void test_play_card_case1(){
    // suit = trump, the card in hand is suit + trump, choose the largest follow suit
    Card in_hand[4] =
    { {JACK, SPADES},
        {JACK, CLUBS},
        {QUEEN, SPADES},
        {ACE, HEARTS},};
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<4; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card nine_spades = {NINE, SPADES};
    Card jack_spades = {JACK, SPADES};
    Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &nine_spades,  //spades is led
     SPADES);         //Spades is trump
    assert(Card_compare(&card_played, &jack_spades) == 0);
    assert(bob.hand_size == 3);
    assert(!Player_has_card_in_hand(&jack_spades, &bob));
}

void test_play_card_case2(){
    // suit != trump, the card in hand is suit + trump, choose the largest follow suit
    Card in_hand[4] =
    { {JACK, SPADES},
        {JACK, CLUBS},
        {NINE, HEARTS},
        {NINE, DIAMONDS},};
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<4; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card queen_hearts = {QUEEN, HEARTS};
    Card nine_hearts = {NINE, HEARTS};
    Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &queen_hearts,  //hearts is led
     SPADES);         //Spades is trump
    assert(Card_compare(&card_played, &nine_hearts) == 0);
    assert(bob.hand_size == 3);
    assert(!Player_has_card_in_hand(&nine_hearts, &bob));
}

void test_play_card_case3(){
    // suit != trump, the card in hand is suit, choose the largest follow suit
    Card in_hand[3] =
    { {KING, HEARTS},
        {ACE, HEARTS},
        {NINE, HEARTS},};
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<3; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card queen_hearts = {QUEEN, HEARTS};
    Card ace_hearts = {ACE, HEARTS};
    Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &queen_hearts,  //hearts is led
     SPADES);         //Spades is trump
    assert(Card_compare(&card_played, &ace_hearts) == 0);
    assert(bob.hand_size == 2);
    assert(!Player_has_card_in_hand(&ace_hearts, &bob));
}

void test_play_card_case4(){
    // suit != trump, the card in hand is no suit, choose the lowest card
    Card in_hand[4] =
    { {JACK, SPADES},
        {ACE, HEARTS},
        {NINE, HEARTS},
        {NINE, DIAMONDS}, };
    Player bob;
    Player_init(&bob, "Bob");
    for (int i=0; i<4; ++i)
        Player_add_card(&bob, &in_hand[i]);
    
    Card queen_clubs = {QUEEN, CLUBS};
    Card nine_hearts = {NINE, HEARTS};
    Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &queen_clubs,  //hearts is led
     SPADES);         //Spades is trump
    assert(Card_compare(&card_played, &nine_hearts) == 0);
    assert(bob.hand_size == 3);
    assert(!Player_has_card_in_hand(&nine_hearts, &bob));
}

int main() {

  ////////////////////////////////////////
  // Player_init() unit tests
  Player alice;
  Player_init(&alice, "Alice");
  assert( strcmp(alice.name, "Alice") == 0 );
  assert( alice.hand_size == 0 );

  Player drew;
  Player_init(&drew, "Drew");
  assert( strcmp(drew.name, "Drew") == 0 );
  assert( drew.hand_size == 0 );
  

  ////////////////////////////////////////
  // Player_add_card() unit tests

  // Create player Bob and give him an awesome hand for Spades trump
  Card awesome_spades_hand[MAX_HAND_SIZE] = 
    { {TEN, SPADES},
      {KING, SPADES},
      {ACE, SPADES},
      {JACK, CLUBS},
      {JACK, SPADES}, };
  Player bob;
  Player_init(&bob, "Bob");
  for (int i=0; i<MAX_HAND_SIZE; ++i) {
    Player_add_card(&bob, &awesome_spades_hand[i]);
    assert(bob.hand_size == i+1);
  }

  // Check that Bob's hand actually has all those spades
  assert(bob.hand_size == MAX_HAND_SIZE);
  for (int i=0; i<MAX_HAND_SIZE; ++i)
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));


  ////////////////////////////////////////
  // Player_make_trump() unit tests

  // Bob should order up Spades if the upcard is a low Spade
  Card nine_spades;
  Card_init(&nine_spades, NINE, SPADES);
  Suit order_up_suit = SPADES;
  bool bob_response = Player_make_trump
    (&bob,            //Player calling trump
     &nine_spades,    //upcard
     &bob,            //Bob is also the dealer
     1,               //first round
     &order_up_suit   //suit ordered up
     );
  assert(bob_response == true);
  assert(order_up_suit == SPADES);

  test_maketrump_first_leftbower_nofacecard();
  test_maketrump_first_leftbower_king();
  test_maketrump_first_rightbower_nofacecard();
  test_maketrump_first_rightbower_king();
  test_maketrump_second_rightbower();
  test_maketrump_second_leftbower();
  test_maketrump_second_nofacecard();
  test_maketrump_second_facecard();
  test_maketrump_second_screwthedealer();
  
  ////////////////////////////////////////
  // Player_add_and_discard() unit tests

  // Bob will throw away the upcard if it's lower than the cards in his hand
  Player_add_and_discard(&bob, &nine_spades);
  assert(bob.hand_size == 5);
  for (int i=0; i<bob.hand_size; ++i)
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));
    
  // Bob will pick up the Queen of Spades, since it's higher than his lowest
  Card queen_spades;
  Card_init(&queen_spades, QUEEN, SPADES);
  Player_add_and_discard(&bob, &queen_spades);
  assert(bob.hand_size == 5);
  assert(Player_has_card_in_hand(&queen_spades, &bob)); //ensure he picked it up
  for (int i=1; i<bob.hand_size; ++i) //ignore that first Ten Spades
    assert(Player_has_card_in_hand(awesome_spades_hand + i, &bob));

  test_add_and_discard_3_discard();
    

  ////////////////////////////////////////
  // Card Player_lead_card() unit tests

  // Bob has the right bower, the max, which he should play if spades is led
 
  Card card_led = Player_lead_card(&bob, SPADES);
  Card jack_spades;
  Card_init(&jack_spades, JACK, SPADES);
  assert(Card_compare(&card_led, &jack_spades) == 0); //check led card
  assert(bob.hand_size == 4); //should have one less card
  assert(!Player_has_card_in_hand(&jack_spades, &bob)); //check discarded
    
  test_lead_Card_nontrump();
  test_lead_Card_both();

  ////////////////////////////////////////
  // Player_play_card() unit tests
    
  // Bob has all spades, so he should play the min if Diamonds is led
  Card nine_diamonds = {NINE, DIAMONDS};
  Card card_played = Player_play_card
    (&bob,            //Bob plays the card
     &nine_diamonds,  //Diamonds is led
     SPADES);         //Spades is trump
  assert(Card_compare(&card_played, &queen_spades) == 0);
    
  test_play_card_case1();
  test_play_card_case2();
  test_play_card_case3();
  test_play_card_case4();

  // if we got to the end without calling an assert(), the tests passed
  cout << "Player_test PASS" << endl;

  return 0;
}
