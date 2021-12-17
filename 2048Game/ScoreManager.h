#pragma once
#include "SingletonBase.h"

class ScoreManager : public SingletonBase<ScoreManager>
{
private:
public:
	ScoreManager() {}
	~ScoreManager() {}

	void saveData(string fileName, int data[18]);
	BOOLEAN loadData(string fileName, int data[18]);

	int readString(HANDLE file, char str[]);
};

