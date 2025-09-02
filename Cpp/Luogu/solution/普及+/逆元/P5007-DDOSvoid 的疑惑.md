# DDOSvoid 的疑惑

## 题目背景

DDOSvoid 最近一直很痴迷于树形结构，尤其是可持久化喜羊羊灰太狼套红太狼树，可以 $O(\log)$ 维护你想维护的信息。

但是这只是一个理论数据结构，为了研究其如何实现，DDOSvoid 开始思考树的父亲和儿子之间的关系。

如果这个数据结构得到实现，那么这个世界就再也没有毒瘤题了。

但毕竟这个问题太难，所以我们先考虑下面的这个问题。


## 题目描述

给定一棵以 $1$ 为根的有根树，定义树的一个毒瘤集为一个集合，并且集合中任意两个元素之间不存在祖先与后代关系。

定义一个毒瘤集的毒瘤指数为集合内所有元素的价值之和。要求给定树的所有毒瘤集的毒瘤指数之和，答案对 $100{,}000{,}007$ 取模。

但这个问题太难了，所以我们考虑化简。

因为点的编号跟它毒瘤指数密切相关，所以我们将会再给出一个整数 $T$：$T = 1$ 表示 $i$ 号点的毒瘤指数为 $i$；$T = 0$，表示所有点的毒瘤指数都是 $1$。

## 说明/提示

#### 样例解释：

$10$ 个集合分别为 $\{1\},\{2\},\{3\},\{4\},\{5\},\{2,5\},\{3,4\}, \{3,5\},\{3,4,5\},\{4,5\}$

#### 数据范围与约定

**本题采用多测试点捆绑测试**

- 对于 $30 \%$ 的部分分，$n \le 15$；
- 另外 $20 \%$ 的部分分，$n \le 10^6$，$T = 0$；
- 对于 $100 \%$ 的数据，$n \le 10^6$，$ T <= 1$。

#### 为了方便你理解题意，下面给出毒瘤集的数学定义：

设一个毒瘤集为 $A$，则

- $\forall i\in A$，不存在一个点 $j$，使得 $j$ 在从 $i$ 到根节点的简单路径上，且 $ j \in A$。其中 $ i,j \in V$，$V$ 为树的点集。

## 样例 #1

### 输入

```
5 0
1 2
2 3
2 4
1 5```

### 输出

```
16```

# 题解

## 作者：DDOSvoid (赞：15)

## Solution：

### subtask 1:

直接 $2^n$ 枚举子集即可

### subtask 2：

定义 $f_i$ 为 i 的子树内的集合个数。

考虑如果 $i$ 只有两个儿子 $v_1$ 和 $v_2$，那么 $f_i=f_{v_1}*f_{b_2}+f_{v_1}+f_{v_2}+1$ 

这个非常显然。考虑如果有多个儿子，我们定义 $g_j$ 为前 $j$ 个儿子的集合个数，那么如果新加入一个儿子 $v$，$g_{j+1}=g_j*f_v+g_j+f_v$ 

$g_j$ 只和 $g_{j-1}$ 有关，所以直接开俩变量记录即可

复杂度 $O(n)$

### subtask 3：

其实跟点权为 1 的情况类似

定义 $f_i$ 为 i 的子树内所有的毒瘤集的价值之和

$g_i$ 为 i 的子树内的毒瘤集的个数

转移与上面类似  v 为 u 的儿子

$f_u=f_u*g_v+f_v*g_u+f_u+g_u$

$g_u=g_u*g_v+g_u+g_v$

时间复杂度依然是 $O(n)$

别忘了模数是 1e8 + 7

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#define maxn 1000010
#define ll long long
#define gc getchar
using namespace std;

int n, m, T;

int w[maxn];

const int p = 100000007;

int read(){
    int x = 0; char c = gc();
    while(!isdigit(c)) c = gc();
    while(isdigit(c)){x = x * 10 + c - '0'; c = gc();}
    return x;
}

struct Edge{
    int to, next;   
}e[maxn * 2]; int c1, head[maxn];
inline void add_edge(int u, int v){
    e[c1].to = v; e[c1].next = head[u]; head[u] = c1++;
}

