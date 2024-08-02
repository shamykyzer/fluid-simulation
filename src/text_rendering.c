#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "text_rendering.h"

// Render text on screen at a given position
void renderText(GLFWwindow* window, const char* text, float x, float y) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glRasterPos2f(x, y); // Use glRasterPos2f instead of glWindowPos2f
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
