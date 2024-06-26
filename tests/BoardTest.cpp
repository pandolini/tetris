
#include "Board.hpp"
#include "Tetrominos.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace tetris;

    TEST_CASE("Block rotation near board boundaries", "[Block][Board]") {  //This unit test was actually quite useful, as it helped me find a bug in the use of the Block::rotate function in the game loop.

        Z_Tetromino z;
        S_Tetromino s;
        Board board(24, 10);

        SECTION("S rotation near left boundary") {
            s.rotate(1);
            s.move(4, 0);
            REQUIRE(board.blockHasInvalidPosition(s.tilePositions()) == false);
            s.rotate(1);
            REQUIRE(board.blockHasInvalidPosition(s.tilePositions()) == true);
        }

        SECTION("Z rotation near right boundary") {
            z.rotate(1);
            z.move(-4, 0);
            REQUIRE(board.blockHasInvalidPosition(z.tilePositions()) == false);
            z.rotate(1);
            REQUIRE(board.blockHasInvalidPosition(z.tilePositions()) == true);
        }
    }

TEST_CASE("saveBlock operation", "[Board]") {

    Board board(24, 10);

    SECTION("Constructor") {
        REQUIRE(board.getGridTileType(0, 0) == SpawnZone);
        REQUIRE(board.getGridTileType(0, 23) == EmptyTile);
    }

    SECTION("saveBlock and getGridTileType operation") {
        std::vector<threepp::Vector2> tiles = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
        board.saveBlock(tiles, T);
        for (auto tile : tiles) {
            REQUIRE(board.getGridTileType(tile.x, tile.y) == T);
        }
    }
}