//
//  BeatGenerator.cpp
//  HeartBeatController
//
//  Created by 秋元和久 on 2016/09/20.
//
//

#include "BeatGenerator.h"
#include "ofMain.h"

void BeatGenerator::intermittentChaos(){ //間欠カオス
    //本来の間欠カオス,0と1に張り付きやすい
    /*
     if(x < 0.5) x = x + 2*x*x;
     else x = x - 2*(1-x)*(1-x);
     */
    
    //改良版,なんだかループしてしまっている
    //http://broadbeans.blog.so-net.ne.jp/2011-07-26
    if(flct == 0) flct = 0.51;
    else if(flct < 0.1) flct = flct + ofRandom(0.3, 0.8);
    else if(flct < 0.5) flct = flct + 2*flct*flct;
    else if(flct >= 0.9)flct = flct - ofRandom(0.3, 0.8);
    else if(flct >= 0.5) flct = flct + 2*(1-flct)*(1-flct);
    
    
}

bool BeatGenerator::autoBeat(int mili, float BPM, float margin){
    if(nextTime<mili){
        
        //printf("nextTime = %f, BPM = %f\n",nextTime/1000.0, (1+margin*(0.5-flct))*BPM);
        
        int f_over_one = BPM+(0.5 - flct)*BPM*margin;
        
        nextTime += 60.0/(float)f_over_one*1000;
        
        //printf("now f %d, %f, %d, %d\n", f_over_one, BPM, mili, nextTime);
        
        intermittentChaos();
        
        return true;
    } else return false;
}
