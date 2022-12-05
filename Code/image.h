
#pragma once

#ifndef IMAGE_H
#define IMAGE_H


#include <stdint.h>
#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include <complex>


const unsigned long STEG_HEADER_SIZE = sizeof(uint32_t) * 8;

enum Type {
    PNG, JPG, BMP, TGA
};

extern bool write(const char* filename);

// static double ker[] =  {   1/16.0,  2/16.0,  1/16.0,
//                         2/16.0, 4/16.0, 2/16.0,
//                         1/16.0, 2/16.0, 1/16.0
//                 };

static double ker[9] = {
		1/16., 2/16., 1/16.,
		2/16., 4/16., 2/16.,
		1/16., 2/16., 1/16.
	};
                
static double emboss_ker[] = { -2/9.0, -1/9.0, 0,
                            -1/9.0, 1/9.0, 0,
                            0, 1/9.0, 2/9.0

};


struct Image 
{

    Image(int w, int h, int channels);

    Image(const Image& img);

    Image(char* input);

    Image() {

    }

    Image(Image& img);

    Image(Image* imageState);

    Image(const char* input);

     virtual ~Image();

    virtual Image* getState() {
        return state_;
    }
    
    void grayscale_avgs();

    void grayscale_lums();
    
    void colorMasks(float r, float g, float b);

    void encodeMessages(const char* message);

    void decodeMessages(char* buffer, size_t* messageLength);

    bool write(const char* filename);

    Type getFileType(const char* filename);

    char* encodeBytes();

    std::string encodeByteString();
    
    void loadFromMemory(const std::vector<char> &img_data);

    Image& std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc);

    void std_convolve_clamp_to_0v(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc);

    Image& std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc) ;

    void std_convolve_clamp_to_borderv(uint8_t channel, uint32_t ker_w, uint32_t ker_h, uint32_t cr, uint32_t cc) ;

    Image& flipX();
	Image& flipY();





    // For later
    


// private:
    uint8_t* data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;
    int random; 
    Image* state_;  

};

 #endif