#pragma once

#include <fstream>
#include "../Lib/json.hpp"
using json = nlohmann::json;

static void parseData() {
	//std::ifstream f("../Saves/example.json");
	//json data = json::parse(f);
	//std::ofstream f("../Saves/example2.json");
	//write(to_string(ex3).c_str(), sizeof(to_string(ex3).c_str()));
	std::ofstream file("Saves/relative_path_test.json");

	if (file.is_open()) {
		file << "{Test file: 1}";
	}

	file.close();
}