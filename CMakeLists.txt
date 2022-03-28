cmake_minimum_required(VERSION 3.10.2)
project(GAME C)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(DEBUG_BUILD ON)
endif()

if(EMSCRIPTEN)
  set(EMSCRIPTEN_FLAGS "-s WASM=1 s USE_SDL=2 ")
  if (DEBUG_BUILD)
    set(EMSCRIPTEN_FLAGS "${EMSCRIPTEN_FLAGS} -s DEMANGLE_SUPPORT=1 -g4 --source-map-base http://localhost:6931/")
  endif()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
  set($ENV{CFLAGS} ${EMSCRIPTEN_FLAGS})
	set($ENV{LDFLAGS} ${EMSCRIPTEN_FLAGS})
	set(CMAKE_REQUIRED_FLAGS ${EMSCRIPTEN_FLAGS})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE game_src "src/*.c" "include/*.h" "3rd_party/stb.c")

add_executable(GAME ${game_src}  "src/framework/texture.c")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(GAME PUBLIC BUILD_64BIT)
endif()

if(NOT GLFW_FETCH_CONTENT_VERSION)
	set(GLFW_FETCH_CONTENT_VERSION 3.3.6)
endif()

if(NOT MINIAUDIO_FETCH_CONTENT_VERSION)
	set(MINIAUDIO_FETCH_CONTENT_VERSION 82e70f4cbe6e613c8edc0ac7b97ff3dd00f2ca27)
endif()

target_compile_definitions(GAME PUBLIC WITHOUT_SDL)
if(NOT EMSCRIPTEN)
	include(FetchContent)
	FetchContent_Declare(
		GLFW
		GIT_REPOSITORY	https://github.com/glfw/glfw
		GIT_TAG			${GLFW_FETCH_CONTENT_VERSION}
	)
	set(BUILD_SHARED_LIBS ON)
	set(GLFW_BUILD_EXAMPLES OFF)
	set(GLFW_BUILD_TESTS OFF)
	set(GLFW_BUILD_DOCS OFF)
	set(GLFW_INSTALL OFF)
	FetchContent_MakeAvailable(GLFW)

	FetchContent_Declare(
		MINIAUDIO
		GIT_REPOSITORY	https://github.com/mackron/miniaudio
		GIT_TAG			${MINIAUDIO_FETCH_CONTENT_VERSION}
	)
	FetchContent_MakeAvailable(MINIAUDIO)

	target_include_directories(GAME PUBLIC "${glfw_SOURCE_DIR}/include" "${miniaudio_SOURCE_DIR}")
	target_link_libraries(GAME glfw3dll)
endif()

target_compile_definitions(GAME PUBLIC SDL_MAIN_HANDLED)
target_compile_definitions(GAME PUBLIC WIN32_LEAN_AND_MEAN)
target_include_directories(GAME PUBLIC "include" "3rd_party" "src")

if(WIN32)
	target_link_libraries(GAME imm32 winmm hid setupapi version ws2_32 Iphlpapi)
endif(WIN32)

if(WIN32)
	if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
		if (DEBUG_BUILD)
			target_compile_options(${PROJECT_NAME} PRIVATE "/ZI")
			target_link_options(${PROJECT_NAME} PRIVATE "/SAFESEH:NO")
		endif()
	endif()
endif(WIN32)

add_custom_command(TARGET GAME POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

