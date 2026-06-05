#include <iostream>
#include <cstring>
 
using namespace std;
 
const int MAXN = 100000;
const int MAXLEN = 100;
const int ALPHA = 27;
const int INSERTION = 32;
 
char pool[MAXN * (MAXLEN + 1)];
char* s[MAXN];
char* aux[MAXN];
 
int getChar(const char* str, int d) {
    char c = str[d];
 
    if (c == '\0') return 0;
 
    return (c - 'a' + 1);
}
 
void insertionSort(char** a, int l, int r, int d) {
 
    for (int i = l + 1; i <= r; ++i) {
 
        char* key = a[i];
        int j = i - 1;
 
        while (j >= l &&
               strcmp(a[j] + d, key + d) > 0) {
 
            a[j + 1] = a[j];
            --j;
        }
 
        a[j + 1] = key;
    }
}
 
void msdRadix(char** a, int l, int r, int d) {
 
    if (l >= r) return;
 
    if (r - l + 1 <= INSERTION) {
        insertionSort(a, l, r, d);
        return;
    }
 
    int cnt[ALPHA] = {};
    int pos[ALPHA];
    int cur[ALPHA];
 
    for (int i = l; i <= r; ++i) {
        ++cnt[getChar(a[i], d)];
    }
 
    pos[0] = l;
 
    for (int i = 1; i < ALPHA; ++i) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
 
    for (int i = 0; i < ALPHA; ++i) {
        cur[i] = pos[i];
    }
 
    for (int i = l; i <= r; ++i) {
 
        int c = getChar(a[i], d);
 
        aux[cur[c]++] = a[i];
    }
 
    for (int i = l; i <= r; ++i) {
        a[i] = aux[i];
    }
 
    for (int i = 1; i < ALPHA; ++i) {
 
        int L = pos[i];
        int R = pos[i] + cnt[i] - 1;
 
        if (L < R) {
            msdRadix(a, L, R, d + 1);
        }
    }
}
 
int main() {
 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
 
    char* ptr = pool;
 
    char tmp[MAXLEN + 1];
 
    for (int i = 0; i < n; ++i) {
 
        cin >> tmp;
 
        s[i] = ptr;
 
        strcpy(ptr, tmp);
 
        ptr += strlen(tmp) + 1;
    }
 
    msdRadix(s, 0, n - 1, 0);
 
    cout << n << '\n';
 
    for (int i = 0; i < n; ++i) {
        cout << s[i] << '\n';
    }
 
    return 0;
}
