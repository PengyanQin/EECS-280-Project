/*  player.cpp
*
*  Created by Pengyan Qin
*  on 5/24/15.
*/

#include "Player.h"
#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>

using namespace std;

void Player_init(Player *player_ptr, const char *name){
    assert(strlen(name) < (unsigned)MAX_STR_LEN);
    int i=0;
    while(i<MAX_STR_LEN){
        if(*name == '\0')
            break;
        else{
            player_ptr->name[i++] = *name;
            name++;
        }
    }
    player_ptr->name[i] = *name;
    
    for (int i=0; i<MAX_HAND_SIZE; ++i)
        player_ptr->hand[i] = Card();
    player_ptr->hand_size = 0;
}

void Player_add_card(Player *player_ptr, const Card *c){
    assert(player_ptr);
    assert(player_ptr->hand_size < MAX_HAND_SIZE);
    if(player_ptr->hand_size > 5)
        return;
    player_ptr->hand_size++;
    player_ptr->hand[player_ptr->hand_size - 1] = *c;
}

bool Player_make_trump(const Player *player_ptr, const Card *upcard,
                       const Player *dealer, int round, Suit *order_up_suit){
    assert(player_ptr);
    int cnt = 0;
    if(round ==1){  // first round
        for(int i=0; i<MAX_HAND_SIZE; ++i){
            if(Card_is_trump(&player_ptr->hand[i], upcard->suit) && Card_is_face(&player_ptr->hand[i]))
                ++cnt;
        }
        if(cnt >= 2){
            *order_up_suit = upcard->suit;
            return true;
        }
        else
            return false;
    }
    else if(round ==2){  // second round
        Suit same_col = Suit_next(upcard->suit);
        if(strcmp(player_ptr->name, dealer->name) != 0){
                for(int i=0; i<MAX_HAND_SIZE; ++i){
                    if(Card_is_trump(&player_ptr->hand[i], same_col) && Card_is_face(&player_ptr->hand[i]))
                    ++cnt;
                }
            if(cnt >= 1){
                *order_up_suit = same_col;
                return true;
                }
            else
                return false;
        }
        else{
            // screw the dealer
             *order_up_suit = same_col;
             return true;
        }
    }
    else  // other round
        return false;

}

void Player_add_and_discard(Player *player_ptr, const Card *upcard){
    assert(player_ptr);
    assert(player_ptr->hand_size > 0);
    if (player_ptr->hand_size < 1)
        return;
    Card min_card = *upcard;
    int min_card_num = -1;
    for(int i=0; i<player_ptr->hand_size; ++i)
        if(Card_compare(&min_card, &player_ptr->hand[i],upcard->suit) > 0){
            min_card = player_ptr->hand[i];
            min_card_num = i;
        }
    
    if(min_card_num == -1) // upcard is the lower
        return;
    else
        player_ptr->hand[min_card_num] = *upcard;

}

Card Player_lead_card(Player *player_ptr, Suit trump){
    assert(player_ptr);
    assert(player_ptr->hand_size > 0);
    Card lead_card;
    int cnt = 0;
    for(int i=0; i<player_ptr->hand_size; ++i){
        if(Card_is_trump(&player_ptr->hand[i], trump))
            cnt++;
    }
    
    if(cnt == player_ptr->hand_size || cnt == 0){    //only trump or only non-trump
        lead_card = player_ptr->hand[player_ptr->hand_size-1];
        for(int i=player_ptr->hand_size - 2; i>=0; --i){
            if(Card_compare(&lead_card, &player_ptr->hand[i], trump) < 0){
                Card temp = lead_card;
                lead_card = player_ptr->hand[i];
                player_ptr->hand[i] = temp;
            }
        }
    }
    else{    // both have trump card and non-trump card
        int f_ntrump = player_ptr->hand_size - 1;
        while(Card_is_trump(&player_ptr->hand[f_ntrump], trump))
            --f_ntrump;
        lead_card = player_ptr->hand[f_ntrump];
        int lead_num = f_ntrump;
        for(int i=f_ntrump-1; i>=0; --i){
            if(!Card_is_trump(&player_ptr->hand[i], trump)){
                if(Card_compare(&lead_card, &player_ptr->hand[i]) < 0){ // only compare non_trump
                    lead_card = player_ptr->hand[i];
                    lead_num = i;
                }
            }
        }
        if(lead_num != (player_ptr->hand_size - 1))
            player_ptr->hand[lead_num] = player_ptr->hand[player_ptr->hand_size - 1];
    }
    (player_ptr->hand_size)--;
    return lead_card;
}

Card Player_play_card(Player *player_ptr, const Card *led_card, Suit trump){
    assert(player_ptr);
    assert(player_ptr->hand_size > 0);
    Card play_card;
    int cnt = 0;
    for(int i=0; i<player_ptr->hand_size; ++i){
        if(Card_get_suit(led_card, trump) == Card_get_suit(&player_ptr->hand[i], trump))
            cnt++;
    }
    if(cnt == 0){ // can't follow suit, play the lowest card in hand
        play_card = player_ptr->hand[player_ptr->hand_size-1];
        for(int i=player_ptr->hand_size - 2; i>=0; --i){
            if(Card_compare(&play_card, &player_ptr->hand[i], trump) > 0){
                Card temp = play_card;
                play_card = player_ptr->hand[i];
                player_ptr->hand[i] = temp;
            }
        }
    }
    else{  // can follow suit, play the highest card that follows suit
        int f_fsuit = player_ptr->hand_size - 1;
        while(Card_get_suit(led_card, trump) != Card_get_suit(&player_ptr->hand[f_fsuit], trump))
            --f_fsuit;
        play_card = player_ptr->hand[f_fsuit];
        int play_num = f_fsuit;
        for(int i=f_fsuit-1; i>=0; --i){
            if(Card_get_suit(led_card, trump) == Card_get_suit(&player_ptr->hand[i], trump)){
                if(Card_compare(&play_card, &player_ptr->hand[i], trump) < 0){ // only compare follow suit
                    play_card = player_ptr->hand[i];
                    play_num = i;
                }
            }
        }
        if(play_num != (player_ptr->hand_size - 1))
            player_ptr->hand[play_num] = player_ptr->hand[player_ptr->hand_size - 1];
    }
    (player_ptr->hand_size)--;
    return play_card;
}


























