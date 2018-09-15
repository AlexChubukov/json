// json.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <iostream>
#include <Windows.h>
#include "Json.h"

using namespace std;


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string json="{ \n\"lastname\" : \"Ivanov\",\n\"firstname\" : \"Ivan\",\n\"age\" : 25,\n\"islegal\" : false,\n\"marks\" : [\n4, 5, 5, 5, 2, 3\n],\n\"address\" : {\n\"city\" : \"Moscow\",\n\"street\" : \"Vozdvijenka\"\n\n}";
	
	Json student = Json::parse(json);
	//Json student = Json::parseFile("json.txt");

	cout << any_cast<string>(student["lastname"]) << endl;
	cout << any_cast<bool>(student["islegal"]) << endl;
	cout << any_cast<int>(student["age"]) << endl;

	auto marks = std::any_cast<Json>(student["marks"]);
	cout << any_cast<int>(marks[0]) << endl;
	cout << any_cast<int>(marks[1]) << endl;

	auto address = std::any_cast<Json>(student["address"]);
	cout << any_cast<std::string>(address["city"]) << endl;
	cout << any_cast<std::string>(address["street"]) << endl;




    return 0;
}


