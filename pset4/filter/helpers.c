#include "helpers.h"

// Obscure with random color adjustments
void deepfry(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            filtered[i][j].rgbtBlue = max(min(image[i][j].rgbtBlue + (rand() % 40) - 20, 255), 0);
            filtered[i][j].rgbtGreen = max(min(image[i][j].rgbtGreen + (rand() % 40) - 20, 255), 0);
            filtered[i][j].rgbtRed = max(min(image[i][j].rgbtRed + (rand() % 40) - 20, 255), 0);
        }
    }
    overwrite(height, width, image, filtered);
    return;
}

// Produce negative image
void negative(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            filtered[i][j].rgbtBlue = 255 - image[i][j].rgbtBlue;
            filtered[i][j].rgbtGreen = 255 - image[i][j].rgbtGreen;
            filtered[i][j].rgbtRed = 255 - image[i][j].rgbtRed;
        }
    }
    overwrite(height, width, image, filtered);
    return;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            filtered[i][j].rgbtBlue = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            filtered[i][j].rgbtGreen = filtered[i][j].rgbtBlue;
            filtered[i][j].rgbtRed = filtered[i][j].rgbtBlue;
        }
    }
    overwrite(height, width, image, filtered);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            filtered[i][width - j - 1] = image[i][j];
        }
    }
    overwrite(height, width, image, filtered);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    blurRow(0, height, width, image, filtered, 0, 1);
    for (int i = 1; i < height - 1; i++)
    {
        blurRow(i, height, width, image, filtered, 1, 1);
    }
    blurRow(height - 1, height, width, image, filtered, 1, 0);
    overwrite(height, width, image, filtered);
    return;
}

void blurRow(int row, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], int up, int down)
{
    blurPixel(row, 0, height, width, image, filtered, up, down, 0, 1);
    for (int j = 1; j < width - 1; j++)
    {
        blurPixel(row, j, height, width, image, filtered, up, down, 1, 1);
    }
    blurPixel(row, width - 1, height, width, image, filtered, up, down, 1, 0);
    return;
}

void blurPixel(int row, int column, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], int up, int down, int left, int right)
{
    int sumBlue = 0;
    int sumGreen = 0;
    int sumRed = 0;
    int area;
    
    for (int k = row - left; k <= row + right; k++)
    {
        for (int l = column - up; l <= column + down; l++)
        {
            sumBlue += image[k][l].rgbtBlue;
            sumGreen += image[k][l].rgbtGreen;
            sumRed += image[k][l].rgbtRed;
        }
    }
    
    area = (up + 1 + down) * (left + 1 + right);
    filtered[row][column].rgbtBlue = sumBlue / area;
    filtered[row][column].rgbtGreen = sumGreen / area;
    filtered[row][column].rgbtRed = sumRed / area;
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*filtered)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    edgeRow(0, height, width, image, filtered, false, true);
    for (int i = 1; i < height - 1; i++)
    {
        edgeRow(i, height, width, image, filtered, true, true);
    }
    edgeRow(height - 1, height, width, image, filtered, true, false);
    overwrite(height, width, image, filtered);
    return;
}

void edgeRow(int row, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], bool up, bool down)
{
    edgePixel(row, 0, height, width, image, filtered, up, down, false, true);
    for (int j = 1; j < width - 1; j++)
    {
        edgePixel(row, j, height, width, image, filtered, up, down, true, true);
    }
    edgePixel(row, width - 1, height, width, image, filtered, up, down, true, false);
    return;
}

void edgePixel(int row, int column, int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width], bool up, bool down, bool left, bool right)
{
    int xsumBlue = 0;
    int xsumGreen = 0;
    int xsumRed = 0;
    int ysumBlue = 0;
    int ysumGreen = 0;
    int ysumRed = 0;
    
    if (up)
    {
        if (left)
        {
            increase(image[row - 1][column - 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, -1, -1);
        }
        increase(image[row - 1][column], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, 0, -2);
        if (right)
        {
            increase(image[row - 1][column + 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, 1, -1);
        }
    }
    if (left)
    {
        increase(image[row][column - 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, -2, 0);
    }
    if (right)
    {
        increase(image[row][column + 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, 2, 0);
    }
    if (down)
    {
        if (left)
        {
            increase(image[row + 1][column - 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, -1, 1);
        }
        increase(image[row + 1][column], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, 0, 2);
        if (right)
        {
            increase(image[row + 1][column + 1], &xsumBlue, &xsumGreen, &xsumRed, &ysumBlue, &ysumGreen, &ysumRed, 1, 1);
        }
    }
    int SobelBlue = min((int) (sqrt((float) (xsumBlue * xsumBlue + ysumBlue * ysumBlue)) + 0.5), 255);
    int SobelGreen = min((int) (sqrt((float) (xsumGreen * xsumGreen + ysumGreen * ysumGreen)) + 0.5), 255);
    int SobelRed = min((int) (sqrt((float) (xsumRed * xsumRed + ysumRed * ysumRed)) + 0.5), 255);
    
    filtered[row][column].rgbtBlue = SobelBlue;
    filtered[row][column].rgbtGreen = SobelGreen;
    filtered[row][column].rgbtRed = SobelRed;
    return;
}

void increase(RGBTRIPLE pixel, int *xB, int *xG, int *xR, int *yB, int *yG, int *yR, int xfactor, int yfactor)
{
    *xB += pixel.rgbtBlue * xfactor;
    *xG += pixel.rgbtGreen * xfactor;
    *xR += pixel.rgbtRed * xfactor;
    *yB += pixel.rgbtBlue * yfactor;
    *yG += pixel.rgbtGreen * yfactor;
    *yR += pixel.rgbtRed * yfactor;
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max(int a, int b)
{
    if (a < b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

void overwrite(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE filtered[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = filtered[i][j];
        }
    }
    free(filtered);
    return;
}