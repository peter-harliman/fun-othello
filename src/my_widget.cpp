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

    /* create Push buttons */
    for (i = 0; i < max_column; i++) {
        for (j = 0; j < max_row; j++) {
            grid[i][j] = new QPushButton();
            gridLayout->addWidget(grid[i][j], i, j);

            /* connect signals */
            connect(grid[i][j], SIGNAL(clicked()), this, SLOT(button_clicked())) ;
        }
    }

    /* construct layouts */
    setLayout(gridLayout) ;
}

void my_widget::button_clicked( ) {
    logger::log_verbose("Button clicked!");
}
