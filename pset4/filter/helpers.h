#include "bmp.h"

// Obscure with random color adjustments
void deepfry(int height, int width, RGBTRIPLE image[height][width]);

// Produce negative image
void negative(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

void edgeRow(int row, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], bool up, bool down);

void edgePixel(int row, int column, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], bool up, bool down, bool left, bool right);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

void blurRow(int row, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], int up, int down);

void blurPixel(int row, int column, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], int up, int down, int left, int right);

void increase(RGBTRIPLE pixel, int *xB, int *xG, int *xR, int *yB, int *yG, int *yR, int xfactor, int yfactor);

int min(int a, int b);

int max(int a, int b);

void overwrite(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width]);
