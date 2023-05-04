Title - InfiniteRunner
By - Tor Nordmark, GP22

Description - A simple Infinite Runner game made in Unreal using as much C++ only programming as possible.


								Features
								Part 1
- Movement
Early movement system is based on changing the velocity in X axis, listening to an InputAction. Jump uses Unreal's inbuilt Jump code provided in MovementComponent.

Left - A
Right - D
Jump - Spacebar

- Scrolling Platforms
The game handles the scrolling platforms by having a blueprint of the c++ class LevelSpawner.
At the start of the game, three platforms are spawned of the Flatground type and will then spawn a random one whenever an old platform is destroyed. Each platform is stored in a TArray in the order they are spawned.
At each tick they are moved by a set amount of units and when the oldest platform, which is the one furthest to the left, reaches a certain X axis threshold it is removed from the TArray and destroyed.
After that one is destroyed, a new platform is picked at randomly from a list and spawned.


- Traps and Projectiles
Currently the only Trap is a pitfall that is created as part of one of the many platforms called Flathole. It interacts with the player by the simply expediency of letting Unreal's gravity drop them.
Beneath the scrolling platforms is a Damager, a utilitarian collision box that checks if the player is overlapping it. On overlap it tells the RunnerCharacter to run Damaged function.
This will likely remain the same for the forseeable future and is simple enough to implement with other traps.

- Lives
Currently the player has 3 lives, but they are not actually doing anything. It is simply an integer that starts at 3 and counts down. At 0 the player will lose, but that is for a future update.

- Respawn
On running Damaged function, the player character is put back to spawn position and receives a grace period at currently 2 seconds. During this time a platform is spawned under the player that stops them from falling through holes.
In future they will also make it impossible to run the Damaged function until the grace period is done, meaning you can move through traps without harm.

- Animations
The only Blueprint system is a simple animation switch that checks if the player is falling or not. On falling they play the falling animation, otherwise it plays the standard running animation.
As of currently, I have no plans on adding or changing this system.

- Known Bugs
1. Running over a hole while grace period is active causes the player to accelerate rapidly. This is caused because the player moves forward by a set speed and the platforms moves backward at a set speed. Only the grace platform does not move so the player will not face resistance.
2. Despite the platform scrolling speed and the player speed is set to the same velocity, they are not moving at the same speed. Reason for this is currently unknown.


								Changelog Part 2
Added flying dangerzones called Arrows in commit 68fd2c1c1814eda3015d72b1cf895c8bfaa4d9cc
