# [CEOI 2021] L-triominoes

## 题目背景

译自 CEOI2021 Day1 T2. [L-triominoes](https://hsin.hr/ceoi/competition/ceoi2021_day1_tasks.pdf)。

## 题目描述

给出一个 $H\times W$ 的矩形，我们称其中 $1\times 1$ 的最小矩形为单元格。这个矩形现在有 $K$ 个单元格遗失了。现在请问能否用形如下图的纸片完全覆盖整个矩形。

![捕获3.PNG](https://cdn.luogu.com.cn/upload/image_hosting/ylltjsyr.png)

我们认为一个矩形能被覆盖，当且仅当其所有未遗失的单元格恰好被纸片覆盖一次且没有纸片超出矩形或覆盖在遗失的单元格上。当然，纸片可以垂直或 $90°$ 旋转。

## 说明/提示

#### 样例解释

对于样例一，如图是一种合法的覆盖：

![捕获4.PNG](https://cdn.luogu.com.cn/upload/image_hosting/xgj9bfbw.png)

对于样例二，你永远无法覆盖 $(1,1)$ 上的单元格。 

![捕获5.PNG](https://cdn.luogu.com.cn/upload/image_hosting/hrrzvyjx.png)

对于样例三，如图是一种合法的覆盖： 

![捕获6.PNG](https://cdn.luogu.com.cn/upload/image_hosting/p5awynm4.png)

#### 子任务

所有测试点均满足 $1\leq W\leq 13$，$2\leq H\leq 10^9$，$0\leq K\leq 250$，$1\leq x_i\leq W$，$1\leq y_i\leq H$。

| 子任务编号 | 分值 |                    约束                     |
| :--------: | :--: | :-----------------------------------------: |
|    $1$     | $10$ | $2\leq W\leq 13$，$2\leq H\leq 10^3$，$K\leq 250$ |
|    $2$     | $7$  | $2\leq W\leq 13$，$2\leq H\leq 10^9$，$K=0$    |
|    $3$     | $11$ |  $2\leq W\leq3$，$2\leq H\leq 10^9$，$K\leq 250$  |
|    $4$     | $17$ | $4\leq W\leq 6$，$2\leq H\leq 10^9$，$K\leq 250$  |
|    $5$     | $35$ | $7\leq W\leq 13$，$2\leq H\leq 10^9$，$K\leq 250$ |
|    $6$     | $20$ | $2\leq W\leq 13$，$2\leq H\leq 10^9$，$K\leq 250$ |

## 样例 #1

### 输入

```
4 3 3
1 1
1 3
4 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
5 2 4
1 2
2 1
5 1
5 2```

### 输出

```
NO```

## 样例 #3

### 输入

```
2 3 0```

### 输出

```
YES```

# 题解

## 作者：Inui_Sana (赞：2)

魔怔题。太不牛了。

下文 $W\to n,H\to m$。

首先考虑 $m\le 10^3$ 怎么做。考虑一个状压（其实本质上是插头）dp：设 $dp_{i,j,S}$ 表示当前前 $i-1$ 行和第 $i$ 行的前 $j$ 个位置已经填完，$S$ 的前 $j$ 位表示 $(i+1,1)$ 到 $(i+1,j)$ 是否被填，后 $n-j$ 位表示 $(i,j+1)$ 到 $(i,n)$ 是否被填。

转移分四种情况讨论。

1. $(i,j+1)$ 为 $1$，转移到 $dp_{i,j+1,T}$。$T$ 是容易处理的，下文也不多解释。
2. $(i+1,j+1)$ 或 $(i+1,j+2)$ 被填，填上一个纸片变成一个正方形，转移到 $dp_{i,j+2,T}$。
3. $(i+1,j+1)$ 和 $(i+1,j+2)$ 都没被填，填上一个有两格在第 $i$ 行的纸片，转移到 $dp_{i,j+2,T}$。
4. $(i+1,j+1),(i+1,j+2),(i+1,j+3)$ 都没填，填上两个纸片拼成 $2\times 3$ 的矩形，转移到 $dp_{i,j+3,T}$。

以上转移还需要判断是否合法，也是容易的，不多讲。

这样就能得到一个 $O(nm2^n)$ 的 dp。

考虑 $m$ 变大怎么办。下文称一个初始有格子被填的行为关键行。一个很自然的想法是用类似矩阵快速幂的方法处理两个关键行之间空的若干行，但是这样复杂度大概至少是 $O((2^n)^3)$，显然难以通过。

然后充分发挥想象力，首先手玩一下，发现除了转移一之外的所有转移，在经过 $6$ 行之后都可以变回原来的状态，加上转移一，感性理解也是类似的。

然后观察（或打表）发现对于一个状态，它能转移到的状态根据行数是指数级增长的。于是大胆猜测：如果两个关键行间距离较远，则删去 $6x$ 行是不影响最后可以到达的状态的，剩下至少 $6$ 行大概就足够转移到所有可行状态。

具体地，考虑两个相邻的关键行是 $x,y$，则令 $y=x+\min(y-x,(y-x-1)\bmod 6+7)$，这样相当于删掉若干行，最多剩下 $12k$ 行，对这些再做上面那个暴力即可。

时间复杂度 $O(nk2^n)$。具体的正确性证明不是很会，可能打表观察是最好的方法，可以参考一下官方题解。

code：

```cpp
int n,m,k,X[M],Y[M],a[17][M],f[17][N],dp[N];
vector<int> g;
map<int,int> id;
void Yorushika(){
	read(n,m,k);
	int s=0;
	rep(i,1,k){
		read(X[i],Y[i]);
		g.eb(Y[i]);
	}
	g.eb(m),g.eb();
	sort(g.begin(),g.end());
	g.erase(unique(g.begin(),g.end()),g.end());
	int lst=0;
	for(int i:g){
		id[i]=id[lst]+min(i-lst,((i-lst-1)%6+13));
		lst=i,m=id[i];
	}
	rep(i,1,k){
		a[X[i]][id[Y[i]]]=1;
		if(Y[i]==1){
			s|=1<<(X[i]-1);
		}
	}
	dp[s]=1;
	const int mx=1<<n;
	cerr<<m<<'\n';
	rep(i,1,m-1){
		mems(f,0);
		rep(S,0,mx-1){
			f[0][S]=dp[S];
		}
		rep(j,0,n-1){
			rep(S,0,mx-1){
				if(!f[j][S]){
					continue;
				}
				int x=S>>j&1,y=S>>(j+1)&1;
				if(j<n-1&&x&&!y&&!a[j+1][i+1]&&!a[j+2][i+1]){
					int T=S|(1<<j)|(1<<(j+1));
					f[j+2][T]|=f[j][S];
				}
				if(j<n-1&&!x&&y&&!a[j+1][i+1]&&!a[j+2][i+1]){
					int T=S|(1<<j)|(1<<(j+1));
					f[j+2][T]|=f[j][S];
				}
				if(j<n-1&&!x&&!y&&!a[j+1][i+1]){
					int T=S|(1<<j)|((a[j+2][i+1])<<(j+1));
					f[j+2][T]|=f[j][S];
				}
				if(j<n-1&&!x&&!y&&!a[j+2][i+1]){
					int T=S|(1<<(j+1))|((a[j+1][i+1])<<j);
					f[j+2][T]|=f[j][S];
				}
				if(j<n-2&&!x&&!y&&!(S>>(j+2)&1)&&!a[j+1][i+1]&&!a[j+2][i+1]&&!a[j+3][i+1]){
					int T=S|(1<<j)|(1<<(j+1))|(1<<(j+2));
					f[j+3][T]|=f[j][S];
				}
				if(x){
					int T=(S^(1<<j))|(a[j+1][i+1]<<j);
					f[j+1][T]|=f[j][S];
				}
			}
		}
		rep(S,0,mx-1){
			dp[S]=f[n][S];
		}
	}
	puts(dp[mx-1]?"YES":"NO");
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

upd：被 hack 了，原因是 `id[i]=id[lst]+min(i-lst,((i-lst-1)%6+7));` 中间留的行数不够。看官方题解似乎是要留 $11$ 行？

---

## 作者：Y204335 (赞：2)

# \[CEOI2021] L-triominoes

一道特殊性质优化 dp 的神秘题。

## 题目大意

有一个 $H\times W$ 的矩形，其中有 $K$ 个格子被挖掉，问能否用 $L$ 形纸片完全覆盖该矩形。

## 题目分析

这种覆盖题的一般解法就是状压 dp，并且发现 $1\le W\le 13$，可以进行状压，先使用 dfs 暴力枚举每种转移（一行每个位置有 $4$ 种可能的放法，还可以不放，直接枚举即可），处理出 dp 的转移图，去重后可以发现总共最多有大约 $1.9\times 10^5$ 种转移，由于 $H$ 的范围过大，无法直接进行 dp。

考虑怎样优化，可以发现 $0\le K\le 250$，范围较小，且 $L$ 形纸片很有规律，如果能找到一种快速转移的方法，快速处理没有挖掉格子的部分，就能解决该问题。

考虑打表找规律，对于每种状态集合进行暴力转移，可以发现所有状态集合都具有循环节，也就是说，若当前行的可能状态的集合为 $A$，在转移若干次后，状态集合会再次变回 $A$（当然也有可能是变回转移过程中的某个状态，但之后一定会循环）。

处理不同的 $W$ 可以发现，当 $W\ne 3$ 时，循环节的长度为 $1$ 或 $3$（准确来说，当 $W\in\left \{ 6,9,12 \right \}$ 时，循环节为 $1$，其他为 $3$）；当 $W=3$ 时，循环节长度为 $1$ 或 $2$，并且最多会在 $9$ 步以内进入循环（关于该性质的讨论见[讨论区](https://www.luogu.com.cn/discuss/983445)）。

发现规律后，这道题就很好处理了，在转移距离大于 $9$ 时，通过将距离模 $2$ 或 $3$（即使当前状态集合循环节为 $1$，也最多多转移 $2$ 次，可以接受），从而实现快速转移。对于挖掉格子的行，直接暴力去掉会重叠的情况，再把挖掉的加上（或到状态中），最后判断能否填满即可。

时间复杂度为 $O(5^WK)$，但由于转移有限制，实际每次转移的上界只有 $1.9\times 10^5$，可以通过。

## 代码

### 打表代码

```cpp
#include <bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
const int N = 8192;
int w, mmax = 0;
vector<int> e[N];
bitset<N> vis[N], a, b, lst[N];
void build(int nw, int a, int b)
{
    if (nw == w + 1) {
        if (vis[a][b])
            return;
        e[a ^ ((1 << w) - 1)].push_back(b);
        vis[a][b] = 1;
        return;
    }
    build(nw + 1, a, b);
    if (nw + 1 <= w && (a & (1 << (nw - 1))) == 0 && (a & (1 << nw)) == 0) {
        if ((b & (1 << (nw - 1))) == 0) {
            build(nw + 1, a | (1 << (nw - 1)) | (1 << nw), b | (1 << (nw - 1)));
        }
        if ((b & (1 << nw)) == 0) {
            build(nw + 1, a | (1 << (nw - 1)) | (1 << nw), b | (1 << nw));
        }
    }
    if (nw + 1 <= w && (b & (1 << (nw - 1))) == 0 && (b & (1 << nw)) == 0) {
        if ((a & (1 << nw)) == 0) {
            build(nw + 1, a | (1 << nw), b | (1 << (nw - 1) | (1 << nw)));
        }
        if ((a & (1 << (nw - 1))) == 0) {
            build(nw + 1, a | (1 << (nw - 1)), b | (1 << (nw - 1) | (1 << nw)));
        }
    }
}
void solve()
{
    for (int i = 0; i < (1 << w); i++) {
        if (!a[i])
            continue;
        for (auto j : e[i]) {
            b[j] = 1;
        }
    }
    a = b;
    b.reset();
}
void check()
{
    for (int i = 1; i < N - 10; i++) {
        lst[i].reset();
    }
    int cnt = 0;
    lst[0] = a;
    while (1) {
        solve();
        cnt++;
        if (cnt >= N)
            break;
        for (int j = 0; j < cnt; j++) {
            for (int p = 0; p < N; p++) {
                if (a[p] != lst[j][p])
                    goto x;
            }
            cout << cnt - j << ' ' << j << endl; // 循环节长度 进入循环的转移次数
            mmax = max(mmax, j);
            return;
        x:;
        }
        lst[cnt] = a;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> w;
    build(1, 0, 0);
    for (int i = 0; i < (1 << w); i++) {
        cout << i << ' ';
        a[i] = 1;
        check();
        for (int j = 0; j < (1 << w); j++) {
            a[j] = 0;
        }
    }
    cout << mmax;
    return 0;
}
```

### AC 代码

```cpp
#include <bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
const int K = 250 + 10, N = 8192 + 10, L = 9;
int w, h, k, cnt, nw;
vector<int> e[N];
bitset<N> vis[N], a, b;
map<int, int> ma;
void build(int nw, int a, int b)
{
    if (nw == w + 1) {
        if (vis[a][b])
            return;
        e[a ^ ((1 << w) - 1)].push_back(b);
        vis[a][b] = 1;
        return;
    }
    build(nw + 1, a, b);
    if (nw + 1 <= w && (a & (1 << (nw - 1))) == 0 && (a & (1 << nw)) == 0) {
        if ((b & (1 << (nw - 1))) == 0) {
            build(nw + 1, a | (1 << (nw - 1)) | (1 << nw), b | (1 << (nw - 1)));
        }
        if ((b & (1 << nw)) == 0) {
            build(nw + 1, a | (1 << (nw - 1)) | (1 << nw), b | (1 << nw));
        }
    }
    if (nw + 1 <= w && (b & (1 << (nw - 1))) == 0 && (b & (1 << nw)) == 0) {
        if ((a & (1 << nw)) == 0) {
            build(nw + 1, a | (1 << nw), b | (1 << (nw - 1) | (1 << nw)));
        }
        if ((a & (1 << (nw - 1))) == 0) {
            build(nw + 1, a | (1 << (nw - 1)), b | (1 << (nw - 1) | (1 << nw)));
        }
    }
}
void solve(int len)
{
    if (w != 3) {
        if (len > L) {
            len = (len - L) % 3 + L;
        }
    } else {
        if (len > L) {
            len = (len - L) % 2 + L;
        }
    }
    while (len--) {
        for (int i = 0; i < (1 << w); i++) {
            if (!a[i])
                continue;
            for (auto j : e[i]) {
                b[j] = 1;
            }
        }
        a = b;
        b.reset();
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> w >> h >> k;
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        ma[y] |= (1 << (x - 1));
    }
    build(1, 0, 0);
    nw = 1;
    a[0] = 1;
    for (auto i : ma) {
        solve(i.fir - nw);
        for (int j = 0; j < (1 << w); j++) {
            if (!a[j])
                continue;
            if ((j & i.sec) == 0) {
                b[j | i.sec] = 1;
            }
        }
        a = b;
        b.reset();
        nw = i.fir;
    }
    solve(h - nw);
    if (a[(1 << w) - 1]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
```

---

