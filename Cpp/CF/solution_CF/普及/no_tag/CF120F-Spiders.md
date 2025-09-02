# Spiders

## 题目描述

Petya 有 $n$ 只玩具蜘蛛，每只玩具蜘蛛可以看作一棵无根树。节点大小忽略不计，边的长度为 1。

Petya 可以在两只蜘蛛中各选一个节点粘在一起，从而形成一只新蜘蛛。新的蜘蛛也是一棵树。

他希望把所有蜘蛛用上面的方式粘在一起，并让新形成的蜘蛛中最远的两个节点距离最大（即树的直径最大）。

如图，在样例 2 中，Petya 将第一只蜘蛛的 2 号点与第二只蜘蛛的 1 号点粘在一起，新得到的蜘蛛的直径被加粗标出。

## 样例 #1

### 输入

```
1
3 1 2 2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
3 1 2 1 3
4 1 2 2 3 2 4
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2
5 1 2 2 3 3 4 3 5
7 3 4 1 2 2 4 4 6 2 7 6 5
```

### 输出

```
7
```

# 题解

## 作者：Priori_Incantatem (赞：4)

### 题目大意

给出 $n$ 棵树，你每次可以选择两个树，并将这两棵树的两个节点粘起来，形成一棵新的树。经过 $n-1$ 次操作后，这 $n$ 棵树就融合为了一棵树  
问最后这棵树的最大直径（最长链）长度

### 解题思路

以前看到有些题是要求直径最短，看到这题之后松了口气

因为最后要求的是**最长链**，所以，每一棵树都要把自己的最长链（直径）贡献给最终答案  
那么我们就把 $n$ 棵树的直径粘成一段不就好了吗

