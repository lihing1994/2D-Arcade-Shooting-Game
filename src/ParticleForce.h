//
//  Forces.hpp
//  Project1_Final
//
//  Created by HINGLI on 4/11/20.
//
#pragma once
#include "ofMain.h"
#include <stdio.h>

class ParticleForce
{
    private:
        string ForceName;
    protected:
        bool applyOnce;
        bool applied;
    public:
        ParticleForce();
        virtual glm::vec3 getForce() = 0;
        virtual ~ParticleForce() =0;
        void setApplyOnce(bool applyOnce);
        void setApplied(bool applied);
        bool getApplyOnce();
        bool getApplied();
};
class GravityForce: public ParticleForce
{
    public:
        GravityForce(const glm::vec3 & gravity);
        ~GravityForce();
        glm::vec3 getForce();
    private:
        glm::vec3 gravity;
};
class TurbulenceForce : public ParticleForce
{
    public:
        TurbulenceForce(const glm::vec3 & min, const glm::vec3 &max);
        ~TurbulenceForce();
        glm::vec3 getForce();
    private:
        glm::vec3 min;
        glm::vec3 max;
};
class ImpulseRadialForce : public ParticleForce
{
    public:
        ImpulseRadialForce(float magnitude);
        ~ImpulseRadialForce();
        glm::vec3 getForce();
        void setHeight(int height);
        void setMagnitude(float magnitude);
        float getMagnitude();
    private:
        float magnitude;
        float height;
        bool isSetHeight;
};


