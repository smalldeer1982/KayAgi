# [NWRRC 2016] CodeCoder vs TopForces

## 题目描述

在 Byteland，竞赛编程非常流行。事实上，每位 Byteland 的公民都在两个编程网站——CodeCoder 和 TopForces 上注册。每个网站都有自己专有的评分系统。每位公民在每个网站上都有一个唯一的整数评分，代表他们的技能。评分越高，技能越好。

Byteland 的人天生乐观。公民 A 认为，如果存在一个 Byteland 公民的序列 $A = P_{0}, P_{1},...,P_{k} = B$，对于某个 $k \ge 1$，使得对于每个 $i (0 \le i < k)$，$P_{i}$ 在一个或两个网站上的评分都高于 $P_{i+1}$，那么他就有机会在编程比赛中击败公民 B。

每位 Byteland 公民都想知道他们在编程比赛中可能击败多少其他公民。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
2 3
3 2
1 1
4 5
```

### 输出

```
2
2
0
3
```

# 题解

## 作者：IDNo1 (赞：6)

# P7033题解

这是一道比较水的绿题。

前言：本人代码中的 `re` 即 `register int`，用 `#define` 宏定义即可实现。

解题思路：由于关系具有传递性，所以不能直接暴力枚举，我们需要建立一张图，再进行扫描，求出答案。

第一步：
定义一个结构体，来存放每一个人的信息。


```cpp
struct node
{
	int a,b,s;
}x[100001];
```

设这是第 $s$ 个人，则 $a$ 表示 $CC_s$，$b$ 表示 $TF_s$，由于后续阶段需要进行排序，我们再定义一个变量 $s$ 表示这是第 $s$ 个人的信息。

第二步：
我们需要先处理读入数据。由于数据量较大，我们需要用快读和快写降低时间复杂度。

这是快读和快写的模板代码，不理解的人可以用普通的 `cin` 和 `cout` 替代。
```cpp
inline int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}
inline void write(int x)
{
    if (x>9) 
	{
        write(x/10);
    }
    putchar(x%10+'0');
}
```
读入数据则需要如下简单的代码（会循环和数组的人都看得懂）：

```cpp
n=read();
for(re i=0;i<n;i++)
{
	x[i].a=read();
	x[i].b=read();
	x[i].s=i;
}
```

第三步：由于强具有传递性，所以我们需要根据 $CC_i$ 和 $TF_i$ 的具体情况分别处理，两个排序函数就可以搞定。代码如下：
```cpp
bool cmp(node u,node v)
{
	return u.a<v.a;
}
bool cmp2(node u,node v)
{
	return u.b<v.b;
}
```
调用则可以这样写，本人用向量进行存图：
```cpp
sort(x,x+n,cmp);
for(re i=1;i<n;i++)
{
	v[x[i].s].push_back(x[i-1].s);
}
sort(x,x+n,cmp2);
for(re i=1;i<n;i++)
{
	v[x[i].s].push_back(x[i-1].s);
}
```
第四步：计算。这是解这道题目最核心的代码，我们可以 `bool` 一个 $vis$ 数组，来记录此人的情况是否被计算过，因为强具有传递性，所以用 `dfs` 搜索就可以得到正确答案。
```cpp
void dfs(re now)
{
	vis[now]=1;//标记已访问
	sum+=1;//开始的时候令 sum=0，由于强具有传递性，所以用类似前缀和的思路即可解决
	for(re i=0;i<v[now].size();i++)//遍历其可以通以打败的人，解决传递性的问题
	{
		if(!vis[v[now][i]])//此人还没有计算过
		{
			dfs(v[now][i]);//搜索
		}
	}
}
```

调用则如下：
```cpp
for(re i=0;i<n;i++)
{
	if(!vis[x[i].s])
	{
		dfs(x[i].s);
	}
	ans[x[i].s]=sum-1;
}
```
因为是从 $0$ 至 $n-1$ 所以每个数据在计算后都会被更新。

其中 $ans$ 数组用于记录答案，因为每个人都会把自己算进去，所以减一即可。

