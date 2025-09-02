# [ICPC 2025 NAC] Popping Balloons

## 题目描述

ICPC 的标志有三种颜色：蓝色、黄色和红色。NAC 志愿者们刚刚充好了大量这三种颜色的气球，并将它们排成一条直线。接下来他们需要按照颜色对气球进行分类，才能分发给参赛者。

不幸的是，由于奥兰多的炎热天气，气球开始随机爆炸：每秒会有一个随机剩余的气球爆炸（志愿者们会从队列中清除爆炸后的残骸）。这也不全是坏事：也许如果 NAC 志愿者们等待足够长的时间，气球就会偶然排好序？请计算在第一次满足以下条件时的期望秒数：所有蓝色气球都位于所有黄色和红色气球之前，且所有黄色气球都位于所有红色气球之前。（即使这些条件是"空洞地"满足的也成立：例如，如果根本没有剩余蓝色气球，那么"所有蓝色气球都在黄色和红色气球之前"这一条件自动成立。）

## 说明/提示

在样例输入 1 中，气球颜色首次正确排序的期望时间是 $\frac{17}{6} = 2 \cdot \frac{1}{6} + 3 \cdot \frac{5}{6}$ 秒：
唯一能在 2 秒后使气球正确排序的情况是前两个爆炸的气球是黄色和红色气球（顺序不限）。这两个气球在蓝色气球之前爆炸的概率是 $\frac{1}{6}$。否则（概率为 $\frac{5}{6}$），气球将在 3 秒后（只剩一个气球时）自动排序。
由于 $6^{-1} \equiv 166\,374\,059 \pmod{p}$，所以答案是 $17 \cdot 166\,374\,059 \equiv 831\,870\,297 \pmod{p}$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
RYBB```

### 输出

```
831870297```

## 样例 #2

### 输入

```
YRBBR```

### 输出

```
598946615```

# 题解

## 作者：sunkuangzheng (赞：1)

第一次排序时间是不好办的，考虑将每一个序列变成排序的过程列出来，给过程中每一个序列贡献 $1$。也即，求所有未排序的子序列出现概率的和就是答案，而子序列的出现概率只与长度有关。正难则反，我们希望对每个长度计算出排好序的子序列的数量。

注意到值域只有 $[0,2]$，可以直接设 $f_{i,j,len}$ 表示前 $i$ 个元素以 $j \in [0,2]$ 结尾形成长度为 $len$ 的有序子序列的概率。直接 DP 复杂度是平方的，套路的考虑分治：对于区间 $[l,r]$，设 $f_{x,y,len}$ 表示左右分别是 $x,y \in [0,2]$ 且长度为 $len$ 的概率，合并左右区间时枚举端点，之后的合并是卷积。

总复杂度 $\mathcal O(v^2n\log^2 n)$，还是可以通过的。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 21.06.2025 20:27:37
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif

#include <algorithm>
#include <array>

#ifdef _MSC_VER
#include <intrin.h>
#endif

// namespace atcoder

#define V vector
#define A array
using ll = long long;
const int N = 5e5+5;
const int W = 3,mod = 998244353;
using namespace std;
using Z = atcoder::modint998244353;
#define T A<A<V<Z>,3>,3>
int n,a[N]; string s;
T solve(int l,int r){
    T dp;
    for(int i = 0;i < W;i ++) for(int j = i;j < W;j ++)
        dp[i][j].resize(r-l+2);
    if(l == r) return dp[a[l]][a[l]][1] = 1,dp;
    int mid = (l + r) / 2;
    T L = solve(l,mid),R = solve(mid+1,r);
    for(int i = 0;i < W;i ++) for(int j = i;j < W;j ++){
        for(int l = 0;l < L[i][j].size();l ++) dp[i][j][l] += L[i][j][l];
        for(int l = 0;l < R[i][j].size();l ++) dp[i][j][l] += R[i][j][l];
    }for(int i = 0;i < W;i ++) for(int p = i;p < W;p ++){
        for(int j = 0;j <= i;j ++) for(int k = p;k < W;k ++){
            V<Z> a = L[j][i],b = R[p][k];
            auto c = atcoder::convolution(a,b);
            for(int l = 0;l < c.size();l ++) dp[j][k][l] += c[l];
        }
    }return dp;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> s,n = s.size(),s = " " + s;
    for(int i = 1;i <= n;i ++) a[i] = (s[i] == 'R' ? 2 : (s[i] == 'Y'));
    auto dp = solve(1,n);
    V<Z> as(n + 1);
    for(int i = 0;i < W;i ++) for(int j = i;j < W;j ++)
        for(int l = 0;l <= n;l ++) as[l] += dp[i][j][l];
    for(int i = 1;i <= n;i ++) cerr << as[i].val() << " \n"[i == n];
    Z C = 1,ans = 0;
    for(int i = 1;i <= n;i ++)
        ans += (C - as[n-i+1]) / C,C = C * (n - i + 1) / i;
    cout << ans.val() << "\n";
}
```

---

