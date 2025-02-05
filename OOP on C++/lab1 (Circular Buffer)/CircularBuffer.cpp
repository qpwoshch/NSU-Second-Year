#include "CircularBuffer.h"
#include <cstring>
#include <string>
#include <sstream>
#include <vector>


std::string CircularBuffer::toString() const {
    std::ostringstream oss;
    int index = head;
    for (size_t i = 0; i < buffer_size; ++i) {
        oss << buffer[index];
        if (i < buffer_size - 1) {
            oss << "";
        }
        index = (index + 1) % buffer_capacity;
    }
    return oss.str();
}

std::string CircularBuffer::LinerizeToString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < buffer_size; ++i) {
        oss << buffer[i];
        if (i < buffer_size - 1) {
            oss << "";
        }
    }
    return oss.str();
}

int index(int i, int head, size_t buffer_capacity) {
    while (i < 0) {
        i+=buffer_capacity;
    }
    int index = (i + head) % buffer_capacity;
    return index;
}


CircularBuffer::CircularBuffer() : buffer(nullptr), head(0), tail(0), buffer_size(0), buffer_capacity(0) {
}

CircularBuffer::~CircularBuffer() {
    if (buffer) {
        delete[] buffer;
        buffer = nullptr;
    }
}

CircularBuffer::CircularBuffer(const CircularBuffer & cb) : buffer_size(cb.buffer_size), buffer_capacity(cb.buffer_capacity), head(cb.head), tail(cb.tail) {
    buffer = new value_type[buffer_capacity];
    std::memcpy(buffer, cb.buffer, buffer_capacity * sizeof(value_type));
}

CircularBuffer::CircularBuffer(int capacity) : head(0), tail(0), buffer_size(0), buffer_capacity(capacity) {
    if (capacity > 0) {
        buffer = new value_type[capacity];
        std::memset(buffer, 0, capacity);
    } else {
        buffer = nullptr;
        throw::std::logic_error("Размерность <=0");
    }
}

CircularBuffer::CircularBuffer(int capacity, const value_type & elem) : head(0), tail(0), buffer_size(capacity), buffer_capacity(capacity) {
    if (capacity > 0) {
        buffer = new value_type[capacity];
        for (int i = 0; i < capacity; i++) {
            buffer[i] = elem;
        }
        head = 0;
        tail = capacity-1;
    } else {
        buffer = nullptr;
        throw::std::logic_error("Размерность <=0");
    }
}


value_type & CircularBuffer::operator[](int i) {
    return buffer[index(i, head, buffer_capacity)];
}

const value_type & CircularBuffer::operator[](int i) const {
    return buffer[index(i, head, buffer_capacity)];
}

value_type & CircularBuffer::at(int i) {
    return buffer[index(i, head, buffer_capacity)];
}

const value_type & CircularBuffer::at(int i) const{
    return buffer[index(i, head, buffer_capacity)];
}

value_type & CircularBuffer::front() {
    return buffer[head];
}

value_type & CircularBuffer::back() {
    return buffer[tail];
}

const value_type & CircularBuffer::front() const {
    return buffer[head];
}

const value_type & CircularBuffer::back() const{
    return buffer[tail];
}

value_type * CircularBuffer::linearize() {
    if (buffer_size == 0) {
        throw::std::out_of_range("Буфер пуст!");
    }
    value_type* new_buffer = new value_type[buffer_capacity];
    for (int i = 0; i < buffer_size; i++) {
        new_buffer[i] = buffer[index(i, head, buffer_capacity)];
    }
    head = 0;
    tail = buffer_size - 1;
    delete[] buffer;
    buffer = new_buffer;
    return buffer;
}

bool CircularBuffer::is_linearized() const {
    return (head == 0) && (tail == buffer_size-1);
}

void CircularBuffer::rotate(int new_begin) {
    value_type* new_buffer = new value_type[buffer_capacity];
    new_begin = (new_begin % buffer_capacity + buffer_capacity) % buffer_capacity;
    for (int i = 0; i < buffer_size; i++) {
        new_buffer[index(i, head, buffer_capacity)] = buffer[index(i + new_begin, head, buffer_capacity)];
    }
    head = (head + new_begin) % buffer_capacity;
    tail = (head + buffer_size) % buffer_capacity;
    delete[] buffer;
    buffer = new_buffer;
}

int CircularBuffer::size() const {
    return buffer_size;
}

bool CircularBuffer::empty() const {
    return buffer_size == 0;
}

bool CircularBuffer::full() const {
    return buffer_capacity == buffer_size;
}

int CircularBuffer::reserve() const {
    return buffer_capacity-buffer_size;
}

int CircularBuffer::capacity() const {
    return buffer_capacity;
}

