# Battleship for CS1B
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
