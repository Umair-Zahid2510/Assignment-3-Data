#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Node structure for games
class GameNode {
public:
    long long gameId;
    char* gameName;
    char* developer;
    char* publisher;
    double price;
    int playerCount;
    GameNode* left;
    GameNode* right;

    GameNode(long long id, const char* name, const char* dev, const char* pub, double p, int count) {
        gameId = id;
        gameName = new char[strlen(name) + 1];
        strcpy(gameName, name);
        developer = new char[strlen(dev) + 1];
        strcpy(developer, dev);
        publisher = new char[strlen(pub) + 1];
        strcpy(publisher, pub);
        price = p;
        playerCount = count;
        left = right = nullptr;
    }

    ~GameNode() {
        delete[] gameName;
        delete[] developer;
        delete[] publisher;
    }
};

// Linked list node for games played by a player
struct GamePlayedNode {
    long long gameId;
    GamePlayedNode* next;
};

// Player node structure
class PlayerNode {
public:
    long long playerId;
    char* playerName;
    GamePlayedNode* gamesPlayed;
    PlayerNode* left;
    PlayerNode* right;
    int height;

    PlayerNode(long long id, const char* name) {
        playerId = id;
        playerName = new char[strlen(name) + 1];
        strcpy(playerName, name);
        gamesPlayed = nullptr;
        left = right = nullptr;
        height = 1;
    }

    ~PlayerNode() {
        delete[] playerName;

        // Free the linked list of games played
        GamePlayedNode* current = gamesPlayed;
        while (current != nullptr) {
            GamePlayedNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class PlayerBST {
private:
    PlayerNode* root;

    // Helper function for insertion
    PlayerNode* insertHelper(PlayerNode* node, PlayerNode* newNode) {
        if (node == nullptr) return newNode;

        if (newNode->playerId < node->playerId) {
            node->left = insertHelper(node->left, newNode);
        } else if (newNode->playerId > node->playerId) {
            node->right = insertHelper(node->right, newNode);
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    int getHeight(PlayerNode* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Helper function for deleting a node
    PlayerNode* deleteNode(PlayerNode* node, long long playerId) {
        if (node == nullptr) return nullptr;

        if (playerId < node->playerId) {
            node->left = deleteNode(node->left, playerId);
        } else if (playerId > node->playerId) {
            node->right = deleteNode(node->right, playerId);
        } else {
            if (node->left == nullptr) {
                PlayerNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                PlayerNode* temp = node->left;
                delete node;
                return temp;
            }

            PlayerNode* temp = minValueNode(node->right);
            node->playerId = temp->playerId;
            node->playerName = temp->playerName;
            node->right = deleteNode(node->right, temp->playerId);
        }
        return node;
    }

    PlayerNode* minValueNode(PlayerNode* node) {
        PlayerNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    PlayerBST() : root(nullptr) {}

    void insert(long long id, const char* name) {
        PlayerNode* newNode = new PlayerNode(id, name);
        root = insertHelper(root, newNode);
    }

    // Add a game to a player's list
    void addGame(PlayerNode* player, long long gameId) {
        GamePlayedNode* newGame = new GamePlayedNode();
        newGame->gameId = gameId;
        newGame->next = player->gamesPlayed;
        player->gamesPlayed = newGame;
    }

    bool hasPlayed(long long playerId, long long gameId) {
        PlayerNode* player = searchPlayer(playerId);
        if (player == nullptr) return false;

        GamePlayedNode* current = player->gamesPlayed;
        while (current != nullptr) {
            if (current->gameId == gameId) return true;
            current = current->next;
        }
        return false;
    }

    PlayerNode* searchPlayer(long long playerId) {
        PlayerNode* current = root;
        while (current != nullptr) {
            if (current->playerId == playerId) return current;
            else if (playerId < current->playerId) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    void deletePlayer(long long playerId) {
        root = deleteNode(root, playerId);
    }

    // Save data to a file using Preorder Traversal
    void saveData(const char* filename) {
        ofstream file(filename);
        if (file.is_open()) {
            saveDataHelper(root, file);
            file.close();
        }
    }

    void saveDataHelper(PlayerNode* node, ofstream& file) {
        if (node == nullptr) return;
        file << node->playerId << "," << node->playerName << endl;
        saveDataHelper(node->left, file);
        saveDataHelper(node->right, file);
    }

    ~PlayerBST() {
        clear(root);
    }

    void clear(PlayerNode* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main() {
    PlayerBST playerTree;

    // Load players and games from files
    playerTree.insert(232510, "John Doe");
    playerTree.saveData("SavedPlayers.csv");

    return 0;
}
