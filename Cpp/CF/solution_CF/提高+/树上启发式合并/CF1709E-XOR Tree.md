# XOR Tree

## 题目描述

给定一棵包含 $n$ 个顶点的树。每个顶点上写有一个数字，第 $i$ 个顶点上的数字为 $a_i$。

我们称一条简单路径为每个顶点最多访问一次的路径。路径的权值定义为该路径上所有顶点的值的按位异或。我们称一棵树是“好”的，如果不存在权值为 $0$ 的简单路径。

你可以进行如下操作任意次（也可以不进行）：选择树上的一个顶点，将其上的值替换为任意正整数。请问，最少需要进行多少次操作，才能使这棵树变为“好”的？

## 说明/提示

在第一个样例中，只需将顶点 $1$ 上的值替换为 $13$，将顶点 $4$ 上的值替换为 $42$ 即可。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
3 2 1 3 2 1
4 5
3 4
1 4
2 1
6 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4
2 1 1 1
1 2
1 3
1 4```

### 输出

```
0```

## 样例 #3

### 输入

```
5
2 2 2 2 2
1 2
2 3
3 4
4 5```

### 输出

```
2```

# 题解

## 作者：enucai (赞：33)

## Analysis

令 $a_u$ 表示 $u$ 的点权，$d_u$ 表示树上 $1$ 到 $u$ 简单路径上所有点的点权异或和。

题目中 $u$ 到 $v$ 的简单路径上的所有点点权异或和 $=0$ 等价于 $d_u\oplus d_v\oplus a_{\text{lca}(u,v)}=0$。

可以证明如果允许改变 $a_u$，那么一定可以使以 $u$ 为根的子树中不存在异或和为 $0$ 的简单路径（一种构造方法是令 $a_u=2^{u+11^{4514}}$）。

考虑对每个点开一个 set，记录其子树中（包括自身）所有点的 $d$。特别的，若一个点被改变，则其 set 为空 $^{[1]}$。

在枚举一个点 $rt$ 的所有儿子时，设现有集合为 $S$，该儿子的集合为 $T$，则枚举 $T$ 中的所有元素。设当前枚举元素为 $T_i$，在 $S$ 中查找是否存在 $a_{rt}\oplus T_i$，若存在，则子树中一定存在两个点 $u,v$ 满足 $d_u\oplus d_v\oplus a_{rt}=0$。因此一定要改变 $a_{rt}$。

${[1]}$：若改变了 $a_{rt}$，那么以 $rt$ 为根的子树中的所有点就不必参与 $rt$ 祖先点中的讨论，因为 $a_{rt}=2^{u+11^{4514}}$，不可能有以 以 $rt$ 为根的子树中的点 为端点的简单路径的异或和为 $0$，因此清空 $S_{rt}$。

复杂度 $O(n^2\log n)$，用 启发式合并 可以使复杂度降低到 $O(n\log^2n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j);i<=(k);i++)
#define Rof(i,j,k) for(int i=(j);i>=(k);i--)
#define eb emplace_back
#define IOS ios::sync_with_stdio(false),cin.tie(0)
#define int long long
int n,res,a[200010],dis[200010];
vector<int> e[200010];
set<int> s[200010];
void dfs(int u,int fa){
	bool tmp=0; s[u].insert(dis[u]);
	for(int v:e[u]) if(v!=fa){
		dis[v]=dis[u]^a[v],dfs(v,u);
		if(s[u].size()<s[v].size()) swap(s[u],s[v]);
		for(int i:s[v]) if(s[u].find(a[u]^i)!=s[u].end()) tmp=1;
		for(int i:s[v]) s[u].insert(i);
	}
	if(tmp) res++,s[u].clear();
}
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n-1){
		int u,v; cin>>u>>v;
		e[u].eb(v),e[v].eb(u);
	}
	dis[1]=a[1];
	dfs(1,0);
	cout<<res;
}
```

---

## 作者：_anll_ (赞：15)

~~学启发式合并时找到的一道好题，发现还能写题解，所以来献丑了。~~
## 题目大意
给你有 $n$ 个点的树，每个点有点权 $a_i$，问你：没有一条简单路径上的**所有点的点权的异或和**为 $0$ 最少需要修改几次点权。

对于一个点，你可以将点权修改为任意正整数。

## 大体思路
首先对于异或，我们需要知道一个很简单的公式：记 $x$ 到根节点的异或和为 $d_x$，于是对于一条简单路径 $(i,j)$ 上的点权异或和则为 $d_i \oplus d_j \oplus a_{lca_{i,j}} $。自然也很容易证明，类似于容斥，因为 $d_i \oplus d_j$ 后会把它们所有祖先的异或和消掉，所以还需要再额外补上他们的 LCA。

然后我们再把公式浅推一下，得到 $d_i \oplus a_{lca_{i,j}} = d_j$。

接下来就好办了。~~既然是奔着启发式合并来的那当然要~~考虑树上启发式合并，枚举每一个可能需要修改被路径的 LCA，在这令其为 $x$。对于 $x$ 的子树 $i$，使用 set 维护它们的 $d_i$。然后去枚举 $x$ 的每一个子树。

不妨令 $x$ 枚举过的子树集合为 $P$，当前枚举子树的集合为 $Q$，比较一下集合内元素的数量，去遍历较小的那个集合的所有元素（后文默认较小集合为 $Q$）。令当前枚举到的元素为 $Q_i$，如果集合 $P$ 内存在 $Q_i \oplus a_x$，则说明该路径不合法，打上标记即可。遍历结束后别忘了把 $Q$ 内所有元素合并至 $P$ 集合。

