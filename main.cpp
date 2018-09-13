
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
typedef string T;
template <typename T>

T* initialize(int& size, int& capacity);
T* add_entry(T* list, const T& new_entry, int& size, int& capacity);
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity);
T* allocate(int capacity);
T* shift_left(T* list, int& size, T* shifter);
void copy_list(T *dest, T* src, int many_to_copy);
T* search_entry(T* list, const T& find_me, int size);
void print_list(T* list, int size);
void test_string();


//9.2 add or remove entry

int main() {

    test_string();

    return 0;
}

T* initialize(int& size, int& capacity) {

    T* list = new T[size];
    T* walker = list;

    while (walker != list + size) {
        *walker = rand() % 10;
        walker++;
    }

    return list;
}

T* add_entry(T* list, const T& new_entry, int& size, int& capacity) {

    //resize if the list capacity is full
    if (size + 1 > capacity) {
        capacity *= 2;
        T* destination = allocate(capacity);
        copy_list(destination, list, size);
    }
    //add new_entry at the end of the list, where the size is.
    T* placer = list + size;
    *placer = new_entry;
    //increment the size by 1
    size++;

    return list;
}

//This function is faulty

T* remove_entry(T* list, const T& delete_me, int& size, int& capacity) {

    //resize the list capacity if needed
    if (size - 1 <= capacity / 4) {
        capacity /= 2;
        T* destination = allocate(capacity);
        copy_list(destination, list, size);
    }

    T* walker = list;
    T* shifter;
    //call search_entry() if it returns nullptr, then walker++. if it finds delete_me and returns the location of it, shift_left()
    while (walker != list + size) {
        if (search_entry(list, delete_me, size) == walker) {
            shifter = walker;
            shift_left(list, size, shifter);
            return list;
        } else {
            walker++;

        }
    }
    return list;
}

T* allocate(int capacity) {

    return new T[capacity];
}

T* shift_left(T* list, int& size, T* shifter) {
    //don't grab the garbage value, hence (size-1)
    while (shifter < list + (size - 1)) {
        *shifter = *(shifter + 1);
        shifter++;
    }
    //decrement the list size every time a duplicate is replaced
    size--;

    return list;
}

void copy_list(T *dest, T* src, int many_to_copy) {

    for (int i = 0; i < many_to_copy; i++) {
        *(dest + i) = *(src + i);
    }
    src = dest;
}

T* search_entry(T* list, const T& find_me, int size) {
    //traverse down the list. If *walker == find_me, return location of find_me
    T* walker = list;
    while (walker != list + size) {
        if (*walker == find_me) {
            return walker;
        }
        walker++;
    }
    return nullptr;
}

void print_list(T* list, int size) {

    T* walker = list;
    while (walker != list + size) {
        cout << *walker << " ";
        walker++;
    }
    cout << endl;
}

void test_string() {

    int capacity = 3;
    int size = 0;

    T* list = allocate(capacity);
    list = add_entry(list, "One", size, capacity);
    print_list(list, size);

    list = add_entry(list, "Two", size, capacity);
    print_list(list, size);

    list = add_entry(list, "Three", size, capacity);
    print_list(list, size);

    list = add_entry(list, "Four", size, capacity);
    print_list(list, size);

    list = add_entry(list, "Five", size, capacity);
    print_list(list, size);

    cout << "Deleting One" << endl;

    list = remove_entry(list, "One", size, capacity);
    print_list(list, size);

    cout << "Deleting Three" << endl;

    list = remove_entry(list, "Three", size, capacity);
    print_list(list, size);

    cout << "Deleting Five" << endl;

    list = remove_entry(list, "Five", size, capacity);
    print_list(list, size);

}