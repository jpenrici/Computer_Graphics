#include "image_processing.hpp"

void ImageProcessing::processing(char* path)
{
    friend_function(path);
}

void friend_function(char* path)
{
    // método somente para teste
    if (path != NULL) {
        for (int i = 0; i < 10; ++i)
            cout << i << ": " << path << "\n";
    } else {
        cout << " :(\n";
    }
    cout << "\n";
}