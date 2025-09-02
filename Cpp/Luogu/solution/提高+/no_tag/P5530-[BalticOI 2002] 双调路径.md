# [BalticOI 2002] 双调路径

## 题目描述

如今的道路收费发展很快。道路的密度越来越大，因此选择最佳路径是很现实的问题。城市的道路是双向的，每条道路有固定的旅行时间以及需要支付的费用。

路径是连续经过的道路组成的。总时间是各条道路旅行时间的和，总费用是各条道路所支付费用的总和。一条路径越快，或者费用越低，该路径就越好。严格地说，如果一条路径比别的路径更快，而且不需要支付更多费用，它就比较好。反过来也如此理解。如果没有一条路径比某路径更好，则该路径被称为最小路径。

这样的最小的路径有可能不止一条，或者根本不存在路径。

问题：读入网络，计算最小路径的总数。费用时间都相同的两条最小路径只算作一条。你只要输出不同种类的最小路径数即可。

## 说明/提示

**数据范围：**
- $1\leq{n}\leq100$，$0\leq{m}\leq300$。
- $1\leq{s,e,p,r}\leq{n}$，$0\leq{c,t}\leq100$。
- $s\neq{e}，p\neq{r}$。

**样例解释：**

![样例输入](https://z3.ax1x.com/2021/09/24/4DN3xP.png)

从 $1$ 到 $4$ 有 $4$ 条路径。为 $1\rightarrow 2\rightarrow 4$（费用为 $4$，时间为 $5$），$1\rightarrow 3\rightarrow 4$（费用为 $4$，时间为 $5$），$1\rightarrow 2\rightarrow 3\rightarrow 4$（费用为 $6$，时间为 $4$），$1\rightarrow 3\rightarrow 2\rightarrow 4$（费用为 $4$，时间为 $10$）。

$1\rightarrow 3\rightarrow 4$ 和 $1\rightarrow 2\rightarrow 4$ 比 $1\rightarrow 3\rightarrow 2\rightarrow 4$ 更好。有两种最佳路径：费用为 $4$，时间为 $5$（$1\rightarrow 2\rightarrow 4$ 和 $1\rightarrow 3\rightarrow 4$）和 费用为 $6$，时间为 $4$（$1\rightarrow 2\rightarrow 3\rightarrow 4$）。

## 样例 #1

### 输入

```
4 5 1 4
2 1 2 1
3 4 3 1
2 3 1 2
3 1 1 4
2 4 2 4```

### 输出

```
2```

# 题解

## 作者：哲学家 (赞：12)

## [题目描述](http://ybt.ssoier.cn:8088/problem_show.php?pid=1505)
### 题目大意
在一张无向图中，我们给出一些边，这一条边有我们对应需要的通过这条边的时间和花费，从A点到B点可能有N多种方式到达，对于每种方式当我们的花费和时间都比其中一种方式大时，此种方式不是最短路，但是如果一种方式花费小而时间大，一种方式时间大而花费小，这样我们无法比较，两种方式都暂时属于我们的最短路。
### 题目分析
本题的题目要求求出从 s 到 e 的最小路径条数

在我们理解了题意之后，应该是很容易就能想出双限制的最短路做法（把我们的dis值用一个二维数组来表示）

普通最短路就是距离限制，我们通过 dis[x] 表示到达点 x 的最小距离

本题最短路则是限制距离（时间）和花费，那我们就加一维使其变成二维数组，那么我们的dis就会有两个值来控制。

—— 用 dis[x][y] 表示到达点 x 花费 y 块钱的最小距离（时间）

最后枚举花费 i ，然后找到满足最短路径的点 dis[e][i]，有多少这样的点我们就可以用一个累加器ans来累计答案，最后输出就行了

怎么判断是否是满足最短路径的点？

设一个变量 last（我用的是last，自己可以随便定义） == 0x3f3f3f3f（极大值就可以） ，如果当前的 dis[e][i] <ans ，则是满足我们条件的点（ ans 表示的是时间）

### 代码
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
int n,m,st,ed;
struct edge{结构体
	int v;
	int w;
	int t;
};
vector<edge> e[105];//结构体数组e中有 i v w t四个数表示从i点到v点的距离为w，时间为t
int d[105][100005];//这个d数组第一维是表示第几种方式第二维表示时间值表示金钱（花费）
bool vis[105];//记录是否重复判断
int main() {
	memset(vis,0,sizeof(vis));
	memset(d,127,sizeof(d));//“127”代表的是一个极大的值
	cin>>n>>m>>st>>ed;
	for(int i=1;i<=m;i++){
		int u,v,w,t;
		cin>>u>>v>>w>>t;
		e[u].push_back((edge){v,w,t});
		e[v].push_back((edge){u,w,t});
	}//预处理
	queue<int> q;
	q.push(st);
	vis[st]=1;
	for(int i=1;i<=10000;i++)d[st][i]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i].v,w=e[u][i].w,t=e[u][i].t;
			bool flag=0;
			for(int j=0;j<=10000-w;j++){
				if(d[v][j+w]>d[u][j]+t){
					d[v][j+w]=d[u][j]+t;
					flag=1;
				}
			}
			if(flag){
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}//spfa的模板
	int ans=0,last=99999999;
	/*
	for(int i=1;i<=n;i++){
		for(int j=1;j<=15;j++){
			cout<<d[i][j]<<' ';
		}
		cout<<endl;
	}
	*/ //当时调试用的，不影响
	for(int i=0;i<=10000;i++){
		if(d[ed][i]>=last)continue;
		last=d[ed][i];
		ans++;//ans累加，输出答案
	}
	cout<<ans;
	return 0;//结束程序
}
```

---

## 作者：ctj12461 (赞：12)

> 大家可以到[这个链接](https://ctj12461.netlify.com/2019/d8d9cac8)或者[这个链接](https://www.cnblogs.com/ctjcalc/p/d8d9cac8.html)阅读。

这是一道双权值`SPFA`树状数组优化最短路。

# 算法分析

首先，我们从题意中知道这个最短路是需要维护两个权值的。很显然，暴力枚举两种值是会`TLE`的，所以，我们需要做一些转化。**当费用确定时，时间更短的路径是更优的。** 于是，**我们借用背包`DP`的思想，把费用看作需要消耗的容量，时间看做价值。** 我们把各种状态加上一维，第一维表示结点编号，第二维表示费用，就是背包`DP`的状态，即$dis_{i,j}$，**表示在**$i$**这个结点时，当费用为**$j$**时所需最小时间**，则有：
$$ dis_{i,j}=min\{f_{k,i-cost_{k,i}}+time_{k,i} | edge_{k,i}\} $$
枚举每一条与$i$相连接的点$k$，从$k$结点转移到$i$结点，费用加了$cost_{k,i}$，时间加了$time_{i,j}$。**再从最短路的角度看，我们还是跑`SPFA`，在队列中存两个值：下一个结点编号与费用。**在对应的$dis$里更新。

最后，我们再统计一下答案，记一个$now$ 初始$now= \infty$费用不断递增，如果$dis_{t,i} < now$，即又有一条可行的路径，答案加一，$now = dis_{t,i}$。

但是，~~时间还是卡不过去~~。有没有什么技巧能够跑更快吗？

考虑这样的一个剪枝：**对于状态**$dis_{i,j}$**，如果**$min\{dis_{i,0 \rightarrow j}\} > f_{i,j}$**，则进行更新。**为什么这是正确的呢？看一看$dis_{i,j}$的定义：**表示在**$i$**这个结点时，当费用为**$j$**时所需最小时间**。如果费用增加了，时间却没有减少，走这条路显然没有之前的那条好。具体的，**我们可以用树状数组维护区间**$[0,j]$**的最小值**。当然线段树也行，但是我们不需要那么多的功能，并且线段树常数时间较大，这道题不适用。

# 代码实现

> 超长代码警告

```cpp
#include <bits/stdc++.h>
using namespace std;
// IO优化
namespace IO
{
    char buf[1<<15],*fs,*ft;
    char out[1<<28],*fe=out;
    inline char getc(){
        return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++;
    }
    
