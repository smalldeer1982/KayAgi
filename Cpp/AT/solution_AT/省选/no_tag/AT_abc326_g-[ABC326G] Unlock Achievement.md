# [ABC326G] Unlock Achievement

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc326/tasks/abc326_g

$ 1 $ から $ N $ の番号がついた $ N $ 種類のスキルと、$ 1 $ から $ M $ の番号がついた $ M $ 種類のアチーブメントがあります。

各スキルには正整数のレベルが定まっており、最初全てのスキルのレベルは $ 1 $ です。

$ C_i $ 円のコストを払うことでスキル $ i $ のレベルを $ 1 $ 上げることができます。これは何度でも行なえます。

アチーブメント $ i $ は、$ j=1,\ldots,N $ の全てについて以下の条件を満たすと達成となり、$ A_i $ 円の報酬をもらえます。

- 条件：スキル $ j $ のレベルが $ L_{i,j} $ 以上である
 
スキルのレベルの上げ方を適切に選ぶとき、得られる報酬の合計から必要なコストの合計を引いた値の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N,M\ \leq\ 50 $
- $ 1\ \leq\ L_{i,j}\ \leq\ 5 $
- $ 1\ \leq\ A_i,C_i\ \leq\ 10^6 $
- 入力は全て整数である
 
### Sample Explanation 1

$ 2 $ 種類のスキルがあります。スキル $ 1 $ はレベルを上げるために $ 10 $ 円、スキル $ 2 $ は $ 20 $ 円かかります。 $ 2 $ 種類のアチーブメントがあります。 アチーブメント $ 1 $ は「スキル $ 1 $ をレベル $ 3 $ 以上、かつ、スキル $ 2 $ をレベル $ 1 $ 以上」にすると達成となり $ 100 $ 円もらえ、 アチーブメント $ 2 $ は「スキル $ 1 $ をレベル $ 1 $ 以上、かつ、スキル $ 2 $ をレベル $ 4 $ 以上」にすると達成となり $ 50 $ 円もらえます。 スキル $ 1 $ をレベル $ 3 $ に、スキル $ 2 $ をレベル $ 1 $ にすることで、報酬が $ 100 $ 円、コストが $ 20 $ 円となり、その差は $ 80 $ 円となります。

### Sample Explanation 2

スキル $ 1 $ をレベル $ 3 $ に、スキル $ 2 $ をレベル $ 4 $ にすることで、報酬が $ 150 $ 円、コストが $ 80 $ 円となり、その差は $ 70 $ 円となります。

## 样例 #1

### 输入

```
2 2
10 20
100 50
3 1
1 4```

### 输出

```
80```

## 样例 #2

### 输入

```
2 2
10 20
100 50
3 2
1 4```

### 输出

```
70```

## 样例 #3

### 输入

```
10 10
10922 23173 32300 22555 29525 16786 3135 17046 11245 20310
177874 168698 202247 31339 10336 14825 56835 6497 12440 110702
2 1 4 1 3 4 4 5 1 4
2 3 4 4 5 3 5 5 2 3
2 3 5 1 4 2 2 2 2 5
3 5 5 3 5 2 2 1 5 4
3 1 1 4 4 1 1 5 3 1
1 2 3 2 4 2 4 3 3 1
4 4 4 2 5 1 4 2 2 2
5 3 1 2 3 4 2 5 2 2
5 4 3 4 3 1 5 1 5 4
2 3 2 5 2 3 1 2 2 4```

### 输出

```
66900```

# 题解

## 作者：樱雪喵 (赞：10)

建模还是挺典的，难点在于你要想到这题是网络流。

## Description

有 $n$ 个技能，$m$ 个成就。每个技能有一个等级，初始均为 $1$。

你可以用 $c_i$ 块钱令技能 $i$ 提升一个等级，该操作没有次数限制。

第 $i$ 个成就达成的条件是对于 $\forall j\in [1,n],level_j \ge L_{i,j} $，其中 $level_j$ 表示第 $j$ 个技能的等级。达成成就 $i$ 后，你会获得 $a_i$ 元的奖励。注意这里奖励与成本是分开的，也就是说你不能用奖励的钱去提升等级。

请最大化获得的奖励与所需成本之差，并输出该值。

$n,m\le 50,\, 1\le L_{i,j}\le 5,\, 1\le a_i,c_i\le 10^6$。

## Solution

考虑构造最小割模型。

因为 $L_{i,j}\le 5$，把点 $i$ 拆成 $6$ 个点，分别为 $id_{i,j}(j\in [1,6])$。令成就 $i$ 为点 $bel_i$。则进行如下的建图：

