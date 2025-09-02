# Strategic game

## 题目描述

### 题目翻译

给定一棵 $n$ 个节点的树。你需要让这棵树上的每条边都被看守。当一条边的端点上至少有一个士兵时，我们就说这条边被看守。求出看守这棵树最少用的士兵数量。

## 样例 #1

### 输入

```
4
0:(1) 1
1:(2) 2 3
2:(0)
3:(0)
5
3:(3) 1 4 2
1:(1) 0
2:(0)
0:(0)
4:(0)
```

### 输出

```
1
2
```

# 题解

## 作者：我没有小白 (赞：33)

>今天学习了树形$dp$，一开始浏览各大$blog$，发现都$TM$是题，连个入门的$blog$都没有，体验极差。所以我立志要写一篇可以让初学树形$dp$的童鞋快速入门。

# 树形$dp$

## 概念类

树形$dp$是一种很优美的动态规划，真的很优美真的，前提是在你学会它之后。

## 实现形式

树形$dp$的主要实现形式是$dfs$，在$dfs$中$dp$，主要的实现形式是$dp[i][j][0/1]$，$i$是以$i$为根的子树，$j$是表示在以$i$为根的子树中选择$j$个子节点，$0$表示这个节点不选，$1$表示选择这个节点。有的时候$j$或$0/1$这一维可以压掉

## 基本的$dp$方程
### 选择节点类
$$\begin{cases}dp[i][0]=dp[j][1]\\dp[i][1]=\max/\min(dp[j][0],dp[j][1])\\\end{cases}$$

### 树形背包类
$$\begin{cases}dp[v][k]=dp[u][k]+val\\dp[u][k]=max(dp[u][k],dp[v][k-1])\\\end{cases}$$
## 例题类

以上就是对树形$dp$的基本介绍，因为树形$dp$没有基本的形式，然后其也没有固定的做法，一般一种题目有一种做法。

### [没有上司的舞会](https://www.luogu.org/problemnew/show/P1352)

这道题是一树形$dp$入门级别的题目，具体方程就用到了上述的选择方程。
```cpp
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define N 6001
using namespace std;
int ind[N],n,hap[N],dp[N][2],fa[N],root,vis[N],ne[N],po[N];
void work(int x)
{
    for(int i = po[x]; i; i = ne[i])
    {
        work(i);
        dp[x][1]=max(max(dp[x][1],dp[x][1]+dp[i][0]),dp[i][0]);
        dp[x][0]=max(max(dp[x][0],dp[i][1]+dp[x][0]),max(dp[i][1],dp [i][0]));
    }
}
int main()
{
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> dp[i][1];
    for(int i=1; i<=n; i++)
    {
        int a,b;
        cin >> b >> a;
        ind[b]++;
        ne[b] = po[a];
        po[a] = b;
    }
    for(int i=1; i<=n; i++)
        if(!ind[i])
        {
            root=i;
            break;
        }
    work(root);
    cout << max(dp[root][0],dp[root][1]);
}
```
### [最大子树和](https://www.luogu.org/problemnew/show/P1122)

