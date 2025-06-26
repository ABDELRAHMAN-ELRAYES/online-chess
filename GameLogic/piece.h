#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>

// enum class is used to define a custom type with a limited set of named values.
// It's like saying: "This variable can only be one of these specific options."
//
// In this case, we use enum class Color to represent the two possible sides in a chess game:
// - WHITE
// - BLACK
//
// We use 'enum class' instead of plain 'enum' because:
// - It keeps the names (WHITE, BLACK) scoped inside 'Color' (you must write Color::WHITE)
// - It avoids accidental mixing with other enums or integers
// - It provides better type safety — you can't accidentally assign an int to a Color
//
enum class Color
{
    WHITE,
    BLACK
};

enum class Type
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

class Piece
{
public:
    // I'm using a typedef here to give the std::pair<int, int> an alias named Position
    // because it's more understandable and i don't want to keep writing std::pair<int,int> :)
    using Position = std::pair<int, int>; // row col

    // Using member initializer list here to give performance for the compiler and to directly initialize values
    // and it's better than assigning values like this:
    //
    // Piece(Color color, Type type, Position position) {
    //
    //    this.color = color;
    //    this.type = type;
    //    this.position = position;
    //
    //  }
    Piece(Color color, Type type, Position position)
        : color(color), type(type), position(position) {}

    // Virtual destructor here is very important when using inheritance and deleting derived objects through base class pointers.
    //
    // Without a virtual destructor, only the base class's destructor is called, and the derived class's resources
    // (like memory ) may not be cleaned up properly — this leads to memory leaks.
    //
    // For example:
    //     Piece* p = new King(); // King is a subclass of Piece
    //     delete p;              // Only calls ~Piece() if ~Piece() is not virtual, skips ~King()
    //
    // Making the destructor virtual ensures the correct order:
    //     ~King() is called first, then ~Piece() — cleaning up everything safely.
    //
    // and the reason behind the destructor = default;
    // It's like you'er saying to the compiler:
    // "I need a virtual destructor for correct behavior in inheritance,
    // but I don’t need to write any custom destruction logic."
    virtual ~Piece() = default;

    // these are getter methods all they do is getting the value of a member in the class
    // they are marked as const because they don't change the value of a member
    Color getColor() const { return color; }
    Type getType() const { return type; }
    Position getPosition() const { return position; }

    // This method defines a common interface for all chess pieces to calculate their possible legal moves.
    // It is marked as 'virtual' and '= 0', which makes it a "pure virtual function".
    // That means this class (Piece) is abstract and cannot be used directly — it's only a base for real pieces like King, Queen, etc.
    //
    // Each specific piece (like King or Rook) must override this method and implement its own movement rules.
    //
    // Why we need this:
    // - Every piece has its own movement logic (e.g., bishops move diagonally, knights move in an L-shape)
    // - But we want to treat all pieces the same way in the game logic (like looping through them)
    // - So we define a shared interface here, and let the derived classes handle the details
    //
    //
    // the Parameter board is a reference to the current chess board, represented as a 2D array (8x8) of pointers to pieces.
    //          This allows each piece to "see" other pieces on the board and decide which moves are valid.
    //
    //
    // and it returns a list (vector) of positions (pairs of integers: row, column) where the piece is allowed to move.
    //
    virtual std::vector<Position> availableMoves(const std::vector<std::vector<Piece *>> &board) const = 0;

protected:
    Color color;

    Type type;
    Position position;
};

#endif