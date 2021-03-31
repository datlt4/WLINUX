# Learn Makefiles
<!-- [![Refence](https://upload.wikimedia.org/wikipedia/commons/thumb/c/cb/Emoji_u1f601.svg/128px-Emoji_u1f601.svg.png)](https://makefiletutorial.com/) -->
[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/2d/Reference-com_logo.svg/1280px-Reference-com_logo.svg.png" height="15">](https://makefiletutorial.com/)

## Getting Started <a name="getting_started"></a>

### Why do Makefiles exist? <a name="why_do_makefiles_exist"></a>

Makefiles được sử dụng để quyết định xem những phần nào trong 1 chương trình lớn cần được biên dịch lại. Nếu các file's dependencies thay đổi, thì file đó cần được biên dịch lại.

### Makefile Syntax <a name="makefile_syntax"></a>

Một Makefile bao gồm một tập các luật, một luật thì thường có dạng như sau:
```
targets: prerequisites
	command
	command
	command
```
- `targets`: tên files, tách biệt bằng dấu cách, thường thì 1 file 1 rule.
- `commands`: chuỗi các bước sử dụng để make `targets`
- `prerequisites`: cũng là các filenames, tách biệt bởi dấu cách, đây là những file cần tồn tại trước khi các `command` run.

### Beginner Examples <a name="beginner_example"></a>

`Makefile` dưới đây gồm 3 rules. Khi ta chạy `make blah`, nó sẽ build một chương trình có tên là `blah` theo một chuỗi các bước.

- `Make` có target là `blah`, nên nó sẽ tìm target của n đầu tiên.
- `blah` yêu cầu `blah.o`, nên `make` sẽ tìm target `blah.o`.
- `blah.o` yêu cầu `blah.c`, nên `make` sẽ tìm target `blah.c`.
- `blah.c` không có dependencies, nên nó sẽ thực hiện lệnh `echo`.
- Lệnh `cc -c` sau đó sẽ chạy, vì tất cả các dependencies của `blah.o` đã thỏa mãn.
- Lệnh `cc` sau đó sẽ chạy, vì tất cả các dependencies của `blah` đã thỏa mãn.
- `blah` đã được complied.

```
blah: blah.o
	cc blah.o -o blah # Runs third

blah.o: blah.c
	cc -c blah.c -o blah.o # Runs second

blah.c:
	echo "int main() { return 0; }" > blah.c # Runs first
```

### Variables

```
files = file1 file2
some_file: $(files)
	echo "Look at this variable: " $(files)
	touch some_file

file1:
	touch file1

file2:
	touch file2

clean:
	rm -f file1 file2 some_file
```

`make`

`make clean`

## Targets

### The all target

```
all: one two three

one:
	touch one
two:
	touch two
three:
	touch three

clean:
	rm -f one two three
```

### Multiple targets

```
all: f1.o f2.o

f1.o f2.o:
	touch $@
```

## Automatic Variables and Wildcards

### * Wildcard
### % Wildcard
### Automatic Variables
```
hey: one two
	# Outputs "hey", since this is the first target
	echo $@

	# Outputs all prerequisites newer than the target
	echo $?

	# Outputs all prerequisites
	echo $^

	touch hey

one:
	touch one

two:
	touch two

clean:
	rm -f hey one two
```

## Fancy Rules

### Static Pattern Rules

Đây là một loại cú pháp của một loại rule mới gọi là static pattern.
```
targets ...: target-pattern: prereq-patterns ...
	commands
```

Bản chất là target đã cho sẽ match với target-pattern (qua % wildcard). Thường được sử dụng đẻ complie `.c` thành `.o`.

>*manual way*
```
objects = foo.o bar.o all.o
all: $(objects)

# These files compile via implicit rules
foo.o: foo.c
bar.o: bar.c
all.o: all.c

all.c:
	echo "int main() { return 0; }" > all.c

%.c:
	touch $@

clean:
	rm -f *.c *.o all
```

>*efficient way*

```
objects = foo.o bar.o all.o
all: $(objects)

$(objects): %.o: %.c

all.c:
	echo "int main() { return 0; }" > all.c

%.c:
	touch $@

clean:
	rm -f *.c *.o all
```

### Static Pattern Rules and Filter

```
obj_files = foo.result bar.o lose.o
src_files = foo.raw bar.c lose.c

all: $(obj_files)

$(filter %.o,$(obj_files)): %.o: %.c
	echo "target: $@ prereq: $<"
$(filter %.result,$(obj_files)): %.result: %.raw
	echo "target: $@ prereq: $<" 

%.c %.raw:
	touch $@

clean:
	rm -f $(src_files)
```

### Implicit Rules

Một số luật ngầm:
- Complie một C program: `.o` file sẽ được tạo tự động từ file `.c` với lệnh `$(CC) -c $(CPPFLAGS) $(CFLAGS)`.
- Complie một C++ program: `.o` file sẽ được tạo tự động từ file `.cpp` với lệnh `$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)`.
- Linking a single object file: `n` file sẽ được tạo tự động từ file `n.o` với lệnh `$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)`

Các biến sử dụng trong các luật ngầm này là:

- `CC`: chương trình complie C program.
- `CXX`: chương trình complie C++ program.
- `CFLAGS`: Extra flags to give to the C compiler.
- `CXXFLAGS`: Extra flags to give to the C++ compiler.
- `CPPFLAGS`: Extra flags to give to the C preprosessor
- `LDFLAGS`: Extra flags to give to compilers when they are supposed to invoke the linker

```
CC = gcc # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info

# Implicit rule #1: blah is built via the C linker implicit rule
# Implicit rule #2: blah.o is built via the C compilation implicit rule, because blah.c exists
blah: blah.o

blah.c:
	echo "int main() { return 0; }" > blah.c

clean:
	rm -f blah*
```

### Pattern Rules
```
# Define a pattern rule that compiles every .c file into a .o file
%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
```

### Error handling with `-k`, `-i`, and `-`

Add `-k` when running make to continue running even in the face of errors. Helpful if you want to see all the errors of Make at once.

Add a `-` before a command to suppress the error

Add `-i` to make to have this happen for every command.

## Makefile Cookbook

```
# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := final_program

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
```

# Introduction to CMake by Example

[<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/2d/Reference-com_logo.svg/1280px-Reference-com_logo.svg.png" height="15">](http://derekmolloy.ie/hello-world-introductions-to-cmake/#)

[<img src= "https://aimansoliman.files.wordpress.com/2020/02/github_owler_20180612_070358_original.png" height="25">](https://github.com/derekmolloy/exploringBB/tree/version2/extras/cmake)

## Introduction

Makefile được sử dụng phổ biến trong các project để tự động hóa quá trình build. Tuy nhiên trong nhiều trường hợp, Makefile trở nên quá phức tạp, cụ thể khi build project chứa nhiều sub directories, hoặc project deploy trên nhiều nền tảng.

Khi này CMake trở thành một công cụ để generate cross-platform Makefile.

## Example 1: The Hello World Example

Trong ví dụ này, đơn giản là build chương trình từ file `HelloWorld.cpp`.

```
/* HelloWorld.cpp */
#include<iostream>

int main(int argc, char *argv[]){
	std::cout << "Hello World!" << std::endl;
	return 0;
}
```

`CMakeList.txt` nằm trong cùng đường dẫn với source và có nội dung:

```
cmake_minimum_required(VERSION 2.8.9)
project (hello)
add_executable(hello helloworld.cpp)
```

- Line 1: version tối thiểu của CMake cho this project.
- Line 2: tên project.
- Line 3: add_executable(param1, param2)

execute the `cmake` command để tạo ra `Makefile`

```
cmake .
```

khi `Makefile` được tạo tự động, chạy lệnh `make` để build project.

```
make
```

## Example 2: A Project with Directories

Khi project lớn dần, cần phải tổ chức project thành các sub-directories.

```
.
|-- CMakeLists.txt
|-- build
|-- include
|   \-- Student.h
\-- src
	|-- Student.cpp
	\-- mainapp.cpp
```

Tạo một `build` directory là nơi chứa các binary executable và các files trung gian cần cho việc build.

```
cmake_minimum_required(VERSION 2.8.9)
project(directory_test)

#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(testStudent ${SOURCES})
```

- `include_directories()` được sử dụng để  include các header files vào môi trường build.
- `set(SOURCES … )` set biến môi trường `$(SOURCE)` cái mà gồm tên của các src file `.cpp` trong project.
- `file()` sử dụng để thêm source files vào project và gàn nó vào biến `$(SOURCE)`. `GLOB` hoặc `GLOB_RECURSE` được dùng để tạo ra một list các files thỏa mãn biểu thức globbing.
- `add_executable()` sử dụng biển `$(SOURCE)` để  build testStudent program.

```
cd build
cmake ..
make
```

## Example 3: Building a Shared Library (.so)

```
studentlib_shared/
|-- CMakeLists.txt
|-- build
|-- include
|   \-- Student.h
\-- src
    \-- Student.cpp
```

```
cmake_minimum_required(VERSION 2.8.9)
project(directory_test)
set(CMAKE_BUILD_TYPE Release)

#Bring the headers, such as Student.h into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(testStudent SHARED ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS testStudent DESTINATION /usr/lib)
```

- `set(CMAKE_BUILD_TYPE Release)` set build type là `release` build.
- `add_executable()` used in previous examples.
- `add_library()` build thư viện thành shared library với cờ `SHARED`, (các option khác là `STATIC` và `MODULE`)
- `install()` để  xác định nơi cài file `.so` (e.g: `/usr/lib`). chạy `sudo make install` cho deployment.

```
cd build
cmake ..
make
```

Ta có thể sử dụng lệnh `ldd` để hiển thị các shared library dependencies:
```
$ ldd libtestStudent.so
linux-vdso.so.1 (0x00007ffd2fc83000)
libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f9c3d3ea000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f9c3cff9000)
libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f9c3cc5b000)
/lib64/ld-linux-x86-64.so.2 (0x00007f9c3d976000)
libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f9c3ca43000)
```

## Example 4: Building a Static Library (.a)

A statically-linked library được tạo - bao gồm tất cả các code và các thư viện liên quan.

```
cmake_minimum_required(VERSION 2.8.9)
project(directory_test)
set(CMAKE_BUILD_TYPE Release)

#Bring the headers, such as Student.h into the project
include_directories(include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#Generate the static library from the sources
add_library(testStudent STATIC ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS testStudent DESTINATION /usr/lib)
```

```
cd build
cmake ..
make
```

## Example 5: Using a Shared or Static Library
```
/* libtest.cpp */
#include"Student.h"

int main(int argc, char *argv[])
{
	Student s("Joe");
	s.display();
	return 0;
}
```


### Using Shared Library

```
cmake_minimum_required(VERSION 2.8.9)
project (TestLibrary)

# For the shared library:
set ( PROJECT_LINK_LIBS libtestStudent.so )
link_directories( ../studentlib_shared/build )
include_directories( ../studentlib_shared/include )

add_executable(libtest libtest.cpp)
target_link_libraries(libtest ${PROJECT_LINK_LIBS} )
```

### Using Static Library

```
cmake_minimum_required(VERSION 2.8.9)
project (TestLibrary)

# For the static library:
set ( PROJECT_LINK_LIBS libtestStudent.a )
link_directories( ../studentlib_static/build )
include_directories( ../studentlib_static/include )

add_executable(libtest libtest.cpp)
target_link_libraries(libtest ${PROJECT_LINK_LIBS} )
```

# Note

## OpenCV

- `CMakeLists.txt`

```
cmake_minimum_required(VERSION 2.8)
project(opencv)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(app main.cpp)
target_link_libraries(app ${OpenCV_LIBS})
```

## Libtorch

- `CMakeLists.txt`

```
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(Project)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(app main2.cpp)
target_link_libraries(app "${TORCH_LIBRARIES}")
set_property(TARGET app PROPERTY CXX_STANDARD 14)
```

## ESP-IDF

- `Makefile`

```
PROJECT_NAME := new_milestone
include $(IDF_PATH)/make/project.mk
```

- `CMakeLists.txt`
```
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(new-milestone)
```

