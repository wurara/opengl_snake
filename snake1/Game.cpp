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




// Game-related State data
SpriteRenderer* spritRender;
std::vector<GameLevel> Levels;

// 初始化挡板的大小
const glm::vec2 PLAYER_SIZE(100, 20);
// 初始化当班的速率
const GLfloat PLAYER_VELOCITY(500.0f);

//玩家对象
GameObject* Player;
//粒子生成器
ParticleGenerator* Particles;
//文本
TextRender* Text;
//音效
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();

std::vector<PowerUp>  PowerUps;

// 初始化球的速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球的半径
const GLfloat BALL_RADIUS = 12.5f;
//球
BallObject* Ball;

//蛇
SnakeObject* snake;

//特效
PostProcessor* Effects;
//晃动时间
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
    //加载着色器
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // 配置着色器
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width),
        static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    //加载纹理
    ResourceManager::LoadTexture("textures/snakeHead.png", GL_TRUE, "snakeHead");
    ResourceManager::LoadTexture("textures/snakeBody.png", GL_TRUE, "snakeBody");
    ResourceManager::LoadTexture("textures/snakeTail.png", GL_TRUE, "snakeTail");
    ResourceManager::LoadTexture("textures/grass.jpg", GL_FALSE, "grass");
    ResourceManager::LoadTexture("textures/sand.jpg", GL_FALSE, "sand");
    //加载配置文件

    //新建render对象
    Shader s = ResourceManager::GetShader("sprite");
    spritRender = new SpriteRenderer(s);

    // 加载关卡
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

    //初始化蛇
    snake = new SnakeObject(Levels[Level].unit_width);
}

void Game::ResetLevel()
{
    if (Level == 0)Levels[0].Load("levels/one.lvl", this->Width, this->Height * 0.5f);
    else if (Level == 1)
        Levels[1].Load("levels/two.lvl", this->Width, this->Height * 0.5f);
    else if (Level == 2)
        Levels[2].Load("levels/three.lvl", this->Width, this->Height * 0.5f);
    else if (Level == 3)
        Levels[3].Load("levels/four.lvl", this->Width, this->Height * 0.5f);

    this->Lives = 3;
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    Player->size = PLAYER_SIZE;
    Player->position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}
//更新逻辑数据
void Game::Update(GLfloat dt)
{
    snake->move();
}


void Game::ProcessInput(GLfloat dt)
{
	Direction snakeDirection;
	if (this->Keys[GLFW_KEY_W]&&Keys[GLFW_KEY_W]==GL_TRUE) {
        snake->changeDirection(UP);
        Keys[GLFW_KEY_W] = GL_FALSE;
	}
	if (this->Keys[GLFW_KEY_S] && Keys[GLFW_KEY_S] == GL_TRUE) {
        snake->changeDirection(DOWN);
        Keys[GLFW_KEY_S] = GL_FALSE;
	}
	if (this->Keys[GLFW_KEY_D] && Keys[GLFW_KEY_D] == GL_TRUE) {
        snake->changeDirection(RIGHT);
        Keys[GLFW_KEY_D] = GL_FALSE;
	}
	if (this->Keys[GLFW_KEY_A] && Keys[GLFW_KEY_A] == GL_TRUE) {
        snake->changeDirection(LEFT);
        Keys[GLFW_KEY_A] = GL_FALSE;
	}

}

void Game::Render()
{
    Levels[Level].Draw(*spritRender);
    snake->Draw(*spritRender);
}

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),  // 上
        glm::vec2(1.0f, 0.0f),  // 右
        glm::vec2(0.0f, -1.0f), // 下
        glm::vec2(-1.0f, 0.0f)  // 左
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


