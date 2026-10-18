# general info
cmake_minimum_required(VERSION 4.1.0)
project(Endianness VERSION 1.0.0 LANGUAGES CXX)


#cpp options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Build with ASan (+UBSan on GCC/Clang)" OFF)
if(ENABLE_SANITIZERS)
	if(MSVC)
		add_compile_options(/fsanitize=address)
	else()
		add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
		add_link_options(-fsanitize=address,undefined)
	endif()
endif()	

add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
	add_subdirectory(tests)
endif()

