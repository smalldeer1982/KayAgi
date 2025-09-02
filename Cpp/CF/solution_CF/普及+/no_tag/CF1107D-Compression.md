# Compression

## 题目描述

You are given a binary matrix $ A $ of size $ n \times n $ . Let's denote an $ x $ -compression of the given matrix as a matrix $ B $ of size $ \frac{n}{x} \times \frac{n}{x} $ such that for every $ i \in [1, n], j \in [1, n] $ the condition $ A[i][j] = B[\lceil \frac{i}{x} \rceil][\lceil \frac{j}{x} \rceil] $ is met.

Obviously, $ x $ -compression is possible only if $ x $ divides $ n $ , but this condition is not enough. For example, the following matrix of size $ 2 \times 2 $ does not have any $ 2 $ -compression:

 $ 01 $   $ 10 $ For the given matrix $ A $ , find maximum $ x $ such that an $ x $ -compression of this matrix is possible.

Note that the input is given in compressed form. But even though it is compressed, you'd better use fast input.

## 说明/提示

The first example corresponds to the matrix:

 $ 11100111 $   $ 11100111 $   $ 11100111 $   $ 00000000 $   $ 00000000 $   $ 11100111 $   $ 11100111 $   $ 11100111 $ It is easy to see that the answer on this example is $ 1 $ .

## 样例 #1

### 输入

```
8
E7
E7
E7
00
00
E7
E7
E7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
7
F
F
F
```

### 输出

```
1
```

# 题解

## 作者：__DICS (赞：3)

## 题意

给你一个01矩阵，问你最大可以压缩多少倍。

## 解

首先考虑一行内的压缩幅度。

一行里面显然是由很多个`0`段和`1`段构成的。

比方说`0001110001110010`由4个`0`段和3个`1`段构成。

对于一行来说，最大的压缩幅度是所有`01`段的长度的最大公约数。

再来看行与行之间的压缩幅度。

只要记录一下相等的行的数量，取最大公约数就可以了。

最后只要取行内的最大压缩幅度，和行间最大压缩幅度的最大公约数就是答案了。

## 代码

采用上述$\gcd$解法，实现会变得非常硬核。

好在最后跑得也快。

78ms, 至今还是cf上最快的解。

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long ll;

int n;
bool bad[128];

inline int __gcd(int a, int b) {
    // return __gcd(b, a % b);
    int temp;
    while (b) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

void test(int x, int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d %d -> %d %d\n", i, j, (int)ceil(i * 1. / x), (int)ceil(j * 1. / x));
        }
    }
}

void init() {
    const char s[] = "24569ABD";
    for (int i = 0; i < 8; ++i) bad[s[i]] = true;
}

char cur[1305], last[1305];
int line, column;

