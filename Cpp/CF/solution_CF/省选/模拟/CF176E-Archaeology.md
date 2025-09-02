# Archaeology

## 题目描述

This time you should help a team of researchers on an island in the Pacific Ocean. They research the culture of the ancient tribes that used to inhabit the island many years ago.

Overall they've dug out $ n $ villages. Some pairs of villages were connected by roads. People could go on the roads in both directions. Overall there were exactly $ n-1 $ roads, and from any village one could get to any other one.

The tribes were not peaceful and they had many wars. As a result of the wars, some villages were destroyed completely. During more peaceful years some of the villages were restored.

At each moment of time people used only those roads that belonged to some shortest way between two villages that existed at the given moment. In other words, people used the minimum subset of roads in such a way, that it was possible to get from any existing village to any other existing one. Note that throughout the island's whole history, there existed exactly $ n-1 $ roads that have been found by the researchers. There never were any other roads.

The researchers think that observing the total sum of used roads’ lengths at different moments of time can help to better understand the tribes' culture and answer several historical questions.

You will be given the full history of the tribes' existence. Your task is to determine the total length of used roads at some moments of time.

## 样例 #1

### 输入

```
6
1 2 1
1 3 5
4 1 7
4 5 3
6 4 2
10
+ 3
+ 1
?
+ 6
?
+ 5
?
- 6
- 3
?
```

### 输出

```
5
14
17
10
```

# 题解

## 作者：Elma_ (赞：3)

> 给一棵树，支持：标记一个关键点，取消一个关键点，查询包含所有关键点的最小连通块的边权和。

有一个结论是，考虑当前有 $k$ 个关键点，按照 $\mathrm{dfs}$ 序从小到大排列后分别为 $f_1,f_2,\cdots,f_k$，那么包含这 $k$ 个点的最小连通块的边权和为：

$$\dfrac{1}{2}\times [dis(f_1,f_2)+dis(f_2,f_3)+\cdots+dis(f_k,f_1)]$$

其中 $dis(x,y)$ 表示点 $x$ 和 $y$ 在树上的距离。这个正确性是显然的，考虑一条边在何时会被算进答案，显然一条边会被算进答案当且权当这条边的两侧都有关键点。在计算路径的时候，我们对于一条边从左侧到右侧时计算了一次，从右侧到左侧时又计算了一次，因此最后除以二就是答案。

于是我们直接用一个 $\mathrm{set}$ 来维护当前关键点的 $\mathrm{dfs}$ 序的集合 $S$，每次插入点 $x$ 时找到 $S$ 中 $\mathrm{dfs}$ 序小于该点的第一个点 $l$（如果没有就是 $\mathrm{dfs}$ 序最大的点）和 $\mathrm{dfs}$ 序大于该点的第一个点 $r$（如果没有就是 $\mathrm{dfs}$ 序最小的点），然后相当于是去掉路径 $(l,r)$ 的贡献，加上 $(l,x)$ 和 $(x,r)$ 的贡献，删点的时候同理。

因为 $\mathrm{set}$ 里存的是关键点的 $\mathrm{dfs}$ 序，因此我们还需要开一个数组来记录每个 $\mathrm{dfs}$ 序对应着哪个节点。要注意一些细节，比如只有一个关键点或没有关键点的特殊情况。时间复杂度 $O(n \log n + q \log^2n)$。

```cpp
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <algorithm>
#define pii pair<int, int>
#define mp make_pair
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 2e5 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f3f3f3f;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
	int nxt, to, val;
} edge[maxn << 1];
int n, q, sum, tot, head[maxn], dep[maxn], fa[maxn][25], dis[maxn];
int tim, dfn[maxn], rev[maxn];

inline void addedge(int u, int v, int w) {
	edge[++tot] = (node){head[u], v, w}, head[u] = tot;
}
inline void dfs(int u, int fath) {
    dfn[u] = ++tim, rev[tim] = u;
    dep[u] = dep[fath] + 1, fa[u][0] = fath;
    for (int i = 1;i <= 20;i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u];i;i = edge[i].nxt) {
        int v = edge[i].to; if (v == fath) continue;
        dis[v] = dis[u] + edge[i].val, dfs(v, u);
    } 
}
inline int getlca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int i = 20;i >= 0;i--)
		if (dep[u] <= dep[v] - (1 << i)) v = fa[v][i];
	if (u == v) return u;
	for (int i = 20;i >= 0;i--)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

set<int> s;
inline int getdis(int x, int y) {
	return dis[x] + dis[y] - (dis[getlca(x, y)] << 1);
}
set<int> :: iterator it, tmp, pre, nxt;
inline int query(set<int> :: iterator it) {
	pre = it, nxt = it;
    pre = it == s.begin() ? s.end() : it, pre--;
    if (++nxt == s.end()) nxt = s.begin();
    int l = rev[*pre], r = rev[*nxt], u = rev[*it];
    return getdis(l, u) + getdis(u, r) - getdis(l, r);
}
inline void insert(int x) {
    it = s.insert(dfn[x]).first;
    if (s.size() > 2) sum += query(it);
    else if (s.size() == 2) {
        tmp = it == s.begin() ? ++it : s.begin();
        sum = getdis(rev[*tmp], x) << 1;
    }
}
inline void remove(int x) {
    it = s.find(dfn[x]);
    if (s.size() > 2) sum -= query(it);
    else if (s.size() == 2)sum = 0;
    s.erase(dfn[x]);
}

signed main(void) {
    n = read();
    for (int i = 1, u, v, w;i < n;i++) {
        u = read(), v = read(), w = read();
        addedge(u, v, w), addedge(v, u, w);
    }
    dfs(1, 0), q = read();
    while (q--) {
        char opt; cin >> opt;
        if (opt == '+') {
            int x = read(); insert(x);
        } else if (opt == '-') {
            int x = read(); remove(x);
        } else {
            printf("%lld\n", sum >> 1);
        }
    }
    return 0; 
}
```


---

## 作者：Leap_Frog (赞：2)

