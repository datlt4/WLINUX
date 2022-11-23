[Source](https://ilyas-hamadouche.medium.com/c-package-management-with-conan-introduction-8c7bd928c009)

# Introduction

- Conan is a free open-source (MIT) package manager developed for C and C++. It is similar to NuGet and npm for .NET and JavaScript respectively. It can run in any operating system that supports `Python`. This includes Linux, Mac, as well as Windows.
- Because there is no standard package manager for C++ yet, Conan is trying to be the one. The tool recently has got more attention from the community and gained trust from big companies such as Huawei, Keysight, and Mercedes-Benz.

# Install

```bash
python3 -m pip install conan
```

The following choices are also valid:

- Arch (yay): `yay -S conan`
- Mac (HomeBrew): `brew install conan`
- Build the tool from the source code. See this [link](https://docs.conan.io/en/latest/installation.html#install-from-source) for more instructions.

# Conan in Action

- To see how Conan can be used to fetch and build packages, let’s have a simple C++ project that depends on a third-party library.

- To build the source code, we need to use Conan to get the SQLite package for us. We need first to know the name and version of the package we would like to use. The following command will display all the sqlite3 packages available on the remote server `conancenter`:

```bash
➜ conan search sqlite3* --remote=conancenter 
Existing package recipes:

sqlite3/3.29.0
sqlite3/3.30.1
    ...
sqlite3/3.39.4
sqlite3/3.40.0
```

<details>
  <summary>test_conan.cpp</summary>

```cpp
#include <iostream>
#include <sqlite3.h>

int main() {
  sqlite3 *db;
  int rc = sqlite3_open("test.db", &db);
  if (SQLITE_OK == rc) {
    std::cout << "Opened database successfully \n";
    sqlite3_close(db);
  } else {
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
  }
  return 0;
}
```

</details>

<details>
  <summary>conanfile.txt</summary>

```
[requires]
sqlite3/3.40.0

[generators]
cmake
```

</details>

<details>
  <summary>CmakeLists.txt</summary>

```Cmakefile
cmake_minimum_required (VERSION 3.8)

project(TestConan CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} test_conan.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
```

</details>

## Build

- Install and build the dependency library SQLite.

```bash
mkdir build
cd build
conan install ..
```

- Build source code
 
```bash
cmake ..
make
```

- Run
    
```bash
cd bin
./TestConan
```
