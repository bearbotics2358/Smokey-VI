/* configAuto - this class is used to read values for Autonomous mode from a file

	 created 3/26/2013 BD

*/
#ifndef _CONFIG_AUTO_H_
#define _CONFIG_AUTO_H_

#include <string>

using namespace std;

class configAuto
{
public:
	configAuto();
	configAuto(string fid);
	~configAuto();

	// return 0 for no error
	int readFile();
	int readFile(string fid);

	// values
	double shooter; // Jaguar voltage setting
	double speed; // driving speed
	double distance; // distance to move
	double time; // time to move

	// the config file name
	string m_fid;

} ;

#endif //_CONFIG_AUTO_H_
