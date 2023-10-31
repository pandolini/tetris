#include <iostream>
#include <threepp/extras/imgui/ImguiContext.hpp>
#include <threepp/threepp.hpp>

#include "Blocks.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Render.hpp"

int main() {
    tetris::Blocks b;
    tetris::Render r;

    r.initializeScene();
    b.getTetronimo(0, 1);
    r.renderScene();
    return 0;
}