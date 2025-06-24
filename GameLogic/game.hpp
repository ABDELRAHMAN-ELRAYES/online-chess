#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include "piece.h"
#include <string>
#include <memory>

// Express cell row and column
using Position = std::pair<int, int>;

// Express player color
enum class Player
{
    WHITE,
    BLACK
};

// Express Game State
enum class GameState
{
    RUNNING,
    CHECKMATE,
    STALEMATE,
    DRAW
};

// Express chosen cell piece and position
struct Cell
{
    Piece *piece;
    Position position;
};

// The size of the board Matrix(RowsxColumns)
const int SIZE = 8;
class Game
{
private:
    // Boar Type -> define the game board or a chunk of it
    using Board = std::vector<std::vector<std::unique_ptr<Piece>>>;
    Board _board;

    // Current Player
    Player _player;

    // Game State
    GameState _gameState;

    // Forming the start state of game board(Top BLACK chunk, Bottom WHITE chunk, Middle empty chunk)
    /*
        B B B B B B B B
        B B B B B B B B
        E E E E E E E E
        E E E E E E E E
        E E E E E E E E
        E E E E E E E E
        W W W W W W W W
        W W W W W W W W
    */
    // Return WHITE player chunk of the board(ROWS -> 0,1, COLUMNS -> (0->7))
    Board getWhitePiecesBoardChunk();

    // Return BLACK player chunk of the board(ROWS -> 6,7, COLUMNS -> (0->7))
    Board getBlackPiecesBoardChunk();

    // Initialize full game board
    Board getInitialGameBoard();

    // Switch Player turns(return a message that the player switched)
    std::string switchPlayer();

public:
    Game() : _board(getInitialGameBoard()), _player(Player::WHITE), _gameState(GameState::RUNNING) {}
    virtual ~Game() = default;
    // Click on specific cell on the board must return cell information(consists of type of the piece and the position of this cell(old piece position ))
    // A Player choose a cell to move a piece from and another cell to move the piece to

    /**
     * @brief Check if it is the player turn, Check the pice belong to current player and Get all available moves for a piece on a given cell.
     * @param cell The cell containing the piece chosen to be moved.
     * @return std::vector<Position> List of available move positions.
     */
    std::vector<Position> movePieceFrom(Cell cell);

    /**
     * @brief Check the if the chosen cell is available to move the piece to.
     * @param cell The cell chosen to move the piece to.
     * @return std::string (a message as a result for action success or fail).
     */
    std::string movePieceTo(Cell cell);

    // Return current board
    Board getGameBoard() const;

    // Return current Player
    Player getPlayer() const;

    // Check if the game is over
    bool isTheGameOver();
};

#endif