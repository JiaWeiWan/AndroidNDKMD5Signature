# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/)
file(GLOB ADDR "${CMAKE_SOURCE_DIR}/src/main/cpp/*.cpp")
add_library( # Sets the name of the library. 设置库的名称。
             native-lib

             # Sets the library as a shared library. 将库设置为共享库。
             SHARED

             # Provides a relative path to your source file(s). 提供源文件的相对路径。
            ${ADDR})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable. 设置路径变量的名称。
              log-lib

              # Specifies the name of the NDK library that 指定NDK库的名称
              # you want CMake to locate. 你想让CMake定位。
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library. 指定目标库。
                       native-lib

                       # Links the target library to the log library 将目标库链接到日志库
                       # included in the NDK. 包括在NDK中。
                       ${log-lib} )