#include "test.h"

using namespace std;

int main() {
    cout << "hello" << endl;
    Node a;
    a.val = 256;
    a.next = nullptr;
    cout << getVal(a) << endl;
}