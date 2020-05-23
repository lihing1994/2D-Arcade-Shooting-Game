//
//  SpriteSystem.hpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//
#pragma once
#include <vector>
#include "Particle.h"
#include "ofMain.h"
#include <ctime>

class ParticleSystem
{
    
    public:
        ParticleSystem();
        ~ParticleSystem();
        void add(Particle);
        void remove(int);
        void update();
        void draw();
        vector<Particle> * getParticle();
        void setIsSpecialMovement(bool isSpecialMovement);
        void sinCurveMovementInYDirection(Particle &temp);
        void verticalMovementInYDirection(Particle &temp);
        void horizontalMoovementInXDirection(Particle &temp);
        void sinCurveMovementInXDirection(Particle &temp);
        void sinCurveMovementInYReflectedDirection(Particle &temp);
        void sinCurveMovementInXReflectedDirection(Particle &temp);
        void setLevelDifficulty(int levelDifficulty);
        void setIsForExplosionEffect(bool isForExplosionEffect);
        void explosionParticleUpdate(Particle &temp);
    private:
        bool isSpecialMovement;
        bool isForExplosionEffect;
        vector<Particle> particle;
        float cycles;
        int levelDifficulty;
};
