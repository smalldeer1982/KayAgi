# [PA 2015] Rozstaw szyn

## 题目描述

给定一棵有 $n$ 个点， $m$ 个叶子节点的树，其中 $m$ 个叶子节点分别为 $1$ 到 $m$ 号点，每个叶子节点有一个权值 $r_i$。

你需要给剩下 $n-m$ 个点各指定一个权值，使得树上相邻两个点的权值差的绝对值之和最小。 

## 说明/提示

对于 $100\%$ 的数据，$2\le n\le 5\times 10^5$，$1\le m\le n$，$1\le u,v\le n$，$1\le r_i\le 5\times 10^5$。

## 样例 #1

### 输入

```
6 4
1 5
2 5
3 6
4 6
5 6
5
10
20
40```

### 输出

```
35```

# 题解

## 作者：Richard_Whr (赞：5)

首先来说考虑特殊情况，先考虑叶子往上一个节点，也可以认为是一个菊花。

此时根据经典套路，如果是有奇数个，放在中位数处最优，如果是偶数，放在两个中位数之间任意位置都可以。

用了这么多次结论，我们有没有考虑过到底为什么是这样。

感性理解，甚至是理性证明上，我们都可以发现，如果将位置从中位数往左侧移动 $x$，左侧有 $a$ 个点到该点的距离减小，但右侧会有 $b$ 个点到该点的距离增加。由于是中位数，因此有 $a<b$，答案会变大。

也许这样不够直观，数形结合百般好，画图理解。

定义函数 $f(x)=\sum\limits_{i=1}^{n}|x-x_i|$，其中 $x_i$ 就是第 $i$ 个点的数或者坐标。

我们会发现这是一个分段函数求和的问题，每个函数都是一个绝对值函数，拐点为 $x_i$

画一条平行于 $y$ 轴的直线 $x=x_0$，对所有交点的纵坐标求和就是 $f(x_0)$

![图1](https://cdn.luogu.com.cn/upload/image_hosting/wgsih6ry.png)

中位数保证了左侧上升的函数段和右侧下降的函数段段数相等，因此在偶数时中间位置都可以取到。

那么对于继续往上扩展，儿子的取值范围有可能都是一段区间（他们的儿子个数是偶数），这时候又该怎么办呢。

其实图像上是容易扩展的，我们发现此时对于每一个 $i$ ，他的函数不过发生了略微的改变，形如这样：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/onovv8i6.png)

对于整体来说，会变成这个样子：

