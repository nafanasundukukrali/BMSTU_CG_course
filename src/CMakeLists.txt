cmake_minimum_required(VERSION 3.5)

project(visual-chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(PROJECT_SOURCES
  utils/vector3d/vector3d.h
  utils/vector3d/vector3d.cpp
  utils/ray/ray.cpp
  utils/ray/ray.h
  utils/boundingbox/boundingbox.h
  utils/boundingbox/boundingbox.cpp
  utils/material/material.h
  utils/material/material.cpp
  object/object.h
  object/invisibleobject/invisibleobject.h
  object/invisibleobject/camera/camera.h
  object/invisibleobject/camera/camera.cpp
  object/invisibleobject/lightsource/lightsource.h
  object/invisibleobject/lightsource/lightsource.cpp
  object/invisibleobject/kdtree/kdtree.h
  object/invisibleobject/kdtree/kdtree.cpp
  object/visibleobject/visibleobject.h
  object/visibleobject/box/box.h
  object/visibleobject/box/box.cpp
  object/visibleobject/triangle/triangle.h
  object/visibleobject/triangle/triangle.cpp
  object/visibleobject/model/model.h
  object/visibleobject/model/model.cpp
  builder/basebuilder.h
  builder/basebuilder.cpp
  builder/pawn/pawn.h
  builder/pawn/pawn.cpp
  builder/bishop/bishop.h
  builder/bishop/bishop.cpp
  builder/king/king.h
  builder/king/king.cpp
  builder/knight/knight.h
  builder/knight/knight.cpp
  builder/queen/queen.h
  builder/queen/queen.cpp
  builder/rook/rook.h
  builder/rook/rook.cpp
  builder/chessdesk/chessdesk.h
  builder/chessdesk/chessdesk.cpp
  scene/scene.h
  scene/scene.cpp
  drawer/basedrawer.h
  drawer/qtdrawer.cpp
  drawer/qtdrawer.h
  utils/baseexception/baseexception.h
  scene/exceptionscene.h
  facade/facade.h
  facade/facade.cpp
  scenemanager/scenemanager.h
  scenemanager/scenemanager.cpp
  command/basecommand.h
  command/scenecommand/scenecommand.h
  factory/abstractfactory.h
  factory/qtdrawerfactory/qtdrawerfactory.h
  factory/qtdrawerfactory/qtdrawerfactory.cpp
  mainwindow.h
  mainwindow.ui
  mainwindow.cpp
  reader/stl_reader.h
  loaddialog/loaddialog.h loaddialog/loaddialog.cpp
)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UP)
if (${CMAKE_BUILD_TYPE_UP} STREQUAL "DEBUG")
     SET(CMAKE_BUILD_TYPE Debug)
    add_executable(visual-chess
        main_test.cpp
        ${PROJECT_SOURCES})
else()
    add_executable(visual-chess
        main_release.cpp
        ${PROJECT_SOURCES})
endif()

#add_executable(visual-chess
#    main_release.cpp
#    ${PROJECT_SOURCES}
#)

include_directories(
${PROJECT_SOURCE_DIR}/utils
${PROJECT_SOURCE_DIR}/loadimage
${PROJECT_SOURCE_DIR}/models)

set(SOURCE_MODELS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/models)
set(DEST_MODELS_PATH ${CMAKE_CURRENT_BINARY_DIR}/models)
set(LOAD_IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/loadimage)
set(LOAD_MODELS_DEST_PATH ${CMAKE_CURRENT_BINARY_DIR}/loadimage)

add_compile_definitions(MODELS_PATH="${DEST_MODELS_PATH}/")
add_compile_definitions(LOADING_PATH="${LOAD_MODELS_DEST_PATH}/load.gif")
add_compile_definitions(MODELS_FILE_TYPE=".stl")
add_compile_definitions(BASE_CELL_SIZE=39)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_MODELS_PATH} ${DEST_MODELS_PATH}
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${LOAD_IMAGE_PATH} ${LOAD_MODELS_DEST_PATH}
)

target_link_libraries(visual-chess PRIVATE  
Qt${QT_VERSION_MAJOR}::Widgets
TBB::tbb
Threads::Threads)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(visual-chess)
endif()
