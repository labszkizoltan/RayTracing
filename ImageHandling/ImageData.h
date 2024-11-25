
#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include <iostream>
#include <vector>
#include <Geometry/Vec2D.h>

class RGBImageData_byte
{
public:
	RGBImageData_byte();
	RGBImageData_byte(int width, int height);
	RGBImageData_byte(std::string path);

	unsigned char* GetPixelLocation(int x, int y);
	unsigned char* GetPixelLocation(Vec2D p);
	void SavePng(std::string path);

	int m_width = 0;
	int m_height = 0;
	std::vector<unsigned char> m_data;

private:
	static const int s_channels = 3;

};

/*
class RGBImageData_float
{
public:
	RGBImageData_float();
	RGBImageData_float(int width, int height);

	float* GetPixelLocation(int x, int y);
	void SavePng(std::string path);

	int m_width = 0;
	int m_height = 0;
	std::vector<float> m_data;

private:
	static const int s_channels = 3;

};
*/




/*
template<typename T>
class ImageData
{
public:
	ImageData();
	ImageData(int width, int height);
	ImageData(int width, int height, int channels);
	ImageData(std::string path);


	int m_width;
	int m_height;
	int m_channels;
	std::vector<T> m_data;

};
*/





#endif // IMAGE_DATA_H
