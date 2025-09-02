# Facer的程序

## 题目描述

Facer 是一个萌萌哒的码农。他写了 $N$ 个程序。程序和程序之间有巧妙的联系，即任意两个程序恰好由一条联系链连在一起。

具体来说，对于程序 $a,b$，存在且仅存在一个序列 $a,x_1,x_2,\dots ,x_n,b$，使得 $a,x_1$ 有联系, $x_1,x_2$ 有联系，依此类推，$x_n,b$ 有联系。符合这样的一组程序称为程序块。

现在已知一个程序块的程序之间的联系，询问它有多少个子程序块。即取出一个程序子集 $S$，使得 $S$ 也满足上述条件。


## 说明/提示

### 样例解释：

子集 $\{1\},\{2\},\{3\},\{1,2\},\{2,3\},\{1,2,3\}$ 满足上述条件。

### 数据范围

对于 $10\%$ 的数据 $1\le N\le20$。

对于 $40\%$ 的数据 $1\le N\le 500$。

对于 $100\%$ 的数据 $1\le N\le10^5$。

## 样例 #1

### 输入

```
3
1 2
2 3```

### 输出

```
6```

# 题解

## 作者：7KByte (赞：5)

$Solution:$

定义:以$1$号节点为根

定义:$f[i]$为以节点$i$为根的子树个数

