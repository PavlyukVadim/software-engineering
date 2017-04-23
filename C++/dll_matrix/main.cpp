#define DLL_EXPORT
#include "main.h"

using namespace std;

extern "C" {

    DECLDIR void generateArr(int n, int m, int **arr) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                arr[i][j] = (rand() % 10 + 1);
            }
        }
    }

    DECLDIR void showResult (int n, int m, int **arr, int *sum) {
        cout << "Matrix: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "Row sum: " << endl;
        for (int i = 0; i < n; i++) {
            cout << i + 1 << " " << sum[i] << endl;
        }
    }

    DECLDIR void countRowSum(int n, int m, int **arr, int* sums) {
        for (int i = 0; i < n; i++) {
            sums[i] = 0;
            for (int j = 0; j < m; j++) {
                sums[i] += arr[i][j];
            }
        }
    }
}
