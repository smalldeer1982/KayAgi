# [ABC399C] Make it Forest

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_c

给定一个由 $N$ 个顶点和 $M$ 条边构成的简单无向图，顶点编号为 $1$ 至 $N$。第 $i$ 条边连接顶点 $u_i$ 和顶点 $v_i$。  
若要将该图变为森林，至少需要删除多少条边？

**森林的定义**：简单无向图 $F$ 是森林，当且仅当 $F$ 不包含任何环。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq \min\left( \frac{N(N-1)}{2}, 2 \times 10^5 \right)$
- $1 \leq u_i < v_i \leq N$
- 输入的图是简单无向图（无自环和重边）
- 所有输入值均为整数

### 样例解释 1

例如，删除第 1 条边后，该图将变为森林。

翻译由 DeepSeek R1 完成

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
1```

## 样例 #2

### 输入

```
5 0```

### 输出

```
0```

## 样例 #3

### 输入

```
10 10
7 9
4 6
6 10
2 5
5 6
5 9
6 8
4 8
1 5
1 4```

### 输出

```
2```

# 题解

## 作者：2011hym (赞：4)

### 解题思路
树的性质是：对于 $k$ 个顶点的树，恰好有 $k-1$ 条边。因此，对于整个图来说，如果它有 $c$ 个连通分量，那么森林的边数应为 $n-c$。因此，需要删除的边数为：

$$
m-(n-c)
$$

即

$$
m-n+c
$$

其中，$c$ 是连通分量的数量。

### 算法解析

1. [**并查集**](https://oiwiki.com/ds/dsu/)：支持合并和查询操作，是一个比较好用的方法，可以用**路径压缩**进行优化。
2. **统计多余的边**：在构建并查集的过程中，如果两个顶点已经在同一个集合中，则当前边是多余的，需要删除。

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{//并查集的实现
    vector<int>p;
    node(int n):p(n,-1){}
    int find(int x){//最基本的找祖先函数
        return p[x]<0?x:p[x]=find(p[x]);
    }
    bool merge(int x,int y){//去重边
        x=find(x),y=find(y);
        if(x==y)return false;
        if(p[x]>p[y])swap(x,y);
        p[x]+=p[y];
        p[y]=x;
        return true;
    }
};
int n,m,ans,u,v;
int main(){
    cin>>n>>m;
    node dsu(n);
    for(int i=0;i<m;i++){
        cin>>u>>v;
        --u,--v;//别忘了减去
        if(!dsu.merge(u,v)){
            ans++;//统计答案
        }
    }
    cout<<ans;
    return 0;
}
```

### 复杂度分析
- **时间复杂度**：$O(m\times\alpha(n))$，其中 $\alpha$ 是反阿克曼函数，通常很小，在最大情况下为 $4$，所以时间复杂度为 $O(4\times m)$。

~拜拜了您嘞。~

---

## 作者：xiaoke2021 (赞：4)

这也太水了。

---

给你一张无向图，删去尽可能少的边使得这张图没有环。

考虑贪心，在加边的过程中判断**添加这条边**是否会使这张图有环。如果是，则不添加这条边，并将答案加一；否则添加这条边。

注意到并查集可以快速维护两点是否联通。那么这道题就变成板子题了。

