#include <iostream>
#include <windows.h>

using namespace std;

typedef void (*generateArr)(int n, int m, int **arr);
typedef void (*showResult)(int n, int m, int **arr, int *sum);
typedef void (*countRowSum)(int n, int m, int **arr, int* sums);

int main() {
    int t, // type gen matrix
        n, m;

    cout << "Input n, m : ";
    cin >> n >> m;

    int **arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
    }

    int *res = new int[n];

    cout << "0 - input" << endl << "!0 - random" << endl;
    cin >> t;

    if(!t) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
               cout << i + 1 << " " << j + 1 << " : ";
               cin >> arr[i][j];
            }
            cout << endl;
        }
    }

    generateArr genArr;
    countRowSum countR;
    showResult shRes;

    HINSTANCE hInstLibrary = LoadLibrary("dll_matrix.dll");
    if (hInstLibrary) {

        genArr = (generateArr)GetProcAddress(hInstLibrary, "generateArr");
        countR = (countRowSum)GetProcAddress(hInstLibrary, "countRowSum");
        shRes = (showResult)GetProcAddress(hInstLibrary, "showResult");

        if (genArr && t) {
            genArr(n, m, arr);
        }
        if (countR) {
            countR(n, m, arr, res);
        }
        if (shRes) {
            shRes(n, m ,arr, res);
        }

        FreeLibrary(hInstLibrary);
   }
   else {
      std::cout << "Error loading DDL ..." << std::endl;
   }

   return 0;
}
