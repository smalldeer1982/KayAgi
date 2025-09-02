#include<bits/stdc++.h>
#define int long long // Keep long long
using namespace std;

const int MAXN_ELEMENTS = 1000005;
const int MAX_BLOCKS = 2005; // Max blocks for N=10^6, k=sqrt(N) is ~1000. 2005 is safe.

int a[MAXN_ELEMENTS];
int add[MAX_BLOCKS]; // Your original add tag array
int mul[MAX_BLOCKS]; // Your original mul tag array
int s_arr[MAX_BLOCKS]; // NEW: To store block sums, similar to 's' in RefCode

int n, q, mod, k_val; // Changed k to k_val to avoid conflict with loop variables

// Your original update function (push_down for a block)
void update(int block_idx) {
    if (mul[block_idx] == 1 && add[block_idx] == 0) return; // Optimization: no tags to push

    int block_start = block_idx * k_val;
    int block_end = min(n, (block_idx + 1) * k_val);

    for (int i = block_start; i < block_end; i++) {
        a[i] = (a[i] * mul[block_idx] + add[block_idx]);
        if (a[i] >= mod || a[i] <= -mod) a[i] %= mod; // Keep a[i] manageable
        if (a[i] < 0) a[i] += mod;
    }
    mul[block_idx] = 1;
    add[block_idx] = 0;
}

// Helper for modulo arithmetic to ensure result is in [0, mod-1]
long long normalize(long long val) {
    if (val >= mod || val <= -mod) val %= mod;
    if (val < 0) val += mod;
    return val;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q >> mod;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        // a[i] = normalize(a[i]); // Initial normalization if numbers can be large/negative
    }

    // k=500; // Your original fixed k
    k_val = sqrt(n); // CHANGE: Use sqrt(n) like RefCode
    if (k_val == 0) k_val = 1; // Avoid k_val = 0 for small n

    int num_blocks = (n + k_val - 1) / k_val;
    if (n == 0) num_blocks = 0;

    for (int i = 0; i < num_blocks; i++) { // Adjusted loop limit
        add[i] = 0;
        mul[i] = 1;
        s_arr[i] = 0; // Initialize block sum
        int block_start = i * k_val;
        int block_end = min(n, (i + 1) * k_val);
        for (int j = block_start; j < block_end; j++) {
            a[j] = normalize(a[j]); // Normalize initial values
            s_arr[i] = (s_arr[i] + a[j]);
            if (s_arr[i] >= mod) s_arr[i] %= mod; // Keep sum manageable
        }
        s_arr[i] = normalize(s_arr[i]); // Final normalization for sum
    }

    for (int I = 0; I < q; I++) {
        int op, l, r, c;
        cin >> op >> l >> r;
        l--; 
        r--; 

        int bl = l / k_val;
        int br = r / k_val;

        if (op == 1) { // Multiply by c
            cin >> c;
            c = normalize(c);

            update(bl); // Push down for the starting block
            if (bl != br) {
                update(br); // Push down for the ending block if different
            }

            if (bl == br) { // Operation within a single block
                for (int i = l; i <= r; i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c);
                    a[i] = normalize(a[i]);
                    s_arr[bl] = (s_arr[bl] + a[i] - old_ai); // s_new = s_old + (a_new - a_old)
                    s_arr[bl] = normalize(s_arr[bl]);
                }
            } else {
                // Partial left block
                int left_block_actual_end = min(n, (bl + 1) * k_val);
                for (int i = l; i < left_block_actual_end; i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c);
                    a[i] = normalize(a[i]);
                    s_arr[bl] = (s_arr[bl] + a[i] - old_ai);
                    s_arr[bl] = normalize(s_arr[bl]);
                }
                // Full blocks in between
                for (int i = bl + 1; i < br; i++) {
                    s_arr[i] = (s_arr[i] * c);
                    add[i] = (add[i] * c);
                    mul[i] = (mul[i] * c);
                    s_arr[i] = normalize(s_arr[i]);
                    add[i] = normalize(add[i]);
                    mul[i] = normalize(mul[i]);
                }
                // Partial right block
                int right_block_actual_start = br * k_val;
                for (int i = right_block_actual_start; i <= r; i++) {
                    long long old_ai = a[i];
                    a[i] = (a[i] * c);
                    a[i] = normalize(a[i]);
                    s_arr[br] = (s_arr[br] + a[i] - old_ai);
                    s_arr[br] = normalize(s_arr[br]);
                }
            }
        } else if (op == 2) { // Add c
            cin >> c;
            c = normalize(c);

            update(bl);
            if (bl != br) {
                update(br);
            }
            
            if (bl == br) {
                for (int i = l; i <= r; i++) {
                    a[i] = (a[i] + c);
                    a[i] = normalize(a[i]);
                    s_arr[bl] = (s_arr[bl] + c);
                    s_arr[bl] = normalize(s_arr[bl]);
                }
            } else {
                // Partial left block
                int left_block_actual_end = min(n, (bl + 1) * k_val);
                int count_left = 0;
                for (int i = l; i < left_block_actual_end; i++) {
                    a[i] = (a[i] + c);
                    a[i] = normalize(a[i]);
                    count_left++;
                }
                s_arr[bl] = (s_arr[bl] + c * count_left);
                s_arr[bl] = normalize(s_arr[bl]);

                // Full blocks in between
                for (int i = bl + 1; i < br; i++) {
                    int current_block_len = min(n, (i + 1) * k_val) - (i * k_val); // Actual length
                    s_arr[i] = (s_arr[i] + c * current_block_len);
                    add[i] = (add[i] + c);
                    s_arr[i] = normalize(s_arr[i]);
                    add[i] = normalize(add[i]);
                }
                // Partial right block
                int right_block_actual_start = br * k_val;
                int count_right = 0;
                for (int i = right_block_actual_start; i <= r; i++) {
                    a[i] = (a[i] + c);
                    a[i] = normalize(a[i]);
                    count_right++;
                }
                s_arr[br] = (s_arr[br] + c * count_right);
                s_arr[br] = normalize(s_arr[br]);
            }        
        } else { // Query sum (op == 3)
            long long ans = 0;
            if (bl == br) {
                // update(bl); // Not strictly needed if query logic applies tags
                for (int i = l; i <= r; i++) {
                    long long current_val = (a[i] * mul[bl] + add[bl]);
                    ans = (ans + normalize(current_val));
                    if (ans >= mod) ans %= mod;
                }
            } else {
                // update(bl); // Not strictly needed
                int left_block_actual_end = min(n, (bl + 1) * k_val);
                for (int i = l; i < left_block_actual_end; i++) {
                    long long current_val = (a[i] * mul[bl] + add[bl]);
                    ans = (ans + normalize(current_val));
                    if (ans >= mod) ans %= mod;
                }

                for (int i = bl + 1; i < br; i++) {
                    ans = (ans + s_arr[i]); // s_arr[i] is already normalized and reflects tags
                    if (ans >= mod) ans %= mod;
                }    
                
                // update(br); // Not strictly needed
                int right_block_actual_start = br * k_val;
                for (int i = right_block_actual_start; i <= r; i++) {
                    long long current_val = (a[i] * mul[br] + add[br]);
                    ans = (ans + normalize(current_val));
                    if (ans >= mod) ans %= mod;
                }
            }
            cout << normalize(ans) << '\n';
        }
    }
    return 0;
}