# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TennisStarWars_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TennisStarWars_autogen.dir\\ParseCache.txt"
  "TennisStarWars_autogen"
  )
endif()
