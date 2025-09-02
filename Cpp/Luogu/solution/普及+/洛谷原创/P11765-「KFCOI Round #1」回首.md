# 「KFCOI Round #1」回首

## 题目背景

控制住不爱一个人很难，因为爱是自由意识的沉沦。

其实从始至终，只要你回首，他就永远都陪伴在你身后。

## 题目描述

你一共有 $n$ 条重要的回忆，每条回忆有一个重要系数 $k_i$，并且这 $n$ 条回忆彼此之间有 $m$ 个前后关系。

每一条关系 $u,v(1\le u,v\le n)$ 表示 $u$ 发生的时间**恰好**在 $v$ 前。

可能是因为时间过久导致你的记忆错乱，在时间线中可能会出现环。

一开始，所有点的重要度均为 $0$，一共你会进行 $T$ 次回想操作。

若当前正在进行第 $t$ 次操作：

* 操作前，对于一条回忆 $x_i$，它的重要度会乘上重要系数 $k_i$。

* 操作中，对于一条回忆 $x_i$，如果有**恰好**发生在回忆 $x_i$ 前的回忆 $y_i$，那么将回忆 $x_i$ 的重要度增加 $y_i$ 在本次乘上重要系数 $k_i$ **之前**的重要度。否则回忆 $x_i$ 的重要度增加 $t$。

当然，为了防止一条回忆过于重要，输出每条回忆的重要度对 $998244353$ 取余的结果。

****

形式化题意：

给定一个 $n$ 个节点，$m$ 条边的有向图，并保证不会出现重边。初始所有点的点权都为 $0$。

一共将进行 $T$ 次操作。

对于第 $t$ 次操作，首先将所有点的点权乘上一个给定的值 $k_i$。

接下来，对于一个点 $x_i$，如果有连向它的点 $y_i$，那么将 $x_i$ 的权值加上 $y_i$ 在本次乘上 $k_i$ 之前的权值。否则如果没有连向它的点，$x_i$ 的权值加上 $t$。

输出的所有点的权值对 $998244353$ 取余的结果。

## 说明/提示

样例解释 1：

