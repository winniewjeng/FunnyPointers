
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;
typedef int T;

T* initialize(int& size, int& capacity);
T* delete_repeats(T* list, int& size, int& capacity);
T* find(T* a, int size, const T& key);
T* allocate(int capacity);
void copy_list(T *dest, T* src, int many_to_copy);
void shift_left(T* list, int& size, T* shifter);
void print_list(T* list, int size);

//9.2 delete repeats

int main() {

    int size = 10000;
    int capacity = 20000;

    T* a = initialize(size, capacity);

    delete_repeats(a, size, capacity);

    print_list(a, size);

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

T* delete_repeats(T* list, int& size, int& capacity) {
    //walker points to the first element of list
    T* walker = list;
    //traverse through the entire list
    while (walker != list + size) {
        //if dereferenced values * are the same but addresses are different, a duplicate is detected
        if (walker != find(list, size, *walker)) {
            //shift everything to the left starting from the duplicate position
            T*shifter = walker;
            shift_left(list, size, shifter);
        } else {
            walker++;
        }
    }
    //if size is less than 1/4 of the capacity, truncate the capacity by half and then allocate new memory with reduced space.
    if ((capacity / 4) >= size) {
        capacity /= 2;
        //call the allocate() function to allocate a memory with less space
        T* destination = allocate(capacity);
        //call the copy_list() function to copy items in list to the memory with less space
        copy_list(destination, list, size);
    }

    return list;
}

T* find(T* a, int size, const T& key) {

    T* walker = a;

    while (walker != a + size) {
        if (*walker == key) {
            return walker;
        }
        walker++;
    }
    return nullptr;
}

T* allocate(int capacity) {
    return new T[capacity];
}

void copy_list(T *dest, T* src, int many_to_copy) {

    for (int i = 0; i < many_to_copy; i++) {
        *(dest + i) = *(src + i);
    }

    src = dest;
}

void shift_left(T* list, int& size, T* shifter) {
    //don't grab the garbage value, hence (size-1)
    while (shifter < list + (size - 1)) {
        *shifter = *(shifter + 1);
        shifter++;
    }
    //decrement the list size every time a duplicate is replaced
    size--;
}

void print_list(T* list, int size) {

    T* walker = list;
    while (walker != list + size) {
        cout << *walker << " ";
        walker++;
    }
    cout << endl;
}