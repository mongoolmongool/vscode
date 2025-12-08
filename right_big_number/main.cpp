#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    int N; // N <= 1M

    cin >> N;

    int* rbn = new int[N];

    int* st_value = new int[N];
    int* top_value = st_value - 1;

    int* st_index = new int[N];
    int* top_index = st_index - 1;

    int A; // A <= 1M

    for(int i = 0; i < N; i++){ // i는 current idx임.
        cin >> A; // A는 current value임.

        while((top_value >= st_value) && (A > *top_value)){
            rbn[*top_index] = A;
            top_value--;
            top_index--;
        }

        rbn[i] = -1;
        top_value++;
        top_index++;
        *top_value = A;
        *top_index = i;
    }

    for(int i = 0; i < N; i++){
        cout << rbn[i] << ' ';
    }

    cout << '\n';

    delete[] rbn;
    delete[] st_value;
    delete[] st_index;

	return 0;
}