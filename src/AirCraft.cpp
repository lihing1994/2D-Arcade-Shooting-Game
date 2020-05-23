//
//  AirCraft.cpp
//  Project1_Part1
//
//  Created by HINGLI on 3/8/20.
//

#include "AirCraft.h"

AirCraft::AirCraft()
{
    this->position = glm::vec3(0,0,0);
    this->health = 100;
    img.load(imagePath);
    this->velocity = 10;
    //position -= glm::vec3(img.getWidth()/2,img.getHeight()/2,0);
}
AirCraft::AirCraft(glm::vec3 position, float health)
{
    this->position = position;
    this->health = health;
    img.load(imagePath);
    this->velocity = 10;
}
AirCraft::AirCraft(glm::vec3 position,float health,std::string imagePath)
{
    this->position = position;
    this->health = health;
    this->imagePath = imagePath;
    img.load(imagePath);
    this->velocity = 10;
}
AirCraft::AirCraft(glm::vec3 position,float health,std::string imagePath,float velocity)
{
    this->position = position;
    this->health = health;
    this->imagePath = imagePath;
    img.load(imagePath);
    this->velocity = velocity;
}
glm::vec3 AirCraft::getPosition()
{
    return position;
}
void AirCraft::setPosition(glm::vec3 position)
{
    this->position = position;
}
float AirCraft::getHealth()
{
    return health;
}
void AirCraft::setHealth(float health)
{
    this->health = health;
}
string AirCraft::getImagePath()
{
    return imagePath;
}
void AirCraft::setImagePath(std::string imagePath)
{
    this->imagePath = imagePath;
}
void AirCraft::setVelocity(float velocity)
{
    this->velocity = velocity;
}
float AirCraft::getVelocity()
{
    return velocity;
}
void AirCraft::setMoveUp()
{
    this->position.y -= velocity*1.5;
}
void AirCraft::setMoveDown()
{
    this->position.y += velocity*1.5;
}
void AirCraft::setMoveLeft()
{
    this->position.x -= velocity*1.5;
}
void AirCraft::setMoveRight()
{
    this->position.x += velocity*1.5;
}
