find_package(CppUTest REQUIRED)

add_executable(tests
	test-fitness.cpp
	main.cpp
)

target_link_libraries(tests
	school-grade
	${CppUTest_LIBRARIES}
)