你学会了吗？

---

## 作者：ni_ju_ge (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P7033)
## 思路
先对强的关系进行连边（由强到弱）。由于强具有传递性，那么题目就等价于求从每个点出发能到达的点的个数。

一个一个点搜是 $O(n^2)$ 的，显然会超时。考虑优化，可以在数组中由弱到强排序，这样 $i$ 能到的 $i+1$ 也能到，搜过的点不用再搜，搜 $i+1$ 时只用在 $i$ 的答案上叠加即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
	int ed[5],id,T,C;
} di[114514];
bool cmp(node i,node j) {
	return i.C<j.C;
}
bool pmc(node i,node j) {
	return i.T<j.T;
}
int ans[114514],n,t[114514],su;//ed[] 和 id 存原编号，t[i] 存 i 现编号 
bool used[114514];
void dfs(int pos) {
	su++;
	used[pos]=true;
	for(int i=1;i<=di[pos].ed[0];i++) {
		int nxt=t[di[pos].ed[i]];
		if(!used[nxt]) dfs(nxt);
	}
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) {
		di[i].id=i;
		cin>>di[i].C>>di[i].T;
	}
	sort(di+1,di+n+1,cmp);
	for(int i=2;i<=n;i++) {
		di[i].ed[++di[i].ed[0]]=di[i-1].id;
	}
	sort(di+1,di+n+1,pmc);
	for(int i=1;i<=n;i++) {
		t[di[i].id]=i;
		if(i==1) continue;
		di[i].ed[++di[i].ed[0]]=di[i-1].id;
	}
	for(int i=1;i<=n;i++) {
		if(!used[i]) dfs(i);
		ans[di[i].id]=su-1;//把自己也算进去了，所以要减一
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
}
```

---

## 作者：Fkxxx (赞：3)

题解有一点长，有不懂的可在下方评论区问我。

### 题目

给出一堆人，他们有两种能力指标。

如果第 $i$ 个人任意一种指标大于第 $j$ 个人，那么我们认为第 $i$ 个人能打败第 $j$ 个人。

你需要计算每个人能打败的人的数量。

### 思路

我们可以利用强的关系建**有向图**，如果 $i$ 节点到 $j$ 节点有通路，那么 $i$ 就强于 $j$。

怎么建图呢？

可以分别按两个指标排序这些人，相邻的建边。这样的建边方式依赖于本题中“强”的传递性（即 A 强于 B 且 B 强于 C 则 A 一定强于 C）。

这样，可以完整的表示所有强弱关系，并且只需 $2n-2$ 条边。

建完图怎么高速查询答案？

还是基于“强”的传递性。如果 B 能打败 A，**那么 A 可以打败的所有人都一定能被 B 打败**。如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/l7wszpth.png)

图中，A 能打败 1、2、3、4，同时 B 也能打败他们，并且 B 还能额外打败 5。

那么我们就能先用 dfs 遍历所有能被 A 打败的人，并开一个全局变量，每遍历一个没去过的人就计数。

同时因为“强”具有传递性，**A 用完的计数变量可以给比他强的 B 接着用**（同时 B 继承 A 记录“访问过”的数组）。我们从弱到强对所有节点跑 dfs，每次跑完后计数变量就是这个节点的答案。

如何做到上文中的“从弱到强对所有节点跑 dfs”？

在前面根据某个指标升序排序数组时，这个顺序就已经是从弱到强了，因为 $i+1$ 必然能打败 $i$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct ff{
    int id , a , b ;
} a[100005] ;
struct Edge{
    int from , to , lip ;
} gra[200005] ;
int n , head[200005] , vis[200005] , dis[200005] , cnt , res ;
void add( int u , int v ){
    gra[++ cnt].lip = head[u] ;
    head[u] = cnt ;
    gra[cnt].from = u ;
    gra[cnt].to = v ;
}
void dfs( int u ){
    if( vis[u] ) return;
    res ++ ;
    vis[u] = true ;
    for( int i = head[u] ; i ; i = gra[i].lip ){
        dfs( gra[i].to ) ;
    }
}
signed main(){
    cin >> n ;
    for( int i = 1 ; i <= n ; i ++ ){
        cin >> a[i].a >> a[i].b ;
        a[i].id = i ;
    }
    sort( a + 1 , a + 1 + n , []
    ( ff a , ff b ){
        return a.a < b.a ;
    }
     ) ;
    for( int i = 2 ; i <= n ; i ++ ){
        add( a[i].id , a[i - 1].id ) ;
    }
    sort( a + 1 , a + 1 + n , []
    ( ff a , ff b ){
        return a.b < b.b ;
    }
     ) ;
    for( int i = 2 ; i <= n ; i ++ ){
        add( a[i].id , a[i - 1].id ) ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        dfs( a[i].id ) ;
        dis[a[i].id] = res - 1 ;
    }
    for( int i = 1 ; i <= n ; i ++ ){
        cout << dis[i] << '\n' ;
    }
    return 0 ;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
好题一道
# 思路
我们发现这道题可以用树状数组来处理，我们可以先按 $s_i.a<s_j.a$ 以及 $s_i.b<s_j.b$ 来排序这样我们对于第 $i$ 个人能战胜的人至少有 $i-1$ 个。然后我们可以统计一个 $s_i.maxb$ 表示 $\max_{j=1}^{i} s_j.b$ 然后我们就可以对于每一个数存一个在原始数组的下表为 $s_i.id$ 然后我们对于这个位置上的答案就等于 $i-1$ 与下表为 $1\sim s_i.maxb$ 中能击败敌人数量的最大值，这里我们可以用树状数组维护最大值然后再对于 $s_i.b$ 去更新最大值。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;--i)
const int N=1e6+100000;
int tr[1001000];
int lowbit(int x) {
	return x&-x;
}
void add(int x,int k) {
	while(x<=1000000+1) {
		tr[x]=max(tr[x],k);
		x+=lowbit(x);
	}
}
int Ans(int z) {
	int res=0;
	while(z) {
		res=max(res,tr[z]);
		z-=lowbit(z);
	}
	return res;
}
struct node{
	int a,b,id,ma;
}s[N];
bool cmp(node a,node b) { //排序 
	if(a.a!=b.a) return a.a<b.a;
	return a.b<b.b;
}
int ans[N];
signed main() {
	int n;
	cin>>n;
	rep(i,1,n) cin>>s[i].a>>s[i].b,s[i].id=i; 
	sort(s+1,s+1+n,cmp);
	rep(i,1,n) s[i].ma=max(s[i-1].ma,s[i].b);
	rep1(i,n,1) {
		ans[s[i].id]=max(i-1,Ans(s[i].ma-1)); //取最大值 
		add(s[i].b,ans[s[i].id]); //用ans[s[i].id]去更新s[i].b下面的 
	}
	rep(i,1,n) cout<<ans[i]<<endl;
	return false;
}

```

