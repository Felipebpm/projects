// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "fractals.h"
#include <cmath>
using namespace std;

/* Uses recursion to draw Sierpinski Triangle of nth order.
 * args: int order (Order of Triangle),
 * double x (x coordinate of reference point),
 * doiuble y (y coordinate of reference point),
 * double size (size of triangle side),
 * GWindow window (window where triangle is drawn)
 */
void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {
    if (x < 0 || y < 0 || size < 0 || order < 0) {
        // Check if user input is valid.
        throw "Input numbers must be positive";
    }
    else {
        if (order == 1) {
            // draws triangle.
            window.drawPolarLine(window.drawPolarLine(window.drawPolarLine(x, y, size, 300), size, 60), size, 180);
        }
        else if (order > 1) {
            // uses self-similarity in triangle to apply recursion.
            drawSierpinskiTriangle(window, x, y, size / 2, order - 1);
            drawSierpinskiTriangle(window, x + size / 2, y, size / 2, order - 1);
            drawSierpinskiTriangle(window, x + size / 4, y + size * sqrt(3) / 4, size / 2, order - 1);
        }
    }
}

/* Uses recursion to chancge the color of a certain object.
 * args: int color (RGB representation of color to be applied),
 * int x (x coordinate of starting point),
 * int y (y coordinate of starting point),
 * GWindow window (window where triangle is drawn)
 * return: 0
 */
int floodFill(GWindow& window, int x, int y, int color) {
    if (!window.inCanvasBounds(x, y)) {
        // checks for valid input.
        throw "Inputs must be within bounds.";
    }
    int pixelColor = window.getPixel(x, y);
    if (pixelColor == color) {
        return 0;
    }
    window.setPixel(x, y ,color);
    if (window.inCanvasBounds(x + 1, y) && pixelColor == window.getPixel(x + 1, y)) {
        // checks if the pixel on the right has the same color as pixel in question.
        floodFill(window, x + 1, y, color);
    }
    if (window.inCanvasBounds(x, y - 1) && pixelColor == window.getPixel(x, y - 1)) {
        // checks if the pixel on the bottom has the same color as pixel in question.
        floodFill(window, x, y - 1, color);
    }
    if (window.inCanvasBounds(x - 1, y) && pixelColor == window.getPixel(x - 1, y)) {
        // checks if the pixel on the left has the same color as pixel in question.
        floodFill(window, x - 1, y, color);
    }
    if (window.inCanvasBounds(x , y + 1) && pixelColor == window.getPixel(x, y + 1)) {
        // checks if the pixel on the top has the same color as pixel in question.
        floodFill(window, x, y + 1, color);
    }
    return 0;
}
