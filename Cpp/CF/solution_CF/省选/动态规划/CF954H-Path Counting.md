# Path Counting

## 题目描述

You are given a rooted tree. Let's denote $ d(x) $ as depth of node $ x $ : depth of the root is $ 1 $ , depth of any other node $ x $ is $ d(y)+1 $ , where $ y $ is a parent of $ x $ .

The tree has the following property: every node $ x $ with $ d(x)=i $ has exactly $ a_{i} $ children. Maximum possible depth of a node is $ n $ , and $ a_{n}=0 $ .

We define $ f_{k} $ as the number of unordered pairs of vertices in the tree such that the number of edges on the simple path between them is equal to $ k $ .

Calculate $ f_{k} $ modulo $ 10^{9}+7 $ for every $ 1<=k<=2n-2 $ .

## 说明/提示

This the tree from the first sample:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954H/8a09c9c56935b94e970d5753d7484c0e7a756d44.png)

## 样例 #1

### 输入

```
4
2 2 2
```

### 输出

```
14 19 20 20 16 16 ```

## 样例 #2

### 输入

```
3
2 3
```

### 输出

```
8 13 6 9 ```

# 题解

## 作者：fade_away (赞：7)

看到其他题解都是枚举端点向上向下 dp ，事实上枚举 LCA 也是可行的。

## 约定

令 $M(i,j)=\prod_{k=i}^{i+j-1}a_k$ 。

令 $g_i=\prod_{k=1}^{i}a_i$ 。

设 $Ans_i$ 表示长度为 $i$ 的路径个数，即答案。

## 分类讨论

#### 一、有一个端点为 LCA

这种情况可以枚举 LCA 的深度，然后枚举链的长度来计算，也即
$$Ans_t\leftarrow Ans_t+\sum_{i=1}^{n-1}M(i,t)M(1,i-1)$$

时间复杂度为 $O(n^2)$ 。

#### 二、没有端点为 LCA

这种情况需要枚举 LCA 的深度，再枚举左右儿子分别的深度，即

$$Ans_t\leftarrow Ans_t+\sum_{i=1}^{n-1}\binom{a_i}{2}M(1,i-1)\sum_{j=1}^{t-1}M(i+1,j-1)M(i+1,t-j-1)$$

这样的时间复杂度是 $O(n^3)$ 的，考虑优化，我们把 $M(i,j)$ 拆成 $\frac{g_{i+j-1}}{g_{i-1}}$ 的形式，整理一下式子：

$$
Ans_t\leftarrow Ans_t+\sum_{i=1}^{n-1}g_{i-1}\frac{1}{g_i^2}\binom{a_i}{2}\sum_{j=1}^{t-1}g_{i+j-1}g_{i+t-j-1}
$$

观察到后面这个 $\sum_{j=1}^{t-1}g_{i+j-1}g_{i+t-j-1}$ 的卷积式，考虑预处理它。

我们设 $f_{t,i}=\sum_{j=1}^{t-1}g_{i+j-1}g_{i+t-j-1}$ ，不难发现 $f_{t,i}=f_{t-2,i+1}+2g_ig_{i+t-2}(t>2)$ ，而 $f_{2,i}=g_i^2$ 。

因此 $f_{t,i}$ 能够被 $O(n^2)$ 递推出来，这样总时间复杂度就变成了 $O(n^2)$ 。

