# [CERC2017] Gambling Guide

## 题目描述

一个铁路系统由 $n$ 个城市和 $m$ 条双向铁路组成。铁路票只能在安装在每个城市的自动售票机购买。不幸的是，黑客们已经篡改了这些售票机，现在它们有下面的规则：

当 $a$ 市的售票机有一个硬币投入时，机器会发一张从 $a$ 市到随机一个邻市的单程票。

你需要从城市 $1$ 到城市 $n$。你知道机器是怎么工作的并且有一份铁路系统的地图。在每一个城市，当你买了一张票时，你可以选择立即使用它后到达目的地，或者是丢掉它并买一张新票。你可以无限制的购买的票。当你到达城市 $n$，旅行就会结束。

你需要确定一个满足以下条件的策略：

- 旅行最终到达终点的概率为 $1$。

- 花在旅行上的硬币的期望值越少越好。

输出这个期望值。

## 样例 #1

### 输入

```
4 4
1 2
1 3
2 4
3 4```

### 输出

```
3.0000000000```

## 样例 #2

### 输入

```
5 8
1 2
1 3
1 4
2 3
2 4
3 5
5 4
2 5```

### 输出

```
4.1111111111
```

# 题解

## 作者：Peter0701 (赞：12)

## 题意

给定一张 $n$ 个点， $m$ 条边的无边权的无向图。有一人从 $1$ 号点出发，可以随机向一个和当前直接相连的点走去，花费 $1$ 的代价；也可以不动，重新随机一个点，也花费 $1$ 的代价。求到达 $n$ 点时的最小总花费。答案四舍五入保留 $6$ 位小数。

## 解法

根据期望 $dp$ 的一般设计方法，因为只有一个终点，且状态已知（期望花费为 $0$ ），因此考虑逆推。

自然地，设 $f_x$ 表示点 $x$ 到终点的期望花费。用 $E$ 表示边集， $deg_x$ 表示 $x$ 点的度数，则有 $f_x=\frac{ \sum \min \{ f_x,f_y \} }{deg_x}+1$ （边 $(x,y)$ 在 $E$ 内）。

那么，对于一个点 $x$ 来说，能对它的期望产生贡献的相邻的点 $y$ 必然有 $f_y<f_x$ 。

一开始不妨令所有的 $x$ 点在计算 $ \min \{ f_x,f_y \}$ 时都为 $f_x$ （下文会证明确实只会出现这种情况）。

假设这样的 $y$ 点有 $cnt_x$ 个，则有 $f_x=\frac{ \sum f_y}{deg_x}+ \frac{(deg_x-cnt_x) \times f_x}{deg_x}+1=\frac{ \sum f_y}{deg_x}+(1- \frac{cnt_x}{deg_x} ) \times f_x+1$ （边 $(x,y)$ 在 $E$ 内且 $f_y<f_x$ ）。

因此，果断求出 $ \sum f_y $ （边 $(x,y)$ 在 $E$ 内且 $f_y<f_x$ ），记为 $sum_x$ ，则 $f_x=\frac{sum_x}{deg_x}+(1- \frac{cnt_x}{deg_x} ) \times f_x+1$ ，化简得 $f_x= \frac{deg_x+sum_x}{cnt_x}$ 。

也就是说，只要相连的 $x,y$ 两点满足 $f_y<f_x$ ，我们就可以利用 $f_y$ 来更新 $f_x$ 的值。

是不是很像堆优化的 $dijkstra$ 的松弛操作呢？时间复杂度与堆优化的 $dijkstra$ 相同，为 $O((m+n)logn)$ 。

##  $trick$ 

$1.$ 利用 $f_y$ 来更新 $f_x$ 的值的算法正确性证明：
设更新后的 $x$ 点的 $f$ 值为 $f_x'$ ， $f_x-f_y=\Delta$ （显然 $\Delta>0$ ）。

由上文推出的式子得 $f_x= \frac{deg_x+sum_x}{cnt_x}$ ，更新后有 $f_x'= \frac{deg_x+sum_x+f_y}{cnt_x+1}$ ，两者相减并化简得 $f_x-f_x'=\frac{\Delta}{cnt_x+1}$ ，则 $f_x-f_x'=\frac{f_x-f_y}{cnt_x+1}$ ，即 $0<f_x-f_x'<f_x-f_y$ ，也即 $f_x>f_x'>f_y$ 。

因此每一次松弛操作不会使得 $f_x$ 变大，也不会使得其小于 $f_y$ 。证毕。

