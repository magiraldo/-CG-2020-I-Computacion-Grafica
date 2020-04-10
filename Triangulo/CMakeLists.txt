cmake_minimum_required(VERSION "3.17.0")

project("Triangulo")

add_executable("${PROJECT_NAME}" "Source.cpp")

install(TARGETS "${PROJECT_NAME}" DESTINATION bin) #${CMAKE_INSTALL_PREFIX}/bin
install(FILES "Source.cpp" DESTINATION src) 	   #${CMAKE_INSTALL_PREFIX}/src
