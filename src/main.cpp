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

#include "logger.h"
#include <QApplication>
#include "my_widget.h"

int logger::level_setting;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    my_widget the_widget;

    logger::set_log_level(0);
    logger::log_verbose("Enter");

    logger::log_verbose("Exit");

    the_widget.show();
    return app.exec();
}