枚举完毕子树后再判断一下经过 $x$ 的路径是否均合法。如果有不合法的就把答案加一，然后清空当前集合即可。

## 代码展示
总体思路大概就是上面那样，如果有表述不清楚的地方可以结合代码与注释理解。
```cpp
#include<iostream>
#include<set>
#define int long long
using namespace std;
struct Edge{
	int l,nxt;
}edges[400005];
int n,ans,a[200005],tt,head[200005];
int d[200005],fas[200005];
set<int> so[200005];
void add_edges(int f,int l){
	tt+=1;
	edges[tt]={l,head[f]};
	head[f]=tt;
}
void dfs1(int x,int fa){//查找d的，其实可以和下面的dfs合并 
	fas[x]=fa,d[x]=d[fa]^a[x];
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l;if(l==fa) continue;
		dfs1(l,x);
	}
}
void dfs2(int x){
	so[x].insert(d[x]);
	bool flag=0;
	for(int i=head[x];i;i=edges[i].nxt){
		int l=edges[i].l; if(l==fas[x]) continue;
		dfs2(l);
		if(so[x].size()<so[l].size()) swap(so[x],so[l]);//让l为那个较小集合 
		for(int e:so[l])
			if(so[x].find(e^a[x])!=so[x].end()) flag=1; //打标记 
		for(int e:so[l]) so[x].insert(e);//将较小集合并入较大集合 
	}
	if(flag) ans+=1,so[x].clear();
}
signed main(){
	int f,l;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		cin>>f>>l;
		add_edges(f,l);add_edges(l,f);
	}
	dfs1(1,0);dfs2(1);
	cout<<ans;
	return 0;
}
```



---

## 作者：happy_dengziyue (赞：9)

### 1 视频题解

![](bilibili:BV1GW4y127vj)

### 2 思路

我们可以对每个点开一个 `set` 去解决问题。

$sum[u]$ 表示，所有的以 $u$ 为一个端点的路径的一个可能的异或和。

然后我们再枚举 $u$ 的儿子。设 $x$ 为 $sum[v]$ 中的一个数，如果存在一个 $x$ 使得 $sum[u]$ 里存在 $x\oplus a[u]$，说明必须将 $a[u]$ 改了。

如果必须将 $a[u]$ 改变，我们就可以砍掉整个 $u$ 的子树。因为 $a[u]$ 可以变为任何数。

深度优先搜索完成后输出答案即可。

具体问题请参见代码。

### 3 代码与记录

```cpp
//Luogu submission 19:10
#include<bits/stdc++.h>
using namespace std;
#define max_n 200000
int n;
int a[max_n+2];
struct E{
	int v,nx;
}e[max_n<<1];
int ei=0;
int fir[max_n+2];
int cnt[max_n+2];
unordered_set<int>sum[max_n+2];
int ans=0;
void addedge(int u,int v){
	e[++ei]=(E){v,fir[u]}; fir[u]=ei;
}
void dfs(int u,int f){
	bool fl=false;
	cnt[u]=cnt[f]^a[u];
	sum[u].insert(cnt[u]);
	for(int i=fir[u],v;i;i=e[i].nx){
		v=e[i].v;
		if(v==f)continue;
		dfs(v,u);
		if(sum[v].size()>sum[u].size())swap(sum[u],sum[v]);
		for(int x:sum[v]){
			if(sum[u].find(a[u]^x)!=sum[u].end())fl=true;
		}
		for(int x:sum[v])sum[u].insert(x);
	}
	if(fl){
		sum[u].clear();
		++ans;
	}
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1709E_2.in","r",stdin);
	freopen("CF1709E_2.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1,u,v;i<n;++i){
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80744763)

By **dengziyue**

---

## 作者：Ynoi (赞：8)

由于题目中对点修改后的点权值没有限制 那么我们可以改成一些奇怪的值，比如 $x$ 号点改成 $2^{30+x}$，这样所有经过被修改的点的路径的 $xor$ 都不可能为 $0$ 了。也就是在这个点把这棵树切断。

然后然后我们有一个贪心策略，将点的深度从大到小排序之后，按顺序枚举每个点$x$判断子树有没有两个点 $u,v$ 使得 $\operatorname{LCA}(u,v) = x$ 且 $u \to v$ 路径 $xor$ 为 $0$，如果有就修改$x$，即把 $x$ 所在的子树切下来。

为什么这样是对的呢？因为假如有另外一条 $xor$ 为0的路径，且与 $u \to v$ 相交，并且它的 LCA 深度小于等于 $x$，那么 $x$ 一定也在这条路径，也就意味着在 $x$ 切断一定不会比 $u \to v$ 路径中的其他点不优。然后你仔细想一下这个证明会发现其实也不一定要严格的深度排序，也可以dfs后序遍历，这样也是符合的,同时这样后面维护也许可以方便点。

然后就是怎么维护的，定义 $c_x$ 为从根节点到 $x$ 节点路径上所有节点的 $xor$，那么 $u \to v$ 路径所有节点的xor就是 $c_u \operatorname{ xor } c_v \operatorname{ xor }a_{\operatorname{ LCA(u,v) }}$。我们可以用类似启发式合并的方式，就将轻子树的节点合并到重子树上去，同时用map维护 $c_i$ ，合并（比如把$t$合并上去）的时候判断是否有 $c_i = c_t \operatorname{xor} a_x$ 就可以了。

如果用 Unordered_map 的话时间复杂度就能做到 $n\log n$ 了。

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define pb push_back

int n,m;
struct bian{
	int x,y,ls;
}b[MAXN<<1];
int t[MAXN],cnt;
map<int,int> p[MAXN];
int a[MAXN],c[MAXN],fa[MAXN],s[MAXN];
vector<int>v[MAXN];

void jb(int x,int y) {
	cnt ++;
	b[cnt].x = x;
	b[cnt].y = y;
	b[cnt].ls = t[x];
	t[x] = cnt; 
}

void rd() {
	cin >> n ;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	for(int i = 1; i <= n-1; i ++) {
		int x,y;
		cin >> x >> y;
		jb(x,y);
		jb(y,x);
	}
}

void dfs(int x) {
	c[x] = c[fa[x]]^a[x];
	s[x] = 1;
	for(int i = t[x]; i != 0; i = b[i].ls)  {
		int y = b[i].y;
		if(y != fa[x]) {
			fa[y] = x;
			v[x].pb(y);
			dfs(y);
			s[x] += s[y];
		} 
	}
}

int w[MAXN],nn;
int f[MAXN];//表示是否被切掉 

void get(int x) { //将轻子树所有搞出来 
	nn ++;
	w[nn] = x;
	for(int i = 0; i < v[x].size(); i ++) {
		int y = v[x][i];
		if(!f[y]) get(y); 
	}
}


void cdcq(int x) {
	int hs = 0;//重儿子 
	for(int i = 0; i < v[x].size(); i ++) {
		int y = v[x][i];
		cdcq(y);
		if((!f[y]) && s[y] > s[hs]) hs = y;
	}
	if(hs == 0) g[x] = x;
	else g[x] = g[hs];
	if(p[g[x]].count(a[x]^c[x])) {
		f[x] = 1;
		return;
	}
	
	p[g[x]][ c[x] ] = x;
	nn = 0;
	for(int i = 0; i < v[x].size(); i ++) {
		int y = v[x][i];
		nn = 0;
		if((!f[y]) && y != hs) 
			get(y);
		//这一部分是合并 
		for(int j = 1; j <= nn; j ++) {
			int y = w[j];
			if(p[g[x]].count(c[y]^a[x])) {
				f[x] = 1;
				return;
			}
		}
		for(int j = 1; j <= nn; j ++) {
			int y = w[j];		
			p[g[x]][ c[y] ] = y;
		}
	}
}

signed main()
{
	rd();
	dfs(1);
	cdcq(1);
	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans += f[i];
	cout<<ans;
	return 0;
 } 


```

