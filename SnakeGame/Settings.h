#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

// The size of the window.
constexpr int screenWidth{ 1600 };
constexpr int screenHeight{ 900 };

// The size of the playing field.
constexpr int fieldWidth{ 1300 };
constexpr int fieldHeight{ 880 };

// The delay between updates.
constexpr int millisecondsDelay{ 200 };

// The radius of a snake segment.
constexpr int kRadius{ 10 };