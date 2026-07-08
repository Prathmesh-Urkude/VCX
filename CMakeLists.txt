cmake_minimum_required(VERSION 3.20)

project(vcx VERSION 1.0 LANGUAGES CXX)

# -----------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

# -----------------------
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

# -----------------------
add_executable(vcx ${SOURCES})

# -----------------------
target_include_directories(vcx PRIVATE include)

# -----------------------
target_link_libraries(vcx PRIVATE
    ZLIB::ZLIB
    OpenSSL::Crypto
)

# -----------------------
if(MSVC)
    target_compile_options(vcx PRIVATE /W4)
else()
    target_compile_options(vcx PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()