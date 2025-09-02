# [LnOI2019] Abbi并不想研学

## 题目背景

题目提供者：XuKaFy

## 题目描述

【原版题目】

给定一颗$n$个节点的树，树的叶节点全部是数字，非叶节点全部是符号`+`或者`*`。

请先对该树进行树链剖分。注意：若出现子树大小相同的情况，请选择编号较小的子节点作为重儿子。

一个节点的权值这样计算：若该节点为叶节点，数值即为节点数值；若该节点非叶节点，则该点的权值为【【【该点的【所有不在该点所在重链上】的子节点】所在重链的所有节点权值】相`+`或者相`*`的结果（操作取决于该节点的符号）】。

另一种表示方式是：设某一节点$i$的儿子集合为$D_{i}$，节点$i$的父亲为$F_{i}$，节点$i$的所在重链节点集合为$P_{i}$。

我们设：
$$Charge_{i}=\cup_{k\in D_{i},\ k\not\in P_{i}}P_{k}$$

令$C_{i}$为这个节点的符号，这个节点的权值就是：
$$
V_{i}=
\begin{cases}
\sum_{j\in Charge_{i}}V_{j} &C_{i}=`+'\\
\prod_{j\in Charge_{i}}V_{j} &C_{i}=`\times'
\end{cases}  
$$

数据不保证每一个非叶节点都有至少一个非链上儿子，若没有合法的儿子则忽略该节点。

你需要支持这三种操作：

- $1$.改变某一叶节点的数值；

- $2$.改变某一非叶节点的符号为`+`或者`*`；

- $3$.查询某一节点所在重链所有节点权值相`+`与相`*`的值。

为防止溢出，请将所有权值$mod\ 99991$。

## 说明/提示

对于$30\%$的数据，$1≤n,m≤1000$。

对于$100\%$的数据，$1≤n,m≤10^{6}, 1≤V_{i}<99991$。

**数据保证任何时刻树上没有权值为$0$的节点。**

## 样例 #1

### 输入

```
8 5
1 2 3 3 2 2 7
1 0 1 3 4 5 0 6
3 1
2 2
3 1
1 4 1
3 1```

### 输出

```
18 132
37 360
35 120```

# 题解

## 作者：wind_whisper (赞：4)

## $\text{Foreword}$
~~一道被洛谷遗忘的闹鬼题。~~  
第一眼：ddp？看一眼通过人数：怕不是道神题吧...  
开始使用大脑：...这暴力跳重链更新不就是 $O(n\log n)$ 吗...  
再看看通过人数...我一定是哪里假了...  
再想想我的做法...哪里假了啊...写写试试？  

提交...过了...  
？？？  
连题解都没有？？那我水一篇吧...  
## $\text{Solution}$
总所周知，树剖每个节点到根的重链个数严格不超过 $\log n$ 的。  
所以对于每个点维护其 $charge_x$ 集合内所有点点权的乘积与加和，再对每个链头维护链上所有点点权的乘积与加和，修改的时候暴力维护即可。  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
#include<string>
using namespace std;
#define ll long long
#define ull unsigned ll
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")

