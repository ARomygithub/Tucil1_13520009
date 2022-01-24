#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define ar array
#define sz(x) (int) (x).size()

const int mxn=1e5;
char* s[12] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m", "\x1B[36m", "\x1B[1m\x1B[31m", "\x1B[1m\x1B[32m", "\x1B[1m\x1B[33m", "\x1B[1m\x1B[34m", "\x1B[1m\x1B[35m", "\x1B[1m\x1B[36m"};
// char s1[10] = "\x1B[1m\x1B[31m";
int n,t;

void solve() {
    // system("Color 08");
    string normal = "\x1B[0m";
    char c = 'J';
    for(int i=0;i<12;i++) {
        char* b = s[i];
        cout <<b <<c;
        printf("%s\n", "\x1B[0m");
    }
    // char b[6] = "\x1B[37m";
    // cout <<s1 <<c;
    // printf("%s\n", "\x1B[0m");
    // cout <<s[0] <<c;
    // printf("%s\n", "\x1B[0m");
    // cout <<s <<"\n";
    // cout <<"Tes 08" <<endl;
    // // system("Color 09");
    // cout <<"Tes 09" <<endl;
    // system("Color 07");
    // cout <<"Tes 07" <<endl;
    cin >>n;
}

int main() {
    cin >>t;
    while(t--) {
        solve();
    }
}
