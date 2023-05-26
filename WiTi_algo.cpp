#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;

int main() {
    int N, power;

    string sets[11] = {"data.10:", "data.11:", "data.12:", "data.13:", "data.14:", "data.15:",
                        "data.16:", "data.17:", "data.18:", "data.19:", "data.20:"};

    for (int i = 0; i < 11; i++) {
        ifstream inputdata("data2.txt");
        string caret = "";
        while (caret != sets[i]) {
            inputdata >> caret;
        }
        inputdata >> N;

        int *P = new int[N];
        int *W = new int[N];
        int *D = new int[N];

        for (int i = 0; i < N; i++) {
            inputdata >> P[i] >> W[i] >> D[i];
        }
        inputdata.close();

        power = pow(2, N);

        int *F = new int[power];
        int *C = new int[power];

        int Cmax, ans, min;

        F[0] = 0;
        C[0] = 0;

        for (int j = 1; j < power; ++j) {
            Cmax = 0;
            for (int k = 0, bit = 1; bit <= j; bit *= 2, k++) {
                if (j & bit) {
                    C[j] = Cmax += P[k];
                }
            }
            min = 99999;
            for (int k = 0, bit = 1; bit <= j; bit *= 2, k++) {
                if (j & bit) {
                    ans = F[j - bit] + (W[k] * max(0, Cmax - D[k]));
                    if (ans < min) {
                        min = ans;
                    }
                }
            }

            F[j] = min;

        }

        cout << sets[i] << endl;
        cout << F[power - 1] << endl;

        vector<int> order;

        int problem = power - 1;

        int minSubproblem = -1;
        int minPenalty = INT_MAX;
        int minSubID = -1;

        while (problem >= 0) {
            minSubproblem = -1;
            minPenalty = INT_MAX;
            minSubID = -1;

            for (int i = 0; i < N; i++) {
                if (problem & (1 << i)) { 
                    int subproblem = problem & ~(1 << i); 
                    int penalty = F[subproblem] + (W[i] * max(0, C[problem] - D[i]));
                    if (penalty < minPenalty) {
                        minSubproblem = subproblem;
                        minPenalty = penalty;
                        minSubID = i;
                    }
                }
            }

            if (minSubproblem >= 0) {
                order.push_back(minSubID + 1);
                problem = minSubproblem;
            } else {
                break;
            }
        }

        reverse(order.begin(), order.end());

        for (int i = 0; i < order.size(); i++) {
            cout << order[i] << " ";
        }

        cout << endl << "##################################" << endl;

        delete[] P;
        delete[] W;
        delete[] D;
        delete[] C;
        delete[] F;
    }

    return 0;
}
