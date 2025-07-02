# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appChameleon_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appChameleon_autogen.dir\\ParseCache.txt"
  "appChameleon_autogen"
  )
endif()
