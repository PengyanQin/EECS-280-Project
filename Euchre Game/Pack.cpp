/*  pack.cpp
 *
 *  Represents a pack of playing cards
 *
 *  by Pengyan Qin
 *  on 5/24/15
 */

#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

void Pack_init(Pack *pack_ptr, const char* pack_filename){
    ifstream fin;
    fin.open(pack_filename);
    if(!fin.is_open()){
        cout<<"Pack file fail to open! "<<endl;
        exit(EXIT_FAILURE);
    }
    string str_of;
    string suit;
    string rank;
    for(int i=0; i<PACK_SIZE; ++i){
        fin >> rank >> str_of >> suit;
        Card_init(&pack_ptr->cards[i], rank.c_str(), suit.c_str());
    }
    pack_ptr->next = &pack_ptr->cards[0];
}

Card Pack_deal_one(Pack *pack_ptr){
    Card last_card = pack_ptr->cards[PACK_SIZE-1];
    Card deal_card = *pack_ptr->next;
    if(Card_compare(pack_ptr->next, &last_card) != 0)
        pack_ptr->next += 1;
    return deal_card;

 }

void Pack_reset(Pack *pack_ptr){
    pack_ptr->next = pack_ptr->cards;
}

void Pack_shuffle(Pack *pack_ptr){
    int cut_num = 3;
    int off_set = 17*cut_num%24;
    pack_ptr->next = pack_ptr->cards + off_set;
    Card *temp = new Card[off_set + 1];
    for(int i =0; i< off_set; ++i){
        *(temp+i) = pack_ptr->cards[i];
    }
    for(int i=0; i<PACK_SIZE-off_set; ++i){
        pack_ptr->cards[i] = pack_ptr->cards[i + off_set];
    }
    int j = 0;
    for(int i=PACK_SIZE-off_set; i < PACK_SIZE; ++i){
        pack_ptr->cards[i] = *(temp + j);
        j++;
    }
    pack_ptr->next = pack_ptr->cards;
    delete temp;
    
}


