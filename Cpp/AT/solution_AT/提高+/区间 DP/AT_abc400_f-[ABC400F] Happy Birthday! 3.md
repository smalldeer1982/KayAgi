# [ABC400F] Happy Birthday! 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc400/tasks/abc400_f

存在一个被沿着半径切割成 $N$ 等分的圆形蛋糕。

各分块按顺时针方向编号为 $1, 2, \ldots, N$。此外，对于满足 $1 \leq i \leq N$ 的整数 $i$，分块 $i$ 也可以被称为分块 $N + i$。

初始时，所有分块的颜色均为颜色 $0$。

你可以执行以下操作任意次数：

- 选择满足 $1 \leq a, b, c \leq N$ 的整数 $a, b, c$。对于每个满足 $0 \leq i < b$ 的整数 $i$，将分块 $a + i$ 的颜色修改为颜色 $c$。此操作需花费 $b + X_c$ 的成本。

请找出使得所有满足 $1 \leq i \leq N$ 的整数 $i$ 对应的分块 $i$ 颜色变为 $C_i$ 时，所需总成本的最小值。

## 说明/提示

### 约束条件

- $1 \leq N \leq 400$
- $1 \leq C_i \leq N$
- $1 \leq X_i \leq 10^9$
- 输入中的所有值均为整数

### 样例解释 1

设分块 $i$ 的颜色为 $A_i$。初始时，$(A_1, A_2, A_3, A_4, A_5, A_6) = (0, 0, 0, 0, 0, 0)$。  
以 $(a, b, c) = (2, 1, 4)$ 执行操作后，$(A_1, A_2, A_3, A_4, A_5, A_6) = (0, 4, 0, 0, 0, 0)$。  
以 $(a, b, c) = (3, 3, 2)$ 执行操作后，$(A_1, A_2, A_3, A_4, A_5, A_6) = (0, 4, 2, 2, 2, 0)$。  
以 $(a, b, c) = (1, 1, 1)$ 执行操作后，$(A_1, A_2, A_3, A_4, A_5, A_6) = (1, 4, 2, 2, 2, 0)$。  
以 $(a, b, c) = (4, 1, 1)$ 执行操作后，$(A_1, A_2, A_3, A_4, A_5, A_6) = (1, 4, 2, 1, 2, 0)$。  
以 $(a, b, c) = (6, 1, 5)$ 执行操作后，$(A_1, A_2, A_3, A_4, A_5, A_6) = (1, 4, 2, 1, 2, 5)$。  
此时总成本为 $(1 + X_4) + (3 + X_2) + (1 + X_1) + (1 + X_1) + (1 + X_5) = (1+4) + (3+2) + (1+1) + (1+1) + (1+6) = 20$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
1 4 2 1 2 5
1 2 3 4 5 6```

### 输出

```
20```

## 样例 #2

### 输入

```
5
1 2 3 4 5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
5000000005```

## 样例 #3

### 输入

```
8
2 3 3 1 2 1 3 1
3 4 1 2 5 3 1 2```

### 输出

```
23```

# 题解

## 作者：wky2011 (赞：20)

显然是一道区间问题，所以考虑区间 dp。（洛谷进阶篇里称为环形 dp）。

定义 $f[l,r]$ 为将 $x[l,r]$ 改为 $c[l,r]$ 的最小改变次数，$g[l,r]$ 为最后一次操作覆盖左端点时的最小改变次数。

之后就是区间 dp 的套路：枚举区间长度和左右端点，根据已知区间合并为大区间。

时间复杂度为 $O(N^3)$。

代码有详细注释。
```
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 405;
int n, c[MAXN], x[MAXN];
long long f[MAXN][MAXN], g[MAXN][MAXN];//f是主DP，g是辅助dp
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c[i]);
		c[n + i] = c[i]; //处理环形
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x[i]); // 颜色
	}
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));// 初始化为极大值
	for (int i = 1; i <= 2 * n + 1; i++) {
		f[i][i] = 0;
		g[i][i] = 0;// 区间长度为0时就不用操作
	}
//普普通通的区间DP模版
	for (int len = 1; len <= 2 * n; len++) {
		for (int l = 1; l <= 2 * n - len + 1; l++) {
			int r = l + len;
			// 枚举分割点，将区间分为[l,j]和[j,r]
			for (int j = l + 1; j < r; j++) {
				f[l][r] = min(f[l][r], f[l][j] + f[j][r]);
				g[l][r] = min(g[l][r], g[l][j] + f[j][r]);//要区最小值
			}//区间DP模版
			//此题重点！！！ 如果区间两端颜色相同，尝试合并操作
			if (c[l] == c[r - 1]) {//颜色相同
				g[l][r] = min(g[l][r], g[l][r - 1]);
				f[l][r] = min(f[l][r], g[l][r] + (r - l) + x[c[l]]); //(r - l)：覆盖区间长度（操作影响的块数）
			}
		}
	}
	long long ans = 114514541881452; //inf
	//枚举所有可能的起点，找到长度为n的最小成本
	for (int i = 1; i <= n; i++) {
		ans = min(ans, f[i][i + n]);
	}
	printf("%lld\n", ans);
	return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc400/submissions/64569669)

---

## 作者：2huk (赞：14)

首先考虑序列。令 $f(l,r)$ 表示将 $[l, r]$ 改为目标状态的最小花费。

考虑 $r$ 这个位置是如何变成目标状态的：

1. 独自操作。即 $f(l,r-1) + X_{C_r}+1 \longrightarrow f(l, r)$。
2. 考虑枚举 $y \in [l, r-1]$ 且 $C_y = C_r$。当 $y$ 这个位置变成目标状态时，我们考虑**扩展**这次操作的区间，使其右端点覆盖到 $r$。然后再操作 $[y+1,r-1]$。即 $f(l,y)+r-y+f(y+1,r-1) \longrightarrow f(l, r)$。因为是扩展，那么 $X_{c_r}$ 的贡献就不用再算一次（已经在 $f(l,y)$ 里算过了），将代价直接加上区间扩展的长度（$r-y$）即可。

然后考虑环。最直接的思路是倍长序列后做上面的区间 DP，然后求 $f(i,i+n-1)$ 的最小值。可以证明破环为链是正确的，即一定存在两个相邻的位置，它们没有被同时操作过。枚举这个位置断开即可。

为什么？如果不存在这个位置，那么每次操作的区间的端点一定被操作过至少两次（除了这次还有另一次）。考虑**最后**一次操作的区间是 $[l, r]$，其中 $r$ 端点还在 $[l', r']$ 这次操作中受到影响（$r \in [l', r']$），那么 $[l',r']$ 这次操作可以完全等价的改为 $[l',r-1]$（或 $[r+1,r']$）。那么这样就构造出了 $r,r+1$ 这两个位置没有被同时操作过。

long long 是一定要开的。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 810;

