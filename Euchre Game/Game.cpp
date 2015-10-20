/*  Game.cpp
 *
 *  Created by Pengyan Qin 
 * on 5/25/15.
 */

#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include "Game.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void Game_init(Game *game_ptr, const char *pack_filename, bool shuffle, int points_to_win, const char *const player_names[]){
    Pack_init(&game_ptr->pack, pack_filename);
    game_ptr->shuffle = shuffle;
    game_ptr->points_to_win = points_to_win;
    for(int i = 0; i < NUM_PARTNERSHIPS; ++i)
        game_ptr->score[i] = 0;
    for(int i = 0; i < NUM_PLAYERS; ++i)
        Player_init(game_ptr->players+i, *(player_names + i));
    return;
}

//REQUIRES: player_ptr points to an initialized Player
//EFFECTS: print out the player's name
static void print_player_name(const Player *const player_ptr){
    int i = 0;
    while(player_ptr->name[i] != '\0'){
        cout << player_ptr->name[i];
        ++i;
    }
}

//REQUIRES: game_ptr points to an initialized Game
//MODIFIES: game_ptr
//EFFECTS:  If the shuffle option is selected shuffle the pack.
//   Otherwise, reset the pack
static void Game_shuffle(Game *game_ptr){
    if (game_ptr->shuffle)
        Pack_shuffle(&game_ptr->pack);
    else
        Pack_reset(&game_ptr->pack);
    return;
}

//REQUIRES: game_ptr points to an initialized Game, dealer is between 0 to 3, inclusive
//MODIFIES: game_ptr
//EFFECTS: deal card to each player, deal 3-2-3-2 cards then 2-3-2-3 cards
//         dealer is the first player,each hand, moves one to the left
//         the first person to receive a card is left of the dealer
static void Game_deal_card(Game *game_ptr, const int dealer){
    assert(game_ptr);
    assert(dealer >= 0 && dealer < 4);
    Card deal;
    
    for(int i = 1; i <= NUM_PLAYERS; ++i){   // deal 3-2-3-2
        if(i == 1 || i == 3){
            for(int j = 0; j < 3; ++j){   //3
                deal = Pack_deal_one(&game_ptr->pack);
                Player_add_card(game_ptr->players + (dealer + i)%NUM_PLAYERS, &deal);
            }
        }
        else{
            for(int j = 0; j < 2; ++j){  // 2
                deal = Pack_deal_one(&game_ptr->pack);
                Player_add_card(game_ptr->players + (dealer + i)%NUM_PLAYERS, &deal);
            }
        }
    }
    
    for(int i = 1; i <= NUM_PLAYERS; ++i){   // deal 2-3-2-3
        if(i == 1 || i == 3){
            for(int j = 0; j < 2; ++j){  //2
                deal = Pack_deal_one(&game_ptr->pack);
                Player_add_card(game_ptr->players + (dealer + i)%NUM_PLAYERS, &deal);
            }
        }
        else{
            for(int j=0; j<3; ++j){  //3
                deal = Pack_deal_one(&game_ptr->pack);
                Player_add_card(game_ptr->players + (dealer + i)%NUM_PLAYERS, &deal);
            }
        }
    }
    return;
}

//REQUIRES: game_ptr points to an initialized Game, dealer is between 0 to 3, inclusive
//MODIFIES: game_ptr, order_up_suit, group_make_trump
//EFFECTS: decide the trump suit and the group that make trump
//         player 0&2 is group = 0, player 1&3 is group = 1
static void Game_make_trump(Game *game_ptr, const int dealer, Suit *order_up_suit, int *group_make_trump, Card *upcard){
    assert(game_ptr);
    assert(dealer >= 0 && dealer < 4);

    int round = 1;
    int flag = 1;
    for(; round < 3; ++round){
        for(int i = 1; i <= NUM_PLAYERS; ++i){
            if(Player_make_trump(game_ptr->players+(dealer+i)%NUM_PLAYERS, upcard, game_ptr->players+dealer, round, order_up_suit)){
                flag = i;
                print_player_name(game_ptr->players+(dealer+i)%NUM_PLAYERS);
                cout << " orders up ";
                Suit_print(*order_up_suit);
                cout << endl;
                cout << endl;
                goto end_loop;
            }
            else{
                print_player_name(game_ptr->players+(dealer+i)%NUM_PLAYERS);
                cout << " passes" << endl;
            
            }
    }
}
end_loop:
    int trump_num = (dealer + flag)%NUM_PLAYERS ;
    if( trump_num == 0 || trump_num == 2)
        *group_make_trump = 0;
    else
        *group_make_trump = 1;

    if(round == 1)
        Player_add_and_discard(game_ptr->players+dealer, upcard);
    
    return;
}

