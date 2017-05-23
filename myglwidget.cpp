#include "myglwidget.h"
#include <stack>
#include "modelloader.h"

void MyGLWidget::initializeGL(){
    createTextures();
    createShader();
    createGeometry();
    createBuffer();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    QPoint p = this->mapFromGlobal(QCursor ::pos());
    this->mouseX = p.x();
    this->mouseY = p.y();

}

void MyGLWidget::resizeGL(int width, int height){
    height = (height == 0) ? 1 : height;
    glViewport(0, 0, width, height);
}

void MyGLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std :: stack<QMatrix4x4> matrixStack;
    QMatrix4x4 modelMatrix, perspectiveMatrix, viewMatrix;
    perspectiveMatrix.setToIdentity();
    perspectiveMatrix.perspective(45.0, 4.0/3.0, 0.1, 100000.0);

    viewMatrix.setToIdentity();
    viewMatrix.translate(-x, -y, z);
    viewMatrix.rotate(rotx,1.0,0.0,0.0);
    viewMatrix.rotate(roty,0.0,1.0,0.0);
    viewMatrix.rotate(rotationz,0.0,1.0,0.0);

    glCullFace(GL_FRONT);
    modelMatrix.setToIdentity();
    modelMatrix.scale(100000);
    render(world, modelMatrix, perspectiveMatrix, viewMatrix);
    glCullFace(GL_BACK);

    modelMatrix.setToIdentity();
    matrixStack.push(modelMatrix);

    for (planet* iterator : planets)
    {
        modelMatrix = matrixStack.top();
        modelMatrix.rotate(iterator->getRotationAroundSun(),0.0,1.0,0.0);
        modelMatrix.translate(iterator->getX(),iterator->getY(),iterator->getZ());
        modelMatrix.rotate(iterator->getGrade(),0.0,0.0,1.0);

        matrixStack.push(modelMatrix);

        modelMatrix.rotate(iterator->getSelfRotation(),0.25,1.0,0.0);
        modelMatrix.scale(iterator->getScale());
        render(iterator,modelMatrix, perspectiveMatrix, viewMatrix);

        for (planet* iteratorMoon : iterator->getMoons())
        {
            modelMatrix = matrixStack.top();
            modelMatrix.rotate(iteratorMoon->getRotationAroundSun(),0.0,1.0,0.0);
            modelMatrix.translate(iteratorMoon->getX(),iteratorMoon->getY(),iteratorMoon->getZ());
            modelMatrix.rotate(iteratorMoon->getGrade(),0.0,0.0,1.0);
            modelMatrix.rotate(iteratorMoon->getSelfRotation(),0.0,1.0,0.0);
            modelMatrix.scale(iteratorMoon->getScale());
            render(iteratorMoon,modelMatrix, perspectiveMatrix,viewMatrix);

            iteratorMoon->calculateRotation();
        }
        matrixStack.pop();
        iterator->calculateRotation();
    }
   time += 0.0002;
}

