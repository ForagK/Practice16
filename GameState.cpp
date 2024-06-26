#include "GameState.h"
#include <SFML/Graphics.hpp>
void GameState::InitStats()
{
	points = 0;
	healthMax = 20;
	health = healthMax;
	spawnTimer = 0.f;
	spawnTimerMax = 50.f;
	spawnTimerCurrent = spawnTimerMax;
	gameOver = false;
}
void GameState::InitTextures()
{
	textures["bullet"] = new sf::Texture();
	textures["bullet"]->loadFromFile("Resources/Bullet.png");
	
	textures["playerIdle"] = new sf::Texture();
	textures["playerIdle"]->loadFromFile("Resources/Player.png");

	textures["background"] = new sf::Texture();
	textures["background"]->loadFromFile("Resources/SpaceBackground.png");

	textures["enemySmall"] = new sf::Texture();
	textures["enemySmall"]->loadFromFile("Resources/EnemySmall.png");

	textures["enemyMed"] = new sf::Texture();
	textures["enemyMed"]->loadFromFile("Resources/EnemyMed.png");

	textures["hpBarBorder"] = new sf::Texture();
	textures["hpBarBorder"]->loadFromFile("Resources/HpBarBorder.png");

	textures["hpBar"] = new sf::Texture();
	textures["hpBar"]->loadFromFile("Resources/HpBar.png");
}
void GameState::InitPlayer()
{
	player = new Player(window->getSize().x/2.f, window->getSize().y / 2.f, textures["playerIdle"],500.f);
}
void GameState::InitEnemy()
{
	if (rand() % 10 == 9)
		enemies.push_back(enemy = new Enemy(rand() % static_cast<int>(window->getSize().x - borderRight.getSize().x * 2 - 60) + borderLeft.getSize().x + 30,
			-200, textures["enemyMed"], 100, 5, 5, 10));
	else
		enemies.push_back(enemy = new Enemy(rand() % static_cast<int>(window->getSize().x - borderRight.getSize().x * 2 - 60) + borderLeft.getSize().x + 30,
			-200, textures["enemySmall"], 200, 1, 1, 5));
}
void GameState::InitGui()
{
	pointText.setFont(font);
	pointText.setCharacterSize(70);
	pointText.setFillColor(sf::Color(41, 158, 162, 255));
	pointText.setPosition(sf::Vector2f(20, 20));

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color(255, 255, 255, 255));
	gameOverText.setString("Game Over");
	gameOverText.setPosition(sf::Vector2f(window->getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
		window->getSize().y / 2 - gameOverText.getGlobalBounds().height * 4));

	borderLeft.setSize(sf::Vector2f(window->getSize().x / 4, window->getSize().y));
	borderLeft.setFillColor(sf::Color(0, 0, 0, 150));

	borderRight.setSize(sf::Vector2f(window->getSize().x / 4, window->getSize().y));
	borderRight.setFillColor(sf::Color(0, 0, 0, 150));
	borderRight.setPosition(sf::Vector2f(window->getSize().x / 4 * 3, 0));

	hpBarBorder.setTexture(*textures["hpBarBorder"]);
	hpBarBorder.setPosition(sf::Vector2f(40, 50));
	hpBarBorder.setScale(8.f / 1920.f * window->getSize().x, 5.f / 1080.f * window->getSize().y);

	hpBar.setTexture(*textures["hpBar"]);
	hpBar.setPosition(hpBarBorder.getPosition().x + 4 * hpBarBorder.getScale().x, hpBarBorder.getPosition().y + 4 * hpBarBorder.getScale().y);
	hpBar.setScale(hpBarBorder.getScale());
}
void GameState::InitBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	background.setTexture(textures["background"]);
}
void GameState::InitFonts()
{
	font.loadFromFile("Resources/Silver.ttf");
}
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	:State(window, states)
{
	InitStats();
	InitTextures();
	InitBackground();
	InitFonts();
	InitGui();
	InitPlayer();
	InitEnemy();
}

GameState::~GameState()
{
	delete player;
	for (auto &i:textures)
	{
		delete i.second;
	}
	for (auto* i : bullets)
	{
		delete i;
	}
	for (auto* i : enemies)
	{
		delete i;
	}
}

void GameState::ReduceHealth(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
		gameOver = true;
	}
}

