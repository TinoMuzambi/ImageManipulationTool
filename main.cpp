// MZMTIN002

#include "main.h"

int main(int argc, char* argv[]) {
    string prefix;
    int i;
    int j;
    string outfile;
    MZMTIN002::VolImage volImage;
    vector<string> comms;
    for (int i = 1; i < argc; i++) {
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