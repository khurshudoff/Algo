#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

class PriorityMinQueue {
  public:
    bool empty() const;
    int top() const;
    void pop();
    void push(int value);
    PriorityMinQueue(vector<int> *inp);

  private:
    vector<int> arr;
    void sift_up(int index);
    void sift_down(int index);
};

PriorityMinQueue::PriorityMinQueue(vector<int> *inp) {
    for (int i = 0; i < inp->size(); i++) {
        arr.push_back(inp->at(i));
    }
    for (int i = arr.size()/2; i >= 0; i--) {
        sift_down(i);
    }
}
bool PriorityMinQueue::empty() const {
    return arr.empty();
}
int PriorityMinQueue::top() const {
    assert(arr.size() != 0);
    return arr[0];
}
void PriorityMinQueue::pop() {
    assert(arr.size() != 0);

    arr[0] = arr[arr.size() - 1];
    arr.pop_back();
    sift_down(0);
}
void PriorityMinQueue::push(int value) {
    arr.push_back(value);
    sift_up(arr.size()-1);
}
void PriorityMinQueue::sift_up(int index) {
    if ((arr[index] < arr[(index-1)/2]) && ((index-1)/2 >= 0)) {
        int tmp = arr[(index-1)/2];
        arr[(index-1)/2] = arr[index];
        arr[index] = tmp;
        sift_up((index-1)/2);
    }
}
void PriorityMinQueue::sift_down(int index) {
    int min_idx = -1;
    int min_val = -1;

    // if no child --> return
    if (index*2+1 >= arr.size()) return;

    // left child always present, if there is a child. Let him be a min
    min_idx = index*2+1;
    min_val = arr[index*2+1];

    // if right child is lower than right
    if (index*2+2 < arr.size()) {
        if (min_val > arr[index*2+2]) {
            min_idx = index*2+2;
            min_val = arr[index*2+2];
        }
    }

    // if min of (right_child_value, right_child_value) is lower than
    // current_node_value --> swap and run sift_down
    if (min_val < arr[index]) {
        int tmp = arr[index];
        arr[index] = min_val;
        arr[min_idx] = tmp;
        sift_down(min_idx);
    }
}


int main() {
    int commands_count = 0;
    cin >> commands_count;

    vector<int> arr(commands_count);

    for (int i = 0; i < commands_count; i++) {
        cin >> arr[i];
    }

    PriorityMinQueue pq(&arr);

    int res = 0;
    while (!pq.empty()) {
        int t1 = pq.top();
        pq.pop();

        int t2 = pq.top();
        pq.pop();

        res += t1 + t2;

        if (!pq.empty()) {
            pq.push(t1 + t2);
        }
    }

    cout << res;

    return 0;
}
