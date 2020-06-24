/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "ResourceManager.h"
#include <iostream>


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
 
// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 800;

Game snake(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    //调用glad管理窗口函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glfwSetKeyCallback(window, key_callback);

    // 窗口设置
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 游戏初始化
    snake.Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    // Start Game within Menu State
    snake.State = GAME_ACTIVE;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //deltaTime = 0.001f;
        // Manage user input
        snake.ProcessInput(deltaTime);

        // Update Game state
        snake.Update(deltaTime);

        // Render
        glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        snake.Render();

        glfwSwapBuffers(window);
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            snake.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE) {
            snake.Keys[key] = GL_FALSE;
            snake.KeysProcessed[key] = GL_FALSE;
        }
    }

}