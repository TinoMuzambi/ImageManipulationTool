// MZMTIN002

#include <regex>
#include "volimage.h"

int main(int argc, char* argv[]) { //TODO parse arguments properly.
    // brain_mri_raws/MRI d 20 50 diffout.txt -x 22 extractout.txt
    string prefix;
    int i;
    int j;
    string outfile;
    MZMTIN002::VolImage volImage;
    vector<string> comms;
    for (int i = 1; i < argc; i++) {
//        cout << argv[i] << endl;
        comms.emplace_back(argv[i]);
    }
    if (comms.empty()) {
        puts("Arguments required. No arguments found.");
        exit(0);
    }
    else if (comms.size() == 1) {
        prefix = comms[0];
        volImage.readImages(prefix);
    }
    else if (comms.size() == 5) {
        prefix = comms[0];
        volImage.readImages(prefix);
        i = stoi(comms[2]);
        j = stoi(comms[3]);
        outfile = comms[4];
        volImage.diffmap(i, j, outfile);
    }
    else if (comms.size() == 4) {
        prefix = comms[0];
        volImage.readImages(prefix);
        i = stoi(comms[2]);
        outfile = comms[3];
        volImage.extract(i, outfile);
    }
    else {
        puts("Invalid number of arguments.");
        exit(0);
    }
    
    return 0;
}

MZMTIN002::VolImage::VolImage() {
    MZMTIN002::VolImage::width = 0;
    MZMTIN002::VolImage::height = 0;
    MZMTIN002::VolImage::slices.clear();
}

MZMTIN002::VolImage::~VolImage() {
    for (int i = 0; i < slices.size(); ++i) {
        delete[] slices[i];
    }
}

bool MZMTIN002::VolImage::readImages(string baseName) {
    puts("In readImages func.");
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
        unsigned char **rawRows = new unsigned char* [stoi(dims[1])];
        for (int j = 0; j < stoi(dims[0]); ++j) {
            for (int k = 0; k < stoi(dims[1]); ++k) {
                char buf[stoi(dims[1])];
                unsigned char value;
                while (raw.read(buf, sizeof(buf))) {
                    memcpy(&value, buf, sizeof(value));
                }
                rawRows[k] = &value;
            }
            slices.push_back(rawRows);
        }
//        char buf[sizeof(short)];
//        unsigned char value;
//        while (raw.read(buf, sizeof(buf))) {
//            memcpy(&value, buf, sizeof(value));
//            cout << value << endl;
//        }
    }
    // 429 303 123 - MRI.data contents
    return false;
}

void MZMTIN002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {
    puts("In diff map func.");
}

void MZMTIN002::VolImage::extract(int sliceId, string output_prefix) {
    puts("In extact func.");
}

int MZMTIN002::VolImage::volImageSize(void) {
    return 0;
}
