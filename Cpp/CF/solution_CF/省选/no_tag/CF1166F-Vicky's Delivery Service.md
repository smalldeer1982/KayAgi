# Vicky's Delivery Service

## 题目描述

在一个魔法世界里，有 $n$ 个城市，编号为 $1, 2, \dots, n$。其中一些城市之间通过有颜色的魔法道路相连。由于魔法不稳定，任何时刻都有可能出现新的道路连接两个城市。

女巫 Vicky 被要求在一些城市对之间进行配送。然而，Vicky 还是个新手，她只能在能够通过“双彩虹”从起点城市到达终点城市时完成配送。一个“双彩虹”是指满足以下条件的城市序列 $c_1, c_2, \dots, c_k$：

- 对于每个 $i$，$1 \le i \le k - 1$，城市 $c_i$ 和 $c_{i+1}$ 之间有一条道路相连。
- 对于每个 $i$，$1 \le i \le \frac{k-1}{2}$，连接 $c_{2i}$ 与 $c_{2i-1}$ 的道路和连接 $c_{2i}$ 与 $c_{2i+1}$ 的道路颜色相同。

例如，如果 $k = 5$，那么 $c_1$ 和 $c_2$ 之间的道路颜色必须与 $c_2$ 和 $c_3$ 之间的道路颜色相同，$c_3$ 和 $c_4$ 之间的道路颜色必须与 $c_4$ 和 $c_5$ 之间的道路颜色相同。

Vicky 有一个按时间顺序排列的事件列表，每个事件要么是她需要完成的一次配送，要么是有一条新道路出现。请帮助她判断每次配送是否能够完成。

## 说明/提示

下图对应样例输入。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166F/d11935603974d3047daa71992c35a66821570525.png)

对于第一次配送，Vicky 可以使用序列 $1, 2, 3, 4$，这是一个“双彩虹”。但她无法完成第二次配送，因为她只能到达城市 $3$。在添加了城市 $1$ 和 $3$ 之间的道路后，她可以通过序列 $4, 3, 1$ 完成从城市 $4$ 到城市 $1$ 的配送。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 2 4
1 2 1
2 3 1
3 4 2
? 1 4
? 4 1
+ 3 1 2
? 4 1
```

### 输出

```
Yes
No
Yes
```

# 题解

## 作者：81179332_ (赞：5)

翻译有点问题，彩虹路不一定要是长度为 $n$ 的，是任意长度的

我们首先可以想到 对于点 $x$，它连出去的同种颜色连着的点都是可以相互到达的，所以我们可以将它们用并查集合并

我们要快速查询一个点连出去某种颜色的边，则我们用 `map<int,vector<int> >` 来存边

这样我们处理完了走偶数步的情况，对于走奇数步的情况，最后一步是随便走的

我们可以对每个集合存一个 `set`，存集合中能一步走到的点，启发式合并即可

```cpp
const int N = 100010;
map<int,vector<int> > v[N];
set<int> s[N];int fa[N];
int getf(int u) { return fa[u] == u ? u : fa[u] = getf(fa[u]); }
void merge(int u,int v)
{
	u = getf(u),v = getf(v);
	if(u != v)
	{
		if(s[u].size() < s[v].size()) swap(u,v);
		for(int i:s[v]) s[u].insert(i);fa[v] = u;
	}
}
void add_edge()
{
	int x = read(),y = read(),w = read();
	s[getf(x)].insert(y),s[getf(y)].insert(x);
	v[x][w].push_back(y),merge(y,v[x][w][0]);
	v[y][w].push_back(x),merge(x,v[y][w][0]);
}
void query()
{
	int x = read(),y = read();
	if(getf(x) == getf(y) || s[getf(x)].count(y)) puts("Yes");
	else puts("No");
}
int n,m,q;
int main()
{
	n = read(),m = read(),read(),q = read();
	for(int i = 1;i <= n;i++) fa[i] = i;
	while(m--) add_edge();
	while(q--)
	{
		char s[10];scanf("%s",s);
		if(s[0] == '?') query();
		else add_edge();
	}
	return 0;
}
```

---

## 作者：intel_core (赞：2)

由于彩虹路的前 $2 \lfloor\frac{n}{2}\rfloor$ 条路的特殊限制，考虑将一条彩虹路中颜色相同的边放在一起考虑。

具体地，若 $x \to z \to y$，两条边颜色相同，我们就把 $x$ 和 $y$ 放到一个并查集中。

这时可以发现 $x\to y$ 有彩虹路等价于 $x$ 和 $y$ 在一个并查集中或者 $x$ 所在的并查集中有点可以一步到 $y$。

用 `set` 维护并查集的邻接点集，启发式合并，复杂度 $O(n \log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=1e5+10;
int n,m,c,q,fa[NR],size[NR];
map<int,int>mp[NR];
set<int>s[NR];

int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	if(size[x]>size[y])swap(x,y);
	fa[x]=y;size[y]+=size[x];
	for(int k:s[x])s[y].insert(k);
	s[x].clear();
}
void add(int x,int y,int z){
	s[get(x)].insert(y);
	if(mp[x][z])merge(mp[x][z],y);
	else mp[x][z]=y;
}

int main(){
	cin>>n>>m>>c>>q;
	for(int i=1;i<=n;i++)fa[i]=i,size[i]=1;
	for(int i=1,x,y,z;i<=m;i++)
		scanf("%d%d%d",&x,&y,&z),add(x,y,z),add(y,x,z);
	while(q--){
		char opt;scanf(" %c",&opt);
		if(opt=='?'){
			int x,y;scanf(" %d %d",&x,&y);
			int x0=get(x),y0=get(y);
			if(x0==y0)puts("Yes");
			else if(s[x0].count(y))puts("Yes");
			else puts("No");
		}
		else{
			int x,y,z;scanf(" %d %d %d",&x,&y,&z);
			add(x,y,z);add(y,x,z);
		}
	}
	return 0;
} 
```

