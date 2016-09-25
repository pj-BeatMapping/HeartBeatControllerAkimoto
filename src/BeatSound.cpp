//
//  BeatSound.cpp
//  HeartBeatControllerAkimoto
//
//  Created by 秋元和久 on 2016/09/25.
//
//

#include "BeatSound.h"

BeatSound::BeatSound(){};

BeatSound::BeatSound(string name1, string name2, string name3){
    player1[0].load(name1);
    player1[1].load(name1);
    player2[0].load(name2);
    player2[1].load(name2);
    player3[0].load(name3);
    player3[1].load(name3);
    
    for(int i=0; i<3; i++){
        cnt[i] = 0;
    }
}

void BeatSound::playSound(int i){
    if(i == 0){
        player1[cnt[i]%2].play();
    }
    
    if(i == 1){
        player2[cnt[i]%2].play();
    }
    
    if(i == 2){
        player3[cnt[i]%2].play();
    }
    
    cnt[i]++;

}