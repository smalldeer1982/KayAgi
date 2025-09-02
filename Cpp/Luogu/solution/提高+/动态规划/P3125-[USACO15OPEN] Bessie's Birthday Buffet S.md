# [USACO15OPEN] Bessie's Birthday Buffet S

## 题目描述

为了庆祝奶牛 Bessie 的生日，Farmer John 允许她在他最好的草地上自由吃草。

这片草地被划分为 $N$ 块草皮（$1 \le N \le 1000$），编号为 $1\ldots N$，每块草皮都有一个独特的质量值。如果 Bessie 吃了质量为 $Q$ 的草，她会获得 $Q$ 单位的能量。每块草皮通过双向路径与最多 10 个相邻草皮相连，Bessie 在相邻草皮之间移动需要消耗 $E$ 单位的能量（$1 \le E \le 1,000,000$）。

Bessie 可以选择从任意一块草皮开始吃草，她希望在积累最大能量后停止吃草。

不幸的是，Bessie 是一头挑剔的牛，一旦她吃了某种质量的草，她就再也不会吃质量等于或低于该水平的草了！她仍然乐意在不吃草的情况下穿过草皮；事实上，她可能会发现穿过一块高质量草皮而不吃草是有益的，只是为了稍后再回来享用美味的小吃。

请帮助确定 Bessie 能够积累的最大能量。

## 说明/提示

Bessie 从草皮 4 开始，获得 5 单位的能量。然后她沿着路径移动到草皮 5，在移动过程中消耗了 2 单位的能量。她拒绝吃草皮 5 上质量较低的草，并继续移动到草皮 3，再次消耗了 2 单位的能量。最后，她吃了草皮 3 上的草，获得了 6 单位的能量，总共积累了 7 单位的能量。

请注意，上述样例与提交时的测试用例 1 不同。

## 样例 #1

### 输入

```
5 2
4 1 2
1 3 1 3 4
6 2 2 5
5 2 2 5
2 2 3 4```

### 输出

```
7```

# 题解

## 作者：Night_Aurora (赞：6)

原题中的挑剔虽然增加了理解难度，但降低了这个题的编写难度

设DPM[i]表示由i这个点出发，能达到的最多的饱食度

那么很明显DPM[i]=i的质量

DPM[i]=max(DPM[i],DPM[wi]-Dist[wi][i]+i的质量),其中wi质量>i质量

Dist[wi][i]表示从i到wi的最短路长度

只需要设定一个DFS来记忆花搜索，每次搜一个点时SPFA一遍然后再用上面的DP方程就行

复杂度$O(kNE)\rightarrow O(10kN^2)$

代码







```cpp
#include <stdio.h>
#include <string.h>
#include <queue>
int N,E;
int Get[1100];
int EHead[1100],ENext[21000],ETo[21000];
int DPM[1100],Elt;
bool DPV[1100];
int Dist[1100][1100];
int Vis[1100][1100];
int SVis[1100];
std::queue<int> Qe;
void SPFA(int sp,int*Dist,int*Vis)
{
    int wi,wt,wl,we;
    Qe.push(sp);
    Dist[sp]=0;
    Vis[sp]=1;
    while(!Qe.empty())
    {
        wi=Qe.front();Qe.pop();
        wl=Dist[wi];
        SVis[wi]=0;
        for(we=EHead[wi];we;we=ENext[we])
            if(!Vis[wt=ETo[we]]||Dist[wt]>wl+E)
            {
                Dist[wt]=wl+E;
                if(!SVis[wt])
                    Qe.push(wt);
                SVis[wt]=Vis[wt]=1;
            }
    }
}
int max(int a,int b)
{return a>b?a:b;}
void DFS(int p)
{
    DPV[p]=1;
    int wi;
    DPM[p]=Get[p];
    SPFA(p,Dist[p],Vis[p]);
    for(wi=1;wi<=N;++wi)
        if(Get[wi]>Get[p])
            if(Vis[p][wi])
            {
                if(!DPV[wi])
                    DFS(wi);
                DPM[p]=max(DPM[p],Get[p]+DPM[wi]-Dist[p][wi]);
            }
}
void AddEdge(int Fr,int To)
{
    ++Elt;
    ENext[Elt]=EHead[Fr];
    ETo[Elt]=To;
    EHead[Fr]=Elt;
}
int main()
{
    scanf("%d %d",&N,&E);
    int wi,wib,t;
    for(wi=1;wi<=N;++wi)
    {
        scanf("%d %d",Get+wi,&wib);
        while(wib--)
        {
            scanf("%d",&t);
            AddEdge(wi,t);
        }
    }
    int mx=0;
    for(wi=1;wi<=N;++wi)
    {
        if(!DPV[wi])
            DFS(wi);
        mx=max(mx,DPM[wi]);
    }
    printf("%d\n",mx);
    return 0;
}
```

