cmake_minimum_required(VERSION 3.19)
project(hpxFutures LANGUAGES CXX)

if(NOT DEFINED HPX_DIR)
  set(HPX_DIR "$ENV{HOME}/hpx-install/lib/cmake/HPX" CACHE PATH "HPX cmake dir")
endif()

find_package(HPX REQUIRED CONFIG)

add_executable(fibonacci_program src/fibonacci_local.cpp)
target_link_libraries(fibonacci_program
  PRIVATE
    HPX::hpx
    HPX::wrap_main
)

add_executable(interest_program src/interest_calculator.cpp)
target_link_libraries(interest_program
  PRIVATE
    HPX::hpx
    HPX::wrap_main
    HPX::iostreams_component 
)

add_executable(three_vectors_program src/three_vectors.cpp)
target_link_libraries(three_vectors_program
  PRIVATE
    HPX::hpx
    HPX::wrap_main
    HPX::iostreams_component
)
