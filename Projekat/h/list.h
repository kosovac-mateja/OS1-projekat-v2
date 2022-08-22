#ifndef PROJEKAT_LIST_H
#define PROJEKAT_LIST_H

#include "../lib/hw.h"
#include "memoryAllocator.h"

template<typename T>

class List {
private:
    struct Elem {
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;

    uint64 cnt = 0;

public:
    List() : head(0), tail(0) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    uint64 getCnt() { return cnt; }

    void addFirst(T *data) {
        Elem *elem = new Elem(data, head);
        head = elem;
        if (!tail) { tail = head; }
        cnt++;
    }

    void addLast(T *data) {
        Elem *elem = new Elem(data, 0);
        if (tail) {
            tail->next = elem;
            tail = elem;
        } else {
            head = tail = elem;
        }
        cnt++;
    }

    T *removeFirst() {
        if (!head) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        T *ret = elem->data;
        delete elem;
        cnt--;
        return ret;
    }

    T *peekFirst() {
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast() {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
            prev = curr;

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
        delete elem;
        cnt--;
        return ret;
    }

    T *peekLast() {
        if (!tail) { return 0; }
        return tail->data;
    }

    void *operator new(size_t size) {
        size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 ); //pretvaranje u blokove
        return MemoryAllocator::mem_alloc(size);
    }

    void *operator new[](size_t size) {
        size = size % MEM_BLOCK_SIZE == 0 ? size / MEM_BLOCK_SIZE : (size / MEM_BLOCK_SIZE + 1 ); //pretvaranje u blokove
        return MemoryAllocator::mem_alloc(size);
    }

    void operator delete(void *p) noexcept { MemoryAllocator::mem_free(p); }

    void operator delete[](void *p) noexcept { MemoryAllocator::mem_free(p); }
};

#endif
