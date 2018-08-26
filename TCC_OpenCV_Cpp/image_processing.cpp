/*
 Testing ...
*/

// #include <cerrno>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>
using std::string;
using std::cout;
// using std::cerr;

#include <algorithm>
using std::transform;

#include <vector>
using std::vector;

// #include <fstream>
// using std::ofstream;

void processing(const string& /*source*/, const string& /*filename extension*/);
void list_files(const char*   /*source*/, vector<string>& /*files*/);
void image_segmentation(const string& /*source*/);

int main(int argc, char const** argv)
{
    cout << "main started ...\n";

    // default
    string source("."), filename_extension(".png");

    // view command
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << char(32);
    }
    cout << '\n';

    // check input
    if (argc > 3) {
        // argc = 3     argv[0]          argv[1]          argv[2]
        cout << "Usage: image_processing --[PNG|JPG|JPEG] <dir_name>\n"
             << "       image_processing --[PNG|JPG|JPEG]\n"
             << "       image_image_processing <source image>\n"
             << "       image_image_processing\n";
        return (EXIT_FAILURE);
    }
    if (argc > 1) {
        if (argv[1][0] == '-' && argv[1][1] == '-') {
            if (argv[1] == string("--PNG"))  filename_extension = ".png";
            if (argv[1] == string("--JPG"))  filename_extension = ".jpg";
            if (argv[1] == string("--JPEG")) filename_extension = ".jpeg";
            if (argc == 3) source = argv[2];
        } else {
            source = argv[1];
        }
    }

    // process image
    cout << "processing source ...\n";
    processing(source, filename_extension);

    cout << "finished!\n";

    return (EXIT_SUCCESS);
}

void processing(const string& source, const string& filename_extension)
{
    cout << "source: " << source
         << "\nfilename extension: " << filename_extension << "\n";

    // create list of files
    vector<string> sources{source};
    list_files(const_cast<char*>(source.c_str()), sources);

    // check image file extension
    bool is_empty(true);
    for (string file: sources) {
        string temp = file;
        if (file.size() > 4) {
            temp = file.substr(file.size() - 4, file.size());
            transform(temp.begin(), temp.end(), temp.begin(),
                [](char c){ return tolower(c); });
        }
        if (temp == filename_extension) {
            is_empty = false;
            image_segmentation(file);
        }
    }
    if (is_empty) cout << "nothing was done found .... \n";
    else cout << "processed ...\ncheck the \"output\" folder!\n";
}

void list_files(const char* source, vector<string>& files)
{
    cout << "reading source ...\n";

    DIR* dir;
    struct dirent* entry;
    char entry_source[PATH_MAX + 1];
    size_t source_len = strlen(source);

    if (source == NULL) source = ".";

    strncpy (entry_source, source, sizeof(entry_source));
    if (entry_source[source_len - 1] != '/') {
        entry_source[source_len] = '/';
        entry_source[source_len + 1] = '\0';
        ++source_len;
    }

    dir = opendir(source);
    if (!dir) {
        cout << "is not a valid folder name. continue ...\n";
        return;
    }

    struct stat info;
    while ((entry = readdir(dir)) != NULL) {
        strncpy(entry_source + source_len, entry->d_name,
            sizeof (entry_source) - source_len);
        lstat (entry_source, &info);
        if (S_ISREG(info.st_mode)) files.push_back(entry_source);
    }

    closedir(dir);

    cout << "folder reading ... ok\n";
}

void image_segmentation(const string& source)
{
    cout << "process " << source << " ...\n";
}