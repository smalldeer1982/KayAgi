# 「GFOI Round 2」Jom & Terry

## 题目背景

我在做 [#3406. 「2020-2021 集训队作业」Tom & Jerry](https://loj.ac/p/3406)……

你说得对，但是：
> Tom and Jerry is an American animated media franchise and series of comedy short films created in 1940 by William Hanna and Joseph Barbera. Best known for its 161 theatrical short films by Metro-Goldwyn-Mayer, the series centers on the rivalry between the titular characters of a cat named Tom and a mouse named Jerry. Many shorts also feature several recurring characters.
> 
> In its original run, Hanna and Barbera produced 114 Tom and Jerry shorts for MGM from 1940 to 1958. During this time, they won seven Academy Awards for Best Animated Short Film, tying for first place with Walt Disney's Silly Symphonies with the most awards in the category. After the MGM cartoon studio closed in 1957, MGM revived the series with Gene Deitch directing an additional 13 Tom and Jerry shorts for Rembrandt Films from 1961 to 1962. Tom and Jerry became the highest-grossing animated short film series of that time, overtaking Looney Tunes. Chuck Jones produced another 34 shorts with Sib Tower 12 Productions between 1963 and 1967. Five more shorts have been produced since 2001, making a total of 166 shorts.
>
> A number of spin-offs have been made, including the television series The Tom and Jerry Show (1975), The Tom and Jerry Comedy Show (1980–1982), Tom & Jerry Kids (1990–1993), Tom and Jerry Tales (2006–2008), and The Tom and Jerry Show (2014–2021). In 1992, the first feature-length film based on the series, Tom and Jerry: The Movie, was released. 13 direct-to-video films have been produced since 2002. In 2021, a a live-action/animated hybrid film was released. In 2019, a musical adaptation of the series, titled Tom and Jerry: Purr-Chance to Dream, debuted in Japan, in advance of Tom and Jerry's 80th anniversary.

## 题目描述

Terry 和 Jom 在一个 $n$ 个点 $m$ 条边的有“根”无向连通图上博弈（图的根为 $r$），遵循以下规则：

- Terry 先手；
- 两人轮流在图上移动，每次只能走一条边（也可以睡觉，啥都不干）；
- Terry 不能走到 Jom 所在的结点（我们认为只有 Terry 自投罗网时才会被抓到，即如果 Terry 先移动到结点 $u$ 后 Jom 在同一回合也移动到 $u$ 是合法的）。

给定 $q$ 次询问，每次询问给定 Terry 和 Jom 的起点 $a, b$，你需要回答 Terry 能否到达根（即点 $r$）。

## 说明/提示

#### 【提示】

本题 IO 量较大，请选手使用较快的读入输出方式。

#### 【数据范围】

**本题采用捆绑测试。**

| 子任务编号 | $n, m, q \le$ |     特殊性质     | 分值 |
| :--------: | :-----------: | :--------------: | :--------: |
|    $0$     |       $10^6$       | A |    $1$     |
|    $1$     |     $10$      |        无        |    $9$     |
|    $2$     |       $10^6$       |  B  |    $15$    |
|    $3$     |       $10^6$       | C |    $15$    |
|    $4$     |       $10^6$       |        无        |    $60$    |

- 特殊性质 A：$q = 0$。
- 特殊性质 B：保证图是一条链。
- 特殊性质 C：保证图是一个菊花。

对于所有数据，满足：

- $1 \le n, m \le 10^6$；
- $0 \le q \le 10^6$；
- $1 \le r, u, v, a, b \le n$；
- 给定的图是一个无向连通图。

## 样例 #1

### 输入

```
5 4 3
4 3
3 2
1 5
1 2
2
1 2
5 4```

### 输出

```
I'm here!
Jom
Jom```

## 样例 #2

### 输入

```
5 5 4
1 4
4 3
3 2
4 5
5 3
2
3 1
5 1```

### 输出

```
I'm here!
Terry
Terry```

# 题解

## 作者：_ScreamBrother_ (赞：12)

这道题是图论题。

## 思路
可以想到，如果 Jom 先到“根”，则 Terry 一定会输。所以 Jom 一定会沿着开始点到“根”的最短路走（这样可以尽量的比 Terry 先到“根”，从而抓到 Terry）。而 Terry 为了不被抓到，肯定也要尽量快的到达“根”。所以当：
$$dis(a) \le dis(b)$$
时，Jom 能抓住 Terry。

跑一遍最短路，按照上面的规则判断一下即可。

## 代码

```cpp
#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) w = ch == '-' ? -1 : 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) s = s * 10 + ch - '0';
	return s * w;
} // 快读

vector < pair <int, int> > G[1000010];
int N, P, C, Q, f[1000010] = {}, x, y, a, b;
bool vis[1000010];

signed main() {
	puts("I'm here!");
//	cin >> N >> P >> C;
	N = read(), P = read(), C = read();
	for (int i = 1; i <= P; i ++) {
		x = read(), y = read();
		G[x].push_back({1, y}), G[y].push_back({1, x});
	}
// 开始跑最短路
	priority_queue < pair <int, int>, vector < pair <int, int> >,
	greater < pair <int, int> > > que;
	que.push({0, C});
	for (int j = 1; j <= N; j ++) f[j] = 1145141919;
	f[C] = 0;
	while (!que.empty()) {
		int x = que.top().second;
		que.pop();
		if (vis[x]) continue;
		vis[x] = true;
		for (int j = 0; j < (int) G[x].size(); j ++) {
			pair <int, int> v = G[x][j];
			if (f[v.second] >= f[x] + v.first && !vis[v.second]) {
				f[v.second] = f[x] + v.first;
				que.push({f[v.second], v.second});
			}
		}
	}
	
	Q = read();
	while (Q --) {
		a = read(), b = read();
		if (f[a] <= f[b]) puts("Terry");
		else puts("Jom"); // 判断距离
	}
}
``````

## 最后
本人是第一次写题解 ~~，给个赞再走吧！！！~~

---

## 作者：ycy1124 (赞：10)

### 题意
Terry 和 Jom 一起在图上玩一个游戏，每次两人可以选择移动一条边或者不动，当 Terry 移动到 Jom 所在的点他就输了，当 Terry 移动到给定节点 $r$ 他就赢了。（当 Jom 先到 $r$ 节点 Jerry 后到也算 Jerry 输）给出一个有 $n$ 个节点 $m$ 条边的图和目标节点 $r$，$q$ 次询问，每次给出 Jerry 和 Jom 的出发节点 $a,b$，Jerry 先手，求胜者是谁。
### 思路
靠虑 Jom 的必胜策略，当他去追逐 Jerry 肯定是没用的，因为 Jerry 肯定是不会自投罗网的。所以 Jom 唯一的策略只有两种，一种是挡在 Jerry 前往 $r$ 的路径上睡大觉，另一种是在 $r$ 上睡大觉。对于第一种情况，当 Jom 能先 Jerry 到达路径上的某一点那么 Jom 也一定能先比 Jerry 到达 $r$。因此，第一种情况也能够化作第二种情况。
### 代码
从 $r$ 开始 bfs 求每个点距离 $r$ 的最短路径，然后在每个问题比一下 $dis_a,dis_b$ 的大小就行了。

由于是 Jerry 先手，比大小那里要取等。
```cpp
#include<bits/stdc++.h>
#define N 1000005
//#define int long long
using namespace std;
inline int rint(){
	int x;
	cin>>x;
	return x;
}
//int js[26];
int n,m,r;
vector<int>a[N];
int dis[N];
struct Node{
	int i,w;
};
queue<Node>q;
void bfs(int p,int w){
	dis[p]=w;
	for(auto it:a[p]){
		if(dis[it]==1e9){
			q.push({it,w+1});
			dis[it]=w+1; 
		}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cout<<"I'm here!\n";
	n=rint(),m=rint(),r=rint();
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1;i<=n;i++){
		dis[i]=1e9;
	}
	q.push({r,0});
	while(!q.empty()){
		bfs(q.front().i,q.front().w);
		q.pop(); 
	}
	int t=rint();
	while(t){
		--t;
		int s=rint(),t=rint();
		if(dis[s]<=dis[t]){
			cout<<"Terry\n";
		}
		else{
			cout<<"Jom\n";
		}
	}
	return 0;
} 
```
[AC 记录](https://www.luogu.com.cn/record/189103931)。

---

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/P11280)

### 题意

在一个无向图上，设 $\operatorname{dis}(u,v)$ 为从 $u$ 到 $v$ 的最短路径长度，判断 $\operatorname{dis}(a,r)\le\operatorname{dis}(b,r)$。

### 思路

不难想到暴力解法，对于每次询问都用 bfs 求最短路径长度并判断。在此基础上，由于这是一个无向图，所以 $\operatorname{dis}(u,v)=\operatorname{dis}(v,u)$。可以在建完图后以 $r$ 为起点做 bfs，预处理 $r$ 到所有点的最短路径长度。时间复杂度 $\mathcal{O}(n+m+q)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e6+10;
int dis[N];
vector<int>vc[N];
queue<int>q;
int main(){
	int n=read(),m=read(),r=read();
	while(m--){
		int u=read(),v=read();
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	memset(dis,-1,sizeof(dis));
	q.push(r),dis[r]=0;
	while(!q.empty()){
		int u=q.front();
		for(auto i:vc[u])
			if(dis[i]==-1){
				dis[i]=dis[u]+1;
				q.push(i);
			}
		q.pop();
	}
	int T=read();
	printf("I\'m here!\n");
	while(T--){
		int u=read(),v=read();
		printf(dis[u]<=dis[v]?"Terry\n":"Jom\n");
	}
	return 0;
}
```

---

## 作者：WsW_ (赞：3)

### 更新
- $2024.11.26$ 删除逗号和汉字之间的一个空格。


---
### 前言
简单图上思维题。

周六的时候还在上课，语文课上拿着同学老年机看题并口胡，秒了。

---
### 约定
将 Jom 称为**猫**，将 Terry 称为**鼠**。  
将鼠移动到根的所有路径中，必须经过的点称为**关键点**。  
将图上两点 $u,v$ 间的最小距离记为 $\operatorname{dis}(u,v)$。

---
### 思路
一个显然的结论是：如果猫能比鼠更早到一个关键点，那么猫就可以一直守在那里并且获胜。  
另一个显然的结论是：根结点必定是关键点。  

所以只要猫能比鼠更早到根节点，即 $\operatorname{dis}(a,r)>\operatorname{dis}(b,r)$，那么猫就赢了。  

再考虑如果猫不能比鼠更早到根结点怎么办。  
猜测结论：如果猫不能比鼠更早到根结点，那么鼠就赢了。考虑用反证法证明结论。  

假设逆命题成立：猫不能比鼠更早到根结点，但猫可能会赢。  

又一个显然的结论是：如果猫不能比鼠更早到任何一个关键点，那么鼠就赢了。  
既然猫可能会赢，而“存在猫能比鼠更早到一个关键点”是“猫赢”的必要条件，那么说明存在一个关键点 $u$，使得猫到这个点的距离小于鼠到这个点的距离，即 $\operatorname{dis}(a,u)>\operatorname{dis}(b,u)$。  
因为 $u$ 对于鼠来说是关键点，所以 $\operatorname{dis}(a,r)=\operatorname{dis}(a,u)+\operatorname{dis}(u,r)$。  
但是 $u$ 对于猫来说不一定是去 $r$ 的关键点，所以 $\operatorname{dis}(b,r)\le\operatorname{dis}(b,u)+\operatorname{dis}(u,r)$。  
综合上面三个式子可得：$\operatorname{dis}(b,r)<\operatorname{dis}(a,r)$，即猫能比鼠更早到达根结点，与假设前提相冲突，所以假设不成立。  

综上所述，如果猫能比鼠更早到根结点，那么猫就赢了；否则鼠就赢了。  

以 $r$ 为源点做一次 bfs 算出所有的 $\operatorname{dis}(u,r)$。询问的时候直接比较 $\operatorname{dis}(a,u),\operatorname{dis}(b,u)$ 即可。 

时间复杂度为 $O(n+m+q)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
int dis[MAXN];
vector<int>edg[MAXN];
queue<int>que;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,m,r; cin>>n>>m>>r;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		edg[u].push_back(v);
		edg[v].push_back(u);
	}
	
	que.push(r);//bfs求出dis
	while(!que.empty()){
		int fr=que.front();
		que.pop();
		for(auto to:edg[fr]){
			if(to!=r&&dis[to]==0){
				dis[to]=dis[fr]+1;
				que.push(to);
			}
		}
	}
	
	int q; cin>>q;
	cout<<"I'm here!\n";
	while(q--){
		int a,b; cin>>a>>b;
		if(dis[b]<dis[a])cout<<"Jom\n";//直接比较
		else cout<<"Terry\n";
	}
	
	return 0;
}
```

---

## 作者：liuchang09 (赞：2)

## 思路

设 $f(x)$ 为 $x$ 节点到根节点的距离，若 $f(x)\ <f(y)$ 则可以说明 $x$ 节点比 $y$ 节点前往根节点所需要的步数更少，又跟据题中所言：


> 如果 Terry 先移动到结点 $u$ 后 Jom 在同一回合也移动到 $u$ 是合法的

所以 $f(x)\ =f(y)$ 的时候，则 Terry 和 Jom 在一路上紧追不舍但 Terry 更先到达根节点，而 Jom 紧随其后，此时仍然算 Terry 赢。

而 $f(x)\ >f(y)$ 的时候，则 Jom 比 Terry 提前了至少一个回合到达根节点，所以 Jom 可以一直在根节点不移动然后等到 Terry 在到达与根节点直接相连的边的时候抓到他，此时 Jom 胜利。

## 解法

通过一遍广度优先搜索来记录 $f(x) $ 的大小，随后通过 $O(1)$ 时间复杂度回答。

总时间复杂度为 $O(n+q)$ ，不加快读快写的话能极限时间过大的数据。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+1e1;
bool vis[maxn];
queue<int > q;
int n,m,root;
int f[maxn];
int t;
vector<int > a[maxn]; 
bool done[maxn];
int main(){
	memset(f,0x3f,sizeof f);
	printf("I'm here!\n");
	scanf("%d%d%d",&n,&m,&root);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		if(u==v) continue;
		a[u].push_back(v);
		a[v].push_back(u);//链接矩阵存双向边
	}
	q.push(root);
	vis[root]=true;
	f[root]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=0;i<a[x].size();i++){
			int y=a[x][i];
			if(!vis[y]) q.push(y),f[y]=f[x]+1,vis[y]=true;
		}
	}
	scanf("%d",&t);
	while(t--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(f[x]<=f[y])
			printf("Terry\n");
		else printf("Jom\n");
	}
	return 0;
}
```

