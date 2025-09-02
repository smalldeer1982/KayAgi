# [ICPC 2020 Shanghai R] Fountains

## 题目描述

假设你和你的队友 Mixsx 将参加 Namomo 训练营。Namomo 训练营将持续 $n$ 天。我们将第 $i$ 天命名为第 $i$ 天（$1 \le i \le n$）。第 $i$ 天的费用为 $s_i$。

不幸的是，Namomo 训练营的日程与 Mixsx 的期末考试冲突。Mixsx 在从第 $L$ 天到第 $R$ 天的每一天都有期末考试。他的大学尚未宣布 $L$ 和 $R$ 的确切值，因此我们假设每对整数 $L$ 和 $R$ 满足 $1 \le L \le R \le n$ 的情况将以概率 $1/(n(n+1)/2)$ 被选择。他决定参加所有考试，因此将从第 $L$ 天到第 $R$ 天缺席 Namomo 训练营。在这种情况下，他的损失将是 $\sum_{i=L}^R s_i$。

作为 Mixsx 的队友，你希望 Mixsx 放弃他的期末考试并回到 Namomo 训练营。在 $L$ 和 $R$ 公布之前，你可以准备 $k$ 个计划。在第 $i$ 个计划中（$1 \le i \le k$），你每天从第 $l_i$ 天到第 $r_i$ 天关闭他的大学的电源。你可以选择 $l_i$ 和 $r_i$ 的值，只要它们是满足 $1 \le l_i \le r_i \le n$ 的两个整数。

一旦 $L$ 和 $R$ 被宣布，你可以选择一个计划 $x$（$1 \le x \le k$），使得 $L \le l_x \le r_x \le R$。然后 Mixsx 将在从第 $l_x$ 天到第 $r_x$ 天的每一天回到 Namomo 训练营。在这种情况下，他的损失变为 $\sum_{i=L}^R s_i - \sum_{i=l_x}^{r_x} s_i$。你将选择一个计划以最小化 Mixsx 的损失。如果没有计划 $x$ 满足 $L \le l_x \le r_x \le R$，Mixsx 将正常参加他的期末考试，他的损失是 $\sum_{i=L}^R s_i$。

请计算如果你选择 $k$ 个计划最优地，Mixsx 的最小可能期望损失 $ans_k$。输出每个从 $1$ 到 $n(n+1)/2$ 的 $k$ 的 $ans_k \cdot n(n+1)/2$。

形式上，给定一个 $n$ 个数字 $s_i$ 的列表（$1 \leq i \leq n$），定义损失函数 $C(L, R) = \sum_{i=L}^R s_i$。给定一个整数 $k$（$1 \leq k \leq n(n+1)/2$），你应该选择 $2k$ 个整数 $l_1, \ldots, l_k, r_1, \ldots, r_k$ 满足对于所有 $1 \leq i \leq k$，$1 \le l_i \le r_i \le n$，使得

$$\sum_{1 \leq L \leq R \leq n} \left[C(L, R) - \max_{1 \le i \le k, L \leq l_i \leq r_i \leq R} C(l_i, r_i) \right]$$

被最小化。（如果没有 $i$ 满足 $1 \le i \le k$ 且 $L \leq l_i \leq r_i \leq R$，则 $\max_{1 \le i \le k, L \leq l_i \leq r_i \leq R} C(l_i, r_i)$ 定义为 $0$。）输出每个整数 $k$ 在 $[1, n(n+1)/2]$ 中的最小化值。

## 说明/提示

对于第一个测试用例，我们只需要考虑 $k = 1$ 的情况。我们只能选择 $l_1 = r_1 = 1$。然后期望损失是 $C(1, 1) - C(1, 1) = 0$，结果是 $0 \times 1 \times (2) / 2 = 0$。

