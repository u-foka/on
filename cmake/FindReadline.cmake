cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED READLINE_INCLUDE_DIR)
find_path(READLINE_INCLUDE_DIR readline/readline.h)
endif()
if(NOT DEFINED READLINE_LIBRARY)
find_library(READLINE_LIBRARY NAMES readline)
endif()

if (READLINE_INCLUDE_DIR AND READLINE_LIBRARY)
    set(HAVE_READLINE 1)
endif (READLINE_INCLUDE_DIR AND READLINE_LIBRARY)

if (HAVE_READLINE)
    if (NOT Readline_FIND_QUIETLY)
        message(STATUS "Found GNU readline: ${READLINE_LIBRARY}")
    endif (NOT Readline_FIND_QUIETLY)
else (HAVE_READLINE)
   if (Readline_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find GNU readline")
   endif (Readline_FIND_REQUIRED)
endif (HAVE_READLINE)
