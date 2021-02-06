//
// Created by aca on 6.2.21..
//

#ifndef RG_3D_SAH_CHESSBOARD_H
#define RG_3D_SAH_CHESSBOARD_H

#include "Shader.h"

class ChessBoard {
    unsigned VBO, VAO, EBO;
public:
    ChessBoard();
    void draw();
    void del();
};


#endif //RG_3D_SAH_CHESSBOARD_H
