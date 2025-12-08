#include <bits/stdc++.h>
using namespace std;

class woobak_number {
public :
    woobak_number() {}
    woobak_number(long long x, int y);

    vector<long long>& get_A1_numbers() { return A1_numbers;}


private :
    long long A;
    int i;

    vector<unique_ptr<woobak_number>> next_A;
    vector<long long> A1_numbers;
};

woobak_number::woobak_number(long long x, int y) {
    A = x; i = y;

    long long next1 = 2 * A;
    long long next2 = 0;

    if((A - 1) >= 3 && (A - 1) % 3 == 0) {
        next2 = (A - 1) / 3;
    }
    
    if(i > 1 && next1 % 2 == 0) {
        next_A.push_back(make_unique<woobak_number>(next1, i - 1));
        
    }

    if(i > 1 && next2 > 1 && next2 % 2 == 1) {
        next_A.push_back(make_unique<woobak_number>(next2, i - 1));
    }

    if(i == 2) {
        for(int n = 0; n < next_A.size(); n++) {
            A1_numbers.push_back(next_A[n]->A);
        }
    }

    if(i > 2) {
        for(int n = 0; n < next_A.size(); n++) {
            if(A1_numbers.size() == 0) {
                A1_numbers = next_A[n]->A1_numbers;
            }

            else {
                A1_numbers.insert(A1_numbers.end(), next_A[n]->A1_numbers.begin(), next_A[n]->A1_numbers.end());
            }
        }
    }
}

class woobak {
public : 
    woobak() {}
    woobak(int n);
    void compute_A1();


private : 
    unique_ptr<woobak_number> root;
    int N;
    map<long long, long long> A1s;
};

woobak::woobak(int n) {
    N = n;
    root = make_unique<woobak_number>(1, N);

    for(auto A : root->get_A1_numbers()) {
        A1s[A] = A;
    }

    if(A1s.size() == 0) {
        A1s[1] = 1;
    }
}

void woobak::compute_A1() {
    cout << A1s.size() << '\n';
    for(auto it = A1s.begin(); it != A1s.end(); it++) {
        cout << it->first << '\n';
    }
}



int main() {
    int N;

    cin >> N;

    woobak w(N);

    w.compute_A1();

	return 0;
}