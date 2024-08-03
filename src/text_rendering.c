#include <GL/glut.h>
#include "text_rendering.h"

void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void renderTextLines(float x, float startY, float lineHeight, const char* texts[], int count) {
    for (int i = 0; i < count; i++) {
        renderText(x, startY - i * lineHeight, texts[i]);
    }
}