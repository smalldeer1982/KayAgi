# [KSN2021] Binary Land

## 题目描述

给定一张 $N$ 个点的图，每个点有权值 $A_i$ 和价值 $B_i$。

两个点 $x,y$ 之间存在一条无向边当且仅当 $A_x\text{ xor }A_y>\max(A_x,A_y)$。

你需要对于 $i=1,2,\cdots n$ 依次求出点 $i$ 所在连通块中所有点的价值和。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：只存在一组数据，满足 $N=8$，$A=[6,39,11,63,3,39,1,43]$，$B=[4,8,3,7,9,1,2,2]$。
- Subtask 2（13 points）：保证 $N \leq 200$。
- Subtask 3（10 points）：保证 $N \leq 2000$。
- Subtask 4（4 points）：保证 $A_1=A_2=\cdots=A_n$。
- Subtask 5（7 points）：保证存在非负整数 $k$ 使得 $A_i=2^k$。
- Subtask 6（19 points）：$A_i\leq 2^{12}-1$。
- Subtask 7（39 points）：无特殊限制。

对于所有数据，$1 \leq N \leq 10^5$，$1 \leq A_i \leq 2^{30}-1$，$1 \leq B_i \leq 10^9$。

## 样例 #1

### 输入

```
3
2 1 1
20 30 10```

### 输出

```
60
60
60```

## 样例 #2

### 输入

```
4
5 4 4 5
10 20 30 40```

### 输出

```
10
20
30
40```

## 样例 #3

### 输入

```
5
1 2 1 7 11
20 10 30 100 100```

### 输出

```
60
60
60
200
200```

# 题解

## 作者：EXODUS (赞：28)

# Part 1：前言
图论建模好题！

# Part 2：正文

首先观察题目中所给的条件

$$A_x\oplus A_y>\max(A_x,A_y)$$

在这里不妨令 $A_x\geq A_y$，将其分解为二进制，并把位数对齐，在这里我们假设 $A_x,A_y$ 分解后的结果如下。
$$
A_x=10110101
$$
$$
A_y=00001010
$$
不难发现这是一种符合条件的情况，你发现了什么？

首先摆出结论，令 $\text{highbit}(x)$ 表示 $x$ 的最高位 $1$ 的位置（从高位到低位），$\text{zero}(x,pos)$ 表示 $x$ 的第 $pos$ 位是否是 $0$，则有 $\text{zero}(A_x,\text{highbit}(A_y))=1$。

考虑如何证明，若 $\text{zero}(A_x,\text{highbit}(A_y))=0$，则异或后结果的第 $\text{highbit}(A_y)$ 位必然是 $0$，由于异或后第 $1,2,...,\text{highbit}(A_y)-1$ 位与异或前的均相同，所以此时有 $A_x\oplus A_y<A_x$。此时如果暴力建边，可以通过维护并查集的方式维护连通块。

注意到  $\text{zero}(A_x,\text{highbit}(A_y))=1$ 与 $A_x\oplus A_y>\max(A_x,A_y)$ 互为充要条件，所以我们可以多维护 $30$ 个并查集，分别表示每一位，然后对每一位 $j$ 记录是否存在 $i$ 使得 $\text{highbit}(A_i)=j$ 以及是否存在 $i$ 使得 $\text{zero}(A_i,j)=1$。接下来对于每个 $A_i$，判断他所有有 $0$ 的位 $x$ 是否存在 $j$，使得 $\text{highbit}(A_j)=x$，以及对其最高位 $y$ 是否存在 $j$ 使得 $\text{zero}(A_j,y)=1$，由于上述的处理，这个可以 $O(1)$ 做到。如果存在上述两种情况的话就直接合并它与对应位数的并查集。

输出的时候直接输出该并查集中的 $B$ 的和，带权并查集解决。由于我没写按秩合并，所以时间复杂度是 $O(n\log^2n)$ 的。