$2.$ 一个非常用不经典套路：对于确定的初始状态仅有极少数（大多数时候仅有一个），其余的状态与相邻的部分（大多数时候是相邻的点）有关的dp，考虑（放到图上）以最短路的方式进行转移。

## 细节

$1.$ 请注意堆的第一维数据类型是 $double$ 。

$2.$ 请注意本题是无向图，要双向建边、双向记度数。

$3.$ 请特别注意标记数组的使用和判断：每个点在自己更新完所有的点后就不能再被更新（因为此时已经是能达到的最小的值了）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int n,m,u,v,w;
int num,head[600005],deg[300005],cnt[300005];
double f[300005],sum[300005];
bool vis[300005];
priority_queue<pair<double,int> > q;
struct edge
{
	int ver,nxt;
}e[600005];
inline void adde(int u,int v)
{
	e[++num].ver=v;
	e[num].nxt=head[u];
	head[u]=num;
}
inline void dijkstra()
{
	q.push(make_pair(0,n));
	while(!q.empty())
	{
		int x=q.top().second;
		q.pop();
		if(vis[x])
			continue;
		vis[x]=1;
		for(register int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].ver;
			if(vis[y])
				continue;
			cnt[y]++;
			sum[y]+=f[x];
			f[y]=(deg[y]+sum[y])/cnt[y];
			q.push(make_pair(-f[y],y));
		}
	}
}
int main()
{
	n=read();
	m=read();
	for(register int i=1;i<=m;i++)
	{
		u=read();
		v=read();
		adde(u,v);
		adde(v,u);
		deg[u]++;
		deg[v]++;
	}
	dijkstra();
	printf("%0.7lf\n",f[1]);
	return 0;
}
```

---

## 作者：银翼的魔术师 (赞：11)

Dijkstra+期望DP。

设$d_u$为节点$u$的度数，$f_u$为从$u$到$n$的期望最小时间（注意：是倒序进行转移），显然有：

$$f_u=1+\frac{1}{d_u}\sum_{(u,v)\in E}min(f_u,f_v)$$

应按$f$从小到大依次确定。

记$c_u$为与$u$相邻的已经确定的点的个数，则有：

$$f_u=1+(1-\frac{c_u}{d_u})f_u+\frac{1}{d_u}\sum_{(u,v)\in E,f_v<f_u}f_v$$

即：

$$f_u=\frac{d_u+\sum_{(u,v)\in E,f_v<f_u}f_v}{c_u}$$

图上求最小值，考虑Dijstra来实现转移。

即我们每次从还未确定$f$的点中选取拥有最小$f$的点$u$，$f_u$确定，再用$f_u$来更新与$u$相邻的点。

下面给出了上面的转移可以通过Dijkstra来实现转移的证明：

设更新之后得到$f_{v^{'}}$，将$f_v$和$f_{v^{'}}$代入上面的状态转移方程，可以得到$f_v-f_{v^{'}}=\frac{f_v-f_u}{c_v+1}$，所以$0<f_v-f_{v^{'}}<f_v-f_u$，即$f_v>f_{v^{'}}>f_u$。

因为Dijkstra是按从小到大依次确定的，所以这种转移是按$f$从小到大依次确定的。

时间复杂度$O(mlogm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int fr[N],ne[N+N],t[N+N],c,b[N],n;
double f[N];
bool v[N];
priority_queue<pair<double,int> >q;
void add(int a,int b)
{
	ne[++c]=fr[a];
	fr[a]=c;
	t[c]=b;
}
void dj()
{
	int u;
	f[n]=0;
	b[n]=1;
	q.push(pair<double,int>(0,n));
	for(int i=1;i<=n;i++)
	{
		do
		{
			if(q.empty())
				return;
			u=q.top().second;
			q.pop();
		}while(v[u]);
		v[u]=1;
		for(int j=fr[u];j;j=ne[j])
			if(!v[t[j]])
			{
				b[t[j]]++;
				f[t[j]]+=f[u]/(double)b[u];
				q.push(pair<double,int>(-f[t[j]]/(double)b[t[j]],t[j]));
			}
	}
}
int main()
{
	int m,a,h;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&h);
		add(a,h);
		add(h,a);
		f[a]++;
		f[h]++;
	}
	dj();
	printf("%.10lf",f[1]/(double)b[1]);
}
```

---

## 作者：dspt (赞：3)

## 前言
非常显然的，最短路 + 期望。

期望一般用期望 DP 求解，这里放到图上处理也是相似的，从终点向起点处理。  
&nbsp;
## 状态转移方程
假设当前处理到点 $p$，$p$ 的期望为 $f_p$。