//REQUIRES: game_ptr points to an initialized Game, lead player index in between 0 and 3, inclusive
//          sub_score record the trick scores
//MODIFIES: game_ptr, sub_score, *lead
//EFFECTS: decide which team win in one trick and change the *lead
//         the highest card of the suit led
static void Game_one_trick(Game *game_ptr, int *lead, Suit trump, int sub_score[]){
    assert(game_ptr);
    assert(*lead >= 0 && *lead < 4);
    
    Card played_cards[4];
    played_cards[0] = Player_lead_card(game_ptr->players + (*lead), trump);
    Card_print(&played_cards[0]);
    cout << " led by ";
    print_player_name(game_ptr->players + (*lead));
    cout << endl;
    for (int i = 1; i < NUM_PLAYERS; ++i){
        played_cards[i] = Player_play_card(game_ptr->players + (*lead + i)%NUM_PLAYERS, &played_cards[0], trump);
        Card_print(&played_cards[i]);
        cout << " played by ";
        print_player_name(game_ptr->players + (*lead + i)%NUM_PLAYERS);
        cout << endl;
    }
    
    Card highest_card = played_cards[0];
    int flag = 0;
    for(int i = 1; i < NUM_PLAYERS; ++i){
        if(Card_compare(&highest_card, &played_cards[i], &played_cards[0], trump) < 0){
            highest_card = played_cards[i];
            flag = i;
        }
    }
    *lead = (*lead + flag)%NUM_PLAYERS;
    print_player_name(game_ptr->players + (*lead));
    cout << " takes the trick" << endl;
    if(*lead == 0 || *lead == 2)
        sub_score[0]++;
    else
        sub_score[1]++;
}


//REQUIRES: game_ptr points to an initialized Game,sub_score record the trick scores
//         group_make_trump record which team make trump
//MODIFIES: game_ptr
//EFFECTS: decide which team win in one hand and decide the score for the two teams
static void Game_score_cal(Game *game_ptr, int sub_score[], int group_make_trump){
    assert(game_ptr);
    assert(group_make_trump == 0 || group_make_trump == 1);
    
    for (int i = 0 ; i < 2; ++i){
        int flag = 0;
        if(group_make_trump == i){
            if(sub_score[i] == 3 || sub_score[i] == 4){
                (game_ptr->score[i])++;
                flag = 1;
            }
            if(sub_score[i] == 5){
                (game_ptr->score[i]) += 2;
                flag = 2;
            }
        }
        else{
            if(sub_score[i] == 3 || sub_score[i] == 4 || sub_score[i] == 5 ){
                (game_ptr->score[i]) += 2;
                flag = 3;
            }
        }
        if(flag != 0){
            print_player_name(game_ptr->players + i);
            cout << " and ";
            print_player_name(game_ptr->players + i + 2);
            cout << " win the hand" << endl;
        }
        if (flag == 2)
            cout << "march!" << endl;
        if (flag == 3)
            cout << "euchred!" << endl;
    }
    
    return;
}

void Game_play(Game *game_ptr){
    assert(game_ptr);
    
    int hand = 0;
    while (game_ptr->score[0] < game_ptr->points_to_win && game_ptr->score[1] < game_ptr->points_to_win){
        cout << "Hand " << hand <<endl;
        Game_shuffle(game_ptr);
        int dealer = hand%4;
        print_player_name(game_ptr->players+dealer);
        cout << " deals" << endl;
        Game_deal_card(game_ptr, dealer);
        Card *upcard = (game_ptr->pack).next;
        Card_print(upcard);
        cout<<" turned up"<<endl;
        
        Suit spades = SPADES;
        Suit *order_up_suit = &spades;
        int group_make_trump = 0;
        Game_make_trump(game_ptr, dealer, order_up_suit, &group_make_trump, upcard);
        
        Suit trump = *order_up_suit;
        int lead = (dealer + 1)%NUM_PLAYERS;
        int sub_score[NUM_PLAYERS] = {};
        for(int i = 0; i < 5; ++i){
            Game_one_trick(game_ptr, &lead, trump, sub_score);
            cout<<endl;
        }
        
        Game_score_cal(game_ptr, sub_score, group_make_trump);
        
        for(int i = 0; i < 2; ++i){
            print_player_name(game_ptr->players + i);
            cout << " and ";
            print_player_name(game_ptr->players + i + 2);
            cout << " have " << game_ptr->score[i] << " points" <<endl;
        }
        cout << endl;
        hand++;
    }
    for(int i = 0; i < 2; ++i){
        if(game_ptr->score[i] >= game_ptr->points_to_win){
            print_player_name(game_ptr->players + i);
            cout << " and ";
            print_player_name(game_ptr->players + i + 2);
            cout << " win!" << endl;
        }
    }
    return;

}

