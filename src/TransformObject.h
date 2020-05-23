//
//  TransformObject.hpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//
#include "ofMain.h"
class TransformObject
{
public:
    TransformObject();
    glm::vec3 trans, scale;
    float    rot;
    bool    bSelected;
    void setCollied(bool isCollied);
    bool getIsCollied();
    void setPosition(glm::vec3 setPosition);
    glm::vec3 getPosition();
    //added
private:
    bool isCollied;
};
