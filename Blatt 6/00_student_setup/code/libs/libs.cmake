# Dependencies

# Setup FetchContent
include(FetchContent)
mark_as_advanced(FORCE
  FETCHCONTENT_BASE_DIR
  FETCHCONTENT_FULLY_DISCONNECTED
  FETCHCONTENT_QUIET
  FETCHCONTENT_UPDATES_DISCONNECTED)

# GLFW
FetchContent_Declare(glfw
  URL https://github.com/glfw/glfw/archive/refs/tags/3.3.6.zip
  URL_HASH MD5=ae8fafce42bf94b658101aa921a74c13)
FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
  message(STATUS "Fetch glfw ...")
  FetchContent_Populate(glfw)
  option(GLFW_BUILD_DOCS "" OFF)
  option(GLFW_BUILD_EXAMPLES "" OFF)
  option(GLFW_BUILD_TESTS "" OFF)
  option(GLFW_INSTALL "" OFF)
  if (WIN32)
    option(GLFW_USE_HYBRID_HPG "" ON)
  endif ()
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_GLFW
    FETCHCONTENT_UPDATES_DISCONNECTED_GLFW
    BUILD_SHARED_LIBS
    GLFW_BUILD_DOCS
    GLFW_BUILD_EXAMPLES
    GLFW_BUILD_TESTS
    GLFW_INSTALL
    GLFW_USE_HYBRID_HPG
    GLFW_USE_OSMESA
    GLFW_USE_WAYLAND
    GLFW_VULKAN_STATIC
    USE_MSVC_RUNTIME_LIBRARY_DLL
    X11_xcb_icccm_INCLUDE_PATH
    X11_xcb_icccm_LIB)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
  set_target_properties(glfw PROPERTIES
    FOLDER libs)
endif ()

# glm
FetchContent_Declare(glm
  URL https://github.com/g-truc/glm/archive/refs/tags/0.9.9.8.zip
  URL_HASH MD5=a421a37d1896ab74765c3f94431ca0f6)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
  message(STATUS "Fetch glm ...")
  FetchContent_Populate(glm)
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_GLM
    FETCHCONTENT_UPDATES_DISCONNECTED_GLM)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

# imgui
FetchContent_Declare(imgui
  URL https://github.com/ocornut/imgui/archive/refs/tags/v1.86.zip
  URL_HASH MD5=bccb1c173296979e6a61b4f9da572429)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
  message(STATUS "Fetch imgui ...")
  FetchContent_Populate(imgui)
  file(COPY ${CMAKE_SOURCE_DIR}/libs/imgui/CMakeLists.txt DESTINATION ${imgui_SOURCE_DIR})
  mark_as_advanced(FORCE
    FETCHCONTENT_SOURCE_DIR_IMGUI
    FETCHCONTENT_UPDATES_DISCONNECTED_IMGUI)
  add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR} EXCLUDE_FROM_ALL)
  set_target_properties(imgui PROPERTIES FOLDER libs)
endif ()

# local libraries

# glad
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad")
add_library(glad
  ${GLAD_DIR}/include/glad/gl.h
  ${GLAD_DIR}/include/KHR/khrplatform.h
  ${GLAD_DIR}/src/gl.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})
set_target_properties(glad PROPERTIES FOLDER libs)

# glowl
set(GLOWL_DIR "${CMAKE_SOURCE_DIR}/libs/glowl")
add_library(glowl
  ${GLOWL_DIR}/GLSLProgram.cpp
  ${GLOWL_DIR}/GLSLProgram.hpp
  ${GLOWL_DIR}/Texture.hpp
  ${GLOWL_DIR}/Texture2D.cpp
  ${GLOWL_DIR}/Texture2D.hpp)
target_include_directories(glowl PUBLIC ${GLOWL_DIR})
target_link_libraries(glowl glad)
set_target_properties(glowl PROPERTIES FOLDER libs)
