#include "Block.hpp"
#include "Board.hpp"
#include "Input.hpp"
#include "Random.hpp"
#include "Tetrominos.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;
using namespace tetris;

int main() {
    Canvas canvas("Tetris");
    WindowSize tetrisSize{650, 800};
    WindowSize glrSize{800, 800};
    canvas.setSize(tetrisSize);
    GLRenderer glr(glrSize);
    glr.setClearColor(Color::black);
    auto scene = Scene::create();
    auto camera = OrthographicCamera::create();
    camera->position.z = 5;
    camera->position.x = 1.5;
    camera->position.y = 10;
    camera->rotateZ(3.1415);
    camera->zoom = 0.09;
    camera->updateProjectionMatrix();


    Board board = Board();
    Random random = Random();
    std::vector<Block> blocks = {T_Tetromino(), S_Tetromino(), Z_Tetromino(), L_Tetromino(), J_Tetromino(), I_Tetromino(), O_Tetromino()};
    int currentType = random.getType();
    int nextType = random.getType();
    Block currentBlock = blocks[currentType];
    Block nextBlock = blocks[nextType];
    std::shared_ptr<threepp::Group> gridGroup = board.drawGrid();
    scene->add(gridGroup);
    std::shared_ptr<threepp::Group> blockGroup = currentBlock.draw();
    scene->add(blockGroup);
    nextBlock.columnOffset = -4;
    nextBlock.rowOffset = 1;
    std::shared_ptr<threepp::Group> nextBlockGroup = nextBlock.draw();
    scene->add(nextBlockGroup);


    Clock clock;
    Input input{clock.elapsedTime};
    canvas.addKeyListener(&input);

    bool drop = false;
    bool down = false;
    float timeLastDown = clock.getElapsedTime();

    canvas.animate([&] {
        glr.render(*scene, *camera);
        glr.resetState();

        input.previousMovement = input.newMovement;
        input.newMovement = NONE;

        int row = 0;
        int column = 0;
        bool rotate = false;
        if (drop || (clock.getElapsedTime() - timeLastDown) > 0.3) {
            row = 1;
            timeLastDown = clock.getElapsedTime();
        } else {
            switch (input.previousMovement) {
                case LEFT:
                    column = 1;
                    break;
                case RIGHT:
                    column = -1;
                    break;
                case DOWN:
                    row = 1;
                    break;
                case ROTATE:
                    rotate = true;
                    break;
                case DROP:
                    drop = true;
                    break;
            }
        }

        if (!board.checkBlockOutOfGrid(currentBlock.peak(row, column, rotate))) {
            blockGroup->clear();
            if (rotate) {
                currentBlock.rotate();
            }
            currentBlock.move(row, column);
            blockGroup = currentBlock.draw();
            scene->add(blockGroup);
        } else {
            if (row != 0) {
                board.saveBlock(currentBlock.blockPositions(), currentBlock.type);
                drop = false;
                currentBlock.rowOffset = -1;
                currentBlock.columnOffset = 4;

                blockGroup->clear();
                currentType = nextType;
                nextType = random.getType();
                currentBlock = blocks[currentType];
                blockGroup = currentBlock.draw();
                scene->add(blockGroup);

                board.rowCleanUp();
                gridGroup->clear();
                gridGroup = board.drawGrid();
                scene->add(gridGroup);

                nextBlockGroup->clear();
                nextBlock = blocks[nextType];
                nextBlock.rowOffset = 1;
                nextBlock.columnOffset = -4;
                nextBlockGroup = nextBlock.draw();
                scene->add(nextBlockGroup);
            }
        }
    });
    return 0;
}