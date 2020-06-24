/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "ResourceManager.h"
#include "SpriteRender.h"
#include <vector>

#include <irrKlang/irrKlang.h>

#include "GameLevel.h"
#include "BallObject.h"
#include "ParticleGenerator.h"
#include "PostProcessor.h"
#include "TextRender.h"
#include "SnakeObject.h"
#include "Foods.h"




// Game-related State data
SpriteRenderer* spritRender;
std::vector<GameLevel> Levels;

// ��ʼ������Ĵ�С
const glm::vec2 PLAYER_SIZE(100, 20);
// ��ʼ�����������
const GLfloat PLAYER_VELOCITY(500.0f);

//����������
ParticleGenerator* Particles;
//�ı�
TextRender* Text;
//��Ч
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();

std::vector<PowerUp>  PowerUps;

// ��ʼ������ٶ�
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// ��İ뾶
const GLfloat BALL_RADIUS = 12.5f;
//��
BallObject* Ball;

//��
SnakeObject* snake;
//ʳ��
Foods foods;

//��Ч
PostProcessor* Effects;
//�ζ�ʱ��
GLfloat ShakeTime = 0.0f;

// powerups
bool IsOtherPowerUpActive(std::vector<PowerUp>& powerUps, std::string type);


Game::Game(GLuint width, GLuint height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
}

void Game::Init()
{
    //������ɫ��
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // ������ɫ��
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    //��������
    ResourceManager::LoadTexture("textures/snakeHead.png", GL_TRUE, "snakeHead");
    ResourceManager::LoadTexture("textures/snakeBody.png", GL_TRUE, "snakeBody");
    ResourceManager::LoadTexture("textures/snakeTail.png", GL_TRUE, "snakeTail");
    ResourceManager::LoadTexture("textures/apple.png", GL_TRUE, "apple");
    ResourceManager::LoadTexture("textures/grass.jpg", GL_FALSE, "grass");
    ResourceManager::LoadTexture("textures/sand.jpg", GL_FALSE, "sand");

    //���������ļ�

    //�½�render����
    Shader s = ResourceManager::GetShader("sprite");
    spritRender = new SpriteRenderer(s);

    // ���عؿ�
    GameLevel one;
    one.Load("levels/one.lvl", this->Width, this->Height);
    GameLevel two;
    two.Load("levels/two.lvl", this->Width, this->Height);
    GameLevel three;
    three.Load("levels/three.lvl", this->Width, this->Height);
    GameLevel four;
    four.Load("levels/four.lvl", this->Width, this->Height);
    Levels.push_back(one);
    Levels.push_back(two);
    Levels.push_back(three);
    Levels.push_back(four);
    Level = 0;

    //��ʼ����
    snake = new SnakeObject(Levels[Level].unit_width);
    //���ɵ�һ��ʳ��
    foods.generate(Levels[Level].units, Levels[Level].unit_height);

    SoundEngine->play2D("audio/bgm.mp3",true);
}

void Game::ResetLevel()
{
}

void Game::ResetPlayer()
{
}
//�����߼�����
void Game::Update(GLfloat dt)
{
    snake->move(this->Width);
    checkFoodEatten();
}


void Game::ProcessInput(GLfloat dt)
{
    
	if (this->Keys[GLFW_KEY_W]) {
        snake->changeDirection(UP, dt);
	}
	else if (this->Keys[GLFW_KEY_S]) {
        snake->changeDirection(DOWN, dt);
	}
	else if (this->Keys[GLFW_KEY_D]) {
        snake->changeDirection(RIGHT, dt);
	}
	else if (this->Keys[GLFW_KEY_A]) {
        snake->changeDirection(LEFT, dt);
	}
    else if (this->Keys[GLFW_KEY_SPACE]) {
        snake->grow();
        this->Keys[GLFW_KEY_SPACE] = false;
    }
}

void Game::Render()
{
    Levels[Level].Draw(*spritRender);
    snake->draw(*spritRender);
    foods.draw(*spritRender);
}



Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // ��
        glm::vec2(1.0f, 0.0f),  // ��
        glm::vec2(0.0f, -1.0f), // ��
        glm::vec2(-1.0f, 0.0f)  // ��
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

void Game::checkFoodEatten()
{
    glm::vec2 mousePosition = snake->snake[0].position + glm::vec2(Levels[Level].unit_height, Levels[Level].unit_height / 2);
    
    for (int i = 0; i < foods.foods.size();i++) {
        glm::vec2 foodPosition = foods.foods[i].position + glm::vec2(Levels[Level].unit_height, Levels[Level].unit_height);
        if (mousePosition.x > foods.foods[i].position.x && mousePosition.y > foods.foods[i].position.y
            && mousePosition.x < foodPosition.x && mousePosition.y < foodPosition.y) {
            foods.foods[i].destroyed = GL_TRUE;
            snake->grow();
            SoundEngine->play2D("audio/eat.mp3",false);
            foods.generate(Levels[Level].units, Levels[Level].unit_height);
        }
    }
}