换句话说：设第 $i$ 棵树的直径端点为 $u_i,v_i$，$[x,y]$ 表示一个将点 $x$ 和点 $y$ 粘起来的操作。  
那么就：$[v_1,u_2],[v_2,u_3] \dots [v_{n-1},u_n]$  
最后的答案就是 $n$ 棵树的直径之和了

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;
const int Maxn=1010,inf=0x3f3f3f3f;
int dis[Maxn],f[Maxn];
int n,ans;
vector <int> e[Maxn];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void dfs(int x,int fa)
{
	int m1=0,m2=0;
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(y==fa)continue;
		dfs(y,x);
		f[x]=max(f[x],f[y]+1);
		int tmp=f[y]+1;
		if(tmp>m1)m2=m1,m1=tmp;
		else if(tmp>m2)m2=tmp;
	}
	dis[x]=max(m1+m2,max(m1,m2));
}
int main()
{
	freopen("input.txt","r",stdin); // 注意这题提交的时候要带文件输入输出
	freopen("output.txt","w",stdout);
	int T=read();
	
	while(T--)
	{
		n=read();
		int tot=0;
		for(int i=1;i<n;++i)
		{
			int x=read(),y=read();
			e[x].push_back(y);
			e[y].push_back(x);
		}
		dfs(1,0);
		for(int i=1;i<=n;++i)
		tot=max(tot,dis[i]);
		ans+=tot;
		
		for(int i=1;i<=n;++i)
		{
			e[i].clear();
			dis[i]=f[i]=0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：copper_ingot (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF120F)

题目大意：给出了 $n$ 棵树，要求把所有的树拼接起来，求最后树的最大直径。

因为要求**最大**直径，所以我们要把每棵树的直径拼接在一起，这样总直径就是所有树的直径和，是最大的。

求一棵树的直径，可以先随便找一个点 $x$，然后找离 $x$ 最远的点 $y$，再找离 $y$ 最远的点 $z$，那么 $[y,z]$ 就是这棵树的直径，可以通过两次 DFS 或 BFS 实现，具体证明见[这里](https://oi-wiki.org/graph/tree-diameter/#%E5%81%9A%E6%B3%95-1-%E4%B8%A4%E6%AC%A1-dfs)。

最后，记得要文件读写，~~我就是因此而 WA 了一发才发现的~~。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, g[101][101], dis[101], ans;
void bfs(int st){//简单的BFS
	memset(dis, 0x3f, sizeof(dis));
	queue<int> q;
	q.push(st); dis[st] = 0;
	while (!q.empty()){
		int u = q.front(); q.pop();
		for (int v = 1; v <= m; v++){
			if (!g[u][v] || dis[v] != 0x3f3f3f3f) continue;
			dis[v] = dis[u] + 1; q.push(v);
		}
	}
}
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &m);
		memset(g, 0, sizeof(g));
		for (int i = 1; i < m; i++){
			int u, v; scanf("%d%d", &u, &v);
			g[u][v] = g[v][u] = 1;
		}//存图
		bfs(1); int maxn = 0, id = 0;
		for (int i = 1; i <= m; i++)
			if (dis[i] > maxn) maxn = dis[i], id = i;
		bfs(id); maxn = 0;
		for (int i = 1; i <= m; i++) maxn = max(maxn, dis[i]);
		ans += maxn;//累加答案
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Mine_King (赞：2)

这题要求最长的直径，那么我们直接把每棵树的直径的两端连起来，结果为所有树的直径之和，不就最长了吗？  
那么为什么可以这么干嘞？明显合并后的直径应该是贯穿两棵树的，否则这棵树连了和没连一样。那么要贯穿两棵树，只能通过连起来的那个点。此时把两条直径连起来自然是最优的。  
**注意了，本题是要写文件输入输出的。**

code：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int T,n,s,len,ans;
int dis[105];
struct graph
{
	int tot;
	int hd[105];
	int nxt[205],to[205];
	void add(int u,int v)
	{
		tot++;
		nxt[tot]=hd[u];
		hd[u]=tot;
		to[tot]=v;
		return ;
	}
	void clear()
	{
		tot=0;
		memset(hd,0,sizeof(hd));
		return ;
	}
}g;
void dfs(int now,int ll)
{
	dis[now]=ll;
	for(int i=g.hd[now];i;i=g.nxt[i])
		if(dis[g.to[i]]==0) dfs(g.to[i],ll+1);
	return ;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		g.clear();
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			g.add(u,v);
			g.add(v,u);
		}
		s=0,len=0;
		memset(dis,0,sizeof(dis));
		dfs(1,1);
		for(int i=1;i<=n;i++)
			if(dis[i]>dis[s]) s=i;
		memset(dis,0,sizeof(dis));
		dfs(s,1);
		for(int i=1;i<=n;i++)
			if(dis[i]>len) len=dis[i];
		ans+=len-1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：1)

## CF120F Spiders 题解
### Solution
一眼树的直径，通过两次 dfs 求解。

第一次搜索从任意节点出发，寻找离它最远的点，这是因为树的最长路径一定包含这个节点。第二次搜索从该节点出发，寻找距离它最远的结点。

因为全局的最长路径一定是由多端局部最长路径拼接而成；而若路径最长，距离任意一个节点最远的点必是这条路径上的一个点。

**最后：写文件读写！！！**

###### ~~（也不知道搞什么名堂）~~

### [Accepted Code](https://codeforces.com/contest/120/submission/304543450)
```cpp
#include<iostream>
#include<vector>
#define pb push_back
#define ll long long
using namespace std;
const int N=1e2+10;
vector<int>G[N][N];
int n,k,u,v,ans,st,mxt=-1;
void dfs(int id,int x,int fa,int d){
	if(G[id][x].size()==1&&G[id][x][0]==fa){
		if(d>mxt){
			mxt=d;
			st=x;
		}
		return;
	}
	for(auto i:G[id][x]){
		if(i==fa) continue;
		dfs(id,i,x,d+1);
	}
}
int calc(int x){
	mxt=-1;
	dfs(x,1,0,0);
	mxt=-1;
	dfs(x,st,0,0);
	return mxt;
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&k);
		for(int j=1;j<k;j++){
			scanf("%d%d",&u,&v);
			G[i][u].push_back(v);
			G[i][v].push_back(u);
		}
	}
	for(int i=1;i<=n;i++) ans+=calc(i);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Tomwsc (赞：1)

# CF120F Spiders 题解

## 题意

给定 $n$ 棵树，要求把 $n$ 棵树拼在一起，使拼完后的树的直径最长，

## 思路

考虑贪心。

可知一棵树内最长的路径便是其直径。可以证明若要拼接后的树的直径最长，那一定是各个树的直径两端节点相连。什么意思？

设这 $n$ 棵树的直径分别是 $(u_1,v_1)$，$(u_2,v_2)$，$\cdots$，$(u_n,v_n)$。那么我们便将 $v_{i-1}$ 与 $u_i$ 拼接。拼接后的树的最长的直径便是 $u_1\rightarrow v_1(u_2)\rightarrow v_2(u_3)\rightarrow\cdots\rightarrow v_n$。

所以贪心思想便是每次都选择对树的直径两端的节点进行拼接。

求树的直径，我们可以用二次 dfs。第一次找到距离任意一个节点距离最长的点。第二次找距离上次 dfs 中找到的点的最长的点。然后这两个点之间的距离便是树的直径。

## 代码实现

注意：要用文件输入输出！

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1ll << 62
using namespace std;
const int MAXN = 105;
int n , cnt , k , ans;
int dis[MAXN];
vector<int>G[MAXN];

void dfs(int u , int fa) {
	for(auto v : G[u]) {
		if(v == fa)
			continue;
		dis[v] = dis[u] + 1;
		dfs(v , u);
	}
	if(dis[u] > ans) {
		ans = dis[u];
		k = u;
	}
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt" , "r" , stdin);
	freopen("output.txt" , "w" , stdout);
	cin >> n;
	for(register int i = 1;i <= n;i ++) {
		int x;
		ans = 0;
		cin >> x;
		for(register int i = 1;i <= x;i ++)
			G[i].clear();
		for(register int i = 1;i < x;i ++) {
			int a , b;
			cin >> a >> b;
			G[a].push_back(b);
			G[b].push_back(a);
		}
		dis[1] = 0;
		dfs(1 , 0);
		ans = 0;
		dis[k] = 0;
		dfs(k , 0);
		cnt += ans;
	}
	cout << cnt;
	return 0;
}
```

---

## 作者：syf159 (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF120F)  
[codeforces 题目传送门](https://codeforces.com/problemset/problem/120/F)

## 题意

有 $ n $ 只蜘蛛，每只蜘蛛可以看作一棵树，第 $ i $ 棵树有 $ n_i $ 个节点，有 $ n - 1 $ 条边，每条边连接节点两个点。

现在要把 $ n $ 棵树连接在一起，得到一颗新的树，使得新树的直径最大。

## 分析

既然使直径最大，那当然是直径拼在一起就好啦！

所以，我们只需要把每一棵树的直径加在一起就得到答案了。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int m;
vector<int> son[40005];
int f[40005],dp[40005];
void dfs(int a,int fat)
{
	int maxx1=0,maxx2=0;
    for(int i=0; i<son[a].size(); i++)
    {
        int t=son[a][i];
        if(t==fat) continue;
		dfs(t,a);
        f[a]=max(f[a],f[t]+1);
        if((f[t]+1)>maxx1) maxx2=maxx1,maxx1=(f[t]+1);
        else if((f[t]+1)>maxx2) maxx2=(f[t]+1);
    }
    dp[a]=max(maxx1+maxx2,max(maxx1,maxx2));
}
long long ans;
int main(){
	freopen("input.txt","r",stdin);//本题要求开freopen 
	freopen("output.txt","w",stdout);
	cin>>t;
	while(t--)
	{
		cin>>n;
        for(int i=1; i<n; i++)
        {
            int f,g;
            cin>>f>>g;
            son[g].push_back(f);
            son[f].push_back(g);
        }
        dfs(1,0);//求直径 
        int ma=0;
        for(int i=1; i<=n; i++)
        {
        	ma=max(ma,dp[i]);
        }
        ans+=ma;
        for(int i=1; i<=n; i++)
        {
            son[i].clear();
            dp[i]=f[i]=0;
        }//多测不清空，爆零两行泪
	}
	cout<<ans;	
    
    return 0;
}
```

---

## 作者：CSPAK_Zhangxiuqi0011 (赞：1)

# CF120F Spiders 题解  
## 0. 前言
本蒟蒻个人认为本题不难，但是我旁边的[某位大佬](https://www.luogu.com.cn/user/910530)挂了硬是调不出来，所以我决定写一篇题解帮帮 Ta。  
还有，因为最近 CF 加强了一下那个什么东西，导致洛谷爬虫爬不到提交记录，所以洛谷提交不了，只能在 [vjudge](https://vjudge.net) 提交  [提交记录](https://vjudge.net/status#un=CSPAKZXQ&OJId=CodeForces&probNum=120F&res=0&language=&onlyFollowee=false)  
## 1. 题意
给定 $n$ 个树，每棵树的每条边的边权都是 $1$。现在要加上 $n-1$ 条边权为 $0$ 的边，使得整个整体成为了一棵新树。问这个新树的直径最大是多少？  
## 2. 前置芝士
先说一句，知道什么是直径的神犇就可以跳过了......  
一棵树的直径其实就是对于这棵树上所有的点对 $(u,v)$ 中最大的 $dis(u,v)$，也就是 $\max(dis(u,v))$。  
具体看图例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/8syzu1is.png)   
如图，选择 $4$ 号点和 $5$ 号点，此时距离最大，即树的直径为 $27$。
## 3. 思路
首先我们来看两棵树的情况，为了~~作者少画点图~~方便理解，我们直接用上面的这棵树，而且边权为 $1$ 的结论对于边权为自然数的情况也适用：  
![](https://cdn.luogu.com.cn/upload/image_hosting/y96gli64.png)  
那么可以发现加了一条边以后两棵树形成了一棵新树，这棵树的直径为 $54$。可以证明虽然还有其他连边方法，但是所得直径都不可能超过 $54$。  
再举几个例子就可以发现，要想满足新树直径最大，就一定会满足这条边所连接的两个点只可能在两棵树的直径路径的起点、终点一共 $4$ 个点之间，且不可能在同一棵树上。所以，新树的最大直径就是之前两棵树的直径之和。  
~~根据直觉~~再经过推导可以发现这个规律在多棵树中同样适用。所以，**我们只要求出每棵树的直径，最后相加即可**。
## 4. 核心代码讲解
知道直径怎么求的大佬可以跳过了......  
首先，我们定义 $dp _ i$ 的意思为从某个叶子结点出发不经过深度小于 $i$ 号节点的节点所走路径的最大长度。如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/e9o3hhxk.png)  
蓝色节点是目前正在进行转移的节点，红色节点是不可以经过的节点，如图，则可以得出只有黄色节点可以走到 $i$ 号节点，$dp _ i = 8$。  
再仔细观察，可以发现一棵树的直径要不然是在某个节点的两棵不同的子树上。要不然就是在一棵子树的一条链上。故我们可以得出以下代码：
```cpp
void dfs(int id,int now,int fa){//id:目前是第几棵树 now:现在在几号节点 fa:此节点的父节点
	int l,m1,m2;//m1:满足上面条件（不能经过比此节点深度小的点）的最长路径长度  m2:次长路径长度（注意这里m1和m2可以相等）
	l = a[id].ve[now].size();
	m1 = 0;//初值赋0，可以规避一条链的情况（因为这时候只有m1有值，m1+m2 = m1+0 = m1）
	m2 = 0;
	for(int i = 0;i<l;i++){
		if(a[id].ve[now][i] == fa){
			continue;
		}
		dfs(id,a[id].ve[now][i],now);
		a[id].dp[now] = max(a[id].dp[now],a[id].dp[a[id].ve[now][i]]+1);
		if(a[id].dp[a[id].ve[now][i]]+1>m1){
			m2 = m1;
			m1 = a[id].dp[a[id].ve[now][i]]+1;//+1加的是从now到ve[now][i]的距离
		}else if(a[id].dp[a[id].ve[now][i]]+1>m2){
			m2 = a[id].dp[a[id].ve[now][i]]+1;
		} 
	}
	a[id].maxn = max(a[id].maxn,m1+m2);
}
```
## 5.AC CODE
**一定不要忘记加 freopen!**  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
struct node{
	int n,maxn,dp[105];
	vector<int>ve[105];
}a[105];
void dfs(int id,int now,int fa){//id:目前是第几棵树 now:现在在几号节点 fa:此节点的父节点
	int l,m1,m2;//m1:满足上面条件（不能经过比此节点深度小的点）的最长路径长度  m2:次长路径长度（注意这里m1和m2可以相等）
	l = a[id].ve[now].size();
	m1 = 0;//初值赋0，可以规避一条链的情况（因为这时候只有m1有值，m1+m2 = m1+0 = m1）
	m2 = 0;
	for(int i = 0;i<l;i++){
		if(a[id].ve[now][i] == fa){
			continue;
		}
		dfs(id,a[id].ve[now][i],now);
		a[id].dp[now] = max(a[id].dp[now],a[id].dp[a[id].ve[now][i]]+1);
		if(a[id].dp[a[id].ve[now][i]]+1>m1){
			m2 = m1;
			m1 = a[id].dp[a[id].ve[now][i]]+1;//+1加的是从now到ve[now][i]的距离
		}else if(a[id].dp[a[id].ve[now][i]]+1>m2){
			m2 = a[id].dp[a[id].ve[now][i]]+1;
		} 
	}
	a[id].maxn = max(a[id].maxn,m1+m2);
}
signed main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin>>a[i].n;
		for(int j = 1;j<a[i].n;j++){
			int u,v;
			cin>>u>>v;
			a[i].ve[u].push_back(v);
			a[i].ve[v].push_back(u);
		}
	}
	int ans;
	ans = 0;
	for(int i = 1;i<=n;i++){
		dfs(i,1,0);
		ans = ans+a[i].maxn;
	}
	cout<<ans<<"\n"; 
	fclose(stdin);
	fclose(stdout);
	return 0;
}

```
那么这篇题解就到这里啦，如果本蒟蒻有什么说的不对的地方请大佬指出，完结撒花！

---

## 作者：MuYC (赞：1)

#### 题外话:
这道题目的翻译有点小问题，翻译没有说要开文件，但是题目是要求开文件的!我因为这个错了一次，看到错误信息才会看题目发现要开文件:
```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```
这是应该开的文件

### 解题思路:
这道题的大意就是给我们$n$棵树，让我们任意合并这$n$棵树，问能得到的最大直径。很显然的贪心，就是我们每次都把直径拼接在一起，然后最后的答案其实就是$n$棵树的直径长度和，我们也根本不用模拟拼接的过程。

#### 对于无根树找直径的方法:
有两种，一种是(两次ＢＦＳor两次ＤＦＳ)，一种是树形ＤＰ，这里介绍两次ＤＦＳ版的

首先任意取一个节点(我是随机rand()了一个节点)，进行一次ＤＦＳ，找出离它最远的点假设为$p$,然后再以$p$为起点进行一次ＤＦＳ，找出离$p$最远的点$q$，这时候,$p$到$q$的路径形成的就是树的直径.

#### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,p,v,m = 0;
struct Edge{
	int next,to;
}edge[10005];
int head[1000];
int deep[1005];
void add_edge(int from,int to)
{
	m ++;
	edge[m].to = to;
	edge[m].next = head[from];
	head[from] = m;
}

void DFS(int x,int from)
{
	deep[x] = deep[from] + 1;
	for(int i = head[x] ; i ; i = edge[i].next)
	{
		int to = edge[i].to;
		if(!deep[to])DFS(to,x);
	}
	return ;
}
int main()
{	
	freopen("input.txt","r",stdin);	
	freopen("output.txt","w",stdout);
	cin >> T;
	int ans = 0;
	
	while(T)
	{
		cin >> n;
		m = 0;
		memset(head,0,sizeof(head));
		memset(deep,0,sizeof(deep));
		for(int i = 1 ; i <= n-1; i ++)
		{
			int u,v;
			cin >> u >> v;
			add_edge(u,v);
			add_edge(v,u);
		}
		srand(time(NULL));
		int s = rand() % n + 1;
		DFS( s , 0 );
		for(int i = 1 ; i <= n ; i ++)
			if(deep[i] > deep[s]) s = i;//第一次DFS
		memset(deep,0,sizeof(deep));
		DFS( s , 0 );
		for(int i = 1 ; i <= n ; i ++)
			if(deep[i] > deep[s]) s = i;
		ans += deep[s] - 1;
        	//第二次DFS,因为起点深度默认为1,所以统计答案要-1
		T--;
	}
	
	cout << ans;
	return 0;
}
```


---

## 作者：Genshin_ht (赞：0)

# 题解：CF120F Spiders

## 题意

每次你都可以选定任意两棵树对其进行合并，并将这两棵树的两个节点合并，形成一棵新的树。不难推出，进行 $n$ 次操作后变成了一颗完整的树。

求这棵树的两个节点距离的最大值（直径）。

## 思路

我们可以用搜索求出每一棵树的直径（参考前置题目：[树的直径](https://www.luogu.com.cn/problem/B4016)），每次拼接时就把选定的两棵树的直径的端点拼在一起，所以答案是 $n$ 棵树的直径之和。

## 注意事项

多测要清空！

本题需要使用文件输入输出。

## 核心代码

用 `dfs` 求直径部分。

```cpp
void dfs(int x, int y, int sum)
{
    if (sum > tmp)
    {
        tmp = sum;
        pos = y;
    }
    visited[x][y] = 1;
    for (int i = 0; i < d[x][y].size(); i++)
    {
        if (!visited[x][d[x][y][i]])
            dfs(x, d[x][y][i], sum + 1);
    }
}
int get_ans(int x)
{
    tmp = 0;
    pos = 0;
    memset(visited, 0, sizeof visited);
    dfs(x, 1, 0);
    tmp = 0;
    memset(visited, 0, sizeof visited);
    dfs(x, pos, 0);
    return tmp;
}
```

---

## 作者：getchar_unlocked (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF120F)

### 思路

本题考查[树的直径](https://www.luogu.com.cn/problem/B4016)。

想求两个节点距离的最大值，则对于每一棵小的树，都要使其直径最大。然后将所有直径粘在一起，即统计出所有树的直径的和即可。

具体如何求单棵树的直径：先以任意起点做一次 dfs，找到离该点距离最大的点 $u$。再以点 $u$ 为起点做 dfs，找到离 $u$ 点距离最大的点 $v$，得到 $u$ 与 $v$ 的距离即为树的直径。

**注意事项**

- 循环的每一次都要清空。
- 注意本题需要文件读写。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=105;
vector<int>vc[N];
int maxx,ans;
void dfs(int x,int fa,int deep){
	if(deep>maxx){
		maxx=deep;
		ans=x;
	}
	for(auto i:vc[x])
		if(i!=fa)
			dfs(i,x,deep+1);
	return;
}
signed main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=read(),sum=0;
	while(n--){
		int x=read();
		for(int i=1;i<=x;++i)
			vc[i].clear();
		for(int i=1;i<x;++i){
			int u=read(),v=read();
			vc[u].push_back(v);
			vc[v].push_back(u);
		}
		maxx=-1,ans=1;
		dfs(1,0,0);
		maxx=-1;
		dfs(ans,0,0);
		sum+=maxx;
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：2022linzhiyi (赞：0)

# 题意
给定 $n$ 棵树，每次可以选择两棵树将他们的一个节点合并，形成一棵新的树，问最后的一棵树的直径最长是多少？
# 解法
我们可以用搜索等做法求出每一棵树的直径，每次拼接时就把选定的两棵树的直径的端点拼接在一起，所以答案是 $n$ 棵树的直径之和。

**注意：**这一题要用文件输入输出。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> d[110][110];
int a[110],ans,tmp,pos;
bool vis[110][110];
void dfs(int x,int y,int sum) {
	if (sum > tmp) {
		tmp=sum;
		pos=y;
	}
	vis[x][y]=1;
	for (int i=0;i<d[x][y].size();i++) {
		if (!vis[x][d[x][y][i]]) dfs(x,d[x][y][i],sum+1);
	}
}
int solve(int x) {
	tmp=0; pos=0; memset(vis,0,sizeof vis);
	dfs(x,1,0);
	tmp=0; memset(vis,0,sizeof vis);
	dfs(x,pos,0);
	return tmp;
}
int main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin >> n;
	for (int i=1;i<=n;i++) {
		cin >> a[i];
		for (int j=1;j<a[i];j++) {
			int x,y;
			cin >> x >> y;
			d[i][x].push_back(y);
			d[i][y].push_back(x);
		}
	}
	for (int i=1;i<=n;i++) ans += solve(i);
	cout << ans;
	return 0;
}

---

## 作者：FrozenDream (赞：0)

### 注意：
本题要用文件读写，翻译没有写出来。
```cpp
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```
知道这一点之后我们就可以开始了。
### 思路：
本题思路非常好想，遍历求出每一棵树的最长直径（坑点二：也就是从 **任意** 一点开始，可以走过的不重复的最长路径），最后把每一棵树的直径相加，就是可以组成的树的最长直径了，毕竟树之间在组合的时候没有任何限制。

在存储树的时候，用边表来存，可以大大节省空间（废话），不会的同学可以参考这篇 [blog](https://www.cnblogs.com/grhyxzc/p/5079704.html)。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,head[205],to[205],nxt[205],a[105],tot,u,v,ans,f[205];
void add(int u,int v){
	tot++;
	nxt[tot]=head[u];
	head[u]=tot;
	to[tot]=v;
}
void dfs(int k,int sum,int jd){
	a[k]=max(a[k],sum);
	for(int i=head[jd];i;i=nxt[i]){
		if(f[to[i]]!=1){
			f[to[i]]=1;
			dfs(k,sum+1,to[i]);
			f[to[i]]=0;
		}
	}
}
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>t;
	for(int i=1;i<=t;i++){
		tot=0;
		memset(head,0,sizeof(head));
		memset(nxt,0,sizeof(nxt));
		memset(to,0,sizeof(to));
		cin>>n;
		for(int j=1;j<n;j++){
			cin>>u>>v;
			add(u,v);
			add(v,u);
		}
		for(int k=1;k<=n;k++){
			memset(f,0,sizeof(f));
			f[k]=1;
			dfs(i,0,k);
		}
	}
	for(int i=1;i<=t;i++){
		ans+=a[i];
	}
	cout<<ans;
}
```


---

