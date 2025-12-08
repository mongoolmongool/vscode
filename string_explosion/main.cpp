#include <bits/stdc++.h>
using namespace std;

// 1M 크기의 array
char c[1000000];

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL);

    // original_string
    string os;

    // explosive_string
    string es;

    // detector_front -> 처음 감지된 곳을 가리켜야함.
    char* detector_front;

    // detector_back -> 계속 ++하면서 가야함. act like an index
    char* detector_back = &c[0];

    getline(cin, os);
    getline(cin, es);

    int bomb = es.length();
    char last_char = es.back();

    for(int i = 0; i < os.size(); i++){
        *detector_back = os[i];

        if(*detector_back != last_char){
            detector_back++;
            continue; 
        }
        
        detector_front = detector_back - 1;

        for(int x = 1; x < bomb; x++){
            if((detector_front >= &c[0]) && (es[bomb-1-x] == *detector_front)) detector_front--;

            else break;
        }

        // detector_front == detector_back - bomb이면 detector_back = detector_front;
        detector_back = (detector_front == detector_back - bomb) ? detector_front : detector_back;

        detector_back++;
    }

    // 아무것도 없으면
    if(detector_back == &c[0]) cout << "FRULA\n";

    // c[0]부터 detector_back이 가리키는 곳까지 string으로 출력.
    else{
        for(auto it = &c[0]; it != detector_back; it++){
            cout << (*it);
        }
        cout << '\n';
    }
    
	return 0;
}