#include <bits/stdc++.h>
using namespace std;

const int mxn=1e3;
const int MXPATH = 5e3;
const int dr[8]= {-1,-1,0,1,1,1,0,-1}, dc[8]= {0,-1,-1,-1,0,1,1,1};
char* clr[12] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m", "\x1B[36m", "\x1B[1m\x1B[31m", "\x1B[1m\x1B[32m", "\x1B[1m\x1B[33m", "\x1B[1m\x1B[34m", "\x1B[1m\x1B[35m", "\x1B[1m\x1B[36m"};
const char* RESET = "\x1B[0m";
int n,m,ct_w;
string file_path;
string puzzle[mxn], word[mxn];
vector<vector<char *>> color(mxn,vector<char *>(mxn,"\x1B[37m")); //inisialisasi warna huruf putih.
int clridx=0;

bool in_puzzle(int r, int c) {
    return r>=0&&r<n&&c>=0&&c<m;
}

void solve() {
    int count_compare=0;
    clock_t start, end;
    start = clock();
    for(int w=0;w<ct_w;w++) {
        bool found=false;
        int length = word[w].length();
        for(int i=0;i<n&&!found;i++) {                                      // Iterasi untuk setiap kotak awal
            for(int j=0;j<m&&!found;j++) {
                for(int k=0;k<8&&!found;k++) {                              // iterasi untuk setiap arah
                    if(in_puzzle(i+(length-1)*dr[k],j+(length-1)*dc[k])) {  // Cek kesesuaian dengan panjang kata
                        int l=0;
                        while(l<length) {
                            count_compare++;
                            if(puzzle[i+l*dr[k]][j+l*dc[k]]==word[w][l]) {
                                l++;
                            } else {
                                break;
                            }
                        }
                        if(l==length) {
                            found=true;
                            for(int l1=0;l1<l;l1++) {
                                color[i+l1*dr[k]][j+l1*dc[k]] = clr[clridx];
                            }
                            clridx = (clridx+1)%12;
                            // Warnain satu kata
                        }
                    }
                }
            }
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(j==0) {
                cout <<color[i][j] <<puzzle[i][j] <<RESET;
            } else {
                cout <<" " <<color[i][j] <<puzzle[i][j] <<RESET;
            }
        }
        cout <<"\n";
    }

    end = clock();
    double exec_time = double(end-start)/double(CLOCKS_PER_SEC);
    cout <<fixed <<setprecision(6) <<exec_time <<" sec\n";
    cout <<count_compare <<" kali\n";
    this_thread::sleep_for(chrono::seconds(10));
}

int main() {
    getline(cin,file_path);
    const char * path=file_path.c_str();
    freopen(path, "r", stdin);
    for(int i=0;;i++) {
        if(i>=mxn) {
            cout <<"[ERROR] Ukuran puzzle terlalu besar\n";
            return 0;
        }
        string s;
        getline(cin,s);
        if(s.find(' ')!=string::npos) {
            puzzle[i] = s;
            while(puzzle[i].find(' ')!=string::npos) {
                puzzle[i].erase(puzzle[i].find(' '), 1);
            }
            // cout <<puzzle[i] <<"\n";
        } else {
            n = i;
            m = puzzle[n-1].length();
            cout <<s;
            break; // asumsi ada baris kosong dan word yang akan dicari
        }
    }
    // cout <<n <<" " <<m;
    string s;
    int i = 0;
    while(getline(cin,s)) {
        word[i] = s;
        i++;
    }
    ct_w = i;
    // cout <<word[0] <<"\n";
    // cout <<word[1] <<"\n";
    // cout <<word[2] <<"\n";
    // cout <<"ct_w: " <<ct_w <<"\n";    
    solve();
}