    template <typename T>
    inline void read(T &x){
        x=0;
        bool f=false;
        char ch=getchar();
        while (!isdigit(ch) && ch^'-') ch=getchar();
        if (ch=='-') f=true, ch=getchar();
        while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
        if(f)
            x=-x;
        return;
    }

    
    inline void flush(){
        fwrite(out,1,fe-out,stdout);
        fe=out;
    }

    template <typename T>
    inline void writeln(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++='\n';
    }

    template <typename T>
    inline void writesp(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++=' ';
    }
}

int tot,n,m,s,t,ans;
// 树状数组类体
class BinaryIndexedTree
{
private:
    int Arr[100005];
    int lowbit(int x){
        return x&-x;
    }
public:
    void modify(int pos,int val){ // 修改，维护最小值
        pos++;
        for(;pos<=n*100;pos+=lowbit(pos)){
            Arr[pos]=min(Arr[pos],val);
        }
    }

    int query(int pos){ // 查询最小值
        ++pos;
        int ans=0x3f3f3f3f;
        for(;pos;pos-=lowbit(pos)){
            ans=min(ans,Arr[pos]);
        }
        return ans;
    }

    void clear(){ // 清空
        memset(Arr,0x3f,sizeof(Arr));
    }
};

struct Edge
{
    int To,Next,Weight,Time; // 链式前向星
};

BinaryIndexedTree tree[105];
Edge e[605];
int head[105];
int dis[105][100005],vis[105][100005];

void link(int from,int to,int len,int tim){
    e[++tot].To=to;
    e[tot].Weight=len;
    e[tot].Time=tim;
    e[tot].Next=head[from];
    head[from]=tot;
}

void spfa(int start){
    queue<pair<int,int> > q;
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<=n;i++) tree[i].clear();
    q.push(make_pair(start,0));
    tree[start].modify(0,0);
    dis[start][0]=0;
    vis[start][0]=1;
    while(!q.empty()){
        int u=q.front().first,w=q.front().second; 
		q.pop(); 
		vis[u][w]=0;
        for(int i=head[u];i;i=e[i].Next){
            int v=e[i].To,neww=w+e[i].Weight; // w：费用，neww：新的费用
            if(tree[v].query(neww)>dis[u][w]+e[i].Time){ // 剪枝
                dis[v][neww]=dis[u][w]+e[i].Time; // 更新
                tree[v].modify(neww,dis[v][neww]);
                if(!vis[v][neww]){
                    vis[v][neww]=1;
                    q.push(make_pair(v,neww));
                }
            }
        }
    }
}

int main(){
    IO::read(n); IO::read(m); IO::read(s); IO::read(t);
    for(int i=1;i<=m;i++){
        int x,y,l,t;
        IO::read(x); IO::read(y); IO::read(l); IO::read(t);
        link(x,y,l,t); link(y,x,l,t);
    }
    spfa(s);
    int now=dis[0][0];
    for(int i=0;i<=n*100;i++){
        if(dis[t][i]<now){
            ans++;
            now=dis[t][i];
        }
    }
    IO::writeln(ans);
    IO::flush();
    return 0;
}
```
~~然而，这份代码是不能`AC`的，因为这道题经过一些变动后，时限~~$1000ms \rightarrow 100ms$~~，常数大的代码过不去了。~~
所以下面还有一份速度更快但~~更丑~~的代码，实测可以`AC`。QAQ\~\~
```cpp
#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    char buf[1<<15],*fs,*ft;
    char out[1<<28],*fe=out;
    inline char getc(){
        return (ft==fs&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),ft==fs))?0:*fs++;
    }

    template <typename T>
    inline void read(T &x){
        x=0;
        bool f=false;
        char ch=getchar();
        while (!isdigit(ch) && ch^'-') ch=getchar();
        if (ch=='-') f=true, ch=getchar();
        while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
        if(f)
            x=-x;
        return;
    }

    inline void flush(){
        fwrite(out,1,fe-out,stdout);
        fe=out;
    }

    template <typename T>
    inline void writeln(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++='\n';
    }

    template <typename T>
    inline void writesp(T x){
        if (!x) *fe++=48;
        if (x<0) *fe++='-', x=-x;
        T num=0, ch[20];
        while (x) ch[++num]=x%10+48, x/=10;
        while (num) *fe++=ch[num--];
        *fe++=' ';
    }
}

const int lim = 1e4 + 5;
int nxt[605], tim[605], cost[605], edge[605], head[605];
int q[1000005][2], dis[105][lim], vis[105][lim];
int minval[105][lim];
int tot, n, m, s, t, ans;

void link(int x, int y, int c, int t) {
    nxt[++tot] = head[x];
    head[x] = tot;
    edge[tot] = y;
    tim[tot] = t;
    cost[tot] = c;
}

int query(int x, int y) {
    ++y;
    int mn = 1e7;
    for (; y; y -= (y & -y)) {
        mn = min(mn, minval[x][y]);
    }
    return mn;
}

void modify(int x, int y, int val) {
    ++y;
    for (; y <= n * 100; y += (y & -y)) {
        minval[x][y] = min(minval[x][y], val);
    }
}

void spfa() {
    memset(dis, 63, sizeof(dis));
    memset(minval, 63, sizeof(minval));
    q[1][0] = s;
    q[1][1] = 0;
    dis[s][0] = 0;
    vis[s][0] = 1;
    modify(s, 0, 0);
    for (int front = 1, back = 1; front <= back; ++front) {
        int x = q[front][0], c = q[front][1];
        vis[x][c] = 0;
        for (int i = head[x], y; y = edge[i], i; i = nxt[i]) {
            int newc = c + cost[i];
            if (query(y, newc) > dis[x][c] + tim[i]) {
                dis[y][newc] = dis[x][c] + tim[i];
                modify(y, newc, dis[y][newc]);
                if (!vis[y][newc]) {
                    vis[y][newc] = 1;
                    q[++back][0] = y;
                    q[back][1] = newc;
                }
            }
        }
    }
}