---

## 作者：Furthe77oad (赞：1)

# CodeCoder vs TopForces Solution

## 写在最前

[题目链接](https://www.luogu.com.cn/problem/P7033)

该题打眼一看，似乎是个排序题，但是交完错了第 $3$ 个点，才发现，这题有点意思哈。

~~本蒟蒻~~和各位大佬的想法不一样，用树状数组维护的方法过了该题。

题意不重复了，自己看翻译……~~别说我懒~~。

## 分析

首先，我第一次是想通过俩次排序，每次记录该人的位次 $i$，那么显然，他该次可以打败 $i - 1$ 人，然后俩次排序来取最大值。

想法很理想，但是错了第三个点，然后仔细思考了一下关于**强弱的传递问题**，并且发现一组样例可以推翻上述的思路：

```
4
1 2
1 3
2 5
3 1
```

在该样例中，我们发现正确的输出应该是：

```
3
3
3
3
```

显然，第一种思路无法满足我们。

所以，就诞生了第二种思路：

首先排序，然后对于第 $i$ 个人，预处理 $ \max(s[1 \sim i]_y)$ 记录为 $s[i]_{my}$。

接下来倒序遍历插入/查询树状数组，此时树状数组所维护的是区间最大值，查询 $y$ 值在 $1 \sim s[i]_{my} - 1$ 之间的人能战胜的最多人数，用来和 $i-1$ 进行比较取最大值。

其实二者是有相似之处，我们只要认真审题，考虑好**强弱传递问题**即可想到第二种思路。

所以总结一下，这题还是很有趣的。

## 参考代码

```C++
#include <bits/stdc++.h>
#define pc putchar
#define gc getchar
#define isd isdigit
using namespace std;
const int N = 1e6 + 1000;
struct node {
    int x, y, my, id;
    bool operator < (node b) const {
        if (x != b.x) return x < b.x;
        return y < b.y;
    }
} s[N];
int n, tree[N], ans[N];
int lb(int x) {return x & -x;}
void add (int x, int data) {
    while (x <= N - 500) {
        tree[x] = max(tree[x], data);
        x += lb(x);
    }
    return;
}
int ask(int x) {
    int ans = 0;
    while (x > 0) {
        ans = max(ans, tree[x]);
        x -= lb(x);
    }
    return ans;
}
void rd(int &n) {
    int x = 0; bool f = 1; char chin = gc();
    while (!isd(chin)) {if (chin == '-') f = 0; chin = gc();}
    while (isd(chin)) {x = (x << 1) + (x << 3) + (chin ^ 48); chin = gc();}
    n = f ? x : -x;
    return;
}
void wr(int n) {
    if (n < 0) pc('-'), n = -n;
    if (n > 9) wr(n / 10);
    pc(n % 10 + '0');
    return;
}
signed main() {
    rd(n);
    for (int i = 1; i <= n; i++) {
        rd(s[i].x);
        rd(s[i].y);
        s[i].id = i;
    }
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++) s[i].my = max(s[i].y, s[i - 1].my);
    for (int i = n; i >= 1; i--) {
        ans[s[i].id] = max(i - 1, ask(s[i].my - 1));
        add(s[i].y, ans[s[i].id]);
    }
    for (int i = 1; i <= n; i++) {
        wr(ans[i]);
        pc(10);
    }
    return 0;
}
```

## 写在最后

顺便拿个最优解了 2023.6.12。

![](https://cdn.luogu.com.cn/upload/image_hosting/iobzugvt.png)

---

## 作者：Doubeecat (赞：1)



> C.CodeCoder vs TopForces
> 
> 有 $n$ 个人，每个人有两个能力值 $a_i$ 和 $b_i$。一个人能打败另一个人当且仅当这个人有一项或两项能力值都大于另一个人。也就是说当 A 比 B 强时可能有 B 比 A 强。
> 
> 强的关系具有传递性，也就是说 A 比 B 强， B 比 C 强，那么 A 比 C 强。
> 求出每个人最多可以打败的人的个数。
> 
> $n \leq 10^5,a_i,b_i \leq 10^6$

这个题很有意思，初看你可能感觉这个是个排序题，后面挂了一发才发现这个题没有那么简单。

对于这种关系可传递的题，我们有一个比较直接的想法是可以将其建成一张有向图。比如我们把样例建图完就是下面的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/amgm6akz.png)

那么对于一个点 $i$，可以击败的人数就是 $i$ 的可达点数。

$O(n^2)$ 做法，对于每个点 dfs 一遍，得出每个点的可达点数量。

但是这样显然是过不去的，我们再从题目中观察条件。发现点 $i$ 可达点 $j$ 的要求是 $a_i > a_j$ 或 $b_i > b_j$。

我们就考虑能不能通过某些处理方法先优化掉一个条件。考虑如下的贪心策略：我们对于每个点按照 $a$ 或者 $b$ 排序（两个条件是等价的），然后对于每个 $b_i$ 较大的点，它前面的那些点是显然可达的。所以我们排序后依次 dfs,对于每个访问到的点打一个标记（后面的点肯定可以访问到），每次 dfs 都直接往答案中累加就行了。

Code:

```cpp

struct node {
    int val,pos;
}a[N],b[N];

int n;

bool cmp(node p,node q) {
    return p.val < q.val;
}

vector <int> G[N];

int vis[N],ans,orz[N];

void dfs(int x) {
    if (!vis[x]) ++ans;
    vis[x] = 1;
    for (int i = 0;i < G[x].size();++i) {
        int y = G[x][i];
        if (!vis[y]) dfs(y);
    }
}

signed main() {
	read(n);
    for (int i = 1;i <= n;++i) {
        read(a[i].val,b[i].val);
        a[i].pos = i,b[i].pos = i;
    }
    sort(a+1,a+1+n,cmp),sort(b+1,b+1+n,cmp);
    for (int i = 2;i <= n;++i) {
        G[a[i].pos].push_back(a[i-1].pos),G[b[i].pos].push_back(b[i-1].pos);
    }
    for (int i = 1;i <= n;++i) {
        if (!vis[a[i].pos]) dfs(a[i].pos);
        orz[a[i].pos] = ans - 1;
    }
    for (int i = 1;i <= n;++i) {
        printf("%d\n",orz[i]);
    }
	return 0;
}
```

---

## 作者：qiliu (赞：0)

## P7033题解

先提个醒，一定要注意传递性，已经有两个人栽在这了。（翻翻讨论就找到了。）

如果你是暴力枚举每一对 $i$ 和 $j$ 判断两个人之间的强弱，出问题的就是这个传递性，我给个样例。

```
3
1 5
3 4
2 6

```
正确输出是

```
2
2
2
```


____

### 思路

我们可以把强与弱的关系看成一张有向图（由强指向弱），因为这个传递性，所以第 $i$ 行的答案就是从 $i$ 点能达到的点的个数。

显然要先建图。这张图的边从大的指向小的，所以直接降序排序，然后 $i$ 指向 $i + 1$ 就行。当然，不嫌麻烦的话，也可以搓二分建图（怪，很怪啊）。

然后我们 DFS 搜图就可以了。但是每个点都全部搜一遍的话，$O(n^2)$ 显然会超时，所以我们考虑一个优化。

我们把人的强弱按照升序排列（哪个关键字都行），因为传递性，所以对于 $i$ 能打败的人 $i+1$ 肯定能打败。所以我们在搜完答案之后不用清空，因为这些人 $i+1$ 是一定能打败的，然后用一个 $vis$ 来标记即可。

------

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
using namespace std;
const int N=1e5+100;
struct dot
{
	int c1,c2;
	int name;
}a[N];
int n;
int ans; 
int cnt[N];
bool cmp1(dot x,dot y)
{
	return x.c1<y.c1;
}
bool cmp2(dot x,dot y)
{
	return x.c2<y.c2;
}
vector<int>mp[N];
bool vis[N];
void dfs(int x)
{
	if(vis[x])return;
	vis[x]=1;
	ans++;
	for(int i=0;i<mp[x].size();i++)
	dfs(mp[x][i]);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].c1>>a[i].c2;
		a[i].name=i;
	}
	sort(a+1,a+1+n,cmp1);
	for(int i=2;i<=n;i++)
	{
		mp[a[i].name].push_back(a[i-1].name);
	}
	sort(a+1,a+1+n,cmp2);
	for(int i=2;i<=n;i++)
	{
		mp[a[i].name].push_back(a[i-1].name);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(a[i].name);
		cnt[a[i].name]=ans-1;//这个地方减一是因为上面的dfs中最先调用的会是自己，所以会多一个。
	}
	for(int i=1;i<=n;i++)
	{
		cout<<cnt[i]<<endl;
	}
    //fclose(stdin);
    //fclose(stdout);
	return 0;
}
```

---

## 作者：niuzh (赞：0)

### 思路

首先，根据点之间的关系建立有向图，一个点 $i$ 能连接点 $j$ 就代表 $i$ 能打过 $j$。很明显，强的关系具有传递性，就是 $i$ 打得过 $j$，$j$ 打得过 $k$，那么 $i$ 一定打得过 $k$。所以所有点 $i$ 能到达的点，都比它弱。

然后，就可以深搜了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=1e6+10;
vector<long long> mp[M];
struct node
{
	int a,b,s;
} a[N];
bool cmp_a(node u,node v)//两种排列方法
{
	return u.a<v.a;
}
bool cmp_b(node u,node v)
{
	return u.b<v.b;
}
long long ans[M],cnt;
bitset<M> vis;//使用bitset可优化一堆东西（雾
void dfs(int now)
{
	vis[now]=true;//标记
	cnt++;//计数
	for (auto x:mp[now])//遍历
	{
		if (!vis[x])//如果没遍历过
		{
			dfs(x);
		}
	}
}
int main()
{
	int n;
	cin>>n;
	for (int i=1; i<=n; i++)
	{
		cin>>a[i].a>>a[i].b;
		a[i].s=i;
	}
	sort(a+1,a+n+1,cmp_a);
	for (int i=2; i<=n; i++)
	{
		mp[a[i].s].push_back(a[i-1].s);
	}
	sort(a+1,a+n+1,cmp_b);
	for (int i=2; i<=n; i++)
	{
		mp[a[i].s].push_back(a[i-1].s);
	}
	for (int i=1; i<=n; i++)
	{
		if (!vis[a[i].s])//如果没遍历过
		{
			dfs(a[i].s);
		}
		ans[a[i].s]=cnt-1;//减去自己
	}
	for (int i=1; i<=n; i++)
	{
		cout<<ans[i]<<'\n';
	}
	return 0;
}
```

