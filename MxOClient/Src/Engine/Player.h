#pragma once
class Player
{
private:
	int m_health;
	int m_kills;
	int m_dmg;

public:
	static Player player;

	static Player& CreatePlayer();

	int GetHealth();

	int GetKills();

	void SetHealth(int health);

	void SetKills(int kills);

	void SetDamage(int dmg);

	int GetDamage();
};