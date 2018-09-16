
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
			while (s[i] == ' ') {
				++i;
			}
			if (s[i] == '"') {
				++i;
				while (s[i] != '"') {
					value1 += s[i];
					++i;
				}
				object.field_obj.insert(std::pair<std::string, std::string>(key,value1));
				key = value1 = "";
			} else {
				if (s[i]=='[') {
					std::vector<std::any> v;
					while (s[i]!=']') {
						++i;
						while (s[i]==' ') {
							++i;
						}
						if (isdigit(s[i])) {
							v.push_back(atof(&(s[i])));
							while (s[i]!=',' && s[i]!=']') {
								++i;
							}
						}
						else {
							if (s[i]=='"') {
								++i;
								std::string s_arr="";
								while (s[i]!='"') {
									s_arr += s[i];
									++i;
								}
								v.push_back(s_arr);
							}
						}
					}
					Json temp_arr(v);
					value = temp_arr;
					object.field_obj.insert(std::pair<std::string, std::any>(key, value));
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
					}
					else {
						if (isdigit(s[i])) {
							value = atof(&(s[i]));
							object.field_obj.insert(std::pair<std::string, std::any>(key, value));
						}
						else {
							if (s[i] == 'f') {
								std::string s_bool="";
								while (s[i]!=',') {
									s_bool += s[i];
									++i;
								}
								if (s_bool == "false") {
									value = false;
									object.field_obj.insert(std::pair<std::string, std::any>(key, value));
								}
							}
							else {
								if (s[i] == 't') {
									std::string s_bool = "";
									while (s[i] != ',') {
										s_bool += s[i];
										++i;
									}
									if (s_bool == "true") {
										value = true;
										object.field_obj.insert(std::pair<std::string, std::any>(key, value));
									}
								}
								else {
									if (s[i]=='n') {
										std::string s_bool = "";
										while (s[i] != ',') {
											s_bool += s[i];
											++i;
										}
										if (s_bool == "null") {
											value = NULL;
											object.field_obj.insert(std::pair<std::string, std::any>(key, value));
										}
									}
								}
							}
						}
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