int leading[16] = {4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
int trailing[16] = {4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0};

int count_leading(unsigned int x, bool reverse) {
    if (x >= 'A') x -= 'A', x += 10;
    else x -= '0';
    if (reverse) x = 15 - x;
    return leading[x];
}

int count_trailing(unsigned int x) {
    if (x >= 'A') x -= 'A', x += 10;
    else x -= '0';
    if (x & 1) x = 15 - x;
    return trailing[x];
}

bool is_odd(char x) {
    if (x >= 'A') return (x - 'A') & 1;
    else return (x - '0') & 1;
}

int process_line() {
    int n_4 = n >> 2;
    int gcd;
    int last_cnt;
    bool last_bit;
    switch(cur[0]) {
        case '0': gcd = 4; break;
        case '1': gcd = 3; break;
        case '2': gcd = 1; break;
        case '3': gcd = 2; break;
        case '4': gcd = 1; break;
        case '5': gcd = 1; break;
        case '6': gcd = 1; break;
        case '7': gcd = 1; break;
        case '8': gcd = 1; break;
        case '9': gcd = 1; break;
        case 'A': gcd = 1; break;
        case 'B': gcd = 1; break;
        case 'C': gcd = 2; break;
        case 'D': gcd = 1; break;
        case 'E': gcd = 3; break;
        case 'F': gcd = 4; break;
    }
    if (gcd == 1) return 1;
    switch(cur[0]) {
        case '0': last_cnt = 4, last_bit = 0; break;
        case '1': last_cnt = 1, last_bit = 1; break;
        case '3': last_cnt = 2, last_bit = 1; break;
        case 'C': last_cnt = 2, last_bit = 0; break;
        case 'E': last_cnt = 1, last_bit = 0; break;
        case 'F': last_cnt = 4, last_bit = 1; break;
    }
    int i = 1;
    if (cur[0] == '0' || cur[0] == 'F') {
        for (; i < n_4; ++i) {
            if (cur[i] == cur[i - 1]) {
                gcd += 4;
            } else {
                gcd += count_leading(cur[i], last_bit), last_cnt = count_trailing(cur[i]), last_bit = is_odd(cur[i]);
                ++i;
                break;
            }
        }
    }
    if (i == n_4) {
        if (cur[0] == '0' || cur[0] == 'F') {
            return gcd;
        } else if (cur[0] == '3' || cur[0] == 'C') {
            return 2;
        } else {
            return 1;
        }
    }
    for (; i < n_4 && gcd != 1; ++i) {
        if (cur[i] == '0') {
            if (last_bit) {
                gcd = __gcd(gcd, last_cnt);
                last_bit = 0;
                last_cnt = 4;
            } else {
                last_cnt += 4;
            }
        } else if (cur[i] == 'F') {
            if (!last_bit) {
                gcd = __gcd(gcd, last_cnt);
                last_bit = 1;
                last_cnt = 4;
            } else {
                last_cnt += 4;
            }
        } else {
            last_cnt += count_leading(cur[i], last_bit);
            gcd = __gcd(last_cnt, gcd);
            last_bit = is_odd(cur[i]);
            last_cnt = count_trailing(cur[i]);
        }
        if (bad[cur[i]]) gcd = 1;
    }
    gcd = __gcd(last_cnt, gcd);
    // printf("gcd: %d\n", gcd);
    return gcd;
}

int main() {
    scanf("%d", &n);
    int cnt = 1;
    scanf("%s", cur);
    int line = process_line();
    memcpy(last, cur, sizeof last);
    bool first_col = true;
    for (int i = 1; i < n && line != 1; ++i) {
        scanf("%s", cur);
        if (strcmp(cur, last) == 0) {
            ++cnt;
        } else {
            line = __gcd(line, process_line());
            memcpy(last, cur, sizeof last);
            if (first_col) column = cnt, first_col = false;
            else column = __gcd(column, cnt);
            cnt = 1;
        }
    }
    if (first_col) column = cnt;
    // printf("%d %d\n", line, column);
    printf("%d\n", __gcd(line, column));
}
```

---

## 作者：ciwomuli (赞：0)

这题据说可以用前缀和做  
我的思想是用bitset  
用bitset判断每一行的相应位置是否一样  
让后再暴力判每一列是否一样  
让后就A了
```
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#define LL long long
#define P pair<int,int>
using namespace std;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = getchar();
    t = 0;
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        t = t * 10 + c - 48, c = getchar();
    if (f)
        t = -t;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
const int maxn = 5220;
bitset<maxn> b[maxn];
int main(){
    int n;
    read(n);
    for(int i=1;i<=n;i++){
        for (int j = 1; j < n;j+=4){
            char ch=getchar();
            while(isspace(ch))
                ch = getchar();
            if(ch=='8' || ch=='9' || ch=='A' || ch=='B' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j] = 1;
            if(ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='C' || ch=='D' || ch=='E' || ch=='F')
                b[i][j+1] = 1;
            if(ch=='2' || ch=='3' || ch=='6' || ch=='7' || ch=='A' || ch=='B' || ch=='E' || ch=='F')
                b[i][j+2] = 1;
            if(ch=='1' || ch=='3' || ch=='5' || ch=='7' || ch=='9' || ch=='B' || ch=='D' || ch=='F')
                b[i][j+3] = 1;
        }
    }
    for (int ans = n; ans >= 2;ans--){
        if (n % ans != 0)
            continue;
        bool ok=true;
        for (int i = 1; i < n;i+=ans){
            for (int j = i+1; j < i + ans;j++){
                ok &= (b[j] == b[i]);
            }
            if(!ok)
                break;
            for (int j = 1; j < n;j+=ans){
                for (int k = j+1; k < j + ans;k++)
                    ok &= (b[i][k] == b[i][k - 1]);
                if(!ok)
                    break;
            }
        }
        if(ok){
            cout << ans << endl;
            return 0;
        }
    }
    puts("1");
}
```

---

