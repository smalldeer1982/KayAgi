# [ABC218F] Blocked Roads

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_f

$ N $ 頂点 $ M $ 辺の有向グラフが与えられます。頂点には $ 1 $ から $ N $ の番号、辺には $ 1 $ から $ M $ の番号がついています。辺 $ i\,(1\ \leq\ i\ \leq\ M) $ は頂点 $ s_i $ から頂点 $ t_i $ に向かう長さ $ 1 $ の辺です。

各 $ i\,(1\ \leq\ i\ \leq\ M) $ について、辺 $ i $ のみ通れないときの頂点 $ 1 $ から頂点 $ N $ までの最短距離を求めてください。ただし、頂点 $ 1 $ から頂点 $ N $ にたどり着けない場合は `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 400 $
- $ 1\ \leq\ M\ \leq\ N(N-1) $
- $ 1\ \leq\ s_i,t_i\ \leq\ N $
- $ s_i\ \neq\ t_i $
- $ (s_i,t_i)\ \neq\ (s_j,t_j) $ $ (i\ \neq\ j) $
- 入力は全て整数である。

### Sample Explanation 2

辺 $ 1 $ のみ通れないとき、頂点 $ 1 $ から頂点 $ N $ にたどり着けないので `-1` を出力します。

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
1
2
1```

## 样例 #2

### 输入

```
4 4
1 2
2 3
2 4
3 4```

### 输出

```
-1
2
3
2```

## 样例 #3

### 输入

```
5 10
1 2
1 4
1 5
2 1
2 3
3 1
3 2
3 5
4 2
4 3```

### 输出

```
1
1
3
1
1
1
1
1
1
1```

## 样例 #4

### 输入

```
4 1
1 2```

### 输出

```
-1```

# 题解

## 作者：SkyWave (赞：10)

# 题意

给定一张 $n$ 个点 $m$ 条边的简单有向图，对于 $1 \leq i \leq m$ 依次回答：若在图上删除第 $i$ 条边，从 $1$ 至 $n$ 的最短路长度。

# 分析

一个朴素的想法就是每次询问都跑一遍 bfs，时间复杂度 $O((n + m)m)$，又因为在稠密图下，$O(m) = O(n^2)$，复杂度与 $O(n ^ 4)$ 同阶。

bfs 求最短路复杂度已经无可挑剔，只能减少跑 bfs 的次数了。

我们想一想自己在学习 bellman-ford 和 dijsktra 时都会用到的一个性质——若原图联通，最短路经过的边数总是不多于 $n - 1$ 的。

简单证明一下：因为最坏情况就是一条单链，只能一步一步经过所有点才到 $n$ 其他情况必定优于单链，会有岔路口或环，反而消耗 $n$，此时直接每一步都向着目标走就行。

知道了这个性质，就又能启发我们一个事实：最终会改变最短路长度的边最多只有 $n - 1$ 条边，其他边删了根本不会影响 $1$ 到 $n$ 最短路的长度。所以我们可以直接先处理初始时 $1$ 到 $n$ 最短路上会经过哪些边与最短路长度，询问时如果删的边不在最短路路径内，那么最短路长度根本不会改变，直接输出全局最短路长度即可。如果在最短路路径内，就说明最短路长度可能会进行改变，此时再进行 bfs。由于 bfs 最多进行 $n$ 轮，所以最后复杂度为 $O((n + m)n + m)$。

# 代码
```cpp
//
//  main.cpp
//  [ABC218F] Blocked Roads
//
//  Created by SkyWave Sun on 2023/8/10.
//

#include <iostream>
#include <cstring>
#include <set>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
#define N 401
#define M N * N
vector<int> vec[N];
int pre[N];
int dis[N];
void bfs(int start, const pii &del/*删除的是哪条边*/) {
    memset(dis, -1, sizeof(dis));
    dis[start] = 0;
    int queue[N];
    int front = 1, rear = 0;
    queue[++rear] = start;
    while (front <= rear) {
        int tmp = queue[front++];
        for (auto i : vec[tmp]) {
            if (pii(tmp, i) == del) {
                continue;
            }
            if (dis[i] == -1) {
                pre[i] = tmp;//记录从哪里来的
                dis[i] = dis[tmp] + 1;
                queue[++rear] = i;
            }
        }
    }
}
pii edges[M];
int main(int argc, const char * argv[]) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[i] = pii(u, v);
        vec[u].push_back(v);
    }
    set<pii> st;
    bfs(1, pii(0, 0));
    int init = dis[n];
    int pos = n;
    while (pre[pos] != 0) {
        st.insert(pii(pre[pos], pos));//这条边在全局最短路中
        pos = pre[pos];//通过不断从 n 回溯到 1 还原出最短路路径
    }
    for (int i = 1; i <= m; ++i) {
        if (st.count(edges[i])) {//如果在最短路路径那么重新 bfs
            bfs(1, edges[i]);
            printf("%d\n", dis[n]);
        }else {
            printf("%d\n", init);//不在直接输出全局最短路长度
        }
    }
    return 0;
}

```

