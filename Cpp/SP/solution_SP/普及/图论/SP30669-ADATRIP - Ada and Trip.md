# ADATRIP - Ada and Trip

## 题目描述

瓢虫 Ada 热爱旅游。她一边拍照，买纪念品，一边周游世界。这星期她去了布干达。普通游客会选择在主城区和一些大都市游玩。但是 Ada 不这么认为。她想走尽可能远的路（因为远离市中心的地方所拍摄的照片更有价值）。

问题来了，布干达非常大，她几乎猜不着哪个城市离她最远（通过最短路）。幸运的是，你在她身旁，于是，她向聪明博学的你发出了求救。你能告诉她最远的城市距离她的距离，以及有多少个这样的城市吗？

## 说明/提示

距离每个询问城市最远的城市编号如下：
```plain
0
2 3
3
2
8
4 8
4 8
4 8
4
4 8
```

## 样例 #1

### 输入

```
10 10 10
1 1 1
1 2 1
1 2 3 
3 1 1
5 4 10
8 5 10
5 6 5
6 7 3
6 9 3
9 7 4
0
1
2
3
4
5
6
7
8
9```

### 输出

```
0 1
1 2
2 1
2 1
20 1
10 2
15 2
18 2
20 1
18 2```

# 题解

## 作者：Anaxagoras (赞：5)

Update:2022.08.09 增加了 SPFA 的优化。

Update:2022.09.17 更新了云剪切板，把可恶的负权环删了。

