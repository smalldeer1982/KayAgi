# Swaps

## 题目描述

You are given an array of integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ). You can perform the following operation several (possibly, zero) times:

- pick an arbitrary $ i $ and perform swap $ (a_i, a_{a_i}) $ .

How many distinct arrays is it possible to attain? Output the answer modulo $ (10^9 + 7) $ .

## 说明/提示

In the first example, the initial array is $ [1, 1, 2] $ . If we perform the operation with $ i = 3 $ , we swap $ a_3 $ and $ a_2 $ , obtaining $ [1, 2, 1] $ . One can show that there are no other attainable arrays.

In the second example, the four attainable arrays are $ [2, 1, 4, 3] $ , $ [1, 2, 4, 3] $ , $ [1, 2, 3, 4] $ , $ [2, 1, 3, 4] $ . One can show that there are no other attainable arrays.

## 样例 #1

### 输入

```
3
1 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4
2 1 4 3```

### 输出

```
4```

## 样例 #3

### 输入

```
6
2 3 1 1 1 2```

### 输出

```
18```

# 题解

## 作者：樱雪喵 (赞：14)

## Description

给定长度为 $n$ 的序列 $a$，每次操作可以选定一个 $i$，并 $\operatorname{swap}(a_i,a_{a_i})$。求能通过某种操作顺序得到的不同序列数。

$n\le 10^6$。

## Solution

