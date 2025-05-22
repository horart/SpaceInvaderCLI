# OOP GameEngine and SpaceInvader Game
## Requirements
* `ncurces`
* `C++20+`
## Installation
```
sudo apt-get install libncurses5-dev
mkdir build
cd build
cmake ..
make
```

## Running
```
./SpaceInvader
```

## Controls
Use `A` and `D` to move, and `Space` to shoot

## Classes

### Core Engine Classes
#### Core logic classes
*   **`Game`:** The main game loop and object manager. It holds all `GameObject` instances, manages their lifecycle (creation, update, destruction), controls frame timing, and owns the `Renderer`. It uses a template method `createObject` (defined in `game.tpp`) to instantiate game objects.
*   **`GameObject`:** A fundamental base class for most entities in the game. It inherits from `Renderable` and manages an object's position, ID, and a weak pointer to the main `Game` instance. It provides virtual methods for initialization (`init`), updates (`update`, `beforeUpdate`), and destruction (`destroy`, `onDestroy`).
*   **`Renderer`:** An abstract base class defining the interface for rendering operations. It includes pure virtual methods for rendering specific primitive types (`RenderingCell`, `RenderingText`), flushing output, clearing the screen, and getting game dimensions. It also has a concrete `render` method to process `Renderable` objects.
#### Rendering abstractions
*   **`Renderable`:** An abstract interface for objects that can be rendered. It requires derived classes to implement `getPrimitives()` to return a collection of rendering primitives and `getPosition()` to define their location.
*   **`RenderingPrimitive`:** An abstract base class for individual drawable elements. It defines a position and an `accept` method for the visitor pattern (used by `Renderer`).
*   **`RenderingCell`:** A concrete `RenderingPrimitive` representing a single colored cell or character on the screen.
*   **`RenderingText`:** A concrete `RenderingPrimitive` representing a string of text with foreground and background colors.
*   **`RenderIterator`:** A base struct for iterators over rendering primitives.
*   **`PrimitivesIterator`:** An iterator for a collection of `std::shared_ptr<RenderingPrimitive>`.
*   **`CellsIterator`:** An iterator that generates `RenderingCell` objects on-the-fly from a collection of `Point`s and a base color.
*   **`RenderRange`:** An abstract base struct representing a collection of rendering primitives that can be iterated over.
*   **`CellsRange`:** A concrete `RenderRange` that provides `CellsIterator`s to iterate over a collection of points as colored cells.
*   **`PrimitivesRange`:** A concrete `RenderRange` that provides `PrimitivesIterator`s to iterate over a collection of `std::shared_ptr<RenderingPrimitive>`.
#### Natively supported input/display implementations
*   **`CLIRenderer`:** A concrete implementation of `Renderer` that uses the ncurses library to render graphics in the command line interface. It manages color pairs and character output.
*   **`CLIInputManager`:** A concrete implementation of `InputManager` that uses ncurses to get character input from the command line.
#### Default supported managers (game logic level)
*   **`InputManager`:** An abstract base class for handling input. It defines an interface for subscribing/unsubscribing input-aware objects (`InputManaged`) and notifying them of input events.
*   **`InputManaged`:** A class that `GameObject`s can inherit from (virtually) to receive input. It holds a weak pointer to an `InputManager` and provides an `onInput` virtual method.
*   **`ColliderManager`:** Manages collision detection between `ColliderManaged` objects. It allows objects to subscribe/unsubscribe and has a `notify` method to check for and report collisions.
*    **`ColliderManaged`:** A class that `GameObject`s can inherit from (virtually) to participate in collision detection. It requires derived classes to provide a collider type ID and size, and an `onCollision` callback.
#### Utility
*   **`Point`:** A simple struct representing a 2D coordinate with `x` and `y` integer members. It overloads several arithmetic and comparison operators for vector-like operations.

### Game-Specific Classes
#### The game class
*   **`SpaceInvaderGame`:** The main class for the Space Invader game logic, derived from the engine's `Game` class. It initializes and owns game-specific managers (`CLIInputManager`, `ColliderManager`, `SpriteManager`, `EnemyManager`) and game objects like `Player` and `Score`. It handles game-specific setup (`init`), game over logic, and score updates.
#### GameObject derivatives
*   **`Entity`:** A base class for game entities that have health and can collide. It inherits virtually from `ColliderManaged` and manages health, collider ID, size, and a weak pointer to the `SpriteManager`.
*   **`Shooter`:** (Definition not fully provided, but likely a class that provides shooting capabilities, managing cooldowns and bullet creation, probably inheriting from `GameObject`).
*   **`Bullet`:** (Definition not fully provided, but represents a projectile in the game, likely inheriting from `Entity` or `GameObject`, and `ColliderManaged`).
*   **`Player`:** Represents the player-controlled character. It inherits from `InputManaged` (to respond to player input), `Shooter` (to fire projectiles), and `std::enable_shared_from_this`. It handles its own rendering and collision logic.
*   **`Enemy`:** Represents an enemy character in the game. It inherits from `Shooter` (presumably for shooting behavior) and `EnemyManaged` (for management by `EnemyManager`), and `std::enable_shared_from_this`. It handles its own rendering primitives based on its type and color.
#### Game-defined managers
*   **`EnemyManager`:** Manages the behavior and spawning of `Enemy` objects. It controls their collective movement and can trigger new enemy spawns.
*   **`EnemyManaged`:** A class that `Enemy` objects inherit from to be managed by the `EnemyManager`. It provides a `move` method.
*   **`SpriteManager`:** Manages and provides access to sprite data (collections of points or primitives) for various game entities like enemies, player, and bullets. It also provides utility functions for getting entity sizes and random colors.
#### UI game objects
*   **`GameOver`:** A `GameObject` derivative that represents the "Game Over" message or screen. It provides the necessary primitives to display this message.
*   **`Score`:** A `GameObject` derivative responsible for displaying the player's score. It updates its `RenderingText` primitive when the score changes.