[Record here.](https://atcoder.jp/contests/abc399/submissions/64296316)

---

## 作者：Nahida_Official (赞：3)

### [AT_abc399_c [ABC399C] Make it Forest](https://www.luogu.com.cn/problem/AT_abc399_c)

## 题意：
题目大意就是给定一个无向图，要求我们从中选取最少的边删除使得这个图没有环。

## 分析：
好多人用的并查集判断环，但是我用另一种思路写出来了，如果不对还望各路大佬 Hack 一下 QWQ。

解决这道题的利器：图的最小生成树（还不会这部分的同学请前往 [P3366](https://www.luogu.com.cn/problem/P3366))。

求一个图的最小生成树之后我们得到了这个最小生成树最包含的边的个数 $cnt$，最终答案便是 $m-cnt$。

注意一个特判：当 $m=0$ 时直接输出 0，别被这个坑点爆了。

跑一遍 Kruskal 就行了。
## Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define Sangonomiya signed
#define Kokomi main()
#define Love return
#define Nahida 0
#define Forever ;
#define IOS cin.tie(nullptr)->sync_with_stdio(false)
using namespace std;
const int N=1e6;
const int M=2e3;
struct node{
	int u,v;
};
node G[N];
int n,m,fa[N],cnt;
int find(int x){
	if(x!=fa[x]) return fa[x]=find(fa[x]);
	return x;
}
void Ks(){
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		int u,v;
		u=find(G[i].u);
		v=find(G[i].v);
		if(v==u) continue;
		fa[v]=u;
		cnt++;
	}
}
Sangonomiya Kokomi{
	IOS;
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>G[i].u>>G[i].v;
	Ks();
	if(m==0) cout<<0;
	else cout<<m-cnt;
	Love Nahida Forever;
}
```

---

## 作者：lizhixun (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc399_c)

### $\texttt{Description}$

给定一个 $n$ 个顶点 $m$ 条边的简单无向图，问如果要将这个无向图变为一个森林，即为不含任何环的简单无向图，至少需要删去多少条边。

### $\texttt{Solution}$

本题需要使用并查集来解决，这里放上[模板题](/problem/P3367)和 [oi.wiki 上对于并查集的介绍](https://oi-wiki.org/ds/dsu/)。

实际上我们每次只需要判断输入的边的两个顶点 $u$ 和 $v$ 是否在一个集合当中，如果已经在一个集合当中，那么添加这条边就会形成一个环，所以需要删除这条边。否则的话就是将 $u$ 和  $v$ 合并到一个集合当中。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 2e5 + 5;
int n, m, ans, f[maxn];

int find(int x) {
	if (f[x] == x) return x;
	return f[x] = find(f[x]);
}

void merge(int x, int y) {
	int fx = find(x), fy = find(y);
	if (fx != fy) f[fx] = fy;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	
	for (int i = 1; i <= n; i++) f[i] = i;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		
		if (find(u) == find(v)) ans++; // 需要删除
		else merge(u, v); // 合并
	}
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：_qumingnan_ (赞：2)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc399_c)

# 正文开始

## 阅读理解

有一个无向图（无自环），求删几条边可以变成森林。

## 思路：

先看定义，森林，一个无环图。我们可以把他看成一个由 $n$ 棵树组成的图。

我们知道，一颗有 $n$ 个点的树是有 $n-1$ 条边的，也就是说，这个森林中每一个连通块都应该是有 $x$ 个点 $x-1$ 条边，另连通块个数为 $s$，也就是说这个森林应该有 $n-s$ 条边。

那既然应该有 $n-s$ 条边，那题目中给出了 $m$ 条边，就用 $m-(n-s)$ 即可得到最终答案（注意结果要大于等于 $0$）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int b[300005],f[300005],s;
int ans;
int fine(int x){//并查集求连通块 
	if(f[x]==x)return x;
	return f[x]=fine(f[x]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)//初始化 
		f[i]=i;
	for(int i=1;i<=m;i++){
        int x,y;
		cin>>x>>y;
		f[fine(x)]=f[fine(y)];
	}
	for(int i=1;i<=n;i++){//统计连通块个数 
		b[f[fine(i)]]++;
		if(b[f[fine(i)]]==1)s++;
	}
	cout<<max(0ll,m-n+s);
	return 0;
}
```

---

## 作者：forwardFish (赞：1)

这是一道简单的图论题，题目让我们求删除多少条边使一个连通块成为树，我们对于一棵树有一个性质，边数等于点数减一，我们只需要求出每个连通块的点数加边数，我们把所有连通块的边减点加一加起来，得到的就是总边数-总点数+连通块总个数，这就是答案了。

代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
   ios::sync_with_stdio(0);cin.tie(0);
   int n,m;cin>>n>>m;
   int c=n;
   while(m--)
   { 
     int u,v;cin>>u>>v;
     int x=u;while(p[x]!=x){p[x]=p[p[x]];x=p[x];} //判断是否联通 
     int y=v;while(p[y]!=y){p[y]=p[p[y]];y=p[y];}
     if(x!=y){p[y]=x;c--;} //求出总联通块个数（记得判重） 
   }
   cout<<max(m-(n-c),0); // 记得防止负数 
}
```

---

## 作者：Lele_Programmer (赞：1)

# AT_abc399_c 题解

## 思路

众所周知，一棵 $n$ 个点的树有 $n-1$ 条边，我们的目的是将原图的每一个连通块都变成树，对于每个连通块，统计它的点数 $n$ 和边数 $m$，我们要删掉一些边让边数为 $n-1$，也就是删去 $m-(n-1)$ 条边。

## 代码

```cpp
const int N=200005;
const int M=400005;

