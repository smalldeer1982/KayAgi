# DSU Master

## 题目描述

You are given an integer $ n $ and an array $ a $ of length $ n-1 $ whose elements are either $ 0 $ or $ 1 $ .

Let us define the value of a permutation $ ^\dagger $ $ p $ of length $ m-1 $ ( $ m \leq n $ ) by the following process.

Let $ G $ be a graph of $ m $ vertices labeled from $ 1 $ to $ m $ that does not contain any edges. For each $ i $ from $ 1 $ to $ m-1 $ , perform the following operations:

- define $ u $ and $ v $ as the (unique) vertices in the weakly connected components $ ^\ddagger $ containing vertices $ p_i $ and $ p_i+1 $ respectively with only incoming edges $ ^{\dagger\dagger} $ ;
- in graph $ G $ , add a directed edge from vertex $ v $ to $ u $ if $ a_{p_i}=0 $ , otherwise add a directed edge from vertex $ u $ to $ v $ (if $ a_{p_i}=1 $ ).

 Note that after each step, it can be proven that each weakly connected component of $ G $ has a unique vertex with only incoming edges.Then, the value of $ p $ is the number of incoming edges of vertex $ 1 $ of $ G $ .

For each $ k $ from $ 1 $ to $ n-1 $ , find the sum of values of all $ k! $ permutations of length $ k $ . Since this value can be big, you are only required to compute this value under modulo $ 998\,244\,353 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1806D/27fd1ea1a5a6a85d7d3f7a744475a00230fb82dd.png) Operations when $ n=3 $ , $ a=[0,1] $ and $ p=[1,2] $  $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^\ddagger $ The weakly connected components of a directed graph is the same as the components of the undirected version of the graph. Formally, for directed graph $ G $ , define a graph $ H $ where for all edges $ a \to b $ in $ G $ , you add an undirected edge $ a \leftrightarrow b $ in $ H $ . Then the weakly connected components of $ G $ are the components of $ H $ .

 $ ^{\dagger\dagger} $ Note that a vertex that has no edges is considered to have only incoming edges.

## 说明/提示

Consider the first test case.

When $ k=1 $ , there is only $ 1 $ permutation $ p $ .

- When $ p=[1] $ , we will add a single edge from vertex $ 2 $ to $ 1 $ . Vertex $ 1 $ will have $ 1 $ incoming edge. So the value of $ [1] $ is $ 1 $ .

Therefore when $ k=1 $ , the answer is $ 1 $ .

When $ k=2 $ , there are $ 2 $ permutations $ p $ .

- When $ p=[1,2] $ , we will add an edge from vertex $ 2 $ to $ 1 $ and an edge from $ 3 $ to $ 1 $ . Vertex $ 1 $ will have $ 2 $ incoming edges. So the value of $ [1,2] $ is $ 2 $ .
- When $ p=[2,1] $ , we will add an edge from vertex $ 3 $ to $ 2 $ and an edge from $ 2 $ to $ 1 $ . Vertex $ 1 $ will have $ 1 $ incoming edge. So the value of $ [2,1] $ is $ 1 $ .

Therefore when $ k=2 $ , the answer is $ 2+1=3 $ .

## 样例 #1

### 输入

```
2
3
0 0
9
0 1 0 0 0 1 0 0```

### 输出

```
1 3 
1 2 7 31 167 1002 7314 60612```

# 题解

## 作者：_Diu_ (赞：18)

比较简单的计数。~~感觉题目难点在于看懂题~~

题目大意就是维护一个类似并查集的东西，每次拿出 $p_i,p_i+1$，找到两个点所在连通块的根节点，根据 $a_{p_i}$ 决定谁连向谁，问所有方案中 $1$ 的入度之和。

显然如果 $a_1=1$ 那答案是 $0$。

先转期望，我们对每个点 $u$ 统计 $u$ 直接连向 $1$ 的概率。

我们发现 $u$ 能直接连向 $1$ 当且仅当：