- 连接源点 $s$ 与 $id_{i,6}$，容量为 $\inf$。
- 连接 $id_{i,j+1}$ 与 $id_{i,j}$，容量为 $c_i\times (j-1)$，割掉这条边则表示将技能 $i$ 升级到 $j$。
- 连接 $id_{i,L_{j,i}}$ 与 $bel_j$，容量为 $\inf$。
- 连接 $bel_i$ 与 $t$，容量为 $a_i$。如果这条边被割掉，说明至少有一个技能的等级未达到该奖励的条件，不能获得奖励。

那么这个图的最小割就是成本与**未获得**的奖励之和，用总奖励减去最小割即为答案。

```cpp
signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=m;i++) a[i]=read(),ans+=a[i];
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) L[i][j]=read();
    s=0,t=n*m*6+105;
    for(int i=1;i<=n;i++)
    {
        id[i][6]=++tot;
        add(s,id[i][6],inf);
        for(int j=5;j>=1;j--)
        {
            id[i][j]=++tot;
            add(id[i][j+1],id[i][j],c[i]*(j-1));
        }
        add(id[i][1],t,inf);
    }
    for(int i=1;i<=m;i++)
    {
        bel[i]=++tot;
        add(bel[i],t,a[i]);
        for(int j=1;j<=n;j++) add(id[j][L[i][j]],bel[i],inf);
    }
    assert(tot<t); assert(tot<1e6);
    while(bfs()) ans-=dfs(s,inf);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：hellolin (赞：5)

# ABC326G Unlock Achievement 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/abc326g/) 获得更好的阅读体验！

需要注意，以下我们将题目中提到的变量全部转为小写。

容易发现，若我们假定所有成就都会达成，那么我们需要考虑的就是一个最小化投入的问题。再观察数据范围，$n$ 和 $m$ 都是极小的 $50$ 级别，合理地猜测使用最小割解决。

> **为啥想到用最小割？**
> 
> 下面会讲到把每个技能拆成五个节点，对应五个等级，容易发现这些 **技能等级** 和 **成就** 都只有达成 or 未达成两种情况，那么根据割的定义，割可以把图分成与源点相连的部分和与汇点相连的部分，自然达成未达成的情况就决策出来了。

首先，建立超级源点 $s$ 和超级汇点 $t$，之后，定义顶点 $A(x, y)$ 表示 $x$ 技能的第 $y$ 级（$x\in [1, n],\ y\in [1, 5]$），定义顶点 $B(z)$ 表示第 $z$ 项成就（$z\in [1, m]$）。

开始连边，每个技能初始都是 $1$ 级，我们连接边 $s\to A(i, 1)$，容量为 $+\infty$。

之后，每个技能升级需要 $c_i$ 块钱，我们对于 $j\in [1,4]$，连接边 $A(i, j)\to A(i, j+1)$，容量设为 $(j - 1)\times c_i$。

这里技能内不可能出现 **下一级达成但上一级未达成** 的情况（即等级之间有依赖关系），所以要连接一条反边容量为 $+\infty$。

之后，连接边 $A(i, 5)\to t$，容量设为 $4\times c_i$，表示这个技能完成了升级。

之后思考，如果我达成了某项成就，我就会获得一些钱，那么如何把他转化成 **投入** 呢？注意到前面提到 **假定所有成就都会达成**，于是我的决策就变成了 **选择哪项成就不达成**，**最小化不达成所带来额外的代价**，所以连边 $s\to B(i)$，容量为 $a_i$。

这里需要注意：达成 $\forall j\in [1, n],\ A(j, l_{i, j})$ 是达成 $B(i)$ 的充要条件。为了避免技能升级升够了成就还没达成的情况，由当前成就向这 $n$ 个技能等级连边，容量为 $+\infty$。

最后答案即为 $\sum a_i - \operatorname{maxflow}(s, t)$。

至此我们成功做完了这一题。注意需要开 `long long`，以及使用 ACL 能省不少事。

``` cpp
#include <bits/stdc++.h>
#include "atcoder/all"
constexpr int N = 60;
constexpr long long Inf = 1e12;
int n, m, s, t;
long long c[N], a[N], l[N][N];
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];
    for (int i = 1; i <= m; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            std::cin >> l[i][j];
    atcoder::mf_graph<long long> mf(5 * (n + 1) + m + 6);
    s = 0, t = 5 * (n + 1) + m + 1;
    for (int i = 1; i <= n; ++i) {
        mf.add_edge(s, 5 * i + 1, Inf);
        for (int j = 1; j <= 4; ++j) {
            mf.add_edge(5 * i + j, 5 * i + j + 1, c[i] * (j - 1));
            mf.add_edge(5 * i + j + 1, 5 * i + j, Inf);
        }
        mf.add_edge(5 * i + 5, t, c[i] * 4);
    }
    for (int i = 1; i <= m; ++i) {
        mf.add_edge(s, 5 * (n + 1) + i, a[i]);
        for (int j = 1; j <= n; ++j) {
            mf.add_edge(5 * (n + 1) + i, 5 * j + l[i][j], Inf);
        }
    }
    std::cout << std::accumulate(&a[1], &a[m + 1], 0ll) - mf.flow(s, t) << '\n';
}
```

---

## 作者：_3414_ (赞：4)

## 前言

被同学强行拉过来补 ABC，然后他不会 G，我一看啊我也不会，于是就有了这篇题解

虽然正确率很高，但是这篇题解不是正解，如果有 hack 可以联系管理撤下题解。

## 题意

给你一个序列 $now$，初始它均为 $1$。你可以花费 $c[i]$ 的代价把 $i$ 这个位置增加 $1$。

再给你 $m$ 个目标，第 $i$ 个目标是一个数组 $l[i][j]$，代表如果 $now$ 每个位置都比 $l[i]$ 对应位置大，那么可以得到 $a[i]$ 的收益。

我们要求出最大净收益。

## 解法

我们发现数据范围奇小无比。所以考虑进行乱搞。

考虑按照净收益对目标排序，然后顺序完成目标，在中途记录答案并更新最大值。

具体实现参考核心代码：

```cpp
bool cmp(int x,int y){
	int ansl=0,ansr=0;
	for(int i=1;i<=n;++i)ansl+=(max(0ll,l[x][i]-now[i]))*c[i],ansr+=(max(0ll,l[y][i]-now[i]))*c[i];
	return a[x]-ansl<a[y]-ansr;
}
```

时间复杂度为 $O(m^2n \log m)$。

然后，这个做法光荣地被卡了一个点。

~~你不要火大。~~

然后你额外乱随一堆目标序列，然后直接尝试顺序达成，更新最大值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[55],c[55],l[55][55],now[55],ans,sans;
vector<int>fuc;
bool cmp(int x,int y){
	int ansl=0,ansr=0;
	for(int i=1;i<=n;++i)ansl+=(max(0ll,l[x][i]-now[i]))*c[i],ansr+=(max(0ll,l[y][i]-now[i]))*c[i];
	return a[x]-ansl<a[y]-ansr;
}
mt19937 rd((unsigned long long)new char);
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>c[i],now[i]=1;
	for(int i=1;i<=m;++i)cin>>a[i],fuc.push_back(i);
	for(int i=1;i<=m;++i)
		for(int j=1;j<=n;++j)cin>>l[i][j];
	for(int i=1;i<=m;++i){
		sort(fuc.begin(),fuc.end(),cmp);
		int t=fuc.back(),sum=0;
		for(int j=1;j<=n;++j)sum+=c[j]*(max(0ll,l[t][j]-now[j]));
		sum=a[t]-sum;
		for(int j=1;j<=n;++j)now[j]=max(now[j],l[t][j]);
		ans+=sum;sans=max(sans,ans);fuc.pop_back();
	}
	for(int tm=1;tm<=102624;++tm){
		for(int i=1;i<=n;++i)now[i]=1;
		for(int i=1;i<=m;++i)fuc.push_back(i);
		ans=0;
		shuffle(fuc.begin(),fuc.end(),rd);
		for(int i=1;i<=m;++i){
			int t=fuc.back(),sum=0;
			for(int j=1;j<=n;++j)sum+=c[j]*(max(0ll,l[t][j]-now[j]));
			sum=a[t]-sum;
			for(int j=1;j<=n;++j)now[j]=max(now[j],l[t][j]);
			ans+=sum;sans=max(sans,ans);fuc.pop_back();
		}
		fuc.clear();
	}
	cout<<sans<<'\n';
	return 0;
}
```

