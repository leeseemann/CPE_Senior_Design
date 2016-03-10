/* University of Alabama in Huntsville
2015-2016 CPE Senior Design - Steelcase Answer Pack Verification
Elaine Boyd, Jacob Brooks, Devon Eastin, Lee Seemann

driver.cpp - source file for the length verification software

Modification History
Developer		Date			Comments
--------------------------------------------------------------------------------
Lee				12/28/15		file created, added startup() function
Lee				1/9/16			used OCCI to created Oracle database connection, executed test query
Lee				1/31/16			modified startup() to receive data from C# wrapper
Lee				3/9/16			added code to allow the path of the color image from the Kinect to be 
								received from the C# driver

--------------------------------------------------------------------------------
*/
#include "driver.h"

using namespace std;

driver::driver()
{
}

void driver::startup(short depth_data[], string file_path)
{
	verify_profile.initialize(); // initialize profile verification
	verify_length.initialize(); // initialize length verification
	verify_color.initialize(); // initialize color verification
	verify_quantity.initialize(); // initialize quantity verification

	// connect to Oracle database
	userName = "hr";
	password = "uah";
	connectString = "";
	conn = oracle_db.connectDatabase(userName, password, connectString);

	// query the Oracle database
	if (conn != NULL)
	{
		query_string = "select num from data";
		result_query = oracle_db.queryDatabase(conn, query_string);
		while (result_query->next())
			cout << "result: " << result_query->getInt(1) << endl;
	}

	cout << "info: " << depth_data[0];

	//cout << "file path: " << file_path << endl;

	return;
}

driver::~driver()
{
}