- $a_{u-1}=0$。
- 在 $p$ 中 $u-1$ 要在 $[1,u-1]$ 中最后出现。（也就是连接 $u,u-1$ 的时候前面 $u-1$ 个点构成连通块）
- 前面 $u-1$ 个点的连通块根节点是 $1$。

第一个条件好办，第二个条件相当于在一个长度 $u-1$ 的随机排列中问某个点在末尾的概率，也就是 $\frac1{u-1}$。

第三个条件等价于对于每一个 $1$ 的情况，我们要求这个 $1$ 不是前面的所有点中最后一个，对于第 $i$ 个位置，这个概率是 $1-\frac 1i$。

我们发现对于每个 $1$，这个事情是独立的，所以我们每次只需要把前缀答案乘起来即可，复杂度 $O(\sum n\log p)$，可以通过预处理逆元做到 $O(\sum n)$，但感觉没必要。

---

## 作者：Cxny (赞：11)

确实只有 Div.2 D 难度。但是场上为什么只有这么点人过呢？

---

阅读理解题。

注意题面中的两个小细节：

1. 连边是 $p_i$ 与 $p_i+1$ 连边，而不是 $p_{i+1}$。
2. 当 $a_{p_i}=1$ 时 $p_i$ 向 $p_i+1$ 连边，而不是 $a_i=1$ 时。

先考虑 $\forall i,a_i=0$ 的情况。

套路地算每个点的贡献。考虑何时 $p_i=x$ 有贡献：

- $x$ 已经与点 $1$ 连通。
- 点 $1$ 没有出边。

每次 $p_i$ 向 $p_i+1$ 所在弱连通分量连边，若将边视作无向，则每个连通块一定是一段区间，每次连边形如合并 $p_i$ 与 $p_i+1$ 所在连通块。

因此，$x$ 与 $1$ 连通等价于 $1$ 至 $x-1$ 均在 $x$ 前出现。

再考虑 $a_x=1$ 的情况。此时 $x$ 一定没有贡献，且若 $1$ 与 $x$ 已经联通，会消除所有 $j>i$ 的贡献。

---

于是就可以递推了。记 $ans_i$ 表示长度为 $i$ 的前缀的答案，$f_i$ 表示若 $a_{i+1}=0$ 会产生的总贡献。

考虑 $i$ 在排列中的位置。可以发现，插入中间不会改变原有的贡献。

当 $a_i=0$ 时，放在最后会额外产生 $1$ 的贡献；$a_i=1$ 时，放在最后会消除后续所有贡献。

于是有：
$$
\begin{cases}
f_i=f_{i-1}\cdot i,\ ans_i=ans_{i-1}\cdot i+f_{i-1}&a_i=0\\
f_i=f_{i-1}\cdot(i-1),ans_i=ans_{i-1}\cdot i&a_i=1
\end{cases}
$$

相当于 $a_i=1$ 时不能放在最后。

---

## 作者：BreakPlus (赞：4)

### Description

>给出序列 $a$。
>
>对于一个长度为 $m - 1$ 的排列 $p$，定义它的价值如下：
>
>有一个初始为森林的并查集，按照 $p_1\dots p_{m-1}$ 的顺序合并并查集 $p_i$ 和 $p_{i}+1$，**如果** $a_{p_i}=0$，那么将 $p_i+1$ 所在的并查集的根并到 $p_i$ 所在的并查集的根上，否则将 $p_i$ 并所在并查集到 $p_i+1$ 所在的并查集的根上，进行完所有操作后 $1$ 的儿子的个数。
>
>你需要对于所有 $k\in[1,n-1]$ 求出长度为 $k$ 的 $k!$ 中排列顺序的价值和，对 $998244353$ 取模。

（翻译有误，在加粗的两个字后面的 $1$ 应该改成 $0$，上面的描述是正确的）

---
### Hint

不难发现每次连接相邻的两个点，意味着无论何时，一个连通块一定是**一个连续段**（一个区间）。