这么做的时间复杂度为 $O(m^2n \log m + Tn(n+m))$，其中 $T$ 为后面一部分的随机次数。实际测试取 $T=102624$，可以稳过。

本算法不是特别依赖随机种子。

---

## 作者：紊莫 (赞：3)

为什么清一色的网络流啊，这是一个模拟退火的题解。

## 分析思路

首先观察到数据范围很小！考虑模拟退火。  

我们把依次执行的操作序列称为 ``op``，我们随机交换 ``op`` 中的任意两个元素，然后检查按当前序列来计算得到的最大值。

**注意**：并不是序列中的每一个都必须取到，而是依次取到每个数时的最大值。  

然后你可能会像我一样错了好几个点，然后陷入无尽的调参中，然而，本题对参数的要求并不是很严格，换言之，还有别的更重要的地方，也就是初始化值。

我们不妨使用贪心的方法来初始化。  

每次取出当前奖励与所需成本之差最大的一个成就并执行，记录下整个过程的最大值，而这个取出的顺序就是初始的 ``op``。

## 代码

[Atcoder](https://atcoder.jp/contests/abc326/submissions/47960949)。

本代码基于随机化处理。

---

## 作者：keep_of_silence (赞：2)

## 思路

### 题目&思考

翻译一下题目：已知有 n 个技能，每个技能可以耗费 $c _ {i}$ 升一级，每个技能最多可以升到 ( $ 1\ \leq\ L_{i,j}\ \leq\ 5 $ ) ，升级的同事可以获得成就，共有 m 个成就，每个成就可以获得 $c _ {i}$ 的收益，每个成就需要每个技能达到一定的限制，询问获得的奖励与所需成本之差。

看到有这么多点以及给出的条件十分繁杂的前提下，可以考虑网络流，对于网络流，最难的是网络流的建模。

### 网络流的建模：

题目所给的条件没有明显源点汇点，所以考虑设立一个**超级源点**  $S$  以及**超级汇点**  $T$。

由于每个技能可以升级，单个点不能处理每一级之间的关系。

考虑**拆点**。

将每一个技能**拆成五个点**，代表此技能的五级，除第五级外每一级向自己的下一级连一条**流量为 inf** 的边(保证它不会被割掉)。

对于源点，其连的是**花费**，因为所有的技能一开始都是一级，所以在一级的时候**不需要花费任何代价**，超级源点 S 向除了第一级的所有点连一条流量为 $c _ {i}$ 的边。

这样连边就可以保证每一级的最大流量是技能升级需要的花费。


对于汇点，由于成就的条件十分繁杂，对于每个成就，考虑**新建节点** $p_ {i}$，其限制条件可以转化为[P1361 小M的作物](https://www.luogu.com.cn/problem/P1361)，将每个成就需要的每个技能级数的点连向当前点 $p_ {i}$，这样就保证了成就限制条件，最后每个 $p_ {i}$ 向超级汇点连一条流量为 $c _ {i}$ 的边，代表此成就的奖励。

所以综上所述，本题的建模规则：

1：将每个点**拆成五个点**，每一级向下一级连一条**流量 inf** 的边。

2：**源点**向每个技能每一级(**除了第一级**)连一条流量为 $c _ {i}$ 的边。

3：对于每一个成就**新建一个点**，将其限制的技能级数连向这个点。

4：每一个代表成就的点**向汇点**连一条流量为 $c _ {i}$ 的边。

这道题利用的便是网络流中的最小割，因为我们要求的是升级每个技能至某一级，最大化获得的奖励与所需成本之差，最小割求得的便是升级所用的**花费**+**没有达成的成就**之和，成就的总和 -  dinic 求出的最小割=获得的奖励与所需成本之差。

在网络流中，最小割的数值上=最大流，所以可以跑一遍 dinic 板子，最后要求的答案就是所有的 $c _ {i}$ 之和减去求得的最小割的值。

更多细节参见代码。



## 代码

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdio>
#define inf 1e9
using namespace std;

inline int min(int x,int y){return x>y?y:x;}

int n,m,s,t,maxx=0;

int cnt=-1,res=0;;
struct N{
	int to,next,val; 
}; N p[800005];
int head[100005],cur[100005];
int c[55],a[55],d[10005];
int mapp[55][55];

inline void add(int a,int b,int c)
{
	++cnt;
	p[cnt].next=head[a];
	head[a]=cnt;
	p[cnt].to=b;
	p[cnt].val=c;
	return ;
}

inline int bfs()
{
	memset(d,-1,sizeof(d));
	queue<int> q;
	q.push(s); 
	d[s]=0;
	while(q.size()>0)
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=p[i].next)
		{
			int v=p[i].to;
			if(d[v]==-1&&p[i].val>0)
			{
				d[v]=d[u]+1;
				q.push(v);
			}
		}
	}
	if(d[t]==-1) return 0;
	else return 1;
}

