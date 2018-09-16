#include "catch.hpp"
#include "Json.h"
#include <string>
#include <any>

using namespace std;


string json = "{\n\"lastname\" : \"Ivanov\",\n\"firstname\" : \"Ivan\",\n\"age\" : 25,\n\"islegal\" : false,\n\"marks\" : [\n4, 5, 5, 5, 2, 3\n],\n\"address\" : {\n\"city\" : \"Moscow\",\n\"street\" : \"Vozdvijenka\"\n\n}";

TEST_CASE("Testing pare") {
	Json student = Json::parse(json);
	REQUIRE(any_cast<string>(student["lastname"])== "Ivanov");
	REQUIRE(any_cast<bool>(student["islegal"])== false);
	REQUIRE(any_cast<double>(student["age"])== 25);
	
	auto marks = any_cast<Json>(student["marks"]);
	REQUIRE(any_cast<double>(marks[0])== 4);
	REQUIRE(any_cast<double>(marks[1])== 5);
	
	auto address = any_cast<Json>(student["address"]);
	REQUIRE(any_cast<string>(address["city"]) == "Moscow");
	REQUIRE(any_cast<string>(address["street"]) == "Vozdvijenka");
}
