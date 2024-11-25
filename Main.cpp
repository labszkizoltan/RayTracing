
#include <iostream>
#include <vector>
// #include <ImageHandling/stb_image.h>
// #include <ImageHandling/stb_image_write.h>

#include <ImageHandling/ImageData.h>
#include <Drawing/TrianglePixelLocator.h>

// #define STB_IMAGE_IMPLEMENTATION
// #include "ImageHandling/stb_image.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "ImageHandling/stb_image_write.h"

void SwapInts(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void DrawFlatTopTriangle(RGBImageData_byte& img, int _x1, int _y1, int _x2, int _y2, int _x3, int _y3)
{
	float dx1 = _x3 - _x1;
	float dx2 = _x3 - _x2;
	for (int y = _y1; y > _y3; y--)
	{
		float baseLength = _x2 - _x1;
		float lambdaY = (float)(y - _y1) / (float)(_y3 - _y1);
		int startX = (int)(_x1 + lambdaY * dx1);
		int endX = (int)(_x2 + lambdaY * dx2);
		// int endX = startX + (int)((1-lambda) * baseLength);
		for (int x = startX; x < endX; x++)
		{
			// float lambdaX = (x - startX) / (endX - startX);
			float lambdaX = (x - startX) / baseLength;
			auto pix = img.GetPixelLocation(x, y);
			pix[0] = (unsigned char) ( (1 - lambdaY) * (1 - lambdaX) * 255 );
			pix[1] = (unsigned char) ( (1 - lambdaY) * (lambdaX) * 255 );
			pix[2] = (unsigned char) ( (lambdaY) * (1 - lambdaX) * 255 );
		}
	}
}

void DrawFlatBottomTriangle(RGBImageData_byte& img, int _x1, int _y1, int _x2, int _y2, int _x3, int _y3)
{
	float dx1 = _x1 - _x2;
	float dx2 = _x1 - _x3;
	for (int y = _y2; y < _y1; y++)
	{
		float baseLength = _x3 - _x2;
		float lambdaY = (float)((y - _y2) / (float)(_y1 - _y2));
		int startX = (int)(_x2 + lambdaY * dx1);
		int endX = (int)(_x3 + lambdaY * dx2);
		// int endX = startX + (int)((1-lambda) * baseLength);
		for (int x = startX; x < endX; x++)
		{
			// float lambdaX = (x - startX) / (endX - startX);
			float lambdaX = (x - startX) / baseLength;
			auto pix = img.GetPixelLocation(x, y);
			pix[0] = 128;
			pix[1] = 128;
			pix[2] = 128;
		}
	}
}


void DrawTriangleOnImage(RGBImageData_byte& img, int _x1, int _y1, int _x2, int _y2, int _x3, int _y3)
{
	int x4 = -1, y4 = -1;
	bool flatTop = false, flatBottom = false;

	if (_y1 < _y2)
	{
		SwapInts(_y1, _y2);
		SwapInts(_x1, _x2);
	}
	if (_y1 < _y3)
	{
		SwapInts(_y1, _y3);
		SwapInts(_x1, _x3);
	}
	if (_y2 < _y3)
	{
		SwapInts(_y2, _y3);
		SwapInts(_x2, _x3);
	}

	// flat top triangle, want x1 to be smaller than x2
	if (_y1 == _y2)
	{
		flatTop = true;
		if (_x1 > _x2) { SwapInts(_x1, _x2); }
	}
	// flat bottom triangle, want x2 to be smaller than x3
	else if (_y2 == _y3)
	{
		flatBottom = true;
		if (_x2 > _x3) { SwapInts(_x2, _x3); }
	}
	else
	{
		float dx = _x3 - _x1;
		float lambda = (float)(_y2 - _y1) / (float)(_y3 - _y1);
		x4 = (int)(_x1 + lambda * dx);
		y4 = _y2;
		if (x4 < _x2) { SwapInts(_x2, x4); }
	}

	if (flatTop)
	{
		DrawFlatTopTriangle(img, _x1, _y1, _x2, _y2, _x3, _y3);
	}
	else if (flatBottom)
	{
		DrawFlatBottomTriangle(img, _x1, _y1, _x2, _y2, _x3, _y3);
	}
	else
	{
		DrawFlatBottomTriangle(img, _x1, _y1, _x2, _y2, x4, y4);
		DrawFlatTopTriangle(img, _x2, _y2, x4, y4, _x3, _y3);
	}




}


int main()
{
	std::cout << "asd \n";
	RGBImageData_byte image = RGBImageData_byte("D:/cpp_codes/39_RayTracing/images/TestImg.png");
	std::vector<LocationSpecifier> pixels = TrianglePixelLocator::LocatePixels(Vec2D(100, 100), Vec2D(200, 110), Vec2D(150, 200));

	for (LocationSpecifier spec : pixels)
	{
		auto pix = image.GetPixelLocation(spec.position);
		pix[0] = (unsigned char)((1 - spec.lambda1) * (1 - spec.lambda2) * 255);
		pix[1] = (unsigned char)(spec.lambda1 * 255);
		pix[2] = (unsigned char)(spec.lambda2 * 255);
	}
	image.SavePng("D:/cpp_codes/39_RayTracing/images/TestImg2.png");

	return 0;
}




int old_main()
{
	std::cout << "asd \n";

	RGBImageData_byte image = RGBImageData_byte("D:/cpp_codes/39_RayTracing/images/TestImg.png");

	// for (int y = 50; y < 100; y++)
	// {
	// 	for (int x = 100; x < 200; x++)
	// 	{
	// 		auto pix = image.GetPixelLocation(x, y);
	// 		pix[0] = 0;
	// 		pix[1] = 128;
	// 		pix[2] = 255;
	// 	}
	// }


	// DrawTriangleOnImage(image, 20, 20, 50, 50, 40, 30);
	// DrawTriangleOnImage(image, 100, 200, 300, 200, 250, 100);
	// DrawTriangleOnImage(image, 100, 200, 300, 200, 250, 350);

	DrawTriangleOnImage(image, 400, 100, 500, 300, 600, 200);

	image.SavePng("D:/cpp_codes/39_RayTracing/images/TestImg2.png");

	// https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/
	/*
	int width, height, channels;
	unsigned char* img = stbi_load("D:/cpp_codes/39_RayTracing/images/TestImg.png", &width, &height, &channels, 0);
	if (img == NULL)
	{
		printf("Error in loading the image\n");
		exit(1);
	}
	for (int i = 0; i < 100; i++)
	{
		img[i] = 0;
	}

	stbi_write_png("D:/cpp_codes/39_RayTracing/images/TestImg2.png", width, height, channels, img, width * channels);
	*/
	
	
	// static int stbi__create_png_image_raw(stbi__png * a, stbi_uc * raw, stbi__uint32 raw_len, int out_n, stbi__uint32 x, stbi__uint32 y, int depth, int color)
	// static int stbi__create_png_image(stbi__png * a, stbi_uc * image_data, stbi__uint32 image_data_len, int out_n, int depth, int color, int interlaced)
	// stbi__create_png_image_raw

	return 0;
}






