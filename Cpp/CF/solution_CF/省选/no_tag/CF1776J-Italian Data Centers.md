# Italian Data Centers

## 题目描述

An Italian data center consists of a set of servers, each colored green, white, or red, and a set of wires connecting them. Each wire connects two distinct servers and two servers are connected by at most one wire. Additionally, the data center is connected, i.e. there is a way to transmit information between any two servers through a sequence of wires.

To judge all of the contestant submissions, SWERC has an Italian data center. Since every year the number of contestants doubles, the data center needs to grow to adapt to the extra load. To address this, SWERC builds a new data center based on the previous year's one by following these steps:

- For each server $ s $ in the old data center, the new data center contains two servers $ s_1 $ and $ s_2 $ of the same color as $ s $ . A wire is placed connecting the two servers $ s_1 $ and $ s_2 $ .
- For each wire connecting servers $ s $ and $ t $ in the old data center: if $ s $ and $ t $ have the same color, then a wire is placed in the new data center connecting $ s_1 $ and $ t_1 $ and another wire connecting $ s_2 $ and $ t_2 $ ; otherwise, a wire is placed in the new data center connecting $ s_1 $ and $ t_2 $ and another one connecting $ s_2 $ and $ t_1 $ .

One can show that if the old data center is connected than the new data center is also connected.

You are given the Italian data center that SWERC currently has, which contains $ n $ servers (indexed by $ 1, \, 2, \, \dots, \, n $ ) and $ m $ wires connecting them. The organization wants to know how good their data center will be after $ k $ years, so you should determine the diameter of the data center SWERC will have in $ k $ years. The diameter of the data center is the largest distance between any two servers, i.e. the shortest number of wires that have to be used to transmit something between the two servers.

## 说明/提示

In the first sample, the Italian data center is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776J/edef1de79ef9c2bcc14fa6b9446793a11b7afc95.png)The distance between any pair of servers is $ 1 $ so the diameter is $ 1 $ .

In the second sample, the initial Italian data center is the one from the first sample.

After one year we obtain the following (where the numbers indicate which copy the server refers to):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776J/96e3dbdfc8bf00194f5d2319faba41b041835e86.png)Consider the highlighted servers. The distance between them is $ 2 $ and there is no pair of servers with greater distance, so the diameter is $ 2 $ .

In the third sample, the data center after one year is the following:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776J/a96277ee314484355b46cdfb9d1cc6a393a91723.png)After one more year:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1776J/d0968ccb87bd991cd5e5178c9ccb249aadafc5d9.png)Consider the highlighted servers. The distance between them is $ 3 $ and there is no pair of servers with greater distance, so the diameter is $ 3 $ .

## 样例 #1

### 输入

