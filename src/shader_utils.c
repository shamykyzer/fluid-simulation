#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

// Function to read the shader source code from a file
char* readShaderSource(const char* filePath) {
    // Open the file in binary read mode
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        // Print error message if file cannot be opened
        fprintf(stderr, "Unable to open file %s\n", filePath);
        return NULL;
    }

    // Move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);
    // Get the length of the file
    long length = ftell(file);
    // Move the file pointer back to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content plus a null terminator
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        // Print error message if memory allocation fails
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    // Read the file content into the buffer
    fread(buffer, 1, length, file);
    // Null-terminate the buffer
    buffer[length] = '\0';

    // Close the file
    fclose(file);
    return buffer;
}

// Function to compile a shader from source
GLuint compileShader(GLenum shaderType, const char* source) {
    // Create a shader object
    GLuint shader = glCreateShader(shaderType);
    // Set the source code of the shader
    glShaderSource(shader, 1, &source, NULL);
    // Compile the shader
    glCompileShader(shader);

    // Check if the shader compilation was successful
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        // Print error message if shader compilation fails
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "Error: Shader Compilation Failed\n%s\n", infoLog);
        return 0;
    }
    return shader;
}

// Function to load, compile, and link shaders into a program
GLuint loadShader(const char* vertexPath, const char* fragmentPath) {
    // Read the vertex shader source code from file
    char* vertexSource = readShaderSource(vertexPath);
    if (!vertexSource) {
        return 0;
    }

    // Read the fragment shader source code from file
    char* fragmentSource = readShaderSource(fragmentPath);
    if (!fragmentSource) {
        free(vertexSource); // Free the vertex source if fragment source fails
        return 0;
    }

    // Compile the vertex shader
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    // Compile the fragment shader
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Free the source code buffers as they are no longer needed
    free(vertexSource);
    free(fragmentSource);

    // Check if either shader compilation failed
    if (!vertexShader || !fragmentShader) {
        return 0;
    }

    // Create a shader program
    GLuint shaderProgram = glCreateProgram();
    // Attach the vertex shader to the program
    glAttachShader(shaderProgram, vertexShader);
    // Attach the fragment shader to the program
    glAttachShader(shaderProgram, fragmentShader);
    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check if the shader program linking was successful
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        // Print error message if shader program linking fails
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Error: Shader Program Linking Failed\n%s\n", infoLog);
        return 0;
    }

    // Delete the shader objects as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
