#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
#include <QOpenGLWidget>
#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "planet.h"
#include <vector>



class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT
    QOpenGLBuffer vbo;
    QOpenGLBuffer ibo;
    GLfloat vertices[4*8];
    GLubyte indices [36];

    GLuint* indexData;
    GLfloat* vboData;
    unsigned int vboLength;
    unsigned int iboLength;

    QOpenGLShaderProgram* default130, *normal, *sunShader , *phongShader;

    QOpenGLTexture* earthTex, *sunTex, *moonTex, *venusTex, *mercuryTex, *marsTex, *jupiterTex, *saturnTex, *uranusTex, *neptunTex, *worldTex, *distortionTex;

    planet *earth, *sun, *moon, *venus, *mercury, *mars, *jupiter, *saturn, *uranus, *neptun, *world;

    GLfloat sunRot= 0.0,day=0.0, year=0.0, moonAroundEarth = 0.0, moonItSelf = 0.0, merkurUm = 0.0, moonAroundMars = 0.0,moonAroundMars1 = 0.0, venusUm =0.0, marsUm =0.0, jupiterUm =0.0, saturnUm=0.0, uranusUm=0.0, neptunUm=0.0;

    bool hasTexCoord;


signals:
     void sendTranslateZ(int value);

public slots:
    void receiveRotationZ(int value);

public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent),vbo(QOpenGLBuffer::VertexBuffer), ibo(QOpenGLBuffer::IndexBuffer){setFocusPolicy(Qt::StrongFocus);}
    unsigned int counter = 0;
    float time = 0.0f;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void createBuffer();
    void createGeometry();
    void render(planet *plan, QMatrix4x4 m, QMatrix4x4 p, QMatrix4x4 v);
    void createTextures();
    void createShader();

 private:
   std::vector<planet*> planets;
   unsigned int rotationz =0;
   GLfloat x =0;
   GLfloat y =0;
   GLfloat z=0;
   GLfloat rotx =0;
   GLfloat roty =0;
   GLfloat mouseX =0;
   GLfloat mouseY = 0;
};

#endif // MYGLWIDGET_H
