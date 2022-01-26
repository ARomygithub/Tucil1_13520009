#include <bits/stdc++.h>
using namespace std;

// maksimal dari banyak baris atau kolom adalah 200
const int mxn=200; 
// Transisi baris dan kolom untuk setiap 8 arah
const int dr[8]= {-1,-1,0,1,1,1,0,-1}, dc[8]= {0,-1,-1,-1,0,1,1,1};
// 12 pilihan warna untuk kata yang ditemukan
char* clr[12] = {"\x1B[31m", "\x1B[32m", "\x1B[33m", "\x1B[34m", "\x1B[35m", "\x1B[36m", "\x1B[1m\x1B[31m", "\x1B[1m\x1B[32m", "\x1B[1m\x1B[33m", "\x1B[1m\x1B[34m", "\x1B[1m\x1B[35m", "\x1B[1m\x1B[36m"};
// warna putih untuk mereset mode print berwarna
const char* RESET = "\x1B[0m";
int n,m,ct_w;
string file_path;
// puzzle sebagai matriks huruf, word sebagai daftar kata
string puzzle[mxn], word[mxn]; 
// color menyimpan warna setiap huruf dan diinisialisasi dengan warna putih
vector<vector<char *>> color(mxn,vector<char *>(mxn,"\x1B[37m"));
int clridx=0; // counter untuk warna berikutnya

bool in_puzzle(int r, int c) {
    // mengembalikan true jika (r,c) indeks yang valid pada puzzle berukuran n*m
    return r>=0&&r<n&&c>=0&&c<m;
}

void solve() {
    // prosedur algoritma brute force untuk permasalahan string matching daftar kata word[ct_w]
    // pada matriks huruf puzzle[n][m] dengan 8 kemungkinan arah 
    int count_compare=0;
    clock_t start, end;
    // memulai timer
    start = clock();
    for(int w=0;w<ct_w;w++) {                                      // memilih kata berikutnya
        // inisialisasi status pencarian dan panjang kata
        bool found=false;
        int length = word[w].length();
        for(int i=0;i<n&&!found;i++) {                     // memilih petak awal berikutnya
            for(int j=0;j<m&&!found;j++) {
                for(int k=0;k<8&&!found;k++) {                     // memilih arah berikutnya
                    if(in_puzzle(i+(length-1)*dr[k],j+(length-1)*dc[k])) {
                        // panjang kata yang dicari dapat dicapai
                        int l=0;
                        while(l<length) {
                            // pencocokan karakter hingga semua cocok atau ada yang tidak cocok
                            count_compare++;
                            if(puzzle[i+l*dr[k]][j+l*dc[k]]==word[w][l]) {
                                l++;
                            } else {
                                break;
                            }
                        }
                        if(l==length) {
                            // semua karakter cocok, lakukan pewarnaan
                            found=true;
                            for(int l1=0;l1<l;l1++) {
                                color[i+l1*dr[k]][j+l1*dc[k]] = clr[clridx];
                            }
                            clridx = (clridx+1)%12; // berputar ke warna berikutnya
                        }
                    }
                }
            }
        }
    }
    end = clock();
    double exec_time = double(end-start)/double(CLOCKS_PER_SEC);
    // semua kata sudah dicari, mulai output matriks huruf sesuai warna
    cout <<"Berikut solusi puzzle yang didapat:\n";
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
    // output waktu pencarian dan total perbandingan huruf
    cout <<"Waktu pencarian: ";
    cout <<fixed <<setprecision(6) <<exec_time <<" sec\n";
    cout <<"Total perbandingan huruf: ";
    cout <<count_compare <<" kali\n";
    // sleep 10 detik agar output tidak langsung hilang
    this_thread::sleep_for(chrono::seconds(10));
}

int main() {
    // membaca lokasi (path) file input dari pengguna
    cout <<"Masukkan lokasi file puzzle: ";
    getline(cin,file_path);
    // mengalihkan stream dari stdin ke file input
    const char * path=file_path.c_str();
    freopen(path, "r", stdin);
    // loop membaca matriks huruf dan 1 baris kosong
    for(int i=0;;i++) {
        if(i>=mxn) {
            cout <<"[ERROR] Ukuran puzzle terlalu besar\n";
            return 0;
        }
        // membaca baris i
        string s;
        getline(cin,s);
        if(s.length()>0) {
            // baris tidak kosong artinya masih termasuk matriks huruf
            puzzle[i] = s;
            while(puzzle[i].find(' ')!=string::npos) {
                // menghapus setiap spasi pada baris
                puzzle[i].erase(puzzle[i].find(' '), 1);
            }
        } else {
            // sudah mencapai baris kosong, matriks huruf sudah terbaca semua
            // ukuran matriks adalah n*m
            n = i;
            m = puzzle[n-1].length();
            break;
        }
    }
    string s;
    int i = 0;
    while(getline(cin,s)) {
        // membaca setiap kata yang ingin dicari
        word[i] = s;
        i++;
    }
    // banyak kata dalam daftar adalah ct_w
    ct_w = i;
    // melakukan algoritma pencarian dan output
    solve();
}
