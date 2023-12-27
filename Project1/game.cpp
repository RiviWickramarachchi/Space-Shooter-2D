#include "game.h"
#include <iostream>
#include <cmath>

void Game::SRender()
{
	if (!gameIsRunning)
	{
		gameWindow.close();
	}


	//clear window
	gameWindow.clear();
	gameWindow.draw(gameText);

	for (auto entity : entityMgr.GetEntities("meteor"))
	{
		//set the position of the entity
		//entity->cShape->circle.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);
		entity->cSprite->sprite.setPosition(entity->cTransform->pos.x, entity->cTransform->pos.y);

		//rotate entity sprite
		entity->cSprite->sprite.rotate(entity->cTransform->rotSpeed);

		//entity->cTransform->angle += 1.0f;
		//entity->cShape->circle.setRotation(entity->cTransform->angle);

		//draw entities
		gameWindow.draw(entity->cSprite->sprite);
	}

	//draw bullet entities
	for (auto bullet : entityMgr.GetEntities("bullet"))
	{
		bullet->cShape->circle.setPosition(bullet->cTransform->pos.x, bullet->cTransform->pos.y);
		gameWindow.draw(bullet->cShape->circle);
	}


	//draw the player entity
	player->cSprite->sprite.setPosition(player->cTransform->pos.x, player->cTransform->pos.y);
	gameWindow.draw(player->cSprite->sprite);


	//display objects on game window
	gameWindow.display();
}

void Game::SInput()
{
	sf::Event event;
	while (gameWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			gameIsRunning = false;
		}
		
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			gameWindow.setView(sf::View(visibleArea));
		}

		//user input logic for movement
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				//W Pressed is true
				std::cout << " W Key is Pressed \n";
				player->cInput->up = true;
				break;
			case sf::Keyboard::S:
				//S key is pressed
				std::cout << " S Key is Pressed \n";
				player->cInput->down = true;
				break;
			case sf::Keyboard::A:
				//A is pressed
				std::cout << " A Key is Pressed \n";
				player->cInput->left = true;
				break;
			case sf::Keyboard::D:
				//D is pressed
				std::cout << " D Key is Pressed \n";
				player->cInput->right = true;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				//W Pressed is false
				player->cInput->up = false;
				break;
			case sf::Keyboard::S:
				//S key is released
				player->cInput->down = false;
				break;
			case sf::Keyboard::A:
				//A is released
				player->cInput->left = false;
				break;
			case sf::Keyboard::D:
				//D is released
				player->cInput->right = false;
				break;
			default:
				break;
			}
		}

		//bullet spawning when mouse is clicked
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (!gamePaused)
				{
					SpawnBullet(player, sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}

			}
		}
	}
}

void Game::SMovement()
{
	player->cTransform->velocity = { 0,0 };
	//up down
	if (player->cInput->up)
	{
		player->cTransform->velocity.y = -5.0f;
	}
	if (player->cInput->down)
	{
		player->cTransform->velocity.y = 5.0f;
	}

	//left right
	if (player->cInput->left)
	{
		player->cTransform->velocity.x = -5.0f;
	}
	if (player->cInput->right)
	{
		player->cTransform->velocity.x = 5.0f;
	}

	//managing entity movement
	EntityVector entities = entityMgr.GetEntities();
	for (auto entity : entities)
	{
		if (entity->IsMovable())
		{
			entity->cTransform->pos.x += entity->cTransform->velocity.x;
			entity->cTransform->pos.y += entity->cTransform->velocity.y;
		}
	}
	
}

void Game::SCollision()
{
	EntityVector meteorEntities = entityMgr.GetEntities("meteor");
	EntityVector bulletEntities = entityMgr.GetEntities("bullet");

	for (auto meteor : meteorEntities)
	{
		float playerMeteorDistanceX = std::pow(player->cTransform->pos.x - meteor->cTransform->pos.x, 2);
		float playerMeteorDistanceY = std::pow(player->cTransform->pos.y - meteor->cTransform->pos.y, 2);
		float distanceBetweenPlayerAndMeteor = std::sqrt(playerMeteorDistanceX + playerMeteorDistanceY);
		float sumOfRadiuses = player->cCollision->collisionRadius + meteor->cCollision->collisionRadius;

		if (sumOfRadiuses >= distanceBetweenPlayerAndMeteor)
		{
			ResetScore();
			meteor->Destroy();
			player->Destroy();
			SpawnPlayer();
			continue;
		}

		//checking bullet and meteor collisions
		for (auto bullet : bulletEntities)
		{
			float bulletMeteorDistanceX = std::pow(bullet->cTransform->pos.x - meteor->cTransform->pos.x, 2);
			float bulletMeteorDistanceY = std::pow(bullet->cTransform->pos.y - meteor->cTransform->pos.y, 2);
			float distanceBetweenBulletAndMeteor = std::sqrt(bulletMeteorDistanceX + bulletMeteorDistanceY);
			float sumOfRadiuses = bullet->cShape->circle.getRadius() + meteor->cCollision->collisionRadius;

			if (sumOfRadiuses >= distanceBetweenBulletAndMeteor)
			{
				UpdateScore(meteor->cPoints->points);
				bullet->Destroy();
				meteor->Destroy();
				continue;
			}
		}

	}
}

void Game::SMeteorRemover()
{
	EntityVector meteorEntities = entityMgr.GetEntities("meteor");
	for (auto entity : meteorEntities)
	{
		if (entity->IsAlive())
		{
			if (entity->cTransform->pos.y > gameWindow.getSize().y + entity->cCollision->collisionRadius)
			{
				entity->Destroy();
			}
		}
	}
}

