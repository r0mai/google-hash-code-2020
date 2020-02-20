#include "parse.hpp"



#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <string>
#include <vector>


using LibraryId = std::size_t;
using BookId = std::size_t;

int main(int argc, char** argv) {

	std::ifstream inputfile(argv[1]);
	assert(inputfile.good());
	InData inData = parse(inputfile);

	std::size_t numberOfLibraries = 0;
	std::cin >> numberOfLibraries;

	std::vector<std::pair<LibraryId, std::vector<BookId>>> scanOrders;
	for (std::size_t i=0; i<numberOfLibraries; ++i) {
		LibraryId libraryId = 0;
		std::size_t booksScanned = 0;
		std::cin >> libraryId >> booksScanned;

		auto library = std::vector<BookId>{};
		library.reserve(booksScanned);
		for (std::size_t j=0; j<booksScanned; ++j) {
			BookId bookId = -1;
			std::cin >> bookId;
			library.push_back(bookId);
		}
		scanOrders.push_back(std::make_pair(libraryId, std::move(library)));
	}

	std::vector<bool> booksScanned(inData.book_scores.size(), false);

	std::vector<LibraryId> availableLibraries;
	std::pair<decltype(scanOrders)::iterator, std::size_t> currentSignup;
	currentSignup = std::make_pair(
			scanOrders.begin(),
			inData.libraries[scanOrders.front().first].signup_days);

	std::size_t score = 0;

	for (std::size_t day=0; day < inData.days; ++day) {
		if (currentSignup.second > 0) {
			--currentSignup.second;
		} else {
			availableLibraries.push_back(currentSignup.first->first);
			++currentSignup.first;
			currentSignup.second =
					inData.libraries[currentSignup.first->first].signup_days-1;
		}
		for (std::size_t j=0; j<availableLibraries.size(); ++j) {
			auto libraryId = availableLibraries[j];

			auto& library = inData.libraries[libraryId];

			std::size_t batchScore = 0;
			auto batchSize = std::min(
					(std::size_t)library.books_per_day,
					scanOrders[j].second.size());

			for (std::size_t i=0; i<batchSize; ++i) {
				// TODO: Check that the book hasn't been scanned yet
				auto bookId = scanOrders[j].second[i];
				auto bookScore = inData.book_scores[bookId];
				if (!booksScanned[bookId]) {
					batchScore += bookScore;
				}
				booksScanned[bookId] = true;
			}
			score += batchScore;
			auto& localScanOrder = scanOrders[j].second;
			localScanOrder.erase(
					localScanOrder.begin(), localScanOrder.begin()+batchSize);
		}

		std::cout << day << " " << score << std::endl;
	}



}