对于第三个测试用例，考虑 $k = 3$ 的情况。我们选择 $l_1 = r_1 = 1$，$l_2 = r_2 = 3$ 和 $l_3 = 1, r_3 = 3$。期望损失是 $2$。结果是 $2 \times 6 = 12$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
1```

### 输出

```
0```

## 样例 #2

### 输入

```
2
13 24```

### 输出

```
26
13
0```

## 样例 #3

### 输入

```
3
6 4 7```

### 输出

```
33
21
12
8
4
0```

# 题解

## 作者：lzqy_ (赞：1)

场上过了 $F$ 但是没过 $L,H$，我玩原神吗。

这个 $n \le 9$ 看上去就很暧昧，基本上发现一两个性质就能做了。

考虑当选取的区间确定之后怎么做。将它从大到小排序，依次贪心覆盖就是对的。

如果将 $L,R$ 按照 $L$ 分类，那么注意到每次覆盖的都是若干个 $L$ 所对应的一段后缀。换句话说，一个 $L$ 对应的未被覆盖的 $R$ 时刻都是一段前缀。

所以对于一个 $L$，只需要存一个指针表示前缀即可。

感觉这个性质已经很强了，摁状态数 DP 然后就过了。

注意，为了让上述发现的性质起作用，要在转移中钦定选择区间的顺序一定是从大到小，否则就会退化成纯暴力 DP。

（但即使纯暴力 DP 也跑得过 $n \le 8$ /cf）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int p=1e7+7;
const ll inf=1ll<<60;
const int maxs=1000010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x; 
}
il void chkmin(ll &x,ll y){if(y<x)x=y;}
int s[10],n,k;
struct info{
	int a[10],c; 
	int val(ll sum=0){
		for(int i=1;i<=n;i++)
			sum*=n+1,sum+=a[i];
		return sum%p;
	}
	bool operator ==(info x)const{
		for(int i=1;i<=n;i++)
			if(a[i]!=x.a[i]) return 0;
		return 1;
	}
};
struct edge{
	info v;
	int c,to;
}e[2][maxs];
int head[2][p],ecnt[2];
int Find(int t,info x,int c){
	int v=x.val();
	for(int i=head[t][v];i;i=e[t][i].to)
		if(e[t][i].v==x&&e[t][i].c==c) return i;
	e[t][++ecnt[t]].v=x,e[t][ecnt[t]].c=c;
	e[t][ecnt[t]].to=head[t][v],head[t][v]=ecnt[t];
	return ecnt[t];
}
pair<int,int>st[100];
ll f[2][maxs];
ll p1[10],p2[10];
ll lim[100],top;
ll sum[100];
ll renew(info &t,int l,int r){
	ll sum=0;
	for(int i=1;i<=l;i++)
		if(t.a[i]>=r){
			sum+=(t.a[i]-r+1)*(p1[r]-p1[l-1]);
			t.a[i]=r-1;
		}
//	printf("!!!%d\n",sum);
	return sum;
}
ll calc(info t){
	ll sum=0;
	for(int i=1;i<=n;i++)
		sum+=(p2[t.a[i]]-p2[i-1])-(t.a[i]-i+1)*p1[i-1];
	return sum;
} 
bool cmp(pair<int,int>x,pair<int,int>y){
	return p1[x.second]-p1[x.first-1]>p1[y.second]-p1[y.first-1];
}
int main(){
	n=read(),k=n*(n+1)/2;
	for(int i=1;i<=n;i++)
		s[i]=read(),p1[i]=p1[i-1]+s[i];
	for(int i=1;i<=n;i++)
		p2[i]=p2[i-1]+p1[i];
	for(int i=1;i<=k;i++)
		lim[i]=inf;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			st[++top]=make_pair(i,j);
	sort(st+1,st+1+top,cmp);
//	for(int i=1;i<=top;i++)
//		printf("(%d,%d)\n",st[i].first,st[i].second);
	info t,M;
	memset(f,127,sizeof(f));
	for(int i=1;i<=n;i++) t.a[i]=n;
	int i1,i2; ll sum=0;
	for(int i=1;i<=n;i++) sum+=p2[n]-p2[i-1]-(n-i+1)*p1[i-1];
	f[0][Find(0,t,0)]=sum;
	for(int i=1;i<=k;i++){
		i1=i-1&1,i2=i&1,sum=0;
//		printf("!!!%d\n",ecnt[i1]);
		for(int j=1;j<=ecnt[i1];j++){
			for(int u=e[i1][j].c+1;u<=top;u++){
					t=e[i1][j].v;
//					printf("!!!%d\n",e[i1][j].c);
					sum=renew(t,st[u].first,st[u].second); 
					chkmin(f[i2][Find(i2,t,u)],f[i1][j]-sum);
					lim[i]=min(lim[i],f[i2][Find(i2,t,u)]);
				}
		}
		for(int j=1;j<=ecnt[i1];j++)
			f[i1][j]=inf,head[i2][e[i2][j].v.val()]=0;
		printf("%lld\n",lim[i]);
	}
	return 0;
}
```

