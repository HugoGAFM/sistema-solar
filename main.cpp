#include <GL/freeglut.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846
#define NUM_ESTRELAS 500

// Olá professor! esse é o projeto do Sistema Solar. 
// Para criar o projeto eu utilizei a biblioteca freeglut, utilizando a biblioteca x64 bits (não a 32 bits!), se tentar utilizar o freeglut.dll de 32 bits, vai dar erro.
// para isso, o comando para rodar o projeto (considerando que a biblioteca freeglut está baixada) é esse:
// g++ main.cpp -o sistema-solar.exe -IC:\freeglut\include -LC:\freeglut\lib\x64 -lfreeglut -lopengl32 -lglu32
// de qualquer forma, se não conseguir rodar, eu vou disponibilizar o .exe do projeto no meu gitHub.
// o link do gitHub --> https://github.com/HugoGAFM/sistema-solar

// Ângulos de órbita dos planetas
float angMercurio = 0.0f, angVenus = 0.0f, angTerra = 0.0f, angMarte = 0.0f;
float angJupiter = 0.0f, angSaturno = 0.0f, angUrano = 0.0f, angNetuno = 0.0f;

// Ângulos de rotação própria
float rotMercurio = 0.0f, rotVenus = 0.0f, rotTerra = 0.0f, rotMarte = 0.0f;
float rotJupiter = 0.0f, rotSaturno = 0.0f, rotUrano = 0.0f, rotNetuno = 0.0f;

// Ângulos das luas
float angLua = 0.0f, angFobos = 0.0f, angEuropa = 0.0f, angTita = 0.0f;

// Velocidades de órbita dos planetas
float velMercurio = 0.045f, velVenus = 0.035f, velTerra = 0.029f, velMarte = 0.023f;
float velJupiter = 0.013f, velSaturno = 0.010f, velUrano = 0.007f, velNetuno = 0.005f;

// Velocidades de rotação própria
float velRotMercurio = 0.04f, velRotVenus = 0.01f, velRotTerra = 0.10f, velRotMarte = 0.097f;
float velRotJupiter = 0.24f, velRotSaturno = 0.20f, velRotUrano = 0.15f, velRotNetuno = 0.13f;

// Velocidades das luas
float velLua = 0.20f, velFobos = 0.30f, velEuropa = 0.15f, velTita = 0.12f;

// Câmera livre
float camX = 0.0f, camY = 5.0f, camZ = 32.0f;
float camYaw = 180.0f;  
float camPitch = 0.0f;

float camSpeed = 0.5f;
float camSensitivity = 0.3f;

bool pausado = false;
bool modoNoturno = false;

int lastMouseX, lastMouseY;
bool mouseLeftDown = false;

float estrelas[NUM_ESTRELAS][3];

float randomAngle() {
    return (float)(rand() % 360);
}

void inicializar() {
    if (modoNoturno) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
       } else {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    }
    glEnable(GL_DEPTH_TEST);         

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void gerarEstrelas() {
    for (int i = 0; i < NUM_ESTRELAS; i++) {
        estrelas[i][0] = (float)(rand() % 200 - 100);
        estrelas[i][1] = (float)(rand() % 200 - 100); 
        estrelas[i][2] = (float)(rand() % 200 - 100); 
    }
}


void desenhaEsfera(float raio) {
    glutSolidSphere(raio, 50, 50);
}

