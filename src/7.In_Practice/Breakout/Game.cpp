/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "breakout/Game.h"
#include <filesystem>

std::string createShaderPath(std::string fileName)
{
	std::filesystem::path currentFile(__FILE__);
	std::filesystem::path directoryPath = currentFile.remove_filename();
	return directoryPath.concat(fileName).generic_string();
}

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

#include <breakout/ResourceManager.h>
#include <breakout/SpriteRenderer.h>

SpriteRenderer  *Renderer;
GameObject      *Player;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);

Game::~Game()
{

}

void Game::Init()
{
	// Create player
	ResourceManager::LoadTexture("../resources/paddle.png", true, "paddle");
	glm::vec2 playerPos = glm::vec2(
		this->Width / 2.0f - PLAYER_SIZE.x / 2.0f,
		this->Height - PLAYER_SIZE.y
	);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	// load shaders
    ResourceManager::LoadShader(createShaderPath("breakout_sprite.vs").c_str(), createShaderPath("breakout_sprite.fs").c_str(), nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("../resources/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("../resources/background.jpg", false, "background");
	ResourceManager::LoadTexture("../resources/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("../resources/block.png", false, "block");
	ResourceManager::LoadTexture("../resources/block_solid.png", false, "block_solid");
	// Load 
	GameLevel one;
	one.Load("../resources/levels/one.lvl", this->Width, this->Height / 2);

	Levels.push_back(one);
	this->Level = 0;

}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		// move playerboard
		if (this->Keys[GLFW_KEY_A])
		{
			if (Player->Position.x >= 0.0f)
				Player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D])
		{
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		// draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f
		);
		// draw level
		this->Levels[this->Level].Draw(*Renderer);
		Player->Draw(*Renderer);
	}
}