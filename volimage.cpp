// MZMTIN002

#include "volimage.h"

MZMTIN002::VolImage::VolImage() {
    MZMTIN002::VolImage::width = 0;
    MZMTIN002::VolImage::height = 0;
    MZMTIN002::VolImage::numImages = 0;
    MZMTIN002::VolImage::slices.clear();
}

MZMTIN002::VolImage::~VolImage() {
    for (auto x = 0; x < slices.size(); x++) {
        for (auto y = 0; y < height; y++) {
            delete slices[x][y];
        }
        delete slices[x];
    }
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
    width = stoi(dims[0]);
    height = stoi(dims[1]);
    numImages = stoi(dims[2]);
    unsigned char ** temp = nullptr;
    for (auto x = 0; x < numImages; x++) {
        ifstream raw(baseName + to_string(x) + ".raw", ios::binary);

        if(!raw) {
            puts("Couldn't open file");
            return false;
        }
        temp = new unsigned char*[height];
        for (auto y = 0; y < height; y++) {
            temp[y] = new unsigned char[width];

            for (auto z = 0; z < width; z++) {
                temp[y][z] = raw.get();
            }
        }
        raw.close();
        slices.push_back(temp);
    }
    return true;
}

void MZMTIN002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {
    ofstream outRaw(output_prefix + ".raw", ios::binary);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            outRaw << (unsigned char)(abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j]) / 2);
        }
    }
    outRaw.close();
    cout << "Successfully computed diffmap from slice " << sliceI << " to " << sliceJ << " and saved result to " << output_prefix << ".raw" << endl;
}

void MZMTIN002::VolImage::extract(int sliceId, string output_prefix) {
    ofstream outdat(output_prefix + ".dat", ios::binary);
    string head = to_string(width) + to_string(height) +" 1";
    outdat << head.c_str();
    outdat.close();

    for (int k = 0; k < slices.size(); k++) {
        if (k == sliceId) {
            ofstream outRaw(output_prefix + ".raw", ios::binary);
            for (auto i = 0; i < height; i++) {
                for (auto j = 0; j < width; j++) {
                    outRaw << slices[sliceId][i][j];
                }
            }
            outRaw.close();
        }
    }

    cout << "Successfully extracted slice " << sliceId << " from the vector and saved result to " << output_prefix << ".raw" << endl;
}

int MZMTIN002::VolImage::volImageSize(void) {
    return width * height * numImages + sizeof(char) + sizeof(char*) + sizeof(char**);
}
