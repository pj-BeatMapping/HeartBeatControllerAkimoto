//
//  BeatGenerator.h
//  HeartBeatController
//
//  Created by 秋元和久 on 2016/09/20.



class BeatGenerator {
    
public:
    int nextTime;
    bool autoBeat(int mili, float BPM, float margin);
    BeatGenerator(){};
    BeatGenerator(int nxt, float x){nextTime = nxt; flct = x;};
private:
    float flct; //ゆらぎ
    void intermittentChaos(); //間欠カオス
};