这道题的$dp$方程有变，因为你的操作是切掉这个点，所以你的子树要么加上价值，要么价值为$0$，所以$dp$方程是
$$dp[u]+=max(dp[v],0)$$
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;
struct edge
{
    int next,to;
} e[40000];
int head[40000],tot,rt,maxn;
void add(int x,int y)
{
    e[++tot].next=head[x];
    head[x]=tot;
    e[tot].to=y;
}
int n,dp[20000],ind[20000];
int val[20000],f[20000];
void dfs_f__k(int x,int fa)
{
    f[x]=fa;
    for(int i=head[x]; i; i=e[i].next)
    {
        int v=e[i].to;
        if(v!=fa)
            dfs_f__k(v,x);
    }
}
void dfs(int x)
{
    dp[x]=val[x];
    for(int i=head[x]; i; i=e[i].next)
    {
        int v=e[i].to;
        if(v!=f[x])
        {
            dfs(v);
            dp[x]+=max(0,dp[v]);
        }
    }
    maxn=max(maxn,dp[x]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1; i<=n; i++)scanf("%d",&val[i]);
    for(int i=1; i<=n-1; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    rt=1;
    dfs_f__k(rt,0);
    dfs(rt);
    printf("%d",maxn);
}
```
### [选课](https://www.luogu.org/problemnew/show/P2014)
这道题的意思是每本书要想选择一门课，必须要先学会它的必修课，所以这就形成了一种依赖行为，即选择一门课必须要选择必修课。那么他又说要选择的价值最大，这就要用到树形背包的知识了。
树形背包的基本代码形式（即上面的树形背包类）
```cpp
/*
设dp[i][j]表示选择以i为根的子树中j个节点。
u代表当前根节点，tot代表其选择的节点的总额。
*/
void dfs(int u,int tot)
{
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].to;
		for(int k=0;k<tot;k++)//这里k从o开始到tot-1，因为v的子树可以选择的节点是u的子树的节点数减一
			dp[v][k]=dp[u][k]+val[u];
		dfs(v,tot-1)
		for(int k=1;k<=tot;k++)
			dp[u][k]=max(dp[u][k],dp[v][k-1]);//这里是把子树的值赋给了根节点，因为u选择k个点v只能选择k-1个点。
	}
}
```
然后这就是树形背包的基本形式，基本就是这样做
代码
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

int n,m;
struct edge
{
    int next,to;
}e[1000];
int rt,head[1000],tot,val[1000],dp[1000][1000];
void add(int x,int y)
{
    e[++tot].next=head[x];
    head[x]=tot;
    e[tot].to=y;
}
void dfs(int u,int t)
{
    if (t<=0) return ;
    for (int i=head[u]; i; i=e[i].next)
    {
        int v = e[i].to;
        for (int k=0; k<t; ++k) 
            dp[v][k] = dp[u][k]+val[v];
        dfs(v,t-1);
        for (int k=1; k<=t; ++k) 
            dp[u][k] = max(dp[u][k],dp[v][k-1]);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int a;
        scanf("%d%d",&a,&val[i]);
        if(a)
          add(a,i);
        if(!a)add(0,i);
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
}
```
### [Strategic game](https://www.luogu.org/problemnew/show/UVA1292)

