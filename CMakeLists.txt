cmake_minimum_required(VERSION 4.2.1)

project(Saga VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SAGA_ENGINE_TARGET_NAME SagaEngine)
set(SAGA_GAME_TARGET_NAME SagaGame)

add_subdirectory(SagaEngine)
add_subdirectory(SagaGame)