void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity < 0) {
        throw ::std::logic_error("новая размерность < 0");
    }
    value_type* new_buffer = new value_type[new_capacity];
    if (buffer_capacity < new_capacity) {
        for (int i = 0; i < buffer_size; i++) {
            new_buffer[index(i, head, new_capacity)] = buffer[index(i, head, buffer_capacity)];
        }
    }
    else {
        for (int i = 0; i < new_capacity; i++) {
            new_buffer[index(i, head, new_capacity)] = buffer[index(i, head, buffer_capacity)];
        }
        buffer_size = new_capacity;
    }
    delete[] buffer;
    buffer = new_buffer;
    buffer_capacity = new_capacity;
}

void CircularBuffer::resize(int new_size, const value_type &item) {
    if (new_size < 0) {
        throw ::std::logic_error("новая размерность < 0");
    }
    if (new_size > buffer_capacity) {
        throw::std::logic_error("новая размерность > размера буффера");
    }
    value_type* new_buffer = new value_type[new_size];
    if (new_size > buffer_size) {
        for (int i = 0; i < buffer_size; i++) {
            new_buffer[index(i, head, new_size)] = buffer[index(i, head, buffer_capacity)];
        }
        for (int i = buffer_size; i < new_size; i++) {
            new_buffer[index(i, head, buffer_capacity)] = item;
        }
    }
    else {
        for (int i = 0; i < new_size; i++) {
            new_buffer[index(i, head, buffer_capacity)] = buffer[index(i, head, buffer_capacity)];
        }
    }
    delete[] buffer;
    buffer = new_buffer;
    buffer_size = new_size;
    tail = (tail + new_size) % buffer_capacity;
}

CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb) {
    delete[] buffer;
    buffer_size = cb.buffer_size;
    buffer_capacity = cb.buffer_capacity;
    head = cb.head;
    tail = cb.tail;

    buffer = new value_type[buffer_capacity];
    for (int i = 0; i < buffer_capacity; ++i) {
        buffer[i] = cb.buffer[i];
    }
    return *this;
}


void CircularBuffer::swap(CircularBuffer & cb) {
    std::swap(buffer, cb.buffer);
    std::swap(head, cb.head);
    std::swap(tail, cb.tail);
    std::swap(buffer_size, cb.buffer_size);
    std::swap(buffer_capacity, cb.buffer_capacity);
}


void CircularBuffer::push_back(const value_type &item) {
    if (buffer[tail] == 0) {
        buffer[tail] = item;
    }
    else {
        if ((tail + 1) % buffer_capacity == head) {
            head = (head + 1) % buffer_capacity;
        }
        tail = (tail + 1) % buffer_capacity;
        buffer[tail] = item;
    }
    if (buffer_size < buffer_capacity) {
        buffer_size++;
    }
}

void CircularBuffer::push_front(const value_type &item) {
    if (buffer[head] == 0) {
        buffer[head] = item;
    }
    else {
        if ((head - 1 + buffer_capacity) % buffer_capacity == tail) {
            tail = (tail - 1 + buffer_capacity) % buffer_capacity;
        }
        head = (head - 1 + buffer_capacity) % buffer_capacity;
        buffer[head] = item;
    }
    if (buffer_size < buffer_capacity) {
        buffer_size++;
    }
}

void CircularBuffer::pop_back() {
    if (buffer_size == 0) {
        throw ::std::logic_error("Размерность равна 0");
    }
    buffer[tail] = 0;
    tail--;
    buffer_size--;
}

void CircularBuffer::pop_front() {
    if (buffer_size == 0) {
        throw ::std::logic_error("Размерность равна 0");
    }
    buffer[head] = 0;
    head++;
    buffer_size--;
}

void CircularBuffer::insert(int pos, const value_type & item) {
    buffer[index(pos, head, buffer_capacity)] = item;
}

void CircularBuffer::erase(int first, int last) {
    if (first > last) {
        throw ::std::logic_error("индекс первого элемента больше индекса второго элемента");
    }
    int elements_to_remove = last - first;
    int current = (head + last) % buffer_capacity;
    int end = (tail + 1) % buffer_capacity;
    while (current != end) {
        buffer[index(first, head, buffer_capacity)] = buffer[current];
        first = (first + 1) % buffer_capacity;
        current = (current + 1) % buffer_capacity;
    }
    tail = (tail + buffer_capacity - elements_to_remove) % buffer_capacity;
    buffer_size -= elements_to_remove;
    if (buffer_size == 0) {
        head = 0;
        tail = 0;
    }
}


void CircularBuffer::clear() {
    if (buffer) {
        for (int i = 0; i < buffer_size; ++i) {
            buffer[index(i, head, buffer_capacity)] = 0;
        }
    }
    head = 0;
    tail = 0;
    buffer_size = 0;
}

bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
    if (a.size() != b.size() ||
        a.capacity() != b.capacity()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[index(i, a[0], a.capacity())] != b[index(i, b[0], b.capacity())]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
    return !(a == b);
}

