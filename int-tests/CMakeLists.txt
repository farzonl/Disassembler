if(UNIX)
    add_subdirectory(linux)
endif(UNIX)

if(APPLE)
    add_subdirectory(mac)
endif(APPLE)

add_subdirectory(windows)