---

## 作者：include13_fAKe (赞：2)

怎么到现在才能写题解，这是我自己的机会吗。

## 思路

有人说这题可以骗分，难道是说可以过 $q=0$ 吗。

本题实际上就是一个单源最短路问题。

可以通过 bfs 寻找 Jom 和 Terry 距离根的最短路长度。

令 Terry 到根的距离为 $x$，Jom 到根的距离为 $y$。

因为是 Terry 先行动，所以当 $x\le y$ 时，Terry 能够到达，否则不能。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=3e6;
int n,m,R;
struct node{
	int to;
	int nxt;
}edge[N];
int num_edge;
int head[N];
int zdl[N]; 
void add(int u,int v){
	edge[++num_edge].nxt=head[u];
	edge[num_edge].to=v;
	head[u]=num_edge;
}
void bfs(int R){
	queue<int> q;
	q.push(R);
	memset(zdl,0x3f,sizeof(zdl));
	zdl[R]=0;
	while(!q.empty()){
		int now=q.front();
		q.pop();
		for(int i=head[now];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(zdl[v]>zdl[now]+1){
				zdl[v]=zdl[now]+1;
				q.push(v);
			}
		}
	}
}
int main(){
	cin>>n>>m>>R;
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v),add(v,u);
	}
	bfs(R);
	int q;
	cin>>q;
	puts("I'm here!");
	while(q--){
		int a,b;
		scanf("%d%d",&a,&b);
		if(zdl[a]>zdl[b])	puts("Jom");
		else	puts("Terry");
	}
	return 0;
}  //再给我两分钟 让我把记忆结成冰  
```

---

## 作者：dzkkkkk (赞：2)

题意，求出每个点到 $r$ 的最短距离，共 $q$ 次查询，注意除去自环。
```cpp
#include<bits/stdc++.h>
using namespace std;

