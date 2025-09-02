# [ABC077D] Small Multiple

## 题目描述

给定一个整数 $K$。求一个 $K$ 的正整数倍 $S$，使得 $S$ 的数位累加和最小。

## 说明/提示

- $2 \le K \le {10}^5$；
- $K$ 是整数。

## 样例 #1

### 输入

```
6```

### 输出

```
3```

## 样例 #2

### 输入

```
41```

### 输出

```
5```

## 样例 #3

### 输入

```
79992```

### 输出

```
36```

# 题解

## 作者：AgrumeStly (赞：42)



### solution

我们先考虑暴力，把 $K$ 的倍数枚举，每枚举一个取每位求和。  

这肯定超时，关键是循环取每位爆炸，那么我们不妨想，一个数的各个位数和是如何求出的。



先看个位，$1$ 的位和为 $1$，$2$ 就在 $1$ 的前提下 $+1$ 以此类推，就能求出个位位和。  

再看其他位，无非就是 $n$ 个 $10$ 加上若干 $1$，思考 $10$，我们可以用 $1 \times 10$ 来表示，那各位和仍为 $1$。



综上，我们可以整理出两种状态：$+1$ 与 $\times 10$，那么 $+1$ 是各位和 $+1$，可 $\times 10$ 各位和却不便，故可以转换为 **01 bfs**，如图