![](https://cdn.luogu.com.cn/upload/image_hosting/9h5jwi1l.png)

第一次操作时，所有的点重要度为 $0$。

乘上重要系数后依旧为 $0$。

第一个点的重要度加上当前正在进行的回想操作次数 $1$。

其余点均加上 $0$。

第一次操作后，所有点的重要度分别为 `1,0,0,0,0`。

类似的，第二次操作后，所有点的重要度分别为 `3,1,0,1,0`。

第三次操作后，所有点的重要度分别为 `6,5,1,8,1`。

****

### 数据范围

**本题采用捆绑测试**。

- Subtask 1（20 points）：$1\le n \le 10$，$1\le T \le 10$。
- Subtask 2（20 points）：$1\le T\le 10^5$。
- Subtask 3（60 points）：无特殊限制。

对于所有测试数据，$1\le n\le100$，$1\le m\le300$，$1\le T\le10^{18}$，$1\le k_i\le10^9$，$1\le x_i,y_i\le n$。



## 样例 #1

### 输入

```
5 5 3
1 2 3 4 5
1 2
2 3
1 4
2 4
4 5```

### 输出

```
6 5 1 8 1```

# 题解

## 作者：koukilee (赞：2)

> 这一次，我还赌你赢。

这里是出题人的题解。

## 题目大意

给定一张 $n$ 个节点的图。

一共进行 $T$ 次操作。

每个节点的权值一开始都会乘上 $k_i$，紧接着如果有连向它的点，就加上那些点的权值，否则加上当前进行的操作次数。

## 题目解析

### **对于 $40\%$ 的数据**：

直接模拟即可，没有任何难度，注意取模的问题，注意这些操作的先后问题。

### **对于 $100\%$ 的数据**：

注意到 $T \le 10^{18}$，此时明显不能暴力模拟。

但是，由于每一次图的形态不会改变，并且每一次每一个点会从哪些点加来权值是固定的。

所以考虑一个并不难的矩阵快速幂。

先预处理出**每次操作前**的转移矩阵，如下：

$$\begin{matrix} & a_{1_t}&a_{2_t}&a_{3_t}&\dots&i&1\\a_{1_{t - 1}}&k_1&0&0&\dots&0&0\\
a_{2_{t - 1}}&0&k_2&0&\dots&0&0&\\
a_{3_{t - 1}}&0&0&k_3&\dots&0&0\\\dots&0&0&0&\dots&0&0\\
i-1&0&0&0&\dots&1&1\\1&0&0&0&\dots&0&1\\
\end{matrix}$$

接下来，如果 $a,b$ 之间有一条有向边，则将矩阵的 $(a,b)$ 赋值为 $1$。

如果点 $i$ 没有入点，则将 $(n + 1, i),(n + 2,i)$ 赋值为 $1$。

最后直接做矩阵快速幂即可。

代码如下：

```c++
  read (n, m, T);

	for (i32 i = 1; i <= n; i++)
		read (Base.mat[i][i]);
	
	for (i32 i = 1; i <= m; i++){
		i64 x, y; read (x, y);
		G[x].push_back (y);
	}
	
	for (i32 i = 1; i <= n; i++) {
		for (auto it : G[i]) 
			in[it]++, Base.mat[i][it] = 1;
	}
	for (i32 i = 1; i <= n; i++)
		if (!in[i])
			Base.mat[n + 1][i] = Base.mat[n + 2][i] = 1;
	Base.mat[n + 1][n + 1] = Base.mat[n + 2][n + 1] = 1;
	Base.mat[n + 2][n + 2] = 1;
	
	F.mat[1][n + 2] = 1;
	
	F = fpow (F, Base, T);
	
	for (i32 i = 1; i <= n; i++)
		print (F.mat[1][i]), putchar (' ');
```

---

## 作者：wurang (赞：0)

这道题目一看数据范围 $n \le 100，1 \le T \le 10^{18}$，就能想到使用矩阵快速幂求解。

这个矩阵不仅要存储每两个点之间的转移，还要记录第 $t$ 次操作中的 $t$，由于每次 $t$ 会加一，所以还要多一维记录常量 $1$。

记本轮为第 $t$ 次，第 $i$ 次后第 $j$ 个点的重要系数为 $dp_{i,j}$，$e_{i,j}$ 表示是否有一条从 $i$ 到 $j$ 的边，$f_i$ 表示第 $i$ 个点的入读是否为 $0$，容易得到转移矩阵。

$$
\begin{bmatrix}
dp_{t-1,1} & dp_{t-1,2} & \cdots & dp_{t-1,100} & t & 1
\end{bmatrix}

\begin{bmatrix}
e_{1,1} & e_{1,2} & \cdots & e_{1,100} & 0 & 0 \\ 
e_{2,1} & e_{2,2} & \cdots & e_{2,100} & 0 & 0 \\
\vdots & \vdots & \ddots & \vdots & \vdots & \vdots\\
e_{100,1} & e_{100,2} & \cdots & e_{100,100} & 0 & 0 \\
f_1 & f_2 & \cdots & f_{100} & 1 & 0
0 & 0 \cdots & 0 & 1 & 1
\end{bmatrix}
=
\begin{bmatrix}
dp_{t,1} & dp_{t,2} & \cdots & dp_{t,100} & t+1 & 1
\end{bmatrix}
$$

初始矩阵为：
$$
\begin{bmatrix}
0 & 0 & \cdots & 0 & 1 & 1
\end{bmatrix}
$$

最后用矩阵快速幂计算即可。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}


const int mod = 998244353, sz = 105;

struct Matrix
{
    int a[sz][sz];
    Matrix()
    {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                a[i][j] = 0;
    }

    Matrix operator*(const Matrix &T) const
    {
        Matrix res;
        int r;
        for (int i = 0; i < sz; ++i)
            for (int k = 0; k < sz; ++k)
            {
                r = a[i][k];
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] = (res.a[i][j] + T.a[k][j] * r) % mod;
            }
        return res;
    }

    Matrix operator^(int x) const
    {
        Matrix res, bas;
        for (int i = 0; i < sz; ++i)
            res.a[i][i] = 1;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                bas.a[i][j] = a[i][j] % mod;
        while (x)
        {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

}ans, mat;

int n, m, t;
int k, u, v;

bool f[105];

signed main()
{
    cin >> n >> m >> t;
    for(int i = 1; i <= n; i++)
        cin >> k, mat.a[i][i] = k;
    for(int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        mat.a[u][v] = 1;
        f[v] = 1;
    }
    for(int i = 1; i <= n; i++)
        if(!f[i]) mat.a[101][i] = 1;
    mat.a[101][101] = mat.a[102][101] = 1;
    mat.a[102][102] = 1;
    ans.a[1][101] = 1, ans.a[1][102] = 1;
    ans = ans * (mat ^ t);
    for(int i = 1; i <= n; i++)
        cout << ans.a[1][i] << " ";
    return 0;
}
```

---

