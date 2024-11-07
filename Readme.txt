Code Structure
Classes
GameNode: Represents a game entry with attributes:

gameId: Unique identifier for the game.
gameName: Name of the game.
developer: Developer of the game.
publisher: Publisher of the game.
price: Price of the game.
playerCount: Number of players playing the game.
left and right: Pointers to the left and right child nodes in the BST.
PlayerNode: Represents a player entry with attributes:

playerId: Unique identifier for the player.
playerName: Name of the player.
gamesPlayed: Linked list of games the player has played.
left and right: Pointers to the left and right child nodes in the BST.
height: Used to manage the height of nodes for balancing purposes.
PlayerBST: The BST that manages players. The key functionalities include:

Insertion: Add a new player to the BST.
Search: Find a player by their playerId.
Delete: Remove a player from the BST.
Add Game: Assign a game to a player.
Check Game: Check if a player has played a particular game.
Save Data: Save the BST data to a CSV file using preorder traversal.
Usage
Insert a Player:
Use PlayerBST::insert(long long id, const char* name) to add a new player to the BST.
Search for a Player:
Use PlayerBST::searchPlayer(long long playerId) to search for a player by their ID.
Delete a Player:
Use PlayerBST::deletePlayer(long long playerId) to delete a player by their ID.
Assign a Game to a Player:
Use PlayerBST::addGame(PlayerNode* player, long long gameId) to assign a game to a player.
Check if a Player Played a Game:
Use PlayerBST::hasPlayed(long long playerId, long long gameId) to check if a player played a particular game.
Save Player Data to CSV:
Use PlayerBST::saveData(const char* filename) to save the BST data to a CSV file using preorder traversal.


Time Complexity Analysis
1. Insertion (PlayerBST::insert)
Time Complexity: O(log n) for a balanced BST, O(n) for an unbalanced BST.
2. Search (PlayerBST::searchPlayer)
Time Complexity: O(log n) for a balanced BST, O(n) for an unbalanced BST.
3. Deletion (PlayerBST::deletePlayer)
Time Complexity: O(log n) for a balanced BST, O(n) for an unbalanced BST.
4. Adding a Game to a Player (PlayerBST::addGame)
Time Complexity: O(1)
5. Checking if a Player Played a Game (PlayerBST::hasPlayed)
Time Complexity: O(m), where m is the number of games played by the player.
6. Save Data to CSV (PlayerBST::saveData)
Time Complexity: O(n), where n is the number of players in the BST.