---

## 作者：Doubeecat (赞：7)

# E.XOR Tree

> 给定一颗 $n$ 个点的带权树，定义一棵树是好的当且仅当这棵树上任意两点间没有一条简单路径满足：路径上的点点权异或和为 $0$。
>
> 你可以做以下操作若干次：选择一个点，将其的点权更改为**任意正整数**。请求出最少需要做多少次操作让这棵树变成好的。
>
> $n \leq 2\times 10^5,1 < a_i < 2^{30}$

## Analysis

启发式合并好题。

记 $dis_x$ 表示从根到点 $x$ 的异或和，$LCA(u,v)$ 表示 $u,v$ 两点的最近公共祖先，我们考虑两个点 $(u,v)$ 之间简单路径和为 $dis_u \bigoplus dis_v \bigoplus a_{LCA(u,v)}$ ，这里利用了异或的性质，消去了 $dis_{LCA(u,v)}$ 的部分。

接下来我们考虑路径异或和为 $0$ 的含义，我们发现，一对 $(u,v)$ 异或和为 $0$ 当且仅当他们的异或和等于 $a_{LCA(u,v)}$。所以我们考虑以 $LCA(u,v)$ 作为切入口。

对于每个点 $x$ 来说，把他作为 $LCA(u,v)$，那么子树内如果存在一对点 $(u,v)$ 满足 $dis_u \bigoplus a_x = dis_v$ ，我们就必须将 $x $ 的点权进行修改。因为题目里说明可以是任意非负正整数，所以我们不需要关心具体的点权，存在多对满足以上条件的也只需要改一次，因为必然是可以构造出一个值让他们的异或和都不为 $0$ 的。

所以我们就考虑启发式合并，用 `set` 维护每个点子树里的点权。先进行一遍 `dfs` 找出重儿子，以及 $dis$ 的预处理。第二遍 `dfs` 将重儿子的集合换上来，对于每个轻儿子，再对其进行查询，并且合并集合。若是发现当前子树内有需要的点，直接让答案加一，清空当前集合（已经通过修改 $a_x$ 使得当前子树内不再拥有可以满足上述条件的点对）

总时间复杂度是 $\mathcal{O}(n^2\log n)$，不怎么需要卡常就可以过。

这题同样可以用按 `size` 合并来做，复杂度是相同的，代码里会给出两种写法。

## Code

按重儿子合并

```cpp
//Every night that summer just to seal my fate
//And I scream, "For whatever it's worth
//I love you, ain't that the worst thing you ever heard?"
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define ll long long

char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
template <typename T> inline void read(T &t) {
	int v = getchar();T f = 1;t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	t *= f;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args) {
	read(t);read(args...);
}

const int N = 2e5 + 10;

int a[N],n,siz[N],b[N],cnt[N],dis[N],dep[N],son[N],l[N],r[N],dfn,rk[N],ans,ansx[N];
vector <int> G[N];
set <int> s[N];
 
void dfs1(int x,int f) {
    l[x] = ++dfn;rk[dfn] = x;
    dis[x] = dis[f] ^ a[x];
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (auto y : G[x]) {
        if (y != f) {
            dfs1(y,x);
            siz[x] += siz[y];
            if (siz[y] > siz[son[x]]) {
                son[x] = y;
            }
        }
    }
    r[x] = dfn;
}

void dfs2(int x,int f) {
    if (son[x]) {
        dfs2(son[x],x);
        swap(s[son[x]],s[x]);
    }
    bool flag = 0;
    if (s[x].find(dis[x] ^ a[x]) != s[x].end()) {
        flag = 1;
    }
    s[x].insert(dis[x]);
    for (auto y : G[x]) {
        if (y != son[x] && y != f) {
            dfs2(y,x);
            for (auto z : s[y]) {
                if (s[x].find(z ^ a[x]) != s[x].end()) flag = 1;
            }
            for (auto z : s[y]) s[x].insert(z); 
        }
    }
    if (flag) ++ansx[1],s[x].clear();
}

signed main() {
    read(n);
    for (int i = 1;i <= n;++i) read(a[i]);
    for (int i = 1;i < n;++i) {
        int x,y;read(x,y);
        G[x].push_back(y);G[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);
    printf("%d\n",ansx[1]);
	return 0;
}
```

