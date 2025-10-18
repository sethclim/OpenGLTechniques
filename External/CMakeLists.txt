add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_LIST_DIR}/stb/)

add_library(OBJ_Loader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/obj_loader/)
target_include_directories(OBJ_Loader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/obj_loader/)

add_library(tiny_obj_loader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/tiny_obj_loader/)
target_include_directories(tiny_obj_loader INTERFACE ${CMAKE_CURRENT_LIST_DIR}/tiny_obj_loader/)

message(STATUS "WHATTT "${CMAKE_CURRENT_LIST_DIR}/obj_loader/OBJ_Loader.h)

add_subdirectory(glfw)
add_subdirectory(glm)

add_subdirectory(freetype)

target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE glm::glm-header-only)

option(FT_DISABLE_ZLIB OFF) 
# FT_DISABLE_BZIP2=TRUE 
# FT_DISABLE_PNG=TRUE 
# FT_DISABLE_HARFBUZZ=TRUE 
# FT_DISABLE_BROTLI=TRUE 

target_link_libraries(app PRIVATE freetype)

target_include_directories(app PRIVATE
    ${PROJECT_SOURCE_DIR}/External/glew-2.1.0-win32/glew-2.1.0/include
)

target_link_libraries(app PRIVATE ${PROJECT_SOURCE_DIR}/External/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64/glew32.lib)

target_link_libraries(app PRIVATE stb_image)
target_link_libraries(app PRIVATE OBJ_Loader)
target_link_libraries(app PRIVATE tiny_obj_loader)