int main() {
    IO::read(n); IO::read(m); IO::read(s); IO::read(t);
    for (int i = 1; i <= m; ++i) {
        int x, y, c, t;
        IO::read(x); IO::read(y); IO::read(c); IO::read(t);
        link(x, y, c, t);
        link(y, x, c, t);
    }
    spfa();
    int now = 0x3f3f3f3f;
    for (int i = 0; i <= n * 100; ++i) {
        if (dis[t][i] < now) {
            ++ans;
            now = dis[t][i];
        }
    }
    IO::writeln(ans);
    IO::flush();
    return 0;
}
```


---

## 作者：Space_Gold_Trash (赞：6)

一道简单的背包+spfa

我们首先分析一下题目

这和我们平时做的模板题不一样

不一样之处就是这加了一个限制

那么我们就得想办法解决这个限制

那么怎么解决呢？

我们很容易想到将从$s$到$i$的所有耗费都存入```dis[i]```

但是很显然会超时

那么我们就要简化

比如说对于到同一个地点

$$
(2,6)

(2,7)
$$

很显然选择$(2,6)$

那我我们怎么确定这个呢？

我们可以给```dis```多加一维

```dis[i][j]```表示到```i```点耗费```j```代价的最小代价

然后答案在哪里呢?

我们就从小到大枚举```j```

如果如果```dis[终点][j]```变小了,就答案+1

那我们跑一次spfa求出```dis```就解决了

```
此代码o2过,或者卡一下常(本人懒,不想卡
#include<bits/stdc++.h>
#define N 1011
#define M 3011
#define V 100011
#define INF 20041026
using namespace std;
int n,m,s,t;
int nex[M],head[N],val_1[M],val_2[M],to[M],tot;
inline void build(int x,int y,int v1,int v2){
	val_1[++tot]=v1;
	val_2[tot]=v2;
	to[tot]=y;
	nex[tot]=head[x];
	head[x]=tot;
}
int dis[N][V];
bool vis[N];
inline void spfa( ){
	queue<int>q;
	int x,y,v1,v2;
	int i,j;
	for(i=1;i<=n;++i)
	for(j=0;j<V;++j)
	dis[i][j]=INF;
	vis[s]=1;
	dis[s][0]=0;
	q.push(s);
	while(!q.empty( )){
		x=q.front( );
		q.pop( );
		for(i=head[x];!!i;i=nex[i]){
			y=to[i];v1=val_1[i];v2=val_2[i];
			for(j=0;j+v1<=n*100;++j)
			if(dis[y][j+v1]>dis[x][j]+v2){
				dis[y][j+v1]=dis[x][j]+v2;
				if(!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
		vis[x]=0;
	}
	int sum=0;
	int best=INF;
	for(i=0;i<=n*100;++i)
	if(best>dis[t][i]){
		best=dis[t][i];
		++sum;
	}
	printf("%d",sum);
}
int main( ){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	int x,y,v1,v2;
	while(m--){
		scanf("%d%d%d%d",&x,&y,&v1,&v2);
		build(x,y,v1,v2);
		build(y,x,v1,v2);
	}
	spfa( );
}
```

---

## 作者：Eleven谦 (赞：6)

# 双调路径

[题目传送门](https://www.luogu.com.cn/problem/P5530)

#### 前言

可能是我语文不太好，题目没读懂，感谢[同桌帮助我理清题意](https://www.cnblogs.com/Poetic-Rain/?tdsourcetag=s_pctim_aiomsg)

------------
#### 题意

对着图讲吧：

![](https://img2020.cnblogs.com/blog/2055990/202007/2055990-20200724150608524-23685340.png)

如图，横轴表示花费的金钱，纵轴表示花费的时间，点表示一条路径

1. 点$（5,5）$和点$（30,3）$是优秀点

2. 点$（10，10）$、点$（15,5）$和点$（23,8）$是无用点

来解释一下：

1. 点$（5,5）$明显比点$（15,5）$优秀，因为花费同样时间，花费金钱少的优秀

2. 点$（10,10）$和点$（23,8）$则肯定是无用点，因为它们花费的时间和金钱都多

3. 点$（5,5）$和点$（30,3）$都是优秀点，因为一个花费的金钱少，一个花费的时间少（相当于不同维度）

推广为一般性问题：

设我们当前的路径表示为$（x，y）$，下一条路径表示为$（u，v）$

1. 如果 $u$ 比 $x$ 小但 $v$ 比 $y$ 大，那么两条路都暂为优秀

2. 如果 $u$ 比 $x$ 大但 $v$ 比 $y$ 小，那么两条路都暂为优秀

3. 如果 $u$ 比 $x$ 小且 $v$ 比 $y$ 小，那么$（u，v）$暂为优秀，而$（x，y）$一定为无用点

------------
#### 分析

题目要求求出从 $s$ 到 $e$ 的最小路径条数

理解了题意，那么应该很容易就能想出**双限制的最短路**做法吧（别在意名字...）

什么意思？

普通最短路就是距离限制，我们通过 $dis[x]$ 表示到达点 $x$ 的最小距离

本题最短路则是限制距离（时间）和花费，那我们就加一维嘛！

—— **用 $dis[x][y]$ 表示到达点 $x$ 花费 $y$ 块钱的最小距离（时间）**

最后**枚举花费 $i$** ，然后找到优秀点 $dis[e][i]$，有多少优秀点答案就是多少

怎么判断是否是优秀点？

设一个变量 $ans$ $=$ $2005020600$（极大值就可以） ，如果当前的 $dis[e][i]$ $<$ $ans$ ，则是优秀点（ $ans$ 表示的是时间）

------------
#### 代码

感觉上面讲的还是挺清楚了qwq，现在贴出代码：

PS：没加树状数组优化什么的，跑得确实有点慢，$1s+$

```cpp
#include <bits/stdc++.h>
using namespace std;
queue<pair<int,int> > q;
int n,m,s,E,p,r,c,t,tot,sum,ans=2005020600,maxn;
int dis[101][30001],vis[101][3001],head[520010];

struct node {
	int to,ti,val,net;
} e[520010];

inline void add(int u,int v,int w,int tim) {
	e[++tot].ti=tim;
	e[tot].to=v;
	e[tot].val=w;
	e[tot].net=head[u];
	head[u]=tot;
}

inline void spfa(int s) {   //其实就是板子 
	for(register int i=1;i<=n;i++) {
		for(register int j=0;j<=maxn;j++) {
			dis[i][j]=2005020600;
		}
	}
	dis[s][0]=0;    //到达点s花费0的最短时间为0 
	vis[s][0]=1;
	q.push(make_pair(s,0));   //为了不开两个queue，我选择开pair 
	while(!q.empty()) {
		int x=q.front().first;
		int y=q.front().second;
		q.pop();
		vis[x][y]=0;
		for(register int i=head[x];i;i=e[i].net) {
			int v=e[i].to;
			if(dis[v][y+e[i].val]>dis[x][y]+e[i].ti) {
				dis[v][y+e[i].val]=dis[x][y]+e[i].ti;
				if(!vis[v][y+e[i].val]) {
					vis[v][y+e[i].val]=1;
					q.push(make_pair(v,y+e[i].val));  //注意第二个存的是花费还不是dis[v][y+e[i].val]！ 
				}
			}
		}
	}
}

int main() {
	scanf("%d%d%d%d",&n,&m,&s,&E);
	for(register int i=1;i<=m;i++) {
		scanf("%d%d%d%d",&p,&r,&c,&t);
		add(p,r,c,t);
		add(r,p,c,t);
		maxn+=c;   //maxn表示最多的花费上限 
	}
	spfa(s);
	for(register int i=0;i<=maxn;i++) {  //枚举花费找答案 
		if(dis[E][i]<ans) {
			sum++;
			ans=dis[E][i];
		}
	}
	printf("%d",sum);
	return 0;
}
```

------------

最后，如果这篇题解有任何问题或不懂的地方，欢迎下方留言区评论，我会及时回复、改正，谢谢大家啊orz

------------







---

## 作者：红色OI再临 (赞：5)

双边权最短路，那就用`dp`吧

设`dis[i][j]`表示在`i`点且已用费用为`j`时的最小时间

$dis[i][j] = min(dis[k][j-cost[k][i]]+time[k][i],dis[i][j])$

然后这个东西就可以在边跑`SPFA`的时候边算，用`vis`数组标记每个状态是否出现过，跑一遍`SPFA`即可

因为有双边权，所以可以用一个二维数组，表示到`i`这个点一种边权为`j`时另一种边权为多少

上代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ll long long
#define re register int
#define maxn 40050
#define MAXN 605
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
struct tu {
    int u, v, w1, w2, nxt;
} e[MAXN];
int head[MAXN], cnt, f[110][maxn], dis[110][maxn];
void add(int u, int v, int w1, int w2) {
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].w1 = w1;
    e[cnt].w2 = w2;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
queue<pair<int, int> > q;
int vis[MAXN][maxn];
int s, t;
int n, m;
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[s][0] = 0;
    vis[s][0] = 1;
    q.push(make_pair(s, 0));
    while (!q.empty()) {
        int w = q.front().second, u = q.front().first;
        q.pop();
        vis[u][w] = 0;
        for (re i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            int w1 = e[i].w1, w2 = e[i].w2;
            vis[u][w] = 0;
            int w3 = w + w1;
            if (w3 <= 10000 && dis[v][w3] > dis[u][w] + e[i].w2) {
                dis[e[i].v][w3] = dis[u][w] + e[i].w2;
                if (!vis[v][w3]) {
                    vis[v][w3] = 1;
                    q.push(make_pair(v, w3));
                }
            }
        }
    }
}
int main() {
    n = read();
    m = read();
    s = read();
    t = read();
    for (re i = 1; i <= m; i++) {
        int a1, a2, a3, a4;
        a1 = read(), a2 = read(), a3 = read(), a4 = read();
        add(a1, a2, a3, a4);
        add(a2, a1, a3, a4);
    }
    spfa();
    int mmin = 0x3f3f3f3f, ans = 0;
    for (re i = 0; i <= 10000; i++) {
        if (dis[t][i] < mmin)
            mmin = dis[t][i], ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```

据~~毒瘤~~出题人说，这个算法还不够优秀，我们发现
`dis[i][j]`如果已经存在一状态`dis[i][k]`,满足$ k<j $
且
$ dis[i][k]<dis[i][j] $，那么`dis[i][j]`就是无用的状态

就可用树状数组维护$dp[i][0-j]$最小值,实现快速查找

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ll long long
#define re register int
#define maxn 10010
#define MAXN 605
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-')
            f = -1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
struct tu {
    int u, v, w1, w2, nxt;
} e[MAXN];
int head[MAXN], cnt, f[110][maxn], dis[110][maxn];
int c[105][maxn];
inline int lowbit(int x) { return x & (-x); }
int vis[MAXN][maxn];
int s, t;
int n, m;
int ask(int x, int y) {
    y++;
    int mmin = 0x7fffffff;
    while (y >= 1) {
        mmin = min(mmin, c[x][y]);
        y -= lowbit(y);
    }
    return mmin;
}
void change(int x, int y, int v) {
    y++;
    while (y < 10100) {
        c[x][y] = min(c[x][y], v);
        y += lowbit(y);
    }
}
void add(int u, int v, int w1, int w2) {
    e[++cnt].u = u;
    e[cnt].v = v;
    e[cnt].w1 = w1;  //费用
    e[cnt].w2 = w2;  //时间
    e[cnt].nxt = head[u];
    head[u] = cnt;
}
queue<pair<int, int> > q;
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(c, 0x3f, sizeof(c));
    dis[s][0] = 0;
    vis[s][0] = 1;
    q.push(make_pair(s, 0));
    change(s, 0, 0);
    while (!q.empty()) {
        int w = q.front().second, u = q.front().first;
        q.pop();
        vis[u][w] = 0;
        for (re i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            int w1 = e[i].w1, w2 = e[i].w2;  //费用和时间
            int w3 = w + w1;
            if (ask(v, w3) > dis[u][w] + w2) {
                dis[v][w3] = dis[u][w] + w2;
                change(v, w3, dis[v][w3]);
                if (!vis[v][w3]) {
                    vis[v][w3] = 1;
                    q.push(make_pair(v, w3));
                }
            }
        }
    }
}
int main() {
    n = read();
    m = read();
    s = read();
    t = read();
    for (re i = 1; i <= m; i++) {
        int a1, a2, a3, a4;
        a1 = read(), a2 = read(), a3 = read(), a4 = read();
        add(a1, a2, a3, a4);
        add(a2, a1, a3, a4);
    }
    spfa();
    int mmin = 0x3f3f3f3f, ans = 0;
    for (re i = 0; i <= 10000; i++) {
        if (dis[t][i] < mmin)
            mmin = dis[t][i], ans++;
    }
    printf("%d\n", ans);
    return 0;
}
```



---

## 作者：Accoty_AM (赞：4)

~~我好快啊 38ms~~
# 看不懂背包的同学看过来

额第一眼看过去，这不是最短路板题，再定睛一看，状态有2维（我们设时间为dis1 费用为dis2）。

通过观察我们发现，这两维可以相互累加，假设我们从s到t有k条路径，每条路径的都会有一个dis1 和 dis2，我们可以把dis1和dis2看成二维平面上的点，这样最终答案就是所有点中，随着dis1递增dis2递减的那个类似凸包（可能不是凸包，自己画个图理解一下）的集合中的所有点。

再进一步的思考，我们发现从s到t的路径很多，但最终的有用状态很少，~~我们可不可以从这里入手优化，答案是肯定的（感觉自己在废话）~~ 我们可以从这里优化,我们对每个点维护一个上段提到的类似凸包的东西，每次走一条边（x，y），相当与对x集合内的所有点加了一个向量，那 **x集合+边（x，y）** 的最优集合的中的点的相对位置是不变的，我们用 **"x集合+边（x，y）"** 去更新y点的集合，如果能更新，就放进spfa的队列，因为y点集合可能更新更多的集合。

一开始s集合内有点(0,0)

为了方便，我代码大部分使用重载运算符，具体的细节请看下面

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
inline int read(){
	rg char ch=getchar();
	rg int x=0,f=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int N=110,M=630;
struct Point{
	int x,y;
	inline bool operator != (const Point &rhs) const {
		return x!=rhs.x||y!=rhs.y;
	} 
	inline Point operator + (const Point &rhs) const {
		Point a;
		a.x=x+rhs.x;
		a.y=y+rhs.y;
		return a;
	}
};
struct lie{//维护一列点，起名方法好奇怪。。。
	vector<Point> v;
	lie(){
		v.clear();
	}
	inline void insert(const Point &rhs){
		if(v.empty()) v.push_back(rhs);
		else if(rhs.x==(*(v.end()-1)).x){
			if(rhs.y<(*(v.end()-1)).y) v.pop_back();
			if(v.empty()) v.push_back(rhs);
			else if(rhs.y<(*(v.end()-1)).y) v.push_back(rhs);//注意这里一定要写小于号，因为重复的点对不会记入答案
		}else if(rhs.y<(*(v.end()-1)).y) v.push_back(rhs);
	}
	inline bool operator != (const lie &rhs) const {
		if(v.size()!=rhs.v.size()) return true;
		for(int i=0,il=v.size();i<il;++i){
			if(v[i]!=rhs.v[i]) return true;
		}
		return false;
	}
	inline lie operator + (const lie &rhs) const {//合并两个集合，这里使用类似归并排序的方法，复杂度线性
		lie rev;
		int l1=0,r1=v.size(),l2=0,r2=rhs.v.size();
		while(l1<r1&&l2<r2){
			if(v[l1].x<rhs.v[l2].x){
				rev.insert(v[l1]);
				++l1;
			}else{
				rev.insert(rhs.v[l2]);
				++l2;
			}
		}
		for(;l1<r1;++l1) rev.insert(v[l1]);
		for(;l2<r2;++l2) rev.insert(rhs.v[l2]);
		return rev;
	}
	inline lie operator + (const Point &rhs) const {//加边的向量
		lie rev;
		for(int i=0,il=v.size();i<il;++i){
			rev.insert((Point){v[i].x+rhs.x,v[i].y+rhs.y});
		}
		return rev;
	}
}dis[N];
int head[N],nxt[M],ver[M],tot,vis[N];
Point edge[M];
int n,m,s,t;
inline void add(int x,int y,Point z){
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
	edge[tot]=z;
}
inline int spfa(){
	queue<int> q;
	dis[s].insert((Point){0,0});
	q.push(s);
	while(!q.empty()){
		int x=q.front();q.pop();
		vis[x]=false;
		for(int y,i=head[x];i;i=nxt[i]){
			y=ver[i];
			lie Dis=dis[y]+(dis[x]+edge[i]);
			if(Dis!=dis[y]){//如果y集合被改变，说明有新的点加入，把y放入队列
				dis[y]=Dis;
				if(!vis[y]){
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	return dis[t].v.size();
}
int main(){
	n=read(),m=read();s=read(),t=read();
	for(int x,y,u,v,i=1;i<=m;++i){
		x=read(),y=read(),u=read(),v=read();
		add(x,y,(Point){u,v});
		add(y,x,(Point){u,v});
	}
	cout<<spfa()<<endl;
	return 0;
}
```


---

## 作者：Zxsoul (赞：2)

# 双调路径

### 前言

> 这题确实需要背包，但是加上 $SPFA$ 树状数组优化会更快，快到吓人！

### 思路

- 与往常不同的是这次最短路有两种选择，那么方向就应该改变了，多状况类型，不是分层图就是DP跑最短路（*差不多*）
- 对于最短路，本事就是DP的过程，数组 $dis$ 不就是吗？，该题目中存在两种权值，因此就需要在加一维，即

$$
f_{i,j}
$$

- 表示在$i$点费用为 $j$ 时所需的最小时间，类似背包，不难看出转移方程式

$$
f_{i,j}=min(f_{k,i-len(k,i)}+time(k,i))(k = head[u]->e[i].next)
$$

- 暴力的话以前是可以过的，不过他改了，因此这里我们用树状数组跑 $spfa$,大体的作用就是维护 $dis$ 数组，在树里跑 $DP$
- 快!

### Code

```c
/*
  树状数组优化版本SPFA  + 二维树状数组
*/
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define N 1100
#define M 3100
#define C 10010
using namespace std;

const int A = 1e5 + 11;
const int B = 2050;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
int n,m,s,t,head[N],cnt=0,dis[N][C],tree[N][C];
bool vis[N][C];
struct node{
  int v,nxt ;
  int w1;
  int w2;
} ed[B << 1];


void add(int u, int v, int c, int t){
  ed[++cnt].nxt = head[u]; 
  ed[cnt].v = v; 
  ed[cnt].w1 = c; 
  ed[cnt].w2 = t; 
  head[u] = cnt;
  return; 
}


int lowbit(int x) {return x & (-x);}

void change(int x, int y, int z){
  y++;
  while(y < 10100){
    tree[x][y] = min(tree[x][y], z);//DP
    y +=  lowbit(y);
  }
  return; 
}

int ask(int x, int y){
  y++;
  int mn = 0x7fffffff;
  while(y >= 1){
    mn = min(mn, tree[x][y]);
    y -= lowbit(y);
  }
  return mn;
}

void spfa(){
  queue<pair<int,int> > q;
  memset(dis, 0x3f, sizeof(dis));
  memset(tree, 0x3f, sizeof(tree));
  memset(vis, 0, sizeof(vis));
  dis[s][0] = 0; //二维变量
  vis[s][0] = 1;
  q.push(make_pair(s, 0));
  change(s, 0, 0);
  while(!q.empty()){
    int w = q.front().second, u = q.front().first;
      //u 位置，w 为 到u 走过的路径，注意dis数组求得是时间而非长度 
    q.pop();
    vis[u][w] = 0;
    for(int i = head[u]; i; i = ed[i].nxt){
      int v = ed[i].v, w1 = ed[i].w1, w2 = ed[i].w2;
      int ww = w + w1;
      if(ask(v,ww) > dis[u][w] + w2)
      {
        dis[v][ww] = dis[u][w] + w2;
        change(v, ww, dis[v][ww]);
        if(!vis[v][ww]){
          q.push(make_pair(v,ww));
          vis[v][ww] = 1;
        }
      }
    }
  }
  return;
}
int main() {
//  freopen(".in", "r", stdin);
//  freopen("cc.out", "w", stdout);
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++){
    int u, v, w1, w2;
    cin >> u >> v >> w1 >> w2;
    add(u, v, w1, w2);
    add(v, u, w1, w2);
  } 
  spfa();
  int minx = 0x3f3f3f3f, ans = 0;
    for (int i = 1; i <= 10000; i++) {
      //cout << dis[t][i] << endl;
		if (dis[t][i] < minx)//知道不同种类的数量
            minx = dis[t][i], ans++;
           // cout << minx << endl;
    }
  printf("%d\n",ans); 
  fclose(stdin);
  fclose(stdout);
  return 0;
  
}


```



---

## 作者：超级玛丽王子 (赞：2)

一道很棒的双权值 SPFA 优化题目。

本题显然是最短路的题目。但是看完题目发现每条边有**两种权值**。因此，我们需要在每个结点处增加一维状态。

用 $f_{i,j}$ 表示在第 $i$ 个点且已用费用为 $j$ 时的最小时间。根据背包的思路，我们可以推出如下状态转移方程：
$$f_{i,j}=\min\{f_{k,i-\operatorname{cost}_{k,i}}+\operatorname{time}_{k,j}\ |\ \operatorname{foreach} \operatorname{edge}_{i,j}\}$$
其中 $\operatorname{cost}_{i,j}$ 表示 $i,j$ 间的边的路费，$\operatorname{time}_{i,j}$ 类似。

由此，我们可以直接用 SPFA 进行求解。其期望复杂度为 $O(K\times N^2\times V)$ （$K$ 为~~玄学的~~期望迭代常数）。然而其状态可能会达到 $100^3$ 即 $10^6$ 级别，即使在实际中算法运行较快，我们也不应该止步于此，而要进一步进行优化。

迭代求解的过程中，考虑到任意新状态 $f_{i,j}$，如果已经存在一个新状态 $f_{i,k}$ 满足 $k<j$ 且 $f_{i,k}<f_{i,j}$，那么显然当前状态 $f_{i,j}$ 不是最优解，故没有继续迭代的必要，直接剪枝剪掉即可，不必加入队列。

具体剪枝流程：对于每个新状态 $f_{i,j}$，查询 $f_{i,0\cdots j}$ 中的最小时间值 $Timemin$，当 $Timemin>f_{i,j}$ 时再进行更新。在实现中，我们考虑对每一个 $f_i$ 维护树状数组加快查询。

虽然期望复杂度变为了 $O(K\times N^2 \times V \times \log N)$，但是其实际效率是惊人的，几乎不耗时间地通过了所有数据。（当然这在 luogu 是不可能的 /xyx）。

考场上的时间效率对比如下：

算法 | SPFA（未优化） | SPFA（树状数组优化） | 官方标程（堆）
-|-|-|-
全部数据所用时间    | 2.09s | 0.24s | 2.60s

可见剪枝优化能力之巨大和 SPFA 迭代的盲目性。

上代码：
```cpp
//P5530 BOI2002 双调路径 树状数组优化
#include <bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int nxt[605],tim[605],fee[605],end[605],poi[605];
int que[1000005][2],dis[105][N],vis[105][N];
int delt[105][N];
int tot,n,m,s,t,ans;
inline int read() {  //快读
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    int x=0;
    while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
    return x;
}
inline void add(int x, int y, int z, int w) {  //前向星
    nxt[++tot]=poi[x],poi[x]=tot,end[tot]=y,tim[tot]=z,fee[tot]=w;
}
inline int min(int x, int y) {  //替换 STL 中的垃圾函数
    return x<y?x:y;
}
inline int query(int x, int y) {  //树状数组查询 dis[x][0...y] 的最小值
    ++y;  //树状数组不支持下标为0，整体加1
    int mn=1e7;
    for(;y;y-=(y&-y)) mn=min(mn,delt[x][y]);
    return mn;
}
inline void updata(int x, int y, int val) {  //树状数组更新
    ++y; 
    for(;y<=n*100;y+=(y&-y)) delt[x][y]=min(delt[x][y],val);
}
void spfa() {
    memset(dis,63,sizeof(dis));
    memset(delt,63,sizeof(delt));
    que[1][0]=s,que[1][1]=0;
    dis[s][0]=0;
    updata(s,0,0);
    for(int q1=1,q2=1;q1<=q2;++q1) {
        int x=que[q1][0],f1=que[q1][1];
        vis[x][f1]=0;
        for(int i=poi[x],y;y=end[i],i;i=nxt[i]) {
            int f2=f1+fee[i];
            if(query(y,f2)>dis[x][f1]+tim[i]) {  //若满足条件，就可能对答案有贡献
                dis[y][f2]=dis[x][f1]+tim[i];
                updata(y,f2,/*这里填什么留待读者思考*/);
                if(!vis[y][f2]) vis[y][f2]=1,que[++q2][0]=y,que[q2][1]=f2;
            }
        }
    }
}
int main(void) {
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;i++) {
        int x=read(),y=read(),w=read(),z=read();
        add(x,y,z,w),add(y,x,z,w);
    }
    spfa();
    int mn=dis[0][0];
    for(int i=0;i<=n*100;++i) if(dis[t][i]<mn) ++ans,mn=dis[t][i];  //费用递增，时间递减
    printf("%d",ans);
    return 0;
}
```
## 完结撒花，求赞求互关QAQ~

---

## 作者：__wzy__ (赞：2)

### 突然发现这题的题解好少啊qwq

# 解题思路：

由于此题与一般最短路不同,边有两种权值,所以需要在每个结点处增加一维状态.即用$f[i][j]$表示在$i$点且已用费为$j$时的最少时间.则：$F[i][j]=Min(F[k][i-Cost(k,i)]+Time(k,i)|For  each edge(k,i))$.

我们可以由此直接使用$SPFA$算法进行求解,期望时间复杂度为$O(K*N^2*V)$ （K为常数）.

## 代码：(超长警告)

```cpp
//未优化
#include<bits/stdc++.h>
#define INF 100001
#define MAXN 0x3f3f3f3f
using namespace std;
int n,m,s,e,maxn,head[INF],cnt,vis[101][10001],min_val=MAXN,ans;
struct node
{
	int to,next,len,val;
}edge[INF];
struct nn
{
	int mon,sum;
}dp[101][10001];
struct mm
{
	int pos,dis;
};
queue<mm>q;
inline int read()//快读 
{
	register int number_read=0,if_ok_read=1;
	char ch_read=getchar();
	while(ch_read<'0'||ch_read>'9')
	{
		if(ch_read=='-')
			if_ok_read=-1;
		ch_read=getchar();
	}
	while(ch_read>='0'&&ch_read<='9')
	{
		number_read=number_read*10+ch_read-'0';
		ch_read=getchar();
	}
	return number_read*if_ok_read;
}
inline void write(register int x_write)//快写 
{
    if(x_write<0)
	{
    	putchar('-');
		x_write=-x_write;
	}
    if(x_write>9)
		write(x_write/10);
    putchar(x_write%10+'0');
    return ;
}
inline void add(int f,int t,int l,int v)//连边 
{
	edge[cnt].to=t;
	edge[cnt].len=l;
	edge[cnt].val=v;
	edge[cnt].next=head[f];
	head[f]=cnt++;
	return ;
}
inline void dij()//核心程序 
{
	for(int i=1;i<=n;i++)
		for(int j=0;j<10001;j++)
		{
			dp[i][j].mon=MAXN;
			dp[i][j].sum=0;
		}
	dp[s][0].mon=0;
	dp[s][0].sum=1;
	vis[s][0]=1;
	mm st;
	st.pos=s;
	st.dis=0;
	q.push(st);
	while(!q.empty())
	{
		mm u=q.front();
		q.pop();
		vis[u.pos][u.dis]=0;
		for(int i=head[u.pos];i!=-1;i=edge[i].next)
		{
			if(u.dis+edge[i].len>maxn+1)
				continue;
			if(dp[u.pos][u.dis].mon+edge[i].val<dp[edge[i].to][u.dis+edge[i].len].mon)
			{
				dp[edge[i].to][u.dis+edge[i].len].mon=dp[u.pos][u.dis].mon+edge[i].val;
				dp[edge[i].to][u.dis+edge[i].len].sum=1;
				if(!(vis[edge[i].to][u.dis+edge[i].len]))ertaideshijianxiao 
				{
					mm vv;
					vv.pos=edge[i].to;
					vv.dis=u.dis+edge[i].len;
					vis[edge[i].to][u.dis+edge[i].len]=1;
					q.push(vv);
				}
			}
		}
	}
	return ;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	m=read();
	s=read();
	e=read();
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read(),c=read(),d=read();
		add(a,b,c,d);
		add(b,a,c,d);
	}
	maxn=(n-1)*100;
	dij();
	for(int i=0;i<=maxn+5;i++)
	{
		if(!dp[e][i].sum)
			continue;
		if(dp[e][i].mon<min_val)//时间长但钱数少 
		{
			ans++;
			min_val=dp[e][i].mon;
		}
	}
	write(ans);
	putchar('\n');
	return 0;
}

```

然而此程序只能得到56分，状态达到$100^3$级别，虽然实际中算法运行比较快，但我们不能就此终止，可以尝试进行优化

# 算法优化：

在求解过程中，考虑任意一种新状态$F[i][j]$,如果已经存在一种状态$F[i][k]$，满足$k<j$且$F[i][k]<F[i][j]$,则显然当前状态$F[i][j]$肯定不是最优解，也没有继续更新的必要，我们大可不必将其加入队列。

于是可以加入这样一个剪枝：对于每个新状态$F[i][j]$，我们查询$F[i][0...j]$中的最小值$Timemin$,当$Timemin>F[i][j]$时才更新。在实现时我们可以对每一个$F[i]$维护一个树状数组以加快查询速度，这样期望时间复杂度变为$O(K*N^2*V*Log^N)$，而它的实际效率却是惊人的，几乎不耗时间地通过了所有数据。

## AC代码：(超长警告)

```cpp
//树状数组优化 
#include<bits/stdc++.h>
#define INF (int)1e4+5
#define MAXN 1000001
#define X 101
using namespace std;
int nxt[MAXN],tim[MAXN],fee[MAXN],e[MAXN],poi[MAXN],que[MAXN][2],dis[X][INF],vis[X][INF],delt[X][INF],tot,n,m,s,t,ans;
inline int read()//快读 
{
	register int number_read=0,if_ok_read=1;
	char ch_read=getchar();
	while(ch_read<'0'||ch_read>'9')
	{
		if(ch_read=='-')
			if_ok_read=-1;
		ch_read=getchar();
	}
	while(ch_read>='0'&&ch_read<='9')
	{
		number_read=number_read*10+ch_read-'0';
		ch_read=getchar();
	}
	return number_read*if_ok_read;
}
inline void write(register int x_write)//快写 
{
    if(x_write<0)
	{
    	putchar('-');
		x_write=-x_write;
	}
    if(x_write>9)
		write(x_write/10);
    putchar(x_write%10+'0');
    return ;
}
inline void add(int x,int y,int z,int w)//连边 
{
	nxt[++tot]=poi[x];
	poi[x]=tot;
	e[tot]=y;
	tim[tot]=z;
	fee[tot]=w;
	return ;
}
inline int query(int x,int y)//查询dis[x][0...y]的最小值 
{
	y++;//树状数组不支持下标为0,所以下标整体加一 
	int mn=1e7;
	for(;y;y-=(y&-y))
		mn=min(mn,delt[x][y]);
	return mn;
}
inline void updata(int x,int y,int val)//树状数组的更新 
{
	y++;//树状数组不支持下标为0,所以下标整体加一 
	for(;y<=n*100;y+=(y&-y))
		delt[x][y]=min(delt[x][y],val);
	return ;
}
inline void spfa()//SPFA 
{
	memset(dis,63,sizeof(dis));
	memset(delt,63,sizeof(delt));
	que[1][0]=s;
	que[1][1]=dis[s][0]=0;
	updata(s,0,0);
	for(int q1=1,q2=1;q1<=q2;++q1)
	{
		int x=que[q1][0],f1=que[q1][1];
		vis[x][f1]=0;
		for(int i=poi[x],y;y=e[i],i;i=nxt[i])
		{
			int f2=f1+fee[i];
			if(query(y,f2)>dis[x][f1]+tim[i])//如果满足条件,则可能对答案有所贡献 
			{
				dis[y][f2]=dis[x][f1]+tim[i];
				updata(y,f2,dis[y][f2]);
				if(!vis[y][f2])
				{
					vis[y][f2]=1;
					que[++q2][0]=y;
					que[q2][1]=f2;
				}
			}
		}
	}
	return ;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	m=read();
	s=read();
	t=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read(),w=read(),z=read();
		add(x,y,z,w);
		add(y,x,z,w);
	}
	spfa();
	int mn=dis[0][0];
	for(int i=0;i<=n*100;++i)// 费用递增,时间递减 
		if(dis[t][i]<mn)
		{
			ans++;
			mn=dis[t][i];
		}
	write(ans);
	putchar('\n');
	return 0;
}

```

---

## 作者：洛桃 (赞：1)

## 思路
是一道最短路的题目。由于路径的优劣同时与两个量相关，需要使用二维的dis数组。

考虑使用 $dp_{x,len}$ 表示目前在 $x$ 点，且已有花费为 $len$ 时的最短时间。我们只要转换一下队列存储的类型以及更新时用的不等式即可。

当一遍spfa/dijkstra跑完后，我们就得到了从起点出发到所有点不同花费的最短时间。

我们可以在读入时计算出最大的可能花费，即所有道路的花费总和，然后从0开始循环，并用minn记录当前的最短时间。

由于我们的花费是递增的，所以如果这个花费用的最短时间比之前记录的最短时间minn更小的话，那么这就是一条类型不同的最短路径，这时我们的ans加1，循环结束后，路径总数也就统计完了。

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int n,m,s,e,head[100110],p,ans,maxn;
struct edge{
	int to,next,len,w;
}a[101100];
bool ex[305][10010];
void add(int x,int y,int c,int t)
{
	a[++p].to=y;a[p].w=t;a[p].len=c;
	a[p].next=head[x];head[x]=p;
}
struct node{
	int pos,dis;
};
int dp[305][30010];
void spfa(int s)
{
	queue<node>q;
	for(int i=1;i<=n;i++)
	for(int j=0;j<=maxn;j++)
	dp[i][j]=0x3f3f3f3f;
	node st;st.dis=0;st.pos=s;
	q.push(st);dp[s][0]=0;ex[s][0]=1;
	while(!q.empty())
	{
		node tmp=q.front();q.pop();
		int u=tmp.pos,dis=tmp.dis;
		ex[u][dis]=0;
		for(int i=head[u];i;i=a[i].next)
		{
			int w=a[i].w,len=a[i].len,v=a[i].to;
			if(w+dp[u][dis]<dp[v][dis+len])
			{
				dp[v][dis+len]=w+dp[u][dis];
				if(ex[v][dis+len]==0)
				{
					ex[v][dis+len]=1;
					node t;
					t.dis=dis+len,t.pos=v;
					q.push(t);
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for(int i=1;i<=m;i++)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(a,b,c,d);
		add(b,a,c,d);
		maxn+=c;
	}
	spfa(s);int minn=0x3f3f3f3f;
	for(int i=0;i<=maxn;i++)
	{
		if(dp[e][i]<minn)
		{
			ans++;
			minn=dp[e][i];
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Randolph、 (赞：1)

[P5530 [BalticOI 2002]双调路径](https://www.luogu.org/problem/P5530)
```
输入样例：
4 5 1 4
2 1 2 1
3 4 3 1
2 3 1 2
3 1 1 4
2 4 2 4
```

样例说明：

从1到4有4条路径。为1→2→4(费用为4,时间为5) ,1→3→4(费用为4,时间为5) ,1→2→3→4(费用为6,时间为4) ,1→3→2→4(费用为4,时间为10)。 1→3→4和1→2→4比1→3→2→4更好。有两种最佳路径:费用为4 ,时间为5(1→2→4和1→3→4)和费用为6,时间为4 (1→2→3→4)。

## 分析
最短路的边有两种权值，所以考虑在每个节点增加一维状态，d【i】【j】：到达节点i且费用为j时所用最少时间，则d【v】【j】=min{d【u】【j-cost（u，v）】}+time（u，v）

用SPFA即可， 533ms /  6.12MB，#8#9TLE，86分

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define R register
struct edge {
    int v,w,t,h;
} e[610];
int h[110],d[110][10100],cnt,mn;
int u,v,w,n,m,S,T;
bool vis[110][10100];//第二维记得开大一些

inline void add(int u,int v,int w,int t) {
    e[++cnt]=(edge) {v,w,t,h[u]},h[u]=cnt;
}

queue<pair<int,int> >q;//二维记录节点u和所用cost
inline void spfa() {
    memset(d,0x3f,sizeof d);
    mn=99999999;
    q.push(make_pair(S,d[S][0]=0)),vis[S][0]=1;
    while(!q.empty()) {
        u=q.front().first,w=q.front().second;
        vis[u][w]=0,q.pop();
        for (R int i=h[u],_w; i; i=e[i].h)
            if ((_w=w+e[i].w)<=10010) {//w是到达u的cost，_w是由u到达v所用cost，_w超出100*100直接舍去
                if (d[v=e[i].v][_w]>d[u][w]+e[i].t) {//同样的cost所用time是否比原来更少
                    d[v][_w]=d[u][w]+e[i].t;
                    if(!vis[v][_w]) q.push(make_pair(v,_w)),vis[v][_w]=1;
                }
            }
    }
}

int main() {
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for (R int t; m; m--)
        scanf("%d%d%d%d",&u,&v,&w,&t),add(u,v,w,t),add(v,u,w,t);
    spfa();

    cnt=0;
    for (R int i=0; i<=10000; i++)
        if(d[T][i]<mn) mn=d[T][i],cnt++;//cost逐渐增长，那么time只有小于其他的time才能算“最小路径”
    printf("%d",cnt);
}
```

## 优化

不难想到，对于d【i】【j】，如果有k（k<j）且d【i】【k】<d【i】【j】（到达i所用cost和time都更少），那么d【i】【j】也就没必要更新了。所以加入剪枝：用树状数组维护d【i】【0~j】的最小值，只有d【i】【j】<最小值才更新

实际效率提高不少， 93ms /  9.93MB，AC代码：

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
using namespace std;
#define R register
struct edge {
    int v,w,t,h;
} e[610];
int h[110],d[110][10100],tr[110][10100],cnt,mn;
int u,v,w,n,m,S,T;
bool vis[110][10100];

inline void add(int u,int v,int w,int t) {
    e[++cnt]=(edge) {v,w,t,h[u]},h[u]=cnt;
}

//用val更新d【x】【0~y】最小值    
inline void upd(int x,int y,int val){
    for (y++;y<10100;y+=y&-y) tr[x][y]=min(tr[x][y],val);
}//树状数组下标不能为0，所以y++

//查询d【x】【0~y】最小值
inline int qry(int x,int y){
    int ans=1e7;
    for (y++;y;y-=y&-y) ans=min(tr[x][y],ans);
    return ans;
}

queue<pair<int,int> >q;
inline void spfa() {
    memset(d,0x3f,sizeof d);
    memset(tr,0x3f,sizeof d);//别忘了初始化
    q.push(make_pair(S,d[S][0]=0)),vis[S][0]=1;
    upd(S,0,0);
    while(!q.empty()) {
        u=q.front().first,w=q.front().second;
        vis[u][w]=0,q.pop();
        for (R int i=h[u],_w; i; i=e[i].h)
                if (qry(v=e[i].v,_w=w+e[i].w)>d[u][w]+e[i].t) {//只有d【i】【j】<最小值才更新
                    d[v][_w]=d[u][w]+e[i].t;
                    upd(v,_w,d[v][_w]);//更新最小值
                    if(!vis[v][_w]) q.push(make_pair(v,_w)),vis[v][_w]=1;
                }
    }
}

int main() {
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for (R int t; m; m--)
        scanf("%d%d%d%d",&u,&v,&w,&t),add(u,v,w,t),add(v,u,w,t);
    spfa();

    cnt=0,mn=99999999;
    for (R int i=0; i<=10000; i++)
        if(d[T][i]<mn) mn=d[T][i],cnt++;
    printf("%d",cnt);
}
```

---