# 总结
当对优化无从下手时，就要思考一下有哪些可能的性质可以减少操作次数。或者直接从反面出发，正难则反。

---

## 作者：_Ponder_ (赞：4)

[Blocked Roads](https://www.luogu.com.cn/problem/AT_abc218_f)

### 题目大意

给定一张 $n$ 个点，$m$ 条边的无向图，每条边的边权均为 $1$。对于每一个 $i\in [1,m]$ 求出从点 $1$ 到 $n$ 的不经过第 $i$ 条边的最短路长度。

### 思路分析

我们先在原图上求出从点 $1$ 到点 $n$ 的最短路，注意到最短路的路径长度不会超过 $n-1$，这是因为每个点最多出现一次。

那么对于每一条边，如果它处于原图中从点 $1$ 到点 $n$ 的最短路径上，我们就把这条边删掉再跑一遍最短路得出答案，否则答案就是原本的最短路长度。

求一次最短路的时间复杂度是 $O(n+m)$ 的，所以总时间复杂度是 $O(n^2+nm)$，可以通过。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;
const int N=200100;
#define inf 0x3f3f3f3f

int n,m,in1,in2;
int dis[N],vis[N],pre[N];

vector<int> to[N];
set<pair<int,int>> s;
queue<int> q;
pair<int,int> edge[N];

int bfs(int notedge){//直接 bfs 求出最短路
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    while(!q.empty()) q.pop();
    q.push(1);dis[1]=0;
    while(!q.empty()){
        int now=q.front();q.pop();
        if(vis[now]) continue;
        vis[now]=1;
        for(int v:to[now]){
            if(edge[notedge]==make_pair(now,v)) continue;//直接跳过删除的边
            if(dis[v]>dis[now]+1){
                dis[v]=dis[now]+1;
                q.push(v);
                if(!notedge) pre[v]=now;
            }
        }
    }
    if(dis[n]==inf) return -1;
    return dis[n];
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&in1,&in2);
        to[in1].push_back(in2);
        edge[i]={in1,in2};
    }
    int len=bfs(0),x=n;
    while(x!=1){//从 n 开始倒推
        if(!pre[x]) break;
        s.insert({pre[x],x});
        x=pre[x];
    }
    for(int i=1;i<=m;i++)
        if(s.count({edge[i].first,edge[i].second})) cout<<bfs(i)<<'\n';
        else cout<<len<<'\n';
    return 0;
}
```

---

## 作者：2020luke (赞：3)

# [[ABC218F] Blocked Roads](https://www.luogu.com.cn/problem/AT_abc218_f) 题解

## Intro

这里提供一种神秘做法，目前题解区里还没有出现。

## Solution

先想暴力，枚举每条边，每次 bfs，总共 $O(nm+m^2)$ 显然不行，我们考虑将每次求答案的 $O(n+m)$ 复杂度优化成 $O(n)$。

我们在一开始的时候分别对原图的正反图以 $1$ 和 $n$ 为起点做 bfs，这样得到 $dis$ 和 $dis1$ 分别是正图上以 $1$ 为起点和反图上以 $n$ 为起点的单源最短路；同时，我们求一个 $flag_{i,k}$ 和 $flag1_{i,k}$ 表示从起点到 $i$ 的最短路是否经过第 $k$ 条边。得到这两个数组后我们枚举每条边 $k$，然后枚举每个点 $i$，若 $[(\lnot{flag_{i,k}})\And(\lnot{flag1_{i,k}})]$ 则用 $dis_i+dis1_i$ 更新答案，最后输出即可。

关于证明复杂度就简单讲一下。bfs 在松弛 $id$ 号边 $(u,v)$ 时 $flag_{v,k}\gets flag_{u,k}$，$flag_{v,id}\gets 1$，由于边权为 $1$ 和 bfs 的性质每一个点只会被更新一次，每次更新 $O(m)$，bfs 的复杂度就是 $O(nm)$。而正确性的证明我们可以尝试感性理解。你可能考虑到如下图的情景：

![](https://cdn.luogu.com.cn/upload/image_hosting/kvje1m8a.png)

我们在枚举边 $(3,6)$ 时枚举到点 $6$，因为我们的 $flag$ 取哪条边作为最短路是不确定的，所以若 $[flag_{6,E(3,6)}]=1$，那么点 $6$ 就不会对答案造成贡献，但是点 $5$ 是会造成贡献的，所以答案仍然正确。具体的理解我们可以想，如果一个点从起点开始有多条长度相同的最短路，并且我们枚举到的边正好就是我们 $flag$ 标记的这条最短路，那在我们没有选择的那几条最短路中必定有点也能造成贡献。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 410;
int n, m, d[N], d1[N];
bool flag[N][N * N], flag1[N][N * N];
pair<int, int> e[N * N];
struct node {
	int v, id;
};
vector<node> g[N], g1[N];
void bfs() {
	queue<int> q;
	q.push(1); memset(d, 0x3f, sizeof(d)); d[1] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto it : g[u]) {
			int v = it.v, id = it.id;
			if(d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				for(int i = 1; i <= m; i++) flag[v][i] = flag[u][i];
				flag[v][id] = true;
				q.push(v);
			}
		}
	}
}
void bfs1() {
	queue<int> q;
	q.push(n); memset(d1, 0x3f, sizeof(d1)); d1[n] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(auto it : g1[u]) {
			int v = it.v, id = it.id;
			if(d1[v] > d1[u] + 1) {
				d1[v] = d1[u] + 1;
				for(int i = 1; i <= m; i++) flag1[v][i] = flag1[u][i];
				flag1[v][id] = true;
				q.push(v);
			}
		}
	}
}
int main() {
	cin >> n >> m;
	for(int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		g[u].push_back({v, i}); g1[v].push_back({u, i}); 
		e[i] = {u, v};
	}
	bfs(); bfs1();
	for(int i = 1; i <= m; i++) {
		int ans = 2e9;
		for(int j = 1; j <= n; j++) {
			if(!flag[j][i] && !flag1[j][i]) ans = min(ans, d[j] + d1[j]);
		}
		if(ans < 1e9) cout << ans << '\n';
		else cout << "-1\n";
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

首先很多人时间复杂度估算错了，这里，我们设 $m=n^2$，这是最坏的情况，所以单次 BFS 的时间复杂度是 $O(n+m)$ 即 $O(n^2)$ 级别的。

每条边都跑一次就是 $O(n^4)$ 了，所以会时超。

我们的做法是把原图最短路的边记录下来，然后删了原图的边再跑最短路，否则直接输出原答案。

因为最短路不大于 $n$，因此时间复杂度是 $O(n^3)$ 级别的，可以通过。

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=405;
struct node
{
	LL to,num;
};
vector<node>v[N],v2[N];
LL n,m,x,y,pos,dis[N],nxt[N],c[N*N],ans,in[N];
pair<LL,LL>lst[N];
queue<LL>q;
LL work(LL pos)
{
	for(int i=0;i<=n;i++)
	{
		dis[i]=1e9;
	}
	dis[1]=0;
	while(!q.empty())q.pop();
	q.push(1);
	while(!q.empty())
	{
		LL t=q.front();
		q.pop();
		for(auto j:v[t])
		{
			if(j.num==pos)continue;
			if(dis[j.to]>dis[t]+1)
			{
				dis[j.to]=dis[t]+1;
				if(pos==0)lst[j.to]={t,j.num};
				q.push(j.to);
			}
			if(j.to==n)return dis[n];
		}
	}	
	if(dis[n]==dis[0])return -1;
}
void dg(LL x)
{
	while(x>1)//注意无解时lst=0，x会变成0,所以不可以把条件写成x!=1
	{
		in[lst[x].second]=1;
		x=lst[x].first;		
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		v[x].push_back({y,i});
	}
	ans=work(0);
	dg(n);
	if(dis[n]==dis[0])ans=-1;
	else ans=dis[n];
	for(int i=1;i<=m;i++)
	{
		if(!in[i])
		{
			printf("%d\n",ans);
			continue;
		}
		printf("%d\n",work(i));
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：1)

首先可以先求出 $ 1 $ 到 $ N $ 的最短路树。

如果一条边不在其最短路树上，则显然答案就是最短路。

否则暴力去掉这条边之后直接跑最短路即可。

分析这为什么是正确的：由于 $ 1 $ 总能到达 $ N $，则显然最短路上只有最多 $ N-1 $ 条边，所以最差情况下求 $ N $ 次最短路就可以解决问题。

这里用 Dijkstra 求最短路，时间复杂度 $ \mathcal{O}(nm\log{m}) $，实际上跑不满所以可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int n, m, ans, d[402];
bool v[402], go[160002];
vector<int> g[402], id[402];
queue<int> q;
inline void dijistra(const int ed) 
{
	memset(d, 0x3f, sizeof(d));
	memset(v, false, sizeof(v));
	q.push(1), d[1] = 0;
	while (q.size()) 
    {
		int x = q.front();
		q.pop();
		if (v[x])
			continue;
		v[x] = true;
		for (int i = 0, y; i < g[x].size(); ++i) 
        {
			if(id[x][i]==ed)
			continue;
			y=g[x][i];
			if (d[y] > d[x] + 1) 
            {
				go[id[x][i]] = 1;
				d[y] = d[x] + 1;
				q.push(y);
			}
		}
	}
}
signed main() 
{
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; ++i)
	scanf("%d%d", &x, &y), g[x].push_back(y), id[x].push_back(i);
	dijistra(0);
	int def = d[n];
	for (int i = 1; i <= m; ++i) 
    {
		if (!go[i])
			ans = def;
		else
			dijistra(i), ans = d[n];
		printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
	}
}
```


