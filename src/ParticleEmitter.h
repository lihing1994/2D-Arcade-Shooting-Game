//
//  ParticleEmitter.hpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//
#pragma once
#include "ofMain.h"
#include "ParticleSystem.h"
#include <iostream>
#include "time.h"
#include "ParticleForce.h"
class ParticleEmitter: public TransformObject {
public:
    ParticleEmitter();
    ParticleEmitter(ParticleSystem * particleSystem);
    ParticleEmitter(ParticleSystem * particleSystem,bool isForExplosionEffect,glm::vec3 pos);
    ParticleEmitter(ParticleSystem * particleSystem,bool isForExplosionEffect,glm::vec3 pos,ofColor particlColor,float particleRadius,int groupSize);
    ~ParticleEmitter();
    void init();
    void draw();
    void start();
    void stop();
    void setLifespan(float);
    void setVelocity(ofVec3f);
    void setChildImage(ofImage);
    void setImage(ofImage);
    void setRate(float);
    void update();
    //Add helper functio*n:
    void setRoationAngle(float rotationAngle);
    void setPictureList(vector<ofImage> pictureList);
    void setIsSpeicalMovement(bool isSpeicalMovement);
    void setIsPictureRandomChange(bool isPictureRandomChange);
    void setLevelDifficulty(int levelDifficulty);
    int getLevelDifficulty();
    ParticleSystem* getParticleSystem();
    bool getIsStarted();
    void setDrawable(bool drawable);
    void setIsForExplosionEffect(bool isForExplosionEffect);
    void explosionParticleSpawn();
    
private:
    bool isSpeicalMovement;
    bool isPictureRandomChange;
    ParticleSystem *sys;
    float rate;
    glm::vec3 velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    float width, height;
    //Adding
    float rotationAngle;
    vector<ofImage> pictureList;
    bool isForExplosionEffect;
    int levelDifficulty;
    bool oneShot;
    bool fired;
    int typeSelection;
    int groupSize;
    ofColor particleColor;
    float particleRadius;
};