inline int dfs(int u,int limit)
{
	if(u==t||!limit) return limit;
	int flow=0,sum=0;
	for(int i=cur[u];i!=-1;i=p[i].next)
	{
		int v=p[i].to;
		cur[u]=i;
		if(d[v]==d[u]+1&&p[i].val>0)
		{
			sum=dfs(v,min(limit,p[i].val));
			limit-=sum;
			flow+=sum;
			p[i].val-=sum;
			p[i^1].val+=sum;
			if(!limit) break;
		}
	}
	if(!flow) d[u]=-1;
	return flow;
}

inline void dinic()
{
	int ans=0;
	while(bfs())
	{
		for(int i=0;i<=t;i++) cur[i]=head[i];//弧优化 
		ans+=dfs(s,inf); 
	}
	cout<<maxx-ans<<endl;
	return ;
}//板子

int main()
{
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	s=0,t=5*n+m+1;//超级源点和超级汇点
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		++res;
		for(int j=2;j<=5;j++)
		{
			res++;
			add(res-1,res,inf),add(res,res-1,0);
			add(s,res,c[i]),add(res,s,0);
		}
	}//拆点，建图规则1&2,点编号 1-5*n
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
		add(5*n+i,t,a[i]),add(t,5*n+i,0);
		maxx+=a[i];
	}//建图规则4,点编号5*n+1-5*n+m
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>mapp[i][j];
			if(mapp[i][j]>1) add(5*(j-1)+mapp[i][j],5*n+i,inf),add(5*n+i,5*(j-1)+mapp[i][j],0);
		}//第i个点点第j级的编号为5(i-1)+j; 
	}//建图规则3
	dinic();//板子
	
	return 0;
}
```
在题目点数众多，限制条件十分繁杂的情况下，都可以考虑使用最小割的方法。和这题处理方法类似的有：

[P1646 [国家集训队] happiness](https://www.luogu.com.cn/problem/P1646)

[P4313 文理分科](https://www.luogu.com.cn/problem/P4313)

[P1361 小M的作物](https://www.luogu.com.cn/problem/P1361)

[P2057 [SHOI2007] 善意的投票](https://www.luogu.com.cn/problem/P2057)

[P1935 [国家集训队] 圈地计划](https://www.luogu.com.cn/problem/P1935)



---

## 作者：Uuuuuur_ (赞：2)

这是一道规划问题，你可以消耗一定的金额将某个技能升一级，当所有技能的等级满足某个条件时，就会获得对应成就，得到一定金额奖励。求最大金额。

转换一下，先算上所有奖励，再进行技能升级的选择，这样就只要求最少的花费。

由于技能等级最大只有 $5$，自然想到拆成多个状态，这样子，每个状态之间都互相有限制，最终要选入一些状态，舍弃一些状态，求最小代价，这就想到了网络流最小割。

首先建立两个超级源汇点，分别代表选/不选。接下来开始连边。

对于**选择**源点 $S$，连上所有成就，边权为 $A_i$。代表着，如果不选某成就，就会增加对应代价。

对于**舍弃**汇点 $T$，由**所有技能状态**向其连边，边权为对应的 $C_i$。

要保证，选了高等级的技能，一定要选低等级的，所以对于每个技能，由高等级状态向低等级连边，边权 $\infty$。

要保证，选了某个成就，一定要选择对应技能状态，所以对于每个成就，向其需要的技能状态连边，边权 $\infty$。

建完图以后，直接跑最大流就好了。

```cpp
#include <bits/stdc++.h>
#define awa(x) ((x) + 5 * n)
#define int long long
using namespace std;
int n, m;
const int N = 600;
const int inf = 0x3f3f3f3f3f3f3f3f;
int c[N];
int a[N];
struct node {
	int to, w, next;
};
int head[N], cnt = 1;
node edge[N * N];
int s = 0, t = 599;
int dep[N];
int now[N];
void add_edge(int u, int v, int c) {

	cnt++;
	edge[cnt].next = head[u];
	edge[cnt].to = v;
	edge[cnt].w = c;
	head[u] = cnt;
}
int dfs(int u, int sum) {
	int flow = 0;
	if (u == t) return sum;
	for (int i = now[u]; i && sum; i = edge[i].next) {
		int v = edge[i].to;
		int c = edge[i].w;
		if (dep[v] == dep[u] + 1 && c) {
			int k = dfs(v, min(sum, c));
			sum -= k;
			flow += k;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
		}
		
	}
	return flow;
}
bool bfs() {
	queue<int> q;
	q.push(s);
	memset(dep, 0x3f, sizeof dep);
	dep[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		now[u] = head[u];
		if (u == t) return 1;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int c = edge[i].w;
			if (c && dep[v] == inf) {
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	return 0;
}
int dinic() {
	int ans = 0;
	while (bfs()) ans += dfs(s, inf);
	return ans;
}
int ans = 0;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> c[i];
		for (int j = 2; j <= 5; j++) {
			int u = 5 * (i - 1) + j;
			add_edge(u, t, c[i]);
			add_edge(t, u, 0);
			add_edge(u, u - 1, inf);
			add_edge(u - 1, u, 0);
			
		}
	}	
	for (int i = 1; i <= m; i++) {
		cin >> a[i];
		add_edge(s, awa(i), a[i]);	
		add_edge(awa(i), s, 0);
		ans += a[i];
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			int l;
			cin >> l;
			int p = 5 * (j - 1) + l;
			add_edge(awa(i), p, inf);
			add_edge(p, awa(i), 0);
		}
	}
	cout << ans - dinic();
	return 0;
}
```



---

## 作者：liangbowen (赞：2)

[blog](https://www.cnblogs.com/liangbowen/p/17810306.html)。简单最小割。

---

发现 $L_{i,j}\le5$，所以对 Level 拆点。初始源点 $S\xrightarrow{0} \text{Lvl}1_i, S\xrightarrow{c_i} \text{Lvl}2_i,\text{Lvl}3_i,\text{Lvl}4_i,\text{Lvl}5_i$，表示当前是 $\text{level }1$，每升一级就要多买个 $c_i$。

对于成就，建边 $\text{Achieve}_i\xrightarrow{a_i} T$。割掉这条边，表示你可以不满足这个成就，但是你会少获得 $a_i$ 元。

对于 $L_{i,j}$，建边 $\text{Lvl} k_j\xrightarrow{+\infty}\text{Achieve}_i(1\le k\le L_{i,j})$，表示你获得这个成就就得保证 $1\sim L_{i,j}$ 均买到了。

跑最小割。最小割就是奖励与所用的成本之和，用成本总和减去最小割即为答案。

[code](https://atcoder.jp/contests/abc326/submissions/47292037)，时间复杂度 $O(\text{能过})$。


---

## 作者：Sharpsmile (赞：1)

# [ABC326G] Unlock Achievement 
 
大家全是直接建模啊，感觉非常难想到。

这里给出一种使用知识点，直接套的想法。最后模型建出来应该是一样的。

看到这个题的限制，发现是：如果希望获得某个成就，那么必须要选择一些升级的行为。感觉长得很像闭合子图。

然后你就会发现，可以把每个成就和每个等级的每个技能当做点。

对于成就点，他需要指向所有等级限制的点。点权为这个成就的收益。

对于一个零级点，点权是零，没有限制。

对于第 $i$ 项技能的 $j$ 级点，我们当成可以使用 $C_i$ 的代价进行升到 $j$ 级这个操作，但是前提是至少有 $j-1$ 级，把他向对应技能的 $j-1$ 级点连边。

然后直接求最大权闭合子图即可。

建模最后和其他题解应该没有本质不同，但是直接套最大权闭合子图的模型的话会更好思考。~~属于是强行用知识点代替脑子了~~

---

## 作者：Xy_top (赞：1)

看数据范围，再根据我的经验就能看出这是道网络流了，但是模拟退火也能过，气人。

其实有原题的，太空飞行计划问题，只要稍微改装一下就能过，来讲怎么改装。

对于每个技能拆成 $5$ 个点，分别表示这个技能的 $5$ 个级别，分别和源点连边，流量为学习这个技能要花的钱。

如果一个奖励要求你的技能 $1$ 达到 $3$ 级，那么要把这个技能的 $1$ $2$ $3$ 级都和这个奖励连边，边权为无穷大，每个奖励再和汇点连边，流量为这个奖励的价值。

跑个最小割就行了，证明太长了还和最大权闭合子图相关，就不证了，感兴趣可以去看原题的证明。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m, k, s, t;
int c[51], a[51], d[305], pre[305], head[305];
int l[51][51];
const int inf = 1000000000000000000;
queue <int> q;
struct Node {int u, v, w, nxt;}e[100005];
void add (int u, int v, int w) {
	e[k ++] = {u, v, w, pre[u]};
	pre[u] = k - 1;
}
bool BFS () {
	For (i, 1, 304) head[i] = pre[i];
	memset (d, 0x3f, sizeof d);
	q.push (s);
	d[s] = 0;
	while (!q.empty () ) {
		int u = q.front ();
		q.pop ();
		for (int i = head[u]; ~i; i = e[i].nxt){
			int v = e[i].v;
			if (e[i].w && d[u] + 1 < d[v]) {
				d[v] = d[u] + 1;
				q.push (v);
			}
		}
	}
	return d[t] <= 600;
}
int dfs (int u, int flow) {
	if (u == t || (!flow) ) return flow;
	int ret = 0;
	for (int &i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].v, di;
		if (e[i].w && d[v] == d[u] + 1 && (di = dfs (v, min (flow - ret, e[i].w) ) ) ) {
			ret += di;
			e[i].w -= di;
			e[i ^ 1].w += di;
			if (ret == flow) return ret;
		}
	}
	return ret;
}
void solve () {
	For (i, 1, 304) pre[i] = -1;
	int ans = 0;
	cin >> n >> m;
	For (i, 1, n) cin >> c[i];
	For (i, 1, m) {
		cin >> a[i];
		ans += a[i];
	}
	For (i, 1, m) For (j, 1, n) cin >> l[i][j];
	s = 5 * n + m + 1;
	t = 5 * n + m + 2;
	For (i, 1, n) {
		int x = 5 * (i - 1);
		add (s, x + 1, 0);
		add (x + 1, s, 0);
		add (s, x + 2, c[i]);
		add (x + 2, s, 0);
		add (s, x + 3, c[i]);
		add (x + 3, s, 0);
		add (s, x + 4, c[i]);
		add (x + 4, s, 0);
		add (s, x + 5, c[i]);
		add (x + 5, s, 0);
	}
	For (i, 1, m) {
		add (5 * n + i, t, a[i]);
		add (t, 5 * n + i, 0);
	}
	For (i, 1, m) {
		For (j, 1, n) {
			int x = 5 * (j - 1);
			For (k, 1, l[i][j]) {
				add (x + k, 5 * n + i, inf);
				add (5 * n + i, x + k, 0);
			}
		}
	}
	while (BFS () ) {
		ans -= dfs (s, inf);
	}
	cout << ans;
}
signed main () {
	int _ = 1;
//	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：FReQuenter (赞：1)

发现题目里的条件和问题都很符合最小割的性质。

最大流=最小割。考虑如何建图。

首先我们需要一个源点 $S$ 和汇点 $T$。

发现每个 $l_{i,j}$ 单独一个点很不合适。所以把它拆了。设拆出来之后为 $s_{i,j}$ 表示技能 $i$ 的级别大于等于 $j$。

还需要表示每个成就。所以每个成就单独开一个点 $t_i$。

接下来一个一个连：

源点：连向 $s_i$ 的末尾为初始值，流量 $\inf$。

汇点：所有 $t_i$ 连向 $T$，流量即为达成成就所得奖励 $a_i$。

从 $s$ 到 $t$：最后状态连向成就，流量 $\inf$。

在 $s$ 内部：我们需要将技能 $i$ 的等级由 $j$ 升级到 $j+1$ 的过程。流量 $c_i\times(j-1)$。

那么这个图的最小割就是最小成本加上没有获取到的奖励设为 $x$，答案就是 $\sum_{i=1}^{n}{A_i}-x$。

最后：ABC上粘一个网络流板子太麻烦？可以试试 AtCoder Library(ACL)里面的 `atcoder/maxflow` 头文件。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
using namespace std;
using namespace atcoder;
int n,m,ans,S,T,c[55],a[55],l[55][55];
mf_graph<int> g(255);
signed main(){
	cin>>n>>m;
    S=4*n+m+1,T=S+1;
	for(int i=1;i<=n;i++) cin>>c[i];
	for(int i=1;i<=m;i++) cin>>a[i],ans+=a[i];
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin>>l[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=4;j++) g.add_edge(S,4*(i-1)+j,c[i]);
    for(int i=1;i<=m;i++) g.add_edge(4*n+i,T,a[i]);
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) for(int k=1;k<l[i][j];k++) g.add_edge(4*(j-1)+k,4*n+i,0x3f3f3f3f);
	cout<<ans-g.flow(S,T);
}
```

