#include "ofMain.h"
#include "ofxGui.h"
#include "ParticleEmitter.h"
#include <iostream>
#include "AirCraft.h"
#include "stdio.h"
#include "ExplosionPosition.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void exit(); // destructor for the game..
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
        //helper function
        void loadAllImage();
        void loadAllSound();
        void drawXRay();
        void drawCircleShield();
        void checkCollisionBulltAndEnemy();
        void checkCollisionTurretAndEnemy();
        void checkCollisionXRayAndEnemy();
        void levelDifficultySwitch();
        void printLevelSwitchingSentence();
        void drawExplosion();
        void findExplosionPictureNextFrame(int maxColumnNumber,int maxRowNumber);
        void drawAirCraft();
        void addFinalExplosionEffectToDrawList();
    private:
        vector<ParticleEmitter *> emitters;
        int numEmitters;
        bool imageLoaded;
    
        //GUI:
        ofxFloatSlider bulleTrate;
        ofxFloatSlider bulletLife;
        ofxFloatSlider bulletAngle;
        ofxFloatSlider enemyRate;
        ofxFloatSlider enemyLife;
        ofxLabel screenSize;
        ofxPanel gui;
        ofImage backGroundPicture;
        ofImage backGroundPictureLevel2;
        ofImage backGroundPictureLevel3;
        ofImage backGroundPictureLevel4;
        ofImage backGroundPictureLetter;
        ofxToggle isBackGroundPlay;
        bool bHide;
    
        //Code for Start up
        bool isGameBegan;
        bool isGameOver;
        bool isGameSuspend;
        ofImage gamingStartUpImage;
        ofImage gamingStartUpImage2;
        int gamingStartUpImageSelect;
        float timeMarker;
        float halfGamingStartUpImageWidth;
        float halfGamingStartUpImageHight;
        ofTrueTypeFont myFront;
        ofTrueTypeFont myScoreBoardFront;
        
        //Code for AirCraft Main Body
        AirCraft * airCraft;
        ofImage airCraftBodyImage;
        int gamingStartedPictureSelection;
        bool isAirCraftCollisionFlashing;
        float AirCraftFlashingTimeMarker;
    
        //Code for skills
        //Following code for skill - shield.
        bool isCircleShieldDrew;
        int circleFlashingSelction;
        float shieldTimeMarker;
        //Following code for skill - ray
        bool isXRayDrew;
        float xRayTimeMarker;
        int xRayFlashingSelection;
        vector<glm::vec3> xRayLineEndingPoint;
        int skillColdDownTime;
    
    
        //Code for bullet
        bool isSpaceBarSelected;
        ofImage bulletImage;
        
        //Code for checking mouse
        bool isMouseOutOfWindowRange;
    
        //code for sound
        ofSoundPlayer   myBackGroundSound;
        vector<std::string> mySoundPathList;
        ofSoundPlayer shootingBulletSound;
        int mySoundPlayingCouting;
        ofSoundPlayer myPunchSound;
    
        //Following code for Enemy
        ParticleEmitter * enemyEmitter;
        vector<ofImage> enemyImageList;
    
        //Following code check for collision:
        ParticleSystem * bulletSystem;
        ParticleSystem * enemySystem;
        
        //Following code add for Score Board:
        int score;
        int health;
    
        //Adding for Level;
        int level;
        float levelTimeMarker;
        float printingLevelSwtichingMarker;
        bool isLevelSwitching;
        int levelFontColorFlashingSelection;
        
        //Adding for draw explosion when collision occured
        vector<ExplosionPosition* > collisionPosition;
        ofImage* explosionPicture;
        int numberOfRowsOfExlosionPicture;
        int numberOfColumnsOfExlosionPicture;
        
        //Add for explosion effect when game exit
        bool isGameOverExplosionAddToDrawList;
        bool isGameOverExplosionEffectDrawCompleted;
        
};