### P.S.
竟然能在阴间键盘以及阴间 win7 下过题，还是一遍过 ![](//xn--9zr.tk/se)  

### Description.
啧啧

### Solution.
首先，考虑无修改操作怎么做。  
直接考虑把所有点按照 $\text{dfn}$ 序排序，然后认为这个序列是环。  
求出相邻两个之间的距离之和，除以二就是答案。  
证明可以按照虚树构建方式也是按照 $\text{dfn}$ 序来排的。  

然后，我们考虑支持插点删点。  
直接用一个 set 维护当前序列。  
插入是直接算出它和左右多出来的贡献，删除时减去。  
然后这题就做完了。  
注意讨论一些边界情况。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}//}}}
typedef set<pair<int,int> >::iterator IT;
struct edge{int to,w,nxt;}e[200005];int n,et,head[100005];
int Q,f[100005][18],dep[100005],dfn[100005],dt;ll ds[100005];
inline void adde(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void dfs0(int x,int fa,int ls)
{
	f[x][0]=fa,dep[x]=dep[fa]+1,ds[x]=ds[fa]+ls,dfn[x]=++dt;
	for(int i=1;i<18;i++) f[x][i]=f[f[x][i-1]][i-1];
	for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs0(e[i].to,x,e[i].w);
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=17;~i;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=17;~i;i--) if(f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
inline ll dis(int x,int y) {int lc=LCA(x,y);return ds[x]+ds[y]-ds[lc]*2;}
int main()
{
	read(n);for(int i=1,x,y,w;i<n;i++) read(x),read(y),read(w),adde(x,y,w),adde(y,x,w);
	set<pair<int,int> >st;ll nw=0;for(dfs0(1,0,0),read(Q);Q--;)
	{
		char ch;int x;scanf("%s",&ch);if(ch^'?') read(x);
		if(ch=='?') {printf("%lld\n",nw>>1);continue;}
		if(ch=='-')
		{
			IT it=st.lower_bound(make_pair(dfn[x],x));
			if((int)st.size()<=2) {st.erase(it),nw=0;continue;}
			IT ls=it;if(ls==st.begin()) ls=--st.end();else --ls;
			IT rs=it;++rs;if(rs==st.end()) rs=st.begin();
			int a=ls->second,b=rs->second;nw-=dis(a,x)+dis(b,x)-dis(a,b);
			st.erase(it);continue;
		}
		if((int)st.size()==0) {st.insert(make_pair(dfn[x],x));continue;}
		if((int)st.size()==1)
		{
			int y=st.begin()->second;nw+=dis(x,y)<<1;
			st.insert(make_pair(dfn[x],x));continue;
		}
		IT it=st.lower_bound(make_pair(dfn[x],x));
		IT ls=it;if(ls==st.begin()) ls=--st.end();else ls--;
		IT rs=it;if(rs==st.end()) rs=st.begin();
		int a=ls->second,b=rs->second;nw+=dis(a,x)+dis(b,x)-dis(a,b);
		st.insert(make_pair(dfn[x],x));
	}
	return 0;
}
```

---

## 作者：zhouxianzhuo (赞：1)

这题 结论的证明 以及 ```set``` 卡了我很久，希望这篇题解可以帮助大家。
# 前缀知识
仅需提前学习 [LCA](https://www.luogu.com.cn/problem/P3379)。
# 思路
可以先将一棵树视为若干个子树的嵌套组合，所以我们仅需讨论子树间的关系就行了。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/8i0vff9x.png)

然后就可以发现，如果将黑点按 DFS 序排列，那么连在一起的一定是同一颗子树内的点。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mxxwtpme.png)

因此再将子树推广到整棵树，如果将这些点按 DFS 序从头到尾形成一个环，所有相邻的两个点的距离之和即为答案的两倍。

为了动态加入和删除黑点，这里使用 ```set```。
## set
```set``` 是一个以红黑树实现，将元素按照一定次序存储的容器，类似于 ```map```。但不同于 ```map``` 的是，```map``` 中存放的是 ```<key,value>```，而 ```set``` 的 ```key``` 与 ```value``` 是相同的，相当于存放的是 ```<value,value>```。

```set<int> s``` 定义一个 ```int``` 型的 ```set``` 容器 $s$。

```set<int>::iterator a``` 定义一个 ```int``` 型的 ```set``` 指针变量 $a$。

```s.begin()``` 返回一个指向 $s$ 的第一个元素的指针变量。

```s.end()``` 返回一个指向 $s$ 的最后一个元素的后一位的指针变量。

```s.size()``` 返回 $s$ 中元素的个数。

```s.insert(x)``` 将 $x$ 加入 $s$ 中。

```s.erase(x)``` 将 $x$ 从 $s$ 中删除。

```s.lower_bound(x)``` 二分，在 $s$ 中找到第一个大于或等于 $x$ 的值，并返回一个指向它的指针变量，如果没有则返回 ```s.end()```。

```s.upper_bound(x)``` 二分，在 $s$ 中找到第一个大于 $x$ 的值，并返回一个指向它的指针变量，如果没有则返回 ```s.end()```。

```a++``` 将指针变量 $a$ 所指的位置向后挪一位（注意不要越界）。

```a--``` 将指针变量 $a$ 所指的位置向前挪一位（注意不要越界）。
# 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,vis[100010],fv[100010],jump[100010][30];
long long st[100010],ans;
vector<int> a[100010],len[100010];
set<int> s;
void dfs(int x,int fa,int ln){
	st[x]=st[fa]+ln;		//对树上的链计算距离前缀和 
	cnt+=1;
	vis[x]=cnt;
	fv[cnt]=x;		//利用 fv反向记录 vis，方便后面取点 
	jump[x][0]=fa;
	for(int i=1;i<=20;i++)
		jump[x][i]=jump[jump[x][i-1]][i-1];
	int l=a[x].size();
	for(int i=0;i<=l-1;i++)
		if(a[x][i]!=fa)dfs(a[x][i],x,len[x][i]);
}
int lca(int u,int v){
	if(u==v)return u;
	if(vis[u]>vis[v])swap(u,v);
	for(int i=20;i>=0;i--)
		if(vis[jump[v][i]]>vis[u])v=jump[v][i];
	return jump[v][0];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x].push_back(y);
		len[x].push_back(z);
		a[y].push_back(x);
		len[y].push_back(z);
	}
	dfs(1,0,0);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		char c;
		c=getchar();
		while(c!='+'&&c!='-'&&c!='?')
			c=getchar();
		if(c=='+')
		{
			int x;
			scanf("%d",&x);
			if(s.size()>=1)
			{
				set<int>::iterator ta=s.upper_bound(vis[x]),tb=s.end();		// ta指向要插入的点右边的点 
				tb--;		// tb指向最后一个点（方便下面判断） 
				if(ta==s.end())ta=s.begin();		//如果没找到右边的点，则 ta指向第一个点（所有点形成一个环） 
				int a=fv[*ta],b;		// a表示要插入的点右边的点，b表示要插入的点左边的点 
				if(ta==s.begin())b=fv[*tb];		//如果要插入的点右边的点在最左边，则 b表示最后一个点（所有点形成一个环） 
				else 
				{
					ta--;
					b=fv[*ta];
					ta++;
				}		//这里必须要打包起来，不然 ta变化后会误判 
				int t;
				t=lca(a,b);
				ans-=st[a]+st[b]-2*st[t];
				t=lca(a,x);
				ans+=st[a]+st[x]-2*st[t];
				t=lca(b,x);
				ans+=st[b]+st[x]-2*st[t];
			}
			s.insert(vis[x]);
		}
		if(c=='-')
		{
			int x;
			scanf("%d",&x);
			if(s.size()>=2)
			{
				set<int>::iterator ta=s.lower_bound(vis[x]),tb=s.end();		// ta指向要删除的点 
				tb--;		// tb指向最后一个点（方便下面判断） 
				int a,b;		// a表示要删除的点右边的点，b表示要删除的点左边的点 
				if(ta==tb)a=fv[*s.begin()];		//如果要删除的点在最右边，则 a表示第一个点（所有点形成一个环） 
				else
				{
					ta++;
					a=fv[*ta];
					ta--;
				}		//这里必须要打包起来，不然 ta变化后会误判 
				if(ta==s.begin())b=fv[*tb];		//如果要删除的点在最左边，则 b表示最后一个点（所有点形成一个环） 
				else
				{
					ta--;
					b=fv[*ta];
					ta++;
				}		//这里必须要打包起来，不然 ta变化后会误判 
				int t;
				t=lca(a,b);
				ans+=st[a]+st[b]-2*st[t];
				t=lca(a,x);
				ans-=st[a]+st[x]-2*st[t];
				t=lca(b,x);
				ans-=st[b]+st[x]-2*st[t];
			}
			s.erase(vis[x]);
		}
		if(c=='?')printf("%lld\n",ans/2);
	}
	return 0;
}
```
# 对拍
为了方便调题，我将 $n$ 设为 $10$，同时推荐一个[构图网站](https://csacademy.com/app/graph_editor/)，可以辅助调题
## dp
```cpp
#include<windows.h>
#include<bits/stdc++.h>
using namespace std;
int main(){
	while(true)
	{
		system("datamaker.exe > data.txt");
		system("code.exe < data.txt > yours.txt");
		system("std.exe < data.txt > exp.txt");
		if(system("fc yours.txt exp.txt"))break;
	}
	return 0;
}
```
## datamaker
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10010],cnt;
bool vis[10010];
int main(){
	srand(time(0));
	int n=10,m=40;
	printf("%d\n",n);
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=n;i++) swap(a[i],a[rand()%n+1]);
	for(int i=2;i<=n;i++)
		printf("%d %d %d\n",a[i],a[rand()%(i-1)+1],rand()%5+1);
	printf("%d\n",m);
	for(int i=1;i<=m;i++)
	{
		int op=rand()%3+1;
		while(true)
		{
			if(op==3)
				if(rand()%5!=0) break;
			if(op==1&&cnt==n) op=rand()%3+1;
			else if(op==2&&cnt==0) op=rand()%3+1;
			else break;
		}
		if(op==1)
		{
			int u=rand()%n+1;
			while(vis[u]) u=rand()%n+1;
			vis[u]=1; cnt++;
			printf("+ %d\n",u);
		}
		if(op==2)
		{
			int u=rand()%n+1;
			while(!vis[u]) u=rand()%n+1;
			vis[u]=0; cnt--;
			printf("- %d\n",u);
		}
		if(op==3)
			printf("?\n");
	}
	return 0;
}
```
### 本题解 部分思路 及 datamaker 来自 @[TallBanana](https://www.luogu.com/user/780698)。

---

## 作者：lzqy_ (赞：1)

怎么都能观察到 dfn 的奇特性质的。

考虑加点和删点的影响。为了方便讨论，先钦定点 $1$ 在最后的连通块中。

加入点 $x$ 时，若 $x$ 的子树内有点，那么 $x$ 是无意义的。否则向上找到第一个点 $y$ 使得其子树内有点，$\{x\rightarrow y\}$ 路径上的边得到额外贡献。

删除点 $x$ 时，若 $x$ 的子树内包括点 $x$ 的点数 $>1$，那么 $x$ 是无意义的。否则向上找到第一个点 $y$，使其子树内包含点 $x$ 的点数 $>1$，$\{x\rightarrow y\}$ 路径上的边撤销贡献。

另一个小问题是最开始的钦定。实际上这也是简单的，连通块真正的根是 $lca(x_1,\dots,x_k)$，跑一遍欧拉序实时维护即可。最后答案减去 $\{1\rightarrow lca\}$ 路径的贡献。

树剖之后线段树二分可以做到 $O(n\log ^2 n)$。

```cpp

#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
const int maxn=100010;
const int MAXN=maxn<<2;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
il int cread(){
	char c=getchar();
	for(;c!='+'&&c!='-'&&c!='?';c=getchar());
	return c;
}
struct edge{
	int v,to,w;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v,int w){
	e[++ecnt].v=v,e[ecnt].w=w;
	e[ecnt].to=head[u],head[u]=ecnt;
}
ll p[maxn];
int Oula[maxn<<1],loc[maxn],cnt;
int st[maxn<<1][20]; 
int a[maxn],n,q,LCA;
int dfn[maxn],DFN[maxn],top[maxn],idx;
int sz[maxn],zson[maxn],dep[maxn],fa[maxn];
int d[MAXN],lz[MAXN];
struct Int{
	int x;
	Int(int y=0){x=y;}
	bool operator <(Int a)const{
		return loc[x]<loc[a.x];
	}
};
set<Int>s;
void dfs1(int fath,int x,int lw=0){
	dep[x]=dep[fath]+1,fa[x]=fath;
	p[x]=p[fath]+lw;
	Oula[++cnt]=x,loc[x]=cnt;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fath){
			dfs1(x,e[i].v,e[i].w),sz[x]+=sz[e[i].v];
			if(sz[zson[x]]<sz[e[i].v]) zson[x]=e[i].v;
			Oula[++cnt]=x;
		}
	sz[x]++;
}
void dfs2(int x){
	dfn[x]=++idx,DFN[idx]=x;
	if(zson[fa[x]]^x) top[x]=x;
	else top[x]=top[fa[x]];
	if(zson[x]) dfs2(zson[x]);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa[x]&&e[i].v!=zson[x]) dfs2(e[i].v);
}
void init(){
	for(int i=1;i<=cnt;i++) st[i][0]=Oula[i];
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=cnt;i++)
			if(dep[st[i][j-1]]>dep[st[i+(1<<j-1)][j-1]])
				st[i][j]=st[i+(1<<j-1)][j-1];
			else st[i][j]=st[i][j-1];
}
int lca(int x,int y){
	x=loc[x],y=loc[y];
	if(x>y) swap(x,y);
	int Log=log2(y-x+1);
	if(dep[st[x][Log]]>dep[st[y-(1<<Log)+1][Log]])
		return st[y-(1<<Log)+1][Log];
	else return st[x][Log]; 
}
void pushdown(int i){
	if(!lz[i]) return ;
	d[i<<1]+=lz[i],d[i<<1|1]+=lz[i];
	lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i];
	lz[i]=0;
}
void A(int i,int l,int r,int L,int R,int x){
	if(l>=L&&r<=R){
		d[i]+=x,lz[i]+=x;
		return ;
	}pushdown(i);
	int mid=l+r>>1;
	if(mid>=L) A(i<<1,l,mid,L,R,x);
	if(mid<R) A(i<<1|1,mid+1,r,L,R,x);
	d[i]=max(d[i<<1],d[i<<1|1]);
}
int Q(int i,int l,int r,int L,int R){
	if(l>R||r<L) return 0;
	if(l>=L&&r<=R) return d[i];
	pushdown(i);
	int mid=l+r>>1;
	return max(Q(i<<1,l,mid,L,R),Q(i<<1|1,mid+1,r,L,R));
}
int Lst(int i,int l,int r,int L,int R,int x){
	if(l>R||r<L) return -1;
	if(d[i]<x) return -1;
	if(l==r) return l;
	pushdown(i);
	int mid=l+r>>1,v;
	if(l>=L&&r<=R){
		if(d[i<<1|1]>=x) 
			return Lst(i<<1|1,mid+1,r,L,R,x);
		else return Lst(i<<1,l,mid,L,R,x);
	}
	if(~(v=Lst(i<<1|1,mid+1,r,L,R,x))) return v;
	return Lst(i<<1,l,mid,L,R,x);
}
void Add(int x){
	if(a[x]) return ; 
	a[x]=1,s.insert(Int(x));
	if(s.empty()) LCA=1;
	else LCA=lca(s.begin()->x,(--s.end())->x); 
	while(x) A(1,1,n,dfn[top[x]],dfn[x],1),x=fa[top[x]];
}
void Era(int x){
	if(!a[x]) return ;
	a[x]=0,s.erase(Int(x));
	if(s.empty()) LCA=1;
	else LCA=lca(s.begin()->x,(--s.end())->x); 
	while(x) A(1,1,n,dfn[top[x]],dfn[x],-1),x=fa[top[x]];
}
int get0(int x){
	if(Q(1,1,n,dfn[x],dfn[x])!=0) return x;
	if(Q(1,1,n,dfn[1],dfn[1])==0) return 1;
	while(x){
		if(Q(1,1,n,dfn[top[x]],dfn[x])==0) x=fa[top[x]];
		else return DFN[Lst(1,1,n,dfn[top[x]],dfn[x],1)];
	}
}
int get1(int x){
	if(Q(1,1,n,dfn[x],dfn[x])!=1) return x;
	if(Q(1,1,n,dfn[1],dfn[1])==1) return 1;
	while(x){
		if(Q(1,1,n,dfn[top[x]],dfn[x])==1) x=fa[top[x]];
		else return DFN[Lst(1,1,n,dfn[top[x]],dfn[x],2)];
	}
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		addedge(x,y,z),addedge(y,x,z);
	}dfs1(0,1),dfs2(1),init();
	q=read();
	ll sum=0,x,y;
	while(q--){
		char op=cread();
		if(op=='?')
			printf("%lld\n",sum-p[LCA]);
		else if(op=='+'){
			x=read(),Add(x);
			sum+=p[x]-p[get1(x)];
		}
		else{
			x=read(),Era(x);
			sum-=p[x]-p[get0(x)];
		}
//		printf("!!!%lld(%d)\n",sum,LCA);
	}
	return 0;
} 
```

---

## 作者：xuanxuan001 (赞：1)

做法不太一样，发篇题解。

考虑对于每一条边它会不会被算在答案里面，然后将贡献求和。在里面不太好计算，可以考虑什么情况下一条边不会被包含。假设这条边连接了 $u$ 和 $v$，并且 $u$ 是 $v$ 的父亲，那么情况就是 $v$ 为根的子树内没有黑点或者外面没有黑点。外面没有黑点可以转换为里面的黑点数量等于全局黑点数量。

那么做一个树剖就能直接维护每个点为根的子树内的黑点数量，但维护值为某个数的位置数并不好做，但有一个非常常见的套路，就是发现没有（$0$）和全部恰好是可能的出现次数的最小值和最大值，而最小值和最大值的数量是可以直接在线段树上维护的。

根节点保证了全局最大值一定是黑点数量，在线段树上加入位置 $0$ 就能保证最小值，然后就解决了。

代码

```cpp
#include<cstdio>
#define TY ll
#define MAXN 100002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
#define EDG(i,u) for(TY i=hed[u];i;i=nxt[i])
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
inline void add(TY &x,TY y){if((x+=y)>=M)x-=M;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(1&b)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a){if(a>9)qw(a/10);putchar(a%10+'0');}
void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY n=qr(),T,u,v,hed[MAXN],nxt[MAXN<<1],to[MAXN<<1],w[MAXN],fa[MAXN];
TY ar[MAXN],sz[MAXN],sn[MAXN],tp[MAXN],dfn[MAXN],tag[MAXN<<2],k,S;
struct node{TY mn,mx,smn,smx;}tre[MAXN<<2];
void addedge(TY id){nxt[id]=hed[u];to[hed[u]=id]=v;}
void dfs(TY u){//树剖预处理
	sz[u]=1;EDG(i,u)if(to[i]!=fa[u]){
		fa[to[i]]=u;dfs(to[i]);sz[u]+=sz[to[i]];
		if(sz[sn[u]]<sz[to[i]])sn[u]=to[i];
	}
}void dfs2(TY u){
	dfn[u]=++v;if(!sn[u])return;
	tp[sn[u]]=tp[u];dfs2(sn[u]);
	EDG(i,u)if(to[i]!=fa[u]){
		if(to[i]!=sn[u])dfs2(tp[to[i]]=to[i]);
		ar[dfn[to[i]]]=w[i>>1];
	}
}void build(TY i,TY j,TY id){
	if(i==j){
		tre[id].smn=tre[id].smx=ar[i];
		tre[id].mn=tre[id].mx=0;return;
	}TY mid=i+j>>1;build(i,mid,id<<1);build(mid+1,j,id<<1|1);
	tre[id].smn=tre[id].smx=tre[id<<1].smn+tre[id<<1|1].smx;
}void upd(TY id,TY k){tre[id].mn+=k;tre[id].mx+=k;tag[id]+=k;}
void chg(TY i,TY j,TY id){//修改
	if(u<=i&&j<=v){upd(id,k);return;}
	TY mid=i+j>>1,sn=id<<1;
	upd(sn,tag[id]);upd(sn|1,tag[id]);tag[id]=0;
	if(u<=mid)chg(i,mid,sn);if(v>mid)chg(mid+1,j,sn|1);
	tre[id].mn=minn(tre[sn].mn,tre[sn|1].mn);
	tre[id].mx=maxn(tre[sn].mx,tre[sn|1].mx);tre[id].smn=tre[id].smx=0;
	if(tre[id].mn==tre[sn].mn)tre[id].smn+=tre[sn].smn;
	if(tre[id].mn==tre[sn|1].mn)tre[id].smn+=tre[sn|1].smn;
	if(tre[id].mx==tre[sn].mx)tre[id].smx+=tre[sn].smx;
	if(tre[id].mx==tre[sn|1].mx)tre[id].smx+=tre[sn|1].smx;
}void chgpth(TY x){for(;x;x=fa[tp[x]]){u=dfn[tp[x]];v=dfn[x];chg(0,n,1);}}
int main(){
	fOR(i,1,n){
		u=qr();v=qr();S+=(w[i]=qr());
		addedge(i<<1);u^=v^=u^=v;addedge(i<<1|1);
	}dfs(1);v=0;dfs2(tp[1]=1);build(0,n,1);
	T=qr();while(T--){
		switch(getc()){
			case '+':k=1;chgpth(qr());break;
			case '-':k=-1;chgpth(qr());break;
			default:if(tre[1].mx==0)printf("0\n");//特判没有黑点
				else qw(S-tre[1].smn-tre[1].smx,'\n');
		}
	}return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给出一个 $n$ 个点的树，边有边权。有 $q$ 次操作，你需要维护一个点集，支持：

- `+ x` 将 $x$ 加入到点集。
- `- x` 在点集中删除 $x$。
- `?` 询问从一个点出发，经过所有点集中的元素，最终到达点集中的一个元素的最短距离。

$1 \leq n,q \leq 10^5$

## 思路

首先考虑如果给出了点集，如何回答询问。

通常的思路是建出点集的虚树，然后按照 dfn 序走。

但是就会出现一个问题，dfn 序最大的到达 dfn 序最小的不一定不佳。

于是你就考虑把它也算进来。

一种朴素的思路就是把 dfn 相邻的点的距离全部加起来，但这样最短路一共就走了两次。于是除以二就好了。

于是得出公式：点集 $p$ 排序后，询问答案为：

$$
\frac{1}{2}\sum_{k=1}^{|p|} \text{dis}(p_k,p_{(k\bmod |p|) + 1})
$$

然后考虑如何解决本问题。如果使用平衡树维护点集，则我们不需要考虑 $p_{|p|}+p_1$ 的问题，最后加就好了。于是只需要维护相邻元素的距离和。

如何维护呢？插入时找到这个数的前驱后继，分裂。删除就倒过来。不过需要注意有些点可能没有前驱或后继的情况。

时间复杂度 $O(q\log n)$ 可以通过本题。

至于平衡树 `pb_ds` 即可，据说用 `set` 也行。

## 代码

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
#define debug(fmt,...) do{fprintf(stderr,fmt,##__VA_ARGS__);fprintf(stderr,"\n");}while(0)
#define error(expr,fmt,...) do{if((expr)){debug(fmt,##__VA_ARGS__);exit(0);}}while(0)
using namespace std;

const int N = 1e5+5;

int n,q;

struct edge{
    int nxt,to,w;
} g[N<<1];
int head[N],ec;

void add(int u,int v,int w){
    g[++ec].nxt=head[u];
    g[ec].to=v;
    g[ec].w=w;
    head[u]=ec;
}

int dep[N],siz[N],dis[N],son[N],top[N],father[N],dfn[N],dfntot;

void dfs1(int u,int fa){
    dep[u] = dep[fa] + 1;
    siz[u] = 1;father[u] = fa;
    dfn[u] = ++dfntot;
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa) continue;
        dis[v] = dis[u] + g[i].w;
        dfs1(v,u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u,int fa){
    if(son[u]){
        top[son[u]] = top[u];
        dfs2(son[u], u);
    }
    for(int i=head[u];i;i=g[i].nxt){
        int v = g[i].to;
        if(v == fa || v == son[u]) continue;
        top[v] = v;
        dfs2(v,u);
    }
}


int lca(int x,int y){
    int fx=top[x],fy=top[y];
    while(fx != fy){
        if(dep[fx] < dep[fy]){
            swap(fx,fy);
            swap(x,y);
        }
        x=father[fx];
        fx=top[x];
    }
    return dep[x]<dep[y]?x:y;
}

inline int d(int x,int y){
    return dis[x] + dis[y] - (dis[lca(x,y)]<<1);
}

struct cmp{
    bool operator()(const int &x, const int &y) const {
        return dfn[x] < dfn[y];
    }
};

template<class T, class Compare = std::less<T> >
class BalancedTree{
private: 
    __gnu_pbds::tree<T, __gnu_pbds::null_type,Compare, __gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> tree;
public:
    void insert(T x){tree.insert(x);}
    bool erase(T x){return tree.erase(x);}
    int rnk(T x){return tree.order_of_key(x)+1;}
    T kth(int x){return *tree.find_by_order(x-1);}
    int size(){return tree.size();}
    bool empty(){return tree.empty();}
};

BalancedTree<int,cmp> tree;
int ans;

void insert(int x){
    if(tree.empty()){
        tree.insert(x);
        return;
    }
    tree.insert(x);
    int rnk = tree.rnk(x);
    if(rnk == 1){
        int suf = tree.kth(rnk + 1);
        ans += d(x, suf);
        return;
    }
    if(rnk == tree.size()){
        int pre = tree.kth(rnk - 1);
        ans += d(x, pre);
        return;
    }
    int pre = tree.kth(rnk - 1);
    int suf = tree.kth(rnk + 1);
    ans -= d(pre, suf);
    ans += d(pre, x);
    ans += d(x, suf);
}

void erase(int x){
    if(tree.size() == 1){
        tree.erase(x);
        return;
    }
    int rnk = tree.rnk(x);
    if(rnk == 1){
        int suf = tree.kth(rnk + 1);
        ans -= d(x, suf);
        tree.erase(x);
        return;
    }
    if(rnk == tree.size()){
        int pre = tree.kth(rnk - 1);
        ans -= d(x, pre);
        tree.erase(x);
        return;
    }
    int pre = tree.kth(rnk - 1);
    int suf = tree.kth(rnk + 1);
    ans += d(pre, suf);
    ans -= d(pre, x);
    ans -= d(x, suf);
    tree.erase(x);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1,u,v,w;i<n;i++){
        cin>>u>>v>>w;
        add(u,v,w);add(v,u,w);
    }
    top[1] = 1;
    dfs1(1, 0);dfs2(1, 0);
    cin>>q;
    while(q--){
        char op;int x;
        cin>>op;
        if(op == '+'){
            cin>>x;
            insert(x);
        }
        if(op == '-'){
            cin>>x;
            erase(x);
        }
        if(op == '?'){
            cout<<((ans + d(tree.kth(tree.size()), tree.kth(1)))>>1)<<'\n';
        }
    }
    return 0;
}

