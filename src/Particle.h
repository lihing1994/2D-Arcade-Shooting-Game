//
//  Particle.hpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//
#pragma once
#include <vector>
#include "ofMain.h"
#include "TransformObject.h"
#include "ParticleForce.h"
class Particle : public TransformObject
{
public:
    Particle();
    ~Particle();
    void draw();
    float age();
    void setImage(ofImage);
    void setRotationAngle(float rotationAngle);
    //Added:
    void setMovementSelection(int movementSelection);
    int getMovementSelection();
    glm::vec3 getVelocity();
    glm::vec3  getAcceleration();
    void setVelocity(glm::vec3 velocity);
    void setAcceleration(glm::vec3 acceleration);
    float getScales();
    void setScales(float scale);
    glm::vec3 sinCurveMovementInYDirection(float y);
    glm::vec3 sinCurveMovementInXDirection(float x);
    glm::vec3 sinCurveMovementInYReflectedDirection(float y);
    glm::vec3 sinCurveMovementInXReflectedDirection(float x);
    ofImage getImage();
    bool getIsOutOfRange();
    void setIsOutOfRange(bool isOutOfRange);
    void setLifeSpan(float lifespan);
    void setBirthtime(float birthtime);
    float getLifeSpan();
    float getRotationAngle();
    void addForce(ParticleForce* force);
    vector<ParticleForce* > getForce();
    //void setForces(glm::vec3 forces);
    void setMass(float mass);
    float getMass();
    void setRadius(float radius);
    void setColor(ofColor color);
    void setIsForExplosion(bool isForExplosion);
private:
    float scale;
    float cycles;
    glm::vec3 acceleration;
    bool isOutOfRange;
    float speed;    //   in pixels/sec
    ofImage image;
    float birthtime; // elapsed time in ms
    float lifespan;  //  time in ms
    string name;
    bool haveImage;
    float width;
    float height;
    float rotationAngle;
    int movementSelection;
    //Force will be apply if and only if
    //isPhysicApplied hold a true value
    bool isForExplosion;
    float mass;
    float damping;
    vector<ParticleForce* > forces;
    glm::vec3 velocity;
    float radius;
    ofColor color;
    

};
