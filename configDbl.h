/* configDbl - this class is used to read a double value from a file

	 created 3/15/2013 BD

*/

#include <string>

using namespace std;

class configDbl
{
public:
	configDbl()
		{}

	configDbl(string fid);


	~configDbl()
		{}

	// return 0 for no error
	int readFile();
	int readFile(string fid);

	// double value
	double d;

	// the config file name
	string m_fid;
} ;

