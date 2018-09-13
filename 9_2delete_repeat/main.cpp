
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;
typedef int T;

T* remove_entry(T* list, const T&, int&, int&);
T* add_entry(T*, const T&, int&, int&); //NOT YET IMPLEMENTED
void shift_left(T*, int&, T*);
T* delete_repeats(T*, int&, int&);
T* allocate(int);
T* copy_list(T*, T*, int); //How can it be a void function????
T* find(T*, int, int);

int main() {

    int size = 10000;
    int capacity = 20000;

    T* a = new T[size];

    for (int i = 0; i < size; i++) {
        *(a + i) = rand() % 10;
    }

    //    T* b = delete_repeats(a, size, capacity);
    T* c = remove_entry(a, 3, size, capacity);
    c = add_entry(a, 3, size, capacity);

    T* walker = c;
    while (walker != c + size) {
        cout << *walker << " ";
        walker++;
    }
    cout << endl;
    cout << "capacity " << capacity << endl;
    cout << "size " << size << endl;

    return 0;
}

T* add_entry(T* list, const T& new_entry, int& size, int& capacity) {

    //resize if the list capacity is full
    if (size + 1 > capacity) {
        capacity *= 2;
        T* destination = allocate(capacity);
        list = copy_list(destination, list, size);
    }
    //add new_entry at the end of the list, where the size is.
    T* placer = list + size;
    *placer = new_entry;
    //increment the size by 1
    size++;

    return list;
}

T* remove_entry(T* list, const T& delete_me, int& size, int& capacity) {

    //resize the list capacity if needed
    if (size - 1 <= capacity / 4) {
        capacity /= 2;
        T* destination = allocate(capacity);
        list = copy_list(destination, list, size);
    }
    //take out delete_me. Traverse through list. If delete_me is found, mark its walker location
    T* walker = list;
    T* shifter;
    while (walker != list + size) {
        if (*walker == delete_me) {
            shifter = walker;
            //shift everything to left
            shift_left(list, size, shifter);
        }
        walker++;
    }
    return list;
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

T* allocate(int capacity) {
    return new T[capacity];
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
        list = copy_list(destination, list, size);
    }

    return list;
}

T* copy_list(T *dest, T* src, int many_to_copy) {

    for (int i = 0; i < many_to_copy; i++) {
        *(dest + i) = *(src + i);
    }
    //release unused memory
    delete[] src;

    return dest;
}

T* find(T* a, int size, int key) {

    T* walker = a;

    while (walker != a + size) {
        if (*walker == key) {
            return walker;
        }
        walker++;
    }
    return nullptr;
}