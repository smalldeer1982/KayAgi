# 「DLESS-2」XOR and Inversion

## 题目描述

给定 $0\sim 2^n-1$ 的排列 $p$，下标从 $0$ 开始，$q$ 次操作，每次操作形如以下两种中的一种：

- `1 x`: 将排列中的每个元素 $p_i$ 替换为 $p_i \oplus x$。
- `2 x`: 重新排列 $p$。对于每一个下标 $i$，操作后下标 $i$ 处的新元素是操作前下标 $i \oplus x$ 处的元素。

其中 $\oplus$ 表示按位异或运算。操作有后效性。

每次操作后，求出整个序列的逆序对数。

## 说明/提示

对于所有数据，保证：

- $1\le T\le 10^5$
- $1\le 2^n,\sum 2^n\le 2^{20}$
- $1\le q,\sum q\le 10^6$
- $0\le x<2^n$

**本题采用打包测试**，各子任务描述如下：

| Subtask | $\sum 2^n\le$ | $\sum q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $2^9$ | $500$ | 无 | $5$ |
| $2$ | $2^{11}$ | $2000$ | 无 | $10$ |
| $3$ | $2^{15}$ | $3\times10^5$ | 无 | $15$ |
| $4$ | $2^{18}$ | $3\times10^5$ | A | $5$ |
| $5$ | $2^{18}$ | $3\times10^5$ | B | $5$ |
| $6$ | $2^{18}$ | $3\times10^5$ | 无 | $10$ |
| $7$ | $2^{20}$ | $10^6$ | A | $5$ |
| $8$ | $2^{20}$ | $10^6$ | B | $10$ |
| $9$ | $2^{20}$ | $3\times10^5$ | 无 | $15$ |
| $10$ | $2^{20}$ | $10^6$ | 无 | $10$ |
| $11$ | $2^{20}$ | $10^6$ | 无 | $10$ |

**其中，除第 $11$ 个子任务空间限制为 128MB 外，其余子任务空间限制为 1GB。**

特殊性质 A：只有第一种操作。

特殊性质 B：只有第二种操作。

## 样例 #1

### 输入

```
3
3 2
7 6 3 2 5 1 0 4 
1 1
1 0
2 4
1 3 0 2 
1 2
1 0
1 1
2 3
2 3
0 2 1 3 
2 1
1 2
2 3```

### 输出

```
18
18
5
5
3
3
3
1
5
```

## 样例 #2

### 输入

```
3
2 2
1 3 2 0 
2 1
2 1
2 2
1 0 3 2 
2 2
2 0
3 5
2 5 3 1 7 0 6 4 
1 4
2 0
2 0
1 5
2 5```

### 输出

```
4
4
6
6
21
21
21
11
19```

## 样例 #3

### 输入

```
1
5 9
21 26 25 9 11 15 4 5 20 14 3 10 23 27 19 7 18 6 29 28 16 17 12 30 22 8 24 2 1 31 0 13 
2 21
1 16
1 15
2 0
2 10
2 24
2 11
1 30
1 21```

### 输出

```
269
225
227
227
259
257
267
223
275```

## 样例 #4

### 输入

```
1
0 4
0
1 0
2 0
2 0
1 0```

### 输出

```
0
0
0
0```

# 题解

## 作者：Gold14526 (赞：19)

我操，单 $\log$ 彻底怒了。单 $\log$ 指出了最核心的矛盾点：如果 std 写的常数足够小，怎么可能 $\log^2$ 轻轻松松直接通过？这确实是我的严重错误。我需要彻底承认 std 写的不够好，想办法把 DLESS Round 糊弄过去。

---

以下设 $h$ 表示题面中的 $n$，$n=2^h$。

首先考虑一个性质：操作是有结合律的。

例如，先执行 $p_i:=p_i\oplus x_1$，再执行 $p_i:= p_i\oplus x_2$，相当于执行一次 $p_i=p_i\oplus x_1\oplus x_2$，操作二也是类似。

于是现在相当于我们对排列 $p$，每次给出 $x_1,x_2$，求排列 $p'$ 使得 $p'_i=p_{i\oplus x_2}\oplus x_1$ 的逆序对数。

