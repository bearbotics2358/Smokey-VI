/* configAuto - this class is used to read values for Autonomous mode from a file

	 created 3/26/2013 BD

*/

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "configAuto.h"

using namespace std;

configAuto::configAuto(string fid)
{
	m_fid = fid;
	configAuto::readFile(fid);
}

int configAuto::readFile()
{
	configAuto::readFile(m_fid);
}

int configAuto::readFile(string fid)
{
	m_fid = fid;

	ifstream fin;
	string s1;
	int i = 0;

	fin.open(fid.c_str());
	if(fin.fail()) {
		printf("configAuto::readFile(): unable to open %s\n", fid.c_str());
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
		switch(i) {
		case 0:
			shooter = atof(s1.c_str());
			break;

		case 1:
			speed = atof(s1.c_str());
			break;

		case 2:
			distance = atof(s1.c_str());
			break;

		case 3:
			time = atof(s1.c_str());
			break;
		}
		i++;
	}
	return 0;
}

