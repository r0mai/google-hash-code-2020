#include <vector>
#include <iostream>


struct InDataSection {
	int T;
	int M;
	std::vector<int> ids;
};

struct InData {
	int D;
	std::vector<int> S;
	std::vector<InDataSection> L;
};


struct OutDataSection {
	int Y;
	std::vector<int> K;
};

struct OutData {
	std::vector<OutDataSection> A;
};


InData parse(std::istream& stream) {
	InData data;
	int B, L, D;

	stream >> B >> L >> D;

	std::vector<int> S(B);

	for (auto& item : S) {
		stream >> item;
	}


	data.L.resize(L);

	// sections
	for (auto i = 0; i < L; ++i) {
		int N, T, M;
		stream >> N >> T >> M;

		std::vector<int> ids(N);
		for (auto& item : ids) {
			stream >> item;
		}

		data.L[i].T = T;
		data.L[i].M = M;
		data.L[i].ids = std::move(ids);

	}

	data.D = D;
	data.S = std::move(S);
	return data;
}

void print(std::ostream& stream, const OutData& data) {
	stream << data.A.size() << std::endl;
	for (auto& item : data.A) {
		stream << item.Y << " " << item.K.size() << std::endl;
		bool first = true;
		for (auto& k : item.K) {
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