边界:$f[i]=1\ \ \ \ \ \ (\text{节点i为叶子节点}$

转移:$\large{}f[i]=\Large\prod\limits_{j\text{是i的子节点}}(f[j]+1)$

推理:对于状态$f[i],i$节点自身一定是要选的，而对于它的子节点为根的子树，有$f[j]$种方案，显然这颗子树也可以不选，所以有$(f[j]+1)$种选法，根据乘法原理，总方案数为它们的乘积，即$\prod\limits_{}(f[j]+1)$

答案:$\sum\limits_{i=1}^nf[i]$

$Code:$

```cpp
#include<bits/stdc++.h>
#define p 1000000007
using namespace std;
typedef long long ll;
int n,h[100005],tot=0;
struct edge{
	int to,next;
}e[200005];
void add(int x,int y){
	e[++tot].to=y;e[tot].next=h[x];h[x]=tot;
}
int f[100005],ans=0;
void dfs(int x,int fa){
	f[x]=1;
	for(int i=h[x];i;i=e[i].next)
	  if(e[i].to!=fa)
	    dfs(e[i].to,x),f[x]=(ll)((ll)f[x]*f[e[i].to]+f[x])%p;
	ans+=f[x];ans%=p;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);add(x,y);add(y,x);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Caro23333 (赞：2)

首先应该能看出来最开始给出的程序块应该是一棵无根树

然后问题就是选出的点集形成一个联通块的方案数

设计状态f[u][0/1]

f[u][0]代表以u为根的子树中，选出的联通块包含u的方案数

f[u][1]代表以u为根的子树中，选出的联通块不包含u的方案数

那么对于每个节点u,枚举它的子节点v,对于每个子节点可以设计出转移方程：

```cpp
for(Node *p = h[u]; p; p=p->next)
{
    f[u][0] *= 1+f[p->v][0];
    f[u][1] += f[p->v][0]+f[p->v][1];
}
```
第二个方程应该比较好理解，解释一下第一个：

假设节点u有若干个子节点v1,v2, ... ,vk,那么在以u为根的子树中如何构造一个包含u的联通块呢？
#### 实际上就是先选择一些u的子节点，对于每个被选择的子节点vi，选出一个在以vi为根的子树中包含vi的联通块，这些联通块选完之后再选择u，这样就形成了一个包含u的更大的联通块
那么对于一个子节点vi，有选或不选两种情况；如果选择的话有f[vi][0]种选法，根据加法原理这个子节点的方案数就是(f[vi][0]+1)

又发现每个子节点的选择情况是互相独立的，则根据乘法原理，总共的情况数为(f[v1][0]+1)(f[v2][0]+1)...(f[vk][0]+1)

也就是上面写出的转移方程了

钦定一个树根，然后从树根开始dfs进行转移

完整代码：

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define mod 1000000007

using namespace std;
typedef long long ll;
const int MAXN = 100005, root = 1;
ll f[MAXN][2];
struct Node
{
    int u,v;
    Node *next;
}*h[MAXN],pool[MAXN<<1];
int n,tot = 0;
inline void addEdge(int u, int v)
{
    Node *p = &pool[++tot], *q = &pool[++tot];
    p->v = v; p->next = h[u]; h[u] = p;
    q->v = u; q->next = h[v]; h[v] = q;
}
inline void dfs(int u, int fa)
{
    f[u][0] = 1;
    for(Node *p = h[u]; p; p=p->next)
    {
        if(p->v==fa) continue;
        dfs(p->v,u);
        f[u][0] = f[u][0]*(1+f[p->v][0])%mod;
        f[u][1] = (f[u][1]+f[p->v][0]+f[p->v][1]%mod)%mod;
	}
}

int main()
{
	cin >> n;
	int u,v;
	for(int i = 1; i<n; i++)
	{
        scanf("%d%d",&u,&v);
	    addEdge(u,v);
	}
	dfs(root,0);
	cout << (f[root][0]+f[root][1])%mod << endl;
	return 0;
}
```

---

## 作者：曹有毒 (赞：2)

dp
f[i]代表 在i这棵子树内，所有包含i的方案数。

从下向上dp，ans为所有f[i]之和。


```cpp
#include<bits/stdc++.h>
#define ll long long
const int mod=1000000007;
using namespace std;
int n;
int cnt,head[100010],ne[200010],to[200010];
ll f[100010];
ll ans;
void add(int a,int b){
    cnt++;
    ne[cnt]=head[a];
    to[cnt]=b;
    head[a]=cnt;
    return ;
}
void update(ll &a,ll b){
    a=a*(b+1)%mod;
}
void dfs(int u,int fa){
    f[u]=1;
    for(int i=head[u];i;i=ne[i]){
        if(to[i]==fa)continue;
        dfs(to[i],u);
        update(f[u],f[to[i]]);
    }
    ans=(ans+f[u])%mod;
    return ;
}
int main(){
    cin>>n;
    for(int i=1;i<n;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    cout<<ans;
}
```

---

## 作者：Link_Space (赞：1)

很简单的一道DP题，考虑用一个$dp[i]$来存储以$i$开头的合法的程序块的个数，那么根据乘法原理就可以很轻松地得到$dp[i]$即为$\prod dp_j+1$，$j$为$i$的儿子，至于为什么要+1呢？你当然还有一种选择是不选择这一条链上的所有程序，即不选该儿子，这也是一种方案，所以+1。

知道了这个之后就可以直接一个dfs,求得答案即为$\sum_{i=1}^n dp[i]$，注意累加时需要模，另外，乘的时候也需要模
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const ll MOD = 1000000007;
int head[N], cnt, nxt[N], ver[N];
void add(int x,int y)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	ver[cnt] = y;
}
ll ans;
ll dp[N];
void dfs(int now,int father)
{
	dp[now] = 1;
	for (int i = head[now]; i;i=nxt[i])
	{
		int v0 = ver[i];
		if(v0==father)
			continue;
		dfs(v0, now);
		dp[now] = (dp[now] * (dp[v0] + 1)) % MOD;
	}
	ans = (ans + dp[now])%MOD;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i < n ;i++)
	{
		int a, b;
		scanf("%d%d",&a,&b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 0);
	printf("%lld\n", ans);
}
```


---

## 作者：JK_LOVER (赞：1)

## 题意
在一棵无根树上，求问有多少颗子树。
## 分析
主要是对其它题解做出说明，并添加公式。树的节点必须要与父亲节点连接（根节点除外）。所以，因为每个儿子有选和不选两种状态，以一个点为根的子树的个数为：
$$
dp[fa] = 1 \times  \prod_{i\in son} (dp[i]+1)
$$
$$
ans= \sum_i^ndp[fa]
$$
或者，重新定义状态，$dp[x][1/0]$ 表示，这个点选择和不选择时，总共的方案数。
$$
dp[x][0] = \sum_{i\in son} (dp[i][1]+dp[i][0])
$$
$$
dp[x][1] = \prod_{i \in son} (dp[i][1]+1) 
$$
$$
ans = dp[root][1]+dp[root][0]
$$
无论是那种方法，当前节点只会在 $fa$ 上被统计一次，所以复杂度为 $O(n)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x = 0,f=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 1e5+10;
const int mod = 1000000007;
int dp[N][2],n;
vector<int> G[N];
void dfs(int u,int fa)
{
	dp[u][1] = 1;dp[u][0] = 0;
	for(int i = 0;i < G[u].size();i++)
	{
		int v = G[u].at(i);
		if(v == fa)continue;
		dfs(v,u);
		dp[u][1] = (1LL*dp[u][1]*(dp[v][1]+1)+mod)%mod;
		dp[u][0] = (1LL*dp[u][0] + dp[v][1] + dp[v][0] + mod)%mod; 
	}
}
int main()
{
	n = read();
	for(int i = 1;i <= n-1;i++)
	{
		int a = read(),b = read();
		G[a].push_back(b);
		G[b].push_back(a);		
	}	
	dfs(n,0);
	printf("%d\n",(1LL*dp[n][1]+dp[n][0]+mod)%mod);
} 
```

