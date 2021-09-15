#ifndef BMP_H
#define BMP_H

#include <iostream>
#include <stdio.h>

using namespace std;

class PIXEL
{
    public:
        unsigned char R;
        unsigned char G;
        unsigned char B;
        float hue;
        float saturation;
        float value;

        void RGB_to_HSV()
        {
            float b = B/255.0;
            float g = G/255.0;
            float r = R/255.0;

            float maks = max(max(r,b),g);
            float mini = min(min(r,b),g);

            value = maks;

            if(maks == 0 || maks == mini)
            {
                saturation = 0;
                hue = 0;
            }
            else
            {
                saturation = (maks- mini)/maks;

                if(maks == r)
                    hue = 60.0 * ((g - b) / (maks - mini)) + 0.0;
                else if(maks == g)
                    hue = 60.0 * ((b - r) / (maks - mini)) + 120.0;
                else
                    hue = 60.0 * ((r - g) / (maks - mini)) + 240.0;

                if(hue < 0)
                    hue += 360.0;
            }
        }

        void HSV_to_RGB()
        {
            if(hue>360)
                hue = 360;
            else if(hue < 0)
                hue = 0;

            if(saturation < 0)
                saturation = 0;
            else if (saturation > 1)
                saturation = 1;

            if(value < 0)
                value = 0;
            else if(value > 1)
                value = 1;

            int   hi = ((int)(hue / 60.0))% 6;
            float f  = (hue / 60.0f) - hi;
            float p  = value * (1.0 - saturation);
            float q  = value * (1.0 - saturation * f);
            float t  = value * (1.0 - saturation * (1.0f - f));

            float r,g,b;
            switch(hi)
            {
            case 0:
                r = value, g = t, b = p;
                break;
            case 1:
                r = q, g = value, b = p;
                break;
            case 2:
                r = p, g = value, b = t;
                break;
            case 3:
                r = p, g = q, b = value;
                break;
            case 4:
                r = t, g = p, b = value;
                break;
            case 5:
                r = value, g = p, b = q;
                break;
            }
            R = (unsigned char)(r*255);
            G = (unsigned char)(g*255);
            B = (unsigned char)(b*255);
        }

};

class BMP
{
     private:
        struct BMPFILEHEADER
        {
            short type;
            int fileSize;
            short reserved0;
            short reserved1;
            int dataOffset;
        };

        struct BMPINFOHEADER
        {
            int hdrSize;
            int width;
            int height;
            short planes;
            short depth;
            int compression;
            int bmpDataSize;
            int hResolution;
            int vResolution;
            int nColors;
            int nImportantColors;
        };

        FILE *picture;
        BMPFILEHEADER file_info;
        BMPINFOHEADER picture_info;

        int padding;
        bool bitmap2_istnieje;

    public:
        BMP(const char *file_name);
        export_picture(const char *result_file_name);
        ~BMP();
        void change_brightness();
        void change_saturation();
        void change_color_scale();
        void negative();
        void grey_image();
        void filter(int **filter, int filter_size, int sum_of_filter, int i_p, int j_p);
        void blur_image();
        void sharpen_image();
        void edge_detection();
        void halftone_approximation();
        void color_accent();
        void tilf_shift();
        void color_toning();
        void filtr();

        PIXEL **bitmap;
        PIXEL **bitmap2;

};

#endif // BMP_H
