# 题目信息

# Mister B and PR Shifts

## 题目描述

Some time ago Mister B detected a strange signal from the space, which he started to study.

After some transformation the signal turned out to be a permutation $ p $ of length $ n $ or its cyclic shift. For the further investigation Mister B need some basis, that's why he decided to choose cyclic shift of this permutation which has the minimum possible deviation.

Let's define the deviation of a permutation $ p $ as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF819B/47275887a8ad3386063ea864423569d3d609b7f9.png).

Find a cyclic shift of permutation $ p $ with minimum possible deviation. If there are multiple solutions, print any of them.

Let's denote id $ k $ ( $ 0<=k&lt;n $ ) of a cyclic shift of permutation $ p $ as the number of right shifts needed to reach this shift, for example:

- $ k=0 $ : shift $ p_{1},p_{2},...\ p_{n} $ ,
- $ k=1 $ : shift $ p_{n},p_{1},...\ p_{n-1} $ ,
- ...,
- $ k=n-1 $ : shift $ p_{2},p_{3},...\ p_{n},p_{1} $ .

## 说明/提示

In the first sample test the given permutation $ p $ is the identity permutation, that's why its deviation equals to $ 0 $ , the shift id equals to $ 0 $ as well.

In the second sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,2,3) $ equals to $ 0 $ , the deviation of the $ 2 $ -nd cyclic shift $ (3,1,2) $ equals to $ 4 $ , the optimal is the $ 1 $ -st cyclic shift.

In the third sample test the deviation of $ p $ equals to $ 4 $ , the deviation of the $ 1 $ -st cyclic shift $ (1,3,2) $ equals to $ 2 $ , the deviation of the $ 2 $ -nd cyclic shift $ (2,1,3) $ also equals to $ 2 $ , so the optimal are both $ 1 $ -st and $ 2 $ -nd cyclic shifts.

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
0 0
```

## 样例 #2

### 输入

```
3
2 3 1
```

### 输出

```
0 1
```

## 样例 #3

### 输入

```
3
3 2 1
```

### 输出

```
2 1
```

# AI分析结果

### 题目内容
# Mister B和PR变换

## 题目描述
不久前，B先生检测到来自太空的一个奇怪信号，他开始对其进行研究。
经过一些变换后，该信号变成了一个长度为$n$的排列$p$或者它的循环移位。为了进一步研究，B先生需要一些基础数据，所以他决定选择这个排列的循环移位中偏差最小的那个。
我们将排列$p$的偏差定义为$\sum_{i = 1}^{n}|p_i - i|$。
找到排列$p$的具有最小可能偏差的循环移位。如果有多个解，输出任意一个。
我们将排列$p$的循环移位的编号$k$（$0 \leq k < n$）定义为达到这个移位所需的右移次数，例如：
- $k = 0$：移位$p_1, p_2, \cdots, p_n$，
- $k = 1$：移位$p_n, p_1, \cdots, p_{n - 1}$，
- $\cdots$，
- $k = n - 1$：移位$p_2, p_3, \cdots, p_n, p_1$。

## 说明/提示
在第一个样例测试中，给定的排列$p$是单位排列，所以它的偏差等于$0$，移位编号也等于$0$。
在第二个样例测试中，$p$的偏差等于$4$，第一个循环移位$(1, 2, 3)$的偏差等于$0$，第二个循环移位$(3, 1, 2)$的偏差等于$4$，最优的是第一个循环移位。
在第三个样例测试中，$p$的偏差等于$4$，第一个循环移位$(1, 3, 2)$的偏差等于$2$，第二个循环移位$(2, 1, 3)$的偏差也等于$2$，所以最优的是第一个和第二个循环移位。

## 样例 #1
### 输入
```
3
1 2 3
```
### 输出
```
0 0
```

## 样例 #2
### 输入
```
3
2 3 1
```
### 输出
```
0 1
```

## 样例 #3
### 输入
```
3
3 2 1
```
### 输出
```
2 1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是避免对每次循环移位都进行$O(n)$时间复杂度的偏差计算，而是通过分析每次移位前后偏差值的变化规律，利用一些数据结构或统计变量来优化计算。不同题解在具体实现上有所差异，有的通过分类讨论并记录相关变量来实现$O(n)$的时间复杂度，有的借助树状数组等数据结构来维护相关信息以优化计算。

