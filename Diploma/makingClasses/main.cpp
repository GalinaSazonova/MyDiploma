#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include "adaptiveClass.h"
#include <ctime>
using namespace std;

int findKap(int q, int *a)
{
	int i = 0;
	while (q != 7)
	{
		if (q > a[i] && q < a[i + 1])
		{
			return i;
		}
		i++;
	}
	return -1;
}

void flowtry()
{
	int a[7] = {10,13,17,21,34,30};
	int ai[7] = { 0, 2, 3, 6, 7, 9 };
	double b[10];
	int c[10] = { 10, 12, 13, 17, 20, 21, 22, 34, 32, 30 };
	int i = 0;
	int j = 0;
	while (i != 10)
	{
		if (i == ai[j])
		{
			b[i] = 0;
			i++;
			j++;
			continue;
		}
		int q = findKap(i, ai);
		b[i] = c[i] - 1 / (double)(ai[q + 1] - ai[q]) * ((ai[q + 1] - i)*c[q] + (i - ai[q])*c[q + 1]);
		i++;
	}
	cout << "--------" << endl;
	for (int k = 0; k < 10; k++)
	{
		cout << b[k] << endl;
	}
}

int main(int argc, char* argv[])
{
	const char* filePath;
	string input;
	if (argc <= 1)
	{
		cout << "Input wave file name: ";
		cin >> input;
		cin.get();
		filePath = input.c_str();
	}
	else
	{
		filePath = argv[1];
		cout << "Input wave file name: " << filePath << endl;
	}

	adaptiveNet adn(filePath);
	
	adn.buildGrid();
	adn.restoreFlow();
	adn.saveResInWav("adn.wav");
	adn.saveNet("smth.txt");
	//adn.printEpsMax();
	adn.printEps();
	adn.buildWaveFlow();
	adn.restoreByWaveFlow();
	adn.saveResInWav2("adnwave.wav");
	adn.compareres();

	return 0;
}