#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN_ELEMENTS = 1000005;
const int MAX_BLOCKS = 2005; // sqrt(10^6) is 1000. 2005 is safe.

int a[MAXN_ELEMENTS];
int add[MAX_BLOCKS];
int mul[MAX_BLOCKS];
int s_arr[MAX_BLOCKS]; // 块和

int n, q, mod, k_val;

// 下推标记函数
void push_down(int block_idx) {
    if (mul[block_idx] == 1 && add[block_idx] == 0) return;

    int block_start = block_idx * k_val;
    int block_end = min(n, (block_idx + 1) * k_val);

    for (int i = block_start; i < block_end; i++) {
        a[i] = a[i] * mul[block_idx] + add[block_idx];
        // 关键的模运算和负数处理
        a[i] %= mod;
        if (a[i] < 0) a[i] += mod;
    }
    mul[block_idx] = 1;
    add[block_idx] = 0;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q >> mod;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    k_val = sqrt(n);
    if (k_val == 0) k_val = 1;

    int num_blocks = (n + k_val - 1) / k_val;
    if (n == 0) num_blocks = 0;

    for (int i = 0; i < num_blocks; i++) {
        add[i] = 0;
        mul[i] = 1;
        s_arr[i] = 0;
        int block_start = i * k_val;
        int block_end = min(n, (i + 1) * k_val);
        for (int j = block_start; j < block_end; j++) {
            a[j] %= mod; // 初始化时规范化
            if (a[j] < 0) a[j] += mod;
            s_arr[i] = (s_arr[i] + a[j]);
            if (s_arr[i] >= mod) s_arr[i] -= mod; // 累加时处理上溢
        }
    }

    for (int I = 0; I < q; I++) {
        int op, l_orig, r_orig, c_val;
        cin >> op >> l_orig >> r_orig;
        l_orig--; 
        r_orig--; 

        int bl = l_orig / k_val;
        int br = r_orig / k_val;

        if (op == 1) { // 乘法
            cin >> c_val;
            c_val %= mod;
            if (c_val < 0) c_val += mod;

            push_down(bl);
            if (bl != br) {
                push_down(br);
            }

            if (bl == br) {
                for (int i = l_orig; i <= r_orig; i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c_val) % mod;
                    if (a[i] < 0) a[i] += mod;
                    
                    s_arr[bl] = (s_arr[bl] + a[i] - old_ai + mod) % mod; // V2风格的块和更新
                }
            } else {
                // 左散块
                for (int i = l_orig; i < min(n, (bl + 1) * k_val); i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c_val) % mod;
                    if (a[i] < 0) a[i] += mod;
                    s_arr[bl] = (s_arr[bl] + a[i] - old_ai + mod) % mod;
                }
                // 中间整块
                for (int i = bl + 1; i < br; i++) {
                    s_arr[i] = (s_arr[i] * c_val) % mod;
                    add[i] = (add[i] * c_val) % mod;
                    mul[i] = (mul[i] * c_val) % mod;
                    // 确保中间整块的标记和块和也是规范的
                    if (s_arr[i] < 0) s_arr[i] += mod;
                    if (add[i] < 0) add[i] += mod;
                    if (mul[i] < 0) mul[i] += mod;
                }
                // 右散块
                for (int i = br * k_val; i <= r_orig; i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c_val) % mod;
                    if (a[i] < 0) a[i] += mod;
                    s_arr[br] = (s_arr[br] + a[i] - old_ai + mod) % mod;
                }
            }
        } else if (op == 2) { // 加法
            cin >> c_val;
            c_val %= mod;
            if (c_val < 0) c_val += mod;

            push_down(bl);
            if (bl != br) {
                push_down(br);
            }
            
            if (bl == br) {
                int count_in_range = 0;
                for (int i = l_orig; i <= r_orig; i++) {
                    a[i] = (a[i] + c_val);
                    if (a[i] >= mod) a[i] -= mod; 
                    // else if (a[i] < 0) a[i] += mod; // 如果c_val可能使a[i]变负
                    count_in_range++;
                }
                s_arr[bl] = (s_arr[bl] + c_val * count_in_range) % mod;
                if (s_arr[bl] < 0) s_arr[bl] += mod;

            } else {
                // 左散块
                int count_left = 0;
                for (int i = l_orig; i < min(n, (bl + 1) * k_val); i++) {
                    a[i] = (a[i] + c_val);
                    if (a[i] >= mod) a[i] -= mod;
                    count_left++;
                }    
                s_arr[bl] = (s_arr[bl] + c_val * count_left) % mod;
                if (s_arr[bl] < 0) s_arr[bl] += mod;

                // 中间整块
                for (int i = bl + 1; i < br; i++) {
                    int current_block_len = min(n, (i + 1) * k_val) - (i * k_val);
                    s_arr[i] = (s_arr[i] + c_val * current_block_len) % mod;
                    add[i] = (add[i] + c_val) % mod;
                    
                    if (s_arr[i] < 0) s_arr[i] += mod;
                    if (add[i] < 0) add[i] += mod;
                }
                // 右散块
                int count_right = 0;
                for (int i = br * k_val; i <= r_orig; i++) {
                    a[i] = (a[i] + c_val);
                    if (a[i] >= mod) a[i] -= mod;
                    count_right++;
                }
                s_arr[br] = (s_arr[br] + c_val * count_right) % mod;
                if (s_arr[br] < 0) s_arr[br] += mod;
            }        
        } else { // 查询 (op == 3)
            long long ans = 0;
            if (bl == br) {
                for (int i = l_orig; i <= r_orig; i++) {
                    ans = (ans + (a[i] * mul[bl] + add[bl]));
                }
            } else {
                for (int i = l_orig; i < min(n, (bl + 1) * k_val); i++) {
                    ans = (ans + (a[i] * mul[bl] + add[bl]));
                }
                for (int i = bl + 1; i < br; i++) {
                    ans = (ans + s_arr[i]);
                }    
                for (int i = br * k_val; i <= r_orig; i++) {
                    ans = (ans + (a[i] * mul[br] + add[br]));
                }
            }
            ans %= mod;
            if (ans < 0) ans += mod;
            cout << ans << '\n';
        }
    }
    return 0;
}