---

## 作者：hegm (赞：1)

好久没写博客了，正好复健一下。

考虑彩虹桥的本质，即第 $2i$ 条边和第 $2i-1$ 条边的颜色是一样的。**并且奇数长度的彩虹桥，对最后一条边颜色无限制。**

先简单的考虑偶数彩虹桥。

对于一个节点 $i$ 我们不妨维护出一个集合来表示只走偶数彩虹桥能到的点的集合。

这玩意可以用并查集维护。

具体的，对于新加入一条边 $(x,y,c)$ 我们先判断 $x$ 节点在此之前是否连接过 $c$ 颜色的边，如果有（将此边链接的点称为 $z$），我们将 $z$ 节点和 $y$ 节点的并查集连接起来。

原因如下：从 $z$ 点到 $y$ 点我们可以经过 $z \to x \to y$ ，由于我们维护的是偶数长度的彩虹边，因此到 $z$ 之前的路径也一定是偶数长度，无需考虑衔接问题。

同时，对于节点 $x$ ，只需对每个颜色记录一个出边即可，用 map 可以简单实现。记录一个出边即可将 $x$ 的所有同颜色出边对应点连接起来。

那么对于一次询问，我们只需考虑两点是否在同一个并查集里即可。

但是以上仅为偶数长度的彩虹桥，对于奇数的彩虹桥还需额外处理。

考虑对每个并查集节点存储一个 `set` 内部存储的是当前并查集内可以用偶数彩虹桥或者在此基础上额外再走一步所能到达的点集，显然此点集内部的点是并查集内所有点，以及向外走一圈所能到达的点构成的集合。

合并并查集的时候，使用按秩合并，容易证明 `set` 总大小为 $2(n+m)$。

