# The Door Problem

## 题目描述

Moriarty has trapped $ n $ people in $ n $ distinct rooms in a hotel. Some rooms are locked, others are unlocked. But, there is a condition that the people in the hotel can only escape when all the doors are unlocked at the same time. There are $ m $ switches. Each switch control doors of some rooms, but each door is controlled by exactly two switches.

You are given the initial configuration of the doors. Toggling any switch, that is, turning it ON when it is OFF, or turning it OFF when it is ON, toggles the condition of the doors that this switch controls. Say, we toggled switch $ 1 $ , which was connected to room $ 1 $ , $ 2 $ and $ 3 $ which were respectively locked, unlocked and unlocked. Then, after toggling the switch, they become unlocked, locked and locked.

You need to tell Sherlock, if there exists a way to unlock all doors at the same time.

## 说明/提示

In the second example input, the initial statuses of the doors are $ [1,0,1] $ ( $ 0 $ means locked, $ 1 $ — unlocked).

After toggling switch $ 3 $ , we get $ [0,0,0] $ that means all doors are locked.

Then, after toggling switch $ 1 $ , we get $ [1,1,1] $ that means all doors are unlocked.

It can be seen that for the first and for the third example inputs it is not possible to make all doors unlocked.

## 样例 #1

### 输入

```
3 3
1 0 1
2 1 3
2 1 2
2 2 3
```

### 输出

```
NO```

## 样例 #2

### 输入

```
3 3
1 0 1
3 1 2 3
1 2
2 1 3
```

### 输出

```
YES```

## 样例 #3

### 输入

```
3 3
1 0 1
3 1 2 3
2 1 2
1 3
```

### 输出

```
NO```

# 题解

## 作者：Adove (赞：7)

扩展域并查集是个好东西啊~~（这题可以绿了~~

首先对于钥匙$i$，可以确定要么选（记为$i$），要么不选（记为$i+m$）

然后对于开着的，把$key1,key2$并起来，$key1+m,key2+m$并起来

对于关着的，把$key1,key2+m$并起来，$key1+m,key2$并起来

如果发现存在$i$，使得$find(i)==find(i+m)$，则无解

否则有解

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1e5+5;

int n,m;
bool b[MAXN],cnt[MAXN];
int key[2][MAXN],f[MAXN<<1];

