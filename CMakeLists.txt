cmake_minimum_required(VERSION 3.13)

file(GLOB Acquisitor_src
	"src/*.c")

project(serial_project)
add_compile_options(-Wall -Wpedantic -Werror)
add_executable(Acquisitor ${Acquisitor_src})
