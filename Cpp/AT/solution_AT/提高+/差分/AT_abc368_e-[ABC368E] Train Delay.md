# [ABC368E] Train Delay

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc368/tasks/abc368_e

Atcoder 国には $ 1 $ から $ N $ の番号がついた $ N $ 個の街と、$ 1 $ から $ M $ の番号がついた $ M $ 本の電車が走っています。  
 電車 $ i $ は街 $ A_i $ を時刻 $ S_i $ に発車し、街 $ B_i $ に時刻 $ T_i $ に到着します。

正の整数 $ X_1 $ が与えられるので、$ 0 $ 以上の整数 $ X_2,\ldots,X_M $ を以下の条件を満たすように定める方法のうち、$ X_2+\ldots+X_M $ が最小になるものを求めてください。

- 条件：$ 1\ \leq\ i,j\ \leq\ M $ を満たす全ての組 $ (i,j) $ について、「$ B_i=A_j $ かつ $ T_i\ \leq\ S_j $」ならば「$ T_i+X_i\ \leq\ S_j+X_j $」
  - すなわち、もともと乗り換え可能だった電車の組は、各電車 $ i $ の発車時刻・到着時刻を $ X_i $ 遅らせても乗り換え可能である
 
なお、$ X_2+\ldots+X_M $ が最小になるような $ X_2,\ldots,X_M $ の定め方は一意であることが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ 0\ \leq\ S_i\ <\ T_i\ \leq\ 10^9 $
- $ 1\ \leq\ X_1\ \leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

街 $ 1 $ から $ 2 $ へ行く電車 $ 1 $ の到着が $ 15 $ 遅れ、時刻 $ 35 $ になりました。 街 $ 2 $ での電車 $ 1 $ から $ 3 $ への乗り換えのため、電車 $ 3 $ の発車時刻を $ 10 $ 遅らせて、時刻 $ 35 $ 発 時刻 $ 50 $ 着とします。 さらに街 $ 3 $ での電車 $ 3 $ から $ 6 $ への乗り換えのため、電車 $ 6 $ の発車時刻を $ 5 $ 遅らせて、時刻 $ 50 $ 発とします。 他の電車は発車を遅らせることなく、元々乗り換え可能だった電車の間を乗り換えることができるため、$ (X_2,X_3,X_4,X_5,X_6)=(0,10,0,0,5) $ は条件を満たします。 また、条件を満たすもののうち和がこれより小さいものは存在しないため、これが答えとなります。

## 样例 #1

### 输入

```
3 6 15
1 2 10 20
1 2 20 30
2 3 25 40
2 3 35 50
3 1 15 30
3 1 45 60```

### 输出

```
0 10 0 0 5```

## 样例 #2

### 输入

```
10 9 100
1 10 0 1
10 2 1 100
10 3 1 100
10 4 1 100
10 5 1 100
10 6 1 100
10 7 1 100
10 8 1 100
10 9 1 100```

### 输出

```
100 100 100 100 100 100 100 100```

## 样例 #3

### 输入

```
4 4 10
1 2 0 1
1 2 0 10
2 3 100 200
2 4 100 200```

### 输出

```
0 0 0```

# 题解

## 作者：xiaofu15191 (赞：14)

> 翻译官方题解，加上自己的理解和代码。

首先 $S_i$ 和 $T_i$ 是列车时刻表上虚假的出发/到达时间，我们称真正的出发/到达时间为 $S_i+X_i$ 和 $T_i+X_i$。

然后你发现题目要你求最小的 $X_2+X_3+\ldots+X_m$，所以我们让 $X_i$ 的值尽量小。开始考虑贪心。

因为题目中有 $T_i \leq S_j$ 的限制，所以我们想到将 $T_i$ 和 $S_i$ 看作同一种事物——时刻，按时刻从早到晚排序。

设置三元组 $(Time_i,type_i,id_i)$ 表示列车的一次出发/到达事件，其中 $Time_i$ 表示事件发生的时间，$type_i=0$ 表示到达，$type_i=1$ 表示出发，$id_i$ 表示事件对应的列车编号。以这三个元素依次为第一、二、三关键字排序。

我们再设置一个 $Station_i$，表示最晚到达站点 $i$ 的时刻。

遍历排序过后的事件。对于第 $i$ 个事件 $(Time_i,type_i,id_i)$，我们分类讨论：

- 如果 $type_i=0$，当前的结束站点为 $P=B_{id_i}$，则 $Station_P$ 变为 $\max(Station_P,Time_i+X_{id_i})$，表示最晚到达站点 $i$ 的时刻。

- 如果 $type_i=1$，当前的开始站点为 $P=A_{id_i}$，则 $X_{id_i}$ 变为 $\max(X_{id_i},Station_P-Time_i)$，因为要保证 $T_{id_i} \ge Station_P$ 才可以正常发车。

