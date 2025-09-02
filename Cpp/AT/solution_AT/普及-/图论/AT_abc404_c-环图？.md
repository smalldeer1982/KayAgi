# 环图？

## 题目描述

你有一个 $N$ 个点 $M$ 条边的简单无向图，点从 $1$ 到 $N$ 编号，边从 $1$ 到 $M$ 编号。$i$ 号边连通了点 $A_i$ 和点 $B_i$。

你需要判断这个图是否是环图。一个图是“环图”当且仅当图中存在一个环包含图中的所有点，并且图上没有其他的边。

保证给定的图中无自环，无重边。

## 说明/提示

**样例 1 解释**

给定的图如下所示，这是一个环图。

![](https://img.atcoder.jp/abc404/92ea02f287069bfd5e2142ffcafa0e3e.png)



**样例 2 解释**

给定的图如下所示，这不是一个环图。

![](https://img.atcoder.jp/abc404/a428538cd729b649a952c46a67afd8d7.png)

By chenxi2009

## 样例 #1

### 输入

```
4 4
2 4
3 1
4 1
2 3```

### 输出

```
Yes```

## 样例 #2

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
No```

# 题解

## 作者：Little_x_starTYJ (赞：7)

### 题目大意
给你一个简单的无向图，图中有 $N$ 个顶点和 $M$ 条边。顶点编号为 $1,2,\dots,N$，边编号为 $1,2,\dots,M$。边 $i$ 连接顶点 $A_i$ 和 $B_i$。

请判断该图是否为循环图。

简单无向图是指不存在自循环或多条边的无向边图。

循环图是指一个顶点标记为 $1,2,\dots,N$ 的 $N$ 顶点图是一个循环图，当存在 $(1,2,\dots,N)$ 的排列 $(v_1,v_2,\dots,v_N)$ 时，它是一个循环图：

- 对于每个 $i = 1,2,\dots,N-1$，顶点 $v_i$ 和 $v_{i+1}$ 之间有一条边。
- 顶点 $v_N$ 和 $v_1$ 之间有一条边。
- 不存在其他边。

### 解题思路
更简单一点的题意就是只要你能够从任意一点出发把所有点都遍历一遍并且 $n = m$ 就输出 `Yes`，否则输出 `No`。

首先可以发现如果 $n \neq m$，直接输出 `No`。

否则我们跑一遍 dfs，如果所有点都被遍历到了就输出 `Yes`，否则输出 `No`。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[200100];
bool vis[200010];
inline void dfs(int x, int fa) {
    vis[x] = 1;
    for (auto u : v[x]) {
        if (u != fa && !vis[u]) {
            dfs(u, x);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    if (n != m) {
        cout << "No";
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, V;
        cin >> u >> V;
        v[u].push_back(V);
        v[V].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        if (v[i].size() != 2) {
            cout << "No";
            return 0;
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";
    return 0;
}
```

---

## 作者：Gilbert1206 (赞：2)

## 题解：AT_abc404_c [ABC404C] Cycle Graph?

[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc404_c)

## 题目大意
这道题的题意非常的简单，意思为有 $N$ 个点与 $M$ 条边，让你求它是不是有且仅有一个的循环图。

## 思路
这道题我们只要看它每个点是不是只相连 $2$ 条边。如果此时它相连了 $3$ 条边，就会形成多个循环图。如果此时它相连了 $1$ 条边，与他相交的那个图就不可能是循环图了。我们还要注意它可能不止一个图。相信大家一定有许多方法去做这一个步骤，那我就使用广度优先搜索做。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[250000],b[250000],c[250000],vis[250000];
vector<int>d[250000];
void bfs(int ap){
	queue<int>x;
	x.push(ap);//初始化
	while(x.size()!=0){
		int al=x.front();
		x.pop();
		vis[al]=1;
		for(int i=0;i<d[al].size();i++){
			if(vis[d[al][i]]==0){
				x.push(d[al][i]);
			}
		}//for循环找到与他相连的边
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>a[i]>>b[i];
		c[a[i]]++,c[b[i]]++;
		d[a[i]].push_back(b[i]);
		d[b[i]].push_back(a[i]);
	}
	for(int i=1;i<=n;i++){
		if(c[i]!=2){
			cout<<"No";
			return 0;
		}
	}//看他挨着几条边
	bfs(1);//广搜
	for(int i=1;i<=n;i++){
		if(vis[i]==0){
			cout<<"No";
			return 0;
		}
	}//如果遍历一次后还有没有被覆盖的，说明了它可能不止一个图。
	cout<<"Yes";
	return 0;
}
```

---

## 作者：UNDERTALE_RS (赞：1)

# AT_abc404_c [ABC404C] Cycle Graph?

[题目传送门](https://www.luogu.com.cn/problem/AT_abc404_c)

## 题目分析

看到题目，我们需要判断的是这**整个图**是不是一个环图。那么我们就要根据其性质去判断了。

### 环图的性质
我们可以想象一个环图，那么我们可以知道对于这个图上的**每一个结点**，它的入度和出度都应该是 $2$。我们可以在输入时就判断。这里我们选择其中一个进行计算就可以。

同时，因为我们要判断的是整个图，所以在上一步的基础上，我们还要判断这整个图是不是一个**连通图**。这样，满足上面两个条件的图就是要求的环图。

代码如下：  

```cpp
#include <iostream>
#include <queue>
using namespace std;
int n,m,head[200005],pos;
int cnt[200005];
struct node{
	int v,nxt;
}edges[400005];
inline void add_eg(int u,int v){ edges[++pos] = {v,head[u]},head[u] = pos; }
bool vis[200005];

bool check(){
	for(int i = 1;i <= n;i++) if(cnt[i] != 2) return 0; // 判断入度或出度
	int ans = 1; // 经过的点的个数
	queue <int> q; // 用 BFS 广搜实现
	q.push(1),vis[1] = 1;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = head[u];i;i = edges[i].nxt)
			if(!vis[edges[i].v]) vis[edges[i].v] = 1,ans++,q.push(edges[i].v);
	}
	return ans == n;
    // 判断是不是一个连通图
}

