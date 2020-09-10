## Environment

    Windows 10 (64-bit)
    Visual Studio 2019

## Step `1`: Download and extract the pre-built library

    Download the latest binary from opencv's Github repository
    [OpenCV 4.1.2](https://github.com/opencv/opencv/releases/download/4.1.2/opencv-4.1.2-vc14_vc15.exe)
    [OpenCV 3.4.6](https://github.com/opencv/opencv/releases/download/3.4.6/opencv-3.4.6-vc14_vc15.exe)

## Step `2`: Add to environment variable

    add to Path -   C:\opencv\build\x64\vc15\bin

## Step `3`: Set platform target to x64
Pre-built binaries are built for x64 Windows platforms.

## Step `4`: Add to Include Directories
Tell the compiler how the OpenCV library looks. This is done by providing a path to the header files `build/include`.

    Project → YourProjectName Properties → go to VC++ Directories → <Edit…> in Include Directories → add -  C:\opencv\build\include

## Step `5`: Add to Library Directories
Tell the linker where it can find the lib files for different modules.

    Project → YourProjectName Properties → go to VC++ Directories → <Edit…> in Library Directories → add -  C:\opencv\build\x64\vc15\bin

## Step `6`: Add Additional Dependencies
List `opencv_world`.

    Project → YourProjectName Properties → go to Linker → Input → <Edit…> in Additional Dependencies → add -  opencv_world346d.dll