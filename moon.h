#ifndef MOON_H
#define MOON_H

#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <vector>



class moon
{
private:
      QOpenGLTexture *texture;
      QOpenGLShaderProgram *shader;


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
    moon(QOpenGLTexture *texture, QOpenGLShaderProgram *shader, float x, float y, float z, float grade, float selfRotation, float rotationAroundSun, float scale);
    QOpenGLTexture* getTexture();
    QOpenGLShaderProgram *getShader();

    void calculateRotation();

    float getX();
    float getY();
    float getZ();
    float getGrade();
    float getSelfRotation();
    float getRotationAroundSun();
    float getScale();

};


#endif // MOON_H