---

## 作者：白鲟 (赞：5)

## 前言
虽然看起来挺麻烦，做起来似乎蛮简单的……

## 题目分析
这道题看起来非常麻烦，然而仔细分析之后发现其实比较简单。由于可以路过而不计算点权，从一个点到另一个点按照最短路走答案必定最优。而我们可以发现，能够计入总贡献的点权是递增的，可以想到按照点权对所有点进行排序。设 $f_i$ 表示计算点 $i$ 的点权后总价值最大值，那么后面的点必定由前面的点转移过来，容易写出以下状态转移方程：

$$
f_i=max\{f_j-dis_{i,j}\}+value_i
$$

预处理出两点之间的最短路，这道题便可以大功告成了。根据这道题给出图边权全部相同这一特殊的性质，我们枚举每一个点算出其余点与其最短距离时可以运用广度优先搜索，第一次搜索到某个点的时候必定会给它最优解，对于每一个点的处理时间复杂度为 $\operatorname{O}(n+m)$。运用队列优化的 Bellman-Ford 算法，每个点也只会在第一次被访问时被松弛，时间复杂度依然如此（而不是所谓 $\operatorname{O}(kn)$ 或者 $\operatorname{O}(km)$）。

## 代码
注意每个点都可作为起点，也就是可以从虚拟点 $0$ 转移。
```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n,e,x,y,tot,v[1001],head[1001],suc[50001],go[50001];
long long ans,dis[1001][1001],f[1001];
bool vis[1001];
queue<int>que;
struct node
{
	int v,no;
}a[1001];
inline bool cmp(const node &t1,const node &t2)
{
	return t1.v<t2.v;
}
void bfs(int start)
{
	memset(vis,0,sizeof vis);
	dis[start][start]=0;
	vis[start]=true;
	que.push(start);
	while(!que.empty())
	{
		int front=que.front();
		que.pop();
		for(int i=head[front];i;i=suc[i])
			if(!vis[go[i]])
			{
				vis[go[i]]=true;
				dis[start][go[i]]=dis[start][front]+e;
				que.push(go[i]);
			}
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&e);
	memset(dis,0x7f,sizeof dis);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",&a[i].v,&x);
		a[i].no=i;
		for(int j=1;j<=x;++j)
		{
			scanf("%d",&y);
			go[++tot]=y;
			suc[tot]=head[i];
			head[i]=tot;
		}
	}
	for(int i=1;i<=n;++i)
		bfs(i);
	for(int i=0;i<=n;++i)
		dis[0][i]=0;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<i;++j)
			f[i]=max(f[i],f[j]-dis[a[j].no][a[i].no]+a[i].v);
		ans=max(ans,f[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：KSToki (赞：3)

本题方法：SPFA+DP

这道题$n$最多就$1000$，所以我们可以~~乱搞~~用$O(kn^2)$的从每一个点以$E$为边权SPFA一遍（当然也可以bfs）求出任意两点间的距离为DP备用。

题目中有一个限制，就是Bessie不会再吃相同或更低质量的牧草。处理方式就是先将其原来的编号存下来，再排个序。DP由质量低的转向质量高的，这样才能保证DP的转移是正确的。

接下来就是状态转移方程式了。由于这道题$n$最多就$1000$，所以我们可以~~乱搞~~用$O(n^2)$的DP，即对于每一个点枚举所有质量比它小的点进行转移，$f_i$表示以$t_i.id$为终点能够得到的最大能量，由于我们排了序，于是就有了下列代码：
```cpp
for(register int i=1;i<=n;++i)
{                            
  for(register int j=1;j<i;++j)
    f[i]=max(f[i],f[j]-dis[t[i].id][t[j].id]);//减去路上消耗的能量
  f[i]+=t[i].Q;
  ans=max(ans,f[i]);
}
```

代码也没有特别需要注意的地方，要说的话就是DP的时候加不加$.id$不要搞错了

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct stu
{
	int Q;
	int id;
}t[1001];
int n,E,d,x,head[1001],nxt[10001],to[10001],tot,dis[1001][1001],f[1001],ans;
bool visit[1001];
queue<int>q;
inline bool cmp(stu t1,stu t2)
{
	return t1.Q<t2.Q;
}
inline void add(int x,int y)
{
	nxt[++tot]=head[x];
	to[tot]=y;
	head[x]=tot;
}
void SPFA(int s)//默认大家都会SPFA。。。板子即可
{
	dis[s][s]=0;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		visit[x]=0;
		for(register int i=head[x];i;i=nxt[i])
		{
			int y=to[i];
			if(dis[s][y]>dis[s][x]+E)
			{
				dis[s][y]=dis[s][x]+E;
				if(!visit[y])
				{
					visit[y]=1;
					q.push(y);
				}
			}
		}
	}
}
int main()
{
	memset(dis,127,sizeof(dis));//初始化
	scanf("%d%d",&n,&E);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d%d",&t[i].Q,&d);
		t[i].id=i;
		while(d--)
		{
			scanf("%d",&x);
			add(i,x);
		}
	}
	for(register int i=1;i<=n;++i)
		SPFA(i);//每次SPFA完队列q肯定为空，visit肯定都是0，所以不用清空
	sort(t+1,t+n+1,cmp);
	for(register int i=1;i<=n;++i)
	{
		for(register int j=1;j<i;++j)
		    f[i]=max(f[i],f[j]-dis[t[i].id][t[j].id]);
		f[i]+=t[i].Q;
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
```

