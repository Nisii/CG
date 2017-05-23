#include "moon.h"

moon::moon(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale)
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

QOpenGLTexture* moon::getTexture(){
    return this->texture;
}

QOpenGLShaderProgram* moon::getShader(){
    return this->shader;
}

void moon::calculateRotation()
{
    this->selfRotation += this->selfOffset;
    this->rotationAroundSun += this->aroundOffset;
}

float moon::getX()
{
    return this->x;
}

float moon::getY()
{
    return this->y;
}

float moon::getZ()
{
    return this->z;
}

float moon::getGrade()
{
    return this->grade;
}

float moon::getSelfRotation()
{
    return this->selfRotation;
}

float moon::getRotationAroundSun()
{
    return this->rotationAroundSun;
}

float moon::getScale()
{
    return this->scale;
}
