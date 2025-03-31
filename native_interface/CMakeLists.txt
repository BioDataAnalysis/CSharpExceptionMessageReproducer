
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(DEFINED ENV{PROJECT_VERSION})
    set(TMP_PROJECT_VERSION $ENV{PROJECT_VERSION})
else()
    message(FATAL_ERROR "The project version is not defined in the environment variable 'PROJECT_VERSION'.")
endif()

project(CSharpExceptionMessageReproducer.NativeInterface VERSION ${TMP_PROJECT_VERSION} LANGUAGES CXX)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


# Do not generate the ZERO_CHECK project, that would re-run cmake:
set(CMAKE_SUPPRESS_REGENERATION ON)


set(SOURCES
    include/ExceptionMessageReproducer.hh
    src/ExceptionMessageReproducer.cc
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})


if(MSVC_IDE)
    # For the Visual Studio cmake generator, ensure we have a static project
    # GUID (value ProjectGuid in the vcxproj file) for our main target, so that
    # the project vcxproj XML configuration will not constantly change. The
    # default from cmake is to hash the path, but that may then differ for
    # different users.
    set("${PROJECT_NAME}_GUID_CMAKE" "BDABDABD-AAAA-BBBB-CCCC-38B45273CFCA" CACHE INTERNAL "Project GUID for target ${PROJECT_NAME}")

    # Set the common language runtime to empty, to indicate a project that uses
    # "Mixed unmanaged/managed C++ using .NET Framework". See also
    # https://cmake.org/cmake/help/latest/prop_tgt/COMMON_LANGUAGE_RUNTIME.html.
    # This setting can be used with cmake generators of type Visual Studio
    # solution file, but not with makefile based generators like Ninja. For
    # makefile based generators, see the solution below.
    set_target_properties(${PROJECT_NAME} PROPERTIES
        COMMON_LANGUAGE_RUNTIME "")
else()
    # For Ninja and other makefile based generators, set the common language
    # runtime via the compile options:
    target_compile_options(${PROJECT_NAME} PRIVATE "/clr")
    # Adding /clr requires to disable incompatible options "/RTC1" and "/EHsc":
    string(REGEX REPLACE "[/|-]RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REGEX REPLACE "[/|-]EH[ascr][ascr]*" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Threads::Threads
        $<$<PLATFORM_ID:Linux>:rt>)