// If you missed the train I'm on,
// You will know that I am gone,
// You can hear the whistle blow a hundred miles.
// ---- Justin Timberlake Five Hundred Miles

```

---

## 作者：荣一鸣 (赞：1)

做这道题我们要知道一点，就是关于dfs序的一个特性。

如果我们要算任意几个点相连的总长（树上），我们可以将这几个点按dfs排序，

然后向的点两两取到其lca的长度，再加上最后一个点到第一个点的lca的长度，最后再除以二。

至于为什么，我们可以随意画一棵树，然后可以看出，我们假设从dfs序的第一个点开始，

向后一个一个走，那么就是先走到与下一个点的lca再走到下一个点，最后从最后一个点走回到第一个点。

我们可以看到因为是按dfs序走，所以一个边最多（也一定）经过两次（下去一次回来一次），

所以就将所有要被选的点都走了两遍，除以二就是我们要求的总长

但是每次都讲长度求一边太慢了，也不能用记忆化，那就要想另一个办法了。

我们可以发现，每次+的时候就是将某一个点插入**以排好dfs序的序列中**

而与该点有关就只有他的前一个点和后一个点，我们要将这两个点的长度减去，再把新生成的两个长度加上

-是同样的操作

最后就是怎么维护这个序列，这可以用STL里的set，二叉排序树可以解决。

注意答案要用 long long

下面上代码

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,fa[100010][20],cc[100010],ne[100010],cnt,dep[100010],lg[100010];
ll le[100010][20],ans;
vector<int> g[100010],w[100010];
set<int> q;

inline int read(){//快读
	char c=getchar();int u=0,f=1;
	while(c<'0'||c>'9'){if(c=='-') f=-1;else f=1;c=getchar();}
	while(c<='9'&&c>='0'){u*=10;u+=c-'0';c=getchar();}
	return u*f;
}

void dfs(int u,int d){
	cc[u]=++cnt;ne[cnt]=u;dep[u]=d;//cc里存dfs序，ne里存dfs对应的点
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i],l=w[u][i];
		if(fa[u][0]==v) continue;
		fa[v][0]=u;
		le[v][0]=l;
		dfs(v,d+1);
	}
}

void init(){//倍增
	for(int i=0,j=1;j<=n;i++,j<<=1) lg[j]=i;
	for(int i=3;i<=n;i++) if(lg[i]==0) lg[i]=lg[i-1];
	for(int l=1;(1<<l)<=n;l++)
		for(int i=1;i<=n;i++)
			fa[i][l]=fa[fa[i][l-1]][l-1],le[i][l]=le[i][l-1]+le[fa[i][l-1]][l-1];
}

ll lca(int x,int y){//lca
	ll sum=0;
	if(dep[x]>dep[y]) swap(x,y);
	for(int l=lg[dep[y]-dep[x]];l>=0;l--){
		if(dep[fa[y][l]]>=dep[x]){
			sum+=le[y][l];
			y=fa[y][l];
		}
	}
	if(x==y) return sum;
	for(int l=lg[dep[x]];l>=0;l--){
		if(fa[x][l]!=fa[y][l]){
			sum+=le[x][l]+le[y][l];
			x=fa[x][l];
			y=fa[y][l];
		}
	}
	return le[x][0]+le[y][0]+sum;
}

int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x,y,l;
		x=read(),y=read(),l=read();
		g[x].push_back(y);g[y].push_back(x);
		w[x].push_back(l);w[y].push_back(l);
	}
	fa[1][0]=1;le[1][0]=0;
	dfs(1,1);
	init();
	scanf("%d",&m);
	while(m--){
		char c;int x;
		scanf("%c",&c);
		while(c!='?'&&c!='+'&&c!='-') scanf("%c",&c);//scanf会出现读入换行符等的问题，所以这么用
		if(c=='?') printf("%lld\n",ans/2);
		else if(c=='+'){
			scanf("%d",&x);
			q.insert(cc[x]);
			if(q.size()>=3){//如果已经有两个三个及以上的数在里面，所以要分开做
				set<int>::iterator st=q.find(cc[x]),pre,nex;
				if(st==q.begin()) pre=q.end();
				else pre=st;
				pre--;
				nex=st;
				if((++nex)==q.end()) nex=q.begin();
				ans+=lca(ne[*pre],ne[*st])+lca(ne[*st],ne[*nex])-lca(ne[*nex],ne[*pre]);
			}
			else if(q.size()==2){//两个点直接求
				set<int>::iterator st=q.begin(),nex=q.begin();
				nex++;
				ans+=lca(ne[*st],ne[*nex])*2;//注意乘2！！！！
			}
		}
		else{
			scanf("%d",&x);
			if(q.size()>=3){//删去和加上一样
				set<int>::iterator st=q.find(cc[x]),pre,nex;
				if(st==q.begin()) pre=q.end();
				else pre=st;
				pre--;
				nex=st;
				if((++nex)==q.end()) nex=q.begin();
				ans-=lca(ne[*pre],ne[*st])+lca(ne[*st],ne[*nex])-lca(ne[*nex],ne[*pre]);
			}
			else ans=0;
			q.erase(cc[x]);
		}
	}
}
```

