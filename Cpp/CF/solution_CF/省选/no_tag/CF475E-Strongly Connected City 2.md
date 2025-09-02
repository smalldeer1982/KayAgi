# Strongly Connected City 2

## 题目描述

Imagine a city with $ n $ junctions and $ m $ streets. Junctions are numbered from $ 1 $ to $ n $ .

In order to increase the traffic flow, mayor of the city has decided to make each street one-way. This means in the street between junctions $ u $ and $ v $ , the traffic moves only from $ u $ to $ v $ or only from $ v $ to $ u $ .

The problem is to direct the traffic flow of streets in a way that maximizes the number of pairs $ (u,v) $ where $ 1<=u,v<=n $ and it is possible to reach junction $ v $ from $ u $ by passing the streets in their specified direction. Your task is to find out maximal possible number of such pairs.

## 说明/提示

In the first sample, if the mayor makes first and second streets one-way towards the junction $ 1 $ and third and fourth streets in opposite direction, there would be 13 pairs of reachable junctions: $ {(1,1),(2,2),(3,3),(4,4),(5,5),(2,1),(3,1),(1,4),(1,5),(2,4),(2,5),(3,4),(3,5)} $

## 样例 #1

### 输入

```
5 4
1 2
1 3
1 4
1 5
```

### 输出

```
13
```

## 样例 #2

### 输入

```
4 5
1 2
2 3
3 4
4 1
1 3
```

### 输出

```
16
```

## 样例 #3

### 输入

```
2 1
1 2
```

### 输出

```
3
```

## 样例 #4

### 输入

```
6 7
1 2
2 3
1 3
1 4
4 5
5 6
6 4
```

### 输出

```
27
```

# 题解

## 作者：louhao088 (赞：5)

CF好题


------------


题目要求我们给边定向，使定向之后存在最多的点对 $(a,b)$ 使得从 $a$ 能到 $b$。


------------


考虑如果有 $n$ 个点，怎样连才能使其贡献最大。肯定是连成一个环，环上两两点之间都能有贡献。

然后我们发现边双一定存在一种方法使其变成一个环。具体的，我们可以用 Tarjan 找边双，把它缩点，计算贡献。这样图就会变成一个树。

然后我们考虑一棵树怎么做。我们发现如果答案最优，那么肯定存在一个点，我们令他为根，使得他的一些子树里是连向他的，它也连向一些子树。在连向它的子树中，所有点都连向它的父亲，在其他子树里，所有点都连向他的儿子。而且两边的子树大小尽可能相同。可以证明这样一定是最优的。

具体的，我们可以枚举每个点为根，统计他的子树大小，用背包的方法维护，我们还可以用 bitset 来优化背包（不优化应该也能过）。


------------

时间复杂度为 $O ( n^2)$ 。

注意统计答案时是用缩过点的树来做的，计算子树大小，统计贡献都要用每个缩点的大小来算，不能用 1。


------------

代码如下。

```cpp
// Problem: CF475E Strongly Connected City 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF475E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 2021-11-09 18:21:40
// Author : louhao088

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=2e3+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,low[maxn],dfn[maxn],tot=0,st[maxn],idx,sz[maxn];
int ans=0,s[maxn],res,id[maxn],a,b,cnt,sum=0;
vector<int>e[maxn],E[maxn];
bitset<2005>f;
void tarjan(int x,int fa)
{
	dfn[x]=++cnt;low[x]=dfn[x];st[++tot]=x;
	for(auto i:e[x])
		if(i!=fa)
		{
			if(!dfn[i]) tarjan(i,x),low[x]=min(low[x],low[i]);
			else low[x]=min(low[x],dfn[i]);
		}
	if(dfn[x]==low[x])
	{
		++idx;
		while(st[tot]!=x&&tot>0)s[idx]++,id[st[tot]]=idx,tot--;
		s[idx]++,id[st[tot]]=idx,tot--;
		sum+=s[idx]*s[idx];
	}
}
void dfs(int x,int fa)
{
	sz[x]=s[x];
	for(auto i:E[x])
		if(i^fa)
			dfs(i,x),sz[x]+=sz[i];
	res+=s[x]*(sz[x]-s[x]);
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++)
		a=read(),b=read(),e[a].push_back(b),e[b].push_back(a);
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,0);
	for(int i=1;i<=n;i++)
		for(auto j:e[i])
			if(id[i]!=id[j])E[id[i]].push_back(id[j]);
	for(int i=1;i<=idx;i++)
	{
		memset(sz,0,sizeof sz);res=0;
		dfs(i,0);f.reset();f[0]=1;
		for(auto j:E[i])f=f|(f<<sz[j]);
		for(int j=(sz[i]-s[i])/2;j>=0;j--)
            if(f[j]){res+=j*(n-j-s[i]);break;}
		ans=max(ans,res);
	}
	cout<<ans+sum<<endl;
 	return 0;
}
```