# Part 3：代码
```cpp
bool DataS=0,FilE=0;
int T;
void init(){
	return;
}
const int N=2e5+7,B=37;
int n;
int a[N],b[N];
int fa[N],sum[N],hib[N];
bool vis1[N],vis2[N];
int find(int i){while(i!=fa[i])i=fa[i]=fa[fa[i]];return i;}
void merge(int x,int y){x=find(x),y=find(y);if(x==y)return;fa[x]=y,sum[y]+=sum[x];}
signed main(){
	if(FilE){
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	}
	T=(DataS?read():1);
	while(T--){
		init();
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++){
			b[i]=read();
			fa[i]=i,sum[i]=b[i];
		}
		int bit=30;
		for(int i=1;i<=bit+1;i++)fa[i+n]=i+n;
		for(int i=1;i<=n;i++){
			for(int j=bit,flag=1;~j;j--){
				if((a[i]&(1<<j))&&flag)vis1[j]=1,flag=0,hib[i]=j;
				if((!(a[i]&(1<<j)))&&(!flag))vis2[j]=1;
			}
		}
		for(int i=1;i<=n;i++){
			if(vis2[hib[i]])merge(i,hib[i]+n+1);
			for(int j=hib[i],flag=1;~j;j--){
				if(!(a[i]&(1<<j))&&vis1[j])merge(i,j+n+1);
			}
		}
		for(int i=1;i<=n;i++){
			int x=find(i);
			printf("%lld\n",sum[x]);
		}
	}
	return 0;
}
```
# Part 4：后文

点赞再走吧（可怜

---

## 作者：Jairon314 (赞：5)

