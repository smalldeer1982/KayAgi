# [ABC292D] Unicyclic Components

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_d

頂点に $ 1 $ から $ N $ の番号が、辺に $ 1 $ から $ M $ の番号がついた $ N $ 頂点 $ M $ 辺の無向グラフが与えられます。辺 $ i $ は頂点 $ u_i $ と頂点 $ v_i $ を結んでいます。

このグラフのすべての連結成分が次の条件を満たすかどうかを判定してください。

- その連結成分に含まれる頂点の個数と辺の本数が等しい。

## 说明/提示

### 注釈

**無向グラフ** とは、辺に向きの無いグラフのことをいいます。  
あるグラフの **部分グラフ** とは、元のグラフのいくつかの頂点といくつかの辺を選んでできるグラフのことをいいます。  
グラフが **連結** であるとは、グラフに含まれるすべての頂点同士が辺を経由して互いに行き来できることをいいます。  
**連結成分** とは、連結な部分グラフのうち、そのグラフを含んだより大きい連結な部分グラフが存在しないものをいいます。

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i\ \leq\ v_i\ \leq\ N $
- 入力はすべて整数

### Sample Explanation 1

このグラフには頂点 $ 1 $ のみからなる連結成分と頂点 $ 2,3 $ からなる連結成分があります。 前者には $ 1 $ 本の辺(辺 $ 2 $ )が、後者には $ 2 $ 本の辺(辺 $ 1,3 $ )が含まれており、条件を満たします。

## 样例 #1

### 输入

```
3 3
2 3
1 1
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
3 5
1 5```

### 输出

```
Yes```

## 样例 #3

### 输入

```
13 16
7 9
7 11
3 8
1 13
11 11
6 11
8 13
2 11
3 3
8 12
9 11
1 11
5 13
3 12
6 9
1 10```

### 输出

```
No```

# 题解

## 作者：zhlzt (赞：5)

### 题目
- 有 $n$ 个顶点。
- 有 $m$ 条无向边。
- 第 $i$ 条无向边连接 $u_i,v_i$。
- 若 $(u_i,v_i)$ 和 $(u_j,v_j)$ 是同一条边，当且仅当 $i=j$。
- 问是否所有连通块里的点数和边数都相等。
- $1\le n,m\le 2\times 10^5$，$1\le u_i\le v_i\le n$。

### BFS 做法
这道题很明显是连通块问题，但重点就在于数边。

因为邻接表存一条无向边是要存两条有向边的，但题目中说的边数是指无向边的个数。

