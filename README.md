# cub3d
## Description
Cub3d is a basic raycaster engine that is inspired by games like Wolfenstein 3D. This game was released in 1992 by id Software, and is considered to be the first first-person shooter to be created. As it is easy to imagine, at those old times, computers were not as powerful as they are now. They had many constraints when it came to memory or processing power. That's why developers, in search of a way to create a 3D game that could be run on the old days' computers, came up with the raycasting technic.

In reality, Wolfenstain 3D (as well as cub3D) does not have a real 3D world, but rather a 2D map. Using raycasting is able to give the impression of 3D. The basic idea behind raycasting, as the name suggests, is the cast of rays from the position the player is currently in. Several rays are cast in all directions and the engine keeps track of distance it takes until intersection with an obstacle. With said distance it is possible to calculate the height of the walls that will be needed to render the 3D view.

![alt-text](https://github.com/javihernant/cub3d/blob/main/demo.gif)

## Features
- Config file to modify various settings such as the textures to be used, the map and the initial position of the player. (WIP)
- Wall textures
- Ceiling and floor textures
- Sprites and animated sprites (WIP)
- Minimap. It shows the position of the player on the map. It also shows the castings of rays and the intersections with obstacles.
- Wall collisions.
- Doors that open and close (WIP)

## Usage
Compile with `make`. Then, execute `cub3d` binary.

## TODO
### Doors
- Slim doors
- Array of doubles containing values saying how open is the door. Use frame time to modify value. Also modify texture x coord.
- Array of int. Status of the door.

### Animated Sprites
- No complex AI. Just sprites moving randomly around.
- Use 2 textures depending on frame time (maybe).
