// MZMTIN002

#include "volimage.h"

/**
 * Constructor, initialise instance variables to zero-values.
 */
MZMTIN002::VolImage::VolImage() {
    MZMTIN002::VolImage::width = 0;
    MZMTIN002::VolImage::height = 0;
    MZMTIN002::VolImage::numImages = 0;
    MZMTIN002::VolImage::slices.clear();
}

/**
 * Destructor, delete memory used during program.
 */
MZMTIN002::VolImage::~VolImage() {
    for (auto x = 0; x < slices.size(); x++) {
        for (auto y = 0; y < height; y++) {
            delete slices[x][y];
        }
        delete slices[x];
    }
}

/**
 * This method reads in the raw files and populates a vector
 * of unsigned char** with the data.
 * @param baseName name of the raw files sequence.
 * @return true for success, false otherwise.
 */
bool MZMTIN002::VolImage::readImages(string baseName) {
    ifstream in(baseName + ".data");
    string header;
    getline(in, header);
    stringstream ss(header);
    string token;
    vector<string> dims; // Vector that stores the ints from the header file.
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

/**
 * Computes diffmap between two raw files and writes it out to
 * another output raw file.
 * @param sliceI the first raw file.
 * @param sliceJ the second raw file.
 * @param output_prefix the output filename sequence.
 */
void MZMTIN002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {
    if (sliceI >= height || sliceJ >= width) { //Error checking
        puts("slice indexes out of bounds");
        exit(1);
    }
    ofstream outRaw(output_prefix + ".raw", ios::binary);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            outRaw << (unsigned char)(abs((float)slices[sliceI][i][j] - (float)slices[sliceJ][i][j]) / 2); //Formula for computing diffmap.
        }
    }
    outRaw.close();
    cout << "Successfully computed diffmap from slice " << sliceI << " to " << sliceJ << " and saved result to " << output_prefix << ".raw" << endl;
}

/**
 * Extract one slice from the slices vector and write
 * it out to the output file.
 * @param sliceId the slice to extract.
 * @param output_prefix he output filename sequence.
 */
void MZMTIN002::VolImage::extract(int sliceId, string output_prefix) {
    if (sliceId >= numImages) { //Error checking
        puts("slice index out of bounds");
        exit(1);
    }
    ofstream outdat(output_prefix + ".dat", ios::binary);
    outdat << to_string(width) + " " + to_string(height) +" 1";
    outdat.close();

    for (auto i = 0; i < slices.size(); i++) {
        if (i == sliceId) {
            ofstream outRaw(output_prefix + ".raw", ios::binary);
            for (auto j = 0; j < height; j++) {
                for (auto k = 0; k < width; k++) {
                    outRaw << slices[sliceId][j][k];
                }
            }
            outRaw.close();
        }
    }

    cout << "Successfully extracted slice " << sliceId << " from the vector and saved result to " << output_prefix << ".raw" << endl;
}

/**
 * Extract one slice row from the slices vector and write
 * it out to the output file.
 * @param sliceId the slice to extract.
 * @param output_prefix he output filename sequence.
 */
void MZMTIN002::VolImage::extractrow(int sliceId, string output_prefix) {
    if (sliceId >= height) { //Error checking
        puts("slice indexes out of bounds");
        exit(1);
    }
    ofstream outdat(output_prefix + ".dat", ios::binary);
    outdat << to_string(width) + " " + to_string(height) +" 1";
    outdat.close();

    for (auto i = 0; i < slices.size(); i++) {
        ofstream outRaw(output_prefix + ".raw", ios::binary);
        for (auto j = 0; j < height; j++) {
            if (j == sliceId) {
                for (auto k = 0; k < width; k++) {
                    outRaw << slices[i][sliceId][k];
                }
            }
        }
        outRaw.close();
    }

    cout << "Successfully extracted slice row " << sliceId << " from the vector and saved result to " << output_prefix << ".raw" << endl;
}

/**
 * Compute number of bytes used to store image data bytes.
 * @return int number of bytes.
 */
int MZMTIN002::VolImage::volImageSize(void) {
    return numImages * (height * width * sizeof(char) + height * sizeof(char*)) + numImages * sizeof(char*);
}

