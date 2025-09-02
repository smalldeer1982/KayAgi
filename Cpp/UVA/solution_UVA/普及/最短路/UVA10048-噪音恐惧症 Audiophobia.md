# 噪音恐惧症 Audiophobia

## 题目描述

**题意描述**


有一张有$C$个路口，$S$条街道的无向图，每条街道都一个噪音值。

请问从$c_1$走到$c_2$，经过的路径上最大噪音的最小值是多少。

## 样例 #1

### 输入

```
7 9 3
1 2 50
1 3 60
2 4 120
2 5 90
3 6 50
4 6 80
4 7 70
5 7 40
6 7 140
1 7
2 6
6 2
7 6 3
1 2 50
1 3 60
2 4 120
3 6 50
4 6 80
5 7 40
7 5
1 7
2 4
0 0 0```

### 输出

```
Case #1
80
60
60

Case #2
40
no path
80```

# 题解

## 作者：Law_Aias (赞：4)

这是一道很神奇的题，什么都不卡，就卡c++11（~~所以评测时要换成c++~~）。
怎么说呐，其实就是跑一个弗洛依德，求图上两点间最大权值最小的路径，输出最大权值最小。
~~P.S.本题n很小，直接floyd变形就行了qwq~~

```
#include<cstdio>
#include<cstring>
#include<iostream>

#define N 105

using namespace std;

const int INF = 0x3f3f3f3f;

int g[N][N], t = 1, que, n, m;

void floyd() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				int maxx = g[i][k] < g[k][j] ? g[j][k] : g[i][k];
				if (g[i][j] > maxx)
					g[i][j] = maxx;
			}
}

int main() {
	while (scanf("%d%d%d", &n, &m, &que) && n || m || que) {
		memset(g, INF, sizeof(g));
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &a, &b, &c);
			g[a][b] = g[b][a] = c;
		}
		floyd();
		int sta, end;
		if (t != 1)
			printf("\n");
		printf("Case #%d\n");
		t++;
		while (que--) {
			scanf("%d%d", &sta, &end);
			if (g[sta][end] < INF)
				printf("%d\n", g[sta][end]);
			else
				printf("no path\n");
		}
	}
	return 0;
}
```
~~不要问我为什么有这么多空格，其实我也不知道为什么！！！~~

---

## 作者：MY_Lee (赞：3)

#### 闲聊
> 若要去做 UVA，一流英语先准备。

#### 题意

就是说给你一个无向图，多次求从 $u$ 到 $v$ 的最短路。其中 点数 $\le 100$，边数 $\le1,000$，询问数 $\le 10,000$。

#### 思路

弄清楚了题意，看清楚了数据范围，思路就不需要多讲了吧。一看到点数 $\le100$，我们就可以用~~简单粗暴~~的 $\mathrm{Floyd}$ 来解决。

$\mathrm{PS}$：接下来的讲解，请会 $\mathrm{Floyd}$ 的同志们立刻跳到后面的环节吧。

---
我来给没学过 $\mathrm{Floyd}$ 最短路的童鞋补上一课罢。

$\mathrm{Floyd}$ 的主要思想，其实还是贪心。我们先来看张图：

