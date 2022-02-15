# cmake_minimum_required(VERSION 3.16.0)
# project(project_name)

# # add_subdirectory(lib)
# add_executable(main  main.cpp)
# target_include_directories(main PUBLIC ~/Downloads/curl/include/curl)
# # target_link_directories(${PROJECT_NAME} PRIVATE lib)
# target_link_libraries(main ~/Downloads/curl/lib/libcurl.a)


cmake_minimum_required(VERSION 3.16.0)
project(project_name)



include_directories(D:/Desktop/json-develop/json-develop/single_include)

include_directories(D:/Desktop/Curl/include)
link_directories(D:/Desktop/Curl/lib)


include_directories(D:/Desktop/libssh/include)
link_directories(D:/Desktop/libssh/lib)

include_directories(D:/Desktop/zlib)


include_directories(D:/Desktop/brotli/include)
link_directories(D:/Desktop/brotli/lib)

include_directories(D:/Desktop/libgsasl/include)
link_directories(D:/Desktop/libgsasl/lib)

include_directories(D:/Desktop/nghttp/include)
link_directories(D:/Desktop/nghttp/lib)
# 
include_directories(D:/Desktop/libidn/include)
link_directories(D:/Desktop/libidn/lib)
# 

add_executable(demo main.cpp)


target_link_libraries(demo curl)
target_link_libraries(demo ssh2)
target_link_libraries(demo brotlienc-static)
target_link_libraries(demo gsasl)
target_link_libraries(demo nghttp2)
target_link_libraries(demo idn2)

