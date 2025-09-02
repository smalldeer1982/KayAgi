# [JRKSJ R3] system

## 题目描述

定义对序列 $a$ 的一次操作为令 $b_i\gets a_{a_i}$，再令 $a_i\gets b_i$，其中 $i\in[1,n]$。

给你一个长为 $n$ 的序列 $a$，询问对 $a$ 进行 $k$ 次操作后的序列。

## 说明/提示

### 样例解释

对于第 $1$ 个样例，$a$ 的变化如下：

$$5,1,3,4,2$$
$$2,5,3,4,1$$

### 数据规模与约定

本题采用捆绑测试。

| $\text{Subtask}$ | $n\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10^4$ | $\text A$ | $5$ |
| $2$ | $10^2$ | 无 | $15$ |
| $3$ | $10^4$ | $\text B$ | $10$ |
| $4$ | $5\times 10^5$ | $\text B$ | $20$ |
| $5$ | $5\times 10^5$ | $\text C$ | $20$ |
| $6$ | $5\times 10^5$ | 无 | $30$ |

性质 $\text A$：$0\le k\le 10^3$。\
性质 $\text B$：$a_i=i\bmod n+1$。\
性质 $\text C$：$a$ 是一个 $[1,n]$ 的排列。

对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$0\le k\le 10^9$，$1\le a_i\le n$。

## 样例 #1

### 输入

```
5 2
2 5 4 3 1```

### 输出

```
2 5 3 4 1```

## 样例 #2

### 输入

```
20 233
1 1 5 6 8 15 10 11 18 14 4 16 16 11 3 5 1 15 4 5```

### 输出

```
1 1 4 5 6 8 4 15 5 6 3 11 11 15 11 4 1 8 3 4```

# 题解

## 作者：ComplexPlanck (赞：9)


题面非常简洁，注意到一次操作之后，$\,a_{i}\,$的值会变为$\,a_{a_{i}}\,$，所以我们不妨建立一张图，并连出$\,a_{i}\rightarrow i\,$的边。

画出这样一张图之后，你会发现这张图有$\,n\,$个点$\,n\,$条边，由于可能存在自环，所以这张图是基环树森林（其中可能存在环是自环的基环树）

