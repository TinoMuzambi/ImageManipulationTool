// MZMTIN002

#ifndef ASSIGNMENT_2_VOLIMAGE_H
#define ASSIGNMENT_2_VOLIMAGE_H
#include <iostream>
#include <vector>
#include <string>
#include "fstream"
#include <sstream>
#include <cwchar>
#include "cstring"

using namespace std;
namespace MZMTIN002 {
    class VolImage {
    private: // private members

        int width, height; // width and height of image stack
        vector<unsigned char **> slices; // data for each slice, in order

    public: // public members

        VolImage(); // default constructor - define in .cpp
        ~VolImage(); // destructor - define in .cpp file

        // populate the object with images in stack and
        //set member variables define in .cpp
        bool readImages(string baseName);

        // compute difference map and write out; define in .cpp
        void diffmap(int sliceI, int sliceJ, string output_prefix);

        // extract slice sliceId and write to output - define in .cpp
        void extract(int sliceId, string output_prefix);

        // extract slice sliceId row and write to output - define in .cpp
        void extractrow(int sliceId, string output_prefix);

        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
        int volImageSize(void); // define in .cpp

        int numImages;
    };
}


#endif //ASSIGNMENT_2_VOLIMAGE_H
