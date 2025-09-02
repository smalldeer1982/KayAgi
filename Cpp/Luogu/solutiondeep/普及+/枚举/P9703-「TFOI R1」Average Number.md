# 题目信息

# 「TFOI R1」Average Number

## 题目背景

**题目背景与题意无关，可直接阅读题目描述。**

有一种人叫做「别人家的妹妹」，小 A 对此感触颇深。

小 A 的妹妹——小 L——经常把小 A 的藏书偷走看，小 A 对此很是头疼。

这一次，强迫症小 A 正在收拾他的藏书，小 L 趁小 A 不注意偷走了一本。

「还给我。」

『不给。不过。。。如果你能猜出我手上的书的编号，我就还给你。』

小 A 为了方便拿取和整理他的藏书，特意给每本书从一开始编了号。

「开玩笑，我的书这么多，我怎么猜？」

『嗯。这样吧，我告诉你剩下的那堆书的编号平均值。怎么样，这个提示够了吧。』

「。。。」

小 A 的藏书多到他都不知道有多少本，但是作为一个合格的 OIer，小 A 借助计算机成功算出了答案。只不过，他想要以这个问题来考验你一下。

## 题目描述

你知道 $\dfrac{\left(\sum\limits^{n}_ {i = 1}i \right) - m}{n - 1}$ 的值，其中 $m \in [1, n]$，$n$ 和 $m$ 均为正整数，你要求出 $n$ 和 $m$ 的值，保证有解。

如果有多种可行解，那么请输出 $n$ 较小的那一组解。

多组测试数据。

## 说明/提示

**本题采用捆绑测试**。

- Subtask 1（5 points）：$T \leqslant 10$，$n \leqslant 10^3$。
- Subtask 2（5 points）：$T \leqslant 10^3$，$n \leqslant 10^3$。
- Subtask 3（5 points）：$T \leqslant 10$，$n \leqslant 5\times 10^5$。
- Subtask 4（40 points）：$T \leqslant 10^3$，$n \leqslant 10^{18}$。
- Subtask 5（45 points）：无特殊限制。

对于所有数据，$1 \leqslant m \leqslant n \leqslant 10 ^ {18}$，$n \not = 1$，$1 \leqslant T \leqslant 2 \times 10 ^{5}$，$1 \leqslant a \leqslant 10 ^{18}$，$0 \leqslant b < c \leqslant 10 ^ {18}$ 。

**保证 $\dfrac{b}{c}$ 是最简真分数。特别的，当 $b=0$ 时，$c=1$。**

---

**题目背景（续）**

『你。。你是怎么猜出来？』

小 L 说话之际，看着小 A 的眼神中的惊讶又多了一份崇拜。

「呵，这种难度的问题怎么可能难得到我？」

『啊。既然是这样子的话，那就再来玩一次吧！』

「。。。」

## 样例 #1

### 输入

```
3
2 1 3
3 1 4
5 1 3```

### 输出

```
4 3
5 2
10 7```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是围绕给定的等式 $\frac{\left(\sum\limits^{n}_ {i = 1}i \right) - m}{n - 1}=a+\frac{b}{c}$ 进行式子推导和变形，通过不同的方法来确定 $n$ 和 $m$ 的值。主要方法包括暴力枚举、求解不等式缩小范围、二分查找等。各题解在思路清晰度、代码可读性和优化程度上存在差异。

### 所选题解
- **作者：Super_Cube (赞：7)**：5星
  - 关键亮点：思路清晰，先给出简单暴力枚举思路，再通过求解不等式和巧妙的缩放推导，得到 $n$ 的范围，实现 $O(1)$ 复杂度的解法。
  - 个人心得：提到在重造数据前，随机数据下简单枚举跑得飞快，因为 $i$ 多数情况下等于 $1$，但这种做法复杂度高，会超时，从而引出后续优化。
- **作者：CaoXian (赞：4)**：4星
  - 关键亮点：作为出题人题解，详细推导式子并进行缩放，得到 $n$ 的范围，代码实现完整且有注释，逻辑清晰。
- **作者：回声之歌 (赞：3)**：4星
  - 关键亮点：通过合理设参，求出 $k$ 的解集，进而确定 $n$ 和 $m$ 的值，思路严谨，代码实现简洁。

