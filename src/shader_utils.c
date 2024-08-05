#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

// Function to read the shader source code from a file
char* readShaderSource(const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

// Function to compile a shader from source
GLuint compileShader(GLenum shaderType, const char* source) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Error: Shader Compilation Failed\n%s\n", infoLog);
        return 0;
    }
    return shader;
}

// Function to load, compile, and link shaders into a program
GLuint loadShader(const char* vertexPath, const char* fragmentPath) {
    char* vertexSource = readShaderSource(vertexPath);
    if (!vertexSource) {
        return 0;
    }

    char* fragmentSource = readShaderSource(fragmentPath);
    if (!fragmentSource) {
        free(vertexSource);
        return 0;
    }

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    free(vertexSource);
    free(fragmentSource);

    if (!vertexShader || !fragmentShader) {
        return 0;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Error: Shader Program Linking Failed\n%s\n", infoLog);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