ll f[maxn], g[maxn];
void dfs(int u, int fa){
    for(int i = head[u]; ~i; i = e[i].next){
        int v = e[i].to; if(v == fa) continue;
        dfs(v, u);
        f[u] = (f[u] * g[v] + f[v] * g[u] + f[u] + f[v]) % p;
        g[u] = (g[u] * g[v] + g[u] + g[v]) % p;
    }
    f[u] = (f[u] + w[u]) % p; ++g[u];
}

int main(){
    memset(head, -1, sizeof head);
    n = read(); T = read();
    for(int i = 1; i <= n; ++i) w[i] = T ? i : 1;
    for(int i = 1; i < n; ++i){
    	int x = read(), y = read();
        add_edge(x, y); add_edge(y, x); 	
    }
    dfs(1, 0); cout << f[1] << endl;
    return 0;
}

```



---

## 作者：BlueQuantum (赞：9)

# P5007 DDOSvoid 的疑惑

## Description

找出树中所有 **内部元素不存在祖先后代关系** 的集合，定义一个集合的权值为集合中所有元素的权值和，再算出所有集合的权值和。

## Solution

乍一看题面好像很迷，但是我们仔细思考一下，对于两棵不同的子树，其内部的集合如何选取是互不影响的。同时我们发现如果要明确每一个集合是什么再去计算答案十分困难，于是想到考虑每个元素的贡献。

设 $f_u$ 为以 $u$ 为根的子树中的答案， $g_u$ 为以 $u$ 为根的子树中的合法集合数量， $v$ 为 $u$ 的一个儿子，得到转移方程为：

$$
f_u = f_v * (g_u + 1) + f_u * (g_v + 1);
$$

$$
g_u = g_u + g_v * (g_u + 1)
$$

值得注意的是：
- $f_u$ 和 $g_u$ 在转移过程中并不严格是上述定义，因为一个点的子树的遍历是按次序进行的，所以 $f_u$ 和 $g_u$ 其实是 **已经遍历过的子树的答案/集合数** 具体的可以看代码
- 一个点本身的权值是在他的子节点全部遍历完后才加进去的，因为要保证集合的合法性，而一旦选中了自己，那么他的子树中的节点就一定不能选了

最终答案即为 $f_1$。

>Talk is cheap, show me your code.

```cpp
#include <cstdio>

const int N = 1000005, mod = 1e8 + 7;
int n, t;
int e_cnt, heads[N], f[N], g[N];

struct Edge {
  int v, nxt;
} e[N << 1];

inline void add(int u, int v) {
  e[++e_cnt].v = v, e[e_cnt].nxt = heads[u], heads[u] = e_cnt;
  e[++e_cnt].v = u, e[e_cnt].nxt = heads[v], heads[v] = e_cnt;
}

void solve(int u, int fa) {
  for (int i = heads[u], v; i; i = e[i].nxt) {
    if ((v = e[i].v) != fa) {
      solve(v, u);
      f[u] = 1ll * f[v] * (g[u] + 1) % mod + 1ll * f[u] * (g[v] + 1) % mod, f[u] %= mod;
      g[u] = g[u] + 1ll * (g[u] + 1) * g[v] % mod, g[u] %= mod;
    }
  }
  f[u] += t ? u : 1, f[u] %= mod, ++g[u];
}

int main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
  freopen("testdata.in", "r", stdin);
  freopen("testdata.out", "w", stdout);
#else
  freopen("P5007 DDOSvoid 的疑惑.in", "r", stdin);
  freopen("P5007 DDOSvoid 的疑惑.out", "w", stdout);