按 `size` 合并：

```cpp

//Every night that summer just to seal my fate
//And I scream, "For whatever it's worth
//I love you, ain't that the worst thing you ever heard?"
#pragma GCC optimize(2)
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cmath>
#include <unordered_set>
using namespace std;
#define pii pair<int,int>
#define mp make_pair
#define ll long long
#define int long long
 
char buf[1 << 20], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)?EOF: *p1++)
template <typename T> inline void read(T &t) {
	int v = getchar();T f = 1;t = 0;
	while (!isdigit(v)) {if (v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {t = t * 10 + v - 48;v = getchar();}
	t *= f;
}
template <typename T,typename... Args> inline void read(T &t,Args&... args) {
	read(t);read(args...);
}
 
const int N = 2e5 + 10;
 
int a[N],n,siz[N],b[N],cnt[N],dis[N],dep[N],son[N],l[N],r[N],dfn,rk[N],ans,ansx[N],fat[N];
vector <int> G[N];
unordered_set <int> s[N];
void dfs1(int x,int f) {
    dis[x] = dis[f] ^ a[x];
    dep[x] = dep[f] + 1;
    for (auto y : G[x]) {
        if (y != f) {
            dfs1(y,x);
        }
    }
}
 
void dfs2(int x,int f) {
    s[x].insert(dis[x]);
    bool flag = 0;
    for (auto y : G[x]) {
        if (y != f) {
            dfs2(y,x);
            if (s[y].size() > s[x].size()) swap(s[x],s[y]);
            for (auto z : s[y]) {
                if (s[x].find(z ^ a[x]) != s[x].end()) flag = 1;
            }
            for (auto z : s[y]) {
                
                s[x].insert(z);
            }
        }
    }
    if (flag) s[x].clear(),++ansx[1];
    return ;
}
 
signed main() {
    read(n);
    for (int i = 1;i <= n;++i) read(a[i]);
    for (int i = 1;i < n;++i) {
        int x,y;read(x,y);
        G[x].push_back(y);G[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);
    printf("%d\n",ansx[1]);
	return 0;
}
```



---

## 作者：__stick (赞：5)

# 题意
给出一棵树，树上的 $u$ 点有权值 $a_u$，定义一条路径的权值为路径上所有点权值的异或和，问最少修改多少点的权值，使得树上的路径没有权值为 $0$ 的。

# 分析

首先对于异或，有一个比较明显的性质，我们记 $d_u$ 表示 $u$ 到根节点的异或和，则一条树上路径 $(u,v)$ 的权值就是：

$$d_u \oplus  d_v \oplus a_{\operatorname{lca}(u,v)}$$
 
 
 证明很简单， $u,v$ 的 lca 和它的所有祖先的异或值都抵消了我们再补上 lca 的值即可。
 
 所以我们就可以快速求出一条路径的权值，但暴力枚举复杂度是 $O(n^2)$ 的，不能接受，于是考虑优化。
 
我们可以按深度从高到低枚举 lca ，检查以这个节点为 lca 的所有路径是否权值为零，然后如果存在这样的路径，我们就修改这个节点，使得以当前节点为跟的子树全部不存在异或和为零的路径。
 
 
 同时，由于异或等于零的条件非常苛刻，我们在修改这个节点时们总是有办法使得经过这个节点的所有路径异或值不为零（一个点权值值域是 $[0,2^{30}]$ ，而树上路径是 $n^2$ 级别的），因此我们在后面的判断中就不需要考虑这个子树中的节点了，也就是相当于删除这个子树。
 
 如何证明这一定能找到最优解？首先，如果存在两条有交集的路径 $A,B$，假设路径 $A$ 两端点的 lca （以下简称路径 $A$ 的 lca）深度更大，在一番讨论后，我们发现，路径 $A$ 的 lca 一定落在 $B$ 上，否则两个路径的交点就会有两个父亲，这显然不可能。有了这个结论以及上面的分析，我们会发现修改一个路径的 lca 一定是最优的，因为这样最有可能同时去掉最多异或值为 $0$ 的路径，同时又因为我们从小到大枚举 lca 如果我们发现以当前节点为 lca 的路径出现了异或值为零的路径，我们就必须修改这个节点，因为如果路径上已经有节点被修改了，我们在遍历子树中节点时已经将所有需要修改的都修改了，还是使它权值为零，所以我们必须修改这个节点，因此，这样做是最优的。
 
 # 实现
 
 不难想到使用 set + 启发式合并做到 $O(n\log^2 n)$，具体实现是每个节点 $u$ 维护一个 set，存子树中所有的 $d_v$ ，$v $ 属于当前节点子树，然后对于它的每个儿子。在合并上来的时候，检查是否存在权值为零的路径（小的 set 中 所有元素 $p$ 在大的那个中查询是否存在 $p\oplus  a_u $ 即可），如果有就直接删除这个子树 （清空 set，答案加一），然后将小的插入大的即可。
 
 ```cpp

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<functional>
#include<map>
#include<queue>
#include<bitset>
#include<cmath>
#include<iomanip>
#include<numeric>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=998244353;

int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n;cin>>n;
	vi a(n+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	vii e(n+1);
	int u,v;
	for(int i=1;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	function<void(int ,int)>dfs;
	vi d=a;int ans=0;
	vector<set<int> >s(n+1);
	dfs=[&](int u,int fa)
	{
		s[u].insert(d[u]);
		bool flag=0;
		for(const int& v:e[u])
		{
			if(v==fa)continue;
			d[v]^=d[u];
			dfs(v,u);
			if(s[u].size()<s[v].size()) s[u].swap(s[v]);
			for(const int & x:s[v])if(s[u].find(a[u]^x)!=s[u].end())flag=1;
			for(const int & x:s[v]) s[u].insert(x);
		}
		if(flag) s[u].clear(),ans++;
	};dfs(1,0);
	cout<<ans;
	return 0;
}
```
还有一种非常骚气的 $O(n \log n$) 做法，用 bitset 做桶，空间是 $\frac{2^{30}}{8}$ 个字节，大概是 $128 $ MB ，完全够用！

