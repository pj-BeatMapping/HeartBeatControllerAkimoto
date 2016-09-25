#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "ofxGui.h"
#include "BeatGenerator.h"
#include "ofxOsc.h"
#include "BeatSound.h"

#define HOST "133.51.63.30" 
#define PORT 8000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

    
    //For Arduino
    ofSerial serial; //シリアル通信受信用のインスタンス
     //ofSerialのメソッドからArduinoのシリアルを受信してる。
     //->複数受信したい場合はこのArduinoごとにインスタンスを用意してやればいいと思われる。
    int send_data ; //Arduinoからwriteされて送られてくる値
    int number; //Beat数のカウント用
    bool counter = true; //フレームの読み込み回数の記録用
    
    //FFT
    ProcessFFT fft;         // FFT分析->Circleビジュアライズ用
    ofxPanel gui;           // GUI
    ofxFloatSlider level;   // 入力レベル調整
    
    //擬似心拍用変数
    float BPM[4]{40,80,20,30};
    float margin = 0.2;
    int flct = 0.3;
    vector<BeatGenerator> bg;
    
    //最終的に心拍情報を送信する変数(配列)
    int beat_detect[7];
    
    ofxOscSender sender;
    
    BeatSound bs1, bs2, bs3, bs4, bs5;
    
    ofSoundPlayer beat;
    
};
