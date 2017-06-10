#ifndef PLANET_H
#define PLANET_H

#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <vector>

class planet
{
private:
      QOpenGLTexture *texture;
      QOpenGLShaderProgram *shader;
      std::vector<planet*> moons;

      float x;
      float y;
      float z;
      float grade;
      float selfRotation = 0.0;
      float selfOffset;
      float rotationAroundSun = 0.0;
      float aroundOffset;
      float scale;


public:
    planet(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale);
    QOpenGLTexture* getTexture();
    QOpenGLShaderProgram *getShader();

    void addMoon(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale);
    void calculateRotation();

    float getX();
    float getY();
    float getZ();
    float getGrade();
    float getSelfRotation();
    float getRotationAroundSun();
    float getScale();

    std::vector<planet*> getMoons();

};

#endif // PLANET_H
