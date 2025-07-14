# cmake/CompileOptions.cmake
# Общие флаги + санитайзеры только для Debug-сборки
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g                      # отладочная информация
        -O0                     # без оптимизаций, чтобы ASan не путался
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    add_link_options(
        -fsanitize=address,undefined
    )
endif()
