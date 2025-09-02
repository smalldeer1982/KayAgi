# Choosing Capital for Treeland

## 题目描述

Treeland 国有 $n$ 个城市，有些城市间存在 **单向** 道路。这个国家一共有 $n - 1$ 条路。我们知道，如果把边视作双向的，那么从任意城市出发能到达任意城市。

城市的委员会最近决定为 Treeland 国选择一个首都，显然首都会是国中的一个城市。委员会将在首都开会，并经常去其他城市（这里不考虑从其他城市回到首都）。因此，如果城市 $a$ 被选为首都，那么所有的道路应该被定向，以使得我们能从城市 $a$ 到达其他城市。所以，有些路可能需要反转方向。
   
帮助委员会选择首都使得他们需要反转道路的次数最小。

## 样例 #1

### 输入

```
3
2 1
2 3
```

### 输出

```
0
2 
```

## 样例 #2

### 输入

```
4
1 4
2 4
3 4
```

### 输出

```
2
1 2 3 
```

# 题解

## 作者：An_Account (赞：26)

树形dp。题目中的边是单向边，但实际存的时候我们可以双向存储这条边，用一个bool型变量w来表示，看做这条边的权值（0为正向，1为反向）。假如第i个点选为首都，那么i不仅可以到它的子节点，还可以到它的祖先。在第一次**自底向上**的dfs中，我们用dp[u]表示**以u节点为首都时，u到所有子节点S需要逆转的边数**。很容易可以得出它的状态转移方程为$dp[u]=\sum(dp[S]+w[i,S])$。在第二次**自顶向下**的dfs中，dp[i]的定义变成了**u到全树节点需要逆转的边数**。假如f是u的父亲，那么当f->u这条边是正向的时候，以u为首都则需要将这条边逆转，$dp[u]+=dp[f]+1$。当f->u这条边是反向的时候，以u为首都不需要将这条边逆转，但由于u是f的子节点，因此在dp[f]中将这条边逆转了，所以$dp[u]+=dp[f]-1$。代码如下。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct edge {
    int to,next;
    bool w;
}e[400010];
int head[200010],cnt,dp[200010];
inline void adde(int from,int to,bool w) {//加边
    e[++cnt]=(edge){to,head[from],w};
    head[from]=cnt;
}
void dfs1(int u,int f) {//第一次dfs：求出u到子节点需要逆转的边数
    for (int i=head[u];i;i=e[i].next) 
        if (e[i].to!=f) {
            dfs1(e[i].to,u);
            dp[u]+=dp[e[i].to]+e[i].w;
        }
}
void dfs2(int u,int f) {//第二次dfs：求出u到全树需要逆转的边数
    for (int i=head[u];i;i=e[i].next)
        if (e[i].to!=f) {
            dp[e[i].to]=dp[u]+(e[i].w?-1:1);
            dfs2(e[i].to,u);
        }
}
int main() {
    int n,a,b;
    while (~scanf("%d",&n)) {
        cnt=0;
        memset(head,0,sizeof(head));
        for (int i=1;i<=n-1;i++) {
            scanf("%d%d",&a,&b);
            adde(a,b,false);adde(b,a,true);//双向加边
        }
        memset(dp,0,sizeof(dp));
        dfs1(1,-1);dfs2(1,-1);
        int Min=99999999;
        for (int i=1;i<=n;i++) if (Min>dp[i]) Min=dp[i];
        printf("%d\n",Min);
        for (int i=1;i<=n;i++) if (Min==dp[i]) printf("%d ",i);
        printf("\n");
    }
}
```

---

## 作者：Durancer (赞：14)

#### 题目描述

给定$n$个点，$n-1$条有向边，求到达所有其他点需要更换方向最小的次数，及符合这类条件的点的升序序列，典型的换根dp鸭

#### 思路分析 
- 首先题目说了，给定的是一颗树，所以一定有唯一的方案通往所有点，设$f[i]$为$i$点到达其余所有点需要修改的道路数量

- 我们可以先把$1$当做树的根节点，分别建立正边和反边，此时就可以保证可以通往所有点了，然后根据经过的反边的数量求出$1$点到达所有的道路所需要修改的道路数量

#### 看图时间

![原谅我高超的画技](https://cdn.luogu.com.cn/upload/image_hosting/xmxfsl7b.png)

举样例2来说明一下。首先，我们设置$1$为根节点，然后，我们就开始神奇的深搜，求出到达所有点需要修改的道路个数

```
void dfs1(int x,int fu)
{
	for(int i=head[x];i;i=e[i].last)
	{
		int v=e[i].to;
		int pd=e[i].pik;
		if(v==fu) continue;
		if(pd==1) f[x]++; //这是一条反边 
		dfs1(v,x);
		f[x]+=f[v];
	}
}
```
当然，在我这个代码中只有$f[1]$有实际意义表示修改的道路个数的，其他的只是当做一个中间媒介，下一次使用要清零（不过貌似没什么影响）,

那么第一遍深搜结束了,此时$f[1]=2$

然后我们再看图找规律，当我们转换到节点4的时候，我们经过的是一条正边走过去的，然后我们用肉眼求出$f[4]=3$
也就是$f[1]+1$

那么我们再看$3$这个点，从$4$点到达$3$点我们是经历了一条反边到达的，然后我们用肉眼求出$f[3]=2$,也就是$f[4]-1$

那么现在，发现规律了没有!

![](https://cdn.luogu.com.cn/upload/image_hosting/s88a873r.png)

没有错，就是你想的那样子，我们现在可以得到状态转移方程了！！！(设标记为$pik$)

$$f[to]=\begin{cases} 

		f[father]+1\ \ \ \ (pik=0)
        \\
        \\
        f[father]-1\ \ \ \ (pik=1)
		
		\end{cases} $$

那么进行完第二遍深搜我们就可以A掉这个题目了

![](https://cdn.luogu.com.cn/upload/image_hosting/lcgmiw89.png)

#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;
const int N=4e5+9;
struct node{
	int last;
	int to;
	int dis;
	int pik;
}e[N];
int f[N];
int ans=0x3f3f3f3f;
int head[N];
int cnt;
void add(int from,int to,int dis)
{
	e[++cnt].last=head[from];
	e[cnt].to=to;
	e[cnt].dis=dis;
	head[from]=cnt;
}
void dfs2(int x,int fu)
{
	for(int i=head[x];i;i=e[i].last)
	{
		int v=e[i].to;
		int pd=e[i].pik;
		if(v==fu) continue;
		if(pd==1)f[v]=f[x]-1;
		if(pd==0)f[v]=f[x]+1;
		ans=min(f[v],ans);
		dfs2(v,x);
	}
}
void dfs1(int x,int fu)
{
	for(int i=head[x];i;i=e[i].last)
	{
		int v=e[i].to;
		int pd=e[i].pik;
		if(v==fu) continue;
		if(pd==1) f[x]++; //这是一条反边 
		dfs1(v,x);
		f[x]+=f[v];
	}
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n-1;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y,1);
		e[cnt].pik=0;//正向边为0 
		add(y,x,1);
		e[cnt].pik=1;//反向边为1 
	}
	dfs1(1,1);
	ans=f[1];
	for(int i=2;i<=n;i++)f[i]=0;
	dfs2(1,1);
	cout<<ans<<endl;
	for(int i=1;i<=n;i++)
	{
		if(f[i]==ans)
		cout<<i<<" ";
	} 
	return 0;
}
```



