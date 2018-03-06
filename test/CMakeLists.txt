find_package(CppUTest REQUIRED)

add_executable(tests
	test-fitness.cpp
	test-grade.cpp
	main.cpp
)

target_link_libraries(tests
	school-grade
	${CppUTest_LIBRARIES}
)