int main(){
	cin >> n >> m;
	while(m--){
		int u,v;
		cin >> u >> v;
		add_eg(u,v),add_eg(v,u),cnt[u]++,cnt[v]++;
        // 记录入度或出度
	}
	cout << (check()?"Yes":"No");
	return 0;
}
```



## 总结
是一道基础的题，考察图的遍历以及部分性质。

感谢您的阅读！

---

## 作者：ZZ0520 (赞：1)

## 题目大意

有 $N$ 个点与 $M$ 条边，让你求它是不是有且仅有一个的循环图。

## 思路

-   首先判断图是否联通，如果不连通就不符合题意，无解。
-   其次考虑 $n$ 个点是不是组成了一个环，我们只需要判断每个点的度数是否都为 $2$，因为如果一个点的度数为 $1$，肯定不在环里，度数大于 $2$，则一定不能只组成一个环。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int du[N];

int f[N];
int find(int x){
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
/*
	1. 判断给定图，是否联通  dfs  并查集
	2. 判断每个点的度数是不是2

*/
int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++) f[i] = i;
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		int fu = find(u), fv = find(v);
		f[fu] = fv;
		du[u]++;
		du[v]++;
	}
	for(int i = 1; i <= n; i++){
		if(find(i) != find(1) || du[i] != 2){
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl;
    return 0;
}
```

---

## 作者：__assassin_ (赞：1)

# 题目大意：

给你一个有 $n$ 个点，$m$ 条边的无向图，让你判断这个无向图是否为一个循环图。

# 思路：

