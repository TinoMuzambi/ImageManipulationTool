// MZMTIN002

#include "volimage.h"

int main(int argc, char* argv[]) { //TODO parse arguments properly.
    // brain_mri_raws/MRI d 20 50 diffout.txt -x 22 extractout.txt
    string prefix;
    string line1;
    string line2;
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
    }

    MZMTIN002::VolImage volImage;
//    volImage.readImages(prefix);
    
    return 0;
}

MZMTIN002::VolImage::VolImage() {
    MZMTIN002::VolImage::width = 0;
    MZMTIN002::VolImage::height = 0;
    MZMTIN002::VolImage::slices.clear();
}

MZMTIN002::VolImage::~VolImage() {
    // delete stuff
}

bool MZMTIN002::VolImage::readImages(string baseName) {
    ifstream in(baseName + ".data");
    string header;
    getline(in, header);
    stringstream ss(header);
    string token;
    vector<string> dims; // Vector that stores the ints in the data file.
    while (getline(ss, token, ' ')) {
        dims.push_back(token);
    }
    for (int i = 0; i < stoi(dims[2]); i++) {
        ifstream raw(baseName + to_string(i) + ".raw", ios::binary);
        char buf[sizeof(short)];
        short value;
        while (raw.read(buf, sizeof(buf))) {
            memcpy(&value, buf, sizeof(value));
            cout << value << " ";
        }
    }
    // 429 303 123 - MRI.data contents
    return false;
}

void MZMTIN002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {

}

void MZMTIN002::VolImage::extract(int sliceId, string output_prefix) {

}

int MZMTIN002::VolImage::volImageSize(void) {
    return 0;
}
