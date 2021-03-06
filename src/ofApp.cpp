#include "ofApp.h"

int mili;
int premili = 0;
int bgSize = 4;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(50);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    beat.loadSound("BEAT.mp3");
    // FFT初期設定
    fft.setup();
    fft.setNumFFTBins(16);
    fft.setNormalize(true);
    // GUI
    gui.setup();
    gui.add(level.setup("Input Level", 500, 0, 5000));
    gui.loadFromFile("settings.xml");
    //Arduino
    serial.setup("/dev/cu.usbmodem1421",9600);//Arduinoのポートを指定。
    
    //擬似心拍クラス
    for(int i=0; i<bgSize; i++){
        bg.push_back(*new BeatGenerator(60.0/(BPM[i]+(0.5 - flct)*BPM[i]*margin)*1000, flct));
        //BPM += 4;
   }
    
    //OSC
    sender.setup(HOST,PORT);
    
    bs1 = *new BeatSound("ws1.mp3","ws2.mp3","ws3.mp3","ws4.mp3","ws1.mp3");
    bs2 = *new BeatSound("piano1.mp3","piano2.mp3","piano3.mp3","piano4.mp3","piano5.mp3");
    bs3 = *new BeatSound("rad1.mp3","rad2.mp3","rad3.mp3","rad1.mp3","rad2.mp3");
    bs4 = *new BeatSound("sc1.mp3","sc2.mp3","sc3.mp3","sc4.mp3","sc5.mp3");
   
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(0);
    fft.update();
    //FFTデバッグ
    //cout<<"低周波数帯:"<<fft.getLowVal()<<endl;
    
    //cout<<"中周波数帯:"<<fft.getMidVal()<<endl;
    
    //cout<<"高周波数帯:"<<fft.getHighVal()<<endl;
    
    //cout<<"====================="<<endl;
    
    //シリアル通信(受信)
    send_data = -2;
    send_data = serial.readByte();//Arduinoでwriteされたデータを取得
    
    
    //擬似心拍の取得
    mili = ofGetElapsedTimeMillis();//起動してからの時間を取得
    for(int i=0; i<bgSize; i++)
        if(bg[i].autoBeat(mili,BPM[i],margin)){
            //ここに心拍が拍動した時の処理を書く
            beat_detect[i+1] = 1;
            if(i == 0) {
                bs1.playSound(ofRandom(0,5));
            }
            if(i == 1) {
                bs2.playSound(ofRandom(0,5));
            }
            if(i == 2) {
                bs3.playSound(ofRandom(0,5));
            }
            if(i == 3) {
                bs4.playSound(ofRandom(0,5));
                printf("now %d\n",mili);
            }
            
        } else beat_detect[i+1] = 0;

    //擬似心拍のデバッグ用
//    for(int i=0; i<bgSize; i++)
//        printf("%d",beat_detect[i+1]);
//    printf("\n");
    
    //鼓動音の再生
    for(int i = 0 ; i < 7 ; i++){
        if(beat_detect[i] == 1 ){
            beat.play();
          //  beat.setVolume(0.5f);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //心拍(From Arduino)

    //Beat検出時以外のフレーム時に-2を受信する(謎)ので、-2を処理しないための処理。
    if(send_data > -1){ //エラーが出た時に実行されないように > -1 と書き換え
        number = send_data; //実際のカウント数を格納(-2以外を格納)
        counter = true;//1フレームに処理を限定。以降はFalseにする。
    }
    if(counter){
        //cout << number <<"times"<< endl; //Beat検出時のデバッグ用
        counter = false; //表示を一回のみに限定
        ofBackground(255);//ビート検出時のみ画面を白に(フラッシュ)
        
        //--------ON----------
        beat_detect[0] = 1;
        //cout << "Arduino = " << beat_detect[0] << endl;
        //--------ON----------
        
        //BPMの検出
        float nowBPM =
        
        (float)(mili-premili)/1000.0*60.0;
        //printf("nowTime = %f, preTime = %f, BPM = %f\n", mili/1000.0, premili/1000.0, nowBPM); //ここでBPMを検出できる
        premili = mili;
    }else{
        //--------OFF---------
         beat_detect[0] = 0;
        //--------OFF---------
        
    }
    //画面のメッセージ
    ofSetColor(255,0,0);
    string msg = "Beat :" + ofToString( number );
    ofDrawBitmapString( msg, ofGetWidth()/2, ofGetHeight()/2);
    
    //FFT
    // 低域、中域、高域の値を取得
    float lowValue = ofMap(fft.getLowVal(), 0, 1, 0, level);
    float midValue = ofMap(fft.getMidVal(), 0, 1, 0, level);
    float highValue = ofMap(fft.getHighVal(), 0, 1, 0, level);
    //描画
    ofSetColor(lowValue, midValue, highValue,50);
    ofFill();
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, lowValue);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, midValue);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, highValue);
    
    cout << lowValue << endl;
    
    // GUI
    gui.draw();
    
    //OSC
    //心拍のデータ
    ofxOscMessage OscBeat;
    OscBeat.setAddress( "/Beat" );
    for(int i = 0;i<7;i++){
        OscBeat.addIntArg(beat_detect[i]);
    }
    sender.sendMessage(OscBeat);
    
    //音響解析データ
    ofxOscMessage OscFFT;
    OscFFT.setAddress( "/Fft" );
    OscFFT.addFloatArg(lowValue);
    OscFFT.addFloatArg(midValue);
    OscFFT.addFloatArg(highValue);
    sender.sendMessage(OscFFT);
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    beat.stop();
    bs1.stop();
    bs2.stop();
    bs3.stop();
    bs4.stop();
}

void ofApp::keyPressed(int key){
    if(key == 'z'){
        if(bgSize > 0)
            bgSize = bgSize - 1;
    }
    
    if(key == 'x'){
        if(bgSize < 4)
            bgSize = bgSize + 1;
    }
}