代码重点看这里：

```cpp
for (int i=1; i<=n; i++)
{
	if (!vis[a[i].s])
	{
		dfs(a[i].s);
	}
	ans[a[i].s]=cnt-1;
}
```

这里不用重新遍历的原因是：运行到这时，$a$ 数组已处在用 $TF$ 从小到大排完的情况，而此时又被遍历过就代表有一个点 $j$，由于题目中保证了 $CC$ 与 $TF$ 两两互不相同，所以 $CC_i<CC_j$ 并 $TF_i>TF_j$，这代表两点都比对方强，$ans$ 也自然相等。如果被遍历过了，那当前点一定是在各方面碾压遍历过的点的，由于强的关系具有传递性，所以可以不将 $vis$ 和 $cnt$ 清零。

---

## 作者：FLORIZ (赞：0)

强具有传导性，A 如果强于 B，那么 A 可以直接继承所有 B 强于的人。这就能把大问题拆成一个个已经处理好的子问题。

考虑建一张有向图，存一下当前已知的强弱关系。一个人最多能战胜的人数就是这个点开始 dfs 能到达的点的数量。

分别按两个能力值排序，显然可以在相邻的两个点直接连边。

发现这样不好从点直接继承。通过对于每个点进行 dfs，复杂度 $O(n^2)$。