int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x;
}

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void un(int a,int b){int fa=find(a),fb=find(b);if(fa!=fb) f[fa]=fb;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) b[i]=read();
	for(int i=1;i<=m;++i){
		int x=read();
		while(x--){
			int y=read();
			key[cnt[y]++][y]=i;
		}f[i]=i;f[i+m]=i+m;
	}for(int i=1;i<=n;++i){
		if(!b[i]) un(key[0][i],key[1][i]+m),un(key[1][i],key[0][i]+m);
		else un(key[0][i],key[1][i]),un(key[0][i]+m,key[1][i]+m);
	}for(int i=1;i<=m;++i) if(find(i)==find(i+m)){puts("NO");return 0;}
	puts("YES");
	return 0;
}
```

---

## 作者：1saunoya (赞：7)

考虑 $\texttt{2-SAT}$

首先每个门 $i$ 都有一个初始状态 $a_i$

题目条件每个门只被两个开关控制，那么很显然的 $\texttt{2-SAT}$

用 $b_{i,{0/1}}$记录是第 $1/2$ 个开关
然后就考虑一下门的初始状态 $a_i$


- 门本身是开的

你开这个开关为开，另一个也要是开的，
反之亦然，所以建两对双向边

- 门本身是关的

你开这个开关为开，另一个必须是关的
反之亦然，所以还是建两对双向边

然后根据 $\texttt{2-SAT}$ 的性质，可得答案

```cpp
#include<bits/stdc++.h>
using namespace std ;
int n , m ;
const int N = 2e5 + 10 ;
int a[N] ;
int b[N][2] ;
struct Edge { int v , nxt ; } e[N << 2] ;
int head[N << 1] , cnt = 0 ;
inline void add(int u , int v) {e[++ cnt] = { v, head[u]} ; head[u] = cnt ; }
int dfn[N << 1] , low[N << 1] , idx = 0 , st[N << 1], tp = 0 , co[N << 1] , num = 0 ;
inline void tarjan(int u) { dfn[u] = low[u] = ++ idx ; st[++ tp] = u ;
  for(register int i = head[u] ; i ; i = e[i].nxt) { int v = e[i].v ;
    if(! dfn[v]){ tarjan(v) ; low[u] = min(low[u] , low[v]) ; }
    else if(! co[v]) { low[u] = min(low[v] , dfn[v]) ; }
  } if(low[u] == dfn[u]) { co[u] = ++ num ; while(st[tp] ^ u) co[st[tp --]] = num ; tp -- ; }
}
signed main() {
#ifdef _WIN64
  freopen("0.in"  , "r" , stdin) ;
#endif
  ios :: sync_with_stdio(false) ; cin.tie(nullptr) ; cout.tie(nullptr) ;
  memset(a , 0 , sizeof(a)) ; memset(b , 0 , sizeof(b)) ;
  cin >> n >> m ;
  for(register int i = 1 ; i <= n ; i ++) { cin >> a[i] ; }
  for(register int i = 1 ; i <= m ; i ++) { int t ; cin >> t ;
    for(register int j = 1 ; j <= t ; j ++) { int x ; cin >> x ; if(b[x][0]) { b[x][1] = i ; } else b[x][0] = i ; }
  }
  for(register int i = 1 ; i <= n ; i ++) {
    if(a[i]) { add(b[i][0] , b[i][1]) ; add(b[i][1] , b[i][0]) ; add(b[i][0] + m , b[i][1] + m) ; add(b[i][1] + m , b[i][0] + m) ; }
    else { add(b[i][0] , b[i][1] + m) ; add(b[i][1] + m , b[i][0]) ; add(b[i][1] , b[i][0] + m) ; add(b[i][0] + m , b[i][1]) ; }
  }
  for(register int i = 1 ; i <= m * 2 ; i ++) { if(! dfn[i]) tarjan(i) ; }
  for(register int i = 1 ; i <= m ; i ++) if(co[i] == co[i + m]) { return cout << "NO\n" , 0 ; }
  cout << "YES\n" ;
  return 0 ;
}
````

---

## 作者：naroto2022 (赞：3)

# CF776D题解

### 题意

有 $n$ 扇门和 $m$ 个开关，门的状态只有开和关两种，初始时只有部分的门是开的。每个开关可以控制多扇门，按下后可以改变对应的门的开关状态（开的关闭，关的开启）。保证每扇门只受两个开关控制，求最少多少次操作后所有的门都会被打开。

数据范围：$n,m\leqslant10^5$。

### 思路

每扇门只有两个状态（开和关），每个开关也只有两个状态（操作和不操作，因为操作偶数次等于不操作，奇数次等于操作一次）。两种变量看起来都适合做 2-SAT。

接下来考虑如何用条件在不同的状态间连边。注意到题目中的特殊条件“保证每扇门只受两个开关控制”，这说明如果想要门的状态不变，那么两个开关一定都按了或都没按；如果想要改变门的状态，那么两个开关肯定一个有按一个不按。
具体地，我们用 $0$ 和 $1$ 表示一个开关没按/按了。假设某一扇门由开关 $x,y$ 控制。如果这扇门一开始是关的，那么 $x$ 与 $y$ 一定一个取 $0$ 一个取 $1$，即连边为 $(x,0)\leftrightarrow(y,1),(x,1)\leftrightarrow(y,0)$；如果这扇门开始的时候已经开了，那么 $x$ 与 $y$ 一定取值相等，连边为 $(x,0)\leftrightarrow(y,0),(x,1)\leftrightarrow(y,1)$。之后跑 2-SAT 求解即可。

