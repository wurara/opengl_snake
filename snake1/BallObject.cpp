/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "BallObject.h"

BallObject::BallObject()
    : GameObject(), radius(12.5f), stuck(true) { }

BallObject::BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), radius(radius), stuck(true) {
    sticky = GL_FALSE;
    passThrough = GL_FALSE;
}

glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width)
{
    // If not stuck to player board
    if (!this->stuck)
    {
        // Move the ball
        this->position += this->velocity * dt;
        // Then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->position.x <= 0.0f)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = 0.0f;
        }
        else if (this->position.x + this->size.x >= window_width)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = window_width - this->size.x;
        }
        if (this->position.y <= 0.0f)
        {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
    }
    return this->position;
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
    this->sticky = GL_FALSE;
    this->passThrough = GL_FALSE;
    this->color = glm::vec3(1.0f, 1.0f, 1.0f);
}