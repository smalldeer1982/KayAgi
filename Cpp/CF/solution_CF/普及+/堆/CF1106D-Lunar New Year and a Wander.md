# Lunar New Year and a Wander

## 题目描述

Lunar New Year is approaching, and Bob decides to take a wander in a nearby park.

The park can be represented as a connected graph with $ n $ nodes and $ m $ bidirectional edges. Initially Bob is at the node $ 1 $ and he records $ 1 $ on his notebook. He can wander from one node to another through those bidirectional edges. Whenever he visits a node not recorded on his notebook, he records it. After he visits all nodes at least once, he stops wandering, thus finally a permutation of nodes $ a_1, a_2, \ldots, a_n $ is recorded.

Wandering is a boring thing, but solving problems is fascinating. Bob wants to know the lexicographically smallest sequence of nodes he can record while wandering. Bob thinks this problem is trivial, and he wants you to solve it.

A sequence $ x $ is lexicographically smaller than a sequence $ y $ if and only if one of the following holds:

- $ x $ is a prefix of $ y $ , but $ x \ne y $ (this is impossible in this problem as all considered sequences have the same length);
- in the first position where $ x $ and $ y $ differ, the sequence $ x $ has a smaller element than the corresponding element in $ y $ .

## 说明/提示

In the first sample, Bob's optimal wandering path could be $ 1 \rightarrow 2 \rightarrow 1 \rightarrow 3 $ . Therefore, Bob will obtain the sequence $ \{1, 2, 3\} $ , which is the lexicographically smallest one.

In the second sample, Bob's optimal wandering path could be $ 1 \rightarrow 4 \rightarrow 3 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 1 \rightarrow 5 $ . Therefore, Bob will obtain the sequence $ \{1, 4, 3, 2, 5\} $ , which is the lexicographically smallest one.

## 样例 #1

### 输入

```
3 2
1 2
1 3
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
5 5
1 4
3 4
5 4
3 2
1 5
```

### 输出

```
1 4 3 2 5 
```

## 样例 #3

### 输入

```
10 10
1 4
6 8
2 5
3 7
9 4
5 6
3 4
8 10
8 9
1 10
```

### 输出

```
1 4 3 7 9 8 6 5 2 10 
```

# 题解

## 作者：Believe_R_ (赞：5)