考虑与 $p$ 有边相连的任意一点 $q$，如果 $f_q<f_p$
，那么点 $q$ 肯定会影响点 $p$ 的答案。

如何影响？在走到点 $p$ 时下一步走点 $q$。

当从点 $n$ 开始的遍历遍历到点 $p$ 时，已经遍历过的点的 $f$ 一定小于 $f_p$，未遍历的点 $f$ 一定大于 $f_p$。

为什么我们可以保证这个性质？因为我们试着考虑最短路，会发现每一个已经遍历过的点与根的距离一定小于一个没有遍历过的点，这是它的正确性。

假设所有 $f_i<f_p(1\leqslant i\leqslant n)$ 中 $i$ 构成的点集称为 $S$，点集大小为 $c$。

那么走到点 $p$ 时肯定走 $S$ 中的点是最优的。

若有 $k$ 个点与 $p$ 相连，那么抽到 $S$ 中的点的概率是 $\frac ck$。其中每一个点的期望为 $\frac 1c\sum_{i\in S}f_i$。

那么可以得到一个式子：
$$
\begin{aligned}
f_p&=\frac ck\sum_{i\in S}\frac{f_i}{c}+\frac{k-c}k\cdot f_p+1\\
kf_p&=\sum_{i\in S}f_i+(k-c)f_p+k\\
cf_p&=\sum_{i\in S}f_i+k\\
f_p&=\frac{\sum_{i\in S}f_i+k}c
\end{aligned}
$$

其中 $1$ 是到了点 $p$ 买的票第一张票（必买的），$\frac ck\sum_{i\in S}\frac{f_i}c$ 是走到 $S$ 中的点的期望，$\frac{k-c}k f_p$ 是重新买票的期望。三个期望累加就是 $f_p$ 。  
&nbsp;
## 最短路
考虑我们要求的是 $\min f_1$。众多最短路中，Dijkstra 堆优化是比较合适的。写一个大根堆维护每一个已处理点的 $f$ 值。

将堆优化 Dijkstra 拿来进行一些修改，用 $f$ 代替最短路建大根堆。实质上 $f$ 与最短路是一样的。  
&nbsp;
## 代码
```cpp
#include <queue>
#include <stdio.h>
using namespace std;
priority_queue<pair<double, int>> q; // <fp, point>
const int _(300005); vector<int> E[_];
bool v[_]; int n, m, a, b, c[_]; double sum[_], f[_];
inline void Dijkstra()
{
    q.push(make_pair(0, n));
    while (!q.empty())
	{
        int p(q.top().second); q.pop();
        if (v[p]) continue; v[p] = true;
        for (int i : E[p]) if (!v[i])
		{
            ++c[i]; sum[i] += f[p];
            f[i] = (E[i].size() + sum[i]) / c[i];
            q.push(make_pair(-f[i], i));
		}
	}
}
int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
	{
        scanf("%d%d", &a, &b);
        E[a].emplace_back(b); E[b].emplace_back(a);
    }
	Dijkstra();
    printf("%.10f\n", f[1]);
    return 0;
}
```

---

## 作者：hzoi_liuchang (赞：3)

## 分析

按照期望题一般的做法，我们设 $f[u]$ 为从 $u$ 走到终点 $n$ 的期望花费

设 $du[u]$ 为节点 $u$ 的出度

那么 $f[u]= \frac{\sum_{u->v} min(f[u],f[v])}{du[u]}+1$

我们会发现这个式子既包含 $f[u]$ 本身又包含与 $f[u]$ 相邻的点 $f[v]$

不好直接转移

但是我们可以确定，如果 $f[v]<f[u]$ ，那么 $f[v]$ 一定会对 $f[u]$ 做出贡献

因此，我们可以利用 $Dij$ 的思想开一个小根堆，每次取出最小的来更新其它的

因为当前的值是最小的，所以一定不会有其它的点可以影响它

我们设 $u$ 被与它相邻的点的 $f$ 值更新了 $cnt$ 次，这些值的和为 $sum$

则 $f[u]=\frac{sum+(du[u]-cnt[u]) \times f[u]}{du[u]}+1$

整理可得 $f[u]=\frac{sum+du[u]}{cnt}$

