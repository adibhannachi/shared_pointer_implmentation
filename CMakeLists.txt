project(easymile_test)
cmake_minimum_required(VERSION 3.10.2)
include_directories(include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)

#delete cmake genereted files
IF (UNIX)
  ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   cmake.check_cache
   *.cmake
   Makefile
   src/Makefile
   test/Makefile
   CMakeFiles
   src/CMakeFiles
   test/CMakeFiles
   cmake_install.cmake
   src/cmake_install.cmake
   test/cmake_install.cmake
   src/libshared_ptr.a
   core core.*
   gmon.out
   *~
   bin/test_shared_ptr
  )
  
  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean  
  )
ENDIF(UNIX)
