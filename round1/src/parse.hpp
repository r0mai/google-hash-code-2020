#ifndef PARSE_HPP_
#define PARSE_HPP_

#include <fstream>
#include <utility>
#include <vector>


struct InLibrary {
	int signup_days;
	int books_per_day;
	std::vector<int> books;
};

struct InData {
	int days;
	std::vector<int> book_scores;
	std::vector<InLibrary> libraries;
};


struct OutLibrary {
	int library_idx;
	std::vector<int> books;
};

struct OutData {
	std::vector<OutLibrary> libraries;
};


inline InData parse(std::istream& stream) {
	InData data;
	int B, L, D;

	stream >> B >> L >> D;

	std::vector<int> S(B);

	for (auto& item : S) {
		stream >> item;
	}


	data.libraries.resize(L);

	// sections
	for (auto i = 0; i < L; ++i) {
		int N, T, M;
		stream >> N >> T >> M;

		std::vector<int> ids(N);
		for (auto& item : ids) {
			stream >> item;
		}

		data.libraries[i].signup_days = T;
		data.libraries[i].books_per_day = M;
		data.libraries[i].books = std::move(ids);
	}

	data.days = D;
	data.book_scores = std::move(S);
	return data;
}



#endif // PARSE_HPP_