void MyGLWidget::render(planet *plan, QMatrix4x4 m, QMatrix4x4 p, QMatrix4x4 v){

    QMatrix3x3 n = m.normalMatrix();
    QVector4D lightPosition(1.0,1.0,1.0,1.0);
    QVector3D lightIntensity(1.0,1.0,1.0);
    QVector3D kd(1.0,1.0,1.0);
    QVector3D ka(0.1,0.1,0.1);
    QVector3D ks(1.0,1.0,1.0);
    float shininess = 32.0;

    plan->getShader()->bind();
    vbo.bind();
    ibo.bind();

    int attrVertices = 0;
    attrVertices = plan->getShader()->attributeLocation("vert");
    int attrTexCoords = 1;
    attrTexCoords = plan->getShader()->attributeLocation("texCoord");
    int attrNorCoords = 2;
    attrNorCoords = plan->getShader()->attributeLocation("normCoord");

    plan->getShader()->enableAttributeArray(attrVertices);
    if(hasTexCoord){
        plan->getShader()->enableAttributeArray(attrTexCoords);
    }
    plan->getShader()->enableAttributeArray(attrNorCoords);
    plan->getTexture()->bind(0);
    plan->getShader()->setUniformValue("texture", 0);

    distortionTex->bind(1);
    plan->getShader()->setUniformValue("distortionTex", 1);

    int unifMatrix = 0;
    unifMatrix = plan->getShader()->uniformLocation("modelMatrix");
    plan->getShader()->setUniformValue(unifMatrix, m);
    int unifMatrix1 = 1;
    unifMatrix1 = plan->getShader()->uniformLocation("perspectiveMatrix");
    plan->getShader()->setUniformValue(unifMatrix1, p);
    int unifMatrix2 = 2;
    unifMatrix2 = plan->getShader()->uniformLocation("viewMatrix");
    plan->getShader()->setUniformValue(unifMatrix2, v);
    int unifTime = 3;
    unifTime = plan->getShader()->uniformLocation("time");
    plan->getShader()->setUniformValue(unifTime, time);
    int unifMatrix3 = 4;
    unifMatrix3 = plan->getShader()->uniformLocation("normalMatrix");
    plan->getShader()->setUniformValue(unifMatrix3, n);
    int unifLightP = 5;
    unifLightP = plan->getShader()->uniformLocation("lightPosition");
    plan->getShader()->setUniformValue(unifLightP, lightPosition);
    int unifLightI = 6;
    unifLightI = plan->getShader()->uniformLocation("lightIntensity");
    plan->getShader()->setUniformValue(unifLightI, lightIntensity);
    int unifKd = 7;
    unifKd = plan->getShader()->uniformLocation("kd");
    plan->getShader()->setUniformValue(unifKd, kd);
    int unifKa = 8;
    unifKa = plan->getShader()->uniformLocation("ka");
    plan->getShader()->setUniformValue(unifKa, ka);
    int unifKs = 9;
    unifKs = plan->getShader()->uniformLocation("ks");
    plan->getShader()->setUniformValue(unifKs, ks);
    int unifShine = 10;
    unifShine = plan->getShader()->uniformLocation("shininess");
    plan->getShader()->setUniformValue(unifShine, shininess);

    if(hasTexCoord){
        int offset = 0;
        int stride = 12 * sizeof(GLfloat);
        plan->getShader()->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
        offset += 4 * sizeof(GLfloat);
        plan->getShader()->setAttributeBuffer(attrNorCoords, GL_FLOAT, offset, 4, stride);
        offset += 4 * sizeof(GLfloat);
        plan->getShader()->setAttributeBuffer(attrTexCoords, GL_FLOAT, offset, 4, stride);
    }
    else{
        int offset = 0;
        int stride = 8 * sizeof(GLfloat);
        plan->getShader()->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
        offset += 4 * sizeof(GLfloat);
        plan->getShader()->setAttributeBuffer(attrNorCoords, GL_FLOAT, offset, 4, stride);
    }

    glDrawElements(GL_TRIANGLES, iboLength, GL_UNSIGNED_INT, 0);

    plan->getShader()->disableAttributeArray(attrVertices);
    if(hasTexCoord){
        plan->getShader()->disableAttributeArray(attrTexCoords);
    }
    plan->getShader()->disableAttributeArray(attrNorCoords);
    plan->getTexture()->release();
    distortionTex->release();
    vbo.release();
    ibo.release();
    plan->getShader()->release();

}

void MyGLWidget::receiveRotationZ(int value){
    rotationz = value;
}

