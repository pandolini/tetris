
#include "Game.hpp"

namespace tetris {
    Game::Game(): board(24, 10), clock(), input(elapsedTime) {
        block = Block();
        random = Random();
        tetrominos = {T_Tetromino(), S_Tetromino(), Z_Tetromino(), L_Tetromino(), J_Tetromino(), I_Tetromino(), O_Tetromino()};
        currentType = random.getType();
        nextType = random.getType();
        currentBlock = tetrominos[currentType];
        nextBlock = tetrominos[nextType];

        movedTilesX = 0;
        movedTilesY = 0;
        rotate = 0;
        tetrisScore = 0;
        gameOver = false;
    }

    void Game::inputHandling() {
        switch (currentMovement) {
            case LEFT:
                    movedTilesX += 1;
                    break;
                case RIGHT:
                    movedTilesX -= 1;
                    break;
                case DOWN:
                    movedTilesY += 1;
                    break;
                case ROTATE:
                    rotate += 1;
                    break;
                case DROP:
                    drop = true;
                    break;
            }
        }

    void Game::moveBlock() {
            if (movementAllowed()) {
                currentBlock.move(movedTilesX, movedTilesY);
                currentBlock.rotate(rotate);
                renderTetromino = true;
            }
    }

    bool Game::movementAllowed() {
        if (!gameOver && !board.blockHasInvalidPosition(currentBlock.peak(movedTilesX, movedTilesY, rotate))) {
            return true;
        } else {
            return false;
        }
    }
    void Game::tickDown() {
        if (drop) {
            movedTilesY += 1;
        } else {
            if (clock.getElapsedTime() - lastTick > 0.3) {
                movedTilesY += 1;
                lastTick = clock.getElapsedTime();
            } else {
                inputHandling();
            }
        }
    }

    bool Game::isGameOver() {
        if (renderGame && board.checkGameOver(currentBlock.peak(movedTilesX, movedTilesY, rotate))) {
            return true;
        }
    }

    void Game::update() {
        if (!gameOver && !movementAllowed() && movedTilesY != 0) {
            board.saveBlock(currentBlock.tilePositions(), currentBlock.type);
            tetrisScore = updateScore(tetrisScore, board.countCompleteLines());
            drop = false;
            currentType = nextType;
            nextType = random.getType();
            currentBlock = tetrominos[currentType];
            board.rowCleanUp();
            nextBlock = tetrominos[nextType];
            renderGame = true;
        }
    }
    //Adds points to "score" according to amount of rows filled in "check"
    int Game::updateScore(int score, int check) {
        if (check == 1) {
            score = score + 40;
        } else if (check == 2) {
            score = score + 100;
        } else if (check == 3) {
            score = score + 300;
        } else if (check == 4) {
            score = score + 1200;
        }
        return score;
    }
}// namespace tetris