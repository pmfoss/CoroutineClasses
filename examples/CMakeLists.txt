
SET(EXAMPLE_SRC_FILES
   DerivedCoTask.cpp
   SimpleCoTask.cpp
   SimpleCoTaskWithAwait.cpp
   SimpleCoTaskWithReturn.cpp
   SimpleCoGenerator.cpp)

foreach(EXAMPLE_SRC_FILE IN LISTS EXAMPLE_SRC_FILES)
    get_filename_component(OUTPUT_FILE ${EXAMPLE_SRC_FILE} NAME_WLE)
    add_executable(${OUTPUT_FILE} ${EXAMPLE_SRC_FILE})
endforeach()