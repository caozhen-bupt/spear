#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
	int i=10,j=100;
	std::stringstream iss, jss;
	iss << i;
	jss << j;
	std::string istr = iss.str();
	std::string jstr = jss.str();
	std::cout<<"10.1."+istr+"."+jstr;
	
	
	return 0;
}
