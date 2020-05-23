//
//  ParticleEmitter.cpp
//  Project1_Part1
//
//  Created by HINGLI on 3/7/20.
//

#include "ParticleEmitter.h"
ParticleEmitter::ParticleEmitter()
{
    this->sys = new ParticleSystem();
    init();
}
ParticleEmitter::ParticleEmitter(ParticleSystem * particleSystem)
{
    if(particleSystem!=nullptr)
    {
        this->sys = particleSystem;
        init();
    }
    else
    {
        cout<<"Can not setting a null pointer to particleSystem"<<endl;
        ofExit();
    }
}
ParticleEmitter::ParticleEmitter(ParticleSystem * particleSystem,bool isForExplosionEffect,glm::vec3 pos)
{
    init();
    this->sys = particleSystem;
    this->isForExplosionEffect = isForExplosionEffect;
    this->setPosition(pos);
    if(isForExplosionEffect)
    {
        explosionParticleSpawn();
    }
}


ParticleEmitter::ParticleEmitter(ParticleSystem * particleSystem,bool isForExplosionEffect,glm::vec3 pos,ofColor particlColor,float particleRadius,int groupSize)
{
    init();
    this->sys = particleSystem;
    this->isForExplosionEffect = isForExplosionEffect;
    this->particleColor = particlColor;
    this->particleRadius = particleRadius;
    this->groupSize = groupSize;
    this->setPosition(pos);
    if(isForExplosionEffect)
    {
        explosionParticleSpawn();
    }
}



ParticleEmitter::~ParticleEmitter()
{
    pictureList.clear();
    delete this->sys;
}
void ParticleEmitter::init()
{
    srand((unsigned int)time(NULL));
    lifespan = 3000;    // milliseconds
    started = false;
    lastSpawned = 0;
    rate = 1;    // sprites/sec
    haveChildImage = false;
    haveImage = false;
    velocity = glm::vec3(100, -100, 0);
    drawable = true;
    width = 50;
    height = 50;
    rotationAngle = 0;
    setLevelDifficulty(1);
    this->oneShot = false;
    this->fired = false;
    this->isForExplosionEffect = false;
    this->isSpeicalMovement = false;
    this->groupSize = 50;
    particleColor = ofColor::red;
    particleRadius = 3.0f;
}
void ParticleEmitter::draw()
{
    if (drawable && !this->isForExplosionEffect)
    {
        if (haveImage)
        {
            image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
        }
        else
        {
            ofSetColor(0, 0, 200);
            ofDrawRectangle(-width/2 + trans.x, -height/2 + trans.y, width, height);
        }
    }
    sys->draw();
}

void ParticleEmitter::update() {
    if(this->isForExplosionEffect)
    {
        sys->update();
        return;
    }
    else if (!started)
    {
        return;
    }
    float temp_time = ofGetElapsedTimeMillis();
    if ((temp_time - lastSpawned) > (1000.0/rate))
    {
        Particle particle;
        if (haveChildImage)
        {
            particle.setImage(childImage);
        }
        else if(isPictureRandomChange)
        {
            int randomPicture = (int)rand() % this->pictureList.size();
            particle.setImage(this->pictureList[randomPicture]);
        }
        //Special Movement include:
        //  1.Acceleartion
        //  2.Random curve movement.
        //  3.setting the curve and cycles for particle.
        if(this->isSpeicalMovement)
        {
            particle.setMovementSelection((int)rand()%levelDifficulty+1);
            this->sys->setLevelDifficulty(this->levelDifficulty);
            /*
            As I defined,
            movementSelection = 1 -> horizontalMoovementInXDirection
            movementSelection = 2 -> verticalMovementInYDirection
            movementSelection = 3 -> sinCurveMovementInYDirection
            movementSelection = 4 -> sinCurveMovementInXDirection
            movementSelection = 5 -> horizontalMoovementInXOppisiteDirection
            movementSelection = 6 -> verticalMovementInYOppisiteDirection
            movementSelection = 7 -> sinCurveMovementInYReflectedDirection
            movementSelection = 8 -> sinCurveMovementInXReflectedDirection
            */
            if(particle.getMovementSelection()==1)
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty,levelDifficulty,0));
                glm::vec3 pos = glm::vec3(0,(int)rand()%(ofGetHeight()-(int)particle.getImage().getHeight())+particle.getImage().getHeight(),0);
                particle.setPosition(pos);
            }
            else if(particle.getMovementSelection() ==2 )
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty,levelDifficulty,0));
                glm::vec3 pos = glm::vec3((int)rand()% (ofGetWidth()-(int)particle.getImage().getHeight())+particle.getImage().getHeight(),0,0);
                particle.setPosition(pos);
            }
            if(particle.getMovementSelection() == 3)
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty,levelDifficulty,0));
                particle.setScales((int)rand() % ofGetWidth()+10);
                particle.setPosition(glm::vec3(0,0,0));
            }
            else if(particle.getMovementSelection() ==4)
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty,levelDifficulty,0));
                particle.setScales((int)rand() % ofGetHeight()+10);
                particle.setPosition(glm::vec3(0,ofGetHeight(),0));
            }
            else if(particle.getMovementSelection() == 5)
            {
                particle.setVelocity(glm::vec3(-60-levelDifficulty,-60-levelDifficulty,0));
                particle.setAcceleration(glm::vec3(-15,-15,0)+glm::vec3(-levelDifficulty,-levelDifficulty,0));
                glm::vec3 pos = glm::vec3(ofGetWidth(),(int)rand()% (ofGetWidth()-(int)particle.getImage().getHeight())+particle.getImage().getHeight(),0);
                particle.setPosition(pos);
            }
            else if(particle.getMovementSelection() == 6)
            {
                particle.setVelocity(glm::vec3(-60-levelDifficulty,-60-levelDifficulty,0));
                particle.setAcceleration(glm::vec3(-15,-15,0)+glm::vec3(-levelDifficulty,-levelDifficulty,0));
                glm::vec3 pos = glm::vec3((int)rand()% (ofGetWidth()-(int)particle.getImage().getHeight())+particle.getImage().getHeight(),ofGetHeight(),0);
                particle.setPosition(pos);
            }
            else if(particle.getMovementSelection() == 7)
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty*levelDifficulty,levelDifficulty*levelDifficulty,0));
                particle.setScales((int)rand() % ofGetWidth()+10);
                particle.setPosition(glm::vec3(ofGetWidth(),0,0));
            }
            else if(particle.getMovementSelection() == 8)
            {
                particle.setVelocity(glm::vec3(60+levelDifficulty,60+levelDifficulty,0));
                particle.setAcceleration(glm::vec3(15,15,0)+glm::vec3(levelDifficulty,levelDifficulty,0));
                particle.setScales((int)rand() % ofGetHeight()+10);
                particle.setPosition(glm::vec3(0,0,0));
            }
        }
        else
        {
            particle.setAcceleration(glm::vec3(0,-3,0) + glm::vec3(0,-levelDifficulty,0));
            particle.setMovementSelection(0);
            particle.setVelocity(velocity);
            particle.setPosition(trans);
        }
        particle.setLifeSpan(lifespan);
        particle.setBirthtime(temp_time);
        particle.setRotationAngle(rotationAngle);
        sys->add(particle);
        lastSpawned = temp_time;
    }
    sys->update();
}