实现的时候就是标准的 dsu on tree 了，直接先求出每个节点的重儿子，每个节点的桶直接继承重儿子的桶，然后轻儿子用 vector 维护集合，直接暴力合并即可，记得先递归轻儿子，在递归重儿子，保证 bitset 中是重儿子的点集，清空就暴力清空即可，具体看实现。

这玩意一定要开 c++ 20（64），才能过，求科普。


```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<functional>
#include<map>
#include<queue>
#include<bitset>
#include<cmath>
#include<iomanip>
#include<numeric>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=998244353;
bitset<(1<<30)>s;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n;cin>>n;
	vi a(n+1);
	for(int i=1;i<=n;i++)cin>>a[i];
	vii e(n+1);
	int u,v;
	for(int i=1;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u);
	function<void(int ,int)>dfs,pre;
	vi siz(n+1),son(n+1);vi d=a;
	pre=[&](int u,int fa)
	{
		siz[u]=1;
		for(const int& v:e[u])
		{
			if(v==fa)continue;d[v]^=d[u];
			pre(v,u);siz[u]+=siz[v];
			if(siz[son[u]]<siz[v])son[u]=v;
		}
	};
	pre(1,0);
	int ans=0;
//	vector<set<int> >s(n+1);
	vii w(n+1);
	dfs=[&](int u,int fa)
	{
		//cout<<u<<endl;
		if(!son[u])
		{
			s[d[u]]=1;
			w[u].push_back(d[u]);
			return ;
		}
		for(const int& v:e[u])
		{
			if(v==fa||v==son[u])continue;
			dfs(v,u);
			for(const int& p:w[v]) s[p]=0;//别忘了清空轻儿子的 vector		
		}
		dfs(son[u],u);
		w[u].swap(w[son[u]]);//vector 也是继承重儿子的
		bool flag=0;
		for(const int& v:e[u])
		{
			if(v==fa||v==son[u])continue;
			//dfs(v,u);
			for(const int& p:w[v]) 
			{
				if(s[p^a[u]])flag=1;
			}
			for(const int& p:w[v])s[p]=1,w[u].push_back(p);
			w[v].clear(),w[v].shrink_to_fit();//一定要释放空间！！！
		}
		if(s[d[u]^a[u]])flag=1;
        s[d[u]]=1,w[u].push_back(d[u]);
		if(flag)
		{
			ans++;
			for(const int& p:w[u])s[p]=0;//遍历 vector ，不要使用 bitset 的 set
			w[u].clear(),w[u].shrink_to_fit();
		}
	};
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

 
 

---

## 作者：_qhbd_ (赞：2)

# 题意
给定一棵树，树上点 $u$ 有点权 $a_u$，现在需要修改尽可能少的点使得这棵树上的任意两点间简单路径上点的点权的异或和不为 $0$。
# 思路
首先，我们需要的是让树上任意两点简单路径上点权异或和不为 $0$，那我们肯定需要一种能够快速求出**两点简单路径上点权异或和**的方法。

做过一些相关 LCA 的题就会知道，求 $u,v$ 之间简单路径，只需要先维护一下树上点的深度 $dep$，然后直接得出 $dis_{u,v}=dep_u+dep_v-2\times dep_{ Lca(u,v)}$。

我们可以用相似的思路，也维护一个树上点的 $dep$，只不过一般求简单路径长度是 $dep_u=dep_{fa}+1$，而对于这道题则应该是 $dep_u=dep_{fa}\oplus a_u$。

然后我们甚至不需要容斥，因为在 $LCA(u,v)$ 及其往上的点的点权都会被异或两次，根据异或的性质，被异或两次的值等同于没有异或过。

所以我们只需要求得 $dep_u\oplus dep_v\oplus a_{LCA(u,v)}$，即为路径上点权异或和。

其次关于修改，如果有两点 $u,v$ 之间的简单路径上点权异或和为 $0$，那我们再去修改 $LCA(u,v)$ 的点权。

至于为什么修改的是 $LCA(u,v)$ 的点权，这个有关整体的思路。首先我们肯定是由深到浅地去找是否有需要修改的点，找的过程必然是枚举的。

我们可以每次固定当前点 $fa$ 为路径上一点，然后在以此点为根子树中查找是否有某一个点 $u$ 使得有 $dep_u\oplus dep_{fa}$ 在以 $fa$ 为根的子树中有点的 $dep$ 有相同值。

如果有，就意味着 $dep_u\oplus dep_v\oplus a_{LCA(u,v)}$ 的值为 $0$ 了，也就说明我们需要更改 $a_{fa}$ 的值以及以这个点为路径上一点的所有路径都可以保证异或和不会为 $0$ 了，因为我们只需要赋值一个二进制下最高位极其靠左且未为其他修改后点赋值的数就可以了（如果不知道为什么，建议去了解一下异或）。

看到这个查找，我们就知道肯定要用 set 或者 map 了。

最后，我们只需要从子孙后代到祖先的去枚举，同时统计修改次数就可以得出结果了。
# 实现
```cpp
#include<iostream>
#include<vector>
#include<set>
#define N 200005
using namespace std;
vector<int> r[N];
set<int> son[N];
int ans,n,a[N],dep[N];
void dfs(int u,int fa){
	int k=0;dep[u]=a[u]^dep[fa];son[u].insert(dep[u]);
	for(auto v:r[u])if(v!=fa){
		dfs(v,u);
		if(son[u].size()<son[v].size())swap(son[u],son[v]);
		for(auto sn:son[v])if(son[u].count(a[u]^sn))k=1;
		for(auto sn:son[v])son[u].insert(sn);
	}if(k)ans++,son[u].clear();
}int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2,u,v;i<=n;i++)
		scanf("%d%d",&u,&v),
		r[u].emplace_back(v),
		r[v].emplace_back(u);
	dfs(1,1);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：2)

