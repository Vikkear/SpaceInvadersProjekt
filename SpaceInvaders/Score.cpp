#include "Score.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Score::Score() {
	scores = new int[10];
	names = new string[10];
}

Score::~Score() {
	delete[] scores;
	delete[] names;
}

void Score::addToCurrentScore(int toAdd) {
	currentScore += toAdd;
}

// Kollar om man har fått ett highscore. Stämmer detta så ska man fylla i ett namn

void Score::checkIfHighscore() {
	bool isScoreAdded = false;

	for (int i = 0; i < 10 && !isScoreAdded; i++) {
		if (currentScore > scores[i]) {
			
			cout << endl << endl << endl << "New Highscore!!! What's your name? ";
			string nameToEnter;
			cin >> nameToEnter;

			// Flyttar alla lägre poäng ner ett steg
			for (int j = 9; j > i; j--) {
				names[j] = names[j - 1];
				scores[j] = scores[j - 1];
			}

			scores[i] = currentScore;
			names[i] = nameToEnter;
			
			isScoreAdded = true;
		}

	}
	cout << "Printar Highscores:" << endl;

	for (int i = 0; i < 10; i++) {
		cout << "Namn: " << names[i] << " Score: " << to_string(scores[i]) << endl;
	}

}


int Score::getScore() const{
	return currentScore;
}

void Score::loadScoreFromFile() {
	ifstream inFile;
	inFile.open("Highscores.txt");

	if (inFile.is_open()) {
		for (int i = 0; i < 10; i++) {
			inFile >> names[i];
			inFile >> scores[i];
		}
	}

	inFile.close();
}

void Score::saveScoreToFile() {
	ofstream outFile;
	outFile.open("Highscores.txt");

	if (outFile.is_open()) {
		for (int i = 0; i < 10; i++) {
			outFile << names[i] << endl << to_string(scores[i]) << endl;
		}

	}

	outFile.close();
}

