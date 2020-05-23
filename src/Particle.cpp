//
//  Particle.cpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//

#include "Particle.h"
Particle::Particle()
{
    speed = 0;
    velocity = glm::vec3(0, 0, 0);
    lifespan = -1;      // lifespan of -1 => immortal
    birthtime = 0;
    bSelected = false;
    haveImage = false;
    name = "Unamed";
    width = 60;
    height = 80;
    rotationAngle = 0;
    isOutOfRange =false;
    isForExplosion = false;
    mass = 1;
    damping = .99;
    this->radius = 2.0f;
}
Particle::~Particle()
{
    for(int i =0;i<this->forces.size();i++)
    {
        forces.erase(forces.begin()+i);
    }
    forces.clear();
}
float Particle::age()
{
    return (ofGetElapsedTimeMillis() - birthtime);
}

void Particle::setImage(ofImage img)
{
    image = img;
    haveImage = true;
    width = image.getWidth();
    height = image.getHeight();
}


void Particle::draw()
{
    ofSetColor(255, 255, 255, 255);
    // draw image centered and add in translation amount
    //
    if (haveImage)
    {
        if(this->movementSelection ==0)
        {
            ofPushMatrix();
            glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(trans.x, trans.y,0));
            glm::mat4 M = glm::rotate(m, glm::radians(rotationAngle), glm::vec3(0, 0, 1));
            ofMultMatrix(M);
            image.draw(-width / 2.0, -height / 2.0,0);
            ofPopMatrix();
        }
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
        else if(this->movementSelection == 1)
        {
            ofPushMatrix();
            glm::vec3 temp_position = glm::vec3(this->trans.x,this->trans.y,0);
            glm::mat4 m = glm::translate(glm::mat4(1.0), temp_position);
            glm::mat4 M = glm::rotate(m,glm::radians(-90.0f), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 2)
        {
            ofPushMatrix();
            glm::vec3 temp_position = glm::vec3(this->trans.x,this->trans.y,0);
            glm::mat4 m = glm::translate(glm::mat4(1.0), temp_position);
            glm::mat4 M = glm::rotate(m,glm::radians(1.0f), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 3)
        {
            ofPushMatrix();
            glm::vec3 dy = sinCurveMovementInYDirection(this->trans.y + 3);
            glm::vec3 lineAC = dy - glm::vec3(this->trans.x,this->trans.y,0);
            glm::vec3 lineAB = glm::vec3(0,image.getHeight()/2,0);
            float tempCosValue = glm::dot(lineAB,lineAC)/(glm::length(lineAB)*glm::length(lineAC));
            float temp_angle = glm::degrees(glm::acos(tempCosValue));
            if(lineAC.x > lineAB.x)
            {
                temp_angle *= -1;
            }
            glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(this->trans.x,this->trans.y,0));
            glm::mat4 M = glm::rotate(m,glm::radians(temp_angle), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if (this->movementSelection == 4)
        {
            ofPushMatrix();
            glm::vec3 dy = sinCurveMovementInXDirection(this->trans.x + 3);
            glm::vec3 lineAC = dy - glm::vec3(this->trans.x,this->trans.y,0);
            glm::vec3 lineAB = glm::vec3(0,image.getHeight()/2,0);
            float tempCosValue = glm::dot(lineAB,lineAC)/(glm::length(lineAB)*glm::length(lineAC));
            float temp_angle = glm::degrees(glm::acos(tempCosValue));
            if(lineAC.x > lineAB.x)
            {
                temp_angle *= -1;
            }
            glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(this->trans.x,this->trans.y,0));
            glm::mat4 M = glm::rotate(m,glm::radians(temp_angle), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 5)
        {
            ofPushMatrix();
            glm::vec3 temp_position = glm::vec3(this->trans.x,this->trans.y,0);
            glm::mat4 m = glm::translate(glm::mat4(1.0), temp_position);
            glm::mat4 M = glm::rotate(m,glm::radians(90.0f), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 6)
        {
            ofPushMatrix();
            glm::vec3 temp_position = glm::vec3(this->trans.x,this->trans.y,0);
            glm::mat4 m = glm::translate(glm::mat4(1.0), temp_position);
            glm::mat4 M = glm::rotate(m,glm::radians(180.0f), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 7)
        {
            ofPushMatrix();
            glm::vec3 dy = sinCurveMovementInYReflectedDirection(this->trans.y + 3);
            glm::vec3 lineAC = dy - glm::vec3(this->trans.x,this->trans.y,0);
            glm::vec3 lineAB = glm::vec3(0,image.getHeight()/2,0);
            float tempCosValue = glm::dot(lineAB,lineAC)/(glm::length(lineAB)*glm::length(lineAC));
            float temp_angle = glm::degrees(glm::acos(tempCosValue));
            if(lineAC.x > lineAB.x)
            {
                temp_angle *= -1;
            }
            glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(this->trans.x,this->trans.y,0));
            glm::mat4 M = glm::rotate(m,glm::radians(temp_angle), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
        else if(this->movementSelection == 8)
        {
            ofPushMatrix();
            glm::vec3 dy = sinCurveMovementInXReflectedDirection(this->trans.x + 3);
            glm::vec3 lineAC = dy - glm::vec3(this->trans.x,this->trans.y,0);
            glm::vec3 lineAB = glm::vec3(0,image.getHeight()/2,0);
            float tempCosValue = glm::dot(lineAB,lineAC)/(glm::length(lineAB)*glm::length(lineAC));
            float temp_angle = glm::degrees(glm::acos(tempCosValue));
            if(lineAC.x > lineAB.x)
            {
                temp_angle *= -1;
            }
            glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(this->trans.x,this->trans.y,0));
            glm::mat4 M = glm::rotate(m,glm::radians(temp_angle), glm::vec3(0,0,1));
            ofMultMatrix(M);
            image.draw(-image.getWidth()/2,-image.getHeight()/2);
            ofPopMatrix();
        }
    }
    else if(isForExplosion)
    {
        ofSetColor(this->color);
        ofDrawSphere(this->getPosition(), this->radius);
        ofSetColor(ofColor::white);
    }
    else
    {
        // in case no image is supplied, draw something.
        //
        ofSetColor(255, 0, 0);
        ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
    }
}
void Particle::setRotationAngle(float rotationAngle)
{
    this->rotationAngle = rotationAngle;
}
int Particle::getMovementSelection()
{
    return this->movementSelection;
}
void Particle::setMovementSelection(int movementSelection)
{
    this->movementSelection = movementSelection;
}
glm::vec3 Particle::getVelocity()
{
    return this->velocity;
}
glm::vec3 Particle::getAcceleration()
{
    return this->acceleration;
}
void Particle::setVelocity(glm::vec3 velocity)
{
    this->velocity = velocity;
}
void Particle::setAcceleration(glm::vec3  acceleration)
{
    this->acceleration = acceleration;
}
glm::vec3 Particle::sinCurveMovementInXDirection(float x)
{
    float u = (1.0f * x * PI)/ofGetWidth();
    return glm::vec3(x,-scale*sin(u)+ofGetHeight(),0);
}
glm::vec3 Particle::sinCurveMovementInYDirection(float y)
{
    float u = (1.0f * y * PI)/ofGetHeight();
    return glm::vec3(scale * sin(u),y, 0);
}
glm::vec3 Particle::sinCurveMovementInYReflectedDirection(float y)
{
    float u = (1.0f * y * PI)/ofGetHeight();
    return glm::vec3(ofGetWidth()-scale * sin(u),y, 0);
}
glm::vec3 Particle::sinCurveMovementInXReflectedDirection(float x)
{
    float u = (1.0f * x * PI)/ofGetWidth();
    return glm::vec3(x,scale*sin(u),0);
}
void Particle::setScales(float scale)
{
    this->scale = scale;
}
float Particle::getScales()
{
    return this->scale;
}
ofImage Particle::getImage()
{
    return this->image;
}
bool Particle::getIsOutOfRange()
{
    return this->isOutOfRange;
}
void Particle::setIsOutOfRange(bool isOutOfRange)
{
    this->isOutOfRange = isOutOfRange;
}
void Particle::setLifeSpan(float lifespan)
{
    this->lifespan = lifespan;
}
void Particle::setBirthtime(float birthtime)
{
    this->birthtime = birthtime;
}
float Particle::getLifeSpan()
{
    return this->lifespan;
}
float Particle::getRotationAngle()
{
    return this->rotationAngle;
}
void Particle::setMass(float mass)
{
    this->mass = mass;
}
float Particle::getMass()
{
    return this->mass;
}
void Particle::setRadius(float radius)
{
    this->radius = radius;
}
void Particle::setColor(ofColor color)
{
    this->color = color;
}
void Particle::addForce(ParticleForce* force)
{
    this->forces.push_back(force);
}
vector<ParticleForce*> Particle::getForce()
{
    return this->forces;
}
void Particle::setIsForExplosion(bool isForExplosion)
{
    this->isForExplosion = isForExplosion;
}

