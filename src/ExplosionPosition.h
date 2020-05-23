//
//  ExplosionPosition.hpp
//  Project1_Part1
//
//  Created by HINGLI on 4/5/20.
//
#include <stdio.h>
#include "ofMain.h"
#include "ParticleEmitter.h"
#include "Particle.h"
class ExplosionPosition
{
    public:
        ExplosionPosition();
        ExplosionPosition(glm::vec3 explosionPosition);
        ExplosionPosition(glm::vec3 explosionPosition,int currentExplosionPictureColumn,int currentExplosionPictureRow);
        ExplosionPosition(glm::vec3 explosionPosition,ofColor particlColor,float particleRadius,int groupSize);
        ~ExplosionPosition();
        void setCurrentExplosionPictureColumn(int currentExplosionPictureColumn);
        void setCurrentExplosionPictureRow(int currentExplosionPictureRow);
        void setExplosionPosition(glm::vec3 explosionPosition);
        void setExplosionPictureColumnPixel(int explosionPictureColumnPixel);
        void setExplosionPictureRowPixel(int explosionPictureRowPixel);
        void setExplosionPictureMaxColumnNumber(int explosionPictureMaxColumnNumber);
        void setExplosionPictureMaxRowNumber(int explosionPictureMaxRowNumber);
        glm::vec3 getExplosionPosition();
        int getCurrentExplosionPictureColumn();
        int getCurrentExplosionPictureRow();
        int getExplosionPictureColumnPixel();
        int getExplosionPictureRowPixel();
        int getExplosionPictureMaxColumnNumber();
        int getExplosionPictureMaxRowNumber();
        bool getIsRemove();
        ParticleEmitter* getParticleEmitter();
        void setExplosionTypeSelection(int explosionTypeSelection);
        int getExplosionTypeSelection();
        void update();
        void setGroupSize(int groupSize);
        void setParticlDrawColor(ofColor color);
    private:
        glm::vec3 explosionPosition;
        int currentExplosionPictureColumn;
        int currentExplosionPictureRow;
        int explosionPictureColumnPixel;
        int explosionPictureRowPixel;
        int explosionPictureMaxColumnNumber;
        int explosionPictureMaxRowNumber;
        bool isRemove;
        int explosionTypeSelection;
        ParticleEmitter* particleEmitter;
        
};
