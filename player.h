#pragma once

class Player {
public:
	void update();

	int getScore();
	void setScore(int s);

	int getHealth();
	void setHealth(int h);

	void increaseScore(int s);
	void decreaseHealth(int h);

private:
	int score = 0;
	int health = 3;
};