cmake_minimum_required(VERSION 3.6)

project(Ryan_teaching_winter_session LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
endif ()
if (CMAKE_CXX_COMPILER MATCHES "em\\+\\+(-[a-zA-Z0-9.])?$")
    message(STATUS "Using em++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_ZLIB=1 -s FULL_ES3=1 -s USE_LIBPNG=1 -s USE_VORBIS=1 -s USE_FREETYPE=1 -s USE_THEORA=1 -s USE_BOOST_HEADERS=1 -s USE_LIBJPEG=1 -s USE_GIFLIB=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=['bmp'] -s USE_SDL_TTF=2")
endif ()

add_subdirectory(third_party/jngl)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(MYGAME_SANITIZE_ADDRESS_DEFAULT ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR ANDROID OR CMAKE_BUILD_TYPE MATCHES "Release")
    set(MYGAME_SANITIZE_ADDRESS_DEFAULT OFF)
endif ()
option(MYGAME_SANITIZE_ADDRESS "Enable AddressSanitizer" ${MYGAME_SANITIZE_ADDRESS_DEFAULT})
if (MYGAME_SANITIZE_ADDRESS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
endif ()

file(GLOB SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        )
if (ANDROID)
    # build native_app_glue as a static lib
    set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
    add_library(native_app_glue STATIC
            ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

    # now build app's shared lib
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall")

    # Export ANativeActivity_onCreate(),
    # Refer to: https://github.com/android-ndk/ndk/issues/381.
    set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

    add_library(Ryan_teaching_winter_session SHARED ${SOURCES})

    target_include_directories(Ryan_teaching_winter_session PRIVATE
            ${ANDROID_NDK}/sources/android/native_app_glue
            ../../../../../../src
            ../../../../../include
            )

    # add lib dependencies
    target_link_libraries(Ryan_teaching_winter_session
            android
            native_app_glue
            EGL
            GLESv3 
            OpenSLES
            log
            z
            jngl
            )


    add_library(bootstrap SHARED android/app/src/main/cpp/bootstrap.cpp src/game.cpp src/game.h)

    target_include_directories(bootstrap PRIVATE
            ${ANDROID_NDK}/sources/android/native_app_glue)

    # add lib dependencies
    target_link_libraries(bootstrap
            android
            native_app_glue
            log)
else ()
    if (WIN32)
        add_executable(Ryan_teaching_winter_session ${SOURCES})
    else ()
        add_executable(Ryan_teaching_winter_session ${SOURCES})
    endif ()
    if (APPLE)
        target_link_libraries(Ryan_teaching_winter_session PRIVATE "-framework AppKit")
    elseif (NOT WIN32)
        # target_link_libraries(Ryan_teaching_winter_session PRIVATE
        #         stdc++fs
        #         )
    endif ()
    target_link_libraries(Ryan_teaching_winter_session PRIVATE
            jngl
            )
endif ()

file(GLOB GFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data CONFIGURE_DEPENDS data/*.webp data/*.png
        data/*/*.webp)
file(GLOB SFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data data/sfx/*.ogg)
# configure_file(src/engine/datafiles.hpp.in include/datafiles.hpp @ONLY)
target_include_directories(Ryan_teaching_winter_session PRIVATE ${CMAKE_BINARY_DIR}/include third_party/cereal/include
        third_party/spine-runtimes/spine-c/spine-c/include)
include_directories(/opt/X11/include/freetype2/)
if (WIN32)
    target_compile_definitions(Ryan_teaching_winter_session PRIVATE _USE_MATH_DEFINES)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(Ryan_teaching_winter_session PROPERTIES WIN32_EXECUTABLE 1)
endif ()