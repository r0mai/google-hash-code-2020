#include "parse.hpp"

#include <vector>
#include <iostream>



void print(std::ostream& stream, const OutData& data) {
	stream << data.libraries.size() << std::endl;
	for (auto& item : data.libraries) {
		stream << item.library_idx << " " << item.books.size() << std::endl;
		bool first = true;
		for (auto& k : item.books) {
			if (first) {
				first = false;
			} else {
				stream << " ";
			}
			stream << k;
		}
		stream << std::endl;
	}
}


int main() {


}
