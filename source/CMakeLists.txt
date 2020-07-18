file(GLOB_RECURSE SRC_CHAI "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
set(SRC_PROTO
    ${SRC_CHAI}
   )

add_executable(chai ${SRC_PROTO})

target_compile_definitions(chai PRIVATE CHAISCRIPT_NO_THREADS)
target_include_directories(chai PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(chai
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_link_libraries(chai
                      pthread
                      dl)
cotire(chai)