![样例 2 的图，x.y 表示序号为 x，a_x 的值为 y 的点，自环 Graph Editor 画不出来...](https://cdn.luogu.com.cn/upload/image_hosting/8q9zf7v7.png)

（样例 2 的图，$\,x.y\,$表示序号为$\,x\,$，$\,a_x\,$的值为$\,y\,$的点，自环 Graph Editor 画不出来...）

并且显然的，这是一个内向树森林，所有点的入度都为$\,1\,$，定义对于边$\,u\rightarrow v\,$，$\,u\,$为$\,v\,$的父亲，注意父亲可能是自己。

注意到这样一个事实：

第一次操作后，$\,a_{i}\,$的值会变为$\,a_{a_{i}}\,$；

第二次操作后，$\,a_{i}\,$的值会变为$\,a_{a_{a_{a_{i}}}}\,$（有$\,4\,$个$\,a\,$）；

第$\,r\,$次操作之后，$\,a_{i}\,$的值会变为

$$\,a_{_{\ddots{a_{i}}}}\,$$

（不知道看不看得清）总之就是有$\,2^{r}\,$个$\,a\,$，相当于是从点$\,i\,$开始，跳到父亲$\,2^r\,$次。

我们不妨对基环树的环和附属子树（设$\,i\,$是环上的点，那么断开其在环上的边，剩下的是一棵树，称其为附属子树）分开讨论。

先讨论附属子树，由于附属子树树高不超过$\,\mathcal{O}(n)\,$，所以对于附属子树上的点，至多只需要$\,\mathcal{O}(\log n)\,$次就能跳到环中。

所以我们可以先跳$\,\left\lceil\log_{2}n\right\rceil\,$次，这样基环树森林的附属子树的高都变为$\,0\,$或$\,1\,$了。高为$\,0\,$的附属子树不用管，对于高为$\,1\,$的附属子树，此时的$\,a_{i}\,$是$\,i\,$下一步要跳到的点，假设$\,ans[p]\,$为点$\,p\,$最终跳到的点，$\,pre[p]\,$为跳到$\,p\,$的点上一步跳到的点，那么点$\,i\,$最终跳到的点就是$\,pre[ans[a_i]]\,$。

那么我们现在只需要处理环以及$\,pre\,$数组就行了。

由于我们之前已经跳过$\,\left\lceil\log_{2}n\right\rceil\,$次，所以接下来我们只需要跳$\,2^{k-\left\lceil\log_{2}n\right\rceil}\,$就够了，假设环长为$\,leng\,$，那么显然每个点只需要跳$\,2^{k-\left\lceil\log_{2}n\right\rceil}\operatorname{mod}leng\,$次就够了。

注意这里不能每个点都跳这么多次，因为这显然对于每个点，最坏是$\,\mathcal{O}(leng)\,$的，最坏复杂度可能到达$\,\mathcal{O}(n^2)\,$，所以我们不妨钦定一个起点$\,st\,$，我们让$\,st\,$跳这么多次就够了，假设最后跳到$\,ed\,$，因为$\,st\,$的后一个点最终跳到的位置显然是$\,ed\,$的后一个点，递推即可，这是$\,\mathcal{O}(1)\,$的。

显然在递推的过程中，我们可以顺带处理出$\,pre\,$数组，所以这个问题我们也解决了。

至此，这道题的流程就结束了，瓶颈在于那个快速幂，总体上时间复杂度是$\,\mathcal{O}(n\log k)\,$的，可以通过，具体实现可以看**带注释的代码**。

```cpp
#include <bits/stdc++.h>

namespace io
	// 省略快读快写
using namespace io;
namespace problems
{
	const int N = 500010;
	int n, k;
	int a[N], b[N], ans[N], pre[N];
	bool vis[N];
	int idc[N], cidx = 0, large;

	void go(void)
	{
		for (int i = 1; i <= n; ++ i)
			b[i] = a[a[i]];
		for (int i = 1; i <= n; ++ i)
			a[i] = b[i];
		return;
	}
	int ksm(int a, int b, int p)
	{
		int res = 1;
		while (b)
		{
			if (b & 1) res = 1ll * res * a % p;
			a = 1ll * a * a % p, b >>= 1;
		}
		return res;
	}

	int main(void)
	{
		memset(vis, false, sizeof(vis));

		read(n), read(k);
		for (int i = 1; i <= n; ++ i)
			read(a[i]);
		int lgn = log2(n) + 1;
		while (lgn && k)
		{
			-- lgn, -- k;
			go();
		}
		if (!k)
		{
			for (int i = 1; i <= n; ++ i)
				writesp(a[i]);
			puts(""); return 0;
		}
		for (int i = 1; i <= n; ++ i)
			if (!vis[i])
			{
				int now = i;
				for ( ; !vis[now]; now = a[now])
					vis[now] = true;
				// 找环
				if (idc[now]) continue;
				// i 是附属子树上的点，找到了旧环
				++ cidx, large = 0;
				int st = now;
				for ( ; !idc[now]; now = a[now])
					idc[now] = cidx, pre[a[now]] = now, ++ large;
				// 给环编号
				int times = ksm(2, k, large);
				// 需要偏移 2^k 次，模数为环长 large
				now = st;
				while (times --)
					now = a[now];
				ans[st] = now;
				// 找到起点对应的位置
				int x = st, y = now;
				x = a[x], y = a[y];
				while (x != st)
				{
					ans[x] = y;
					x = a[x], y = a[y];
				}
				// 将环上的点的答案处理掉
			}
		for (int i = 1; i <= n; ++ i)
			if (!idc[i])
			// 处理附属子树
				ans[i] = pre[ans[a[i]]];
		for (int i = 1; i <= n; ++ i)
			writesp(ans[i]);
		puts("");

		return 0;
	}
}

int main(void)
{
	problems::main();

	return 0;
}
```






---

## 作者：critnos (赞：7)

思考：若 $a$ 是一个环，怎么做？

不妨令 $a=2,3,4\dots n ,1$。

当 $n$ 是偶数的时候，$a$ 会分裂成不相交的两个环 $3,5\dots n-1$ 和 $4,6\dots n,2$。

当 $n$ 是奇数的时候，$a$ 仍是一个环。显然第 $i$ 次操作，整个环会转 $2^{i-1}$ 步。更直观的，操作 $k$ 次后，$a_i$ 就是 $i$ 在环上的往后第 $2^k$ 个点。

比如说：

$$2,3,4,5,1$$
$$3,4,5,1,2$$
$$5,1,2,3,4$$
$$4,5,1,2,3$$
$$2,3,4,5,1$$

所以当 $n$ 是偶数的时候，我们可以将环分裂，再递归的处理两个不相交的环。到环大小为奇数为止。

那么考虑 $a$ 一般的情况。此时是一个内向基环森林。

其实非常简单。每次操作会令树高减半。暴力处理即可。

具体的，对于每棵基环树，我们进行若干次操作，直到分裂出来的每棵基环树环都是奇环且每棵树都被“压扁”了。这时候会得到一些奇环，上面一些点下面挂着一些点的状态。显然 $i$ 下面挂着的点 $j$ 最后指向的就是 $a_i$ 在环上的前一个点。显然对于一个大小为 $s$ 的基环树，操作次数为 $O(\log s)$。 

时间复杂度 $O(n(\log n+\log k))$。若用拓展欧拉定理可优化至 $O(n\log n)$。

（找环的方法可以比较弱，因为环下面挂的树最多一层）

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005];
int b[500005];
bool v[500005];
int c[500005];
int pre[500005];
int ans[500005];
int n;
void f()
{
	int i;
	for(i=1;i<=n;i++)
		b[i]=a[a[i]];
	memcpy(a,b,n+1<<2);
}
int qpow(int a,int p,int mod)
{
	int mul=1;
	for(;p;p>>=1)
	{
		if(p&1) mul=1ll*mul*a%mod;
		a=1ll*a*a%mod;
	}
	return mul;
}
int main()
{
    int k,i,j,t,co=0,si,w;
	scanf("%d%d",&n,&k);
	t=log2(n)+5;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=0;i<t&&k;i++,k--) f();
	if(!k)
	{
		for(i=1;i<=n;i++)
			printf("%d ",a[i]);
		return 0;
	}
	for(i=1;i<=n;i++)
	{
		if(v[i]) continue;
		for(j=i;!v[j]&&!c[j];j=a[j])
			v[j]=1;
		if(c[j]) continue;
		co++;
		si=0;
		for(w=j;!c[j];j=a[j])
			c[j]=co,pre[a[j]]=j,si++;
		t=qpow(2,k,si);
		for(j=w;t--;j=a[j]);
		ans[t=w]=j;
		for(w=a[w],j=a[j];w!=t;w=a[w],j=a[j])
			ans[w]=j;
	}
	for(i=1;i<=n;i++)
		if(!c[i])
			ans[i]=pre[ans[a[i]]];
	for(i=1;i<=n;i++)
		printf("%d ",ans[i]);
} 
```


---

## 作者：aru123 (赞：2)

额，不知道为啥这个题的通过率爆低然而只是蓝题，而且出题人的题解我也看不懂，所以只能自己写一个题解了（题外话，这题我调了5个小时最后发现是快速幂写错了，所以一切的努力全部木大了）

好了，不废话，题面非常简单,假设这次操作是第 $n + 1$ 次的话，那么就有 $a_{n + 1,i} = a_{{a_{n, i}}, i}$ ，如此往复下去，直到操作 $k$ 次，求最后的序列。显然，如果我们只考虑下标变化的话，那么有 $ idx_{n + 1, i} = a_{n, i}$ , 从当前位置跳到当前位置上的数指向的位置，大概就是叫你去连一条边 $i\rightarrow a_{i}$ 。这样的边有 $n$ 条, 每个点的出度为 1，所以是基环树（森林），而且是内向的。

非常Trivial的，我们先考虑单环的情况，应该可以感性的了解到**环上的点都是一样的（意思是任何时刻环上的点步数是一样的）**, 不感性也行，用归纳法可证。 假设到第 $n$ 次一共走了 $f_{n}$步，那么到第 $n + 1$ 次一共走了 $f_{n + 1} = f_{n} + 1 + f_{n} = 2f_{n} + 1$ 步， 即自己之前走的步数（$f_{n}$） + 这一步的步数（1） + 到达的下一步的点的累计步数 ($f_{n}$)。 显然 $f_1 = 1 $，得到通项公式 $f_{n} = 2 ^{n} - 1$ 。

那么，环上的点到第 $k$ 次操作的时候一共走了 $2 ^{k} - 1$ 步， 之后考虑链子的问题。 如果这个链子是无限长的， 那么和环没有任何区别， 所以走了 $2 ^{k} - 1$ 步仍然到不了环上的点似乎也是走了 $2 ^{k} - 1$ 步，然而可能存在一个疑惑，就是从链子跑到环上的点是否也是走了$2 ^{k} - 1$ 步呢？不要紧，其实你已经得到答案了，注意看前边， _**环上的点都是一样的（意思是任何时刻环上的点步数是一样的）**_，所以任何时刻顶部的点的步数是一定的，所以**整个图都走了 $2 ^{k} - 1$ 步**。

到这里整个就结束了，剩下的都是常规操作，快速幂，$dfs$ 压栈求 $k$ 级祖先（因为有走不到环上的）、找环、拆环啥的，具体可以看代码，应该写的挺详细的。
```cpp
#include <bits/stdc++.h>

