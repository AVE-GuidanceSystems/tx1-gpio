#!/bin/bash
g++ ./src/exampleGPIOApp.cpp -Wall -o ./exampleGPIOApp `pkg-config --cflags glib-2.0 --libs glib-2.0` ./src/drv2605.cpp ./src/drv2605.h ./src/jetsonGPIO.c
