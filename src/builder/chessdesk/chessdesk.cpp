#include "chessdesk.h"

void ChessDeskBuilder::build()
{
    _model = std::make_shared<Model>();
    _model->_is_chess_desk = true;
    double init = - BASE_CELL_SIZE * 4;
    double start_x = init;
    double div_cell = BASE_CELL_SIZE / 2;

    for (size_t i = 0; i < 8; i++)
    {
        bool flag = i % 2;
        double start_y = init;

        for (size_t j = 0; j < 8; j++)
        {
            std::shared_ptr<Object> obj;

            if (flag)
                obj = std::make_shared<Box>(Vector3D(start_x + div_cell, start_y + div_cell, - div_cell),
                                            Vector3D(BASE_CELL_SIZE, BASE_CELL_SIZE, BASE_CELL_SIZE), blackcell);
            else
                obj = std::make_shared<Box>(Vector3D(start_x + div_cell, start_y + div_cell, - div_cell),
                                            Vector3D(BASE_CELL_SIZE, BASE_CELL_SIZE, BASE_CELL_SIZE), whitecell);

            _model->add(obj);

            flag = !flag;
            start_y += BASE_CELL_SIZE;
        }

        start_x += BASE_CELL_SIZE;
    }

    _model->generate_kd_tree();
}