---

## 作者：MurataHimeko (赞：6)

## [CF219D](https://www.luogu.com.cn/problem/CF219D)



------------
  
### 思路

我们对读入的边进行处理，读入的正向边的边权设为 0 ，同时建立一条反向边，边权设为 1 。然后以每个点为根将所有点遍历一遍，将遍历过程中的边权累加，就是以当前点为根要翻转的边的数量。时间复杂度为 $O(n^2)$



------------

### 优化

我们考虑换根 DP，设父亲节点为 $u$，子节点为 $v$，那么分别以这两个点为根遍历时，除了这两个点之间的边权不同，其他的边权没有变化。而当 $u$ 向 $v$ 的边权为 1 时， $v$ 向 $u$ 的边权一定为 0。反之亦然。所以可以有以下转移方程：

$$ dp[v] = \left\{ 
\begin{array}{rcl}
	dp[u] + 1 &  & {e[i].w = 0} \\
	dp[u] - 1 &  & {e[i].w = 1 } \\
\end{array} \right.
$$


时间复杂度为 $O(n)$ ，可以通过此题。

------------

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define swap_(i, j) i = i^j, j = i^j, i = i^j
#define abs_(x) (((x)>>31)^(x)) - ((x)>>31)
#define INF 0x3f3f3f3f
#define rep(i, f, t) for(register int i(f); i <= t; ++i)
#define per(i, f, t) for(register int i(t); i >= f; --i)
#define ste(i, f, t, s) for(register int i(f); i <= t; i += s)
#define nx(i, u) for(register int i(head[u]); i; i = e[i].next) 
#define index(l, r) (l + r | l != r)
// #define dis(a, b) (abs(nd[a].x - nd[b].x))
// #define int long long
typedef long long ll;

/***************??***************/

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

/***************??***************/

int n, u, v, ans;
int dp[200003];

struct node {
    int to, next, lim;
}e[400003];

int cnt, head[200003];

inline void add (int u, int v, int w) {
    e[++cnt] = (node){v, head[u], w};
    head[u] = cnt;
}

void dfs_1 (int u, int fa) {
    nx(i, u) {
        int v = e[i].to;
        if(v == fa) continue;
        dp[1] += e[i].lim;
        dfs_1(v, u);
    }
}

void dfs_2 (int u, int fa) {
    nx(i, u) {
        int v = e[i].to;
        if(v == fa) continue;
        if(e[i].lim) dp[v] = dp[u] - 1;
        else dp[v] = dp[u] + 1;
        ans = min_(ans, dp[v]);
        dfs_2(v, u);
    }
}

int main () {
    read(n);
    rep(i, 1, n-1) {
        read(u), read(v);
        add(u, v, 0), add(v, u, 1);
    }
    dfs_1(1, 0);
    ans = dp[1];
    dfs_2(1, 0);
    outn(ans);
    rep(i, 1, n) if(ans == dp[i]) out(i);
}
```


------------

感谢您能阅读本蒟蒻这篇博客！

---

## 作者：K2sen (赞：3)

### Choosing Capital for Treeland
[传送门](https://www.luogu.com.cn/problem/CF219D)

给你一棵树，但是树上的边都是单向边，问以 i 点为根的时候，为了能够遍历到每个点，需要修改多少条边的方向。

---

设 $f_x$ 为令 x 当首都的时候，如要翻转多少条边。

建图的时候按照双向边建图，正向和反向边分别标记，然后可以很轻松的求出以 1 为根时的答案。

转移的时候就判断 x 与 to 之间连的边是正向边还是反向边就行了。

- 如果是正向边，我们的首都从 x 到 to，需要把这条边翻转，答案就是 $f_{to} = f_{x} + 1$。

- 如果是反向边，因为以 x 为首都的时候已经翻转了，所以要翻转回来，也就是不用翻转 $f_{to} = f_{x}-1$。

### code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 200010
#define M 1010

using namespace std;
int n, add_edge;
int head[N << 1], dp[N];
struct node {
  int next, to; bool w;
}edge[N << 1];

int read() {
  int s = 0, f = 0; char ch = getchar();
  while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
  while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
  return f ? -s : s;
}

void add(int from, int to, bool w) {
  edge[++add_edge].next = head[from];
  edge[add_edge].to = to;
  edge[add_edge].w = w;
  head[from] = add_edge;
}

void dfs(int x, int fa) {
  for (int i = head[x]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (to == fa) continue;
    if (edge[i].w == 1) dp[1]++;
    dfs(to, x);
  }
}

void dfs2(int x, int fa) {
  for (int i = head[x]; i; i = edge[i].next) {
    int to = edge[i].to;
    if (to == fa) continue;
    if (edge[i].w == 1) dp[to] = dp[x] - 1;
    else dp[to] = dp[x] + 1;
    dfs2(to, x);
  }
}

int main() {
  n = read();
  for (int i = 1, x, y; i < n; i++) {
    x = read(), y = read();
    add(x, y, 0), add(y, x, 1);
  }
  dfs(1, 1);
  dfs2(1, 1);
  int minn = 1111111111;
  for (int i = 1; i <= n; i++)
    minn = min(minn, dp[i]);
  printf("%d\n", minn);
  for (int i = 1; i <= n; i++)
    if (dp[i] == minn) cout << i << " ";
  return 0;
}

```

---

## 作者：wick (赞：3)

~~**这道题的难度不应该是紫的呀**~~

n的范围是（2<=n<=2e5），那么我们可以先算出一个点（任意，就当他是节点1好了）是首都时要改的路的数量，那么我们便可以递推出与之相邻的点的答案，取最小值，再扫一遍，输出。

就这么几点：
  - 算出任意一个点（固定）
  - 递推出与之相邻的点的答案
  - 输出
  
第二点比较重要，见图:
![](https://cdn.luogu.com.cn/upload/image_hosting/d1q57ohj.png)
至于第一点的跑dfs应该是很简单的。

递归求解即可。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
struct R {
	int e;//下一个点
	bool w;//1是马路，0是小路
} s;
int ans[200005],tem=INT_MAX;
vector <R> E[200005];
int dfs(int now,int last) {
	int ans=0;
	for(int k=0; k<E[now].size(); k++) {
		if(last==E[now][k].e) continue;
		ans+=(E[now][k].w==1?0:1)+dfs(E[now][k].e,now);//"?"不会用的话，可自行换成if
	}
	return ans;
}
void dp(int now,int last) {//第二步
	tem=min(tem,ans[now]);//取最小
	for(int k=0; k<E[now].size(); k++) {
		if(last==E[now][k].e) continue;
		ans[E[now][k].e]=(E[now][k].w==1?1:-1)+ans[now];
		ddfs(E[now][k].e,now);
	}
}
int main() {
	cin>>n;
	for(int j=1; j<n; j++) {
		int e,u;
		cin>>e>>u;
		s.e=u,s.w=1;
		E[e].push_back(s);
		s.e=e,s.w=0;
		E[u].push_back(s);
	}
	ans[1]=dfs(1,1);//一般以1起点，其他的点跑出来也一样，与下面的“dp”中相同即可
	dp(1,1);
	printf("%d\n",tem);
	for(int j=1; j<=n; j++)
    		if(tem==ans[j]) printf("%d ",j);
	return 0;
}

```


---

## 作者：封禁用户 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF219D)

第一稿：2020.8.16 21:10:59

第二稿：2020.8.17 14:33:21 添加了题面简述，增加了代码注释，增强了题解可读性，更改了分组。

题意简述(已去除题目背景)：
已知一棵有 $n$ 个节点的树，树上的边是有向的，现需要指定一个节点为根，使得此根能到达所有其他节点。如果无法通过某条路，你可以将其翻转（即将 $a->b$ 改为 $b->a$)。
你的任务是：找到一个根，使此根满足题目要求所需翻转道路数最小。（答案不唯一），输出最小的翻转边数及所有满足此翻转边数的根。

对于样例一（如图）：
点 $2$ 即为满足题意的最优解，以其为根无需翻转任何一条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/tuqux12f.png)

对于样例二（如图）：
如果选择点 $4$ 则需要翻转 $3$ 条边，而选择点 $1$，$2$ 或 $3$ 则只需翻转两条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/qh0qo1vw.png)

假设我们现在搜索到点 $nod$，此节点只能通往 $fa$ 和唯一的点 $son$,那么点 $nod$ 的状态只与点 $son$ 的状态和此两点之间的边决定。

此结论对于此节点有 $k$ 个 $son$ 依然成立。

不难看出这是一个树形dp。

所以我们可以定义一个dp数组，用来存储当前点的状态。

如果有向边为 $nod$ 到 $son$，则 $dp[nod]+=dp[son];$（此边不需翻转）

否则 $dp[nod]+=dp[son]+1;$（此边需翻转）

于是我们得到了以下的代码段(树形dp）：
```cpp
void dfs(int nod,int fa) {  // nod为当前节点，fa为当前节点的父节点
    int l(way[nod].size());
    for(int i(0); i!=l; ++i) {
        int son(way[nod][i]);
        if(son==fa) continue;
        dfs(son,nod);
        dp[nod]+=dp[son];
        if(_to[mpr(son,nod)]) ++dp[nod];
    }
```

~~然后我傻乎乎地跑了一个O(TLE) 的n遍树形dp。。。~~

~~Time Limit Exdeeded in #8~~

让我们再来分析一下题目：
对于以点 $nod$ 为首都和以点 $son$ 为首都，对其造成影响的只有它们中间的一条路，即 $dp[nod]$ 和 $dp[son]$ 的差值为 1 。

所以我们加一个判断，如果单向路为从 $nod$ 到 $son$ ，则 $dp[son]=dp[nod]+1;$ 否则 $dp[son]=dp[nod]-1;$

于是就有了这段代码（具体的注释在下面的AC代码中）：
```cpp
#define mpr make_pair

typedef pair<int,int> P;
map <P,bool> _to;

if(_to[mpr(son,nod)]) ans[son]=ans[nod]-1;
else ans[son]=ans[nod]+1;
```
以上即为题目的大体思路，下面附上AC代码~~（结合注释食用更佳）~~ ：
```cpp
#include<bits/stdc++.h>
#define mpr make_pair
using namespace std;
const int MAXN=2e5+20; // 即为200020 
typedef pair<int,int> P;
map <P,bool> _to; // 用来存有向边  
vector <int> way[MAXN],a;// way[nod]表示有哪些点和点nod有边直接相连, a用来存储最优解有哪几种   
int dp[MAXN],ans[MAXN];// ans[nod] 表示以点nod为根所需翻转边数  
int n,minn(MAXN);
void made() { // 存储边 
    int x,y;
    scanf("%d%d",&x,&y);
    _to[mpr(x,y)]=true;  // 有向边存储  
    way[x].push_back(y);
    way[y].push_back(x); // 双向道路 方便处理  
}
void dfs(int nod,int fa) { // 第一遍搜索  
    int l(way[nod].size());
    for(int i(0); i!=l; ++i) {
        int son(way[nod][i]);
        if(son==fa) continue; // 防止nod->son->nod->son...死循环 
        dfs(son,nod);  //先向下一级搜索，回溯  
        dp[nod]+=dp[son]; //当前点状态需与子节点状态相加  
        if(_to[mpr(son,nod)]) ++dp[nod]; //若有向边为son->nod则需要再增加一下翻转此边的次数  
    }
}
void solve(int nod,int fa) { // 换根  
    int l(way[nod].size());
    for(int i(0); i!=l; ++i) {
        int son(way[nod][i]);
        if(son==fa) continue;// 防止nod->son->nod->son...死循环 
        if(_to[mpr(son,nod)]) ans[son]=ans[nod]-1; //单向边为从 son 到 nod
        else ans[son]=ans[nod]+1; //单向边为从 nod 到 son 
        solve(son,nod); //下一点状态需从当前点推出，所以当前点搜完再搜下一点 
    }
}
void output() {
    printf("%d\n",minn);
    int l(a.size());
    for(int i(0); i!=l; ++i) printf("%d ",a[i]);
    printf("\n");
}
int main() {
    scanf("%d",&n);
    for(int i(1); i!=n; ++i) made();
    dfs(1,0); ans[1]=dp[1]; solve(1,0);
    for(int i(1); i<=n; ++i) {// 答案处理 
        if(ans[i]<minn) {
            minn=ans[i];
            a.clear();
        }
        if(ans[i]==minn) a.push_back(i);
    }
    output();
    return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：2)

树形DP新手入门必备之题 ->[this](https://www.luogu.com.cn/problem/CF219D)

其实是黄题的难度啦。

换根DP~~套路~~思路：

1. 随便找一个根(一般取1)，计算出当决策为它时的答案（计算出以1为首都需要反转几条路）

2. 由根推向叶子，我们需要找出一个 DP 方程。

经典例题：

1. 树的重心，找到一个点，使得把树变成以该节点为根的有根树时，最大子树的节点数最小。

如果按套路，就应该设$f_i$为以 i 为根时的最大子树的节点数。

不过这样不好转移，经过思考，我们可以直接求出以 1 为根时子树 i 的大小$sum_i$（有几个节点），$f_i$ 即为$\max(sum_i-1~,~n-sum_i )$ ,然后取最小值即可。

这个例子告诉我们求转移方程时要灵活。

-------------------------------------

步入正题： 

相比树的重心，此题更加符合套路。

设 $f_i$为以 $i$ 为首都需要反转几条道路。在求 1 为首都时，不难想出，若道路的方向是由 `根 <- 子节点 的话`，$f_1$就要加1，翻转此条道路。

然后转移方程也很好想，一般我们通常使用 pull($f_i = f_{i-1}+f_{i-2}$) 型的转移方程，然而在此题中 push 型$(f_{i+1}+=f_i~,~f_{i+2}+=f_i)$更好写。

思考后，可以想到很简单的方程
$$f_{edge_i} = f_i + 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~(\text{路径为根 -> 子节点}
$$
$$f_{edge_i} = f_i - 1 ~~~~~~~~~~~~~~~~~~~~~~~~~~(\text{路径为根 <- 子节点}))$$

为甚？首先 路径为 根 -> 子节点 时，我们要让子节点朝向根才行，反之同理。具体细节见代码吧。

```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<ctime>
typedef long long ll;
const int N = 1e6+10;
int cnt = 0,head[N],edge[N],next[N],val[N];
//val = 1表示边的方向为正向的，否则是反向边。
void add(int x,int y,int v) {
	next[++cnt] = head[x];
	head[x] = cnt;
	edge[cnt] = y;
	val[cnt] = v;
} 
void addd(int x,int y) {add(x,y,1);add(y,x,0);}
int f[N],cntt = 0x7ffffff;//cnt为答案
int pre(int fa,int now) {
	int ans = 0;
	for(int i = head[now];i; i = next[i]) {
		if(edge[i] == fa)continue;
		if(!val[i])ans++;//！val[i] <-> val[i] == 0
		ans += pre(now,edge[i]);
	}
	return ans;
}
void dp(int fa,int now) {
	cntt = std::min(cntt,f[now]);
	for(int i = head[now];i; i = next[i]) {
		if(edge[i] == fa)continue;
		if(val[i] == 1)f[edge[i]] = f[now]+1;
		if(val[i] == 0)f[edge[i]] = f[now]-1;
		dp(now,edge[i]);
	}
}
int main() {
	int n;scanf("%d",&n);
	for(int i = 1; i <= n-1; i++) {
		int a,b;scanf("%d%d",&a,&b);
		addd(a,b);
	}
	f[1] = pre(-1,1);
	dp(-1,1);
	printf("%d\n",cntt);
	for(int i = 1; i <= n; i++) 
		if(f[i] == cntt)printf("%d\n",i);

	return 0;
} 
//      ┏┛ ┻━━━━━┛ ┻┓
//      ┃　　　　　　 ┃
//      ┃　　　━　　　┃
//      ┃　┳┛　  ┗┳　┃
//      ┃　　　　　　 ┃
//      ┃　　　┻　　　┃
//      ┃　　　　　　 ┃
//      ┗━┓　　　┏━━━┛
//        ┃　　　┃   神兽保佑
//        ┃　　　┃   AC Accept 得分100！
//        ┃　　　┗━━━━━━━━━┓
//        ┃　　　　　　　    ┣┓
//        ┃　　　　         ┏┛
//        ┗━┓ ┓ ┏━━━┳ ┓ ┏━┛
//          ┃ ┫ ┫   ┃ ┫ ┫
//          ┗━┻━┛   ┗━┻━┛
```


---

## 作者：lgswdn_SA (赞：2)

这是个不难的二次扫描题目（或者可以说是换根法）。

为了方便，对于一条有向边 $u\to v$，我们建边 $(u,v,0)$（即边权为 $0$）和 $(u,v,1)$，理由很简单，边权代表要不要换才能从 $u$ 走到 $v$。

我们设 $f_u$ 为以 $u$ 为首都的时候要换多少次边。第一次遍历，我们求出 $u$ 子树中要换多少次边。

```cpp
void dfs1(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa)
			dfs1(v,u),
			f[u]+=(f[v]+e[i].w);
}
```

然后，我们从父亲节点推出子节点的总共的代价。我们画图可以发现，影响的只有父节点到子节点这条边。如果父节点直接连向子节点，那么子节点的总共代价应该是父节点 $+1$（因为需要改变这条边），否则应该是父节点的代价 $-1$。

```cpp
void dfs2(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa)
			f[v]=f[u]+pow(-1,e[i].w),
			dfs2(v,u);
	if(f[u]<ans) ans=f[u],cnt=0;
	if(f[u]==ans) ak[++cnt]=u;
}
```

最后统计答案即可。放上全部代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
struct edge{int to,nxt,w;}e[N*2]; int hd[N],tot;
void add(int u,int v,int w){e[++tot]=(edge){v,hd[u],w};hd[u]=tot;}
int f[N],ans,ak[N],cnt;
void dfs1(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa)
			dfs1(v,u),
			f[u]+=(f[v]+e[i].w);
}
void dfs2(int u,int fa){
	for(int i=hd[u],v;i;i=e[i].nxt)
		if((v=e[i].to)!=fa)
			f[v]=f[u]+pow(-1,e[i].w),
			dfs2(v,u);
	if(f[u]<ans) ans=f[u],cnt=0;
	if(f[u]==ans) ak[++cnt]=u;
}
int main(){
	int n;
	while(cin>>n){
		memset(f,0,sizeof(f)),memset(ak,0,sizeof(ak)),ans=0x3f3f3f3f;
		memset(hd,0,sizeof(hd)),memset(e,0,sizeof(e)),tot=0;
		for(int i=1,u,v;i<n;i++)
			scanf("%d%d",&u,&v),add(u,v,0),add(v,u,1);
		dfs1(1,0), dfs2(1,0);
		printf("%d\n",ans);
		sort(ak+1,ak+cnt+1);
		for(int i=1;i<=cnt;i++) printf("%d ",ak[i]); puts("");
	}
	return 0;
}
```

---

## 作者：Gauss0320 (赞：2)

The country Treeland consists of n cities, some pairs of them are connected with unidirectional roads. Overall there are n - 1 roads in the country. We know that if we don't take the direction of the roads into consideration, we can get from any city to any other one.

The council of the elders has recently decided to choose the capital of Treeland. Of course it should be a city of this country. The council is supposed to meet in the capital and regularly move from the capital to other cities (at this stage nobody is thinking about getting back to the capital from these cities). For that reason if city a is chosen a capital, then all roads must be oriented so that if we move along them, we can get from city a to any other city. For that some roads may have to be inversed.

Help the elders to choose the capital so that they have to inverse the minimum number of roads in the country.
## Input
The first input line contains integer n (2 ≤ n ≤ 2·105) — the number of cities in Treeland. Next n - 1 lines contain the descriptions of the roads, one road per line. A road is described by a pair of integers si, ti (1 ≤ si, ti ≤ n; si ≠ ti) — the numbers of cities, connected by that road. The i-th road is oriented from city si to city ti. You can consider cities in Treeland indexed from 1 to n.
## Output
In the first line print the minimum number of roads to be inversed if the capital is chosen optimally. In the second line print all possible ways to choose the capital — a 
sequence of indexes of cities in the increasing order.
## 题目解析

我们需要跑两次树形dp，最终求解出所有结点到整颗数的结点需要反转的边数

不妨在原图的基础上建立反图，正向边权值为$0$，逆向边权值为$1$，令$c$为图的权函数

在第一遍树形dp中，我们令$f[x]$表示点$x$到其子树结点需要反转的边数

在搜索其孩子结点回溯时，我们可以通过以下状态转移方程得到结果
$$f[x]=\sum_{y\in son(x)}c(x,y)$$
那么我们就可以考虑求点$x$到整棵树结点所需反转的边数了，令其结果为$f'[x]$

有以下两种情况

- $c(x,y)=1$，即边$(x,y)$为正向边，所以边$(y,x)$为反向边，$f'[y]=f'[x]-1$

- $c(x,y)=0$，即边$(x,y)$为反向边，所以边$(y,x)$为正向边，$f'[y]=f'[x]+1$

代码如下
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 2e+5 + 1;
const int inf = 0x3f3f3f3f;
int n, x, y, ans, tot, head[N], dp[N];
struct Graph {
	int to, w, next;
}edge[N<<1];

void add_edge(int x, int y, int w) {
	edge[++tot].to = y;
	edge[tot].w = w;
	edge[tot].next = head[x];
	head[x] = tot;
}
void dfs1(int x, int fa) {
	for(int i = head[x]; i; i = edge[i].next) {
		int y = edge[i].to;
		if(y == fa) continue;
		dfs1(y, x);
		dp[x] += dp[y] + edge[i].w;
	}
}
void dfs2(int x, int fa) {
	for(int i = head[x]; i; i = edge[i].next) {
		int y = edge[i].to;
		if(y == fa) continue;
		dp[y] = dp[x] + (edge[i].w ? -1 : 1);
		dfs2(y, x);
	}
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		memset(head, 0, sizeof head);
		memset(dp, 0, sizeof dp);
		ans = inf, tot = 0;
		for(int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			add_edge(x, y, 0);
			add_edge(y, x, 1);
		}
		dfs1(1, 0);
		dfs2(1, 0);
		for(int i = 1; i <= n; i++)
			ans = min(ans, dp[i]);
		printf("%d\n", ans);
		for(int i = 1; i <= n; i++)
			if(dp[i] == ans) printf("%d ", i);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Isprime (赞：1)

看到这种一棵树上每一个点都要求答案的可以考虑换根 dp 解决。

题目大意是给一些有向边，问最少把这些有向边翻转多少次能形成一棵树，并且要求以哪些结点为根时翻转次数最少。

首先想想怎么求以一个点作为根时的最少翻转次数。题目中虽然给的是有向边，但我们可以知道只需要将一条边翻转一次就可以得到一条翻转的有向边。也就是说，我们不妨设一条边的边权为这条边翻转的次数，题目中给出的原有的边边权为 $0$，这条边的反向边边权为 $1$.显然以一个点作为根时的最少翻转次数就是以这个点作为根节点时组成树所有边权之和。

以样例为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/i2x9hqk0.png)

黑边为原来的有向边，红边为反转边，蓝色部分即为以 $1$ 为根的树的所有边。

我们已经求出了以 $1$ 为根的树的最少翻转次数，接下来需要想想如何快速的求出以其他点为根的最少翻转次数。

设 $f_i$ 为以 $i$ 为根的最少翻转次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/9yo9fc1n.png)

从图中我们可以看到当跟由 $i$ 变为 $i$ 的一个儿子 $j$ 时整棵树只有这两个节点之间的边的方向需要改变。由此我们可以得到当这条边边权为 $0$ 时它翻转后需要原来没有的有向边（就是我们存的边权为 $1$ 的边），所以 $f_j=f_i+1$，反之则是 $f_j=f_i-1$.

Code

```cpp

#include <cstdio>
using namespace std;
const int MAXN=200005;
inline int read() {
	int res=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0'; ch=getchar();}
	return res*f;
}
int n,ecnt;
int head[MAXN];
int f[MAXN];
int t[MAXN];
struct Edge {
	int next,to,dis;
}e[MAXN<<1];
inline void add(int from,int to,int dis) {
	e[++ecnt].next=head[from];
	e[ecnt].to=to;
	e[ecnt].dis=dis;
	head[from]=ecnt;
}
inline void dfs1(int x,int fa) { //求出以1为根时最少翻转次数
	t[x]=0;
	for(register int i=head[x];i;i=e[i].next) {
		if(e[i].to==fa) continue;
		dfs1(e[i].to,x);
		t[x]+=e[i].dis;
		t[x]+=t[e[i].to];
	}
}
inline void dfs2(int x,int fa) {//换根dp
	for(register int i=head[x];i;i=e[i].next) {
		if(e[i].to==fa) continue;
		if(e[i].dis) f[e[i].to]=f[x]-1;
		else f[e[i].to]=f[x]+1;
		dfs2(e[i].to,x);
	}
}
signed main() {
	while(~scanf("%d",&n)) {//由于题目输入没有给样例组数所以需要用这个while来判断读入是否结束
		for(register int u,v,i=1;i<n;++i) {
			u=read(); v=read(); 
			add(u,v,0); add(v,u,1);
            
		}
		dfs1(1,0);
		f[1]=t[1];
		dfs2(1,0);
		int mn=1919810;
		for(register int i=1;i<=n;++i)
			if(f[i]<mn) mn=f[i];
		printf("%d\n",mn);
		for(register int i=1;i<=n;++i)
			if(f[i]==mn) printf("%d ",i);
		printf("\n");
		ecnt=0;
		for(register int i=1;i<=n;++i)
			head[i]=0;
        //别忘了每组数据处理完后要重新初始化数组
	}
	return 0;
}

---

## 作者：Aw顿顿 (赞：1)

题目链接：**[CF219D Choosing Capital for Treelan](https://www.luogu.com.cn/problem/CF219D)**

这是一道简单的（且涉及到一个小 Trick 的）换根 DP。

## 题意

给定一个 $n$ 个节点 $n-1$ 条有向边的树，设置某个节点 $i$ 为根，则为了让他能够到达任意一个节点需要翻转 $k$ 道路，求出使得 $k$ 最小的节点 $i$。

## 解法

根与根之间须有关系。

首先将读入的边边权设为 $0$，同时建立一条反向的边，设置其边权为 $1$。

不难发现，这就变成了一个典型的换根 DP。

令父亲节点为 $u$，儿子节点为 $v$，此时不难发现当根节点转化的时候，除了这两点之间的一条边，其他的边并没有发生改变，并且 $u\to v$ 和 $v\to u$ 一定是一个 $0$ 一个 $1$，那么我们就可以写出状态转移方程：

$$f_v=\begin{cases}f_u+1&{w_{u,v}=0}\\f_u-1&{w_{u,v}=1}\end{cases}$$
 

显然，我们只需要计算其中一个点的 $f$ 值就可以推及所有的 $f$ 值。代码就很容易实现了。

## 代码

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 200005 
#define INF 0x7fffffff
using namespace std;
struct Edge{
    int v,nxt;
    bool w;
}e[N<<1];
int h[N],cnt,f[N],n,a,b;
void add(int u,int v,bool w){
	e[++cnt].v=v;e[cnt].nxt=h[u];
	e[cnt].w=w;h[u]=cnt;
}void dfs(int x,int fa){
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,x);f[x]+=f[v]+e[i].w;
	}
}void cal(int x,int fa){
	for(int i=h[x];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa)continue;
		f[v]=f[x]+(e[i].w?-1:1);
		cal(v,x);
	}
}signed main(){
    while(scanf("%lld",&n)!=EOF){
        cnt=0;
        memset(h,0,sizeof h);
        memset(f,0,sizeof f);
        for(int i=1;i<n;i++){
            scanf("%lld%lld",&a,&b);
            add(a,b,0);add(b,a,1);
        }dfs(1ll,-1ll);cal(1ll,-1ll);
        int mn=INF;
        for(int i=1;i<=n;i++)mn=min(mn,f[i]);
        printf("%lld\n",mn);
        for(int i=1;i<=n;i++)if(f[i]==mn)printf("%lld ",i);
        puts("");
    }return 0;
}
```

进行两次深搜是普通换根 DP 的普遍解法，这样一个 $O(n)$ 的 DP 是可以被接受的。

---

## 作者：Schwarzkopf_Henkal (赞：1)

其他的不用说了吧，我们直接切入正题。

首先考虑最简单的算法，也就是枚举首都位置，再求解当前位置下最小需要改建道路的条数。时间复杂度$O(n^2)$。对于本题的数据规模显然会超时。

如果是大佬这里就会用树形dp了，但是我不是大佬，所以我们用一个萌新也听得懂的方法。

对于bfs实现求某点为首都下的最小改建道路条数并不难，也不做过多讲解，具体实现见代码。然后重要的部分来了，看图片。以样例2为例，
![](https://cdn.luogu.com.cn/upload/image_hosting/9ua74crn.png)
设$Cost_i$为某个点能够达到的最小改建条数，如果有点$j$有一条小路到达$i$，则$Cost_j=Cost_i+1$，如果点$j$有一条马路到达$i$，则$Cost_j=Cost_i-1$。

注意，这个结论只有在当前图是一棵树时才适用，正确性其实不甚显然，由于在一棵树中，一条边左右连着的两个块有且仅有这一条路径通向另外一个块，所以通过这条边上付出的代价变化即为总需要付出的代价变化。

就是这样，求出一个点的最小代价后，来次深搜导出其他点的最小代价。

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,v[200005],val,res,top;
bool mk[200005];
vector<pair<int,bool> >w[200005];//保存连到某个点的边
queue<pair<int,int> >que;
struct node{
    int val,id;
}ans[200005],sta[200005];//结果的队列
bool cmp1(node a,node b){
    return a.val<b.val;
}
bool cmp2(node a,node b){
    return a.id<b.id;
}
void dfs(int p,int val){
    for(int i=0;i<w[p].size();i++)
        if(!mk[w[p][i].first]&&w[p][i].second){
            que.push(make_pair(w[p][i].first,val));
            mk[w[p][i].first]=1;
            dfs(w[p][i].first,val);
        }
}
void dfs2(int p,int c){
    ans[p].val=val+c;//深搜标记某点及其最小代价
    for(int i=0;i<w[p].size();i++)
        if(!mk[w[p][i].first]){
            mk[w[p][i].first]=1;
            if(w[p][i].second){
                dfs2(w[p][i].first,c+1);//经过马路额外值就增加
            }
            else{
                dfs2(w[p][i].first,c-1);//否则减少
            }
        }
}
int main(){
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        w[u].push_back(make_pair(v,1));
        w[v].push_back(make_pair(u,0));
    }
    mk[1]=1;
    que.push(make_pair(1,0));
    while(!que.empty()){
        int cur=que.front().first,id=que.front().second+1;
        // cout<<"cur="<<cur<<" val="<<val<<'\n';
        que.pop();
        dfs(cur,id-1);//直接标记不需要通过小路的点
        for(int i=0;i<w[cur].size();i++)
            if(!mk[w[cur][i].first]&&w[cur][i].second==0){
                que.push(make_pair(w[cur][i].first,id));
                val++;
                mk[w[cur][i].first]=1;
            }//广搜实现查找某点的最小代价
    }
    for(int i=1;i<=n;i++){
        ans[i].id=i;
        ans[i].val=2147483647;
    }
    // cout<<"val="<<val<<'\n';
    memset(mk,0,sizeof(mk));
    mk[1]=1;
    dfs2(1,0);
    sort(ans+1,ans+n+1,cmp1);
    cout<<ans[1].val<<'\n';
    for(int i=1;i<=n&&ans[i].val==ans[1].val;i++)
        sta[++top]=ans[i];
    sort(sta+1,sta+top+1,cmp2);
    for(int i=1;i<=top;i++)
        cout<<sta[i].id<<" ";//排序并输出
}


```

---

## 作者：da32s1da (赞：1)

考虑一个比较简单的思路。

我们从$1$开始dfs，能求出对于$1$点的答案。顺便能求出各个点相对于$1$点的**答案差**，同时开**vector**记录答案差的点集。

```
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+50;
int n,x,y,ans,Ans;
int to[N<<1],las[N<<1],fir[N],ds[N<<1],cnt;
inline void add_edge(int u,int v){
	to[++cnt]=v;las[cnt]=fir[u];fir[u]=cnt;ds[cnt]=1;
	to[++cnt]=u;las[cnt]=fir[v];fir[v]=cnt;ds[cnt]=-1;
}
vector<int>vp[N<<1];
void dfs(int u,int v,int a){
	//u为当前节点，v是父亲，a是与1点答案的差
	vp[a+N].push_back(u);//vector记录
	if(Ans>a)Ans=a;//更新最小值
	for(int i=fir[u];i;i=las[i])
	if(to[i]!=v)ans+=(ds[i]<0),dfs(to[i],u,a+ds[i]);
    //记录1点的答案
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
	}
	dfs(1,0,0);
	printf("%d\n",ans+Ans);
    //答案显然是1点的答案加上最小值
	Ans+=N;
	sort(vp[Ans].begin(),vp[Ans].end());
	for(int i=0;i<vp[Ans].size();i++)
	printf("%d ",vp[Ans][i]);//排序输出
}
```

---

## 作者：Crab_Dave (赞：0)

## CF219D 题解

+ ### 题意

  给出一颗含有$n$个点的有向树，显然要从某个点走到其他所有点可能行不通，这时我们需要将一些边反向，你的任务是找出一个点，使得该点反向最少边能够到达其他所有点，如果有多个这样的点，升序输出。

+ ### 思路

  考虑换根dp。

  按照套路，设 $g[i]$ 表示 $i$ 到以 $i$ 为根的子树有多少条反向边，$f[i]$ 表示 $i$ 到所有点有多少条反向边。

  怎么记录反向边呢？很简单，建双向边的时候给边打上 `0/1` 标记，$0$ 表示正向，$1$ 表示反向。

  于是有方程：
  $$
  g[u] = \sum \limits _{v \in son[u]} ( g[v] + [e_{u,v}=1])
  $$

  $$
  f[u]=f[fa]+(e_{fa,u}=1?-1:1)
  $$

  ~~所以g[x]用处不大可以直接只求一个 $g[1]$~~

  第二个方程画画图应该很好懂（

+ ### 部分代码

  ```cpp
  void dfs1(int u,int fa){
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		dfs1(v,u);g[u]+=g[v]+e[i].d;
  	}
  }
  
  void dfs2(int u,int fa){
  	for(int i=head[u];i;i=e[i].next){
  		int v=e[i].to;if(v==fa)continue;
  		f[v]=f[u]+(e[i].d?-1:1);
  		dfs2(v,u);
  	}
  }
  ```

---

## 作者：When (赞：0)

#### 算法

换根DP（二次扫描法）

#### 思路

首先，我们根据题意建树，并给边附上权值：原有的边权值为$0$，反向边权值为$1$，代表走这条边所需代价。

第一次$DFS$，钦定$1$为根，我们可以求出以$1$为根的答案。

第二次$DFS$，考虑根由$u$转移到$v$时答案会怎么变。

+ 若$u$到$v$的边权为$0$，那么一开始我们是从$u$到$v$，没有计算边权，所以不仅要加上从$v$到$u$的边权$1$，还要把一开始没算的边权加上，总共要$+2$；
+ 边权为$1$同理，不过是$-2$。

设$f_u$为以$u$为根时的最小转换次数，则有：

$$f_v=f_u - (val_{u->v}=1) + (val_{u -> v} = 0) \quad [v \in ch_u]$$

其中，$val_{u->v}$表示由$u$连向$v$的边的权值。

这样，我们就可以方便地统计出答案了！

#### 参考代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 2e5 + 10;
int n,head[maxn << 1],num;
struct Edge{
    int then,to,val;
}e[maxn << 1];

void add(int u, int v, int val){e[++num] = (Edge){head[u], v, val}; head[u] = num;}

int f[maxn];
void DFS1(int u, int fa){
    for(int i = head[u]; i; i = e[i].then){
        int v = e[i].to;
        if(v != fa){
            f[u] += e[i].val;
            DFS1(v, u);
            f[u] += f[v];
        }
    }
}

void DFS2(int u, int fa){
    for(int i = head[u]; i; i = e[i].then){
        int v = e[i].to;
        if(v != fa){
            f[v] = f[u] + (e[i].val == 0) - (e[i].val == 1);
            DFS2(v, u);
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i < n; ++ i){
        int u,v; scanf("%d%d", &u, &v);
        add(u, v, 0); add(v, u, 1);
    }
    DFS1(1, 1); DFS2(1, 1);
    int Ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; ++ i) Ans = min(Ans, f[i]);
    printf("%d\n", Ans);
    for(int i = 1; i <= n; ++ i)
        if(f[i] == Ans) printf("%d ", i);
    printf("\n");
    return 0;
}
```



---

## 作者：傅思维666 (赞：0)


## 题解：

思路：

树上最优化：考虑树形DP。需要枚举所有根求树上最优化：考虑换根DP。

所以正解：树形换根DP。

换根DP也叫二次扫描DP，如有不懂的小伙伴请走这边：

[浅谈换根DP](https://www.cnblogs.com/fusiwei/p/13615814.html)

所谓二次扫描，当然就是要扫描两次。第一次扫描是从下往上回溯信息，也就是”选择任意节点为根的树形DP预处理“。第二次扫描是从上往下更新信息，也就是”改变树的形态，祖先变儿子的换根DP“。

关键在于找出两次扫描的转移方程。

第一次扫描的转移方程是比较好想的，只需要判断当前枚举到的这条边需不需要反向即可。需要反向就加一，不需要反向就不动。

第二次扫描呢？

对于当前节点y来讲，它目前维护的以1为初根的dp[y]是正确的，也就是我们只需要统计它原来的祖先会对它造成什么影响。容易根据上一次转移发现的性质是：它父亲的答案是包含它的，也就是，对于一对父子(x,y)来讲，只需要考虑他们中间的边在换根后需不需要转向。

原来不需要，现在就需要，原来需要，现在就不需要。

于是我们也构思出了另外一个转移方程。

剩下的细节可以详见代码。再需要墨迹的一个小技巧就是对于这种有向图判断反转边的问题，可以考虑把双向边都存进去，也就是存两条边$(u,v,0),(v,u,1)$表示这条边需不需要反转。

那么代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=2*1e5+10;
const int INF=1e9;
int n,cnt,ans;
int tot,to[maxn<<1],nxt[maxn<<1],val[maxn<<1],head[maxn];
int pos[maxn],dp[maxn];
//dp[i]表示以i为根子树需要转多少边才能转回去
void add(int x,int y,int z)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	val[tot]=z;
	head[x]=tot;
}
void dfs1(int x,int f)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		dfs1(y,x);
		dp[x]+=(dp[y]+val[i]);
	}
}
void dfs2(int x,int f)
{
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==f)
			continue;
		dp[y]=dp[x]+pow(-1,val[i]);
		dfs2(y,x);
	}
	if(dp[x]<ans)
		ans=dp[x],cnt=0;
	if(dp[x]==ans)
		pos[++cnt]=x;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		cnt=0;tot=0;ans=INF;
		memset(dp,0,sizeof(dp));
		for(int i=1;i<n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y,0);
			add(y,x,1);
		}
		dfs1(1,0);
		dfs2(1,0);
		printf("%d\n",ans);
		sort(pos+1,pos+cnt+1);
		for(int i=1;i<=cnt;i++)
			printf("%d ",pos[i]);
		puts("");
	}
	return 0;
}
```



---

## 作者：GIFBMP (赞：0)

看到需要求出以所有节点为根的答案，很显然是一道换根 DP。

首先我们需要求出在以 $1$ 为根的情况下，每个节点的子树对它的贡献。

我们设 $f_i$ 表示以 $i$ 为根时，它的子树的最小反转边数。

对于每一个节点 $v(v\in son_x)$：

当 $E(x,v)$ 的方向为从 $x$ 到 $v$ 时，$f_x+=f_v$；

当 $E(x,v)$ 的方向为从 $v$ 到 $x$ 时，$f_x+=f_v+1$。

紧接着我们考虑换根。

设 $g_i$ 表示以 $i$ 为根时，整棵树的最小反转边数。

显然有 $g_1=f_1$。

然后我们考虑根从 $x$ 换到 $v(v\in son_x)$ 时：

显然除了 $E(x,v)$ 外，其它边都不需要转向。

当 $E(x,v)$ 的方向为从 $x$ 到 $v$ 时，$g_v=g_x+1$；

当 $E(x,v)$ 的方向为从 $v$ 到 $x$ 时，由于 $E(x,v)$ 在 $g_x$ 中已经变换了一次，所以 $g_v=g_x-1$。

为了方便判断，我们把正向边的边权记为 $0$，反向边的边权记为 $1$。

Code:

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std ;
const int MAXN = 2e5 + 10 , INF = 0x3f3f3f3f ;
int n , f[MAXN] ; 
struct edge {
	int to ; bool dir ;
	edge (int v = 0 , bool w = 0) {to = v ; dir = w ;}
} ;
vector <edge> G[MAXN] ;
void dfs1 (int x , int fa) {
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i].to , w = G[x][i].dir ;
		if (v == fa) continue ;
		dfs1 (v , x) ;
		f[x] += f[v] + w ;
	}
}
void dfs2 (int x , int fa) {
	for (int i = 0 ; i < G[x].size () ; i++) {
		int v = G[x][i].to , w = G[x][i].dir ;
		if (v == fa) continue ;
		f[v] = f[x] + (w ? -1 : 1) ;
		dfs2 (v , x) ;
	}
}
int main () {
	while (scanf ("%d" , &n) == 1) {
		memset (f , 0 , sizeof (f)) ;
		for (int i = 1 ; i <= n ; i++) G[i].clear () ; 
		for (int i = 1 ; i < n ; i++) {
			int u , v ;
			scanf ("%d %d" , &u , &v) ;
			G[u].push_back (edge (v , 0)) ;
			G[v].push_back (edge (u , 1)) ; 
		}
		dfs1 (1 , 0) ;
		dfs2 (1 , 0) ;
		int k = INF ;
		for (int i = 1 ; i <= n ; i++)
			if (f[i] < k) k = f[i] ;
		printf ("%d\n" , k) ;
		for (int i = 1 ; i <= n ; i++)
			if (f[i] == k) printf ("%d " , i) ;
		printf ("\n") ;
	}
	return 0 ;
}
```

---

## 作者：Polaris_Dane (赞：0)

可以树形DP

然后考虑一下换根就可以了

$dp[u]=\sum\limits_{v\in son_u}dp[v]+w(u,v)$

换根后

$dp'[u]=dp[u]-dp[v]-w(u,v)$

$dp'[v]=dp[v]+dp'[u]+w(v,u)=dp[u]+w(v,u)-w(u,v)$

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<set>
#include<queue>
#define M 1000100
#define inf 0x3f3f3f3f
#define LL long long
const int mod=988244353;
using namespace std;
inline int read(){
	int f=1,x=0;char s=getchar();
	while (!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while (isdigit(s)){x=(x<<1)+(x<<3)+(s^48),s=getchar();}
	return x*f;
}
int t,n,head[M],cnt,dp[M],dpp[M],ans,c[M];
struct edge{int to,nxt,val;}e[M<<1];
inline void add_edge(int u,int v,int w){e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v,e[cnt].val=w;} 
inline void dfs(int rt,int fa){
	dp[rt]=0;
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa) continue;
		dfs(e[i].to,rt),dp[rt]+=dp[e[i].to]+e[i].val;	
	}
}
inline void redfs(int rt,int fa){
	for (int i=head[rt];i;i=e[i].nxt){
		if (e[i].to==fa) continue;
		dpp[e[i].to]=dpp[rt]+(e[i].val?-1:1);
		redfs(e[i].to,rt);
	}
}
vector<int>p; 
signed main(void){
	while (scanf("%d",&n)!=EOF){
		memset(head,0,sizeof(head)),cnt=0;
		for (int i=1;i<=n-1;i++){
			int u=read(),v=read();
			add_edge(u,v,0),add_edge(v,u,1);
		}
		dfs(1,0),dpp[1]=dp[1];
		redfs(1,0);int ans=0,minx=inf;
		for (int i=1;i<=n;i++){
			if (minx>dpp[i]) minx=dpp[i],p.clear(),ans=0;
			if (minx==dpp[i]) p.push_back(i),ans++;
		}
		printf("%d\n",minx);
		for (int i=0;i<p.size();i++) printf("%d ",p[i]);
		puts("");
	}
	return 0;
}

```


