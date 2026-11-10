#include <vector>
#include <algorithm>

template <typename T, typename Container = std::vector<T>>

class Heap {
public:
	Heap(const T& (*func)(const T&, const T&)) {
		data = Container();
		comp_func = func;
		size = 0;
	}
	Heap(Container origin, const T& (*func)(const T&, const T&)) {
		comp_func = func;
		build_heap(origin);
	}

private:
	Container data;
	const T& (*comp_func)(const T&, const T&);
	int size;

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * i + 2; }

	void percolate_up(int i) {
		while (i > 0 && comp_func(data[i], data[parent(i)]) == data[i]) {
			std::swap(data[i], data[parent(i)]);
			i = parent(i);
		}
	}
	void percolate_down(int i) {
		int l = left(i);
		int r = right(i);
		int largest;

		if (l < size && comp_func(data[l], data[i]) == data[l]) {
			largest = l;
		} else {
			largest = i;
		}
		if (r < size && comp_func(data[r], data[largest]) == data[r]) {
			largest = r;
		}

		if (largest != i) {
			std::swap(data[i], data[largest]);
			percolate_down(largest);
		}
	}

public:
	T top() { return data[0]; }
	void insert(const T& val) {
		data.emplace_back(val);
		percolate_up(size);
		size++;
	}
	T delete_end() {
		size--;
		T val = data[size];
		data.pop_back();
		return val;
	}
	T pop() {
		size--;
		T val = top();
		std::swap(data[0], data[size]);
		data.pop_back();
		percolate_down(0);
		return val;
	}
	int get_size() { return size; }
	bool empty() { return size == 0; }

	void build_heap(Container origin) {
		size = origin.size();
		data = origin;
		for (int i = (origin.size() / 2) - 1; i >= 0; i--) {
			percolate_down(i);
		}
	}
};