#endif
#endif

  scanf("%d%d", &n, &t);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d%d", &u, &v);
    add(u, v);
  }
  solve(1, 1);
  printf("%d", f[1]);
  return 0;
}
```

---

## 作者：zrzluck99 (赞：8)

**p党和c党的福利**

------------

作为比赛的T2，这应该是一道比较容易想出来的树形DP

我们设以节点u为根的树，它本身权值为 $a[u]$ ，内部所包含的非空集合数为 $p[u]$ ，所有集合的毒瘤值之和为 $f[u]$ ，节点u的子树为 $tree_1 , tree_2 ... tree_n$ 。

显然，对于任意不同的子树所含的集合，交叉合并都能生成一个新的符合要求的集合。由于每个子树都有 $p[tree]+1$ 种状态（任何集合都不选 or 选其中某一个集合），即意味着：

$p[u]=(p[tree_1]+1)(p[tree_2]+1) ... (p[tree_n]+1)$

$p[u]$ 就算好了，接下来求 $f[u]$。

------------

假如我们先固定子树 $tree_1$ 不动，那么包含 $tree_1$ 的集合一共有 $(p[tree_2]+1)(p[tree_3]+1) ... (p[tree_n]+1)$ 个。由于子树 $tree_1$ 对每个集合的贡献为 $f[tree_1]$ ，所以它对 $f[u]$ 的总贡献就应该是 $f[tree_1](p[tree_2]+1)(p[tree_3]+1) ... (p[tree_n]+1)$ 。

同理，对于任意子树 $tree_i$ ，我们都能求出它的贡献：

$f[tree_i](p[tree_1]+1)(p[tree_2]+1) ... (p[tree_{i-1}]+1)(p[tree_{i+1}]+1) ... (p[tree_n]+1)$

我们发现，$f[tree_i]$右边那个因子，恰好等于 $p[u]/(p[tree_i]+1)$，所以可以化简一下：

$\frac{p[u]}{p[tree_i]+1}f[tree_i]$

即 

$f[u]=a[u]+\sum_{n=1}^{N} \frac{p[u]}{p[tree_i]+1}f[tree_i]$

其中除法可以用扩欧逆元做。

最终 $f[1]$ 就是所要求的值了。

------------

喜闻乐见的上代码时刻：

```pascal
const INF=100000007;
var
    head:array[-1..1000001] of longint;
    e,next:array[-1..2000001] of longint;
    f,p,c,v,a:array[-1..2000001] of int64;
    t:longint;
    i,n,flag,x,y:longint;
    
procedure exgcd(p,q:int64; var x,y:int64);  //扩展欧几里得
var tmp:int64;
begin
    if q=0 then begin x:=1; y:=0; exit; end;
    exgcd(q,p mod q,x,y);
    tmp:=x; x:=y; y:=tmp-p div q*y;
end;

function reverse(x:int64):int64;  //求逆元
var res,tmp:int64;
begin
    res:=0; tmp:=0;
    exgcd(x,INF,res,tmp);
    res:=(res mod INF+INF) mod INF;
    exit(res);
end;
    
procedure addedge(x,y:longint);  //前向星建边
begin
    inc(t); e[t]:=y; next[t]:=head[x]; head[x]:=t;
    inc(t); e[t]:=x; next[t]:=head[y]; head[y]:=t;
end;

procedure dp(x,fa:longint);  //树形DP
var 
    i:longint;
begin
    i:=head[x]; p[x]:=1; f[x]:=a[x];
    while i>0 do begin
        if e[i]<>fa then begin
            dfs(e[i],x); p[x]:=p[x]*(p[e[i]]+1) mod INF;  //遍历子树并更新点x的子集数量
        end;
        i:=next[i];
    end;
    i:=head[x];
    while i>0 do begin
        if e[i]<>fa then begin
            f[x]:=(f[x]+((f[e[i]]*p[x]) mod INF*reverse(p[e[i]]+1)) mod INF) mod INF;  //更新子树上集合的毒瘤值之和
        end;
        i:=next[i];
    end;
end;

begin
    readln(n,flag);
    for i:=1 to n-1 do begin 
        readln(x,y);
        addedge(x,y);
    end;
    for i:=1 to n do if flag=0 then a[i]:=1 else a[i]:=i;
    dp(1,0);
    writeln(f[1]);  //答案即为整棵树上集合的毒瘤值之和
end.
```



------------


```cpp
#include<bits/stdc++.h>
#define INF 100000007
#define M 2000001
typedef long long ll;
using namespace std;

struct Edge{
    int to,next;
}e[M];

int head[M], n, t = 0;
ll f[M], p[M], a[M];

ll Exgcd(ll p, ll q, ll &x, ll &y) {  //扩展欧几里得
    if (q == 0) {
        x = 1,y = 0; 
        return p;
    }
    ll res = Exgcd(q, p%q, x, y);
    int tmp = x;
    x = y;
    y = tmp-p/q*y;
}