![松弛1](https://cdn.luogu.com.cn/upload/image_hosting/14h3g6jl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这张无向图里， $1\rightarrow3$ 的直接连接距离是 $3$，但是 $3$ 并不是最短路：我们可以通过 $2$ 号点中转，先从 $1\rightarrow2$ 再从 $2\rightarrow3$，这样的距离就是 $1+1=2$ 为最短路了。

$\mathrm{Floyd}$ 就是这样的思想，第一层循环枚举那个中转的点，第二层和第三层枚举出发点和结束点。然后是我们的重点：
> 如果出发点到中转点的距离 + 中转点到结束点的距离 $\le$ 出发点到街书店的距离，那就更新。

写成伪代码，应该是这样滴：

```plain
for(int i=1->n)
	for(int j=1->n)
   		for(int k=1->n)
			dis(j,k)=min(dis(j,k),dis(j,i)+dis(i,k));
    
```
---
但是这道题并不能只敲板子，因为他要求的是路径上的最大值。不过根据上面的思想，我们只需要写为：
```plain
dis(j,k)=min(dis(j,k),max(dis(j,i),dis(i,k)))
```
就是正解啦。~~是不是很简单啊？~~
另外注意**多组数据**还有坑死人的的输出：每个数据后要**多输出一个换行**。

---
#### 代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm> 
using namespace std;
long long dis[105][105],street,rode,que,s,d,c,cnt=1,x,y;
int main(){
	while(scanf("%lld%lld%lld",&street,&rode,&que)==3){
		if(street==0&&rode==0&&que==0){
			return 0;
		}
		if(cnt!=1){
			printf("\n");
		}//要多输出一个换行
		for(int i=1;i<=street;i++){
			for(int j=1;j<=street;j++){
				dis[i][j]=2147483647;
			}
			dis[i][i]=0;
		}//初始化
		for(int i=0;i<rode;i++){
			scanf("%lld%lld%lld",&s,&d,&c);
			dis[s][d]=min(dis[s][d],c);
			dis[d][s]=min(dis[d][s],c);
		}//注意有可能会有重边，所以要最小值
		for(int i=1;i<=street;i++){
			for(int j=1;j<=street;j++){
				for(int k=1;k<=street;k++){
					if(dis[j][i]!=2147483647&&dis[i][k]!=2147483647&&dis[j][k]>max(dis[j][i],dis[i][k])){
						dis[j][k]=max(dis[j][i],dis[i][k]);
					}
				}
			}
		}//Floyd
		printf("Case #%lld\n",cnt);//格式输出
		cnt++;
		for(int i=0;i<que;i++){
			scanf("%lld%lld",&x,&y);
			if(dis[x][y]==2147483647){
				printf("no path\n");
			}
			else{
				printf("%lld\n",dis[x][y]);
			}
		}
	}
	return 0;
}
```
---
#### 番外
感谢大家的收看！

如果有空，记得来[我的博客](https://moon-snow.blog.luogu.org/)转一转罢！

---

## 作者：w23c3c3 (赞：3)

这边有个$Floyd$的，那我来个$dijkstra$吧。               
$dijkstra$方法介绍：                                 
将一个结点记为起点，则该点与自己的距离为0。我们针对map数组进行求最小值，将这个最小值进行扩散（即松弛操作，将它能到的点（未松弛过）的距离$map[x]+f[x][y]$与原来的$map[y]$作比较，就能得到更近的距离），并将它标记为“已搜索过”。这样最多松弛$n$次，所以复杂度为$O(n^2)$，由于对每一个点都要做一遍，所以时间为$O(n^3)$。                   
$dijkstra$的方法推理：                               
因为权值为正，所以现在的最小值已经不可能从别的点继承过来，所以我们可以将它保存起来。但别的点可能可以从最小值转过来，所以要对其他点进行松弛操作。                 
$dijkstra$的盲区：                                   
当图中有负权值时，原来的最小值并不一定不能从别的点过来，所以，$dijkstra$只能以$O(n^2)$的时间解决无负权值的图的最小值。而有负权的就交给$Floyd$和$SPFA$了。       
接下来是代码环节（我太垃圾了，连堆优化和线段树优化都不会）：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,q,t,f[101][101],map[101][101],i,x,y,z,e[101],j,k,v;
int main(){
    read("%d%d%d",&n,&m,&q);//输入
    while(n!=0&&m!=0&&q!=0){
        t++;
        memset(f,1,sizeof f);//初始化 
        for(i=1;i<=m;i++)read("%d%d%d",&x,&y,&z),f[x][y]=z,f[y][x]=z;//邻接矩阵存储
        write("Case #%d\n",t);
        memset(map,1,sizeof map);
        for(i=1;i<=n;i++){//寻找起点
            memset(e,0,sizeof e);
            map[i][i]=0;
            for(j=1;j<=n;j++){
                x=1<<30;
                for(k=1;k<=n;k++)if(map[i][k]<x&&e[k]==0)x=map[i][k],v=k;//找最小值
                e[v]=1;
                for(k=1;k<=n;k++)if(e[k]==0)map[i][k]=min(map[i][k],max(f[k][v],map[i][v]));//松弛操作 
            }
        }
        while(q--){
            read("%d%d",&x,&y);if(x>y)swap(x,y);
            if(map[x][y]==16843009)write("no path\n");else write("%d\n",map[x][y]);//如果没变，只可能是不能到
        }
        read("%d%d%d",&n,&m,&q);
        if(n!=0&&m!=0&&q!=0)write("\n");
    }
}
```
*注：照样有坑

---

## 作者：封禁用户 (赞：2)

# Ad
个人博客升级版高清重制版同步：https://cinema000.xyz/1583.ruby

欢迎评论点赞转发赞赏友链以及洛谷游览团访问。

这篇题解作为一道图论题的题解：

思路流畅，

讲解清晰，

码量偏低，

提醒到位，

是篇不可多得的值得通过题解！
# 分析

这里是广义的Floyd， 把floyd算法中的加法改成$min$，$min$改成$max$即可。

~~算理大概就是最短路径的子路径也是最短路径，不，好像不对，不应该这么说。~~

诶其实这题就是求个通过两点边权最小的路径，这个边权每条边独立的，不累加的。

于是改下floyd就好了。

# 代码

## Hints

注意UVa 输出换行万年老坑

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const int INF = 0x3f3f3f3f;
const int MAXN = 100 + 6;
int G[MAXN][MAXN];

int main(){
	int n,m,q,id = 0;
	while(scanf("%d %d %d",&n,&m,&q) == 3 && n){
		memset(G,INF,sizeof(G));
		int u,v,d;
		while(m--){
			scanf("%d %d %d",&u,&v,&d);
			G[u][v] = G[v][u] = d;
		}
		for(int p = 1;p <= n;p++)
			for(int i = 1;i <= n;i++)
				for(int j = 1;j <= n;j++)
					G[i][j] = std::min(G[i][j],std::max(G[i][p],G[p][j]));
		if(id) printf("\n");
		printf("Case #%d\n",++id);
		while(q--){
			scanf("%d %d",&u,&v);
			if(G[u][v] == INF) printf("no path\n");
			else printf("%d\n",G[u][v]);
		}
	}
	
	return 0;
}
```



---

## 作者：ljcljc (赞：2)

【题目大意】

给定一无向图，每条边都有一个权值，现在给你起点和终点，要求你找出起点到终点途经的边的最大值，要求这个值尽量小，到不了输出no path。

【分析】

这就是一道$floyd$的板子题，但是这道题要把加改成$max$

对于$i$到$j$的路径，一定存在$k$使得$i$到$j$的最大代价等于$max(d[i][k], d[k][j])$,但我们知道$i$到$j$路径并不唯一的，
所以还要取一条最小的：$d[i][j] = min(d[i][j], max(d[i][k], d[k][j]));$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 110;
int n, m, q, G[MAXN][MAXN], T;
int main() {
    while(cin >> n >> m >> q && n) {
        memset(G, 127, sizeof(G)); //初始化
        while(m--) {
            int u, v, x;
            cin >> u >> v >> x;
            G[u][v] = G[v][u] = x; //邻接矩阵存图
        }
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    G[i][j] = min(G[i][j], max(G[i][k], G[k][j])); //floyd的变形
        if(T) cout << '\n';
        cout << "Case #" << ++T << '\n';
        while(q--) {
            int u, v;
            cin >> u >> v;
            if(G[u][v] >= 1e9) cout << "no path\n"; //达不到
            else cout << G[u][v] <<'\n';
        }
    }
    return 0;
}
```


---

## 作者：Bitter_Tea (赞：1)

我的做法是$djikstra$

使最大噪音的值最小，我们很自然地会想到二分。
但是一看数据范围，二分似乎不行。

其实根本没有必要二分，我们可以直接跑一遍最短路得出答案。大体写法和普通的$dijkstra$没有区别，只是在判断的时候进行了小小的修改，$qwq$。

由于每组询问数是$10000$，而$n$只有$100$，所以我们直接跑$n$次$dijkstra$然后$O(1)$回答就可以啦。

~~话说卡换行是什么操作~~

## $Code$
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=105;
struct D{int nxt,to,w;}e[N*20];
int fir[N],tot,d[N][N];
int n,m,Q,t;
priority_queue< pair<int,int> > q;
bool v[N];
void add(int x,int y,int z)
{
	e[++tot].nxt=fir[x];
	e[tot].to=y;
	e[tot].w=z;
	fir[x]=tot;
}
void dij(int x)
{
	memset(v,0,sizeof(v));
	d[x][x]=0;
	q.push(make_pair(0,x));
	while(!q.empty())
	{
		int now=q.top().second;
		q.pop();
		if(v[now]) continue;
		v[now]=1;
		for(int i=fir[now];i;i=e[i].nxt)
		{
			int p=e[i].to;
			if(d[x][p]>max(d[x][now],e[i].w))
			{
				d[x][p]=max(d[x][now],e[i].w);
				q.push(make_pair(-d[x][p],p));
			}
		}
	}
}
void solve()
{
	if(t>1) puts("");
	printf("Case #%d\n",t);
	tot=0;
	memset(fir,0,sizeof(fir));
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	for(int i=1;i<=n;i++) dij(i);
	for(int i=1;i<=Q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(d[x][y]!=0x3f3f3f3f) printf("%d\n",d[x][y]);
		else printf("no path\n");
	}
}
int main()
{
	for(;;)
	{
		t++;
		scanf("%d%d%d",&n,&m,&Q);
		if(n==0&&m==0&&Q==0) break;
		solve();
	}
	return 0;
}
```



---

## 作者：zmza (赞：1)

这题是最短路。

这题不会卡Floyd，所以我们可以使用Floyd算法。

具体看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c,s,q;
int dis[105][105];
void chu()//初始化
{
	for(int i = 1; i <= c; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			dis[i][j] = (i == j) ? 0 : 1e9; //如果i=j，那就dis[i][j]=0。不然就设为一个极大的数
		} 
	}
}
int cnt;
int main()
{
	while(scanf("%d%d%d",&c,&s,&q))//多组数据
	{
		cnt++;
		if(c == 0 && s == 0 && q == 0)
		{
			break;
		}
		chu();//初始化
		for(int i = 1; i <= s; i++)
		{
			int a,b,d;
			scanf("%d%d%d",&a,&b,&d);
			dis[a][b] = d;//邻接矩阵建图
			dis[b][a] = d;
		}
		for(int k = 1; k <= c; k++)
		{
			for(int i = 1; i <= c; i++)
			{
				for(int j = 1; j <= c; j++)
				{
					dis[i][j] = min(dis[i][j],max(dis[i][k],dis[k][j]));//Floyd算法。三重循环。这是求最小的最大
				}
			}
		}
		if(cnt > 1)
			printf("\n");注意输出格式
		printf("Case #%d\n",cnt);
		for(int i = 1; i <= q; i++)//输出
		{
			int a,b;
			scanf("%d%d",&a,&b);
			if(dis[a][b] == 1e9)
			{
				printf("no path\n");//没有答案输出no path
			}
			else
			{
				printf("%d\n",dis[a][b]);//不然就输出dis[a][b]
			}
		}
	}
	return 0;
}
```


---

## 作者：hulean (赞：1)

## 【题意】

输入一个$C$个点$S$条边 $(C<=100)$ $(S<=1000)$的无向带权图，边权表示该路径上的噪声值。当噪声太大时，耳膜可能会收到损伤，所以当你从某点去往另一个点时，总是希望路上经过的噪声最大值最小。输入一些询问，每次询问两个点，求出这两点间最大噪声值最小的路径。输出其最大噪声值

## 【算法】

$Floyd$

## 【分析】

本题的做法十分简单：直接用$Floyd$算法，但是要把$+$改成$min$，$min$改成$max$。

**为什么可以这样做呢？** 大部分题解都没给出证明，这里给出证明过程

- 证明过程

不管是$Floyd$还是$Dijkstra$算法，都是基于这样一个事实：对于任意一条至少包含两条边的路径``i->j``,一定存在某一个中间点``k``使得``i->j``的总长度等于``i->k``与``k->j``的长度之和。对于不同的点``k``，``i->k``和``k->j``的长度之和可能不同，最后还需要取一个最小值才是``i->j``的最短路径。把刚才推理中“之和”与“取最小值”换成“取最小值”和“取最大值”，推理仍然适用

## 【代码】

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,Q;
int g[110][110];
int T;
inline int read()
{
    int tot=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        tot=tot*10+c-'0';
        c=getchar();
    }
    return tot;
}
int main()
{
    n=read();m=read();Q=read();
    while(1)
    {
        T++;
        memset(g,0x3f,sizeof(g));
        for(int i=1;i<=m;i++)
        {
            int x=read(),y=read(),z=read();
            g[x][y]=z;
            g[y][x]=z;
        }
        for(int k=1;k<=n;k++)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    g[i][j]=min(g[i][j],max(g[i][k],g[k][j]));
                }
            }
        }
        cout<<"Case #"<<T<<endl;
        while(Q--)
        {
            int x=read(),y=read();
            if(g[x][y]==0x3f3f3f3f)cout<<"no path\n";
            else cout<<g[x][y]<<endl;
        }
        n=read();m=read();Q=read();
        if(n||m||Q)cout<<endl;
        else break;
    }
    return 0;
}
```

---

## 作者：Sata_moto (赞：0)

### 前言：


[$ \large{}\color {#6495ED} \mathcal{MyBlog} $](https://xjx885.coding-pages.com/)

发现没有人发克鲁斯卡尔重构树的题解诶...

于是过来发一发...

（话说我为什么要给这种规模的题写克鲁斯卡尔重构树啊0.0）

---

### 题目大意：

给定一张无向图，多次求两个点之间路径上最大权值最小是多少...

---

### 题目分析:

Emmm...最大权值最小....果断克鲁斯卡尔重构树0.0...

啥是克鲁斯卡尔重构树？

首先，你得熟练掌握最小生成树中的克鲁斯卡尔算法...

然后，你得知道...无向图的最小生成树一定是最小瓶颈生成树

没理解？出门左转[洛谷日报 克鲁斯卡尔重构树详解](https://www.luogu.org/blog/user9012/ke-lu-si-ka-er-zhong-gou-shu-lve-xie)

我直接说具体操作...

首先，克鲁斯卡尔算法选定一条边E时，加入一个点V，权值为这条边...

把E链接的两个连通块的顶点A,B的父亲设为V，并把A,V和B,V之间连边...

这一操作完毕之后...询问a,b路径上最长边最小值时，直接输出a,b的LCA的权值就好...

具体细节见代码

---

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int C, S, Q;

//克鲁斯卡尔需要的边 
struct node
{
	int a, b, c;

	node (int aa, int bb, int cc)
	{
		a = aa, b = bb, c = cc;
	}
	node () { }

	bool operator < (const node & other ) const
	{
		return c < other.c;
	}
};
vector <node > Link; 

//并查集 
int fa[N * 3]; 
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

//克鲁斯卡尔重构树 
int f[N * 3][10];
int d[N * 3], deep[N * 3];
vector <int > link[N * 3];
int n;

void Kruskal()
{
	sort(Link.begin(), Link.end());

	n = C;

	for(int k = 0; k < (int )Link.size(); k++)
	{
		int a = Link[k].a, b = Link[k].b, c = Link[k].c;

		if(find(a) != find(b))
		{
			int top_a = fa[a], top_b = fa[b];
		
			//把两个连通块的顶点的父亲设为新加节点 
			fa[top_a] = fa[top_b] = ++n;
			
			//把两个连通块的顶点的父亲与新加节点连边 
			link[n].push_back(top_a);
			link[n].push_back(top_b);
			
			//新加节点权值设为该边边权 
			d[n] = c;
		}
	}
}

//倍增LCA预处理 
void dfs(int wz, int fa)
{
	deep[wz] = deep[fa] + 1, f[wz][0] = fa;
	for(int k = 1; k < 10; k++)
		f[wz][k] = f[f[wz][k - 1]][k - 1];

	for(int k = 0; k < (int )link[wz].size(); k++)
	{
		int to = link[wz][k];

		dfs(to, wz);
	}
}

//倍增LCA 
int LCA(int a, int b)
{
	if(deep[a] < deep[b])
		swap(a, b);

	for(int k = 9; k >= 0; k--)
		if(deep[a] - (1 << k) >= deep[b])
			a = f[a][k];

	if(a == b)
		return d[a];

	for(int k = 9; k >= 0; k--)
		if(f[a][k] != f[b][k])
			a = f[a][k], b = f[b][k];

	return d[f[a][0]];
}

int main()
{
	int opt = 0;

	while(scanf("%d %d %d", &C, &S, &Q))
	{
		if(C == 0) break;

		memset(deep, 0, sizeof(deep));
		memset(link, 0, sizeof(link));
		Link.clear();

		if(opt++ != 0)
			printf("\n");

		printf("Case #%d\n", opt);

		for(int k = 1; k <= C * 3; k++)
			fa[k] = k;

		for(int k = 1; k <= S; k++)
		{
			int c1, c2, d;
			scanf("%d %d %d", &c1, &c2, &d);

			Link.push_back(node(c1, c2, d));
		}

		Kruskal();

		for(int k = 1; k <= n; k++)
			if(!deep[k])
				dfs(find(k), 0);

		for(int k = 1; k <= Q; k++)
		{
			int c1, c2;
			scanf("%d %d", &c1, &c2);

			if(find(c1) == find(c2))
				printf("%d\n", LCA(c1, c2));
			else
				printf("no path\n");
		}
	}

	return 0;
}
```


