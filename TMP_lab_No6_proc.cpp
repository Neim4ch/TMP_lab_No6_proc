// TMP_lab_No6_proc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Source.h"
using namespace std;
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "incorrect command line! Waited: command in_file out_file" << endl;
		exit(1);
	}
	ifstream ifst(argv[1]);
	ofstream ofst(argv[2]);

	fileCheck(ifst);

	ifst.close();
	ifst.open(argv[1]);

	cout << "Start" << endl;
	
	container films;
	inCont(ifst, &films);
	ofst << "Filled container. " << endl;
	ofst << "Unsorted cont. " << endl;
	outCont(ofst, &films);
	ofst << endl << endl;

	sort(films);
	ofst << "Sorted cont. " << endl;
	outCont(ofst, &films);
	ofst << endl << endl;

	outFeature(ofst, &films);
	clear(&films);
	ofst << "Empty container. " << endl;
	outCont(ofst, &films);
	
	cout << "Stop" << endl;
	return 0;
}