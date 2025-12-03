set(target ${MP2_TESTS})

file(GLOB hdrs "${MP2_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty")

add_executable(${target} ${srcs})
target_sources(${target} PRIVATE ${hdrs})

target_include_directories(${target} PRIVATE ${MP2_INCLUDE})
target_link_libraries(${target} gtest)
