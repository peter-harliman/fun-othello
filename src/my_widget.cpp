/*
   Copyright 2016 Peter Harliman Liem <peter.harliman@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <QtGui>
#include <QString>
#include "my_widget.h"
#include "logger.h"

my_widget::my_widget ( QWidget *parent )
    : QWidget( parent ) {

    int i, j;

    /* create grid layout */
    gridLayout = new QGridLayout;

    turn = STATE_WHITE;

    /* create Push buttons */
    for (i = 0; i < max_row; i++) {
        for (j = 0; j < max_column; j++) {
            grid[i][j] = new my_button();
            gridLayout->addWidget(grid[i][j], i, j);

            std::cout << "Created " << grid[i][j] << std::endl;

            /* connect signals */
            connect(grid[i][j], SIGNAL(clicked()), this, SLOT(button_clicked())) ;

            if ((i == 3 && j == 4) || (i == 4 && j == 3))
                grid[i][j]->update_state(STATE_WHITE);
            else if ((i == 3 && j == 3) || (i == 4 && j == 4))
                grid[i][j]->update_state(STATE_BLACK);
            else
                grid[i][j]->update_state(STATE_BLANK);

            grid[i][j]->row = i;
            grid[i][j]->col = j;
        }
    }

    /* create scoreboard */
    score = 0;
    scoreboard = new QLabel(QString::number(score));
    gridLayout->addWidget(scoreboard);

    /* construct layouts */
    setLayout(gridLayout) ;
}

void my_widget::button_clicked() {
    my_button* obj = static_cast<my_button*> (sender());

    logger::log_verbose("Button clicked");
    std::cout << obj << std::endl;

    obj->update_state(turn);
    score += turn;

    /* update other boxes */
    button_flip(obj->row, obj->col,  1, 0);
    button_flip(obj->row, obj->col, -1, 0);
    button_flip(obj->row, obj->col, 0,  1);
    button_flip(obj->row, obj->col, 0, -1);
    button_flip(obj->row, obj->col,  1, 1);
    button_flip(obj->row, obj->col, -1, 1);
    button_flip(obj->row, obj->col, 1,  1);
    button_flip(obj->row, obj->col, 1, -1);

    /* toggle turn */
    if (turn == STATE_WHITE)
        turn = STATE_BLACK;
    else if (turn == STATE_BLACK)
        turn = STATE_WHITE;

    scoreboard->setText(QString::number(score));
}

void my_widget::button_flip(int x, int y, int x_axis, int y_axis)
{
    int i, j;

    for (i = x + x_axis, j = y + y_axis;
            i >= 0 && j >=0 && i < max_row && j < max_column;
            i+=x_axis, j+=y_axis) {
        if (grid[i][j]->state == STATE_BLANK)
            break; /* no flip */
        else if (grid[i][j]->state == turn) {
            /* move backward and flip */
            i -= x_axis;
            j -= y_axis;
            while (i != x || j != y) {
                grid[i][j]->update_state(turn);
                score += turn * 2;
                i -= x_axis;
                j -= y_axis;
            }
            break;
        } else
            continue; /* keep looking */
    }
}

void my_button::update_state(enum button_state_e new_state) {
    const char* text;

    this->state = new_state;

    switch (new_state) {
    case STATE_BLANK:
        text = " ";
        break;
    case STATE_WHITE:
        text = "W";
        break;
    case STATE_BLACK:
        text = "B";
        break;
    default:
        return;
    }

    this->setText(text);
}