---

不妨先考虑一下没有操作一怎么做。

考虑我们平时有什么方式求逆序对，考虑通过分治的方式求逆序对。

考虑当 $n$ 为 $2$ 的幂次时，每次分治时，我们都会将一个区间 $[k2^p,(k+1)2^p)$ 分成两个区间 $[2k2^{p-1},(2k+1)2^{p-1}),[(2k+1)2^{p-1},(2k+2)2^{p-1})$，然后再归并求出跨过中点的信息。

我们把分治过程中 $p$ 相同的区间看作“一层”。

考虑如果 $x_2$ 的第 $p-1$ 位为 $1$ 会发生什么，此时左右两个区间会交换，在计算跨过中点的信息时，逆序对数应当是原来的正序对数，可以发现，这种交换在每一层是独立的，即只有 $x_2$ 的第 $p$ 位为 $1$ 时会交换第 $p$ 层向上合并的贡献，对其它位没有影响。

于是，对于一层 $p$，我求出这一层向上合并时，跨过上一层中点的正序对数和逆序对数，即可轻松解决询问，时间复杂度 $O((n+q)\log n)$。

---

接下来考虑没有操作二怎么做。

发现一个排列的逆序对数等于其逆排列的逆序对数，所以仿照没有操作一的做法即可完成。

---

接下来，我们考虑两者都有的情况。

我们考虑先按下标分治，接下来在每次分治时，我们将中点左侧的标记为 $0$，右侧的标记为 $1$，然后再按值域分治，求出每一层中跨过中点的标记正序对数和逆序对数即可得到一个 $O(n\log^2n+q\log^2n)$ 的做法。

实现时用线段树或 01-Trie 实现较为简便，实际上，这两种数据结构正是动态的分治。

