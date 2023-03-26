# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "doc/cfl/html"
  "doc/home1/html"
  "doc/home2/html"
  "doc/home3/html"
  "doc/setup/html"
  "doc/test_all/html"
  )
endif()
