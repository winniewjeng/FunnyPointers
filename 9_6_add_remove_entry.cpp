
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

template <typename T>
struct List {
    
    static T* add_entry(T* list, const T& new_entry, int& size, int& capacity) {
        //resize if the list capacity is full
        if (size + 1 > capacity) {
            capacity *= 2;
            T* destination = allocate(list, capacity);
            copy_list(destination, list, size);
        }
        //add new_entry at the end of the list, where the size is.
        T* placer = list + size;
        *placer = new_entry;
        //increment the size by 1
        size++;

        return list;
    }

    static T* remove_entry(T* list, const T& delete_me, int& size, int& capacity) {
        //resize the list capacity if needed
        if (size - 1 <= capacity / 4) {
            capacity /= 2;
            T* destination = allocate(list, capacity);
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

    static T* allocate(T* list, int capacity) {

        list = new T[capacity];
        return list;
    }

    static void copy_list(T *dest, T* src, int many_to_copy) {
        for (int i = 0; i < many_to_copy; i++) {
            *(dest + i) = *(src + i);
        }

        src = dest;
    }

    static T* shift_left(T* list, int& size, T* shifter) {
        //don't grab the garbage value, hence (size-1)
        while (shifter < list + (size - 1)) {
            *shifter = *(shifter + 1);
            shifter++;
        }
        //decrement the list size every time a duplicate is replaced
        size--;

        return list;
    }

    static T* search_entry(T* list, const T& find_me, int size) {
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

    static void print_list(T* list, int size) {
        T* walker = list;
        while (walker != list + size) {
            cout << *walker << " ";
            walker++;
        }
        cout << endl;
    }
    
    static void print_sz_ca(int size, int capacity) {
        cout << "size: " << size << endl;
        cout << "capacity: " << capacity << endl;
        cout << endl;
    }

    static void test_string() {
        
        int size = 0;
        int capacity = 1;

        cout << "test_string() is called: " << endl;
        T* list = allocate(list, capacity);
        list = add_entry(list, string("Adele"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        list = add_entry(list, string("Bill"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        list = add_entry(list, string("Char"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        list = add_entry(list, string("Domo"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        list = add_entry(list, string("Ebb"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        cout << "--Deleting Adele--" << endl;

        list = remove_entry(list, string("Adele"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        cout << "--Deleting Char--" << endl;

        list = remove_entry(list, string("Char"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        cout << "--Deleting Ebb--" << endl;

        list = remove_entry(list, string("Ebb"), size, capacity);
        print_list(list, size);
        print_sz_ca(size, capacity);

        delete[] list;
    }

    static void test_int() {
        int intsize = 0;
        int intcap = 1;

        cout << "test_int() is called: " << endl;
        T* intlist = allocate(intlist, intcap);
        intlist = add_entry(intlist, 1, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        intlist = add_entry(intlist, 2, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        intlist = add_entry(intlist, 3, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        intlist = add_entry(intlist, 4, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        intlist = add_entry(intlist, 5, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        cout << "--Deleting 1--" << endl;

        intlist = remove_entry(intlist, 1, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        cout << "--Deleting 3--" << endl;

        intlist = remove_entry(intlist, 3, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        cout << "--Deleting 5--" << endl;

        intlist = remove_entry(intlist, 5, intsize, intcap);
        print_list(intlist, intsize);
        print_sz_ca(intsize, intcap);

        delete[] intlist;

    }
};

//9.6 add or remove entry

int main() {

    List<string>::test_string();
    cout << endl;
    List<int>::test_int();

    return 0;
}