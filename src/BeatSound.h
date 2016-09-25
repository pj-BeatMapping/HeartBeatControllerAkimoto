//
//  BeatSound.h
//  HeartBeatControllerAkimoto
//
//  Created by 秋元和久 on 2016/09/25.
//
//


#include "ofMain.h"
class BeatSound{
public:
    BeatSound(string name1, string name2, string name3, string name4, string name5);
    BeatSound();
    void playSound(int i);
    void stop();
    ofSoundPlayer player1[2];
    ofSoundPlayer player2[2];
    ofSoundPlayer player3[2];
    ofSoundPlayer player4[2];
    ofSoundPlayer player5[2];
    
    int cnt[5];
    
};

