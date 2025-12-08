#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; // 1 <= N <= 10^5
    map<int, int> meetings;
    map<int, int> same;

    cin >> N;

    // edge case 정리
    // 회의의 시작시간과 끝나는 시간이 같은 경우
    //// 위에꺼 사례 하나 찾음. 1 1만 10개를 넣는 경우 2가 출력됨
    //// 10이 출력되어야함. same의 개수를 세어 해결

    // edge case 또 찾음, 2 2와 2 5가 들어왔을때, 2 2만 살게 됨.
    // 예를 same의 개수를 세는 same이라는 map을 두어서 해결

    // 회의가 끝나는 동시에 다음 회의가 시작되는 경우
    // N == 1인 경우

    for(int i = 0; i < N; i++) {
        int begin;
        int end;

        cin >> begin >> end;

        if(meetings.find(end) == meetings.end()) { // 아예 한번도 들어온 적 없는 경우
            meetings[end] = begin; // 회의를 하나 만들어 주고
            if(end == begin) { // 만약 처음 들어왔는데 같았다?
                same[end] = 1; // 그러면 same이 1이된다.
            }

            continue;
        }

        if(end == begin) { // 들어온 적이 있는데 같은게 들어온다.
            same[end]++; // same만 올려준다.
            continue;
        }

        if(meetings[end] == end) { // 들어온 적이 있는데 다른게 들어온다. 그러나 처음에 들어올 때 같은 값이 들어왔다.
            meetings[end] = begin; // 지금 들어온 애로 초기화 해준다.
            continue;
        }

        if(meetings[end] < begin) { // 들어온 적이 있는데 다른게 들어왔고 마지막으로 회의 종료시간이 같은데 지금 들어온 애가 시작시간이 뒤이면
            meetings[end] = begin; // update
            continue;
        }

    }
    vector<int> prev;
    prev.push_back(meetings.begin()->first); // end
    prev.push_back(meetings.begin()->second); // begin

    int count = 0;

    if(meetings.begin()->first == meetings.begin()->second) { // 초기 조건, 같은 놈들밖에 없으면 count에 same 값만 더해줌
        count += same[meetings.begin()->first];
    }

    else { // 아니라면 1도 더 더해줌.
        count = same[meetings.begin()->first] + 1;
    }

    auto st = meetings.begin();
    st++; // begin의 다음부터 탐색할 것

    for(auto it = st; it != meetings.end(); it++) {
        if(it->first == it->second) { // 같은 놈들밖에 없으면
            count += same[it->first]; // same값만 더해줌
        }

        else if(prev[0] <= it->second) { // 다를 때, greedy method로 종료시각보다 시작시각이 후이면 prev로 현재 iterator를 채택.
            count += same[it->first]; // same값과
            prev[0] = it->first;
            prev[1] = it->second;
            count++; // 1을 더해준다.
        }
    }

    cout << count << '\n';

	return 0;
}

// 전체적으로 없는 key를 탐색하면 0을 return 하는 것을 볼 수 있다.