//
// Created by aca on 3.2.21..
//

#ifndef RG_3D_SAH_CHESSFIGURE_H
#define RG_3D_SAH_CHESSFIGURE_H

#include "Model.h"
#include "Shader.h"

enum type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum color {
    BLACK,
    WHITE
};

enum status {
    INACTIVE,
    ACTIVE
};

class ChessFigure {
    type figure_type;
    color figure_color;
public:
    Model *model;
    std::pair<int, int> position; // [0][0] is top left of the board
    status figure_status = INACTIVE;
    ChessFigure(Model *model, std::pair<int, int> position, type figure_type, color figure_color);
    void draw(Shader &shader);
};


#endif //RG_3D_SAH_CHESSFIGURE_H
