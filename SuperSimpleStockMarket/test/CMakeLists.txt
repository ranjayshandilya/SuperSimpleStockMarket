cmake_minimum_required(VERSION 3.2.0)

set(This UnitTests)

set(Sources
    UnitTests.cpp
)

add_executable(${This} ${Sources})
include(CTest)

#Turn on multithreaded builds and turn off secure crt warnings
if(MSVC)
	set_target_properties(${This} PROPERTIES COMPILE_FLAGS /MP)
	target_compile_definitions(${This} PRIVATE -D_SCL_SECURE_NO_WARNINGS)
endif()

target_link_libraries(${This} PUBLIC
    gtest_main
    SimpleStockMarket
)

add_test(
    NAME ${This}
    COMMAND ${This}
)