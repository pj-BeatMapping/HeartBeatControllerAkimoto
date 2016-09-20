#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
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
    
};