---

## 作者：chen_zhe (赞：1)

以下内容转载自官方题解：

先考虑所有 $\mathrm{weight} = 1$ 的情况。把每个区间 $(L, R)$ 看成平面上 $x = L, y = R$ 的一个点。一个区间包含另一个即前者在后者左上方。那么可以斜角按 $R - L$ 由大到小 dp，维护考虑了 $\frac{n\times (n+1)}{2}$ 个区间中的前 $i$ 个时，选择了 $j$ 个区间，并且没有被覆盖到的区间形成的边界线是 $n \geq a_1 \geq a2 \geq \dots \geq a_n \geq 0$ 时的花费。边界线总情况是 $2n$ 选 $n$，总共的 $\mathrm{state}$ 大概是 $(\frac{n(n+1)}{2})^2 \times \binom{2n}{n}$。转移可以 $O(n)$ 实现。

加上 $\mathrm{weight}$ 之后，实际是考虑点 $\mathrm{prefix}_{L-1}$ 和 $\mathrm{prefix}_{R}$, 实现时只需要按照区间 $(L,R)$ 的 $\mathrm{weight}$ 排序，由大往小做即可。

---

## 作者：xzy090626 (赞：0)

## Analysis

题意大概就是给定长为 $n$ 的序列 $s$，对于每个 $k\in [1,{n(n+1)\over 2}]$，选出 $k$ 个区间，使得原序列的每个子区间的区间和减去 $k$ 个区间中被该子区间完全包含的区间和的最大值之和最小。

由于 $n\le 9$，显然 dp 是比较合理的想法，但是显然直接做是不行的，我们考虑如何优化 dp 状态。

我们考虑当选出了所有 $k$ 个区间之后如何选择，使得每个子区间贡献最小。显然将这 $k$ 个区间贪心地从大到小排序，找出第一个完全覆盖的区间即可。

现在，dp 状态可以这样定义：我们让状态为目前选了 $i$ 个区间，再加上一维即仍未处理的子区间的状态。

由于刚刚所说的贪心选取覆盖区间的做法，我们很容易注意到对于一个 $l\in[1,n]$，以它为左端点的未处理的区间一定是连续的。也即，如果存在以 $l$ 为区间左端点的未处理的子区间，那么一定存在一个 $r\in[l,n]$ 使得对于所有 $l\le p \le r$，$[l,p]$ 这个子区间并没有被处理。这是因为更大的区间会更可能覆盖 $k$ 个区间中的一个。

那么这个状态可以定义为 $f(x,\{r_i\})$ 为目前选了 $x$ 个区间，子区间处理状态为 $\{r_i\}$。考虑到 $r_i\ge i-1$（当然，$r_i=i-1$ 指的是不存在未处理的子区间的情形）且 $r$ 单调不递减，这个状态的规模大概是 $O(n^2n!)$。

这样看起来不太容易跑过去。但是我们算一下具体的运算次数，爆搜一下发现合法的状态数大概是 $5\times10^5$ 级别的（不一定准确），再加上 6 秒的时间限制，可以用 `map` 来做。

---