就这样，我们成功解决了这道 $*2140$ 的题目。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
long long n,m,x1,ans[200010],station[200010];
struct train
{
	long long a,b,s,t;
}trains[200010];
struct event
{
	long long ti,type,id;
};
vector<event>events;
bool cmp(event a,event b)
{
	if(a.ti==b.ti)
	{
		if(a.type==b.type) return a.id<b.id;
		else return a.type<b.type;
	}
	else return a.ti<b.ti;
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&x1);
	for(long long i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&trains[i].a,&trains[i].b,&trains[i].s,&trains[i].t);
		events.push_back((event){trains[i].s,1,i});
		events.push_back((event){trains[i].t,0,i});
	}
	sort(events.begin(),events.end(),cmp);
	ans[1]=x1;
	for(auto e:events)
	{
		long long id=e.id,ti=e.ti,type=e.type;
		if(type)
		{
			if(id>1)
				ans[id]=max(0ll,station[trains[id].a]-ti);
		}
		else station[trains[id].b]=max(station[trains[id].b],ti+ans[id]);
	}
	for(long long i=2;i<=m;i++) printf("%lld ",ans[i]);
}
```

---

## 作者：PineappleSummer (赞：6)

[[ABC368E] Train Delay](https://www.luogu.com.cn/problem/AT_abc368_e)

赛时被歪榜了，没写 E，难受。感觉 E 比 G 题简单。

设从车站 $a$ 出发的一列火车为 $i$，到达车站 $a$ 的一列火车为 $j$。对于所有的 $i$，若 $T_j\le S_i$，需要满足 $S_i+X_i\ge T_j+X_j$。移项，得 $X_i\ge T_j+X_j-S_i$，为了让 $X_i$ 最小，$X_i$ 应等于 $\max\limits_{T_j\le S_i}{(T_j+X_j)}-S_i$。

考虑按照 $S_i$ 从小到大排序，这样保证更新顺序是正确的。因为若 $T_j\le S_i$，一定有 $S_j\le S_i$。

对于更新答案时所需的最大值，用树状数组维护即可。具体地，对于每个车站开一个树状数组，下标为 $T_i$，值为 $T_j+X_j$ 的最大值。但是下标值域过大，可以使用 `unordered_map` 代替数组。

时间复杂度 $\Theta (m\log V)$。

```cpp
struct Node {int a, b, s, t, id; } a[N];
namespace BIT {
    umap <int, int> c[N];
    void add (int p, int x, int y) {
        for (; x < MAXN; x += x & -x) c[p][x] = max (c[p][x], y);
    }
    int ask (int p, int x) {
        int res = 0;
        for (; x; x -= x & -x) res = max (res, c[p][x]);
        return res;
    }
}
bool operator < (Node x, Node y) { return x.s < y.s; }
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n >> m >> x[1];
    for (int i = 1; i <= m; i++) {
        cin >> a[i].a >> a[i].b >> a[i].s >> a[i].t;
        a[i].id = i;
    }
    sort (a + 1, a + m + 1);
    for (int i = 1; i <= m; i++) {
        if (a[i].id != 1) x[a[i].id] = max (0ll, BIT::ask (a[i].a, a[i].s) - a[i].s);
        BIT::add (a[i].b, a[i].t, a[i].t + x[a[i].id]);
    }
    for (int i = 2; i <= m; i++) cout << x[i] << ' ';
    return 0;
}
```

---

## 作者：M1saka16I72 (赞：6)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc368-e.html)

笑点解析：

![](https://pic.imgdb.cn/item/66c9e5c7d9c307b7e9825b80.png)

![](https://pic.imgdb.cn/item/66ca8fbad9c307b7e95510b9.png)

![](https://pic.imgdb.cn/item/66ca780ad9c307b7e93b5f58.png)

## 思路

一种很新的建图 trick，看完题解你会发现这题的思想和 [[ABC232G] Modulo Shortest Path](https://www.luogu.com.cn/problem/AT_abc232_g) 一模一样。

先想缩小数据范围怎么做。题意相当于一堆形如 $X_i+(T_i-S_j)\leq X_j$ 的不等式，给定 $X_1$，要求最小的一组解。如果点数 $m$ 缩小到 $500$，这就是一个差分约束跑最长路的经典问题，直接暴力从每个 $i$ 向 $j$ 连边建图跑最长路然后输出答案即可，边数为 $m^2$ 级别，但有一个很好的性质就是题目保证 $T_i\leq S_j$，差分约束边权全部为非正值，可以不用跑 spfa，使用复杂度为 $\mathcal{O}(m^2\log m)$ 的 Dijkstra 求解即可。关于跑最长路能最小化解的正确性不再赘述，感性理解一下最短路算法的松弛过程即可。

我们发现这个做法的瓶颈主要在于图上的边数，如果能把边数缩小到 $\mathcal{O}(m)$ 级别就好了。观察连边过程，我们发现如果将所有 $A_j$ 相等的 $j$ 放在一起按 $S_j$ 排序，那么每次从 $i$ 向 $j$ 连边都是在 $A_j=B_i$ 的所有 $j$ 中挑一段后缀连边。这启示我们使用后缀和优化建图。具体的，在图上新建 $m$ 个虚点，对于每一堆 $A_j$ 相等的 $j$，都连上 $(j+m,j,-S_j)$ 和 $(j+m,j+m+1,0)$ 两条有向边，这样对于每个 $i$ 就只用二分最小的满足 $S_j\geq T_i$ 的 $j$，连边 $(i,j+m,T_i)$ 即可。

![](https://pic.imgdb.cn/item/66ca8bb2d9c307b7e951c526.png)

但是问题还没有解决。刚刚的优化建图方式边数为 $\mathcal{O}(m)$，但边权存在正负两种值，只能跑复杂度 $m^2$ 的 spfa。由于跑的是最长路，考虑怎么把边权全部转化为负值，这样就可以在全负权图上跑 Dijkstra 了。挖掘“后缀和优化建图”的性质，我们发现一件神奇的事情：如果将所有 $(j+m,j+m+1)$ 的权值改为 $S_j$ 的差分，由于差分的后缀和就是原序列，我们就可以直接凑出每个 $S_j$！把边权修改为下图的形式，由于 $S_j$ 从小到大排序，且保证 $T_i\leq S_j$，现在图上的边权已经全为负数了。

![](https://pic.imgdb.cn/item/66ca8c14d9c307b7e95218d6.png)

于是这题我们就做完了，时间复杂度 $\mathcal{O}(m\log m)$。

## 代码

[link](https://atcoder.jp/contests/abc368/submissions/57109388)，赛时差分约束写错源点调了一百年，结束后五分钟才过的代码，写的很丑。

---

## 作者：zrl123456 (赞：4)

[[ABC368E] Train Delay ](https://www.luogu.com.cn/problem/AT_abc368_e)  

题目考察：图论建模，思维，双指针。  
题目简述：  
有 $m$ 辆火车在 $n$ 个城市间穿梭，对于第 $i$ 辆火车，他会在 $s_i$ 时刻从 $a_i$ 城市出发，在 $t_i$ 时刻从到达 $b_i$ 城市。  
现在第 $1$ 辆火车推迟了 $ans_1$ 单位时间，问在使得推迟总时间最小的情况下，怎样使原本可以换乘的火车现在还可以换乘（换乘不需要时间）。  
数据范围：  
- $2\le n,m\le 2\times 10^5$
- $\forall i\in[1,m],1\le a_i,b_i\le n,a_i\ne b_i$
- $\forall i\in[1,m],0\le s_i<t_i\le 10^9$
- $1\le ans_1\le 10^9$
---
要想直接跑拓扑的话，轻轻松松就卡成 $\Theta(n^2)$ 了，不可行。  

那么我们发现瓶颈是在拓展以下式子而变慢的：
$$ans_v=max(0,ans_u+t_u-t_v)$$
但是我们发现，$ans_u+t_u$ 这部分都是一样的，那么我们可以将其记录在 $b_u$ 这个点上，当拓展这个式子时从这个点上取值计算就可以了。  

当然，$t_u\le s_v$ 的才有贡献，那么我们复制一份火车时程表，一个按 $s_i$ 排序，一个按 $t_i$ 排序，跑一个类似于双指针的东西就可以了。   

时间复杂度为 $\Theta(m\log m)$，瓶颈在排序。  

[代码](https://atcoder.jp/contests/abc368/submissions/57076714)

---

## 作者：Richard_Whr (赞：4)

来一发抽象但是比较好想的题解。

首先看到这样的限制 $x_i+T_i \le x_j + S_j$ 为不等关系的二元限制，再看到最终的目标是最小化每个值。

很难不想到差分约束，然后最小化跑最长路建边方向是 $\le$。

如果暴力 $n^2$ 建图的话肯定是寄了，考虑优化建图。

将每趟列车挂在起始和终止位置上，然后分别按照 $S,T$ 从大到小排序。

这样每个终止位置在这里的列车 $i$ 都会向其实位置在这里的 $j$ 且 $T_i \le S_j$ 的列车连边，权值为 $T_i-S_j$。

拆边权然后前缀优化建图，这样点边数量都变成了 $O(m)$ 级别。

此外还需要注意由于 $1$ 被钉死，需要连 $(0,1,X_1)$ 的边。

~~我不会告诉你跑个堆优化spfa就过了。~~

咳咳，考虑到 spfa 算法的不稳定性，寻找复杂度更优的算法进行最长路求解。

此时需要一个观察，由于发车时间是 $S_i \le T_i$ 的，而且是 $T_i \le S_j$ 的才会连边，因此不会连出环来，整张图是一张 DAG。

那直接拓扑排序好了，复杂度为 $O(m)$。

其实想到这里已经和官方题解很接近了。

我们直接将每趟列车拆成起点和终点，按照拓扑序遍历所有节点，拓扑序就是 $S,T$ 一块从小到大排序完之后的。在终点更新所有在这个点发车的列车的最早时间，在起点直接取出最早时间即可。

这相当于隐式的拓扑排序。

代码写的是差分约束系统。

不知道 spfa 在拓扑图上是不是有可观的复杂度，或者加上什么优化就是理论可过的。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int N=4e5+10;
int A[N],B[N],S[N],T[N];
int d[N],din[N];
bool st[N];
vector<PII> e[N];
int n,m,X;
vector<int> vec1[N];
vector<int> vec2[N];
int pre[N],tot;
 
void add(int a,int b,int c)
{
	e[a].push_back({b,c});
	din[b]++;
}

void Topsort()
{
	queue<int> q;
	for(int i=0;i<=tot;i++) if(!din[i]) q.push(i);
	while(q.size())
	{
		int u=q.front();q.pop();
		for(auto it:e[u])
		{
			int v=it.first,w=it.second;
			d[v]=max(d[v],d[u]+w);
			din[v]--;
			if(!din[v]) q.push(v);
		}
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m>>X;
	for(int i=1;i<=m;i++) cin>>A[i]>>B[i]>>S[i]>>T[i],vec1[B[i]].push_back(i),vec2[A[i]].push_back(i);
	
	add(0,1,X);
	tot=m;
	for(int i=1;i<=n;i++)
	{
		if(!vec1[i].size() || !vec2[i].size()) continue;
		sort(vec2[i].begin(),vec2[i].end(),[&](int x,int y){return S[x]>S[y];});
		sort(vec1[i].begin(),vec1[i].end(),[&](int x,int y){return T[x]>T[y];});
		for(int j=0;j<vec2[i].size();j++) 
		{
			pre[j]=++tot;
			if(j) add(pre[j],pre[j-1],0);
			add(pre[j],vec2[i][j],-S[vec2[i][j]]);
		}
		for(int j=0,k=0;j<vec1[i].size();j++)
		{
			while(k<vec2[i].size() && S[vec2[i][k]]>=T[vec1[i][j]]) k++;
			if(k>0) add(vec1[i][j],pre[k-1],T[vec1[i][j]]);
		}
	}
	
	Topsort();
	
	for(int i=2;i<=m;i++) cout<<d[i]<<" ";
	
	cout<<"\n";
	
	return 0;
}
```

