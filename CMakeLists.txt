cmake_minimum_required(VERSION 3.6)
project(coiote_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp config.h CostMatrix.cpp Problem.cpp Solution.cpp SolutionCell.cpp ExceptionManager.cpp ExceptionManager.h Exceptions/Headers/IOException.hpp Exceptions/Headers/CoioteBaseException.hpp Exceptions/Implementations/IOException.cpp Exceptions/Headers/IOException.hpp Exceptions/Implementations/CoioteException.cpp Exceptions/Headers/CoioteException.hpp util.cpp util.hpp)

#file(GLOB SOURCE_FILES "*.cpp" "*.hpp" "*.h")

add_executable(coiote_project ${SOURCE_FILES})