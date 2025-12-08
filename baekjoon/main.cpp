#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    // 결국 낮에 다 올라간다.
    // (c - a 이상인 가장 작은 (a - b)의 배수 / (a - b)) + 1이 답이다.

    if ((c - a) % (a - b) == 0) {
        std::cout << (c - a) / (a - b) + 1 << '\n';
    }

    else {
        std::cout << (c - a) / (a - b) + 2 << '\n';
    }
}