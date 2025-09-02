# [COCI 2021/2022 #3] Cijanobakterije

## 题目描述

一位微生物学家有 $n$ 个蓝藻细菌。这些细菌中有 $m$ 组细菌 $(a_i,b_i)$，表示 $a_i$ 和 $b_i$ 之间有一条生物链。若干条生物链顺次连接之后可组成长链。长链的长度定义为这条长链上的细菌数量。

现可在细菌之间两两添加若干条生物链，使得添加之后的所有生物链均不存在环。

求在进行若干次添加生物链的操作后，最长的长链的长度是多少。

## 说明/提示

**【样例 2 解释】**

在 $2$ 和 $6$ 之间添加一条生物链后，最长的长链为 $3-1-2-6-5-7$，长度为 $6$。

**【数据规模与约定】**

**本题采用子任务捆绑测试。**

- Subtask 1（15 pts）：$m=n-1$。
- Subtask 2（6 pts）：$b_i=a_i+1$。
- Subtask 3（6 pts）：$1 \le a_i \le 2$。
- Subtask 4（15 pts）：$1 \le n \le 1000$。
- Subtask 5（28 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$0 \le m \lt n$，$1 \le a_i,b_i \le n$。

**【提示与说明】**

**题目译自 [COCI 2021-2022](https://hsin.hr/coci/) [CONTEST #3](https://hsin.hr/coci/contest3_tasks.pdf) _Task 2 Cijanobakterije_。**

**本题分值按 COCI 原题设置，满分 $70$。**

## 样例 #1

### 输入

```
100 0```

### 输出

```
100```

## 样例 #2

### 输入

```
8 6
1 2
1 3
1 4
5 6
5 7
5 8```

### 输出

```
6```

## 样例 #3

### 输入

```
6 5
1 2
2 3
3 4
4 6
4 5```

### 输出

```
5```

# 题解

## 作者：Naro_Ahgnay (赞：7)

## 题目大意

现有一个森林图，随意添加边使它成为一棵树。求这棵树的直径。

## 思路

树的直径：树上最远两点间的距离。

我们可以把森林中每一棵树的直径两端连接起来。因为一棵树的直径原本就是这棵树中最长的链，所以在新树中也不可能存在比这条新的、用原来的树的直径组成的链更长的新链。那么很明显，答案就是该森林中所有树的直径的和。

那么怎么求出这个距离呢？求树的直径有很多方法，可以使用两遍 dfs 求直径的方法。

### step 1

在树上随便选一个点作为起点，然后向它能到达的走去。记录下走过的点数。

### step 2

找出从起点开始，步数最多的点，记录下来，作为下一次 dfs 的起点。

### step 3

从刚才新的起点开始，继续搜索它能到达的点。最后距离新起点最远的点和新起点的距离就是这棵树的直径。

求出每棵树的直径，然后加起来就成了最终的答案。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v,ans,res,id;
int in[100001];
bool vis[100001];
vector<int> g[100001];
void dfs(int x,int z)
{
	vis[x]=1;
	if(res<z) res=z,id=x;
	int si=g[x].size();
	for(int i=0;i<si;i++)
		if(!vis[g[x][i]]) dfs(g[x][i],z+1);
	return;
}
void sfd(int x,int f,int z)
{
	res=max(res,z);
	int si=g[x].size();
	for(int i=0;i<si;i++)
		if(g[x][i]!=f) sfd(g[x][i],x,z+1);
	return;
}
void wok(int x)
{
	res=0;dfs(x,1);
	res=0;sfd(id,id,1);
	ans+=res;
}
int main()
{
//	freopen("P8028.in","r",stdin);
//	freopen("P8028.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		g[u].push_back(v);
		g[v].push_back(u);
		in[u]++,in[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(in[i]==1&&!vis[i]) wok(i);
		if(!in[i]) ans++;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：BirdCO3_UwU (赞：1)

题意：给你若干个树，你需要在这些树之间任意加边使之形成一个大树。问大树的直径最大是多少。

题解：不难想到将每棵树的直径依次连接起来，得到的树的直径肯定最大。问题就转换为了如何求一个树的直径。

这是一个经典问题，做两遍 dfs 就行 

具体来说，第一遍任取一个点作为根，进行一遍 dfs，找出与他距离最远的点。这个点一定是这个树某条直径的一个端点。

第二遍以这个点作为根，进行第二遍 dfs，找出与他距离最远的点。这两个点之间的路径就是这个树的其中一条直径了。

时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
const ll N=1e5+10;
inline ll read(){
	ll a=0,x=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	x=-x;
		c=getchar();
	}
	while(isdigit(c)){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*x;
}
ll n,m;
ll to[N<<1],hd[N],nt[N<<1],tt;
ll vis[N],dep[N];
ll ans,rt,maxd;
void push(ll u,ll v){
	to[++tt]=v;
	nt[tt]=hd[u];
	hd[u]=tt;
}
void dfs1(ll nw,ll en){
	dep[nw]=dep[en]+1;
	vis[nw]=true;
	if(dep[nw]>dep[rt])	rt=nw;
	for(int i=hd[nw];i;i=nt[i]){
		if(to[i]==en)	continue;
		dfs1(to[i],nw);
	}
}
void dfs2(ll nw,ll en){
	dep[nw]=dep[en]+1;
	if(dep[nw]>maxd)	maxd=dep[nw];
	for(int i=hd[nw];i;i=nt[i]){
		if(to[i]==en)	continue;
		dfs2(to[i],nw);
	}
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		ll u=read(),v=read();
		push(u,v),push(v,u);
	}
	for(int i=1;i<=n;i++){
		if(vis[i])	continue;
		rt=0,maxd=0;
		dfs1(i,0);
		dfs2(rt,0);
		ans+=maxd;
	}
	printf("%lld\n",ans);
	return 0;
}
```

为什么突然写这篇题解呢，熟悉我的人知道我是基本不写 luogu 题解的。所以说是为什么呢？是为什么呢？

2023.11.13


---

## 作者：P7GAB (赞：1)

### 简要题意

给定一个森林，可以在树与树之间连边，不可成环，求最长链。

### 解析

对于一棵树而言，她本身的最长链自然就是她的直径。

贪心的想，把所有的树的直径全部连接起来就是最长的那一条链。

所以，对于每一棵树求出她的直径然后求和就好了。

**特别注意，这题的长度是指节点的个数，因此比边数大 $1$**。

### 代码实现

树的直径有两种求法：两遍搜索和树形 DP。

前者可以保存遍历路径但无法处理负边权，后者则正好反之。

#### 搜索

先选树上任意一点 $u$，然后找到距离 $u$ 最远的点 $v$，之后再以 $v$ 为起点，找到离她最远的点 $w$。最后 $v$ 与 $w$ 之间的距离即为该树的直径。

理论上 DFS 与 BFS 均可，但写 DFS 的似乎更多。

#### DP

别的题解讲的还挺明白的，而且本题也没有负边权~~我不会~~，这里就不放了。

此外，树的直径还有不少性质，这里贴个[链接](https://www.cnblogs.com/crab-in-the-northeast/p/diameter-and-center-on-tree.html)，如需自取。

终于来到了喜闻乐见的代码环节。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+12;
int n,m;
int head[maxn],cnt=0;
struct node {
	int nxt,to;
} edge[maxn];
bool vis[maxn],vis2[maxn];
int ans=0,o=0,dis=0;
void add(int u,int v) {
	cnt++;
	edge[cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs1(int u,int d) {
	vis[u]=1;
	if(d+1>dis) {
		dis=d+1;
		o=u;
	}
	for(int i=head[u]; i; i=edge[i].nxt) {
		int v=edge[i].to;
		if(!vis[v])
			dfs1(v,d+1);
	}
}
void dfs2(int u,int d) {//可以跟dfs1和到一起的，不过容易出锅，模拟赛100->30。
	vis2[u]=1;
	dis=max(dis,d+1);
	for(int i=head[u]; i; i=edge[i].nxt) {
		int v=edge[i].to;
		if(!vis2[v]) {
			dfs2(v,d+1);
		}
	}
}
int main() {
	cin>>n>>m;
	for(int i=1; i<=m; i++) {
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1; i<=n; i++) {
		if(!vis[i]) {
			dis=0;//记得清零 
			dfs1(i,0);
			dfs2(o,0);
			ans+=dis;
		}
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：thh_loser (赞：1)

# P8028 [COCI2021-2022#3] Cijanobakterije

[题面](https://www.luogu.com.cn/problem/P8028)
 
## 题意

给出 $n$ 个点，$m$ 条边，求在添加若干条边后形成的最长的一条链的长度。

## [前置芝士：树的直径](https://oi-wiki.org/graph/tree-diameter/)

## 思路

看到最长的链，很容易想到树的直径。由于数据可能是一片森林，对于每一棵树，因为不能包含环，显然他们的直径之和即为最长的一条链。

## code
```cpp
#include<bits/stdc++.h>
#define N 201000
using namespace std;
int n,m;
int fir[N],ne[N],to[N],tot;
int ans,maxx,op;
bool vis[N];
void add(int x,int y){
	ne[++tot]=fir[x];
	fir[x]=tot;
	to[tot]=y;
}
void dfs(int x,int fa=0,int dis=1){
	vis[x]=1;
	if(dis>maxx){
		maxx=dis;
		op=x;//记录最远节点的编号 
	}
	for(int i=fir[x];i;i=ne[i]){
		int e=to[i];
		if(e==fa){
			continue;
		}
		dfs(e,x,dis+1);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);//双向建图 
	}
	for(int i=1;i<=n;i++){
		if(vis[i]){//如果该节点包含在一棵已访问过的的树中
			continue;
		}
		maxx=-0x3f3f3f3f,op=0;//记得初始化 
		dfs(i);
		maxx=-0x3f3f3f3f;
		dfs(op);//两次dfs找直径 
		ans+=maxx;//将答案累加 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：aaron0919 (赞：1)

# [P8028 の题解](https://www.luogu.com.cn/problem/P8028)

### 题目大意

有 $n$ 个蓝藻细菌。这些细菌中有 $m$ 组细菌，这些细菌之间互相构成食物链（无环）。

现可在细菌之间两两添加若干条生物链，使得添加之后的所有生物链均不存在环（说明题目中的给出的图是森林）。

现在要求在进行若干次添加生物链的操作后，最长的长链的长度是多少。

### 理性分析

由于题目给的是森林，又把每个树连在一起，那么最长的长链就是每个树的长链加上串联这些树的长度。

### 代码实现

求一棵树的最长链就是求这棵树的直径，求一棵树的有两种办法，两遍 dfs 或 treedp，时间复杂度均为 $O(n)$。所以就选择 dfs 了，treedp 做的话有些多余（树形 dp 做的话可以跑负边权）。

不过跑两次 dfs 不需要打两遍，所以简单为好。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

vector<int> edge[N];
bool vis[N];
int d[N];
int maxi, n, m, ans;

void dfs(int prev, int cur)
{
    vis[cur] = true;
    if (d[cur] > d[maxi])
    {
        maxi = cur;
    }

    for (auto &nxt : edge[cur])
    {
        if (nxt == prev)
        {
            continue;
        }
        d[nxt] = d[cur] + 1;
        dfs(cur, nxt);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            d[i] = 1;
            maxi = i;
            dfs(-1, i);

            d[maxi] = 1;
            dfs(-1, maxi);

            ans += d[maxi];
        }
    }

    printf("%d", ans);
}
```

---

## 作者：1234567890sjx (赞：0)

写一个考场做法。

题目大意就是给出一个无向森林，让你加一些边满足不存在环，让森林连通，并让树的直径最长。

由于不能存在环，所以森林中若有 $n$ 个树，那么必然会恰好加入 $n-1$ 条边，且一个树不能加入任何的一条新边，也就是每一个树对答案的最大贡献必然为其的直径长度。

连边过程中并没有添加任何的新点，所以答案就是每一个树的直径的和。

用并查集维护森林中不同的树即可，时间复杂度 $O(\alpha n)$。

[代码](https://www.luogu.com.cn/paste/3dj9k4ov)

---

## 作者：xindlantern (赞：0)

# 题解

## 题目大意

存在若干个树，这些树之间都不联通，但我们可以连接起这些树，并求出在没有环的情况下，连接后形成的最长链的长度（指的是节点数）。

## 思路

很容易想到，我们连接森林里的树，要使最后得到一个最长链，就必须把所有的小树连接起来，形成一棵树。进一步地，每棵小树中的最长链是其直径，不断的将小树的直径进行依次连接即可得到最长链，并且不可能存在比最后求得的链更优的新链。

## 解法

关于树的直径的求法普遍有两种：两遍搜索和 DP。

### 搜索

从树上任意一点 $a$ 开始，走到能走到的最远的点 $b$，再从点 $b$ 出发，走到能走到的最远的点 $c$，那么从点 $b$ 到点 $c$ 之间的路径即树的直径。DFS 和 BFS 都可以实现这个操作。

### DP

树形 dp，以某一节点为根，求出它所有子树中的最长路径和次长路径，两相一加即为经过这一个点能得到的最长路径，所有的最长路径的最大值就是树的直径。

## 代码

以下代码用 DP 实现。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int n,m;
int h[N],ne[N<<1],e[N<<1],idx;
int ans,res;
bool st[N];

void add(int a,int b){
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

int dfs(int u,int fa){//树形dp
    st[u]=1;
    int d1=0,d2=0;//最大路径和次大路径
    for(int i=h[u];i!=-1;i=ne[i]){
        int j=e[i];
        if(j==fa) continue;
        int d=dfs(j,u)+1;
        if(d>=d1) d2=d1,d1=d;
        else if(d>d2) d2=d;
    }
    res=max(res,d1+d2);
    return d1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=1;i<=m;++i){
        int x,y;
        cin>>x>>y;
        add(x,y),add(y,x);
    }
    int ans=0;
    for(int i=1;i<=n;++i){
        if(!st[i]){//做标记，算过的树跳过
            res=0;
            dfs(i,-1);
            ans+=res+1;//累加答案
            //值得注意的是，这里dfs求出的是路径长度，要求路径上节点数需要加一
        }
    }
    cout<<ans;
    return 0;
}
```



---

