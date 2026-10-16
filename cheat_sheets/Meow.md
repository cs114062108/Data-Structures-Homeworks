# Meow Cheatsheet

### `hello.cpp`
```cpp
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]) {
    int exp = 2;
    if (argc != exp+1) {
        cerr << "Usage: " << argv[0] << " <name> <times>" << endl;
        return 1;
    }

    string name;
    name = argv[1];
    int times;

    try {
        // times = atoi(argv[2]);
        times = stoi(argv[2]);
        cout << "Name: " << name << ", " << "Times: " << times << endl;
    } catch (const invalid_argument &expc) {
        cerr << "Error: times should but integer, but got '" << argv[2] << "' instead" << endl;
        cerr << "Caught error message: " << expc.what() << endl;
        return 1;
    }

    for (int i = 0; i < times; i++) {
        cout << i+1 << ": " << "Hello, " << name << "!" << endl;
    }

    return 0;
}

```

<div style="page-break-after: always;"></div>

### `hi.cpp`
```cpp
#include <iostream>
using namespace std;

int main(void) {
    printf("Hi\n");
    return 0;
}

```

<div style="page-break-after: always;"></div>

### `meow.cpp`
```cpp
#include <iostream>
using namespace std;

int main(void) {
    printf("Meow\n");
    return 0;
}

```

<div style="page-break-after: always;"></div>

### `momo.cpp`
```cpp
#include <iostream>
using namespace std;

int main(void) {
    printf("Momo\n");
    return 0;
}

```

<div style="page-break-after: always;"></div>

