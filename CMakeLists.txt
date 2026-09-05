cmake_minimum_required(VERSION 3.13)

project(3DSTemplate LANGUAGES C CXX)

set(APP_NAME "3DS Template" CACHE STRING "App name")
set(APP_DESCRIPTION "My first 3DS app" CACHE STRING "App description")
set(APP_AUTHOR "Your Name" CACHE STRING "Author")

set(DEVKITPRO $ENV{DEVKITPRO})
list(APPEND CMAKE_MODULE_PATH ${DEVKITPRO}/cmake)
include(3DS)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

set(SMDH_FILE ${PROJECT_NAME}.smdh)

ctr_generate_smdh(${SMDH_FILE}
    NAME "${APP_NAME}"
    DESCRIPTION "${APP_DESCRIPTION}"
    AUTHOR "${APP_AUTHOR}"
    # ICON assets/icon.png   # optional
)

ctr_create_3dsx(${PROJECT_NAME}
    SMDH ${SMDH_FILE}
)