#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int pid;
    int time;
} process;

template <typename T>
class node {
public:
    T data;
    node<T>* next;
    node<T>* prev;

    node(T data) {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

template <typename T>
class cll {
private:
    node<T> *head;
    node<T> *tail;

public:
    cll() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(T data) {
        auto new_node = new node<T>(data);

        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        tail->next = head;
        head->prev = tail;
    }

    void pop_front() {
        if (head == nullptr)
            return;

        auto temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = tail;
            tail->next = head;
        }
    }

    void pop_back() {
        if (tail == nullptr)
            return;

        auto temp = tail;
        tail = tail->prev;
        delete temp;

        if (tail == nullptr) {
            head = nullptr;
        } else {
            head->prev = tail;
            tail->next = head;
        }
    }

    node<T>* front() {
        return head;
    }

    bool empty() {
        return head == nullptr;
    }
};

void solve(vector<process>& processes, int quantum) {
    cll<process> queue;

    for (auto& process : processes)
        queue.push_back(process);

    auto current = queue.front();
    auto total = 0;

    while (true) {
        auto time = min(quantum, current->data.time);

        current->data.time -= time;
        total += time;

        if (current->data.time == 0) {
            current->prev->next = current->next;
            current->next->prev = current->prev;

            cout << current->data.pid << " (" << total << ")\n";

            if (current == current->next) {
                delete current;
                break;
            }
        }

        current = current->next;
    }
}

int main() {
    int N, Q, P, T;
    cin >> N >> Q;

    vector<process> processes;
    
    for (int i = 0; i < N; i++) {
        cin >> P >> T;
        processes.push_back({ .pid = P, .time = T * 1000 });
    }

    solve(processes, Q);
}
