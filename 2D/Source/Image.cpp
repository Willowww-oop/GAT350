#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Image.h"
#include <fstream>
#include <iostream>

bool Image::Load(const std::string& filename)
{
	// load image getting the width and height (pass 4 for the last parameter to create RGBA image)
    std::ifstream file(filename);
    if (!file.good())
    {
        std::cerr << "File not found: " << filename << std::endl;
        return false;
    }
    file.close();

    // Load the image with stb_image
    int channels;
    uint8_t* data = stbi_load(filename.c_str(), &m_width, &m_height, &channels, 4);
    if (data == NULL)
    {
        std::cerr << "Error loading image: " << filename << " - " << stbi_failure_reason() << std::endl;
        return false;
    }
	// resize the image buffer to the number of pixels in the image
	m_buffer.resize(m_width * m_height);

	// copy the image data into the buffer, !!takes in number of bytes to copy!! 
	std::memcpy(m_buffer.data(), data, m_width * m_height * sizeof(color_t)); // https://en.cppreference.com/w/cpp/string/byte/memcpy

	// free the image data
	stbi_image_free(data);

	return true;
}