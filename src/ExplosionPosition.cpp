//
//  ExplosionPosition.cpp
//  Project1_Part1
//
//  Created by HINGLI on 4/5/20.
//

#include "ExplosionPosition.h"
ExplosionPosition::ExplosionPosition()
{
    this->explosionPosition = glm::vec3(0,0,0);
    this->currentExplosionPictureColumn = 0;
    this->currentExplosionPictureRow = 0;
    this->explosionPictureColumnPixel = 0;
    this->explosionPictureRowPixel = 0;
    this->explosionPictureMaxColumnNumber = 0;
    this->explosionPictureMaxRowNumber =0;
    this->isRemove = false;
    ParticleSystem* explosionSys = new ParticleSystem();
    explosionSys->setIsForExplosionEffect(true);
    this->particleEmitter = new ParticleEmitter(explosionSys,true,this->explosionPosition);
}
ExplosionPosition::ExplosionPosition(glm::vec3 explosionPosition)
{
    this->explosionPosition = explosionPosition;
    this->currentExplosionPictureColumn = 0;
    this->currentExplosionPictureRow = 0;
    this->explosionPictureColumnPixel = 0;
    this->explosionPictureRowPixel = 0;
    this->explosionPictureMaxColumnNumber = 0;
    this->explosionPictureMaxRowNumber =0;
    this->isRemove = false;
    ParticleSystem* explosionSys = new ParticleSystem();
    explosionSys->setIsForExplosionEffect(true);
    this->particleEmitter = new ParticleEmitter(explosionSys,true,this->explosionPosition);
}
ExplosionPosition::ExplosionPosition(glm::vec3 explosionPosition,int currentExplosionPictureColumn,int currentExplosionPictureRow)
{
    this->explosionPosition = explosionPosition;
    this->currentExplosionPictureColumn = currentExplosionPictureColumn;
    this->currentExplosionPictureRow = currentExplosionPictureRow;
    this->explosionPictureColumnPixel = 0;
    this->explosionPictureRowPixel = 0;
    this->explosionPictureMaxColumnNumber = 0;
    this->explosionPictureMaxRowNumber =0;
    this->isRemove = false;
    ParticleSystem* explosionSys = new ParticleSystem();
    explosionSys->setIsForExplosionEffect(true);
    this->particleEmitter = new ParticleEmitter(explosionSys,true,this->explosionPosition);
}
ExplosionPosition::ExplosionPosition(glm::vec3 explosionPosition,ofColor particlColor,float particleRadius,int groupSize)
{
   this->explosionPosition = explosionPosition;
    this->currentExplosionPictureColumn = 0;
    this->currentExplosionPictureRow = 0;
    this->explosionPictureColumnPixel = 0;
    this->explosionPictureRowPixel = 0;
    this->explosionPictureMaxColumnNumber = 0;
    this->explosionPictureMaxRowNumber =0;
    this->isRemove = false;
    ParticleSystem* explosionSys = new ParticleSystem();
    explosionSys->setIsForExplosionEffect(true);
    this->particleEmitter = new ParticleEmitter(explosionSys,true,this->explosionPosition,particlColor,particleRadius,groupSize);
}
 
ExplosionPosition::~ExplosionPosition()
{
    delete particleEmitter;
}
void ExplosionPosition::setCurrentExplosionPictureColumn(int currentExplosionPictureColumn)
{
    this->currentExplosionPictureColumn = currentExplosionPictureColumn;
}
void ExplosionPosition::setCurrentExplosionPictureRow(int currentExplosionPictureRow)
{
    this->currentExplosionPictureRow = currentExplosionPictureRow;
}
void ExplosionPosition::setExplosionPosition(glm::vec3 explosionPosition)
{
    this->explosionPosition = explosionPosition;
}
glm::vec3 ExplosionPosition::getExplosionPosition()
{
    return this->explosionPosition;
}
int ExplosionPosition::getCurrentExplosionPictureColumn()
{
    return this->currentExplosionPictureColumn;
}
int ExplosionPosition::getCurrentExplosionPictureRow()
{
    return this->currentExplosionPictureRow;
}
int ExplosionPosition::getExplosionPictureColumnPixel()
{
    return this->explosionPictureColumnPixel;
}
int ExplosionPosition::getExplosionPictureRowPixel()
{
    return this->explosionPictureRowPixel;
}
int ExplosionPosition::getExplosionPictureMaxColumnNumber()
{
    return this->explosionPictureMaxColumnNumber;
}
int ExplosionPosition::getExplosionPictureMaxRowNumber()
{
    return this->explosionPictureMaxRowNumber;
}
void ExplosionPosition::setExplosionPictureColumnPixel(int explosionPictureColumnPixel)
{
    this->explosionPictureColumnPixel = explosionPictureColumnPixel;
}
void ExplosionPosition::setExplosionPictureRowPixel(int explosionPictureRowPixel)
{
    this->explosionPictureRowPixel = explosionPictureRowPixel;
}
void ExplosionPosition::setExplosionPictureMaxColumnNumber(int explosionPictureMaxColumnNumber)
{
    this->explosionPictureMaxColumnNumber = explosionPictureMaxColumnNumber;
}
void ExplosionPosition::setExplosionPictureMaxRowNumber(int explosionPictureMaxRowNumber)
{
    this->explosionPictureMaxRowNumber = explosionPictureMaxRowNumber;
}
void ExplosionPosition::update()
{
    if(currentExplosionPictureColumn < explosionPictureMaxColumnNumber)
    {
        currentExplosionPictureColumn++;
    }
    else
    {
        currentExplosionPictureColumn = 0;
        currentExplosionPictureRow++;
    }
    if(currentExplosionPictureRow >= explosionPictureMaxRowNumber)
    {
        currentExplosionPictureRow = 0;
        isRemove = true;
    }
}
bool ExplosionPosition::getIsRemove()
{
    if(this->explosionTypeSelection % 2 ==0)
    {
        if(particleEmitter->getParticleSystem()->getParticle()->empty())
        {
            return true;
        }
        return false;
    }
    return this->isRemove;
}

ParticleEmitter* ExplosionPosition::getParticleEmitter()
{
    return this->particleEmitter;
}
void ExplosionPosition::setExplosionTypeSelection(int explosionTypeSelection)
{
    this->explosionTypeSelection = explosionTypeSelection;
}
int ExplosionPosition::getExplosionTypeSelection()
{
    return this->explosionTypeSelection;
}
