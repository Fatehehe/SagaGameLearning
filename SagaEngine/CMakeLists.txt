add_library(${SAGA_ENGINE_TARGET_NAME} STATIC

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

)

target_include_directories(${SAGA_ENGINE_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${SAGA_ENGINE_TARGET_NAME} PUBLIC SFML::Graphics)
target_link_libraries(${SAGA_ENGINE_TARGET_NAME} PUBLIC SFML::Window)
target_link_libraries(${SAGA_ENGINE_TARGET_NAME} PUBLIC SFML::System) 
target_link_libraries(${SAGA_ENGINE_TARGET_NAME} PUBLIC SFML::Audio)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
    ${SFML_LIB_NAME}
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 3.0.0
    GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibToTarget(sfml-graphics ${SAGA_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${SAGA_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${SAGA_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-audio ${SAGA_ENGINE_TARGET_NAME})