### 所选的题解
- **作者：hzoi_liuchang（5星）**
  - **关键亮点**：思路清晰，通过将数列中的数按$p_i - i$的正负分类，记录各类数的个数和贡献，分析每次循环移位时这些变量的变化规律，巧妙处理临界情况，实现了$O(n)$时间复杂度的高效解法，代码简洁明了。
  - **重点代码**：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int maxn = 1e7 + 5;
ll n, Zcnt, Fcnt, Ztot, Ftot;
ll a[maxn], judone[maxn];
int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (ll i = 1; i <= n; i++) {
        if (a[i] <= i) {
            Fcnt++;
            Ftot += (i - a[i]);
        }
        else {
            judone[a[i] - i]++;
            Zcnt++;
            Ztot += (a[i] - i);
        }
    }
    ll ans = Ztot + Ftot, jl = 0;
    for (ll i = 1; i < n; i++) {
        Ztot -= Zcnt;
        Zcnt -= judone[i];
        Ftot += Fcnt;
        Fcnt += judone[i];
        ll x = a[n - i + 1];
        Ftot -= n + 1 - x, --Fcnt;
        if (x > 1) ++judone[x - 1 + i], Ztot += x - 1, ++Zcnt;
        else ++Fcnt;
        if (ans > Ftot + Ztot) ans = Ftot + Ztot, jl = i;
    }
    printf("%lld %lld\n", ans, jl);
    return 0;
}
```
  - **核心实现思想**：预处理时统计$p_i - i$大于0和小于等于0的两类数的相关信息，循环移位时，根据规律更新这些信息，同时处理好边界元素导致的类别变化，从而快速得到每次移位后的偏差值。

- **作者：vanyou（4星）**
  - **关键亮点**：定义$b_i = a_i - i$，通过分析发现每次变化对$b_i$的影响规律，利用树状数组维护$b_i$中小于等于0的数的个数，从而在$O(\log n)$时间内计算出每次循环移位后的偏差值，整体时间复杂度为$O(n\log n)$ ，代码实现巧妙。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[1000010], b[1000010], now, ans, front, N = 1000000, c[3000010], id;

int lowbit(int x) { return x & -x; }

void update(int x, int v) {
    x += N;
    for (int i = x; i <= n + N; i += lowbit(i)) c[i] += v;
}

int sum(int x) {
    x += N;
    int ans = 0;
    for (int i = x; i; i -= lowbit(i)) ans += c[i];
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i] - (i + 1);
        now += abs(b[i]);
        update(b[i], 1);
    }
    ans = now, id = 0;
    for (int i = 1; i < n; i++) {
        front = (front - 1 + n) % n;
        b[front] -= i - 1;
        now -= abs(b[front]);
        update(b[front], -1);
        b[front] += n - 1;
        now += abs(b[front]);
        int x = sum(0);
        update(b[front], 1);
        N++;
        now += x * 2 - n + 1;
        if (ans > now) ans = now, id = i;
    }
    cout << ans << " " << id;
    return 0;
}
```
  - **核心实现思想**：利用树状数组可以快速统计一定范围内元素个数的特点，通过对$b_i$数组的维护和更新，结合每次移位对$b_i$的影响，高效计算每次移位后的偏差值。

- **作者：yzxoi（4星）**
  - **关键亮点**：通过观察移动操作对偏移值的影响规律，大力分类讨论，分别记录$p_i > i$和$p_i \leq i$两种情况的相关信息，利用桶来维护可能出现的状态变化，从而实现$O(n)$时间复杂度的计算，思路清晰，代码简洁。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty, typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define CI Cn int&
