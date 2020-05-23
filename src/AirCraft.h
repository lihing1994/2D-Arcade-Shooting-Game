//
//  AirCraft.hpp
//  Project1_Part1
//
//  Created by HINGLI on 3/8/20.
//

#include "ofMain.h"
#include <iostream>
#include <vector>
#include <stdlib.h>     
#include <time.h>
class AirCraft
{
    public:
        AirCraft();
        AirCraft(glm::vec3 position, float health);
        AirCraft(glm::vec3 position,float health,std::string imagePath);
        AirCraft(glm::vec3 position,float health,std::string imagePath,float velocity);
        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);
        float getHealth();
        void setHealth(float health);
        string getImagePath();
        void setImagePath(std::string imagePath);
        float getVelocity();
        void setVelocity(float velocity);
        void setMoveUp();
        void setMoveDown();
        void setMoveLeft();
        void setMoveRight();    
    private:
        ofImage img;
        glm::vec3 position;
        float health;
        std::string imagePath;
        float velocity;
};