void GameState::UpdateInput(const float& deltaTime)
{
	if (!gameOver) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player->Move(deltaTime, -1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player->Move(deltaTime, 0.f, 1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player->Move(deltaTime, 1.f, 0.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player->Move(deltaTime, 0.f, -1.f);
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && player->CanAttack()) {
			bullets.push_back(new Bullet(textures["bullet"], player->GetPos().x, player->GetPos().y, 0.f, -1.f, 500.f));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		EndState();
}

void GameState::UpdateGui()
{
	std::stringstream strStream;
	strStream << "Points: " << points;
	pointText.setString(strStream.str());
	pointText.setPosition(sf::Vector2f(hpBarBorder.getGlobalBounds().left, hpBarBorder.getGlobalBounds().top + hpBarBorder.getGlobalBounds().height + 10));
	hpBar.setScale(hpBarBorder.getScale().x / healthMax * health, hpBarBorder.getScale().y);
}

void GameState::UpdateCollision()
{
	if (player->getBounds().left < borderLeft.getSize().x) {
		player->SetPos(borderLeft.getSize().x + (player->getBounds().width / 2), player->GetPos().y);
	}
	if (player->getBounds().left + player->getBounds().width > window->getSize().x - borderLeft.getSize().x) {
		player->SetPos(window->getSize().x - borderLeft.getSize().x - (player->getBounds().width / 2), player->GetPos().y);
	}
	if (player->getBounds().top < 0.f) {
		player->SetPos(player->GetPos().x, 0.f + (player->getBounds().height / 2));
	}
	if (player->getBounds().top + player->getBounds().height > window->getSize().y) {
		player->SetPos(player->GetPos().x, window->getSize().y - (player->getBounds().height / 2));
	}
}

void GameState::UpdateTimer()
{
	if (spawnTimerMax - points / 5.f > 9)
		spawnTimerCurrent =  spawnTimerMax - points / 5.f;
}

void GameState::UpdateBullets(const float& deltaTime)
{
	unsigned counter = 0;
	for (auto* bullet : bullets) {
		bullet->update(deltaTime);
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}

void GameState::UpdateEnemy(const float& deltaTime)
{
	spawnTimer += 0.5f;
	if (spawnTimer >= spawnTimerCurrent) {
		InitEnemy();
		spawnTimer = 0.f;
	}
	unsigned counter = 0;
	for (auto* enemy : enemies) {
		bool enemyRemoved = 0;
		enemy->Update(deltaTime);
		if (enemy->getBounds().intersects(borderLeft.getGlobalBounds()) || enemy->getBounds().intersects(borderRight.getGlobalBounds())) {
			enemy->SetPos(borderLeft.getSize().x + (enemy->getBounds().width / 2), enemy->GetPos().y);
		}
		for (int i = 0; i < bullets.size() && !enemyRemoved; i++) {
			if (bullets[i]->getBounds().intersects(enemies.at(counter)->getBounds())) {
				bullets.erase(bullets.begin() + i);

				enemy->SetHealth();
				if (enemy->GetHealth() == 0) {
					points += enemy->GetPoints();
					enemies.erase(enemies.begin() + counter);
					enemyRemoved = 1;
				}
			}
		}
		if (!enemyRemoved) {
			if (enemy->getBounds().top - enemy->getBounds().height > window->getSize().y) {
				ReduceHealth(enemy->GetDamage());
				delete enemies.at(counter);
				enemies.erase(enemies.begin() + counter);
				--counter;
				enemyRemoved = 1;
			}
			++counter;
		}
	}
}

void GameState::Update(const float& deltaTime)
{
	UpdateInput(deltaTime);
	if (!gameOver) {
		UpdateMousePos();
		player->Update(deltaTime);
		UpdateEnemy(deltaTime);
		UpdateBullets(deltaTime);
		UpdateCollision();
		UpdateGui();
		UpdateTimer();
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	target->draw(background);
	target->draw(borderLeft);
	target->draw(borderRight);
	target->draw(pointText);
	target->draw(hpBar);
	target->draw(hpBarBorder);
	for (auto* bullet : bullets) {
		bullet->render(target);
	}
	for (auto* enemy : enemies) {
		enemy->Render(*target);
	}
	player->Render(*target);
	if (gameOver) {
		target->draw(gameOverText);
	}
}
