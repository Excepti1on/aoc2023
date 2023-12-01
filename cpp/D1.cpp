//
// Created by oliver on 01.12.2023.
//

#include "D1.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cctype>

uint64_t D1::PartOne() {
	std::string line;
	std::vector<std::string> lines;
	std::vector<std::uint64_t> numbers;
	std::ifstream file("../../day1/input.txt");
	if(!file){
		std::cout << "Error opening file" << std::endl;
		system("pause");
		return -1;
	}
	while (std::getline(file, line)){
		lines.push_back(line);
	}
	std::ranges::transform(lines.begin(), lines.end(), lines.begin(), [](auto s){
		std::size_t first_index = s.find_first_of("0123456789");
	    std::size_t last_index = s.find_last_of("0123456789");
		return std::string{s.at(first_index), s.at(last_index)};
	});
	std::ranges::transform(lines, std::back_inserter(numbers), [](auto s){
		return std::stoull(s);
	});
	std::uint64_t result = std::ranges::fold_left(numbers, 0, std::plus());
	file.close();
	return result;
}
uint64_t D1::PartTwo() {
	std::string line;
	std::vector<std::string> lines;
	std::vector<std::uint64_t> numbers;
	std::ifstream file("../../day1/input.txt");
	if(!file){
		std::cout << "Error opening file" << std::endl;
		system("pause");
		return -1;
	}
	while (std::getline(file, line)){
		lines.push_back(line);
	}

	file.close();
    return 0;
}
