/*
 *  Hand.cpp
 *
 *  Created by Pengyan Qin 
 *  on 6/9/15.
 */
#include <iostream>
#include "Card.h"
#include "Hand.h"

Hand::Hand(): value(0), soft(false){}

void Hand::discard_all(){
    value = 0;
    soft = false;
    return;
}

void Hand::add_card(Card c){
    Card::Rank c_rank = c.get_rank();
    if(c_rank <= Card::TEN){
        value += c_rank + 2;
        if(value > 21 && soft){
            value -= 10;
            soft = false;
        
        }
    }
    else if(c_rank <= Card::KING){
        value += 10;
        if(value > 21 && soft){
            value -= 10;
            soft = false;
            
        }
    }
    else{
        if(value >= 11){
            value += 1;
        }
        else{
            value += 11;
            soft = true;
        }
    }
    return;
}

int Hand::hand_value() const{
    return value;
}

bool Hand::hand_is_soft() const{
    return soft;
}





