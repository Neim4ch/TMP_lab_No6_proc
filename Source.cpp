#include "Source.h"
using namespace std;

string VOWELS = "aeiouyAEIOUY";
string DIGITS = "0123456789";

void in(ifstream& ifst, featureFilm& fF) 
{ 
	ifst >> fF.director;
}

void out(ofstream& ofst, featureFilm& fF) 
{
	ofst << "It is feature film. Director is " << fF.director << endl;
}

void in(ifstream& ifst, documentaryFilm& dF) 
{
	ifst >> dF.year;
}

void out(ofstream& ofst, documentaryFilm& dF) 
{
	ofst << "It is documentary film. It's year of creation is " << dF.year << endl;
}

void in(ifstream& ifst, animationFilm& aF) 
{
	int wocType;
	ifst >> wocType;
	switch (wocType)
	{
	case 1:
		aF.woc = DRAWN;
		break;
	case 2:
		aF.woc = DOLL;
		break;
	case 3:
		aF.woc = STOP_MOTION;
		break;
	}
}

void out(ofstream& ofst, animationFilm& aF) 
{
	switch (aF.woc)
	{
	case 0:
		ofst << "It is animation film. It's way of creation is drawing." << endl;
		break;
	case 1:
		ofst << "It is animation film. It's way of creation is using dolls" << endl;
		break;
	case 2:
		ofst << "It is animation film. It's way of creation is stop motion" << endl;
		break;
	}
}

Film* inFilm(ifstream& ifst) 
{
	Film* film = new Film;
	featureFilm* fF;
	animationFilm* aF;
	documentaryFilm* dF;
	int typeOfFilm = 0;
	
	ifst >> typeOfFilm;
	ifst >> film->name;
	
	switch (typeOfFilm) 
	{
	case 1:
		film->key = feature;
		fF = new featureFilm;
		in(ifst, *fF);
		film->obj = (void*)fF;
		break;
	case 2:
		film->key = animation;
		aF = new animationFilm;
		in(ifst, *aF);
		film->obj = (void*)aF;
		break;
	case 3:
		film->key = documentary;
		dF = new documentaryFilm;
		in(ifst, *dF);
		film->obj = (void*)dF;
		break;
	default:
		return 0;
	}

	ifst >> film->country;

	return film;
}

void outFilm(ofstream& ofst, Film& film) 
{
	ofst << "This is \"" << film.name << "\". ";
	if (film.key == feature)
	{
		featureFilm* fF;
		fF = (featureFilm*)(film.obj);
		out(ofst, *fF);
	}
	if (film.key == animation)
	{
		animationFilm* aF;
		aF = (animationFilm*)film.obj;
		out(ofst, *aF);
	}
	if (film.key == documentary)
	{
		documentaryFilm* dF;
		dF = (documentaryFilm*)film.obj;
		out(ofst, *dF);
	}
	ofst << "Number of vowels = " << countVowel(film) << endl;
	ofst << "The picture was filmed in " << film.country << ".\n";
}

void clear(container* cont) 
{
	cont->head = NULL;
	cont->curr = NULL;
	cont->size = 0;
}

void inCont(ifstream& ifst, container* cont) 
{
	while (!ifst.eof()) 
	{
		Node* newNode = new Node;
		newNode->film = inFilm(ifst);
		if (cont->head == NULL)
		{
			cont->head = newNode;
			cont->size = 1;
		}
		else
		{
			cont->curr = cont->head;
			while (cont->curr->next != NULL)
			{
				cont->curr = cont->curr->next;
			}
			cont->curr->next = newNode;
			cont->size++;
		}
	}
}

void outCont(ofstream& ofst, container* cont) 
{
	int i = 0;

	ofst << "Container contents " << cont->size << " elements." << endl;

	cont->curr = cont->head;
	while (cont->curr != NULL)
	{
		ofst << i << ": ";
		outFilm(ofst, *(cont->curr->film));
		cont->curr = cont->curr->next;
		i++;
	}
}


