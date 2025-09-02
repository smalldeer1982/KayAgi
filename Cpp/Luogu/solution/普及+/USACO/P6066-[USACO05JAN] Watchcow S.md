# [USACO05JAN] Watchcow S

## 题目描述

Farmer John 有 $N$ 个农场（$2 \leq N \leq 10^4$），这些农场由 $M$ 条道路连接（$1 \leq M \leq 5 \times 10^4$）。不保证没有重边。

Bassie 从 $1$ 号农场开始巡逻，每条路必须从两个方向各走**恰好一遍**，最后回到 $1$ 号农场。

请输出一条满足上述要求的路径。

保证这样的路径存在。如果有多条路径，任意输出一条即可。

## 样例 #1

### 输入

```
4 5
1 2
1 4
2 3
2 4
3 4```

### 输出

```
1
2
3
4
2
1
4
3
2
4
1```

# 题解

## 作者：SCP982 (赞：17)

## 需要知识点:
- 图的基础知识（有向图&无向图, 图的存储）

- 欧拉回路基础概念
## 本篇用到知识点
- vector 存储

- 欧拉回路
## 解析
从 **1 号农场开始**巡逻，每条路必须从两个方向各走恰好一遍，最后回到 1 号农场，从一个点出发，每条边都走一遍并回到起点，这是一个经典的欧拉回路问题。由于每条路必须从两个方向各走恰好一遍，所以需要**双向建边**，本人没有看到任何一篇使用了 vector 存图的新手向题解，所以过来写一篇较朴实无华の新手向题解，只要知道欧拉回路和 vector 是啥就行。
###     啥是欧拉回路
- 对于无向图，欧拉回路就是在图的所有结点的度都是偶数，并且图是连通的情况下，从任意一个节点开始 dfs 都可以回到原点。

- 对于有向图，欧拉回路就是在图的所有结点的出度和入度都相同，并且图是连通的情况下，从任意一个节点开始 dfs 都可以回到原点。

- 本题明确说明存在欧拉回路，所以不需要判断。
###     啥是度
- 对于无向图，度就是连接节点的边数（没有 up 会给你解释这个的）