---


### 结语：

如果本题解有BUG...

那么...那么...那么...

（随意了）还请私信作者....

---

## END

---

## 作者：henrytb (赞：0)

## 这是一个Floyd的扩展

就是求图上任意两点之间的使最大边权最小的路径啦QAQ

所以，我们可以稍微对Floyd进行一些微小的改动：

把

```cpp
f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```

改成

```cpp
f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
```

就AC了QAQ

我们这里$f[i][j]$的意思是$i$到$j$的路径中，使噪声最大的路径最小的方案里的噪声最大的路径的权值

正确性证明：类似Floyd，略

附代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,q,now,f[105][105];
int main(){
    while(~scanf("%d%d%d",&n,&m,&q)&&n){
        memset(f,0x3f3f3f3f,sizeof(f));
        rep(i,1,m){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            f[u][v]=w;
            f[v][u]=w;
        }
        rep(k,1,n)rep(i,1,n)rep(j,1,n){
            f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
        }
        if(now)printf("\n");
        printf("Case #%d\n",++now);
        rep(i,1,q){
            int a,b;
            scanf("%d%d",&a,&b);
            if(f[a][b]==0x3f3f3f3f)printf("no path\n");
            else printf("%d\n",f[a][b]);
        }
    }
    return 0;
}
```

---

## 作者：Colin_Lovecraft (赞：0)

这个题实际上是广义的Floyed算法。

思路：
d[i][j]表示从i到j这条路上所有路径中的最大值。
对于i，j两个点和中间点k，首先应该在d[i][k]和d[k][j]之间选最大值，再将这个与d[i][j]比较，取最小值。
将原来的

$d[i][j]=min(d[i][j],d[i][k]+d[k][j])$

修改一下，就像这样：

$d[i][j] = min(d[i][j],max(d[i][k],d[k][j]))$

下面是代码。
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int d[500][500], t = 1, q, n, m,id = 0;
		int a,b,c;

int main(){
	while(scanf("%d %d %d",&n,&m,&q) == 3 && n){
		memset(d,INF,sizeof(d));
	while(m--){
            scanf("%d %d %d",&a,&b,&c);
            d[a][b] = d[b][a] = c;
        }
		for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if((d[i][k] != INF)&&(d[k][j]!= INF))
                d[i][j] = min(d[i][j],max(d[i][k],d[k][j]));
            }
	if(id) printf("\n");
        printf("Case #%d\n",++id);
        while(q--){
            scanf("%d %d",&a,&b);
            if(d[a][b] == INF) printf("no path\n");
            else printf("%d\n",d[a][b]);
        }
	}
    return 0;
}
```
这个题看起来是绿题其实应该没有这个难度。
从这个题我们可以看到Floyed算法其实是很灵活的，有很多的变种。