inline ll read() {
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
const int N=1e6+100;
const int mod=99991;

bool mem1;

inline ll ksm(ll x,ll k){
  ll res(1);
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}

int n,m,k;

vector<int>e[N];
ll mul[N],sum[N],cur[N],ori[N];
ll top_mul[N],top_sum[N],ni[N];
int top[N],fa[N],siz[N],hson[N];
int a[N];
void dfs1(int x,int f){
  fa[x]=f;
  siz[x]=1;
  for(int to:e[x]){
    if(to==f) continue;
    dfs1(to,x);
    siz[x]+=siz[to];
    if(siz[to]>siz[hson[x]]||(siz[to]==siz[hson[x]]&&to<hson[x])) hson[x]=to;
  }
  return;
}
bool tag[N];
void dfs2(int x,int tp){
  top[x]=tp;
  mul[x]=1;
  if(x==top[x]) top_mul[x]=1;
  if(hson[x]) dfs2(hson[x],tp);
  for(int to:e[x]){
    if(to==hson[x]) continue;
    dfs2(to,to);
  }
  if(e[x].empty()) cur[x]=a[x],tag[x]=1;
  else cur[x]=a[x]?mul[x]:sum[x];
  if(!tag[x]) return;
  if(top[x]>1){
    mul[fa[top[x]]]=mul[fa[top[x]]]*cur[x]%mod;
    sum[fa[top[x]]]=(sum[fa[top[x]]]+cur[x])%mod;
    tag[fa[top[x]]]=1;
  }
  top_mul[top[x]]=top_mul[top[x]]*cur[x]%mod;
  top_sum[top[x]]=(top_sum[top[x]]+cur[x])%mod;
  //printf("x=%d cur=%lld\n",x,cur[x]);
  return;
}
inline void upd(int x){
  if(!tag[x]) return;
  ori[x]=cur[x];
  if(e[x].empty()) cur[x]=a[x];
  else cur[x]=a[x]?mul[x]:sum[x];
  top_mul[top[x]]=top_mul[top[x]]*ni[ori[x]]%mod;
  top_sum[top[x]]=(top_sum[top[x]]+mod-ori[x])%mod;
  top_mul[top[x]]=top_mul[top[x]]*cur[x]%mod;
  top_sum[top[x]]=(top_sum[top[x]]+cur[x])%mod;

  if(top[x]>1){
    mul[fa[top[x]]]=mul[fa[top[x]]]*ni[ori[x]]%mod;
    sum[fa[top[x]]]=(sum[fa[top[x]]]+mod-ori[x])%mod;
    mul[fa[top[x]]]=mul[fa[top[x]]]*cur[x]%mod;
    sum[fa[top[x]]]=(sum[fa[top[x]]]+cur[x])%mod;
    upd(fa[top[x]]);
  }
}

bool mem2;
signed main() {
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  for(int i=1;i<mod;i++) ni[i]=ksm(i,mod-2);
  n=read();m=read();
  for(int i=2;i<=n;i++) e[read()].push_back(i);
  for(int i=1;i<=n;i++) a[i]=read();
  dfs1(1,0);
  dfs2(1,1);
  for(int i=1;i<=m;i++){
    int op=read(),x=read();
    if(op==1){
      int w=read();
      a[x]=w;
      upd(x);
    }
    else if(op==2){
      a[x]^=1;
      upd(x);
    }
    else printf("%lld %lld\n",top_sum[top[x]],top_mul[top[x]]);
  }
  return 0;
}
/*
  3 1
  2 3 3 1
  1 1
*/
```


---

## 作者：OIer_ACMer (赞：2)

~~呜呜呜，我再也不想写树剖了！~~

------------
这道题由于乘法部分本人实在不会想，部分题解参考[大佬思路](https://www.luogu.com.cn/blog/wind-whisper/solution-p5499)。

------------
## 大致思路：
这道题本身就是个树剖加上快速幂，本人今天就来试着做了一下这道题~~尽管乘法部分是找大佬学的~~，但这并不影响我今天“愉悦”的心情~~说白了就是学不学都一样菜~~。

首先，让我们观察题目，题目要我们满足三种操作：

1. 改变某一叶节点的数值。

2. 改变某一非叶节点的符号为加号或者乘号。

3. 查询某一节点所在重链所有节点权值相加与相乘的值。

同时，我们根据之前所学过的知识，可以知道：**这道题是一道在树上做操作的线段树的模板题**！俗称，树链剖分。之后，我么就要考虑怎么用树链剖分实现这些操作。

我们先用 dfs 深度优先搜索找出这棵树上的**重儿子**，也就是各个重链的链头，并将以 $x$ 为父亲节点的重儿子储存在数组 $beson_i$ 里面，同时，我们要注意一个地方：**若出现子树大小相同的情况，请选择编号较小的子节点作为重儿子**。这个条件很隐晦，稍微不注意可能就直接大红大紫~~就像我一样~~。

接着，我们就根据得到的重儿子数组进行维护各个重链的和与乘积，由于题目的难点主要是更改加号和乘号，所以我们着重看符号的修改，同时数的修改也是必不可少的。

首先，我们假设：我们在 $x$ 节点的数被更新了，首先受影响的是他自己，其次就是这个点所在重链的和与乘积，所以我们要维护链上的和与乘积。而对于链顶节点的父亲节点 $u$ 来说，$x$ 节点**是属于一条重链的**，所以由于 $x$ 节点权值被修改，所以连带着 $u$ 的点权也需要进行修改，然后由于 $u$ 点权修改，**连带着又要重复上面的修改，直接递归直到根节点即可**。

然后，我们来处理第二种操作：修改符号。由于符号修改会影响到整个除重链以外的节点的乘积或和的结果，所以我发直接记录点权的变化~~除非你硬是不怕 TLE 猛冲我可不管~~。因此，为了解决上述情况，我们可以**同时维护两种符号下各个点的乘积与和，要修改时一起修改**，至于修改操作和前面并无他样，但是要注意点权更改的值不一样了。

------------
## 警钟敲烂：
注意注意！！！在做第二种操作时，点权修改涉及到乘号的修改是会爆 int 的！不开 long long 见祖宗！！！

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int mod = 99991;
int qp(int n, int m)
{
    int ans = 1;
    while (m)
    {
        if (m & 1)
        {
            ans *= (n % mod);
            ans %= mod;
        }
        n *= (n % mod);
        n %= mod;
        m >>= 1;
    }
    return ans % mod;
}
const int N = 1e6 + 6;
const int M = 1e6 + 6;
int n, m, k;
int head[N], cnt;
struct node
{
    int to, next;
} edge[N];
// vector<int> edge[N];
void add(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
} 
int chengji[N], sum[N], cur[N], ori[N];
int headcheng[N], headsum[N], ni[N];
int top[N], fa[N], siz[N], beson[N];
int a[N];
void findbeson(int x, int fath)
{
    fa[x] = fath;
    siz[x] = 1;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (y == fath)
        {
            continue;
        }
        findbeson(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[beson[x]] || (siz[y] == siz[beson[x]] && y < beson[x])) // 判断重儿子，同时满足题目要求的“如果两个儿子子树节点数相同则编号小的为重儿子”。
        {
            beson[x] = y;
        }
    }
    return;
}
bool lazy[N];
void dfs(int x, int topp)
{
    // cout << "beson[" << x << "]=" << beson[x] << endl;
    top[x] = topp;
    // cout << "top[" << x << "]=" << top[x] << endl;
    chengji[x] = 1;
    if (x == top[x])
    {
        headcheng[x] = 1;
    }
    if (beson[x])
    {
        dfs(beson[x], topp);
    }
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (y == beson[x])
        {
            continue;
        }
        dfs(y, y);
    }
    if (/*edge[x].empty()*/!head[x])
    {
        // cout << "重置\n";
        cur[x] = a[x], lazy[x] = 1;
    }
    else
    {
        cur[x] = a[x] ? chengji[x] : sum[x];
    }
    if (!lazy[x])
    {
        return;
    }
    if (top[x] > 1)
    {
        chengji[fa[top[x]]] = chengji[fa[top[x]]] * cur[x] % mod;
        sum[fa[top[x]]] = (sum[fa[top[x]]] + cur[x]) % mod;
        lazy[fa[top[x]]] = 1;
    }
    headcheng[top[x]] = headcheng[top[x]] * cur[x] % mod;
    headsum[top[x]] = (headsum[top[x]] + cur[x]) % mod;
    return;
}
void updata(int x)
{
    if (!lazy[x])
    {
        return;
    }
    ori[x] = cur[x];
    if (/*/*edge[x].empty()*/!head[x])
    {
        // cout << "重置\n";
        cur[x] = a[x];
    }
    else
    {
        cur[x] = a[x] ? chengji[x] : sum[x];
    }
    headcheng[top[x]] = headcheng[top[x]] * ni[ori[x]] % mod;
    headsum[top[x]] = (headsum[top[x]] + mod - ori[x]) % mod;
    headcheng[top[x]] = headcheng[top[x]] * cur[x] % mod;
    // cout << "headcheng[" << "top[" << x << "]]=" << headcheng[top[x]] << ' ' << "cur[" << x << "]=" << cur[x] << endl;
    headsum[top[x]] = (headsum[top[x]] + cur[x]) % mod;
    if (top[x] > 1)
    {
        chengji[fa[top[x]]] = chengji[fa[top[x]]] * ni[ori[x]] % mod;
        sum[fa[top[x]]] = (sum[fa[top[x]]] + mod - ori[x]) % mod;
        chengji[fa[top[x]]] = chengji[fa[top[x]]] * cur[x] % mod;
        sum[fa[top[x]]] = (sum[fa[top[x]]] + cur[x]) % mod;
        updata(fa[top[x]]);
    }
}

signed main()
{
    for (int i = 1; i < mod; i++)
    {
        ni[i] = qp(i, mod - 2);
    }
    n = read();
    m = read();
    for (int i = 2; i <= n; i++)
    {
        int aa = read();
        // edge[aa].push_back(i);
        add(aa, i);
    }
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    findbeson(1, 0);
    dfs(1, 1);
    for (int i = 1; i <= m; i++)
    {
        int op = read(), x = read();
        if (op == 1)
        {
            int w = read();
            a[x] = w;
            updata(x);
        }
        else if (op == 2)
        {
            a[x] ^= 1;
            updata(x);
        }
        else
        {
            cout << headsum[top[x]] << ' ' << headcheng[top[x]] << endl;
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/121719366)

---

## 作者：hmya (赞：1)

写篇题解纪念一下。

首先我们发现按照他这个模式，只有轻儿子才会被统计上去，什么意思呢。

我们把思路逆转一下，也就是只有遇到轻边才会贡献上去。

我们把一个值修改为 $val$，只需要这个点往上爬重链，每次遇到轻边就上传贡献。

然后就是转换符号，直接暴力计算显然是不合理的，直接就挂飞了。

那我们就对于每个点，幻想出他的符号是加号和乘号两种情况时的权值，然后到时候直接在换符号的点上换点权就可以了。

对于查询，就是一整条重链的答案对吧。

做到这里，我直接放弃思考，去码树剖套线段树，然后狠狠超时，查了一天才发现 $\log^2n$ 会超时。

那我们怎么办呢，这很难搞啊。

实际上对于修改考虑这次修改造成的影响，然后对于当前重链整体把影响落到实处就好了。

然后就做完了。

[没有注释的 code1](https://www.luogu.com.cn/paste/ojglge5t)

[有注释的 code2](https://www.luogu.com.cn/paste/dhluf9rx)

最后再给几组 hack 数据。

[hack](https://www.luogu.com.cn/paste/kp29eesu)

---

## 作者：yizhiming (赞：1)

一开始没看懂题解，还以为胡了个新做法，写完才发现是一样的。。。

## 题面描述

这题的题面太难概述了，还是放个 [$Link$](https://www.luogu.com.cn/problem/P5499) 让读者自己看吧（

## 题面分析

这道题的点权计算方式很有意思，我们需要维护当前节点的点权，注意到查询操作是询问两种值，所以对于每个重链的链顶节点，都要维护这条链上点权和以及点权积，这两个操作仅需要一次树剖就可以很轻松的维护出来。

我们现在先来考虑第一种修改操作：

当一个节点 $u$ 的点权被更新了，会有哪些节点收到影响呢？首先节点 $u$ 本身点权会变，紧接着就会影响节点 $u$ 所在链的和以及积，所以我们还需要更新链顶的和与积值（允许我简称为这个）。而对于链顶节点的父亲节点 $x$ 来说，$u$ 节点是属于 $Charge_x$ 集合的，所以由于 $u$ 节点权值更改，所以连带着 $x$ 的点权也需要进行修改，然后由于 $x$ 点权修改，连带着又要重复上面的修改，直接递归直到根节点即可。

注意要考虑一个非叶子节点的权值是如何变化的。

由于第二种操作，导致我们不能只记录当前节点的权值，原因很简单，假设当前一个非叶节点的符号被修改，那么如果只记当前点权的话无法进行修改，除非再次遍历一遍其轻儿子，但是这样的话一个菊花图就能卡成平方。

所以我们要对于每个非叶节点，维护其两种符号下的不同点权，修改的时候一起修改即可。这个修改本质上和第一种操作修改是一样的，都是将一个节点的点权修改，注意一下点权是怎么变换的即可。

## Code

注意一下要取模，所以为了在更新积时将原点权的贡献删掉，要先预处理逆元，删掉原本的贡献相当于乘上逆元。

```cpp
#include<iostream>
#include<cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 2e6+5;
int Mod = 99991;
struct aa{
	int nxt,to;
}edge[N];
int head[N],tot,n,m;
void add(int u,int v){
	edge[++tot].nxt = head[u];edge[tot].to = v;head[u] = tot;
}
int fa[N],son[N],siz[N],top[N];
void dfs1(int u,int f){
	if(u<0||u>n){
		return;
	}
	fa[u] = f;
	siz[u] = 1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v = edge[i].to;
		if(v==f||v<0||v>n){
			continue;
		}
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]==siz[son[u]]){
			if(v<son[u]){
				son[u] = v;
			}
		}
		if(siz[v]>siz[son[u]]){
			son[u] = v;
		}
	}
}
int val[N],val1[N],val2[N],sum1[N],sum2[N];
int getval(int u){
	if(!son[u]){
		return val[u];
	}
	if(val[u]==0){
		return val1[u];
	}else{
		return val2[u];
	}
}
bool lefy[N],flgs[N];
int las[N];
void dfs2(int u,int t){
	if(u<0||u>n){
		return;
	}
	top[u] = t;
	if(!lefy[u]){
		val1[u] = val[u];
		val2[u] = val[u];
		sum1[u] = val[u];
		sum2[u] = val[u];
		las[u] =  val[u];
		flgs[u] = 1;
		return;
	}
	val1[u] = 0;val2[u] = 1;sum1[u] = 0;sum2[u] = 1;
	dfs2(son[u],t);
	sum1[u] = (sum1[u]+sum1[son[u]])%Mod;
	sum2[u] = (sum2[u]*sum2[son[u]])%Mod;
	sum1[u] = max(0ll,sum1[u]);
	sum2[u] = max(1ll,sum2[u]);
	int cnt = 0ll;
	int res1=0ll,res2=1ll;
	for(int i=head[u];i;i=edge[i].nxt){
		int now = edge[i].to;
		if(now==fa[u]||now==son[u]||now<0||now>n){
			continue;
		}
		dfs2(now,now);
		cnt++;
		res1 = (res1+sum1[now])%Mod;
		res2 = (res2*sum2[now])%Mod;
	}
	val1[u] = res1;
	val2[u] = res2;
	int res = getval(u);
	las[u] = res;
	if(!cnt){
		return;
	}
	flgs[u] = 1;
	sum1[u] = (sum1[u]+res)%Mod;
	sum2[u] = (sum2[u]*res)%Mod;
}
int inv[N],du[N];
void upd(int u){
	while(flgs[u]){
		int olds = las[u];
		las[u] = getval(u);
		int news = las[u];
		u = top[u];
		sum1[u] = (sum1[u]-olds+news+Mod)%Mod;
		sum2[u] = ((sum2[u]*inv[olds])%Mod*news)%Mod;
		if(u==1){
			break;
		}
		u = fa[u];
		val1[u] = (val1[u]-olds+news+Mod)%Mod;
		val2[u] = ((val2[u]*inv[olds])%Mod*news)%Mod;
	}
}
int opt,x,k;
signed main(){
	n = read();m = read();
	
	for(int i=2;i<=n;i++){
		x = read();
		add(x,i);
		lefy[x] = 1;
		du[x]++;
	}
	for(int i=1;i<=n;i++){
		val[i] = read();
	}
	inv[1] = 1;
	for(int i=2;i<Mod;i++){
		inv[i] = (Mod-Mod/i)*inv[Mod%i]%Mod;
		
	}
	dfs1(1,0);
	dfs2(1,1);
	while(m--){
		opt = read();x = read();
		if(opt==1){
			k = read();
			val[x] = k;
			upd(x);
		}else if(opt==2){
			val[x]^=1;
			upd(x);
		}else{
			cout<<sum1[top[x]]<<" "<<sum2[top[x]]<<"\n";
		}
	}
	return 0;
}
```

~~这么个简单题耗了我三天~~

---