于是我们可以想到，给存同一条无向边的两条有向边存相同的编号，这样数边时就只会数一次了。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,num,x,y,vis[200010],mp[200010];
vector<pair<int,int> >edge[200010];
bool bfs(int s){
	queue<int>q;
	int fa,sn,id,ans1=0,ans2=0;
	q.push(s),vis[s]=1;
	while(!q.empty()){
		fa=q.front(),q.pop();
		ans1++;//数点
		for(int i=0;i<edge[fa].size();i++){
			sn=edge[fa][i].first,id=edge[fa][i].second;
			if(mp[id]==0) ans2++,mp[id]=1;//数边
			if(vis[sn]==0) q.push(sn),vis[sn]=1;
		}
	}
	return ans1==ans2;//判断点数和边数是否相等 
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		edge[x].push_back({y,i});
		edge[y].push_back({x,i});
	}
	int flag=1;
	for(int i=1;i<=n;i++)
		if(vis[i]==0)
			flag&=bfs(i);//只有当所有连通块都满足条件时才成立 
	if(flag==1) printf("Yes");
	else printf("No");
	return 0;
}
```

---

## 作者：Eleveslaine (赞：3)

基础图论题。  
前置知识：[并查集](https://www.luogu.com.cn/problem/P3367)。

## 题意

给定一个 $n$ 个顶点 $m$ 条边的**无向图**，判断以下命题是否成立：

- 该图的每一个连通分量中，点数和边数相等。

注：无向图的连通分量可以简单地理解为把图划分成几个部分，使这些子图之间互相没有连边，则每个子图都是无向图的一个连通分量。

## 分析

无向图，直接使用并查集：对于输入的每条边 $(u_i,v_i)$，合并 $u_i,v_i$ 所在集合。  
这样合并完之后，剩下的每个集合就是一个连通分量。  
同时，为了判断答案，我们需要记录每个连通分量中的点数和边数。设 `e[i]` 为第 $i$ 个连通分量中的点数，`siz[i]` 为其边数，合并完扫一遍所有边和所有点统计这两个量即可。  
最后遍历所有连通分量，按题目要求判断答案即可。  

**注意：并查集别忘了初始化，每个元素祖先是自己。**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200005
int n,m,fu,fv,f[maxn],e[maxn],u[maxn],v[maxn],siz[maxn];
// 并查集模板
inline int find(int k)
{
    if(f[k]==k)
        return f[k];
    return f[k]=find(f[k]);
}
#define Yes {cout << "Yes\n";return 0;}
#define No {cout << "No\n";return 0;}
int main()
{
    cin >> n >> m;
    // 初始化，勿忘
    for(int i=1;i<=n;++i)
        f[i]=i;
    for(int i=1;i<=m;++i)
    {
        cin >> u[i] >> v[i];
        fu=find(u[i]),fv=find(v[i]);
        f[fu]=fv;
    }
    for(int i=1;i<=m;++i)
        ++e[find(u[i])];
    for(int i=1;i<=n;++i)
        ++siz[find(i)];
    for(int i=1;i<=n;++i)
        if(f[i]==i && e[i]!=siz[i])
            No;
    Yes;
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

直接对于整个图跑 `dfs`，那么此时我们就可以得到每一个连通块。

在 `dfs` 的同时，记录每个连通块的点数 $cnt_a$，边数 $cnt_b$。

注意到一条边 $(u,v)$，在 $u\rightarrow v$ 和 $v\rightarrow u$ 的时候都会遍历到，所以这个连通块的实际边数只有 $\dfrac{cnt_b}{2}$。由于我们需要判断每个连通块内部的边数是否等于点数，所以我们可以知道若 $cnt_a=\dfrac{cnt_b}{2}$ 时合法，否则不合法。

时间复杂度 $O(n+m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m,cnta,cntb;
bool vis[maxn];
vector<int> G[maxn];
void dfs(int u){
	if(vis[u])
		return;
	++cnta;
	vis[u]=1;
	for(auto v:G[u]){
		++cntb;
		dfs(v);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			cnta=cntb=0;
			dfs(i);
			if(cnta!=cntb/2){
				puts("No");
				return 0;
			}
		}
	puts("Yes");
	return 0;
}
```

---

## 作者：Hyh_111 (赞：1)

## **题意**

给定一个 $n$ 个点，$m$ 条边的无向图，若在这个图中所有强连通分量包含的点数和边数都相同，输出 `Yes`，否则输出 `No`。

## **思路**

看到“无向图”“强连通分量”“点数”和“边数”，我们可以想到用并查集解决此题。

我们可以用 $fa_i$ 表示在并查集中节点 $i$ 的父亲，用 $siz_i$ 表示以节点 $i$ 为根的子树的节点数，用 $esz_i$ 表示以节点 $i$ 为根的子树的边数，在输入时合并并查集的每一棵树。

最后，我们检验所有满足 $fa_i = i$ 的节点的 $siz_i$ 和 $esz_i$ 是否相等即可。

## **代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
int fa[200005],siz[200005],esz[200005];
int n,m;

int find(int x)//找祖先
{
	return (fa[x] == x)?(x):(fa[x] = find(fa[x]));
}

