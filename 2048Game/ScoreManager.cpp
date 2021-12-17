#include "stdafx.h"
#include "ScoreManager.h"

void ScoreManager::saveData(string fileName, int data[18])
{
	HANDLE file;
	DWORD write;
	file = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (int i = 0; i < 18; i++) 
	{
		string str = to_string(data[i]).c_str();
		for (int j = 0; j < str.length(); j++) 
		{
			str[j] += (j + 1) * (i + 1);
;		}
		str += "\n"
;		WriteFile(file, str.c_str(), str.size(), &write, NULL);
	}
	CloseHandle(file);
}

BOOLEAN ScoreManager::loadData(string fileName, int data[18])
{
	HANDLE file;
	LPDWORD lpFileSizeHigh = NULL;
	DWORD fileSize = 0;
	char str[128];
	file = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		fileSize = GetFileSize(file, lpFileSizeHigh);
		if (fileSize != 0) {
			int lngth;
			for (int i = 0; i < 18; i++) {
				lngth = readString(file, str);
				if (lngth <= 0 && i < 18) 
				{
					CloseHandle(file);
					return false;
				}
				for (int j = 0; j < lngth; j++)
				{
					str[j] -= (j + 1) * (i + 1);
				}
				data[i] = stoi(str);
				fill(begin(str), end(str), 0);
			}
			CloseHandle(file);
			return true;
		}
		else 
		{ 
			CloseHandle(file);
			return false; 
		}
	}
	else return false;
}

int ScoreManager::readString(HANDLE file, char str[])
{
	DWORD read;
	char chr[1];
	int length = 0;
	do {
		ReadFile(file, chr, 1, &read, NULL);
		if (read != 0) {
			if (chr[0] != '\r' || chr[0] != '\n') {
				str[length] = chr[0];
				length++;
			}
		}
		else
			break;
	} while (chr[0] != '\r' && chr[0] != '\n');
	return length;
}
