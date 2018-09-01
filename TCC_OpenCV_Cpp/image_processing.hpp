#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include <iostream>
using std::cout;

class ImageProcessing
{
	friend void friend_function(char* /*path*/);
public:
	ImageProcessing();
	~ImageProcessing();
	static void processing(char* /*path*/);
};

void friend_function(char* /*path*/);

#endif // IMAGE_PROCESSING_HPP