代码就不放了

---

## 作者：Mine_King (赞：3)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/15864995.html)

## Problem

[CF776D The Door Problem](https://www.luogu.com.cn/problem/CF776D)

**题目大意：**

有 $n$ 扇门和 $m$ 把钥匙，初始时有些门开着，有些门关着。一把钥匙对应多个门，每个门对应恰好两把钥匙。使用一把钥匙会使该钥匙对应的所有门的状态改变（开变成关，关变成开），问是否有存在一种钥匙的使用方案使得所有门都被打开。

## Solution

我们将初始时开着的和关着的门分开讨论。

对于开着的门，两把钥匙要么都用，要么都不用。  
对于关着的门，两把钥匙必须使用恰好一把。

也就是说，对于开着的门，两把钥匙的使用情况相同。  
对于关着的门，两把钥匙的使用情况不同。

于是我们可以想到扩展域并查集。对于第 $i$ 扇门，若他对应的钥匙是 $k_1$ 和 $k_2$，若他是开着的，则合并 $(k_1,k_2),(k_1+n,k_2+n)$，若他是关着的，则合并 $(k_1,k_2+n),(k_1+n,k_2)$。

若最终出现一把钥匙 $j$，$j$ 和 $j+n$ 被并在一起，说明 $j$ 既要被使用，又要不被使用，显然是不合法的。否则就是合法的。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,lck[100005],key[100005];
struct bin
{
	int f[200005];
	bin(){for(int i=1;i<=200000;i++) f[i]=i;}
	int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
	void merge(int x,int y){f[find(x)]=find(y);return;}
	int query(int x,int y){return find(x)==find(y);}
}b;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&lck[i]);
	for(int i=1;i<=m;i++)
	{
		int k;
		scanf("%d",&k);
		for(int j=1;j<=k;j++)
		{
			int x;
			scanf("%d",&x);
			if(key[x]!=0)
			{
				if(lck[x]==0) b.merge(key[x],i+m),b.merge(key[x]+m,i);
				else b.merge(key[x],i),b.merge(key[x]+m,i+m);
			}
			else key[x]=i;
		}
	}
	for(int i=1;i<=m;i++)
		if(b.query(i,i+m)){puts("NO");return 0;}
	puts("YES");
	return 0;
}
```


---

## 作者：小明小红 (赞：1)

# CF776D题解
**算法思路**：为什么要用 $2-SAT$？我不会啊！既然我们知道每一个门对应两个钥匙，那么要想使这个门是开着的，这两个钥匙之间肯定有一定的关系，所以我们可以考虑**扩展域并查集**。

**什么是扩展域并查集**：顾名思义，是在原先并查集的基础上添加一些元素。

**如何构造**：每个钥匙对于门只有**两种情况**，开门或者不开门，既然如此我们可以令第 $i$ 个钥匙为用 $i$ 钥匙开门，而第 $i+m$ 个则为不用 $i$ 钥匙开门。

**如何建立关系**：门的初始状态只有两种，开或者不开，我们一一讨论。

初始为 $1$：代表这个门本来就是开着的，我们要么两个钥匙**都用**，要么两个钥匙**都不用**，所以在 $x$ 与 $y$ 之间建立关系， $x+m$ 与 $y+m$ 之间建立关系。 

初始为 $0$：代表着这个门本来就是关着的，两个钥匙只能用一个，所以在 $x$ 与 $y+m$ 之间建立关系， $x+m$ 与 $y$ 之间建立关系。

**如何判断最终是否合法**：我们知道，一把钥匙的使用与否不能变，所以如果 $i$ 和 $i+m$ 在一个并查集内，这就不是合法的。

记住并查集要开两倍空间！
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,t[100009];
struct door {
	ll l,r;
} s[100009];
ll fa[200009];
ll find(ll x) {
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void add(ll x,ll y) {
	fa[find(y)]=find(x);
}
int main() {
	cin>>n>>m;
	for(ll i=1; i<=n; i++) {
		cin>>t[i];
	}
	for(ll i=1; i<=m; i++) {
		ll a,x;
		cin>>a;
		while(a--) {
			cin>>x;
			if(s[x].l==0) {//l,r分别存这扇门的两个钥匙 
				s[x].l=i;
			} else {
				s[x].r=i;
			}
		}
	}
	for(ll i=1; i<=2*m; i++) {
		fa[i]=i;//两倍空间 
	}
	for(ll i=1; i<=n; i++) {
		if(t[i]==1) {//建立关系 
			add(s[i].l,s[i].r);
			add(s[i].l+m,s[i].r+m);
		} else {
			add(s[i].l+m,s[i].r);
			add(s[i].l,s[i].r+m);
		}
	}
	for(ll i=1; i<=m; i++) {
		if(find(i)==find(i+m)) {//钥匙不能变 
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```
最后加一句，如果还想练习扩展域并查集的话，可以来[这道题](https://www.luogu.com.cn/problem/P2024)。

---

## 作者：yi_fan0305 (赞：1)

给定题目一看，门有初始状态。开关要么开，要么关，只有这两种状态，这就提示我们可以用 2-SAT 来做。
对于每一扇门，如果它是开着的，那么对应的两个开关必须同时开或同时关；如果初始是关着的，对应的两个开关必须是一关一开，我们可以根据这个关系来建图连边，最后跑一遍 tarjan 来判断是否有解即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

int n, m, cnt, tim, scc;
int g[N][2], id[N][2], dfn[N << 1], low[N << 1], lt[N << 1];
bool chock[N];
vector<int> son[N << 1], sta;

void tarjan(int u) {
	dfn[u] = low[u] = ++ tim;
	sta.push_back(u);
	for (int v : son[u]) {
		if (! dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (!lt[u]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		lt[u] = ++ scc;
		while (sta.back() != u) {
			lt[sta.back()] = scc;
			sta.pop_back();
		}
		sta.pop_back();
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; ++ i) {
		scanf("%d", &x);
		if (x == 0)	fg = 0;
		chock[i] = x;
	}
	for (int i = 1, tot; i <= m; ++ i) {
		scanf("%d", &tot);
		for (int j = 1, x; j <= tot; ++ j) {
			scanf("%d", &x);
			if (!g[x][0])	g[x][0] = i; // 记录门对应的两个开关
			else	g[x][1] = i;
		}
	}
	for (int i = 0; i <= 1; ++ i) { // 给每个状态打上标号
		for (int j = 1; j <= m; ++ j) {
			id[j][i] = ++ cnt;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		if (! chock[i]) {
			son[id[g[i][0]][0]].push_back(id[g[i][1]][1]);
			son[id[g[i][1]][1]].push_back(id[g[i][0]][0]);
			son[id[g[i][1]][0]].push_back(id[g[i][0]][1]);
			son[id[g[i][0]][1]].push_back(id[g[i][1]][0]);
		}
		else {
			son[id[g[i][0]][1]].push_back(id[g[i][1]][1]);
			son[id[g[i][1]][1]].push_back(id[g[i][0]][1]);
			son[id[g[i][1]][0]].push_back(id[g[i][0]][0]);
			son[id[g[i][0]][0]].push_back(id[g[i][1]][0]);
		}
	}
	for (int i = 1; i <= 2 * m; ++ i) {
		if (! dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= m; ++ i) {
		if (lt[id[i][0]] == lt[id[i][1]]) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：1)

每个门只能用两个开关（钥匙）控制，明显的 2-SAT。

设当前开关为 $i$ 表示使用，则 $i+m$ 表示不使用此开关。

我们考虑建边，由于最后的门都是开的，并且我们知道开关按两次相当于不按，所以有以下两种情况：

1. 当前门是关着的，所以需要开奇数次的开关，所以两个开关的次数分别为一奇一偶，而由上面得知偶数的相当于不开，所以相当于其中一个开关只能开一次，所以设控制当前门的开关为 $(i,j)$，所以连接 $(i,j+m),(i+m,j),(j+m,i),(j,i+m)$。

2. 当前门是开着的，所以需要开偶数次的开关，同上可以想出两个开关要么都开一次，要么都不开，设控制当前门的开关为 $(i,j)$，所以连接 $(i,j),(j,i),(i+m,j+m),(j+m,i+m)$。

然后我们的图建好了，跑一遍 2-SAT 模板就好了。

code:

```cpp
#include<bits/stdc++.h>
#define N 1000100
using namespace std;
struct sb{int u,v,next;}e[N];
int n,m,cnt,a[N],mp[N][2],low[N],dfn[N],tim,stk[N],top,vis[N],sd[N],head[N];//加m表示不用 
inline int read(){int x=0,f=1;char ch=getchar();while(!isdigit(ch)){f=ch!='-';ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return f?x:-x;}
inline void add(int u,int v){e[++cnt].v=v;e[cnt].next=head[u];head[u]=cnt;}
inline void tarjan(int x)
{
	low[x]=dfn[x]=++tim;vis[x]=1,stk[++top]=x;
	for(int i=head[x];i;i=e[i].next)
	{
		int v=e[i].v;
		if(!dfn[v])tarjan(v),low[x]=min(low[x],low[v]);
		else if(vis[v])low[x]=min(low[x],dfn[v]);
	}
	if(low[x]==dfn[x])
	{
		int y;
		while(1)
		{
			y=stk[top--];
			sd[y]=x;
			vis[y]=0;
			if(x==y)break;
		}
	}
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)
	{
		int k=read();
		for(int j=1;j<=k;j++)
		{
			int x=read();
			if(!mp[x][0])mp[x][0]=i;
			else mp[x][1]=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==0)
		{
			add(mp[i][0],mp[i][1]+m);
			add(mp[i][1],mp[i][0]+m);
			add(mp[i][0]+m,mp[i][1]);
			add(mp[i][1]+m,mp[i][0]);
		}
		else 
		{
			add(mp[i][0],mp[i][1]);
			add(mp[i][1],mp[i][0]);
			add(mp[i][0]+m,mp[i][1]+m);
			add(mp[i][1]+m,mp[i][0]+m);
		}
	}
	for(int i=1;i<=m*2;i++)if(!dfn[i])tarjan(i);
	for(int i=1;i<=m;i++)
	{
		if(sd[i]==sd[i+m])
		{
			cout<<"NO"<<endl;
			return 0;
		}	
	}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

这篇文章主要介绍**拓展域并查集**。

拓展域并查集，主要用于一种状态表示无法解决问题的题目。例如本题，一个开关有两种状态，用和不用。

本文主要介绍二倍拓展域的拓展域并查集。

## 什么是拓展域并查集？

拓展域并查集是一种数据结构，用于解决具有多个相互关系集合的问题。它是传统并查集的扩展，能够处理集合间的不同关系，如相互排斥或相互独立的关系。

## 拓展域并查集有什么用？
只看定义是不可以的，我们来看一个应用场景：

$n$ 个点有 $m$ 对关系，把 $n$ 个节点放入**两个集合**里，要求**每对**存在关系的两个节点**不能**放在同一个集合。问能否成功完成？

这个问题我们直接用普通并查集是无法通过的，我们必须换一个更加高级的办法。

在原本的并查集中，$i$ 号点在并查集中对应的点正好为 $i$，而在拓展域并查集中对应的是 $i$ 和 $i+n$ 等。当然这个题只需要 $i$ 和 $i+n$ 就够了，有些需要 $i+2n$ 之类的。

例如：对于以下样例，如果我们使用普通并查集，建出来的图是这样的：

```
4 6
1 2
2 3
3 4
4 5
5 6
6 1
```

![](https://cdn.luogu.com.cn/upload/image_hosting/kefslj3p.png)

但是如果我们对于下面的样例，结果是这样的：

```
4 7
1 2
2 3
3 4
4 5
5 6
6 7
7 1
```

![](https://cdn.luogu.com.cn/upload/image_hosting/frpvpe0i.png)

这张图除了比上面这张多了一个点之外，与上面一张基本没有什么区别，如果我们仅仅只使用并查集的话，是看不出什么区别的。

所以这个使用普通并查集是不可取的。

我们使用拓展域并查集，$u$ 和 $u+n$ 分别表示点 $u$ 的两个相反状态，将 $(u,v+n)$ 连边表示 $(u,v)$ 不应该在一个集合里（也可以看做 $u$ 和 $v$ 的反状态在一个集合里）。当然 $(u,v+n)$ 存在边了，相反地，$(v,u+n)$ 也理应右边。

那么就好办了，判断不可以的方式是存在 $u$ 的正反状态在一个集合里。

附上上面两个样例的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/elgn7s5c.png)

等效图：

![](https://cdn.luogu.com.cn/upload/image_hosting/57800r5i.png)

可以看到这张图明显没有任何 $u$ 的正反状态在一个集合里。

但是第二组的样例就不一样了。

![](https://cdn.luogu.com.cn/upload/image_hosting/126xhjev.png)

不够直观？看看这张等效图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gjnau3e0.png)

可以看出点 $1$ 的正反两个状态在一个集合里，所以不行。

## 拓展域并查集怎么写？

拓展域并查集在写法上仅有初始化与两点连边与普通并查集不同。

初始化：

```
for(int i=1;i<=2*n;i++)fa[i]=i;//2 倍点
```

查询父亲和合并函数与普通并查集一样。

```
int findd(int now){
    if(fa[now]==now)return now;
    return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
    u=findd(u);v=findd(v);
    if(u==v)return;
    fa[u]=v;
}
```

连边：

```
int u,v;
vnion(u,v+n);
vnion(v,u+n);
```

如果需要集合大小，集合内包含的元素等，直接与普通并查集相同写即可。


## 例题

### P1525 [NOIP2010 提高组] 关押罪犯

[题目传送门。](https://www.luogu.com.cn/problem/P1525)

我们贪心，对影响力从大到小排序。

每遇到一个事件，因为如果让这两个囚犯 $(u,v)$ 在一个监狱内，答案就是这个事件的影响力了。我们尽量尝试让最大影响力发生在后面的时间上，所以我们将 $u$ 与 $v$ 的反状态关在一个监狱里。

当你发现 $u$ 与 $u$ 的反状态关在一个监狱里时，这说明已经没救了，无论如何你都避免不了打架，那么就输出当前影响力即可（显然你可以操控使得影响力最小的事件在一个监狱内发生）。

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int u,v,w;
}e[100005];
bool cmp(node _,node __){
	return _.w>__.w;
}
int fa[40005];
int findd(int now){
	if(fa[now]==now)return now;
	return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
	u=findd(u),v=findd(v);
	if(u==v)return;
	fa[u]=v;
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=2*n;i++)fa[i]=i;
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		vnion(e[i].u+n,e[i].v);
		vnion(e[i].u,e[i].v+n);
		if(findd(e[i].u)==findd(e[i].u+n)||findd(e[i].v)==findd(e[i].v+n)){
			printf("%d",e[i].w);
			return 0;
		}
	}
	printf("0");
	return 0;
}
```

### CF776D The Door Problem

[题目传送门。](https://www.luogu.com.cn/problem/CF776D)

这题最难的是状态设计。也因此这题是蓝。

每个钥匙都有动或不动两种状态，分别设为 $i$ 和 $i+m$。

那么我们对于每个门，看看它初始开不开。设控制它的两把钥匙为 $(u,v)$：

- 如果门初始开，$(u,v)$ 只能同时选或不选，合并 $(u,v)$ 及 $(u+m,v+m)$。
- 如果门初始关，$(u,v)$ 只能二选其一，合并 $(u+m,v)$ 及 $(u,v+m)$。

```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
vector<int>g[N];
int fa[N],n,a[N],m;
int findd(int now){
    if(fa[now]==now)return now;
    return fa[now]=findd(fa[now]);
}
void vnion(int u,int v){
    u=findd(u);v=findd(v);
    if(u==v)return;
    fa[u]=v;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=2*m;i++)fa[i]=i;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1,k,x;i<=m;i++){
        scanf("%d",&k);
        for(int j=1;j<=k;j++){
            scanf("%d",&x);
            g[x].push_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i]==1){
            vnion(g[i][0],g[i][1]);
            vnion(g[i][0]+m,g[i][1]+m);
        }
        else{
            vnion(g[i][0],g[i][1]+m);
            vnion(g[i][0]+m,g[i][1]);
        }
    }
    for(int i=1;i<=m;i++){
        if(findd(i)==findd(i+m)){
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

我们已经得知每盏灯的初始状态和哪两个开关控制它。

首先分类讨论：

如果最开始这盏灯是开着的，那么这两个开关应该做出同样的操作，即要么全按，要么全不按。

如果最开始这盏灯是关着的，那么这两个开关应该做出不同的操作，即一个按一个不按。

转化一个思路，就变成了有 $m$ 个数，其中有 $n$ 个关系，有些关系是两个数要一样，有些关系是两个数要不一样，问是否合理。

自然而然地，我们想到了并查集。

先处理一样的，再处理不一样的。

一样的很好处理，直接合并了。

重点是如何处理不一样的。

我们可以用一个数组 $f$ 来存 $i$ 上一次的关系中，应该与那个数不一样。

那么，假设这一次的关系中，是 $i,j$ 要保持不一样，那么，我们可以肯定的是 $i$ 应该与 $f_j$ 一样，$j$ 应该与 $f_i$ 一样，所以合并就好了，再更新 $f_i,f_j$ 即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int k,l,r;}t[100005];
inline bool cmp(node a,node b){return a.k>b.k;}
int n,m,a,b,fa[100005];
int s[100005];
int find(int x){return (fa[x]==x)?x:fa[x]=find(fa[x]);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) fa[i]=i;
	for(int i=1;i<=n;++i) scanf("%d",&t[i].k);
	for(int i=1;i<=m;++i)
	{
		scanf("%d",&a);
		while(a--)
		{
			scanf("%d",&b);
			if(t[b].l) t[b].r=i;
			else t[b].l=i;
		}
	}
	sort(t+1,t+n+1,cmp);
	for(int i=1;i<=n;++i)
	{
		if(t[i].k){if(find(t[i].l)!=find(t[i].r)) fa[find(t[i].l)]=find(t[i].r);}
		else
		{
			int fl=find(t[i].l),fr=find(t[i].r);
			if(fl==fr) printf("NO"),exit(0);
			else
			{
				if(s[fr]) fa[s[fr]]=fl;s[fr]=fl;
				if(s[fl]) fa[s[fl]]=fr;s[fl]=fr;
			}
		}
	}
	printf("YES");
	return 0;
}
```

---

## 作者：白简 (赞：0)

### 题目大意
给定门和钥匙的数量，每把钥匙控制 $k_i$ 扇门，每扇门被两把钥匙控制。

给定初始时每扇门的状态，求是否存在一种方法使得所有的门都打开。
### 思路
扩展域并查集。

考虑分类讨论：

- 对于开着的门，要么两把钥匙都用，要么两把钥匙都不用；
- 对于关着的门，两把钥匙只能用一把。

那么我们就可以用并查集来进行维护了。

设 $i$ 为用第 $i$ 把钥匙，$i+m$ 为不用第 $i$ 把钥匙。

对于一扇门，我们记它的两把钥匙为 $u,v$。

如果这扇门开着，我们将 $u$ 与 $v$ 合并，$u + m$ 与 $v+m$ 合并；

如果这扇门关着，我们将 $u$ 与 $v+m$ 合并，$u + m$ 与 $v$ 合并。

最后，我们检查 $i$ 与 $i + m$ 是否在同一集合，如果有在同一集合的，输出 `NO`，否则输出 `YES`。
### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200500;

int n,m,k[N];
int state[N];
vector<int> key[N];

int fa[N << 1];

class DSU{
public:
    int Find(int x) {
        if(fa[x] == x)
            return x;
        return fa[x] = Find(fa[x]);
    }

    void Merge(int x,int y) {
        x = Find(x);
        y = Find(y);

        fa[x] = y;
        return ;
    }

    bool Check(int x,int y) {
        x = Find(x);
        y = Find(y);

        if(x == y)
            return 1;
        return 0;
    }
}dsu;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 1;i <= n; i++) 
        cin >> state[i];

    for(int i = 1,num,x;i <= m; i++) {
        cin >> num;
        fa[i] = i;
        fa[i + m] = i + m;
        for(int j = 1;j <= num; j++) {
            cin >> x;
            key[x].push_back(i);
        }
    }

    for(int i = 1;i <= n; i++) {
        int u = key[i][0],v = key[i][1];

        if(state[i]) {
            dsu.Merge(u,v);
            dsu.Merge(u + m,v + m);
        }
        else {
            dsu.Merge(u,v + m);
            dsu.Merge(u + m,v);
        }
    }

    for(int i = 1;i <= m; i++) {
        if(dsu.Check(i,i + m)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

~~假翻译害人~~

记 $x_i$ 表示当前开关是否使用过。

由于每扇门只受到两个开关的控制。

因此，若当前门是锁上的，对应的两个开关 $i,j$ 满足 $x_i\oplus x_j=1$，即 $x_i=!x_j$。

否则 $x_i\oplus x_j=0$ 即 $x_i=x_j$。

因此原题就等价于有若干个 $0/1$ 变量和若干个形如 $x_i=x_j$ 或 $x_i=!x_j$ 的约束条件，判断这些条件是否满足。

可以发现若出现 $x_i=!x_j$ 且 $x_j=!x_k$ 便可以推出 $x_i=x_k$。

对于每个元素 $i$，对应两个节点 $i,i'$，将 $i$ 和 $x_i=x_j$ 相同的变量放在一个集合中，将 $i'$ 和与 $x_i=!x_j$ 变量放在一个集合中。

最后判断一下 $x_i=!x_j$ 的是否在同一集合，$x_i=x_j$ 的是否在不同集合。

用并查集做一下就可以了。

时间复杂度 $\mathcal O(n+m)$。

```cpp
#include<bits/stdc++.h>
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
using namespace std;
int n,m;
int r[222222],fa[222222];
int a[222222][2];
int c[222222];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m;
	R(i,1,n) cin>>r[i];
	R(i,1,m)
	{
		int k,x;
		cin>>k;
		while(k--)
		{
			cin>>x;
			a[x][c[x]++]=i;			
		}
	}
	R(i,1,m<<1) fa[i]=i;
	int ok=1;
	R(i,1,n)
	{
		if(!r[i])
		{
			int x=find(a[i][0]),y=find(a[i][1]);
			if(x==y)
			{
				ok=0;
				break;
			}
			x=find(a[i][0]),y=find(a[i][1]+m);
			if(x!=y) fa[y]=x;
			x=find(a[i][0]+m),y=find(a[i][1]);
			if(x!=y) fa[y]=x;
		}
		else
		{
			int x=find(a[i][0]),y=find(a[i][1]+m);
			if(x==y)
			{
				ok=0;
				break;
			}
			x=find(a[i][0]),y=find(a[i][1]);
			if(x!=y) fa[y]=x;
			x=find(a[i][0]+m),y=find(a[i][1]+m);
			if(x!=y) fa[y]=x;
		}
	}
	cout<<(ok?"YES":"NO")<<endl;
}	
```

---

