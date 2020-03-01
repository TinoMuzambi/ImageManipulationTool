// MZMTIN002

#include <regex>
#include "volimage.h"

int main(int argc, char* argv[]) {
    // brain_mri_raws/MRI -d 20 50 diffout.txt -x 22 extractout.txt
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
        cout << "Number of images: " << volImage.numImages << endl;
        cout << "Number of bytes required: " << volImage.volImageSize() << endl;
    }
    else if (comms.size() == 5) {
        prefix = comms[0];
        volImage.readImages(prefix);
        i = stoi(comms[2]);
        j = stoi(comms[3]);
        outfile = comms[4];
        volImage.diffmap(i, j, outfile);
        cout << "Number of images: " << volImage.numImages << endl;
        cout << "Number of bytes required: " << volImage.volImageSize() << endl;
    }
    else if (comms.size() == 4) {
        prefix = comms[0];
        volImage.readImages(prefix);
        i = stoi(comms[2]);
        outfile = comms[3];
        volImage.extract(i, outfile);
        cout << "Number of images: " << volImage.numImages << endl;
        cout << "Number of bytes required: " << volImage.volImageSize() << endl;
    }
    else {
        puts("Invalid number of arguments.");
        exit(0);
    }
    return 0;
}

MZMTIN002::VolImage::VolImage() {
    puts("In constructor");
    MZMTIN002::VolImage::width = 0;
    MZMTIN002::VolImage::height = 0;
    MZMTIN002::VolImage::numImages = 0;
    MZMTIN002::VolImage::slices.clear();
}

MZMTIN002::VolImage::~VolImage() {
    puts("In destructor");
    for (auto x = 0; x < slices.size(); x++) {
        for (auto y = 0; y < height; y++) {
            delete slices[x][y];
        }
        delete slices[x];
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
    width = stoi(dims[0]);
    height = stoi(dims[1]);
    numImages = stoi(dims[2]);
    streampos size;
    unsigned char ** temp = nullptr;
    for (auto x = 0; x < numImages; x++) {
        ifstream raw(baseName + to_string(x) + ".raw", ios::binary | ios::ate);

        if(!raw) {
            puts("Couldn't open file");
            return false;
        }
        temp = new unsigned char*[height];
        for (auto y = 0; y < height; y++) {
            temp[y] = new unsigned char[width];

            for (auto z = 0; z < width; z++) {
                temp[y][z] = raw.get();
//                size = raw.tellg();
//                raw.seekg(0, ios_base::end);
//                raw.read(reinterpret_cast<char *>(temp[x][y][z]), size);
//                raw.seekg(0, ios_base::beg);
//                cout << slices.size() << endl;
            }
        }
        raw.close();
        slices.push_back(temp);
    }
    // 429 303 123 - MRI.data contents
    return true;
}

void MZMTIN002::VolImage::diffmap(int sliceI, int sliceJ, string output_prefix) {
    puts("In diff map func.");
    auto diff = new int*[height];
    for (int j = 0; j < height; j++) {
        diff[j] = new int[width];
        for (int k = 0; k < width; k++) {
            diff[j][k] = (int)(abs((float)slices[sliceI][j][k] - (float)slices[sliceJ][j][k])/2);
        }
    }

    ofstream outRaw(output_prefix + ".raw", ios::binary);
    outRaw.write(reinterpret_cast<char*>(diff), slices.size());
    outRaw.close();
    cout << "Successfully computed diffmap from slice " << sliceI << " to " << sliceJ << " and saved result to " << output_prefix << ".raw" << endl;
}

void MZMTIN002::VolImage::extract(int sliceId, string output_prefix) {
    puts("In extract func.");
//    cout << slices.size() << endl;
//    cout << slices[0] << endl;
//    cout << slices[0][0] << endl;
//    cout << int(slices[0][0][0]) << endl;
    ofstream outdat(output_prefix + ".dat", ios::binary);
    string head = to_string(width) + to_string(height) +" 1";
    outdat << head.c_str();
    outdat.close();
    
    ofstream outRaw(output_prefix + ".raw", ios::binary);
    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            outRaw << slices[sliceId][i][j];
        }
    }
    outRaw.close();

    cout << "Successfully extracted slice " << sliceId << " from the vector and saved result to " << output_prefix << ".raw" << endl;
}

int MZMTIN002::VolImage::volImageSize(void) {
    return width * height * numImages + sizeof(char) + sizeof(char*) + sizeof(char**);
}
