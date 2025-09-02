# Mancala

## 题目描述

考虑以下游戏：

- 准备排成一列的 $N$ 个格子和大量石子。
- 初始时，在第 $i$ 个格子（$1 \leq i \leq N$）中放入 $a_i$ 个石子。
- 玩家可以重复进行以下操作：选择一个恰好有 $i$ 个石子的格子 $i$，将其中的所有石子取出，并在第 $1$ 到第 $i-1$ 个格子中各添加 $1$ 个石子。
- 最终剩余石子的总数即为得分。

对于长度为 $N$ 的数列 $a$，将该游戏进行后可能得到的最小得分记为 $f(a)$。

现在，对于所有长度为 $N$ 且每个元素在 $0$ 到 $K$ 之间的数列 $a$，求 $f(a)$ 的总和。由于答案可能非常大，请对 $1000000007$（即 $10^9+7$）取模。

## 说明/提示

### 约束条件

- $1 \leq N \leq 100$
- $1 \leq K \leq N$

### 样例解释 1

当 $N=2$ 且 $K=2$ 时，共有 $9$ 种可能的数列 $a$，各数列对应的 $f(a)$ 值及操作示例如下：
- $f(\{0,0\})$：$0$（无法操作）
- $f(\{0,1\})$：$1$（无法操作）
- $f(\{0,2\})$：$0$（依次操作格子 $2$ 和格子 $1$）
- $f(\{1,0\})$：$0$（选择格子 $1$）
- $f(\{1,1\})$：$1$（选择格子 $1$）
- $f(\{1,2\})$：$0$（依次操作格子 $1$、格子 $2$、格子 $1$）
- $f(\{2,0\})$：$2$（无法操作）
- $f(\{2,1\})$：$3$（无法操作）
- $f(\{2,2\})$：$3$（选择格子 $2$）

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2 2```

### 输出

```
10```

## 样例 #2

### 输入

```
20 17```

### 输出

```
983853488```

# 题解

## 作者：_huangweiliang_ (赞：2)

#### 前言：
~~感觉难度没有紫吧，因为我在模拟赛场切了耶。~~

#### 题目描述：
有 $n$ 个数，第 $i$ 个数为 $a_{i}$，每次可以选择一个 $i$ 满足 $a_{i}=i$，并将 $a_{i}$ 赋值为 $0$，并将 $\left[1,i \right)$ 的 $a_{i}$ 加 $1$，最后你的得分为剩下的数的和，你希望最后得分越小越好。

给出 $n, k$，你需要求出所有 $a_{i} \in \left[ 0,k \right]$ 的情况下，你的得分总和与 $10^9+7$ 取模。

#### 解题思路 & 代码实现：
我的考场思路是这样的，先思考如果给定 $a$ 序列，如何求答案。

模拟之后发现，如果有 $a_{i}=i$ 的话，则一定会操作 $i$，并且每次一定会选取最前面的 $i$ 进行操作，因为这样一定不会影响其他可行操作位置。

继续思考，发现每个数对答案的具体贡献只和 **后面的总操作数** 有关。

假设 $m_{i}$ 表示 $i$ 到 $n$ 的总操作数，那么可以这么分类讨论：
|  | $a_{i} \le i$  | $a_{i} > i$|
| ------------ | ------------ | ------------ |
| 贡献 | $(m_{i+1}+a_{i}) \bmod i$  |$m_{i+1}+a_{i}$|
| 增加的操作次数  | $(m_{i+1}+a_{i})/i$ | $0$ |

具体解释的话，如果 $a_{i} \le i$ 那么它的贡献一定是在操作一定次数当前位置后剩余的数，反之就无法操作，只能一直加上去。

增加的操作次数也是同理。

那么我们就可以写出暴力代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 110, mod = 1e9 + 7;
int n, k, a[N], ans;
void solve(int id){
    if(id > n){
        for(int i = n, m = 0; i >= 1; i--){
            if(a[i] <= i) ans = (ans + (m + a[i]) % i) % mod;
            else ans = (ans + m + a[i]) % mod;
            if(a[i] <= i) m += (m + a[i]) / i;
        }
        return;
    }
    for(int i = 0; i <= k; i++)
        a[id] = i, solve(id + 1);
}
signed main(){
    // freopen("stone.in", "r", stdin);
    // freopen("stone.out", "w", stdout);
    cin >> n >> k;
    solve(1);
    cout << ans << endl;
    return 0;
}
```

那么我们现在会处理一个序列了，那么可以开始思考正解了。

注意到 $n,k \le 100$，可以发现 **后面的总操作数** 在 $n \times k$ 以内。

那么就可以很自然的设置出两个状态。

$f_{i}$ 表示从后往前考虑到 $i$ 的最小得分总和。

$g_{i,j}$ 表示从后往前考虑到 $i$，操作总数为 $j$ 的方案数。

那么转移具体如下： 
$$
\begin{equation}
    \begin{cases}
    f_{i} = f_{i} + f_{i+1}+ \sum_{m=0}^{k \times n} g_{i+1,m} \times ((m+j) \bmod i) &        &(j \le i) \\
    f_{i} = f_{i} + f_{i+1}+ \sum_{m=0}^{k \times n} g_{i+1,m} \times (m+j) &        &(j > i)\\ 
    \end{cases}
\end{equation}$$

$$\begin{equation}
    \begin{cases}
    g_{i,m + (m + j) / i} = g_{i,m + (m + j) / i} + g_{i + 1,m}&        &(j \le i) \\
	g_{i,m} = g_{i,m} + g_{i + 1,m}&        &(j > i) \\
    \end{cases}
\end{equation}$$

那么正解代码如下：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
const int N = 110, M = 5e4 + 10, mod = 1e9 + 7;
int f[N], g[N][M];
signed main(){
    // freopen("stone.in", "r", stdin);
    // freopen("stone.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    g[n + 1][0] = 1;
    for(int i = n; i >= 1; i--){
        for(int j = 0; j <= k; j++){//a[i]
            for(int m = 0; m <= k * n; m++){//m[i+1]
                if(j <= i) g[i][m + (m + j) / i] = (g[i][m + (m + j) / i] + g[i + 1][m]) % mod;
                else g[i][m] = (g[i][m] + g[i + 1][m]) % mod;
            }
        }
        for(int j = 0; j <= k; j++){
            if(j <= i){
                f[i] = (f[i] + f[i + 1]) % mod;
                for(int m = 0; m <= k * n; m++)
                    f[i] = (f[i] + g[i + 1][m] * ((m + j) % i) % mod) % mod;
            }else{
                f[i] = (f[i] + f[i + 1]) % mod;
                for(int m = 0; m <= k * n; m++)
                    f[i] = (f[i] + g[i + 1][m] * ((m + j) % mod) % mod) % mod;
            }
        }
    }
    cout << f[1] << endl;
    return 0;
}
```
时间复杂度 $O(n^2k^2)$。

---

