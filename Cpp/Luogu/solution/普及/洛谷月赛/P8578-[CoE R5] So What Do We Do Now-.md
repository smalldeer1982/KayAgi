# [CoE R5] So What Do We Do Now?

## 题目背景

![396ac9d3c58dbf329d6ead206944a5a495930006.jpg](https://img-kysic-1258722770.file.myqcloud.com/f2a3112865eea75d3c27aae713e1a8a8/ae2c3e0c34910.jpg)

>$\texttt{I'm getting tired of hiding.}$

声明：上述图片取自网络，`pid:6544352`，如有侵权，告知即删。

## 题目描述

给定一棵 $n$ 个结点的有根树，根结点编号为 $1$。设以 $i$ 为根的子树为 $T_i$。你需要给每个结点赋一个正整数点权 $v_i$，使得所有点的点权恰为 $1,2,\dots,n$ 各一个。记
$$f=\sum_{i=1}^{n}R_i,$$
其中 $R_i$ 是以 $i$ 为根的子树中点权的极差，即
$$R_i=\max_{j \in T_i}\{v_j\}-\min_{j \in T_i}\{v_j\}.$$
对于所有的赋点权的方式，请求出一组使 $f$ 取到最小值的点权。


## 说明/提示

**样例说明**

输入 $\#1$

![graph.png](https://img-kysic-1258722770.file.myqcloud.com/4a372f1ae46e27a31fae60c4db5e439e/af9581fa182de.png)

$R_1=3-1=2,R_2=2-2=0,R_3=3-3=0,f=R_1+R_2+R_3=2$，可以证明，不存在使得 $f$ 更小的构造。


------------

**数据范围**

对于 $10\%$ 的数据，$n \le 10$；

对于另外 $10\%$ 的数据，树是一条链；

对于另外 $20\%$ 的数据，有一个结点与其他 $n-1$ 个结点都相连；

对于另外 $20\%$ 的数据，树是一棵完全二叉树，即除了叶子结点外每个结点都恰有两个子结点；

对于 $100\%$ 的数据，$1 \le n \le 10^6$。

## 样例 #1

### 输入

```
3
1 2
1 3```

### 输出

```
1 2 3```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
1 2```

## 样例 #3

### 输入

```
5
1 2
2 3
3 4
4 5```

### 输出

```
1 2 3 4 5```

# 题解

## 作者：Da_un (赞：5)

# Solution
求 $f=\sum\limits_{i=1}^n R_i$ 中的 $f_{min}$，只需让每个 $R_i$ 尽可能地小就行了，即让每个以 $i$ 为根的子树中点权的极差最小，这需要在某种遍历时给点附上权值来实现。

这种遍历的应该尽可能的让父亲与儿子的权值相邻，不断遍历，不断赋值，由局部最优推到全局最优，讲到这里，大家应该也都明白了其实这就是深搜遍历，也叫作 dfs 序。

dfs 序是指每个节点在 dfs 深度优先遍历中的进出栈的时间序列，我们把树建完跑一遍 dfs 序，dfs 进入子树 $i$ 的时间就是每个点应附的权值。因为根节点未给出，我们可以任选一个作为根节点，最后输出进入的时间戳即为答案。

# Code
```cpp
#include<iostream>
#include<cstdio> 
#include<vector>
#include<algorithm>
using namespace std;
const int N=1000100;
int n;
int in[N],out[N];
int u,v;
int Times;
vector<int> f[N];
void dfs(int now,int fa)
{
	in[now]=++Times;//dfs进入now的时间
	for(int i=0;i<f[now].size();i++)
		if(f[now][i]!=fa) dfs(f[now][i],now);
	//out[now]=Times;//dfs离开子树now的时间，这题用不到
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		f[u].push_back(v);
		f[v].push_back(u);
	}
	dfs(1,0);//选1为根节点
	for(int i=1;i<=n;i++)	
		printf("%d ",in[i]);
	return 0;
}
```


---

## 作者：f_x_f (赞：4)

[洛谷题面](https://www.luogu.com.cn/problem/P8578)

这是一道不错的构造体。

我们一下图为例子

![](https://cdn.luogu.com.cn/upload/image_hosting/7ilmik2m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在以 $i$ 为根的子树中，$size_i \leq \min {R_{i}}$ 其中 $size_i$ 表示以 $i$ 为根的子树之中有多少个节点，所以我们就构造最小值，也就是 dfs 一边，对于每个搜索到的值都将其赋值为踏上一个遍历到的节点的编号 +1 。

用这种方法构造出来的方案为其中的方案之一。

代码如下。

```cpp
#include<bits/stdc++.h>
namespace vec{
	#define vei vector<int>
	#define vel vector<ll>
	#define si size()
	#define em empty()
	#define pd(i) push_back(i)
	#define pb pop_back()
}
namespace my_std{
	using namespace std;
	#define ll long long
	#define ref(i,x,y) for(register int i=(x);i<=(y);i++)
	#define fer(i,x,y) for(register int i=(x);i>=(y);i--)
	#define il inline
	#define mpii map<int,int>
	#define mpib map<int,bool>
	#define mpplll map<pll,ll>
	#define mppccl map<pcc,ll>
	#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
	char buf[1<<21],*p1=buf,*p2=buf;
	inline ll read(){
	    char c=getchar();
	    ll x=0;
	    for(;!isdigit(c);c=getchar());
	    for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	    return x;
	}
}

using namespace my_std;
using namespace vec;
const ll maxn=1e6+10;
ll n;
ll ans[maxn];
ll sum[maxn];
struct node{
	int sum,id;
}a[maxn];
vel g[maxn];
ll cnt;
inline void dfs(int u,int fa){
	a[u].sum=1,ans[u]=++cnt;;
	for(int i=0;i<g[u].si;i++){
		if(g[u][i]==fa){
			continue;
		}
		dfs(g[u][i],u);
		a[u].sum+=a[g[u][i]].sum;
	}
	return ;
}
inline bool cmd(node x,node y){
	return x.sum<y.sum;
}
ll u,v;
int main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i].id=i;
	}
	for(int i=1;i<=n-1;i++){
		cin>>u>>v;
		g[u].pd(v),g[v].pd(u);
	}
	dfs(1,0);
	// sort(a+1,a+n+1,cmd);
	// for(int i=1;i<=n;i++){
		// ans[a[i].id]=n-i+1;
	// }
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
}
```

---

## 作者：gyyyyx (赞：1)

简单题

假设有一棵子树所有点权从小到大排列是 $a_1\sim a_{siz}$。

那很明显这棵子树的 $R=a_{siz}-a_1$，那么如果 $R$ 要最小肯定要使得 $a_1\sim a_{siz}$ 是连续的正整数，这样的话 $R_i=siz_i-1$。

那有没有一种排列方式使得所有的子树上的点权是连续的呢？

想到了 $\text{dfs}$ 序。

因此直接输出树的 $\text{dfs}$ 序即可。

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,u,v,head[N],nxt[N<<1],to[N<<1],cnt,id[N],tot;
inline void add(int x,int y){
    to[++cnt]=y;
    nxt[cnt]=head[x];
    head[x]=cnt;
}
void dfs(int k,int f){
    id[k]=++tot;
    for(int i(head[k]);i;i=nxt[i]){
        int s(to[i]);
        if(!(s^f)) continue;
        dfs(s,k);
    }
}
int main(){
    scanf("%d",&n);
    for(int i(1);i<n;++i){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    for(int i(1);i<=n;++i) printf("%d ",id[i]);
    return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

# P8578 Solution

显然，一个 $R_i$ 数值最小就是其子树大小减去一，这要求子树内的数值是**连续的**，而每一个 $R_i$ 都可以取到最小值，而每一个 $R_i$ 都取到最小值，$f$ 不就最小了吗？dfs 序就是构造的答案。

第 $i$ 个点的 dfs 序就是对树进行深度优先遍历时第几个被访问的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=1000005;
vector<int>g[maxn];
int d[maxn],a[maxn],fa[maxn],pre[maxn],vis[maxn],dfn[maxn],tot;
void dfs(int u,int fa){
	dfn[u]=++tot;
	for(auto i:g[u])
		if(i!=fa) dfs(i,u);
}
signed main(){
	int n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) printf("%lld ",dfn[i]);
}
```


