add_library(endianness_warnings INTERFACE)
add_library(Endianness::warnings ALIAS endianness_warnings)

if(MSVC)
	target_compile_options(endianness_warnings INTERFACE /W4 /WX /external:W0)
else()
	target_compile_options(endianness_warnings INTERFACE -Wall -Wextra -Wpedantic -Werror)
endif()

add_library(endianness INTERFACE)
add_library(Endianness::endianness ALIAS endianness)
target_include_directories(endianness INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(endianness INTERFACE cxx_std_23)

add_executable(endianness_app main.cpp)
target_link_libraries(endianness_app PRIVATE Endianness::endianness Endianness::warnings)