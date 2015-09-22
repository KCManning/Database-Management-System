#include "Constants.h"

class Queries
{
public:
	//Queries();

	MYSQL mysql; 
	MYSQL_ROW row; 
	MYSQL_RES *result; 

	unsigned int num_fields; 

	string stateSelect;
	string stateInsert;
	string table;
	string query;
	string whereStatement;


private:

};