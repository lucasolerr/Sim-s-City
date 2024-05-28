cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)
include(CTest)

# Tests unitaires
enable_testing()

# Tests de la liste chainée
add_executable(test_liste tests_liste.c "../src/utils/liste.c")
add_test(test_liste test_liste "../tests")

file(GLOB_RECURSE SIM_SOURCE_FILES "../src/sim/*.c")
file(GLOB_RECURSE UTILS_SOURCE_FILES "../src/utils/*.c")

add_executable(test_sim_habitation "sim/test_sim_habitation.c" ${SIM_SOURCE_FILES} ${UTILS_SOURCE_FILES})
add_test(test_sim_habitation test_sim_habitation "../tests")

add_executable(test_vector tests_vector.c ${UTILS_SOURCE_FILES})
add_test(test_vector test_vector "../tests")