//Sadia Afrin id:41230301548
//Md. Al Amin id:41230301816
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

float triangleX = 100.0f;
float triangleY = 400.0f;
float triangleRadius = 22.0f;

float squareX = 400.0f;
float squareY = 100.0f;
float squareSize = 25.0f;
float squareSpeed = 5.0f;

bool gameRunning = true;
int winner = 0;
clock_t gameStartTime;
clock_t lastMouseClickTime;
bool firstMouseClick = true;

const double GAME_TIME = 45.0;
const double MOUSE_INTERVAL = 0.3;

void drawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawTriangle()
{
    glColor3f(0.0f, 0.95f, 1.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(triangleX, triangleY + triangleRadius);
        glVertex2f(triangleX - triangleRadius, triangleY - triangleRadius);
        glVertex2f(triangleX + triangleRadius, triangleY - triangleRadius);
    glEnd();
}

void drawSquare()
{
    glColor3f(1.0f, 0.2f, 0.3f);

    glBegin(GL_QUADS);
        glVertex2f(squareX - squareSize, squareY - squareSize);
        glVertex2f(squareX + squareSize, squareY - squareSize);
        glVertex2f(squareX + squareSize, squareY + squareSize);
        glVertex2f(squareX - squareSize, squareY + squareSize);
    glEnd();
}

bool checkCollision()
{
    float dx = triangleX - squareX;
    float dy = triangleY - squareY;
    float distance = sqrtf(dx * dx + dy * dy);

    float minDistance = (triangleRadius * 0.75f) + squareSize;

    return distance < minDistance;
}

double getGameTime()
{
    clock_t currentTime = clock();
    return (double)(currentTime - gameStartTime) / CLOCKS_PER_SEC;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawTriangle();
    drawSquare();

    double elapsedTime = getGameTime();
    int remainingTime = (int)(GAME_TIME - elapsedTime);
    if (remainingTime < 0) remainingTime = 0;

    glColor3f(1.0f, 0.85f, 0.2f);
    char timerText[50];
    sprintf(timerText, "Time Left: %02d s", remainingTime);
    drawText(15, 470, timerText);

    glColor3f(0.85f, 0.85f, 0.9f);
    drawText(15, 445, "Square: [W A S D]  |  Triangle: [Mouse Click]");

    if (!gameRunning)
    {
        if (winner == 1)
        {
            glColor3f(1.0f, 0.3f, 0.3f);
            drawText(175, 270, "SQUARE WINS!");
            glColor3f(1.0f, 0.9f, 0.9f);
            drawText(145, 240, "Square Caught Triangle!");
        }
        else if (winner == 2)
        {
            glColor3f(0.0f, 0.95f, 1.0f);
            drawText(165, 270, "TRIANGLE WINS!");
            glColor3f(1.0f, 1.0f, 1.0f);
            drawText(145, 240, "Triangle Caught Square!");
        }
        else if (winner == 3)
        {
            glColor3f(1.0f, 0.85f, 0.2f);
            drawText(195, 270, "TIME UP!");
            glColor3f(1.0f, 1.0f, 1.0f);
            drawText(155, 240, "Match Draw! Nobody Caught!");
        }

        glColor3f(1.0f, 0.85f, 0.2f);
        drawText(160, 205, "Press 'R' to Restart");
    }

    glutSwapBuffers();
}

void keyboardFunc(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        triangleX = 100.0f;
        triangleY = 400.0f;

        squareX = 400.0f;
        squareY = 100.0f;

        gameStartTime = clock();
        lastMouseClickTime = clock();
        firstMouseClick = true;
        gameRunning = true;
        winner = 0;

        glutPostRedisplay();
        return;
    }

    if (!gameRunning)
        return;

    if (key == 'w' || key == 'W') squareY += squareSpeed;
    else if (key == 's' || key == 'S') squareY -= squareSpeed;
    else if (key == 'a' || key == 'A') squareX -= squareSpeed;
    else if (key == 'd' || key == 'D') squareX += squareSpeed;

    if (squareX - squareSize < 0) squareX = squareSize;
    if (squareX + squareSize > WINDOW_WIDTH) squareX = WINDOW_WIDTH - squareSize;
    if (squareY - squareSize < 0) squareY = squareSize;
    if (squareY + squareSize > WINDOW_HEIGHT) squareY = WINDOW_HEIGHT - squareSize;

    if (checkCollision())
    {
        gameRunning = false;
        winner = 1;
    }

    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_UP || !gameRunning)
        return;

    clock_t currentTime = clock();
    double timeSinceLastClick = (double)(currentTime - lastMouseClickTime) / CLOCKS_PER_SEC;

    if (firstMouseClick || timeSinceLastClick >= MOUSE_INTERVAL)
    {
        firstMouseClick = false;
        lastMouseClickTime = currentTime;

        int oglY = WINDOW_HEIGHT - y;

        triangleX = (float)x;
        triangleY = (float)oglY;

        if (triangleX - triangleRadius < 0) triangleX = triangleRadius;
        if (triangleX + triangleRadius > WINDOW_WIDTH) triangleX = WINDOW_WIDTH - triangleRadius;
        if (triangleY - triangleRadius < 0) triangleY = triangleRadius;
        if (triangleY + triangleRadius > WINDOW_HEIGHT) triangleY = WINDOW_HEIGHT - triangleRadius;

        if (checkCollision())
        {
            gameRunning = false;
            winner = 2;
        }

        glutPostRedisplay();
    }
}

void timerFunc(int value)
{
    if (gameRunning)
    {
        double elapsedTime = getGameTime();

        if (elapsedTime >= GAME_TIME)
        {
            gameRunning = false;
            winner = 3;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timerFunc, 0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initialization()
{
    glClearColor(0.04f, 0.06f, 0.1f, 1.0f);

    gameStartTime = clock();
    lastMouseClickTime = clock();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 50);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Triangle Catch Game - OpenGL");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);

    initialization();

    glutTimerFunc(16, timerFunc, 0);

    glutMainLoop();

    return 0;
}