可以考虑从由弱到强地从每个点进行 dfs，每个新点都能战胜所有已经遍历过的老点，它的 dfs 都要继承当前所有已经遍历过的点数。所以只需要统计能遍历到的原本没有到过的点就行。只需要一遍完整的 dfs 即可，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
	{int f(1),x(0);
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	return f*x;
	}
#define debug(x) cout<<"###"<<x<<endl;

#define maxn 100010
int n;
struct reni
	{int cc,tf,hao;
	} ren[maxn];
bool cmpc(reni x,reni y)
	{return x.cc>y.cc;
	}
bool cmpt(reni x,reni y)	
	{return x.tf>y.tf;
	}

int head[maxn],tot;
struct bian
	{int to,nx;
	} bian[maxn<<1];
inline void add(int from,int to)
	{bian[++tot].to=to;
	bian[tot].nx=head[from];
	head[from]=tot;
	}

int sum,vis[maxn],ans[maxn];
void dfs(int x)
	{sum++;
	vis[x]=1;
	for(int i=head[x];i;i=bian[i].nx)
		{int y=bian[i].to;
		if(vis[y]) continue;
		dfs(y);
		}
	}

int main()
	{n=read();
	for(int i=1;i<=n;i++)
		{ren[i].hao=i;
		ren[i].cc=read();
		ren[i].tf=read(); 
		}
	
	sort(ren+1,ren+1+n,cmpc);
	for(int i=1;i<n;i++)
		{add(ren[i].hao,ren[i+1].hao);
		}
	sort(ren+1,ren+1+n,cmpt);
	for(int i=1;i<n;i++)
		{add(ren[i].hao,ren[i+1].hao);
		}
	
	for(int i=n;i>=1;i--)
		{if(!vis[ren[i].hao])
			{dfs(ren[i].hao);
			}
		ans[ren[i].hao]=sum-1;
		}
	
	for(int i=1;i<=n;i++)
		{cout<<ans[i]<<endl;
		}
	return 0;
	}
