// MZMTIN002

#include "volimage.h"

int main(int argc, char* argv[]) {
    string prefix;
    string line1;
    string line2;
    try {
        prefix = argv[1];
        line1 = argv[2];
        line2 = argv[3];
    }
    catch (int e) {}

    ifstream in(prefix + ".data");
    string header;
    getline(in, header);
    cout << header << endl;
    stringstream ss(header);
    string token;
    vector<int> dims; // Vector that stores the ints in the data file.
    while (ss >> token) {
        stringstream ss2(token);
        int curr;
        ss2 >> curr;
        dims.push_back(curr);
    }
    for (int i = 0; i < dims[0]; i++) {
        // do valuable stuff.
    }
    return 0;
}

VolImage::VolImage() {
    VolImage::width = 0;
    VolImage::height = 0;
    VolImage::slices.clear();
}

VolImage::~VolImage() {
    // delete stuff
}

bool VolImage::readImages(string baseName) {
    return false;
}

void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {

}

void VolImage::extract(int sliceId, string output_prefix) {

}

int VolImage::volImageSize(void) {
    return 0;
}
