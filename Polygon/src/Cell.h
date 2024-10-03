#pragma once

#include "Renderer/Renderer2D.h"
#include <SFML/Graphics.hpp>

const static int ROW = 50;
const static int COL = 50;
const int cellsize = 8;

static float xoffset = 16;
static float yoffset = 16;
enum { UP, DOWN, RIGHT, LEFT };
enum {
  RED,
  BLUE,
  BLACK,
  WHITE,
  GRAY,
  PINK,
};
const std::vector<Color> Colors = {
    Color{200, 0, 0, 255},     // RED
    Color{153, 204, 255, 255}, // BLUE
    Color{0, 0, 0, 255},       // BLACK
    Color{255, 255, 255, 255}, // WHITE
    Color{224, 224, 224, 255}, // GRAY
    Color{255, 192, 203, 255}, // PINK
};

class Cell {
public:
  Cell() {
    for (int i = 0; i < 4; i++) {
      wall[i] = true;
      block[i] = false;
    }
    FillColor = Colors[GRAY];
    WallColor = Colors[BLACK];
  }
  Cell &operator=(const Cell &t) {
    this->FillColor = t.FillColor;
    this->WallColor = t.WallColor;
    for (int i = 0; i < 4; ++i) {
      this->wall[i] = t.wall[i];
      this->block[i] = t.block[i];
    }
    return *this;
  }
  void Draw(float row, float col) {
    float thick = 2;
    Renderer2D::DrawFillRectangle(col * cellsize + xoffset,
                                  row * cellsize + yoffset, cellsize, cellsize,
                                  FillColor);
    for (int i = 0; i < 4; i++) {
      if (wall[i] == true) {
        float x[2], y[2];
        switch (i) {
        case LEFT:
          x[0] = col * cellsize + thick / 4 + 1;
          y[0] = row * cellsize;
          x[1] = x[0];
          y[1] = y[0] + cellsize;
          break;
        case RIGHT:
          x[0] = (col + 1) * cellsize - thick / 4 + 1;
          y[0] = row * cellsize;
          x[1] = x[0];
          y[1] = y[0] + cellsize;
          break;
        case UP:
          x[0] = col * cellsize;
          y[0] = row * cellsize + 0;
          x[1] = x[0] + cellsize;
          y[1] = y[0];
          break;
        case DOWN:
          x[0] = col * cellsize;
          y[0] = (row + 1) * cellsize - 0;
          x[1] = x[0] + cellsize;
          y[1] = y[0];
          break;
        }
        x[0] += xoffset;
        x[1] += xoffset;
        y[0] += yoffset;
        y[1] += yoffset;
        Renderer2D::DrawLine(x[0], y[0], x[1], y[1], thick / 2, WallColor);
      }
    }
  }
  Color FillColor;
  Color WallColor;
  bool wall[4];
  bool block[4];
};
