#include "ImageEditor.h"
#include <iostream>
using namespace std;

int main() {
    try {
        /*cout << "Loading Pikachu..." << endl;
        ImageEditor pikachu("pikachu.png");
        cout << "Pikachu loaded successfully!" << endl;

        pikachu.addShadow(10, 10, 0.3);
        // pikachu.addGlow(15, 0.5);
        pikachu.save("pikachu_shadow.png");*/
        
        cout << "Opening Italy.png" << endl;
        ImageEditor italy("Italy.png");
        cout << "Opened Italy.png" << endl;
        italy.overlay("pikachu.png");
        italy.save("Italy2.png");

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
