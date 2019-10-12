#pragma once
#include <string>


using namespace std;

class Score {
private:
	int currentScore = 0;
	int *scores;
	string *names;

public:
	Score();
	~Score();

	void addToCurrentScore(int toAdd);
	void checkIfHighscore();
	int getScore() const;
	void loadScoreFromFile();
	void saveScoreToFile();

};