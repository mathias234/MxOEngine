#include "Player.h"
Player Player::player;


Player& Player::CreatePlayer()
{
	player = Player();

	return player;
}

int Player::GetHealth()
{
	return m_health;
}

int Player::GetKills()
{
	return m_kills;
}

void Player::SetHealth(int health)
{
	m_health = health;
}

void Player::SetKills(int kills)
{
	m_kills = kills;
}

int Player::GetDamage()
{
	return m_dmg;
}

void Player::SetDamage(int dmg)
{
	m_dmg = dmg;
}