> [题目链接](https://www.luogu.com.cn/problem/P7973)

$ \text{Solution} $

------------

看到题目中有异或操作，且值域形式给的是$\le 2^{30}-1$，那么我们容易想到拆位处理。

1. 设 $\operatorname{dig}(S,k)$ 表示 $S$ 的二进制下从高位到低位第 $k$ 位的值（最高位是 $2^{30}$，不足补 $0$ ）。

1. 设 $\operatorname{highbit}(S)$ 表示 $S$ 的最高非零位是哪一位。

设命题 $p, q :$

$p:a\;\operatorname{xor}\;b>\max\{a,b\}$，$(a>b)$.

$q:\operatorname{dig}(\,a,\operatorname{highbit}(b)\,)=0.$

显然 $p\Leftrightarrow q$ . 理由如下：

> 充分性 $(p\Rightarrow q)$
> > 考虑反证法 $(\lnot \, q \Rightarrow \lnot \, p)$
>
> > 如果有 $\operatorname{dig}(\,a,\operatorname{highbit}(b)\,) = 1$，那么易发现 $\operatorname{dig}(\,b,\operatorname{highbit}(b)\,)=1$， 则 $\operatorname{dig}(  a \; \operatorname{xor} \; b , \operatorname{highbit}(b) \, ) = 0$. 由于 $\operatorname{highbit}(b)$ 是 $b$ 的最高位，所以 $a \; \operatorname{xor} \; b$ 在更高位都与 $a$ 相同，且在这一位 $a \; \operatorname{xor} \; b$ 为 $0$ 而 $a$ 为 $1$，所以 $a \; \operatorname{xor} \; b < a = \max\{a,b\}$.
>
> 必要性 $( q \Rightarrow p )$
> > 如果有 $\operatorname{dig}(\,a,\operatorname{highbit}(b)\,) = 0$，那么易发现 $\operatorname{dig}(\,b,\operatorname{highbit}(b)\,)=1$， 则 $\operatorname{dig}(  a \; \operatorname{xor} \; b , \operatorname{highbit}(b) \, ) = 1$. 由于 $\operatorname{highbit}(b)$ 是 $b$ 的最高位，所以 $a \; \operatorname{xor} \; b$ 在更高位都与 $a$ 相同，且在这一位 $a \; \operatorname{xor} \; b$ 为 $1$ 而 $a$ 为 $0$，所以 $a \; \operatorname{xor} \; b > a = \max\{a,b\}$.

然后我们就可以枚举 $\operatorname{highbit}(A_y)$，找到所有 $\operatorname{highbit}(A_y)$ 是这一位的 $A_y$，然后找到能与其产生贡献的所有 $A_x$，扔进并查集里算贡献即可。注意对于某一位若没有可能的 $A_x$ 或者 $A_y$，不能计算找到的单独的集合 $A_y$ 或者集合 $A_x$ 的贡献，因为没有合法的元素 $\in A_x$ 或 $\in A_y$ 与之连边。

由于并查集使用了启发式合并（也不知道是不是按秩合并，不是依赖最大深度而是依赖子树大小），复杂度大概是 $O(n\log n \; \alpha(n))$.

------------

[点击查看缺省源"Jairon.h"](https://www.luogu.com.cn/paste/bckqxxoh)

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lint long long

#include <"Jairon.h">

#define maxn 1000010
#define SIZE 5010

int dig(int S,int k){ return (S>>(k-1))&1; }
bool highbit(int S,int k){ (dig(S,k)==1)&&(S<(1<<k)); }

int n;
int A[maxn];
int B[maxn];

struct dsu{
	int Siz;
	vii par,siz,val;
	dsu(){}
	dsu(int n):Siz(n),par(n+1),siz(n+1),val(n+1){ FOR(i,1,n){ siz[i]=1,par[i]=i,val[i]=B[i]; } }
	int find(int x){ return x==par[x]?par[x]:par[x]=find(par[x]); }
	bool same(int u,int v){ return find(u)==find(v); }
	int count(int x){ return siz[find(x)]; }
	int get_val(int x){ return val[find(x)]; }
	void unite(int u,int v){
		u=find(u),v=find(v);
		if(u==v){ return; }
		if(siz[u]<siz[v]){ swap(u,v); }
		val[u]+=val[v]; siz[u]+=siz[v]; par[v]=u;
		return;
	}
};

signed main(){
	read(n);
	FOR(i,1,n){ read(A[i]); }
	FOR(i,1,n){ read(B[i]); }

	dsu uf(n);
	ROF(bit,31,1){
		vii vec; bool flag=false,FLAG=false;
		FOR(i,1,n){ if( dig(A[i],bit)==1 && A[i]<(1<<(bit)) ){   vec.pb(i); FLAG=true; } }
		FOR(i,1,n){ if( dig(A[i],bit)==0 && A[i]>(1<<(bit-1)) ){ vec.pb(i); flag=true; } }
		if(!flag||!FLAG){ continue; } FOR(i,1,(int)vec.size()-1){ uf.unite(vec[i],vec[i-1]); }
	}

	FOR(i,1,n){ outn( uf.get_val(i) ); }
	return 0;
}

/**/
```


---

## 作者：ycy1124 (赞：3)

### 前言：
模考题，考场想到正解然后因为细节挂了 $50$ 分。
### 题意
有 $n$ 个点，每个点有一个权值 $a_i$ 和一个价值 $b_i$，假如一对点 $i,j$ 满足 $a_i \oplus a_j > max(a_i,a_j)$，那么就可以在它们之间连一条无向边。求所有边连完以后每个点所处的连通块内所有点的价值和。
### 思路
首先考虑 $\mathcal{O}(n^2)$ 的做法：枚举所有可能连边的点对，暴力连边后跑一边图。明显，这个方法是会 TLE 的，复杂度瓶颈在于连边。

然后考虑优化连边，对于一个 $a_i$，我们考虑它能和哪些其它的 $a_j$ 连上边。这里我们可以分类讨论一下：

1. 如果 $a_i,a_j$ 转化成二进制数之后长度相等，那么它们一定是不满足条件的。因为它们的最高位异或起来等于零，所以一定会比 $max(a_i,a_j)$ 更小。
2. 如果 $a_i,a_j$ 转化成二进制后长度不相等，我们假定 $a_i$ 的长度大于 $a_j$，那么在 $a_j$ 的首位异或上 $a_i$ 的这一位等于 $1$ 时，也就是 $a_i$ 的这一位等于 $0$，它们就是满足条件的。例如：```1101 10``` 这两个二进制数是合法的。

此时我们可以发现，对于每个 $a_i$，我们可以先将其进行二进制拆分。对于拆分后的每一位，假如它是 $1$ 并且它是最高位时，我们就将它与当前的位数连一条边。假如它是 $0$，我们就可以直接将其与当前位连一条边。这样我们就可以把连边的复杂度降到 $\mathcal{O}(n\log a)$。我们可以额外开（虚拟出） $64$ 个点做为当前位数。当新开的点连着至少一个 $1$ 和一个 $0$ 时，它所连的所有点它们一定时联通的，否则这个点就无效。最后 dfs 求解就可了。

讲的比较抽象，建议看代码方便理解。
### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 100005
using namespace std;
inline char fgc(){
	return getchar();
}
inline long long rint(){//快读
    long long x=0,s=fgc(),f=1;
    for(;s<'0'||'9'<s;s=fgc()){}
    for(;'0'<=s&&s<='9';s=fgc())x=x*10+(s^'0');
    return x*f;
}
long long a[Maxn];//存a
int n,Color;
vector<int>t[Maxn+100];//存图
bool bj1[100],bj2[100];//标记每个新开的点是否练了1和0
int vis[Maxn+100];//记录每个点所处的连通块
long long sum[Maxn];//记录连通块的价值和
int w[Maxn];//价值
void dfs(int p){//dfs求解
	vis[p]=Color;//记录这个点的连通块
	if(p<=n){//假如这个点是存在的
		sum[Color]+=w[p];//当前联通块的价值加上这个点的价值
	}
	for(auto it:t[p]){//遍历图
		if(vis[it]){
			continue;
		}
		if(it<=n){
			dfs(it);
		}
		else if(bj1[it-n]&&bj2[it-n]){//判断这个数位是否有效
			dfs(it);
		}
	}
	return;
}
signed main(){
	n=rint();
	for(int i=1;i<=n;++i){
		a[i]=rint();
	}
	for(int i=1;i<=n;i++){
		w[i]=rint();
	}
	for(int i=1;i<=n;++i){
		int js=0;
		long long x=a[i];
		while(x){//判断首位
			++js;
			x/=2;
		}
		if(js){
			t[i].push_back(n+js);
			t[n+js].push_back(i);//记得连无向边
			bj2[js]=1;
		}
		js=0;
		x=a[i];
		while(x){
			++js;
			if(x%2==0){
				t[i].push_back(n+js);//判断每一位的0
				t[n+js].push_back(i);
				bj1[js]=1;
			}
			x=x/2;
		}
	}
	for(int i=1;i<=n;++i){
		if(!vis[i]){//假如已经属于连通块
			Color++;
			dfs(i);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld\n",sum[vis[i]]);//输出每个点所处的连通块的价值和
	}
	return 0;
}
```
+ 复杂度 $\mathcal{O}(64\times n)$。

---

## 作者：NATO (赞：2)

【数据删除】sol

$\text{sub}1,2,3$：

直接 $O(n^2)$ 枚举点对判断是否有边后直接并查集连边即可。

$\text{sub}5$：

考虑任意两个数 $2^i,2^{i'}(i\neq i')$，显然 $2^i \oplus 2^{i'}=2^i+2^{i'}>\max(2^i,2^{i'})$，故任意两个不相等的数之间均有连边，故如果所有数相同则有 $n$ 个连通块，否则 $1$ 个。

$\text{sub}6$：

考虑直接把本质不同的数拿出来做 $\text{sub}1,2,3$ 即可。

正解：

$\text{sub}5$ 启示我们按位考虑，而 $\text{sub}6$ 启示我们精简枚举的方法。

我们钦定当前枚举的 $a_i=\max(a_i,a_{i'})$，如果 $a_{i'}$ 二进制下的最高非零位和 $a_i$ 的那一位均为 $1$ 的话（设该位为从低到高的第 $k$ 位）就会减去 $2^{k-1}$，而后面的位无论加上多少都补不上，必然无边；反之若 $a_i$ 的那一位为 $0$ 就会加上 $2^{k-1}$，而后面的位无论减去多少都减不完，必然有边。

故两个点是否有边仅由大的那个数在小的那个数二进制下的最高非零位那一位是否为 $1$ 决定，为 $1$ 无边，否则有边。

故对于 $1\le k\le 30$ 记录有哪些连通块存在一个数满足最高位是从低到高第 $k$ 位，从小到大枚举 $a_i$ 将点 $i$ 和与符合上述条件的连通块用并查集合并即可。

时间复杂度 $O(n(\log v+\alpha(n)))$（std 只写了路径压缩，是 $O(n(\log v+\log n))$ 的，不过不重要）。

#### 参代码考：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define MOD 998244353
using namespace std;
struct px
{
	ll a,b,uid;
	bool operator<(const px&b)const
	{
		return a<b.a;
	}
}a[100005];
ll ans[100005],f[100005],sum[100005],cv[100005],n;
vector<ll>h[30];
ll find(ll x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
void merge(ll a,ll b)
{
	if(find(a)==find(b))return;
	sum[find(b)]+=sum[find(a)];cv[find(b)]|=cv[find(a)];f[find(a)]=find(b);
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<=n;++i)cin>>a[i].a;
	for(ll i=1;i<=n;++i)cin>>a[i].b,a[i].uid=i;
	sort(a+1,a+1+n);
	for(ll i=1;i<=n;++i)
	{
		f[i]=i;sum[i]=a[i].b;
		ll cnt=0,now=1;
		while(now*2<=a[i].a)now*=2,++cnt;
		cv[i]=now;
		for(ll j=cnt;j>=0;--j)
			if(((a[i].a>>j)&1)==0)
			{
				for(auto it:h[j])merge(it,i);
				h[j].clear();
			}
		for(ll j=cnt;j>=0;--j)
			if((cv[find(i)]>>j)&1)
			h[j].emplace_back(find(i));
	}
	for(ll i=1;i<=n;++i)ans[a[i].uid]=sum[find(i)];
	for(ll i=1;i<=n;++i)cout<<ans[i]<<'\n';
}
```

---

## 作者：RainySoul (赞：1)

本题的数据好像是故意卡着的，正解做法 AC 也是看数据心情。

### 思路

观察那个关系式 $A_x \oplus A_y > \max(A_x,A_y)$，你考虑什么时候才会在 $x$ 和 $y$ 之间连边。

钦定 $A_x$ 为 $A_x,A_y$ 中的较大值，记 $A_x \oplus A_y$ 为 $t$。那么现在是当 $t > A_x$ 时连边。对二进制下的 $A_x$ 的每一位从高到低讨论。

当 $A_x$ 的当前位为 $1$ 的时候：

> 如果当前位仍有限制（$t$ 和 $A_x$ 的更高位全部相等），$t$ 的当前位仅能取 $1$，因此 $A_y$ 的当前位仅能取 $0$；
>
> 否则 $t$ 的当前位可以任意取。

当 $A_x$ 的当前位为 $0$ 的时候：

> $t$ 的当前位可以任意取，当现在仍有限制时，如果当前位取 $0$ 限制会继续传递到下一位；
>
> 如果 $t$ 的当前位取 $1$ 就把限制永久性解除了，即 $A_y$ 的当前位如果取 $1$ 后面不论如何动都是合法的。

经过上面的讨论，你发现 $A_x$ 合法的匹配首先应该出现在它的最高位连续一段 $1$ 之后，形似这样：（其中 `?` 就是可以任意取）

```
A[x]=11111001001
A[y]=000001?????
```

进一步地，对于每一个 $A_x$ 的为 $0$ 的位你都可以发现相似的结论：如果 $A_x$ 当前位为 $0$ 且当前位是 $A_y$ 的最高位，这个 $A_y$ 一定合法。

tip：建议自己推一下这个结论，这是简单的。

```
A[x]=11111001001
A[y]=000001?????
A[y]=0000001????
A[y]=000000001??
A[y]=0000000001?
```

以上的 $A_y$ 均是匹配的。

发现这可以换成一个 $A_x$ 对着一个区间内的 $A_y$ 全部连边，表示成以下形式：

如果 $A_x$ 从左到右的第 $k$ 位为 $0$，从 $A_x$ 向 $[2^k,2^{k+1}-1]$ 中的所有数连边，这会使得区间内的数和 $A_x$ 全部连通。

首先把所有数按照二进制位数分成 $k$ 层，从位数更高的层向位数更低的层连边，直接枚举，并查集维护。

有个显然的巨大的复杂度优化，记一下这一层的数是不是全部连通的，是的话只连这一层的第一个就好了。

时间复杂度 $O(n \log n \times \log A)$。

那个 $\log A$ 是 $A_i$ 转二进制的复杂度。

AC code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
struct zyx{int num,loc;};
int n,a[N],fa[N],sz[N],maxn,ans,sum[N],b[N];
bool f[N],flag[N];
vector<zyx> v[N],ve[N];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int find(int x){
	if(x==fa[x])return x;
	else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	fa[find(x)]=find(fa[y]);
}
int mlog(int a){
	int ans=0;
	while(a>0)a/=2,ans++;
	return ans;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),maxn=max(maxn,a[i]);
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		fa[i]=i,sz[i]=1;
		v[mlog(a[i])].push_back((zyx){a[i],i});
	}
	for(int i=1;i<=mlog(maxn);i++)
		for(int j=0;j<v[i].size();j++){
			int temp=v[i][j].num,now=0;
			while(temp>0){
				now++;
				if(temp%2==0){
					if(flag[now]==0){ 
						for(int k=0;k<v[now].size();k++)
							merge(v[i][j].loc,v[now][k].loc);
						flag[now]=1;
					}
					else if(v[now].size()>0)merge(v[i][j].loc,v[now][0].loc);
				}
				temp/=2;
			}
		}
	for(int i=1;i<=n;i++)sum[find(i)]+=b[i];
	for(int i=1;i<=n;i++){
		cout<<sum[find(i)]<<'\n';
	}
	return 0;
}
```

---