---

## 作者：shao0320 (赞：3)

注意到除开 $X_1$，其余所有的 $X$ 均满足，$X_j=\max(T_i+X_i-S_j),T_i<S_j$。

显然有，若 $T_i<S_j$， 则 $S_i<S_j$

那么考虑对每一个站点维护所有以该站点为终点站的列车 $i$ 中 $T_i+X_i$ 。并按 $S$ 排序所有列车，查询该站点中所有原本可以换乘的车辆的 $T_i+X_i$ 最大值即可。

查询时需要考虑 $T_i$ 的限制，使用树状数组，用下标对应时间，查询前缀最大值即可，但会爆空间，使用 unordered_map 进行动态开点即可。

code:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#define N 500005
#define lowbit(x) x&-x
#define int long long
#define MAXN 2000000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int n,m,X[N],f[N],b[N],cnt,tot;
unordered_map<int,int>c[N];
struct train{int a,b,s,t,id;}t[N];
struct Fenwick_Tree
{
    void modify(int p,int x,int k)
    {
        for(;x<=MAXN;x+=lowbit(x))
        {
            c[p][x]=max(c[p][x],k);
        }
    }
    int query(int p,int x)
    {
        int res=0;
        for(;x;x-=lowbit(x))
        {
            res=max(res,c[p][x]);
        }
        return res;
    }
}T;
bool cmp(train a,train b){return a.s<b.s;}
signed main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    n=read();m=read();X[1]=read();
    for(int i=1;i<=m;i++)
    {
        t[i].a=read();t[i].b=read();t[i].s=read();t[i].t=read();
        t[i].id=i;b[++cnt]=t[i].t;
    }
    sort(t+1,t+1+m,cmp);
    for(int i=1;i<=m;i++)
    {
        if(t[i].id!=1)X[t[i].id]=max(T.query(t[i].a,t[i].s)-t[i].s,0ll);
        T.modify(t[i].b,t[i].t,t[i].t+X[t[i].id]);
    }
    for(int i=2;i<=m;i++)printf("%lld ",X[i]);
}
```

---

## 作者：huangrenheluogu (赞：3)

需要求 $x_i\le x_1+k$，容易让我想到差分约束。

由于对于 $B_i=A_j,T_i\le S_j$ 的边都要搞，可以排序一下线段树优化建图。

突然发现这个图是一个 dag，跑拓扑 dp 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fir first
#define sec second
#define mid (l + r >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
using namespace std;
const int N = 2e5 + 5;
int n, m, x1, f[N * 5], deg[N * 5], l, r, L, R;
int q[N * 5], h, t;
vector<pii> G[N * 5];
struct node{
	int s, t, a, b, id;
}a[N];
inline void addedge(int x, int y, int z){
	G[x].push_back({y, z});
	deg[y]++;
}
inline void build(int p, int l, int r){
	for(int i = l; i <= r; i++){
		addedge(p + m, a[i].id, -a[i].s);
	}
	if(l == r) return ;
	build(ls, l, mid);
	build(rs, mid + 1, r);
}
inline bool operator < (node x, node y){
	if(x.a == y.a) return x.s < y.s;
	return x.a < y.a;
}
inline void modify(int p, int l, int r, int x, int y, int v, int u){
	if(x <= l && r <= y){
		addedge(u, p + m, v);
		return ;
	}
	if(mid >= x) modify(ls, l, mid, x, y, v, u);
	if(mid < y) modify(rs, mid + 1, r, x, y, v, u);
}
inline void topo(){
	for(int i = 1; i <= m * 5; i++){
		if(deg[i] == 0) q[++t] = i;
	}
	#define x q[h]
	while(h < t){
		h++;
		for(pii e : G[x]){
			f[e.fir] = max(f[e.fir], f[x] + e.sec);
			deg[e.fir]--;
			if(!deg[e.fir]) q[++t] = e.fir;
		}
	}
	#undef x
}
signed main(){
	scanf("%lld%lld%lld", &n, &m, &x1);
	for(int i = 1; i <= m; i++){
		scanf("%lld%lld%lld%lld", &a[i].a, &a[i].b, &a[i].s, &a[i].t);
		a[i].id = i;
	}
	sort(a + 1, a + m + 1);
	build(1, 1, m);
//	for(int i = 1; i <= m; i++){
//		printf("%lld ", a[i].id);
//	}
//	puts("");
	for(int i = 1; i <= m; i++){
		L = m + 1, R = m + 1;
		l = 1, r = m;
		while(l <= r){
			if(a[mid].a > a[i].b || (a[mid].a == a[i].b && a[mid].s >= a[i].t)){
				L = mid, r = mid - 1;
			}
			else l = mid + 1;
		}
		l = 1, r = m;
		while(l <= r){
			if(a[mid].a > a[i].b){
				R = mid, r = mid - 1;
			}
			else l = mid + 1;
		}
		R--;
		if(L <= R){
//			cerr << a[i].id << ' ' << L << ' ' << R << endl;
			modify(1, 1, m, L, R, a[i].t, a[i].id);
		}
	}
	f[1] = x1;
	topo();
	for(int i = 2; i <= m; i++){
		printf("%lld ", f[i]);
	}
	puts("");
	return 0;
}
```

