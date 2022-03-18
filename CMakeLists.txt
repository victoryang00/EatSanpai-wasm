cmake_minimum_required(VERSION 3.6)

project(Ryan_teaching_winter_session LANGUAGES C CXX)

set(CPM_DOWNLOAD_VERSION 0.34.3)

IF (APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF ()

if (CPM_SOURCE_CACHE)
    #Expand relative path.This is important if the provided path contains a tilde(~)
    get_filename_component(CPM_SOURCE_CACHE ${CPM_SOURCE_CACHE} ABSOLUTE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif (DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else ()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif ()

if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION}
            )
endif ()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(NAME cereal VERSION 1.2.2 GIT_REPOSITORY https://github.com/USCiLab/cereal OPTIONS "JUST_INSTALL_CEREAL 1")

set(CMAKE_CXX_STANDARD 20)
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
endif ()
if (CMAKE_CXX_COMPILER MATCHES "em\\+\\+(-[a-zA-Z0-9.])?$")
    message(STATUS "Using em++")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -s WASMFS=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ASSERTIONS=2 -s TOTAL_MEMORY=67108864 -s DEMANGLE_SUPPORT=1 -s FULL_ES2=1 -s USE_WEBGL2=1 -s NO_DISABLE_EXCEPTION_CATCHING=1 -s EXPORTED_RUNTIME_METHODS=printErr,ccall,cwrap  -s USE_ZLIB=1 -s USE_LIBPNG=1 -s USE_VORBIS=1 -s USE_FREETYPE=1 -s USE_BOOST_HEADERS=1 -s USE_LIBJPEG=1 -s MAX_WEBGL_VERSION=1 -s MIN_WEBGL_VERSION=2 -s USE_GIFLIB=2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\", \"png\", \"jpg\"]' -s USE_SDL_GFX=2 ")

    set(USE_FLAGS "-s USE_SDL=2 -s USE_FREETYPE=1 -s USE_VORBIS=1 -s USE_LIBPNG=1 -s DISABLE_EXCEPTION_CATCHING=0 ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS} -s ASSERTIONS=1 -s FULL_ES3=1 -s INITIAL_MEMORY=1024MB --preload-file image ") # -s ALLOW_MEMORY_GROWTH=1 --source-map-base http://127.0.0.1:8000/ -g ")
else ()
    include(CheckCCompilerFlag)
    set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;x86_64")
    check_c_compiler_flag("-arch x86_64" x86_64Supported)
    message("x86_64Supported=${x86_64Supported}")

    set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;arm64")
    check_c_compiler_flag("-arch arm64" arm64Supported)
    message("arm64Supported=${arm64Supported}")
endif ()

add_subdirectory(third_party/jngl)

set(MYGAME_SANITIZE_ADDRESS_DEFAULT OFF)
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
        src/engine/*.cpp
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
        add_executable(Ryan_teaching_winter_session ${SOURCES} src/Explosion.cpp src/Explosion.h)
    endif ()
    if (APPLE)
        target_link_libraries(Ryan_teaching_winter_session PRIVATE "-framework AppKit")
    endif ()
    target_link_libraries(Ryan_teaching_winter_session PRIVATE
            jngl cereal
            )
endif ()
file(GLOB GFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data CONFIGURE_DEPENDS data/*.webp data/*.png
        data/*/*.webp)
file(GLOB SFX_FILES RELATIVE ${CMAKE_SOURCE_DIR}/data data/sfx/*.ogg)
target_include_directories(Ryan_teaching_winter_session PRIVATE ${CMAKE_BINARY_DIR}/include third_party/cereal/include
        third_party/spine-runtimes/spine-c/spine-c/include)
if (WIN32)
    target_compile_definitions(Ryan_teaching_winter_session PRIVATE _USE_MATH_DEFINES)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(Ryan_teaching_winter_session PROPERTIES WIN32_EXECUTABLE 1)
endif ()
