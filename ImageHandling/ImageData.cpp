#include "ImageData.h"


#define STB_IMAGE_IMPLEMENTATION
#include "ImageHandling/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "ImageHandling/stb_image_write.h"

RGBImageData_byte::RGBImageData_byte() : m_width(0), m_height(0), m_data(0) {}

RGBImageData_byte::RGBImageData_byte(int width, int height) : m_width(width), m_height(height), m_data((size_t)(width) * (size_t)height) {}

RGBImageData_byte::RGBImageData_byte(std::string path)
{
	int channels;
	unsigned char* img = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
	if (img == NULL)
	{
		std::string message("Error in loading the image: ");
		message += path;
		throw std::exception(message.c_str());
	}
	if (s_channels != channels)
	{
		std::string message("Channel count doesnt match expectation. : ");
		message += path;
		throw std::exception(message.c_str());
	}
	m_data = std::vector<unsigned char>(m_width * m_height * channels);
	std::memcpy(&m_data[0], img, m_width * m_height * channels * sizeof(unsigned char));
}

unsigned char* RGBImageData_byte::GetPixelLocation(int x, int y)
{
	return &m_data[s_channels*(x+m_width*y)];
}

unsigned char* RGBImageData_byte::GetPixelLocation(Vec2D p)
{
	return &m_data[s_channels * ((int)p.x + m_width * (int)p.y)];
}

void RGBImageData_byte::SavePng(std::string path)
{
	stbi_write_png("D:/cpp_codes/39_RayTracing/images/TestImg2.png", m_width, m_height, s_channels, &m_data[0], m_width * 3);
}





