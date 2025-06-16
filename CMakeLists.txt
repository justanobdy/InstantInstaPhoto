cmake_minimum_required(VERSION 3.20)
project(InstantInstaPhoto LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#add_compile_options(/fsanitize=address)
#add_link_options(/fsanitize=address)

find_package(nlohmann_json 3.12.0 REQUIRED)

if(SFML_STATIC)
    set(SFML_STATIC_LIBRARIES ON)
endif()
# set(CMAKE_FIND_FRAMEWORK LAST)

option(LINK_OPENGL ON)

if(LINK_OPENGL)
    find_package(OpenGL REQUIRED COMPONENTS OpenGL)
endif()

find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED)

file(GLOB LIBSSRC lib/*.cpp)
file(GLOB LIBSHEADERS lib/*.hpp lib/*.h )

set(HEADERS
    "include/App.hpp"
    "include/AppState.hpp"
    "include/Common.hpp"
    "include/Module.hpp"
    "include/Object.hpp"
    "include/SelectModule.hpp"
    "include/SpriteObject.hpp"
    "include/DetailModule.hpp"
    "include/ObjectListModule.hpp"
    "include/Exporter.hpp"
    "include/ObjectContextModule.hpp"
    "include/MenuBarModule.hpp"
    "include/NewProjectModule.hpp"
    "include/EditProjectModule.hpp"
    "include/ProjectManager.hpp"
)

set(SOURCES
        src/main.cpp
 "src/SpriteObject.cpp" "src/App.cpp"  "src/SelectModule.cpp" "src/Object.cpp" "src/DetailModule.cpp" "src/ObjectListModule.cpp" "src/AppState.cpp" "src/Exporter.cpp" "src/Module.cpp" "src/ObjectContextModule.cpp" "src/MenuBarModule.cpp" "src/NewProjectModule.cpp" "src/EditProjectModule.cpp" "src/ProjectManager.cpp")

add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${LIBSSRC})

source_group(libs FILES ${LIBSSRC})
source_group("Library Headers" FILES ${LIBSHEADERS})
source_group("Headers" FILES ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib")

if(LINK_OPENGL)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
endif()

include_directories(include/ lib/)

# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
