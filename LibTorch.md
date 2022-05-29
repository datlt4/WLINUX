# Install LibTorch for C++

```bash
$ wget https://download.pytorch.org/libtorch/cu101/libtorch-shared-with-deps-1.6.0%2Bcu101.zip
$ unzip libtorch-shared-with-deps-1.6.0+cu101.zip
```

**_Note_** that the above link has libtorch 1.6.0. If you would like to download an other GPU or CPU-only libtorch, find the right link in the link selector on https://pytorch.org

# Make Torch C++ project

```
example-project/
├── CMakeLists.txt
└── main.cpp
```

## Example code

```cpp
#include <torch/torch.h>

int main()
{
    torch::Device device(torch::kCPU);
    torch::Tensor tensor = torch::zeros({2, 2});
    std::cout << tensor << std::endl;

    if (torch::cuda::is_available())
    {
        std::cout << "CUDA is available! " << std::endl;
        device = torch::kCUDA;
    }

    torch::Tensor test_gpu_tensor = tensor.to(device);

    std::cout << test_gpu_tensor << std::endl;
    return 0;
}
```

## CMakeLists

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(torch-app)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(torch-app main.cpp)
target_link_libraries(torch-app "${TORCH_LIBRARIES}")
set_property(TARGET torch-app PROPERTY CXX_STANDARD 14)

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET torch-app
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        ${TORCH_DLLS}
                        $<TARGET_FILE_DIR:torch-app>)
endif (MSVC)
```

## Build the application in project folder

```bash
export LIB_TORCH="~/libtorch"
mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=$LIB_TORCH ..
# cmake --build . --config Release
make
./torch-app
```