这道题的意思是选择最少的点来覆盖一棵树，可以用最小点覆盖（也就是二分图最大匹配）或者树形$dp$来做，因为这里我们的专题是树形$dp$，所以我们现在就讲树形$dp$的做法。
我们做这道题的方法是用选择方程来做，因为你要做最小点覆盖，要么选这个点要么不选对吧。
于是$dp$的转移方程就是上述一方程
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int n;
struct edge
{
    int next,to;
} e[4000];
int head[4000],tot,dp[4000][2],ind[4000];
void add(int x,int y)
{
    e[++tot].next=head[x];
    head[x]=tot;
    e[tot].to=y;
}
void dfs(int x)
{
    dp[x][1]=1;
    for(int i=head[x]; i; i=e[i].next)
    {
        int v=e[i].to;
        dfs(v);
        dp[x][0]+=dp[v][1];
        dp[x][1]+=min(dp[v][0],dp[v][1]);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        memset(head,0,sizeof(head));
        memset(ind,0,sizeof(ind));
        tot=0;
        for(int j=1; j<=n; j++)
        {
            int a,b;
            scanf("%d:(%d)",&a,&b);
            for(int i=1; i<=b; i++)
            {
                int c;
                scanf("%d",&c);
                ind[c]++;
                add(a,c);
            }
        }
        int rt;
        for(int i=0; i<=n; i++)
            if(!ind[i])
            {
                rt=i;
                break;
            }
        dfs(rt);
        printf("%d\n",min(dp[rt][1],dp[rt][0]));
    }
}
```

---

## 作者：Froranzen (赞：9)

### [题目传送门~](https://www.luogu.com.cn/problem/UVA1292)

------------
# 思路

------------
本题可以考虑**树形dp**（当然也可以用二分图匹配）。

维护一个二维数组 $dp[u][1/0]$  表示 u 点选(1)还是不选(0)所需的最小代价

设 v 是 u 的子节点，接下来看下面这句话：
#### 士兵只能放在节点上 ，但是却可以保卫所有与这个节点相邻的边 

那么可以得出：

1. 如果选择了当前节点，那么它的子节点一定会被当前节点覆盖，所以转移方程为：

$$ dp[u] += min (dp[v][0], dp[v][1]); $$

2. 如果不选择当前节点，那么就必须选择它的所有子节点来覆盖当前节点，所以转移方程为：

$$ dp[u] += dp[v][1];$$

这道题还有一个坑点，就是根节点不一定是 0 。可以通过记录入度，并判断入度是否为 0 来寻找根节点。

# 代码

------------

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
using  namespace std;

int n;

struct node {
	int to;
	int next;
}e[666666];

int _head[666666], cnt;

void add (int u, int v) {
	e[++cnt].to = v;
	e[cnt].next = _head[u];
	_head[u] = cnt;
}

int qwq[666666][2];

inline int minn (int a, int b) {
	return a < b ? a : b;
}

void dfs (int u, int fa) {
	qwq[u][1] = 1;
	for (register int i(_head[u]); i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs (v, u);
		qwq[u][1] += minn (qwq[v][0], qwq[v][1]);
		qwq[u][0] += qwq[v][1];
	}
}

int _in[6666];
int root;

int main () {
	 while (scanf ("%d",&n) != EOF) {
		memset (qwq, 0, sizeof (qwq));
		memset (e, 0, sizeof (e));
        memset (_head, 0, sizeof (_head));
        memset (_in, 0, sizeof (_in));
		for (register int i(1); i <= n; ++i) {
			int u, k;
            scanf ("%d:(%d)", &u, &k);
            u ++;
			for (register int j(1); j <= k; ++j) {
                int v;
				scanf ("%d", &v);
                v ++;
                _in[v]++;
				add (u, v);
				add (v, u);
			}
		}
		for (register int i(1); i <= n; ++i) {
			if (!_in[i]) {
				root = i;
				break;
			}
		}
		dfs (root, 0);
		printf ("%d\n", minn (qwq[root][0], qwq[root][1]));
	}
	return 0;
}
```


---

## 作者：唔啊唔 (赞：5)

此题为一道树形DP，作为树形DP的初学者，我认为这是一道较为典型的树状动规题，这道题还是双倍经验oh！

