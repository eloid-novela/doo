cmake_minimum_required(VERSION 3.20)
project(doo VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(doo_lib
	src/app.cpp
	src/config.cpp
	src/limiter.cpp
	src/logger.cpp
	src/monitor.cpp
	src/network_controller.cpp
)
target_include_directories(doo_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(doo_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(doo src/main.cpp)
target_link_libraries(doo PRIVATE doo_lib)

install(TARGETS doo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES configs/doo.json DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/doo)
install(FILES systemd/doo.service DESTINATION lib/systemd/system)

if(BUILD_TESTING)
	add_executable(doo_tests tests/test_main.cpp)
	target_link_libraries(doo_tests PRIVATE doo_lib)
	target_compile_options(doo_tests PRIVATE -Wall -Wextra -Wpedantic)
	add_test(NAME doo_tests COMMAND doo_tests)
endif()
