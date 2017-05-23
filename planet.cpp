#include "planet.h"

planet::planet(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale)
{
    this->texture = texture;
    this->shader = shader;
    this->x = x;
    this->y = y;
    this->z = z;
    this->grade = grade;
    this->selfOffset = selfRotation;
    this->selfRotation = selfRotation;
    this->aroundOffset = rotationAroundSun;
    this->rotationAroundSun = rotationAroundSun;
    this->scale = scale;
}

void planet::addMoon(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale)
{
    planet* temp = new planet(texture,shader,x,y,z,grade,selfRotation,rotationAroundSun,scale);
    moons.push_back(temp);
}


std::vector<planet*> planet::getMoons()
{
    return moons;
}

QOpenGLTexture* planet::getTexture(){
    return this->texture;
}

QOpenGLShaderProgram* planet::getShader(){
    return this->shader;
}

void planet::calculateRotation()
{
    this->selfRotation += this->selfOffset;
    this->rotationAroundSun += this->aroundOffset;
}

float planet::getX()
{
    return this->x;
}

float planet::getY()
{
    return this->y;
}

float planet::getZ()
{
    return this->z;
}

float planet::getGrade()
{
    return this->grade;
}

float planet::getSelfRotation()
{
    return this->selfRotation;
}

float planet::getRotationAroundSun()
{
    return this->rotationAroundSun;
}

float planet::getScale()
{
    return this->scale;
}