完！

---

## 作者：Together_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3125)

### 想法：

- 如果用 dfs 写，不用想，肯定超时，所以我们要进行优化。

- 我们可以用一个 $d$ 数组来记录路程，其中 $d_{i,j}$ 表示从点 $i$ 到点 $j$ 的最短距离。

- 然后再用使用动态规划来推这个答案，其中 $f_i$ 表示在 $i$ 号牧场停止享用的最大美味值。

### 思路：

- 遍历一遍所有点，分别从每个点出发进行 bfs，求出 $d$ 数组。

**bfs 代码：**
```cpp
void bfs(int b){
	queue<int> q;
	q.push(b);
	d[b][b] = 0;
	vis[b][b] = 1;
	while(!q.empty()){
		int front = q.front();
		q.pop();
		for(int i=0; i<G[front].size(); i++){
			if(!vis[b][G[front][i]]){
				vis[b][G[front][i]] = 1;
				d[b][G[front][i]] = d[b][front]+1;
				q.push(G[front][i]);
			}
		}
	}
}
```

- 在动态规划前，一定要**按美味值排序，排序，排序**，因为我们等会要考虑牧场的美味值这个因素，排好序就不用判断了，只要 $i>j$，那么 $c_i.v>c_j.v$。

- 在使用动态规划去推答案，答案是 $f_1$ 到 $f_n$ 之间的最大值。

**递推公式：**

### $f_i=\max(f_i, f_j+c_i.v-d_{c_j.id,c_i.id}×e)$

**递推部分代码:**