[题目传送门](https://www.luogu.com.cn/problem/SP30669)

## 0xff 前言

这里将介绍四种最短路算法，其中三种单源最短路算法（Dijkstra，Bellman-Ford，SPFA），一种多源最短路（Floyed-Warshall）算法。但只有两种可以过。本人喜欢 Dijkstra，所以本人用的是 Dijkstra。

## 0x00 Floyed-Warshall（简称 Floyed）

### 0x01 什么是 Floyed？

Floyed 是一种多源最短路算法，可以计算任意两个点的最短路距离。

### 0x02 Floyed 的算法思路及其本质？

Floyed 的算法思路为：依次枚举中转点、起点、终点进行松弛，所以 Floyed 的算法本质是动态规划。

### 0x03 Floyed 的缺陷？

无（如果不算时空复杂度的话）。

### 0x04 Floyed 的时空复杂度及其优化？

Floyed 设的状态为：`dis[i][j]` 表示从点 `i` 到点 `j` 的最短路距离，所以 Floyed 的空间复杂度为 $\Theta(n^2)$。由于有三层循环依次枚举中转点、起点、终点，所以 Floyed 的时间复杂度为 $\Theta(n^3)$，所以对于本题，时间复杂度绝对过不了。

关于 Floyed 的优化，本蒟蒻暂时不知道（知道的可以私信或评论）。

## 0x10 Dijkstra

### 0x11 什么是 Dijkstra？

Dijkstra 是一种单源最短路算法，可以计算从一个点开始到其它所有点的最短路距离。

### 0x12 Dijkstra 的算法思路及其本质？

Dijkstra 的思路为：每次从所有点中选出未被标记且距离源点最近的点，将其标记，并把与其相连的点松弛，所以 Dijkstra 算法本质为贪心。

### 0x13 Dijkstra 的缺陷？

Dijkstra 不能处理**大部分**有负边权的图，为避免篇幅过长，已放入[云剪切板](https://www.luogu.com.cn/paste/93qg0oa6)中。

### 0x14 Dijkstra 的时空复杂度及其优化？

Dijkstra 的所有数组都是一维的，所以空间复杂度为 $\Theta(n)$，朴素的 Dijkstra 是要枚举每一点进行比较，一共是 $\Theta(n)$，再加上最外层枚举每一个点的循环，就是 $\Theta(n^2)$。这样的复杂度是绝对过不了的。

但为什么我还能过呢？因为 Dijkstra 可以进行堆优化。不知道堆的出门右转[百度](https://baike.baidu.com/item/%E5%A0%86/20606834?fr=aladdin)，这里不予解释。由于取出堆顶以及入队的复杂度为 $\Theta(1)$，堆排序的复杂度为 $\Theta(\log n)$ ,所以时间复杂度就降为了 $\Theta(n\log n)$，对于本题，能过。

## 0x20 Bellman-Ford（简称 Ford）

### 0x21 什么是 Ford？

Ford 是一种单源最短路算法，可以计算从一个点开始到其它所有点的最短路距离。

### 0x22 Ford 的算法思路及其本质？

Ford 的思路为：枚举每一个点以及每一条边进行松弛操作。本质就是通过松弛求最短路

### 0x23 Ford 的缺陷？

Ford 在存在负权环的图中无法结束执行，因为可以不断进行松弛操作。但这好像也是一个好处，我们可以用 Ford 来判断是否有负权环。

### 0x24 Ford 的时空复杂度及其优化

Ford 的所有数组都是一维的，所以 Ford 的空间复杂度为 $\Theta(n)$。由于 Ford 两层循环分别枚举所有点以及所有边，所以 Ford 的时间复杂度为 $\Theta(nm)$，所以对于本题过不了。

Ford 也有优化，可以使用队列进行优化，这就是我们接下来介绍的 SPFA。

## 0x30 SPFA

### 0x31 什么是 SPFA？

SPFA 是 Bellman-Ford 的队列优化，国际上通称“队列优化的 Bellman-Ford 算法”，只在中国流行 SPFA 的称呼。SPFA 是一种单源最短路算法，可以计算从一个点开始到其它所有点的最短路距离。

### 0x32 SPFA 的算法思路及其本质？

SPFA 的思路为：从源点开始，每当对一条边进行了松弛操作，只要另一个端点不再队列中，就将其入队。由于 SPFA 是 Ford 的优化，所以本质就是 Ford。

### 0x33 SPFA 的缺陷？

由于 SPFA 是 Ford 的优化，所以 SPFA 的缺陷同 Ford。SPFA 还有一个缺陷，就是会在网格图中被卡（下面会讲）。

### 0x34 SPFA 的时空复杂度及其优化

SPFA 的所有数组都是一维的，所以 SPFA 的空间复杂度为 $\Theta(n)$。由于每一条边都一定会被枚举至少一遍 SPFA 的时间复杂度为 $\Theta(km)$。其中 $k$ 是一个不稳定的常数，范围为 $1\le k\le n$，所以在某些时候 SPFA 会被卡会 Ford。于是有一位 NOI 出题人~~出言不逊~~直言不讳：

> 关于 SPFA，它死了。

那到底在什么情况下会被卡回 $\Theta(nm)$ 呢？就是在每一条边都被每一个点更新的时候，也就是网格图。

但是本题出题人没有尝试去卡 SPFA，所以对于此题，SPFA 能过。

SPFA 有四种优化，也就是 Ford 的优化的优化。

1. SLF 优化：全称 Small Label First 优化，这是用双段队列优化的，一般使用 STL
中的 deque。这种优化最常用。

1. LLL 优化：全称 Large Label Last 优化，顾名思义就是大的放后面，这个不是针对要入队的元素，而是针对要出队的元素。

1. SLF+LLL 优化：这是第一种与第二种的结合，SLF 针对的是入队元素，LLL 针对的是出对元素，两者互不干扰，所以可以结合。

1. DFS 优化：普通 SPFA 是用的是 BFS 思想，每当扩展出一个新的节点，总是把它放到队列的末尾，这种方法的缺点是中断了迭代的连续性，实际上可以直接从这个新节点继续往下扩展。这种优化一般用于判断[负环](https://www.luogu.com.cn/problem/P3385)，可以将时间复杂度降到 $\Theta(m)$（$m$ 是边数）。但如果求最短路，建议不要使用。

## 0x40 AC Code（本人懒，只写了 Dijkstra）

```cpp
//by olkieler
#include<bits/stdc++.h>
#define int long long
#define inf LLONG_MAX
#define N 1000005
#define M 10000005
using namespace std;
struct node
{
	int vaule;
	int rk;
	friend bool operator<(node x,node y)
	{
		return x.vaule>y.vaule;
	}//重载运算符
}ls;
priority_queue<node>q;
struct nd
{
	int next;
	int vaule;
	int pointer;
};
nd edge[M];//邻接表存图
int tot,n,m,s;
bool visited[N];
int head[N];
int d[N];
inline void add(int x,int y,int z)
{
	edge[++tot].vaule=z;
	edge[tot].pointer=head[x];
	edge[tot].next=y;
	head[x]=tot;
}//建边
inline void dijkstra(int s)
{
	while(!q.empty())
	{
		q.pop();
	}
	for(int i=0;i<n;i++)//注意点是从 0 开始，我在这里卡了两天！
	{
		d[i]=inf;
		visited[i]=0;
	}
	d[s]=0;
	q.push(node{0,s});
	while(!q.empty())
	{
		ls=q.top();
		q.pop();
		if(visited[ls.rk])
		{
			continue;
		}
		visited[ls.rk]=1;
		for(int j=head[ls.rk];j;j=edge[j].pointer)
		{
			if(d[edge[j].next]>d[ls.rk]+edge[j].vaule)
			{
				d[edge[j].next]=d[ls.rk]+edge[j].vaule;
				q.push(node{d[edge[j].next],edge[j].next});
			}
		}
	}
}//模板 Dijkstra
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1;i<=s;i++)
	{
		int a,maxx=0,ans=0;
		cin>>a;
		dijkstra(a);
		for(int i=0;i<n;i++)
		{
			if(d[i]>maxx&&d[i]!=inf)
			{
				maxx=d[i];
			}
		}
		for(int i=0;i<n;i++)
		{
			if(d[i]==maxx)
			{
				ans++;
			}
		}
		cout<<maxx<<' '<<ans<<'\n';
	}
	cout<<'\n';
	return 0;
}
```

感谢您的观看。

---

## 作者：Blikewsr (赞：3)

 - [$\color{orange}\text{[SP30669 原题链接]}$](https://www.luogu.com.cn/problem/SP30669)
 
 - 题目描述， 输入格式， 输出格式           
   [$\color{lightblue}\text{[见云切板]}$](https://www.luogu.com.cn/paste/sk002qpa)

 - 思路              
   根据题意， 我们可以知道， 题目让我们通过最短路求出距离主人公最远的城市以及它们的数量。
   
   注意！ 本题是双向边， 而且是通过求最短路找最远的城市， 而不是求最长路。
   
   那么， 说到最短路， 会想到什么？
   
   Floyed， 时间复杂度为 $O(N^{3})$， 但是， 再看看数据， 嗯， 过不了， 会超时。
   
   于是， 我们就可以写 dijkstra 再加一点优先队列优化。
   
   首先， 我们要知道什么是 dijkstra 算法。 
          
   dijkstra 算法是用来计算一个点到其它所有点的最短路径的算法， 是一种单源最短路径算法。 
   
   也就是说， 只能计算起点只有一个的情况。       
   
   dijkstra 算法的时间复杂度是 $O(N^{2})$， 它不能处理一些存在负边权的情况。                
   
   算法描述：   
   
   设起点为 `s`， $dis_v$ 表示从 `s` 到 `v` 的最短路径， `w[u][v]` 表示有一条从 `u` 到 `v` 长度为 `w` 的路。
   
   - 初始化： $dis_v = \infty$, $dis_s = 0$               
   
   - ```for (int i = 1; i <= n; ++ i)``` 
   
      1. 在没有被访问过的点中找到一个点 `u` 使得 `dis[u]` 是最小的。
      
      2. 将 `u` 标记为已经访问过。
      
      3. `for` 循环对于每一个与 `u` 相连的未确定的点 `v`。
      
      ```
      if (dis[v] > dis[u] + w[u][v]) {
      // 找到了更短的路径
      	dis[v] = dis[u] + w[u][v];
      }
      ```
      
   - 算法结束： `dis[v]` 为 `s` 到 `v` 的最短路径距离。
   
   既然你已经懂得 dijkstra 算法了， 那么就先去试试这两题吧：       
   - [$\color{lightblue}\text{单源最短路径}$](https://www.luogu.com.cn/problem/P4779)
   - [$\color{lightblue}\text{邮递员送信}$](https://www.luogu.com.cn/problem/P1629)
    
   但是， 我们再看看本题的数据：              
   
   $1 \le N < 10^{5} , 0 \le M \le 10^{6}$。           
   
   嗯， 普通的 dijkstra 肯定会超时 ， 所以， 我们就需要优先队列优化一下。 
   
   但是， 这题目翻译有坑， 题中写的是 $1 \le N < 10^{5}$， 但如果你只开 $10^{5}$, 那么空间是不够的。
   
   所以， 我们最好开大一点。
   
   所以， 堆优化过的 dijkstra 算法就是如下代码 （ 时间复杂度为 $O(m\log m)$， 要用邻接表储存边 ）：  
   
   - 邻接表储存
   ```cpp
   inline void add (int x, int y, int w) {
	f[++tot].y = y;
	f[tot].edge = w;
	f[tot].next = head[x];
	head[x] = tot;
	return;
   }
   ```
   
   - dijkstra 优先队列优化版
   ```cpp
   inline void dijkstra (int start_point) {   
	// dijkstra 优先队列优化版
		for (int i = 0; i < n; i++) {
			dis[i] = Inf;
			v[i] = 0;
		}   // 初始化
		dis[start_point] = 0;    // 起点标记为 0 
		q.push (make_pair (0, start_point));  // 入队
		while (!q.empty ()) {     // 如果队列不为空
			int minn = q.top ().second;   // 取出所有的点中最小的一个
			q.pop ();   // 取出
			if (v[minn]) continue;  // 如果该点被访问过， 则跳过
			v[minn] = 1;   // 标记该点已访问过
			for (int i = head[minn]; i; i = f[i].next) {
				int y = f[i].y;
				int z = f[i].edge;
				if (dis[y] > dis[minn] + z){  // 更新最短路
				  dis[y] = dis[minn] + z;
				  q.push (make_pair (-dis[y], y));   // 下一个点入队
				}
			}
		}
		return;
	}
   ```
   
   接着， 我们在每一次讯问都跑一遍以输入的 `s` 为起点的 dijkstra ， 最后再找到最远的城市和它们的数量就行了。
   
   那么， 怎么找最远的呢？
   
   首先， 我们可以定义 $waylongest = -1$, $numcity = 1$。
   
   接着， 我们用一个 `for` 循环， 其主要内容为：           
   
     - 如果 $dis_i = maxn$， 则跳过。
   
     - 如果记录的 $waylongest$ 小于 $dis_i$， 则把 $waylongest = dis_i$。
    
     - 如果记录的 $waylongest$ 等于 $dis_i$， 则把 $numcity++$。
   
     - 否则， 不做如何处理。
   
   所以， 该部分代码为：       
   ```cpp
	int way_longest = -1, num_city = 1;    
      /*
       way_longest : 最远的距离
       num_city    : 距离最远的城市的个数
       */
	for (int i = 0; i < n; ++ i) {   // 找
		if (dis[i] == Inf) continue;  
           // 没有通往此点的最短路径， 则跳过
		else if (dis[i] > way_longest) {   
           // 有更远的城市
			way_longest = dis[i];    // 更新最远距离
			num_city = 1;   // 个数重新设为 1
		}
		else if (dis[i] == way_longest) {
           // 最短路径长度与最远距离相等， 则城市个数加 1
			++ num_city;
	    }	
	}
   cout << way_longest << ' ' << num_city << '\n';   // 输出
   ```
   最后再把结果输出就行了。   
   
 - 代码
```cpp
#include <bits/stdc++.h>  // 万能头
#define int long long
#define N 10000001        // 数组大小
#define Inf (1 << 31) - 1     // 用来给 dis 初始化
using namespace std;
priority_queue < pair <int, int> > q;     // 优先队列
int n, m, qt;    
/*
 n  :  城市的数量
 m  :  道路的数量
 qt :  询问的次数
*/
int dis[N], v[N]; 
/*
 dis : 用来记录最短路径
  v  : 用来标记该点是否走过
*/
int tot, head[N]; 
struct node {
	int y, next, edge;
} f[N];
/*
 邻接表（上）
 储  存（下）
*/
inline void add (int x, int y, int w) {
	f[++tot].y = y;
	f[tot].edge = w;
	f[tot].next = head[x];
	head[x] = tot;
	return;
}
inline void dijkstra (int start_point) {   
// dijkstra 优先队列优化版
	for (int i = 0; i < n; i++) {
		dis[i] = Inf;
		v[i] = 0;
	}   // 初始化
	dis[start_point] = 0;    // 起点标记为 0 
	q.push (make_pair (0, start_point));  // 入队
	while (!q.empty ()) {     // 如果队列不为空
		int minn = q.top ().second;   // 取出所有的点中最小的一个
		q.pop ();   // 取出
		if (v[minn]) continue;  // 如果该点被访问过， 则跳过
		v[minn] = 1;   // 标记该点已访问过
		for (int i = head[minn]; i; i = f[i].next) {
			int y = f[i].y;
			int z = f[i].edge;
			if (dis[y] > dis[minn] + z){  // 更新最短路
			  dis[y] = dis[minn] + z;
			  q.push (make_pair (-dis[y], y));   // 下一个点入队
			}
		}
	}
	return;
}
signed main () {
//	freopen ("SP30669.out", "w", stdout);
	cin >> n >> m >> qt;    // 输入
	for (int i = 0; i < m; ++ i) {  // 建图
		int u, v, w;
		cin >> u >> v >> w;
		add (u, v, w);
		add (v, u, w);
        // 双向边
	}
	for (int t = 0; t < qt; ++ t) {   // qt 次询问
		int start_point;      // 起点
		cin >> start_point;
		dijkstra (start_point);      // 跑一遍 dijkstra
		int way_longest = -1, num_city = 1;    
        /*
         way_longest : 最远的距离
         num_city    : 距离最远的城市的个数
        */
		for (int i = 0; i < n; ++ i) {  
			if (dis[i] == Inf) continue;  
            // 没有通往此点的最短路径， 则跳过
			else if (dis[i] > way_longest) {   
            // 有更远的城市
				way_longest = dis[i];    // 更新最远距离
				num_city = 1;   // 个数重新设为 1
			}
			else if (dis[i] == way_longest) {
            // 最短路径长度与最远距离相等， 则城市个数加 1
				++ num_city;
			}	
		}
		cout << way_longest << ' ' << num_city << '\n';   // 输出
	}
	return 0;    // 完美结束
}
```

 - 此题解仅供参考， 谢谢！
 

---

## 作者：kaceqwq (赞：3)

# 题目大意：
有 $N$ 个城市之间有 $M$ 条双向边，现要求通过最短路求出距离 $Q$ 个起始点最远的距离和这样的城市数量。

# 分析：
由题意可知，这题是一道最短路的题目，是一道很好的练手题，首先我们可以根据题目给出的城市间道路的信息，通过邻接表存图，然后使用 **SPFA** 算法求出从起始点到各个城市的最短路径，接着在这之中找出最长的路径以及最远的城市数量即可。

# 关于 SPFA 算法：
 SPFA 算法在国际上通称为“队列优化的 Bellman-Ford 算法”。
 
###  算法流程如下：

1.建立一个队列，最初队列中只含有起点 $S$ 。

2.取出队头节点 $x$ ，扫描他的所有出边，若 $ans_y >ans_x+z$ ，则使用 $ans_x+z$ 更新 $ans_y$ 。同时，
若 $y$ 不在队列中，则把 $y$ 加入队列；

3.重复上述步骤，直到队列为空。
 
同时本题的坑点：

1.本题起始点可以为 $0$ ；

2.本题为双向边。

# Code：
```cpp
#include <bits/stdc++.h> 
#define int long long 
using namespace std;
int head[10000005],ver[10000005],ed[10000005],net[10000005],ans[10000005];
int n,m,s,tot,x,y,z,Q,num,zd;
queue < int > q; 
bool flag[10000005];
void add(int x,int y,int z){   //邻接表建边
    ver[++tot]=y;
    ed[tot]=z;
    net[tot]=head[x];
    head[x]=tot;
}
void spfa(){   //SPFA算法
    for(int i=0;i<n;i++)
    ans[i]=-1;   
    memset(flag,0,sizeof(flag));
    ans[s]=0;
    flag[s]=1;
    q.push(s);
    while(!q.empty()){
        int sum=q.front();
        q.pop();
        flag[sum]=0;
        for(int i=head[sum];i;i=net[i]){
            int y=ver[i],z=ed[i];
            if(ans[y]>ans[sum]+z||ans[y]==-1){   //不断更新最短路
            ans[y]=ans[sum]+z;
            if(!flag[y]){
                flag[y]=1;
                q.push(y);
                }
            }
        }
    }
}
signed main(){
	ios::sync_with_stdio(0);
    cin>>n>>m>>Q;
    for(int i=0;i<m;i++){
        cin>>x>>y>>z;
        add(x,y,z);   //双向建边
        add(y,x,z);
    }
    for(int i=0;i<Q;i++){
    cin>>s;
    spfa();
    num=0;   // num 存储最远城市数量
    zd=0;    // zd 存储最远距离
    for(int j=0;j<n;j++){   //有可能从0开始
        if(ans[j]>zd){   //寻找最大的距离
            zd=ans[j];
            num=1;    //找到了，数量就变为1
        }
        else if(ans[j]==zd)   //如果某个距离和最大距离相等，说明最远城市数量加1
        num++;
    }
    cout<<zd<<' '<<num<<'\n';
    }
    return 0;
}
```


---

## 作者：SuperCowHorse (赞：1)

### 题目大意
求距离源点 $s$ 最短路最远的城市数量。
### 题目分析
首先建图。在这里使用链式前向星建图，`vector`可能常数略大，在此不提倡。~~虽然比较方便~~
``` cpp
struct edge{
	int u,v,w,next;
}e[maxm<<1];int head[maxn],cnt;
void add(int u,int v,int w){//链式前向星
	++cnt;
	e[cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
```
然后跑最短路。

使用优先队列优化的 dijkstra，跑得很快。SPFA 似乎也行，~~但作者太弱~~，这里不讲述。
``` cpp
void dij(int s){//从s跑最短路
	priority_queue<node>q;//优先队列
	memset(dis,63,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		tmp=q.top();q.pop();
		int u=tmp.pos;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push((node){v,-dis[v]});
			}
		}
	}
}
```
之后直接统计答案即可。

找出最大值，边找变统计，最大值更新就`++ans`，最后直接输出。

Code:
``` cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int pos,dis;
	bool operator <(const node &a) const{return a.dis>dis;}
}tmp;
const int maxn=5e5+5,maxm=1e6+5;
int n,m,q;
int dis[maxn];
bool vis[maxn];
struct edge{
	int u,v,w,next;
}e[maxm<<1];int head[maxn],cnt;
void add(int u,int v,int w){//链式前向星
	++cnt;
	e[cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dij(int s){//跑dijkstra
	priority_queue<node>q;
	memset(dis,63,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		tmp=q.top();q.pop();
		int u=tmp.pos;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push((node){v,-dis[v]});
			}
		}
	}
}
signed main(){
	scanf("%d%d%d",&n,&m,&q);
	while(m--){
		int u,v,w;
		scanf("%d%d%lld",&u,&v,&w);
		++u;++v;
		add(u,v,w);add(v,u,w);
	}
	while(q--){
		int s;
		scanf("%d",&s);++s;
		dij(s);
		int ans=0,maxx=-1e8;
		for(int i=1;i<=n;++i){//统计最大值
			if(dis[i]==dis[maxn-2])
				continue;
			if(dis[i]>maxx){
				maxx=dis[i];
				ans=0;
			}
			if(dis[i]==maxx)
				++ans;
		}
		printf("%lld %lld\n",maxx,ans);
	}
}
```

---

## 作者：LYqwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP30669)

# 题目大意

给定一张无向图，并给出 $q$ 个询问。对于每个询问，给出起始点 $s_i$，请求出距离起始点最短路最远的点，并求出最远的点的个数。

$1 \le n \le 5 \times 10^5,1 \le m \le 10^6,\max\{n,m\} \times q \le 10^7$。

保证边权不为负。

时间限制 $5.5s$，空间限制 $1.46GB$。

# 思路

第一眼题面：[数据删除]范围这么大...怎么跑最短路啊......

第二眼题面：哦时限 $5.5s$ 那没事了......

此题翻译数据范围假了，至少在我写题解的时候，$n$ 是 $5 \times 10^5$。

既然时限这么大，那么就可以考虑下全源最短路。

但是 $n \le 5 \times 10^5$，爆栈了要。

既然栈会寄，那就只好~~时间换空间~~每次询问都跑一遍最短路了。

这题可以 dijkstra 或 SPFA，~~但考虑到 SPFA 寄了~~，我就写 dijkstra 了。

每次跑完后都循环一遍找最远的一个点，若这个点比先前找到的最远的点还要远，那么最远的点数统计变量也要清空。

这样跑会不会出错？不会。就相当于这样一个场景：捡贝壳，一列贝壳让你捡，你会一个一个捡，要捡到所有最好看的贝壳，你会使用一种贪心策略，若当前贝壳的好看度比手上的大，那么你会丢弃原来的所有贝壳，并捡起新的贝壳，原来的贝壳就没有任何意义了。

注意开 long long。

# 代码

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
template<typename T=long long>
inline T read(){
    T X=0; bool flag=1; char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
    if(flag) return X;
    return ~(X-1);
}

typedef long long ll;
const ll N=5e5+5,M=2e6+5,inf=0x3f3f3f3f3f3f3f3f;
struct edge{
    int to,nxt;
    ll val;
}e[M];
int n,m,q,u,v,s;
ll w,ans,cnt;
int head[N],top;
ll dist[N];
int vis[N];
priority_queue<pair<int,int>> h;

void add(int u,int v,int w){
    top++;
    e[top].to=v;
    e[top].val=w;
    e[top].nxt=head[u];
    head[u]=top;
}

void dijkstra(int s){
    for(int i=0; i<n; i++)
        dist[i]=inf,vis[i]=0;
    h.push(make_pair(0,s));
    dist[s]=0;
    while(!h.empty()){
        u=h.top().second;
        h.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u]; i; i=e[i].nxt){
            v=e[i].to;
            if(dist[v]>dist[u]+e[i].val){
                dist[v]=dist[u]+e[i].val;
                h.push(make_pair(-dist[v],v));
            }
        }
    }
}

signed main(){
    n=read(),m=read(),q=read();
    while(m--){
        u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    while(q--){
        s=read();
        dijkstra(s);
        ans=-114514,cnt=1;
        for(int i=0; i<n; i++)
            if(dist[i]==inf) continue;
            else if(ans<dist[i]){
                ans=dist[i];
                cnt=1;
            }else if(ans==dist[i]) cnt++;
        printf("%lld %lld\n",ans,cnt);
    }
    return 0;
}
```

---

## 作者：Acerkaio (赞：1)

## 简化题意

$N$ 个节点，$M$ 条便，起点为 $Q_i$ 的最短路最远距离和最远的城市数。

## 坑点

1. 节点编号是从 $0$ 开始的。
1. 要求双向边。

## 思路

跑 $Q$ 遍最短路，每次起点为 $Q_i$，枚举到每个节点的最短路，求出最大值并记录最远的城市数。

我所用的算法是 dijskra 最短路算法，总的来说，此题就是板子题改动一下。

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
#define N (1<<31)-1
using namespace std;
priority_queue < pair < int, int > > q;
int d[10000001];
int head[1000001], tot;
bool v[10000001];
struct node {
	int edge ,next, y;
}f[10000001];
int n, m, s;
inline int read() {
    int n = 0, m = 1;
    char a = getchar();
    while (!isdigit(a)) {
        if(a == '-') {
            m = -1;
        }
        a = getchar();
    } 
    while (isdigit(a)) {
        n = (n << 3) + (n << 1) + (a - '0');
        a = getchar();
    }
    return n * m;
}
void add (int x, int y, int w) {
	f[++tot].y = y;
	f[tot].edge = w;
	f[tot].next = head[x];
	head[x] = tot;
}
void dj () {
	for (int i = 1; i <= n; i++) {
		d[i] = N;
		v[i] = 0;
	}
	d[s] = 0;
	while(!q.empty())
		q.pop();
	q.push(make_pair(0,s));
	for (int i = 1; i < n; i++) {
		int minn= 0;
		while (!q.empty()) {
			int minn = q.top().second;
			q.pop();
			if (v[minn])  continue;
			else  v[minn] = 1;
			for (int i = head[minn]; i; i = f[i].next) {
				int y = f[i].y;
				int z = f[i].edge;
				if (d[y] > d[minn] + z){
					d[y] = d[minn] + z;
					q.push(make_pair(-d[y], y));
				}
			}
		}
	}
}
signed main () {
    n = read(), m = read();
	int Q = read();
	for (int i = 1; i <= m; i++) {
		int u = read() + 1, v = read() + 1, w = read();
		add(u,v,w);
		add(v,u,w);
	}
	dj ();
	while(Q--) {
		s = read() + 1;
		dj();
		int maxn = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			if (d[i] > maxn && d[i] != 0x7fffffff) {
				maxn = d[i];
				ans = 0;
			}
			if (d[i] == maxn) {
				ans++;
			}
		}
		cout << maxn << ' ' << ans << '\n';
	}
	return 0;
}
```


---

## 作者：ZBAA_MKC (赞：0)

给一组样例：

**输入**
```
4 6 2
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
1
2
```

**输出**
```
4 1
2 2

```

**提示：翻译有坑！点的数组开到 $10^5$ 不够！需要开到 
$10^6$!**

### 题意简述

给出一个 $n$ 个点，$m$ 条边的无向图，求出从源点 $s$ 到其余所有点的最短路径中最长的距离是多少以及其出现的数量。(每个测试点包含 $Q$ 组数据)

### 思路分析

这是一道最短路类模板题，实现起来并不难，但要注意以下两点：

$1.$ 点的编号从 $0$ 开始。

$2.$ 输入的图是无向图，所以要双向建边。

我们按照输入的数据，跑 $Q$ 次堆优化迪杰斯特拉算法，求出最短路径后将存储最短路的数组从大到小排序，跳过距离为为正无穷的点后统计最长距离的点有几个，按要求输出距离和编号即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9 + 7;

struct edge
{
	int w;
	int v; 
};

struct node
{
	int pos;
	int dis;
	bool operator <(const node &a)const
	{
		return dis > a.dis;
	}
};

vector<edge> adj[1000005];
priority_queue<node> q;
int dist[1000005];
bool vis[1000005];
int n, m, Q;

void djstl(int s)
{
	for(int i = 0; i <= n; i++)
	{
		vis[i] = false;
		dist[i] = inf;
	}
	node node_u;
	node_u.pos = s;
	node_u.dis = 0;
	q.push(node_u);
	dist[s] = 0;
	while(!q.empty())
	{
		node_u = q.top();
		q.pop();
		if(vis[node_u.pos] == true)
		{
			continue;
		}
		vis[node_u.pos] = true;
		for(int i = 0; i < adj[node_u.pos].size(); i++)
		{
			int v = adj[node_u.pos][i].v;
			int w = adj[node_u.pos][i].w;
			if(dist[node_u.pos] + w < dist[v])
			{
				dist[v] = dist[node_u.pos]+w;
				node tmp;
				tmp.dis = dist[v];
				tmp.pos = v;
				q.push(tmp);
			}
		}
	}
}

//以上是堆优化dijsktra模板，不解释

int main(){
	scanf("%d%d%d",&n, &m, &Q);	
	int u;
	edge vw;
	for(int i = 0; i < m; i++)
	{
        edge t;
		scanf("%d%d%d", &u, &vw.v, &vw.w);
        t.v = u;
        t.w = vw.w;
		adj[u].push_back(vw);
        adj[vw.v].push_back(t); //双向建边
	}
	while (Q--)
    {
        int x;
        scanf("%d", &x);
        djstl(x); //跑最短路
        sort(dist, dist + n + 1, greater<int>()); //排序
        int tmp;
        int cnt = 0;
        int ps;
        for (int i = 0; i <= n; i++) //跳过inf
        {
            if (dist[i] == inf)
            {
                continue;
            }
            else
            {
                ps = i;
                tmp = dist[i];
                break;
            }
        }
        for (int i = ps; i <= n; i++) //统计答案
        {
            if (dist[i] == tmp)
            {
                cnt++;
            }
            else
            {
                break;
            }
        }
        printf("%d %d\n", dist[ps], cnt); //输出
    }
	return 0;
}
```

感谢大家的阅读！

---

## 作者：_Fontainebleau_ (赞：0)

## SP30669 [$\textit{【ADATRIP-Ada and Trip】}$](https://www.spoj.com/problems/ADATRIP/)

~~不得不说，原来的翻译我是醉了。~~



$\texttt{Description}$

------------

瓢虫 $Ada$ 热爱旅游。她一边拍照，买纪念品，一边周游世界。这星期她去了布干达。普通游客会选择在主城区和一些大都市游玩。但是 $Ada$ 不这么认为。她想走尽可能远的路（因为远离市中心的地方所拍摄的照片更有价值）。

问题来了，布干达非常大，她几乎猜不着哪个城市离她最远（通过最短路）。幸运的是，你在她身旁，于是，她向聪明博学的你发出了求救。你能告诉她最远的城市距离她的距离，以及有多少个这样的城市吗？

$\texttt{InputForMat}$

------------
第一行有 $3$ 个整数。 $1≤N≤10^5$ $0≤M≤10^6$  $Q$ 分别表示，城市数量，道路数量，提问数量。

接下来 $M$ 行一行三个整数 $0≤A,B＜N$ $0≤L≤10$ 表示有一条从 $A$ 市 到 $B$ 市距离为 $L$ （双向边）。

接下来 $Q$ 行，一行一个整数 $0≤ Q_i < N$，表示出发的城市。

$\texttt{OutputForMat}$

------------
共 $Q$ 行。一行两个整数，分别表示最远的距离，以及城市数量（见 $\texttt{Description}$）

$\texttt{Analysis}$

------------
一眼看就是最短路。并无什么要注意的。就是[这道题](https://www.luogu.com.cn/problem/P3371)换了输出方式。

难度 黄题不足，橙题有余？

直接放代码。
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int n,m,q,cnt;
int h[500001],t[2000001],val[2000001],nxt[2000001];
int dis[500001];
bool inq[500001];
int f,e,Q[100010001];
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
inline void addedge(int a,int b,int c)
{
	t[++cnt]=b,val[cnt]=c,nxt[cnt]=h[a],h[a]=cnt;
}
inline void spfa()
{
	while(f<=e)
	{
		int u=Q[f++];
		for(int p=h[u];p;p=nxt[p])
		{
			int v=t[p],c=val[p];
			if(dis[v]==-1||dis[v]>dis[u]+c)
			{
				dis[v]=dis[u]+c;
				if(!inq[v])	inq[v]=true,Q[++e]=v;
			}
		}
		inq[u]=false;
	}
}
int main()
{
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++)
	{
		int u=read()+1,v=read()+1,w=read();
		addedge(u,v,w),addedge(v,u,w);
	}
	for(int i=1;i<=q;i++)
	{
		int x=read()+1;//因为城市编号从0开始，故将编号加一，改为从1开始
		memset(dis,-1,sizeof(dis));
		memset(inq,false,sizeof(inq));
		f=e=1,Q[1]=x,dis[x]=0,inq[x]=true;
		spfa();
		int ans=0,p=0;
		for(int j=1;j<=n;j++)
			if(dis[j]>ans)	ans=dis[j],p=1;
			else	if(dis[j]==ans)	p++;
		printf("%d %d\n",ans,p);
	}
	return 0;
}

```


------------
提供一组样例。


输入
```
10 10 10
1 1 1
1 2 1
1 2 3 
3 1 1
5 4 10
8 5 10
5 6 5
6 7 3
6 9 3
9 7 4
0
1
2
3
4
5
6
7
8
9
```
输出
```
0 1
1 2
2 1
2 1
20 1
10 2
15 2
18 2
20 1
18 2
```
解释
```
0
2 3
3
2
8
4 8
4 8
4 8
4
4 8
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP30669)              
学了最短路，来水一发最短路题解。          
先说一下思路。      
我们对于每个起点，做一次最短路，我们找出其中的最长路并统计答案，最后输出。      
多测要清空。         
这里具体讲一下一些细节。      
## 1.存边         
### 1.1 直接存边     
首先需要一个 edge 结构体，存储 $3$ 个信息：$2$ 个端点和边权。           
但是，这种方法不能迅速通过一个点确定与它相连的所有路径。由于本题需要求最短路，这个方法不可行。        
### 1.2 邻接矩阵        
定义一个数组 $edge$，$edge_{i,j}$ 表示 $i$ 到 $j$ 这条边的边权，如果这条边不存在就设为 $\infty$。          
显然，$edge$ 最大是一个 $10^5\times10^5$ 的数组，会 MLE，同样不可行。        
### 1.3 邻接表      
邻接表通常用 vector 实现。        
定义一个 vector 数组 $edge$，$edge_{i,j}$ 表示 $i$ 与 $j$ 之间有一条边连接。     
这种方法相比邻接矩阵，优点是不用占用太多空间。      
本题中，$M$ 最大是 $10^6$，同时要建无向边（即建 $2$ 遍），所以最多要存储 $2\times10^6$ 个点。       
但是，vector 在不开 O2 优化下比较慢，容易被卡常，所以我们不使用这种方法。       
### 1.4 链式前向星      
链式前向星是邻接表的优化方法，存图的方法类似于链表。     
定义一个结构体 edge，存 $3$ 个值：$u$ 代表与当前结点相连的下一个结点，$nxt$ 代表上一个当前结点的结构体的位置，$w$ 代表边权。       
建一个 edge 数组 $a$，$a_i$ 表示第 $i$ 条边的信息。       
那么，我们怎么维护 $nxt$ 这个值呢？       
定义一个数组 $last$，$last_i$ 表示最后一个结点为 $i$ 的结构体的数组下标，初始为 $-1$。           
加边操作就很简单了：        
```cpp
inline void add(int u,int v,int w){
	a[++tot].u=v;
	a[tot].nxt=last[u];
	a[tot].w=w;
	last[u]=tot;
}
```
链式前向星不论是在空间还是时间都比较优秀，所以我们使用链式前向星存图。          
## 2.最短路      
### 2.1 Floyd 全源最短路         
这种方法需要利用邻接矩阵存图，本质为 dp。       
初始都为 $\infty$，对于每个在 $1$ 到 $N$ 内的 $i$，都有 $edge_{i,i}=0$。        
状态转移方程为 $edge_{i,j}=\min(edge_{i,j},edge_{i,k}+edge{k,j})$。        
因为邻接矩阵会 MLE，所以我们不使用 Floyd。        
同时，Floyd 是 $O(N^3)$ 的，明显会 TLE。              
### 2.2 SPFA 单源最短路           
这个算法通过队列“松弛”每个结点来求出最短路。         
但 SPFA 会被卡，我们不能使用，这里不做过多讲解了。             
### 2.3 Dijkstra 单源最短路          
和 SPFA 差不多，也是通过“松弛”每个结点求出最短路。          
我们定义一个 $dis$ 数组，初始都是 $\infty$，再定义一个 $vis$ 数组，$vis_i$ 表示结点 $i$ 有没有被访问过。        
我们用堆优化整个算法过程即可。         
CODE：     
```cpp
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define umap unordered_map
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pll pair<long long,long long>
const ll INF=9223372036854775807;
namespace mySTL{
	inline int max(int a,int b){return a>b?a:b;}
	inline int min(int a,int b){return a<b?a:b;}
	inline ll max(ll a,ll b){return a>b?a:b;}
	inline ll min(ll a,ll b){return a<b?a:b;}
	inline ld min(ld a,ld b){return a<b?a:b;}
	inline ld max(ld a,ld b){return a>b?a:b;}
	inline int _abs(int a){return a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline long long readll(){char c=getchar();long long f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}
	inline void swap(ll &a,ll &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void writell(long long x){if(x<0){putchar('-');x=-x;}
	if(x>=10){writell(x/10);}putchar(x%10+'0');}
	inline ll pw(ll a,ll b,ll p){if(b==0)return 1;
	if(b==1)return a%p;
	ll mid=pw(a,b/2,p)%p;
	if(b&1)return mid*mid%p*a%p;else{return mid*mid%p;}}
	inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
	inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
	inline int lcm(int a,int b){return a*b/gcd(a,b);}
}
using namespace mySTL;
struct edge{
	int u;
	int nxt;
	int w;
}a[2000020];
int n,m,t,s,u,v,w,last[1000010],tot,dis[1000010],maxx,maxn;
bool vis[1000010];
inline void add(int u,int v,int w){
	a[++tot].u=v;
	a[tot].nxt=last[u];
	a[tot].w=w;
	last[u]=tot;
}
struct node{
	int pos;
	int dis;
	bool operator<(const node& x) const{
		return x.dis<dis;
	}
};
priority_queue<node>q;
inline void Dijkstra(int s){//最短路
	memset(dis,0x3f,sizeof(last));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push(node{s,0});
	while(!q.empty()){
		int pos=q.top().pos,_dis=q.top().dis;
		q.pop();
		if(vis[pos]){
			continue;
		}
		vis[pos]=true;
		dis[pos]=_dis;
		for(int i=last[pos];i!=-1;i=a[i].nxt){
			int v=a[i].u;
			if(dis[v]>dis[pos]+a[i].w){
				dis[v]=dis[pos]+a[i].w;
				if(!vis[v]){
					q.push(node{v,dis[v]});
				}
			}
		}
	}
}
int main(void){
	//freopen("data.txt","r",stdin);
	memset(last,-1,sizeof(last));
	n=read();
	m=read();
	t=read();
	while(m--){
		u=read();
		v=read();
		w=read();
		add(u,v,w);
		add(v,u,w);
	}
	while(t--){
		maxx=0;
		maxn=0;
		s=read();
		Dijkstra(s);
		for(int i=1;i<=n;i++){//计算结果
			if(dis[i]==0x3f3f3f3f){
				continue;
			}
			if(dis[i]>maxx){
				maxx=dis[i];
				maxn=1;
			}else if(dis[i]==maxx){
				maxn++;
			}
		}
		write(maxx);
		putchar(' ');
		write(maxn);
		putchar('\n');
	}
	return 0;
}
```

---

