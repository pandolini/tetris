
#ifndef TETRIS_RENDER_HPP
#define TETRIS_RENDER_HPP
#include "Blocks.hpp"
#include "Board.hpp"
#include "Input.hpp"
#include <threepp/threepp.hpp>

namespace tetris {

    class Render {// Inspiration taken from example in threepp
    public:
        Render(float width, float height);
        std::shared_ptr<threepp::Mesh> createPlane(const threepp::Vector3& pos, const threepp::Color& color);
        std::shared_ptr<threepp::Mesh> createBox(const threepp::Vector3& pos, const threepp::Color& color);
        void initializeScene();

    private:
        float width_;
        float height_;
    };

}// namespace tetris

#endif//TETRIS_RENDER_HPP