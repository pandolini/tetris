#include "Block.hpp"
#include "Board.hpp"
#include "Tetrominos.cpp"
#include <threepp/threepp.hpp>
using namespace threepp;
using namespace tetris;

int main() {
    Canvas canvas("Tetris");
    WindowSize tetrisSize{1200, 1200};
    canvas.setSize(tetrisSize);
    GLRenderer glr(canvas.size());
    glr.setClearColor(Color::blueviolet);
    auto scene = Scene::create();
    auto camera = OrthographicCamera::create();
    camera->position.z = 5;
    camera->position.x = 5.5;
    camera->position.y = 10;
    camera->rotateZ(3.1415);
    camera->zoom = 0.09;
    camera->updateProjectionMatrix();

    Board brd = Board();
    brd.saveBlock(4, 0, 1, 8);
    brd.saveBlock(6, 0, -4, 13);


    brd.printGrid();
    //std::shared_ptr<threepp::Group> grid = brd.drawGrid();
    //scene->add(grid);

    //T_tetronimo T = T_tetronimo();

    canvas.onWindowResize([&](WindowSize size) {
        //        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        glr.setSize(size);
    });

    Clock clock;
    canvas.animate([&] {
        glr.render(*scene, *camera);
        glr.resetState();
        float dt = clock.getDelta();

        std::shared_ptr<threepp::Group> grid = brd.drawGrid();
        scene->add(grid);

        //    std::shared_ptr<threepp::Group> block = T.draw();
        //    scene->add(block);
    });
    return 0;
}