---
### Sol

**没有技巧，全是感情**

这种题第一感觉应该会是考虑把答案转化为 **每一条边（$i \to i+1$）能给答案贡献的排列数** 之和。

先把对 $p$ 的计数转化为对连边顺序的计数（显然一样）。

假设 $i \to i+1$ 贡献了 $1$ 的答案，那么 $[1,i]$ 这一段**首先**要成一个连通块（不然不会连到 $1$ 的下面），**然后** $a_i=0$，其实就这两个条件。（我们只关心这条边是否会使得答案加 $1$，不在乎 $i+1$ 这个点在哪个连通块）


令一个 $k$ 对应的答案为 $S_k$，考虑计数 $S_k$。先设在 $i-1$ 次合并操作中，使得 $[1,i]$ 合并为一个根为 $1$ 的连通块的方案数。

$S_k = \sum \limits_{i=1}^{k-1} [a_i=0] {k-1 \choose i}f_i (k-i-1)!$

具体地，$[1,i]$ 的排列方案数是 $f_i$ 没错，而 $i \to i+1$ 的合并操作必须在这些操作之后进行，所以 $(i-1) +1$ 共 $i$ 次操作可以捆绑起来看，在一共 $k-1$ 次操作中挑位置放置。而后面的 $[i+1,k]$ 区间的连边顺序我们是不在乎的，直接 $(k-i-1)!$ 就好了。


惊奇地发现组合数和阶乘可以约掉。

$S_k = (k-1)! \sum \limits_{i=1}^{k-1} [a_i=0] 
\dfrac{f_i}{i!} $

只要求出 $f_i$，上式就可以 $\mathcal{O}(n)$ 求了。

$f_i$ 咋求？我们考虑 **最后一次连边操作**，此时整个 $[1,i]$ 的序列应当分成前半段和后半段，而最后一次操作就是把前半段和后半段连起来。枚举断的地方，类似的方法去计数。注意前半段应该以 $1$ 为根，后半段无所谓。

$f_i = \sum \limits_{j=1}^{i-1} [a_j=0] {i-2 \choose j-1}f_j (i-j-1)!$

$f_i = (i-2)!\sum \limits_{j=1}^{i-1} [a_j=0] \dfrac{f_j}{(j-1)!}$

那么同理也可以 $\mathcal{O}(n)$ 求了。

----

### Comment

本题作为一个 Div.2 D，考查了选手的思维能力**或**基础（因为做法很多），是一道合格甚至不错的计数题。某 rating 2100 的选手用大约 35min 就解决了这个问题，说明本题并没有难度和考察范围上的问题。

2500 纯粹恶评，应该是 1900。某 rating 2100 的选手场上写 1900 的题也用了 35min。

---

## 作者：masonpop (赞：3)

CF *2500，难度貌似只在题意理解。做法貌似比较固定，语言描述部分参照官方题解。

注意洛谷翻译有误，以下是真实题意。

对于排列 $\{p_1,p_2,\cdots p_{m-1}\}$，我们考虑每个 $i$，如果 $a_{p_i}=0$，那么我们从 $p_i+1$ 所属连通块的根向 $p_i$ 所属连通块的根连边，否则反过来。定义每个连通块的根是那个所有点指向的点（即出度为 $0$ 的点，这个确实有点像并查集）。定义这个排列的贡献为操作结束后点 $1$ 的入度。对于每个 $k$ ，$k=1,2,\cdots n-1$，分别求所有长度为 $k$ 的排列的贡献和。

记一次操作为 $(p_i,a_{p_i})$。考虑什么样 $(x,a_x)$ 的操作能对 $1$ 的入度产生贡献。容易发现，这次操作产生贡献的条件是 $a_x=0$ 并且 $1$ 至 $x-1$ 均在这次操作前出现，即 $1$ 与 $x$ 已经联通。我们可以只考虑涉及 $x$ 的连通性的操作。