const int maxN = 5E5 + 5;

struct edge
{
    int to, next;
}edges[maxN], invEdges[maxN];

int head[maxN], invHead[maxN], noe = 0;
int stk1[maxN], stk2[maxN], stk3[maxN], cir[maxN], top1 = 0, top2 = 0, top3 = 0, cnt = 0, k, f;
int arr[maxN], res[maxN], lg[maxN], leftover[maxN];
bool inStk[maxN], vis[maxN];

inline void add(int u, int v)
{
    edges[++noe].to = v;
    edges[noe].next = head[u];
    head[u] = noe;
    invEdges[noe].to = u;
    invEdges[noe].next = invHead[v];
    invHead[v] = noe;
}

inline bool dfs1(int u)
{
    if(inStk[u])
    {
        do{
            cir[++cnt] = stk1[top1];
        }while(stk1[top1--] != u);
        return true;
    }
    if(vis[u]) return false;
    inStk[u] = vis[u] = 1;
    stk1[++top1] = u;
    for(int e = head[u]; e; e = edges[e].next)
    {
        int& v = edges[e].to;
        if(dfs1(v)) return true;
    }
    inStk[u] = 0;
    --top1;
    return false;
}

inline void dfs2(int u)
{
    stk2[++top2] = u;
    vis[u] = 1;
    if(lg[top2] <= k)
    {
        stk3[++top3] = u;
        leftover[u] = top2 - 1;
    }
    else
    {
        res[u] = stk2[top2 - (1 << k) + 1];
    }
    for(int e = invHead[u]; e; e = invEdges[e].next)
    {
        int& v = invEdges[e].to;
        if(v == f) continue;
        dfs2(v);
    }
    --top2;
}

