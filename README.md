# WIP VERSION: THIS VERSION IS IN DEVELOPMENT! #

# hardframe #
Hardframe is a framework for making games and demos with components for graphics, physics, and more. Hardframe is currently in very early development but expect more soon! Make sure to give the [wiki a look,](https://github.com/iMakeMehPrograms/hardframe/wiki) or the [resources repo.](https://github.com/iMakeMehPrograms/hardframe_resources)

## Uses ##
Demos, games, really anything that can use libraries for 3D graphics, fonts, physics, etc.

## How to Build ##
- Install SDL2, GLEW, GLM, and CMake with your favorite package manager. 
- Replace the path of glm_DIR with whereever you have it installed.
- Replace the path of the error logs in build.sh with wherever you put them.

Run build.sh with any of these arguments:

- run: Execute the binary after finished
- config: Configure cmake (adds the caches back)(useful for a complete reset)
- delete: Delete everything in the build folder to build from nothing. If you have this arg and build without the arg config it will fail.
- nobuild: Skips the build proccess, useful for just executing the binary.
- clean: Deletes .a files from static libraries. 

## List of Libraries ##
- Utility
    - General: For general utilities such as casts and others
        - hardframe-general-utility
        - hardframe/utility/general.hpp
    - Spatial: Spatial constructs such as vectors, rotations, and more
        - hardframe-spatial-utility
        - hardframe/utility/spatial.hpp
    - Loadable: Base for asset-loaders, to have a standard way of doing things
        - hardframe-load-utility
        - hardframe/utility/loadable.hpp
- Graphics
    - OpenGL (3D)
        - Base: Base 3D graphics with all the trappings one would expect in a game engine 
            - hardframe-base-graphics
            - hardframe/graphics/opgl/base.hpp