```


---

## 作者：harmis_yz (赞：0)

## 分析

很简单，我们用有向图来进行求解。根据两种不同的能力值对这 $n$ 个人排序，根据传递性，我们只需要先将相邻两个人进行连边，再利用前缀和得到答案。注意，求答案的时候需要从按照某一种能力值排序之后的最弱的人到最强的人求解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n;
struct node{
	int a,b,id;
}a[N];
map<int,map<int,bool> > mp;
int ne[N],e[N],h[N],idx;
void add(int a,int b){
	ne[idx]=h[a],e[idx]=b,h[a]=idx++;
}
bool cmp1(node a,node b){
	return a.a<b.a;
}
bool cmp2(node a,node b){
	return a.b<b.b;
}
int ans;
int s[N],vis[N];
int dfs(int now){
	if(!vis[now]) ans++;
	vis[now]=1;
	for(int i=h[now];~i;i=ne[i]){
		int j=e[i];
		if(!vis[j]){
			dfs(j);
		}
	}
}
signed main(){
	memset(h,-1,sizeof(h));
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=n;i>1;i--){
		add(a[i].id,a[i-1].id);
		mp[a[i].id][a[i-1].id]=1;
	}
	sort(a+1,a+n+1,cmp2);
	for(int i=n;i>1;i--){
		if(!mp[a[i].id][a[i-1].id]){
			add(a[i].id,a[i-1].id);
		}
	}
	for(int i=1;i<=n;i++){
		ans=0;
		if(!vis[a[i].id]) dfs(a[i].id);
		s[a[i].id]=s[a[i-1].id]+ans;
	}
	for(int i=1;i<=n;i++){
		cout<<s[i]-1<<"\n";//因为把自己算进去了，所以要-1 
	}
	return 0;
}
```