---

## 作者：swl3992 (赞：0)

由题可知，每两个节点之间都有不同的路径。

本题就是要经过的边的最大边权最小。可以用 Floyd 算法求出。

如果用 $d_{i,j}$ 表示从 i 到 j 要经过的边的最大边权最小值，那么 $d_{ i , j } = min ( d_{i,j} , max( d_{ i , k }, d_{ k , j }))$ .

也就是换成从 i 到 k 再从 k 到 j .

示例代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int d[150][150];	//Floyd 用
int c,s,q;	//意义如题所示
int main()
{
    int Case=0;
    while(cin>>c>>s>>q&&c)
    {
        for(int i=0;i<c;i++)
        {
            d[i][i]=0;	//自己到自己为0（注意此步一定要做）
            for(int j=i+1;j<c;j++)
            {
                d[i][j]=d[j][i]=2147483647;	//手动初始化为最大值
            }
        }
        for(int i=0;i<s;i++)
        {
            int c1,c2,l;
            cin>>c1>>c2>>l;
            c1--,c2--;	//程序中下表从0开始
            d[c2][c1]=d[c1][c2]=min(d[c1][c2],l);	//取最小值
        }
        for(int k=0;k<c;k++)	//Floyd
        {
            for(int i=0;i<c;i++)
            {
                for(int j=0;j<c;j++)
                {
                    if(d[i][k]<2147483647&&d[k][j]<2147483647)	//如果为 inf 不应运算
                    {
                        d[i][j]=min(d[i][j],max(d[i][k],d[k][j]));	//转移
                    }
                }
            }
        }
        if(Case)
        {
            cout<<endl;
        }
        cout<<"Case #"<<++Case<<endl;
        for(int i=0;i<q;i++)
        {
            int c1,c2;
            cin>>c1>>c2;
            c1--,c2--;
            if(d[c1][c2]==2147483647)	//无路径
            {
                cout<<"no path"<<endl;
            }
            else
            {
                cout<<d[c1][c2]<<endl;
            }
        }
    }
    return 0;
}
```


---

