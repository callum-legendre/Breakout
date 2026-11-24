# Breakout
A small breakout clone made using SDL3, C++, and a little bit of nlohmann-json for file handling.

## Gameplay
Currently there are 5 distinct level layouts, but the player can keep playing until they loose as these levels loop. It is easy to add more because the resource manager and all level handling logic is entirely data driven. To add a new level all you need to do is create another json with the correct formatting, make sure it is in the correct resources directory, and add the relative path to the resourcs.json file.

Each time the ball hits a brick, the player is awarded 20 points. The game continues until all balls have left the screen, where the player loses. 

## Controls
The mouse controls where the paddle is. It is fixed on the Y axs but follows the x axis of the mouse position. 

When the ball is attached to the paddle in the beggining of a level, left click to launch it. 

On the game over screen, the player can right click to start a new game. Alternatively, the game can be closed at any time by closing the window.

## Future plans
There are a few mechanics that I wanted to introduce that I did not have time to. I wanted to have sound effects play when certian events occured (like when a ball hits or destroys a brick) but I ran out of time to do that. I may come back later and impliment it for fun.

Additionally, I wanted to introduce a power up system. My idea was to have some bricks spawn in with a "power up" which, when the tile they were attached to was broken, would spawn an orb that moved at a fixed place towards the bottom of the window. If the power up orb was "collected" by the player (by the paddle moving into the orb) the orb would grant its effect. 

A few ideas for power ups that I had were as follows:
- Extra ball: would spawn in another ball (the game only ends if both go offscreen).
- Extra power: the ball deals 2 damage to bricks rather than one
- Extra points: would give a fixed increase in points (for example, 50)
- Extra life: would give the player an extra life instead of the game restarting.

## Libraries Used
- SDL3
- nlohmann-json

(these are packaged with the release, there is no need to download them.)
