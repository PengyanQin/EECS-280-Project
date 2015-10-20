/*  euchre.cpp
 *
 *  Created by Pengyan Qin 
 *  on 5/25/15.
 */

#include "Player.h"
#include "Card.h"
#include "Pack.h"
#include "Game.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 8 || atoi(argv[3])>100 || atoi(argv[3])<0 || (strcmp(argv[2],"shuffle") !=0 && strcmp(argv[2],"noshuffle") !=0)){
        cout << "Usage: euchre PACK_FILENAME [shuffle|noshuffle] POINTS_TO_WIN NAME1 NAME2 NAME3 NAME4" <<endl;
        return -1;
        exit (EXIT_FAILURE);
    }
    for(int i=0; i<argc; ++i){
        cout << argv[i]<<" ";
    }
    cout<<endl;
    
    bool is_shuffle = false;
    if(strcmp(argv[2],"shuffle") ==0)
        is_shuffle = true;
    
    Game game;
    Game_init(&game, argv[1], is_shuffle, atoi(argv[3]), &argv[4]);
    Game_play(&game);
    return 0;
}