- 对于有向图，出度就以该点为起点的边的条数，入度就是以该点为终点的边的条数。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,u,v;
vector<int> ve[10002];
queue<int> ans;
//这里就是一个朴实无华的深搜，就只是用了欧拉回路的思路，反正他会回来，每次删边就行
void dfs(int f){
	int len=ve[f].size();
	for(int i=0;i<len;++i){
		int xn=ve[f][i];
		if(xn){
			//删边
			ve[f][i]=0;
			dfs(xn);
		}
	}
  	//ans是用来存最终的顺序的
	ans.push(f);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		scanf("%d%d",&u,&v);
  		//双向建边
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	//从1号点开始dfs
	dfs(1);		
  	//输出，每次输出都出队
	while(!ans.empty()) {
		printf("%d\n",ans.front());
		ans.pop();
	}
  	//朴实无华的结束
	return 0;
}
```
## 对代码的补充说明
在代码第五行我使用了队列来存储最后的答案，这个方法只是偷了个懒，没有算如果用数组最多要开多大，那接下来就算一下。

首先题中明确给出了边的最大数量也就是 $M$（$1 \leq M \leq 5 \times 10^4$），又因为这里每条边要走两次，相当于 $2M$ 条边，从起点出发，每走一条边，就会扩展一个点，再加上起点，欧拉回路最终会有 $2M+1$ 个点，也就是 $100001$ 个点，因为我的数组要从下标一开始存，所以数组的空间要开到 $100002$。

---

## 作者：ArrTue (赞：10)

（**不需要欧拉回路相关知识**）

[题目传送门](https://www.luogu.com.cn/problem/P6066)

#### 前置知识：

链式前向星。

生成树（只需了解定义即可）。

#### 题意：

- 给出一张 $n$ 个点 $m$ 条边的无向图，问是否可以找到一条从 $1$ 出发最后回到 $1$ 的路径，每条边经过两次，并且两次经过的方向相反。

- 保证存在至少一条这样的路径，$n\le10^4$，$m\le5\times10^4$。

#### 分析：

（不与任何边相连的点在该题中无作用，故不考虑。此时图一定连通。）

我们先考虑特殊情况，图退化成一棵树。

这种情况比较显然，只需要 dfs 一遍，按照遍历的顺序输出即可。

接下来考虑图的情况。

先求出这张图的任意一棵生成树。由于图连通，生成树一定存在。对于这棵树上的边，直接像树的情形一样遍历。

![](https://z3.ax1x.com/2021/11/10/Ia1Pqs.png)

考虑其他不在树上的边 $(u,v)$。可以在遍历 $u$ 的时候沿着 $(u,v)$ 走一次，沿着 $(v,u)$ 走回来，然后继续遍历 $u$。

这样，生成树上的边一定被经过两遍；而所有不在生成树上的边的两个节点都会被遍历到，只需在遍历到的时候按照上述方法即可经过两遍。故可以得到一条合法路径。

![](https://z3.ax1x.com/2021/11/10/Ia1Crj.png)

#### 思路：

1. 通过 dfs 来求任意一棵生成树。

2. 在 dfs 求生成树的同时对所有非生成树边进行上述操作。

---

#### 实现细节：

实际写代码时，只需要进行一次 dfs，并不需要区分树边与非树边。

由于只需要求出任意一棵生成树，所以当遍历到 $u$，枚举所有与 $u$ 相连的边 $(u,v)$ 时，只要 $v$ 未被遍历过，就将 $(u,v)$ 看做生成树边，对 $v$ 进行 dfs；反之，若 $v$ 被遍历过，就将 $(u,v)$ 看做非树边。

显然，按照上述方法遍历，所有边都会被遍历到，可以得到合法路径。

另外，上述 dfs 的深度最多是 $\mathcal O(n)$ 的，故不需要手写栈，直接递归即可。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mN=1e4+9, mM=5e4+9;
int n, m;
int oe=1, head[mN], nxt[mM<<1], ver[mM<<1];
bool used[mM];  //边是否被遍历过
inline void add(int x, int y) {nxt[++oe]=head[x], ver[oe]=y, head[x]=oe;}

bool vis[mN];   //点是否被遍历过
void dfs(int x) {
	printf("%d\n", x), vis[x]=1;    //第一次遍历到点 x，标记并且输出路径
	for(int t=head[x]; t; t=nxt[t]) if(!used[t>>1]) {
		used[t>>1]=1;
		if(!vis[ver[t]]) dfs(ver[t]), printf("%d\n", x);  //点未被遍历过，是树边，去 dfs 另一个点
		else printf("%d\n%d\n", ver[t], x); //点被遍历过，是非树边，去一次再回来
	}
}

int main() {
    scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v), add(v, u);
	}
	dfs(1);
	return 0;
}
```

---

## 作者：fanfansann (赞：3)

# 首先讲一下什么是欧拉回路

# $O(N+M)$非递归版代码  防止栈溢出

**欧拉回路**就是给一个图，存在一条回路把所边经过且每条边只经过一次。

## 对于无向图：

存在欧拉回路的条件：每个点的度都为偶数；
　　
存在欧拉路的条件：有且只有两个点的度为一，且这两个点分别为起点和终点；

## 对于有向图：

存在欧拉回路的条件：每个点出度等于入度；

存在欧拉路的条件：存在一个点出度比入度多一作为起点，存在一点入度比出度多一作为终点，其余点出度等于入度；

求欧拉回路的方法——基本（套圆）法
　　dfs搜索，不能再往下走便回溯，回溯时记录路径，回溯时不清除对边的标记，最后求出来的路径就是欧拉回路。


> 上述的时间复杂度为$O(NM)$。因为一个点会被重复遍历多次。
> 假设我们采用邻接表存储无向图，我们可以在访问一条边$(x,y)$后，及时地修改表头$head[x]$，令它指向下一条边，这样我们每次只需取出$head[x]$,就自然跳过了所有已经访问过的边。（vis数组突然就没什么用了）
> 
> 另外，因为欧拉回路的DFS的递归层数是$O(M)$级别的，很容易造成系统栈的溢出，我们可以用另一个栈，模拟机器的递归过程，把代码转化为非递归实现，优化后的程序时间复杂度为$O(N+M)$
> 
> --------------
> ——《算法竞赛进阶指南》


回到本题，由于题目要求每条边要正反走两边，那么我们直接把**原求欧拉回路模板的vis数组的双向标记改为单向标记即可**。因为按照一般的存储方式，无向边在邻接表中是被拆成了两条有向边来存储，若无标记，根据欧拉回路中的更新方式来看，正好会经过两次。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<math.h>
#include<cstring>
#include<queue>
//#define ls (p<<1)
//#define rs (p<<1|1)
#define over(i,s,t) for(register int i = s;i <= t;++i)
#define lver(i,t,s) for(register int i = t;i >= s;--i)
//#define int __int128
//#define lowbit(p) p&(-p)
using namespace std;