void desenharSistemaSolar() {
    // Sol
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    desenhaEsfera(0.7f);
    glPopMatrix();

    // Mercúrio
    glPushMatrix();
    glRotatef(angMercurio, 0, 1, 0);
    glTranslatef(2.0f, 0, 0);
    glRotatef(rotMercurio, 0, 1, 0);
    glColor3f(0.6f, 0.6f, 0.6f);
    desenhaEsfera(0.10f);
    glPopMatrix();

    // Vênus
    glPushMatrix();
    glRotatef(angVenus, 0, 1, 0);
    glTranslatef(4.0f, 0, 0);
    glRotatef(rotVenus, 0, 1, 0);
    glColor3f(1.0f, 0.8f, 0.2f);
    desenhaEsfera(0.20f);
    glPopMatrix();

    // Terra
    glPushMatrix();
    glRotatef(angTerra, 0, 1, 0);
    glTranslatef(6.0f, 0, 0);
    glRotatef(rotTerra, 0, 1, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaEsfera(0.25f);

    // Lua
    glPushMatrix();
    glRotatef(angLua, 0, 1, 0);
    glTranslatef(0.5f, 0, 0);
    glColor3f(0.8f, 0.8f, 0.8f);
    desenhaEsfera(0.05f);
    glPopMatrix();

    glPopMatrix();

    // Marte
    glPushMatrix();
    glRotatef(angMarte, 0, 1, 0);
    glTranslatef(8.0f, 0, 0);
    glRotatef(rotMarte, 0, 1, 0);
    glColor3f(1.0f, 0.3f, 0.0f);
    desenhaEsfera(0.15f);

    // Fobos
    glPushMatrix();
    glRotatef(angFobos, 0, 1, 0);
    glTranslatef(0.3f, 0, 0);
    glColor3f(0.7f, 0.7f, 0.7f);
    desenhaEsfera(0.03f);
    glPopMatrix();

    glPopMatrix();

    // Júpiter
    glPushMatrix();
    glRotatef(angJupiter, 0, 1, 0);
    glTranslatef(10.0f, 0, 0);
    glRotatef(rotJupiter, 0, 1, 0);
    glColor3f(1.0f, 0.85f, 0.6f);
    desenhaEsfera(0.60f);

    // Europa
    glPushMatrix();
    glRotatef(angEuropa, 0, 1, 0);
    glTranslatef(0.8f, 0, 0);
    glColor3f(0.85f, 0.9f, 1.0f);
    desenhaEsfera(0.06f);
    glPopMatrix();

    glPopMatrix();

    // Saturno
    glPushMatrix();
    glRotatef(angSaturno, 0, 1, 0);
    glTranslatef(13.0f, 0, 0);

    // Anel de Saturno (horizontal)
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glColor3f(0.8f, 0.7f, 0.5f);
    glutSolidTorus(0.10f, 1.0f, 30, 60);
    glPopMatrix();

    glRotatef(rotSaturno, 0, 1, 0);
    glColor3f(1.0f, 0.8f, 0.4f);
    desenhaEsfera(0.50f);

    // Titã
    glPushMatrix();
    glRotatef(angTita, 0, 1, 0);
    glTranslatef(1.6f, 0, 0);
    glColor3f(0.9f, 0.7f, 0.3f);
    desenhaEsfera(0.07f);
    glPopMatrix();

    glPopMatrix();

    // Urano
    glPushMatrix();
    glRotatef(angUrano, 0, 1, 0);
    glTranslatef(15.0f, 0, 0);
    glRotatef(rotUrano, 0, 1, 0);
    glColor3f(0.5f, 0.8f, 0.9f);
    desenhaEsfera(0.40f);
    glPopMatrix();

    // Netuno
    glPushMatrix();
    glRotatef(angNetuno, 0, 1, 0);
    glTranslatef(17.0f, 0, 0);
    glRotatef(rotNetuno, 0, 1, 0);
    glColor3f(0.0f, 0.0f, 0.6f);
    desenhaEsfera(0.40f);
    glPopMatrix();
}

void updateCamera() {
    float yawRad = camYaw * M_PI / 180.0f;

    float pitchRad = camPitch * M_PI / 180.0f;

    float dirX = cosf(pitchRad) * sinf(yawRad);
    float dirY = sinf(pitchRad);
    float dirZ = cosf(pitchRad) * cosf(yawRad);

    gluLookAt(camX, camY, camZ,
              camX + dirX, camY + dirY, camZ + dirZ,
              0.0f, 1.0f, 0.0f);

    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    updateCamera();

        if (modoNoturno) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDisable(GL_LIGHTING);
        glPointSize(1.5f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f); 
        for (int i = 0; i < NUM_ESTRELAS; i++) {
        glVertex3f(estrelas[i][0], estrelas[i][1], estrelas[i][2]);
        }
        glEnd();
    } else {
        glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    }

    desenharSistemaSolar();

    glutSwapBuffers();
}

void atualizar(int valor) {
    if (!pausado) {
        angMercurio += velMercurio;
        angVenus += velVenus;
        angTerra += velTerra;
        angMarte += velMarte;
        angJupiter += velJupiter;
        angSaturno += velSaturno;
        angUrano += velUrano;
        angNetuno += velNetuno;

        rotMercurio += velRotMercurio;
        rotVenus += velRotVenus;
        rotTerra += velRotTerra;
        rotMarte += velRotMarte;
        rotJupiter += velRotJupiter;
        rotSaturno += velRotSaturno;
        rotUrano += velRotUrano;
        rotNetuno += velRotNetuno;

        
        angLua += velLua;
        angFobos += velFobos;
        angEuropa += velEuropa;
        angTita += velTita;
    }


    glutPostRedisplay();
    glutTimerFunc(16, atualizar, 0);
}

