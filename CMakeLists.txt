cmake_minimum_required(VERSION 3.13)

file(GLOB serial_src
	"src/*.c")

project(serial_project)
add_compile_options(-Wall -Wpedantic -Werror)
add_executable(serial ${serial_src})