---

## 作者：licn (赞：2)

## **思路分析：**

首先我们按照 $s$ 也就是出发时间排序，我们可以发现后面的一定到不了前面，那么排在后面的就不会影响前面的。

并且使前面的 $x$ 数组尽量小，也会使后面的更优。

对于排完序后当前的 $i$，如果 $j<i$ 且 $s_i \ge t_j$ 且 $b_j=a_i$ 那么 $j$ 会对 $i$ 产生影响。

由题 $s_i+x_i \ge t_j+x_j$ 那么 $x_i$ 的值取决于符合条件的 $j$ 中最大的 $t_j+s_j$，$x_i=\max(0,\max(t_j+x_j)-s_i)$。

## **如何维护？**

从前往后跑，跑完当前的 $j$ 丢到小根堆里面，当后面跑到 $i$ 时，满足 $s_i \ge t_j$ 时出队，更新 $b_j$ 这个点对应的最大 $t+x$。

因为 $s$ 是单调的，丢到小跟队里后 $t$ 也是单调的，所以每个点最多入队一次出队一次，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n,m,x[N],f[N],cnt;
struct node{
	int a,b,s,t,id;
}h[N];
bool cmp(node hzx,node lcn){
	if(hzx.s==lcn.s)return hzx.id<lcn.id;
	return hzx.s<lcn.s;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>x[1];
	for(int i=1;i<=m;i++)cin>>h[i].a>>h[i].b>>h[i].s>>h[i].t,h[i].id=i;
	sort(h+1,h+1+m,cmp);
	int fl=0;
	priority_queue<pair<int,int> >q;
	for(int i=1;i<=m;i++){
		int p=h[i].id;
		while(q.size()){
			int z=q.top().second;
			if(h[z].t>h[i].s)break;
			q.pop();
			f[h[z].b]=max(f[h[z].b],h[z].t+x[h[z].id]);
		}
		if(p==1)fl=1;
		if(p!=1&&fl)x[p]=max(0ll,f[h[i].a]-h[i].s);
		q.push({-h[i].t,i});
	}
	for(int i=2;i<=m;i++)cout<<x[i]<<" ";
	return 0;
}