## Code
```cpp
int a[MAXN], _g[MAXN << 2], g[MAXN << 2], Ans[MAXN << 2], f[MAXN << 1][MAXN];
int upd(int x, int y) { return x + y >= mods ? x + y - mods : x + y; }
int quick_pow(int x, int y) {
	int ret = 1;
	for (; y ; y >>= 1) {
		if (y & 1) ret = 1ll * ret * x % mods;
		x = 1ll * x * x % mods;
	}
	return ret;
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n;
	read(n), g[0] = 1;
	for (int i = 1; i < n ; ++ i) read(a[i]), g[i] = 1ll * g[i - 1] * a[i] % mods, _g[i] = quick_pow(g[i], mods - 2);
	for (int t = 1; t < n ; ++ t)
		for (int i = 1; i <= n - t ; ++ i)
			Ans[t] = upd(Ans[t], g[i + t - 1]);

	for (int i = 1; i < n ; ++ i) f[2][i] = 1ll * g[i] * g[i] % mods;
	for (int t = 3; t <= n + n - 2 ; ++ t)
		for (int i = 1; i < n ; ++ i)
			f[t][i] = upd(f[t - 2][i + 1], 2ll * g[i] * g[i + t - 2] % mods);

	for (int t = 2; t <= n + n - 2 ; ++ t)
		for (int i = 1; i < n ; ++ i)
			Ans[t] = upd(Ans[t], 1ll * (a[i] - 1) * inv2 % mods * _g[i] % mods * f[t][i] % mods);

	for (int t = 1; t <= n + n - 2 ; ++ t) print(Ans[t]), putc(' ');
	return 0;
}
```


---

## 作者：我打 (赞：1)

