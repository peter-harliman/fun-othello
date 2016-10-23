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

#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

enum button_state_e {
    STATE_BLACK = -1,
    STATE_BLANK = 0,
    STATE_WHITE = 1,
};

class my_button : public QPushButton {
    Q_OBJECT

public:
    void update_state(enum button_state_e new_state);
    int row;
    int col;
    enum button_state_e state;

private:

};


class my_widget : public QWidget {

    Q_OBJECT
public:
    my_widget( QWidget *parent = 0 ) ;

private slots:
    void button_clicked();
    void button_flip(int x, int y, int x_axis, int y_axis);

private :
    static const int max_column = 8;
    static const int max_row = 8;
    button_state_e turn;
    my_button* grid[max_column][max_row];
    QGridLayout *gridLayout;
};
#endif
