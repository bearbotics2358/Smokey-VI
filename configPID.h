/* configPID - this class is used to read PID values from a file

	 created 3/12/2013 BD

*/

#include <string>

using namespace std;

class configPID
{
public:
	configPID()
		{}

	configPID(string fid);


	~configPID()
		{}

	// return 0 for no error
	int readFile(string fid);

	// PID values
	double P;
	double I;
	double D;

} ;

