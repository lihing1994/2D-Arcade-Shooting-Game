//
//  ParticleSystem.cpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//

#include "ParticleSystem.h"
ParticleSystem::ParticleSystem()
{
    this->cycles = 1.0f;
}
ParticleSystem::~ParticleSystem()
{
    this->particle.clear();
}
void ParticleSystem::add(Particle s)
{
    particle.push_back(s);
}
void ParticleSystem::remove(int i)
{
    particle.erase(particle.begin() + i);
}
void ParticleSystem::update()
{

    if (particle.size() == 0) return;
    vector<Particle>::iterator s = particle.begin();
    vector<Particle>::iterator tmp;

    // check which particle have exceed their lifespan and delete
    // from list.  When deleting multiple objects from a vector while
    // traversing at the same time, use an iterator.
    //
    while (s != particle.end())
    {
        if ((s->getIsCollied())||(s->getIsOutOfRange())||(s->getLifeSpan() != -1 && s->age() > s->getLifeSpan()))
        {
            tmp = particle.erase(s);
            s = tmp;
        }
        else
        {
            s++;
        }
    }
    if(this->isForExplosionEffect)
    {
        for(int i = 0;i<particle.size();i++)
        {
            TurbulenceForce* turbulenceForce = new TurbulenceForce(glm::vec3(-10000,-10000,0),glm::vec3(10000,10000,0));
            particle.at(i).addForce(turbulenceForce);
            this->explosionParticleUpdate(particle[i]);
        }
    }
    else if(!this->isSpecialMovement)
    {
        for (int i = 0; i < particle.size(); i++)
        {
            particle.at(i).addForce(new GravityForce(glm::vec3(0,-30,0)));
            verticalMovementInYDirection(particle.at(i));
        }
    }
    else
    {
        /*
            As I defined,
            movementSelection = 1 -> horizontalMoovementInXDirection
            movementSelection = 2 -> verticalMovementInYDirection
            movementSelection = 3 -> sinCurveMovementInYDirection
            movementSelection = 4 -> sinCurveMovementInXDirection
            movementSelection = 5 -> horizontalMoovementInXOppsiteDirection
            movementSelection = 6 -> verticalMovementInYOppsiteDirection
            movementSelection = 7 -> sinCurveMovementInYReflectedDirection
            movementSelection = 8 -> sinCurveMovementInXReflectedDirection
        */
        for(int i=0;i<particle.size();i++)
        {
            int temp_movement_selection = particle[i].getMovementSelection();
            if(temp_movement_selection==1)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(30+2*levelDifficulty,0,0));
                particle[i].addForce(gravityForce);
                horizontalMoovementInXDirection(particle[i]);
            }
            else if(temp_movement_selection == 2)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(0,30+2*levelDifficulty,0));
                particle[i].addForce(gravityForce);
                verticalMovementInYDirection(particle[i]);
            }
            else if(temp_movement_selection ==3 )
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(0,30+2*levelDifficulty,0));
                particle[i].addForce(gravityForce);
                sinCurveMovementInYDirection(particle[i]);
            }
            else if(temp_movement_selection ==4 )
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(30+2*levelDifficulty,0,0));
                particle[i].addForce(gravityForce);
                sinCurveMovementInXDirection(particle[i]);
            }
            else if(temp_movement_selection == 5)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(-30-2*levelDifficulty,0,0));
                particle[i].addForce(gravityForce);
                horizontalMoovementInXDirection(particle[i]);
            }
            else if(temp_movement_selection == 6)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(0,-30-2*levelDifficulty,0));
                particle[i].addForce(gravityForce);
                verticalMovementInYDirection(particle[i]);
            }
            else if(temp_movement_selection == 7)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(0,30+2*levelDifficulty,0));
                particle[i].addForce(gravityForce);
                sinCurveMovementInYReflectedDirection(particle[i]);
            }
            else if(temp_movement_selection == 8)
            {
                GravityForce* gravityForce = new GravityForce(glm::vec3(30+2*levelDifficulty,0,0));
                particle[i].addForce(gravityForce);
                sinCurveMovementInXReflectedDirection(particle[i]);
            }
            
        }
    }
    
}

void ParticleSystem::draw()
{
    for (int i = 0; i < particle.size(); i++)
    {
        //There is no need to draw any Object, which is alreay collied or
        //It was in the area outside the screen.
        if(!particle[i].getIsCollied()&&!particle[i].getIsOutOfRange())
        {
            particle[i].draw();
        }
    }
}
 vector<Particle> * ParticleSystem::getParticle()
{
    return &particle;
}
void ParticleSystem::setIsSpecialMovement(bool isSpecialMovement)
{
    this->isSpecialMovement = isSpecialMovement;
}
void ParticleSystem::sinCurveMovementInYDirection(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    float scale = (int)rand() % ofGetWidth()+10;
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.y += tempVeolicty.y*dt;
    float u = (cycles * tempPostion.y * PI)/ofGetHeight();
    temp.setPosition(glm::vec3(temp.getScales() * sin(u),tempPostion.y, 0));
    glm::vec3 tempForce;
    for(int i =0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce *(1/temp.getMass()));
    tempVeolicty.y += tempAcceleration.y * dt;
    temp.setVelocity(tempVeolicty);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}