关于思想，请见我博客中的另一篇题解[P2016](https://www.luogu.org/blog/99247/solution-p2016)

那么我还是附上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[5000][5000],father[5000];
vector<int> s[5000];
inline void dfs(int x){
	f[x][0]=0;
	f[x][1]=1;
	if(s[x].size()==0)return;
	for(register int i=0;i<s[x].size();i++){
		int y=s[x][i];
		dfs(y);
		f[x][0]+=f[y][1];
		f[x][1]+=min(f[y][1],f[y][0]);
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){		//记得及时结束,否则会TLE 
		memset(f,0,sizeof(f));		//数组初始化不要忘记 
		memset(father,0,sizeof(father));
		memset(s,0,sizeof(s));
		int a,b,z;
		for(register int i=1;i<=n;i++){
			scanf("%d:(%d)",&a,&b);		//重点注意这个输入,卡了我半个小时 
			a++;
			for(register int j=1;j<=b;j++){
				scanf("%d",&z);
				z++;
				s[a].push_back(z);
				father[z]=1;
			}
		}
		int root;
		for(register int i=1;i<=n;i++){
			if(father[i]==0){
				root=i;
				break;
			}
		}
		dfs(root);
		cout<<min(f[root][0],f[root][1])<<endl;
	}
	return 0;
}
```


---

## 作者：李小浪 (赞：4)

对于一棵树,每一个节点都有选或不选两种选择.
用$f[i][0/1]$表示节点$i$选或不选.

对于一个叶子结点,$f[i][1]=1,f[i][0]=0$.

对于一个非叶子节点,答案可以由子节点转移过来.

$$f[i][1]=\sum _{j\in son\ of\ i}min(f[j][1],f[j][0]).$$

如果不选$i$,那么它的儿子们一定全部选上了.
$$f[i][0]=\sum _{j\in son\ of\ i}f[j][1].$$

```cpp
//... ...
#include<cstdio>
#include<cstring>
#include<iostream>
#define X 1507
using namespace std;
int f[X][2],head[X];
bool aper[X];
int n,num_edge;
struct Edge {
	int pre,to;
} edge[X];

void add(int from,int to) {
	edge[++num_edge].pre=head[from];
	edge[num_edge].to=to;
	head[from]=num_edge;
}
void dfs(int now) {
	if(!head[now]) {
		f[now][1]=1,f[now][0]=0;
		return;
	}
	for(int i=head[now]; i; i=edge[i].pre)
		dfs(edge[i].to);
	f[now][1]=1,f[now][0]=0;
	for(int i=head[now]; i; i=edge[i].pre) {
		f[now][1]+=min(f[edge[i].to][1],f[edge[i].to][0]);
		f[now][0]+=f[edge[i].to][1];
	}
}
int main() {
	int u,v,num,rt,ans;
	while(scanf("%d",&n)!=EOF) {
		num_edge=0;
		memset(head,0,sizeof(head));
		memset(aper,0,sizeof(aper));
		for(int i=1; i<=n; ++i) {
			scanf("%d:(%d)",&u,&num);
			for(int j=1; j<=num; ++j) {
				scanf("%d",&v);
				add(u+1,v+1);
				aper[v+1]=1;
			}
		}

		for(int i=1; i<=n; ++i)
			if(!aper[i]) {
				rt=i;
				break;
			}
		dfs(rt);

		ans=min(f[rt][1],f[rt][0]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：2)

## 前言

本题需要的知识点：

- 树形dp

- ~~没了~~

### $\text{Part1 } \bold{\text{树形dp}}$

需要的知识点：

- 邻接表

- dfs

- dp

- ~~没了~~

以上三点如果您不会，建议先了解一下，否则阅读本题解可能会有困难。

树形 dp 思想其实是利用树的结构，完成 dp 的过程。具体做法是，首先将一个问题的子问题和父问题进行连边，构建一棵树。然后每次通过 dfs 的性质首先求出子问题的解，再求出父问题的解。这个和“递推”类似。

放个图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nsz1ezrj.png)

首先我们要求根节点。我们利用 dfs 把根节点的子节点都算一遍。首先，路径从 1 到 2，然后从 2 找到 5 和 6 这两个最小的子问题。找完节点 5 和 6，回溯计算出节点 2，然后处理节点 3 和节点 4。最后，我们发现 2~6 五个子问题都解决了，然后通过一定的计算求出根节点 1 的值。

由于本人学识有限，树形dp只能做出这样的解释了。不懂得同学们可以去 [OI-Wiki](http://OIwiki.com) 上查询相关资料。

### $\text{Part2 } \bold{\text{本题思路 \& 解法}}$

首先考虑每一个节点如何看守。

第一种情况是当前节点不放士兵，第二个是当前节点放士兵。如果不放士兵，那么它的所有儿子必须都有士兵看守；如果放，那么他的儿子就 free ~~免费~~了。

我们用 $dp_{i,1/0}$ 表示第 $i$ 个节点放/不放士兵时**其子树**所需最少的士兵。

由此得到：

$dp_{i,0} = \sum^{s}_{j=0}dp_{j,1}$ 

$dp_{i,1} = \sum^{s}_{j=0} \max(dp_{j,0},dp_{j,1})$

其中 $s$ 表示 $i$ 的儿子总数。

然后每次进行 dfs，进行转移即可，最后输出 $\min(dp_{r,0/1})$。

### $\text{Part3 } \bold{\text{代码}}$

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;
bool hfa[1505];
vector<int> son[1505];
int dp[1505][3];

void dfs(int cur)
{
	dp[cur][0]=0; dp[cur][1]=1;
	for(int i=0;i<son[cur].size();i++)
	{
		int v=son[cur][i]; dfs(v); //先计算儿子
		dp[cur][0]+=dp[v][1]; //转移
		dp[cur][1]+=min(dp[v][0],dp[v][1]);
	}
}
int main()
{
	int n;
	while(~scanf("%d",&n)) // 多组数据
	{
		for(int i=0;i<=n;i++)
			dp[i][0]=dp[i][1]=0,hfa[i]=0,son[i].clear(); //记得清空！另外，使用 for 清零在多测中比 memset() 保险。
		int root,tmp,x;
		for(int i=1;i<=n;i++)
		{
			scanf("%d:(%d)",&x,&tmp);
			for(int i=1;i<=tmp;i++)
			{
				int y; scanf(" %d",&y);
				son[x].push_back(y); //建树
				hfa[y]=1;
			}
		}
		
		for(int i=0;i<n;i++)
			if(!hfa[i]) root=i; //注意！0不一定是根节点
		dfs(root); //计算
		printf("%d\n",min(dp[root][1],dp[root][0]));
	}
	return 0;
}
```

$$\large\text{-------- The End --------}$$

$$\text{thx for readin'}$$

---

## 作者：zhenghwen (赞：2)

**树形dp**
------------
当我看到这道题的题面的时候，发现他是一个树形结构，刚好又要在节点上面放置士兵，瞬间就觉得八九不离十就是树形dp了。

这道题要求我们放置士兵，士兵可以监视相邻的节点，这里我们就把它当做子节点，（其实也无所谓），使得士兵可以监视整个树。了解题目要干嘛了以后，我们就开始推方程。

这里设一个二维数组f，第一维表示当前节点x，第二维表示x节点是否放置士兵，**f[x][]表示根节点为x的子树放置士兵个数**。由题意“监视相邻的节点”，得：**当前节点x，子节点y，要么x监视y，要么y监视x，要么x、y相互监视**。那么可以根据这一点，分类讨论：
1. y监视x，即为x节点没士兵，y节点有士兵，此时f[x]就是其子节点的士兵和（**条件：子节点放置士兵**）
1. x节点有士兵，此时，**对于y节点是否放置士兵没有要求**，那么f[x]就是子节点的士兵和的最小值再加上**自身的1**


------------
由以上讨论，整理，得出转移方程：
```cpp
f[x][0] += f[y][1];
f[x][1] += min(f[y][0], f[y][1]);
```
其余的嘛，就是注意多组数据，别忘了**初始化**什么的了。

下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e3 + 50;

int n;
int f[N][2];//f[x][0]x节点不方 f[x][1]x节点放
vector <int> e[N];//vector存边

void dfs(int x) {
	f[x][1] = 1;//x节点放置士兵，自身加1
	for(int i = 0; i < e[x].size(); i ++) {
		int y = e[x][i];//子节点
		dfs(y);
		f[x][0] += f[y][1];//x节点不放
		f[x][1] += min(f[y][0], f[y][1]);//x节点放，取子节点的最小值
	}
}

int main() {
	while(scanf("%d", &n) != EOF) {//多组数据
		int st = 0;//起点
		memset(f, 0, sizeof(f));//初始化
		for(int i = 1; i <= n; i ++) {
			int x, k;
			scanf("%d:(%d)", &x, &k);
			e[x].clear();//初始化
			while(k --) {
				int y;  scanf("%d", &y);
				e[x].push_back(y);//存边
			}
			if(i == 1) st = x;//记录根节点
		}
		dfs(st);//dp
		printf("%d\n", min(f[st][0], f[st][1]));//输出
	}
	return 0;
}
```


---

## 作者：Imakf (赞：2)

借这道题讲点其他的。

这道题实质上是求 **最小权覆盖集** 的权值，但我们不会怎么办办呢？

用到一个结论：**最小权覆盖集 = 所有权值 - 最大权独立集**。

而最大权独立集就是没有上司的舞会。

还有一件事，题目里的点下标是从 0 开始的，记得 +1。

```
#include <cstdio>
#define MX (1500 + 5)

void addedge(int u ,int v){加边}

int dp[MX][2];
void dapai(int x ,int f){
	dp[x][1] = 1 ,dp[x][0] = 0;
	for(int i = head[x] ,d ; i ; i = h[i].next){
		d = h[i].node;
		if(d == f)	continue;
		dapai(d ,x);
		dp[x][0] += max(dp[d][0] ,dp[d][1]);
		dp[x][1] += max(dp[d][0] ,0);
	}
}

int main(){
	int n;
	while(~scanf("%d" ,&n)){
		tot = 0;
		for(int i = 1 ; i <= n ; ++i)	head[i] = 0;
		for(int u ,v ,i = 1 ,j ; i <= n ; ++i){
			scanf("%d:(%d)" ,&u ,&j); ++u;
			while(j--){
				scanf("%d" ,&v); ++v;
				addedge(u ,v);
				addedge(v ,u);
			}
		}
		dapai(1 ,0);
		int t = max(dp[1][0] ,dp[1][1]);
		printf("%d\n" ,n - t);
	}
	return 0;
}
```

---

## 作者：andysk (赞：2)


[Luogu2016](https://www.luogu.org/problem/P2016)

[UVA1292 Strategic game](https://www.luogu.org/problem/UVA1292)


双倍经验，重题请做P2016

很明显的一道树形DP，可以分两种情况讨论。

第一种，在当前点 $u$ 不放置一个士兵，那么它的子树全部得放，则：$f[u][0] = \sum_{v \in son(u)} f[v][1]$

第二种，如果放置一个士兵，它子树中的节点可放可不放，则：$f[u][1] = \sum_{v\in son(u)} min(f[v][1], f[v][0])$

最后答案为 $root$ 节点的放置个数，即：$min(f[1][0], f[1][1])$ 

习惯于 $1$ 作为根节点，故读入时全部节点编号$+1$



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1500 + 5;

int n, num;
int head[SIZE], f[SIZE][2];

struct node {
    int to, Next;
} edge[SIZE << 1];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline void Addedge(int x, int y)
{
    edge[++num].to = y;
    edge[num].Next = head[x];
    head[x] = num;
}

inline void DFS(int u, int fa)
{
    f[u][1] = 1, f[u][0] = 0;
    for (int i = head[u]; i; i = edge[i].Next) {
        int v = edge[i].to;
        if (v == fa) continue;
        DFS(v, u);
        f[u][0] += f[v][1];
        f[u][1] += std::min(f[v][0], f[v][1]);
    }
}

int main()
{
    n = read();
    for (int i = 1; i <= n; i++) {
        int u = read() + 1, k = read();
        for (int j = 1; j <= k; j++) {
            int v = read() + 1;
            Addedge(u, v);
            Addedge(v, u);
        }
    }
    DFS(1, 0);
    printf("%d", std::min(f[1][0], f[1][1]));
    return 0;
}
```



---

## 作者：xyvsvg (赞：1)

看大家都用的 dp，我来一发贪心思路吧。

如果一个节点是叶子节点，则将士兵放在它的父亲一定是更优的。否则，检查此节点的所有儿子，如果都有士兵，则该节点不用放，否则需要放一个士兵。

正确性也是显然的，因为每个士兵的代价都为 $1$，因此即使你当前在本可以不放士兵的节点放了一个士兵，也最多节约 $1$ 的代价，还不如不放。

代码（一个坑点是节点 $1$ 不一定是根）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        vector<vector<int> >G(n+10);
        vector<bool>vis(n+10);
        for(int i=1;i<=n;++i)
        {
            int u,k;
            scanf("%d:(%d)",&u,&k);
            while(k--)
            {
                int v;
                scanf("%d",&v);
                G[u+1].push_back(v+1);
                vis[v+1]=1;
            }
        }
        queue<int>que;
        vector<int>id;
        for(int i=1;i<=n;++i)
            if(!vis[i])
                que.push(i);
//        que.push(1);
        while(!que.empty())
        {
            int u=que.front();
            que.pop();
            id.push_back(u);
            for(int v:G[u])
                que.push(v);
        }
        reverse(id.begin(),id.end());
        vector<int>res(n+10);
        for(int u:id)
        {
            bool flag=1;
            for(int v:G[u])
                flag&=res[v];
            res[u]=!flag;
        }
        cout<<accumulate(res.begin(),res.end(),0)<<endl;
    }
    return 0;
}
```

---

## 作者：Zxsoul (赞：1)

# 树形DP模板
## 思路
为了保证士兵相互看到，换句话说就是他们俩个相连，所以只选择其中一个点就好了，这像级了**舞会**，那么我们的dp式子有
$$
dp[i][1]+=min\{dp[v][1],dp[v][0]\} 
$$
$$
dp[i][0]+=dp[v][1]
$$

$dp[i][1/0]$ 表示以 $i$ 为根的子树内最少选择士兵数，且 $i$点选与不选，

两点相连至少有一个被选中才可，所以有了上述的转移方程

深搜回溯，由子树扩展到整颗树，树形DP模板通俗易懂

## 注意

数据为多组，请看好PDF

## Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <string.h>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int v,nxt;
}e[B<<1];

int n, f[B][3],head[B],m,cnt;

void add(int u,int v)
{
  e[++cnt].nxt=head[u];
  e[cnt].v=v;
  head[u]=cnt;
}

void dfs(int u,int fa)
{
  f[u][0]=0;f[u][1]=1;
  for (int i=head[u];i;i=e[i].nxt)
  {
    int v=e[i].v;
    if(v==fa) continue;
    dfs(v,u);
    f[u][0]+=f[v][1];
    f[u][1]+=min(f[v][1],f[v][0]);
  }
}

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  while(scanf("%d",&n)!=EOF)
  {
    memset(f,0,sizeof(f));
    memset(head,0,sizeof(head));
    cnt=0;
  for (int i=1;i<=n;i++)
  {
    int u=read(),k=read();
    for (int j=1;j<=k;j++)
    {
      int v=read();
      add(u,v);
      add(v,u);
    }
  }
  dfs(0,-1);
  printf("%d\n",min(f[0][0],f[0][1]));
  }
  fclose(stdin);
  fclose(stdout);
  return 0;
}


```

---

## 作者：Ezis (赞：1)

#### 题意：
标记最少的点使所有的边都被包含。

前置知识：树形DP

**状态：**

$f[u][0/1]$ 表示 $u$ 号点，选或不选。

若当前点不选，那它的儿子选或不选都可以。

若当前点要选，那它的儿子只能不选。

**转移：**

$f[u][0]+=max(f[v][0],f[v][1])$

$f[u][1]+=f[v][0]$

**初值：**
 
$f[u][0]=0$

$f[u][1]=1$

最后的答案就是 $n-max(f[1][0],f[1][1])$

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int edgenum,n;
int head[3005];
struct node{
	int to,nxt;
}edge[3005];
int f[3005][2];
void init(){
	edgenum=0;
	memset(head,0,sizeof(head));
	memset(f,0,sizeof(f));
	memset(edge,0,sizeof(edge));
}
void add(int u,int v){
	edgenum++;
	edge[edgenum].to=v;
	edge[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int u,int fa){
	f[u][0]=0;
	f[u][1]=1;
	for(int e=head[u];e;e=edge[e].nxt){
		int v=edge[e].to;
		if(v==fa)
			continue;
		dfs(v,u);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
}
int main(){
	while(scanf("%d",&n)!=EOF){
		init();
		for(int i=1;i<=n;i++){
			int u,m;
			scanf("%d",&u);
			getchar();
			getchar();
			scanf("%d",&m);
			getchar();
//			cout<<m<<endl; 
			u++;
			while(m--){
				int v;
				scanf("%d",&v);
				v++;
				add(u,v);
				add(v,u);
			}
		}
		dfs(1,0);
		printf("%d\n",n-max(f[1][0],f[1][1]));
	}
	return 0;
} 
```


---

