#include <bits/stdc++.h>
using namespace std;

int binary_search(int low, int high, int goal) {
	int mid = (high + low) / 2;
	int ans;

	while(true) {
		if(low == goal) {
			ans = low;
			break;
		}

		else if(high == goal) {
			ans = high;
			break;
		}

		if(mid <= goal) {
			low = mid;
		}

		else {
			high = mid;
		}

		mid = (high + low) / 2;

		if(low == mid) {
			ans = low;
			break;
		}

			
	}

	return (ans == goal);
}

int main() {
    for(int i = 1; i <= 1000; i++) {
		cout << binary_search(1, 1000, i) << '\n';
	}
	return 0;
}