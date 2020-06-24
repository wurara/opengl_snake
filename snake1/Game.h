/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<tuple>
#include <glm/glm/glm.hpp>
#include "PowerUp.h"


// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};
 


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // ��Ϸ����
    GameState              State;
    GLboolean              Keys[1024];
    unsigned int           Width, Height;
    GLuint                 Lives;
    GLboolean              KeysProcessed[1024];
    GLuint                 Level;



    // ���캯��
    Game(GLuint width, GLuint height);
    ~Game();
    // ��ʼ���������������еĹؿ�������ɫ����
    void Init();
    void ResetLevel();
    void ResetPlayer();
    // ��Ϸѭ��
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    void checkFoodEatten();
};

#endif