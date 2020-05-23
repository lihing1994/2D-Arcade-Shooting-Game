#include "ofApp.h"
#define OF_KEY_SPACE 32
//--------------------------------------------------------------
void ofApp::setup()
{
    numEmitters = 1;
    if(ofGetWidth()<ofGetScreenWidth()||ofGetHeight()<ofGetScreenHeight())
    {
        ofToggleFullscreen();
    }
    timeMarker = ofGetSystemTimeMillis();
    shieldTimeMarker = -10;
    xRayTimeMarker = -10;
    ofSetBackgroundColor(ofColor::peachPuff);
    myFront.load("font/cooperBlack.ttf", 20);
    myScoreBoardFront.load("font/cooperBlack.ttf",20);
    loadAllImage();
    loadAllSound();
    gui.setup();
    gui.add(this->bulleTrate.setup("Bullet Creating rate", 5, 5, 10));
    gui.add(this->bulletLife.setup("Bullet life", 5, .1, 10));
    gui.add(this->bulletAngle.setup("Bullet shooting angle°: ",0,-45.0,45.0));
    gui.add(this->enemyRate.setup("Enemy rate", .5, .5, 10));
    gui.add(this->enemyLife.setup("Enemy life", 5, .11, 10));
    gui.add(isBackGroundPlay.setup("Background music",false));
    isGameBegan = false;
    bHide = true;
    isMouseOutOfWindowRange = false;
    isBackGroundPlay = true;
    this->bulletSystem = this->emitters[0]->getParticleSystem();
    this->enemySystem = this->enemyEmitter->getParticleSystem();
    this->score = 0;
    this->health = 5;
    this->isGameOver = false;
    this->isGameSuspend = false;
    this->isLevelSwitching = false;
    this->isAirCraftCollisionFlashing = false;
    skillColdDownTime = 10000;
    levelFontColorFlashingSelection = 1;
    isGameOverExplosionAddToDrawList = false;
    isGameOverExplosionEffectDrawCompleted = false;
}
void ofApp::exit()
{
    
    for(int i=0;i<emitters.size();i++)
    {
        emitters.erase(emitters.begin()+i);
    }
    emitters.clear();
    for(int i =0;i<collisionPosition.size();i++)
    {
        collisionPosition.erase(collisionPosition.begin()+1);
    }
    collisionPosition.clear();
    xRayLineEndingPoint.clear();
    mySoundPathList.clear();
    enemyImageList.clear();
    delete this->airCraft;
    delete this->bulletSystem;
    delete this->enemyEmitter;
    
}
//--------------------------------------------------------------
void ofApp::update()
{
    if(this->health <= 0)
    {
        isGameOver = true;
        if(!isGameOverExplosionAddToDrawList)
        {
            ExplosionPosition *temp = new ExplosionPosition(glm::vec3(ofGetScreenWidth()/2,ofGetScreenHeight()/2,0),ofColor::blue,2.0f,1000);
            temp->setExplosionTypeSelection(2);
            collisionPosition.push_back(temp);
            isGameOverExplosionAddToDrawList = true;
        }
        return;
    }
    else if(this->isGameSuspend)
    {
        return;
    }
    float current = ofGetSystemTimeMillis();
    if(!myBackGroundSound.isPlaying())
    {
        if(mySoundPlayingCouting==mySoundPathList.size())
        {
            mySoundPlayingCouting = 0;
        }
        myBackGroundSound.load(mySoundPathList[++mySoundPlayingCouting]);
        myBackGroundSound.play();
    }
    if(isBackGroundPlay == false)
    {
        myBackGroundSound.setPaused(true);
    }
    else
    {
        myBackGroundSound.setPaused(false);
    }
    if(!isGameBegan)
    {
        if(current-timeMarker > 500 )
        {
            
            if(gamingStartUpImageSelect == 1)
            {
                gamingStartUpImageSelect =2;
            }
            else
            {
                gamingStartUpImageSelect = 1;
            }
            timeMarker = current;
        }
    }
    else if(isGameBegan)
    {
        backGroundPicture.resize(ofGetWidth(),ofGetHeight());
        this->checkCollisionBulltAndEnemy();
        this->checkCollisionTurretAndEnemy();
        this->checkCollisionXRayAndEnemy();
        this->levelDifficultySwitch();
        for (int i = 0; i < numEmitters; i++)
        {
            ParticleEmitter *emitter = emitters[i];
            emitter->setRate(this->bulleTrate);
            emitter->setLifespan(this->bulletLife * 1000);    // convert to milliseconds
            glm::vec3 temp(100*glm::sin(glm::radians(float(this->bulletAngle))),-100*glm::cos(glm::radians(float(this->bulletAngle))),0);
            emitter->setVelocity(temp);
            emitter->setRoationAngle(this->bulletAngle);
            glm::vec3 bullet_begin_position = airCraft->getPosition() - glm::vec3(0,airCraftBodyImage.getHeight()/2,0);
            bullet_begin_position -= glm::vec3(0,bulletImage.getHeight(),0);
            emitter->setPosition(bullet_begin_position);
            emitter->update();
        }
        
        //Update for enemy..
        enemyEmitter->setRate(this->enemyRate);
        enemyEmitter->setLifespan(this->enemyLife * 1000);
        enemyEmitter->update();
        if(current-timeMarker > 500 )
        {
            if(gamingStartedPictureSelection == 1 )
            {
                airCraftBodyImage.load("images/Project1_part1_AirCraft_100by100_2.png");
                gamingStartedPictureSelection = 2;
            }
            else if(gamingStartedPictureSelection ==2)
            {
                airCraftBodyImage.load("images/Project1_part1_AirCraft_100by100_1.png");
                gamingStartedPictureSelection = 1;
            }
            timeMarker = current;
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw()
{
    if(this->isGameSuspend)
    {
        myFront.drawString("Game has been suspend!\nPlease press enter to resume the game", ofGetWidth()/2 - 225, ofGetWindowHeight()/2);
        return;
    }
    if(!isGameBegan)
    {
        ofSetColor(ofColor::white);
        myFront.drawString("Welcom to Shooter Arcade game", ofGetWidth()/2 - 225, 100);
        if(gamingStartUpImageSelect == 1)
        {
            gamingStartUpImage.draw(ofGetWidth()/2-halfGamingStartUpImageWidth,ofGetHeight()/2-halfGamingStartUpImageHight);
        }
        else
        {
            gamingStartUpImage2.draw(ofGetWidth()/2-halfGamingStartUpImageWidth,ofGetHeight()/2-halfGamingStartUpImageHight);
        }
        myFront.drawString("Please press spacebar to start the game", ofGetWidth()/2-225, ofGetHeight()/2+halfGamingStartUpImageHight+100);
      
    }
    else if(isMouseOutOfWindowRange)
    {
        myFront.drawString("Mouse out of windows area, game suspend", ofGetWidth()/2 - 225, ofGetWindowHeight()/2);
    }
    else if(isGameOver&&!isGameOverExplosionEffectDrawCompleted)
    {
        backGroundPicture.draw(0,0);
        drawExplosion();
    }
    else if(isGameOver)
    {
        myFront.drawString("Game Over! \nPlease press enter keys to restart the game", ofGetWidth()/2 - 225, ofGetWindowHeight()/2);
    }
    else if(isGameBegan)
    {
        backGroundPicture.draw(0,0);
    backGroundPictureLetter.draw(ofGetWidth()-backGroundPictureLetter.getWidth()-40,ofGetHeight()-backGroundPictureLetter.getHeight());
        if(isLevelSwitching)
        {
            this->printLevelSwitchingSentence();
        }
        if(isCircleShieldDrew)
        {
            this->drawCircleShield();
        }
        if(!this->collisionPosition.empty())
        {
            this->drawExplosion();
        }
        drawAirCraft();
        //glm::vec3 bullet_begin_position = airCraft->getPosition() - glm::vec3(0,airCraftBodyImage.getHeight()/2,0);
        //bullet_begin_position -= glm::vec3(0,bulletImage.getHeight(),0);
        if(isSpaceBarSelected)
        {
            for(int i = 0;i<numEmitters;i++)
            {
                //emitters[i]->setPosition(bullet_begin_position);
                emitters[i]->draw();
            }
        }
        else
        {
            for(int i =0;i<numEmitters;i++)
            {
                emitters[i]->getParticleSystem()->update();
                emitters[i]->getParticleSystem()->draw();
            }
        }
        enemyEmitter->draw();
        if(isXRayDrew)
        {
            drawXRay();
            ofSetColor(ofColor::white);
        }
        ofSetColor(ofColor::blanchedAlmond);
        myScoreBoardFront.drawString("Score : "+ std::to_string(this->score),ofGetScreenWidth()-200, 30);
        myScoreBoardFront.drawString("Health : "+ std::to_string(this->health),ofGetScreenWidth()-200, 50);
        ofSetColor(ofColor::white);
    }
    if (!bHide)
    {
        gui.draw();
    }
}


//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    if(!isMouseOutOfWindowRange)
    {
        airCraft->setPosition(glm::vec3(x,y,0));
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(!isMouseOutOfWindowRange)
    {
        airCraft->setPosition(glm::vec3(x,y,0));
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
    isMouseOutOfWindowRange = false;
    airCraft->setPosition(glm::vec3(x,y,0));
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    isMouseOutOfWindowRange = true;
}

void ofApp::keyPressed(int key) {
    if(!isGameBegan && key== OF_KEY_SPACE)
    {
        this->isGameBegan =true;
        this->enemyEmitter->start();
        this->levelTimeMarker = ofGetSystemTimeMillis();
    }
    else if(isGameBegan && !isGameOver && key== OF_KEY_SPACE)
    {
        for(int i =0;i<numEmitters;i++)
        {
            if(!emitters.at(i)->getIsStarted())
            {
                emitters.at(i)->start();
            }
        }
        myBackGroundSound.setVolume(0.1);
        if(!shootingBulletSound.isPlaying())
        {
            shootingBulletSound.play();
        }
        this->isSpaceBarSelected = true;
    }
    else if(isGameBegan && !isGameOver && !isGameSuspend && key==OF_KEY_RETURN)
    {
        this->isGameSuspend = true;
    }
    else if(isGameSuspend && key == OF_KEY_RETURN)
    {
        this->isGameSuspend = false;
    }
    else if(isGameOver && key == OF_KEY_RETURN)
    {
        this->emitters.clear();
        this->enemyEmitter = nullptr;
        this->setup();
    }
    else if(isGameBegan && (key == OF_KEY_UP||key==119||key == 87))//
    {
        //airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2
        if(airCraft->getPosition().y - airCraftBodyImage.getHeight()/2 >0)
            airCraft->setMoveUp();
    }
    else if(isGameBegan && (key == OF_KEY_DOWN||key==115||key==83))
    {
         if(airCraft->getPosition().y + airCraftBodyImage.getHeight()/2 < ofGetHeight())
             airCraft->setMoveDown();
    }
    else if(isGameBegan && (key == OF_KEY_LEFT||key==97||key==65))
    {
         if(airCraft->getPosition().x - airCraftBodyImage.getWidth()/2 > 0)
             airCraft->setMoveLeft();
    }
    else if(isGameBegan && (key == OF_KEY_RIGHT||key==100||key==68))
    {
        if(airCraft->getPosition().x + airCraftBodyImage.getWidth()/2 < ofGetWidth())
            airCraft->setMoveRight();
    }
    else if(key == 120 || key ==88)// when player press "x" or "X"
    {
        //If cirecle shile is drew already, limit the skill to be drew again.
        //Prevent player to continuously press key to draw circle forever.
        if(isCircleShieldDrew)
        {
            return;
        }
        //Limite player to use the shield skill in each 3 second
        if(ofGetSystemTimeMillis()-shieldTimeMarker > skillColdDownTime )
        {
            shieldTimeMarker = ofGetSystemTimeMillis();
            isCircleShieldDrew = true;
            circleFlashingSelction = 1;
        }
    }
    else if(key == 90 ||key == 122)
    {
        //If ray is drew already, limit the skill to be drew again.
        //Prevent player to continuously press key to draw ray forever.
        if(isXRayDrew)
        {
            return;
        }
        else if(ofGetSystemTimeMillis() - xRayTimeMarker > skillColdDownTime)
        {
            xRayTimeMarker = ofGetSystemTimeMillis();
            isXRayDrew = true;
            xRayFlashingSelection = 1;
        }
    }
    else if(key == 71 || key == 103)
    {
        bHide = !bHide;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if(key == OF_KEY_SPACE)
    {
        if(isGameBegan)
        {
            isSpaceBarSelected = false;
        }
        for(int i =0;i<numEmitters;i++)
        {
            emitters.at(i)->stop();
        }
        myBackGroundSound.setVolume(0.5);
    }
    // when player press "x" or "X", then draw a shield.
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
void ofApp::loadAllImage()
{
    gamingStartedPictureSelection = 1;
    airCraft = new AirCraft(glm::vec3(ofGetWidth()/2,ofGetHeight()/2,0),100,"images/Project1_part1_AirCraft_100by100_1.png");
    this->explosionPicture = new ofImage();
    if(!gamingStartUpImage.load("images/Project1_part1_AirCraft_500by500_1.png"))
    {
        cout<<"Can not load <Project1_part1_AirCraft_fixed_start_up_sprite.png> "<<endl;
        cout<<"game exit!"<<endl;
        ofExit();
    }
    else if(!gamingStartUpImage2.load("images/Project1_part1_AirCraft_500by500_2.png"))
    {
        cout<<"Can not load <Project1_part1_AirCraft_fixed_start_up_sprite_2.png>"<<endl;
        cout<<"game exit!"<<endl;
        ofExit();
    }
    else if(!airCraftBodyImage.load(airCraft->getImagePath()))
    {
        cout<<"Can not load <Project1_part1_AirCraft_100by100_1.png>"<<endl;
        cout<<"game exit!"<<endl;
        ofExit();
    }
    else if(!bulletImage.load("images/bullet.png"))
    {
        cout<<"<Can not load <bullet.png>"<<endl;
        cout<<"game exit!"<<endl;
        ofExit();
    }
    else if(!explosionPicture->load("images/exlosion_effect.png"))
    {
        cout<<"<Can not load <exlosion_effect.png>"<<endl;
        cout<<"game exit!"<<endl;
        ofExit();
    }
    else if(!backGroundPicture.load("images/BackGroundPicutre.jpeg"))
    {
        cout<<"Can not load <BackGroundPicutre.png>"<<endl;
        ofExit();
    }
    else if(!backGroundPictureLevel2.load("images/BackGroundPicutre_2.jpeg"))
    {
        cout<<"Can not load <BackGroundPicutre_2.png>"<<endl;
        ofExit();
    }
    else if(!backGroundPictureLevel3.load("images/BackGroundPicutre_3.jpeg"))
    {
        cout<<"Can not load <BackGroundPicutre_3.png>"<<endl;
        ofExit();
    }
    else if(!backGroundPictureLevel4.load("images/BackGroundPicutre_4.jpeg"))
    {
        cout<<"Can not load <BackGroundPicutre_4.png>"<<endl;
        ofExit();
    }
    else if(!backGroundPictureLetter.load("images/backgroundLetter.png"))
    {
        cout<<"Can not load <backgroundLetter.png>"<<endl;
        ofExit();
    }
    backGroundPicture.resize(ofGetScreenWidth(), ofGetScreenHeight());
    backGroundPictureLevel2.resize(ofGetScreenWidth(), ofGetScreenHeight());
    backGroundPictureLevel3.resize(ofGetScreenWidth(), ofGetScreenHeight());
    backGroundPictureLevel4.resize(ofGetScreenWidth(), ofGetScreenHeight());
    gamingStartUpImageSelect = 1;
    halfGamingStartUpImageWidth = gamingStartUpImage.getWidth()/2;
    halfGamingStartUpImageHight = gamingStartUpImage.getHeight()/2;
    //Set up emitter for bullet
    ParticleEmitter * temp = new ParticleEmitter(new ParticleSystem());
    glm::vec3 half(airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2,0);
    glm::vec3 bullet_begin_position = airCraft->getPosition() - glm::vec3(0,airCraftBodyImage.getHeight()/2,0);
    bullet_begin_position -= glm::vec3(bulletImage.getWidth()/2,bulletImage.getHeight(),0);
    temp->setPosition(bullet_begin_position);
    temp->setDrawable(false);
    temp->setChildImage(bulletImage);
    emitters.push_back(temp);
    
    //Following code add for enemy
    vector<std::string> enemyList;
    enemyList.push_back("images/enemy_1_100by100.png");
    enemyList.push_back("images/enemy_2_100by100.png");
    enemyList.push_back("images/enemy_3_100by100.png");
    enemyList.push_back("images/enemy_4_100by100.png");
    
    //Set up emitter for enemy object
    this->enemyEmitter = new ParticleEmitter(new ParticleSystem());
    this->enemyEmitter->setDrawable(false);
    this->enemyEmitter->setPosition(glm::vec3(0,0,0));
    for(int i=0;i<enemyList.size();i++)
    {
        ofImage temp_image;
        if(!temp_image.load(enemyList[i]))
        {
            std::cout<<"Can not load "<<enemyList[i]<<std::endl;
            std::cout<<"game exit!"<<std::endl;
            ofExit();
        }
        else
        {
            enemyImageList.push_back(temp_image);
        }
    }
    this->enemyEmitter->setPictureList(enemyImageList);
    //Setting the enemy emitter to allow enemy object moving in curve.
    this->enemyEmitter->setIsSpeicalMovement(true);
    this->enemyEmitter->setIsPictureRandomChange(true);
    this->level = 1;
    this->enemyEmitter->setLevelDifficulty(1);
    
}
void ofApp::loadAllSound()
{
    mySoundPathList.push_back("music/Binary Code - Interface Sound Effects.mp3");
    mySoundPathList.push_back("music/Brand X Music - Extinction.mp3");
    mySoundPathList.push_back("music/Position Music - Charmand's Empire.mp3");
    mySoundPathList.push_back("music/Position Music - Man At Arms.mp3");
    mySoundPlayingCouting = 0;
    myBackGroundSound.load(mySoundPathList[0]);
    myBackGroundSound.setVolume(0.5);
    myBackGroundSound.play();
    shootingBulletSound.load("music/Doom 2016 Pistol Sound Effect.mp3");
    myPunchSound.load("music/punch_sound.mp3");
}

void ofApp::drawXRay()
{
    glm::vec3 half(airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2,0);
    ofSetLineWidth(3.0f);
    glm::vec3 drawStartingPoint = airCraft->getPosition() - half;
    int numberOfXRayDraw = 4;
    int nextPoint = airCraftBodyImage.getWidth()/numberOfXRayDraw;
    if(ofGetSystemTimeMillis()-xRayTimeMarker>6000)
    {
        isXRayDrew = false;
        xRayTimeMarker = ofGetSystemTimeMillis();
    }
    else if(ofGetSystemTimeMillis()-xRayTimeMarker>5000)
    {
        if(xRayFlashingSelection == 1 && ofGetSystemTimeMillis()%2==0)
        {
            ofSetColor(ofColor::red);
            xRayFlashingSelection = 2;
        }
        else
        {
            ofSetColor(ofColor::lightYellow);
            xRayFlashingSelection = 1;
        }
    }
    else
    {
        ofSetColor(ofColor::red);
    }
    for(int i = 0;i<=numberOfXRayDraw;i++)
    {
    
        ofDrawLine(airCraft->getPosition()-glm::vec3(0,airCraftBodyImage.getHeight()/2,0) ,glm::vec3(drawStartingPoint.x,0,0));
        xRayLineEndingPoint.push_back(glm::vec3(drawStartingPoint.x,0,0));
        drawStartingPoint.x += nextPoint;
    }
}
void ofApp::drawCircleShield()
{
    if(ofGetSystemTimeMillis()-shieldTimeMarker>5000)
    {
        if(circleFlashingSelction ==1 && ofGetSystemTimeMillis()%2==0)
        {
            ofSetColor(ofColor::greenYellow);
            circleFlashingSelction = 2;
        }
        else
        {
            ofSetColor(ofColor::lightYellow);
            circleFlashingSelction = 1;
        }
        ofDrawCircle(airCraft->getPosition(),airCraftBodyImage.getWidth()/2+10);
        ofSetColor(ofColor::white);
        if(ofGetSystemTimeMillis()-shieldTimeMarker>6000)
        {
            isCircleShieldDrew = false;
            shieldTimeMarker = ofGetSystemTimeMillis();
        }
    }
    else
    {
        ofSetColor(ofColor::lightYellow);
        ofDrawCircle(airCraft->getPosition(),airCraftBodyImage.getWidth()/2+10);
        ofSetColor(ofColor::white);
    }
}
void ofApp::checkCollisionBulltAndEnemy()
{
    if(bulletSystem == nullptr || enemySystem == nullptr)
    {
        return;
    }
    else
    {
        bulletSystem = this->emitters[0]->getParticleSystem();
        enemySystem = this->enemyEmitter->getParticleSystem();
        for(int i = 0;i<enemySystem->getParticle()->size();i++)
        {
            if(!enemySystem->getParticle()->at(i).getIsOutOfRange())
            {
                for(int j = 0;j<bulletSystem->getParticle()->size();j++)
                {
                    if(!bulletSystem->getParticle()->at(j).getIsOutOfRange())
                    {
                        ofVec3f first = enemySystem->getParticle()->at(i).getPosition();
                        ofVec3f second = bulletSystem->getParticle()->at(j).getPosition();
                        ofVec3f distance = first - second;
                        if(distance.length() < this->enemyImageList[0].getHeight()/2+this->bulletImage.getHeight()/2)
                        {
                            if(!myPunchSound.isPlaying())
                            {
                                myPunchSound.play();
                            }
                            bulletSystem->getParticle()->at(j).setCollied(true);
                            enemySystem->getParticle()->at(i).setCollied(true);
                            this->score += 10;
                            ExplosionPosition *temp = new ExplosionPosition(first);
                            temp->setExplosionTypeSelection(2);
                            temp->setExplosionPictureMaxColumnNumber(8);
                            temp->setExplosionPictureMaxRowNumber(6);
                            temp->setExplosionPictureColumnPixel(256);
                            temp->setExplosionPictureRowPixel(256);
                            this->collisionPosition.push_back(temp);
                        }
                    }
                }
            }
        }
    }
}
void ofApp::checkCollisionTurretAndEnemy()
{
    if(this->airCraft==nullptr||this->enemySystem ==nullptr)
    {
        return;
    }
    else
    {
        enemySystem = this->enemyEmitter->getParticleSystem();
        for(int i =0;i<enemySystem->getParticle()->size();i++)
        {
            //Make sure only check the Sprites that within the screen area..
            if(!enemySystem->getParticle()->at(i).getIsOutOfRange())
            {
                glm::vec3 temp_turret_position = this->airCraft->getPosition();
                ofVec3f temp_enemy_position = enemySystem->getParticle()->at(i).getPosition();
                glm::vec3 distance = temp_turret_position - temp_enemy_position;
                if(glm::length(distance) < this->airCraftBodyImage.getHeight()/2 +enemySystem->getParticle()->at(i).getImage().getHeight()/2)
                {
                    if(!enemySystem->getParticle()->at(i).getIsCollied())
                    {
                        if(!myPunchSound.isPlaying())
                        {
                            myPunchSound.play();
                        }
                        enemySystem->getParticle()->at(i).setCollied(true);
                        if(!isCircleShieldDrew)
                        {
                            this->health -= 1;
                            this->isAirCraftCollisionFlashing = true;
                            this->AirCraftFlashingTimeMarker = ofGetSystemTimeMillis();
                        }
                        else
                        {
                            this->score += 10;
                            ExplosionPosition *temp = new ExplosionPosition(temp_enemy_position);
                            temp->setExplosionTypeSelection(1);
                            temp->setExplosionPictureMaxColumnNumber(8);
                            temp->setExplosionPictureMaxRowNumber(6);
                            temp->setExplosionPictureColumnPixel(256);
                            temp->setExplosionPictureRowPixel(256);
                            this->collisionPosition.push_back(temp);
                        }
                        
                    }
                }
            }
        }
    }
}
void ofApp::checkCollisionXRayAndEnemy()
{
    if(!isXRayDrew||this->enemySystem ==nullptr)
    {
        return;
    }
    glm::vec3 half(airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2,0);
    glm::vec3 airCraftPos = airCraft->getPosition() - glm::vec3(0,airCraftBodyImage.getHeight()/2,0);
    for(int i=0;i<xRayLineEndingPoint.size();i++)
    {
        glm::vec3 tempEndingPoint = xRayLineEndingPoint.at(i);
        for(int j =0;j<enemySystem->getParticle()->size();j++)
        {
            if(!enemySystem->getParticle()->at(j).getIsOutOfRange())
            {
                ofVec3f tempEnemyPostion = enemySystem->getParticle()->at(j).getPosition();
                if(airCraftPos.x == tempEndingPoint.x)
                {
                    continue;
                }
                float slope = (airCraftPos.y - tempEndingPoint.y)/(airCraftPos.x - tempEndingPoint.x);
                float b = airCraftPos.y - slope * airCraftPos.x;
                float tempKX = -slope * enemySystem->getParticle()->at(j).getPosition().x;
                float tempY = enemySystem->getParticle()->at(j).getPosition().y;
                float numerator = abs(tempKX+tempY-b);
                float denominator = sqrt(pow(-slope,2)+1);
                float distance = numerator/denominator;
                if(distance < enemySystem->getParticle()->at(j).getImage().getWidth()/2)
                {
                    enemySystem->getParticle()->at(j).setCollied(true);
                    this->score += 10;
                    ExplosionPosition *temp = new ExplosionPosition(tempEnemyPostion);
                    temp->setExplosionTypeSelection(1);
                    temp->setExplosionPictureMaxColumnNumber(8);
                    temp->setExplosionPictureMaxRowNumber(6);
                    temp->setExplosionPictureColumnPixel(256);
                    temp->setExplosionPictureRowPixel(256);
                    this->collisionPosition.push_back(temp);
                }
            }
        }
    }
    xRayLineEndingPoint.clear();
}
void ofApp::levelDifficultySwitch()
{
    if(this->level <4 && ofGetSystemTimeMillis()-levelTimeMarker >= 100*1000)
    {
        this->level = 4;
        this->enemyRate = 10;
        this->bulleTrate = 12;
        skillColdDownTime =5000;
        this->health += level*2;
        this->isLevelSwitching = true;
        this->printingLevelSwtichingMarker = ofGetSystemTimeMillis();
        if(!bulletImage.load("images/bullet_4.png"))
        {
            cout<<"Can not load <bullet_4.png>"<<endl;
        }
    }
    else if(this->level <3 && ofGetSystemTimeMillis()-levelTimeMarker >= 50*1000)
    {
        this->level = 3;
        this->enemyRate = 5;
        this->bulleTrate = 10;
        skillColdDownTime = 7000;
        this->isLevelSwitching = true;
        this->health += level*2;
        this->printingLevelSwtichingMarker = ofGetSystemTimeMillis();
        if(!bulletImage.load("images/bullet_3.png"))
        {
            cout<<"Can not load <bullet_3.png>"<<endl;
        }
    }
    else if(this->level <2 && ofGetSystemTimeMillis()-levelTimeMarker >= 15*1000)
    {
        this->level = 2;
        this->enemyRate = 3;
        this->bulleTrate = 8;
        this->health += level*2;
        skillColdDownTime = 8000;
        this->isLevelSwitching = true;
        this->printingLevelSwtichingMarker = ofGetSystemTimeMillis();
        if(!bulletImage.load("images/bullet_2.png"))
        {
            cout<<"Can not load <bullet_2.png>"<<endl;
        }
    }
}
void ofApp::printLevelSwitchingSentence()
{
    if(ofGetSystemTimeMillis() - this->printingLevelSwtichingMarker > 3000)
    {
        if(levelFontColorFlashingSelection ==1 && ofGetSystemTimeMillis()%2 ==0)
        {
            ofSetColor(ofColor::blue);
            levelFontColorFlashingSelection = 2;
            myFront.drawString("Preparing Level "+to_string(this->level), ofGetWidth()/2 - 100, ofGetHeight()/2);
        }
        else
        {
            ofSetColor(ofColor::white);
            levelFontColorFlashingSelection = 1;
            myFront.drawString("Preparing Level "+to_string(this->level),ofGetWidth()/2 - 100, ofGetHeight()/2);
        }
        ofSetColor(ofColor::white);
        if(ofGetSystemTimeMillis()-this->printingLevelSwtichingMarker>6000)
        {
            this->isLevelSwitching = false;
            this->printingLevelSwtichingMarker = ofGetSystemTimeMillis();
            this->enemyEmitter->setLevelDifficulty(level);
            for(int i=0;i<numEmitters;i++)
            {
                emitters.at(i)->setLevelDifficulty(this->level);
                emitters.at(i)->setChildImage(bulletImage);
            }
            if(level == 2)
            {
                this->backGroundPicture = backGroundPictureLevel2;
            }
            else if(level == 3)
            {
                this->backGroundPicture = backGroundPictureLevel3;
            }
            else if(level == 4)
            {
                this->backGroundPicture = backGroundPictureLevel4;
            }
        }
    }
    else
    {
        myFront.drawString("Preparing Level "+to_string(this->level), ofGetWidth()/2 - 100, ofGetHeight()/2);
    }
}

void ofApp::drawExplosion()
{
    //If no collision can be detected,
    //there is no need to draw exolosion effect.
    if(this->collisionPosition.empty())
    {
        return;
    }
    else
    {
        if(!isGameOver)
        {   for(int i = 0;i<collisionPosition.size();i++)
            {
                ExplosionPosition * temp = collisionPosition.at(i);
                if(temp->getExplosionTypeSelection() % 2 == 0)
                {
                    if(!temp->getIsRemove())
                    {
                        temp->getParticleEmitter()->update();
                        temp->getParticleEmitter()->draw();
                    }
                    else
                    {
                        this->collisionPosition.erase(collisionPosition.begin()+i);
                    }
                }
                else
                {
                    if(!temp->getIsRemove())
                    {
                        glm::vec3 temp_pos = collisionPosition.at(i)->getExplosionPosition();
                        explosionPicture->drawSubsection(temp_pos.x,temp_pos.y,temp->getExplosionPictureColumnPixel(),temp->getExplosionPictureRowPixel(), 256*temp->getCurrentExplosionPictureColumn(), 256*temp->getCurrentExplosionPictureRow());
                        temp->update();
                    }
                    else
                    {
                        this->collisionPosition.erase(collisionPosition.begin()+i);
                    }
                }
            }
        }
        else
        {
            for(int i =0;i<collisionPosition.size();i++)
            {
                ExplosionPosition * temp = collisionPosition.at(i);
                if(temp->getExplosionTypeSelection() % 2 == 0)
                {
                    if(!temp->getIsRemove())
                    {
                        temp->getParticleEmitter()->update();
                        temp->getParticleEmitter()->draw();
                    }
                    else
                    {
                        this->collisionPosition.erase(collisionPosition.begin()+i);
                    }
                }
            }
            if(collisionPosition.empty())
            {
                this->isGameOverExplosionEffectDrawCompleted = true;
            }
            
        }
    }
}
void ofApp::drawAirCraft()
{
    if(!isAirCraftCollisionFlashing)
    {
        glm::vec3 half(airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2,0);
        airCraftBodyImage.draw(airCraft->getPosition()-half);
    }
    else
    {
        if(ofGetSystemTimeMillis()-AirCraftFlashingTimeMarker > 500)
        {
            isAirCraftCollisionFlashing = false;
        }
        else if(ofGetSystemTimeMillis()% 2 == 0)
        {
            glm::vec3 half(airCraftBodyImage.getWidth()/2,airCraftBodyImage.getHeight()/2,0);
            airCraftBodyImage.draw(airCraft->getPosition()-half);
        }
    }
}
