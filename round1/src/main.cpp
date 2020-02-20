#include <vector>
#include <iostream>


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


InData parse(std::istream& stream) {
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
