#!/bin/bash

qmake -project "QT+=widgets" .
qmake -o Makefile fun-othello.pro