void tecladoEspecial(int key, int x, int y) {
    float yawRad = camYaw * M_PI / 180.0f;
    float pitchRad = camPitch * M_PI / 180.0f;

    float dirX = cosf(pitchRad) * sinf(yawRad);
    float dirY = sinf(pitchRad);
    float dirZ = cosf(pitchRad) * cosf(yawRad);

    float rightX = sinf(yawRad - M_PI / 2.0f);
    float rightZ = cosf(yawRad - M_PI / 2.0f);

    switch(key) {
        case GLUT_KEY_UP:
            camX += dirX * camSpeed;
            camY += dirY * camSpeed;
            camZ += dirZ * camSpeed;
            break;
        case GLUT_KEY_DOWN:
            camX -= dirX * camSpeed;
            camY -= dirY * camSpeed;
            camZ -= dirZ * camSpeed;
            break;
        case GLUT_KEY_RIGHT:
            camX += rightX * camSpeed;
            camZ += rightZ * camSpeed;
            break;
        case GLUT_KEY_LEFT:
            camX -= rightX * camSpeed;
            camZ -= rightZ * camSpeed;
            break;
    }

    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    float yawRad = camYaw * M_PI / 180.0f;
    float pitchRad = camPitch * M_PI / 180.0f;

    float dirX = cosf(pitchRad) * sinf(yawRad);
    float dirY = sinf(pitchRad);
    float dirZ = cosf(pitchRad) * cosf(yawRad);

    float rightX = sinf(yawRad - M_PI / 2.0f);
    float rightZ = cosf(yawRad - M_PI / 2.0f);

    switch (key) {
        case 'w':
        case 'W':
            camX += dirX * camSpeed;
            camY += dirY * camSpeed;
            camZ += dirZ * camSpeed;
            break;
        case 's':
        case 'S':
            camX -= dirX * camSpeed;
            camY -= dirY * camSpeed;
            camZ -= dirZ * camSpeed;
            break;
        case 'd':
        case 'D':
            camX += rightX * camSpeed;
            camZ += rightZ * camSpeed;
            break;
        case 'a':
        case 'A':
            camX -= rightX * camSpeed;
            camZ -= rightZ * camSpeed;
            break;
        case 'p':
        case 'P':
            pausado = !pausado;  // Alterna entre pausado e rodando
            break;
        case 'n':
        case 'N':
            modoNoturno = !modoNoturno;
            break;
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (mouseLeftDown) {
        int dx = x - lastMouseX;
        int dy = y - lastMouseY;

        camYaw += dx * camSensitivity;
        camPitch += dy * camSensitivity;

        if(camPitch > 89.0f) camPitch = 89.0f;
        if(camPitch < -89.0f) camPitch = -89.0f;

        lastMouseX = x;
        lastMouseY = y;

        glutPostRedisplay();
    }
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseLeftDown = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            mouseLeftDown = false;
        }
    }

 
    if (button == 3 || button == 4) { 
        float zoomDirection = (button == 3) ? 1.0f : -1.0f;

       
        float yawRad = camYaw * M_PI / 180.0f;
        float pitchRad = camPitch * M_PI / 180.0f;

        float dirX = cosf(pitchRad) * sinf(yawRad);
        float dirY = sinf(pitchRad);
        float dirZ = cosf(pitchRad) * cosf(yawRad);

        camX += dirX * camSpeed * zoomDirection;
        camY += dirY * camSpeed * zoomDirection;
        camZ += dirZ * camSpeed * zoomDirection;

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    gerarEstrelas();

    angMercurio = randomAngle();
    angVenus    = randomAngle();
    angTerra    = randomAngle();
    angMarte    = randomAngle();
    angJupiter  = randomAngle();
    angSaturno  = randomAngle();
    angUrano    = randomAngle();
    angNetuno   = randomAngle();

    angLua     = randomAngle();
    angFobos   = randomAngle();
    angEuropa  = randomAngle();
    angTita    = randomAngle();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar 3D");

    inicializar();

    glutDisplayFunc(display);
    glutTimerFunc(16, atualizar, 0);

    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
