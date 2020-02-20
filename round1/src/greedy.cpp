#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "parse.hpp"

double power = 2.0f;
double lambda = 1.0f;

int wasted_days = 0;

struct Greedy {
	Greedy(InData in) : in(std::move(in)) {}

	InData in;

	std::vector<bool> books_scanned;
	std::vector<bool> libraries_signed;
	std::vector<int> library_scores;

	int DaysToScanEverything(int library_idx) {
		auto& library = in.libraries[library_idx];

		int non_scanned_book_count = 0;
		for (int book : library.books) {
			if (!books_scanned[book]) {
				non_scanned_book_count++;
			}
		}
		// TODO round up
		return library.signup_days + non_scanned_book_count / library.books_per_day;
	}

	int BookScoreLibrary(int library_idx, int start_day) {
		auto& library = in.libraries[library_idx];

		int days_left = in.days - start_day - library.signup_days;
		int scannable_books = days_left * library.books_per_day;

		int score = 0;
		for (int book : library.books) {
			if (scannable_books <= 0) {
				break;
			}
			if (!books_scanned[book]) {
				score += in.book_scores[book];
				--scannable_books;
			}
		}
		return score;
	}

	float SmartScoreLibrary(int library_idx, int start_day) {
		auto& library = in.libraries[library_idx];

		int book_score = BookScoreLibrary(library_idx, start_day);
		if (book_score == 0) {
			return std::numeric_limits<float>::lowest();
		}
		int days_left = in.days - start_day;
		int setup_time = library.signup_days;

		return book_score * (std::pow(double(days_left - lambda * setup_time), power) / double(days_left));
	}

	std::vector<int> ScanFromLibrary(int library_idx, int start_day) {
		auto& library = in.libraries[library_idx];

		int days_left = in.days - start_day - library.signup_days;
		int scannable_books = days_left * library.books_per_day;

		if (days_left <= 0) {
			return {};
		}

		if (scannable_books > library.books.size()) {
			wasted_days += (scannable_books - library.books.size()) / library.books_per_day;
		}

		std::vector<int> books;
		books.reserve(scannable_books);

		for (int book : library.books) {
			if (scannable_books <= 0) {
				break;
			}
			if (!books_scanned[book]) {
				books.push_back(book);
				books_scanned[book] = true;
				--scannable_books;
			}
		}
		return books;
	}

	OutData Solve() {
		books_scanned.resize(in.book_scores.size());
		library_scores.resize(in.libraries.size());
		libraries_signed.resize(in.libraries.size());

		// sort books in desceding order of score
		for (auto& library : in.libraries) {
			std::sort(library.books.begin(), library.books.end(),
				[this](int lhs, int rhs) {
					return in.book_scores[lhs] > in.book_scores[rhs];
				}
			);
		}

		OutData out;
		int day = 0;
		while (true) {
			float max_score = std::numeric_limits<float>::lowest();
			int max_idx = -1;
			for (int i = 0; i < in.libraries.size(); ++i) {
				if (libraries_signed[i]) {
					continue;
				}
				auto score = SmartScoreLibrary(i, day);
				if (score > max_score) {
					max_score = score;
					max_idx = i;
				}
			}

			// nothing more to scan
			if (max_idx < 0) {
				break;
			}

			OutLibrary out_lib;
			out_lib.library_idx = max_idx;
			out_lib.books = ScanFromLibrary(max_idx, day);
			out.libraries.push_back(std::move(out_lib));

			auto& best_library = in.libraries[max_idx];
			day += best_library.signup_days;
			libraries_signed[max_idx] = true;
			// out of time
			if (day >= in.days) {
				break;
			}
		}
		return out;
	}
};


int main(int argc, char** argv) {
	if (argc >= 2) {
		power = std::stod(argv[1]);
	}
	if (argc >= 3) {
		lambda = std::stod(argv[2]);
	}

	print(std::cout, Greedy{parse(std::cin)}.Solve());
	// std::cerr << "Wasted days = " << wasted_days << std::endl;
}
