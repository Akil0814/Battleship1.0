# BattleShip
This’s a BattleShip game based on the **[EasyX](https://easyx.cn/)** Graphics Library,There are currently two game modes: Local PVP and PVE. <br>

## About the Code
This code is for CS1B final project

## Class and Function Design
### Player
<details>
  <summary>Player class</summary>
  
#### **Key Responsibilities：**
#### Ship Lifecycle

-   `setup_ship()` / `put_ship()` → pure virtual, forcing derived classes to implement how and when ships are initialized and placed.
    
-   `delete_all_ship()`:
    
    -   Frees heap-allocated `Ship*` objects (a classic raw pointer cleanup pattern—might switch to `unique_ptr` in the future if you’re brave enough).
        

####  Ship Drawing

-   `draw_all_ship()` (overloaded):
    
    -   Draws all ships either on the left or right side.
        
    -   Uses the ship’s own `draw()` and `draw_right()` methods to handle rendering logic per side.
        

####  Board Interactions

-   `check_pos_can_hit(x, y)`:
    
    -   If the given position is valid and hittable, update the board and return `true`.
        
-   `check_board_available(x, y)`:
    
    -   Just checks if the target cell is available (not already hit or invalid).
        
-   `update_board(x, y)`:
    
    -   For manually updating a cell—used in gameplay.
        
-   `check_pos_type(x, y)`:
    
    -   Returns the current cell type (like empty, ship, hit, etc.).
        
-   `get_ship_count_index_on_board()`:
    
    -   Used to track remaining unhit ship parts—important for win condition checking.
        

####  Board Drawing

-   `draw_player_board(...)` (3 overloads):
    
    -   Draws board either left/right and covered/uncovered.
        
    -   Smart overload design, though could use default params to make it even cleaner: `draw_player_board(bool is_left = true, bool cover_ship = true)`.

#### Human Player
Inherited from **`Player`**

#### Computer Player
Inherited from **`Player`**

</details>

### Scene

### Board
<details>
  <summary> Board class</summary>
#### Board Setup & Reset

-   `set_board()`:
    
    -   Initializes the board to all `IS_EMPTY` values (0).
        
    -   Sets pixel dimensions (`board_height`, `board_width`) based on grid size and `base_width`.
        

####  Ship Management

-   `set_ship(size, is_horizontal, x, y)`:
    
    -   Places a ship of a given size at the specified position and orientation.
        
    -   Fails if the ship goes out of bounds or overlaps another ship.
        
    -   Increments `ship_count_index`.
        
-   `ship_moved(...)`:
    
    -   Removes a ship from the board (sets its grid to `IS_EMPTY`).
        
    -   Decrements `ship_count_index` for each removed cell.
        

####  Board Updates

-   `update_board(x, y)`:
    
    -   If a ship is hit at (x, y), marks it as `IS_HIT` and decrements `ship_count_index`.
        
    -   If the position was empty, marks it as `IS_CHEAKED` (yes, typo noted—it should be `CHECKED`, but fine…).
        
-   `check_board(x, y)`:
    
    -   Validates if a position is in range and not previously hit or checked.
        

####  Board Rendering

-   Uses EasyX to draw the board visually:
    
    -   `draw_player_board_left()` / `draw_player_board_right()`:
        
        -   Renders full board with ships visible.
            
    -   `draw_player_board_left_end()` / `draw_player_board_right_end()`:
        
        -   Hides ships (for showing only hits/misses to opponents).
            
    -   `putimage_alpha(...)`: Internal method to draw images with alpha blending using GDI’s `AlphaBlend`.
        

#### Utility Functions

-   `get_board_type(x, y)`: Returns the current status of a grid cell.
    
-   `get_width()` / `get_height()`: Dimensions in pixels.
    
-   `get_ship_count_index()`: Remaining ship units (used to determine win/loss).
    
-   `show_board()`: Console debug output for board state.


</details>

### Button

#### **Main Features:**

<details>
  <summary>Button class</summary>
-   **Image Management:**
    
    -   `set_images(...)`: Assigns different images for idle, hover, and pressed states.
        
    -   These are stored as raw `IMAGE*` pointers, so be careful with their lifecycle—this class doesn't manage memory for them.
        
-   **Positioning:**
    
    -   `set_position(x, y)`: Sets the button's top-left position, and calculates its bounding box (`RECT region`) based on the `img_idle` size.
        
-   **Drawing Logic:**
    
    -   `draw()`: Renders the correct image depending on the current state (`Idle`, `Hovered`, `Pushed`).
        
-   **Event Handling:**
    
    -   `process_event(msg)`: Accepts an `ExMessage` (EasyX event) and updates the button’s internal state based on mouse actions:
        
        -   On `WM_MOUSEMOVE`, checks if the cursor is over the button.
            
        -   On `WM_LBUTTONDOWN`, marks it as pressed if clicked.
            
        -   On `WM_LBUTTONUP`, sets `is_clicked` if the button was previously pressed.
            
-   **Click State:**
    
    -   `reset_click()`: Clears the `is_clicked` flag—meant to be called after the click has been "handled".
        
    -   `is_clicked_now()`: Returns whether the button was just clicked.
        
-   **Utility Getters:**
    
    -   Methods to retrieve the button’s size and position (`get_width()`, `get_height()`, `get_left()`, `get_top()`).

####  **Private Members:**

-   `Status enum`: Tracks button state (Idle / Hovered / Pushed).
    
-   `RECT region`: Defines the clickable area of the button.
    
-   `IMAGE*` pointers: Hold different button graphics.
    
-   `is_clicked`: A flag that becomes `true` when the button was clicked and needs to be reset manually.
</details>

### Ship
<details>
  <summary>Ship class</summary>
  
- ####  **Main Responsibilities:**

-   **Abstract Interface:**
    
    -   `setup_ship()` and `put_ship()` are **pure virtual functions**, meaning derived classes must implement how ships are initialized and placed.
        
-   **Ship Management:**
    
    -   `vector<Ship*> ship_list` holds pointers to the player's ships.
        
    -   `delete_all_ship()` deletes all ships to free memory.
        
    -   `draw_all_ship()` draws ships either on the left or right side of the screen depending on the context.
        
-   **Board Operations** (handled via the `Board` class):
    
    -   `check_pos_can_hit(x, y)` checks if a coordinate can be hit and updates the board accordingly.
        
    -   `check_board_available(x, y)` checks if a spot is available.
        
    -   `update_board(x, y)` manually updates the board status at a given coordinate.
        
    -   `check_pos_type(x, y)` returns the type of cell at a given position.
        
    -   `get_ship_count_index_on_board()` returns the count of ship tiles that have been hit.
        
-   **Board Drawing:**
    
    -   `draw_player_board(...)` has multiple overloads to draw the board on the left or right side, and optionally with or without ship visibility (e.g., hiding opponent ships).

#### **Member Variables:**

-   `ship_list`: List of ship pointers currently owned by the player.
    
-   `board`: The player's personal board.
    
-   `num_of_ship`: Default number of ships (5).
    
-   `size_of_base`: Base size used for ship dimensions, usually tied to image width.
    
-   `is_win`: A flag indicating whether the player has won (currently unused).
</details>

### Scene Manaer
The program use Scene Manager to switch between game scenes.
The idea about scene manager is from [VoidmatrixHeathcliff (Voidmatrix)](https://github.com/VoidmatrixHeathcliff).
about how Scene Manager work you can chack on the video [Scene Manager](https://www.youtube.com/watch?v=iY4SjVaV9So&t=53s)