void MyGLWidget::keyPressEvent(QKeyEvent *event){
     GLfloat scale_factor = 0.5;
     GLfloat scale_factor1 = 1.0;
     switch(event->key()){
     case Qt::Key_W:
     case Qt::Key_Up:
         y +=scale_factor;
         break;
     case Qt::Key_A:
     case Qt::Key_Left:
         x -= scale_factor;
         break;
     case Qt::Key_D:
     case Qt::Key_Right:
         x += scale_factor;
         break;
     case Qt::Key_S:
     case Qt::Key_Down:
         y -= scale_factor;
         break;
     case Qt::Key_G:
         x=0;
         y=0;
         z=0;
         rotx=0;
         roty=0;
         emit sendTranslateZ(z);
         break;
     default:
         QOpenGLWidget::keyPressEvent(event);
     }
 }

void MyGLWidget::wheelEvent(QWheelEvent *event){
    GLint scale_factor = 1;
    if(event->delta() >0){
        z +=scale_factor;
        emit sendTranslateZ(z);
    }
    else if(event->delta() <0){
      z-=scale_factor;
      emit sendTranslateZ(z);
    }
    else{
        QOpenGLWidget::wheelEvent(event);
    }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event){
    GLfloat scaleFactor = 0.5;
    if(event->x() - this->mouseX < 0){
        roty -= scaleFactor;
    }
    else if(event->x() - this->mouseX > 0){
        roty += scaleFactor;
    }
    this->mouseX = event->x();

    if(event->y() - this->mouseY < 0){
        rotx -= scaleFactor;
    }
    else if(event->y() - this->mouseY > 0){
        rotx += scaleFactor;
    }
    this->mouseY = event->y();
}

void MyGLWidget::createGeometry(){

    sun = new planet(sunTex,sunShader,0.0,0.0,0.0,   7.25,    0.1,  0.0,    1.0);
    mercury = new planet(mercuryTex,phongShader, 1.5, 0.0,1.0, 1.0, 0.5, 0.22,   0.1);
    venus = new planet(venusTex,phongShader, 2.7,0.0,1.0,   177.36,  0.5, 0.08125,0.25);
    earth = new planet(earthTex,phongShader, 3.75,0.0,1.0,  -23.44,  0.5, 0.05,   0.27);
    earth->addMoon(moonTex,phongShader, 0.6,0.0,0.0,   6.68,    0.5, 0.2,    0.054);
    mars = new planet(marsTex,phongShader, 5.7,0.0,1.0,   25.19,   0.5, 0.03,   0.14);
    mars->addMoon(moonTex,phongShader,     0.4,0.0,0.0,   6.68,    0.5, 0.4,    0.045);
    mars->addMoon(moonTex,phongShader,     -0.4,0.0,0.0, 6.68,    0.5, 0.4,    0.045);
    jupiter = new planet(jupiterTex,phongShader, 11.73,0.0,1.0, 3.13,    0.5, 0.024,  0.55);
    saturn = new planet(saturnTex,phongShader, 17.92,0.0,1.0, 26.73,   0.5, 0.012,  0.48);
    uranus = new planet(uranusTex,phongShader, 22.9,0.0,1.0,  97.86,   0.5, 0.0055, 0.35);
    neptun = new planet(neptunTex,phongShader, 30.0,0.0,1.0,  29.58,   0.5, 0.0028, 0.3);
    world = new planet(worldTex, default130, 0.0,0.0,0.0,   0.0,     0.0,  0.0,    100000);

    planets.push_back(sun);
    planets.push_back(mercury);
    planets.push_back(venus);
    planets.push_back(earth);
    planets.push_back(mars);
    planets.push_back(jupiter);
    planets.push_back(saturn);
    planets.push_back(uranus);
    planets.push_back(neptun);

}