---

## 作者：_qingshu_ (赞：0)

很典型的以点的状态为分界来拆点的题，难点在想到是网络流（笑。

# 建模：

首先考虑将图中点分为两个集，一个为技能，一个为成就，因为看到 $1\le L_{i,j}\le 5$，那么考虑把每一个技能分为 $5$ 种状态，建立 $6$ 个点，其中第 $i$ 个技能中的边 $level_{j+1}$ 连向 $level_j$ 的流量分别为 $c_i \times (j-1)$，表示将技能升到 $j$ 级所需要的花费。

又因为流量限制，既定流向一定为从大往小，所以把源点往每个技能的第 $6$ 个点连接一条流量无限的边。

考虑如何表示赚钱，那么把每一个成就连接汇点，流量为奖励的钱数。

再把每一个成就所对应的技能等级连接起来，流量无限。

最后跑图把可能得到的奖励钱数总和减去最大流就是答案了。

# 证明：

对于任意一个成就，如果奖励的钱数小于等于其所需支付升级技能的钱，我们可以看作把这 $a_i$ 元的奖励金额去升级技能，并且允许技能等级先支付一部分，这样子我们最后得到的钱并不会增加，但是会成功影响后面共享同一个技能的选择，在其中最大流加上奖励钱数。

如果当前这个成就可以得到的钱大于所需支付升级技能，我们可以赚得这个成就连向汇点的残余流量的钱，如果这个里面有之前预先支付的就更改前面的理解为把这几个成就一起获得总共赚这么多钱，这个正确性是显然的，在其中，最大流加上支付钱数总和。