## [XOR Tree ](https://www.luogu.com.cn/problem/CF1709E)

> $\mathtt{TAGS}$：**树上启发式合并** + 异或 + 贪心
>
> $\mathtt{ESTIMATION}$：非常好的启发式合并题目

### First.如何**去除** $0$ 路径

对于一条路径 $u \to v$，要使其不为 $0$ 肯定是将 $\mathtt{LCA} (u,v)$ 变为 $2 ^ {30 + x}$ 最好，这样异或值的第 $30 + x$ 位一定为 $1$（因为 $a_i \le 2 ^ {30}$），修改之后，$u,v$ 在 $\mathtt{LCA} (u,v)$ 为根的子树内的路径都一定不为 $0$ 了。显然，这样是最优的。

### Second.如何快速判断一颗子树下有无 $0$ 路径

首先，对于 $u \to v$ 的路径权值 $dis_{u, v}$ 可以化为 $dis_{u, 1} \oplus dis_{v, 1} \oplus a_{\mathtt{lca}(u,v)}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/jl2lb9ko.png)

> 其实知道这个就可以去做 P4551 了。

这个时候可以用一个 set 储存该子树所有 $dis_{u, 1}$ 的值。然后枚举一个 $v$ 查找有无 $dis_{v, 1} \oplus a_u$ 在其中，如果有，那么他们异或起来为 $0$，就是有 $0$ 路径。

然后就是把这个子树删除，set 合并到它的父亲上。

这样，大体思路就出来了，暴力的话时间复杂度 $\text{O}(n ^ 2 \log n)$（枚举节点的 $n ^ 2$ 和 set 的 $\log n$）。

### Third.优化**时间复杂度**

启发式合并，每次将大小小一些的集合合并到大一些的集合上，执行 $\log n$ 次，节点数就会达到 $n$。所以只会合并 $\log n$ 次。

