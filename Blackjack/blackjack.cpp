/*
 *  blackjack.cpp
 *  Created by Pengyan Qin 
 *  on 6/10/15.
 */

#include "Card.h"
#include "Hand.h"
#include "Player.h"
#include "rand.h"
#include "Deck.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <stdlib.h>

using namespace std;

#define MINIMUM 5

int main(int argc, char *argv[]){
    if(argc != 4 || atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0 || (strcmp(argv[3],"simple") != 0 && strcmp(argv[3],"counting") != 0 && strcmp(argv[3],"competitor") != 0 )){
        cout << "Usage: blackjack <bankroll> <hands> [simple|counting|competitor]" << endl;
        return -1;
        exit (EXIT_FAILURE);
    }
    
    Deck d;
    cout << "Shuffling the deck" << endl;
    for(int i = 0; i < 7; ++i){
        int cut = get_cut();
        d.shuffle(cut);
        cout << "cut at " << cut << endl;
    }
   
    Player *player = player_factory(argv[3]);
    player->shuffled();
    
    int minimum = MINIMUM;
    int hand_tot = atoi(argv[2]);
    int bankroll = atoi(argv[1]);
    int thishand = 1;
    
    while(bankroll >= minimum && thishand <= hand_tot){
        cout << "Hand " << thishand << " " << "bankroll " << bankroll << endl;
        thishand++;
        
        if(d.cards_remaining() < 20){
            cout << "Shuffling the deck" << endl;
            for(int i = 0; i < 7; ++i){
                int cut = get_cut();
                d.shuffle(cut);
                cout << "cut at " << cut << endl;
            }
             player->shuffled();
        }
        
        Hand hand_player;
        Hand hand_dealer;
        int wager = player->bet(bankroll, minimum);
        cout << "Player bets " << wager << endl;
        
        Card player_up1 = d.deal();
        player->expose(player_up1);
        hand_player.add_card(player_up1);
        cout << "Player dealt " << player_up1 << endl;
        
        Card dealer_up = d.deal();
        player->expose(dealer_up);
        hand_dealer.add_card(dealer_up);
        cout << "Dealer dealt " << dealer_up << endl;
        
        Card player_up2 = d.deal();
        player->expose(player_up2);
        hand_player.add_card(player_up2);
        cout << "Player dealt " << player_up2 << endl;
        
        Card dealer_down = d.deal();
        
        if(hand_player.hand_value() == 21){
            bankroll += (wager*3)/2;
            cout << " Player dealt natural 21" << endl;
        }       // player get natural 21
        else{
            while(player->draw(dealer_up, hand_player)){
                Card dealt_to_player = d.deal();
                player->expose(dealt_to_player);
                hand_dealer.add_card(dealt_to_player);
                cout << "Player dealt " << dealt_to_player << endl;
            }
            cout << "Player's total is " << hand_player.hand_value() << endl;
            if(hand_player.hand_value() > 21){
                cout << "Player busts" << endl;
                bankroll -= wager;
            }     // player bust
            else{
                cout << "Dealer's hole card is " << dealer_down << endl;
                hand_dealer.add_card(dealer_down);
                player->expose(dealer_down);
                while(hand_dealer.hand_value() < 17){
                    Card dealt_to_dealer = d.deal();
                    hand_dealer.add_card(dealt_to_dealer);
                    player->expose(dealt_to_dealer);
                    cout << "Dealer dealt " << dealt_to_dealer << endl;
                }
                cout << "Dealer's total is " << hand_dealer.hand_value() << endl;
                if(hand_dealer.hand_value() > 21){
                    bankroll += wager;
                    cout << "Dealer busts" << endl;
                }  // dealer bust
                else{
                    if(hand_player.hand_value() > hand_dealer.hand_value()){
                        bankroll += wager;
                        cout << "Player wins" << endl;
                    }  // player wins
                    else if(hand_player.hand_value() < hand_dealer.hand_value()){
                        bankroll -= wager;
                        cout << "Dealer wins" << endl;
                    }  // dealer wins
                    else
                        cout << "Push" << endl;  // push
                }
            }

        }
    }
    
    cout << "Player has " << bankroll << " after " << thishand-1 << " hands" << endl;
    return 0;
}