void Game::SLifeSpan()
{
	//check lifespan of entities with one and destroy them when time runs out
	for (auto entity : entityMgr.GetEntities("bullet"))
	{
		if (entity->cLifespan->remaining > 0)
		{
			entity->cLifespan->remaining--;
		}
		else
		{
			entity->Destroy();
		}

	}
}

Game::Game()
{
	Init();
}

void Game::Init()
{
	gameWindow.create(sf::VideoMode(1280, 720), "SFML GAME");
	gameWindow.setFramerateLimit(60);
	if (!meteorTexture.loadFromFile("D:/C++ Projects/SFML_MiniGame/SpaceShooter/Res/Sprites/ROCK.png"))
	{
		std::cout << "Meteor Texture didnt load properly \n";
	}
	if (!playerTexture.loadFromFile("D:/C++ Projects/SFML_MiniGame/SpaceShooter/Res/Sprites/PLAYER.png"))
	{
		std::cout << "Player Texture didnt load properly \n";
	}
	meteorSprite.setTexture(meteorTexture);
	playerSprite.setTexture(playerTexture);
	
	if (!gameFont.loadFromFile("D:/C++ Projects/SFML_MiniGame/SpaceShooter/Res/Fonts/Abaddon Bold.ttf"))
	{
		std::cout << "Game font didnt load properly \n";
	}
	else
	{
		gameText.setFont(gameFont);
		gameText.setFillColor(sf::Color::White);
		gameText.setCharacterSize(75);
		gameText.setString(std::to_string(score));
	}

	SpawnPlayer();
}

void Game::PauseAndResume()
{
}

void Game::SpawnMeteor()
{
	//creating and adding sprite,collision and health components to the meteor entity
	auto meteorEntity = entityMgr.AddEntity("meteor", true);
	meteorEntity->cSprite = std::make_shared<CSprite>(sf::Vector2f(1, 1), meteorSprite);
	meteorEntity->cCollision = std::make_shared<CCollision>(meteorEntity->cSprite->sprite.getTexture()->getSize().x * 0.5f);
	meteorEntity->cHealth = std::make_shared<CHealth>(100.0f);
	meteorEntity->cPoints = std::make_shared<CPoints>(100);
	//creating spawning position for the entity
	float meteorRadius = meteorEntity->cCollision->collisionRadius;
	int widthRange = 1 + (gameWindow.getSize().x - meteorRadius) - meteorRadius;
	float ey = -5.0f; //since the meteors should spawn without the user being able to see
	float ex = meteorRadius + (rand() % widthRange);
	
	//adding transform component
	meteorEntity->cTransform = std::make_shared<CTransform>(sf::Vector2f(ex,ey), sf::Vector2f(0.0f, meteorFallSpeed), 2.0f);
}

void Game::SpawnPlayer()
{
	auto playerEntity = entityMgr.AddEntity("player",true);
	float centreX = gameWindow.getSize().x / 2.0f;
	float centreY = gameWindow.getSize().y / 2.0f;
	playerEntity->cTransform = std::make_shared<CTransform>(sf::Vector2f(centreX, centreY), sf::Vector2f(0.0f, 0.0f), 0.0f);
	playerEntity->cSprite = std::make_shared<CSprite>(sf::Vector2f(2,2),playerSprite);
	playerEntity->cCollision = std::make_shared<CCollision>(playerEntity->cSprite->sprite.getTexture()->getSize().x * 0.5f);
	playerEntity->cInput = std::make_shared<CInput>();
	player = playerEntity;
}

void Game::SpawnBullet(std::shared_ptr<Entity> entity, const sf::Vector2f& mousePos)
{
	//bullet radius and speed
	float bulletRadius = 2.0f;
	float speed = 8.0f;

	float bulletDamage = 10.0f;

	//bullet lifespan 
	int bulletLifeSpan = 80;
	
	auto bulletEntity = entityMgr.AddEntity("bullet", true);

	sf::Vector2f bulletVelocityVec = sf::Vector2f(0, -1) * speed;
	
	bulletEntity->cTransform = std::make_shared<CTransform>(sf::Vector2f(entity->cTransform->pos.x, entity->cTransform->pos.y), bulletVelocityVec, 0.0f);
	bulletEntity->cShape = std::make_shared<CShape>(bulletRadius, 100, sf::Color(255, 255, 255), sf::Color(255, 255, 255), 1.0f);
	bulletEntity->cDamage = std::make_shared<CDamage>(bulletDamage);
	bulletEntity->cLifespan = std::make_shared<CLifespan>(bulletLifeSpan);
}



void Game::IncreaseMeteorSpeed()
{
	meteorFallSpeed += 0.25f;
}

void Game::UpdateScore(int s)
{
	score += s;
	gameText.setString(std::to_string(score));
}

void Game::ResetScore()
{
	score = 0;
	gameText.setString(std::to_string(score));
}

void Game::SMeteorSpawner()
{
	if (currentFrame - lastMeteorSpawnedFrame >= meteorSpawnInterval)
	{
		//spawn meteor
		SpawnMeteor();
		lastMeteorSpawnedFrame = currentFrame;
	}
}



void Game::Run()
{
	while (gameIsRunning)
	{
		entityMgr.Update();

		SInput();
		SRender();
		SMeteorSpawner();
		SCollision();
		SMovement();
		SMeteorRemover();
		SLifeSpan();
		currentFrame++;
	}
	
}
