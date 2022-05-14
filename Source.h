#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>

using namespace std;

enum Type { animation, feature, documentary };
struct Film 
{
	void* obj = NULL;
	Type key;
	string country = "";
	string name = "";
};

struct Node 
{
	Film* film = NULL;
	Node* next = NULL;
};

struct featureFilm 
{
	string director = "";
};

struct documentaryFilm 
{
	int year = 0;
};

enum Way { DRAWN, DOLL, STOP_MOTION };//way of creation

struct animationFilm 
{
	Way woc;//way of creation
};

struct container 
{
	int size = 0;
	Node* head = NULL;
	Node* curr = NULL;
};

void in(ifstream& ifst, featureFilm& fF);
void out(ofstream& ofst, featureFilm& fF);
void in(ifstream& ifst, animationFilm& aF);
void out(ofstream& ofst, animationFilm& aF);
void in(ifstream& ifst, documentaryFilm& dF);
void out(ofstream& ofst, documentaryFilm& dF);
Film* inFilm(ifstream& ifst);
Film* outFilm(ifstream& ifst);
void clear(container* cont);
void inCont(ifstream& ifst, container* cont);
void outCont(ofstream& ofst, container* cont);

int countVowel(Film& film);

bool cmpVowels(Film* film1, Film* film2);
void sort(container& cont);
void outFeature(ofstream& ofst, container* cont);

bool fileCheck(ifstream& ifst);