typedef long long ll;
typedef pair<int,int> PII;
const ll INF = 1e18;
const int N = 5e4+7;
const int M = 5e5+7;

int head[N],nex[M],ver[M],tot = 1;
bool vis[M];
int stk[M],ans[M];//模拟系统栈，答案栈
int n,m,s,t,cnt,top;
queue<int>q;

void add(int x,int y){
    ver[++tot] = y;nex[tot] = head[x];head[x] = tot;
}

void euler(){//模拟dfs
    stk[++top] = 1;//起点
    while(top > 0){
        int x = stk[top],i = head[x];
        while(i && vis[i])i = nex[i];//找到一条尚未访问过的路
        // 与x相连的所有边均已访问，模拟回溯过程，并记录
        if(i){
            stk[++top] = ver[i];
            vis[i] =  true;//题目要求要回来的嘛，需要标记一次
            //vis[i] = ver[i ^ 1] = true;//正常的欧拉回路模板
            head[x] = nex[i];
        }
        else {// 与x相连的所有边均已访问，模拟回溯过程，并记录
            top--;
            ans[++cnt] = x;
        }

    }
}

int main(){
    scanf("%d%d",&n,&m);
    tot = 1;
    over(i,1,m){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);add(y,x);
    }
    euler();
    over(i,1,cnt)
    printf("%d\n",ans[i]);
}

```


---

## 作者：yzh_Error404 (赞：2)

这道题是一道改了一点点的欧拉回路模板题。

要求每条边正反各走一次。

正反各连一条单向边求欧拉回路即可。

值得注意的是，标记边的地方需要从标记两条边变成标记一条边，因为正反两条边是分开的。

这里用的是栈来保证遍历的顺序。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=6e5+5;
struct node
{
	int to,nxt;
}e[MAXN];//链式前向星存图
int head[MAXN],cnt;
inline void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
bitset<MAXN>vis;
int n,m;
stack<int>s;
inline void dfs(int x)//欧拉回路模板
{
	for(register int i=head[x];i;i=e[i].nxt)
	{
		if(!vis[i])
		{
			vis[i]=1;//标记只要标记一条边
			dfs(e[i].to);
			s.push(e[i].to);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);//把双向边当成两条单向边连
	}
	int st=1;
	dfs(st);
	s.push(st);//要把起点也放进栈里
	while(!s.empty())
	{
		printf("%d\n",s.top());
		s.pop();
	}
	return 0;
}
```

---

## 作者：xh39 (赞：2)

此题要从两个方向各走一遍,所以我们可以想象$u$-$v$直接建的$2$条$u$->$v$和$v$->$u$的**有向**图。

我们都知道,一个有向图是否有欧拉回路(即走每条边1次,又回到原点。),只有它的入度==出度时。(每一个点都要进1次,出1次,才可以构成回路)。所以这道题不存在没有欧拉回路的情况。

如何寻找欧拉回路?找出一个回路,然后将这个回路删除,在各连通块中找出用同样的方法欧拉回路。然后合并到答案中。

在实现中,删除实现为标记。然后我们~~暴力~~dfs遍历每一条边,把顶点依次入栈。就做到了合并答案(没有讲得太清楚,请读者自行思考,或跳过这篇题解)。

接下来细节方面的注释都在代码里了。
## AC.code
```cpp
//阅读此篇代码先学习链表。
#include<iostream>
using namespace std;
struct xyq{ //链表。
	int v,next;
}_[1000005];
int head[1000005],tot=2;
void add(int u,int v){ //建有向边。
	_[tot].v=v;
	_[tot].next=head[u]; //插入链表头。
	head[u]=tot; //链表头变成了当前节点。
	++tot;
}
bool mark[1000005],zyl[1000005]; //mark标记数组。
int s[1000005],top=0;
void dfs(int iakioi){ //dfs。
	for(register int i=head[iakioi];i;i=_[i].next){
		if(!mark[i]){ //如果此边没有被访问过。
			mark[i]=1; //对边进行标记。
			dfs(_[i].v); //继续dfs。
			s[top++]=_[i].v; //入栈。
		}
	}
}
int main(){
	int n,m,i,a,b;
	cin>>n>>m;
	for(i=0;i<m;++i){
		scanf("%d %d",&a,&b); //scanf卡常,不然会tle。
		add(a,b); //双向建有向边。
		add(b,a); //同上。
	}
	dfs(1); //题目要求从1号节点开始。
	for(i=0;i<top;++i){
		cout<<s[i]<<endl; //依次输出栈中元素。
	}
	cout<<1; //由于最后的1没有入栈,所以还需输出一个1。
	return 0;
}
```