---

## 作者：xwh_Marvelous (赞：0)

这题看似复杂，实际上意思却很简单。就是让你构造一个赋点权的方案，使得每个子树所以点权的极差最小。

哪么什么时候最小呢？

我们可以看出以下性质。

1. 对于每个子树，无论怎么赋值，最小值都是子树的点数减一。

1. 子树内的所有点权如果极差最小，那么所以点权构成一个连续的数列，例如 $1\ 2\ 3\ 4\ 5$ 或 $4\ 5\ 6\ 7\ 8$，而且只要是连续的数列就能满足极差最小。

对于性质一而言，因为如果满足了题目要求，我们就不能让某两个点点权相同，所以最好的方案就是性质二所说的赋权方案。我们可以按节点是分段，递归为每个点赋值。整理后可以发现其实就是按 DFS 序赋值。

**AC code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int tot,n,f[1000005];
int head[1000005],xx[2000005],nt[2000005];
void link(int a,int b){
	nt[++tot]=head[a];
	xx[tot]=b;
	head[a]=tot;
}
void dfs(int x,int ff){
	f[x]=++tot;
	for(int i=head[x];i;i=nt[i]){
		if(xx[i]==ff)continue;
		dfs(xx[i],x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		link(a,b);
		link(b,a);
	}
	tot=0;
	dfs(1,0);
	for(int i=1;i<=n;i++)printf("%d ",f[i]);
	return 0;
}
```


---

## 作者：Dregen_Yor (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P8578)。


### [更好的阅读体验](http://dregen-yor.123ds.tk/index.php/2022/10/17/p8578/)。

# 思路

本题要求所有子树中点权的极差的和的最小的构造情况，我们来考虑一下在什么情况下一颗子树内的极差才能最小。

因为每个点权只能出现一次，若想要点权极差最小的话，我们应让子树内的所有点的点权为**连续**的，即 $1,2,3,4,5\dots$ 这种，根据 **dfs 序**的性质，我们知道一棵树的 dfs 序在每个子树内都是连续的，也就是说，对于本题，我们只需要输出数的 dfs 序即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans[1000010],cnt;
vector <int> G[1000010];
void dfs(int x,int fa){
    ans[x]=++cnt;
    for(auto to: G[x]){
        if(to==fa){
            continue;
        }
        dfs(to,x);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,1);
    for(int i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }
    return 0;
}
```


---

## 作者：Erotate (赞：0)

这题实际就是让我们去求每个子树的极差最小，让我们找出一种赋值方式。

### Solution

我们发现，无论怎么怎样赋值，一棵子树的极差最小是他的 $size-1$。那么整一棵数的极差和的最小值，就是它所有的子树的 $size-1$ 的和。

然后我们想想，如何构造。那么，我们只需要使得每一棵子树上的点的权值连续即可。自然而然，我们就能想到 dfs 序。于是，我们只需要求出每一个节点的 dfs 序，再按顺序输出即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct edge{
	int v,nxt;
}e[N<<1];
int n,head[N],cnt,a[N],dfn;
void dfs(int u,int fa){
	a[u]=++dfn;
	for(int i=head[u];i;i=e[i].nxt)
		if(fa!=e[i].v) dfs(e[i].v,u);
}
void add(int x,int y){
	e[++cnt]=((edge){y,head[x]});
	head[x]=cnt;
}
signed main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;++i){
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,-1);
	for(int i=1;i<=n;++i) printf("%d ",a[i]);
	return 0;
}
```


---

