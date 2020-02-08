#include <unistd.h>
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;
using std::ifstream;


const int MAXgridSize = 10;

struct data {
int grid[MAXgridSize*MAXgridSize] = { 0 };
int rowSums[MAXgridSize] = { 0 };
int colSums[MAXgridSize] = { 0 };
int sizeX, sizeY;
int actualX, actualY;
int endX, endY;
};

int showGrid(data &indata);
void printRows(data &indata);
bool endConditionMet(data &indata);
int validUp(data &indata);
int validDown(data &indata);
int validRight(data &indata);
int validLeft(data &indata);
void ClearScreen();
void endRutine(data &indata);

int main(int argc, char *argv[]) {
    if ( argc == 2 ) {
        cout << "Inupt file: " << argv[1] << endl;
    } else if ( argc > 2 ) {
        cout << "To many argument" << endl;
        return -1;
    } else {
        cout << "One argument expected" << endl;
        return -1;
    }

    data data1;
    int popInt;
    bool skipUp = false, skipDown = false, skipLeft = false, skipRight = false;
    char temp;

    ifstream myfile;
    myfile.open(argv[1]);

    myfile >> data1.sizeX >> temp >> data1.sizeY;
    myfile >> data1.actualX >> temp >> data1.actualY;
    myfile >> data1.endX >> temp >> data1.endY;


    for (int i=0; i < data1.sizeX ; i++) {
        myfile >> data1.colSums[i];
    }
    for (int i=0; i < data1.sizeY ; i++) {
        myfile >> data1.rowSums[i];
    }

    myfile.close();

    data1.grid[data1.actualX + data1.sizeX * data1.actualY] = 5;

    do {
        if ( validUp(data1) and not skipUp ) {
            data1.grid[data1.actualX + data1.sizeX * (--data1.actualY)] = 1;
            if (endConditionMet(data1)) {
                endRutine(data1);
                return 0;
            }
            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;
        } else if (validRight(data1) and not skipRight) {
            data1.grid[++data1.actualX + data1.sizeX * (data1.actualY)] = 2;
            if (endConditionMet(data1)) {
                endRutine(data1);
                return 0;
            }
            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;
        } else if (validDown(data1) and not skipDown) {
            data1.grid[data1.actualX + data1.sizeX * (++data1.actualY)] = 3;
            if (endConditionMet(data1)) {
                endRutine(data1);
                return 0;
            }
            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;
        } else if (validLeft(data1) and not skipLeft) {
            data1.grid[--data1.actualX + data1.sizeX * (data1.actualY)] = 4;
            if (endConditionMet(data1)) {
                endRutine(data1);
                return 0;
            }
            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;
        } else if ( skipUp == true and skipDown == true and skipLeft == true and skipRight == true and popInt != 4 ) {

            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;

            switch ( popInt ) {
                case 1:
                    skipUp = true;
                    break;
                case 2:
                    skipUp = true; skipRight = true;
                    break;
                case 3:
                    skipUp = true; skipRight = true; skipDown = true;
                    break;
                case 4:
                    skipUp = true; skipRight = true; skipDown = true; skipLeft = true;
                    break;
                case 5:
                    cout << "koniec1";
                    return -1;
                    break;
            }
        } else {
            popInt = data1.grid[data1.actualX + data1.sizeX * data1.actualY];
            data1.grid[data1.actualX + data1.sizeX * data1.actualY] = 0;

            skipUp = false; skipRight = false; skipDown = false; skipLeft = false;

            switch ( popInt ) {
                case 1:
                    skipUp = true;
                    data1.actualY++;
                    break;
                case 2:
                    skipUp = true; skipRight = true;
                    data1.actualX--;
                    break;
                case 3:
                    skipUp = true; skipRight = true; skipDown = true;
                    data1.actualY--;
                    break;
                case 4:
                    skipUp = true; skipRight = true; skipDown = true; skipLeft = true;
                    data1.actualX++;
                    break;
                case 5:
                    cout << "THE END";
                    return -1;
            }
        }

        // usleep(355000);
        // ClearScreen();
        // showGrid(data1);
    } while (true);

    return 0;
}

int showGrid(data &indata) {
    for (int i=0; i < indata.sizeY; i++) {

        for (int j = 0; j < indata.sizeX; j++) {
            cout<< indata.grid[j+indata.sizeX*i] <<" ";
        }
        cout << endl;
    }
    return 0;
}