### 重点代码及核心实现思想
#### Super_Cube 的题解
```cpp
// 缩放得到 n 范围后的代码
for(long long i=1,n,m;;++i){
    n=c*i+1;
    m=(__int128)n*(n+1)/2-(__int128)a*(n-1)-b*i;
    if(m>=1&&m<=n){
        printf("%lld %lld\n",n,m);
        break;
    }
}
// 推导得到 2a - 2 <= n <= 2a + 2 后的代码
for(long long n = max(2 * a - 2, 2LL); n <= 2 * a + 2; ++n) {
    if((n - 1) % c == 0) {
        long long m = n * (n + 1) / 2 - (n - 1) / c * (a * c + b);
        if(m >= 1 && m <= n) {
            printf("%lld %lld\n", n, m);
            break;
        }
    }
}
```
核心思想：先通过简单枚举找到 $n$ 和 $m$，但复杂度高。然后通过缩放得到 $n$ 的范围，在该范围内枚举 $n$，计算 $m$ 并判断其合法性。

#### CaoXian 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar gc
typedef __int128 ll;
#define fu(i, l, r) for(ll i = l; i <= r; ++i)
char gc() {static char ibuf[1 << 20], *p1 = ibuf, *p2 = ibuf; return p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1000010, stdin), p1 == p2) ? -1 : *p1++;}
void read(ll& x) {x = 0; int f = 1; char ch = getchar(); while(ch < '0' || ch > '9') f *= ((ch == '-') ? -1 : 1), ch = getchar(); while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); x *= f;}
ll t, m, a, b, c;
int main() {
    read(t);
    while(t--) {
        read(a), read(b), read(c);
        fu(i, max(2 * a - 2, (ll)2), 2 * a + 1) {
            if((i - 1) % c) continue;
            m = i * (i + 1) / 2 - (i - 1) / c * (a * c + b);
            if(m < 1 || m > i) continue;
            printf("%lld %lld\n", (long long)i, (long long)m);
            break;
        }
    }
    return 0;
}
```
核心思想：通过推导和缩放得到 $2 \times a - 2 \leqslant n \leqslant 2 \times a + 1$ 的范围，在该范围内枚举 $n$，计算 $m$ 并判断其合法性。

#### 回声之歌的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
__int128 read() {
    __int128 x = 0, f = 1;
    char c;
    while ((c = getchar()) < 48 || c > 57);
    do x = (x << 1) + (x << 3) + (c ^ 48);
    while ((c = getchar()) > 47 && c < 58);
    return x * f;
}
void write(__int128 x) {
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
__int128 f(__int128 x, __int128 y) {
    if (x % y) return x / y + 1;
    return x / y;
}
int t;
__int128 a, b, c, k, n, m;
int main() {
    for (cin >> t; t; t--) {
        a = read(), b = read(), c = read();
        k = f(2 * a * c + 2 * b - 3 * c, c * c);
        if (k < 1) k = 1;
        n = c * k + 1;
        m = (n * n + n) / 2 - k * (a * c + b);
        write(n), putchar(' ');
        write(m), putchar('\n');
    }
    return 0;
}
```
核心思想：设 $n = ck + 1$，通过求解不等式得到 $k$ 的取值范围，取最小的 $k$ 计算 $n$ 和 $m$。

### 最优关键思路或技巧
- **式子推导与缩放**：通过对给定等式进行变形和推导，结合 $m$ 的取值范围进行缩放，得到 $n$ 的范围，从而缩小枚举范围，降低时间复杂度。
- **二分查找**：对于一些难以直接确定解的问题，可以通过二分查找来确定解的范围，逐步逼近正确答案。
- **使用 `__int128`**：由于数据范围较大，使用 `__int128` 可以避免数据溢出。

### 可拓展之处
同类型题或类似算法套路：
- 涉及数学公式推导和范围求解的题目，如已知平均数求原数据的问题。
- 利用不等式进行范围缩放的题目，通过对变量的取值范围进行限制，缩小搜索空间。
- 二分查找在数学问题中的应用，对于单调变化的函数或问题，可以使用二分查找来提高效率。

### 推荐洛谷题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1067 [NOIP2009 普及组] 多项式输出
- P1075 [NOIP2012 普及组] 质因数分解

---
处理用时：51.88秒