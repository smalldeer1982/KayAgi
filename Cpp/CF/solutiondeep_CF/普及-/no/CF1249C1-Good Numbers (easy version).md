# 题目信息

# Good Numbers (easy version)

## 题目描述

简单难度与困难难度的唯一差别是$n$的取值范围

现在给出一个定义：Good Number（下文以好数代替），好数是指可以变成$3$的**不同**次幂的加和的数

例如：

$30$ 是好数 $30=3^3+3^1$

$1$ 是好数 $1=3^0$

$12$ 是好数 $12=3^2+3^1$

$2$ 不是好数，因为$2=3^0+3^0$，不符合不同次幂的条件

$19$ 不是好数，例如$19=3^2+3^2+3^0=3^2+3^1+3^1+3^1+3^0$，不符合不同次幂的条件

$20$不是好数，同理不符合不同次幂的条件，无法把$20$分为$3$的不同次幂的加和

现在给你一些正整数$n$，对于每个$n$请你给出一个最小的$m$满足：①$m$是好数 ②$n≤m$

## 样例 #1

### 输入

```
7
1
2
6
13
14
3620
10000
```

### 输出

```
1
3
9
13
27
6561
19683
```

# AI分析结果

### 题目内容
# Good Numbers (easy version)

## 题目描述
简单难度与困难难度的唯一差别是$n$的取值范围。
现在给出一个定义：Good Number（下文以好数代替），好数是指可以变成$3$的**不同**次幂的加和的数。
例如：
$30$是好数，$30 = 3^3 + 3^1$；
$1$是好数，$1 = 3^0$；
$12$是好数，$12 = 3^2 + 3^1$；
$2$不是好数，因为$2 = 3^0 + 3^0$，不符合不同次幂的条件；
$19$不是好数，例如$19 = 3^2 + 3^2 + 3^0 = 3^2 + 3^1 + 3^1 + 3^1 + 3^0$，不符合不同次幂的条件；
$20$不是好数，同理不符合不同次幂的条件，无法把$20$分为$3$的不同次幂的加和。
现在给你一些正整数$n$，对于每个$n$请你给出一个最小的$m$满足：①$m$是好数；②$n \leq m$。

## 样例 #1
### 输入
```
7
1
2
6
13
14
3620
10000
```
### 输出
```
1
3
9
13
27
6561
19683
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕如何高效找出不小于给定正整数$n$的最小好数展开。部分题解利用三进制特性，如将$n$转换为三进制后通过模拟进位或直接判断每一位来确定好数；部分通过状态压缩结合二分查找，用二进制数表示好数的构成；还有的采用01背包思想或暴力枚举等方法。不同题解在时间复杂度、空间复杂度及代码实现的难易程度上各有差异。

### 所选的题解
- **作者：Priori_Incantatem (赞：3)  星级：4星**
    - **关键亮点**：利用状态压缩将好数用二进制数表示，结合二分查找快速定位大于等于$n$的最小好数，时间复杂度为$\operatorname{O}((\log_2n)^2)$，效率较高。
    - **重点代码**：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const long long Maxn = 50;
const long long n = 39;
long long a[Maxn], m;
inline long long read() {
    long long s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-')w = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9')s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s * w;
}
long long get(long long x) { // 计算二进制数x对应的好数
    long long ret = 0;
    for (long long i = 0; i <= n; ++i)
        if ((x >> i) & 1)ret += a[i];
    return ret;
}
int main() {
    //	freopen("in.txt","r",stdin);
    a[0] = 1;
    for (long long i = 1; i <= n; ++i)
        a[i] = a[i - 1] * 3;
    long long T = read();
    while (T--) {
        m = read();
        long long l = 1, r = (1ll << n) - 1;
        while (l < r) { // 二分
            long long mid = (l + r) >> 1;
            long long tmp = get(mid);
            if (tmp >= m)r = mid;
            else l = mid + 1;
        }
        printf("%lld\n", get(l));
    }
    return 0;
}
```
    - **核心实现思想**：先预处理出$3$的各次幂存于数组`a`，通过`get`函数将二进制数转换为对应的好数。每次读入$m$后，在二进制数表示的好数范围内二分查找，找到满足条件的最小好数。