void MyGLWidget::createBuffer(){
    ModelLoader model;
    bool res = model.loadObjectFromFile("/home/nisi/Studium/CG Praktikum/Praktikum neu/Praktikum3_n/sphere_high.obj");
    if (res) {
    if(model.hasTextureCoordinates()){
        hasTexCoord = true;
        vboLength = model.lengthOfVBO(0,true,true);
        iboLength = model.lengthOfIndexArray();
        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genVBO(vboData,0,true,true);
        model.genIndexArray(indexData);
        }
     else{
        hasTexCoord = false;
        vboLength = model.lengthOfVBO(0,true,false);
        iboLength = model.lengthOfIndexArray();
        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genVBO(vboData,0,true,false);
        model.genIndexArray(indexData);
        }
    }
    else {}

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(vboData, sizeof(GLfloat) * vboLength);
    vbo.release();

    ibo.create();
    ibo.bind();
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo.allocate(indexData, sizeof(GLuint) * iboLength);
    ibo.release();
}

void MyGLWidget::createTextures(){

    glEnable(GL_TEXTURE_2D);

    distortionTex = new QOpenGLTexture(QImage(":/sun.jpg").mirrored());
    distortionTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    distortionTex->setMagnificationFilter(QOpenGLTexture::Linear);
    distortionTex->setWrapMode(QOpenGLTexture::Repeat);

    sunTex = new QOpenGLTexture(QImage(":/sun.jpg").mirrored());
    sunTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    sunTex->setMagnificationFilter(QOpenGLTexture::Linear);

    mercuryTex = new QOpenGLTexture(QImage(":/mercury.jpg").mirrored());
    mercuryTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    mercuryTex->setMagnificationFilter(QOpenGLTexture::Linear);

    venusTex = new QOpenGLTexture(QImage(":/venus.jpg").mirrored());
    venusTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    venusTex->setMagnificationFilter(QOpenGLTexture::Linear);

    earthTex = new QOpenGLTexture(QImage(":/earth.jpg").mirrored());
    earthTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    earthTex->setMagnificationFilter(QOpenGLTexture::Linear);

    marsTex = new QOpenGLTexture(QImage(":/mars.jpg").mirrored());
    marsTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    marsTex->setMagnificationFilter(QOpenGLTexture::Linear);

    jupiterTex = new QOpenGLTexture(QImage(":/jupiter.jpg").mirrored());
    jupiterTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    jupiterTex->setMagnificationFilter(QOpenGLTexture::Linear);

    saturnTex = new QOpenGLTexture(QImage(":/saturn.jpg").mirrored());
    saturnTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    saturnTex->setMagnificationFilter(QOpenGLTexture::Linear);

    uranusTex = new QOpenGLTexture(QImage(":/uranus.jpg").mirrored());
    uranusTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    uranusTex->setMagnificationFilter(QOpenGLTexture::Linear);

    neptunTex = new QOpenGLTexture(QImage(":/neptune.jpg").mirrored());
    neptunTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    neptunTex->setMagnificationFilter(QOpenGLTexture::Linear);

    moonTex = new QOpenGLTexture(QImage(":/moon.jpg").mirrored());
    moonTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    moonTex->setMagnificationFilter(QOpenGLTexture::Linear);

    worldTex = new QOpenGLTexture(QImage(":/world.jpg").mirrored());
    worldTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    worldTex->setMagnificationFilter(QOpenGLTexture::Linear);

}

void MyGLWidget::createShader(){

    default130 = new QOpenGLShaderProgram();
    default130->addShaderFromSourceFile(QOpenGLShader::Vertex,":/default130.vert");
    default130->addShaderFromSourceFile(QOpenGLShader::Fragment,":/default130.frag");
    default130->link();

    normal = new QOpenGLShaderProgram();
    normal->addShaderFromSourceFile(QOpenGLShader::Vertex,":/normal.vert");
    normal->addShaderFromSourceFile(QOpenGLShader::Fragment,":/normal.frag");
    normal->link();

    sunShader = new QOpenGLShaderProgram();
    sunShader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/default130.vert");
    sunShader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/sun.frag");
    sunShader->link();

    phongShader = new QOpenGLShaderProgram();
    phongShader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/phong.vert");
    phongShader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/phong.frag");
    phongShader->link();
}