```
3 3 0
1 2 3
1 2
2 3
3 1```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3 1
1 2 3
1 2
2 3
3 1```

### 输出

```
2```

## 样例 #3

### 输入

```
3 3 2
1 2 1
1 2
2 3
3 1```

### 输出

```
3```

## 样例 #4

### 输入

```
8 14 100
3 3 2 2 1 2 2 1
2 7
1 5
7 8
4 6
2 8
1 8
2 6
6 7
1 6
1 4
3 5
1 3
4 5
5 7```

### 输出

```
53```

# 题解

## 作者：幽云蓝 (赞：4)

来写一波口胡过程。

可以发现，假设图只有一个点，那么我们去画这个图的 $k$ 拓展。一开始是一个点，然后是一条边，然后是一个方形的圈，再然后是一个立方体。可以观察到，一个点的 $k$ 拓展实际可以看做一个 $k$ 维超立方体。那么我们已经能对一个点求出答案了——从超立方体的“一角”（即 $00\dots0$，从二进制视角看的话）走到“另一角”（即 $11\dots1$，从二进制视角看的话），答案恰好是 $k$。

再想想，如果所有点都是同一个颜色，那么事实上对于任意两超立方体 $u,v$ 的两点 $p,q$ 的最短路，我们都可以在 $u$ 中直接从 $p$ 走到 $q$，然后再顺着原图的边从 $u$ 走到 $v$。答案就是 $k$ 加上原图的直径。

然后接下来考虑异色怎么办。手摸一下，发现走两次异色，正好能回到原点，走一次异色，正好能走到对角（事实上从二进制视角来说就是 $01$ 翻转，比如 $010$ 的对角就是 $101$）。那么我们依旧考虑对任意两超立方体 $u,v$ 的两点 $p,q$ 的最短路。如果 $u$ 到 $v$ 同时存在走奇数和偶数次的路径，那么从 $p$ 到 $q$ 就出现了两种方案：从 $p$ 走到 $q$，然后再从 $u$ 到 $v$，图中经过偶数次异色；从 $p$ 走到 $q$ 的对角 $q'$，然后再从 $u$ 到 $v$，图中经过奇数次异色。一种简单的实现方式是枚举 $p$ 和 $q$ 的二进制位存在几位不同（因为我们只需要关心这个），然后对所有方案求个 $\min$ 就行。当然，如果只存在一种类型的路径那最短路就是 $k+\text{dis}(u,v)$。

---

## 作者：Kelvin2009 (赞：3)

只是一道几何分析加全源最短路。

首先，考虑对**单个点**的分裂状态。

将一个点分裂后的第一个点记为该点的 0 号，第二个点为 1 号。

则 $k$ 天后一个点 $u$，会分裂出 $2^{k}$ 个点。设 $s$ 为 $t$ 天后的某个状态，对 $t+1$ 天，新分裂的 $u_{\overline{s0}}$ 与 $u_{\overline{s1}}$ 会连一条边。再分裂，$u_{\overline{s00}}$ 与 $u_{\overline{s01}}$ 连边，$u_{\overline{s10}}$ 与 $u_{\overline{s11}}$ 连边。

可以发现，两个点的状态标号在只有其中某一位上不同时，才会连边。这实际上是一个 $k$ 维超立方体。

建议参考[这篇](https://blog.csdn.net/qq_39378221/article/details/107420496)

一个超立方体上可以被经过的最长的最短路长为 $k$，因为每移动到相邻的点上，至多能改变一个二进制位。从向量 $(x_1,x_2,\cdots,x_k)$ 至 $(1-x_1,1-x_2,\cdots,1-x_k)$ 最短路最长，恰为 $k$。

其次，考虑**两个超立方体**之间的连边。

由于是最短路，在单个超立方体上的移动至多进行一次，最大为 $k$，相当于跨越了一半的超立方体。因此一个点可以简化为 0,1 两个状态，两点互相对顶（最长的最短路在单个超立方体上一定移动了最多）。

对于连边：颜色相同的超立方体在每次二进制位延展（从第 $k$ 至第 $k+1$ 天）时，会把两个超立方体延展的那位相等的两个顶点连边，因此只有两点最终状态相同（初始就两个 0 维原点，类似数学归纳法）时相连。反之，颜色不同就只有两点最终状态互补时相连。

一个点简化为了两个状态，可以用 floyed 求出各个点两两之间的最短路。

寻找最长的最短路，可以先找最长的最短环，再破为两半。固定一个顶点 $u$，对于超立方体 $v$，其中最长环为三段：从 $u$ 分别到 $v$ 上两对顶点的两端距离，及两对顶点间的距离。前两段距离由 floyed 求出，最后的那段最优取 $k$。

---

代码：


---


```cpp
#include<bits/stdc++.h>
using namespace std;

const int range=605;

const int lim=0x3f3f3f3f;

int n,m,k;

int c[range];

int grab[range][range],ans;

inline int get(int u,bool op)
{
	return op*n+u;
}

int main()
{
	memset(grab,lim,sizeof(grab));
	
	scanf("%d%d%d",&n,&m,&k);
	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		grab[i][i]=grab[get(i,1)][get(i,1)]=0;
		grab[get(i,1)][i]=grab[i][get(i,1)]=k;
	}
	
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(c[u]==c[v]) 
		{
			grab[get(u,0)][get(v,0)]=grab[get(v,0)][get(u,0)]=1;
			grab[get(u,1)][get(v,1)]=grab[get(v,1)][get(u,1)]=1;
		}
		else
		{
			grab[get(u,0)][get(v,1)]=grab[get(v,0)][get(u,1)]=1;
			grab[get(u,1)][get(v,0)]=grab[get(v,1)][get(u,0)]=1;
		}
	}
	
	int ran=2*n;
	
	for(int kk=1;kk<=ran;kk++)
	{
		for(int i=1;i<=ran;i++)
		{
			for(int j=i+1;j<=ran;j++)
			{
				grab[j][i]=grab[i][j]=min(grab[i][j],grab[i][kk]+grab[kk][j]);
			}
		}
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans=max(ans,(grab[i][get(j,0)]+grab[i][get(j,1)]+k)/2);
		}
	}
	
	printf("%d",ans);
	
	return 0;
}
```

---

## 作者：Leasier (赞：2)

考虑最后的图是啥形态的。

不难发现每个点都会变成 $2^k$ 个点，考虑将这些点按每次分裂为 $s_1$ 还是 $s_2$ 进行二进制编号，手玩一下会发现：

- 新图中有边 $((u, s_1), (u, s_2))$ 当且仅当 $s_1, s_2$ 恰好有一位不同。

这个东西也可以理解为 $k$ 维超立方体。

接下来我们考虑原图中相邻点直接的连边。手玩一下会发现：

- 当 $c_u = c_v$，新图中有边 $((u, s_1), (v, s_2))$ 当且仅当 $s_1 = s_2$。
- 当 $c_u \neq c_v$，新图中有边 $((u, s_1), (v, s_2))$ 当且仅当 $s_1 = rev(s_2)$。

接下来考虑如何求两点间的最短路。

感性理解一下，中间不在一个点上绕圈而只可能在终点绕圈显然是不劣的。

设我们现在讨论 $(u, s_1), (v, s_2)$，则有两种情况：

- 中间走过了偶数条 $c_u \neq c_v$ 的边，最后在 $v$ 上绕圈。
- 中间走过了奇数条 $c_u \neq c_v$ 的边，最后在 $v$ 上绕圈。

bfs 求出走过偶 / 奇数条边到达指定点的最短路，求答案时直接枚举 $s_1, s_2$ 之间不同元素数量即可。时间复杂度为 $O(nm + n^2 k)$。

代码：
```cpp
#include <iostream>
#include <queue>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt = 0;
int c[107], head[107], dis[107][7];
Edge edge[9907];
queue<pair<int, int> > q;