---

## 作者：EricWan (赞：2)

这题我本来能首切的，但是先做的别的题！急了！

对于每一个节点，建立一个动态开点维护最大值的树状数组记录再某个时刻以前到站的车推迟后最晚的到站时间。

从发车时间小到大考虑每一个车，再发车点查询后更新终点的树状数组。

动态开点树状数组因为要维护最大值，自然想到 `unordered_map`，把 $n$ 个 `unordered_map` 当做树状数组用就可以，代码很短，但不好想，很像一个 CF 题，常打 CF 我竟然做出来了。

---

## 作者：spire001 (赞：2)

## 题目分析

将这些火车按出发时间排序，这样的话每次处理某一辆车的时候可以保证可以用于换乘的车已经被处理过了。

分析一下某一辆车的 $x$ 的取值。

假如前一辆车 $i$ 的终点是后一辆车 $j$ 的起点且 $t_i\ge s_j$ 同时 $t_i +x_i \ge s_j + x_j$。容易发现 $x_j=\max\limits _{b_i=a_j\wedge t_i\ge s_j}{t_i+x_i-s_j}$。

挑数据结构倒是好说，开 $n$ 个动态开点线段树维护区间最值即可。每一个航线在代表终点的树加入 $t_i+x_i$ 随时准备查询最大值。

