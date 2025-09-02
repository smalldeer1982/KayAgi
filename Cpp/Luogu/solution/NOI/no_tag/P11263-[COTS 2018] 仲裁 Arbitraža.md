# [COTS 2018] 仲裁 Arbitraža

## 题目背景



译自 [Izborne Pripreme 2018 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2018/) D2T1。$\texttt{10s,1G}$。


## 题目描述


A 国和 B 国正在划分一块 $n\times m$ 的矩形土地。

显然，这块土地上有 $(n-1)$ 条水平线和 $(m-1)$ 条垂直线。

给这 $(n+m-2)$ 条线分配 $[1,k]$ 间的整数。定义一个格子的**权值**为在它左/上方的线上整数之和减去在它右/下方的线上整数之和。

![](https://cdn.luogu.com.cn/upload/image_hosting/l5bb8lab.png)

给定每个格子权值的要求（要求这个格子的权值 $\lt 0$ 或者 $\gt 0$）。在 $k^{n+m-2}$ 种分配整数的方案中，求出有多少个方案符合要求。

只需要输出答案对 $(10^9+7)$ 取模后得到的结果。

## 说明/提示


对于 $100\%$ 的数据，保证 $1\le n,m,k\le 80$。


| 子任务编号 | $n$ |  $m $ | $k\le$   | 特殊性质 |  得分 |  
| :--: | :--: | :--: | :--: |  :--: |  :--: |
| $ 1 $    | $ \le 10 $    |  $\le 10$ | $ 4$ |  | $ 10 $   |   |
| $ 2 $    | $ \le 80 $   |  $=1$ | $80$ | | $ 10 $   |
| $ 3 $    | $\le20$ | $\le 20$ | $20$  |  | $ 10 $   |  
| $ 4 $    | $\le40$ | $\le 40$ | $40$ |   |$  20 $   |   
| $ 5 $    | $\le79$ | $=n+1$ | $80$ |  A |$  20 $   |   
| $ 6 $    | $\le 80$ | $\le 80$ | $80$ |  |$  30 $   |   


特殊性质 A：$(i,j)$ 要求为 $\texttt{+}$，当且仅当 $i+j\ge m+1$。

## 样例 #1

### 输入

```
4 6 4
-----+
----++
--++++
-+++++```

### 输出

```
2364```

## 样例 #2

### 输入

```
3 3 2
--+
--+
-++```

### 输出

```
2```

## 样例 #3

### 输入

```
2 3 2
---
+++```

### 输出

```
0```

# 题解

## 作者：ForgotMe (赞：2)

答辩 dp 题。

设 $s_{x,y}$ 表示 $(x,y)$ 处的符号。

首先可以看出来 + 号组成了一个阶梯形状，且 $s_{n,1}$ 与 $s_{1,m}$ 一定异号，否则答案一定为 $0$。（规定左上角为 $(1,1)$，右下角为 $(n,m)$。)

设 $a_i,b_i$ 分别表示 $x=i$ 与 $y=i$ 对应直线的权值，初始条件有 $a_1=b_1=0$（根本没有这条直线），那么有位置 $(x,y)$ 的权值为 $2(\sum_{i=1}^xa_i+\sum_{i=1}^yb_i)-(\sum_{i=1}^n a_i+\sum_{i=1}^m b_i)$。

编出一个粗暴的做法是简单的，直接从左下角开始 dp，注意到这个格子的权值是 $\sum_{i=1}^n a_i-\sum_{j=1}^m b_i$，而右上角的值是 $\sum_{i=1}^m b_i-\sum_{i=1}^n a_i$，也就是两者的权值是相反数。那么直接考虑枚举左下角的权值，然后按照 + 号形成的阶梯轮廓做 dp 即可。复杂度高达 $\mathcal{O}((n+m)k^4)$，没有写，不知道能不能过。10 s 感觉很有希望。

考虑换一种思路，注意到一个显然的性质是格子 $(x,y)$ 的权值严格大于其右下方的权值。那么最多只有 $n+m$ 个限制有用，这与最开始的阶梯状结论相互照应，只是这里更加细化了而已。一个 - 号的限制是有用的当且仅当其右下角无 - 号，类似地，一个 + 号的限制是有用的当且仅当其右下角无 + 号。