void ParticleSystem::sinCurveMovementInXDirection(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    float scale = (int)rand() % ofGetHeight()+10;
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.x += tempVeolicty.x * dt;
    float u = (cycles * tempPostion.x * PI)/ofGetWidth();
    temp.setPosition(glm::vec3(tempPostion.x,-temp.getScales()*sin(u)+ofGetHeight(),0));
    glm::vec3 tempForce;
    for(int i =0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce *(1/temp.getMass()));
    tempVeolicty.x += tempAcceleration.x * dt;
    temp.setVelocity(tempVeolicty);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}
void ParticleSystem::verticalMovementInYDirection(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.y += tempVeolicty.y*dt;
    glm::vec3 tempForce;
    for(int i =0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce * (1/temp.getMass()));
    tempVeolicty.y += tempAcceleration.y *dt;
    temp.setPosition(tempPostion);
    temp.setVelocity(tempVeolicty);
    //temp.setAcceleration(tempAcceleration);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}
void ParticleSystem::horizontalMoovementInXDirection(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.x += tempVeolicty.x * dt;
    glm::vec3 tempForce;
    for(int i=0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce * (1/temp.getMass()));
    tempVeolicty.x += tempAcceleration.x * dt;
    temp.setVelocity(tempVeolicty);
    temp.setPosition(tempPostion);
    //temp.setAcceleration(tempAcceleration);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}

void ParticleSystem::sinCurveMovementInYReflectedDirection(Particle &temp)
{
     
    float dt = 1/ofGetFrameRate();
    float scale = (int)rand() % ofGetWidth()+10;
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.y += tempVeolicty.y*dt;
    float u = (cycles * tempPostion.y * PI)/ofGetHeight();
    temp.setPosition(glm::vec3(ofGetWidth()-temp.getScales() * sin(u),tempPostion.y, 0));
    glm::vec3 tempForce;
    for(int i =0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce *(1/temp.getMass()));
    tempVeolicty.y += tempAcceleration.y * dt;
    temp.setVelocity(tempVeolicty);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}
void ParticleSystem::sinCurveMovementInXReflectedDirection(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    float scale = (int)rand() % ofGetHeight()+10;
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.x += tempVeolicty.x * dt;
    float u = (cycles * tempPostion.x * PI)/ofGetWidth();
    temp.setPosition(glm::vec3(tempPostion.x,temp.getScales()*sin(u),0));
    glm::vec3 tempForce;
    for(int i =0;i<temp.getForce().size();i++)
    {
        if(!temp.getForce().at(i)->getApplied())
        {
            tempForce += temp.getForce().at(i)->getForce();
            if(temp.getForce().at(i)->getApplyOnce())
            {
                temp.getForce().at(i)->setApplied(true);
            }
        }
    }
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce *(1/temp.getMass()));
    tempVeolicty.x += tempAcceleration.x * dt;
    temp.setVelocity(tempVeolicty);
    tempPostion = temp.getPosition();
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}
void ParticleSystem::setLevelDifficulty(int levelDifficulty)
{
    this->levelDifficulty = levelDifficulty;
}
void ParticleSystem::setIsForExplosionEffect(bool isForExplosionEffect)
{
    this->isForExplosionEffect = isForExplosionEffect;
}
void ParticleSystem::explosionParticleUpdate(Particle &temp)
{
    float dt = 1/ofGetFrameRate();
    glm::vec3 tempPostion = temp.getPosition();
    glm::vec3 tempVeolicty = temp.getVelocity();
    tempPostion.x += tempVeolicty.x * dt;
    tempPostion.y += tempVeolicty.y * dt;
    temp.setPosition(tempPostion);
    glm::vec3 tempForce;
    for(int i=0;i<temp.getForce().size();i++)
    {
        tempForce += temp.getForce().at(i)->getForce();
    }
    temp.getForce().clear();
    glm::vec3 tempAcceleration = temp.getAcceleration() + (tempForce *(1/temp.getMass()));
    tempVeolicty.x += tempAcceleration.x * dt;
    tempVeolicty.y += tempAcceleration.y * dt;
    temp.setVelocity(tempVeolicty);
    if(tempPostion.x<0||tempPostion.x>ofGetWidth()||tempPostion.y<0||tempPostion.y>ofGetHeight())
    {
        temp.setIsOutOfRange(true);
    }
}