---

## 作者：ttq012 (赞：0)

这个题的数据范围非常的小，所以可以暴力枚举每一条删除的边，然后跑最短路，最短路不用这一条被更新掉了的边更新就可以了。

这个暴力算法的时间复杂度是 $O(n^3k)$ 的（SPFA），$O(n^3\log n)$ 的（Dijkstra），$O(n^3)$ 的（宽（广？）搜，BFS）。因为

但是这个题目卡常，所以考虑优化。

容易发现如果一条边不在最短路上那么删除这一条边对答案没有任何的影响。

如果一条边在最短路上那么有可能造成影响。

那么考虑记录一下任意一个最短路的路径，每一次删除边的时候判断一下在不在最短路上，如果在那么再更新答案。

由于最短路最多只有 $n-1$ 条边，所以时间复杂度是 $O(n^2)$（BFS）。

注意下一开始图不连通的情况（Test #17），特殊判断一下即可。

应管理要求添加代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 410;
int d[N];
int pre[N];
vector<int> z[N];
bool vis[N];
struct edg
{
    int u, v; 
} ed[N * N];
set<pair<int, int>> plist;
void spfa(int pu, int pv, bool fid)
{
    memset(d, 0x3f, sizeof d);
    memset(vis, false, sizeof vis);
    queue<int> q;
    q.push(1);
    vis[1] = true;
    d[1] = 0;
    while (q.size())
    {
        int f = q.front();
        q.pop();
        for (int &g : z[f])
            if (f != pu || g != pv)
            {
                if (!vis[g])
                {
                    d[g] = d[f] + 1;
                    if (fid)
                        plist.insert({f, g});
                    q.push(g);
                    vis[g] = true;
                }
            }
    }
}
signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> ed[i].u >> ed[i].v;
        z[ed[i].u].push_back(ed[i].v);
    }
    srand(time(0));
    spfa(1e9 + rand(), 1e9 + rand(), true);
    int cpy = d[n];
    if (cpy > 1e9)
        cpy = -1;
    for (int i = 1; i <= m; i++)
    {
        if (plist.count({ed[i].u, ed[i].v}))
        {
            spfa(ed[i].u, ed[i].v, false);
            if (d[n] > 1e9)
                cout << "-1\n";
            else
                cout << d[n] << '\n';
        }
        else
            cout << cpy << '\n';
    }
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