#define gc getchar
#define D isdigit(c = gc())
#define pc(c) putchar((c))
#define min(x, y) ((x) < (y)? (x) : (y))
#define max(x, y) ((x) > (y)? (x) : (y))
using namespace std;
namespace Debug {
    Tp I void _debug(Cn char* f, Ty t) { cerr << f << '=' << t << endl; }
    Ts I void _debug(Cn char* f, Ty x, Ar... y) { W (*f!= ',') cerr << *f++; cerr << '=' << x << ","; _debug(f + 1, y...); }
    Tp ostream& operator<<(ostream& os, Cn vector<Ty>& V) { os << "["; for (Cn auto& vv : V) os << vv << ","; os << "]"; return os; }
    #define gdb(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}using namespace Debug;
namespace FastIO {
    Tp I void read(Ty& x) { char c; int f = 1; x = 0; W (!D) f = c ^ '-'? 1 : -1; W (x = (x << 3) + (x << 1) + (c & 15), D); x *= f; }
    Ts I void read(Ty& x, Ar&... y) { read(x), read(y...); }
    Tp I void write(Ty x) { x < 0 && (pc('-'), x = -x, 0), x < 10? (pc(x + '0'), 0) : (write(x / 10), pc(x % 10 + '0'), 0); }
    Tp I void writeln(Cn Ty& x) { write(x), pc('\n'); }
}using namespace FastIO;
Cn int N = 1e6 + 10;
int n, k, a[N], cnt[N << 1], c0, c1;
LL s0, s1, Ans;
int main() {
    RI i; for (read(n), i = 1; i <= n; i++) read(a[i]), a[i] > i? ++cnt[a[i] - i], ++c0, s0 += a[i] - i : (++c1, s1 += i - a[i]);
    Ans = s0 + s1; for (i = 1; i <= n; i++) s0 -= c0, s1 += c1, c0 -= cnt[i], c1 += cnt[i], (--c1, s1 -= (n + 1) - a[n - i + 1]),
        a[n - i + 1] > 1? ++cnt[a[n - i + 1] - 1 + i], ++c0, s0 += a[n - i + 1] - 1 : ++c1, s0 + s1 < Ans && (Ans = s0 + s1, k = i);
    return write(Ans), pc(' '), writeln(k), 0;
}
```
  - **核心实现思想**：预处理时统计不同情况的信息，循环移位时，依据规律更新统计变量，同时处理好末尾元素移动带来的变化，进而快速求出最小偏移值及对应的移位次数。

### 最优关键思路或技巧
1. **分类讨论与变量统计**：将$p_i - i$按正负分类，统计每类数的个数和对偏差值的贡献，利用这些统计信息快速更新每次循环移位后的偏差值，避免重复计算。
2. **利用数据结构优化**：如使用树状数组维护数列中特定范围元素的个数，从而在$O(\log n)$时间内获取相关信息，优化整体时间复杂度。

### 可拓展思路
此类题目属于分析序列变换规律并优化计算的类型。类似算法套路可应用于其他涉及序列元素位置变换且需计算某种累积值的问题。例如，对于一些数组元素循环移动后求最值或满足特定条件的问题，可以尝试分析每次移动对关键值的影响规律，通过统计变量或合适的数据结构来优化计算。

### 推荐洛谷题目
1. **P1990 覆盖墙壁**：涉及对序列状态变化规律的分析，通过递推求解问题，与本题分析循环移位规律有相似之处。
2. **P2141 珠心算测验**：需要对数据进行处理和分析，找出满足特定条件的元素数量，和本题通过统计信息来解决问题的思路类似。
3. **P1006 传纸条**：通过分析路径移动规律，利用动态规划解决问题，和本题分析循环移位对偏差值影响的思维方式有相通之处。 

---
处理用时：90.26秒