今天模拟赛做到了一道好题（题目传送门）：[CF1106D](https://www.luogu.org/problemnew/show/CF1106D)

虽然是英文题，但是洛谷很好心地给了中文翻译~~（也就是一句话题意）~~：**用字典序最小的方法走过图上的所有点** 

看到这道题许多人想到的就是图的遍历。其实我个人认为，这道题和图的遍历有一点点像。下面先给出图的遍历的代码（前向星存图）：

```cpp
/*
输入格式:
共M+1行。
第1行包含2个正整数N，M，表示有N个点，M条边。
第2～M+1行包含2个用空格隔开的正整数u,v，表示一条从u到v的无向路径。注意，可能会有重边和自环，一个点不与自己相邻。

输出格式:
共N行，由小到大输出每个点相邻的点，如果这个点是孤立的，则输出一个空行。
*/
#include <bits/stdc++.h>
using namespace std;
const int N=500000;
int n,m,ans,tot=0;
int head[N],nex[N],to[N],f[N];
void add_edge(int x,int y)
{
    for(int i=head[x];i;i=nex[i]) if(to[i]==y) return;
    to[++tot]=y;
    nex[tot]=head[x];
    head[x]=tot;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x!=y) add_edge(x,y),add_edge(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        ans=0;
        for(int j=head[i];j;j=nex[j]) f[++ans]=to[j];
        if(ans==0) printf("\n");
        else
        {
            sort(f+1,f+ans+1);
            for(int k=1;k<=ans;++k) printf("%d ",f[k]);
            printf("\n");
        }
    }
    return 0;
}
```



这道题说白了也可以说是图的遍历，也是从第一个节点开始一步一步遍历，一直遍历到将所有的点全部遍历完。所以这里就很容易想到算法，也很容易写出伪代码：

> 前向星存图的那些东西不用说了，背都可以背下来
>
> 我开了一个 $bool$ 类型 $vis$ 数组，来存从第 $1$ 个到第 $n$ 个节点是否遍历过
>
> 其他的东西和“图的遍历”就很像了

```cpp
const int M=1e6+5;
int n,u,v,tot=0;
int head[M],to[M],nex[M];
bool vis[M]={true};
void add_edge(int x,int y)    //前向星存图
{
    ......
}
void dfs(int x)
{
    vis[x]=false;
    for(int i=head[x];i;i=nex[i])
    {
        if(vis[to[x]]==true)
        {
            找到x连出的边所指向的最小节点p;
            dfs(p);
        }
    }
}
int main()
{
    输入, 存边;
    dfs(1);
    输出;
    return 0;
}
```



这样一个伪代码就写好了。但是我们在实现的过程中会发现在 $dfs$ 中，找到 $x$ 连出的边所指向的最小节点 $p$ 时，有点难处理，总不能每次做 $dfs$ 时都排一下序吧~~【你非要这么做我也不拦你，自己**TLE** 别来找】~~ 

这里，我们就要进出今天的主角：堆！



## 堆（排序）

众所周知，堆可以做许多事情，其中**堆排序**就很常用，复杂度也很优秀：

> 插入（或删除）一个元素： $O(\log n)$ 
>
> 堆排序：$O(n \log n)$ 

而且，堆相对来说操作起来也比较简单【我指的是**STL**中的堆】，只要定义一个 $priority\_queue$  即可。具体（常见）操作可以往下看：

```cpp
priority_queue<int> q;             					//定义大根堆
priority_queue<int,vector<int>,greater<int> > q;	//定义小根堆

int x;
q.push(x)				// 插入x
q.top() 				// 取出堆的根
q.pop() 				// 弹出（删除）堆的根
q.size()				// 堆中元素的个数
q.empty()				// 判断堆是否为空
```

如果你觉得你堆的内容还没掌握，可以先去看一下这两道题目（传送门）：[P3378 【模板】堆](https://www.luogu.org/problemnew/show/P3378)，[P1168 中位数](https://www.luogu.org/problemnew/show/P1168)



如果你觉得你堆的知识已经掌握了，那么你可以回到这道题目，**看一下如何找到 $x$ 连出的边所指向的最小节点 $p$。** 

……………………………………………………我是分割线……………………………………………………



> 对于这道题，我是开了一个小根堆，然后将节点 $x$ 的下一个节点都丢到堆里面。
>
> 这样，堆顶元素就是 $x$ 连出的边所指向的最小节点 $p$。
>
> 当队列空了的时候，就说明图中所有的节点都被我们处理掉啦！！！
>
> 另外在代码里，我是用力一个 $while$ 循环，看的时候可以注意一下。

**下面贴上c++代码（维护社会和平，请勿 $Ctrl + A$ & $Ctrl + C$）**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int M=500000;
int n,m,tot=0;
int head[M],to[M],nex[M];
int vis[M],ans[M];
priority_queue<int,vector<int>,greater<int> > q;
void add_edge(int x,int y)
{
    to[++tot]=y;
    nex[tot]=head[x];
    head[x]=tot;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    q.push(1);
    int sum=0;
    while(!q.empty())
    {
        int h=q.top();
        q.pop();
        vis[h]=1; ans[++sum]=h;
        for(int i=head[h];i;i=nex[i])
        {
            int p=to[i];
            if(!vis[p])
            {
                vis[p]=1;
                q.push(p);
            }
        } 
    }
    for(int i=1;i<=n;++i) printf("%d ",ans[i]);
    return 0;
}
```

总而言之，这题的算法应该就是**图的遍历 + 堆**，所以根本就没有蓝题的难度~~【永远不要相信洛谷的标签】~~！

---

## 作者：lemon2021 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1106D)

## 题目大意
本题题意非常简单（主要是洛谷有简洁明了的翻译），大概意思就是有一个**双向图**，从 $1$ 号点出发，依次遍历所有节点，求**字典序最小**的遍历方法。

## 思路
说说思路吧，这题既然要遍历图上所有点，那首先就会想到 BFS 或 DFS，可本题还要求要字典序小，这两种方法要把所有情况都遍历一遍才能求出最值，这样显然会 TLE。那我们再想，这题要求字典序最小的遍历方法，那我们就利就用贪心思想，每次选编号最小的节点去走，这样结果肯定是最优的。

咦？是不是感觉这跟求最短路的 Dijkstra 算法很像，但又不太一样？Dijkstra 算法中是从起点开始把节点放入优先队列中，然后用 BFS 的思想，以起点为中心向外层扩展，每次取出队头（即队列中最短的边），然后把当前节点进行更新，并把新更新过的节点放入优先队列中，直到队列为空则结束。而此题跟 Dijkstra 算法基本相同，只是把取队列中距离最短的点变成了取所连的节点编号最小的点。

那这下就简单啦，我们把原 Dijkstra 算法中的选边判断改为选队列中所连的点编号最小的边，再把原本记录距离的数组改为记录遍历过程中的节点编号就好啦！

## AC 代码（有注释）：
```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100001;
int n,m,s;//节点个数，路径条数，起点编号 
vector<int> a[MAXN];//存边 
bool v[MAXN];//记录每个节点是否被访问 
int ans[MAXN];//存储最终答案 
priority_queue<int, vector<int>, greater<int> > q;//优先队列(STL大法好)
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;//u到v的双向边
		a[u].push_back(v);//记得u->v和v->u都要存哦！
		a[v].push_back(u);
	}
	s=1;
	q.push(s);
	while(!q.empty())
	{
		int x;
		x=q.top();
		q.pop();
		if(v[x]==true)//若节点一被访问过，则跳过 
		{
			continue;
		}
		v[x]=true;//把该节点设为已访问 
		ans[s]=x;//存入 
		s++;
		for(int i=0;i<a[x].size();i++)//枚举该节点出边 
		{
			if(v[a[x][i]]==true)//若节点一被访问过，则跳过 
			{
				continue;
			}
			q.push(a[x][i]);//存入优先队列 
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}

```

---

## 作者：世末OIer (赞：2)

C++ set自动排序了解一下？

```cpp
int n,m;
vector<int>g[100005];
vector<int>ans;
set<int>num;
bool used[100005];
int main(){
	n=getint();m=getint();
	for(int i=0;i<m;i++){
		int a=getint(),b=getint();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	num.insert(1);
	while(num.begin()!=num.end()){       //利用了set自动排序和bfs的原理
		int x=*num.begin();
		used[x]=true;
		ans.push_back(x);                //加入答案队列
		num.erase(num.begin());
		for(auto to:g[x])if(!used[to])num.insert(to); //下一步
	}
	for(auto v:ans)putint(v),put(' ');   //输出
	put('\n');
	clear();
	return 0;
}
```

---

## 作者：Silence_World (赞：1)

# 思路

题意很简单，无需赘述了，很明显的 bfs，用优先队列维护一下，我们从贪心的思路想，首先我们从 1 的位置开始，遍历这个图，把你即将要走的点都存入优先队列中，每次取第一个走，再重复进行此操作，每次都用一个数组存下来路径，本题结束。

# 代码

```
#include <bits/stdc++.h>
using namespace std;
priority_queue<int,vector<int>,greater<int> >a;
vector<int>b[100005];
bool c[1000005];
int d[1000005];
main(){
	int n,m;
	cin>>n>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		b[x].push_back(y);
		b[y].push_back(x);
	}
	int t=1;
	a.push(1);
	while(a.size()){
		int x1=a.top();
		a.pop();
		if(c[x1]){
			continue;
		}
		c[x1]=1; 
		d[t]=x1;
		t++;
		for(int i=0;i<b[x1].size();i++){
			if(!c[b[x1][i]])a.push(b[x1][i]);
		}
	}
	for(int i=1;i<=t-1;i++)cout<<d[i]<<" ";
	return 0;
}
```


---

## 作者：Erina (赞：1)

## 想吐槽一句就是这题是怎么评上蓝题的

好了进入正题

这题和NOIp2018D2T1怎么这么相似?

当时考试的时候我竟然看错了题然后想到了这题的错解(那天数据范围出奇的小), 就是用`bitset`处理邻接矩阵, 每一次找到最小的能走的点就行了.

现在发现这题数据范围变大了......

然后我们就不能直接`bitset`了,  我们每一次需要维护一个最小值, 脑海里直接蹦出`std::priority_queue`我们用它直接维护可以走到的新点的最小值就可以了.

下面放上丑陋的代码

```cpp
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> road[100005], ans;
bool vis[100005];
priority_queue<int,vector<int>,greater<int>> q;
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        road[x].push_back(y), road[y].push_back(x);
    }
    q.push(1);
    while (q.size())
    {
        int x=q.top();
        q.pop();
        cout<<x<<' ';
        vis[x] = 1;
        for (int it : road[x])
            if (!vis[it])
                q.push(it),vis[it]=1;
    }
}
```

---

## 作者：Dog_Two (赞：1)

考虑最短路的做法：

在堆优化的Dijkstra算法中，堆里优先度最高的是“路径最短”的节点，这里我们只需认为优先度最高的是“序号最小”的节点即可。

故，算法流程即“修改了优先级的Dijkstra算法”。

与NOIP原题不同的是，这里已经经过的节点可以任意访问，所以这个算法正确性是显然的。

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,m;
bool vis[maxn];
vector<int> G[maxn];
vector<int> ans;
priority_queue<int,vector<int>,greater<int> > q;

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v; scanf("%d%d",&u,&v);
		G[u].push_back(v),
		G[v].push_back(u);
	}
	q.push(1);
	while(!q.empty()){
		int u=q.top(); q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		ans.push_back(u);
		for(int i=0;i<G[u].size();++i){
			int v=G[u][i];
			if(!vis[v]) q.push(v);
		}
	}
	for(int i=0;i<ans.size();++i) printf("%d ",ans[i]);
	return 0;
}


```

