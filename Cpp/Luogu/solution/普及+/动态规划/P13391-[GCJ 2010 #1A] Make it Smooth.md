# [GCJ 2010 #1A] Make it Smooth

## 题目描述

你有一个长度为 $N$ 的一维像素数组。每个像素都有一个取值，表示为 $0$ 到 $255$ 之间的一个数字（包含 $0$ 和 $255$）。两个像素之间的距离定义为它们数值的绝对差。

你可以进行以下任意次数的操作：

1. 以代价 $D$，删除任意一个像素，此时它原本的相邻像素会变为新的相邻像素。
2. 以代价 $I$，在任意位置插入一个任意值的像素——可以插在任意两个像素之间，也可以插在第一个像素之前或最后一个像素之后。
3. 你可以修改任意一个像素的值，代价为该像素的新旧值的绝对差。

如果数组中任意相邻像素的距离都不超过 $M$，则称该数组是“平滑”的。请你求出将输入数组变为平滑数组所需的最小总代价。

注意：空数组（即不包含任何像素的数组）也被认为是平滑的。

## 说明/提示

**样例解释**

在第 1 组中，将 $7$ 降为 $3$ 的代价为 $4$，这是最便宜的方案。在第 2 组中，删除操作非常昂贵；插入元素使最终数组变为 $[1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 50, 45, 40, 35, 30, 25, 20, 15, 10, 7]$ 更便宜。

**数据范围**

- 输入中的所有数字均为整数。
- $1 \leqslant T \leqslant 100$
- $0 \leqslant D, I, M, a_i \leqslant 255$

**小数据范围（12 分，测试点 1 - 可见）**

- $1 \leqslant N \leqslant 3$。

**大数据范围（24 分，测试点 2 - 隐藏）**

- $1 \leqslant N \leqslant 100$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
6 6 2 3
1 7 5
100 1 5 3
1 50 7```

### 输出

```
Case #1: 4
Case #2: 17```

# 题解

## 作者：luuia (赞：1)

### Solution

看到这种一堆操作求最小代价的题，首先考虑 dp。

我们设 $f_{i,j}$ 表示考虑到前 $i$ 个元素，最后一个保留的元素是 $j$ 的最小代价，如果目前还没有保留任何像素，我们认为 $j=256$。那么初始化是简单的，有：$f_{0,256} = 0$，$f_{0,i} = \infty\,(0 \le i \le 255)$。这里的数组下标从 $0$ 开始。

从 $i$ 转移到 $i+1$ 的时候，我们按照每个操作分别考虑：

- 首先我们可以直接删掉第 $i+1$ 个元素，于是有 $f_{i+1,j} \gets \min(f_{i+1,j},f_{i,j}+x)$。

- 保留第 $i+1$ 个元素（即 $a_i$），并将它修改为新的值 $k$，这有两部分代价，第一部分是直接修改的 $|a_{i}-k|$，还有一部分是给 $k$ 前面插入若干元素使得序列依然合法，这部分的代价为：

$$
f(j,k)=
\begin{cases}
0, &j=256 \lor (0\le j\le255 \land |j-k|\le M),\\
\left\lfloor\dfrac{|j-k|-1}{m}\right\rfloor \times y, & 0\le j\le255 \land |j-k|>m \land m>0,\\
\infty, & m=0\land|j-k|>0.
\end{cases}
$$

如果 $j$ 是 $256$，代表前面还没有元素，那么就没必要插入元素，代价为 $0$；如果 $j$ 和 $k$ 的差距已经 $\le m$，也没必要插入；如果 $m=0$，那么怎么插都没办法让序列合法，我们视为代价 $\infty$；否则我们从 $j$ 开始，每两个数的间隔都是 $m$ 这样的插下去，最后代价如上式所示，那么这部分的转移式子为，枚举 $k \in [0,255]$：

$$f_{i+1,k}\gets \min(f_{i+1,k},f_{i,j} + |a_i-k| + f(j,k))$$

那么这道题完整的递推式子为：

$$f_{i+1,j} \gets \min(f_{i+1,j},f_{i,j}+x) \qquad j \in [0,256]$$

$$f_{i+1,k}\gets \min_{0 \le j \le 256}(f_{i+1,k},f_{i,j} + |a_i-k| + f(j,k)) \qquad k \in [0,255]$$

直接转移，时间复杂度 $O(nV^2)$。

### Code

代码直接问 o4 就有了，放一下我的：

```cpp
/**
 *    author: luuia
 *    created: 2025.07.26 00:19:37
**/
#include<bits/stdc++.h>
using ll = long long;
#define For(i,j,k) for(int i = j;i <= k;i++)
#define Rep(i,j,k) for(int i = j;i >= k;i--)
using namespace std;
template<typename T> bool _min(T &a,T b){return a > b ? a = b,1 : 0;}ll ct;
void sol(){ll n,m,d,e;cin >> d >> e >> m >> n;vector<ll> a(n);for(auto &x : a) cin >> x;
    vector<vector<ll>> f(n + 1,vector<ll>(257,1e18));f[0][256] = 0;
    For(i,0,n - 1) For(j,0,256){_min(f[i + 1][j],f[i][j] + d);
        For(k,0,255) _min(f[i + 1][k],f[i][j] + abs(a[i] - k) + (j == 256 ? 0 : 
            abs(j - k) <= m ? 0 : !m ? (ll)1e18 : (abs(j - k) - 1) / m * e));
    }cout << "Case #" << ++ct << ": " << *min_element(f[n].begin(),f[n].end()) << "\n";
}int main(){
    // freopen("input.in","r",stdin);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    ll T;cin >> T;while(T--) sol();return 0;
}
```

---

