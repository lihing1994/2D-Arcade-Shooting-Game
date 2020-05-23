//
//  TransformObject.cpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//

#include "TransformObject.h"
TransformObject::TransformObject() {
    trans = glm::vec3(0,0,0);
    scale = glm::vec3(1, 1, 1);
    rot = 0;
    isCollied = false;
}

void TransformObject::setPosition(glm::vec3 pos)
{
    trans = pos;
}
void TransformObject::setCollied(bool isCollied)
{
    this->isCollied = isCollied;
}
bool TransformObject::getIsCollied()
{
    return isCollied;
}
glm::vec3 TransformObject::getPosition()
{
    return this->trans;
}
