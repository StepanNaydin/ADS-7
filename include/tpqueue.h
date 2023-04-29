// Copyright 2022 NNTU-CS
#include <iostream>
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct Node {
    char val;
    int prior;
    Node* next;

    Node(char val, int prior) : val(val), prior(prior), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(char val, int prior) {
        Node* p = new Node(val, prior);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void remove_first() {
        if (is_empty()) {
            return;
        }
        Node* p = first;
        first = p->next;
        delete p;
    }

    void remove_last() {
        if (is_empty()) {
            return;
        }
        if (first == last) {
            remove_first();
            return;
        }
        Node* p = first;
        while (p->next != last) {
            p = p->next;
        }
        p->next = nullptr;
        delete last;
        last = p;
    }

    Node* operator[] (const int index) {
        if (is_empty()) {
            return nullptr;
        }
        Node* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) {
                return nullptr;
            }
        }
        return p;
    }

    void prisvoit(const int index, char ch, int prior) {
        Node* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        p->prior = prior;
        p->val = ch;
    }
};

struct SYM {
    char ch;
    int prior;
};

template <typename T>
struct TPQueue {
 private:
    list arr;
    int count;

 public:
    TPQueue() : count(0) {}
    void push(const T& sum) {
        if (count == 0) {
            arr.push_back(sum.ch, sum.prior);
            count++;
        } else {
            for (int q = 0;; q++) {
                if (count == q) {
                    arr.push_back(sum.ch, sum.prior);
                    count++;
                    break;
                } else if (arr[q]->prior >= sum.prior) {
                    arr.push_back(arr[count - 1]->val, arr[count - 1]->prior);
                    for (int w = count - 1; w > q; w--) {
                        arr.prisvoit(w, arr[w - 1]->val, arr[w - 1]->prior);
                    }
                    arr.prisvoit(q, sum.ch, sum.prior);
                    count++;
                    break;
                }
            }
        }
    }
    const T pop() {
        T c{ arr[count - 1]->val, arr[count - 1]->prior };
        arr.remove_last();
        count--;
        return c;
    }
};

#endif  // INCLUDE_TPQUEUE_H_
