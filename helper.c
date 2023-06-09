#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


bool swapped(int *ne, int *le)
{
    int *temp = malloc(sizeof(int));

    if (temp == NULL) //If NULL
    {
        free(temp);//free temp
    }

    *temp = *ne;
    *ne = *le;
    *le = *temp;

    free(temp);//free temp
    return true;//return true
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // int i = malloc(height * sizeof(int));
    // int j = malloc(width * sizeof(int));

    // if (count_height == NULL && count_width == NULL)//if NULL pointer
    // {
    //     free(count_height);//free count_height
    //     free(count_width);//free count_width
    // }

    float blue;
    float green;
    float red;
    int average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;//Initialize Blue value
            green = image[i][j].rgbtGreen;//Initialize Green value
            red = image[i][j].rgbtRed;//Initialize Red value

            //calculate the average
            average = (int) round((blue + green + red) / 3.0);

            image[i][j].rgbtBlue = average;//Set blue to new value
            image[i][j].rgbtGreen = average;//Set Green to new value
            image[i][j].rgbtRed = average;//Set Red to new value
        }
    }

    //free(count_height);
    //free(count_width);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width / 2; j++)
        {
            // Reflect pixels
            RGBTRIPLE temp = image[i][j];
            int m = width - (j + 1);
            image[i][j] = image[i][m];
            image[i][m] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise values
            float sum_red;
            float sum_blue;
            float sum_green;
            int counter;
            sum_red = sum_blue = sum_green = counter = 0;
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Otherwise add to sums
                    sum_red += temp[i + k][j + l].rgbtRed;
                    sum_blue += temp[i + k][j + l].rgbtBlue;
                    sum_green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                }
            }

            // Get average and blur image
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }

    return;
}

//Sepia image
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float blue;
    float green;
    float red;
    int average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;//Initialize Blue value
            green = image[i][j].rgbtGreen;//Initialize Green value
            red = image[i][j].rgbtRed;//Initialize Red value

            //calculate sepia
            red = (int) round((red * .393) + (green * .769) + (blue * .189));
            green = (int) round((red * .349) + (green * .686) + (blue * .168));
            blue = (int) round((red * .272) + (green * .534) + (blue * .131));

            if (red > 255)
            {
                red = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            image[i][j].rgbtBlue = blue;//Set blue to new value
            image[i][j].rgbtGreen = green;//Set Green to new value
            image[i][j].rgbtRed = red;//Set Red to new value
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialise ints
    float Gx_red;
    float Gx_blue;
    float Gx_green;
    float Gy_red;
    float Gy_blue;
    float Gy_green;
    Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;

    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (blue > 255)
            {
                blue = 255;
            }

            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }

    return;
}