[地址](https://www.luogu.com.cn/blog/xzc/solution-p2796)

---

## 作者：asdfghjkl123 (赞：1)

当时我做这道题的时候，没看懂题，以为是记录树上路径总数，于是cout<<n*(n+1)/2，结果可想而知……

后来终于在他人的帮助下看懂了是道记录子树个数，结果struct的数组开了100001，结果……ARWWWWRWRW……

对代码进行解说：
```cpp
void adde(int a,int b)
{
	tree[++temp].to=a;tree[temp].next=head[b];head[b]=temp;
	tree[++temp].to=b;tree[temp].next=head[a];head[a]=temp;
}
```
这是一个建边的过程，目的就是邻接表遍历边。temp是一个用来记录边的序号的变量。
```cpp
void dfs(int node,int fa)
{
	dp[node]=1;
	for(int i=head[node];i;i=tree[i].next)if(tree[i].to!=fa)
	{
		dfs(tree[i].to,node);
		dp[node]=((dp[node]%mod)*((1+dp[tree[i].to])%mod))%mod;
	}
	ans=(ans+dp[node])%mod;
}
```
这里就是转移状态的函数了。其中，node表示当前修改的节点，fa表示当前边的父亲（叫法可能不太严谨）。这是为了在函数内的for循环判断是否连了返祖边，防止无限递归。

对于dp数组的初值，就在dfs函数中赋即可，因为这个数组只会在对应节点被访问的时候才会影响答案，否则没有影响。

dp的数值修改表示：当前节点已遍历的子树有dp[node]棵，因此再加上当前新遍历的子节点，子树个数就增加[p[tree[i].to]*dp[node]棵。所以得到了上述的式子。

最后，在每次dfs末尾，由于node节点为根的子树已经全部遍历，所以ans加上当前计算出的dp值。

最后输出结果。

---

## 作者：云浅知处 (赞：0)

题意其实是求一棵树有多少个子图满足这个子图也是一棵树。

考虑 dp：设 $F(u)$ 为以 $u$ 为根的是树的子图个数，那么有：

- 当 $u$ 为叶节点时 $F(u)=1$。
- 当 $u$ 不为叶节点时，注意到对于 $u$ 的每个子节点 $v$，如果选上 $v$，我们有 $F(v)$ 种选法。
- 此外还有“直接不选这棵子树”这种情况，因此转移方程就是：

$$
F(u)=\prod_{v\in \text{son}(u)}(F(v)+1)
$$

最终的答案就是所有 $F(u)$ 之和。

时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>

#define int long long
const int MN=1e5+5;
const int mod=1e9+7;

using namespace std;

inline int read(){
    int x=0,f=1;char c=getchar();
    for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
    for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
    return x*f;
}

int dp[MN];
vector<int>G[MN];
int n;

int ans=0;
void dfs(int u,int fa){
	dp[u]=1;
	for(int i=0;i<G[u].size();i++){
		if(G[u][i]==fa)continue;
		dfs(G[u][i],u);
		dp[u]=dp[u]*(dp[G[u][i]]+1)%mod;
	}
	ans=(ans+dp[u])%mod;
}

signed main(void){

	cin>>n;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	
	dfs(1,0);
	cout<<ans<<endl;

    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15150402.html)

> 给定一棵树，统计其子树数量。

一道小清新树形 DP 题。

定义 $dp[i]$ 为 $i$ 的子树数量，那么我们对于点 $i$，进行 dfs 求出其子节点 $v$，那么状态转移方程就是

$$dp[i]=\prod_{v}dp[v]$$ 

吗？（

仔细想一想，还要考虑子树不选的方案，所以正确是：

$$dp[i]=\prod_{v}(dp[v]+1)$$

最后的结果 $ans=\sum\limits_{i=1}^{n}dp[i]$。

~~555要是所有树形 DP 都这么返璞归真就好了（bushi~~

代码可以到博客里面去看一下，这里就不放了。

---

