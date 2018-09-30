#ifndef JSON_H
#define JSON_H
#endif  // ! JSON_H
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <any>
#include <map>
#include <vector>
#include <optional>

const int OPS_ERROR = 1;

struct object_ {
  std::map<std::string, std::any> field_object;
};

struct Array {
  std::vector<std::any> field_array;
};

class Json {
  object_ object_;
  Array vector_;

 public:
  Json();

  Json(std::vector<std::any>&
           value);  // Конструктор для присваивания массива полю Json
                    // Конструктор из строки, содержащей Json-данные.
  Json(const std::string& value);

  // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив.
  // Иначе false.
  bool is_array() const;

  // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект.
  // Иначе false.
  bool is_object() const;

  // Метод возвращает значение по ключу key, если экземпляр является
  // JSON-объектом.
  // Значение может иметь один из следующих типов: Json, std::string, double,
  // bool или быть пустым.
  // Если экземпляр является JSON-массивом, генерируется исключение.
  std::optional<std::any> operator[](const std::string& key);

  // Метод возвращает значение по индексу index, если экземпляр является
  // JSON-массивом.
  // Значение может иметь один из следующих типов: Json, std::string, double,
  // bool или быть пустым.
  // Если экземпляр является JSON-объектом, генерируется исключение.
  std::optional<std::any> operator[](unsigned int index);

  // Метод возвращает объект класса Json из строки, содержащей Json-данные.
  static Json parse(const std::string& s);

  // Метод возвращает объекта класса Json из файла, содержащего Json-данные в
  // текстовом формате.
  static Json parseFile(const std::string& path_to_file);
};

Json::Json() {}

Json::Json(std::vector<std::any>& value) { vector_.field_array = value; }

Json::Json(const std::string& s) {
  int counter = 0;
  std::string key = "", value_string = "";
  std::any value;
  while (s[counter] != '\0') {
    if (s[counter] == '"') {
      ++counter;
      while (s[counter] != '"') {
        key += s[counter];
        ++counter;
      }
    }
    if (s[counter] == ':') {
      ++counter;
      while (s[counter] == ' ') {
        ++counter;
      }
      if (s[counter] == '"') {
        ++counter;
        while (s[counter] != '"') {
          value_string += s[counter];
          ++counter;
        }
        object_.field_object.insert(
            std::pair<std::string, std::string>(key, value_string));
        key = value_string = "";
      } else {
        if (s[counter] == '[') {
          std::vector<std::any> vector_of_values;
          while (s[counter] != ']') {
            ++counter;
            while (s[counter] == ' ') {
              ++counter;
            }
            if (isdigit(s[counter])) {
              vector_of_values.push_back(atof(&(s[counter])));
              while (s[counter] != ',' && s[counter] != ']') {
                ++counter;
              }
            } else {
              if (s[counter] == '"') {
                ++counter;
                std::string string_to_array = "";
                while (s[counter] != '"') {
                  string_to_array += s[counter];
                  ++counter;
                }
                vector_of_values.push_back(string_to_array);
              } else {
                if (s[counter] == '[') {
                  ++counter;
                  std::string string_to_parse = "";
                  while (s[counter] != ']') {
                    string_to_parse += s[counter];
                    ++counter;
                  }
                  string_to_parse += " ";
                  ++counter;
                  vector_of_values.push_back(Json(string_to_parse));
                } else {
                  if (s[counter] == '{') {
                    ++counter;
                    std::string string_of_objects = "";
                    while (s[counter] != '}') {
                      string_of_objects += s[counter];
                      ++counter;
                    }
                    vector_of_values.push_back(Json(string_of_objects));
                  }
                }
              }
            }
          }
          Json temp_arr(vector_of_values);
          value = temp_arr;
          object_.field_object.insert(
              std::pair<std::string, std::any>(key, value));
        } else {
          if (s[counter] == '{') {
            std::string string_objects;
            while (s[counter] != '}') {
              string_objects += s[counter];
              ++counter;
            }
            string_objects += '}';
            Json temp(string_objects);
            object_.field_object.insert(
                std::pair<std::string, Json>(key, temp));
          } else {
            if (isdigit(s[counter])) {
              value = atof(&(s[counter]));
              object_.field_object.insert(
                  std::pair<std::string, std::any>(key, value));
            } else {
              if (s[counter] == 'f') {
                std::string string_of_bool = "";
                while (s[counter] != ',' && s[counter] != '"' &&
                       s[counter] != ' ') {
                  string_of_bool += s[counter];
                  ++counter;
                }
                if (string_of_bool == "false") {
                  value = false;
                  object_.field_object.insert(
                      std::pair<std::string, std::any>(key, value));
                }
              } else {
                if (s[counter] == 't') {
                  std::string string_of_bool = "";
                  while (s[counter] != ',') {
                    string_of_bool += s[counter];
                    ++counter;
                  }
                  if (string_of_bool == "true") {
                    value = true;
                    object_.field_object.insert(
                        std::pair<std::string, std::any>(key, value));
                  }
                } else {
                  if (s[counter] == 'n') {
                    std::string string_of_null = "";
                    while (s[counter] != ',' && s[counter] != ' ' &&
                           s[counter] != '"') {
                      string_of_null += s[counter];
                      ++counter;
                    }
                    if (string_of_null == "null") {
                      value = NULL;
                      object_.field_object.insert(
                          std::pair<std::string, std::any>(key, value));
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
    ++counter;
  }
}

bool Json::is_array() const { return !vector_.field_array.empty(); }

bool Json::is_object() const { return !object_.field_object.empty(); }

std::optional<std::any> Json::operator[](const std::string& key) {
  if (this->is_object()) {
    for (auto it = object_.field_object.begin();
         it != object_.field_object.end(); ++it) {
      if (it->first == key) {
        return it->second;
      }
    }
    return std::nullopt;
  }
  throw OPS_ERROR;
}

std::optional<std::any> Json::operator[](unsigned int index) {
  if (this->is_array()) {
    if (index < vector_.field_array.size()) {
      return this->vector_.field_array[index];
    }
    return std::nullopt;
  }
  throw OPS_ERROR;
}

Json Json::parse(const std::string& s) { return Json(s); }

Json Json::parseFile(const std::string& path_to_file) {
  std::ifstream fin(path_to_file);
  char temp;
  std::string s;
  if (fin.is_open()) {
    while (!fin.eof()) {
      fin >> temp;
      s += temp;
    }
  } else {
    std::cout << "Данного файла не существует." << std::endl;
  }
  fin.close();
  return Json(s);
}