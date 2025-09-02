# 巨大企業

## 题目描述

### 题目简述

有一个 $n$ 点有向图，每个点的编号由 $1$ 到 $n$ 。除了一个点之外，其它每个点都会有一条边连向另外一个点（不存在重边和自环，也不存在一个点，使得从该点出发，沿着有向边走，能够回到这个点）。现在有 $q$ 组询问，每组询问给定两个点的编号 $a_i$ 和 $b_i$ ，请问能否能从 $a_i$ 出发走到 $b_i$ 。

## 样例 #1

### 输入

```
7
-1
1
1
2
2
3
3
6
7 1
4 1
2 3
5 1
5 2
2 5```

### 输出

```
Yes
Yes
No
Yes
Yes
No```

## 样例 #2

### 输入

```
20
4
11
12
-1
1
13
13
4
6
20
1
1
20
10
8
8
20
10
18
1
20
18 14
11 3
2 13
13 11
10 15
9 5
17 11
18 10
1 16
9 4
19 6
5 10
17 8
15 8
5 16
6 20
3 19
10 12
5 13
18 1```

### 输出

```
No
No
No
No
No
No
No
Yes
No
Yes
No
No
No
Yes
No
Yes
No
No
No
Yes```

# 题解

## 作者：xzh15960292751 (赞：11)

# 题目分析

题目中说明有 $n$ 个点，编号为 $1$ 到 $n$，在输入中，给出了编号为 $i$ 的点连出的有向边连向的点的编号。\
注意到这里：
```
不存在重边和自环，也不存在一个点，使得从该点出发，沿着有向边走，能够回到这个点
```
所以，我们可以把这个图看成一棵树，只是这棵树是由有向边联通的。\
此时，如果有一个点连接的点的编号为 $-1$，就说明这个点为根节点。\
题目中要判断从 $a_i$ 出发能否到达 $b_i$，即两个点是否有公共祖先。

# AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n,q,s;
int f[N][20], depth[N];
int tot, lg[N];
int head[N]; 
struct node {
	int u, v, nxt;
}e[N << 1];
void add(int u,int v) {
	++tot;
	e[tot] = {u, v, head[u]};
	head[u] = tot;
}
void dfs(int now, int fa) {
	depth[now] = depth[fa] + 1;
	f[now][0] = fa;
	for(int i = head[now]; i; i = e[i].nxt) {
		if(e[i].v != fa) dfs(e[i].v, now);
	}
}
int lca(int x, int y) {
	if(depth[x] < depth[y]) swap(x, y);
	while(depth[x] > depth[y]) {
		int c = depth[x] - depth[y];
		x = f[x][lg[c]];
	}
	if(x == y) return x;
	for(int i=18; i>=0; i--) {
		if(f[x][i] != f[y][i]) {
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(int i=2; i<=n; i++) lg[i] = lg[i / 2] + 1;
	for(int i=1; i<=n; i++) {
		int edge;
		cin >> edge;
		if(edge == -1) s = i;
		else add(edge, i);
	}
	dfs(s, 0);
	for(int j=1; j<=18; j++)
		for(int i=1; i<=n; i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
	cin >> q;
	while(q--) {
		int a, b;
		cin>> a >> b;
		if(lca(a, b) == b) cout << "Yes" << '\n';
		else cout << "No" << '\n';
	}
	return 0;
}
```

---

## 作者：ljc2230 (赞：10)

[AT\_past201912\_k 巨大企業](https://www.luogu.com.cn/problem/AT_past201912_k)

### 题目解析

输入 $n$ 个点所指向的点，构成一个有向图，然后判断是否能从 $a$ 点走到 $b$ 点。\
我们可以把这个有向图看成一棵树，因为每个点都只有一条边连向另外一个点。\
所以题目能否能从 $a$ 出发走到 $b$，就是求 $\operatorname{lca(a,b)}$ 是否等于 $b$。其他就是最近公共祖先的模板了，我这里用的是倍增求最近公共祖先。

### 代码

```
#include<bits/stdc++.h>
using namespace std;

const int N=5e5+5;
int n,q,start;
int f[N][20],dep[N];
int to[N],nxt[N],head[N];
int cnt;

void add(int u,int v){
	cnt++;
	to[cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

void dfs(int now,int fa){
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=head[now];i>0;i=nxt[i]){
		if(to[i]!=fa)dfs(to[i],now); 
	}
}

int lca(int x,int y){
	if(dep[y]>dep[x])swap(x,y);
	while(dep[x]>dep[y]){
		int p=dep[x]-dep[y],pp=log2(p);
		x=f[x][pp];
	}
	if(x==y)return x;
	for(int i=18;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x==-1)start=i;
		else add(x,i);
			
	}
	dfs(start,0);
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
			f[i][j]=f[f[i][j-1]][j-1];
	cin>>q;
	while(q--){
		int a,b;
		cin>>a>>b;
		if(lca(a,b)==b)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：yedalong (赞：10)

## Solution
注意到这句话：  
>除了一个点之外，其它每个点都会有一条边连向另外一个点。

这是什么意思呢？其实那个没有出边的点我们可以给它看做树的根。  
当我们把这些边反着建的时候就能发现建出来的图其实很想一棵树（只是边是有向边而已），然后我们又发现 $a_i$ 能够到达 $b_i$ 其实就是 $\text{lca}(a_i,b_i)=b_i$，这里还是很好想的，不懂的同学可以自己画图看看。  

所以，这道题就成了十分模板的最近公共祖先。。。

## AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s,q,x,y,a,b,deep[500005],f[500005][20],lg[500005];
vector<int> edge[500005];
void dfs(int now,int father){
	f[now][0]=father,deep[now]=deep[father]+1;
	for(int i = 1;i<=lg[deep[now]]-1;i++) f[now][i]=f[f[now][i-1]][i-1];
	for(auto to:edge[now]) if(to!=father) dfs(to,now);
}
int LCA(int x,int y){
	if(deep[x]<deep[y]) swap(x,y);
	while(deep[x]>deep[y]) x=f[x][lg[deep[x]-deep[y]]-1];
	if(x==y) return x;
	for(int i = lg[deep[x]]-1;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++) lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	for(int i = 1;i<=n;i++){
		cin>>x;
		if(x==-1) s=i;
		else edge[x].push_back(i);
	}
	dfs(s,0);
	cin>>q;
	while(q--){
		cin>>a>>b;
		if(LCA(a,b)==b) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：jzl_1210 (赞：1)

这道题目其实很简单，关键在于如何转化成最近公共祖先的问题。

# 具体过程

可以发现，这个图和树有不少相似的地方，例如：无环。

因为除了一个点之外，其它每个点都会有一条边连向另外一个点，那么这个没有向外连边的点就是根结点。

但是它是有向图啊，树不是无向的吗？

其实，如果有一条有向边由 $u$ 指向 $v$，那么我们可以让 $v$ 作为 $u$ 的父结点，这样就构成了一棵树。

这棵树有什么特点呢？就是父亲结点不能走向它的孩子结点，这个很好理解，因为他是有向的。

设有两个点 $x$ 和 $y$，那么对于 $x$ 能走到 $y$ 当且仅当 $y$ 是 $x$ 的祖先结点的时候才能满足。

思路理清了，只要让 $x$ 跳到和 $y$ 一样深度的地方，看结点是否一样即可。

# 代码

因为倍增法比较好写，所以这里使用倍增法。


```cpp
#include <bits/stdc++.h>
using namespace std;
//如何求解LCA就不多说了，想了解的可以到模板题。 
const int N = 150005;
int n, m, lg[N], f[N][19], dep[N], head[N], ct, gjd, maxd = -1;
struct edge{
	int to, nxt;
} a[N];
void add(int u, int v){
	a[++ct].to = v, a[ct].nxt = head[u], head[u] = ct;
}
void dfs(int x, int fa){
	dep[x] = dep[fa] + 1;
	if(dep[x] > maxd) maxd = dep[x];
	for(int i = head[x];i > 0;i = a[i].nxt){
		dfs(a[i].to, x);
	}
}
bool lca(int u, int v){
	if(dep[u] < dep[v]) return 0;
	//当u的深度都小于v，v肯定不是u的祖先 
	while(dep[u] > dep[v]){
		int lgc = lg[dep[u] - dep[v]];
		u = f[u][lgc];
	}
	//看这两个结点是否相同 
	if(u == v) return 1;
	return 0;
}
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++){
		int num;
		scanf("%d", &num);
		if(num != -1){
			f[i][0] = num;
			add(f[i][0], i);
		} else{
			gjd = i;
		}
	}
	for(int i = 2;i <= n;i++){
		lg[i] = lg[i / 2] + 1;
	}
	dfs(gjd, 0);
	for(int j = 1;j <= lg[maxd];j++){
		for(int i = 1;i <= n;i++){
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	int Q;
	scanf("%d", &Q);
	while(Q--){
		int u, v;
		scanf("%d%d", &u, &v);
		//求解 
		if(lca(u, v)){
			printf("Yes\n");
		} else{
			printf("No\n");
		}
	}
	//结束啦！ 
	return 0;
}
```

---

## 作者：tuntunQwQ (赞：1)

由于每个点最多连向一个点，那么反向建图后整张图就成为了一棵树，树的根就是原先出度为 $0$ 的点。

要求 $a$ 能否到达 $b$，就相当于求 $b$ 是否为 $a$ 的祖先，即 $a,b$ 的最近公共祖先是 $b$。

代码如下，可供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,s,idx,d[N],h[N],e[N],nxt[N],fa[N],f[N][30],a,xx,yy;
void add(int a,int b){
	e[++idx]=b;nxt[idx]=h[a];h[a]=idx;
}
void dfs(int u){
	f[u][0]=fa[u];
	for(int j=1;j<=22;j++){
		f[u][j]=f[f[u][j-1]][j-1];
	}
	for(int i=h[u];i!=-1;i=nxt[i]){
		int v=e[i];
		if(v!=fa[u]){
			fa[v]=u;
			d[v]=d[u]+1;
			dfs(v);	
		}
	}
}
int query(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=22;i>=0;i--){
		if(d[f[x][i]]>=d[y]){
			x=f[x][i];
		}
	}
	if(x==y)return x;
	for(int i=22;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return fa[x];
}
int main(){
	memset(h,-1,sizeof h);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(~a)add(a,i);
		else s=i;
	}
	d[s]=1;
	dfs(s);
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>xx>>yy;
		if(query(xx,yy)==yy)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：CatnipQwQ (赞：1)

提供一个不需要求 LCA 的算法。

我们可以发现如果把给定的图看作无向图，那么这张图是一棵树。并且如果把唯一没有出边的点当作这棵树的根节点，那么所有的边都是从儿子指向父亲的。那么点 $a$ 可以到达点 $b$ 就意味着在这棵树上 $a$ 在 $b$ 的子树中。我们知道一个点的子树的 DFS 序是连续的。于是我们只需要对于每个点 $p$ 求出它的 DFS 序 $dfn_p$ 和它子树中最大的 DFS 序 $maxx_p$，那么 $a$ 可以到达 $b$ 的条件就是 $dfn_b\leq dfn_a$ 并且 $maxx_b\geq dfn_a$，于是这题就做完了 awa。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> e[150005];
int dfn[150005], maxx[150005], tot=0;
void dfs(int p)
{
	dfn[p]=++tot;
	for(auto son:e[p])
		dfs(son);
	maxx[p]=tot;
}
int main()
{
	int n,rt;
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
	{
		int fa;
		scanf("%d", &fa);
		if(fa==-1)
			rt=i;
		else
			e[fa].push_back(i);
	}
	dfs(rt);
	int q;
	scanf("%d", &q);
	for(int i=1; i<=q; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(dfn[b]<=dfn[a] && maxx[b]>=maxx[a])
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```

---

## 作者：andyli (赞：1)

注意到题目里的图的反图类似一个有根树，则询问转化为判定有根树中 $\operatorname{lca}(a,b)$ 是否为 $b$。  

```cpp
int main() {
    dR(int, n);
    Graph<void, true> g(n);
    int r = -1;
    _for (i, n) {
        dR(int, p), p--;
        if (p == -2) {
            r = i;
        }
        else {
            g.add(p, i);
        }
    }
    g.build();
    Tree tree(g, r);
    dR(int, q);
    _for (q) {
        dR(int, a, b), a--, b--;
        Yes(tree.lca(a, b) == b);
    }
    return 0;
}
```

---

## 作者：angiing1222 (赞：1)

首先先看题干：

> 给出一个 $n$ 点 $n-1$ 边的有向无环图（其中只有一个点出度为 $0$,其他点出度均为 $1$），给出一些点 $a_i,b_i$，问是否能从点 $a_i$ 走到点 $b_i$。

经过一通分析，发现给出的图很像一棵树，而边的方向一定是由子节点到父节点的。如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/c4yd4wv9.png)

不难发现，在已知 $a_i$ 寻找 $b_i$ 的过程中需要一步一步向上跳，因为 $a_i$ 能到达的点一定是它的父亲、父亲的父亲等等。

顺理成章的，可以联想到基于倍增的 `LCA`，将两个点提到同一深度后，如果它们不相等，则说明不可能从 $a_i$ 走到 $b_i$。

注意在初始化时由于需要预处理点的深度以及它们的 $2^k$ 次祖先，需要反向建边。

以下是通过代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int>G[10000005];
int dep[10000005],f[10000005][21];
void init(int x,int fa){//LCA板子：初始化
	dep[x]=dep[fa]+1;
	for(int i=0;i<=19;++i)f[x][i+1]=f[f[x][i]][i];
	for(int i=0;i<G[x].size();++i){
		int nx=G[x][i];
		f[nx][0]=x;
		init(nx,x);
	}
}
string lca(int x,int y){//LCA板子：查询（略有改动）
	if(dep[x]<=dep[y])return "No";//如果出发点深度比目的点深度小或相等，就不可能到达
	for(int i=20;i>=0;--i){
		int nx=f[x][i];
		if(dep[nx]>=dep[y])x=nx;
		if(dep[x]==dep[y])break;
	}
	return x==y?"Yes":"No";//将两个点提到同一深度后，如果它们不等，则说明不可能从x走到y
}
int main(){
	ios::sync_with_stdio(0);//一点小优化
	cin.tie(0);
	int n,q,g;
	cin>>n;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(x!=-1)G[x].push_back(i);//如果不是根，就反向建边；否则就记录一下
		else g=i;
	}
	init(g,0);
	cin>>q; 
	while(q--){
		int a,b;
		cin>>a>>b;
		cout<<lca(a,b)<<"\n";
	}
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

因为每个点最多有一条与其他点连接的边，所以我们可以把这个图看作一棵树。

于是我们就可以在这个图上进行 LCA 的预处理和查询。

要判断 $a$ 能否到达 $b$，就是在查询 $LCA(a,b)$ 是否为 $b$。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep( i , l , r ) for (int i = (l) ; i <= (r) ; i++)
#define per( i , r , l ) for (int i = (r) ; i >= (l) ; i--)
int n , Q ;
int d[500100] ;
int st[500100][31] ;
int tot ;
struct node{
	int to , nxt ;
}g[500010];
int head[1000010] ;
void add (int u , int v){
	g[++tot] = (node){v , head[u]} ;
	head[u] = tot ;
}
void dfs (int u , int fa){
	d[u] = d[fa] + 1 ;
	st[u][0] = fa ;
	rep (i , 1 , 30){
		st[u][i] = st[st[u][i - 1]][i - 1] ;
	}
	for (int i = head[u] ; i ; i = g[i].nxt){
		int v = g[i].to ;
		if (v == fa) continue ;	
		d[v] = d[u] + 1 ;
		st[v][0] = u ;
		dfs (v , u) ;
	}
}

int LCA (int u , int v){
	if (d[u] < d[v]) swap (u , v);
	per (i , 30 , 0){
		if (d[st[u][i]] >= d[v]){
			u = st[u][i] ;
		}
	}
	if (u == v) return u ;
	per (i , 30 , 0){
		if (st[u][i] != st[v][i]){
			u = st[u][i] ;
			v = st[v][i] ;
		}
	}
	return st[u][0] ;
}

void solve (){
	cin >> n ;
	int root = 0 ;
	rep (i , 1 , n){
		int v ;
		cin >> v ;
		if (v == -1) root = v ;
		add (v , i) ;
	}
	cin >> Q ;
	dfs (root , 0) ;
	while (Q--){
		int a , b ;
		cin >> a >> b ;
		if (LCA (a , b) == b) cout << "Yes\n" ;
		else cout << "No\n" ;
	}
}

signed main (){
	int _ = 1 ;
	//cin >> _ ;
	while ( _-- ){solve () ;}
	return 0 ;
}
```

---