---

## 作者：ivyjiao (赞：0)

一本通提高篇的题居然还能写题解。

双倍经验：[P3320 [SDOI2015] 寻宝游戏](https://www.luogu.com.cn/problem/P3320)。

---

Cloudflare 176E /cf

[AC 记录](https://codeforces.com/problemset/submission/176/276857626)。

---

我们先看 P3320。

结论很好猜，模拟一下走的路径就明白了：

假设下图中，$4,5,8$ 号节点有宝物。

![](https://cdn.luogu.com.cn/upload/image_hosting/jm23r9ta.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

红色路径就是我们来时走过的路径。如果我们算上返回时走的路径，那么我们经过的路径经过且仅经过两次。

此时~~根据直觉~~，能知道这条路径与 LCA 有关，于是我们先敲一个板子。

```cpp
void dfs(int u,int fa,int w){
    dep[u]=dep[fa]+1;
    dis[u]=dis[fa]+w;
    f[u][0]=fa;
    for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i].se,w=G[u][i].fi;
        if(v==fa) continue;
        dfs(v,u,w);
    }
}
int lca(int x,int y){
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    }
    if(x==y) return x;
    for(int i=20;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int getdis(int x,int y){
    return dis[x]+dis[y]-2*dis[lca(x,y)];
}
```

然后进一步分析。我们先假设只有 $(4,5)$ 一对点（单程）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0ghmqqai.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我们发现，结合 LCA，从 $4$ 到 $5$ 的路径长度可以表示为 $dis_4+dis_5-2\times dis_{2}=dis_4+dis_5-2\times dis_{lca_{4,5}}$。

对于 $(5,8)$，$(4,8)$ 两对点，也是如此。

但是我们还发现，如果把宝物点的数量继续增多，那么点对的顺序将不能随意变化。模拟之后，我们发现点对的顺序仅仅和点的 dfs 序有关，且最终 $n$ 个点组成 $n$ 个点对，拆开后变成一个环（因为最终要回到最开始的点）。实际上，原图点的顺序就是 dfs 序。

我们再假设原图中 $9$ 号点也有宝物，那么 $4$ 个点对分别是 $(4,5),(5,8),(8,9),(9,4)$。路径如下（往返）：

![](https://cdn.luogu.com.cn/upload/image_hosting/66hfckwq.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

设 $dist_{u,v}=dis_u+dis_v-2\times dis_{lca_{u,v}}$，$a_i$ 为字典序为第 $i$ 大的宝物点，则 $ans=dist_{a_1,a_2}+dist_{a_2,a_3}+\cdots+dist_{a_{n-1},a_n}+dist_{a_n,a_1}$。动态维护 $ans$ 即可。

dfs 序的顺序是很好维护的，用 set 维护即可，也可以用 rb_tree_tag。

对于本题，由于我们经过的路径经过且仅经过两次，而本题每条路径只需要算一遍，所以直接将答案 $\div 2$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second
#define int long long
using namespace std;
int n,m,x,y,z,t,dep[100001],dis[100001],dfn[100001],f[100001][21],sum,ans;
char op;
bool vis[100001];
vector<PII>G[100001];
set<PII>st;
void dfs(int u,int fa,int w){
    dep[u]=dep[fa]+1;
    dis[u]=dis[fa]+w;
    dfn[u]=++sum;
    f[u][0]=fa;
    for(int i=1;i<=20;i++) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i].se,w=G[u][i].fi;
        if(v==fa) continue;
        dfs(v,u,w);
    }
}
int lca(int x,int y){
    if(x==y) return x;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--){
        if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    }
    if(x==y) return x;
    for(int i=20;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int getdis(int x,int y){
    return dis[x]+dis[y]-2*dis[lca(x,y)];
}
signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>x>>y>>z;
        G[x].push_back({z,y});
        G[y].push_back({z,x});
    }
    dfs(1,0,0);
    cin>>m;
    while(m--){
        cin>>op;
        if(op=='+'||op=='-'){
            cin>>t;
            vis[t]=!vis[t];
            if(vis[t]) st.insert({dfn[t],t});
            auto it1=st.lower_bound({dfn[t],t}),it2=st.upper_bound({dfn[t],t});
            int a=(it1==st.begin()? (*--st.end()).se:(*--it1).se);
            int b=(it2==st.end()? (*st.begin()).se:(*it2).se);
            swap(a,b);
            if(!vis[t]) st.erase({dfn[t],t});
            int d=getdis(t,a)+getdis(t,b)-getdis(a,b);
            if(vis[t]) ans+=d;
            else ans-=d;
        }
        else cout<<ans/2<<endl;
    }
}
```

---

## 作者：IkunTeddy (赞：0)

# 题目分析

现在就是考虑如何用最少的边把这些点连起来，我们发现这好像就是[P3320 [SDOI2015] 寻宝游戏](https://www.luogu.com.cn/problem/P3320)。

按照 dfs 序的大小关系，由小到大去走点一定最优，所以我们用一个 set 维护相邻两点的距离和即可。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//
const int maxn=1e5+10;
int n,q;
ll ans;
struct Edge{
	int v,w,next;
}edge[maxn<<1];
int head[maxn],tot;
void add_edge(int u,int v,int w){
	edge[++tot].v=v;
	edge[tot].w=w;
	edge[tot].next=head[u];
	head[u]=tot;
}
ll dis[maxn];
int fa[maxn],dfn[maxn],dfncnt,st[maxn][20],Log[maxn],vis[maxn];
void dfs(int u,int f){
	fa[u]=f;
	dfn[u]=++dfncnt;
	for(int i=head[u];i;i=edge[i].next){
		int v=edge[i].v,w=edge[i].w;
		if(v==fa[u])continue ;
		dis[v]=dis[u]+w;
		dfs(v,u);
	}
}
int get(int x,int y){return dfn[x]<dfn[y]?x:y;}
void init_ST(){
	Log[0]=-1;
	for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)st[dfn[i]][0]=fa[i];
	for(int j=1;j<=Log[n];j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=get(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int LCA(int x,int y){
	if(x==y)return x;
	if(dfn[x]>dfn[y])swap(x,y);
	int l=dfn[x]+1,r=dfn[y];
	int k=Log[r-l+1];
	return get(st[l][k],st[r-(1<<k)+1][k]);
}
ll dist(int x,int y){return dis[x]+dis[y]-2*dis[LCA(x,y)];}
struct SET{
	int x;
	bool operator < (const SET &it)const{
		return dfn[x]<dfn[it.x];
	}
};
set<SET>s;
#define Set set<SET>::iterator
void insert(int x){
	Set it=s.insert({x}).first,pre,nxt;
	pre=nxt=it;
	pre--,nxt++;
	if(pre!=s.begin()&&nxt!=s.end())ans-=dist(pre->x,nxt->x);
	if(pre!=s.begin())ans+=dist(pre->x,x);
	if(nxt!=s.end())ans+=dist(x,nxt->x);
}
void delet(int x){
	Set it=s.lower_bound({x}),pre,nxt;
	pre=nxt=it;
	pre--,nxt++;
	if(pre!=s.begin()&&nxt!=s.end())ans+=dist(pre->x,nxt->x);
	if(pre!=s.begin())ans-=dist(pre->x,x);
	if(nxt!=s.end())ans-=dist(x,nxt->x);
	s.erase(it);
}
ll getsum(){ //计算头尾
	if(s.size()<3)return 0;
	Set head=s.begin(),tail=s.end();
	head++,tail--;
	return dist(head->x,tail->x);
}
int main(){
	cin>>n;
	s.insert({0});
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	init_ST();
	cin>>q;
	while(q--){
		char op;
		int u;
		cin>>op;
		if(op=='+'){
			cin>>u;
			insert(u);
			vis[u]=1;
		}else if(op=='-'){
			cin>>u;
			delet(u);
			vis[u]=0;
		}else{
			cout<<(ans+getsum())/2<<'\n';
		}
	}
	
	return 0;
}
```

---

## 作者：MSavannah (赞：0)

**Statement** 

给定一棵树，有三种操作：

1. 白点变黑点。
2. 黑点变白点。
3. 查询包含所有黑点的最小连通块中的边权和。

一开始所有点都是白点。

**Solution**

观察性质，我们先求出树上每个点的 dfs 序。发现，如果我们有 $x$ 个点是黑点，将这些黑点按照 dfs 序排序，那么包含这 $x$ 个黑点的最小连通块的边权和为：

$$[dis(dfn_1,dfn_2)+\cdots+dis(dfn_{x-1},dfn_x)+dis(dfn_x,dfn_1)]\times \frac{1}{2}$$

知道这个式子之后直接用 set 维护黑点点集，对于插入操作，对于一个点 $x$，设在集合中第一个比他小的数是 $pre$，第一个比它大的是 $nxt$。每次更新，加入 $dis(pre,x)+dis(x,nxt)$ 的贡献，同时删去之前 $dis(pre,nxt)$ 的贡献。删除操作同理，把插入操作反过来就是了。

最后就是一些边界问题实现的时候需要注意。

[code](https://www.luogu.com.cn/record/161173159 "code")

---

## 作者：syLph (赞：0)

是一道双倍经验题目。
 
 一棵  $n$ 个节点的树，边有边权。

每个点可能是黑点，每次操作改变一个点是否是黑点。

求所有关键点形成的极小连通子树的边权和的两倍。

显然我们有一个结论：假如我们把所有的黑点按照时间戳进行排序，那么上述的值相当于 $\sum_{i=1}^{k} \operatorname{dist}(a_1,a_k)$。

那么我们使用 set 来维护黑点的时间戳，然后每次插入或是删除一个点，相当于就是：

不妨设当前进行修改的节点编号为 $x$，那么容易求出在时间戳意义上的前驱和后继，不妨设其为 $y$ 和 $z$，则此时答案就会加上 $\operatorname{dist}{(x,y)}+\operatorname{dist}{(x,z)}-\operatorname{dist}{(y,z)}$。

然后我们正常倍增求 lca 即可，顺便统计深度和距离。

注意数据范围。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 200010,maxm = 22;
int nxt[maxn],head[maxn],ver[maxn],edg[maxn],dep[maxn],f[maxn][maxm],dfn[maxn];
int n,m,dist[maxn],ins[maxn],idfn[maxn],ans = 0,tot = 1,num,T;
inline int read(){
	int x = 0,f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while('0' <= c && c <= '9') x = x * 10 + c - '0',c = getchar();
	return x * f;
} 
inline void add(int x,int y,int z){ver[++tot] = y,nxt[tot] = head[x],edg[tot] = z,head[x] = tot;}
void dfs(int x,int fa){
	dfn[x] = ++num,idfn[num] = x,dep[x] = dep[f[x][0] = fa] + 1;
	for(int j = 1 ; j <= T ; j ++) f[x][j] = f[f[x][j-1]][j-1];
	for(int i = head[x] ; i ; i = nxt[i]) if(ver[i] != fa) dist[ver[i]] = dist[x] + edg[i],dfs(ver[i],x);
}
inline int lca(int x,int y){
	if(dep[x] > dep[y]) swap(x,y);
	for(int j = T ; j >= 0 ; j --) if(dep[f[y][j]] >= dep[x]) y = f[y][j];
	if(x == y) return x;
	for(int j = T ; j >= 0 ; j --) if(f[x][j] != f[y][j]) x = f[x][j],y = f[y][j];
	return f[x][0];
}
inline int Dist(int x,int y){return dist[x] + dist[y] - 2 * dist[lca(x,y)];}
set<int> ddfn;
set<int>::iterator it;
 main(){
	//freopen("a.cpp","r",stdin);
	n = read(),m = read();T = log(n) / log(2) + 1;
	for(int i = 1 ; i < n ; i ++){
		int u = read(),v = read(),w = read();
		add(u,v,w),add(v,u,w);
	}dep[1] = 1,dfs(1,0);
	for(int j = 1 ; j <= m ; j ++){
		int x = read(),y,z,d; x = dfn[x];
		if(!ins[idfn[x]]) ddfn.insert(x);
		y = idfn[(it = ddfn.lower_bound(x)) == ddfn.begin() ? *--ddfn.end() : *--it];
		z = idfn[(it = ddfn.upper_bound(x)) == ddfn.end() ? *ddfn.begin() : *it];
		if(ins[idfn[x]]) ddfn.erase(x);
		x = idfn[x],d = Dist(x,y) + Dist(x,z) - Dist(y,z);
		if(!ins[x]) ins[x] = 1,ans += d;
		else ins[x] = 0,ans -= d;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：hejianxing (赞：0)

[link](https://www.luogu.com.cn/problem/CF176E)

双倍经验 [P3320 [SDOI2015] 寻宝游戏](https://www.luogu.com.cn/problem/P3320)。

# 题意

给定一棵带权树，最初所有点是白色，每次操作可以改变一个点的颜色，询问黑点的导出子图的边权和。

# 题解

考虑一个结论：黑点导出子图的边权和，将黑点按 dfs 序排，边权和为 $\frac 1 2(dis(a_1,a_2)+\cdots+dis(a_{k-1},a_k)+dis(a_k,a_1))$。

考虑一条边被计算，当且仅当这条边两边有黑点。这条边两个方向的贡献分别计算了一次。由于按 $dfs$ 序排列，这种方法是不重不漏的。

于是就简单了。维护黑点的 dfs 序列，插入时相当于减去 $dis(pre,suf)$，加上 $dis(pre,x)+dis(x,suf)$。删除相反。

可以使用 `set` 实现。

时间复杂度 $O(n\log n)$。

# 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;
int n, q, cnt = 0, fir[N], nxt[N << 1], to[N << 1], val[N << 1], dfn[N], tot = 0, top[N], son[N], sz[N], fa[N], dep[N], vdfn[N];
LL sum = 0, d[N];
set<int> s;
void ade(int u, int v, int w) {
    cnt++, nxt[cnt] = fir[u], fir[u] = cnt, to[cnt] = v, val[cnt] = w;
    cnt++, nxt[cnt] = fir[v], fir[v] = cnt, to[cnt] = u, val[cnt] = w;
}
void dfs1(int r) {
    sz[r] = 1, dep[r] = dep[fa[r]] + 1;
    for (int i = fir[r]; i; i = nxt[i])
        if (to[i] != fa[r]) {
            fa[to[i]] = r, d[to[i]] = d[r] + val[i], dfs1(to[i]), sz[r] += sz[to[i]];
            if (sz[to[i]] > sz[son[r]]) son[r] = to[i];
        }
}
void dfs2(int r, int tp) {
    dfn[r] = ++tot, vdfn[tot] = r, top[r] = tp;
    if (son[r]) dfs2(son[r], tp);
    for (int i = fir[r]; i; i = nxt[i]) if (to[i] != fa[r] && to[i] != son[r]) dfs2(to[i], to[i]);
}
int LCA(int u, int v) {
    for (; top[u] != top[v]; u = fa[top[u]]) if (dep[top[u]] < dep[top[v]]) swap(u, v);
    return dep[u] < dep[v] ? u : v;
}
LL dis(int u, int v) { return d[u] + d[v] - 2 * d[LCA(u, v)]; }
int main() {
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; i++) scanf("%d%d%d", &u, &v, &w), ade(u, v, w);
    dfs1(1), dfs2(1, 1);
    scanf("%d", &q);
    char sin[2];
    for (int i = 1, x; i <= q; i++) {
        scanf("%s", sin + 1);
        if (sin[1] == '+') {
            scanf("%d", &x);
            if (!s.size()) s.insert(dfn[x]);
            else {
                auto suf = s.upper_bound(dfn[x]), pre = suf;
                if (suf != s.begin()) pre--;
                else pre = s.end(), pre--;
                if (suf == s.end()) suf = s.begin();
                sum -= dis(vdfn[*pre], vdfn[*suf]), sum += dis(vdfn[*pre], x) + dis(x, vdfn[*suf]), s.insert(dfn[x]);
            }
        } else if (sin[1] == '-') {
            scanf("%d", &x);
            if (s.size() == 1) s.erase(dfn[x]);
            else {
                auto it = s.find(dfn[x]), pre = it, suf = it;
                if (it != s.begin()) pre--;
                else pre = s.end(), pre--;
                suf++;
                if (suf == s.end()) suf = s.begin();
                sum += dis(vdfn[*pre], vdfn[*suf]), sum -= dis(vdfn[*pre], vdfn[*it]) + dis(vdfn[*it], vdfn[*suf]), s.erase(it);
            }
        } else printf("%lld\n", sum >> 1);
    }
    return 0;
}
```

---

## 作者：SJH__qwq (赞：0)

首先有一个性质：在树 $T$ 上点集 $V$ 固定的时候，这些点的导出子树的边权和固定，且设 $V=\lbrace U_1,U_2,U_3,\ldots,U_k\rbrace$，则先将这些点按照 `dfn` 的顺序排序，那么 $V$ 关于树 $T$ 的导出子树的边权和一定为 $\frac{\sum\limits_{i=1}^n D(U_i,U_{i\bmod n+1})}{2}$，其中 $D(u,v)$ 的定义为树 $T$ 上 $u$ 和 $v$ 两点的简单路径上经过的所有边的边权之和。

那么问题就简单了。首先跑一遍树上倍增求出树上任意两点的距离，然后对于每一个查询操作直接在更新点集的时候顺便预处理答案，而对于插入点的时候用一个平衡树来按照 `dfn` 为排序值维护出一个点的前驱 / 后继，直接用前驱 / 后继来更新这个点对答案的贡献即可。删除一个点同理。

时间复杂度为 $O(n\log n)$。很好写。

---

## 作者：Acc_Robin (赞：0)

# CF176E Archaeology 题解

[更高更妙的观看体验](https://accrobin.github.io/2021/11/09/solver/176E/)

[传送门](https://www.luogu.com.cn/problem/CF176E)

## 题意

给定一棵 $n$ 个点的带权树，要求维护一个点集支持以下操作：

- 加入一个点
- 删除一个点
- 输出当前点集构成虚树的边权和

## 题解

虚树板子，我们使用 `set` 维护当前点集，内部按照 dfs 序排序。同时直接维护虚树边权和的二倍。

- 插入操作：设当前加入的点为 $x$ ，前驱是 $a$ ，后继是 $b$，那么加入这个点对答案的贡献就是 $\operatorname{dis}(a,x)+\operatorname{dis}(x,b)-\operatorname{dis}(a,b)$
- 删除操作：删除一个点的贡献就是插入操作的相反数。
- 输出操作：注意，上面维护的答案会把每条边计数两次，所以输出时要除以二。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
enum{N=100009};
using ll=long long;
set<pair<int,int>>s;
vector<pair<int,int>>G[N];
int p[N],d[N],f[N][20],t;
ll l[N],ans;
void dfs(int u){
 p[u]=++t,d[u]=d[*f[u]]+1;
 for(int i=0;f[u][i];++i)f[u][i+1]=f[f[u][i]][i];
 for(auto[v,w]:G[u])if(v!=*f[u])l[v]=l[u]+w,*f[v]=u,dfs(v);
}
auto LCA=[](int x,int y){
 if(d[x]<d[y])swap(x,y);
 for(int i=18;~i;--i)if(d[f[x][i]]>=d[y])x=f[x][i];
 if(x==y)return x;
 for(int i=18;~i;--i)if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
 return *f[x];
};
auto ds=[](int x,int y){return l[x]+l[y]-2*l[LCA(x,y)];};
int main(){
 ios::sync_with_stdio(0),cin.tie(0);
 int n,m,i,x,y,z;char op[3];set<pair<int,int>>::iterator it,i1,i2;
 for(cin>>n,i=1;i<n;++i)cin>>x>>y>>z,G[x].emplace_back(y,z),G[y].emplace_back(x,z);
 for(dfs(1),cin>>m;m--;)if(cin>>op,*op=='?')cout<<ans/2<<'\n';
 else{
  cin>>x,it=*op=='+'?s.emplace(p[x],x).first:s.find({p[x],x});
  i1=it==s.begin()?--s.end():prev(it),i2=it==--s.end()?s.begin():next(it);
  if(*op=='-')s.erase(it);
  ans+=(*op=='+'?1:-1)*(ds(i1->second,x)+ds(x,i2->second)-ds(i1->second,i2->second));
 }
}
```

## 小细节

在求前驱 / 后继时注意：我们需要的是 **循环** 前驱 / 后继，也就是说：最后一个点的后继是第一个点，第一个点的前驱是最后一个点。



---

