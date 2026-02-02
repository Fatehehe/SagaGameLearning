add_executable(${SAGA_GAME_TARGET_NAME} 

    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/ship/Ship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ship/Ship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerShip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerShip.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Weapon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Weapon.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/KineticWeapon.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/KineticWeapon.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Projectile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Projectile.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/enemies/EnemyShip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/enemies/EnemyShip.cpp
)

target_include_directories(${SAGA_GAME_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${SAGA_GAME_TARGET_NAME} PUBLIC ${SAGA_ENGINE_TARGET_NAME}) 

function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()

CopyLibDirToTarget(${SAGA_ENGINE_TARGET_NAME} ${SAGA_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
        TARGET ${SAGA_GAME_TARGET_NAME}
        POST_BUILD
        COMMAND 
        ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_SOURCE_DIR}
        $<TARGET_FILE_DIR:${SAGA_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
)

configure_file(
    "config.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)