ll Reverse(ll x){  //求关于100000007的逆元
    ll res = 0,tmp = 0;
    Exgcd(x,INF,res,tmp);
    res = (res%INF+INF) % INF;
    return res;
}
    
void AddEdge(int x, int y){  //前向星建边
    e[++t] = (Edge){y, head[x]}; head[x] = t;
    e[++t] = (Edge){x, head[y]}; head[y] = t;
}

void DP(int x, int fa){  //树形DP
    p[x] = 1; f[x] = a[x];
    for (int i = head[x]; i; i = e[i].next){
        if (e[i].to!=fa) {
            DP(e[i].to, x); (p[x] *= p[e[i].to]+1) %= INF;  //遍历子树并更新点x的子集数量
        }
    }
    for (int i = head[x]; i; i = e[i].next){
        if (e[i].to!=fa) {
            (f[x] += ((f[e[i].to]*p[x]) % INF) * (Reverse(p[e[i].to]+1) % INF)) %= INF;  //更新子树上集合的毒瘤值之和
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    int flag;
    cin >> n >> flag;
    for (int i=1; i<n; i++) {
        int x,y;
        cin >> x >> y;
        AddEdge(x,y);
    }
    for (int i=1; i<=n; i++){
        if (!flag) a[i] = 1; else a[i] = i;
    }
    DP(1,0);
    cout << f[1] << endl;  //答案即为整棵树上集合的毒瘤值之和
    return 0;
}
```

---

## 作者：Dioretsa (赞：6)

我们规定：
- $f_i$ 为以 $i$ 为根节点的子树中所有毒瘤集的毒瘤指数之和。
- $g_i$ 为以 $i$ 为根节点的子树中毒瘤集的个数。
- $w_i$ 为节点 $i$ 的毒瘤指数。

假设节点 $u$ 有两个子节点 $a$ 和 $b$，则**以 $a$ 为根节点的子树中所有毒瘤集都可以和以 $b$ 为根节点的子树中所有毒瘤集互相组合**，那么可以得到：
- $f_u=f_a\times g_b+f_b\times g_a+f_a+f_b$
- $g_u=g_a\times g_b+g_a+g_b$

于是，规定 $u$ 为 $v$ 的父亲。我们可以得出状态转移方程：
- $f_u=f_u\times g_v+f_v\times g_u+f_u+f_v$
- $g_u=g_u\times g_v+g_u+g_v$

但是，别忘了节点 $u$ 本身也可以作为一个毒瘤集。我们只需要在最后加上即可：
- $f_u=f_u+w_u$
- $g_u=g_u+1$

除此之外，我们还需要注意取模。

代码如下：
```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
#define mod 100000007
using namespace std;
int n,T;
long long w[MAXN],f[MAXN],g[MAXN];
vector <int> tree[MAXN];
void dfs(int u,int father){
	for(int i=0;i<=tree[u].size()-1;i++){
		int v=tree[u][i];
		if(v==father) continue;
		dfs(v,u);
		f[u]=(f[u]*g[v]+f[v]*g[u]+f[u]+f[v])%mod;
		g[u]=(g[u]*g[v]+g[u]+g[v])%mod;
	}
	f[u]=(f[u]+w[u])%mod;
	g[u]=(g[u]+1)%mod;
}
int main(){
	scanf("%d%d",&n,&T);
	if(T==0) for(int i=1;i<=n;i++) w[i]=1;
	if(T==1) for(int i=1;i<=n;i++) w[i]=i;
	for(int i=1;i<=n-1;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		tree[x].push_back(y);
		tree[y].push_back(x);
	}
	dfs(1,0);
	printf("%lld\n",f[1]);
	return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# P5007 题解
[题目传送门](https://www.luogu.com.cn/problem/P5007)

~~一眼树形 dp~~

我们以 $1$ 为根，设 $dp_x$ 为 $u$ 的子树中的答案、$dp2_x$ 为只考虑 $u$ 的子树，毒瘤集的数量。自底向上传递答案，最后的结果就是 $dp_1$。

从而我们可以得到转移的方法，遍历 $x$ 的每个儿子 $u$，$dp_x=dp_u\times dp2_x+dp_x\times dp2_u+dp_x+dp_u,dp2_x=dp2_x+dp2_u\times dp2_x+dp2_u$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 100000007;
long long n, k, sum, dp[1000001], dp2[1000001];
bool t;
vector <int> e[1000001];
void dfs(int x, int fa){
	for (auto u : e[x]){
		if (u == fa){
			continue;
		}
		dfs(u, x);
		dp[x] = dp[u] * dp2[x] + dp[x] * dp2[u] + dp[x] + dp[u];
		dp[x] %= mod;
		dp2[x] = dp2[x] + dp2[u] * dp2[x] + dp2[u];
		dp2[x] %= mod;
	}
	dp[x] += pow(x, t);
	dp[x] %= mod;
	dp2[x]++;
	dp2[x] %= mod;
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int u, v;
	cin >> n >> t;
	for (int i = 1; i < n; i++){
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	cout << dp[1];
	return 0;
}

```

---

## 作者：SunsetSamsara (赞：1)

## 前置知识

树形 dp

## 分析

dp 嘛，令 $f_i$ 表示 $i$ 的子树内的集合个数。

### 1. $Subtask\space2$

因为点权都是 $1$，所以 $Subtask\space2$ 相当于求毒瘤集个数。

首先发现对于一个点 $u$ 与它的儿子们 $S_u$：

$$f_u = \sum \limits_{\footnotesize \textsf{集合} \space v \subseteq S_u \space} \prod \limits_{i \in v_i} f_i$$

但是这个东西不好算，所以令 $g_i$ 表示前 $i$ 个儿子的集合个数，那么如果加入一个新的儿子$v$， 那么

$$g_{i + 1} = g_i f_v + g_i + f_v$$

### 2. $Subtask\space 3$

点权不是 $1$ 了，但是基本差不多。

对于节点 $u$ 的每个儿子 $v$，$f_u$ 初始化为 $w_u$，$g_u$ 初始化为 $0$

$$\begin{aligned}
	g_u &= g_u g_v + g_u + g_v\\
	f_u &= f_u g_v + f_v g_u + f_u + g_u
\end{aligned}$$

最后，记得 $g_u$ 要加上 $u$ 自己

所以就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
#define lld long long
using namespace std;
const int mod = 1e8 + 7;
int n, T;
int w[1000010];
struct edge {
	int to, nxt;
} es[3000010];
int ecnt;
int head[1000010];
void addedge(int fr, int to) {
	es[++ ecnt] = (edge){to, head[fr]};
	head[fr] = ecnt;
}
lld f[1000010];
lld g[1000010];
void dfs(int u, int fa) {
	for (int e = head[u], v; e; e = es[e].nxt)
		if ((v = es[e].to) != fa) {
			dfs(v, u);
			f[u] = (f[u] * g[v] % mod + f[v] * g[u] % mod + f[u] + f[v]) % mod;
			g[u] = (g[u] * g[v] % mod + g[u] + g[v]) % mod;
		}
	f[u] = (f[u] + w[u]) % mod;
	++ g[u];
}
int main() {
	scanf("%d%d", &n, &T);
	for (int i = 1; i <= n; ++ i) {
		if (T) w[i] = i;
		else w[i] = 1;
	}
	for (int i = 1, u, v; i < n; ++ i) {
		scanf("%d%d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
	dfs(1, 0);
	printf("%lld\n", f[1]);
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P5007)/[安利博客](https://www.cnblogs.com/ni-ju-ge/p/18591451)
## 思路
[树形 dp](https://oi-wiki.org/dp/tree/) 模版题。

设 $dp_i$ 为 $pos$ 的结果，$dp2_i$ 为只考虑 $pos$ 子树时，毒瘤集的数量。

可得：\
$dp_i=dp_{i}\times dp2_{son}+dp_{son}\times dp2_{i}+dp_i+dp_{son}$\
$dp2_i=dp2_{i}\times dp2_{son}+dp2_{i}+dp2_{son}$

用深搜来更新 $dp$ 数组即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=100000007;
vector<int>g[1140000];
long long dp[1140000],dp2[1140000],n,w[1140000],x,y,key;
void dfs(int pos,int f) {
	for (int i=0; i<g[pos].size(); i++) {
		int t=g[pos][i];
		if (t!=f) {
			dfs(t,pos);
			dp[pos]=(dp[t]*dp2[pos]+dp[pos]*dp2[t]+dp[pos]+dp[t])%mod;
			dp2[pos]=(dp2[pos]+dp2[t]*dp2[pos]+dp2[t])%mod;
		}
	}
	dp[pos]=(long long)(pow(pos,key)+dp[pos])%mod;
	dp2[pos]=(dp2[pos]+1)%mod;
	return;
}
int main() {
	cin>>n>>key;
	for(int i=1; i<n; i++) {
		cin>>x>>y;
		g[y].push_back(x);
		g[x].push_back(y);
	}
	dfs(1,0);
	cout<<dp[1];//最后的答案是 dp[1]
}
```

---

## 作者：wzc6666 (赞：0)

## 1 问题

题目大意:

定义一棵树内的集合毒瘤集，其中**任意两个元素**没有**祖先**与**后代**关系。

也就是说，任意一个点为的**子树内不会有其他点**。

求所有毒瘤集内点权求和，模上 $10^8+7$。

## 2 考虑暴力

可以直接枚举子集，判断是否合法然后求和。

时间复杂度 $O(2^n)$。

## 3 优化暴力-树形 dp

暴力慢就慢在要枚举每种情况，我们如果能通过子问题直接转移呢。

本题的数据结构是一棵树，可以考虑树形 dp。

## 4 状态设置

本文要求整棵树毒瘤集内点权求和，我们考虑子问题，当然是先考虑**子树**。

我们就可以设 $dp_{i}$ 为以 $i$ 为根的子树中毒瘤集的点权和。

为了方便计算，我们还可以设 $cnt_{i}$ 为以 $i$ 为根的子树中的毒瘤集数量。

## 5 状态转移

 **（1）先考虑当前点 $i$ 只有一个儿子节点 $j_{1}$ 的情况。**

我们**分情况讨论**:

情况一，不取 $i$ 点，点权和为 $dp_{j_{1}}$ ，毒瘤集数为 $cnt_{j_{1}}$。

情况二，取 $i$ 点，$i$ 点为子树的根，取完之后子节点不能再取，故点权和为 $w_{i}$ ，即 $i$ 的点权。

而毒瘤集数显然为 $1$ ，即 $i$ 本身一个点。

综上，此时状态转移方程为:

**$dp_{i} = dp_{j_{1}}+w_{i},cnt_{i} = cnt_{j_{1}}+1$**。

**（2）假如i还有一个儿子节点 $j_{2}$。**

考虑我们能不能直接用 $j_{1}$ 更新完 $i$，再用 $j_{2}$ 更新 $i$。

我们可以发现，无论子节点怎么变，$i$ 节点本身的毒瘤集只有一个。

所以在 $j_{1}$ 更新 $i$ 时，我们先留着 $w_{i}$ 不加到 $dp_{i}$ 上，等 $i$ 的所有儿子节点处理完后再加上即可。

我们设 $j_{1}$ 已经更新完成，此时 $dp_{i} = dp_{j_{1}},cnt_{i} = cnt_{j_{1}}$。

考虑 $j_{2}$ 怎么更新 $i$，方法也可以参考上文的分情况讨论。

情况一，只选 $j_{1}$ 子树中的毒瘤集，其实这个已经分析完了。
点权和 $dp_{j_{1}}$，毒瘤集数 $cnt_{j_{1}}$。

情况二，只选 $j_{2}$ 子树中的毒瘤集，同上。

点权和 $dp_{j_{2}}$，毒瘤集数 $cnt_{j_{2}}$。

情况三，两颗子树都取，这个是本题最难点。

$cnt$ 终于要出场了。

这种情况集合数为多少，**$cnt_{j_{1}}\times cnt_{j_{2}}$**，这个从 $cnt$ 的定义出发，是显然的。

但是这里有个性质，$dp_{j_{1}}$ 其实隐含着 $j_{1}$ 子树中所有毒瘤
集的条件，因为 $dp_{j_{1}}$ 是 $j_{1}$ 子树中所有毒瘤集求和。

我们对于每个 $j_{2}$ 子树中的集合，都把 $dp_{j_{1}}$ 复制一遍。

得 $dp_{j_{1}}\times cnt_{j_{2}}$。

接下来就是本篇题解的精髓，这个操作的实质是什么？

就是对于每个组合后的毒瘤集，都加上其中来自 $j_{1}$ 子树的点的点权。

（温馨提示，为了语言简洁，以下的毒瘤集称为集合）

是不是有点蒙，再来理解一下，对于每个新的集合，是不是**一个 $j_{1}$ 中集合并上 $j_{1}$ 中的集合**。

我们吧 $dp_{j_{1}}$ 拆开为$ n $个集合中的点权和 ${v_{1},v_{2}\dots v_{n}}$。

每一个 $j_{1}$ 集合都要并上每一个 $j_{2}$ 集合。

**即 $v_{1}\times cnt_{j_{2}}+v_{2}\times cnt_{j_{2}} \dots v_{n}\times cnt_{j_{2}}$**。

将 $cnt_{j_{2}}$ 提出，剩下括号里的就是 $dp_{j_{1}}$。

但是，这够吗，只是算上了新集合中来自 $j_{1}$ 子树的子集点权和。

我们可以参照上面做法，我们再给合并后的集合加上来自 $j_{2}$ 子树的点权。

即 $dp_{j_{2}}\times cnt_{j_{1}}$。

得状态转移方程(已经将 $dp_{j_{1}}$,$cnt_{j_{1}}$ 替换为 $dp_{i}$,$cnt_{i}$ )。

$dp_{i} = dp_{i}\times cnt_{j_{2}}+dp_{j_{2}}\times cnt_{i}+dp_{i}+dp_{j_{2}}$。

$cnt_{i} = cnt_{i}\times cnt_{j_{2}}+cnt_{i}+cnt_{j_{2}}$。

至此，算法已成。

但是我们还要特判 $i$ 的第一个儿子？

不用！我们尝试将第一个儿子的情况带入。

此时 $dp_{i}$，$cnt_{i}$ 均等于 $0$。

得此时状态转移方程：

$dp_{i} = dp_{j_{1}},cnt_{i} = cnt_{j_{1}}$。

跟上面一样了，这一个 for 循环就解决了。

别忘了把i点本身加上，别忘了模数是 $10^8+7$。

每个点都遍历到正好一次，时间复杂度显然 $O(n)$。

**附代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MOD = 100000007;
int n,T;
int w[2333333],vis[2333333];
long long dp[2333333],cnt[2333333];
vector<int> a[2333333];
void dfs(int x){
	for(int i = 0;i<a[x].size();i++){
		int h = a[x][i];
		if(!vis[h]){
			vis[h] = true;
			dfs(h);
			dp[x] = (dp[x]*cnt[h]+dp[h]*cnt[x]+dp[x]+dp[h])%MOD;
			cnt[x] = (cnt[x]*cnt[h]+cnt[x]+cnt[h])%MOD;
		}
	}
	cnt[x]+=1;
	dp[x]+=w[x];
	dp[x]%=MOD;
	return;
}
int main(){
	cin>>n>>T;
	for(int i = 1;i<=n;i++){
		if(T==0){
			w[i] = 1;
		}else{
			w[i] = i;
		}
	}
	for(int i = 1;i<n;i++){
		int u,v;
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	vis[1] = true;
	dfs(1);
	cout<<dp[1];
	return 0;
}

```


## 6 后记

这真是一道**简**（毒）**单**（瘤）的题，但是确实适合新手练习树形 dp。

大多数题解只给出结论，但是并没有教会我们结论是怎么想出来的。

其实，所有的结论都不是突然想出的。

像是分类讨论，数学分析这些技巧，还有试错才是解题的常态。

所有考场上思维好的神犇都是经过练习的。

最后祝大家 AKIOI。

---

## 作者：songhongyi (赞：0)

题意：定义一个有点权的有根树上的毒瘤集为满足任意两个节点不存在祖先—后代关系的集合，求所有毒瘤集的点权和的和



设以 $x$ 为根的子树的毒瘤集的和为 $f_x$，毒瘤集个数为 $g_x$，那么我们先考虑毒瘤集如何选择，显然对于某个点，只有：

* 只选这个点 （这个与其儿子无关，可以单独处理，所以下面暂时不统计这种情况）
* 选若干个子树

我们先考虑第一个儿子 $son_1$，则会有 $f_x=f_{son},g_x=g_{son}$。

加入现在来了第二个儿子 $son_2$，我们分情况考虑会对 $f$ 和 $g$ 的贡献。

| 情况           | 对 $f$ 的贡献                                       | 对 $g$ 的贡献              |
| -------------- | --------------------------------------------------- | -------------------------- |
| 只选第一个儿子 | $f_{son_1}$                                         | $g_{son_1}$                |
| 只选第二个儿子 | $f_{son_2}$                                         | $g_{son_2}$                |
| 同时选两个儿子 | $f_{son_1}\cdot g_{son_2}+f_{son_2}\cdot g_{son_1}$ | $g_{son_1}\cdot g_{son_2}$ |

也就是，$f_x=f_{son_1}\cdot g_{son_2}+f_{son_2}\cdot g_{son_1}+f_{son_1}+f_{son_2}$，$g_x=g_{son_1}\cdot g_{son_2}+g_{son_1}+g_{son_2}$

现在我们已经统计完了 $k$ 个儿子，来了第 $k+1$ 个儿子，我们把前 $k$ 个视为一个整体，注意到它与第 $k+1$ 个儿子也有与上面类似的三种关系，即选前 $k$ 个，选第 $k+1$ 个，和同时选这两个。

所以我们便可以按照上面那个式子遍历所有儿子了（当然初始时是 $f_x=g_x=0$）。

注意到还没有讨论到只选 $x$ 的情况，所以在刚刚求出的基础上，$f_x$ 要加上 $x$ 的点权，$g_x$ 要加 $1$。

注意乘法的地方可能爆 `int` ，还有注意模数是 $10^8+7$ 而非 $10^9+7$。

注意到完全没有用到点权是 $x$ 的性质，所以这个算法完全可以适用于任意点权的情况。

代码如下：

```cpp
//
// Problem: P5007 DDOSvoid 的疑惑
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5007
// Memory Limit: 500 MB
// Time Limit: 1000 ms

#include <iostream>
#include <vector>
using namespace std;
vector< int > edges[ 1000010 ];
long long int a[ 1000010 ]; //点权
long long int f[ 1000010 ], g[ 1000010 ]; // f 与 g
const long long int pmod = 100000007; 
void dfs( int x, int fa )
{
    for ( auto i : edges[ x ] ) //遍历所有儿子
    {
        if ( i == fa )
        {
            continue;
        }
        dfs( i, x );
        f[ x ] = ( f[ x ] * g[ i ] + f[ i ] * g[ x ] + f[ x ] + f[ i ] ) % pmod;
        g[ x ] = ( g[ x ] * g[ i ] + g[ x ] + g[ i ] ) % pmod;  //按照式子转移
    }
    f[ x ] = ( f[ x ] + a[ x ] ) % pmod; 
    g[ x ]++; //加上只选自己的情况
}
int main()
{
    int n;
    bool t;
    cin >> n >> t;
    for ( int i = 1; i < n; i++ )
    {
        int u, v;
        cin >> u >> v;
        edges[ u ].push_back( v );
        edges[ v ].push_back( u );
        if ( t )
        {
            a[ i ] = i;
        }
        else
        {
            a[ i ] = 1;
        } 
    }
    if ( t )
    {
        a[ n ] = n;
    }
    else
    {
        a[ n ] = 1;
    }//按照题目格式存点权
    dfs( 1, 0 );
    cout << f[ 1 ] << endl;
}
```



---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
很明显通过标签发现是树形 DP。我们令 $dp_i$ 为子树 $i$ 毒瘤集的价值之和，$c_i$ 为为子树 $i$ 毒瘤集的个数。通过题面易得状态转移方程为 
$$
\begin{cases}
dp_i=dp_i\times c_j+dp_j\times c_i+dp_i+c_i\\
c_i=c_i\times c_j+c_i+c_j
\end{cases}
$$
复杂度是线性的。
## 代码
[AC 记录和代码](https://www.luogu.com.cn/record/193177057)

---