细节方面就是需要离散化以及注意数据范围。。。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#include <queue>
#define int long long
#define lowbit(x) (x & -(x))

using namespace std;

typedef long long LL;

constexpr int N = 300010;
string s;
int n, k, m, ln;

struct node {
  int u, v, l, r, id;
} a[N];
LL b[N << 1]; // 离散化两倍空间

// 动态开点线段树
struct tree {
  int lc, rc;
  LL val;
} t[N * 100]; int rt[N], tot;

inline void up(const int root)
{
  t[root].val = max(t[t[root].lc].val, t[t[root].rc].val);
  return;
}
void insert(const int l, const int r, const int pos, const LL val, int &x)
{
  if (!x) x = ++tot;

  if (l == r)
  {
    t[x].val = max(t[x].val, val);
    return;
  }

  const int mid = (l + r) >> 1;

  if (pos <= mid)
    insert(l, mid, pos, val, t[x].lc);
  else 
    insert(mid + 1, r, pos, val, t[x].rc);
  
  return up(x);
}
LL ask(int l, int r, int u, int v, int root) // 询问最大值
{
  if (!root) return 0;
  if (u <= l && r <= v) return t[root].val;

  const int mid = (l + r) >> 1;

  LL ans = 0;

  if (u <= mid)
    ans = max(ans, ask(l, mid, u, v, t[root].lc));
  if (v >  mid)
    ans = max(ans, ask(mid + 1, r, u, v, t[root].rc));
  
  return ans;
}

