# hardframe
Hardframe is a framework for making games and demos with components for graphics, physics, and more. Hardframe is currently in very early development but expect more soon!

## Uses ##
Demos, games, really anything that can use libraries for 3D graphics, fonts, physics, etc.

## How to Build ##
Run build.sh with any of these arguments:
- run: Execute the binary after finished
- config: Configure cmake (adds the caches back)(useful for a complete reset)
- delete: Delete everything in the build folder to build from nothing. If you have this arg and build without the arg config it will fail.
- nobuild: Skips the build proccess, useful for just executing the binary.
- clean: Deletes .a files from static libraries. 