---

## 作者：FunnyCreatress (赞：3)

首先对于一个边双显然是要定向成两两可达，所以缩点后考虑树上情况。

手玩样例后我们猜测，最优情况下对于每个点，以它为根后每个子树内同时指向该点或远离该点。

证明：若不然，那么把最浅的逆行连通块翻转后一定不劣 (因为块内贡献不变，增加了该块对非逆行部分的贡献)。

观察这样的树的形态，发现至多有一个点入度和出度都 $\ge 2$。考虑枚举这个点 (当然可以不考虑度数的限制)，以这个点为根，DP求出子树大小以及子树内部的贡献 (显然不管指向哪边内部贡献相同)。剩下的贡献显然是向内的子树大小之和乘向外子树的大小之和，由于和为定值，所以越接近越好，做大小为 $\lfloor\dfrac{n-s_{rt}}2\rfloor$ 的背包即可。由于每个点度数之和为 $O(n)$，所以总复杂度 $O(n^2)$，如果运用一些换根DP的技巧并用 bitset 优化背包可以做到 $O(\dfrac{n^2}w)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005,M=2e6+5;
int n,m,hd[N],to[M<<1],nxt[M<<1],tot,low[N],dfn[N],cnt,stk[N],tp,b[N],cs,s[N],ans,sz[N],tmp;vector<int> v[N];bool f[N];
void add(int x,int y){to[++tot]=y,nxt[tot]=hd[x],hd[x]=tot;}
void tarjan(int x,int Fa){
	low[x]=dfn[x]=++cnt,stk[++tp]=x;
	for(int i=hd[x],y;i;i=nxt[i])
		if(!dfn[y=to[i]])tarjan(y,x),low[x]=min(low[x],low[y]);
		else if(y!=Fa)low[x]=min(low[x],dfn[y]);
	if(low[x]==dfn[x]){
		cs++;
		do{b[stk[tp]]=cs,s[cs]++;}while(stk[tp--]!=x);
	}
}
void dfs(int x,int Fa){
	sz[x]=s[x];
	for(int y:v[x])if(y!=Fa)dfs(y,x),sz[x]+=sz[y];
	tmp+=s[x]*(sz[x]-s[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
	tarjan(1,0);
	for(int i=1;i<=n;i++)
		for(int j=hd[i],y;j;j=nxt[j])
			if(b[y=to[j]]!=b[i])v[b[i]].push_back(b[y]);
	for(int i=1;i<=cs;i++){
		tmp=0,dfs(i,0),fill(f,f+n+1,0),f[0]=1;
		for(int y:v[i])
			for(int k=n;k>=sz[y];k--)f[k]|=f[k-sz[y]];
		int t=0;
		for(int j=1;j<=n;j++)if(f[j])t=max(t,j*(n-s[i]-j));
		ans=max(ans,tmp+t);
	}
	for(int i=1;i<=cs;i++)ans+=s[i]*s[i];
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：shenxinge (赞：3)

### 题目描述:

给一个无向图，你需要给所有边定向，使定向之后存在最多的点对 $(a,b)$ 使得从 $a$ 能到 $b$。

### 想法：
考虑到这道题目环的重要性（有环点对肯定多），我们就容易想到这样一个引理：

**对于一个边双来说，总会存在一种方法使得把所有无向边改为有向边的方法，使得边双内的点可以互相到达。**

显然，我们对这个图进行边双缩点，**而且此图缩完点后必为一颗树，两边双之间的桥即是边。**

接下来问题便简化成了: 对于一颗树，如何对他的所有边进行定向使得他的价值最大。

首先，对于这种树型结构的东西上面搞 $dp$ ，枚举点 $O(n^3)$ 的算法往往可以被均摊压成 $O(n^2)$ 的，这不由得加深了我对这道题目是 $dp$ 的怀疑。

对于价值贡献来说，内部点的贡献为 $cnt^2$ ，而外部点的贡献取决于我们如何去安排。

我们考虑构造最优解，发现总是有 **中流砥柱** 的那一条路的出现。像是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/wmz07jx2.png)


中间的那个点起到至关重要的一步，他的存在使得所有的点可以通过最优解的有向边到达他本身，也可以从它本身到达其他所有的点。


我们把中间的点称为 **中流点** ，那么我们就可以通过枚举中流点的方法，（把他当作根）做一个类树型背包的 $dp$ 就可以了。

记 $s_i$ 为编号为 $i$ 的边双大小，$sz_i$ 记以 $i$ 为根的子树大小。

那么每个节点 $i$ 的子树内贡献的答案就是 $s_i\cdot(sz_i-s_i)$

所以最后我们还得统计一下过中流点的答案，也就是决定连着中流点的那些边的朝向。

假设朝向中流点的节点的 $sz$ 总和为 $sumsz$ ，那么另一部分就是 $(n-s_i-sumsz)$ 那么过中流点的答案就是 $sumsz\cdot(n-s_i-sumsz)$

把它尽可能地搞成一样，直接莽 $dp$ 。时间复杂度均摊 $O(n^2)$ 。

---

## 作者：JWRuixi (赞：1)

### 题意

给定一张 $n$ 个点 $m$ 条边的无向图，你需要给边定向使得满足 $u$ 能到达 $v$ 的点对 $(u, v)$ 的数量最大。特殊的 $(u, u)$ 被认为是合法的。

$n \le 2000, n - 1 \le m \le \dfrac{n \times (n - 1)}{2}$。

### 分析

先简化题目，若给定的是一棵树怎么做。先考虑菊花，发现一定是以菊花的根为中心，剩下的点一半连向花心，一半从花心出去。这其实我们应该能在树上找到一个中心，使得在最优解的前提下，一定是一半向外，一半向内。

具体证明就是，考虑这样的构型相当于一个从左到右的流线，而如果中间的一条边反向相当于将原问题拆成两个子问题，而原问题的贡献为两个子问题的乘积，所以不优。

那么我们的最优决策显然是让向外和向内的子树大小尽可能接近（均值不等式），可以使用 01 背包解决。进一步的，我们考虑到除了重心以外，其它点为根必有一棵子树大小大于 $\lfloor \dfrac{n}{2} \rfloor$，那么直接去这棵子树为一个部分，剩下的一个部分即可。

考虑放在一个图上，显然可以进行边双缩点，缩点后每个边双连通分量都可以通过定向成为一个强连通分量，所以缩点后跑树上做法即可。

时间复杂度 $\mathcal O(n^2)$，或 $\mathcal O(\dfrac{n^2}{\omega})$（用 `bitset` 优化）。

### Code

提交记录：<https://codeforces.com/contest/475/submission/222390234>。



---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

~~\*2700？\*1700！~~ 对不起，我伪证了，有点唐。

题意：给定一个无向图，给每条边定向使得可达点对数量最多。

做法：

首先对于一个边双，显然能找到一种定向方式使得其内所有点互相可达。

接下来，问题变为了一棵带权的树上的定向。

容易发现最终的定向结果一定是这样：存在中间一个点，它的一部分子树由叶子连向根，另一部分子树由根连向叶子。

以上为原题解部分。

----

这里添加了证明，以及发现了非重心的点无用。

证明的话可以参考 <https://www.luogu.me/paste/v8ci96zo>。写的时候精神状态可能不太稳定，这里大概简单描述一下证明的步骤：

1. 首先，一个图中有宽三段则一定有三段；
2. 接下来证明一个图包含宽三段（或三段）等价于不存在好点；
3. 接下来证明存在三段一定不优；于是这个时候就已经得出了最优情况一定存在至少一个好点。
4. 最后证明以其他点为好点的定向方式调整成以重心为好点的定向方式一定不劣。

链接里面第四步写的有点简略，~~因为昨天晚上忙着回家懒得写了~~这里详细展开一下。

假设现在以 $rt$ 为根，$rt$ 的每个子树的权值和分别为 $a_1,a_2,\dots,a_k$，$S=\sum a$，$S_T=\sum_{i\in T}a_i$。

那么如果我选择了一个集合 $T$，表示 $T$ 中所有子树都定向成外向树，其余子树定向成内向树，因为每个边双内部贡献，每个子树内部贡献以及子树跟 $rt$ 的贡献对于同一个 $rt$ 都是定值，所以这里只考虑子树之间的贡献，即 $S_T(S-S_T)$。那么我们要最大化这个，也就是让 $S_T$ 尽可能接近 $\frac S2$。

而众所周知，对于一棵带权的树，除了带权重心 $r$ 以外的每一个点 $p$，以 $p$ 为根时包含 $r$ 的那个子树的点权和一定是超过了所有点点权和的一半的。那也就是说，只要选择了这一个子树，就应当不选其他子树了，此时是 $p$ 为根时的最优情况。当然也可以理解为选择了除了这个子树以外的所有子树。

那考虑在这个时候把方案换成这样：以 $r$ 为根，只选择包含 $p$ 的那个子树。这个时候，因为后者比前者至少多了一个 $p$，所以子树的点权和肯定变大了。而且因为带权重心的性质，这个方案选择的点权和没有超过 $\frac S2$，所以答案一定变优。

于是实际上只需要对 $r$ 的所有子树跑一遍背包即可。

原来的部分也不算完全烂，比如复杂度分析就是需要思考一下的事情，所以就留着了。

-----

以下为原题解部分。

所以接下来枚举中间的那个点。现在我们知道了它的一堆子树。

容易发现这个时候每个子树内部的贡献都与方向无关，可以提前计算。子树间的贡献为朝向根的子树权值之和乘上朝向叶子的子树权值之和。

注意到两项总和固定（为 $n$ 减去中间节点的权值）而且范围很小，可以背包判断。

细节有点多。

```cpp
int n,m;
vector<int>v[2005];
int dcnt,bcnt,cnt=1,low[2005],dfn[2005],bcc[2005],va[2005],sz[2005],f[2005];
bool b[2000005],p[2005];
int hd[2005];
struct edge{int to,nxt;}e[2000005];
void ade(int x,int y){e[++cnt]={y,hd[x]},hd[x]=cnt;}
void dfs(int now,int ee){
	dfn[now]=low[now]=++dcnt;
	for(int _=hd[now];_;_=e[_].nxt){
		int i=e[_].to;
		if(!dfn[i]){
			dfs(i,_);
			if(low[i]>dfn[now])b[_]=b[_^1]=1;
			low[now]=min(low[now],low[i]);
		}else if(_!=(ee^1))low[now]=min(low[now],dfn[i]);
	}
}
void dfs2(int now,int v){
	++va[bcc[now]=v];
	for(int _=hd[now];_;_=e[_].nxt){
		int i=e[_].to;
		if(bcc[i]||b[_])continue;
		dfs2(i,v);
	}
}
void dfs3(int now,int fa){//子树和
	f[now]=fa;
	sz[now]=va[now];
	for(auto i:v[now])if(i^fa)dfs3(i,now),sz[now]+=sz[i];
}
int cds(int now,int fa,int d){//计算子树内部贡献
	int s=d*va[now];
	for(auto i:v[now])if(i^fa)s+=cds(i,now,d+va[now]);
	return s;
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,ade(x,y),ade(y,x);
	for(int i=1;i<=n;i++)if(!dfn[i])dfs(i,0);
	for(int i=1;i<=n;i++)if(!bcc[i])dfs2(i,++bcnt);
	for(int i=1;i<=n;i++)for(int _=hd[i];_;_=e[_].nxt){
		int j=e[_].to;
		if(bcc[i]^bcc[j])v[bcc[i]].push_back(bcc[j]);
	}
	for(int i=1;i<=bcnt;i++)sort(all(v[i])),v[i].erase(unique(all(v[i])),v[i].end());
	int N=n;
	n=bcnt;//将原图缩成一棵树
	dfs3(1,1);
	int ans=0;
	for(int now=1;now<=n;now++){
		Cl(p);
		p[0]=1;
		for(auto i:v[now]){
			int x=i==f[now]?N-sz[now]:sz[i];
			for(int j=2000;j>=x;j--)p[j]|=p[j-x];//背包
		}
		int s=0;
		for(auto i:v[now])s+=cds(i,now,va[now]);
		int nn=N-va[now];
		for(int k=0;k<=nn/2;k++)if(p[nn/2-k]&&p[nn-(nn/2-k)]){
			ans=max(ans,s+(nn/2-k)*(nn-(nn/2-k)));//取最近的两个
			break;
		}
	}
	for(int i=1;i<=n;i++)ans+=va[i]*va[i];//别忘了每个节点自身的贡献
	cout<<ans<<"\n";
}
```

---

## 作者：ReTF (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF475E)

首先发现边双可以重定向为强连通分量，所以缩点。图变成了树。

观察到关键性质：最优的构造方案一定是选定一个节点当根，它的子树中有若干子树中的边全部指向叶子方向，其他子树中的边全部指向根节点方向。

然后枚举根节点做个背包就做完了。

时间复杂度 $O(n^2)$。

[代码](https://codeforces.com/contest/475/submission/244904964)

---

## 作者：N2MENT (赞：0)

有意思的，不难写的，不卡常的，好想的。

---

一头雾水，怎么办，先找显然结论，如果点在一个环上，上面的点全部可达，但这是给无向图定向，所以这是边双。

按照边双缩点，缩完点后内部的点互相可达，最后加进贡献即可，下文不考虑。现在只要知道树怎么做就行。

首先显然的，对于一颗子树，内向树和外向树贡献一样，原本的点对反过来就能一一对应。

然后，有一个重要结论，就是一定有一个点，它的一些子树是内向树，一些子树是外向树。

为什么呢，猜的，怎么证？把整棵树以这个点为根平摊开来，左边是内向树，右边是外向树，此时的总贡献 

$$F(S) = \sum_{v\in son_u} F(S_v) + val_u \times(n - val_u) + (\sum_{v\in in_u} siz_v)(\sum_{v\in out_u} siz_v)$$

![](https://cdn.luogu.com.cn/upload/image_hosting/tsh34qon.png)

如果全是外向树

$$F(S) = \sum_{v\in son_u} F(S_v) + val_u \times(n - val_u)$$

不会更优。类似于递归，可以理解其他地方不符合预期的情况。

那怎么实现，对于每个点做背包，dp 值存这个大小能否由子树组成出来。

然而，小学数学告诉我们 $(\sum_{v\in in_u} siz_v)(\sum_{v\in out_u} siz_v)$ 这个式子，两项的差越小乘积越大，非重心的点有一个超过 $\frac{n}{2}$ 的子树，肯定是取这个子树单独作为内向树或外向树，可以直接算，因此只需要对重心 dp。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2010;
class Edge {
public:
	int v, ord;
	Edge() = default;
	Edge(int v, int ord) : v(v), ord(ord) {
	}
};
int dfn[maxn], low[maxn], cnt;
vector<Edge> G[maxn];
bool brg[maxn * maxn];
void Tarjan(int u, int fa) {
	dfn[u] = low[u] = ++cnt;
	for(Edge e : G[u]) {
		int v = e.v, ord = e.ord;
		if(v == fa) continue;
		if(!dfn[v])	Tarjan(v, u);
		low[u] = min(low[u], low[v]);
		if(low[v] > dfn[u]) {
			brg[ord] = true;
		}
	}
}
int col[maxn], colsiz[maxn], colcnt;
vector<int> R[maxn];
void dfs(int u, int c) {
	col[u] = c;
	colsiz[c]++;
	for(Edge e : G[u]) {
		int v = e.v, ord = e.ord;
		if(col[v] && brg[ord]) {
			R[col[u]].emplace_back(col[v]);
			R[col[v]].emplace_back(col[u]);
			continue;
		}
		if(brg[ord] || col[v]) continue;
		dfs(v, c);
	}
}
int n, m;
int ans;
int f[maxn], siz[maxn];
bool g[maxn];
void dfs2(int u, int fa) {
	siz[u] = colsiz[u];
	f[u] = 0;
	for(int v : R[u]) {
		if(v == fa) continue;
		dfs2(v, u);
		siz[u] += siz[v];
		f[u] += colsiz[u] * siz[v] + f[v];
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].emplace_back(v, i);
		G[v].emplace_back(u, i);
	}
	Tarjan(1, 0);
	for(int i = 1; i <= n; i++) {
		if(!col[i]) {
			dfs(i, ++colcnt);
		}
	}
	for(int i = 1; i <= colcnt; i++) {
		dfs2(i, 0);
		int mx = 0;
		int sum = 0;
		for(int v : R[i]) {
			sum += f[v];
			if(!mx || siz[v] > siz[mx]) mx = v;
		}
		if(2 * siz[mx] >= n - colsiz[i]) {
			sum += siz[mx] * (n - colsiz[i] - siz[mx]) + colsiz[i] * (n - colsiz[i]);
			ans = max(ans, sum);
			continue;
		} 
		memset(g, 0, sizeof(g));
		g[0] = true;
		for(int v : R[i]) {
			for(int j = n; j >= siz[v]; j--) {
				g[j] |= g[j - siz[v]]; 
			}
		}
		for(int j = 1; j <= n; j++) {
			if(g[j]) ans = max(ans, sum + j * (n - colsiz[i] - j) + colsiz[i] * (n - colsiz[i]));
		}
	}
	for(int i = 1; i <= colcnt; i++) {
		ans += colsiz[i] * colsiz[i];
	}
	printf("%d", ans);
}
```


---

