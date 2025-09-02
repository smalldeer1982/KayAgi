# [GCJ 2021 #2] Matrygons

## 题目描述

[套娃](https://en.wikipedia.org/wiki/Matryoshka_doll)是一种起源于一个多世纪前俄罗斯的玩偶。它们的显著特征是由一组大小各异的玩偶组成，较小的玩偶可以完美地嵌套在较大的玩偶内部。

在本问题中，我们研究**套娃多边形**，这是一组遵循类似嵌套规则的正则凸多边形。一个套娃多边形由一组面积为正的正则凸多边形 $p_1, p_2, \ldots, p_k$ 组成，且满足对于所有 $i$，$p_{i+1}$ 的顶点是 $p_i$ 顶点的**真子集**（即 $p_{i+1}$ 的边数严格少于 $p_i$）。

例如，下图展示了两个套娃多边形。第一个包含 3 个正则凸多边形：一个正二十四边形（24 条边）、一个正六边形（6 条边）和一个等边三角形（3 条边）。第二个包含 2 个正则凸多边形：一个正二十二边形（22 条边）和一个正十一边形（11 条边）。这两个套娃多边形的总边数均为 33。

![](https://cdn.luogu.com.cn/upload/image_hosting/3kcm72a3.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/pf69u83n.png)

给定总边数 $\mathbf{N}$，计算在总边数恰好为 $\mathbf{N}$ 的套娃多边形中，最多可以包含多少个多边形。

## 说明/提示

**样例解释**

问题描述中的第一个套娃多边形是样例 #1 的最优解。

在样例 #2 中，我们可以将一个正五边形（5 条边）嵌套在正十边形（10 条边）内，得到包含 2 个多边形的套娃多边形。

在样例 #3 中，无法创建包含多个正则多边形的套娃多边形，因此唯一选择是使用单个正四十一边形（41 条边）。

**限制条件**

- $1 \leq \mathbf{T} \leq 100$。

**测试集 1（7 分，可见判定）**

- 时间限制：20 秒。
- $3 \leq \mathbf{N} \leq 1000$。

**测试集 2（13 分，可见判定）**

- 时间限制：40 秒。
- $3 \leq \mathbf{N} \leq 10^6$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
33
15
41```

### 输出

```
Case #1: 3
Case #2: 2
Case #3: 1```

# 题解

## 作者：RainySoul (赞：0)

### 转化题意

构造序列 $a_1,a_2,\cdots,a_n$ 满足 $\sum_{i=1}^{n}a_i=N$ 且对于任意 $a_i(i\in \left [ 2,n\right ])$ 有 $a_{i-1} \mid a_i$。

在此基础上最大化 $n$。

### 咋做？

显然对于任意 $a_i(i\in \left [ 1,n\right ])$ 有 $a_1 \mid a_i$。

把整个序列除以 $a_1$ 可以得到新的序列 $1,e_2,e_3,\cdots,e_n$。发现把最前面的 $1$ 拿掉之后是一个和前面几乎一样的问题，那么对于任意一个满足和为 $x$ 的合法序列，只要将其变为原来的 $k$ 倍 ($k>1$) 再在最前方添上一个 $1$ 你就得到了一个和为 $k\times x+1$ 的合法序列。

于是可以 $\text{dp}$。设计状态 $dp_i$ 表示和为 $i$ 的序列最多可以包含多少个元素，枚举 $k$ 转移：

$$dp_{k\times x +1}=\max(dp_{k \times x +1},dp_{x}+1)$$

注意由于是个多边形，$a_1$ 是不能小于 $3$ 的。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000010;
int T,ans,dp[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    for(int i=0;i<=N-10;i++)dp[i]=1;
    for(int i=1;i<=N-10;i++)
        for(int k=2;k*i+1<=N-10;k++)
            dp[k*i+1]=max(dp[k*i+1],dp[i]+1);
    int cnt=0;
    while(T--){
        int n,ans=1;
        cin>>n;
        for(int i=3;i<=n;i++)
            if(n%i==0)ans=max(ans,dp[n/i]);
        cout<<"Case #"<<++cnt<<": "<<ans<<'\n';
    }
    return 0;
}
```

---

