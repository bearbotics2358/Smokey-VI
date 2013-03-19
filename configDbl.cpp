/* configDbl - this class is used to read a double value from a file

	 created 3/15/2013 BD

*/

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "configDbl.h"

using namespace std;

configDbl::configDbl(string fid)
{
	configDbl::readFile(fid);
}

int configDbl::readFile(string fid)
{
	ifstream fin;
	string s1;


	fin.open(fid.c_str());
	if(fin.fail()) {
		printf("configDbl::readFile(): unable to open %s\n", fid.c_str());
		return -1;
	}
	while(!fin.eof()) {
		getline(fin, s1);
		if(fin.eof()) {
			break;
		}
		// comment - ignore it
		if(s1[0] == '#') {
			continue;
		}
		printf(" %s\n", s1.c_str());
		d = atof(s1.c_str());
		break;
	}
	return 0;
}