---

## 作者：LlLlCc (赞：0)

因为以遍历过的节点可以多次访问且不影响答案，所以对于每个节点把能走的所有边存一下。为了满足字典序最小，每次在所以可遍历的节点中挑最小的。而满足最小性质的就是堆和集合了。

[不会堆的看这里](https://www.jianshu.com/p/6b526aa481b1)

[不会集合的看这里](https://www.cnblogs.com/woxiaosade/p/10793497.html)

AC代码（堆）：

```
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
int n,m,lnk[maxn],tot,now,x,y,hep[maxn],top,nxt[maxn*2],son[maxn*2];
bool vis[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;}
inline void put(int x){
    hep[now=++top]=x;
    while (now>1&&hep[now]<hep[now>>1]) swap(hep[now],hep[now>>1]),now>>=1;
}
inline int get(){pop_heap(hep+1,hep+top+1,greater<int>());return hep[top--];}
inline void Dfs(int x){
	printf("%d ",x);tot++;
	for (int i=lnk[x];i;i=nxt[i]) if (!vis[son[i]]) vis[son[i]]=1,put(son[i]);
	if (tot!=n) Dfs(get());
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++) x=read(),y=read(),add(x,y),add(y,x);
    tot=0;vis[1]=1;Dfs(1);
    return 0;
}
```


---

## 作者：Memory_of_winter (赞：0)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10345347.html)

### 题目大意

给你一张$n(n\leqslant10^5)$个点$m(m\leqslant10^5)$条边的无向图，现在在点$1$，每次到一个没有经过过的点就把那个点记录下来，直到经过所有$n$个点，问最后记录下的序列最小的字典序是什么，可以重复经过点和边。

谁可以告诉我为什么我交翻译的时候LATEX全部出锅了？

### 题解

这可比$NOIP2018D2T1$简单多了，只需要求一个一个类似最小生成树的东西就行了。用一个小根堆记录当前经过过的点可以到达的没有经过过的点，每次取出堆顶，把与它相连的点加入堆即可。




### C++ Code：

```cpp
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define maxn 100010
int head[maxn], cnt;
struct Edge {
	int to, nxt;
} e[maxn << 1];
inline void addedge(int a, int b) {
	e[++cnt] = (Edge) { b, head[a] }; head[a] = cnt;
	e[++cnt] = (Edge) { a, head[b] }; head[b] = cnt;
}

int Tim, n, m;
std::priority_queue<int, std::vector<int>, std::greater<int> > q;
bool inq[maxn];
int main() {
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> m;
	for (int i = 0, a, b; i < m; ++i) {
		std::cin >> a >> b;
		addedge(a, b);
	}
	q.push(1);
	inq[1] = true;
	for (int Tim = 1; Tim < n; ++Tim) {
		int u = q.top(); q.pop();
		std::cout << u << ' ';
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!inq[v]) {
				q.push(v);
				inq[v] = true;
			}
		}
	}
	std::cout << q.top() << std::endl;
	return 0;
}

```

---

## 作者：FlyInTheSky (赞：0)

BFS+优先队列。

~~我第一眼以为是 NOIP 出到一般图上的毒瘤题~~

这题和 NOIP 不同的是，NOIP 那题只能一条边进入后回溯，不能再走重复的，而这题是可以的。

所以我们可以想到字典序最小肯定是当前最小的就拿最小

所以我们从 $1$ 点开始拓展节点，然后全部塞到优先队列里(按节点编号从小到大排序)，每次从优先队列里取出一个最小点扩展更新。

**注意在扩展时就要打上标记以后不再入队，不然 MLE QAQ**

扩展即用 BFS。

~~我这题刚开始写了个$O(nm)$的做法自己0.5h没发现 QAQ~~

```c++
//==========================Head files==========================
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
#include<iostream>
#include<map>
#define LL long long
#define db double
#define mp make_pair
#define pr pair<int, int>
#define fir first
#define sec second
#define pb push_back
#define ms(i, j) memset(i, j, sizeof i)
using namespace std;
//==========================Templates==========================
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){if (c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}
inline LL readl() {
    LL x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){if (c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}
int power(int a, int b) {
	int ans = 1;
	while (b) {
		if(b & 1) ans = ans * a;
		b >>= 1; a = a * a;
	}
	return ans;
}
int power_mod(int a, int b, int mod) {
	a %= mod;
	int ans = 1;
	while (b) {
		if(b & 1) ans = (ans * a) % mod;
		b >>= 1, a = (a * a) % mod;
	}
	return ans;
}
LL powerl(LL a, LL b) {
	LL ans = 1ll;
	while (b) {
		if(b & 1ll) ans = ans * a;
		b >>= 1ll;a = a * a;
	}
	return ans;
}
LL power_modl(LL a, LL b, LL mod) {
	a %= mod;
	LL ans = 1ll;
	while (b) {
		if(b & 1ll) ans = (ans * a) % mod;
		b >>= 1ll, a = (a * a) % mod;
	}
	return ans;
}
LL gcdl(LL a, LL b) {return b == 0 ? a : gcdl(b, a % b);}
LL abssl(LL a) {return a > 0 ? a : -a;}
int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}
int abss(int a) {return a > 0 ? a : -a;}
//==========================Main body==========================
#define LD "%I64d"
#define D "%d"
#define pt printf
#define sn scanf
#define pty printf("YES\n")
#define ptn printf("NO\n")
//==========================Code here==========================

const int MAXN = 100000 + 5;

vector<int > G[MAXN];

int n, m, vis[MAXN];

struct data {
	int u;
	operator < (const data &rhs) const {return u > rhs.u;}
};

priority_queue<data > q;

int main() {
	ms(vis, 0);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		G[x].push_back(y), G[y].push_back(x);
	}
	for (int u = 1; u <= n; ++u) sort(G[u].begin(), G[u].end());
	
	if ((int)G[1].size() <= 0) return printf("1 "), 0;
	
	q.push((data){1});
	vis[1] = 1;
	while (!q.empty()) {
		
		data p = q.top(); q.pop();

		for (int i = 0; i < (int)G[p.u].size(); ++i) if (!vis[G[p.u][i]]) 
			q.push((data){G[p.u][i]}), vis[G[p.u][i]] = 1;
		
		printf("%d ", p.u);
		vis[p.u] = 1;
	}
	
	return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [CF1106D 题解](https://www.luogu.com.cn/problem/CF1106D)

暑期学校军训第一天模拟赛的题，相对而言比较简单

## 题意：

题意其实很简单，就是有一个**无向图**，需要你从$1$号节点出发，然后一次遍历所有的点，输出其中**字典序最小**的遍历

## 思路

说说思路吧，这题既然要遍历图上所有点，那首先就会想到 $\texttt{BFS}$ 或 $\texttt{DFS}$，可本题还要求要字典序小，这两种方法要把所有情况都遍历一遍才能求出最值，这样显然会 $\texttt{TLE}$。那我们再想，这题要求字典序最小的遍历方法，那我们就利就用贪心思想，每次选编号最小的节点去走，这样结果肯定是最优的。

然后这道题就很简单了，一个 $\texttt{DFS}$ 用优先队列维护一下就做完了~

这里还有一个知识点是链式前向星，就是存图加边的~~一个算是小模板的小小小函数~~

```
void add(int u,int v){
	tot++;
    a[tot].next=head[u];
    a[tot].to=v ;
    head[u]=tot;
}
```

~~这个 $\texttt{DFS}$ 其实我感觉和 $\texttt{SPFA}$ 里面的代码很像~~，不知道为什么

~~不信给你们看看~~

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
const int INF=0x3f3f3f3f;
struct node{
    int e,w;
};
int n,m,x,y,z;
int dis[N],vis[N];
vector<node> a[N];
queue<int> q;
void spfa(){
    q.push(1);
    vis[1]=1;
    memset(dis,INF,sizeof(dis));
    dis[1]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=0;i<a[u].size();i++){
            int e=a[u][i].e;
            int w=a[u][i].w;
            if(dis[e]>dis[u]+w){
                dis[e]=dis[u]+w;
                if(vis[e]==0){
                    vis[e]=1;
                    q.push(e);
                }
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y>>z;
        a[x].push_back({y,z});
        a[y].push_back({x,z});
    }
    spfa();
    cout<<dis[n];
    return 0;
}
//给定M条边，N个点的带权无向图。求1到N的最短路。 
```

~~你看是不是很像~~

好了，还是看看这道题的代码吧

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+100;
int n,m;
struct edge{
    int to,next;
}a[N<<1];
priority_queue<int,vector<int>,greater<int> >q;
int head[N],vis[N],tot;
void add(int u,int v){
	tot++;
    a[tot].next=head[u];
    a[tot].to=v ;
    head[u]=tot;
}
void dfs(){
    q.push(1);
    vis[1]=1;
    while(!q.empty()){
        int u=q.top();
        q.pop() ;
        printf("%d ",u);
        for(int i=head[u];i;i=a[i].next){
            int v=a[i].to;
            if(!vis[v]){
            	vis[v]=1;
            	q.push(v);
			}
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
    	int x,y;
    	scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs();
    return 0 ;
}
```
总而言之，这道题就是图的遍历，~~我觉得这道题甚至都不可以放在绿题里面，黄题差不多了~~

---