void printRows(data &indata) {
    int i, j, sum = 0;
        for (i = 0; i < indata.sizeY; ++i) {
            for (j = 0; j < indata.sizeX; ++j) {
                if (indata.grid[i+indata.sizeX*j] != 0 ) sum++;
            }
            cout << "Sum of the col " << i << " = " << sum   << endl;
            sum = 0;
            }

        sum = 0;
        for (i = 0; i < indata.sizeX ; ++i) {
            for (j = 0; j < indata.sizeY; ++j) {
                if (indata.grid[j+indata.sizeX*i] != 0 ) sum++;
            }
            cout << "Sum of the row " << i << " = " << sum   << endl;
            sum = 0;
        }
}

bool endConditionMet(data &indata) {
    int i, j, sum = 0;

    if ( indata.endX == indata.actualX and indata.endY == indata.actualY ) {
        for (i = 0; i < indata.sizeY ; ++i) {
            for (j = 0; j < indata.sizeX ; ++j) {
                if (indata.grid[i+indata.sizeX*j] != 0 ) sum++;
            }
            if (sum != indata.colSums[i] and indata.colSums[i] != 0) {
                return false;
            }
            sum = 0;
        }

        sum = 0;
        for (i = 0; i < indata.sizeX ; ++i) {
            for (j = 0; j < indata.sizeY ; ++j) {
                if (indata.grid[j+indata.sizeX*i] != 0 ) sum++;
            }
            if (sum != indata.rowSums[i] and indata.rowSums[i] != 0) {
                return false;
            }
            sum = 0;
        }
        return true;
    }
    return false;
}

int validUp(data &indata) {
    bool result_valid = true;

    if ( indata.actualY-1 >= 0 ) {

        if ( indata.grid[ indata.actualX + indata.sizeX * (indata.actualY-1)] != 0 ) return false;

        if ( indata.actualX - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

        if ( indata.actualX + 1  < indata.sizeX ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

    } else { return false; }

    if ( indata.actualY-2 >= 0 ) {

        if ( indata.grid[ indata.actualX + indata.sizeX * (indata.actualY-2)] != 0 ) return false;

        if ( indata.actualX - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY-2)] != 0 ) return false;
        }

        if ( indata.actualX + 1  < indata.sizeX ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY-2)] != 0 ) return false;
        }
    }

    return true;
}

int validDown(data &indata) {
    bool result_valid = true;

    if ( indata.actualY+1 < indata.sizeY ) {

        if ( indata.grid[ indata.actualX + indata.sizeX * (indata.actualY+1)] != 0 ) return false;

        if ( indata.actualX - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }

        if ( indata.actualX + 1  < indata.sizeX ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }


    } else { return false; }

    if ( indata.actualY+2 < indata.sizeY ) {

        if ( indata.grid[ indata.actualX + indata.sizeX * (indata.actualY+2)] != 0 ) return false;

        if ( indata.actualX - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY+2)] != 0 ) return false;
        }

        if ( indata.actualX + 1  < indata.sizeX ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY+2)] != 0 ) return false;
        }
    }

    return true;
}

int validRight(data &indata) {

    if ( indata.actualX+1 < indata.sizeX ) {

        if ( indata.grid[ indata.actualX + 1 + indata.sizeX * (indata.actualY)] != 0 ) return false;

        if ( indata.actualY - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

        if ( indata.actualY + 1  < indata.sizeY ) {
            if ( indata.grid[ indata.actualX+1 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }


    } else { return false; }

    if ( indata.actualX+2 < indata.sizeX ) {

        if ( indata.grid[ indata.actualX + 2 + indata.sizeX * (indata.actualY)] != 0 ) return false;

        if ( indata.actualY - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX+2 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

        if ( indata.actualY + 1  < indata.sizeY ) {
            if ( indata.grid[ indata.actualX+2 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }
    }

    return true;
}

int validLeft(data &indata) {

    if ( indata.actualX-1 >= 0 ) {

        if ( indata.grid[ indata.actualX - 1 + indata.sizeX * (indata.actualY)] != 0 ) return false;

        if ( indata.actualY - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

        if ( indata.actualY + 1  < indata.sizeY ) {
            if ( indata.grid[ indata.actualX-1 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }


    } else { return false; }

    if ( indata.actualX-2 >= 0 ) {

        if ( indata.grid[ indata.actualX - 2 + indata.sizeX * (indata.actualY)] != 0 ) return false;

        if ( indata.actualY - 1  >= 0 ) {
            if ( indata.grid[ indata.actualX-2 + indata.sizeX * (indata.actualY-1)] != 0 ) return false;
        }

        if ( indata.actualY + 1  < indata.sizeY ) {
            if ( indata.grid[ indata.actualX-2 + indata.sizeX * (indata.actualY+1)] != 0 ) return false;
        }
    }

    return true;
}

void ClearScreen() {
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

void endRutine(data &indata) {
                ClearScreen();
                showGrid(indata);
                printRows(indata);
}