---

## 作者：Elma_ (赞：0)

对于两个能力值分别排序，每个人和上一个比自己弱的人连边。

两次连边后形成了一个图，并且缩点后是一个DAG,求出拓扑序之后前面所有点都是可达的。

并不会证明，所以我场上其实也是乱搞过题。

```cpp
#include <map>
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct node {
	int cc, tf, pos;
}a[maxn];
vector<int> f[maxn];
int vis[maxn], ans[maxn], sum, n;

inline bool cmp1(node x, node y) {
	return x.cc < y.cc;
}
inline bool cmp2(node x, node y) {
	return x.tf < y.tf;
}
inline void dfs(int x) {
	if (vis[x]) return;
	++sum, vis[x] = 1;
	for (int i = 0;i < f[x].size();i++)
		dfs(f[x][i]);
}

int main(void) {
	n = read();
	for (int i = 1;i <= n;i++) a[i].cc = read(), a[i].tf = read(), a[i].pos = i;
	sort(a + 1, a + n + 1, cmp1);
	for (int i = 2;i <= n;i++) f[a[i].pos].push_back(a[i - 1].pos);
	sort(a + 1, a + n + 1, cmp2);
	for (int i = 2;i <= n;i++) f[a[i].pos].push_back(a[i - 1].pos);
	for (int i = 1;i <= n;i++) dfs(a[i].pos), ans[a[i].pos] = sum - 1;
	for (int i = 1;i <= n;i++) printf("%d\n", ans[i]);
	return 0;
}
```


---