[代码](https://www.luogu.com.cn/paste/2pejyvwl)。

---

先来考虑如何优化查询部分。

现在我们相当于有两张 $\log n\times\log n$ 的表格，分别表示 $x_1$ 与 $x_2$ 的每一位两两之间的正序对和逆序对个数。

但是我们可以做更多的预处理，比如说我们把它变成两个 $n\times\log n$ 的表格，表示 $x_1$ 到 $x_2$ 的每一位间的正逆序对个数，于是我们便可以支持单 $\log$ 查询。

不过，我们可以把 $n$ 分成高 $\frac{h}{2}$ 位和低 $\frac{h}{2}$ 位，分成 $4$ 个 $\sqrt{n}\times\sqrt{n}$ 的块，这样便可以支持单次 $O(1)$ 查询，那么查询的复杂度已经达到了最优。

不过在本题的数据范围下单次查询 $O(\log n)$ 也足以通过。

---

对于贡献的预处理部分，我们有至少两种 $O(n\log n)$ 做法：

#### 虚树做法

建一棵原排列的 01-Trie $S$，一棵逆排列的 01-Trie $T$，每次对于 $S$ 上的一个节点求出该节点包含的数在 $T$ 上的虚树，在虚树上 dp 求出贡献。

这种做法空间复杂度可以做到 $O(n)$，时间复杂度 $O(n\log n)$，不难证明，这两者都已经到达了最优复杂度。

可惜的是，这种做法常数要了命的大，即使在 $n,q$ 在 $10^6$ 级别的范围下仍然无法快于双 $\log$ 做法，完全无法通过此题。

[代码](https://www.luogu.com.cn/paste/5lkqehy7)。

#### Trie 树合并做法

考虑分治，每次将分治左右两侧的 01-Trie 合并，并在合并过程中计算信息，当一个节点左右有来自不同 Trie 的子节点时，将它们子树中元素个数相乘更新贡献。

这种做法空间复杂度为 $O(n\log n)$，时间复杂度 $O(n\log n)$，不过常数并不是很大，可以获得 $88$ 分。

[代码](https://www.luogu.com.cn/paste/ni61yalu)。

---

（这一部分做法感谢帮我们审核的管理 ppip）

但是，真的只能获得 $88$ 分吗？

常写树状数据结构的人肯定知道，我们可以进行垃圾回收。即，将删除的点重新在下次创建节点的时候利用。

在本题中，只要加了垃圾回收，Trie 树合并做法空间就是 $O(n)$ 的。

此时，空间复杂度为同一时刻最多存在的节点数。

设一棵 Trie 中存了 $k$ 个元素（并非节点），考虑把每一棵 Trie 分成上下两部分，上 $\log k$ 层为上部分，剩下的为下部分。容易证明上下部分均只有 $O(n)$ 个节点，所以总结点数为 $O(n)$。

于是，我们得到了常数并没有那么大的空间 $O(n)$，时间 $O(n\log n+q)$ 做法。

[代码](https://www.luogu.com.cn/paste/7bra03dz)。

---

## 作者：hamsterball (赞：7)

提供一个不需要trie的$\Omicron(n^22^n)$做法。

问题的操作显然可以添加，分别合并1操作的参数和2操作的参数可以将问题转换为：

给定$a$,$b$，在以$a$为参数进行一次操作1和以$b$为参数进行一次操作2后的逆序对数。

考虑一对逆序对$(i,j)$（$i<j$）在什么情况下会不产生贡献。

先假设$b=0$，那么$p_i$和$p_j$在异或上$a$二进制下按位比较，由于二者同时被异或上一个值，所以原来相同的位不变，不同的位大小翻转。

那么令$f(x,y)$为$x$和$y$首个不同的二进制位，即$\lfloor\log_2(x\oplus y)\rfloor$。$2^{f(p_i,p_j)}\land x=0$时显然$p_i,p_j$大小关系不变，否则翻转。

这样的话可以预处理$c_{i,0/1}$表示$f(p_x,p_y)=i$的顺序对/逆序对数量。

每次查询就是枚举$f(p_i,p_j)$，如果$x$在当前位为$1$，那取顺序对，否则取逆序对。

加上$b$之后就是扩展一维，同时预处理$c_{i,j,0/1}$表示$f(p_i,p_j)$和$f(i,j)$以及对的类型，查询时枚举$f(p_i,p_j)$和$f(i,j)$。

但如何预处理$c_{i,j,0/1}$。一种想法是直接枚举$i,j$后把对应前缀放进哈希表。这样时间和空间复杂度都是$\Omicron(n^22^n)$，占用内存大，效率也低。

考虑分治一下第一维，那么那么对于第二维就只需要放进桶了。常数小了很多，而且桶动态的开的话空间是$\Omicron(2^n)$。

实测不加快读最大的数据点1.82s，不过空间很优秀，只有12.47MB。

```cpp
#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ull = unsigned long long;
const int MAXN=1<<20;
const int MAXD=20;
int n,q,*b[MAXD];
ull cnt[MAXD][MAXD][2];
uint p[MAXN];
inline void solve(int d,int l,int r)
{
    if(l==r) return;
    int mid=(l+r)>>1;
    solve(d-1,l,mid);
    solve(d-1,mid+1,r);
    for(int i=l;i<=mid;i++)
        for(int j=0;j<n;j++)
            ++b[j][p[i]>>j];
    for(int i=mid+1;i<=r;i++)
        for(int j=0;j<n;j++)
            cnt[d][j][p[i]>>j&1^1]+=b[j][p[i]>>j^1];
    for(int i=l;i<=mid;i++)
        for(int j=0;j<n;j++)
            b[j][p[i]>>j]=0;
}
int main()
{
    int T;
    scanf("%d",&T);
    for(int i=0,j=MAXN;i<MAXD;i++,j>>=1)
        b[i]=new int[j]();
    while(T--)
    {
        scanf("%d%d",&n,&q);
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                cnt[i][j][0]=cnt[i][j][1]=0;
        for(int i=0;i<1<<n;i++)
            scanf("%u",&p[i]);
        solve(n-1,0,(1<<n)-1);
        int a=0,b=0;
        while(q--)
        {
            int op,x;
            scanf("%d%d",&op,&x);
            if(op==1) b^=x;
            else a^=x;
            ull res=0;
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    res+=cnt[i][j][(a>>i&1)^(b>>j&1)^1];
            printf("%llu\n",res);
        }
    }
    for(int i=0;i<MAXD;i++)
        delete[] b[i];
    return 0;
}
```

---

## 作者：xieziheng (赞：4)

虽然但是，卡常人绝对是原神玩多了。本题难点超过一半在于如何卡常。

首先题意等价于多次询问求出序列 $a_{i\bigoplus x}\bigoplus y$ 的逆序对。

考虑 $x=0$ 怎么做，直接建 $\text{trie}$，把每个值对应的位置插进去，然后考虑每一对的第一位不同的位置，对每一层的每个点算一下两个子树的逆序对数，然后询问的时候看一下那一位是什么就行。

然后一般情况是同理的，一个暴力的做法是，你在上一个做法中，对每个点的子树中的对应位置再建 $\text{trie}$。然后同理跑那个做法，但是这样是两只 $\log$ 的，而且常数巨大，只有五十分。

发现这个其实只需要在 $\text{trie}$ 上做 $\text{trie}$ 合并，计算贡献只需要在合并的同时统计即可，这样在大的 $\text{trie}$ 上分治然后合并的时候垃圾回收就是一只 $\log$ 的了，而且空间线性。

具体细节见代码：

```cpp
#include <bits/stdc++.h>
#define il inline
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const ll mod=998244353;
il ll qp(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod,b>>=1;
	}return ans;
}
il int read(){
	int x=0,c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x;
}
const int N=(1<<20)+5,M=N*10;
int T,k,n,m,a[N];
char lg[N];ll s[21][21][2];
int cnt,t[M][2],siz[M];char de[M];
int buc[M],top;
il int GET(){return top?buc[top--]:++cnt;}
il void INIT(int x){t[x][0]=t[x][1]=siz[x]=de[x]=0,buc[++top]=x;}
il void add(int &rt,int v){
	if(!rt) rt=GET();
	int x=rt,c;
	for(int i=k-1;i>=0;--i){
		c=((v>>i)&1);
		if(!t[x][c]) t[x][c]=GET(),de[t[x][c]]=de[x]+1;
		x=t[x][c],++siz[x];
	}
}
int clen;
int merge(int x,int y){
	if(!x || !y) return x|y;
	ll w;
	w=1ll*siz[t[y][0]]*siz[t[x][1]],s[clen][de[x]][0]+=w;
	w=1ll*siz[t[x][0]]*siz[t[y][1]],s[clen][de[x]][1]+=w;
	t[x][0]=merge(t[x][0],t[y][0]),t[x][1]=merge(t[x][1],t[y][1]),siz[x]=siz[t[x][0]]+siz[t[x][1]],INIT(y);
	return x;
}
int rt[N<<1];
il void init(){
	for(int i=0;i<n*2;++i) rt[i]=0;
	for(int i=0;i<=cnt;++i) t[i][0]=t[i][1]=siz[i]=0,de[i]=0;cnt=0;
}
void solve(int x,int d,int l,int r){
	if(l==r){add(rt[x],a[l]);return ;}
	int mid=(l+r)>>1;
	solve(x<<1,d+1,l,mid),solve(x<<1|1,d+1,mid+1,r);
	clen=d,rt[x]=merge(rt[x<<1],rt[x<<1|1]);
}
int x,y,z,opt;ll u,v,w;
int main(){
	for(int i=2;i<N-5;++i) lg[i]=lg[i>>1]+1;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&k,&m);n=(1<<k);top=0;
		for(int i=0;i<n;++i) a[read()]=i;
		int cur=0;
		for(int i=0;i<k;++i) for(int j=0;j<k;++j) s[i][j][0]=s[i][j][1]=0;
		solve(1,0,0,n-1);
		int c1=0,c2=0;
		while(m--){
			opt=read(),x=read();if(opt==1) c1^=x;else c2^=x;
			ll sum=0;
			for(int i=0;i<k;++i){
				w=0;int cc=((c1>>(k-1-i))&1);
				for(int j=0;j<k;++j) sum+=s[i][j][cc!=((c2>>(k-1-j))&1)];
			}
			printf("%lld\n",sum);
		}
		init();
	}
	return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：2)

~~暴论：ARC200A 比这题难。~~

### Solution

设置换 ${\rm W}(x)$ 满足 ${\rm W}(x)_i=i\oplus x$。

不难注意到 ${\rm W}(u)\times {\rm W}(v)={\rm W}(u\oplus v)$，且操作 $1$ 相当于右乘 ${\rm W}(x)$，操作 $2$ 相当于左乘 ${\rm W}(x)$，由于置换具有结合律可以发现实际上相当于求 $q={\rm W}(L)\times p\times {\rm W}(R)$ 的逆序对，此时 $q_i=p_{i\oplus L}\oplus R$。

不妨考虑 $R=0$（即只有操作 $2$）的情况怎么做。对序列建出一棵 01-Trie，则操作 $2$ 可以刻画成：对于满足 $x$ 的第 $k$ 位为 $1$ 的 $k$，交换 Trie 上所有第 $k$ 层节点的左右儿子。可以发现 Trie 的结构也能够很好的计算逆序对：枚举每个非叶节点，统计有多少对 $(u,v)$ 满足 $u$ 在左子树，$v$ 在右子树，且 $p_u>p_v$。可以预处理出每层节点是否交换的贡献，查询时枚举每一位算，即可将该部分问题做到 $O(n(2^n+q))$ 或 $O(n2^n+q)$。

接下来考虑一般的情形。此时与 $R=0$ 的情况的不同之处仅有子树内的点值异或了 $R$。这是一个类似的问题：对于每一个节点的内层再建一棵 Trie（为区分下文写作 trie），trie 上的每个节点贡献即为左右子树 size 的乘积，类似地分层算贡献即可。直接做是 $O(n^2(2^n+q))$ 的（据说这个也能过？），注意到 trie 是可以合并的，且询问可以使用光速幂的技巧优化到 $O(1)$，这部分可以做到 $O(n2^n+q)$。

但是空间 $O(n2^n)$ 爆了，尝试优化空间。考虑在合并过程中加一个垃圾回收，实现后可以发现这样空间就是 $O(2^n)$ 了，为啥呢？

尝试进行分析。首先不难发现每个时刻至多有 $n$ 个 trie，且每个 trie 的大小均形如 $2^k$，且 $k$ 不重。对于一个大小为 $2^k$ 的 trie，其前 $k$ 层填满也至多有 $2^k$ 个点，这部分的贡献为 $\sum_{k=0}^{n-1}2^k=O(2^n)$；后 $n-k$ 层的贡献为 $\sum_{k=0}^{n-1}2^k(n-k)$，根据经典结论这是 $O(2^n)$ 的，于是我们证明了空间复杂度是 $O(2^n)$ 的。

综上，可以做到 $O(n2^n+q)$ 时间与 $O(2^n)$ 空间。

### Code

一份比较丑的 $O(n2^n+q)$ 实现。

似乎跑的没有某些人的 $O(n^2(2^n+q))$ 快，这下这下了。

```cpp
bool Mst;
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=1<<20,M=1<<10,mod=998244353;
inline ll add(ll x,ll y){return (x+=y)>=mod&&(x-=mod),x;}
inline ll Add(ll &x,ll y){return x=add(x,y);}
inline ll sub(ll x,ll y){return (x-=y)<0&&(x+=mod),x;}
inline ll Sub(ll &x,ll y){return x=sub(x,y);}
inline ll qpow(ll a,ll b){
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
int n,m,q,B0,B1,U0,U1,a[N];ll _coef[20][20][2],coef[20][20][2],res0[M][M],res1[M][M],res2[M][M],res3[M][M];
int idx,rt[N<<1],siz[N<<2],t[N<<2][2],rub[N<<2],top;
inline int newnode(){
	int p=top?rub[top--]:++idx;
	return siz[p]=t[p][0]=t[p][1]=0,p;
}
inline void del(int &p){
	rub[++top]=p,p=0;
}
inline void ins(int &rt,int x){
	rt=newnode();
	int p=rt;++siz[p];
	for(int k=m-1;k>=0;k--){
		bool c=x>>k&1;
		t[p][c]=newnode();
		p=t[p][c],++siz[p];
	}
}
inline int merge(int p,int q,int x,int y=m-1){
	if(!p||!q)return p|q;
	_coef[x][y][0]+=(ll)siz[t[p][1]]*siz[t[q][0]];
	_coef[x][y][1]+=(ll)siz[t[p][0]]*siz[t[q][1]];
	t[p][0]=merge(t[p][0],t[q][0],x,y-1);
	t[p][1]=merge(t[p][1],t[q][1],x,y-1);
	siz[p]+=siz[q],del(q);
	return p;
}
inline void solve(int l,int r,int p=1,int d=m-1){
	if(!~d){
		ins(rt[p],a[l]);
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid,p<<1,d-1),solve(mid,r,p<<1|1,d-1);
	rt[p]=merge(rt[p<<1],rt[p<<1|1],d);
}
void Solve(){
	cin>>m>>q,n=1<<m;
	B0=(m+1)>>1,B1=m>>1,U0=(1<<B0)-1,U1=(1<<B1)-1;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<2;k++)
				_coef[i][j][k]=0;
	idx=top=0;
	for(int i=1;i<(n<<1);i++)rt[i]=0;
	solve(0,n);
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			for(int k=0;k<2;k++)
				coef[i][j][k]=_coef[j][i][k];
	for(int i=0;i<=U0;i++){
		auto res=res0[i];res[0]=0;
		for(int k=0;k<B0;k++){
			ll tmp0=0,tmp1=0;int lim=1<<k;
			for(int l=0;l<B0;l++){
				tmp0+=coef[k][l][i>>l&1];
				tmp1+=coef[k][l][!(i>>l&1)];
			}
			for(int j=0;j<lim;j++){
				res[j|1<<k]=res[j]+tmp1;
				res[j]+=tmp0;
			}
		}
	}
	for(int i=0;i<=U0;i++){
		auto res=res1[i];res[0]=0;
		for(int k=0;k<B1;k++){
			ll tmp0=0,tmp1=0;int lim=1<<k;
			for(int l=0;l<B0;l++){
				tmp0+=coef[k+B0][l][i>>l&1];
				tmp1+=coef[k+B0][l][!(i>>l&1)];
			}
			for(int j=0;j<lim;j++){
				res[j|1<<k]=res[j]+tmp1;
				res[j]+=tmp0;
			}
		}
	}
	for(int i=0;i<=U1;i++){
		auto res=res2[i];res[0]=0;
		for(int k=0;k<B0;k++){
			ll tmp0=0,tmp1=0;int lim=1<<k;
			for(int l=0;l<B1;l++){
				tmp0+=coef[k][l+B0][i>>l&1];
				tmp1+=coef[k][l+B0][!(i>>l&1)];
			}
			for(int j=0;j<lim;j++){
				res[j|1<<k]=res[j]+tmp1;
				res[j]+=tmp0;
			}
		}
	}
	for(int i=0;i<=U1;i++){
		auto res=res3[i];res[0]=0;
		for(int k=0;k<B1;k++){
			ll tmp0=0,tmp1=0;int lim=1<<k;
			for(int l=0;l<B1;l++){
				tmp0+=coef[k+B0][l+B0][i>>l&1];
				tmp1+=coef[k+B0][l+B0][!(i>>l&1)];
			}
			for(int j=0;j<lim;j++){
				res[j|1<<k]=res[j]+tmp1;
				res[j]+=tmp0;
			}
		}
	}
	int L=0,R=0,op,x,L0,L1,R0,R1;
	while(q--){
		cin>>op>>x;
		if(op==1)R^=x;
		else L^=x;
		L0=L&U0,L1=L>>B0,R0=R&U0,R1=R>>B0;
		cout<<(res0[L0][R0]+res1[L0][R1]+res2[L1][R0]+res3[L1][R1])<<'\n';
	}
}
bool Med;
int main(){
	cerr<<abs(&Mst-&Med)/1048576.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int _Test;cin>>_Test;
	while(_Test--)Solve();
	return 0;
}
```

---