---

## 作者：carp_oier (赞：1)

# advertisement

这位靓仔，你都来看我的题解了，你为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/17732760.html)看呢。

# prologue

这个题这么水的一个板子题。

# analysis

这个题目我们正反建两条边，在跑欧拉回路的时候，看这个边是不是被走过，走过就不走，跳过这个边。如果没走，就走这条边并且标记这个边走过了。

# code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rl register ll 

const ll N = 2e4 + 10, M = 1e5 + 10;

ll n, m;

ll tot, ne[M], e[M], h[N], ans[M], cnt;

bool rm[M];

inline void add(ll a, ll b)
{
    ne[++tot] = h[a], h[a] = tot, e[tot] = b;
}

inline void dfs(ll u)
{
    for(rl i=h[u]; ~i; i = ne[i])
    {
        if(rm[i]) continue;

        rm[i] = true;

        ll v = e[i];
        dfs(v);
    }
    ans[++cnt] = u;
}

int main()
{
    freopen("1.in", "r", stdin), freopen("1.out", "w", stdout);
    cin >> n >> m;
    
    memset(h, -1, sizeof h);

    for(rl i=1; i <= m; ++ i)
    {
        ll a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs(1);

    for(rl i=cnt; i; -- i) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：Yoimiyamwf (赞：1)

# 题意
给定一张无向图，输出一条路径，使得该路径恰好从两个方向通过无向图的每一条边。
# 分析
一道欧拉回路板子题，貌似没什么好分析的（bushi）

本题我们使用链式前向星存图，这样只需要正反各建一次边，再当成有向图的欧拉回路做即可。

每次通过一条边后可以直接将这条边删去，既可以保证每条边不会被重复走，还能加快运行效率，避免多次执行不必要的循环。
# 代码
```cpp
#include <bits/stdc++.h>
#define in inline
#define rint register int
#define r(a) runtimerror(a)
#define w(a) wronganswer(a)
#define wl(a) wronganswer(a);putchar('\n')
using namespace std;
typedef long long ll;
int n,m,u,v,tot,head[20010],ans[100010],cnt;
template <typename t> void wronganswer(t a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) wronganswer(a/10);
	putchar(a%10^48);
}
template <typename t> in void runtimerror(t &a){
	char ch=getchar();
	t x=1,f=0;
	while(!isdigit(ch)){
		if(ch=='-') x=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		f=(f<<3)+(f<<1)+(ch^48);
		ch=getchar();
	}
	a=x*f;
}
struct Edge{
	int to,nex;
}edge[100010];
in void add_edge(int from,int to){
	edge[++tot]={to,head[from]};
	head[from]=tot;
}
void dfs(int id){
	for(rint i=head[id];i;i=head[id]){//i=head[id]可以保证循环到的下一条边一定是未被删去的边
		head[id]=edge[i].nex;//通过这条边后，从图中删去它
		dfs(edge[i].to);
	}
	ans[++cnt]=id;//储存路径
}
int main(){
	r(n),r(m);
	for(rint i=1;i<=m;i++){
		r(u),r(v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1);
	for(rint i=cnt;i;i--){//按照上面的代码越走到的路径会被放在数组最后，故倒序输出
		wl(ans[i]);
	}
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：1)

~~这道题为啥只是个黄题？~~

------------
注：本题涉及到的知识点较为单一，所以笔者不会过多赘述证明以及原理，望周知！

------------
## 大致思路：
题目上要求的是从 $1$ 号点出发，走过一个回路之后再回到 $1$ 号点，但是要求的**是同一条路径要按照相反的方向各走一遍**，到这里我们必须理解到一点就是，对于图上的点来所，有且仅有一个点要走 $3$ 次，其余的点**都要走两次**。

由于是无向边，而且每条边**要求正反各走一次**，所以**一定存在欧拉回路**。存图时把每条无向边看成两条相反的有向边，**直接利用欧拉回路求解**。但是这样的路径走法可能有许多种，我们只需要输出其中一种即可，至于输出，就在递归完成后直接回溯的同时输出就可以了（用栈的同学小心爆栈）。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, m;
struct Node
{
    int next;
    int to;
} edge[100005];
int head[20009];
int cnt = 0;
void add(int u, int v) 
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
bool vis[200009];
void dfs(int x)
{
    for (int i = head[x]; i; i = edge[i].next)
    {
        if (vis[i] == 1)
        {
            continue;
        }
        vis[i] = 1;
        dfs(edge[i].to);
    }
    cout << x << endl;
}
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        x = read();
        y = read();
        add(x, y);
        add(y, x);
    }
    dfs(1);
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122851950)

---

## 作者：Mars_Dingdang (赞：1)

欧拉回路的模板题，加一点点变形即可。

## 题目大意
给定一个 $n$ 个节点，$m$ 条边的无向图，保证有解，求出从 $1$ 出发并回到 $1$ 的路径，使每条边被沿着正反两个方向恰好经过一次。

## 大体思路
先来看每条边经过一次的欧拉回路如何求解。

有一个基于 dfs 的朴素算法：对于当前节点 $x$，遍历从 $x$ 出发的每一条边 $(x, y)$，若已经访问过则跳过，否则将这条边标记为已访问，递归处理 $y$，将 $y$ 压入答案栈 $ans$。在主函数中调用 dfs 函数，然后倒序输出答案栈即可。

```cpp
int head[maxn], tot = 1, ver[maxn], nxt[maxn];
inline void dfs(int x) {
	for(int i = head[x]; i; i = nxt[i]) {// 遍历每条出边
		int y = ver[i];
		if(!vis[i]) {
			vis[i] = vis[i ^ 1] = 1;// 标记边，成对变换
			dfs(y);
			ans[++t] = y; // 入栈
		}
	}
}
int main () {
	// input, add_edge
	dfs(1);
	for(int i = t; i; i --) writeln(ans[i]);
}
```
由于一个点会被访问多次，每次都会扫描所有与它相邻的边，上述算法的复杂度为 $O(nm)$。易知，大部分边都已经被访问过，所以上述算法有很大提升空间。

考虑优化，即跳过已经访问过的边。这里借鉴 Dinic 算法中的“当前弧优化”算法，每次访问一条边 $(x, y)$ 时，及时修改链表表头 $head_x\leftarrow nxt_i$，即指向下一条边。这样每次取出表头时，自动跳过了已访问的边，复杂度为 $O(n+m)$。

由于欧拉回路 dfs 的层数时 $O(m)$ 级别，很容易造成系统栈溢出，因此可以手写栈 $stk$ 模拟递归过程，利用非递归实现求解。

```cpp
inline void euler() {
	stk[++top] = 1;
	while(top) {
		int x = stk[top], i = head[x];
		while(i && vis[i]) i = nxt[i];
		if(i) {
			stk[++top] = ver[i];
			vis[i] = vis[i ^ 1] = 1; // 成对变换
			head[x] = nxt[i];
		} else {
			top --;
			ans[++t] = x;
		}
	}
}
```

回到本题。本题与模板唯一的区别，就是每条边被允许正反访问各一次。关注到上方代码中正是利用成对变换（即 $2i \oplus 2i+1 = 1$）保证每条边仅被访问一次，我们只需删去上方带注释的那一行即可。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef double db;
const int maxn = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, m, head[maxn], tot = 1, ver[maxn], nxt[maxn];
inline void add(int u, int v) {
	ver[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
	ver[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
}
int ans[maxn], t, stk[maxn], top;
bool vis[maxn];
inline void euler() {
	stk[++top] = 1; // 模拟系统栈 
	while(top) {
		int x = stk[top], i = head[x];
		while(i && vis[i]) i = nxt[i];
		if(i) {
			stk[++top] = ver[i];
//			vis[i] = vis[i ^ 1] = 1;
			head[x] = nxt[i];// 更新表头 
		} else {
			top --;
			ans[++t] = x;
		}
	}
}
int main () {
	read(n); read(m);
	rep(i, 1, m) {
		int x, y;
		read(x); read(y);
		add(x, y);
	}
	euler();
	Rep(i, t, 1) writeln(ans[i]);
	return 0;
}
```

---

## 作者：wtyqwq (赞：1)

- [P6066 Watchcow](https://www.luogu.com.cn/problem/P6066)

- 解题思路：这道题近似于欧拉回路的模板题，只需将模板中的 $vis_i$ 数组去掉即可。原来要加上它原因是，原先一条边只需走一遍，所以正向访问一条边的时候，不仅要更新表头，去掉当前访问的边，还要把反向的边给打上标记（反边同样不能走）。而这道题要求：每条路必须从两个方向各走恰好一遍。所以直接去掉 $vis_i$ 的标记即可，仍然更新表头。这样每条边恰好经过两次，符合题目要求。

------------
```cpp
#include <cstdio>
#define N 10005
#define M 100005
int head[N], nex[M], ver[M], tot;
int ans[M], sta[M], top, n, m, cnt;
void add(int x, int y) {
	ver[++tot] = y;
	nex[tot] = head[x];
	head[x] = tot;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y), add(y, x);
	}
	sta[++top] = 1;
	for (int x, i; top; ) {
		i = head[x = sta[top]];
		if (i == 0)
			--top, ans[++cnt] = x;
		else {
			sta[++top] = ver[i];
			head[x] = nex[i];
		}
	}
	for (int i = cnt; i >= 1; --i) printf("%d\n", ans[i]);
	return 0;
}
```
- 算法标签：欧拉路问题（深度优先搜索）。

- 时间复杂度：$O(N+M)$。

- 空间复杂度：$O(N+M)$。

- 期望得分：$100$ 分。[提交记录](https://www.luogu.com.cn/record/32588655)。

---

## 作者：LongDouble (赞：1)

好像没人写有代码的题解啊。

------------

##### **解题思路**：

这题是很明显的求**欧拉回路**题。

不同的是，这题中每条边得从两个方向各走一遍。

既然得从两个方向各走一遍，就可以把每条双向边看成两条单向边。

再跑一遍有向图的欧拉回路即可。

##### **代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010, M = 500010;
int head[N], ver[M], pre[M];
bool v[M];
int n, tot, m;
stack<int> q;

void add(int u, int v)
{
	ver[++tot] = v;
	pre[tot] = head[u];
	head[u] = tot;
}

void dfs(int x)
{
	for (int i = head[x]; i; i = pre[i])
		if (!v[i])
		{
			v[i] = 1;
			dfs(ver[i]);
			q.push(ver[i]);
		}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v);
		add(v, u);
	}	
	dfs(1);
	q.push(1);
	while (!q.empty())
	{
		printf("%d\n", q.top());
		q.pop();
	}
	return 0;
}
```


---

## 作者：Misophiliac (赞：0)

[题目](https://www.luogu.com.cn/problem/P6066)

### 前置知识

链式前向星存图。

### 题目大意

给出一个无向图，求一条从 $1$ 号点出发，最后回到 $1$ 号点的路径，要求每一条边从两个方向经过恰好一次。

容易看出这就是欧拉回路模板，稍微改了一下而已。

### 什么是欧拉回路

如果你没听说过欧拉回路和欧拉路径，这里简单介绍一下：欧拉路径其实就是一个图中经过每条边恰好一次的一条路径，如果这条路径的起点和终点相同就叫欧拉回路。一笔画问题本质上就是寻找欧拉路径和欧拉回路。

欧拉回路存在的充要条件是每个点的度（这个点连边的数量）是偶数。本题明确说明存在欧拉回路，所以不需要判断。

### 关于本题做法

深搜，从 $1$ 号点开始遍历每一条边并标记已访问，访问过的边不再访问。由于题目要求正反各走一次，于是对每一条无向边，我们改成分别建立两个方向的有向边。搜索中遇到一个点就以它为起点进行递归搜索，然后输出它即可。

### 代码

```c
#include <stdio.h>
#define N 10005
#define M 50005
int getint() {
    int x = 0;
    for (char c = getchar(); c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + (c ^ '0');
    return x;
}
int tot = 1, hd[N], nxt[M<<1], to[M<<1];
void add(int u, int v) {
    nxt[++tot] = hd[u];
    to[tot] = v;
    hd[u] = tot;
    return;
}
void dfs(int u) {
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v) {
            to[i] = 0;//表示该边不能再次经过
            dfs(v);
        }
    }
    printf("%d\n", u);//注意如果入栈（有些dalao的方法）在最前，直接输出则在最后
    return;
}
int main() {
    getint();//我们并不需要n
    for (int m = getint(); m; --m) {
        int u = getint(), v = getint();
        add(u, v);
        add(v, u);
    }
    dfs(1);
    return 0;
}
```

---