## 代码
``` cpp
#include<cstdio>
#include<cstring>
#include<queue>
const int maxn=6e5+5;
inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
int head[maxn],tot=1;
struct asd{
	int to,next;
}b[maxn];
void ad(int aa,int bb){
	b[tot].to=bb;
	b[tot].next=head[aa];
	head[aa]=tot++;
}
struct jie{
	int num;
	double jl;
	jie(){}
	jie(int aa,double bb){
		num=aa,jl=bb;
	}
	bool operator < (const jie &A) const{
		return jl>A.jl;
	}
};
int n,m,du[maxn],cnt[maxn];
double sum[maxn],f[maxn];
bool vis[maxn];
std::priority_queue<jie> q;
void dij(){
	q.push(jie(n,0));
	while(!q.empty()){
		int now=q.top().num;
		q.pop();
		if(vis[now]) continue;
		vis[now]=1;
		for(int i=head[now];i!=-1;i=b[i].next){
			int u=b[i].to;
			if(vis[u]) continue;
			cnt[u]++;
			sum[u]+=f[now];
			f[u]=(du[u]+sum[u])/cnt[u];
			q.push(jie(u,f[u]));
		}
	}
}
int main(){
	memset(head,-1,sizeof(head));
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int aa,bb;
		aa=read(),bb=read();
		ad(aa,bb);
		ad(bb,aa);
		du[aa]++,du[bb]++;
	}
	dij();
	printf("%.10f\n",f[1]);
	return 0;
}

```

---

## 作者：WeLikeStudying (赞：2)

- 当时记录的思路，感觉很有用，姑且记录下来。