首先，我第一个想到的方法，就是记录每个点的度数。如果度数不为 $2$，说明它不可能是一个循环图，输出 `No`，并结束程序。最后输出 `Yes`。

但这个思路有个缺陷，如果给出的图为下面这种，本来要输出 `No` 的，求输出了 `Yes`。

![](https://cdn.luogu.com.cn/upload/image_hosting/za29a20z.png)

这是因为，虽然这六个点的度数都为 $2$，但它们却组成了两个循环图，并不是题目要求的一个循环图。想要是否为一个循环图也很简单，这里采用并查集的方法。我们用 $f_i$ 表示点 $i$ 最大的祖先，在输入的时候，用 $a$ 表示较小的节点编号，用 $b$ 表示较大的节点编号，存完点 $a$ 和 $b$ 的度数后，将 $f_a$ 改为 $b$ 的祖先。最后判断 $n$ 个点的度数和祖先就可以了。

# AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a,b;
int u[200010];
int f[200010];
int flag;
int find(int x){//求最大的祖先 
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;//初始化 
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		u[a]++,u[b]++;//计算每个点的度数 
		f[find(a)]=find(b);//修改a的祖先 
	}
	for(int i=1;i<=n;i++) if(u[i]%2==1) cout<<"No",exit(0);//判断度数是否都为2 
	flag=find(f[1]);//初始化 
	for(int i=2;i<=n;i++){//判断是否为一个连循环图 
		f[i]=find(f[i]);//更新最大祖先 
		if(flag!=f[i]) cout<<"No",exit(0);//不是所有节点的祖先都一样，说明不止一个循环图 
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：HasNoName (赞：0)

### 思路
显然，一个图是环的话，它肯定联通。

又因为如果一个图的任意一个度数大于或小于 $2$，则一定不为环。

显然，一个满足这两个条件的简单图一定是环。

在输入边的时候统计度数，再用并查集维护即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
struct T
{
	int ne,to;
}e[2*N];
int he[N],idx,d[N],fa[N];
void add(int x,int y)
{
	e[++idx].ne=he[x];
	e[idx].to=y;
	he[x]=idx;
}
int find(int x)
{
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	if(m!=n)
	{
		cout<<"No\n";
		return 0;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		d[x]++;
		d[y]++;
		x=find(x);
		y=find(y);
		fa[x]=y;
	}
	for(int i=1;i<=n;i++)
		if(d[i]!=2||find(i)!=find(1))
	{
		cout<<"No\n";
		return 0;
	}
	cout<<"Yes\n";
	return 0;
}
```

---

## 作者：Chase12345 (赞：0)

特别友好的一道题。

首先对于一个环，在去除掉所有无关点之后每个点的度都应该为 $2$。这一点相对显然，就不证明了。

其次，如果一个图是环，则必然连通，必须使用 DFS 进行搜索一遍看看是否连通。

最后，也就是代码环节：
```cpp
#include <bits/stdc++.h> 
using namespace std; 
 
const int N = 2e5 + 5; 
vector<int> adj[N]; 
bool vis[N]; 
int deg[N]; 

void dfs(int cur) { 
    vis[cur] = 1; 
    for (int nex : adj[cur]) 
        if (!vis[nex])
            dfs(nex); 
} 
 
int main() { 
    int n, m; 
    cin >> n >> m;
    if (n != m) { 
        cout << "No\n"; 
        return 0; 
    }
    for (int i = 1, u, v; i <= m; i++) { 
        cin >> u >> v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
        deg[u]++; 
        deg[v]++; 
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] != 2) { 
            cout << "No\n"; 
            return 0; 
        } 
    dfs(1);
    for (int i = 1; i <= n; i++)
        if (!vis[i]) { 
            cout << "No\n"; 
            return 0; 
        }
    cout << "Yes\n"; 
    return 0; 
}
```

---

## 作者：Double_Light (赞：0)

首先，一个 $n$ 个点的环会有 $n$ 条边，先判一下。

然后，一个环一定是连通的，DFS 一遍，再判一下。

接下来，这个图肯定是一棵基环树（一棵树再加一条边），判断每个点的度数是否都为 $2$。

如果上面所有条件全部满足，输出 `Yes`，否则输出 `No`。

---

## 作者：HuangTingFu (赞：0)

这道题要判断给出的无向图是不是一个“循环图”。其实，“循环图”就是一个每个点的度都为 $2$ 的**连通图**。度为 $2$ 很好判断，定义一个 $degree$ 数组记录每个点的度，输入时将每条边的两个端点的度 $+1$ 即可。
```cpp
for(int i=1,x,y;i<=m;i++)
{
  cin>>x>>y;
  degree[x]++,degree[y]++;
  head[x].push_back(y);
  head[y].push_back(x);
}
```
而判断是否为连通图可以用 dfs 或 bfs 进行遍历。这里给出 dfs 做法。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int degree[200010];
bool used[200010];
vector<int> head[200010];
void dfs(int x)
{
	used[x]=1;
	for(int v:head[x])
	{
		if(used[v]==0) dfs(v);
	}
}
signed main()
{
  cin>>n>>m;
  for(int i=1,x,y;i<=m;i++)
  {
  	cin>>x>>y;
  	degree[x]++,degree[y]++;
  	head[x].push_back(y);
  	head[y].push_back(x);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		if(degree[i]!=2||used[i]==0)
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
  return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

用了两个算法发现结合起来就能过了（

## Solution

我们用两个方法来检验图是否符合标准，首先有一个显而易见的判断：如果边数不等于 $n$，就不符合。

先统计每一个点的度数，如果有一个不是 $2$，那么不符合条件。但是样子会有一个错误，在这里放一个 Hack。

```
6 6
1 2
2 3
3 1
4 5
5 6
6 4
```

然后从任一点开始搜索，如果有没有遍历到的点，那么不符合。

于是，我们做完了这一道题。

## Code

[Submission](https://atcoder.jp/contests/abc404/submissions/65472470)

---

## 作者：AnotherDream (赞：0)

# [AT_abc404_c](https://www.luogu.com.cn/problem/AT_abc404_c) 题解
## 题意简述
给你一个图，判断这个图是不是一个环。
## 思路
赛时灵光一闪想到并查集，好像比搜索更好写。

首先环的点数和边数应该相等，但是不判不会影响结果。 

对于前 $M-1$ 条边，这条边连接的两个端点在以前应该是不连通的。  
换句话说，前 $M-1$ 条边构成一条链。

但是最后一条边不能放任不管，所有边都处理完之后，最后的图所有点度数都要为 $2$，否则仍然不能构成环。
## 代码
``` cpp
#include <bits/stdc++.h>
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N = 2e5 + 10;
int tong[N];//度数
struct DSU {
private:
	int *f;
public:
	DSU(int n) {
		f=new int[n+10];
		for(int i=0;i<=n;i++) f[i]=i;
	}
	~DSU() {
		delete []f;
	}
	inline int find(int x) {
		if(f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	inline void merge(int x,int y) {
		f[find(x)]=find(y);
	}
	inline bool ask(int x,int y) {
		return find(x)==find(y);
	}
} a(N);//这是并查集
int n,m;
signed main() {
	fst;
	cin>>n>>m;
	if(n!=m) {
		cout<<"No"<<endl;//显然不是环
		return 0;
	}
	for(int i=1;i<=m;i++) {
		int u,v;
		cin>>u>>v;
		if(a.ask(u,v)&&i<m) {//连接的两条边已经连通
			cout<<"No"<<endl;
			return 0;
		}
		a.merge(u,v);//合并两个点
		tong[u]++,tong[v]++;//统计度数
	}
	for(int i=1;i<=n;i++) {
		if(tong[i]!=2) {//环的每个点度数为2
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;//是环
	return 0;
}

```

---