inline int qpow(int p, int q)
{
    int a = 2, res = 1;
    while(p)
    {
        if(p & 1) res = 1ll * res * a % q;
        a = 1ll * a * a % q;
        p >>= 1;
    }
    return res;
}

inline void solveCir()
{
    cir[cnt + 1] = cir[1];
    int m = (qpow(k, cnt) + cnt - 1) % cnt;
    for(int i = 1; i <= cnt; ++i)
    {
        f = cir[i + 1];
        dfs2(cir[i]);
        int p = (i - m + cnt - 1) % cnt + 1;
        while(top3)
        {
            res[stk3[top3]] = arr[cir[(p + leftover[stk3[top3]] - 1) % cnt + 1]];
            --top3;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n >> k;
    for(int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
        add(i, arr[i]);
    }
    for(int i = 2; i <= n; ++i)
    {
        lg[i] = lg[(i + 1) >> 1] + 1;
    }
    for(int i = 1; i <= n; ++i)
    {
        if(!vis[i])
        {
            top1 = cnt = 0;
            dfs1(i);
            solveCir();
        }
    }
    for(int i = 1; i <= n; ++i) std::cout << res[i] << ' ';
    return 0;
}
```

---

## 作者：CJ_Fu (赞：1)

## [P7981 [JRKSJ R3] system](https://www.luogu.com.cn/problem/P7981)

给你一个数列 $p_i$，每次操作**同时** $p_i=p_{p_i}$，求 $k$ 次操作后的 $p$ 数列。

$p_i\le n\le 5\times 10^5,k\le 10^{9}$

部分分（50 pts）：$p$ 是一个排列。

即为 [ABC377E Permute K times 2](https://atcoder.jp/contests/abc377/tasks/abc377_e)，~~最新最热~~

考虑建图，连边 $i\to p_i$（本质上就是 $p_i\to p_{p_i}$），可以形成若干置换环，而每次操作将会 $p_i\to p_{p_i}\to p_{p_{p_{p_{i}}}}\to p_{p_{p_{p_{p_{p_{p_{p_{i}}}}}}}}\to \cdots$（$2^k$ 个 $p$），相当于在环上走了 $2^k$ 步到达的位置，直接上快速幂，对环长取模即可。时间复杂度 $O(n\log k)$。

100 pts：

同样建图，会形成内向基环树森林。考虑分两步：先跳到环上，再在环上按 50 分做法快速幂。第一步可以用一个类似求 LCA 时用的 $2^x$ 级祖先的一个倍增数组 $fa(x,i)$，由于 $n\le 5\times 10^5$，$x$ 最多预处理到 $19$。对于 $k\le 19$，直接跳 $fa(k,i)$ 即为答案；对于 $k>19$，直接跳 $2^{20}-1$ 级祖先，一定能跳到环上，然后再在环上走 $2^k-(2^{20}-1)$ 步即可。时间复杂度为 $O(n\log n+n\log k)$。

代码实现略有不同，对跳环第一步进行了一点常数优化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+7;
int n,k,rcnt;
int fa[20][maxn],vis[maxn],p[maxn],siz[maxn],ans[maxn],scc[maxn];
vector<int>v[maxn];
int qpow(int a,int b,int mod){
    int res=1;
    for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;
    return res;
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>fa[0][i]; p[i]=fa[0][i];
    }
    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++)
            fa[j][i]=fa[j-1][fa[j-1][i]]; // 处理倍增数组
    for(int i=1;i<=n;i++){ // 找环
        if(vis[i]) continue;
        int j,l;
        for(j=i;!vis[j];j=p[j]) vis[j]=-i;
        if(vis[j]>-i) continue; // 不重复找环
        v[++rcnt].emplace_back(j);
        vis[j]=++siz[rcnt],scc[j]=rcnt;
        for(l=p[j];l!=j;l=p[l]) v[rcnt].emplace_back(l),vis[l]=++siz[rcnt],scc[l]=rcnt;
    } // vis[i]>0 表示 i 在环上的相对顺序
    for(int i=1;i<=n;i++){
        if(k<20){ // 直接跳
            ans[i]=fa[k][i];
        }else{ 
            ans[i]=i;
            int step=0;
            for(int j=19;~j;j--){ // 跳到环上
                ans[i]=fa[j][ans[i]];
                step|=(1<<j);
                if(vis[ans[i]]>0){ // 到环上了
                    int rsiz=siz[scc[ans[i]]];
                    int rk=((vis[ans[i]]-1+qpow(2,k,rsiz)-step%rsiz+rsiz)%rsiz+rsiz)%rsiz;
                    ans[i]=v[scc[ans[i]]][rk];
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
```

---

## 作者：bryce (赞：0)

## [P7981 [JRKSJ R3] system](https://www.luogu.com.cn/problem/P7981)
### 思路
这个题目和 ABC377E 有些不同，但也有相同的思路，考虑对 $i$ 向 $p_i$ 连边，发现建出来的图是一个基环树，我们先不考虑基环树怎么做，先考虑只给一个排列，建边后只有环。

对于当前 $i$ 位置上一个数变换一次变为 $p_{p_i}$，$p_{p_i}$ 上的数变为 $p_{p_{p_i}}$，变换两次，$i$ 上的数就变为了 $p_{p_{p_{p_i}}}$，$p_{p_{p_i}}$ 上的数变为 $p_{p_{p_{p_i}}}$，以此类推，发现一个数会在自己的所在的环中变换 $2^k - 1$ 次，于是，找出这个环，找到从当前这个数开始往后第 $2^k - 1$ 个数。

接下来考虑基环树，我们发现这是一个内向基环树，按照上面的结论，从自己一直走 $2^k - 1$ 边，考虑这个怎么做，用倍增去维护，先倍增跳到一个环上，再判断在环上要走多少边，对环的大小取模，再在环上跳到正确的点。
### 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 5e5 + 10, M = 21;
int n, k;
int a[N], fa[N][M], vis[N], cir[N];
void dfs(int u, int id){
    if (vis[u] == id){
        if (cir[u]) return;
        int x = u, num = 1;
        while (a[x] != u){
            x = a[x];
            if (cir[x]) return;
            num++;
        }
        x = u, cir[x] = num;
        while (a[x] != u){
            x = a[x];
            if (cir[x]) return;
            cir[x] = num;
        }
        return;
    }
    if (vis[u]) return;
    vis[u] = id;
    fa[u][0] = a[u];
    dfs(a[u], id);
}
void init(){
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++) fa[j][i] = fa[fa[j][i - 1]][i - 1];
}
int qpow(int a, int b, int mod){
    int ans = 1;
    while (b){
        if (b & 1){
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

signed main(){
    n = read(), k = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++)
        if (!vis[a[i]]) dfs(a[i], i);
    init();
    for (int i = 1; i <= n; i++){
        int p = a[i], j;
        for (j = 0; j <= 19 && !cir[p]; j++) p = fa[p][j];
        int mod = cir[p], turn = ((((qpow(2, k, mod) - 1 + mod) % mod - qpow(2, j, mod) + mod) + mod) % mod + 1) % mod;
        for (j = 19; j >= 0; j--){
            if (turn >= (1 << j)) turn -= (1 << j), p = fa[p][j];
        }
        cout << p << ' ';
    }
    return 0;
}
```

---

