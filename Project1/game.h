#include <SFML/Graphics.hpp>
#include "entityManager.h"

class Game {

	sf::RenderWindow gameWindow;
	//textures and sprites
	sf::Texture meteorTexture;
	sf::Texture playerTexture;
	sf::Sprite meteorSprite;
	sf::Sprite playerSprite;

	//text 
	sf::Font gameFont;
	sf::Text gameText;

	EntityManager entityMgr;

	std::shared_ptr<Entity> player;
	
	int score = 0;
	//int meteorSize = 0;
	int currentFrame = 0;
	int lastMeteorSpawnedFrame = 0;
	int meteorSpawnInterval = 10;
	float meteorFallSpeed = 2;
	bool gamePaused = false;
	bool gameIsRunning = true;


	void Init();
	void PauseAndResume();
	void SpawnMeteor();
	void SpawnPlayer();
	void SpawnBullet(std::shared_ptr<Entity>, const sf::Vector2f& mousePos);
	void IncreaseMeteorSpeed();
	void UpdateScore(int s);
	void ResetScore();

	//Systems
	void SRender();
	void SInput();
	void SMeteorSpawner();
	void SMovement();
	void SCollision();
	void SMeteorRemover();
	void SLifeSpan();
public:
	Game();
	void Run();

};