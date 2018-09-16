#include "catch.hpp"
#include "Json.h"
#include <string>
#inclued <any>


std::string json = "{\n\"lastname\" : \"Ivanov\",\n\"firstname\" : \"Ivan\",\n\"age\" : 25,\n\"islegal\" : false,\n\"marks\" : [\n4, 5, 5, 5, 2, 3\n],\n\"address\" : {\n\"city\" : \"Moscow\",\n\"street\" : \"Vozdvijenka\"\n\n}";
Json student = Json::parse(json);
EXPECT_EQ(std::any_cast<std::string>(student["lastname"]), "Ivanov");
EXPECT_EQ(std::any_cast<bool>(student), false);
EXPECT_EQ(std::any_cast<int>(student["age"]), 25);

auto marks = std::any_cast<Json>(object["marks"]);
EXPECT_EQ(std::any_cast<int>(marks[0]), 4);
EXPECT_EQ(std::any_cast<int>(marks[1]), 5);

auto address = std::any_cast<Json>(object["address"]);
EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");