
#include "Json.h"
#include <string>
#include <cctype>
#include <vector>
#include <iostream>
#include <fstream>

Json::Json() {}

Json::Json(std::vector<std::any>& v) {
	vec.field_arr = v;
}

Json::Json(const std::string & s) {
	//std::string *s1=s;
	//std::vector<int> v;
	int i = 0;
	std::string key = "", value1 = "";
	std::any value;
	while (s[i]!='\0') {
		if (s[i] == '"') {
			++i;
			while (s[i] != '"') {
				key += s[i];
				++i;
			}
		}
		if (s[i] == ':') {
			++i;
			if (s[i] == '"') {
				++i;
				while (s[i] != '"') {
					value1 += s[i];
					++i;
				}
				object.field_obj.insert(std::pair<std::string, std::string>(key,value1));
				//object.field_obj.insert(std::pair<std::string, std::string>(key, value1));
				key = value1 = "";
			} else {
				if (s[i]=='[') {
					std::vector<std::any> v;
					while (s[i]!=']') {
						++i;
						if (isdigit(s[i])) {
							v.push_back(atoi(&(s[i])));
						}
					}
					Json temp_arr(v);
					value = temp_arr;
					object.field_obj.insert(std::pair<std::string, std::any>(key, value));
					//mas.field_mas = v;
				}
				else {
					if (s[i]=='{') {
						std::string temp_s;
						while (s[i] != '}') {
							temp_s += s[i];
							++i;
						}
						temp_s += '}';
						Json temp(temp_s);
						object.field_obj.insert(std::pair<std::string,Json>(key,temp));
						//std::map<std::string, std::any> my_map;
						/*std::string key_2;
						std::any value_2;
						while (s[i]!='}') {
							++i;
							if (s[i] == '"') {
								++i;
								while (s[i] != '"') {
									key_2 += s[i];
									++i;
								}
							}
							if (s[i] == ':') {
								i += 2;
								if (s[i] == '"') {
									++i;
									while (s[i] != '"') {
										value1 += s[i];
										++i;
									}
									temp.
									my_map.insert(std::pair<std::string, std::string>(key2, value1));
									key2 = value1 = "";
								}
								else {
									if (s[i] == '[') {
										while (s[i] != ']') {
											++i;
											if (isdigit(s[i])) {
												v.push_back(atoi(&(s[i])));
											}
										}
										mas.field_mas = v;
									}
									else {
										if (isdigit(s[i])) {
											value = atoi(&(s[i]));
										}
										else {
											if (s[i] == 'f') {
												value = false;
											}
											else {
												value = true;
											}
										}
										my_map.insert(std::pair<std::string, std::any>(key2, value1));
									}
									key2 = "";
								}
							}
						}
						value = my_map;*/
					}
					else {
						if (isdigit(s[i])) {
							value = atoi(&(s[i]));
							//value2 = atoi((s1+i).c_str());
						}
						else {
							if (s[i] == 'f') {
								value = false;
							}
							else {
								value = true;
							}
						}
						object.field_obj.insert(std::pair<std::string, std::any>(key, value));
						//object.field_obj.insert(std::pair<std::string, std::any>(key, value));
					}
				}
				key = "";
			}
		}
		++i;
	}
}

bool Json::is_array() const {
	return !vec.field_arr.empty();
}

bool Json::is_object() const
{
	return !object.field_obj.empty();
}

std::any & Json::operator[](const std::string & key) {
	for (auto it = object.field_obj.begin(); it != object.field_obj.end(); ++it) {
		if (it->first == key) {
			return it->second;
		} 
	}
}

std::any & Json::operator[](int index) {
	if (this->is_array()) {
		return this->vec.field_arr[index];
	}
}

Json Json::parse(const std::string & s) {
	return Json(s);
}

Json Json::parseFile(const std::string & path_to_file) {
	std::ifstream fin(path_to_file);
	char temp;
	std::string s;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> temp;
			s += temp;
		}
	}
	else {
		std::cout << "Данного файла не существует." << std::endl;
	}
	fin.close();
	return Json(s);
}