void Union(int u,int v)//合并
{
	int x = find(u),y = find(v);
	if (x == y) {esz[x]++;return;}
	fa[x] = y;
	siz[y] += siz[x];
	esz[y] += esz[x] + 1;
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i,siz[i] = 1,esz[i] = 0;//记得初始化
	for (int i = 1; i <= m; i++)
	{
		int u,v;
		cin >> u >> v;
		Union(u,v);//输入时合并
	}
	for (int i = 1; i <= n; i++)
		if (fa[i] == i)
			if (esz[i] != siz[i])//检验
			{
				puts("No");
				return 0;
			}
	puts("Yes");
	return 0;
}
```

---

## 作者：ケロシ (赞：0)

# 题意
在一个 $n$ 个点，$m$ 条边的图中，如果每一个连通块的点数与边数相同，那么输出 Yes，否则输出 No。
# 解题思路
方法一：   
可以用并查集维护，并查集中维护每一个块的父节点与这个块的点数与边数。
方法二：    
只用并查集维护每一个节点在并查集中的父节点，然后通过枚举每一个点和边来对块的点数和边数进行计数。
# 代码
可以使用并查集板子，或者 Atcoder 提供的库 AC Library。    
方法一：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+5;
int n,m;
int f[N],s[N],p[N];
int find(int x){ // 并查集
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        f[i] = i;
        s[i] = 1; // 节点数
        p[i] = 0; // 边数
    }
    for(int i=1;i<=m;i++) {
        int u,v;
        cin >> u >> v;
        if(find(u)==find(v)) { // 已经在一个块里了
            p[find(u)]++; 
        }
        else{
            // 并查集合并
            s[find(u)]+=s[find(v)]; 
            p[find(u)]+=p[find(v)]+1;
            f[find(v)]=find(u);
        }
    }
    for(int i=1;i<=n;i++) {
        if(s[find(i)]!=p[find(i)]){
            cout << "No";
            return;
        }
    }
    cout << "Yes";
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```
方法二：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+5;
int n,m,f[N],u[N],v[N];
int a[N],b[N]; // 记录每一个块点数与边数
int find(int x){
    if(f[x]==x) return x;
    return f[x]=find(f[x]);
}
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        f[i] = i;
    }
    for(int i=1;i<=m;i++) {
        cin >> u[i] >> v[i];
        f[find(v[i])]=find(u[i]); // 直接合并
    }
    for(int i=1;i<=n;i++) { // 统计点数
        a[find(i)]++;
    }
    for(int i=1;i<=m;i++) { // 统计边数
        b[find(u[i])]++;
    }
    for(int i=1;i<=n;i++) if(a[find(i)]!=b[find(i)]) {
        cout << "No";
        return;
    }
    cout << "Yes";
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```
对于法二还可以使用 AC Library 中的 DSU:
```cpp
#include <bits/stdc++.h>
#include <atcoder/all>
#define ll long long
using namespace std;
using namespace atcoder;
const int N = 2e5+5;
int n,m,u[N],v[N];
int a[N],b[N];
void solve(){
    cin >> n >> m;
    dsu d(n + 1);
    for(int i=1;i<=m;i++) {
        cin >> u[i] >> v[i];
        d.merge(u[i],v[i]);
    }
    for(int i=1;i<=n;i++) {
        a[d.leader(i)]++;
    }
    for(int i=1;i<=m;i++) {
        b[d.leader(u[i])]++;
    }
    for(int i=1;i<=n;i++) if(a[d.leader(i)]!=b[d.leader(i)]) {
        cout << "No";
        return;
    }
    cout << "Yes";
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```

---

## 作者：incra (赞：0)

## 题意
给定 $n$ 个点，$m$ 条边一张图，判断每一个连通块的点数和边数是否相同。
## 题解
由于若一个连通块连通且没有环，也就是说这个连通块是一个树时，若这个图有 $n$ 个点，那么就有 $n$ 条边，所以我们只需要用并查集统计在么一个连通块中，多余的边数量为 $1$。这里的多余是指这条边连上后，总的连通块数量不变。

由于我们无法很好的统计边的数量，所以我们可以把要统计的边的数量加到这条边的某一个点上。

当 $n\neq m$，答案显然为 No。
## 代码
```cpp
#include <iostream>
using namespace std;
const int N = 200010;
int n,m;
int p[N],cnt[N];
int find (int x) {
	if (p[x] != x) p[x] = find (p[x]);
	return p[x];
}
int main () {
	cin >> n >> m;
	if (n != m) {
		puts ("No");
		return 0;
	}
	for (int i = 1;i <= n;i++) p[i] = i;
	while (m--) {
		int a,b;
		cin >> a >> b;
		int ra = find (a),rb = find (b);
		if (ra != rb) p[ra] = rb;
		else cnt[a]++;
	}
	for (int i = 1;i <= n;i++) {
		int ri = find (i);
		if (ri != i) cnt[ri] += cnt[i];
	}
	for (int i = 1;i <= n;i++) {
		if (i != find (i)) continue;
		if (cnt[i] != 1) {
			puts ("No");
			return 0;
		}
	}
	puts ("Yes");
    return 0;
}
```

---

## 作者：zajasi (赞：0)

## 题意
给你一个无向图（可能由重边和自环），问满不满足以下要求：

+ 对于图中的每一个强连通分量，满足点数和边数相等。
## 解题思路
首先，用邻接表建图。

然后，对于 $1 \sim n$ 中每一个没有访问过的结点就进行访问。在访问的过程中，记录结点数和边数。由于边是双向的，也就是每一条边会加两次。所以最后结点个数要乘 $2$ 进行比较。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int c,z,x,y,n,m;
int in[200020];
vector<int> g[200020];
void dfs(int x){
    in[x]=1;
    c+=g[x].size();
    z++;
    for(int i=0;i<g[x].size();i++){
        if(!in[g[x][i]])dfs(g[x][i]);
    }
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);    
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            c=0;
            z=0;
            dfs(i);
            if(c!=z*2){
                cout<<"No";
                return 0;
            }            
        }
    }
    cout<<"Yes";
    return 0;
}
```

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定 $n$ 个点 $m$ 条无向边（可能重边，可能自环）。对于每个联通块，是否满足点数等于边数的条件。

### 题目分析：

这道题我们统计每个点的度数，对于一张无向图，边数等于所有节点的度数除于 $2$。我们只用统计每个联通块的点数和度数和即可。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
vector<int> a[N];
int into[N];
bool vis[N];
int n,m;
int P=0;
int dfs(int x){
	P+=into[x];vis[x]=true;int res=0;
	for(int i=0;i<a[x].size();i++)
		if(!vis[a[x][i]])
			res+=dfs(a[x][i]);
	return res+1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		into[x]++;into[y]++;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			P=0;
			if(dfs(i)!=(P>>1)){
				puts("No");
				return 0;
			}
		}
	puts("Yes");
	return 0;
}
```

---

## 作者：Kevin_Mamba (赞：0)

## 题意

给定一个 $n$ 个点 $m$ 条边的无向图。

求对于**每个连通块，其点数是否等于边数**。

若**所有的**连通块都满足要求，输出 ```Yes```；否则输出 ```No```。

## 解题思路

遍历每个连通块，求出它的点数是很容易的，只要开个数组表示是否到达过，保证不重复遍历即可。

对于边数也不难。记录连通块内**每个点的所有连边（重复的也要算，看样例就知道了）** 的和，将其除以 $2$ 就是这个连通块的边数。

## 代卖实现

可能用 ```vector``` 查询边数时会更方便，但我喜欢用前向星。

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

const int N=2e5+10,M=1e6+10;

int n,m,to[M],cnt,nxt[M],head[N],s1,s2;

bool vis[N];

il void qian(re int u,re int v) {
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

il void dfs(re int u) {
	vis[u]=true;
	s1++;
	for(re int i=head[u];i;i=nxt[i]) {
		re int v=to[i];
		s2++;
		if(vis[v]) continue;
		dfs(v);
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(re int i=1,u,v;i<=m;i++) {
		scanf("%d%d",&u,&v);
		qian(u,v);
		 qian(v,u);
	}
	for(re int i=1;i<=n;i++) {
		if(vis[i]) continue;
		s1=s2=0;
		dfs(i);
		if(s1!=s2>>1) return puts("No"),0;
	}
	return puts("Yes"),0;
}

```

---