int n, c[N], x[N];
int f[N][N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) cin >> c[i], c[i + n] = c[i];
	for (int i = 1; i <= n; ++ i ) cin >> x[i];
	
	for (int i = 1; i <= n * 2; ++ i ) {
		f[i][i] = x[c[i]] + 1;
	}
	
	for (int len = 2; len <= 2 * n; ++ len )
		for (int l = 1, r = len; r <= 2 * n; ++ l, ++ r ) {
			f[l][r] = f[l][r - 1] + f[r][r];
			for (int x = l; x < r; ++ x )
				if (c[x] == c[r]) f[l][r] = min(f[l][r], f[l][x] + r - x + f[x + 1][r - 1]);
		}
	
	int res = 1e18;
	for (int l = 1, r = n; r <= 2 * n; ++ l, ++ r ) res = min(res, f[l][r]);
	cout << res;
	
	return 0;
}
```

---

## 作者：Ace_FutureDream (赞：9)

感谢有道翻译成功让我以为是序列而不是环导致坠机。

题目意思转换一下，就是给你一个环，每次可以选出一个区间，然后给那个区间染成任意颜色 $c$，代价是区间长度加 $X_c$，求最小代价使得最终颜色序列为目标序列。

首先把环变成序列。

设 $f_{i,j}$ 表示将区间 $[i,j]$ 染成目标颜色的最小代价。

第一种转移肯定是合并，即 $f_{i,j}=f_{i,k}+f_{k+1,j}$。

第二种就是在一次染色中顺便把右一个端点给染了，即 $f_{i,j}=f_{i,k}+f_{k+1,j-1}+j-k$，条件是 $c_j=c_k$。

这里的转移为什么是 $f_{i,k}+f_{k+1,j-1}$ 而不是 $f_{i,j-1}$ 呢？因为你在给 $[k,j]$ 染色的时候，在 $[i,k]$ 和 $[k+1,j-1]$ 中不能有跨区间的染色，不然就会产生覆盖，优先级无法保证。

第三种就是在一次染色中顺便把左一个端点给染了，即 $f_{i,j}=f_{i+1,k-1}+f_{k,j}+k-i$，条件是 $c_i=c_k$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=810;
int f[N][N],v[N],c[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i],c[i+n]=c[i];
	for(int i=1;i<=n;i++)cin>>v[i];
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=2*n;i++)f[i][i]=v[c[i]]+1,f[i][i-1]=0;
	for(int len=2;len<=n;len++){
		for(int i=1;i<=2*n-len+1;i++){
			int j=i+len-1;
			for(int k=i+1;k<=j;k++)
				if(c[k]==c[i])
					f[i][j]=min(f[i][j],f[i+1][k-1]+f[k][j]+k-i);
			for(int k=i;k<=j-1;k++)
				if(c[k]==c[j])
					f[i][j]=min(f[i][j],f[i][k]+f[k+1][j-1]+j-k);				
			for(int k=i;k<j;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
		}
	}
	int ans=1e18;
	for(int i=1;i<=n;i++){
		ans=min(ans,f[i][i+n-1]);
	}
	cout<<ans<<'\n'; 
	return 0;
}
```

---

## 作者：Ivan422 (赞：7)

题意：给你一个环，一开始环上点的颜色为 $0$，有 $n$ 个点 $n$ 种颜色，求染成目标颜色的具体代价。

代价：一次染色的区间长与给定颜色代价 $x_i$ 之和。

怎么看都是染色加强版。

首先显然环上问题**破环成链**，注意空间要开双倍~~罚时吃饱了~~。

然后我们考虑动态规划。

设 $f_{i,j}$ 为染完 ${i,j}$ 的最小代价。

首先，区间动态规划需要先预处理出单点答案 $f_{i,i}$，显然染一个点 $f_{i,i}=x_{c_i}+1$。

然后我们考虑按照常规思路动态规划。

按照区间长度枚举，从 $2$ 枚举到 $n$。

显然我们发现 $f_{i,j}=f_{i,i}+f_{i+1,j}$。

之后，我们枚举一下区间分隔点 $k$。

我们注意到要是分隔点 $c_i \neq c_k$，那么无法简减少代价，答案其实就是已知的 $f_{i,j}=f_{i,i}+f_{i+1,j}$。

那么我们考虑 $c_i = c_k$ 的情况。

1. 当中间没有额外元素，即 $k=i+1$，答案就是 $f_{i,j}=\min(f_{i,j}, f_{i+1,j}+1)$，直接增长区间即可，不需要重复统计代价。
2. 当中间有额外元素，那么变为 $f_{i,j}=\min(f_{i,j},(k-i-1+1)+f_{i+1,k-1}+f_{k,j})$。我们观察这个式子，其实就是额外染 $i+1$ 到 $k$ 的区间，然后覆盖上中间元素 $i+1$ 到 $k-1$，再加上剩下的一段。

然后我们就做完了，答案就是 $\min_{i=1}^nf_{i,i+n-1}$。