queue<int> q;
vector<int> g[1000010];
bool flag[1000010];
int f[1000010],n,m,r,x;

int main()
{
	printf("I'm here!\n");
	cin>>n>>m>>r;
	for(int i=1;i<=n;i++)
		f[i]=1e9;//初始化 
	f[r]=0;//注意原点不是1e9 
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(u==v) continue;//去除自环 
		g[u].push_back(v);
		g[v].push_back(u);
	}
	flag[r]=true;//初始化 
	q.push(r);//原点压入队列 
	while(!q.empty()) 
	{
		int u=q.front();
		q.pop();
		int len=g[u].size();
		for(int i=0;i<len;i++)
		{
			int v=g[u][i];
			if(!flag[v])
			{
				flag[v]=true;
				q.push(v);
				f[v]=f[u]+1;
			}
		}
	}
	cin>>x;
	while(x--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(f[u]<=f[v])
			printf("Terry\n");
		else
			printf("Jom\n");
	}
	return 0;
}
```

---

## 作者：gavinliu266 (赞：1)

# 思路
记 Terry 的位置为 $a$，Jom 的位置为 $b$，两点之间最短路长度为 $\operatorname{dis}$。

如果 $\operatorname{dis}(r,a)>\operatorname{dis}(r,b)$，那么 Jom 能比 Terry 先到根，Jom 就可以守在那里获胜。

否则，$\operatorname{dis}(r,a) \le \operatorname{dis}(r,b)$，Terry 会向根的最短路径跑，猜测 Terry 必胜，即证明此时 Jom 追不上 Terry 即可。

反证法，如果 Jom 能比 Terry 先到达某个点，设为 $k$，那么 $\operatorname{dis}(a,k)>\operatorname{dis}(b,k)$，所以 $\operatorname{dis}(r,k)+\operatorname{dis}(a,k)>\operatorname{dis}(b,k)+\operatorname{dis}(r,k)$。

因为 $k$ 是 $a$ 到 $r$ 最短路上的点，所以 $\operatorname{dis}(r,k)+\operatorname{dis}(a,k)=\operatorname{dis}(r,a)$，所以 $\operatorname{dis}(r,a)>\operatorname{dis}(b,k)+\operatorname{dis}(r,k) \ge \operatorname{dis}(r,b)$。矛盾，所以此时 Terry 必胜。

于是当 $\operatorname{dis}(r,a)>\operatorname{dis}(r,b)$ 时 Jom 必胜，否则 Terry 必胜。

程序好写了，时间复杂度 $O(n+q)$。

---

## 作者：封禁用户 (赞：1)

真，图上博弈。  
### 具体思路
很明显，如果 Jom 从起点到根的距离小于 Terry 从起点到根的距离，那么 Jom 就可以先到达根，Terry 就绝对无法合法地到达根，因为题目已经说明了 Terry 不能走到 Jom 所在的结点。但是反之，由于 Terry 先手，如果 Terry 从起点到根的距离**小于等于** Jom 从起点到根的距离，那么 Terry 就可以先到达根。这是最短路？图上边权全是 $1$，因此直接 bfs 遍历图并记录从根到每个结点的最短距离即可。  
### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
const int N=1e6+5;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
struct Edge {
	int act,next;
} edge[2*N];//链式前向星建无向图，所以需要两倍的空间 
int eid,head[N],ans[N];
void eadd(int u,int v) {
	eid++;
	edge[eid].act=v;
	edge[eid].next=head[u];
	head[u]=eid;
}
int flag;
int main() {
	cout<<"I'm here!\n";
	int n,m,r;
	n=read(),m=read(),r=read();
	for(int i=1; i<=m; i++) {//建图 
		int u,v;
		u=read(),v=read();
		eadd(u,v); 
		eadd(v,u);
	}
	queue<int>p,l;//也可以用一个队列套 pair 代替 
	p.push(r);
	l.push(0);
	ans[r]=0;
	while(!p.empty()) {//图遍历 
		int u=p.front(),k=l.front()+1;
		p.pop(),l.pop();
		for(int i=head[u]; i; i=edge[i].next) {
			if(!ans[edge[i].act]&&edge[i].act!=r) {//注意根需要特判 
				ans[edge[i].act]=k;//记录答案 
				p.push(edge[i].act);
				l.push(k);
			}
		}
	}
	int q;
	q=read();
	while(q--) {//回答每次询问 
		int a,b;
		a=read(),b=read();
		if(ans[a]<=ans[b])puts("Terry");
		else puts("Jom");
	}

	return 0;
}

```

