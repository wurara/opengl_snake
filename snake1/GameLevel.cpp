/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameLevel.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // �����������
    this->Bricks.clear();
    // ���ظ�ʽ�ļ�
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // ��ȡ�ļ���ÿһ��
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // �Կո�����ȡÿһ����
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : this->Bricks)
        if (!tile.destroyed)
            tile.Draw(renderer);
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData[0].size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    units = static_cast<float>(width);
    unit_width = levelWidth / static_cast<float>(width);
    unit_height = levelHeight / static_cast<float>(height);
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // �����1�������������Ϊ��
            if (tileData[y][x] == 1) // solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("grass"), glm::vec3(1.0f, 1.0f, 1.0f));
                this->Bricks.push_back(obj);
            }            
            // �����1�������������Ϊɳ
            else if (tileData[y][x] == 2)
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("sand"), glm::vec3(1.0f, 1.0f, 1.0f));
                this->Bricks.push_back(obj);
            }
        }
    }
}