LL x[N];

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n >> m >> x[1];

  for (int i = 1; i <= m; i++) cin >> a[i].u >> a[i].v >> a[i].l >> a[i].r, a[i].id = i;
  sort(a + 1, a + m + 1, [](const node A, const node B) { return A.l != B.l ? A.l < B.l : A.r < B.r; }); // 按出发时间排序

  for (int i = 1; i <= m; i++) b[++ln] = a[i].l, b[++ln] = a[i].r;
  
  sort(b + 1, b + ln + 1); ln = unique(b + 1, b + ln + 1) - b - 1; // 离散化

  for (int i = 1; i <= m; i++)
  {
    a[i].l = lower_bound(b + 1, b + ln + 1, a[i].l) - b;
    a[i].r = lower_bound(b + 1, b + ln + 1, a[i].r) - b;
  }

  // insert(1, ln, a[1].r, b[a[1].r] + x[1], rt[a[1].v]);

  // 注意 x[1] 是给定的
  for (int i = 1; i <= m; i++)
  {
    // if (a[i].id == 1) continue;
    if (a[i].id != 1)
      x[a[i].id] = max(0ll, ask(1, ln, 1, a[i].l, rt[a[i].u]) - b[a[i].l]);
    insert(1, ln, a[i].r, b[a[i].r] + x[a[i].id], rt[a[i].v]);
  }

  for (int i = 2; i <= m; i++) cout << x[i] << ' ';

  return 0;
}
```

---

## 作者：快乐的大童 (赞：2)

发现这个设题形式 $T_i+X_i\le S_j+X_j$ 非常像差分约束。

但是官方给出的正解不是差分约束。

那么这题怎么用差分约束去做呢？

令 $U_i,V_i$ 表示边 $i$ 的起点和终点，$S_i,T_i$ 表示边 $i$ 的起始时间和终止时间。

考虑先如何求出 $\sum X_i$ 的最小值。用差分约束跑最长路跑出 $X_i$ 的一组字典序最小解，那么该解即为 $\sum X_i$ 的最小解。

>感性理解一下，首先每个 $X_i$ 不能在原有的解的基础上继续减小，其次若我们增大 $X_i$ 的值，因为是最长路，所以只会使其他的 $X_j(j\not =i)$ 增大或不变。

转化式子，$T_i+X_i\le S_j+X_j\rightarrow X_j-X_i\ge T_i-S_j$。考虑对每条边建点，对于两条边 $i,j$，若 $V_i=U_j$ 且 $T_i\le S_j$，根据上述式子 $X_j-X_i\ge T_i-S_j$，从 $i\rightarrow j$ 连一条长度为 $T_i-S_j$ 的边。

那么，从 $1$ 开始跑最长路（注意 $X_1$ 是给定的不能赋成 $0$），跑出来的解即为答案。

如果存在某些边不和 $1$ 连通，对于每个不和 $1$ 连通的连通块，因为是字典序最小解，所以令连通块内编号最小的点作为起点，初值赋成 $0$ 即可。

由于 $T_i\le S_j$ 才连边，所以原图边权必定非正，用 dijkstra 跑非正权最长路即可，把边权取反后就是非负权最短路了，但注意此时需要把 $X_1$ 和求得的答案都取反并和 $0$ 取最大值（因为 $X_i\ge 0$）。

但是此时边数达到了 $O(m^2)$，肯定过不去。

考虑一条边能和谁连边，将该边终点的所有出边按照 $S_j$ 排序，那么该边能连边的边在这些出边中是一段后缀，后缀和优化建图即可。注意此时需要另开新点然后让新点往其所指代的点连 $0$ 权边。时间复杂度 $O(m\log m)$。

代码：[https://atcoder.jp/contests/abc368/submissions/57115715](https://atcoder.jp/contests/abc368/submissions/57115715)

---

## 作者：_ayaka_ (赞：1)

延误列车（迫真
### 详解题意

有 $N$ 个地点，$M$ 辆列车，一辆列车是在第 $S_i$ 分钟时从 $A_i$ 发车，在第 $T_i$ 分钟时到达 $B_i$。定义如果两辆列车 $(i,j)$ 前一辆的终点 $B_i$ 等于后一辆的起点 $A_j$，且前一辆的到达时间 $T_i$ 小于等于后一辆的发车时间 $S_i$，称这两辆列车是“可换乘”的。

现在告诉你第一辆列车晚点了 $X_i$ 分钟，即其发车时间 $S_i$ 与到达时间 $T_i$ 都将延后 $X_i$ 分钟，问你如何在所有列车的晚点时间总和最小的情况下，保证原先“可换乘”的两辆列车 $(i,j)$ 依然满足此条件？

### 思路

考虑建图，但发现建出来边数极多，于是转换思路，选择从时刻点的方向思考。将发车时间与到达时间放在一起讨论。想到发车时刻一个时刻只会被原本时刻在自己之前的到达时刻时刻所影响，因此将所有时刻排序，可以求出在此发车时刻前所有到达时刻内 $T_j+X_j$ 的最大值，改变 $X_i$ 并附给此发车时刻与其对应的到达时刻。因此我们的操作就可以是这样的：

1. 用一个数组 $w_u$ 表示目前以第 $u$ 个点为起点的列车的最早发车时间。
2. 对于每个到达时间 $T_i$，将其与 $w_{B_i}$ 取 $\max$。
3. 对于每个发车时间 $S_i$，将其 $X_i$ 改为 $w_{A_i}$（若为负数就不改）并将 $X_i$ 附给 $T_i$。

时间复杂度为 $O(n\log n)$，即排序的复杂度。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, ans[1000005], x[1000005], w[1000005];
struct tim {
	int op, d, ti, id;
} t[1000005];
bool cmp(tim b1, tim b2) {
	if (b1.ti == b2.ti) {
		if (b1.op == b2.op) return b1.id < b2.id;
		return b1.op > b2.op;
	}
	return b1.ti < b2.ti;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> x[1];
	for (int i = 1; i <= m; i++) {
		cin >> t[i * 2 - 1].d >> t[i * 2].d >> t[i * 2 - 1].ti >> t[i * 2].ti;
		t[i * 2 - 1].id = t[i * 2].id = i;
		t[i * 2 - 1].op = 0, t[i * 2].op = 1;
	}
	sort(t + 1, t + 2 * m + 1, cmp);
	for (int i = 1; i <= 2 * m; i++) {
		if (t[i].op == 0) {
			x[t[i].id] = max(x[t[i].id], w[t[i].d] - t[i].ti);
		} else {
			w[t[i].d] = max(w[t[i].d], t[i].ti + x[t[i].id]);
		}
	}
	for (int i = 2; i <= m; i++) cout << x[i] << " ";
	return 0;
}
```

