#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define fst first
#define scd second

using ll = int64_t;

const int N = (int)5e5 + 20;
const int K = 25;
const int INF = (int)2e9;
int a[N], st[K][N], lg[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    lg[1] = 0;
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i/2] + 1;
    }

    for (int j = 0; j < n; j++) {
        st[0][j] = a[j];
    }

    for (int i = 1; i <= K; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }

    while(q--) {
        int L, R; cin >> L >> R;
        int i = lg[R - L];

        // min in range [L, R)
        cout << min(st[i][L], st[i][R - (1 << i)]) << "\n";
    }

    return 0;
}