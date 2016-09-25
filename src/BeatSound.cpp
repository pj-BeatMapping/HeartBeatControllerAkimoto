//
//  BeatSound.cpp
//  HeartBeatControllerAkimoto
//
//  Created by 秋元和久 on 2016/09/25.
//
//

#include "BeatSound.h"

BeatSound::BeatSound(){};



BeatSound::BeatSound(string name1, string name2, string name3, string name4, string name5){
    player1[0].load(name1);
    player1[1].load(name1);
    player2[0].load(name2);
    player2[1].load(name2);
    player3[0].load(name3);
    player3[1].load(name3);
    player4[0].load(name4);
    player4[1].load(name4);
    player5[0].load(name5);
    player5[1].load(name5);
    
    for(int i=0; i<5; i++){
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
    
    if(i == 3){
        player4[cnt[i]%2].play();
    }
    if(i == 4){
        player5[cnt[i]%2].play();
    }
    cnt[i]++;

}

void BeatSound::stop(){
    player1[0].stop();
    player1[1].stop();
    player2[0].stop();
    player2[1].stop();
    player3[0].stop();
    player3[1].stop();
    player4[0].stop();
    player4[1].stop();
    player5[0].stop();
    player5[1].stop();
}