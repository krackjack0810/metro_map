#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T>
class Heap {
private:
    std::vector<T> data;
    std::unordered_map<T, int> map;

    void upheapify(int ci) {
        int pi = (ci - 1) / 2;
        if (isLarger(data[ci], data[pi]) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }

    void swap(int i, int j) {
        T ith = data[i];
        T jth = data[j];

        data[i] = jth;
        data[j] = ith;
        map[ith] = j;
        map[jth] = i;
    }

    void downheapify(int pi) {
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;
        int maxi = pi;

        if (lci < static_cast<int>(data.size()) && isLarger(data[lci], data[maxi]) > 0) {
            maxi = lci;
        }

        if (rci < static_cast<int>(data.size()) && isLarger(data[rci], data[maxi]) > 0) {
            maxi = rci;
        }

        if (maxi != pi) {
            swap(maxi, pi);
            downheapify(maxi);
        }
    }

    int isLarger(T t, T o) {
        if (t < o) return -1;
        else if (t == o) return 0;
        else return 1;
    }

public:
    void add(T item) {
        data.push_back(item);
        map[item] = data.size() - 1;
        upheapify(data.size() - 1);
    }

    void display() {
        for (const T& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    int size() {
        return static_cast<int>(data.size());
    }

    bool isEmpty() {
        return size() == 0;
    }

    T remove() {
        swap(0, data.size() - 1);
        T rv = data.back();
        data.pop_back();
        downheapify(0);
        map.erase(rv);
        return rv;
    }

    T get() {
        return data[0];
    }

    void updatePriority(T pair) {
        int index = map[pair];
        upheapify(index);
    }
};

int main() {
    Heap<int> heap;
    heap.add(5);
    heap.add(3);
    heap.add(7);
    heap.add(1);
    heap.add(9);
    heap.display();

    heap.updatePriority(1);
    heap.display();

    std::cout << "Removed: " << heap.remove() << std::endl;
    heap.display();

    return 0;
}

