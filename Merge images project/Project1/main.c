#include <math.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"


unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}

unsigned char *force_image(unsigned char *i1, unsigned char *i2, int width, int height, int channel)
{
    unsigned char *temp_array = uc_arrayNew_1d(width * height * channel);

    for (int i = 0; i < width * height * channel; i+=3)
    {
        if ((i1[i] >=50 && i1[i]<= 180) && (i1[i+1] >=137 && i1[i+1] <= 255) && (i1[i+2] <= 100 && i1[i+2] >= 0))
        {
            temp_array[i] = i2[i];
            temp_array[i+1] = i2[i+1];
            temp_array[i+2] = i2[i+2];
        }
        else
        {
            temp_array[i] = i1[i];
            temp_array[i+1] = i1[i+1];
            temp_array[i+2] = i1[i+2];
        }
    }
    return temp_array;

}

int main()
{
    int width, height, channel;
    char path_img1[] = "./images/foreground.png";
    char path_img2[] = "./images/weather_forecast-resized.jpg";
    char save_path[] = "./images/background.png";
    
    unsigned char *image1 = stbi_load(path_img1, &width, &height, &channel, 3);
    unsigned char *image2 = stbi_load(path_img2, &width, &height, &channel, 0);

    unsigned char *fimage = force_image(image1, image2, width, height, channel);
    stbi_write_jpg(save_path, width, height, channel, fimage, width * channel);
}
