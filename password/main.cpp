#include <bits/stdc++.h>
using namespace std;

int L, C;
// 코드 짜다 지쳐서 무슨 알고리즘이지 하고 찾아보니까 BRUTE-FORCE였던....

class Password{
public :
    Password(string c, int no, int ne, int vv, int cc) : cur(c), now(no), next(ne), v(vv), c(cc) {}
    string& get_cur() { return cur; }
    int& operator[](const int n);

private :
    string cur;
    int now;
    int next;
    int v; 
    int c;
};

int& Password::operator[](const int n) {
    switch(n) {    
        case 1 :
            return now;
            break;

        case 2 :
            return next;
            break;

        case 3 : 
            return v;
            break;

        case 4 :
            return c;
            break;

        default :
            throw out_of_range("Invalid index for Password");
            break;
    }
}

bool is_vowel(char s) {
    if(s == 'a') { return true; }

    else if(s == 'e') { return true; }

    else if(s == 'i') { return true; }

    else if(s == 'o') { return true; }

    else if(s == 'u') { return true; }

    else { return false; }
}

void dfs(string s, int now, string l, int v, int c) {
    l += s[now];

    if(is_vowel(s[now])) v++;
    else c++;

    if(l.size() == L) {
        if(v >= 1 && c >= 2) cout << l << '\n';
        return;
    }

    for(int i = now + 1; i < C; i++) dfs(s, i, l, v, c);
    return;
}

void dfs_with_stack(string s) {
    stack<Password> pw_st;

    string c = "";
    c += s[0];

    Password pw(c, 0, 1, is_vowel(s[0]), !is_vowel(s[0]));

    pw_st.push(pw);

    while(!pw_st.empty()) {
        string str = pw_st.top().get_cur();
        int now = pw_st.top()[1];
        int next = pw_st.top()[2];
        int nv = pw_st.top()[3];
        int ns = pw_st.top()[4];

        if(str.size() == L) {
            if(nv >= 1 && ns >= 2) {
                cout << str << '\n';
            }

            pw_st.pop();
            pw_st.top()[2]++;

            continue;
        }

        if(next == C && pw_st.size() != 1) {
            pw_st.pop();
            pw_st.top()[2]++;

            continue;
        }

        if(next == C && pw_st.size() == 1) {
            if(now == C - L) {
                pw_st.pop();
            }

            else{
                pw_st.pop();
                now += 1;

                string empty = "";
                empty += s[now];
                Password new_base(empty, now, now + 1, is_vowel(s[now]), !is_vowel(s[now]));
                pw_st.push(new_base);
            }

            continue;
        }


        Password new_pw(str + s[next], next, next + 1, nv + is_vowel(s[next]), ns + !is_vowel(s[next]));

        pw_st.push(new_pw);
    }

}

int main() {

    ios::sync_with_stdio(false); cin.tie(NULL);

    cin >> L >> C;

    string alphabet ="";

    for(int i = 0; i < C; i++) {
        string p;
        cin >> p;
        alphabet += p;
    }

    sort(alphabet.begin(), alphabet.end());

    // for(int i = 0; i <= C - L; i++) {
    //     dfs(alphabet, i, "", 0, 0);
    // }

    dfs_with_stack(alphabet);

	return 0;
}