[博客链接](https://www.cnblogs.com/Laoli-2020/p/16696709.html)

题目大意：给定一颗以 $1$ 为根，深度为 $n$ 的有根树（规定根的深度为 $1$），树上每一个深度为 $i$ 的点都有 $a_i$ 个儿子。对于每一个 $k \in [1,2n-2]$ 求出长度为 $k$ 的路径数量。

数据范围：$2 \le n \le 5000$，$2 \le a_i \le 10^9$。

路径分为两种，一种为两端点的LCA在路径中间（不在端点上），另一种为两端点的LCA在端点上，我们分别求解，然后将路径数量相加。

#### LCA在路径中间
我们考虑在LCA处统计路径数。

设 $f_{i,j}$ 表示以深度为 $i$ 的点为LCA的路径中，长度为 $j$ 的有多少条。

我们考虑如何计算 $f_{i,j}$，有一个非常显然的式子，就是枚举左右端点的深度，然后计算满足这两个端点的LCA深度为 $i$ 的方案数，即：

$$
\large f_{i,j}=\frac{a_i \times (a_i-1)} 2 \times \sum_{k=i+1}^{i+j-1}(\prod_{x=i+1}^{k-1} a_x \prod_{x=i+1}^{j-k-1} a_x) 
$$

式子的含义就是先选出该节点的两个儿子，然后从这两个儿子向下扩展路径，一个扩展 $k-1$ 长度，另外一个扩展 $j-k-1$，可以简单前缀积优化一下做到 $O(N^3)$。

需要进行优化，注意到 $f_{i,j}$ 式子右边的式子和 $f_{i+1,j-2}$ 的很像，我们把这两个式子放在一起。



$$\large f_{i,j}=\frac{a_i \times (a_i-1)} 2 \times \sum_{k=i+1}^{i+j-1}(\prod_{x=i+1}^{k-1} a_x \prod_{x=i+1}^{j-k-1} a_x) $$
$$
\large f_{i+1,j-2}=\frac{a_{i+1} \times (a_{i+1}-1)} 2 \times \sum_{k=i+2}^{i+j-2}(\prod_{x=i+2}^{k-1} a_x \prod_{x=i+2}^{j-k-3} a_x)$$

发现 $f_{i,j}$ 的大部分贡献都是从 $\frac{a_i \times (a_i-1)} 2 \times f_{i+1,j-2} \times \frac{2a_{i+1}}{a_{i+1}-1}$，除去 $k=1$ 和 $k=i+j-1$ 的情况，这两种情况用前缀积算上就好了。

最后，$f_{i,j}$ 乘上深度为 $i$ 的点的数量就是这一部分对于答案的贡献了。

#### LCA在端点
这个更好做了，LCA在端点的路径中长度为 $i$ 的只有可能在深度大于 $i$ 的点取到，统计每个深度有多少个点即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5005;
const int mod=1000000007;
int n;
int a[maxn];
int f[maxn][maxn*2],g[maxn*2],inv[maxn];
int power(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)
			ans=1ll*ans*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		scanf("%d",&a[i]),inv[i]=power(a[i]-1,mod-2);
	f[n-1][2]=1ll*a[n-1]*(a[n-1]-1)/2%mod;
	for(int i=n-2;i>=1;i--)
	{
		for(int p=2*n-2;p>=2;p--)
			f[i][p]=1ll*a[i]*(a[i]-1)/2%mod*f[i+1][p-2]%mod*inv[i+1]%mod*2ll%mod*a[i+1]%mod;//从f[i+1][p-2]转移贡献
		//加上k=1和k=i+j-1的贡献
		f[i][2]=(f[i][2]+1ll*a[i]*(a[i]-1)/2%mod)%mod;
		int cnt=1;
		for(int p=3;p<=2*n-2;p++)
		{
			cnt=1ll*cnt*a[i+p-2]%mod;
			f[i][p]=(f[i][p]+1ll*a[i]*(a[i]-1)%mod*cnt%mod)%mod;
		}
	}
	int cnt=1,sum=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=2*n-2;j++)
			g[j]=(g[j]+1ll*cnt*f[i][j]%mod)%mod;//计算对答案的贡献
		sum=(sum+cnt)%mod;
		cnt=1ll*cnt*a[i]%mod;
	}
	cnt=1;int num=0;
	for(int i=1;i<n;i++)
		num=(num+cnt)%mod,g[i]=(0ll+g[i]+sum-num+mod)%mod,cnt=1ll*cnt*a[i]%mod;//LCA在端点的路径
	for(int i=1;i<=2*n-2;i++)
		printf("%d ",g[i]);
	puts("");
	
	return 0;
}
```

---

## 作者：_SeeleVollerei_ (赞：0)

出于个人习惯，我们把原题的 $a_{[1,n-1]}$ 整体平移到 $a_{[2,n]}$。

为了方便，令 $g_{i,j}$ 表示一个深度为 $i$ 的点有多少个深度为 $i+j$ 的子孙，显然这些子孙到这个点的距离为 $j$。

其实我一开始设的是深度为 $j$，没啥区别，只是后面式子里上面的设法会舒服一点。

那么显然有 $g_{i,j}=\prod_{k=i+1}^ja_k$。

我们考虑枚举路径两端的 LCA 的深度 $i$，对于一端就是 LCA 的情况，我们直接将 $g_{i,j}$ 加到 $ans_j$ 即可。

对于剩下的情况，我们可以列出以下式子。

$\binom{a_{i+1}}{2}\sum_{k=0}^jg_{i+1,k}\times g_{i+1,j-k}\to ans_j$。

然后就有了一个 $O(n^3)$ 的做法，考虑优化。

这是一个卷积的形式，我们把这部分单独提出来。

设 $f_{i,j}=\sum_{k=0}^jg_{i,k}\times g_{i,j-k}$。

一个很重要的性质在于 $g_{i,j}=\frac{g_{i-1,j+1}}{a_i}$。

我们发现这个转移和 $j$ 无关。然后每个 $g_{i,j}$ 都有个 $\frac{1}{a_i}$ 意味着 $f_{i,j}$ 整体有一个 $\frac{1}{a_i^2}$。

然后注意 $g_{i-1,j+1}$，相当于集体平移一位，那么对应到 $f_{i,j}$ 就是集体平移两遍。

那么我们把特殊的 $g_{i-1,0}$ 的影响减掉后，有 $f_{i,j}=\frac{f_{i-1,j+2}}{a_i^2}$。

这样，我们就用 $O(n^2)$ 的复杂度求出了 $f_{i,j}$。

https://codeforces.com/contest/954/submission/183982007

---

