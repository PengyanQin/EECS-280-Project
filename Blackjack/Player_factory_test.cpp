#include "Player.h"
#include "Card.h"

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

//------------------------------------------------------------------------------

static void expose_and_check_player_bet(
    Player* player, Card to_expose,
    int times_to_expose, int bankroll, int minimum, int expected_bet);

//------------------------------------------------------------------------------

int main()
{
    Card two(Card::TWO, Card::SPADES);

    cout << "Testing simple player..." << endl;
    Player* simple = player_factory("simple");
    assert(simple);
    expose_and_check_player_bet(simple, two, 20, 100, 10, 10);
    cout << "Simple player OK" << endl;

    cout << "Testing counting player..." << endl;
    Player* counting = player_factory("counting");
    assert(counting);
    assert(counting != simple);
    expose_and_check_player_bet(counting, two, 20, 100, 10, 20);
    cout << "Counting player OK" << endl;

    cout << "Testing competitor..." << endl;
    Player* competitor = player_factory("competitor");
    assert(competitor);
    assert(competitor != simple);
    assert(competitor != counting);
    cout << "Competitor OK" << endl;
    
    cout << "PASS" << endl;

    return 0;
}// main

//------------------------------------------------------------------------------

static void expose_and_check_player_bet(
    Player* player, Card to_expose,
    int times_to_expose, int bankroll, int minimum, int expected_bet)
{
    for (int i = 0; i < times_to_expose; ++i)
    {
        player->expose(to_expose);
    }

    int actual_bet = player->bet(bankroll, minimum);

    cout << "Expected bet: " << expected_bet << endl;
    cout << "Actual bet: " << actual_bet << endl;

    assert(expected_bet == actual_bet);
}// expose_and_check_player_bet