inline void init(int n){
	for (int i = 1; i <= n; i++){
		dis[i][0] = dis[i][1] = 2e9;
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline void bfs(int start){
	dis[start][0] = 0;
	q.push(make_pair(start, 0));
	while (!q.empty()){
		int dis_i;
		pair<int, int> pr = q.front();
		q.pop();
		dis_i = dis[pr.first][pr.second] + 1;
		for (int i = head[pr.first]; i != 0; i = edge[i].nxt){
			int x = edge[i].end, y = pr.second ^ (c[pr.first] == c[x] ? 0 : 1);
			if (dis[x][y] == 2e9){
				dis[x][y] = dis_i;
				q.push(make_pair(x, y));
			}
		}
	}
}

int main(){
	int n, m, k, ans = 0;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++){
		cin >> c[i];
	}
	for (int i = 1; i <= m; i++){
		int s, t;
		cin >> s >> t;
		add_edge(s, t);
		add_edge(t, s);
	}
	for (int i = 1; i <= n; i++){
		init(n);
		bfs(i);
		for (int j = 1; j <= n; j++){
			for (int x = 0; x <= k; x++){
				ans = max(ans, min(dis[j][0] + x, dis[j][1] + (k - x)));
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

给一种 $O(nm)$ 的做法。

$k$ 次拓展后明显形成一个点数 $2^k$ 的超立方体，将其中的每个点表示成一个长度为 $k$ 的二进制串，第 $i$ 位表示第 $i$ 此拓展中该点为 $s1$ 还是 $s2$，对于 $k$ 次拓展的图有优秀的性质。

以下将两个端点颜色不同的边称为异色边，否则称为同色边。

1. 走一条异色边相当于把二进制串按位取反。
2. 走一条同色边二进制串不变。
3. 走一条超立方体内部的边相当于把一位按位取反。

同时也不难发现，我们只在终点的时候才走超立方体内部的边一定不劣。

一个自然的思路是，我们求出两两点对之间恰走奇数条异色边和恰走偶数条异色边的最短路，对之分讨一下解决。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
#define cin Fastio :: cin
#define cout Fastio :: cout

const int N=1e5+10;
const int Max=2e3+10;
const int inf=1e9+1e7;
struct node{int to,typ;node(int to=0,int typ=0):to(to),typ(typ){;}};
int n,m,k,ans,dis[2][Max],c[N];
vector < int > v[N];
queue < node > Q;

inline void BFS(int s){
	for(int i=1;i<=n;++i) dis[0][i]=dis[1][i]=inf;
	Q.push(node(s,0));dis[0][s]=0;
	while(!Q.empty()){
		int x=Q.front().to,op=Q.front().typ;Q.pop();
		for(int i:v[x]){
			int tmp=op^(c[x]!=c[i]);
			if(dis[tmp][i]!=inf) continue;
			dis[tmp][i]=dis[op][x]+1;
			Q.push(node(i,tmp));
		}
	}
	for(int i=1;i<=n;++i){
		int tmp1=min(dis[0][i],dis[1][i]);
		int tmp2=max(dis[0][i],dis[1][i]);
		if(dis[0][i]==inf||dis[1][i]==inf){ans=max(ans,tmp1+k);}
		else {
			int d=max(0,k-(tmp2-tmp1));
			if(d) ans=max(ans,tmp2+d/2);
			else ans=max(ans,tmp1+k);
		}
	}
}

int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i) cin>>c[i];
	for(int i=1,x,y;i<=m;++i){
		cin>>x>>y;
		v[x].emplace_back(y);
		v[y].emplace_back(x);
	}
	for(int i=1;i<=n;++i) BFS(i);
	cout<<ans<<endl;
	return 0;
} 
```

---