### $\text{CODE}$

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define N 100005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,m,q,c;
int fa[N];
set<int> s[N]; 
map<int,int> mp[N];
int find(int x)
{
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
void merge(int a,int b)
{
	a=find(a);b=find(b);
	if(a==b)return ;
	if(s[a].size()>s[b].size())swap(a,b);
	fa[a]=b;for(auto x:s[a])s[b].insert(x);
}
int tot; 
signed main()
{
	n=read();m=read();c=read();q=read();
	for(int i=1;i<=n;i++)fa[i]=i,s[i].insert(i);
	for(int i=1,x,y,z;i<=m;i++)
	{
		x=read();y=read();z=read();
		if(!mp[x][z])mp[x][z]=y;
		else merge(y,mp[x][z]);
		if(!mp[y][z])mp[y][z]=x;
		else merge(x,mp[y][z]);
		s[find(x)].insert(y);
		s[find(y)].insert(x);
	}
	char c;
	for(int i=1,x,y,z;i<=q;i++)
	{
		c=getchar();
		if(c=='?')
		{
			x=read();y=read();tot++;
			find(x);
			if(s[fa[x]].find(y)!=s[fa[x]].end())cout<<"Yes\n";
			else cout<<"No\n";
		}
		else
		{
			x=read();y=read();z=read();
			if(!mp[x][z])mp[x][z]=y;
			else merge(y,mp[x][z]);
			if(!mp[y][z])mp[y][z]=x;
			else merge(x,mp[y][z]);
			s[find(x)].insert(y);
			s[find(y)].insert(x);
		}
	}
	return 0;
}

```

---

## 作者：qczrz6v4nhp6u (赞：1)

## Solution

发现彩虹路长度为偶数时比较好做，首先考虑彩虹路长度为偶数的情况：

考虑建一个新图，其中边 $(x,y)$ 存在表示存在 $p,z$，使得原图中存在两条边 $(x,p,z),(p,y,z)$，即 $x,y$ 间存在长度为 $2$ 的彩虹路。

容易发现，对于任意的长度为偶数的彩虹路的两端，它们在新图中一定是连通的。我们考虑使用并查集维护连通性。

加入一条边 $(x,y,z)$ 时，可以枚举边 $(x,p,z)$，将两条边拼起来就得到了一个长度为 $2$ 的彩虹路。在并查集中合并 $p,y$ 即可。

注意到对于所有在原图中满足边 $(x,p,z)$ 存在的 $p$，它们在新图中一定是连通的，于是我们只需要找任意一个满足条件的 $p$ 合并。

接下来考虑彩虹路长度为奇数的情况：

因为最后一步是随便走的，同时除去了最后一步后就是长度为偶数的情况，问题转化为是否存在一个点 $p$，使得原图中 $y,p$ 间有边且新图中 $p,x$ 连通。

这是一个容易解决的问题：对于新图中的每个连通块，维护连通块内所有点在原图中走一步到达的点集。对于上面转化的问题，我们查询 $x$ 对应的点集内是否存在 $y$ 即可。

另外在并查集合并的过程中，我们需要更新合并后的点集。使用启发式合并可以很轻松地做到这一点。

视 $n,m,q$ 同阶，则最终复杂度为 $O(n\log n)$。

注：遍历 set 的时间复杂度貌似是 $O(size)$（$size$ 为 set 大小）的。

## Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=x*10+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
const int N=1e5+5;
int n,m,c,q,f[N];
set<int>st[N];
int get(int x){return f[x]==x?x:f[x]=get(f[x]);}
void merge(int x,int y){
	x=get(x),y=get(y);
	if(x==y)return;
	if(st[x].size()>st[y].size())swap(x,y);
	for(auto &o:st[x])st[y].insert(o);
	st[x].clear();
	f[x]=y;
}
map<int,int>fir[N];
int at(int x,int y,int z){
	auto &o=fir[x][z];
	if(!o)o=y;
	return o;
}
void add(int x,int y,int z){
	st[get(x)].insert(y);
	st[get(y)].insert(x);
	merge(x,at(y,x,z));
	merge(y,at(x,y,z)); 
}
bool query(int x,int y){
	return get(x)==get(y)||st[get(x)].find(y)!=st[get(x)].end();
}
int main(){
	read(n,m,c,q);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1,x,y,z;i<=m;i++){
		read(x,y,z);
		add(x,y,z);
	}
	for(int i=1,x,y,z;i<=q;i++){
		char c=getchar();
		while(c!='+'&&c!='?')c=getchar();
		if(c=='+'){
			read(x,y,z);
			add(x,y,z);
		}
		else{
			read(x,y);
			puts(query(x,y)?"Yes":"No");
		}
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

先考虑路径长度为偶数，必然每条路径颜色相同。将每个点出发颜色相同的边走到的点放入同一个并查集中。这样只需要判断 $u$ 和 $v$ 是否在同一并查集中即可。

但路径长度也有可能为奇数，若是这样，最后一条边的颜色可能不同。维护并查集中每个根所在集合，以及这个点为根，多出来那条路颜色不同能到的点的集合。启发式合并即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <set>
#include <map>
using namespace std;

const int N = 1e5 + 5;

map<__int32, __int32> G[N];
set<__int32> st[N];
__int32 n, m, c, q;

vector<__int32> fa, sz;

function<void()> Init = []()
{
	fa.resize(n + 1);
	sz.resize(n + 1);
	for (auto i = 1; (i <=> n) <= 0; i++)
	{
		fa[i] = i;
		sz[i] = 1;
	}
};

function<__int32(__int32)> finds = [](auto u)
{
	if (fa[u] == u) [[unlikely]]
	{
		return u;
	}
	else [[likely]]
	{
		return fa[u] = finds(fa[u]);
	}
};

function<void(int, int)> merges = [](auto u, auto v)
{
	auto x = finds(u), y = finds(v);
	if ((x <=> y) == 0) return;
	if ((sz[x] <=> sz[y]) > 0) swap(x, y);
	sz[y] += sz[x];
	fa[x] = y;
	for_each(st[x].begin(), st[x].end(), [&](auto j)
		{
			st[y].insert(j);
		});
};

function<void(__int32, __int32, __int32)> Solve = [](auto x, auto y, auto z)
{
	st[finds(x)].insert(y);
	if (!G[x].count(z)) [[likely]]
	{
		G[x][z] = y;
	}
	else [[unlikely]]
	{
		merges(G[x][z], y);
	}
};

function<bool(__int32, __int32)> query = [](auto u, auto v)
{
	if (!(finds(u) ^ finds(v)) or st[finds(u)].count(v)) [[unlikely]]
	{
		return 1;
	}
	else [[likely]]
	{
		return 0;
	}
};

auto main() -> int
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> c >> q;
	Init();
	for (__int32 i{ 1 }; (i <=> m) <= 0; i++)
	{
		__int32 u, v, w;
		cin >> u >> v >> w;
		Solve(u, v, w);
		Solve(v, u, w);
	}
	for (__int32 i{ 1 }; (i <=> q) <= 0; i++)
	{
		char c;
		cin >> c;
		if (c == '?')
		{
			__int32 u, v;
			cin >> u >> v;
			if (bool p = query(u, v)) [[unlikely]]
			{
				cout << R"(Yes
)";
			}
			else [[likely]]
			{
				cout << R"(No
)";
			}
		}
		else
		{
			__int32 u, v, w;
			cin >> u >> v >> w;
			Solve(u, v, w);
			Solve(v, u, w);
		}
	}
	return 0;
}
```


---

## 作者：PCCP (赞：0)

## 胡言乱语：

并查集是维护无向图连通性相关问题的利器——PCCP（

个人认为这个题应该只有绿或者下位蓝的难度（

## 思考过程：

FBI Warning：阅读以下内容前，请保证您已理解题意。

我们不难发现，每一对相连的相同颜色的边，都有一个中心节点，从中心节点出发，将所有颜色相同的路径的终点合并到同一个连通块内即可，询问时查询两个点是否连通即可。

但是，还有一种情况是，路径边数为奇数时，最后一条边的颜色可以是任意颜色，也就是说，在这条合法路径上终点的前一个节点应当是和起点连通的，我们把和终点的点遍历一下看看有没有和起点在同一个连通块即可。（注意：题意要求的合法路径是第 $ 2i $ 条边和 $ 2i-1 $ 条边颜色相同，即最后一条边颜色任意，第一条不行）

但是如果只是这样，这题就不会是 Div.2F，也不会是紫题了，撑破天黄题了。

## 实现：

我们有了思路，按照并查集+建图+遍历的方法开始实现。

然后，恭喜你： T 飞了。

为什么呢？因为我们可以随随便便构造一个图，使得单次询问时，你遍历终点相连的点的时间复杂度达到 $ O(n) $，建图的时间复杂度达到 $ O(n^2) $，总时间复杂度达到惊人的 $ O(n^2) $（以下视 $ m $、$ n $ 和 $ q $ 同阶）。

考虑优化。我们想到，要同时优化建图和询问到接近 $ O(1) $ 的程度。对于每一次建图，我们不一定要把每一个和输入的颜色相同的边的端点和输入的另一个点都合并一次，只要合并其中一个即可。其次我们还可以利用数据结构保存当前节点的当前边颜色的上一次加入的点，要求这个数据结构可以确定第一和第二维，这个问题我在学术区发了帖子，[具体见这](https://www.luogu.com.cn/discuss/643242)。

经过我们的讨论，发现 ``` vector<vector<vector<int>>> ``` 和 ``` vector<int> x[N][N] ``` 都是不可行的，其他的读者可以自行尝试，我这里采用其他题解的 ``` map<int,vector<int>> ```。

最后用 ``` set<int> x ``` 维护一个连通块的连通点集，每次询问查询起点所在连通块的连通点集即可。

- 注意！不能维护与点相连的连通块集，考虑如下情况：设某一点所在连通块编号为 $ x $，某次加边合并后变为 $ fa_x $，又经历一次合并变为 $ fa_{fa_x} $。请问这种局面阁下又该怎样应对呢？

- 注意！记得把你之前写的屎山代码删干净！

- 注意！合并时要合并连通点集。路径压缩时不要，之前已经合并过了，再合并会超时。

预测时间复杂度：$ O(n\log_{2}{n}) $。

最后上代码：

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<set>
#include<vector>
#include<map>
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10;
const int M=4e5+10;
int n,m,c,q,fa[N],siz[N];
map<int,vector<int> > pos[N];
set<int> mp[N];
inline int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
inline void unify(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy){
		return;
	}
	if(siz[fx]<siz[fy]){
		swap(fx,fy);
	}
	fa[fy]=fx;
	siz[fx]+=siz[fy];
	set<int>::iterator it;
	for(it=mp[fy].begin();it!=mp[fy].end();it++){
		mp[fx].insert(*it);
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&c,&q);
	for(int i=1;i<=n;i++){
		fa[i]=i;
		siz[i]=1;
	}
	int x,y,z;
	char op;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		mp[find(x)].insert(y);
		mp[find(y)].insert(x);
		pos[x][z].push_back(y);
		unify(y,pos[x][z][0]);
		pos[y][z].push_back(x);
		unify(x,pos[y][z][0]);
	}
	while(q--){
		cin>>op;
		if(op!='?'&&op!='+'){
			cin>>op;
		}
		if(op=='+'){
			scanf("%d%d%d",&x,&y,&z);
			mp[find(x)].insert(y);
			mp[find(y)].insert(x);
			pos[x][z].push_back(y);
			unify(y,pos[x][z][0]);
			pos[y][z].push_back(x);
			unify(x,pos[y][z][0]);
		}
		else{
			scanf("%d%d",&x,&y);
			if(mp[find(x)].count(y)||find(x)==find(y)){
				printf("Yes\n");
			}
			else{
				printf("No\n");
			}
		}
	}
}
```

这么良心的题解，不点个赞再走？

---

## 作者：王熙文 (赞：0)

提供一种不同的解法。

## 思路

首先有一种思路是，构造一个新图，如果有一条路径 $x \to y \to z$ 且两条边的边权相等，则连接 $x,z$。这样对于查询，若路径长度为偶数，判断 $u,v$ 是否联通即可；若路径长度为奇数，则可以枚举 $v$ 的每一个相邻的点判断 $u$ 是否与它联通。

但是新图的边数会很大。注意到只需要判断连通性，所以对于一个点的所有边权为 $w$ 的边，并不需要两两连边，只需要将相邻的两个连边即可。这样边数就降下来了。

还有一个问题，查询时需要枚举一个点的相邻的点，若这个点的度数很大就会时间超限。考虑对度数根号分治，若度数 $\le B$，则 $\mathcal O(B)$ 遍历判断；否则这样的点最多只有 $\dfrac{m+q}{B}$ 个，可以将这些点单独处理。对于这样的每一个点，先将这个点与相邻的点在新图中连边，这样就不用遍历相邻的点了。后面的按照上面的方式做即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,q;
struct edge { int u,v,w; } ed[100010];
vector<int> e1[100010];
map<int,int> e2[100010];
int in[100010];
struct Query
{
	char op; int u,v,w;
} q1[100010];
int fa[100010]; int find(int x) { while(x!=fa[x]) x=fa[x]=fa[fa[x]]; return x; }
int ans[100010];
void add(int u,int v,int w)
{
	e1[u].push_back(v),e1[v].push_back(u);
	if(e2[u][w]!=0) fa[find(e2[u][w])]=find(v);
	if(e2[v][w]!=0) fa[find(e2[v][w])]=find(u);
	e2[u][w]=v,e2[v][w]=u;
}
int main()
{
	cin>>n>>m>>c>>q;
	for(int i=1; i<=m; ++i) cin>>ed[i].u>>ed[i].v>>ed[i].w,++in[ed[i].u],++in[ed[i].v];
	for(int i=1; i<=q; ++i)
	{
		cin>>q1[i].op;
		if(q1[i].op=='+') cin>>q1[i].u>>q1[i].v>>q1[i].w,++in[q1[i].u],++in[q1[i].v];
		if(q1[i].op=='?') cin>>q1[i].u>>q1[i].v;
	}
	memset(ans,-1,sizeof(ans));
	for(int i=1; i<=n; ++i)
	{
		if(in[i]<=500) continue;
		for(int j=1; j<=n; ++j) fa[j]=j,e2[j].clear();
		for(int j=1; j<=m; ++j) add(ed[j].u,ed[j].v,ed[j].w);
		for(int j:e1[i]) fa[find(i)]=find(j);
		int now=0;
		for(int j=1; j<=q; ++j)
		{
			if(q1[j].op=='+')
			{
				add(q1[j].u,q1[j].v,q1[j].w);
				if(q1[j].u==i || q1[j].v==i) fa[find(q1[j].u)]=find(q1[j].v);
			}
			if(q1[j].op=='?' && q1[j].v==i)
			{
				ans[j]=(find(q1[j].u)==find(i));
				++now;
			}
		}
	}
	for(int i=1; i<=n; ++i) fa[i]=i,e1[i].clear(),e2[i].clear(),e1[i].push_back(i);
	for(int i=1; i<=m; ++i) add(ed[i].u,ed[i].v,ed[i].w);
	for(int i=1; i<=q; ++i)
	{
		if(q1[i].op=='+') add(q1[i].u,q1[i].v,q1[i].w);
		if(q1[i].op=='?' && in[q1[i].v]<=500)
		{
			ans[i]=0;
			for(int j:e1[q1[i].v])
			{
				if(find(q1[i].u)==find(j)) { ans[i]=1; break; }
			}
		}
	}
	for(int i=1; i<=q; ++i) if(ans[i]!=-1) puts(ans[i]==1?"Yes":"No");
	return 0;
}
```

---