---

## 作者：chenxi2009 (赞：1)

# 思路
记一个点 $i$ 到 $r$ 的距离为 $d_i$。\
当 $d_a>d_b$ 时，Terry 不能到达根。Jom 可以先走到根，使得 Terry 无法来到此位置。\
当 $d_a\le d_b$ 时，Terry 可以到达根。若两人走向 $r$ 的最短路无交叉，显然 Terry 可以走到根；若两人的最短路有交叉，显然是 Terry 先走到交叉点，否则 Jom 的最短路会更短，矛盾。

综上，Terry 走到根的可能性取决于 $d_a$ 和 $d_b$ 的大小关系。采用广度优先搜索可以预处理出 $d$。时间复杂度 $O(n+q)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,r,u,v,T,a,b,dis[1000001];
vector<int>e[1000001];
queue<int>q;
int main(){
	printf("I'm here!\n");//别忘了签到 
	scanf("%d%d%d",&n,&m,&r);
	for(int i = 1;i <= m;i ++){
		scanf("%d%d",&u,&v);
		e[u].push_back(v),e[v].push_back(u);
	}
	dis[r] = 0,q.push(r);//预处理 
	while(q.size()){//广度优先搜索 
		u = q.front();
		q.pop();
		for(auto v : e[u]){
			if(dis[v] || v == r)continue;
			dis[v] = dis[u] + 1,q.push(v);
		}
	}
	scanf("%d",&T);
	for(int i = 1;i <= T;i ++){
		scanf("%d%d",&a,&b);
		if(dis[a] <= dis[b]) printf("Terry\n");
		else printf("Jom\n");
	}
	return 0;
}
```

---

## 作者：Hy13_xsm (赞：1)

## 题意理解

Jom 和 Terry 在一个图上面博弈，给定一个节点，问 Terry 是否能在 Jom 把他堵住之前到达那个节点。

## 题目分析

不难发现，如果 Terry 的最短路小于 Jom 的，他一定就能够到达指定节点。

思路一下就打开了，这道题成了最短路模板题。使用单源最短路径求解即可。（注意使用堆优化）如果你发现你 TLE 了，请把你的输如输出改成 scanf 和 printf，我就是赛时使用标准 IO 然后遗憾地只有 $40$ 分。使用快速 IO 也是一个良好习惯。

## 参考代码


```cpp
#include<bits/stdc++.h>
#define N 1000005
#define inf 100000005
using namespace std;
int n,m,s,t,vis[N],dis[N];
vector<int>g[N];
struct node{
	int to,val;
	friend bool operator <(node a,node b)
	{
		return a.val>b.val;
	}
};
priority_queue<node>q;
void solve()
{
	for(int i=1;i<=n;i++)
	dis[i]=inf;
	dis[s]=0;
	q.push({s,0});
	for(int i=1;i<=n;i++)
	{
		while(vis[q.top().to])q.pop();
		int u=q.top().to;
		q.pop();
		vis[u]=1;
		for(int j=0;j<g[u].size();j++)
		{
			int v=g[u][j];
			if(dis[v]>dis[u]+1)
			{
				dis[v]=dis[u]+1;
				q.push({v,dis[v]});
			}
		}
	}
}
int main()
{
	cout<<"I'm here!"<<endl;
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	solve();//堆优化 dij
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(dis[x]>dis[y])printf("Jom\n");
		else printf("Terry\n");
	}//愉快地判断 dis
	return 0;
}
```

---

## 作者：abc1856896 (赞：1)

S组炸了，遂写篇简单题题解。

# Solution

显然如果能 Jom 比 Terry 早到根节点，那么 Tom 就可以一直守在那里并且获胜。

再考虑如果 Jom 不能比 Terry 早到根节点的情况。

我们充分发挥人类智慧，猜测结论是 Terry 赢。

证明：首先 Terry 和 Jom 必然都会按最短路走。那么 Terry 和 Jom 的情况就只有以下两种：

![](https://cdn.luogu.com.cn/upload/image_hosting/msp3r7ux.png)

这种情况下必然双方都会直接往上走。由于 Terry 先手，所以 Terry 必然先到根，获胜。

![](https://cdn.luogu.com.cn/upload/image_hosting/9jd7ewyh.png)

这种情况下双方也都会直接按最短路径往上走。因为 Jom 不能比 Terry 早到根节点，所以 Jom 必然追不上 Terry，证毕。

上面两个图都是只含有最短路相关的边。

跑最短路后判断 $dis_a \le dis_b$ 输出即可。

时间复杂度 $O(m+n \log n + T)$。

# Code


```cpp
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>n>>m>>s;
for(int i=1;i<=m;i++) {
	int u,v;
	cin>>u>>v;
	add_edge(u,v,1);
	add_edge(v,u,1);
}
dijkstra(s);
cin>>T;
cout<<"I'm here!\n";
while(T--) {
	int l,r;
	cin>>l>>r;
	if(dis[l]<=dis[r]) cout<<"Terry\n";
	else cout<<"Jom\n";
}
```

---

## 作者：cwd2023 (赞：1)

# P11280题解
### by cwd2023
---
吐槽：黑题爆改黄题([原题](https://www.luogu.com.cn/problem/P7353))。
### 思路：
1. 什么情况下先手会被拦住？当然是后手在先手经过的最短路径上提前等待，而且如果在终点提前等待一定能抓住。
2. 会不会先手不走最短路（绕一下）还能躲过抓捕？不会，因为后手如果可以在先手走最短路的情况下先到终点，那么先手不走他也能提前到达。
   
所以就是比较先手和后手那个离终点更近 。

再次吐槽：卡常神题！dij 的 $O(n\log{n})$ 会被卡，正常输入输出也卡，一百分直接变四十，所以必须用 BFS 加快读。

---

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,r,p;
vector<ll>e[1000010];
ll dis[1000010]; 
bool vis[1000010];
ll read(){
	ll x=0,w=1;
	char ch=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return x*w;
}
struct node{
	ll u,d;
	//	bool operator<(const node&cur)const{
	//		return d>cur.d;
	//	}
};
queue<node>q;
inline void dij(ll s){
	for(ll i=1;i<=n;i++)dis[i]=1e18;
	dis[s]=0;
	q.push({s,0});
	while(q.size()){
		ll u=q.front().u;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(auto v:e[u]){
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				if(!vis[v])q.push({v,dis[v]});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cout.tie(0),cin.tie(0);
	cout<<"I'm here!\n";
	n=read(),m=read(),r=read();
	for(ll i=1;i<=m;i++){
		ll u,v;
		u=read(),v=read();
		if(u==v)continue;
		e[u].emplace_back(v),e[v].emplace_back(u);
	}
	dij(r);
	p=read();
	while(p--){
		ll a,b;
		a=read(),b=read();
		(dis[a]<=dis[b]&&dis[a]!=1e18)?cout<<"Terry\n":cout<<"Jom\n";
	}
	return 0;
}
```