思路来自 [官方题解](https://codeforces.com/blog/entry/119902)。

考虑建图。对于每个 $i$，连边 $i \to a_i $。则构造出一个 $n$ 个点 $n$ 条边的图，且每个点有且仅有一条出边。

定义操作 $\operatorname{swap}(a_i,a_{a_i})$ 为“操作点 $i$”。观察对点 $i$ 进行操作后图的变化（不考虑环），发现原图从 $i\to a_i \to a_{a_i}$ 变为 $i\to a_{a_i},a_i\to a_i$。对于交换后不改变序列的情况，形如 $u\to v\to v$，则操作不合法。由于每次操作都对图的结构进行改动不好处理，我们换一种方式，对 $i \to a_i$ 这条边打个标记来表示对 $i$ 进行了一次操作。

假设当前局面的点 $i$，分为两种情况：

- 点 $i$ 存在一条入边被标记，那实际上的序列里 $i$ 已经是自环了，不能再操作；
- 点 $i$ 不存在入边被标记，那么我们顺着 $i$ 的出边走，直到找到**第一条未被标记**的边，把它打上标记。

完成操作后，对于一个给定的标记集合，可以用如下方式构造出实际序列：

- 若点 $i$ 存在入边被标记，$a_i=i$;
- 否则，$a_i$ 的实际值为 沿着 $i$ 的出边走，第一条未被标记的边 指向的点。

对边的标记集合进行计数。设每个点的入度为 $in_i$，且每个点至多有一条入边被标记，则总方案数为 $\prod\limits_{i=1}^n (in_i+1)$。

但不是所有满足这个条件的标记集合都是合法的。考虑图中存在环的情况，并不能构造出一种方案，使这个环的所有边都被标记。因为这个环在只剩一条边未被标记时，实际的序列就已经所有 $a_i=i$ 了。  
这同时启发我们发现，对于一个环只有一条边未标记的情况，无论哪条边不被标记，生成的序列都是一样的。那么对于长度为 $k$ 的环 $c_1,c_2,\dots,c_k$，恰有一条边未被标记的方案数有 $\sum\limits_{i=1}^k in_{c_i}$ 种，合法且不重复的方案数为：
$$\prod_{i=1}^k (in_{c_i}+1) -[(\sum_{i=1}^k in_{c_i})-1]-1=\prod_{i=1}^k (in_{c_i}+1) -\sum_{i=1}^k in_{c_i}$$

则总方案数为：

$$\prod_{\operatorname{cycles}}(\prod_{i=1}^k (in_{c_i}+1) -\sum_{i=1}^k in_{c_i})\cdot\prod_{\operatorname{other\ v}}(in_v+1)$$

```cpp
const int N=1e6+5,mod=1e9+7;
int n,a[N],in[N];
int ans=1,flag[N],tot,t[N],instk[N],vis[N];
void dfs(int now)
{
    if(vis[now]) return;
    vis[now]=1,instk[now]=1,t[++tot]=now;
    if(instk[a[now]])
    {
        int res=1,sum=0;
        for(int i=tot;i;i--)
        {
            flag[t[i]]=1;
            res=1ll*res*(in[t[i]]+1)%mod,sum=(sum+in[t[i]])%mod;
            if(t[i]==a[now]) break;
        }
        ans=1ll*ans*(res-sum)%mod;
    }
    else dfs(a[now]);
    tot--,instk[now]=0;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read(),in[a[i]]++;
    for(int i=1;i<=n;i++) dfs(i);
    for(int i=1;i<=n;i++) if(!flag[i]) ans=1ll*ans*(in[i]+1)%mod;
    printf("%d\n",(ans+mod)%mod);
    return 0;
}
/*
8
3 3 3 1 1 5 7 3
*/
```

---

## 作者：EuphoricStar (赞：11)

看到 $a_{a_i}$ 和 $a_i \in [1, n]$，果断连边 $i \to a_i$，得到内向基环森林。

那么每次相当于把 $a_i$ 变成自环，连边 $i \to a_{a_i}$。

但是每次操作都改变图的形态很不好办，考虑打标记。

每次 $\operatorname{swap}(a_i, a_{a_i})$，我们就把 $i \to a_i$ 的边打上标记。那么经过若干次操作后，$a_i$ 实际上是，不断跳出边，第一条没被打标记的边指向的点。

考虑把最终的 $a$ 一一对应到对边打标记的方案。每个点至多有一条出边被打标记，设点 $u$ 的入度为 $d_u$，方案数为 $\prod d_u + 1$。

但是我们发现，对于一个长度为 $k$ 的环，如果环上有 $k - 1$ 条边被标记，那整个环就都变成自环了。

有 $\sum\limits_{u \in \text{cycle}} d_u + 1$ 个方案对应最后环上的点全部变成自环（钦定一个点没有入边被标记或者有一条除环上边之外的入边被标记，或者整个环的边都被标记），减去 $\sum\limits_{u \in \text{cycle}} d_u$。因此最后答案为：

$$(\prod\limits_{u \in \text{cycle}} (d_u + 1) - \sum\limits_{u \in \text{cycle}} d_u) \prod\limits_{u \notin \text{cycle}} (d_u + 1)$$

[code](https://codeforces.com/problemset/submission/1863/223719107)

---

## 作者：spdarkle (赞：8)


简洁的题面，深邃的思想。

首先，一个经典的套路是：

> 对于序列中涉及到对于 $a_{a_i}$ 和 $a_i$ 进行操作的问题，一般可以考虑建立 $(i,a_i)$ 的内向基环树或者 $(a_i,i)$ 的外向基环树转化为图论问题。

我们建立 $(i,a_i)$ 的内向基环树，$swap(a_i,a_{a_i})\implies a'_i=a_{a_i},a'_{a_i}=a_i$。这等价于将 $a_i$ 改为自环，然后令 $i$ 的父亲变为 $a_i$ 的父亲。

让我们想想，这样操作是很复杂的。

如何简化操作，并且支持快速地查找到某个点的实际父亲？

先不考虑环，一棵树的情况怎么办？

**可以对被删除的边打标记，这样在删除了若干边之后，点 $x$ 的实际父亲是往上找的第一条未被标记的边的指向点**。

而为了对应自环的限制，则点 $x$ 最多只能有一个儿子到它的边被标记。

所以最终每个点有两种情况，第一种是有一个儿子到它的边被标记，第二种是没有。

方案数为 $in_{x}+1$。

那么这棵树的总方案是 $\prod_{i=1}^n(in_i+1)$

转为基环树？

可以发现，对于一个环而言，若有且仅有边 $(cir_i,cir_{i+1})$ 没有被标记，也等价于 $a'_{cir_i}=cir_{i}$。全部都被自环。

并且环不可以被全部标记。

容斥原理，钦定某条边不被标记且其他边都被标记，则方案数是该边端点的入度。

有 $-1+\sum_{i=1}^{num}in_{cir_{i}}$ 个方案重复了，且有一个方案不合法。

所以容斥后，环上的贡献是 $\prod_{i=1}^{num}in_{cir_i}-sum_{i=1}^{num}in_{cir_i}+1-1=\prod_{i=1}^{num}in_{cir_i}-sum_{i=1}^{num}in_{cir_i}$

然后在把其他不在环上的点 $i$ 的 $in_i+1$ 乘上去就行了。

对于每一个基环树的方案全部乘起来就好了。

```cpp
#define int long long
const int p=1e9+7;
#define N 2050500 
vector<int>g;
int dcc,vis[N],c[N],in[N],head[N],flag,tag,ver[N],nxt[N],tot,n,m,a[N],num,cir[N];
void ad(int u,int v){
	nxt[++tot]=head[u],ver[head[u]=tot]=v;
} 
void add(int u,int v){
	ad(u,v);ad(v,u);
}
void pai(int u){
	c[u]=dcc;g.push_back(u);
	for(int i=head[u];i;i=nxt[i]){
		int v=ver[i];
		if(!c[v])pai(v);
	}
}
int get(int u){
	num=0;g.clear();++dcc;pai(u);
	for(auto x:g)vis[x]=0;
	while(!vis[u])vis[u]=1,u=a[u];
	int v=a[u];cir[++num]=u;
	while(v!=u)cir[++num]=v,v=a[v];
	for(auto x:g)vis[x]=0;
	for(int i=1;i<=num;i++)vis[cir[i]]=1;
	int s=0,t=1;
	for(int i=1;i<=num;i++)t=t*(in[cir[i]]+1)%p,s+=in[cir[i]];
	t=(t-s+p)%p;
	for(auto x:g){
		if(!vis[x])t=t*(in[x]+1)%p;
	}
	return t;
}
signed main(){
	ios::sync_with_stdio(false);
	int ans=1,n;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];in[a[i]]++;add(i,a[i]);
	}
	for(int i=1;i<=n;i++)if(!c[i])ans=ans*get(i)%p;
	ans=(ans+p)%p;
	cout<<ans<<"\n"; 
}
```



---

## 作者：do_while_true (赞：6)

看成内向基环森林，操作 $u\to v$ 相当于让 $u$ 连向 $v$ 所连的点，$v$ 变成自环。发现如果一个点 $v$ 变成了自环，那么操作任意一个 $u\to v$ 都没有用。

从简单的情形出发，对于一个内向树（或者说环大小为 $1$ 的内向基环树），每次操作 $x\to fa_x$ 时，相当于让 $fa_x$ 变成一个自环，然后 $x$ 的父亲就变成了 $fa_{fa[x]}$，并且 $fa_x$ 其它子树往上连的边再也不能跨过 $fa_x$．于是想到用树链剖分去对应操作出来的一张图。对于一条树链，让链底连向链顶的父亲，非链底的节点都是自环。

于是每次操作 $x$ 的时候，如果 $x$ 是链底并且链顶的父亲还没有重儿子，那么将链顶到父亲的这条边设为重边，否则什么也不干（对应 $x$ 是自环或 $x$ 连向了一个自环）。于是这样完成了链剖分方案与一张合法图方案的双射。这里有个问题是根已经是自环了，所以不能它不能有重（zhong）边连下去。于是方案数就是除了根以外的度数 +1 之积 $\prod(d_i+1)$．

现在考虑环很大，依然想要让它去对应链剖分的情况。当环上全是重边的时候定义其表示环上所有点都是自环。

但是这个时候发现有计重的情况，当环上只有一条边不是重边的时候会出现这样的计重：

![](https://s1.ax1x.com/2023/09/06/pPsftj1.png)

环上点的入边轻重选取方案将所有左侧的这种情况减去即可，也就是减去 $\sum_{u\in circle}d_u$．所以答案就是 $\prod_{circle}(\prod_{u\in circle}(d_u+1)-\sum_{u\in circle}d_u)\prod_{u\notin circle}(d_u+1)$

---

## 作者：hfjh (赞：5)

# CF1863G. Swaps 题解

## 题意

给定长度为 $n$ 的序列 $a$，每次操作可以选定一个 $i$，并 $\operatorname{swap}(a_i,a_{a_i})$。求能通过某种操作顺序得到的不同序列数。

## 题解

### 套路总结：

> 序列涉及 $a_{a_i},a_i$ 的操作，一般转化为 $(i,a_i)$ 的基环树。

转化为边 $(i,a_i)$ 的基环树森林。

每次操作 $i$ 就是把 $a_i$ 变成自环，连边 $(i,a_{a_i})$。

![](https://cdn.luogu.com.cn/upload/image_hosting/r8jqgpyq.png)

最终序列和最终图是一一对应的，我们可以就在图上考虑。

当选出一个 $i$ 而 $a_i$ 是自环，对于这次操作是没有任何改变的，我们定义这是无效操作。

也就是说所有指向 $a$ 的点最多只能选出一个 $i$ 操作。

我们把操作 $(i,a_i)$ 看做对边 $(i,a_i)$ 打标记，也就是说对于每个点的入边最多被**标记一条**。

特别的，例如下图，我们每次对 $1$ 操作两次，看做对边 $1,2$ 打标记。

![](https://cdn.luogu.com.cn/upload/image_hosting/tunghzsg.png)

最终图的形态是：

- 若这个点有入边被标记，那么这个点指向自己

- 否则这个点向上指直到**第一条未被标记的边**。

所以最终图不同当且仅当标记不同。

设 $d_i$ 表示 $i$ 这个点入度为 $d_i$，最终方案数就是 ：$\prod_{i = 1}^n(d_i+1)$。

> 可以标记一条边有 $d_i$ 种，也可以不标记，就是 $d_i+1$。

但还没完，我们考虑一个环：

- 若是一个自环，那么不能有入边被标记。

- 若是一个大小为 $n$ 的环，那么环上最多有 $n-1$ 条边被标记，并且每一种选择都相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/2ftljpmk.png)

如图只有 $1,2$ 边被标记。

我们考虑枚举连向点 $i$ 的边不被标记，那么这个点还剩 $d_i$ 种选择（选择他的另外 $d_i - 1$ 边标记或者不标记）。

考虑环上每个边都可以不被标记，总方案数就是 $\sum_{i=1}^n d_i$。

这些方案得到的最终图是相同的，但是合法的，所以要加一种，减去 $(\sum_{i=1}^nd_i -1)$。

还有一种不合法的就是环上所有边都被标记，所以还要 $-1$。

总方案数就是

$$
\prod_{cycles}(\prod_{i\in cycle} (d_i + 1) - (\sum_{i\in cycle}d_i - 1)-1) \times \prod_{x\notin cycle}(d_i+1)
$$

---

## 作者：Bitaro (赞：2)

将 $i$ 与 $a_i$ 连边，可以发现图构成若干棵内向基环树。

考虑交换的含义与条件：对于有向边 $(u,v)$，交换的含义是删除 $(u,v)$，将 $v$ 的出边转移到 $u$ 上，将 $v$ 的出边变成自环。条件是，$v$ 的出边不是连向自己。

容易发现对于树上节点，至多只有一个儿子可以与其进行交换操作。可得当前节点为答案贡献入度加一，运用乘法原理将当前这部分乘起来。

考虑环上节点，有特殊情况。由于大小为 $sz$ 的环上如果进行了 $sz-1$ 次交换，那么剩下的一个点实际上也强制进行了交换，所以不存在 $sz-1$ 次交换的情况。打表发现非法的情况恰好就是环上所有点入度和，把环单独列出减去非法情况再用乘法原理即可。

下面是对结论的理解：对于进行交换的 $sz-1$ 个点，不会再有其他节点与它们进行交换。对于剩下的一个点，我们强制规定了环上的点不会与其进行交换，那么设其入度为 $deg$，则它交换的方案是 $deg-1$ 种，加上一种不交换的方案，总共 $deg$ 种。运用加法原理可得总方案数即为入度之和。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define pre(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=1e6+6,p=1e9+7;
int plu(int a,int b) { return a+b>=p?a+b-p:a+b; }
int mul(int a,int b) { return (1ll*a*b)%p; }
int n,ans,cnt;
array<int,N> a,in,his,vis,col;
stack<int,vector<int>> s;
array<vector<int>,N> cir;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin>>n;
  pre(i,1,n) cin>>a[i];
  pre(i,1,n) in[a[i]]++,his[a[i]]++;
  queue<int> q;
  pre(i,1,n) if(his[i]==0) q.push(i);
  int ans=1;
  while(!q.empty()) {
    int u=q.front();
    vis[u]=1;
    ans=mul(ans,in[u]+1);
    q.pop();
    his[a[u]]--;
    if(his[a[u]]==0) q.push(a[u]);
  }
  pre(i,1,n) {
    if(vis[i]==1) continue;
    if(col[i]==1) continue;
    int u=i,tot=1,sum=0;
    while(col[u]==0) {
      col[u]=1;
      tot=mul(in[u]+1,tot);
      sum=plu(in[u],sum);
      u=a[u];
    }
    tot-=sum;tot=((tot%p)+p)%p;
    ans=mul(ans,tot);
  }
  cout<<ans<<endl;
  
  return 0;
}
```


---

## 作者：Exber (赞：1)

> 给定长度为 $n$ 的序列 $a$，每次操作可以选定一个 $i$，并 $\operatorname{swap}(a_i,a_{a_i})$。求能通过进行任意次这种操作得到的不同序列数。
>
> $n\le 10^6$。 


不妨称能经过若干次操作得到的序列为合法序列。

看到这个操作形式可以想到建立一个 $n$ 个点的图 $G$ 且从 $i$ 向 $a_i$ 连一条有向边。那么 $G$ 一定是一棵内向基环树。

那么发现一次操作相当于：

![](https://www.ckjweb.tk/post-images/1695201087791.png)

那么对于一个固定的 $i$，操作若干次相当于：

![](https://www.ckjweb.tk/post-images/1695202077979.png)

设 $i$ 最后指向的点为 $p_i$，显然 $p_i$ 一定是 $i$ 的某个祖先。则不难发现 $G$ 中每个点会且仅会被一条 $[i,p_i)$ 的链（$i\to p_i$ 的去掉 $p_i$ 的路径）包含，那么每一个 $G$ 的链剖分方案都能对应一个合法序列（不一定是一一对应，一个合法序列有可能对应多个链剖分方案）：

![](https://www.ckjweb.tk/post-images/1695204211184.png)

设 $son_u=\sum\limits_{i=1}^n [a_i=u]$ 即 $u$ 的儿子个数，那么显然 $G$ 的链剖分方案个数就是 $\prod\limits_{i=1}^n son_i+1$ 即每个点可以选一个儿子的链接上或者不接。

对于树的情况，容易发现链剖分方案和合法序列一一对应。但是由于是基环树，所以会出现这种情况：

![](https://www.ckjweb.tk/post-images/1695208966470.png)

也就是绕了一圈回来了。

不难证明只有这种情况不合法，那么减掉这种链剖分的个数 $\sum\limits_{i=1}^n [i\in cir]son_{i}\times \prod\limits_{i=1}^n[i\notin cir](son_i+1)$ 即可（在环上的每个点都可以选择某个儿子的链接上再绕一圈，不在环上的点不影响）。

时间复杂度 $O(n)$，代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int S=1000005,p=1000000007;

int fra[S];
int n,a[S];
vector<int> g[S];
int ind[S];
int son[S],fa[S];
int siz[S],res[S],ans[S];

int fnd(int x)
{
	return fa[x]==x?x:fa[x]=fnd(fa[x]);
}

int main()
{
	fra[0]=1;
	for(int i=1;i<=S-3;i++) fra[i]=1ll*fra[i-1]*i%p;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) g[i].push_back(a[i]),ind[a[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++) if(ind[i]==0) q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int v:g[u]) if(--ind[v]==0) q.push(v);
	}
	for(int i=1;i<=n;i++) son[a[i]]++,fa[i]=i;
	for(int i=1;i<=n;i++) fa[i]=fnd(a[i]);
	for(int i=1;i<=n;i++) siz[i]=0,res[i]=ans[i]=1;
	for(int i=1;i<=n;i++)
	{
		int ri=fnd(i);
		if(ind[i]==0) res[ri]=1ll*res[ri]*(son[i]+1)%p;
		else siz[ri]+=son[i],ans[ri]=1ll*ans[ri]*(son[i]+1)%p;
	}
	int val=1;
	for(int i=1;i<=n;i++)
	{
		if(fa[i]!=i) continue;
		val=1ll*val*((ans[i]-siz[i])%p+p)%p*res[i]%p;
	}
	printf("%d\n",val);
	return 0;
}
```

---

## 作者：Leasier (赞：1)

$\operatorname{swap}(a_i, a_{a_i})$ 让我们想到**基环内向树**：考虑建图 $i \to a_i$，则每次操作相当于：

- 连边 $i \to a_{a_i}, a_i \to a_i$。
- 删除原有边 $i \to a_i, a_i \to a_{a_i}$。
- 此时 $a_i$ 将成为一个自环。

------------

改变图的形态使得问题不便考虑，我们尝试换一种描述：

- 每次从 $i$ 出发向前跳 $a$ 直到当前边 $j \to a_j$ 未被标记。
- **标记**边 $j \to a_j$。

我们尝试对标记后的图计数：

- 最终每个点的入边只会被标记**至多一条**。
- 设 $u$ 的入度为 $deg_u$，则 $u$ 的方案数为 $deg_u + 1$。

于是一个简单的想法就是将所有 $deg_u + 1$ 的积作为答案，但注意到这样在环上存在问题：

- 如果大小为 $k$ 的环上有至少 $k - 1$ 条边被标记，则这个环将成为**自环**。

考虑这种情况对应了多少种标记后的图：

- 环上每个点都有一条入边被标记：方案数为 $1$。
- 环上恰好一个点没有入边被标记：方案数为 $\displaystyle\sum_{u \in \operatorname{cycle}} deg_u$。

于是我们把每个联通块的树上和环上部分分开，把环上部分的方案数减去度数和即可。

时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

const int mod = 1e9 + 7;
int root[1000007], a[1000007], deg[1000007], dot[1000007], vis[1000007];
bool mark[1000007];
vector<int> v[1000007];

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		root[i] = i;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int get_root(int x){
	if (root[x] == x) return x;
	return root[x] = get_root(root[x]);
}

inline void merge(int x, int y){
	int x_root = get_root(x), y_root = get_root(y);
	if (x_root != y_root) root[x_root] = y_root;
}

int main(){
	int n = read();
	ll ans = 1;
	init(n);
	for (register int i = 1; i <= n; i++){
		a[i] = read();
		deg[a[i]]++;
		merge(i, a[i]);
	}
	for (register int i = 1; i <= n; i++){
		v[get_root(i)].push_back(i);
	}
	for (register int i = 1; i <= n; i++){
		if (get_root(i) == i){
			int size = v[i].size(), leaf = v[i][0];
			ll x = 1, y = 1, z = 0;
			for (register int j = 1; j < size; j++){
				if (deg[v[i][j]] == 0){
					leaf = v[i][j];
					break;
				}
			}
			for (register int j = 1; ; j++){
				if (vis[leaf] != 0){
					for (register int k = vis[leaf]; k < j; k++){
						mark[dot[k]] = true;
					}
					break;
				}
				dot[j] = leaf;
				vis[leaf] = j;
				leaf = a[leaf];
			}
			for (register int j = 0; j < size; j++){
				if (!mark[v[i][j]]){
					x = x * (deg[v[i][j]] + 1) % mod;
				} else {
					y = y * (deg[v[i][j]] + 1) % mod;
					z = (z + deg[v[i][j]]) % mod;
				}
			}
			ans = (ans * x % mod * (y - z) % mod + mod) % mod;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

发现我们建边 $i\to a_i$ 后，原图变成基环森林。每棵基环树是独立的，所以我们只需要考虑一棵基环树。

令 $in_u$ 为 $u$ 的入度。

接下来是手玩的过程：

考虑只有树的情况。

考虑 $a\to b\to c$ 对 $a\to b$ 进行操作后会怎么样。手玩发现会产生一个 $b\to b$ 的自环和 $a\to c$。

也就是说，对 $a\to b$ 进行操作并不影响  $in_c$。

继续分析，如果操作 $a\to b$ 而 $b$ 有自环，那么操作一次之后仍然是 $a->b$。

也就是说，每个点只会被它的直接儿子（即有向它连边的点）操作一次，当然也可以不操作。

那么数的答案就是所有节点的 $in$ 之积 $+1$。

现在考虑引入环。

考虑 $a\to b\to c\to a$ 操作 $a\to b$ 之后，会产生 $a\to c\to a$ 和一个 $b\to b$ 的自环。

每一个都可以留下来或单独产生自环，所以就是 $2^n$ 种。

但是发现只剩下一个的时候，它一定是自环，所以只留下 $1$ 个点的情况的 n 种是算重了的，需要减去，即 $2^{n}-n$。

注意到此时 $in_u=1$。

把二者结合起来。

你会发现，环上的点 $u$ 产生自环的方案数就是 $in_u$，即它会算重 $in_u$ 次。

考虑容斥，总方案数就是环上的点的 $in_u+1$ 的积，然后减去算重的 $\sum in_u$ 次。

然后不在环上的点不会存在这个问题，方案数仍然是 $\prod(in_u+1)$。

综上，答案为：

$$\prod\limits_{\text{circle}}(\prod\limits_{u\in\text{circle}}(in_u+1)-\sum\limits_{u\in\text{circle}}in_u)\prod\limits_{u \text{not in circle}}(in_u+1)$$

---

## 作者：lizhous (赞：1)

首先套路的把 $i$ 和 $a_i$ 连边。注意到连出来的是内向基环树森林，每棵树之间独立，所以我们只需要研究一棵基环树，全部乘起来即可。

先看看这个树是什么东西。一个点 $i$ 上写着他指向的点 $a_i$，操作他可以把他和自己的出边交换，然后因为这个两个点已经改变，他们就不能操作了。

有一个结论：对于一个点，他只能**被**交换一次。因为他**被**交换一次后，他上面就写着自己了，再交换对序列没有影响。

所以先考虑树的情况。每个点可以选择操作或者不操作，同时每个点的儿子只能有一个点选择操作。而因为操作完一个点后他和他的父亲都不能再操作了，所以我们必须自上而下的执行所有操作，即每个操作对应的最终结果是唯一的。把他写成 DP，其中 $v$ 为儿子，$son$ 为儿子个数。
$$
f_u=\prod f_{v}\times(son+1)
$$
接下来考虑环怎么搞。先看看这个环是什么东西，每个点上写着不同的数，操作他可以把他和他下一个点交换，然后他们就不能操作了。

我们可以把环上每一个点看成一个根，儿子有连向他的树点和环上他前面的一个点。对他进行上面的转移。

不过我们发现环上会有一些奇怪的限制。比如不能所有环上的点都选择操作，因为这样必然会有一个点无法执行自己的操作。

继续对限制进行探讨，发现如果只有一个点选择不操作，最终的局面一定是每个点都写这他上一个点写的数，即他自己。这个时候那个选择不操作的点也不能和树上的点交换。

继续对限制进行探讨，发现如果有两个点以上的点选择不操作，就没有怪事了，因为环被断成两个链，就没有环的性质了。

所以对于一个环上的点：
$$
f_u=\prod f_{v}
$$
最终环上的答案，其中 $son_u$ 表示点 $u$ 树点儿子个数：
$$
rans=\prod f_{u}\times(son_u+2) \\
cans=\prod f_{u}\\
dans=\sum son_u+1\\
ans=\prod (rans-cans\times dans)
$$
其中 $rans$ 表示不考虑所有环限制的操作方案数。$cans$ 表示除环以外所有树的操作方案数。$dans$ 表示环上只有一个点不选择操作的方案数。因为只有一个点不选择操作要保留一种情况，和所有点都选择操作抵消，所以最终答案就是上述东西。

注意自环要特判。

---

