#include <bits/stdc++.h>
using namespace std;

// v길이의 휴가가 가능한가?
bool possible(const vector<long long>& wage, long long k, long long x, long long v) { 

    long long earning = 0;
    long long not_vac = wage.size() - v; // 휴가가 아닌 날의 수, 즉 일하는 날의 수..

    long long starting_idx = not_vac - 1;
    // for문을 통해 휴가 출발일 전날 일당 부터 earning에 더해갈 것인데
    // starting_idx가 휴가 출발일 전날의 idx를 의미함

    // 첫번째 체크 : 휴가를 모두 뒤에 몰아서 휴가 앞에 not_vac일의 일을 하는 경우
    for(long long i = 0; i < not_vac; i++) {
        earning += x * wage[starting_idx - i];
        // starting_idx부터 0까지 더해주는 것이다.

        if(earning >= k) {
            return true;
        }
        // K를 넘었는지 체크, 넘었으면 휴가 v일이 possible 하다는 것이기 때문에...
    }

    // 두번째 체크 : 이제 v일의 휴가를 앞으로 땡겨보면서
    // 휴가 앞의 일당을 빼주고 휴가 뒤에 생기는 일당을 더해주면서 earning을 갱신한다.
    for(long long j = 0; j < not_vac; j++) {
        earning -= x * wage[starting_idx - j]; // 휴가 바로 앞쪽
        earning += wage[wage.size() - 1 - j]; // 휴가 바로 뒤

        if(earning >= k) {
            return true;
        }
        // K를 넘었는지 체크, possible 여부
    }

    // 여기까지 왔다는 것은 길이 v의 휴가에서 어떻게 휴가를 배치해도 earning이 K를 넘지 못한다는 것이다.
    // 그러므로 impossible -> false를 return 한다.
    return false;
}

int main() {
    long long N, K, X;

    // 일당 저장해놓는 벡터
    vector<long long> total_wage;

    long long first_check = 0; // 매일 일할 시 받는 wage.... yeoljeong pay!

    cin >> N >> K >> X;

    for(long long i = 0; i < N; i++) {
        long long a;
        cin >> a;
        total_wage.push_back(a);

        first_check += a * X;
    }

    // 먼저 휴가를 아예 못 나가는 경우를 제외한다.
    // 매일 일해도 기껏해야 K를 번다 = 휴가를 아예 못 나간다.
    if(first_check <= K) {
        cout << -1 << '\n';
        return 0;
    } 
        
    long long vac_high = N - 1; // 가장 많이 휴가를 나가는 경우
    long long vac_low = 0; // 가장 적게 휴가를 나가는 경우

    long long mid = (vac_high + vac_low) / 2; // binary search

    long long ans;

    // do! binary search
    while(vac_low <= vac_high) {
        mid = (vac_high + vac_low) / 2;

        if(possible(total_wage, K, X, mid)) {
            ans = mid;
            vac_low = mid + 1;
        }

        else{
            vac_high = mid - 1;
        }
    }

    // 얘 때문에 엄청 고생함...
    // ans가 0이라는 것은 휴가를 아예 못 나간다는 것
    // first_check를 통과했더라도 간신히 K를 넘기는 경우가 있었음.
    if(ans == 0) {
        cout << -1 << '\n';
        return 0;
    }

    else{
        // ans가 0이 아니라는 것은 휴가를 나갈 수 있다는 것
        // 그러므로 ans를 출력한다.
        cout << ans << '\n';
    }
        
    return 0;
}