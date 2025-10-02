cmake_minimum_required(VERSION 3.16)
project(SecureFileTransfer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)

# Tell AUTOUIC where our .ui files live
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

qt_add_executable(SecureFileTransfer
    src/main.cpp
    src/MainWindow.cpp
    src/ClientWidget.cpp
    src/ServerWidget.cpp
    src/Encryption.cpp
    src/TransferSession.cpp
    ui/MainWindow.ui
    ui/ClientWidget.ui
    ui/ServerWidget.ui
)

target_include_directories(SecureFileTransfer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(SecureFileTransfer
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Network
)

if(MSVC)
    target_compile_options(SecureFileTransfer PRIVATE /W4 /WX)
else()
    target_compile_options(SecureFileTransfer PRIVATE -Wall -Wextra -Werror)
endif()