最后，希望本篇题解对你有所帮助，感谢观看。
### 望管理员通过！

---

## 作者：__lu114514ljh__ (赞：0)

## P11280 「GFOI Round 2」Jom & Terry 题解

显然如果能 Jom 比 Terry 早到根节点，那么 Jom 就可以一直守在那里并且获胜。

Jom 为了抓到 Terry 一定会沿着开始点到根的最短路走。而 Terry 为了不被抓到，肯定也要尽快到达根，所以双方都会选择最短路走。所以我们跑完最短路后，对于每组询问判断如果 $dis_a < dis_b$ 时，Terry 赢，否则 Jom 赢。


时间复杂度 $O(m+n \log n + T)$。

---

## 作者：anke2017 (赞：0)

## 思路

容易发现，如果 Terry 需要比 Jom 更多的步数才能到达 $r$ 点，那么 Jom 可以堵在 $r$ 点（直接走过去），从而使得 Terry 不能到达 $r$ 点。

但 Terry 需要的步数小于等于 Jom 时呢？

假设 Terry 前往 $r$ 点的最短路径中，第二个节点（即第一步的节点）为 $c$，那么显然 Jom 不在这个节点上（否则与 Terry 需要步数小于等于 Jom 矛盾），即 Terry 的这一步一定合法。而 Jom 不管怎么走，都无法**先**移动到 $r$ 或 Terry 的必经节点上（否则也与 Terry 需要步数小于等于 Jom 矛盾），所以 Terry 一定能走到 $r$。