首先我们应当对给出的图求一个从点 $1$ 到点 $n$ 的最短路，做一个预处理。     
可使用常规的最短路算法，但这里推荐 BFS，好写还不会超时。       
（多说一嘴，BFS 在边权全为 $1$ 时是个很好的求最短路的工具，大力推荐。）       
同时记录这条最短路会经过哪些边。     
接着对于每条边，判断这条边是不是求出的最短路的一部分。如果是，那么再跑一次 BFS 求出删掉此边的最短路，否则把最短路长度输出即可。       

分析一下复杂度。预处理复杂度 $O(n^2)$，对于所有的边，最多只有 $n$ 条边会出现在预处理出的最短路中，所以重新 BFS 最多只会重新做 $n$ 次，每次 $O(n^2)$，所以总的复杂度为 $O(n^2+n^3)$，不会超时。
```cpp
#include<stdio.h>
#include<string.h>
int n,m,bian[405][405],a[160005],b[160005],data1[405],data2[405],data3[405],i,j,s,ss,len,get;bool f[405],ff[160005],shuchu;
int digui(int where)
{
    if(!where) return 0;
    ff[bian[data1[digui(data3[where])]][data1[where]]]=1;
    return where;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(s=1;s<=m;++s) scanf("%d%d",&a[s],&b[s]),bian[a[s]][b[s]]=s;
    i=get=data2[1]=0,memset(f,0,sizeof(f)),data1[j=1]=1; 
    while(i<j)
    {
        ++i;
        for(ss=1;ss<=n;++ss) if((bian[data1[i]][ss])&&(!f[ss]))
        {
            data2[j]=data2[i]+(f[data1[++j]=ss]=1),data3[j]=i;
            if(!(ss^n)) {len=data2[j],get=j;break;}
        }
        if(get) break;
    }
    ff[bian[data1[digui(get)]][data1[get]]]=1;
    for(s=1;s<=m;s++)
    {
        if(ff[bian[a[s]][b[s]]]==0) printf("%d\n",(len==0)?-1:len);
        else
        {
            i=shuchu=data2[1]=0,memset(f,0,sizeof(f)),data1[j=1]=1; 
            while(i<j)
    	    {
        	++i;
		for(ss=1;ss<=n;++ss) if((ss^data1[i])&&(bian[data1[i]][ss]^s)&&(bian[data1[i]][ss])&&(!f[ss]))
                {
            	    data2[j]=data2[i]+(f[data1[++j]=ss]=1);
            	    if(!(ss^n)) {printf("%d\n",data2[j]),shuchu=1;break;}
        	}
        	if(shuchu) break;
            }
    	    if(!shuchu) printf("-1\n");
        }
    }
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
这题就像是在考察暴力，当我们删除的那一条边不在原本的最短路的时候那么就可以直接输出原本的最短路。

否则我们可以直接暴力删除那一条边，然后然后跑一遍最短路输出 $dis(1,n)$，这里暴力删除的时候其实也不用真的在图里面删掉这一条边，只用把这一条边记录下来然后在找最短路的时候遇到了跳过就行了。

这个看上去是 $O(nm\log n)$ 的复杂度，但我们简单分析过后，可以发现需要跑最短路的边的个数最多 $n-1$ 个，所以最后的复杂度是 $O(n^2\log n)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=450*450;
vector<int>e[maxn];
set<pair<int,int>>st;
pair<int,int>a[maxn];
int vis[maxn],dis[maxn],pre[maxn],n,m;
int bfs(int x){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	queue<int>Q;
	Q.push(1);dis[1]=0;
	while(Q.size()){
		int u=Q.front();
		Q.pop();
		if(u==n)return dis[n];
		if(vis[u]==0){
			vis[u]=1;
			for(int v:e[u]){
				if(a[x]!=make_pair(u,v)){
					if(dis[v]>dis[u]+1){
						if(x==0)pre[v]=u;
						dis[v]=dis[u]+1;
						Q.push(v);
					}
				}
			}
		}
	}
	return -1;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		a[i]={u,v};
	}
	int x=bfs(0),now=n;
	while(now!=1){
		if(!pre[now])break;
		st.insert({pre[now],now});
		now=pre[now];
	}
	for(int i=1;i<=m;i++){
		if(st.count({a[i].first,a[i].second}))cout<<bfs(i)<<"\n";
		else cout<<x<<"\n";
	}
	return 0;
}
```

---

