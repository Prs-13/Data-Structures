#include <iostream>
using namespace std;

class MaxHeap {
private:
    int* heap;
    int capacity;
    int size;

    int parent(int i) {
        return (i - 1) / 2; 
    }

    int left(int i)   {
        return 2 * i + 1;
    }

    int right(int i)  {
        return 2 * i + 2; 
    }

    void upHeapify(int i) {
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void downHeapify(int i) {
        int largest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] > heap[largest])
            largest = l;
        if (r < size && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            downHeapify(largest);
        }
    }

public:
    MaxHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        heap = new int[cap];
    }

    bool push(int key) {
        if (size == capacity) {
            cout << "Heap overflow\n";
            return false;
        }
        heap[size] = key;
        upHeapify(size);
        size++;
        return true;
    }

    bool removeKey(int &removedValue) {
        if (size == 0) {
            cout << "Heap underflow\n";
            return false;
        }

        removedValue = heap[0];       
        heap[0] = heap[size - 1];
        size--;
        downHeapify(0);
        return true;
    }

    bool top(int &maxValue) {
        if (size == 0) return false;
        maxValue = heap[0];
        return true;
    }
};

int main() {
    MaxHeap h(10);
    h.push(10);
    h.push(40);
    h.push(20);
    h.push(50);
    h.push(30);
    int val;
    cout << "Removing top elements: ";
    while (h.removeKey(val)) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