我们可以发现，最后得出的最大流为完成之后不优的成就的奖励加上完成成就所需要付出的代价，用可能获得所有奖励和减去最大流就是最后可以获得的钱。

# Code：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int n,m,s,t;
int c[5200010],a[5200010],mp[520][520];
struct edge{
	int to,nxt;
	long long val;
}e[5200010];
int head[5200010],tot=1;
inline void add(int u,int v,int val){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].val=val;
	head[u]=tot;
	
	e[++tot].to=u;
	e[tot].nxt=head[v];
	e[tot].val=0;
	head[v]=tot;
}
long long ans=0;
int dep[5200010],now[5200010];
inline bool bfs(){
	queue<int> q;
	q.push(s);
	for(int i=1;i<=t;i++)dep[i]=inf;
	dep[s]=0;
	now[s]=head[s];
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].val&&dep[v]>dep[x]+1){
				dep[v]=dep[x]+1;
				now[v]=head[v];
				q.push(v);
				if(v==t){
					return true;
				}
			} 
		}
	}
	return false;
}
inline long long dfs(int x,long long sum){
	if(x==t)return sum;
	long long res=0,i;
	for(i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(e[i].val&&dep[v]==dep[x]+1){
			int k=dfs(v,min(e[i].val,sum));
			e[i].val-=k;
			e[i^1].val+=k;
			sum-=k;
			res+=k;
		} 
	} 
	now[x]=i;
	return res;
}
inline void dinic(){
	while(bfs()){
		ans+=dfs(s,inf);
	}
}
long long sum=0;
int main(){
	cin>>n>>m;s=5180;t=s+1;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		add(s,i*6,inf);
		for(int j=6;j>=2;j--){
			add((i-1)*6+j,(i-1)*6+j-1,c[i]*(j-2));
		}
	}	
	for(int i=1;i<=m;i++){
		cin>>a[i];
		sum+=a[i];
		add(n*6+i,t,a[i]);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>mp[i][j];
			add((j-1)*6+mp[i][j],n*6+i,inf);
		}
	}
	dinic();
	cout<<sum-ans;
}
```

---

## 作者：best_brain (赞：0)

$\qquad$[题面](https://www.luogu.com.cn/problem/AT_abc326_g)

$\qquad$首先，我们分析一下这道题。在这道题中，想要达成成就 $i$，就必须先使得 $\forall j\in [1,n],level_j\geq L_{i,j}$。这个描述形式非常符合最大权闭合图的形式，所以我们按照最大权闭合图的要求建边。考虑将一个技能点拆成 $level_{1\sim 5}$ 五个点，对于一个成就 $i$ 和一个技能 $j$，我们让 $i$ 向 $level_{j,1\sim L_{i,j}-1}$ 连一条容量为 $INF$ 的边。注意是 $1\sim L_{i,j}-1$，因为每个技能初始 $level$ 都是一。然后从超级源点向所有成就点 $i$ 连一条容量为 $a_i$ 的边，从所有技能点 $j$ 向超级汇点连一条容量为 $c_j$ 的边，答案就是 $\sum_{i=1}^ma_i$ 减去最小割权值。

$\qquad$[代码](https://www.luogu.com.cn/paste/sfvbaijj)

---

