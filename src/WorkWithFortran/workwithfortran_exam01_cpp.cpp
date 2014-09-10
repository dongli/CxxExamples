#include <iostream>
#include <vector>

using namespace std;

class Foo {
    vector<int> data;
public:
    Foo() {}
    ~Foo() {}

    void setData(int n, int *data) {
        this->data.resize(n);
        for (int i = 0; i < n; ++i) {
            this->data[i] = data[i];
        }
    }

    void printData() {
        for (int i = 0; i < data.size(); ++i) {
            cout << data[i] << endl;
        }
    }
};

Foo *foo;

extern "C" {

void foo_init() {
    foo = new Foo;
}

void foo_set_data(int *n, int *data) {
    foo->setData(*n, data);
}

void foo_print_data() {
    foo->printData();
}

}