![](https://cdn.luogu.com.cn/upload/image_hosting/qhejrx3s.png)



但是我们发现还有一个问题，那就是这种方法是会超 $\sf long~long$ 的，难道我们还要用高精吗？  

当然不，我们发现我们欲求 $K$ 的倍数，那么我们在每次 $\times 10$ 是 $\% K$ 就行了，因为这样余数不变，不影响结果。



讲完基本思路，讲一下如何实现。



我们知道 bfs 一般会用队列，那么在 01 bfs 中，我们会用到双向队列 $\rm deque$。  

`#include <queue>` 与 `#include <deque>` 均包含 $\rm deque$，可以用任意一个库。



### Code



```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
using namespace std;

const int NR = 1e6 + 5;
int k;
int ans;
bool vis[NR];
struct node {
	int num, w;
};
deque<node> d;

void bfs() {
	d.push_front(node{1, 1});
	vis[1] = true;
	while (!d.empty()) {
		int num = d.front().num, w = d.front().w;
		d.pop_front();
		if (num == 0) {
			cout << w << endl;
			return;
		}
		if (!vis[10 * num % k]) {
			d.push_front(node{10 * num % k, w});
			vis[10 * num % k] = true;
		}
		if (!vis[num + 1]) {
			d.push_back(node{num + 1, w + 1});
		}
	}
	return;
}

int main() {
	cin >> k;
	bfs();
	return 0;
}
```





---

## 作者：sky_of_war (赞：29)

考虑极端情况数字是可能爆`long long`甚至`__int128`这种东西的

所以思考的方向是对于数位进行处理

考虑每一个数都能从$1$通过以下两种操作来得到：

 - 乘$10$，数位和不变
 - 加$1$，并且数位和$+1$
 
在$\text{mod}\ k$的意义下进行计算，把$0 \sim k-1$中的每一个数看成一个点，$i$向$i+1$连一条权值为$1$的边，$i$向$10i$连一条权值为$0$的边，从$1$到$0$跑最短路即可

这时有一个问题，上面说了，$+1$的时候必须保证数位和$+1$，所以连续走$10$次及以上权值为$1$的边是不合法的。但可以发现这样走一定不是最短路（可以在乘$10$之前走$1$步然后再乘$10$），所以不影响答案。

我们其实也可以得到一种等价的做法：

$k$个点表示$\text{mod}\ k=0\sim k-1$的最小数字和，起点是$1\sim k-1(d_i=i)$，终点为$0$，$x$向$(10x+0 \sim 9) \text{mod}\ k$连边权为$0\sim 9$的边，跑最短路。
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1e5 + 10;
int n, m, first[MAXN], tot, d[MAXN], s, t;

struct edge { int from, v, w; } e[20 * MAXN];
struct Node
{
	int x, d;
	bool operator <(const Node &b)const
	{
		return d > b.d;
	}
}cyc;
priority_queue<Node> q;
inline void insert(int u, int v, int w)
{
	tot++; e[tot].v = v; e[tot].w = w; e[tot].from = first[u]; first[u] = tot;
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for (register int i = 1; i <= n; i++)
		for (register int j = 0; j <= 9; j++)insert(i, ((i - 1) * 10 + j) % n + 1, j);
	for (register int j = 1; j <= 9; j++) insert(0, j + 1, j);
	s = 0; t = 1;
	memset(d, 0x3f, sizeof d);
	d[s] = 0; q.push((Node) { s, d[s] });
	while (!q.empty())
	{
		cyc = q.top(); q.pop();
		if (cyc.d != d[cyc.x])continue;
		register int x = cyc.x;
		for (register int i = first[x]; i; i = e[i].from)
			if (d[e[i].v] > d[x] + e[i].w)
			{
				d[e[i].v] = d[x] + e[i].w;
				q.push((Node) { e[i].v, d[e[i].v] });
			}
	}
	return cout << d[t], 0;
}
```

---

## 作者：zjh111111 (赞：20)

$AT3621$ $ $ [ARC084B] $Small\ Multiple$

[link](https://www.luogu.com.cn/problem/AT3621)

难度虚高，大概绿题。

设 $f(s)$ 为 $s$ 各个位数上的和

我们要求的 $ans$ 满足 $ans\equiv 0\ $ $\pmod k\ $ 且 $\ f(ans)$ 最小

考虑 $dp[i]$ 表示 $\min {f(x)}\ $ $(\ x \equiv i\pmod k)$ 

怎么转移，

考虑在$\ x$ $(\ x \equiv i\pmod k)$  后加上一个数 $y(y \in [0,9]),$ 那么易得加上后的余数为
$$(x\times 10+y) \mod k$$
即
$$(i\times 10+y) \mod k$$

所以
$$dp[(i\times 10+y)\mod k] = \min (dp[i]+y)$$

$ $

有木有感觉和松弛操作的方程很像？

接下去就建图确定转移顺序，再跑一遍单源最短路径板子即可，答案即 $dis[0]$

边是 $k$ 的 $10$ 倍，复杂度带只 $\log$

$\mathcal{O(k\log_{2} k)}$

$code:($ 大半部分都是 dijkstra 板子，核心就几行 $)$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long LL;
template <typename T>
inline void read(T &x) {
    char c = getchar(); int w = 1; x = 0;
    while (!isdigit(c))
        (c == '-') && (w = -w), c = getchar();
    while (isdigit(c))
        x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
    x *= w;
}

const int N = 100005;
int k, cnt = 0, dis[N], head[N];
struct edge {
    int dis, to, nxt;
} e[N<<4];//k的10倍，这里开了16倍
struct node {
    int u, d;
    node(int x, int y) : u(x), d(y) { }
    inline bool operator < (const node & a) const {
        return d > a.d;
    }
} ;
inline void add(int u, int v, int w) {
    e[++ cnt].dis = w; e[cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
}
inline void Dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    priority_queue<node> q;
    q.push(node(s, 0));
    while (!q.empty()) {
        node h = q.top(); q.pop();
        int u = h.u, d = h.d;
        if (d != dis[u]) continue;
        for (register int i=head[u]; i; i=e[i].nxt) {
            int to = e[i].to;
            if (dis[u] + e[i].dis < dis[to]) {
                dis[to] = dis[u] + e[i].dis;
                q.push(node(to, dis[to]));
            }
        }
    }
    return;
}         //板子
signed main() {
    read(k);
    for (register int i=0; i<k; ++i)
        for (register int j=0; j<10; ++j) {
            add(i, (i*10+j)%k, j);
        }
    for (register int i=1; i<10; ++i)
        add(k, i%k, i);//建虚点,第一位不能为0
    Dijkstra(k);
    cout << dis[0];
    return 0;
}
```


---

## 作者：xiejinhao (赞：14)

# AT3621【Small Multiple】 题解  

[题目传送门](https://www.luogu.org/problemnew/show/AT3621)

虽然说代码很短，但是卡了我很久……**~~说好的水题呢？~~**

好了，这个题目其实还是很~~水~~的。

------------

**题意解读**：

题目就是让你把整数$K$翻$n$倍，使得各数位之和最小。

------------

**解题思路**：

首先我们假设满足$XmodK=0$，且$X$为我们要求的那个数。

那么我们对$X=1$有两种操作：

1. $X*=10$，那么我们会发现，这个数的**各位数之和没变**，其代价为$0$；

1. $X+=1$，同上，$X$比上次多了$1$，就是个位数字多了$1$，那么这次操作的代价为$1$；

然后我们**只要判断是不是倍数就行了**，取模操作就不用解释了。

~~至于那些同余和最短路，本蒟蒻表示一窍不通~~

所以**暴力打个$BFS$，反正$BFS$应该是正解吧？**

然后具体实现就是使用一个双端队列，把代价为$0$的操作放队首，代价为$1$的放队尾，同时用个$pair$存一下当前$X$和数位之和。

~~由于上面解释的很清楚了，那我下面就只放代码了。~~

$Code$|~~正解~~
------------
```cpp
    #include<cstdio>
    #include<queue>
    #define put(x,y) make_pair(x,y)
    using namespace std;
    const int SIZE=1e6;
    deque< pair<int,int> > p;
    bool vis[SIZE];
    int k;
    void bfs() {
        while(p.size()) {
            pair<int,int> now=p.front(); p.pop_front();
            if(vis[now.first]) continue;
            vis[now.first]=true;
            if(!now.first) {
                printf("%d\n",now.second);
                return;
            }
            p.push_front(put(now.first*10%k,now.second));
            p.push_back(put((now.first+1)%k,now.second+1));
        }
    }
    int main() {
        scanf("%d",&k);
        p.push_front(put(1,1));
        bfs();
        return 0;
    }
```





---

## 作者：Otomachi_Una_ (赞：9)

我第一次拿到这个题的时候想法是暴力枚举，结果发现

$k\leq10^5$ 而且这是一道省选题，就知道凉凉。

先引用一个小公式：

$\overline{ab}=10*a+b $ 

这是一道 bfs 的题，先定义一个 $f_i$ 数组表示余数为 $i$ 的数字和最小值，初始化时设为无穷大。

再定义一个结构体 num 存入一个数的数字和和余数。

对于每一次，先让一位数和他的余数一起入队，每一次只要队列还有元素，就取出队首，然后在最后加上 $1,2,3...,9$，算出余数再入队，代码如下：

```cpp
for(int i=0;i<=9;i++){//枚举下一位
	ds.r=(10*dy.r+i)%k;
	ds.s=dy.s+i;
	q.push(ds);
}
```

特别的，如果队首都已经不是最优解了，就继续下一个回合，不然更新 $f_i$。

## _Code_

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
#define ll long long
const int MAXN=1e5+5;
int f[MAXN];//f[i]表示余数为i数字和最小值
struct num{
	int r=0;//余数
	int s;//数字和
}ds,dy;
queue <num> q;
int k;
int main(){
	for(int i=0;i<MAXN;i++)
		f[i]=1e9;
	cin>>k;
	for(int i=1;i<=9;i++){
		ds.r=i%k;
		ds.s=i;
		q.push(ds);
	}
	while(!q.empty()){
		dy=q.front();
		q.pop();
		if(f[dy.r]<=dy.s)
			continue;
		f[dy.r]=dy.s;
		for(int i=0;i<=9;i++){//枚举下一位
			ds.r=(10*dy.r+i)%k;
			ds.s=dy.s+i;
			q.push(ds);
		}
	}
	cout<<f[0];
}
```







---

## 作者：是个妹子啦 (赞：6)

第一次做这样的题

题意：给定一个整数$K$.求一个$K$的整数倍$SUM$,使得$SUM$的数位累加和最小

纪念$ATcoder$ 神题$Orz$

考虑数位取模套路，$*10$对答案贡献为$0$，$+1$贡献为$1$。

跑一个同余最短路，在$(\mod K)$意义下建图，$i$向$i+1$连一条边权为$1$的边，$i$向$10i$连一条边权为$0$的边，

最短路的意义就是产生一个能整除$K$的正整数在数位上所需的最小代价

边权只有$0$和$1$       $01BFS$

注意优先把贡献为$0$扔到队头，保证每次从队首取出来的是当前队中距离源点最短的节点

$O(n+m)$

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 1e5 + 5;
struct node{int num,w;};
deque<node>q; int K;
bool v[N];
void bfs(){
    while(!q.empty()){
        node x = q.front(); q.pop_front();
        if(v[x.num]) continue;
        v[x.num] = 1;
        if(!x.num){ printf("%d",x.w); return ; }
        q.push_front((node){x.num*10 % K,x.w});
        q.push_back((node){(x.num+1) % K,x.w + 1});
    }
}
int main(){
    scanf("%d",&K);
    q.push_front((node){1,1});
    bfs();
}
```



---

## 作者：flyfree (赞：6)

做法很简单，但是不太好理解（~~主要是我太菜了~~）

思路：

第一步：

首先看这个数据范围，如果先求出来**k的整数倍**再**把每一位相加**的话，肯定会炸。

所以考虑怎样转化一下，**直接求位数和**。

建图，每个数x向x+1连边权为1的边，向x * 10连边权为0的边，dis[1]=1，跑01bfs，每个点的dis值就是位数和。（这个比较好理解）

第二步：

但是k的倍数又没有上限，肯定不能直接这样建。所以就修改一下每个节点的含义，节点x表示**模k为x**。

易知，对于一个x(x<k),如果

(x+1)%k==y，且 (x * 10)%k==z

那么

对于**所有模k等于x的数a**，都有

(a+1)%k==y，(a * 10)%k==z

这样，我们的图就是有限的了，共k个点，分别是0~k-1。

建图就是对于每个点x，向(x+1)%k连边权为1的边，向(x * 10)%k连边权为0的边。

初始化依然是dis[1]=1，求出dis[0]即为答案。

~~为什么呢~~

首先这样求出来的dis[0]一定满足这个含义：

**从一个%k==1的数变成k的倍数，位数和至少要增加多少。**

然后我们肯定想让dis[1]尽量小，就只能是1了，所以初始化dis[1]=1。换句话说，节点1的意义就是1，而不是所有%k==1的数。

那为什么其他节点x的意义是所有%k==x的数，而不是x呢？

因为从节点1走到x的过程中，可能经过了若干次 * 10，所以节点x不一定是k的多少倍+x。

具体实现：

我手写的队列，大概就是边权为0的加到q1中（相当于双向队列加入队首），边权为1的加到q2中，每次把q1清空后再从q2取出队首。

不过手写的有很多容易忽略的细节，强烈建议大家用STL的双向队列。

上代码~

```cpp
#include <cstdio>
using namespace std;
const int N=100005;
int p,dis[N],q1[N],l1,r1,q2[N],l2,r2;
bool vi[N][2],flag;
//vi[x][0]表示节点x是否加入过q1
//vi[x][1]表示节点x是否加入过q2
int read()
{	char x=getchar();
	while(x<48||x>57) x=getchar();
	int ans=0;
	while(x>=48&&x<=57)
	{	ans=(ans<<1)+(ans<<3)+(x^48);
		x=getchar();
	}
	return ans;
}
void add(int num)
{	int x;
	x=(num+1)%p;
	if(!vi[x][1]&&!vi[x][0])
	{	vi[x][1]=true;dis[x]=dis[num]+1;
		q2[r2]=x;r2++;
	}
	x=(num*10)%p;
	if(!vi[x][0])
	{	vi[x][0]=true;dis[x]=dis[num];
		q1[r1]=x;r1++;
		if(x==0) { flag=true;return;}
	}
}
void solve()
{	l1=1;r1=2;l2=r2=1;
	q1[1]=1;dis[1]=1;vi[1][0]=true;
	while(r1>l1||r2>l2)
	{	while(r1>l1)
		{	add(q1[l1]);l1++;
			if(flag) return;
		}
		while(r2>l2)
		{	if(vi[q2[l2]][0]) {l2++;continue;}
			vi[q2[l2]][0]=true;add(q2[l2]);l2++;
			if(flag) return;
			break;
		}
	}
}
int main()
{	p=read();
	solve();
	printf("%d\n",dis[0]);
	return 0;
}
```


---

## 作者：sh1kong (赞：2)

[In Luogu](https://www.luogu.com.cn/problem/AT_arc084_b)

写自梦熊模拟赛赛后补题。梦熊模拟赛出原题，望周知。

为什么没有人写好想又好写的 DP？

解：考虑 DP。

记 $f_{i,j}$ 表示当前的数字为 $i$，且 $i$ 的数位和为 $j$，此时的 $i$ 是否能被组成。

那么就是很板的数位 DP 了，每次枚举下一位填什么，转移即可。

打一下表，发现答案不会超过 $50$，故当数字和 $j > 50$ 时，返回即可。 

值得注意的是，由于数字 $i$ 可能会很大，需要每次转移时对 $k$ 进行取模。

给一下代码吧，个人认为码风还是好的。

```cpp
ll k;

ll T = 0;

bool vis[N][52];

void dfs(ll digit, ll sum)
{
	if (digit > 50) return ;
	if (vis[sum][digit]) return ;
	vis[sum][digit] = true;
	for (ll i = 0; i <= 9; i ++ ) dfs(digit + i, (sum * 10 + i) % k);
}

signed main()
{
//	freopen("min.in", "r", stdin);
//	freopen("min.out", "w", stdout);

	FstIO; 

	cin >> k;
	for (ll i = 1; i <= 9; i ++ ) dfs(i, i);
	for (ll i = 1; i <= 50; i ++ )
	{
		if (vis[0][i]) 
		{
			cout << i << '\n';
			return 0;
		}
	}
}
```

---

## 作者：xcyle (赞：2)

~~蒟蒻的解法和正解本质上差不多，但难写INF倍~~

设乘的倍数为$x$，先将$x$拆位，那么$K\times x$就是由若干个$(0 - 9) \times x$加起来的，像列竖式那样

这个时候开始dp，设$f_i$表示当前最后若干位是$i$，之前的最小的位数和，转移的时候枚举$x$的新的最低位，只有9种

因此考虑建图，在图上跑最短路即可（$i$节点的最终答案需要加上$i$）

---

## 作者：HYdroKomide (赞：1)

# **正文：**
## 题意:
每一个数都可以进行如下操作：
1. 将其 $\times 10$ ，位数之和不变，所以此边对应权重为 $0$。
2. 将其 $+1$ ，位数之和也随之 $+1$ 其对应权重为 $1$。

如果保存那个数它本身可能会爆long long，所以我们每一次只存储其权重，将其原值 $\mod k$ 即可。

使用 0-1 $bfs$ 进行搜索，从 $1$ 开始进行搜索，将权重为 $0$ 的结点推入队首，权重为 $1$ 的结点推入队尾，从队首至队尾遍历，当判断到 $k$ 的倍数时进行输出即可。
## 程序如下:
```cpp
#include<cstdio>
#include<deque>
using namespace std;

int k;
bool vis[100005];              //用来存已访问的结点

struct node{
	int num,w;                 //w存到此结点的代价和
};

deque<node> d;                 //定义一个双端队列

void bfs(){
	d.push_front(node{1,1});   //从1开始，1的代价为1
	vis[1]=true;
	while(!d.empty()){
		int num=d.front().num,w=d.front().w;
		d.pop_front();
		if(num==0){
			printf("%d\n",w);  //ATcoder题都需要换行
			return;
		}
		if(!vis[num*10%k]){
			d.push_front(node{num*10%k,w});
			vis[num*10%k]=true;
		}
		if(!vis[(num+1)%k])d.push_back(node{(num+1)%k,w+1});
		//队尾不需要标记已访问
	}
	return;
}

int main(){
	scanf("%d",&k);
	bfs();
	return 0;
}
```
# **THE END**

---

## 作者：极寒神冰 (赞：1)

一个数$x ->x+1$使数位和$+1$，$x->10\times x$和不变。

那考虑在$\mod k$意义下的每个数之间的关系，可以建出一个$k$个点的图，编号为$0$~$(k-1)$，其中$0$~$(k-1)$的点向$(10 \times i) \bmod k$ ，$(10 \times i+1) \bmod k$ ，$(10 \times i+2) \bmod k$ $……$ $(10 \times i +9) \bmod k$ ，边权分别为$0,1,2……9$。


而$dis[x]$表示到数$x$所需要的代价

因为所求为$k$的整数倍的最小数位和，所以可以分别从$1$~$9$分别跑最短路，答案为$min(dis[0])$

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
const int mod=19930726;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=1e5+10;
int n,res=inf;
int dis[N],vis[N];
struct edge
{
	int to,val;
};
std::vector<edge>e[N];
int spfa(int s=1)
{
	deque<int>q;
	fill(dis,dis+n+1,inf);dis[s]=0;
	q.push_back(s);
	vis[s]=1;
	while(q.size()>0)
	{
		int u=q.front();
		q.pop_front();
		vis[u]=0;
		for(auto vv:e[u])
		{
			int v=vv.to,val=vv.val;
			if(dis[v]>dis[u]+val)
			{
				dis[v]=dis[u]+val;
				if(!vis[v]) {
					vis[v]=1;
					q.push_back(v);
				}
			}
		}
	}
	return dis[0]+s;
}

signed main()
{
	n=read();
	for(int i=1;i<n;i++) for(int j=0;j<=9;j++) e[i].push_back((edge){(10*i+j)%n,j});
	R(i,1,9) res=min(res,spfa(i));
    printf("%lld\n",res);
}	
```



---

## 作者：zzq_AC (赞：1)

01bfs做法
```
# include <cstdio>
# include <queue>
# include <cstring>
# include <iostream>
using namespace std;

int k;
bool vis[100005];//余数为j有没有被访问过
struct node{
	int num, w;//余数，数码和
};
deque<node> q;
void bfs()
{
	q.push_front(node{1, 1});
	vis[1] = true;
	while(!q.empty()){
		node temp = q.front();
		q.pop_front();
		if(temp.num == 0){
			cout << temp.w << endl;
			return;
		}
		if(!vis[(temp.num * 10) % k]){
			q.push_front(node{(temp.num * 10) % k, temp.w});
			vis[(temp.num * 10) % k] = 1;
		}
		q.push_back(node{(temp.num + 1) % k, temp.w + 1});
	}
	return;
}
int main()
{
	cin >> k;
	bfs();
	return 0;
}
```


---

## 作者：MilkyCoffee (赞：0)

这道题的解法是 $01bfs$ + $deque$。

不难发现，每一个数都可以从 $1$ 通过以下两种途径得到

- $+1$

- $*10$

而这两种途径所增加的权重（数字和）分别为：

- $1$

- $0$

我们可以利用 $deque$ 的特性:两端都能 $push$ 数字

但是如果把每种数字都存下来，爆 $long\ long$ 也是有可能的。而我们判断他是不是一个数的倍数，只需要知道 $n \mod k$ 就可以了。

将权重为 $0$ 的结点 $push$ 入双端队列的队首，将权重为 $1$ 的结点 $push$ 入双端队列的队尾，然后从队首到队尾遍历即可。

```
// syx AK IOI
#include <iostream>
#include <cstdio>
#include <deque>
#include <cstring>
using namespace std;

const int COL = 1e5 + 5;

struct node {
	int x, res;
	// num ans
};

deque <node> d;
int k;
bool vis[COL];

void bfs() {
	memset(vis, 0, sizeof(vis));
	d.push_front((node){1, 1});
	vis[1] = 1;
	while (!d.empty()) {
		int x = d.front().x, res = d.front().res;
		d.pop_front();
		if (x == 0) { // x % k == 0 -> 是 k の倍数
			cout << res << endl;
			return ;
		}
		// * 10
		if (!vis[x*10%k]) { // didn't found
			d.push_front((node){x * 10 % k, res}); // 不变
			vis[x*10%k] = 1;
		}
		// + 1
		if (!vis[(x+1)%k]) { // didn't found
			d.push_back((node){(x + 1) % k, res + 1}); // changed
		}
	}
	return ;
}

int main() {
	scanf("%d", &k);
	bfs();
	return 0;
}
```

---