---

## 作者：GavinZheng (赞：0)

# CF219D Choosing Capital for Treeland

这道题一开始觉得比较毒，但是想一下还是想的出来的。

我们考虑定义$dp[i][0]$代表到点$i$所有子节点的最小权值，$dp[i][1]$代表到点$i$子树外所有节点的最小权值。

那么显然有：$dp[i][0]=\sum _{t\in son_i} dp[t][0]+[t->i]$

当$fa_i=p$，又可以推出：$dp[i][1]=dp[p][1]+[i->p]+\sum _{t\in son_p,t\neq i}(dp[t][0]+[t->p])$

那么最后，对于节点$x$，选择$x$为首都的代价就是：$dp[x][0]+dp[x][1]$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
#include<unordered_map>
#define ll long long
#define maxn  (int)(2e5+1000)
using namespace std;
struct node {
    int u,v;
};
struct cop {
  bool operator()(const node a,const node b) const{
    return (a.u==b.u)?(a.v<b.v):(a.u<b.u);
  }
};
int dp[maxn][2],n,ans[maxn],cnt,mi=1e9+1000;
vector<int>side[maxn];
map<node,bool,cop>check;
ll sum[maxn];
bool test(int u,int v) {
    struct node a={u,v};
    return check[a];
}
void dfs1(int now,int fa) {
    for(int i=0;i<side[now].size();i++) {
        int v=side[now][i];if(v==fa)continue;
        dfs1(v,now);dp[now][0]+=dp[v][0]+test(v,now);
    }
}
void dfs2(int now,int fa) {
    if(now==1){dp[now][1]=0;}
    else {
        dp[now][1]=dp[fa][1]+test(fa,now)+(sum[fa]-(dp[now][0]+test(now,fa)));
    }
    int tmp=dp[now][0]+dp[now][1];
    if(tmp<mi) {
        cnt=1,ans[cnt]=now,mi=tmp;
    }
    else if(tmp==mi) {
        ans[++cnt]=now;
    }
    for(int i=0;i<side[now].size();i++) {
        int v=side[now][i];if(v==fa)continue;
        sum[now]+=dp[v][0]+test(v,now);
    }
    for(int i=0;i<side[now].size();i++) {
        int v=side[now][i];if(v==fa)continue;
        dfs2(v,now);
    }
}
int main() {
    cin>>n;
    for(int i=1;i<n;i++) {
        int u,v;cin>>u>>v;side[u].push_back(v);side[v].push_back(u);
        struct node a={u,v};check[a]=1;
    };
    dfs1(1,0);
    dfs2(1,0);
    sort(ans+1,ans+1+cnt);
    cout<<mi<<endl;
    for(int i=1;i<=cnt;i++)cout<<ans[i]<<' ';
    return 0;
}
```




---

## 作者：yijan (赞：0)

这个题可以 一次 dfs 解决的pwq 

首先求出以1 为根的时候需要反转多少次，并记录对于节点u在1为根的时候讲u为根的子树上反转成合法子树需要多少次。。（合法 意思是 从u可以到u子树上的任何点）

顺便跑的时候记录每个点的深度和从这个点到根结点（1）把1为根合法时候一共反转了的次数。。

然后统计答案。对于每个点，如果想把这个点变成根然后使得这个树合法，显然就只需要将原来1 为根的时候从1到这个点全部变成逆序就好。原来是从1可以一路走道u，现在变成从u可以一路走到1

那么这个时候由于原来是反转过的边现在显然不需要反转，所以把1为根的答案-=从这个根到这个点的反转次数，然后由于剩下的边全部需要反转（原来没反转）再加上dep[u] - 从这个根到这个点的反转次数 总的来说就是 -= 2*这个根到这个点的反转次数 + dep[u] 统计答案，解决问题。  
代码中用depf 表示这个点到1为根的时候1到这个点的反转次数。。

开始没想着记录暴力从这个点跑到根1，T飞。。。

```cpp
/*Heroes Never Die!*/
#pragma GCC optimize(3)
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
using namespace std;
#define MAXN 200006
int sum[MAXN];
int yn;
struct edge{
    int u,w;edge* next;
    edge(int u=0,int w=0,edge* next=NULL):u(u),w(w),next(next){}
    void insert(int u,int w){
        if(this->next == NULL) this->next = new edge(u,w,NULL);
        else this->next = new edge(u,w,this->next);
    }
}e[MAXN];
int depf[MAXN],dep[MAXN];
void dfs(int u,int fa){
    for(edge* n=e[u].next;n!=NULL;n=n->next){
        int v = n->u;
        if(v == fa) continue;
        depf[v] = depf[u] + n->w;
        dep[v] = dep[u] + 1;
        dfs(v,u);
        sum[u] += sum[v] + n->w;
    }
}
int ans[MAXN],p;
int res = 0,Res
int main(){
    cin >> yn;
    for(int i=0;i<yn-1;++i){
        static int u,v;scanf("%d%d",&u,&v);
        e[u].insert(v,0),e[v].insert(u,1);
    }
    dfs(1,1);
    Res = res = sum[1],ans[p++] = 1;
    for(int i=2;i<=yn;++i){
        int curres = Res;
        curres += -2*depf[i] + dep[i];
        if(curres < res) res = curres,p = 0,ans[p++] = i;
        else if(curres == res) ans[p++] = i;
    }
    sort(ans,ans+p);
    cout << res << endl;
    for(int i=0;i<p;++i) printf("%d ",ans[i]);
}
```

---

