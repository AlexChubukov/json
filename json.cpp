#include "my_json.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
    json empty_array = json::array();
	json my_json = json::array({
		{"Si-9.15", "RTS-9.15", "GAZP-9.15"},
		{100024, 100027, 100050},
		{"Futures contract for USD/RUB", "Futures contract for index RTS", "Futures contract for Gazprom shares"}
	});
    
    size_t count = 0;
	for (size_t j = 0; j < my_json.begin()->size(); ++j) {
		count = 0;
		json temp = json::object();
		for (size_t i = 0; i <my_json.size(); ++i,++count) {
			switch(count) {
			case 0:
				temp["ticker"] = my_json[i][j];
				break;
			case 1:
				temp["id"] = my_json[i][j];
				break;
			case 2:
				temp["description"] = my_json[i][j];
				break;
			}
		}
		empty_array.push_back(temp);
	}
    
        
    return 0;
}