![图3](https://cdn.luogu.com.cn/upload/image_hosting/qq8zvklf.png)

那么对于 $L[i],R[i]$ 将 $x_0$ 包含的位置，都是 $0$ 不需要考虑，此时左侧的上升线段和右侧的上升线段仍然相等，回到了刚刚的特殊形式。

我们仍可以利用调整法证明取在所有与拐点的中位数时最优的，且在两个中位数之间任意取值都不会影响总和。

**总结**

对于每个点 $i$ 有取值范围 $L[i] \le x_i \le R[i]$，函数 $f(x)=\sum\limits_{i=1}^{n}\min\limits_{k=L[i]}^{R[i]}|x-k|$ 的最小取值 $x_0$ 为集合 $S=\{L[i],R[i]\}$ 的中位数。

注意特判全部是叶子的阴间情况。

代码就比较简洁了：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
vector<int> e[N];
int w[N];
int L[N],R[N];
int n,m,res;

void add(int a,int b)
{
	e[a].push_back(b),e[b].push_back(a);	
} 

void dfs(int u,int fa)
{
	vector<int> S;
	if(u<=m) return;
	for(auto v:e[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		S.push_back(L[v]),S.push_back(R[v]); 
	}
	sort(S.begin(),S.end());
	int sz=S.size();
	if(sz&1) L[u]=R[u]=S[sz/2];
	else L[u]=S[sz/2-1],R[u]=S[sz/2];
	for(auto v:e[u])
	{
		if(v==fa) continue;
		if(L[u]>R[v]) res+=L[u]-R[v];
		else if(L[u]<L[v]) res+=L[v]-L[u];	
		else res+=0;
	} 
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1,a,b;i<n;i++)
	{
		cin>>a>>b;
		add(a,b);
	}
	
	for(int i=1;i<=m;i++) cin>>w[i],L[i]=R[i]=w[i];
	
	if(n==2) 
	{
		cout<<abs(w[1]-w[2])<<"\n";
		return 0;
	}
	
	dfs(m+1,0);
	
	cout<<res<<"\n";
	
	return 0;
} 
```

---

## 作者：Prean (赞：3)

~~贪心和DP一样，上来先找规律~~

考虑一种特殊情况：菊花图。

很容易发现这是小学数学题，排序后取中点。

来考虑另一种情况：深度为 3 的完全二叉树。

假设这颗完全二叉树的节点编号是按照线段树编号的，给定权值的节点是 4 5 6 7。方便起见，设 $ v_u $ 为编号为 $ u $ 的节点的权值，且有 $ v_5>v_4,v_7>v_6 $。

很容易发现 $ v_3 $ 取值范围是 $ [v_4,v_5] $，$ v_4 $ 的取值范围是 $ [v_6,v_7] $。

那么 $ v_1 $ 呢？

分类讨论。

1. $ v_5 \leq v_6 $ 很明显是 $ [v_5,v_6] $。
2. 两个区间相交 很明显取值范围就是区间的交。

有没有一点儿思路了？

再来看看一种情况（下面设节点 $ u $ 的取值范围是 $ [l_u,r_u] $）：

节点 $ u $ 有三个儿子 $ a,b,c $，且 $ l_a \leq l_b,r_b \leq r_a,r_a \leq l_c $ （也就是 $ a $ 包含了 $ b $）

取值范围明显是 $ [r_b,r_a] $。

所以最终思路是：将儿子的取值范围的左右端点全部拉出来，排序后取最中间的两个作为该节点的取值范围。

记得特判 $ n=m=2 $ 的阴间情况（
```cpp
#include<algorithm>
#include<cstdio>
const int M=5e5+5;
int n,m,cnt,f[M],h[M],l[M],r[M];int len,tmp[M<<1];long long ans;
struct Edge{
	int v,nx;
}e[M<<1];
inline void Add(const int&u,const int&v){
	e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
	e[++cnt]=(Edge){u,h[v]};h[v]=cnt;
}
void DFS(const int&u){
	for(int v,E(h[u]);E;E=e[E].nx)if((v=e[E].v)^f[u])f[v]=u,DFS(v);
	for(int v,E(h[u]);E;E=e[E].nx)if((v=e[E].v)^f[u])tmp[++len]=l[v],tmp[++len]=r[v];
	if(!e[h[u]].nx)return;std::sort(tmp+1,tmp+len+1);l[u]=tmp[len>>1];r[u]=tmp[(len>>1)+1];len=0;
	for(int v,E(h[u]);E;E=e[E].nx)if((v=e[E].v)^f[u])ans+=l[u]>r[v]?l[u]-r[v]:l[u]<l[v]?l[v]-l[u]:0;
}
signed main(){
	int i,u,v;scanf("%d%d",&n,&m);
	for(i=1;i<n;++i)scanf("%d%d",&u,&v),Add(u,v);for(i=1;i<=m;++i)scanf("%d",&u),l[i]=r[i]=u;
	if(n==2)return!printf("%d",l[1]>l[2]?l[1]-l[2]:l[2]-l[1]);
	DFS(n);printf("%lld",ans);
}
```

---

## 作者：ycy1124 (赞：0)

### 题意
给出一个 $n$ 个节点，$m$ 个叶子节点的树，每个叶子节点都有一个定值 $w_i$，试求在其他节点可以填任意值时树上相邻节点的差之和最小为多少。
### 思路
我们考虑随便从一个节点往下枚举。假如一个节点的所有子节点都为叶子节点，那么这个点的值就为他子节点权值的中位数，如果子节点个数为偶数个，那么它的取值范围就在两个中位数之间。这里简单证明一下，当我们取中位数时，它左右两边的值得个数相等，所以无论我们将取值往中位数左或者右边移动他的差之和只会变大。

接下来考虑当一个节点的子节点的权值不确定时怎么办。我们可以取它所有子节点的取值范围的 $l_i,r_i$ 的中位数。证明，我们此时可以将所有子节点的取值看作一些区间。当我们取中位数时，除去包含中位数的区间外，左右两边区间个数相等。此时我们向左向右移动差之和只会增加。

最后，在我们求完所有节点的取值范围后，将根节点的值随意，子节点取取值范围内与父亲节点权值差较小的值。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,tot;
int l[500005],r[500005],qwq[1000005];
vector<int>a[500005];
void dfs(int p,int f){
	if(l[p]||r[p]){//叶子节点退出
		return;
	}
	for(auto it:a[p]){
		if(it!=f){
			dfs(it,p);//先处理子节点
		}
	}
	tot=0;
	for(auto it:a[p]){
		if(it!=f){
			qwq[++tot]=l[it];
			qwq[++tot]=r[it];
		}
	}
	sort(qwq+1,qwq+tot+1);
	l[p]=qwq[tot/2];
	r[p]=qwq[tot/2+1];
}
void Dfs(int p,int f){
	if(r[p]<=l[f]){
		l[p]=r[p];
	}
	else if(r[p]>=l[f]&&l[p]<=l[f]){
		l[p]=l[f];
	}
	for(auto it:a[p]){
		if(it==f){
			continue;
		}
		Dfs(it,p);
		ans+=abs(l[p]-l[it]);//累加答案
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1;i<=m;i++){
		cin>>l[i],r[i]=l[i];
	}
	if(m!=n){
		dfs(m+1,m+1);
		Dfs(m+1,m+1);
	}
 	else{
		Dfs(1,1);
	}
	cout<<ans;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/218198138)。

---

## 作者：_lbw_ (赞：0)

观察题面，问题即为有若干 $r$ 已知，确定剩下的 $r$ 使得树上有连边点差的绝对值尽可能小。

考虑费用流对偶。

问题为 $\min \sum\limits_{(u,v)}|r_u-r_v|$，转化为 $\min\sum\limits_{(u,v)}\max(r_u-r_v,0)+\max(r_v-r_u,0)$

这是费用流对偶的形式，剩下的问题是有一些 $r$ 是确定的。

根据套路考虑加入源汇 $S,T$，令 $r_T\leq r_S$。

再对于每个确定的 $r_i$ 连边 $(S,i,r_i),(i,T,-r_i)$ 流量上限为 $\infty$，等价于限制：

$$r_S+r_i\leq r'_i$$
$$r'_i-r_i\leq r_T$$

于是得到 $r_S=r_T,r'_i=r_S+r_i$，与原问题等价。

我们重新书写问题，即为求下图的最大费用流：

- $(S,i,\infty,r_i)$
- $(i,T,\infty,-r_i)$
- $(u_i,v_i,1,0)$

立即考虑模拟费用流与启发式合并结合，自下而上的做。

维护两个堆，分别为流向 $S$ 和 $T$ 的边，在每次 dfs 返回时做截断至两个堆的大小均 $\leq 1$ 即可。

对于每个节点，启发式合并（其实直接 push 就好了）它的所有出边堆，合并后加入当前节点，直接匹配，匹配成功要加入反边。

时间复杂度 $\mathcal{O}(n\log n)$。


[P5992](https://www.luogu.com.cn/paste/dw00b21r)

---

## 作者：Prophesy_One (赞：0)

对于一个只有叶子作为儿子的点，设其儿子权值序列为 $v_1,v_2,\cdots,v_k$，那么选其中位数 $p$ 一定能使 $\sum_{i=1}^k|v_i-p|$ 最小。

证明大概就是在数轴上取两个关于中位数下标对称的点 $a_i,a_j(i<j)$，两个点到一个定点 $v$ 的距离满足 $|v-a_i|+|a_j-v| \geq a_j-a_i$，那么取一个位于 $a_i,a_j$ 之间的数即可。对应的，所有对称的 $i,j$ 都满足这个规律，那么取中位数最优。

但若 $k$ 为偶数，中位数取值便是一个区间，于是我们需要考虑对于一个儿子权值二元组序列 $(l_i,r_i)$，如何取值 $(l_u,r_u)$ 使答案最优。

我们发现对于权值 $v$，可以看做区间 $[v,v]$。类似于权值的思路，我们将所有 $l_i,r_i$ 放在一起排序，那么 $l_u,r_u$ 取该序列的两个中位数最优。

在 $\text{dfs}$ 过程中统计答案即可。

特判 $n=2$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=5e5+5;
struct edge
{
	int next,to;
}e[N<<1];
long long ans;
int n,m,cnt,in[N],le[N],ri[N],b[N<<1];
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch^48;
	while((ch=getchar())>='0'&&ch<='9')
	res=(res<<1)+(res<<3)+(ch^48);
	return res*f;
}
void add(int x,int y)
{
	e[++cnt].next=in[x];
	e[cnt].to=y;
	in[x]=cnt;
}
void dfs(int u,int fa)
{
	if(le[u]&&ri[u])
	return;
	int i,v,x,tot=0;
	for(i=in[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa)
		continue;
		dfs(v,u);
	}
	for(i=in[u],tot=0;i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa)
		continue;
		b[++tot]=le[v];b[++tot]=ri[v];
	}
	x=tot/2;
	sort(b+1,b+tot+1);
	le[u]=b[x];ri[u]=b[x+1];
//	printf("%d %d\n",le[u],ri[u]);
	for(i=in[u];i;i=e[i].next)
	{
		v=e[i].to;
		if(v==fa)
		continue;
		//le_v </=/> le_u 
		ans+=le[u]>ri[v]?le[u]-ri[v]:le[u]>=le[v]?0:le[v]-le[u];
	}
}
int abs(int x)
{
	return x>=0?x:-x;
}
int main()
{
	int i,x,y;
	n=read();m=read();
	for(i=1;i<=n-1;i++)
	{
		x=read();y=read();
		add(x,y);add(y,x);
	}
	for(i=1;i<=m;i++)
	le[i]=ri[i]=read();
	if(n==2)
	{
		printf("%d",abs(le[2]-le[1]));
		return 0;
	}
	dfs(n,0);
	printf("%lld",ans);
	return 0;
}
```

---

