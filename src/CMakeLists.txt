file(GLOB source_file . *.cpp)

include_directories(
	${fullgene_SOURCE_DIR}/include
	)

add_executable(
	tests
	main.cpp
	Vertice_01.cpp
	Vertice.cpp
	Graph_01.cpp
	Graph.cpp
	functions.cpp
	graphExceptions.cpp
	graphPrinter.cpp
	graphGenerator.cpp
	)

TARGET_LINK_LIBRARIES(tests m)

install(TARGETS tests DESTINATION bin)