总时间复杂度为 $\text{O}(n \log^2 n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
vector<int> G[N];
int a[N], dis[N];
void dfs(int u, int fa) {
	dis[u] = a[u];
	if(fa) dis[u] ^= dis[fa];
	for (auto v : G[u]) {
		if(v != fa) dfs(v, u);
	}
}
set<int> s[N]; // 快速查找有无 0 路径
void move (int u, int v) { // 合并
	for (auto x : s[u]) s[v].insert(x);
	s[u].clear();
}
int ans = 0;
void dfs2(int u, int fa) {
	bool mark = 0;
	s[u].insert(dis[u]);
	for (auto v : G[u]) {
		if(v != fa) {
			dfs2(v, u);
			if(s[u].size() < s[v].size()) swap(s[u], s[v]); // 保证是小的合并至大的里面【启发式合并】
			for (auto x : s[v])	mark |= s[u].count(x ^ a[u]); // 如果存在 dis[u] = x ^ a[u] 说明子树中存在异或路径为 0 的路径
			move(v, u);
		}
	}
	if(mark) ans ++, s[u].clear(); // 如果存在，那么该节点需要删除
}

signed main() {
	ios::sync_with_stdio(0);
	cin >> n;
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i < n; i ++) {
		int u, v;
		cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
	}
	dfs(1, 0);
	dfs2(1, 0);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

若是「边权异或和为 $0$」的话，我们只要记录每个点到根节点的路径异或和为 $d_x$，两点间路径异或和即为 $d_x\oplus d_y$。

但是现在是点权，非常难搞。

我们称一条路径是非法的当且仅当路径上点权异或和为 $0$。

设 $a_x$ 为点权，$b_x$ 为 $x$ 到根的点权异或和，则 $x,y$ 路径上点权异或和为 $b_x\oplus b_y\oplus a_{lca(x,y)}$。

我们注意到题目中将点重新赋值相当于删除点，分成多个子树，其中不存在非法路径。

我们考察所有儿子均已做完的节点 $x$。

由于儿子均已做完，以 $x$ 为根的子树中只可能有经过 $x$ 的路径非法。

设 $S_x$ 表示 $x$ 的子树中到根没有被删除的点的 $b$ 值集合。

考虑启发式合并 $S_y(\forall y\in son_x)$，若有非法路径经过 $x$，则 $Ans\leftarrow Ans+1$（$x$ 节点被删去），然后清空 $S_x$。

时间 $O(n\log^2n)$。

```cpp
//We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug(...) cerr<<"#"<<__LINE__<<": "<<__VA_ARGS__<<endl
#define ll long long
const ll mod=1;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int ll
#define N 200010
int n,a[N],b[N],root[N],ans;
set<int> s[N];
vector<int> e[N];
void dfs(int rt,int fa,int val){
	b[rt]=a[rt]^val;
	s[root[rt]].insert(b[rt]);
	bool flag=0;
	for(int i:e[rt]) if(i!=fa){
		dfs(i,rt,b[rt]);
		if(s[root[rt]].size()<s[root[i]].size()) swap(root[rt],root[i]);
		for(int j:s[root[i]]) if(s[root[rt]].find(a[rt]^j)!=s[root[rt]].end()) flag=1;
		for(int j:s[root[i]]) s[root[rt]].insert(j);
	}
	if(flag){
		ans++;
		s[root[rt]].clear();
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	cin>>n;
	iota(root+1,root+1+n,1);
	For(i,1,n) cin>>a[i];
	int x,y;
	For(i,1,n-1){
		cin>>x>>y;
		e[x].pb(y);
		e[y].pb(x);
	}
	dfs(1,0,0);
	cout<<ans<<endl;
return 0;}
```

---

## 作者：Isharmla (赞：0)

不妨令 $d_i$ 表示从根节点到节点 $i$ 的最短路径上的异或和。题目要求任意两点点 $u$ 点到点 $v$ 的异或和不为零也就等价于要求任意两点 $d_u \oplus d_v \oplus a_{lca(u,v)}$ 不为零。

现在我们只需要解决 $d_u \oplus d_v \oplus a_{lca(u,v)}$ 为零的情况，由于是异或操作，我们**一定可以构造一个数**，使得**更改后异或值不为零**。很好证明，因为 $a_i$ 二进制下最多只会有三十位，因此只需要构造出一组二进制下位数大于三十的数即可。因此，我们不需要考虑如何构造，并且，这个点修改后，就不用担心不同这个点的子树和外面的数异或值了，因为他的子树和外面的点的简单路径必定经过点 $u$。我们只需要考虑点 $u$ 的子树内部了。否则，我们才需要让儿子一同参与外面的讨论。

接下来，考虑如何实现，使用一个桶，对点 $u$ 的子树加入搜索，每次将 $a_u \oplus d_v$ 加入桶，其中的 $v$ 表示儿子，在遍历其他子树，只需要考虑桶内部是否存在这个值即可。和感觉这个步骤和点分治差不多？如果存在，说明需要修改，我们答案加一，然后不让这个点的子树加入讨论，否则需要加入讨论。

使用树上启发式合并可以变成 $O(n \log^2 n)$，可以通过，也许点分治也可以？可以去试试。

---

## 作者：E1_de5truct0r (赞：0)

下文中 $\oplus$ 表示二进制按位异或运算（C++ 中的 `^`）。

如果令 $d_u$ 表示从 $u$ 到根的异或值，那么 $u$ 和 $v$ 两点之间的异或值可以表示为 $d_u \oplus d_v \oplus w_{\text{lca}(u,v)}$。

显然是不能暴力枚举 $u,v$ 了，那么我们考虑枚举这个 LCA。

考虑修改一个点，由于是可以把权值修改成任意正整数，所以只要我们改的够离谱，所有经过这个点的路径就都不合法了。但是这只能处理过这一点的，没法处理这个点子树内的答案。

所以我们有一个显然的策略，把点从深到浅依次处理，这样可以保证处理经过点 $u$ 的路径的时候，以点 $u$ 子树内任意一点为 LCA 的路径已经被处理过。

具体的处理方法就很暴力了，对每个节点维护一个 set 表示它的 $d$ 数组。那么我们只需要把点 $u$ 的答案合并到它的父亲上去就好了，如果出现不符合题意的，那么就直接把 $u$ 的 set 删掉，同时答案 +1。

暴力合并是 $O(n^2 \log n)$ 的，但是直接启发式合并一下就可以做到 $O(n \log^2 n)$。

[Code & Submission](https://codeforces.com/contest/1709/submission/211827542)

---

## 作者：船酱魔王 (赞：0)

# CF1709E XOR Tree 题解

## 题意回顾

有一个 $ n $ 个结点的树，点带权，改变最少的点权的个数使得任意简单路径异或和不为 $ 0 $。

$ 1 \le n \le 2 \times 10^5 $。

## 分析

首先，因为没有给定修改范围，因此可以修改得无限大，所以可以构造 $ 2 $ 的极大次幂来使得包含点 $ u $ 的所有路径合法。

考虑 XOR 路径的原理，记 $ P(u,v) $ 为 $ u $ 到 $ v $ 的异或和，$ dis_u $ 为 $ 1 $ 到 $ u $ 的异或和，可以发现 $ P(u,v)=dis_u\oplus dis_v \oplus a_{lca(u,v)} $。

也就是说，对于点 $ u $，如果它的所有子树中，存在两个不同的子树，使得子树中各存在一个点使得 $ dis $ 的异或值为 $ a_u $，则 $ u $ 必须改。

我们递归地考虑所有的结点，考虑完成所有子树后删去已经被修改的子树，再行处理当前结点。对于该结点的每棵子树，用子树所有结点寻找是否存在已经被加入的结点使得异或和为 $ a_u $，子树处理完成后加入 $ u $ 子节点集合。

但是，因为树不一定随机生成，时空复杂度不可接受。

我们有一个技巧，叫“树上启发式合并”，每次对于子结点数最大的子结点，将该子结点集合优先直接放入 $ u $ 子结点集合，之后正常处理。

（Tips：注意 set swap 时间复杂度 $ O(1) $。）

每次一个点会由小的集合进入大的集合，小的集合一定不会大于大的集合的一半（否则会被直接 $ O(1) $ 合并），因此时间复杂度 $ O(n \log n) $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int N = 2e5 + 5;
int n;
int v[N];
vector<int> g[N];
int sz[N];
int big[N];
int dis[N];
int pre_dfs(int u, int fath) {
	dis[u] = dis[fath] ^ v[u];
	for(int i = 0; i < g[u].size(); i++) {
		if(g[u][i] != fath) {
			sz[u] += pre_dfs(g[u][i], u);
			if(sz[g[u][i]] > sz[big[u]]) {
				big[u] = g[u][i];
			}
		}
	}
	sz[u]++;
	return sz[u];
}
set<int> se[N];
int ans[N];
void dfs(int u, int fath) {
	ans[u] = 0;
	int v1;
	for(int i = 0; i < g[u].size(); i++) {
		if(g[u][i] != fath) {
			dfs(g[u][i], u);
		}
	}
	swap(se[big[u]], se[u]);
	for(int i = 0; i < g[u].size(); i++) {
		v1 = g[u][i];
		if(v1 == big[u] || v1 == fath) {
			continue;
		}
		for(set<int>::iterator it = se[v1].begin(); it != se[v1].end(); it++) {
			if(se[u].find((*it) ^ v[u]) != se[u].end()) {
				ans[u] = 1;
			}
		}
		for(set<int>::iterator it = se[v1].begin(); it != se[v1].end(); it++) {
            se[u].insert(*it);
		}
		se[v1].clear();
	}
	if(se[u].find(dis[u] ^ v[u]) != se[u].end()) {
		ans[u] = 1;
	}
	if(ans[u] == 0) {
		se[u].insert(dis[u]);
	} else {
		se[u].clear();
	}
}
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &v[i]);
	}
	int x, y;
	for(int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	pre_dfs(1, 0);
	dfs(1, 0);
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		if(ans[i] == 1) {
			sum++;
		}
	}
	printf("%d\n", sum);
	return 0;
}
```

## 总结与评价

挺好的题，不错的技巧，很有教育意义。

准备放到校内模拟赛 T5，感觉场上应该不会有人 A 吧。

---

## 作者：lyhqwq (赞：0)

# Solution

一些定义：$a_i$ 为 $i$ 号点的点权，$dis_i$ 为 $i$ 号点到根节点的点权异或和。

由题意得，$P(u,v)=dis_u \oplus dis_v \oplus a_{lca(u,v)}$。

如果需要改变 $a_i$，那么一定只需要改变一次，具体方法为将 $a_i$ 改为 $2$ 的很大次幂即可。

如果一个点是 $lca(u,v)$，那么 $u$ 和 $v$ 一定是在以 $lca$ 为根的不同字树内，且确定其中一个就可以确定另一个。

我们考虑对每个结点开一个 set，存储子树中所有节点的 $dis$ 值，每次将这个节点的 set 合并到父亲的 set 里。

我们考虑 dfs 的同时合并，假设我们 dfs 到 $i$，接下来要 dfs 的节点为 $j$，那么我们可以考虑以 $i$ 作为 lca。

对于已经和父节点的 set 合并的部分，我们从中寻找一个数，作为 $dis_u$，并在 $j$ 的 set 中去找 $dis_u \oplus a_{lca}$，如果能找到，说明去要修改，然后把 $i$ 的 set 和 $j$ 的 set 合并即可。

如果在以 $i$ 为根的子树中存在需要修改的节点，我们直接修改 $a_i$ 即可，之后需要把 $i$ 的 set 清空。

时间复杂度 $O(n^2\log n)$，启发式合并可以做到 $O(n\log n)$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,ans;
int a[N],dis[N];
vector<int> g[N];
set<int> s[N];
void dfs(int u,int fa){
	s[u].insert(dis[u]);
	int f=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i]; 
		if(v==fa) continue;
		dis[v]=dis[u]^a[v];
		dfs(v,u);
		if(s[u].size()<s[v].size()) swap(s[u],s[v]);
		for(set<int>::iterator it=s[v].begin();it!=s[v].end();it++){
			if(s[u].find(a[u]^(*it))!=s[u].end()){
				f=1;
			}
		}
		for(set<int>::iterator it=s[v].begin();it!=s[v].end();it++) s[u].insert(*it);
	}
	if(f){
		ans++;
		s[u].clear();
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u); 
	}
	dis[1]=a[1];
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：intel_core (赞：0)

如果修改了一个点的点权，随便胡诌一个充分大的 $2$ 的幂就可以让没有 $P(u,v)=0$ 的路径经过这个点。

所以修改点权相当于删掉这个点和连出去的所有边。

贪心的，如果当前 $u$ 的子树内没有 $P(u,v)=0$ 的路径，那么就不用修改 $u$ 的点权，否则就需要把 $u$ 从树上砍掉。

现在问题变成了怎么快速求出 $P(u,v)$ 的值。

因为异或具有 $x \oplus x=0$ 和 $x \oplus y=y \oplus x$ 的性质，所以考虑差分。

令 $c_u$ 表示 $P(root,u)$ 的值，那么 $P(u,v)=c_u \oplus c_v \oplus a_{lca}$。

我们可以把当前 $u$ 子树内没有被砍掉的节点的 $c$ 值都扔进一个数据结构里，每次插入 $x$ 时都询问当前有没有 $y=x \oplus a_u$。

可以用 `std::set` 或者线性基的启发式合并，复杂度 $O(n \log a_i)$ 或 $O(n \log ^2n)$。

---