- **作者：Karry5307 (赞：2)  星级：4星**
    - **关键亮点**：将问题转化为三进制表示下的贪心问题，通过模拟进位操作，每次将三进制表示中$2$所处位置的最高位及低位处理，直到三进制表示中无$2$，时间复杂度$O(q\log n)$，思路清晰，实现相对简单。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN = 2e5 + 51;
ll test, tot, kk, ptr, res;
ll num[MAXN];
inline ll read() {
    register ll num = 0, neg = 1;
    register char ch = getchar();
    while (!isdigit(ch) && ch!= '-') {
        ch = getchar();
    }
    if (ch == '-') {
        neg = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        num = (num << 3) + (num << 1) + (ch - '0');
        ch = getchar();
    }
    return num * neg;
}
inline void solve() {
    kk = read();
    memset(num, 0, sizeof(num)), tot = 0, res = 0;
    while (kk) {
        num[++tot] = kk % 3, kk /= 3;
    }
    for (register int i = tot; i; i--) {
        if (num[i] == 2) {
            num[i] = 0, ptr = i + 1;
            for (register int j = i - 1; j; j--) {
                num[j] = 0;
            }
            while (num[ptr] == 1) {
                num[ptr++] = 0;
            }
            num[ptr] = 1, tot = max(tot, ptr);
        }
    }
    for (register int i = tot; i; i--) {
        res = (res * 3) + num[i];
    }
    printf("%lld\n", res);
}
int main() {
    test = read();
    for (register int i = 0; i < test; i++) {
        solve();
    }
}
```
    - **核心实现思想**：先将读入的数`kk`转换为三进制存于数组`num`，从低位到高位遍历`num`，遇到$2$时，将该位及低位清$0$，并对高位进行进位处理，最后将处理后的三进制数转换回十进制输出。
- **作者：minVan (赞：1)  星级：4星**
    - **关键亮点**：通过计算$3$的幂的前缀和，从大到小判断是否选择$3$的某次方作为结果的一部分，利用递归和暴力的思想解决问题，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e18;
long long n, ans, sum[105], a[105];
long long solve(long long x) {
    long long ans = 0;
    for (int i = 38; i >= 1; i--) {
        if (ans + sum[i - 1] >= x) {
            continue;
        }
        else {
            ans += a[i];
        }
    }
    if (ans < x) {
        ans += 1;
    }
    return ans;
}
int main() {
    sum[0] = 1;
    a[0] = 1;
    long long cnt = 3;
    for (int i = 1; i <= 100 && sum[i - 1] <= INF; i++) {
        sum[i] = sum[i - 1] + cnt;
        a[i] = cnt;
        cnt *= 3;
    }
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << solve(n) << "\n";
    }
    return 0;
}
```
    - **核心实现思想**：先预处理出$3$的各次幂`a`及其前缀和`sum`，在`solve`函数中，从大到小遍历$3$的幂，若当前已选数字之和加上剩余前缀和仍大于等于目标值`x`，则不选当前幂，否则选择，最后若结果小于`x`，则加上$1$。

### 最优关键思路或技巧
利用三进制特性或状态压缩结合二分查找是较为高效的方法。将问题转化为三进制表示下的处理，能直观地根据好数定义进行操作；状态压缩结合二分查找则充分利用好数的二进制表示特性，通过二分快速定位结果，在时间复杂度上有较好表现。

### 可拓展之处
同类型题常围绕特定进制下数字的组合问题，类似算法套路包括对数字进行进制转换后根据条件进行处理，或利用状态压缩表示数字组合情况，结合二分查找等优化手段提高效率。

### 洛谷相似题目推荐
- [P1018 乘积最大](https://www.luogu.com.cn/problem/P1018)
- [P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G](https://www.luogu.com.cn/problem/P1090)
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)

### 个人心得摘录与总结
无。 

---
处理用时：89.07秒