[代码](https://atcoder.jp/contests/abc400/submissions/64587770)。

---

## 作者：chenwenmo (赞：4)

### [ABC400F Happy Birthday! 3](https://www.luogu.com.cn/problem/AT_abc400_f)

> 简要题意：
>
> 给定一个长度为 $n(1\le n\le 400)$ 的环，每个点从 $1$ 到 $n$ 编号，初始颜色都为 $0$，给定目标颜色序列 $C_i$，以及花费 $X_i$，代表将 $[l,r]$ 覆盖成颜色 $C$ 的操作要花费 $r-l+1+X_c$，求把环涂成目标颜色的最小花费。

首先破环成链转换为序列问题。

考虑最优解会以一种什么样的形式呈现：

- 涂过的区间一定不相交或者包含。

- 可能存在某种方案，在某个区间中，先在底层操作，一次把所有颜色相同的一并涂上，然后上层覆盖一些操作。但是继续往上层想，就会发现，上层可能又把最开始底层的操作给覆盖了，然后转化为了更上层的子问题。

  那么我们可以想象成，最底层的操作，实际上是选择一部分颜色相同的一并涂上，而不是全部，那么被选择的格子，我们规定上层之后不能再覆盖它，于是这样考虑完了之后，就遍历了整个状态空间。

根据以上讨论来设计 DP，设 $f(l,r)$ 表示 $[l,r]$ 的最小花费：

- $f(i,i)=1+X_{C_i}$。

- $f(l,r)=\min\limits_{l\le k<r}\{f(l,k)+f(k+1,r)\}$。

- 然后考虑怎么选择把相同的颜色合并：
  $$
  f(l,r)=\min\limits_{l\le k<r, C_k=C_r}\{f(l,k)+(r-k)+f(k+1,r-1)\} \\
  f(l,r)=\min\limits_{l<k\le r, C_k=C_l}\{f(k,r)+(k-l)+f(l+1,k-1)\}
  $$
  即，分别考虑把 $l$ 或 $r$ 与中间某个颜色相同的 $k$ 合并。

  由于 $X_{C_l}$ 或 $X_{C_r}$ 的贡献已经在 $f(k,r)$ 或 $f(l,k)$ 计算过了，因此只需要再加上长度的贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
using LD = long double;
using PII = pair<int, int>;

const int N = 805;
const LL INF = 2e18;

int n, c[N];
LL x[N], f[N][N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        c[n + i] = c[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 1; i <= n * 2; i++) {
        f[i][i] = 1 + x[c[i]];
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n * 2; l++) {
            int r = l + len - 1;
            f[l][r] = INF;
            for (int i = l; i <= r; i++) {
                if (i > l && c[i] == c[l]) {
                    f[l][r] = min(f[l][r], f[l + 1][i - 1] + i - l + f[i][r]);
                }
                if (i < r && c[i] == c[r]) {
                    f[l][r] = min(f[l][r], f[i + 1][r - 1] + r - i + f[l][i]);
                }
            }
            for (int i = l; i < r; i++) {
                f[l][r] = min(f[l][r], f[l][i] + f[i + 1][r]);
            }
        }
    }
    LL ans = INF;
    for (int i = 1; i <= n; i++) ans = min(ans, f[i][i + n - 1]);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：huhaoming2011 (赞：3)

## 题目大意
在一个 $n$ 等份的圆上，每次可以给连续区间染色（扇形），代价是该种颜色代价加长度。问：最初无色，染色到目标状态的最小花费。

## 题解
其实，很明显可以看出是一道动态规划的题目。发现数据看上去可以 $O(n^3)$ 过，考虑区间 DP。

发现直接从无色开始染很难做，考虑倒过来，从目标状态做到无色。

设 $f_{i,j}$ 表示把 $i$ 到 $j$ 染成无色的最小代价，很明显有 $f_{i,j}=\min^{j-1}_{k=i}f_{i,k}+f_{k+1,j}$。但是因为一段区间里的颜色可能不一样，所以要让它可以被染成无色。我们再设 $g_{i,j}$ 表示把 $i$ 到 $j$ 整成可以拿去染成无色（即这一段颜色相同）的最小代价，很明显有 $g_{i,j}=\min^{j-1}_{k=i}g_{i,k}+f_{k+1,j}$，解释一下后面为什么要加 $f_{k+1,j}$：因为此时已经保证（长度小，前面算过）$i$ 到 $k$ 区间颜色相同，但是剩下的区间的颜色不一定与该区间颜色相同，所以直接用无色的代价。

特别的，当 $c_i=c_j$ 时，可以不操作，让 $g_{i,j}=\min(g_{i,j},g_{i,j-1})$，同时可以通过操作整成无色 $f_{i,j}=\min(f_{i,j},g_{i,j}+len+X_{c_i})$，其中 $len$ 是区间的长度，$X_{c_i}$ 是该颜色的特有代价。

记得破环成链！

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e3+7;
const int inf=1e18;
int f[MAXN][MAXN],g[MAXN][MAXN];
int n,c[MAXN],val[MAXN];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&c[i]);
		c[i+n]=c[i];
	}
	for(int i=1;i<=n;i++)
		scanf("%lld",&val[i]);
	for(int i=1;i<=2*n;i++)
		for(int j=1;j<=2*n;j++)
			f[i][j]=g[i][j]=inf;
	for(int i=1;i<=n*2;i++)
	{
		f[i][i]=1+val[c[i]];
		g[i][i]=0;
	}
	for(int len=2;len<=n;len++)
	{
		for(int l=1;l+len-1<=2*n;l++)
		{
			int r=l+len-1;
			for(int k=l;k<r;k++)
			{
				f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
				g[l][r]=min(g[l][r],g[l][k]+f[k+1][r]);
			}
			if(c[l]==c[r])
			{
				g[l][r]=min(g[l][r],g[l][r-1]);
				f[l][r]=min(f[l][r],g[l][r]+len+val[c[l]]);
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++)
		ans=min(ans,f[i][i+n-1]);
	printf("%lld",ans);
	return 0;
}
```
谢谢观看！

---

## 作者：szh_AK_all (赞：3)

在此处感谢翻译以及 @int_stl 大佬成功让我读错题面。

这题很显然是区间 dp，于是考虑转移。首先对于 $c_l=c_{l+1}$ 以及 $c_r=c_{r-1}$ 等情况进行特判，分别用 $f_{l+1,r}$ 与 $f_{l,r-1}$ 来转移，当 $c_l=c_r$ 时便考虑先将 $l\sim r$ 都染成 $c_l$ 的颜色，然后再对颜色不合法的区间进行转移。

然后是正常操作，也就是枚举断点 $k$，用 $f_{l,k}+f_{k+1,r}$ 来转移；当然需要注意当 $c_k=c_r$ 时我们可以进行特别的操作，也就是先将 $l\sim r$ 染成 $c_k$ 的颜色，然后对区间 $[l,k]$ 与 $[k+1,r-1]$ 进行操作，也就是 $f_{l,k}+f_{k+1,r-1}+r-k$，注意到转移式不应是 $f_{l,k}+f_{k+1,r-1}+r-l+1+x_{c_k}$，因为 $x_{c_k}$ 与 $k-l+1$ 已经被 $f_{l,k}$ 算进去了。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[805][805], c[805], x[805];

signed main() {
	int n;
	cin >> n;
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = n + 1; i <= 2 * n; i++)
		c[i] = c[i - n];
	for (int i = 1; i <= 2 * n; i++)
		f[i][i] = 1 + x[c[i]];
	for (int len = 2; len <= 2 * n; len++) {
		for (int l = 1; l + len - 1 <= 2 * n; l++) {
			int r = l + len - 1;
			if (c[l] == c[l + 1])
				f[l][r] = min(f[l][r], f[l + 1][r] + 1);
			else
				f[l][r] = min(f[l][r], f[l + 1][r] + 1 + x[c[l]]);
			if (c[r - 1] == c[r])
				f[l][r] = min(f[l][r], f[l][r - 1] + 1);
			else
				f[l][r] = min(f[l][r], f[l][r - 1] + 1 + x[c[r]]);
			if (c[l] == c[r]) {
				int ll = l, rr = r;
				while (ll + 1 <= r && c[ll + 1] == c[l])
					ll++;
				while (rr - 1 >= l && c[rr - 1] == c[r])
					rr--;
				f[l][r] = min(f[l][r], f[ll + 1][rr - 1] + r - l + 1 + x[c[l]]);
			}
			for (int k = l; k <= r; k++)
				f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
			for (int k = l; k <= r; k++) {
				if (c[k] == c[r])
					f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r - 1] + r - k);
			}
		}
	}
	int ans = f[0][0];
	for (int i = 1; i + n - 1 <= 2 * n; i++)
		ans = min(ans, f[i][i + n - 1]);
	cout << ans;
}
```

~~也许我的方法中有一些多余的转移。~~

---

## 作者：beyoursven (赞：2)

## 题意

给定一个大小为 $N$ 的环形序列，序列中每个元素初始时无色。每次操作中，可以选择序列中一个长度为 $M$（$M \le N$）的连续子序列染成颜色 $c$，代价为 $X_c + M$。现在序列中每个元素需要染成目标颜色 $C_i$，求最小总代价。

## 思路

根据数据范围，可以猜测使用区间 dp 求解。先考虑解决线性序列上的问题。

经过推导可以发现，两次染色的区间可以是不相交或者包含关系，但不可能是非包含但相交的关系。

定义 $dp_{i, j}$ 表示区间 $[i, j]$ 染成目标颜色的最小代价。

对于不相交的情况，显然有：
$$
dp_{i, j} \gets \min \limits_{i \le k \lt j} \{ dp_{i, k} + dp_{k + 1, j} \}
$$
对于包含情况，就是**第一步**把区间 $[i, j]$ 染成颜色 $C_i$，再处理区间内部的染色，处理时，左端点 $i$ 的颜色不发生变化。

定义 $g_{i, j}$ 表示区间 $[i, j]$ 染成目标颜色而第一步先把区间 $[i, j]$ 染成 $C_i$ 的最小代价。该状态不能由 $dp_{i, j}$ 代替。

包含情况只可能出现在 $C_i = C_j$ 时，有：
$$
dp_{i, j} \gets g_{i, j}
$$
考虑如何维护 $g_{i, j}$。

当区间 $[i, j]$ 中至少两个目标颜色为 $C_i$ 时，我们可以枚举 $C_k = C_i$ 的位置 $k$，将 $g_{i, j}$ 的染色看做是 $g_{i, k}$ 和 $g_{k, j}$ 合并后的结果，此时有：
$$
g_{i, j} \gets \min \limits_{i \le k \lt j, C_{k + 1} = C_i} \{ g_{i, k} + g_{k + 1, j} - X_{C_i}\}
$$
我们还可以考虑当区间 $[i, j]$ 染色为 $C_i$ 后直接处理区间 $[i + 1, j]$ 的染色，此时有：
$$
g_{i, j} \gets dp_{i + 1, j} + X_{C_i} + j - i + 1
$$

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 4e2 + 1;
const ll INF = 1e18;

int n, c[2 * MAXN], x[MAXN];
ll ans = LLONG_MAX, dp[2 * MAXN][2 * MAXN], g[2 * MAXN][2 * MAXN];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
    c[i + n] = c[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }
  for (int i = 1; i <= 2 * n; i++) {
    dp[i][i] = g[i][i] = x[c[i]] + 1;
  }
  for (int len = 2; len <= n; len++) {
    for (int i = 1, j = i + len - 1; j <= 2 * n; i++, j++) {
      dp[i][j] = INF, g[i][j] = x[c[i]] + j - i + 1 + dp[i + 1][j];
      for (int k = i; k < j; k++) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        if (c[i] == c[k + 1]) {
          g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j] - x[c[i]]);
        }
      }
      if (c[i] == c[j]) {
        dp[i][j] = min(dp[i][j], g[i][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[i][i + n - 1]);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：GUO120822 (赞：2)

**下文将 $c_i$ 称为 $a_i$，$X_i$ 称为 $x_i$。**

$n \leq 400$，考虑区间 dp。

首先题目说的是环，所以套路的断环成链。

然后套路的状态设计：

$dp_{i,j}$ 表示 $[i,j]$ 区间被染成正确的颜色的最小花费。

考虑两种转移：

1. 把区间劈开，枚举端点 $k$，$dp_{i,j}=\min(dp_{i,j},dp_{i,k}+dp_{k+1,j})$。

2. 把区间作为一个整体，一起操作，所以这种情况与 $i$ 和 $j$ 有关。需要将 $i$ 和 $j$ 放在一次操作中。所以前提条件为：$a_i=a_j$。那么如果进行一次操作，那么肯定横跨整个区间。并且此操作颜色为 $a_i$。所以在区间中的与 $a_i$ 颜色相同的点可以染，也可以不染。染了不一定更优，例如：$1 2 3 4 1 4 3 2 1$，把三个 $1$ 提出来操作反而把中间的区间劈开了，操作次数不但没减少，还增多了。所以接下来的问题就是决策与 $a_i$ 相同的位置是否染色。令 $f_{i,j}$ 表示 $[i,j]$ 的与 $a_i$ 不相同的位置染色最小价值。注意：与 $a_i$ 相同的也可以修改为正确的。然后 $dp_{i,j}=f_{i,j}+x_{a_i}+j-i+1$。考虑 $f_{i,j}$ 如何转移。$f_{i,j}=\min(f_{i,j},f_{i,k}+dp_{k+1,j})$ 。当 $a_j=a_i$ 时，$f_{i,j}=\min(f_{i,j},f_{i,j-1})$ 因为可以省略。

初始状态：$dp_{i,i}=x_{a_i}+1,f_{i,i}=0$。

[代码](https://atcoder.jp/contests/abc400/submissions/64583220) 在这。

---

## 作者：ty_mxzhn (赞：2)

考虑解的形式，每次选择一个区间覆盖，那么你不可能白白覆盖掉以前的整个区间。

所以匹配形如把一些同个颜色的点串在一起，而且不和其他线交叉。

我们设计两个状态转移：第一个是没有支付钱，正在纯粹的划分。第二个是支付了钱，现在可以免费点亮中间一个和两端同色的点，并且不需要付费直接划分。

注意答案在环上求，一定存在一个“旋转”的方式把环断成链。

只需要把环读两遍即可，时间复杂度 $O(n^3)$。

---

## 作者：Getaway_Car (赞：2)

考虑正难则反。问题转化为：

> 一个环上有 $n$ 个物品，颜色分别为 $col_i$，每次操作选择两个数 $i, j$ 使得 $\forall k \in [i, j],  col_k = col_i \lor col_k = 0$，将 $[i, j]$ 中的每个物品的颜色都设为 $0$。（下文将这种操作称为“漂白”。）一次操作的代价为 $j - i + 1 + x_{col_i}$。求将整个环漂白的最小总代价。
  
先断环为链。设 $dp_{i, j}$ 表示将 $[i, j]$ 漂白的最小代价，那么显然有 $dp_{i, j} = \min_{k = i}^{j - 1} dp_{i, k} + dp_{k + 1, j}$。

设 $f_{i, j}$ 表示使 $[i, j]$ 能够漂白的最小代价，那么显然有 $f_{i, j} = \min_{k = 1}^{j - 1} f_{i, k} + dp_{k + 1, j}$。当 $col_i = col_j$ 时，有 $f_{i, j} = \min (f_{i, j}, f_{i, j - 1}), dp_{i, j} = \min (dp_{i, j}, f_{i, j} + j - i + x_{col_i})$。

答案即为 $\min_{i = 1}^n dp_{i, i + n - 1}$。

---

## 作者：Xy_top (赞：2)

感觉比较显然的一道题，不太理解为什么赛时只有 $200$ 个人过。

首先我们注意到一个性质：所有染色区间要么两两包含，要么无交。这是非常好证明的，如果有交集又不是包含，那么先染的可以不染这里，代价更小。此外，我们也注意到假如将区间 $[l, r]$ 都染为 $x$，那么 $c_l$ 与 $c_r$ 都必须为 $x$。

根据以上结论，破环为链是正确的，因为不可能不存在断点。非常容易想到区间 ``DP``，设 $f_{i, j}$ 为将区间 $[i, j]$ 染为目标颜色的最小代价，如果 $c_i$ 不等于 $c_j$，那么直接枚举断点即可。

重点在于 $c_i$ 等于 $c_j$，此时的答案仍有可能是枚举断点。但另一种情况，对于 $[i, j]$ 中每个颜色为 $c_i$ 的地方，可以选择通过 $(i, j - i + 1, c_i)$ 来染色，也可以通过 $f_{i + 1, j - 1}$ 中的染色方法来染色，决策这个的过程还是一个 ``DP``。此时如果直接去做那么复杂度变为 $O(n^4)$， 不可接受。

比较显然的优化方法是，对于所有相同的颜色一起做 ``DP``，设 $g_{i, j}$ 为将 $[i, j]$ 这一段染成目标颜色，要求 $c_i = c_j$，且 $[i, j]$ 中已经等于 $c_i$ 的位置可以不染的最小代价。转移可以枚举断点，如果没有断点，那就是 $f_{i + 1, j - 1}$。算出 $g_{i, j}$ 后， $f_{i, j}$ 就等于 $g_{i, j} + j - i + 1 + x_{c_{i} }$。

于是我们就在 $O(n^3)$ 的时间内愉快地解决了这道简单题，代码（甚至写完都没调试一遍过）：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int c[805], x[805];
int f[805][805], g[805][805];
vector <int> v[805];
/*
g[i][j]：将 i + 1 ~ j - 1 变为和答案一样的最小代价

要求 c_i = c_j，转移枚举中间数

需要注意如果没有断点，答案为 f[i + 1][j - 1]
*/
void solve () {
	memset (f, 0x3f, sizeof f);
	memset (g, 0x3f, sizeof g);
	cin >> n;
	For (i, 1, n) {
		cin >> c[i];
		v[c[i] ].push_back (i);
		if (i != n) v[c[i] ].push_back (n + i);
		c[n + i] = c[i];
	}
	For (i, 1, n) cin >> x[i];
	For (i, 1, 2 * n - 1) {
		f[i][i - 1] = 0;
		f[i][i] = x[c[i] ] + 1;
	}
	For (len, 2, n) {
		For (i, 1, 2 * n - len) {
			int j = i + len - 1;
			For (k, i, j - 1) f[i][j] = min (f[i][j], f[i][k] + f[k + 1][j]);
			if (c[i] == c[j]) {
				//求 g[i][j]
				g[i][j] = f[i + 1][j - 1];
				For (k, i + 1, j - 1) if (c[k] == c[i])
                    g[i][j] = min (g[i][j], g[i][k] + g[k][j]);
				f[i][j] = min (f[i][j], g[i][j] + j - i + 1 + x[c[i] ]);
			}
		}
	}
	int ans = 10000000000000LL;
	For (i, 1, n) ans = min (ans, f[i][i + n - 1]);
	cout << ans;
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Eous (赞：2)

### 思路

做法来自官方题解。

我们发现正着做很难做，考虑正难则反。将题目改为：有一个长度为 $n$ 的环，环上每个点有一个颜色。每次操作可以花费 $len + v_{c_i}$ 的操作将 $[i,i + len - 1]$ 的每个点漂白，当且仅当这一段区间内的点要么没有颜色，要么颜色为 $c_i$，求将整个环漂白的最小代价。

我们发现这玩意很区间 dp 啊，直接设 $f_{i,j}$ 表示将 $[i,j]$ 漂白的最小代价。我们考虑最后一次操作，如果操作的区间 $[i',j']$ 不是 $[i,j]$ 但是与 $[i,j]$ 有交，那么考虑两种交的情况：

- $i' \in [i,j]$，可以将这个区间分成 $f_{i,i'} + f_{i' + 1,j}$。
- $j' \in [i,j]$，可以将这个区间分成 $f_{i,j'} + f_{j' + 1,j}$。

总之我们可以将 $[i,j]$ 分成 $[i,k] \cup [k + 1,j]$，有转移：

$$
f_{i,j} = \min_{k = i}^{j - 1}f_{i,k} + f_{k + 1,j}
$$

那么对于最后一次操作在 $[i,j]$ 上的，那么一定有 $c_i = c_j$。因为如果 $c_j \neq c_i$ 那么 $c_j$ 就只能是 $0$，都是 $0$ 了就没必要花多的代价漂白它了。转移有 $f_{i,j} = val + len + v_{c_i}$。其中 $val$ 表示将 $[i,j]$ 整成能漂的最小代价。

考虑如何求 $val$。设 $g_{i,j}$ 表示将 $[i,j]$ 整成能漂的最小代价。如何转移呢？在上面转移 $f_{i,j}$ 的时候，我们想想如何转移 $g$。我们将它分成两个区间 $[i,k] \cup [k + 1,j]$，我们想让它能漂，那么 $[i,k]$ 是得能漂的。然后我们想当然的就想：$[k + 1,j]$ 也能漂就足够了。但是这显然是不行的。因为如果 $[k + 1,j]$ 也能漂，我们又不知道 $[k + 1,j]$ 这里面的一样的颜色是啥。所以只能让 $[k + 1,j]$ 变成无色。有转移：

$$
g_{i,j} = \min_{k = i}^{j - 1}g_{i,k} + f_{k + 1,j}
$$

我们考虑当 $c_i = c_j$ 时如何转移。有 $g_{i,j} \leftarrow g_{i,j - 1}$，表示第 $j$ 个不操作。

最后的答案显然是 $\min_{i = 1}^{n}f_{i,i + n - 1}$。

### code

```cpp
#include<bits/extc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
int n;
int c[805],v[405];
int dp1[805][805],dp2[805][805];
// dp1 -> f,dp2 -> g
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
        c[i + n] = c[i];
    }
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    memset(dp1,0x3f,sizeof dp1);
    memset(dp2,0x3f,sizeof dp2);
    for (int i = 1; i <= n << 1; i++)
    {
        dp1[i][i] = 1 + v[c[i]];
        dp2[i][i] = 0;
    }
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1,j; (j = i + len - 1) <= n << 1; i++)
        {
            for (int k = i; k < j; k++)
            {
                dp1[i][j] = min(dp1[i][j],dp1[i][k] + dp1[k + 1][j]);
                dp2[i][j] = min(dp2[i][j],dp2[i][k] + dp1[k + 1][j]);
            }// 第一个转移
            if (c[j] == c[i])
            {
                dp2[i][j] = min(dp2[i][j],dp2[i][j - 1]);
                dp1[i][j] = min(dp1[i][j],dp2[i][j] + len + v[c[j]]);
            }// 第二个转移
        }
    }
    int ans = inf;
    for (int i = 1; i <= n; i++)// 最后的答案
        ans = min(ans,dp1[i][i + n - 1]);
    cout << ans;
    return 0;
}
```

---

## 作者：george0929 (赞：2)

一句话题意：每次你可以选一个圆环上的区间 $[l,r]$ 和颜色 $c$，花费 $r-l+1+x_c$ 的代价将这个区间涂成颜色 $c$。求达到目标状态的最小代价。

由于 $n\leq 400$，考虑区间 DP。

首先断环成链，这样只需考虑序列问题。

先列出状态、答案和初值：

- $dp_{l,r}$ 表示区间 $[l,r]$ 达到目标状态的最小代价。
- 答案：$\min_{1\leq i\leq n} dp_{i,i+n-1}$。
- 初始时 $dp_{i,i}=x_{c_i}+1$。

接下来考虑转移。区间 DP 的转移分两类——**区间合并**和**区间扩张**。

- 区间合并
  - 直接区间拼接：$dp_{l,r}\leftarrow \min_{l\leq k<r} dp_{l,k}+dp_{k+1,r}$。
  - 两个交集大小为 $1$，并集为 $[l,r]$ 的区间（即区间 $[l,k]$ 和 $[k,r]$）
    - 在左区间中，交集处最后被涂色的区间必定为**左区间的后缀**。
    - 在右区间中，交集处最后被涂色的区间必定为**右区间的前缀**。
    - 那么可以合并这两个涂色区间：$dp_{l,r}\leftarrow \min_{l\leq k\leq r} dp_{l,k}+dp_{k,r}-x_{c_k}-1$。
- 区间扩张
  - 区间扩张本质上是在处理**区间合并类转移的边界情况**，若区间的左右端点目标颜色相同，且区间中间（不含左右端点）没有与左右端点颜色相同的点，则左右端点永远无法通过上述转移合并到同一个涂色区间（即无法使用“将区间 $[l,r]$ 涂为 $c_l$”的操作），因此特殊处理。
    - $dp_{l,r}\leftarrow dp_{l+1,r}+r-l\ (c_l=c_r)$。
    - $dp_{l,r}\leftarrow dp_{l,r-1}+r-l\ (c_l=c_r)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,c[805],x[805];
int dp[805][805];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i],c[n+i]=c[i];
	for(int i=1;i<=n;i++) cin>>x[i];
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=2*n;i++) dp[i][i]=x[c[i]]+1;
	for(int len=2;len<=2*n;len++){
		for(int l=1;l+len-1<=2*n;l++){
			int r=l+len-1;
			if(c[l]==c[r]){
				dp[l][r]=min(dp[l][r],dp[l+1][r]+r-l);
				dp[l][r]=min(dp[l][r],dp[l][r-1]+r-l);
			}
			for(int k=l;k<r;k++){
				dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
			}
			for(int k=l;k<=r;k++){
				dp[l][r]=min(dp[l][r],dp[l][k]+dp[k][r]-x[c[k]]-1);
			}
		}
	}
	int ans=1e18;
	for(int i=1;i<=n;i++) ans=min(ans,dp[i][i+n-1]);
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：wflhx2011 (赞：1)

发现一段区间可以由两次修改小区间合并过来，考虑区间 dp。

设 $f_{l,r}$ 表示使区间 $[l,r]$ 为最后结果的最小代价。

首先因为在环上，不妨断环成链，即复制一次原序列接到最后，这样就解决了存在环无法转移的问题。

初始状态为 $f_{i,i}=X_{C_i}+1$，也就是只修改这一个位置。

然后，对于转移方程，考虑 $r$ 这个位置可以如何得到。

- 只修改 $r$ 这个位置，此时 $f_{l,r}=f_{l,r-1}+f_{r,r}$。

- 修改 $[i,r]$ 这段区间，其中 $l\le i< r$。此时应满足 $C_i=C_r$，否则，$i$ 这个点需要再次修改，此时把 $i$ 和 $r$ 放在两次修改中分别修改，一定不会使答案更劣。

  那么考虑先修改好区间 $[l,i]$，然后对于区间 $[i+1,r]$ 在之前对 $i$ 的修改中一起修改（或者理解为扩展对 $i$ 的修改到 $r$），这里因为只修改了一次，所以不需要额外加 $X_{C_i}$。最后修改 $[i+1,r-1]$，也就是 $f_{l,r}=f_{l,i}+r-i+f_{i+1,r-1}$。

对于二者取最小值。

这里注意不能把初值赋为极大值，因为转移时可能出现 $f_{l,r}$ 中 $l>r$，正确值应为 $0$，但不会被转移到，如果赋为极大值就无法从该状态转移出去。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c[805],f[805][805],x[805],res=1e18; 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>c[i],c[n+i]=c[i];
	for(int i=1;i<=n;i++)
		cin>>x[i];
//	memset(f,0x3f,sizeof(f)); 
	for(int i=1;i<=2*n;i++)
		f[i][i]=x[c[i]]+1;
	for(int len=2;len<=2*n;len++)
		for(int l=1;l+len-1<=2*n;l++)
		{
			int r=l+len-1;
			f[l][r]=f[l][r-1]+f[r][r];
			for(int i=l;i<r;i++)
				if(c[i]==c[r])
					f[l][r]=min(f[l][r],f[l][i]+r-i+f[i+1][r-1]);
		}
	for(int l=1;l<=n+1;l++)
		res=min(res,f[l][l+n-1]);
	cout<<res;	
	return 0;
}

```

---

## 作者：lyx128 (赞：1)

本题目考虑使用区间型动态规划实现，$dp_{i,j}$ 表示将 $i$ 到 $j$ 的区间全部变到对应的 $c$ 的最小代价。

如果你觉得难度较高，可以考虑先看一看这一道[题目](https://www.luogu.com.cn/problem/P4170)，这道题目只是和本题存在计算代价的差别。

先考虑初始化，显而易见 $dp_{i,i}=x_{c_i}+1$，这里的 $+1$ 指的是区间长度 $b$。

接着，考虑对 $dp_{i,j}$ 转移方程，考虑以下 $2$ 种情况：

- $c_i=c_j$，我们可以直接将左大子区间的花费 $dp_{i,j-1}$ 和单次修改 $j$ 的花费相加或右大子区间的花费 $dp_{i+1,j}$ 和单次修改 $i$ 的花费相加取最小值得到。
- 直接合并，考虑寻找中间点 $k$，使得 $dp_{i,j}$ 可以被划分为 $dp_{i,k}$ 和 $dp_{k+1,j}$ 或 $dp_{k,j}$ 转移而来。那么，为什么有一步特殊的交叉区间计算呢？这是因为有时正常计算时，会少计算重复修改颜色的情况，当然，加入交叉长度的循环计算也是可以的，但是请注意**容斥原理**的应用。

最后，请各位同学注意：这是一个环上的动态规划，注意破环成链。

以下为满分通过的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=800;
const ll oo=1e18;
int n;
int c[N+5];
int x[N+5];
ll dp[N+5][N+5];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		c[i+n]=c[i];
	}
	for(int i=1;i<=n;i++)
		cin>>x[i];
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=(n<<1);i++)
		dp[i][i]=x[c[i]]+1;
	for(int len=2;len<=n;len++){
		for(int i=1;i<=(n<<1)-len+1;i++){
			int j=i+len-1;
			if(c[i]==c[j])
				dp[i][j]=min(dp[i+1][j],dp[i][j-1])+(j-i+1)-1;
			for(int k=i;k<=j;k++)
				dp[i][j]=min({dp[i][j],dp[i][k]+dp[k+1][j],dp[i][k]+dp[k][j]-x[c[k]]-1});
		}
	}
	ll res=oo;
	for(int i=1;i<=n;i++)
		res=min(res,dp[i][i+n-1]);
	cout<<res<<"\n";
	return 0;
}
```

---

## 作者：SDSXC (赞：1)

神秘抽象做法。

题意：环上染色，给定目标状态，每次可以花费 $X_c+L$ 的代价把一段长为 $L$ 的区间染成 $C$，求最小代价。

考虑区间dp，$f_{i,j}$ 表示 $[i,j]$ 的最小代价。

看看怎么转移，首先显然可以将两个区间直接拼起来，代价相加，如果这两个区间连接处颜色一样，那么显然可以少刷一次，代价 $f_{i,k}+f_{k+1,i}-X_{C_k}$。

然后对于形如 AAA___AAA，这样的，我们可以考虑先把一整段全刷成 A，然后再把下划线填上，代价就是下划线那一段的再加一整段刷成 A 的。但是还有可能 AAA 并不是两段，而是超过了三段，比如 AAA___AAA___AAA。这种情况其实已经被统计到了，从中间的 AAA 中间将区间劈开时，左右均统计了先刷 A 再刷下划线的方案，然后按照上文提到的合并方法就可以正确的统计到答案，唯一会出问题的就是中间的 AAA 只有一个 A 的情况，这种情况下没法从中间劈开。

如何处理这种情况呢？我们可以将原C数组每一位扩展成2位，即 ABC 变成 AABBCC，再把所有的 $X$ 乘以二，这样就会统计出答案的两倍，最后除掉即可。

~~赛时因为所有 C 全相等的情况处理错了误以为自己假了没调出来，太幽默了。~~

[代码](https://atcoder.jp/contests/abc400/submissions/64566393)

---

## 作者：_Kamisato_Ayaka_ (赞：1)

[ABC400F](https://www.luogu.com.cn/problem/AT_abc400_f)

## Statement

你有一个环状数组，你可以执行以下操作：

- 选择三个整数 $1 \leq a,b,c \leq n$，$\forall i \in [0,b-1]$，修改 $a + i$ 的位置颜色变成 $c$，这次操作的代价为 $b + x_c$。

求出使得最后数组颜色状态为数组 $C$ 的最小代价，$n \leq 400$。

## Solution

考虑操作反过来，一开始颜色状态为 $C$，要把所有颜色去掉的最小代价。

看到 $n\leq 400$ 并且是区间问题，考虑区间 dp。

记 $dp_{l,r}$ 表示将 $[l,r]$ 内的颜色去掉的最小代价。

- 如果当前操作不覆盖整个区间，枚举分界点 $k$ 做区间合并，$dp_{l,r} \leftarrow dp_{l,k} + dp_{k+1,r}$。
- 如果当前操作覆盖整个区间，此时满足 $c_l = c_r$，要么区间全是无颜色，要么全是 $c_l$。
  
  - 考虑枚举分界点 $k$ 满足 $c_k = c_l$，这时候把 $[k+1,r-1]$ 变成无颜色是无额外代价的，因为已经在 $dp_{l,k}$ 中计算过了，$[l,k]$ 变成无颜色需要额外增加 $r - k$，即可以理解区间向后扩张了 $r - k$ 的长度，$dp_{l,r} \leftarrow dp_{l,k} + dp_{k+1,r-1} + r - k$。

破环成链，答案就是 $\min\limits_{i=1}^{n}\{dp_{i,i+n-1}\}$。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

constexpr int MAXN = 810;
int n, c[MAXN], x[MAXN], dp[MAXN][MAXN];

inline void chkmin (int &x, int y) { if (x > y) x = y; }

signed main() {
	cin.tie(0) -> sync_with_stdio(0);
	cout.tie(0) -> sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> c[i], c[i + n] = c[i];
	for (int i = 1; i <= n; i ++) cin >> x[i];
	for (int i = 1; i <= (n << 1); i ++)
		dp[i][i] = 1 + x[c[i]];
	for (int i = 1; i < (n << 1); i ++) 
		dp[i][i + 1] = 2 + (c[i] == c[i + 1] ? x[c[i]] : x[c[i]] + x[c[i + 1]]);
	for (int len = 3; len <= n; len ++) {
		for (int l = 1; l + len - 1 <= (n << 1); l ++) {
			int r = l + len - 1;
			dp[l][r] = 1e18;
			chkmin (dp[l][r], dp[l + 1][r] + x[c[l]] + 1);
			chkmin (dp[l][r], dp[l][r - 1] + x[c[r]] + 1);
			if (c[l] == c[r]) {
				chkmin (dp[l][r], dp[l + 1][r - 1] + len + x[c[l]]);
				for (int k = l + 1; k < r; k ++) if (c[k] == c[l])
					chkmin (dp[l][r], dp[l][k] + dp[k + 1][r - 1] + r - k);
			}
			for (int k = l; k < r; k ++)
				chkmin (dp[l][r], dp[l][k] + dp[k + 1][r]);
		}
	}
	int Answer = 3e18;
	for (int i = 1; i <= n; i ++)
		chkmin (Answer, dp[i][i + n - 1]);
	cout << Answer << '\n';
	return 0;
}
```

---

## 作者：wmrqwq (赞：1)

这是一篇视频题解。

![](bilibili:BV19BRdYdEHk?t=679)

[参考代码](https://atcoder.jp/contests/abc400/submissions/64552268)

---

## 作者：ax_by_c (赞：0)

这种题肯定考虑区间 DP。

首先考虑链的情况，设 $f_{i,j}$ 为染完 $[i,j]$ 所需的最小代价。

转移考虑染色是最左边的颜色还是最右边的颜色，需要在中间再选一些把所有异色覆盖掉，这个可以再套一个 DP 解决。还有一个转移是直接分段。

考虑环怎么做，考虑破环成链。注意到不可能每个相邻都被跨过，所以答案就是 $\min f_{i,i+n-1}$。

套的那个 DP 肯定不用每次都跑一遍，直接从子区间那里继承过来就好了。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll llinf=3e18;
const int N=805;
int n,a[N];
ll w[N],f[N][N],gl[N][N],gr[N][N];
void slv(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]),a[i+n]=a[i];
	rep(i,1,n)scanf("%lld",&w[i]);
	rep(i,1,n*2)rep(j,1,n*2)f[i][j]=gl[i][j]=gr[i][j]=llinf;
	rep(i,0,n*2)gl[i+1][i]=gr[i+1][i]=0;
	rep(len,1,n){
		for(int l=1,r=len;r<=n*2;l++,r++){
			{
				if(a[r]==a[l]){
					gr[l][r]=min(gr[l][r],gr[l][r-1]);
				}
				rep(x,l,r)gr[l][r]=min(gr[l][r],gr[l][x-1]+f[x][r]);
				f[l][r]=min(f[l][r],w[a[l]]+(r-l+1)+gr[l][r]);
			}
			{
				if(a[l]==a[r]){
					gl[l][r]=min(gl[l][r],gl[l+1][r]);
				}
				rep(x,l,r)gl[l][r]=min(gl[l][r],gl[x+1][r]+f[l][x]);
				f[l][r]=min(f[l][r],w[a[r]]+(r-l+1)+gl[l][r]);
			}
			rep(x,l,r-1)f[l][r]=min(f[l][r],f[l][x]+f[x+1][r]);
		}
	}
	ll ans=llinf;
	rep(i,1,n)ans=min(ans,f[i][i+n-1]);
	printf("%lld\n",ans);
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ax_by_c::main();
	return 0;
}
```

---

## 作者：无名之雾 (赞：0)

小号 $9$ 分钟切，一场 $1200$ 手速之巅。

## solution


环上不太好做，套路化的展开，将序列复制一遍到后面。对于每一个位置 $i \in [1, n]$，考虑以 $i$ 开头的长度为 $n$ 的连续区间，即 $[i, i+n-1]$，总共有 $n$ 种方式枚举整圈。

这相当于将环转为线性并维护所有可能的旋转起点。

进行一个显然的区间 dp。

令 $dp_{i,j}$ 表示将区间 $[i, j]$ 染色为目标颜色的最小额外操作代价。

转移是显然的，有：

$$dp_{i,j}=\min(dp_{i+1,j}+x_{c_i},dp_{i+1,k-1}+ dp_{k,j}+k-i-1)$$
最终答案为：
$$\min_{1 \le i \le n} (dp_{i,i+n-1}+n)$$

$O(n^3)$ 跑得飞快。

蓝？搞错了吧。

---

## 作者：lw393 (赞：0)

赛时成功地由于没打完代码而没进前 200。

一道还不错的区间 dp 板子。从第 $i$ 个格子可以看作第 $i+n$ 个格子，我们就知道这是在环上跑 dp。于是我们想到[石子合并](https://www.luogu.com.cn/problem/P1880)这道题，直接看作长度为 $2n$ 的序列即可，最终答案在每个长度为 $n$ 的序列答案中取最小即可。

我们定义 $dp_{l,r}$ 为区间 $[l,r]$ 中，取得最终状态的最小代价。

先对初始状态做预处理 $dp_{i,i}=x[c[i]]+1$。

再而，我们通过观察样例与解释，发现有两种填充颜色的方法：

1. 直接在一段已经填充好了的颜色段的末尾添上一个单点。
2. 我们可以在填充中间的一段之前将这一整段填上同一颜色。

对于第一种情况，$ans_1 = dp_{l,r-1}+x[c[r]]+1$。

对于第二种情况，$ans_2 = \min_{m=l}^{r-1} ([c[m]\not=c[r]]\times\infty + [c[m]=c[r]]\times(dp_{l,m}+r-m+dp_{m-1,r-1}))$。

于是 $dp_{l,r}=\min(ans_1,ans_2)$。

注意 $dp_{l,r}$ 在 $l > r$ 时，值是 $0$ 而不是常常设置的 $+\infty$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 8e2 + 5;

int x[N], c[N];
int dp[N][N];

signed main(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> c[i], c[i + n] = c[i];
	for(int i = 1; i <= n; i++) cin >> x[i];
	for(int i = 1; i <= 2 * n; i++) dp[i][i] = x[c[i]] + 1;
	for(int len = 2; len <= 2 * n; len++){
		for(int l = 1; l + len - 1 <= 2 * n; l++){
			int r = l + len - 1;
			dp[l][r] = dp[l][r - 1] + x[c[r]] + 1;
			for(int m = l; m < r; m++){
				if(c[m] == c[r]) dp[l][r] = min(dp[l][r], dp[l][m] + r - m + dp[m + 1][r - 1]);
			}
		}
	}
	int ans = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1; i <= n; i++) ans = min(ans, dp[i][i + n - 1]);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：AmaoFox (赞：0)

考虑到操作整个颠倒过来，我们得到这样一个问题：

> 对于所有的 $i$ ，最初将第 $i$ 块涂成颜色 $C_i$。通过重复以下操作，求出将所有块涂成 $0$ 所需的最小成本。
> - 选择 $a, b, c$，区间 $[a,a+b)$ 的颜色必须只为 $0$ 或 $c$，然后用 $0$ 涂满这个区间，操作花费 $b + X_c$。

这两个问题是等价的，所以我们考虑转换后的问题。

那么，第 $a$ 块和第 $a+b-1$ 块在每次操作之前肯定是上了色的，否则你就可以通过缩短这个区间来减小你的花费了。

考虑最后一次操作。假设最后一次操作是在区间 $[x,x+y)$ 上进行的。由于在最后一次操作之前，区间 $[x,x+y)$ 被涂上了颜色 $c$，因此我们知道从未对包含在 $[x,x+y)$ 中的块、和另一个不包含在 $[x,x+y)$ 中的块同时进行过任何操作；否则，这个操作的区间跨过了 $x$ 或者 $x+y-1$，那么它就被涂上 $0$ 了。

因此，我们现在可以分别求出区间 $[x,x+y)$ 和其他区间将所有块涂成颜色 $0$ 的最小成本，并将它们相加求出 $[x,x+y)$ 作为最后一次操作的最小成本。

由上可知，该问题可以分治，因此我们考虑 dp。原来的问题是一个圆，我们把它拆分成一个序列问题，只要每一个位置都切开，找出解的最小值就可以了。

设 $dp_{l,r}$ 是使棋子 $[l,r)$ 涂满 $0$ 所需的总成本的最小值。根据最后一次操作是否在 $[l,r)$ 上进行，有不同的方式计算 $dp_{l, r}$。

假设最后一次操作不在棋子 $[l,r)$，而是在棋子 $[l',r')$ 上，首先 $l\neq l'$ 或 $r\neq r'$。对于 $l\neq l'$，我们可以单独考虑 $[l,l')$ 和 $[l',r)$，而对于另一侧也是一样的。因此，这种情况中的成本就是 $dp_{l, m} + dp_{m, r}$ 的最小值。

现在假设最后一次操作是在区间 $[l,r)$ 上进行的情况。则首先要将区间 $[l,r)$ 全部涂成 $0$ 或 $C_l$，再加上 $r-l+X_{C_l}$。

将区间 $[l,r)$ 全部涂成 $0$ 或 $C_l$ 的成本可以直接 dp。具体地说，我们假设 $C_{r-1}$ 被变为 $0$，则 $dp_{l, r} \leftarrow \min(dp_{l, m} + dp_{m, r})$。而假设 $C_{r - 1}$ 变为 $C_l$，$dp_{l, r} \leftarrow \min(dp_{l, r}, ep_{l, r - 1})$。然后再加上最后操作的成本就可以获得答案了。

这样就完成了 dp 的计算，最终答案是 $\min dp_{i,i+N}$。

总体时间复杂度为 $O(N^3)$。

~~翻译由 DeepSeek R1 完成。~~

---

## 作者：Yao_yx (赞：0)

显然每次操作即为覆盖一个区间。又注意到这些区间只能包含或相离，不能相交，否则其交集被覆盖两遍肯定不优。

再注意到一个性质：至少存在一个点使得所有覆盖它的区间必有一端点是它（每个点都不满足的话必存在相交区间）。所以可以一这个点为端点断环成链，在数列上区间dp。

对于当前区间 $[i,j]$，枚举覆盖左端点的区间（显然只有一个），设该区间右端点为 $k$，有转移：

$$ dp_{i,j} \gets dp_{i,k}+dp_{k+1,j} $$

但是如果 $i$ 与 $j$ 颜色相同，可以先完整覆盖 $[i,j]$ 区间一遍，再在该区间内部覆盖，每段区间的贡献则为许多段小区间的贡献之和。

设 $[i,j]$ 中有 $tot$ 段颜色都与 $i$ 颜色相同的区间，则显然除去完整覆盖区间的贡献每段连续区间的贡献是相等的，可记 $f_j$ 为第 $j$ 段区间除去完整覆盖区间的贡献的贡献，枚举上一段端点 $k$ 有转移：

$$ f_j \gets f_k+dp_{r_k, l_j} $$

其中 $l_i$ 与 $r_i$ 表示第 $i$ 段区间的左右端点。

枚举 $i,j$ 是 $O(n^2)$ 的，每次转移 $f$ 也是 $O(n^2)$ 的，时间复杂度 $O(n^4)$，不能通过。

注意到每次转移 $f$ 时左端点是固定的，所以区间dp时按左端点从大到小，右端点从小到大的顺序枚举。这样只会转移 $n$ 次 $f$。时间复杂度 $O(n^3)$。

注意先转移第二种转移，再转移第一种转移。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;

const int MAXN = 405;

int n, tot;
int a[MAXN], c[MAXN << 1], f[MAXN << 1];
int dp[MAXN << 1][MAXN << 1];
pair<int, int> b[MAXN << 1];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n; for(int i = 1; i <= n; ++i) cin >> c[i], c[i + n] = c[i];
	for(int i = 1; i <= n; ++i) cin >> a[i]; memset(dp, 63, sizeof(dp));
	for(int i = n * 2; i >= 1; --i){
		tot = 0;
		for(int j = i + 1, now = i; j <= n * 2 + 1; ++j){
			if(c[j] == c[i] && c[j - 1] != c[i]) now = j;
			if(c[j] != c[i] && c[j - 1] == c[i]) b[++tot] = {now, j - 1};
		}
		memset(f, 63, sizeof(f)); f[1] = 0;
		for(int j = 2; j <= tot; ++j){
			for(int k = 1; k < j; ++k){
				f[j] = min(f[j], f[k] + dp[b[k].se + 1][b[j].fi - 1]);
			}
		}
		for(int j = 1; j <= tot; ++j){
			for(int k = b[j].fi; k <= b[j].se; ++k){
				dp[i][k] = min(dp[i][k], k - i + 1 + a[c[i]] + f[j]);
			}
		}
		T:;
		for(int j = i; j <= n * 2; ++j){
			if(i == j){ dp[i][j] = a[c[i]] + 1; continue; }
			for(int k = i; k <= j; ++k){
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}
		}
	}
	int ans = 1e18; for(int i = 1; i <= n; ++i) ans = min(ans, dp[i][i + n - 1]); cout << ans;

	return 0;
}

```

---

