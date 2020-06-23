/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>

#include "texture.h"
#include "SpriteRender.h"

#define PI 3.1415926

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // Object state
    glm::vec2   position, size, velocity;
    glm::vec3   color;
    GLfloat     rotation,direction;
    int changPointCount;
    GLboolean   throughable;
    GLboolean   destroyed;
    // Render state
    Texture2D   texture;
    // Constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(1.0f, 0.0f));
    // Draw sprite
    virtual void Draw(SpriteRenderer& renderer);
    void setTexture(Texture2D texture);
};

#endif