include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0
)

# CMake 3.14+
FetchContent_MakeAvailable(catch2)

FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff.git
    GIT_TAG master
)

FetchContent_MakeAvailable(fff)

add_library(phy_hal_mock INTERFACE)
target_include_directories(phy_hal_mock INTERFACE ${CMAKE_CURRENT_LIST_DIR}/mock)

target_link_libraries(${PROJECT_NAME} phy_hal_mock)

add_executable(register_node_test ${CMAKE_CURRENT_LIST_DIR}/functionality/register_node.cpp)
target_link_libraries(register_node_test ${PROJECT_NAME} Catch2 fff phy_hal_mock)
target_compile_definitions(register_node_test PUBLIC "FFF_GENERATE" "LWRB_DISABLE_ATOMIC")

add_library(fake_slave_handlers ${CMAKE_CURRENT_LIST_DIR}/mock/fakes/fake_hw_can.c
                                ${CMAKE_CURRENT_LIST_DIR}/mock/fakes/fake_hw_nvm.c
                                ${CMAKE_CURRENT_LIST_DIR}/mock/fakes/fake_hw_timer.cpp)

target_link_libraries(fake_slave_handlers ${PROJECT_NAME} fff)                                
add_executable(master_node_sim_test ${CMAKE_CURRENT_LIST_DIR}/functionality/master_node_sim.cpp)
target_link_libraries(master_node_sim_test ${PROJECT_NAME} Catch2 fff phy_hal_mock fake_slave_handlers)
target_compile_definitions(master_node_sim_test PUBLIC "FFF_GENERATE" "LWRB_DISABLE_ATOMIC")


add_test(
        NAME register_node_test
        COMMAND register_node_test
)


add_test(
        NAME master_node_sim_test
        COMMAND master_node_sim_test
)