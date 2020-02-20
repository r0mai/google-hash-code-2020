#include <vector>
#include <iostream>


struct Data2 {
	int t;
	int m;
	std::vector<int> ids;
};

struct Data {
	int D;
	std::vector<int> S;
	std::vector<Data2> L;
};


Data parse(std::istream& stream) {
	Data data;
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
