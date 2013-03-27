/* configPID - this class is used to read PID values from a file

	 created 3/12/2013 BD

*/

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "configPID.h"

using namespace std;

configPID::configPID(string fid)
{
	m_fid = fid;
	configPID::readFile(fid);
}

int configPID::readFile()
{
	configPID::readFile(m_fid);
}

int configPID::readFile(string fid)
{
	m_fid = fid;

	ifstream fin;
	string s1;
	int i = 0;

	fin.open(fid.c_str());
	if(fin.fail()) {
		printf("configPID::readFile(): unable to open %s\n", fid.c_str());
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
			P = atof(s1.c_str());
			break;

		case 1:
			I = atof(s1.c_str());
			break;

		case 2:
			D = atof(s1.c_str());
			break;
		}
		i++;
	}
	return 0;
}

