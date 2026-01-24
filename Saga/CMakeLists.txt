add_executable(${SAGA_GAME_TARGET_NAME}
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

)

target_include_directories(${SAGA_GAME_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${SAGA_GAME_TARGET_NAME} PUBLIC SFML::Graphics)
target_link_libraries(${SAGA_GAME_TARGET_NAME} PUBLIC SFML::Window)
target_link_libraries(${SAGA_GAME_TARGET_NAME} PUBLIC SFML::System) 
target_link_libraries(${SAGA_GAME_TARGET_NAME} PUBLIC SFML::Audio)

function(CopyLibToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}
    )
endfunction()

CopyLibToTarget(sfml-graphics ${SAGA_GAME_TARGET_NAME})
CopyLibToTarget(sfml-window ${SAGA_GAME_TARGET_NAME})
CopyLibToTarget(sfml-system ${SAGA_GAME_TARGET_NAME})
CopyLibToTarget(sfml-audio ${SAGA_GAME_TARGET_NAME})