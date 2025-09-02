# [PA 2015] 人赢 / Mistrzostwa

## 题目背景

译自 [PA 2015](https://sio2.mimuw.edu.pl/c/pa-2015-1/p/) R2.

## 题目描述

给定一张 $n$ 个点 $m$ 条边的**简单**（无重边自环的）无向图 $G=(V,E)$。其中节点编号 $1\sim n$。

给定正整数 $d$。选出一个最大的点集 $S\subseteq V$，满足：

- $\forall u\in S$，$\displaystyle \sum_{v\in S} [(u,v)\in E]\ge d$。换句话说，$u$ 向 $S$ 内点至少连了 $d$ 条边。
- $S$ 的导出子图（induced subgraph）是连通的。

你需要构造一个 $S$ 使得 $|S|$ 取到最大值，或者报告无解。

点集 $V'\subseteq V$ 的导出子图定义为 $G'=(V',E')$，其中 $E'=\{(u,v)\in E: u\in V'\land v\in V'\}$。


## 说明/提示

- $1\le d\lt n\le 2\times 10^5$；
- $1\le m\le 2\times 10^5$。
- 给定的图无重边自环。


## 样例 #1

### 输入

```
4 4 2
1 2
2 3
3 4
4 2```

### 输出

```
3
2 3 4```

## 样例 #2

### 输入

```
3 2 2
1 2
2 3```

### 输出

```
NIE```

# 题解

## 作者：tuboshu666 (赞：1)

## 前言：
本篇主要介绍本题的并查集做法。如果你还不了解并查集，可以先做做 [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)。

## 思路：
首先简化题意：本题要求在无向图内，找到一个任意一点出度均不小于 $d$ 的联通子图。

直观想到的做法是：找到每个出度不小于 $d$ 的点，判断与其相连的点出度是否符合要求，若符合，将两个点集合并。

但是这种做法有一个问题。请看以下样例：

```cpp
5 4 2
1 2
1 3
2 4
3 5
```

![](https://cdn.luogu.com.cn/upload/image_hosting/anyqx1z8.png)

很显然，该样例应该报告无解。但上述做法却会认为 $1-2-3$ 为一个合法点集。原因就在于节点 $1、2、3$ 出度均为 $2$，而事实上，并不是所有出度都应该被计算在内。例如 $5$ 一定不可能包含在一个合法点集内，因此与其相连点的出度均要减去 $1$。

于是问题就转换为：我们应当如何删掉无效出度？通过分析，初始出度小于 $d$ 的点一定无效。那么从这些点出发，其相连点出度均要减 $1$。若某点在删除过程中出度变得小于 $d$，则该点也不合法，再从该点出发重复以上步骤。该过程可以通过队列实现。

## Solution：
通过以上分析，我们需要先删除无效出度，再对剩下的出度不小于 $d$ 的点进行并查集操作。最后遍历每个并查集，找到最大点集，并升序输出其中各点。

特别地，若每个并查集的大小均不大于 $d$，则报告无解。

具体实现过程已在代码中注释。最后十分感谢阅读此题解。

## Code：

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 2e5 + 10;
vector<int> g[N];
queue<int> q;
bool vis[N]; //标记是否入队
int fa[N]; //父节点
int dout[N]; //出度
int cnt[N]; //并查集计数
int n,m,d;

int find(int x) //查询x的祖先
{
    if (fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> d;
    for (int i = 1 ; i <= m ; i++)
    {
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        dout[u]++;
        dout[v]++;
    }

    for (int i = 1 ; i <= n ; i++)
    {
        fa[i] = i; //并查集初始化
        if (dout[i] < d) //出度小于d则入队
        {
            q.push(i);
            vis[i] = true;
        }
    }

    while (!q.empty()) //删除入度小于d的点
    {
        int pos = q.front();
        q.pop();

        for (int i = 0 ; i < g[pos].size() ; i++)
        {
            int to = g[pos][i];
            dout[to]--;
            if (dout[to] < d && !vis[to]) //删边后入度小于d且未入队的点入队
            {
                q.push(to);
                vis[to] = true;
            }
        }
    }

    for (int i = 1 ; i <= n ; i++)
    {
        if (dout[i] < d) continue;
        for (int j = 0 ; j < g[i].size() ; j++)
        {
            int to = g[i][j];
            if (dout[to] < d) continue;
            int r1 = find(to);
            int r2 = find(i);
            if (r1 != r2) fa[r2] = r1; //处于不同并查集则合并
        }
    }

    for (int i = 1 ; i <= n ; i++)
    {
        int r = find(i);
        cnt[r]++; //并查集大小计数
    }

    int maxn = -2e9;
    int id = 0;
    for (int i = 1 ; i <= n ; i++)
    {
        if (cnt[i] > d)
        {
            if (cnt[i] > maxn)
            {
                maxn = cnt[i];
                id = i; //符合要求的并查集编号
            }
        }
    }

    if (maxn == -2e9) cout << "NIE" << endl; //无符合要求点集则输出无解
    else
    {
        cout << maxn << endl;
        for (int i = 1 ; i <= n ; i++)
        {
            if (find(i) == id)
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
```

---

## 作者：hytallenxu (赞：1)

## 前言
没啥好说的简单题。

## 正文
题目就是让你输出一个无向图里面，每个点度数至少为 $d$ 的**最大的**联通子图。

那直接说怎么做。

显然，在这个子图里面度数少于 $d$ 的点肯定是不能被包括进去的，所以我们应该能自然而然地想到，需要在全图中把它们删掉。

删掉的过程也很简单，将每一个度数少于 $d$ 的点 $u$ 加入队列删邻居即可。需要注意的是，减完度数之后，假如邻居的度数少于 $d$ 的话，也要加入队列。

做完了之后就可以判断是不是还有点没有加入过这个队列，假如所有点都进过队列的话就代表无解。

判完无解之后，我们就得到了很多个连通分量，遍历每一个连通分量，取当中最大的集合就好了。

## Code

时间复杂度为 $\Theta (n\log n)$，瓶颈在排序。

```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mkp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,m,t,cnt=0;
const int maxn=2e5+10;
const double eps=1e-6;
vector<int> e[maxn];
int deg[maxn],vis[maxn];

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>m>>t;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		e[u].pb(v);e[v].pb(u);
		deg[u]++,deg[v]++;
	}
	bitset<maxn> in;in.flip();
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(deg[i]<t) q.push(i),in[i]=0;
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int v:e[u]){
			if(in[v]){
				deg[v]--;
				if(deg[v]<t){
					in[v]=0;
					q.push(v);
				}
			}
		}
	}
	bool flag=0;
	for(int i=1;i<=n;i++) if(in[i]){flag=1;break;}
	if(!flag) return cout<<"NIE"<<endl,0;
	vector<int> ans;
	for(int i=1;i<=n;i++){
		if(in[i] && !vis[i]){
			vector<int> res;
			queue<int> q;
			q.push(i);vis[i]=1;
			while(!q.empty()){
				int u=q.front();q.pop();res.pb(u);
				for(int v:e[u]){
					if(in[v] && !vis[v]){
						vis[v]=1,q.push(v);
					}
				}
			}
			if(res.size()>ans.size()) ans=res;
		}
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(int x:ans) cout<<x<<" ";
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：1)

拓扑排序即可。

显然，我们只需要把所有度数 $< d$（删除过程中 $< d$ 的也算）的点删除，再找出一个点的个数最多的连通块即可。

对于前半部分，可以使用拓扑排序，判连通块可以使用 `dfs` 解决。

注意在拓扑排序时不要让一个点连续入队。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
const int inf = 1e16;
const int inf2 = 1e15;
int T,n,m,d;
int deg[N],sz[N],from[N];
vector <int> g[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void toposort(){
	queue <int> q;
	for (int i = 1 ; i <= n ; i++){
		if (deg[i] < d){
			q.push(i);
			deg[i] = inf;
		}
	}
	while (!q.empty()){
		int u = q.front();
		q.pop();
		for (auto v : g[u]){
			deg[v]--;
			if (deg[v] < d){
				q.push(v);
				deg[v] = inf; // 标记
			}
		}
	}
}
void dfs (int u,int tot){ // 跑连通块
	from[u] = tot;
	for (auto v : g[u]){
		if (deg[v] >= inf2 || from[v]) continue;
		dfs(v,tot);
	}
}
signed main(){
	close();
	cin >> n >> m >> d;
	for (int i = 1 ; i <= m ; i++){
		int u,v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++; deg[v]++;
	}
	toposort();
	int tot = 0;
	for (int i = 1 ; i <= n ; i++){
		if (deg[i] >= inf2 || from[i]) continue;
		dfs(i,++tot);
	}
	if (!tot) cout << "NIE\n";
	else{
		int mx = 0,id = 0;
		for (int i = 1 ; i <= n ; i++)
			if (deg[i] < inf2) sz[from[i]]++;
		for (int i = 1 ; i <= tot ; i++){
			if (sz[i] > mx){
				mx = sz[i];
				id = i;
			}
		}
		cout << mx << endl;
		for (int i = 1 ; i <= n ; i++)
			if (from[i] == id) cout << i << ' ';
		cout << endl;
	}
	return 0;
}
```

---

## 作者：ZRZ0818 (赞：1)

题目要求选出子图的任意节点度数不小于 $d$，所以可知任意度数小于 $d$ 的节点**不可能会有贡献**。

于是我们考虑将度数小于 $d$ 的节点直接删除，具体做法：

1. 新建一个队列，存储原来所有度数小于 $d$ 的节点；
2. 弹出队首元素 $u$，遍历 $u$ 的所有相连节点 $v$；
3. $v$ 的度数减 $1$，若 $v$ 的度数小于 $d$，入队。
4. 循环步骤 2，直到队列为空。

删完节点后我们就会得到若干个连通块，可以考虑使用并查集维护连通块，若没有连通块则无解。

 _AC code：_ 

 
```cpp
#include<bits/stdc++.h>
const int MAXN =2e5+5;

using namespace std;
int n,m,d,ind[MAXN],fa[MAXN],cnt[MAXN];
bool vis[MAXN];
deque<int> g[MAXN];
queue<int> out;

void input() {
	cin >>n >>m >>d;
	for ( int i=1; i<=m; i++) {
		int u,v; cin >>u >>v;
		g[u].push_back(v),g[v].push_back(u);
		++ind[u],++ind[v];
	}	
}

void init() {
	for ( int i=1; i<=n; i++) fa[i] =i;	
	for ( int i=1; i<=n; i++) {
		if ( ind[i] <d) out.push(i),vis[i] =1;
	}
	while ( out.size()) {  //删边
		int pos =out.front(); out.pop();
		for ( const int to:g[pos]) {
			if ( vis[to]) continue;
			--ind[to];
			if ( ind[to] <d) vis[to] =1,out.push(to); 
		}
	}	
}

int find( int x) {
	return x ==fa[x]? x:fa[x] =find(fa[x]);
}

void solve() {
	for ( int u=1; u<=n; u++) { 
		if ( vis[u]) continue;
		for ( const int v:g[u]) {
			if ( vis[v]) continue;
			int fu =find(u),fv =find(v);
			fa[fv] =fu;
		}
	}
	int mmax =0,id =0;
	for ( int i=1; i<=n; i++) {
		int fi =find(i);
		if ( vis[fi] || vis[i]) continue;
		++cnt[fi];
	}
	for ( int i=1; i<=n; i++) {
		if ( mmax <cnt[fa[i]]) mmax =cnt[fa[i]],id =fa[i];
	}
	if ( !mmax) {
		cout <<"NIE\n"; exit(0);
	}
	cout <<mmax <<'\n';
	for ( int i=1; i<=n; i++) {
		if ( fa[i] ==id && !vis[i]) cout <<i <<' ';
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	input();
	
	init();
	
	solve();
	
	return 0;
}
```

---

## 作者：ycy1124 (赞：0)

### 题意
给出一张简单无向图，要求选出其中一个最大的点集满足点集内每个点连接该点集内的边数大于等于 $d$ 并且该点集内所有点联通。
### 思路
发现如果有两个合法点集有交那么肯定是可以将这两个合法点集合并成一个更大的合法点集。并且我们发现如果把所有度数小于 $d$ 的去掉后剩余的每个点一定都可以有一种方案与其他的点构成一个合法点集。至于为什么你会发现只需要对于一个点此时将所有与他不连通的点去掉那么对于他这个联通块内的所有点不受到影响，于是就能得到一个合法点集。接下来考虑如何去掉那些度数小于 $d$ 的点。我们发现最开始就不满足的很好找，但是有一些点是在某些点删掉后才不满足的，每删掉一个点就重新找时间会炸。考虑优化这个，由于每个点删掉后只会对它连着的点造成影响，所以每次只需要判断一下被删点连着的点就行了。
### 代码
由于此题边数并不多，所以是不会超时的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,ans;
int du[200005],w;
bool bj[200005],vis[200005];
vector<int>a[200005],b,Ans;
void work(int p){
    bj[p]=1;
    for(auto it:a[p]){
        if(bj[it]){
            continue;
        }
        du[it]--;
        if(du[it]<d){
            work(it);
        }
    }
}
void dfs(int p){
    w++;
    b.push_back(p);
    vis[p]=1;
    // ans=max(ans,w);
    for(auto it:a[p]){
        if(!vis[it]&&!bj[it]){
            dfs(it);
        }
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>m>>d;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
        du[u]++;
        du[v]++;
    }
    for(int i=1;i<=n;i++){
        if(bj[i]){
            continue;
        }
        if(du[i]<d){
            work(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]&&!bj[i]){
            w=0;
            b.clear();
            dfs(i);
            if(w>ans){
                ans=w;
                Ans=b;
            }
        }
    }
    if(!ans){
        return cout<<"NIE",0;
    }
    cout<<ans<<'\n';
    sort(Ans.begin(),Ans.end());
    for(auto it:Ans){
        cout<<it<<' ';
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/205939801)。

---

## 作者：litangzheng (赞：0)

### 前言：  

虽然是黄题，但是本蒟蒻调了好久才A……  

### 过程：  

观察数据范围，很显然我们需要一个 $O(n+m)$ 的算法，这个算法一定是搜索啦。  
其实这道题和拓扑排序有点像。都用了 bfs 和度数，具体的过程如下：  
1. 算出所有点的度数，将度数小于 $d$ 的点入队，并打上标记。
2. 取出队头的点 $x$ ，并弹出队头。
3. 遍历所有与 $x$ 相邻的点，将相邻的点的度数减一。
4. 如果相邻的点没有被标记且度数小于 $d$ ，将这个点入队并标记。  
重复2,3,4步，直到队列为空。  

此时，没有被标记的点就是集 $S$ 内点的候选点。然后 dfs 找一下联通块，比较一下联通块大小并输出最大联通块内的点就好了，注意要排序。

### 代码：  


```cpp
#include<bits/stdc++.h>
#define N 2000005
#define int unsigned int //不知为何不加这个会报错
using namespace std;
int head[N],cnt=1,n,m,d,du[N],l_cnt,maxn,maxdex,s[N];
bool vis[N];
vector <int> ans[N]; //记联通块的
struct Edge{
	int to,nxt;
}edge[N*2]; //无向图开两倍
void addedge(int u,int v){
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt++;
}
void dfs(int x){
	ans[l_cnt].push_back(x);
	vis[x]=1;
	for(int i=head[x];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(!vis[to]) dfs(to);
	}
}
signed main(){
	cin>>n>>m>>d;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		du[u]++;du[v]++; //无向图，两个点都要加
		addedge(u,v);addedge(v,u);
	}
	queue<int> q;
	for(int i=1;i<=n;i++){
        if(du[i]<d){
            q.push(i);
            vis[i]=1;
        }
    }
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=edge[i].nxt){
			int to=edge[i].to;
			du[to]--;
			if(!vis[to]&&du[to]<d){
				q.push(to);
				vis[to]=1;
			}
		} 
	}//核心就这一段
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			l_cnt++;
			dfs(i); // dfs 找联通块
		}
	}
	if(l_cnt==0) cout<<"NIE"; //没有联通块代表所有点都不能进入 S 集
	else{
		for(int i=1;i<=l_cnt;i++){
			if(ans[i].size() > maxn){
				maxn=ans[i].size();
				maxdex=i;
			}
		}//找找谁才是最大的联通块
        cout<< ans[maxdex].size() <<endl;
	    for(int i=0;i < ans[maxdex].size() ;i++) s[i]=ans[maxdex][i];
        sort(s,s+ans[maxdex].size()); //排个序
        for(int i=0;i < ans[maxdex].size() ;i++) cout<<s[i]<<" ";//输出一下
	}
}
```
完结撒花！！！

---

