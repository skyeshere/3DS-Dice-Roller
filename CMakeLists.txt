cmake_minimum_required(VERSION 3.13)

project(DiceRoller LANGUAGES C CXX)

set(APP_NAME "3DS Dice Roller" CACHE STRING "App name")
set(APP_DESCRIPTION "Roll a D20 and more on your 3DS!" CACHE STRING "App description")
set(APP_AUTHOR "skyeshere" CACHE STRING "Author")

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
    ICON assets/icon.png   # optional
)

ctr_create_3dsx(${PROJECT_NAME}
    SMDH ${SMDH_FILE}
)
