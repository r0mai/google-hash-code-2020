#include <vector>
#include <iostream>


struct InDataSection {
	int t;
	int m;
	std::vector<int> ids;
};

struct InData {
	int D;
	std::vector<int> S;
	std::vector<InDataSection> L;
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
		int n, t, m;
		stream >> n >> t >> m;

		std::vector<int> ids(n);
		for (auto& item : ids) {
			stream >> item;
		}

		data.L[i].t = t;
		data.L[i].m = m;
		data.L[i].ids = std::move(ids);

	}

	data.D = D;
	data.S = std::move(S);
	return data;
}






int main() {


}
