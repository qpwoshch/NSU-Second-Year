cmake_minimum_required(VERSION 3.10)
project(lab6)

set(CMAKE_CXX_STANDARD 17)

# Указываем путь к папке с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/include)

# Указываем путь к папке с DLL
link_directories(${CMAKE_SOURCE_DIR}/MinGW64/dll)

# Добавляем исходники и создаем исполнимый файл
add_executable(lab6 main.cpp)

# Линкуем с динамической библиотекой
target_link_libraries(lab6 kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib)

# Убедитесь, что CMake может найти DLL во время выполнения
set_target_properties(lab6 PROPERTIES
        INSTALL_RPATH "${CMAKE_SOURCE_DIR}/MinGW64/dll"
)

# Важно: убедитесь, что DLL доступна в каталоге с исполнимым файлом во время выполнения
