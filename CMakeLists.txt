# SPDX-FileCopyrightText: Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

# =============================================================================
# NLib - NVIDIA NURBS library (standalone build, NURBS algorithms only)
# -----------------------------------------------------------------------------
# Builds NLib without the SMLib / B-Rep kernel. The NURBS algorithms are
# self-contained; the few SMLib symbols they reference are defined directly
# in nlib/inc/StdAfx.h.
#
# Windows (Visual Studio project):
#     cmake -S . -B build -G "Visual Studio 17 2022" -A x64
#     cmake --open build
#
# Linux / macOS (single-config generator):
#     cmake -S . -B build
#     cmake --build build --config Release
# =============================================================================

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(NLib
    VERSION 7.0.0
    DESCRIPTION "NLib NURBS algorithms library"
    LANGUAGES CXX)

include(GNUInstallDirs)

# -----------------------------------------------------------------------------
# Options
# -----------------------------------------------------------------------------
option(NLIB_BUILD_SHARED "Build NLib as a shared library (DLL on Windows)" OFF)
option(NLIB_ENABLE_PCH   "Build with a precompiled header (StdAfx.h)" OFF)
option(NLIB_USE_TBB      "Enable Intel TBB scalable allocator support" OFF)

# -----------------------------------------------------------------------------
# C++ standard
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------------------------------------------
# Output layout
# -----------------------------------------------------------------------------
# Visual Studio and Ninja Multi-Config get a per-config output directory;
# single-config generators (Makefiles, Ninja) get a fixed bin/lib layout.
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakePredefinedTargets")

if(CMAKE_GENERATOR MATCHES "Visual Studio|Ninja Multi-Config")
    foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/$<CONFIG>)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/$<CONFIG>)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/$<CONFIG>)
    endforeach()
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
endif()

# -----------------------------------------------------------------------------
# Library target
# -----------------------------------------------------------------------------
set(NLib_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlib/inc)
set(NLib_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlib/src)

file(GLOB NLib_HEADERS CONFIGURE_DEPENDS ${NLib_HEADERS_DIR}/*.h)
file(GLOB NLib_SOURCES CONFIGURE_DEPENDS ${NLib_SOURCES_DIR}/*.cpp)

if(NLIB_BUILD_SHARED)
    add_library(NLib SHARED)
else()
    add_library(NLib STATIC)
endif()

add_library(NLib::NLib ALIAS NLib)

target_sources(NLib PRIVATE ${NLib_SOURCES} ${NLib_HEADERS})

target_include_directories(NLib
    PUBLIC
        $<BUILD_INTERFACE:${NLib_HEADERS_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Nice folder layout in Visual Studio's Solution Explorer.
source_group("Source Files" FILES ${NLib_SOURCES})
source_group("Header Files" FILES ${NLib_HEADERS})

# -----------------------------------------------------------------------------
# Precompiled header (optional - this is a large codebase)
# -----------------------------------------------------------------------------
if(NLIB_ENABLE_PCH)
    target_precompile_headers(NLib PRIVATE ${NLib_HEADERS_DIR}/StdAfx.h)
endif()

# -----------------------------------------------------------------------------
# Compiler-specific flags
# -----------------------------------------------------------------------------
if(MSVC)
    # The legacy code uses fopen/sprintf/sscanf/... which MSVC marks deprecated;
    # silence those warnings to keep the build output readable.
    target_compile_definitions(NLib PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _CRT_NONSTDC_NO_DEPRECATE)
    target_compile_options(NLib PRIVATE /EHsc)
endif()

# -----------------------------------------------------------------------------
# Optional Intel TBB scalable allocator
# -----------------------------------------------------------------------------
if(NLIB_USE_TBB)
    find_package(TBB QUIET)
    if(TBB_FOUND)
        target_compile_definitions(NLib PRIVATE SM_USE_TBB_SCALABLE)
        target_link_libraries(NLib PRIVATE TBB::tbb)
    else()
        message(WARNING "NLIB_USE_TBB is ON but TBB was not found; building without it.")
    endif()
endif()

# -----------------------------------------------------------------------------
# Install & CMake package export
# -----------------------------------------------------------------------------
install(TARGETS NLib
    EXPORT NLibTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install public headers. The trailing slash copies the *contents* of nlib/inc
# (rather than the directory itself) into <prefix>/include.
install(DIRECTORY ${NLib_HEADERS_DIR}/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)

install(EXPORT NLibTargets
    FILE NLibTargets.cmake
    NAMESPACE NLib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NLib)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/NLibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/NLibConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NLib)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/NLibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/NLibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/NLibConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NLib)
