//
//  Forces.cpp
//  Project1_Final
//
//  Created by HINGLI on 4/11/20.
//

#include "ParticleForce.h"
ParticleForce::ParticleForce()
{
    this->applyOnce = false;
    this->applied = false;
}
ParticleForce::~ParticleForce()
{
    
}
void ParticleForce:: setApplyOnce(bool applyOnce)
{
    this->applyOnce = applyOnce;
}
void ParticleForce::setApplied(bool applied)
{
    this->applied = applied;
}
bool ParticleForce::getApplyOnce()
{
    return this->applyOnce;
}
bool ParticleForce::getApplied()
{
    return this->applied;
}

GravityForce::GravityForce(const glm::vec3 & gravity)
{
    this->gravity = gravity;
}
GravityForce::~GravityForce()
{
    
}
glm::vec3 GravityForce::getForce()
{
    return this->gravity;
}

TurbulenceForce::TurbulenceForce(const glm::vec3 & min, const glm::vec3 &max)
{
    this->min = min;
    this->max = max;
}
TurbulenceForce::~TurbulenceForce()
{
    
}
glm::vec3 TurbulenceForce::getForce()
{
    return glm::vec3(ofRandom(min.x,max.x),ofRandom(min.y,max.y),ofRandom(min.z,max.z));
}

ImpulseRadialForce::ImpulseRadialForce(float magnitude)
{
    this->magnitude = magnitude;
    applyOnce = true;
    this->isSetHeight = false;
    this->height = ofRandom(-1,1);
}
ImpulseRadialForce::~ImpulseRadialForce()
{
    
}

glm::vec3 ImpulseRadialForce::getForce()
{
    if(!isSetHeight)
    {
        return glm::vec3(ofRandom(-1,1),ofRandom(-1,1),ofRandom(-1,1));
        //particle->setForces(particle->getForce()+glm::normalize(temp)*magnitude);
    }
    else
    {
        return glm::vec3(ofRandom(-1,1),height,ofRandom(-1,1));
      
    }
}

void ImpulseRadialForce::setHeight(int height)
{
    this->height = height;
    this->isSetHeight = true;
}
void ImpulseRadialForce::setMagnitude(float magnitude)
{
    this->magnitude = magnitude;
}
float ImpulseRadialForce::getMagnitude()
{
    return this->magnitude;
}