int countVowel(Film& film)
{
	int cnt = 0;
	for (int i = 0; i < film.name.length(); i++)
	{
		if (VOWELS.find(film.name[i]) < VOWELS.length())cnt++;
	}
	return cnt;
}

bool cmpVowels(Node* node1, Node* node2)
{
	return countVowel(*node1->film) < countVowel(*node2->film);
}

void sort(container& cont)
{
	Node* curri = cont.head;
	Node* currj = cont.head;
	while (curri != NULL)
	{
		currj = curri->next;
		while (currj != NULL) {
			if (cmpVowels(curri, currj))
			{
				swap(curri->film, currj->film);
			}
			currj = currj->next;
		}
		curri = curri->next;
	}
}

void outFeature(ofstream& ofst, container* cont)
{
	ofst << "Only feature films." << endl;
	cont->curr = cont->head;
	int i = 0;
	while (cont->curr != NULL)
	{
		ofst << i << ": ";
		if (cont->curr->film->key == feature)
		{
			outFilm(ofst, *cont->curr->film);
		}
		else
			ofst << endl;
		i++;
		cont->curr = cont->curr->next;
	}
}

bool fileCheck(ifstream& ifst)
{
	char lineC[100];
	string lineCPP;


	if (!ifst.is_open())
	{
		cout << "Input file was not found.";
		exit(1);
	}

	int cnt = 1;
	while (!ifst.eof())
	{
		ifst.getline(lineC, 100, '\n');//type check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The type is a blank string.\n";
			exit(1);
		}
		for (int i = 0; i < lineCPP.length(); i++)
		{
			if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
			{
				cout << cnt << " film: Type definition contains incorrect characters.\n";
				exit(1);
			}
		}
		int typeOfFilm = std::stoi(lineCPP);
		if (typeOfFilm <= 0 || typeOfFilm > 3)
		{
			cout << cnt << " film: Type is out of range.\n";
			exit(1);
		}

		ifst.getline(lineC, 100, '\n');//name check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The name of the film is a blank string.\n";
			exit(1);
		}

		switch (typeOfFilm)//type's pole check
		{
			int typeOfCreation;
		case 1:
			ifst.getline(lineC, 100, '\n');//director's name check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The director's name of the film is a blank string.\n";
				exit(1);
			}
			break;
		case 2:
			ifst.getline(lineC, 100, '\n');//way of creation check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The way of creation of the film is a blank string.\n";
				exit(1);
			}
			for (int i = 0; i < lineCPP.length(); i++)
			{
				if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
				{
					cout << cnt << " film: The way of creation contains incorrect characters.\n";
					exit(1);
				}
			}
			typeOfCreation = std::stoi(lineCPP);
			if (typeOfCreation <= 0 || typeOfCreation > 3)
			{
				cout << cnt << " film: Way of creation is out of range.\n";
				exit(1);
			}
			break;
		case 3:
			ifst.getline(lineC, 100, '\n');//year check
			lineCPP = lineC;
			if (lineCPP == "")
			{
				cout << cnt << " film: The year of creation of the film is a blank string.\n";
				exit(1);
			}
			for (int i = 0; i < lineCPP.length(); i++)
			{
				if (!(DIGITS.find(lineCPP[i]) < DIGITS.length()))
				{
					cout << cnt << " film: The year of creation contains incorrect characters.\n";
					exit(1);
				}
			}
			int year = std::stoi(lineCPP);
			if (year <= 0 || year > 2022)
			{
				cout << cnt << " film: The year of creation is out of range.\n";
				exit(1);
			}
			break;
		}

		ifst.getline(lineC, 100, '\n'); //country check
		lineCPP = lineC;
		if (lineCPP == "")
		{
			cout << cnt << " film: The film's country is a blank string.\n";
			exit(1);
		}

		cnt++;
	}
	return true;
}