cmake_minimum_required(VERSION 3.13)

file(GLOB Main_src
	"src/*.c")

file(GLOB Acquisitor_src
	"src/acquisitor/*.c")

file(GLOB FileManager_src
	"src/fileManager/*.c")

file(GLOB Configurator_src
	"src/configurator/*.c")

file(GLOB Filter_src
	"src/filter/*.c")

file(GLOB Gpio_src
	"src/gpio/*.c")

project(Acquisitor_project)
add_compile_options(-Wall -Wpedantic -Werror)
add_executable(Acquisitor ${Main_src} ${Acquisitor_src} ${FileManager_src} ${Configurator_src} ${Filter_src} ${Gpio_src})

target_include_directories(Acquisitor PRIVATE src)
target_link_libraries(Acquisitor PRIVATE m)