```cpp
for(int i=1; i<=n; i++){
	f[i] = c[i].v;
	for(int j=1; j<i; j++){
		if(vis[c[j].id][c[i].id]){
			f[i] = max(f[i], f[j]+c[i].v-d[c[j].id][c[i].id]*e);
		}
	}
	ans = max(ans, f[i]);
}
```

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

struct cow{
	int v, id;
};

cow c[1010];
int n, e, t1, t;
int f[1010], ans;
int d[1010][1010];
int vis[1010][1010];
vector<int> G[1010];

void bfs(int b){
	queue<int> q;
	q.push(b);
	d[b][b] = 0;
	vis[b][b] = 1;
	while(!q.empty()){
		int front = q.front();
		q.pop();
		for(int i=0; i<G[front].size(); i++){
			if(!vis[b][G[front][i]]){
				vis[b][G[front][i]] = 1;
				d[b][G[front][i]] = d[b][front]+1;
				q.push(G[front][i]);
			}
		}
	}
}

bool cmp(cow x, cow y){
	return x.v < y.v;
}

int main(){
	cin>>n>>e;
	for(int i=1; i<=n; i++){
		cin>>c[i].v;
		c[i].id = i;
		cin>>t;
		for(int j=1; j<=t; j++){
			cin>>t1;
			G[i].push_back(t1);
		}
	}
	for(int i=1; i<=n; i++)
		bfs(i);
	sort(c+1, c+1+n, cmp);
	for(int i=1; i<=n; i++){
		f[i] = c[i].v;
		for(int j=1; j<i; j++){
			if(vis[c[j].id][c[i].id]){
				f[i] = max(f[i], f[j]+c[i].v-d[c[j].id][c[i].id]*e);
			}
		}
		ans = max(ans, f[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_lmz_ (赞：2)

大佬们用什么 SPFA 和 DP，我这个蒟蒻根本看不懂，既然看不懂，就来水一篇简单易懂的 BFS + DP 的题解吧！

题意简化：

有 $n$ 片草地，每篇草地与一些草地相邻，奶牛一开始的能量为 $0$，走到相邻的草地需要花费 $e$ 点能量。

之所以这题使用 BFS，是因为它的每一个点不是与其他点相通的，并且只会吃比之前吃的草更好吃，即能量更多的草。

所以我们只需要用 BFS 遍历一遍，记录每片草地能从哪些草地过来，这是 BFS 要做的事情。

接下来，就来到 DP 的部分了。

首先给出递推式：

$$f_i=\max(f_i,f_j-\mathit{d}_{{a_i.id},{a_j.id}} \times e+a_i.v)$$

先解释一下式子中变量的意思，$f_i$ 代表在第 $i$ 片草坪结束的最大能量，$d$ 数组表示两片草坪中间需要走过多少草地，$a_i.id$ 表示第 $i$ 片草坪的编号，$a_j.id$ 也同理，$a_i.v$ 表示在第 $i$ 片草地能吃到的能量值。

然后来解释一下这个式子，通过推导，可以发现从第 $i$ 片到第 $j$ 片需要 ```d[i][j]*e``` 的能量值，于是这个式子就被我们推导出来了。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,e,vis[1010][1010],d[1010][1010],f[1010];
struct cow{
	int id,v;
}a[1010];
vector<int>g[1010];
void bfs(int b){
	queue<int>q;
	q.push(b);
	vis[b][b]=1;
	d[b][b]=0;
	while(q.size()){
		int front = q.front();
		q.pop();
		for(int i=0;i<g[front].size();i++){
			int t=g[front][i];
			if(!vis[b][t]){
				vis[b][t]=1;
				d[b][t]=d[b][front]+1;
				q.push(t);
			}
		}
	}
}
bool cmp(cow A,cow B){
	return A.v<B.v;
}
int main(){
	cin>>n>>e;
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
		a[i].id=i;
		int t;
		cin>>t;
		for(int j=1;j<=t;j++){
			int temp;
			cin>>temp;
			g[i].push_back(temp);
		}
	}
	for(int i=1;i<=n;i++)
		bfs(i);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		f[i]=a[i].v;
		for(int j=1;j<i;j++){
			if(vis[a[i].id][a[j].id])
				f[i]=max(f[i],f[j]-d[a[i].id][a[j].id]*e+a[i].v);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：kai586123 (赞：2)

欢迎来蒟蒻的博客看本题题解[Baka's Blog](https://baka.online/usaco15openbessie%E7%9A%84%E7%94%9F%E6%97%A5%E8%87%AA%E5%8A%A9%E9%A4%90/)

[[USACO15OPEN]Bessie的生日自助餐](https://www.luogu.org/problemnew/show/P3125)

上面的题解写了记搜，实际上也可以DP。首先预处理出任意两点间距离，因为本题边权都一样，bfs即可。

要求吃草顺序单增，考虑每一个点，要么作为终点，要么走向更大的点。把点按点权从大到小排序。DP转移方程：$f(x)=max(val(x),max(val(x)+f(y)-dis(x,y)))$，其中$val(x)<val(y)$，排序后即$y<x$

$ans=max(f(x))$。复杂度$O(nm+n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int a = 1, b = 0; char c = getchar();
    while (!isdigit(c)) a = c == '-' ? 0 : 1, c = getchar();
    while (isdigit(c)) b = b * 10 + c - '0', c = getchar();
    return a ? b : -b;
}

const int N = 1000 + 233, M = N * 10;

int n, e, val[N], dis[N][N], node[N], f[N], ans;
queue<int> que;
bool vis[N];

struct Graph { int to, nxt; } g[M * 2];
int head[N], tot;

void addedge(int x, int y) {
    g[++tot].to = y, g[tot].nxt = head[x],
    head[x] = tot;
}

bool comp(int x, int y) { return val[x] > val[y]; }

int main() {
    // read
    n = rd(), e = rd();
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; ++i)
        dis[i][i] = 0;
    for (int i = 1; i <= n; ++i) {
        val[i] = rd();
        node[i] = i;
        for (int j = rd(); j; --j)
            addedge(i, rd());
    }
    
    // bfs
    for (int s = 1; s <= n; ++s) {
        memset(vis, 0, sizeof(vis));
        que.push(s);
        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = head[x]; i; i = g[i].nxt) {
                int y = g[i].to;
                if (!vis[y]) {
                    vis[y] = true;
                    que.push(y);
                    dis[s][y] = dis[s][x] + e;
                }
            }
        }
    }

    // dp
    sort(node + 1, node + n + 1, comp);
    for (int i = 1; i <= n; ++i) {
        f[i] = val[node[i]];
        for (int j = 1; j < i; ++j)
            f[i] = max(f[i], val[node[i]] + f[j] - dis[node[i]][node[j]]);
        ans = max(ans, f[i]);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：yxy666 (赞：1)

题意：给我们 $n$ 个点和若干条边，每一个点都有权值，每经过一条边都需要付出 $E$ 的代价，且每一个点只可取一次。我们可以从任意点出发，每次选择加的权值必须大于上一次选择的权值。求选取权值减去代价的最大值。

分析：很明显，如果选取当前的点，那么只能从权值小于当前点的点推过来。设 $f_i$ 为最后一次取 $i$ 的最优解，当前点为 $i$，上一次的节点为 $j$，当前节点的权值为 $W_i$，从 $j$ 到 $i$ 的最小代价为 $P$。易得状态转移方程为 $f_i=\max(f_i,f_j-P)+W$。

由于本题数据较水，$n\le1000$，我们完全可以以每一个点为起点刷一趟最短路，预处理出两点之间的距离。然后按照权值大小排一趟序，刷一趟 DP 就好了。
```cpp
#include<bits/stdc++.h>
#define TT 100000
using namespace std;
const int maxn=1005,maxe=20005;
int n,E,tot,Ans,f[maxn],lnk[maxn],dis[maxn][maxn],son[maxe],nxt[maxe],que[100005];
struct yxy{
	int x,id;bool operator<(const yxy b)const{return x<b.x;}
}a[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f; 
}
void add_e(int x,int y){son[++tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void spfa(int x){
	int hed=0,til=1;que[til]=x;
	dis[x][x]=0;
	while(hed!=til){
		hed=(hed+1)%TT;
		for(int j=lnk[que[hed]];j;j=nxt[j]){
			if(dis[x][son[j]]<=dis[x][que[hed]]+E)continue;
			dis[x][son[j]]=dis[x][que[hed]]+E;
			que[til=(til+1)%TT]=son[j];
		}
	}
}
int main(){
	n=read();E=read();int D,x; 
	for(int i=1;i<=n;i++){
		a[i].x=read(),D=read();a[i].id=i;
		for(int j=1;j<=D;j++)x=read(),add_e(i,x);
	}
	memset(dis,63,sizeof dis);
	for(int i=1;i<=n;i++)spfa(i);
	sort(a+1,a+1+n);
	for( int i=1;i<=n;++i){
		for( int j=1;j<i;j++)f[i]=max(f[i],f[j]-dis[a[i].id][a[j].id]);
		f[i]+=a[i].x;
		Ans=max(Ans,f[i]);
	}
	printf("%d\n",Ans);
	return 0;
}
```


---

## 作者：VioletIsMyLove (赞：1)

对于每一片草地，如果吃了这个草地的草，那么再要吃的话只能吃质量比这块地更高的，那么果断对土地按照质量从低到高排序，然后刷 $n$ 次 $BFS$，刷出每个点到另一点的最短路，那么对于 $i$ 这个点，如果要吃的话，就从 $1----i-1$ 之前找一个最大值，然后 $i$ 的值就是 $i$ 位置草的质量和之前最大值 $+i$ 位置草的质量 $-e*i----$ 最大值的最短路。最后在 $1----n$ 刷一趟最大值就ok了。(代码有坑）

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ZS{
	int v,id;
	bool operator <(const ZS b)const{return v<b.v;}
}a[10005];
int n,e,tot,ans;
int lnk[1005],w[1005],v[1005],q[100005],nxt[20005],son[20005];
int dis[1005][1005];
bool vis[1005];
void make(int x,int y){son[++tot]=y;nxt[tot]=lnk[x];lnk[x]=tot;}
void BFS(int x){
	int hed=0,til=1;vis[x]=1;q[til]=x;
	while(hed<=til)
		for(int i=lnk[q[++hed]];i;i=nxt[i])if(!vis[son[i]]){
			dis[x][son[i]]=dis[x][q[hed]]+1;
			q[++til]=son[i];vis[son[i]]=1;
	}
	memset(vis,0,sizeof vis);
}
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main()
	freopen("buffet.in","r",stdin);
	freopen("buffet.out","w",stdout);
	n=read();e=read();
	for(int i=1;i<=n;i++){
		a[i].v=read();a[i].id=i;
		w[i]=v[i]=a[i].v;
		int x=read();
		for(int j=1;j<=x;j++){
			int y=read();
			make(i,y);make(y,i);
		}
	}
	for(int i=1;i<=n;i++)BFS(i);
	sort(a+1,a+1+n);
	for(int i=1;i<n;i++)
	for(int j=i+1;j<=n;j++)if(dis[a[i].id][a[j].id])w[a[j].id]=max(w[a[j].id],w[a[i].id]+v[a[j].id]-e*dis[a[i].id][a[j].id]);
	for(int i=1;i<=n;i++)ans=max(ans,w[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：45dino (赞：1)

貌似有一个更容易理解的方法。

令 $Q_i$ 表示第 $i$ 个草地的质量，$dp_i$ 表示吃这个草地后对整体的增益。

对于每一个 $i$ ，如果 $d_l$ 代表 $l$ 和 $i$ 的距离，则
$$dp_i=max(Q_i+dp_l-e\times d_l|Q_i<Q_l)$$

则对于每一个 $i$ ，用 SPFA 算 $d$ 数组，再求 $dp_i$ 。

注意到有一个限制条件 $Q_i<Q_l$ ，有一个 $trick$ 可以避免在转移时比较。

把所有草地编号按 $Q$ 从大到小排序，这样在转移时先算 $Q$ 大的，再算 $Q$ 小的，转移前面的值时不会用到后面的值。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int to,next;
} edge[10001];
int n,e,cnt,Q[1001],dp[1001],head[10001],d[1001];
bool cmp(int x,int y)
{
	return Q[x]<Q[y];
}
void add(int x,int y)
{
	edge[++cnt].to=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
}
int main()
{
	scanf("%d%d",&n,&e);
	for(int i=1;i<=n;i++)
	{
		int d;
		scanf("%d%d",&Q[i],&d);
		while(d--)
		{
			int a;
			scanf("%d",&a);
			add(i,a);	
		} 
	}
	vector<int> v;
	for(int i=1;i<=n;i++)
		v.push_back(i);
	sort(v.begin(),v.end(),cmp);
	int ans=0;
	for(int i=n-1;i>=0;i--)
	{
		int u=v[i];
		queue<int> q;
		for(int l=1;l<=n;l++)
			d[l]=-1;
		q.push(u);
		d[u]=0;
		while(!q.empty())
		{
			int v=q.front();
			q.pop();
			for(int l=head[v];l;l=edge[l].next)
				if(d[edge[l].to]==-1)
				{
					d[edge[l].to]=d[v]+1;
					q.push(edge[l].to);
				}
		}
		int res=Q[u];
		for(int l=1;l<=n;l++)
			if(d[l]!=-1)
				res=max(res,Q[u]+dp[l]-e*d[l]);
		dp[u]=res;
    	ans=max(ans,res);
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：iterator_it (赞：0)

## BFS 基础题，建议降黄

题意简述：

有 $n$ 片草地，每篇草地与一些草地相邻，奶牛一开始的能量为 $0$，走到相邻的草地需要花费 $e$ 点能量。

但是贝西很挑剔，每次吃的草的美味程度必须严格大于上一次吃的草。

`BFS` 可以让我们求出第 $i$ 块草地到第 $j$ 块草地需要多少能量，所以我们可以列出以下转移方程：
$$dp_j-d_{i,j} \times e + a_i$$
其中：$d_{i,j}$ 表示从 $i$ 到 $j$ 需要的单位时间，$\times e$ 代表了所需要的能量。

$a_i$ 则是第 $i$ 块草地的美味程度，也就是能够补充的能量值。

接下来，我们要解决题目的特殊条件，非常简单，在 `BFS` 之前把 $a$ 数组排序以下，`BFS` 的时候只往后面搜索，就可以满足条件。

因为要排序，不能直接使用 $a$ 数组的下标，所以 $a$ 数组应该是结构体类型，里面有他的序号和美味值。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,e,vis[maxn][maxn],d[maxn][maxn],dp[maxn];
struct Node{
	int k,v;//k为序号，v是美味值 
}a[maxn];
vector<int>g[maxn];
void bfs(int b){
	queue<int>q;
	q.push(b);
	vis[b][b]=1;
	d[b][b]=0;
	while(q.size()){
		int f = q.f();
		q.pop();
		for(int i=0;i<g[f].size();i++){
			int t=g[f][i];
			if(!vis[b][t]){
				vis[b][t]=1;
				d[b][t]=d[b][f]+1;
				q.push(t);
			}
		}
	}
}
bool cmp(Node A,Node B){
	return A.v<B.v;//按美味值排序 
}
int main(){
	cin>>n>>e;
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
		a[i].k=i;
		int t;
		cin>>t;
		for(int j=1;j<=t;j++){
			int x;
			cin>>x;
			g[i].push_back(x);
		}
	}
	for(int i=1;i<=n;i++)
		bfs(i);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		dp[i]=a[i].v;
		for(int j=1;j<i;j++){
			if(vis[a[i].k][a[j].k])
				dp[i]=max(dp[i],dp[j]-d[a[i].k][a[j].k]*e+a[i].v);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i]);
	cout<<ans;
	return 0;
}

```

---

