#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            BYTE average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Process sepia colors
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            // Update pixel values
            if (sepiaBlue < 256)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            if (sepiaGreen < 256)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            if (sepiaRed < 256)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // switch the pixel at [0][0] with the one at [0][width-1]
            // [0][1]<-->[0][width - 1 - 1]
            // swith pixels following this criteria [i][j]<-->[i][width - 1 - j]
            // Update pixel values
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of image for reference
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop over all pixels

    // center case
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // Process pixels: box blur - the new value of a pixel is the average
            // of the 9 pixels that make up a 3x3 box centered on the pixel in cuestion

            image[i][j].rgbtBlue =
                round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                       copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                       copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                       copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                      9.0);

            image[i][j].rgbtGreen = round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                                           copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                                           copy[i + 1][j + 1].rgbtGreen) /
                                          9.0);
            image[i][j].rgbtRed = round(
                (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                 copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                 copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                9.0);
        }
    }

    // corners
    // upper left corner
    image[0][0].rgbtBlue = round(
        (copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) /
        4.0);

    image[0][0].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen +
                                   copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) /
                                  4.0);

    image[0][0].rgbtRed = round(
        (copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);

    // upper right corner
    image[0][width - 1].rgbtBlue =
        round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue +
               copy[1][width - 2].rgbtBlue + copy[1][width - 1].rgbtBlue) /
              4.0);

    image[0][width - 1].rgbtGreen =
        round((copy[0][width - 1].rgbtGreen + copy[0][width - 2].rgbtGreen +
               copy[1][width - 2].rgbtGreen + copy[1][width - 1].rgbtGreen) /
              4.0);

    image[0][width - 1].rgbtRed = round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed +
                                         copy[1][width - 2].rgbtRed + copy[1][width - 1].rgbtRed) /
                                        4.0);

    // lower right corner
    image[height - 1][width - 1].rgbtBlue =
        round((copy[height - 1][width - 1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue +
               copy[height - 2][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue) /
              4.0);

    image[height - 1][width - 1].rgbtGreen =
        round((copy[height - 1][width - 1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen +
               copy[height - 2][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen) /
              4.0);

    image[height - 1][width - 1].rgbtRed =
        round((copy[height - 1][width - 1].rgbtRed + copy[height - 1][width - 2].rgbtRed +
               copy[height - 2][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed) /
              4.0);

    // lower left corner
    image[height - 1][0].rgbtBlue =
        round((copy[height - 1][0].rgbtBlue + copy[height - 1][1].rgbtBlue +
               copy[height - 2][1].rgbtBlue + copy[height - 2][0].rgbtBlue) /
              4.0);

    image[height - 1][0].rgbtGreen =
        round((copy[height - 1][0].rgbtGreen + copy[height - 1][1].rgbtGreen +
               copy[height - 2][1].rgbtGreen + copy[height - 2][0].rgbtGreen) /
              4.0);

    image[height - 1][0].rgbtRed =
        round((copy[height - 1][0].rgbtRed + copy[height - 1][1].rgbtRed +
               copy[height - 2][1].rgbtRed + copy[height - 2][0].rgbtRed) /
              4.0);

    // upper border
    for (int j = 1; j < width - 1; j++)
    {
        image[0][j].rgbtBlue =
            round((copy[0][j - 1].rgbtBlue + copy[0][j].rgbtBlue + copy[0][j + 1].rgbtBlue +
                   copy[1][j - 1].rgbtBlue + copy[1][j].rgbtBlue + copy[1][j + 1].rgbtBlue) /
                  6.0);

        image[0][j].rgbtGreen =
            round((copy[0][j - 1].rgbtGreen + copy[0][j].rgbtGreen + copy[0][j + 1].rgbtGreen +
                   copy[1][j - 1].rgbtGreen + copy[1][j].rgbtGreen + copy[1][j + 1].rgbtGreen) /
                  6.0);
        image[0][j].rgbtRed =
            round((copy[0][j - 1].rgbtRed + copy[0][j].rgbtRed + copy[0][j + 1].rgbtRed +
                   copy[1][j - 1].rgbtRed + copy[1][j].rgbtRed + copy[1][j + 1].rgbtRed) /
                  6.0);
    }
    // lower border
    for (int j = 1; j < width - 1; j++)
    {
        image[height - 1][j].rgbtBlue =
            round((copy[height - 1][j - 1].rgbtBlue + copy[height - 1][j].rgbtBlue +
                   copy[height - 1][j + 1].rgbtBlue + copy[height - 2][j - 1].rgbtBlue +
                   copy[height - 2][j].rgbtBlue + copy[height - 2][j + 1].rgbtBlue) /
                  6.0);

        image[height - 1][j].rgbtGreen =
            round((copy[height - 1][j - 1].rgbtGreen + copy[height - 1][j].rgbtGreen +
                   copy[height - 1][j + 1].rgbtGreen + copy[height - 2][j - 1].rgbtGreen +
                   copy[height - 2][j].rgbtGreen + copy[height - 2][j + 1].rgbtGreen) /
                  6.0);
        image[height - 1][j].rgbtRed =
            round((copy[height - 1][j - 1].rgbtRed + copy[height - 1][j].rgbtRed +
                   copy[height - 1][j + 1].rgbtRed + copy[height - 2][j - 1].rgbtRed +
                   copy[height - 2][j].rgbtRed + copy[height - 2][j + 1].rgbtRed) /
                  6.0);
    }

    // left border
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtBlue =
            round((copy[i - 1][0].rgbtBlue + copy[i - 1][1].rgbtBlue + copy[i][0].rgbtBlue +
                   copy[i][1].rgbtBlue + copy[i + 1][0].rgbtBlue + copy[i + 1][1].rgbtBlue) /
                  6.0);

        image[i][0].rgbtGreen =
            round((copy[i - 1][0].rgbtGreen + copy[i - 1][1].rgbtGreen + copy[i][0].rgbtGreen +
                   copy[i][1].rgbtGreen + copy[i + 1][0].rgbtGreen + copy[i + 1][1].rgbtGreen) /
                  6.0);
        image[i][0].rgbtRed =
            round((copy[i - 1][0].rgbtRed + copy[i - 1][1].rgbtRed + copy[i][0].rgbtRed +
                   copy[i][1].rgbtRed + copy[i + 1][0].rgbtRed + copy[i + 1][1].rgbtRed) /
                  6.0);
    }
    // right border
    for (int i = 1; i < height - 1; i++)
    {
        image[i][width - 1].rgbtBlue =
            round((copy[i - 1][width - 1].rgbtBlue + copy[i - 1][width - 2].rgbtBlue +
                   copy[i][width - 1].rgbtBlue + copy[i][width - 2].rgbtBlue +
                   copy[i + 1][width - 1].rgbtBlue + copy[i + 1][width - 2].rgbtBlue) /
                  6.0);

        image[i][width - 1].rgbtGreen =
            round((copy[i - 1][width - 1].rgbtGreen + copy[i - 1][width - 2].rgbtGreen +
                   copy[i][width - 1].rgbtGreen + copy[i][width - 2].rgbtGreen +
                   copy[i + 1][width - 1].rgbtGreen + copy[i + 1][width - 2].rgbtGreen) /
                  6.0);
        image[i][width - 1].rgbtRed =
            round((copy[i - 1][width - 1].rgbtRed + copy[i - 1][width - 2].rgbtRed +
                   copy[i][width - 1].rgbtRed + copy[i][width - 2].rgbtRed +
                   copy[i + 1][width - 1].rgbtRed + copy[i + 1][width - 2].rgbtRed) /
                  6.0);
    }

    return;
}
