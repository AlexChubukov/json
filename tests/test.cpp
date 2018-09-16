#include "catch.hpp"
#include "Json.h"
#include <string>
#include <any>

using namespace std;


string json = "{\n\"lastname\" : \"Ivanov\",\n\"firstname\" : \"Ivan\",\n\"age\" : 25,\n\"islegal\" : false,\n\"marks\" : [\n4, 5, 5, 5, 2, 3\n],\n\"address\" : {\n\"city\" : \"Moscow\",\n\"street\" : \"Vozdvijenka\"\n\n}";

TEST_CASE("Testing pare") {
	Json student = Json::parse(json);
	REQUIRE(student["lastname"])== "Ivanov");
	REQUIRE(student["islegal"]== false);
	REQUIRE(student["age"]== 25);
	
	auto marks = any_cast<Json>(student["marks"]);
	REQUIRE(marks[0]== 4);
	REQUIRE(marks[1]== 5);
	
	auto address = any_cast<Json>(student["address"]);
	REQUIRE(address["city"] == "Moscow");
	REQUIRE(address["street"] == "Vozdvijenka");
}