void ParticleEmitter::start() {
    started = true;
    lastSpawned = ofGetElapsedTimeMillis();
}

void ParticleEmitter::stop() {
    started = false;
    fired = false;
}


void ParticleEmitter::setLifespan(float life) {
    lifespan = life;
}

void ParticleEmitter::setVelocity(ofVec3f v) {
    velocity = v;
}

void ParticleEmitter::setChildImage(ofImage img) {
    childImage = img;
    haveChildImage = true;
}

void ParticleEmitter::setImage(ofImage img) {
    image = img;
}

void ParticleEmitter::setRate(float r) {
    rate = r;
}
void ParticleEmitter::setRoationAngle(float rotationAngle)
{
    this->rotationAngle = rotationAngle;
}
void ParticleEmitter::setPictureList(vector<ofImage> pictureList)
{
    this->pictureList = pictureList;
}
void ParticleEmitter::setIsSpeicalMovement(bool isSpeicalMovement)
{
    this->isSpeicalMovement = isSpeicalMovement;
    this->sys->setIsSpecialMovement(isSpeicalMovement);
}
void ParticleEmitter::setIsPictureRandomChange(bool isPictureRandomChange)
{
    if(pictureList.empty())
    {
        isPictureRandomChange = false;
        return;
    }
    this->isPictureRandomChange = isPictureRandomChange;
}
int ParticleEmitter::getLevelDifficulty()
{
    return this->levelDifficulty;
}
ParticleSystem* ParticleEmitter::getParticleSystem()
{
    return this->sys;
}
bool ParticleEmitter::getIsStarted()
{
    return this->started;
}
void ParticleEmitter::setDrawable(bool drawable)
{
    this->drawable = drawable;
}
void ParticleEmitter::setLevelDifficulty(int levelDifficulty)
{
    if(levelDifficulty * 2 > 8)
    {
        return;
    }
    this->levelDifficulty = levelDifficulty*2;
}
void ParticleEmitter::setIsForExplosionEffect(bool isForExplosionEffect)
{
    this->isForExplosionEffect = isForExplosionEffect;
}
void ParticleEmitter::explosionParticleSpawn()
{
    float tempTime = ofGetElapsedTimeMillis();
    Particle particle;
    particle.setPosition(this->getPosition());
    particle.setLifeSpan(lifespan);
    particle.setVelocity(this->velocity);
    particle.setAcceleration(glm::vec3(0,0,0));
    particle.setBirthtime(tempTime);
    particle.setIsForExplosion(true);
    particle.setRadius(this->particleRadius);
    particle.setColor(this->particleColor);
    for(int i = 0 ;i<this->groupSize;i++)
    {
        this->sys->add(particle);
    }
}
