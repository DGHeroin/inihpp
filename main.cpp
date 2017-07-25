#include <iostream>
#include "inihpp.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "params error" << endl;
        return -1;
    }
    const char* file = argv[1];

    inihpp ini;
    if (!ini.parse(file)) {
        cout << "ini format error" << endl;
        return -1;
    }
    ini.set("", "new key", "\"new value\"");

    ini.save("test_dump.ini");
    cout << "global comment: " << ini.get("", "comment") << endl;
    cout << "database comment: " << ini.get("database", "comment") << endl;
    cout << "database no value: " << ini.get("database", "no value") << endl;
    cout << "no such section: " << ini.get("no section", "no value") << endl;

    return 0;
}