一个关键 Observation：所有有用的限制对应位置的权值全部在区间 $[-2k,2k]$ 内。这个是容易证明的，给张图就能明白。

![图图可爱](https://cdn.luogu.com.cn/upload/image_hosting/zc5qfd24.png)

图里面打钩的位置就是有用的限制。注意到从 + 号转移到 - 号时一定是先往右走若干步，然后向上走一步切换符号。在这个过程中，往右边走会让权值变大，往上走会让权值变小，所以起始位置的权值必定在 $[-2k,2k]$ 内，否则无法切换符号。从 - 号转移至 + 号同理。

最后一个问题就是左下角与右上角可能不是有用的限制，需要把这两段拼起来。这里可能出现两种情况。

![图图可爱](https://cdn.luogu.com.cn/upload/image_hosting/sr4v3xlw.png)

![图图可爱](https://cdn.luogu.com.cn/upload/image_hosting/bm3pkp12.png)

其中打钩的位置分别是第一个/最后一个有用的限制。

那么现在需要再用一个 dp 去算出左上角/右上角对应权值的方案数。这个是容易算出的，拿第一个有用的限制来说，注意到往左下角靠的时候，数只会变大（如果是 + 号）/变小（如果是 - 号），用一个大小为 $k^2$ 的背包算一下就行。右上角同理。这里的复杂度直接写的话还是五方的（因为要枚举第一个有用的限制对应位置的权值）。优化是容易的，因为第一个限制对应的位置的权值是什么并不重要，只需要知道在往左下角靠的时候权值大了/小了多少对应的方案数即可，这个可以直接预处理，不需要每次重新算。

那么就做完了，时间复杂度 $\mathcal{O}(k^4+(n+m)k^3)$。

直接写五方（不预处理）比四方快/kx。

扔个没啥可读性的代码：https://www.luogu.com.cn/paste/1c43248e

---

## 作者：_lmh_ (赞：0)

给直线赋权值相当于构造两个序列 $\{x_1\dots x_n\}$ 和 $\{y_1\dots y_m\}$ 使得：

$$
x_1+x_n=y_1+y_m=0\\
\forall 1\le i<n,x_i-x_{i-1}\in\{2,4,6\dots 2k\}\\
\forall 1\le i<m,y_i-y_{i-1}\in\{2,4,6\dots 2k\}\\
$$

同时每一组 $x_i+y_j$ 和 $0$ 的大小关系需要满足特定条件。

令 $y'_i=-y_{m-i+1}$，题意转化为：构造序列 $\{x_i\}$ 和 $\{y'_i\}$ 使得

$$
x_1+x_n=y'_1+y'_m=0\\
\forall 1\le i<n,x_i-x_{i-1}\in\{2,4,6\dots 2k\}\\
\forall 1\le i<m,y'_i-y'_{i-1}\in\{2,4,6\dots 2k\}\\
$$

同时每一组 $x_i-y'_j$ 和 $0$ 的大小关系需要满足特定条件。

显然 $x_i>x_{i-1},y'_i>y'_{i-1}$ 这样就可以将限制条件建图。发现这是一个竞赛图，所以如果有解就必定能找到一条唯一的拓扑序。

现在它变成一个序列上的问题，难点在于头尾两个位置互为相反数的条件不好做——直接动态规划求解需要记录一个 $O(nk)$ 的维度，复杂度无法接受。

每个位置的值是 $O(nk)$ 的，但是相邻两数之差是 $O(k)$ 的。而我们还可以发现，对于单独一个序列，只要确定了相邻两数之差，那么每个位置的值都可以确定下来——因为 $0$ 必须是头尾两个数的中点。

因此，这个限制实际上相当于说，$x_1,x_n$ 的中点与 $y_1,y_m$ 的中点相同。

不妨假设 $x_1<y_1<y_m<x_n$（其余情况是类似的），此时先确定 $y_1,y_m$ 的中点，再将 $x_1,x_n$ 的中点调整到那个位置。

找到 $y_1$ 前面第一个 $x$ 和 $y_m$ 后面第一个 $x$，这两个差值都是 $O(k)$ 的，可以直接 dp。然后用剩下的位置调整使得两个中点对齐，就做完了。

用前缀和优化，时间复杂度 $O((n+m)^2+(n+m)k^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200,MOD=1e9+7;
ll n,m,k,l,r,a[N],to[N][N],deg[N],ans,_sum[N<<1],f[2][N],_g[2][N*N*2];
ll *sum=_sum+N,*g[2]={_g[0]+N*N,_g[1]+N*N};
char s[N];
queue<int> q;
void add(int u,int v){to[u][v]=1;++deg[v];}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for (int i=1;i<=n;++i) for (int j=i+1;j<=n;++j) add(i,j);
	for (int i=1;i<=m;++i) for (int j=i+1;j<=m;++j) add(j+n,i+n);
	for (int i=1;i<=n;++i){
		cin>>(s+1);
		for (int j=1;j<=m;++j){
			if (s[j]=='-') add(i,j+n);
			else add(j+n,i);
		}
	}
	for (int i=1;i<=n+m;++i) if (deg[i]==0) q.push(i);
	for (int t=1;t<=n+m;++t){
		if (q.empty()){cout<<0<<endl;return 0;}
		int u=a[t]=q.front();q.pop();
		for (int i=1;i<=n+m;++i) if (to[u][i]) if ((--deg[i])==0) q.push(i);
	}
	for (int i=1;i<=n+m;++i) a[i]=(a[i]>n);
	n+=m;
	if (a[1]!=a[n]){cout<<0<<endl;return 0;}
//	for (int i=1;i<=n;++i) cout<<a[i];cout<<endl;
	l=1;r=n;
	while(a[l]==a[l+1]) ++l;while(a[r]==a[r-1]) --r;
	for (int L=2*k-1;L;--L){
		memset(f,0,sizeof(f));f[0][L]=1;
		int now=1,pre=0;
		for (int i=l+2;i<=r;++i){
			for (int j=1;j<2*k;++j) if (f[pre][j]){
				ll tmp=f[pre][j];f[pre][j]=0;
				if (a[i]==a[i-1]) (f[now][j+2]+=tmp)%=MOD;
				else{
					(f[now][j&1]+=tmp)%=MOD;
					(f[now][2*(k+1)-j]+=MOD-tmp)%=MOD;
				}
			}
			for (int j=2;j<2*k;++j) (f[now][j]+=f[now][j-2])%=MOD;
			f[now][0]=0;
//			cout<<i<<endl;
//			for (int j=1;j<2*k;++j) cout<<f[now][j]<<' ';cout<<endl;
			swap(now,pre);
		}
		for (int R=1;R<=2*k-1;++R) if (f[pre][R]) (sum[(R-L)/2]+=f[pre][R])%=MOD;
	}
//	for (int i=-k;i<=k;++i) cout<<i<<' '<<sum[i]<<endl;
	g[0][0]=1;
	int now=1,pre=0;
	for (int i=l-1;i;--i){
		for (int j=-10000;j<=10000;++j) if (g[pre][j]){
			ll tmp=g[pre][j];g[pre][j]=0;
			(g[now][j+1]+=tmp)%=MOD;
			(g[now][j+k+1]+=MOD-tmp)%=MOD;
		}
		for (int j=-10000;j<=10000;++j) (g[now][j]+=g[now][j-1])%=MOD;
		swap(now,pre);
	}
	for (int i=r+1;i<=n;++i){
		for (int j=-10000;j<=10000;++j) if (g[pre][j]){
			ll tmp=g[pre][j];g[pre][j]=0;
			(g[now][j-k]+=tmp)%=MOD;
			(g[now][j]+=MOD-tmp)%=MOD;
		}
		for (int j=-10000;j<=10000;++j) (g[now][j]+=g[now][j-1])%=MOD;
		swap(now,pre);
	}
	for (int i=-k;i<=k;++i) (ans+=sum[i]*g[pre][i])%=MOD;
	cout<<ans<<endl;
	return 0;
}
```

---

