
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;
//typedef string T;

template <typename T>
struct Functions {

    static T* initialize(int& size, int& capacity) {
        T* list = new T[size];
        T* walker = list;

        while (walker != list + size) {
            *walker = rand() % 10;
            walker++;
        }

        return list;
    }

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

    static void test_string() {
        int capacity = 3;
        int size = 0;

        cout << "test_string() is called: " << endl;
        T* list = allocate(list, capacity);
        list = add_entry(list, string("One"), size, capacity);
        print_list(list, size);

        list = add_entry(list, string("Two"), size, capacity);
        print_list(list, size);

        list = add_entry(list, string("Three"), size, capacity);
        print_list(list, size);

        list = add_entry(list, string("Four"), size, capacity);
        print_list(list, size);

        list = add_entry(list, string("Five"), size, capacity);
        print_list(list, size);

        cout << "--Deleting One--" << endl;

        list = remove_entry(list, string("One"), size, capacity);
        print_list(list, size);

        cout << "--Deleting Three--" << endl;

        list = remove_entry(list, string("Three"), size, capacity);
        print_list(list, size);

        cout << "--Deleting Five--" << endl;

        list = remove_entry(list, string("Five"), size, capacity);
        print_list(list, size);
    }

    static void test_int() {
        int intsize = 0;
        int intcap = 1;

        cout << "test_int() is called: " << endl;
        T* intlist = allocate(intlist, intcap);
        intlist = add_entry(intlist, 1, intsize, intcap);
        print_list(intlist, intsize);
        
        intlist = add_entry(intlist, 2, intsize, intcap);
        print_list(intlist, intsize);
        
        intlist = add_entry(intlist, 3, intsize, intcap);
        print_list(intlist, intsize);
        
        intlist = add_entry(intlist, 4, intsize, intcap);
        print_list(intlist, intsize);
        
        intlist = add_entry(intlist, 5, intsize, intcap);
        print_list(intlist, intsize);
        
        cout << "--Deleting 1--" << endl;
        
        intlist = remove_entry(intlist, 1, intsize, intcap);
        print_list(intlist, intsize);
        
        cout << "--Deleting 3--" << endl;
        
        intlist = remove_entry(intlist, 3, intsize, intcap);
        print_list(intlist, intsize);
        
        cout << "--Deleting 5--" << endl;
        
        intlist = remove_entry(intlist, 5, intsize, intcap);
        print_list(intlist, intsize);
        
    }
};


//9.2 add or remove entry

int main() {

    Functions<string>::test_string();
    cout << endl;
    Functions<int>::test_int();

    return 0;
}

//T* initialize(int& size, int& capacity) {
//
//    T* list = new T[size];
//    T* walker = list;
//
//    while (walker != list + size) {
//        *walker = rand() % 10;
//        walker++;
//    }
//
//    return list;
//}

//T* add_entry(T* list, const T& new_entry, int& size, int& capacity) {
//
//    //resize if the list capacity is full
//    if (size + 1 > capacity) {
//        capacity *= 2;
//        T* destination = allocate(list, capacity);
//        copy_list(destination, list, size);
//    }
//    //add new_entry at the end of the list, where the size is.
//    T* placer = list + size;
//    *placer = new_entry;
//    //increment the size by 1
//    size++;
//
//    return list;
//}

//T* remove_entry(T* list, const T& delete_me, int& size, int& capacity) {
//
//    //resize the list capacity if needed
//    if (size - 1 <= capacity / 4) {
//        capacity /= 2;
//        T* destination = allocate(list, capacity);
//        copy_list(destination, list, size);
//    }
//
//    T* walker = list;
//    T* shifter;
//    //call search_entry() if it returns nullptr, then walker++. if it finds delete_me and returns the location of it, shift_left()
//    while (walker != list + size) {
//        if (search_entry(list, delete_me, size) == walker) {
//            shifter = walker;
//            shift_left(list, size, shifter);
//            return list;
//        } else {
//            walker++;
//        }
//    }
//
//    return list;
//}

//T* allocate(T* list, int capacity) {
//
//    list = new T[capacity];
//    return list;
//}

//void copy_list(T *dest, T* src, int many_to_copy) {
//
//    for (int i = 0; i < many_to_copy; i++) {
//        *(dest + i) = *(src + i);
//    }
//
//    src = dest;
//}

//T* search_entry(T* list, const T& find_me, int size) {
//    //traverse down the list. If *walker == find_me, return location of find_me
//    T* walker = list;
//    while (walker != list + size) {
//        if (*walker == find_me) {
//            return walker;
//        }
//        walker++;
//    }
//
//    return nullptr;
//}

//T* shift_left(T* list, int& size, T* shifter) {
//    //don't grab the garbage value, hence (size-1)
//    while (shifter < list + (size - 1)) {
//        *shifter = *(shifter + 1);
//        shifter++;
//    }
//    //decrement the list size every time a duplicate is replaced
//    size--;
//
//    return list;
//}

//void print_list(T* list, int size) {
//
//    T* walker = list;
//    while (walker != list + size) {
//        cout << *walker << " ";
//        walker++;
//    }
//
//    cout << endl;
//}
//
//void test_string() {
//
//    int capacity = 3;
//    int size = 0;
//    int intsize = 0;
//    int intcap = 4;
//
//    T* list = allocate(list, capacity);
//    list = add_entry(list, string("One"), size, capacity);
//    print_list(list, size);
//
//    list = add_entry(list, string("Two"), size, capacity);
//    print_list(list, size);
//
//    list = add_entry(list, string("Three"), size, capacity);
//    print_list(list, size);
//
//    list = add_entry(list, string("Four"), size, capacity);
//    print_list(list, size);
//
//    list = add_entry(list, string("Five"), size, capacity);
//    print_list(list, size);
//
//    T* intlist = allocate(intlist, capacity);
//    intlist = add_entry(intlist, 40, intsize, intcap);
//    print_list(intlist, size);
//
//    cout << "Deleting One" << endl;
//
//    list = remove_entry(list, string("One"), size, capacity);
//    print_list(list, size);
//
//    cout << "Deleting Three" << endl;
//
//    list = remove_entry(list, string("Three"), size, capacity);
//    print_list(list, size);
//
//    cout << "Deleting Five" << endl;
//
//    list = remove_entry(list, string("Five"), size, capacity);
//    print_list(list, size);
//
//}