所以判断 Terry 所在点和 Jom 所在点到 $r$ 的最短距离就行了。最短路径可以用 $O(m \log m+q)$ 的 dijkstra 或 $O(n+m+q)$ 的 BFS。这里选用前者。

代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

vector<int> e[1000001];
int dij[1000001];
int n,m,r;

struct node
{
	int now,num;
	bool operator <(const node tmp)const
	{
		return num>tmp.num;
	}
};

void dijk()//dijkstra 算法
{
	memset(dij,0x3f,sizeof(dij));
	dij[r]=0;
	priority_queue<node> q;
	q.push({r,0});
	while(!q.empty())
	{
		node tmp=q.top();
		q.pop();
		if(dij[tmp.now]<tmp.num)continue;
		for(int i=0;i<e[tmp.now].size();i++)
		{
			if(dij[e[tmp.now][i]]>dij[tmp.now]+1)dij[e[tmp.now][i]]=dij[tmp.now]+1,q.push({e[tmp.now][i],dij[tmp.now]+1});
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	cout<<"I'm here!\n";//签到
	cin>>n>>m>>r;
	for(int i=1;i<=m;i++)
	{
		int t1,t2;cin>>t1>>t2;
		e[t1].emplace_back(t2);
		e[t2].emplace_back(t1);
	}
	dijk();
	int q;cin>>q;
	for(int i=1;i<=q;i++)
	{
		int t1,t2;cin>>t1>>t2;
		if(dij[t1]<=dij[t2])cout<<"Terry\n";//注意小于等于
		else cout<<"Jom\n";
		//cout<<dij[t1]<<' '<<dij[t2]<<'\n';
	}
	return 0;
}
```

---

## 作者：emo_zkt (赞：0)

这道题有点坑。

我刚开始以为这是树，后来才发现这是图，呜呜呜，虽然但是，这哪怕真是树，LCA 也不如 BFS，因为针对这道题，太慢了。

BFS 板子题，统计根节点到每个节点的最小距离，然后针对每次询问，直接比较与根节点距离，距离小的就是胜者，但要注意的是如果双方距离一样，是 Terry 获胜。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,s,head[N],tot=-1,vis[N],dis[N],t;
struct nod{
	int to,ne;
}e[2*N];
queue<int>q;
void add(int x,int y){
	e[++tot].to=y;
	e[tot].ne=head[x];
	head[x]=tot;
}
int main(){
	memset(head,-1,sizeof head);
	printf("I'm here!\n");
	int n,m,r;
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	q.push(r);
	dis[r]=0,vis[r]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=e[i].ne){
			int v=e[i].to;
			if(!vis[v]){
				q.push(v);
				vis[v]=1;
				dis[v]=dis[u]+1;
			}
		}
	}
	cin>>t;
	while(t--){
		int a,b;
		scanf("%d%d",&a,&b);
		if(dis[a]<=dis[b])printf("Terry\n");
		else printf("Jom\n");
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/P11280)

### 题目分析

由于可以在每次操作时不选择移动，则 Jom 获得胜利只需在 Terry 之前到达点 $r$ 即可。

用 bfs 得出 Terry 和 Jom 离根的距离即可。由于 Terry 先手，当 Jom 距根更近时才能获胜。

### 参考代码


```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
};
int n,m,r;
vector<int>e[1000005];
int f[1000005];
queue<node>q;
void bfs()
{
	f[r]=1;
	q.push(node{r,1});
	while(!q.empty())
	{
		node h=q.front();
		q.pop();
		for(auto i:e[h.x])
		{
			if(f[i])f[i]=min(f[i],h.y+1);
			else f[i]=h.y+1,q.push(node{i,h.y+1});
		}
	}
}
int main()
{
	printf("I'm here!");
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	bfs();
	int q;
	scanf("%d",&q);
	for(int i=1,u,v;i<=q;i++)scanf("%d%d",&u,&v),printf("\n"),printf(f[u]>f[v]?"Jom":"Terry");
	return 0;
}
```
感谢阅读。

---

## 作者：MnZnOIer (赞：0)

考场上一眼秒了，个人认为可以放 T1 的。

### 解题思路
我们可以发现，如果 Terry 能够先到达根，Terry 就赢了；如果 Jom 先到，他就可以在根节点睡觉，Terry 就不可能到达根了。

这个结论是显而易见的，所以我们可以处理每个点到根的最短时间，我用的是 bfs 分层图，取层数最少的。但是这个复杂度貌似是假的，因为遇到能更新的深度更小的点，会把它接下来的所有能到达的点重新更新。希望评论区能给出证明这个算法的时间复杂度。

当 Terry 的深度 $\le$ Jom 的深度时，Terry 可以先到达根节点，否则 Jom 先到达根节点。

### 代码部分
给出 bfs 部分的代码：
```cpp
queue <int> q;
dep[r] = 0;
while (! q.empty ())q.pop ();
q.push (r);
while (! q.empty ())
{
	int d = q.front ();
	q.pop ();
	for (int i = h[d]; i; i = e[i].nxt)
	{
		int y = e[i].v;
		if (dep[d] + 1 < dep[y])//可以更新深度。
		{
			dep[y] = dep[d] + 1;
			q.push (y);//更新并入队。
		}
	}
}
```

---