由此就可以设计 dp 状态了。设 $f_i$ 表示长度为 $i$，且操作完后 $1$ 至 $i+1$ 的节点联通的排列个数。我们考虑新加入的操作 $(i,a_{i})$ 的位置：若 $a_i=0$，则不管加到哪里都不会影响 $1$ 的出度为 $0$。否则，容易发现当且仅当其放到最后一个位置时会影响 $1$ 树根的地位，也只有这个位置不合法。因此，当 $a_i=1$ 时，$f_i=f_{i-1}\times (i-1)$。否则，$f_i=f_{i-1}\times i$。

接下来统计答案就轻而易举了。设 $g_i$ 表示所有长度为 $i$ 的排列的总贡献。容易发现操作 $(i,a_{p_i})$ 的加入不会影响前面操作的贡献。而且，当且仅当其放在最后一个位置且前面 $i-1$ 次操作已经让 $1$ 成为了根。因此，$g_i=g_{i-1}\times i+[a_i=0]\times f_{i-1}$。

时间复杂度 $O(n)$。[代码](https://codeforces.com/contest/1806/submission/215336336)。

---

## 作者：Kisaragi_Nanami (赞：2)

不知道为什么能评上`*2500`。

~~可能是题意描述的问题。~~

注意题目中的「排列」是 $\{a_i\}$ 的排列，而 $\{a_i\}$ 是决定 $i$ 与 $i+1$ 所在弱连通分量的连边情况的。

容易知道如果从 $1$ 连出去了任意一条边，后续的操作便不会产生贡献了。考虑到这是一个临界情况，递推之。

设 $f_i$ 为考虑操作序列 $[1,i]$ 的排列，最终 $1$ 仍然没有出边的方案数。

若 $a_i=0$，那么在 $f_{i-1}$ 中一定是从 $i+1$ 连向 $1$，随便放即可。

否则 $1$ 一定不能是 $i$ 所在弱连通分量的无出边点，考虑在 $f_{i-1}$ 中，若 $a_1$ 在最后面，那么只要放到除了 $a_1$ 后面的 $i-1$ 个位置即可。

否则设 $a_1$ 的位置是 $p$，在这之前的所有位置可以任选。考虑操作排列 $[p,i-1]$ 内一定不存在从 $1$ 所在弱连通分量 $G'$ 连出去的边，因此要么是连入 $G'$ 的边，要么是相对孤立的两个点连边，此时证明 $i-1 \notin G'$。

>假设如此，那么如果 $i-1$ 连入了 $G'$，那么一定有 $i-2 \in G'$ 中，进而 $i-3 \in G'$。由此递归下去得到此时必须连完了所有边，与 $p \neq i-1$ 矛盾。

由于 $i-1 \notin G'$，所以 $a_i$ 的操作不影响 $1$，仅仅不能放在最后一个位置，方案仍然是 $i-1$。

于是

$$

f_i = \begin{cases}

f_{i-1} \cdot i & a_i = 0

\\

f_{i-1} \cdot (i-1) & a_i =1

\end{cases}

$$

考虑统计答案，设 $ans_i$ 为 $[1,i]$ 的贡献。考虑 $ans_{i-1} \rightarrow ans_i$，首先把 $a_i$ 扔到里面任何位置不会改变原有的贡献。其次如果 $a_i = 0$，那么有 $f_{i-1}$ 种方法使得 $ans_{i-1}$ 贡献 $f_{i-1}$ 个 $1$ 出去；而当 $a_i = 1$ 时，无论如何都无法使得 $1$ 的入边增加。

$$

ans_i = ans_{i-1} \cdot i + (1-a_i) \cdot f_{i-1}

$$



---

## 作者：gcx114514 (赞：0)

考虑算贡献，当一个点 $x$ 加入时，如果会产生贡献，当且仅当 $a_x=0$ 且 $1$ 到 $x-1$ 的操作已经出现，表现在图上就是 $1$ 与 $x$ 已经联通。

设 $dp_i$ 表示操作完 $1$ 到 $i+1$ 后的连通块排列数，现在考虑新加入一个节点 $j$，如果 $a_j=0$ 可以发现无论其在何处都不影响 $1$ 的根地位，若 $a_j=1$ 那么可以发现只有在序列末尾才影响 $1$ 根的地位，所以更新方式如下 $dp_i=dp_{i-1}\times(i-a_i)$。

那么考虑答案贡献，可以发现加入一个数不会影响前面的贡献，而且只有其在最后其加入前 $1$ 已经是根时会有贡献，所以 $ans_i=ans_{i-1}\times i+[a_i=0]\times (dp_{i-1})$。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
bool Mst;
const int Max=5e5+10;
const int mod=998244353;
const int inf=1e9+10;

struct modint{

	int val;

	static int norm(const int &x){return x<0?x+mod:x;}

	modint inv()const{
		int a=val,b=mod,u=1,v=0,t;
		while(b>0)t=a/b,swap(a-=t*b,b),swap(u-=t*v,v);
		return modint(u);
	}
	modint():val(0){}
	modint(const int &m):val(norm(m)){}
	modint(const ll &m):val(norm(m%mod)){}
	modint operator -()const{return modint(norm(-val));}
	bool operator ==(const modint &x){return val==x.val;}
	bool operator !=(const modint &x){return val!=x.val;}
	bool operator <=(const modint &x){return val<=x.val;}
	bool operator >=(const modint &x){return val>=x.val;}
	bool operator >(const modint &x){return val>x.val;}
	bool operator <(const modint &x){return val<x.val;}
	modint& operator *=(const modint &x){return val=static_cast<int>(1ll*val*x.val%mod),*this;}
	modint& operator +=(const modint &x){return val=(1ll*val+x.val)%mod,*this;}
	modint& operator -=(const modint &x){return val=norm(1ll*val-x.val),*this;}
	modint& operator >>=(const modint &x){return val>>=x.val,*this;}
	modint& operator <<=(const modint &x){return val<<=x.val,*this;}
	modint& operator ^=(const modint &x){return val^=x.val,*this;}
	modint operator >>(const modint &x){return modint(*this)>>=x;}
	modint operator <<(const modint &x){return modint(*this)<<=x;}
	modint& operator /=(const modint &x){return *this*=x.inv();}
	modint operator +(const modint &x){return modint(*this)+=x;}
	modint operator -(const modint &x){return modint(*this)-=x;}
	modint operator *(const modint &x){return modint(*this)*=x;}
	modint operator /(const modint &x){return modint(*this)/=x;}
	modint operator ^(const modint &x){return modint(*this)^=x;}
	friend std::ostream& operator<<(std::ostream& os,const modint &a){return os<<a.val;}
	friend std::istream& operator>>(std::istream& is,modint &a){return is>>a.val;}

};


inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

template <typename T>
struct TreeArray{

	vector<T>sum;
	int len;
	inline int lowbit(int x){return x&(-x);}
	void init(int n){sum.resize(n+3);len=n;}
	inline T Query(int x){T ans=0;while(x){ans+=sum[x],x-=lowbit(x);}return ans;}
	inline void Modify(int x,T val){while(x<=len){sum[x]+=val,x+=lowbit(x);}}
	inline T Query(int l,int r){return Query(r)-Query(l-1);}

};

modint f[Max],ans[Max];
int a[Max];

void work(){
	int n=read();
	f[0]=1;
	for(int i=1;i<n;++i){
		a[i]=read();
		if(a[i]) {
			f[i]=f[i-1]*(i-1);
		}else f[i]=f[i-1]*i;
	}
	ans[0]=0;
	for(int i=1;i<n;++i){
		ans[i]=ans[i-1]*i+(a[i]==0?f[i-1]:0);
		cout << ans[i] << " " ;
	}
	cout << "\n";
}

bool Med;
signed main(){
	int T=read();
	while(T--)work();


	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}
/*

*/


```

---

