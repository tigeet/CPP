# cmake_minimum_required(VERSION 3.16.0)
# project(project_name)

# # add_subdirectory(lib)
# add_executable(main  main.cpp)
# target_include_directories(main PUBLIC ~/Downloads/curl/include/curl)
# # target_link_directories(${PROJECT_NAME} PRIVATE lib)
# target_link_libraries(main ~/Downloads/curl/lib/libcurl.a)


cmake_minimum_required(VERSION 3.16.0)

project(project_name)



include_directories(~/Downloads/json-develop/single_include/)
include_directories(~/Downloads/curl/include/)
link_directories(~/Downloads/curl/lib/)

add_executable(demo main.cpp)

target_link_libraries(demo curl)