int n,m;
int e[M],ne[M],h[N],tot;
bool vis[N];

void add(int a,int b) {
    e[tot]=b,ne[tot]=h[a],h[a]=tot++;
}

void dfs(int u,int fa,int& cntp,int& cnte) {
    cntp++;
    vis[u]=true;
    _graph(i,u) {
        cnte++;
        if (vis[e[i]]) continue;
        dfs(e[i],u,cntp,cnte);
    }
}

int main() {
    memset(h,-1,sizeof(h));
    read(n),read(m);
    while (m--) {
        int a,b;
        read(a),read(b);
        add(a,b),add(b,a);
    }
    int ans=0;
    _rep(i,1,n) {
        if (vis[i]) continue;
        int cntp=0,cnte=0;
        dfs(i,0,cntp,cnte);
        cnte>>=1;
        ans+=cnte-(cntp-1);
    }
    write(ans);
    return 0;
}
```

---

## 作者：xy_mc (赞：1)

这道题我一开始居然还想建边？！

### 前置芝士：

[并查集](https://www.luogu.com.cn/problem/P3367)。

### 正解：

题意很简单，就是将每一个连通块里多余的边加到答案里就行了。但是一看数据范围，建边显然是不行的，空间容易炸掉。那么还有什么方法能求连通块呢？

既然这道题并不需要实际意义上的删边，那么并查集就是一个很好的选择，这样一来就不需要建边了。只要节点 $u$ 和节点 $v$ 是同一个祖先，那么说明它们已经在一个连通块内，不需要 $(u,v)$ 这条边了。反之，若祖先不同，就将其合并。

注意：数据量较大，请使用快读。并查集记得路径压缩。

### code：

```cpp
#include<bits/stdc++.h>
#define inl inline
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)
typedef long long ll;
using namespace std;
const int INF=INT_MAX;
const int N=2e5+10;
inl int sf(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,m,f[N],ans;
int find(int x){
	if(f[x]==x) return f[x];
	return f[x]=find(f[x]);
}
int main(){
	n=sf();m=sf();
	rep(i,1,n) f[i]=i;
	rep(i,1,m){
		int u,v;
		u=sf();v=sf();
		int fu=find(u),fv=find(v);
		if(fu==fv) ans++;
		else f[fu]=fv;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：1)

题意简述：

给定一个有 $n$ 个顶点和 $m$ 条边的简单无向图，顶点编号从 $1$ 到 $n$。为了将这个图变成森林，最少需要删除多少条边？一个简单无向图被称为森林，是指它不包含任何环。

思路：

没有环的连通图就是树，如果一棵树有 $n$ 个节点，那么就只要 $n-1$ 条边。设题目中有 $x$ 个连通块，分别有 $y_1,y_2,\dots,y_x$ 个节点，那么只需要 $(y_1-1) + (y_2-1) + \dots +(y_x-1)$ 条边就能构成森林，因为 $n$ 就等于 $y_1+y_2+\dots+y_x$，所以只需要 $n-x$ 条边即可，删去的边就为 $m-(n-x)$，也就是 $m-n+x$ 条边。

所以我们只需要求出有多少个连通块即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int N=2e5+5;
int n,m;
bool vis[N];
vector<int>a[N];
signed main(){
	IOS;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	int num=0;
	for(int i=1;i<=n;i++){//求连通块数量
		if(!vis[i]){
			vis[i]=true;
			num++;
			queue<int>q;
			q.push(i);
			while(!q.empty()){
				int x=q.front();
				q.pop();
				int len=a[x].size();
				for(int j=0;j<len;j++){
					int y=a[x][j];
					if(vis[y])continue;
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	cout<<m-n+num;
	return 0;
}
```
[记录](https://atcoder.jp/contests/abc399/submissions/64294767)。

---

## 作者：Ybll_ (赞：1)

# 题意：

给你一张**简单图**，让你**删除**若干条**边**，让这张图中不出现**环**。

求**最少**要删几条边。

# 思路：

[并查集](https://baike.baidu.com/item/%E5%B9%B6%E6%9F%A5%E9%9B%86/9388442)，每次输入 $u$ 和 $v$ 的时候判断 $u$ 和 $v$ 是否已经连通，如果连通答案加 $1$，不连通就把 $u$ 和 $v$ 所在的集合合并。

# 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[200005],ans;
int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int k=0,i,j;k<m;k++){
		cin>>i>>j,i=find(i),j=find(j);
		if(i==j)ans++;else f[i]=j;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qwqerty (赞：0)

# 解题思路
看到这道题，首先联想到最小生成树。所以我们可以使用并查集。直接合并输入的两个点，若输入的两个点本身已存在于同一集合中，直接跳过，并将答案自增。  
# AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, cnt;
int fa[200005];
int fd(int x) {
	if (fa[x] == x) return x;
	return fa[x] = fd(fa[x]);
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if (fd(u) == fd(v)) cnt++;
		fa[fd(u)] = fd(v);
	}
	cout << cnt;
	return 0;
} 
```

---

## 作者：fengshengshuiqi (赞：0)

### 思路
借助并查集来判断每一条边的两个端点是否属于同一个连通分量。若属于同一个连通分量，就把这样的边视为多余边，最后输出多余边的数量。  
### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int parent[MAXN];
int find(int u) {
    if (parent[u] != u) parent[u] = find(parent[u]); 
    return parent[u];
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) parent[i] = i;
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (find(u) == find(v)) cnt++;
        else parent[find(v)] = find(u); 
    }
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 题目大意

给定一个图，要求删除最少的边使得其变为一个森林。

### 思路

考虑使用并查集。

由于并查集很难删除边，考虑反过来做。

对于一条边的两个点，不连通就连上。

然后记录总答案数再用边数 $m$ 减掉。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400010;
int n,m;
int h[N],e[N],ne[N],idx = 0;
void add(int a,int b){
	e[idx] = b,ne[idx] = h[a],h[a] = idx ++ ;
}
int p[N];
int find (int x){
	if (p[x] != x){
		p[x] = find(p[x]);
	}
	return p[x];
}
bool debug = 0;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ){
		p[i] = i;
	}
	int res = 0;
	for (int i = 1; i <= m; i ++ ){
		int a,b;
		cin >> a >> b;
		int pa = find(a),pb = find(b);
		if (pa != pb){
			p[pa] = pb;
			res ++ ;
		}
	}
	cout << m - res;
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

对于每个连通分量，若它的边数 $E$ 大于节点数 $V$，则存在多余的边需要被删除。

设 $V$ 是顶点数，$E$ 是边数。

如果 $E > V - 1$，我们需要删除 $E - (V - 1)$ 条边，这部分边即为多余的边。

### 代码实现

还是不写代码模板为好。

```cpp
#include <bits/stdc++.h>

#define please return
#define AC 0
#define int long long

#define rep(i, a, b) for (int i = a; i <= b; i++)
using namespace std;

const int MAXN = 2e5 + 10;

int P[MAXN];

int fd (int x) {
    return P[x] == x ? x : P[x] = fd (P[x]);
}
signed main () {
    int N, M; cin >> N >> M;
    rep(i, 1, N) P[i] = i;
    int cnt = 0;
    while (M --) {
        int u, v; cin >> u >> v;
        if (fd (u) != fd (v)) P[fd (u)] = fd (v);
        else cnt ++;
    }
    cout << cnt << endl;
    
	please AC;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc399_c)

[AtCoder 题目传送门](https://atcoder.jp/contests/abc399/tasks/abc399_c)

下面给出一种基于并查集的方法来求解该问题。问题转化为：在一个无向图中形成森林只需要保留每个连通分量的扫树（即一棵树），而每个连通分量的节点数为 $n_i$ 时，理想的边数应为 $n_i-1$。因此，一共最多保留的边数为：
$$
\sum_{i=1}^t(n_i-1)=N-t
$$
这里 $t$ 为连通分量的个数。如果原图有 $M$ 条边，则需要删除的边数为 $M-(N-t)$。

在使用并查集的过程中，如果插入一条边时发现两个顶点已经在同一个集合中，就说明这条边会形成环，因此这条边应当被删除。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int n,m,pa[N],rk[N],ans;
int find(int a){
    if(pa[a]!=a) pa[a]=find(pa[a]);
    return pa[a];
}
void work(int a,int b){
    a=find(a),b=find(b);
    if(a==b) return;
    if(rk[a]<rk[b]) pa[a]=b;
    else{
        pa[b]=a;
        if(rk[a]==rk[b]) rk[a]++;
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) pa[i]=i;
    for(int i=1,u,v;i<=m;i++){
        cin>>u>>v;
        if(find(u)==find(v)) ans++;
        else work(u,v);
    }
    cout<<ans;
}
```

---

## 作者：include13_fAKe (赞：0)

原题即为给定若干个图，求将其变成森林需要删除的最小边数。

考虑对每一个连通块 DFS，求出所有点的父亲。若有一条边的两侧点分别为 $u,v$，且 $fa_u \ne v,fa_v\ne u$ 即必须删除。


```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e6;
int n,m;
vector<int> g[N];
int u[N],v[N];
int fa[N];
int vis[N];
void dfs(int u){
	vis[u]=true;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!vis[v]){
			fa[v]=u;
			dfs(v);
		}
	}
}
signed main(){
	memset(fa,0,sizeof(fa));
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		g[u[i]].push_back(v[i]),g[v[i]].push_back(u[i]);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	int include13=0;
	for(int i=1;i<=m;i++){
		if(fa[u[i]]!=v[i]&&fa[v[i]]!=u[i])	include13++;
	}
	cout<<include13<<endl;
	return 0;
}//ABC399C 
```

---

## 作者：emot1ons (赞：0)

## 题意
给定一个有 $N$ 个顶点和  $M$  条边的简单无向图，顶点标号从  $1$  到  $N$。第  $i$  条边连接顶点  $u_i$  和顶点  $v_i$。为了将图转换为森林，至少需要删除多少条边？

## 思路
我们只需要将每一个联通子图中多余的边都删去，让它变为一棵树即可。

设一个联通子图有 $i$ 个点，则删去后剩余边数为 $i-1$。


## 代码

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,ans,sum;
int in[N],fa[N],siz[N];
vector<int> e[N];
bool vis[N];
int dfs(int);
int main()
{
	cin>>n>>m;
	ans=m;
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i]){
			sum+=dfs(i)-1;
		}
	}
	cout<<m-sum<<endl;
	return 0;
}
int dfs(int x)
{
	vis[x]=true;
	siz[x]=1;
	for(int i=0;i<(int)e[x].size();i++)
	{
		int y=e[x][i];
		if(vis[y]) continue;
		siz[x]+=dfs(y);
	}
	return siz[x];
}
```

---

## 作者：exLucas (赞：0)

显然，用并查集在输入时维护当前两个点是否连通即可，联通则答案加一，因为要把他们拆开，不联通不管。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, res;
struct UF {
    vector<int> pa, rk;
    UF(int n) : pa(n+1), rk(n+1, 0) {
        iota(pa.begin(), pa.end(), 0);
    }
    int find(int x) {
        if(pa[x] != x)  pa[x] = find(pa[x]);
        return pa[x];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(rk[x] < rk[y]) {
            pa[x] = y;
        }
        else {
            pa[y] = x;
            if (rk[x] == rk[y]) rk[x]++;
        }
        return true;
    }
};
int main() {
    scanf("%d %d", &n, &m);
    UF uf(n);
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        if(!uf.unite(u, v)) {
            res ++;
        }
    }
    cout << res;
    return 0;
}
```

---

## 作者：zby0501_ (赞：0)

## 思路：
首先题目要求我们删掉最少的边数，使图没有环。因为删边操作不好做，所以考虑加边。把输入的边一条条加进去，当图出现环时，说明这一条边需要删除，把它加入答案。这时这条边就不用加了。加边的操作我们也可以用并查集高效维护。
## 代码：
```
#include<bits/stdc++.h>
//#define int long long
using namespace std;
int n,m,f[200005],ans;
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) f[i]=i;
	while(m--){
		int a,b;cin>>a>>b;
		if(find(a)==find(b)) ++ans;
		else f[find(a)]=find(b);
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

