/*
Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
*/

#include <assert.h>
#include <iostream>
#include <cstring>

using namespace std;

class Stack {
  public:
    ~Stack();
    bool empty() const;

    void push(int value);

    void pop();

    int top();

  private:
    int index = 0;
    int current_length = 1;
    int* arr = new int[current_length];
};

Stack::~Stack() {
    delete[] arr;
}
bool Stack::empty() const {
    return index == 0;
}
void Stack::push(int value) {
    if (index != current_length) {
        arr[index++] = value;
    } else {
        current_length *= 3;
        int* tmp = new int[current_length];
        memcpy(tmp, arr, index * sizeof(int));
        delete[] arr;
        arr = tmp;
        arr[index++] = value;
    }
}
int Stack::top() {
    assert(index != 0);
    return arr[index-1];
}
void Stack::pop() {
    assert(index != 0);

    index--;

    if (index < current_length/3) {
        current_length /= 3;
        int* tmp = new int[current_length];
        memcpy(tmp, arr, index * sizeof(int));
        delete[] arr;
        arr = tmp;
    }
}

class Queue {
public:
    bool empty();
    void push(int value);
    int top();
    void pop();
private:
    Stack stack_1;
    Stack stack_2;
    void push_to_stack_2();
};

bool Queue::empty(){
    return (stack_2.empty() && stack_1.empty());
};
void Queue::push(int value) {
    stack_1.push(value);
}
int Queue::top() {
    push_to_stack_2();
    return stack_2.top();
}
void Queue::pop() {
    push_to_stack_2();
    stack_2.pop();
}
void Queue::push_to_stack_2() {
    if (stack_2.empty()) {
        // if stack_2 is empty -> fill it from stack_1
        while (!stack_1.empty()) {
            stack_2.push(stack_1.top());
            stack_1.pop();
        }
    }
}

int main() {
    Queue queue;

    int commands_count = 0;
    cin >> commands_count;

    for (int i = 0; i < commands_count; ++i) {
        int command = 0;
        int value = 0;

        cin >> command >> value;

        if (command == 3) {  // top
            queue.push(value);
        }
        if (command == 2) {  // pop
            if (queue.empty()) {
                if (value != -1) {
                    cout << "NO" << endl;
                    return 0;
                }
            } else {
                if (queue.top() != value) {
                    cout << "NO";
                    return 0;
                }
                queue.pop();
            }
        }
    }

    cout << "YES" << endl;

    return 0;
}
