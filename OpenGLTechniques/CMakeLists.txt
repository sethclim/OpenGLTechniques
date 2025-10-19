set(TARGET_H
    Application.h
    Camera.h
    Fonts.h
    GameController.h
    Mesh.h
    Mouse.h
    MoveLightScene.h
    PostProcessor.h
    Resolution.h
    Scene.h
    Shader.h
    Singleton.h
    Skybox.h
    SpaceScene.h
    StandardIncludes.h
    Texture.h
    ToolWindow.h
    transformScene.h
    Utilities.h
    WaterScene.h
    WindowController.h
)

set(TARGET_SRC
    Application.cpp
    Camera.cpp
    Fonts.cpp
    GameController.cpp
    main.cpp
    Mesh.cpp
    MoveLightScene.cpp
    PostProcessor.cpp
    Scene.cpp
    Shader.cpp
    Skybox.cpp
    SpaceScene.cpp
    StandardIncludes.h
    Texture.cpp
    ToolWindow.cpp
    TransformScene.cpp
    Utilities.cpp
    WaterScene.cpp
    WindowController.cpp
)

set_source_files_properties(${TARGET_SRC} PROPERTIES COMPILE_FLAGS "/clr")

set(TARGET_RESX
  ToolWindow.resx
)

set(TARGET_LIBRARIES ${SYSLIBS})


add_executable(app  ${TARGET_SRC} ${TARGET_H} ${TARGET_RESX})

target_compile_features(app PRIVATE cxx_std_17)


target_link_libraries(app PRIVATE ${OPENGL_LIBRARY})

if(NOT CMAKE_GENERATOR MATCHES "Visual Studio 1[0-6]")
  # VS 17 2022 and above require a global mark on managed assemblies.
  # CMake adds this automatically when using COMMON_LANGUAGE_RUNTIME,
  # but this test covers direct use of /clr.
  set_property(TARGET app PROPERTY VS_GLOBAL_ManagedAssembly "true")
endif()


# Note: The property VS_GLOBAL_KEYWORD must be set.
set_property(TARGET app PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")

# Note: The property VS_DOTNET_REFERENCES must be set.
set_property(TARGET app PROPERTY VS_DOTNET_REFERENCES "System" "System.Data" "System.Drawing" "System.Windows.Forms" "System.Xml")

# Note: Modification of compiler flags is required for CLR compatibility now that we are using .resx files.
string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")


add_custom_command(TARGET app POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/External/glew-2.1.0-win32/glew-2.1.0/bin/Release/x64/glew32.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:app>)                 # <--this is out-file path

add_custom_command(
    TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:app>/Assets
    COMMENT "Copying Assets" VERBATIM
)

add_custom_command(
    TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory              
        ${CMAKE_SOURCE_DIR}/OpenGLTechniques/shaders $<TARGET_FILE_DIR:app>/shaders
    COMMENT "Copying Assets" VERBATIM
)