**问题**
- 有 $n$ 个 $m$ 元线性方程组：判断它的解的情况（无解，无数解，有唯一解），如何是好呢？
- 也就是说，设 $n$ 元列向量 $y$，和 $n\times m$ 的矩阵 $A$，求 $m$ 元列向量 $x$，使得：
$$Ax=y$$
- 不过这显然是没有必要的，我们可以只需要用式子来推导即可。
- 高斯消元的核心思想即对于每个式子都找到一个代表元，然后让其它的式子都不存在这个代表元，显然，由于涉及乘除法，我们不希望代表元的系数太小。
- 所以我们可以写出如下实现：寻找第 $i$ 个代表元的系数的绝对值最大的式子，然后将其它的式子消元。
- 在消元中可能遇到的问题：以 $i$ 为代表元的系数为零，还有一些式子可能还没有判断。
- 如果在消元的中途已经没有多余的式子，显然有无数解。
- 这是容易解决的：多余的式子系数一定全都是 $0$，只需要判断它们的常数项，如果不是 $0$，显然无解。
- 然后如果发现有代表元的系数为 $0$，显然有无数解。
- 最后只有代表元有非 $0$ 系数，此时显然有唯一解，暴力除过去，得到答案。
- 板子特别短。
- [带注释实现](https://www.luogu.com.cn/paste/hqa20vj0)。
- [实现](https://www.luogu.com.cn/paste/z1v9x1pq)。
- [模板题](https://www.luogu.com.cn/problem/P3232)。
- [对拍](https://www.luogu.com.cn/paste/7jwgb211)。
- 这题需要求经过每条边的期望，考虑算出经过每个点的期望 $e_u$，然后 $e_{(u,v)}=\dfrac{e_u}{d_u}+\dfrac{e_v}{d_v}$，然后我们考虑列方程组求解，[实现](https://www.luogu.com.cn/paste/y3sk36k6)。
- [模板题](https://www.luogu.com.cn/problem/P4745)。
- 其实和高斯消元并没有关系，但是挺有趣，设达到终点的期望步数为 $f_u$，显然：
$$f_u=\frac{1}{d_u}\sum_{(u,v)}\min(f_u,f_v)+1$$
- 其实就是一个贪心，期望步数不更优就留在原地，但这个东西没法高斯消元了。
- 考虑借助循环不变式设计算法，设 $g_u$ 为虚假的期望，初始时 $g_t=f_t=0$。
- 在每层循环的时候将最小的一个期望加入信任队列（显然存在一个点只有已加入的点期望比它小，而显然它应该实际期望最小），然后用它再更新所有的期望。
- 容易发现它很像迪杰斯特拉算法，即在 $O(m\log n)$ 的时间解决了该题。
- [代码实现](https://www.luogu.com.cn/paste/rf5x63tw)。
- [模板题](https://www.luogu.com.cn/problem/P4457)。
- 当然是高斯消元啦！减的部分可以二项分布暴力，然后发现 $n\le 1500,T\le 100$，~~套路地使用快速矩阵乘法~~。
- 是这样的，你会发现你只有一次治疗之雨，这个性质肯定得用上，它意味着这个矩阵几乎是三角矩阵，也就是离消元就差一步的那种。
- 也就是说，我们在高斯消元的时候只需要考虑两个元素了，然后消的时候回头向上消一下，也能消成对角，然后这个时间复杂度就是 $O(n^2)$。
- 等等，我们还要判断无解啊，这不又一大堆东西……
- [代码实现](https://www.luogu.com.cn/paste/qnzayu3c)，果然，这种相对简单的题目就要注意一大堆细节，需要注意。

---

## 作者：zyxawa (赞：2)

## 「CERC2017」Gambling Guide

给定一张 $n$ 个点，$m$ 条边的无向图，在每个时刻每个点会随机开放一条出边，你可以不动或沿着开放的边走（均花费 $1$ 的时间），求**最优策略**下从 $1$ 到达 $n$ 的期望时间。

---

图上问题考虑逆推，设节点 $i$ 到达 $n$ 的期望时间为 $dp_i$，节点 $i$ 的出度为 $deg_i$。

则有 $dp_i=\frac{\sum min(dp_i,dp_j)}{deg_i}+1$（$i$ 与 $j$ 之间有边相连）。

令 $cnt_i$ 为满足 $dp_j < dp_i$ 且 $i$ 与 $j$ 之间有边相连的 $j$ 的数量，$sum_i$ 为满足 $dp_j < dp_i$ 且 $i$ 与 $j$ 之间有边相连的 $j$ 的 $\sum dp_j$。

则有 $dp_i=\frac{sum_i}{deg_i}+\frac{(deg_i-cnt_i) \times dp_i}{deg_i}+1$。

移项得 $(1-\frac{deg_i-cnt_i}{deg_i}) \times dp_i=\frac{sum_i}{deg_i}+1$。

那么 $\frac{cnt_i}{deg_i} \times dp_i=\frac{sum_i+deg_i}{deg_i}$。

化简得 $dp_i=\frac{sum_i+deg_i}{cnt_i}$。

考虑用 dijkstra，只是我们每次转移的时候去以当前节点更新与它相连的节点应该为未访问过的节点，因为如果已经访问过了，而且边权都为 $1$（$>0$），那么只会增加它的 $dp$ 值，不属于最优策略。

### 示例代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,vis[300001];
double dp[300001],sum[300001],cnt[300001];
vector <int> G[300001];
priority_queue <pair<double,int>,vector<pair<double,int> >,greater<pair<double,int> > > Q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	Q.push({0,n});
	while(!Q.empty()){
		int rt=Q.top().second;
		Q.pop();
		if(vis[rt]) continue;
		vis[rt]=1;
		for(int i=0;i<G[rt].size();i++){
			int to=G[rt][i];
			if(!vis[to]){
				cnt[to]++;
				sum[to]+=dp[rt];
				dp[to]=(1.0*G[to].size()+sum[to])/cnt[to];
				Q.push({dp[to],to});
			}
		}
	}
	printf("%.10lf",dp[1]);
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

设 $f_u$ 表示 $u$ 到终点所需要的最少抽票数。

在某点抽票之后有两种策略，一种是直接走，还有一种是重新抽。于是根据两种策略可以列出一下转移方程，

$$f_u=1+\sum\limits_{(u,v)\in E}\dfrac{\min(f_u,f_v)}{d_u}$$

可以发现这个取 $\min$ 非常影响推导，我们可以按照 Dijkstra 的顺序来转移就能消除 $\min$ 了。

可是我们不可能一次性就遍历某点的所有出边，所以在某些 $v$ 没有更新 $u$ 的时候，$\min(f_u,f_v)$ 就取 $f_u$。这也保证了当 $f_u$ 被当作最小值取出的时候，它的值是正确的，因为当 $f_u$ 为最小值的时候，$\min(f_u,f_v)=f_u$。

时间复杂度 $O((n+m)\log m)$。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=3e5+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
vector<int> G[maxn]; int c[maxn];
double f[maxn],s[maxn];
int n,m,vis[maxn],deg[maxn];
priority_queue<pair<double,int> > q;
void Dijkstra(){
	f[n]=0; q.push(mp(0,n));
	while(!q.empty()){
		int u=q.top().se; q.pop();
		if(vis[u]) continue; vis[u]=1;
		for(auto v:G[u]){
			if(vis[v]) continue;
			c[v]++; s[v]+=f[u];
			f[v]=(deg[v]+s[v])/c[v];
			q.push(mp(-f[v],v));
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		G[u].pb(v); G[v].pb(u);
		deg[u]++; deg[v]++;
	}
	Dijkstra(); printf("%.7lf",f[1]);
	return 0;
}
```

---