---

## 作者：123zbk (赞：1)

**题意简述**：

一共 $n$ 个点，每个点给定 $A_i$，$B_i$，$S_i$ 和 $T_i$。给定$X_1$，现需要求出非负整数序列  $X_2,\ldots,X_M$ 的最小值，满足：对于所有 $1 \leq i,j \leq M$，如果 $B_i=A_j$ 且 $T_i \leq S_j$ ，那么 $T_i+X_i \leq S_j+X_j$ 。

**主体思路**：

看到不等式想到差分约束，转化一下就是满足 $X_i+(T_i-S_j) \leq X_j$，可以直接 dijkstra 跑最长路。此时边数为 $m^2$ 级别，考虑优化。

对于每一个 $B_i$，我们要找出所有和它相等的 $A_j$。所以对于所有 $A_j$ 相等的点，按照 $S_j$ 从小到大排序，可知 $T_i$ 应与一段后缀连边。二分找到第一个 $S_j>T_i$ 的 $j$，考虑建 $m$ 个虚点，此时将 $i$ 和 $j$ 对应的虚点连一条 $T_i$ 的边，虚点和虚点之间边权为 $0$，虚点和对应实点之间的边权为 $-S_j$。这样我们将边数就优化成 $O(m)$ 级别。

但是此时边权有正有负，不能使用 dijkstra。这里用一个小 trick，将 $i$ 和 $j$ 对应的虚点的边权改为 $T_i-S_j$，将虚点和虚点之间的边权改为 $S_j$ 的差分，虚点和对应实点的边权改为 $0$。此时边权全部变成非正数，跑 dijkstra 最长路即可。

时间复杂度 $O(m\log m)$。

**code**:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int n,m,x,tot;
int head[N],a[N],b[N],s[N],t[N],dis[N],vis[N];
struct edge
{
	int to,nxt,w;
}e[N<<1];
struct node
{
	int u,dis;
	bool operator <(const node &ret) const{
		return dis<ret.dis;
	} 
};
priority_queue <node> q;
struct Node
{
	int s,id;
	bool operator <(const Node &ret) const{
		return s<ret.s;
	}
};
vector <Node> V[N];
void add(int u,int v,int w)
{
	++tot;
	e[tot].to=v;
	e[tot].nxt=head[u];
	e[tot].w=w;
	head[u]=tot;
}
void dijk(int s)
{
	memset(dis,-0x3f,sizeof(dis));
	dis[s]=0;
	q.push({s,dis[s]});
	while(!q.empty()){
		node tmp=q.top();
		q.pop();
		int u=tmp.u;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			int w=e[i].w;
			if(dis[v]<dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({v,dis[v]});
			}
		}
	}
}
int main()
{
	//freopen("random.in","r",stdin);
	//freopen("ans.out","w",stdout);
	cin>>n>>m>>x;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&a[i],&b[i],&s[i],&t[i]);
		V[a[i]].push_back({s[i],i});
	}	
	for(int i=1;i<=n;i++){
		if(V[i].empty()) continue;
		sort(V[i].begin(),V[i].end());
		if(V[i].size()>1){
			for(int j=0;j<V[i].size()-1;j++){
				add(V[i][j].id+m,V[i][j+1].id+m,s[V[i][j].id]-s[V[i][j+1].id]);
			}
		}
		for(auto it:V[i]){
			add(it.id+m,it.id,0);
		}
	}
	for(int i=1;i<=m;i++){
		if(V[b[i]].empty()) continue;
		auto it=lower_bound(V[b[i]].begin(),V[b[i]].end(),(Node){t[i],-1});
		if(it!=V[b[i]].end()){
			add(i,(*it).id+m,t[i]-(*it).s);
		} 
	}
	add(0,1,x);
	dijk(0);
	for(int i=2;i<=m;i++){
		printf("%d ",(dis[i]==0x3f3f3f3f)?0:max(0,dis[i]));
	}
	return 0;
} 
/*
3 5 5
1 2 15 30
2 3 30 40
3 1 50 60
2 3 30 50
3 1 30 60
*/
```

---

