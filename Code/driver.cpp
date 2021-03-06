/* University of Alabama in Huntsville
2015-2016 CPE Senior Design - Steelcase Answer Pack Verification
Elaine Boyd, Jacob Brooks, Devon Eastin, Lee Seemann

driver.cpp - source file for the length verification software

*/
#include "driver.h"

using namespace std;

driver::driver()
{
}

// functions like main() and kicks off the execution of the rest of the verification software
int* driver::startup(short depth_data[])
{
	printDataToFile(depth_data);
	// connect to test Oracle database
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

	is_profile_correct = verify_profile.initialize(); // initialize profile verification
	is_length_correct = verify_length.initialize(); // initialize length verification
	is_color_correct = verify_color.initialize(); // initialize color verification
	is_quantity_correct = verify_quantity.initialize(); // initialize quantity verification

	// based on the results of the verification code, populate the results array with the information needed
	// to inform the C# wrapper of the success/failure of the verification process	
	if (!is_profile_correct)
		results[0] = wrong_profile;
	else
		results[0] = correct;

	if (!is_length_correct)
		results[1] = wrong_length;
	else
		results[1] = correct;

	if (!is_color_correct)
		results[2] = wrong_color;
	else
		results[2] = correct;

	if (!is_quantity_correct)
		results[3] = wrong_quantity;
	else
		results[3] = correct;

	return results;
}

// printDataToFile() prints an array to a file for debugging purposes
void driver::printDataToFile(short data[])
{
	ofstream data_file;
	data_file.open("depth_data.txt");
	data_file << data[0] << endl;
	data_file.close();
}

driver::~driver()
{
}
