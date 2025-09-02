# Cool Slogans

## 题目描述

Bomboslav set up a branding agency and now helps companies to create new logos and advertising slogans. In term of this problems, slogan of the company should be a non-empty substring of its name. For example, if the company name is "hornsandhoofs", then substrings "sand" and "hor" could be its slogans, while strings "e" and "hornss" can not.

Sometimes the company performs rebranding and changes its slogan. Slogan $ A $ is considered to be cooler than slogan $ B $ if $ B $ appears in $ A $ as a substring at least twice (this occurrences are allowed to overlap). For example, slogan $ A= $ "abacaba" is cooler than slogan $ B= $ "ba", slogan $ A= $ "abcbcbe" is cooler than slogan $ B= $ "bcb", but slogan $ A= $ "aaaaaa" is not cooler than slogan $ B= $ "aba".

You are given the company name $ w $ and your task is to help Bomboslav determine the length of the longest sequence of slogans $ s_{1},s_{2},...,s_{k} $ , such that any slogan in the sequence is cooler than the previous one.

## 样例 #1

### 输入

```
3
abc
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
ddddd
```

### 输出

```
5
```

## 样例 #3

### 输入

```
11
abracadabra
```

### 输出

```
3
```

# 题解

## 作者：iostream (赞：36)

## right集合神题 + 神仙结论题 

### 结论（1）

每次只算$s[i-1]$是$s[i]$的后缀的情况，显然是不会影响答案的。

因为如果$s[i-1]$不是$s[i]$的后缀，那么我们把不与$s[i-1]$匹配的那后面一截都去掉，$s[i]$就会变短。

如果没变短之前它在某一个字符串里出现过了，那么变短后显然还是出现过的。

这个结论是显然的，也比结论（2）容易理解。 

建立后缀自动机。
容易想到直接在parent树上自上向下DP； 

考虑如何判断x的祖先y所代表的子串是否在x中出现了两次：
$len[x]$表示$x$代表的最长子串长度，假设$x$的$right$集合中存在一个位置$p$，
那么$p$显然已经在$y$的$right$集合中了，
我们只要判断$y$的$right$集合中有没有一个元素，
在区间$[pos(x)-len(x)+len(y),pos(x)-1]$中判断y串是否出现两次即可。

这个容易线段树合并完成。 

可以发现，我们以上的做法都只考虑父亲代表的最长串都必须出现在x代表的最长串中。

这样有没有问题呢？又如何dp呢？ 

### 结论（2）

设s是某个节点u表示的最长串,v是u的祖先（即串的后缀）， 
则v表示的所有字符串在s上的匹配情况是等价的（即不会出现有的能匹配、有的不能）。

证明的话，我们举个例子：

$(1)\ \ \ \ \ \ abcb$

$(2)\ \ \ \ babcb$

$(s)\ \ \ \ \ \ abcbabcb$

考虑反证： 

假设这里(s)的后缀(1)(2)均为v节点表示的串，（1）成功匹配而（2）不行。

因为(2)，所有显然还存在着这个串：

$(3)\ \ \ \ babcbabcb$

又因为(s)表示的已经是u的最长串了，所以(3)串一定来自另一个节点。

设(3)串来自另一个节点w，u是w的祖先。

根据定义知
$$ |Right(u)| > |Right(w)| $$

这样，则一定存在一个位置p
$$p ∈Right(u) - Right(w)$$
在这个位置只出现了(s)串而没有(3)串。

这样就存在一个位置使得只出现(1)串而没有(2)串。

这样得到(1)(2)两串$Right$集合不同？？ 

这与它们来自同一个节点矛盾！

证毕. 

有了结论（2），我们就可以设计dp状态了： 

$dp[i]$表示使用节点i最长的那个字符串的答案，
转移的时候可以直接使用祖先节点j最长的那个字符串转移（因为都等价啊）

这样一来整个dp过程都是忽略那部分短串的，就非常自然了。 

这个dp显然可以倍增，容易做到线性。其他题解说的很清楚了。

```cpp
#include<set>
#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;

typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;

const int N=400005;

char S[N];
int n,tot(1),la,ch[N][26],len[N],fa[N],pos[N],rt[N],cnt,rk[N],ar[N],dp[N],fr[N],Ans;

struct node {
	int lc,rc;
}t[N*20];

void Upd(int &u,int l,int r,int p)
{
	if(!u)
		u=++cnt;
	if(l!=r)
	{
		int m=(l+r)>>1;
		if(m>=p) Upd(t[u].lc,l,m,p);
		else Upd(t[u].rc,m+1,r,p);
	}
}

int Merge(int x,int y,int l,int r)
{
	if(!x||!y)
		return x+y;
	int o=++cnt;
	if(l!=r)
	{
		int m=(l+r)>>1;
		t[o].lc=Merge(t[x].lc,t[y].lc,l,m);
		t[o].rc=Merge(t[x].rc,t[y].rc,m+1,r);
	}
	return o;
}

int Query(int u,int l,int r,int L,int R)
{
	if(!u||l>R||r<L)
		return 0;
	if(l>=L&&r<=R)
		return 1;
	int m=(l+r)>>1;
	return Query(t[u].lc,l,m,L,R)||Query(t[u].rc,m+1,r,L,R);
}

void extend(int id,int where)
{
	int p=la;
	int np=++tot;
	len[np]=len[p]+1;
	pos[np]=where;
	while(p && !ch[p][id])
	{
		ch[p][id]=np;
		p=fa[p];
	}
	if(!p)
	{
		fa[np]=1;
	}
	else
	{
		int q=ch[p][id];
		if(len[p]+1==len[q])
		{
			fa[np]=q;
		}
		else
		{
			int nq=++tot;
			len[nq]=len[p]+1;
			fa[nq]=fa[q];
			pos[nq]=pos[q];
			for(int i=0; i<26; i++)
				ch[nq][i]=ch[q][i];
			fa[np]=fa[q]=nq;
			while(p && ch[p][id]==q)
			{
				ch[p][id]=nq;
				p=fa[p];
			}
		}
	}
	la=np;
	Upd(rt[la],1,n,where);
}

void Sort()
{
	for(int i=1; i<=tot; i++) ar[len[i]]++;
	for(int i=1; i<=n; i++) ar[i]+=ar[i-1];
	for(int i=1; i<=tot; i++) rk[ar[len[i]]--]=i;
}

int main()
{
	scanf("%d%s",&n,S+1);
	la=1;
	for(int i=1; i<=n; i++) extend(S[i]-'a',i);
	Sort();
	for(int i=tot; i!=1; i--)
	{
		int u=rk[i],v=fa[u];
		rt[v]=Merge(rt[v],rt[u],1,n);
	}
	for(int i=2; i<=tot; i++)
	{
		int u=rk[i],v=fa[u];
		if(v==1)
		{
			dp[u]=1;
			fr[u]=u;
		}
		else if(Query(rt[fr[v]],1,n,pos[u]-len[u]+len[fr[v]],pos[u]-1))
		{
			dp[u]=dp[v]+1;
			fr[u]=u;
		}
		else
		{
			dp[u]=dp[v];
			fr[u]=fr[v];
		}
		Ans=max(Ans,dp[u]);
	}
	printf("%d",Ans);
	return 0;
}


---

## 作者：xht (赞：19)

> [CF700E Cool Slogans](https://codeforces.com/contest/700/problem/E)

## 题意

- 给定一个长度为 $n$ 的字符串 $s$。
- 你要构造一个最长的字符串序列 $t_{1\dots k}$，满足：
  1. 对于 $i \in [1,k]$，$t_i$ 为 $s$ 的子串。
  2. 对于 $i \in [2,k]$，$t_i$ 在 $t_{i-1}$ 中出现了至少两次。
- $n \le 2 \times 10^5$。

## 题解

对字符串建 SAM，用可持久化线段树合并求出每个节点的 $\operatorname{endpos}$ 集合。

在 $\operatorname{parent}$ 树上从根向下 dp，设 $f_i$ 表示到节点 $i$ 时的最大值。

如果一个父节点的子串在子节点的子串中出现了至少两次，则转移时 $f$ 加一，否则不变。

考虑如何判断是否出现了至少两次，设此时的子节点为 $x$，父节点为 $pa_x$。

找到 $x$ 对应的 $\operatorname{endpos}$ 中的任意一个位置 $pos$，则 $pos$ 处 $pa_x$ 的子串一定出现了一次。

那么另一次只要在 $[pos - \operatorname{len}(x) + \operatorname{len}(pa_x), pos - 1]$ 中有出现就行了。

总时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
const int N = 2e5 + 7;
struct T {
	int l, r;
} t[N<<6|1];
int rt[N<<1], f[N<<1], g[N<<1], tot, ans = 1;

int insert(int l, int r, int x) {
	int p = ++tot;
	if (l == r) return p;
	int mid = (l + r) >> 1;
	if (x <= mid) t[p].l = insert(l, mid, x);
	else t[p].r = insert(mid + 1, r, x);
	return p;
}

int merge(int p, int q) {
	if (!p || !q) return p | q;
	int o = ++tot;
	t[o].l = merge(t[p].l, t[q].l);
	t[o].r = merge(t[p].r, t[q].r);
	return o;
}

bool ask(int p, int l, int r, int L, int R) {
	if (!p) return 0;
	if (L <= l && R >= r) return 1;
	int mid = (l + r) >> 1;
	if (L <= mid && ask(t[p].l, l, mid, L, R)) return 1;
	if (R > mid && ask(t[p].r, mid + 1, r, L, R)) return 1;
	return 0;
}

struct SAM {
	int n, l, ch[N<<1][26], len[N<<1], pa[N<<1], t;
	char s[N];
	int pos[N<<1];
	inline void init() { pa[0] = -1; }
	inline void add(int c, int o) {
		int w = ++t, p = l;
		len[w] = len[l] + 1, pos[w] = o;
		while (~p && !ch[p][c]) ch[p][c] = w, p = pa[p];
		if (!~p) return pa[l=w] = 0, void();
		int q = ch[p][c];
		if (len[p] + 1 == len[q]) return pa[l=w] = q, void();
		int k = ++t;
		pa[k] = pa[q], pos[k] = pos[q], memcpy(ch[k], ch[q], sizeof(ch[k]));
		len[k] = len[p] + 1, pa[w] = pa[q] = k;
		while (~p && ch[p][c] == q) ch[p][c] = k, p = pa[p];
		l = w;
	}
	inline void build() {
		init();
		for (int i = 1; i <= n; i++) add(s[i] - 'a', i);
	}
	int b[N<<1], c[N];
	inline void sort() {
		for (int i = 1; i <= t; i++) ++c[len[i]];
		for (int i = 1; i <= n; i++) c[i] += c[i-1];
		for (int i = 1; i <= t; i++) b[c[len[i]]--] = i;
	}
	inline void work() {
		for (int i = 1, p = 0; i <= n; i++)
			p = ch[p][s[i]-'a'], rt[p] = insert(1, n, i);
		for (int i = t; i; i--)
			rt[pa[b[i]]] = merge(rt[pa[b[i]]], rt[b[i]]);
		for (int i = 1; i <= t; i++) {
			int x = b[i];
			if (!pa[x]) {
				f[x] = 1, g[x] = x;
				continue;
			}
			if (ask(rt[g[pa[x]]], 1, n, pos[x] - len[x] + len[g[pa[x]]], pos[x] - 1))
				f[x] = f[pa[x]] + 1, g[x] = x;
			else f[x] = f[pa[x]], g[x] = g[pa[x]];
			ans = max(ans, f[x]);
		}
	}
} sam;

int main() {
	rd(sam.n), rds(sam.s, sam.n), sam.build();
	sam.sort(), sam.work(), print(ans);
	return 0;
}
```

---

## 作者：小粉兔 (赞：17)

后缀数组再次证明了：SAM 能做的题，SA 也能做。

我们尝试改变一下定义，强制让 $t_{i + 1}$ 是 $t_i$ 的 border，如果不是的话可以减小 $t_i$ 的长度，显然不更劣。

在这样的调整下，我们发现可以这样定义：

令 $\mathrm{cool}(s)$ 表示强制要求 $t_1 = s$ 以及 $t_{i + 1}$ 是 $t_i$ 的 border 的，最大的 $k$ 值。

那么要求的即是 $s$ 的所有子串中的最大的 $\mathrm{cool}$ 值。

因为我们考虑使用 SA，所以令 $\mathrm{f}[i]$ 表示 $s$ 以 $i$ 开始的后缀的所有前缀中的最大的 $\mathrm{cool}$ 值。

然后我们考虑转移，显然从后往前转移（后缀的长度递增）是比较合理的。

假设我们要利用后面的信息求出 $\mathrm{f}[i] = k$，根据定义，要么 $\mathrm{f}[i] = 1$，要么有 $t_2$ 是 $t_1$ 的 border。

而如果 $t_2$ 是 $t_1$ 的 border，显然 $t_2$ 不仅是 $s[i : n]$ 的一个前缀，而且还必须在 $s[i + 1 : n]$ 中出现过至少 $1$ 次。

而且我们还有 $\mathrm{cool}(t_2) = k - 1$。

那么我们考虑后面的所有 $\mathrm{f}[j] = k - 1$ 的位置，它们就有可能转移给 $\mathrm{f}[i]$，然而实际上我们并不知道 $k$ 的值。

也就是说，与其考虑一个位置从后转移而来，不如换个角度，考虑让一个位置向前转移。

但是转移的过程却和后缀的 LCP 以及 $\mathrm{f}[i]$ 对应的前缀长度息息相关：  
一个 $i$ 能转移到更前面的 $j$ 当且仅当 $\mathrm{LCP}(j, i) \ge |s_i|$，其中 $s_i$ 即为 $\mathrm{cool}(s_i) = \mathrm{f}[i]$ 的一个 $s[i : n]$ 的前缀。

可以发现，**当有多个满足条件的 $\boldsymbol{s_i}$ 时，取最短的 $\boldsymbol{s_i}$ 才是正确的**。

----

这提示我们可能需要再维护一个对应的 $s_i$ 长度的信息，记作 $\mathrm{len}$。如果 $\mathrm{f}[i] = 1$，显然 $\mathrm{len}[i] = 1$。

这时你可能会想出这样的转移过程：  
如果 $\mathrm{LCP}(j, i) \ge \mathrm{len}[i]$，那么 $\mathrm{f}[j] = \mathrm{f[i]}$，$\mathrm{len}[j] = \mathrm{len[i]} + i - j$。  
（当然要在以 $\mathrm{f}$ 尽量大的前提下，让 $\mathrm{len}$ 尽量小）

但是很可惜这样是错误的，考虑 $s = \mathtt{acacaba}$。

对于位置 $7$ 有 $\langle \mathrm{f}, \mathrm{len} \rangle = \langle 1, 1 \rangle$，转移给位置 $1, 3, 5$。

对于位置 $5$ 有 $\langle \mathrm{f}, \mathrm{len} \rangle = \langle 2, 3 \rangle$，注意它**无法**转移给 $1$ 和 $3$。

但是，对于位置 $3$，真实的 $\langle \mathrm{f}, \mathrm{len} \rangle$ 应该为 $\langle 2, 3 \rangle$，然而在这里变成了 $\langle 2, 5 \rangle$，是被位置 $7$ 而非位置 $5$ 转移的。

进而影响到位置 $1$ 的值，最终影响答案，正确答案为 $3$ 但是这样求出来的答案为 $2$。

如果位置 $5$ 当 $\mathrm{f} = 1$ 时的 $\mathrm{len}$ 也能转移给位置 $3$ 就好了，但是这是不现实的，因为 $\mathrm{f}$ 可能太大无法一一转移。

----

其实正确方法是，不用同时维护 $\mathrm{len}$ 了，直接在使用时计算 $\mathrm{len}$ 即可。

因为实际上，如果 $\mathrm{len}$ 的计算正确，是不会影响 $\mathrm{f}$ 值的转移的，但是问题出在 $\mathrm{len}$ 的计算上。

如果我们已知 $\mathrm{f}[i] = k$，能否同时确定 $\mathrm{len}$ 的值呢？

- 如果 $k = 1$，则 $\mathrm{len}[i] = 1$。
- 否则我们还需要知道 $\mathrm{f}[i]$ 是从哪个 $\mathrm{f}[j] = k - 1$ 处转移而来的。
  - 如果有多处，应该选择 $\mathrm{len}[j]$ 最小的那一处。
  - 获得了 $\mathrm{len}[j]$ 之后，我们在 SA 中定位 $\mathrm{LCP}(i, x) \ge \mathrm{len}[j]$ 的可行的 $x$ 的区间。
  - 在线段树中查询这个区间内，在 $i$ 之后的，且离 $i$ 尽量近的位置 $y$。
  - 则 $\mathrm{len}[i] = \mathrm{len}[j] + y - i$。

确定了 $\mathrm{len}[i]$ 之后，就可以往前转移了。在 SA 中定位 $\mathrm{LCP}(x, i) \ge \mathrm{len}[i]$ 的可行的 $x$ 的区间。

然后用线段树，转移给区间内的所有在 $i$ 之前的位置，线段树要维护在 $k$ 尽量大的前提下让 $\mathrm{len}$ 尽量小。

时间复杂度为 $\mathcal O (n \log n)$，[评测链接](https://codeforces.com/contest/700/submission/73441291)。

---

## 作者：2018LZY (赞：13)

[更好的阅读体验哦~~](https://blog.csdn.net/qq_42886072/article/details/105092059)

[题目](https://www.luogu.com.cn/problem/CF700E)

简明题意:给你一个字符串$S$,要求构造$s_1,s_2,...s_k$,满足$\forall i\in[1,k]\cap N,s_i\in S$除第最后个串外,其他每个串都在后一个串出现两次以上.

**upd:方法1为错解,正确性无法保证(仅供娱乐),感谢[Treaker](https://www.luogu.com.cn/user/153898)的hack,如有类似方法1的正确实现方法,麻烦告知我.(2020/4/7)**
> $hack数据:$

> 10

> aaabaabaab
# 方法1
本文提供一种简短高效的STL+Hash的方法.

本文主要参考神犇[zhouyuyang](https://codeforces.ml/problemset/submission/700/36707934)在CF中的AC代码,并解释一下神犇的代码所蕴含的神奇思路.

## 单向$orz ~~zhouyuyang$.

## 单向$orz ~~zhouyuyang$.

## 单向$orz ~~zhouyuyang$.


# 正题

直接贴出神犇的代码并附本人菜鸡理解:
```cpp
#include<cstdio>
#include<map>
#include<vector>
#define ll long long
#define mk make_pair
#define pb push_back
using namespace std;
const int N=2e5+5;
const int Mo=1e9+713,Base=317;//神犇模数 
map<pair<int,int>,vector<int> >f[N];
//pair<int,int>代表一个字符串,第一元为hash值,第二元为长度.这样大大减小hash的错误.
//它所映射的vector,表示该字符串的所有开头位置. 
int n,i,j,ans,q[N];char s[N];
int pow[N],num[N];
int Hash(int l,int r){
	return (num[r]-(ll)num[l-1]*pow[r-l+1]%Mo+Mo)%Mo;
}
int main(){
	scanf("%d%s",&n,s+1);
	for (pow[0]=1,i=1;i<=n;i++){//hash常规操作 
		num[i]=((ll)num[i-1]*Base+s[i])%Mo;
		pow[i]=(ll)pow[i-1]*Base%Mo;
	}
	for (i=1;i<=n;i++) f[1/*这一维表示该字符串能形成的最大答案*/][mk(s[i],1)].pb(i);//根据上述定义,所以要这样预处理. 
	for (i=1;i<=n;i++) if (!f[i].empty()){ans=i;//更新答案. 
		map<pair<int,int>,vector<int> >::iterator it;
		for (it=f[i].begin();it!=f[i].end();it++){
			int len=it->first.second;
			vector<int>a=it->second;
			int m=a.size()-1;
			for (j=0;j<m;j++)
				q[j]=Hash(a[j]+len,a[j+1]-1);
				//把相邻两个该串之间的串进行预处理. 
			for (int l=0,r=1;l<m;l=r,r++){
				for (;r<m&&q[r-1]==q[r];r++);//是循环串就不断增长. 
				f[i+r-l][mk(Hash(a[l],a[r]+len-1),a[r]-a[l]+len)].pb(a[l]);
				//每次处理完后[l,r]被合并成新的串.循环次数为(r-l+1),那么对答案的最大贡献就为r-l 
			}
		}
	}
	printf("%d",ans);
}
```
## 时间复杂度证明
首先我们来看复杂度最迷的地方.
```cpp
for (int l=0,r=1;l<m;l=r,r++){
	for (;r<m&&q[r-1]==q[r];r++);//是循环串就不断增长. 
	f[i+r-l][mk(Hash(a[l],a[r]+len-1),a[r]-a[l]+len)].pb(a[l]);
	//每次处理完后[l,r]被合并成新的串.循环次数为(r-l+1),那么对答案的最大贡献就为r-l 
}
```

我们直接考虑极限:每次处理完都是$r=l+1$,这样生成的状态显然最多.

这样状态复杂度显然$O(n^2)$?不不不.

注意到每次生成的都是**极大**循环串,生成出来的串的长度也至少为$2len$.

你可能会问:它们不可能相交吗?

> 证明: (归纳法)
显然对于底层(一个字符而言)不可能重叠.
那么合并的时候发现可能存在重叠的新状态$[l,r][r,r']$.
但是这俩新状态对应的字符串一定不同,否则与极大循环串矛盾.

最后我们根据底层得出复杂度:

最坏情况下底层每两个相同相邻字符之间会生成$\log(n)$个状态.

例如"abaca",第一个'a'与第二个'a'生成一堆状态.第二个'a'与第三个'a'生成一堆状态.

这样总共有$O(n)$级别的相同相邻字符,每次生成$\log(n)$个状态,加上map,天然的常数$\log(n)$.总复杂度即为$O(n*\log^2(n))$.

# 小结
这个方法避免使用SAM+线段树合并的高深思路,复杂度也不逊色.

加上本题大时限+CF超强评测机,一点也不用担心会T.

# 方法2
>SAM+线段树合并.

结论:

 1. $s_{i-1}一定为s_i$的后缀,不然把$s_i$后面截去一定可以变为$s_{i-1}$的后缀,这样$s_i$长度更短,且与$s_{i-1}$的匹配次数不变,显然更优.
 2. $对于SAM中状态x,y(y为x父节点),则y所对应的所有子串在x最长串中的匹配次数相等$.
 $证明:(反证法).设s为x的最长串,a,b为y的两个子串$
 $举个例子,设a="abcb",b="babcb",s="ababcb",此时a,b在s的出现次数不同$
 $a,b$在相同状态,所以一定有$w="bababcb"$.
 因为$s$为$x$最长串,所以$w$一定为$x$的一个孩子.
 根据定义得:$|\operatorname{endpos(s)}|>|\operatorname{endpos(w)}|$.
 所以一定存在一个$p\in \operatorname{endpos(s)}-\operatorname{endpos(w)}$
那么必然存在一个位置$a存在,b不存在$,与$ab$在相同状态矛盾,证毕!

综上:我们的父节点一定取最长的最优,因为这样它包含的串最多且对后面影响相同.
所以我们可以考虑在$parent$树上$dp$.

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define lc t[x].l
#define rc t[x].r
using namespace std;
const int N=1<<19|9;
char s[N];
int n,ans,root[N],f[N],top[N];

//SAM
struct node {int len,fa,v[26],pos;}tr[N]; int last=1,tot=1,b[N],c[N];
void add(int c,int now) {
	int p=last,x=last=++tot; tr[x].len=tr[p].len+1; tr[x].pos=now;
	for(	;p&&!tr[p].v[c];p=tr[p].fa) tr[p].v[c]=x;
	if(!p) tr[x].fa=1;
	else {
		int q=tr[p].v[c],y;
		if(tr[p].len+1==tr[q].len) tr[x].fa=q;
		else {
			tr[y=++tot]=tr[q];
			tr[y].len=tr[p].len+1;
			tr[q].fa=tr[x].fa=y;
			for(	;p&&tr[p].v[c]==q;p=tr[p].fa) tr[p].v[c]=y;
		}
	}
}

//主席树 
struct T {int l,r;}t[N*18]; int cnt;
void insert(int &x,int l,int r,int p) {
	if(!x) x=++cnt;
	if(l==r) return ;
	int mid=(l+r)>>1;
	if(p<=mid) insert(lc,l,mid,p);
	else insert(rc,mid+1,r,p);
}
int merge(int x,int y) {
	if(1LL*x*y==0) return x|y;
	int z=++cnt;
	t[z].l=merge(t[x].l,t[y].l);
	t[z].r=merge(t[x].r,t[y].r);
	return z;
}
bool query(int x,int l,int r,int L,int R) {
	if(!x) return 0;
	if(L<=l&&r<=R) return 1;
	int mid=(l+r)>>1;
	if(L<=mid&&query(lc,l,mid,L,R)) return 1;
	if(mid< R&&query(rc,mid+1,r,L,R)) return 1;
	return 0;
}

int main() {
	scanf("%d %s",&n,s+1);
	for(int i=1;i<=n;i++) add(s[i] -= 'a',i),insert(root[last],1,n,i);
	for(int i=1;i<=tot;i++) c[tr[i].len]++;
	for(int i=1;i<=n;i++) c[i]+=c[i-1];
	for(int i=tot;i ;i--) b[c[tr[i].len]--]=i;
	for(int i=tot,j,k;i>1;i--) j=b[i],k=tr[j].fa,root[k]=merge(root[k],root[j]);
	ans=1;
	for(int i=2;i<=tot;i++) {
		int x=b[i],fa=tr[x].fa,p=tr[x].pos;
		if(fa==1) {f[x]=1; top[x]=x; continue;}
		int t=query(root[top[fa]],1,n,p-tr[x].len+tr[top[fa]].len,p-1);
		if(t) f[x]=f[fa]+1,top[x]=x,ans=max(ans,f[x]);
		else  f[x]=f[fa],top[x]=top[fa];
	}
	printf("%d\n",ans); return 0;
}

```


---

## 作者：bztMinamoto (赞：12)

　　看了一个中午的代码终于弄懂了……$yyb$大佬强无敌……

　　一开始以为是SAM建好之后直接上$dp$，直接用$parent$树上的儿子节点更新父亲，因为parent树上节点不同说明出现次数必定不同。但交上去一发WA了。才发现自己这种想法不能保证$parent$树上的父亲必定在儿子中出现过超过两次……

　　还是来说说正解吧。我们先对原串建好SAM，并记录下每一个节点的任意一个$endpos$。考虑一下如何判断一个串是否在另一个串中出现，如果一个串（设串$A$）在另一个串（设串$B$）中出现了大于等于两次，那么在原串的任意位置的串$B$中都出现了两次。

　　于是考虑一下维护每一个点的$endpos$集合，这个只要用线段树就行了。如果$A$在$B$中出现了两次，那么$A$的$endpos$集合在$[pos[B]-len[B]+len[A],pos[B]]$中出现了至少两次（其中$pos[B]$表示$B$的任意一个$endpos$）。

　　不难发现有一个$dp$，每一个$parent$树上的父亲节点都可能转移到儿子节点，于是从上到下$dp$。又因为$parent$树上父亲是儿子的严格后缀，所以必然在儿子里出现了一次，那么只要考虑$endpos[A]$中是否有元素在$[pos[B]-len[B]+len[A],pos[B]-1]$中就行了
```
//minamoto
#include<cstdio>
#include<cstring>
using namespace std;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
const int N=444444;
int fa[N],ch[N][26],l[N],f[N],a[N],c[N],pos[N],top[N];char s[N];
int last=1,cnt=1,n,ans=1;
void ins(int c,int k){
    int p=last,np=++cnt;last=np,l[np]=l[p]+1,pos[np]=k;
    for(;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;
    if(!p) fa[np]=1;
    else{
        int q=ch[p][c];
        if(l[q]==l[p]+1) fa[np]=q;
        else{
            int nq=++cnt;l[nq]=l[p]+1,pos[nq]=pos[q];
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[nq]=fa[q],fa[np]=fa[q]=nq;
            for(;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;
        }
    }
}
void calc(){
    for(int i=1;i<=cnt;++i) ++c[l[i]];
    for(int i=1;i<=cnt;++i) c[i]+=c[i-1];
    for(int i=1;i<=cnt;++i) a[c[l[i]]--]=i;
}
int L[N*25],R[N*25],rt[N],tot;
void modify(int &now,int l,int r,int x){
    now=++tot;if(l==r) return;
    int mid=l+r>>1;
    if(x<=mid) modify(L[now],l,mid,x);
    else modify(R[now],mid+1,r,x);
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    int z=++tot;
    L[z]=merge(L[x],L[y]);
    R[z]=merge(R[x],R[y]);
    return z;
}
int query(int x,int l,int r,int ql,int qr){
    if(!x) return 0;if(ql<=l&&qr>=r) return 1;
    int mid=l+r>>1;
    if(ql<=mid&&query(L[x],l,mid,ql,qr)) return 1;
    if(qr>mid&&query(R[x],mid+1,r,ql,qr)) return 1;
    return 0;
}
int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;++i) ins(s[i]-'a',i),modify(rt[last],1,n,i);
    calc();
    for(int i=cnt;i>1;--i) rt[fa[a[i]]]=merge(rt[fa[a[i]]],rt[a[i]]);
    for(int i=2;i<=cnt;++i){
        int u=a[i],ff=fa[u];
        if(ff==1){f[u]=1,top[u]=u;continue;}
        int x=query(rt[top[ff]],1,n,pos[u]-l[u]+l[top[ff]],pos[u]-1);
        if(x) f[u]=f[ff]+1,top[u]=u;
        else f[u]=f[ff],top[u]=top[ff];
        cmax(ans,f[u]);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：nkwhale (赞：10)

[更不好的阅读体验（个人博客）](https://www.cnblogs.com/whale-at-cola/p/sulotion-cf700e.html)

题目传送门：[luogu](https://www.luogu.com.cn/problem/CF700E)，[CF](codeforces.com/problemset/problem/700/E)。

单字符串的子串相关问题，考虑先套上一个 SAM。

考虑 $s_p$ 对应的 SAM 上的节点 $x$，因为 $s_p$ 为 $s_{p+1}$ 的子串，所以最优情况下 $s_{p+1}$ 一定为 $s_p$ 的后缀，即 $s_{p+1}$ 对应的节点一定在 $x$ 的 fail 树子树中。

但是，SAM 中一个节点对应多个 endpos 集合相同的串，当产生一个新的 $s_p$ 时应该取对应节点的一个什么长度的串呢？发现对于节点 $x$ 对应的所有长度的串，因为它们 endpos 集合相同，所以每个长度的串可产生的 $s_{p+1}$ 所对应的节点 $y$ 的集合都一样（考虑 $x$ 对应的 $s_p$ 增长后如果 $s_{p+1}$ 不能再对应某一个节点 $y$，那说明增长前后的串 endpos 一定不同），而又要对于不同的 $s_{p-1}$ 接纳进来的最多，所以长度直接取 $maxlen_x$ 一定不会使情况变劣（为方便，下文中将 $x$ 节点对应的串中长为 $maxlen_x$ 的串成为 $mls_x$）。

那么考虑一个树形 dp，$dp_x$ 表示 $x$ 子树中按上述构造方法能生成的最长的 $s$ 序列，方程为 $dp_x=max \{dp_y|y\in subtree_x \wedge show(mls_x,mls_y)\geq 2\}$（其中 $show(s1,s2)$ 表示 $s1$ 在 $s2$ 中的出现次数）。

根据定义，对于一个 $x$ 满足 $show(mls_p,mls_x)\geq 2$ 的 $p$ 一定是它到根路径上深度浅的一段，设其中最深的点为 $g_x$，可以发现 $g_{fa_x}$ 一定为 $g_x$ 的祖先节点，所以预处理出每个点的 $g_x$ 就可以很方便的 dp 了。

预处理的一个麻烦之处就是判断要 $show(mls_x,mls_y)\geq 2$ 是否为真，套路地线段树合并维护出每个点的 endpos 集合，对于 $endpos_y$ 中的一个位置 $p$，其所对应的串即为 $[p-maxlen_y+1,p]$ 这个区间。因为 $x$ 为 $y$ 祖先，所以 $p$ 一定也在 $endpos_x$  中，记 $p$ 的前驱（在 $endpos_x$ 中）为 $q$，若 $q$ 所对应的串 $[q-maxlen_x+1,q]$ 被 $[p-maxlen_y+1,p]$ 包含，则说明 $show(mls_x,mls_y)\geq 2$ 成立，否则不成立。因为所对应的串本质相同，所以 $p$ 取 $endpos_y$ 中的任意元素均可，实现中取第一个比较方便。

代码见下，码风不很能看，勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register

const int N=404040,M=N*80;
int n,tot=1,las=1,ch[N][26],ml[N],fa[N],fp[N],ton[N],tp[N],g[N],rt[N];
int cnt,sum[M],ls[M],rs[M],dp[N];

inline void ext(int c,int k){
	int x=++tot,p=las,q;
	las=x,ml[x]=ml[p]+1,fp[x]=k;
	while(!ch[p][c]&&p) ch[p][c]=x,p=fa[p];
	if(!p) return fa[x]=1,void();
	if(ml[q=ch[p][c]]==ml[p]+1) return fa[x]=q,void();
	ml[++tot]=ml[p]+1,fa[tot]=fa[q],fa[q]=fa[x]=tot;
	memcpy(ch[tot],ch[q],sizeof ch[tot]);
	while(ch[p][c]==q) ch[p][c]=tot,p=fa[p];
}

inline void topo(){
	for(re int i=1;i<=tot;++i) ++ton[ml[i]];
	for(re int i=tot-1;i;--i) ton[i]+=ton[i+1];
	for(re int i=1;i<=tot;++i) tp[ton[ml[i]]--]=i;
}

inline void upd(int &k,int l,int r,int x){
	sum[k=++cnt]=1;
	if(l==r) return ;
	int d=(l+r)>>1;
	if(x<=d) upd(ls[k],l,d,x);
	else upd(rs[k],d+1,r,x);
}

inline int mrg(int k1,int k2,int l,int r){
	if(!k1||!k2) return k1|k2;
	int k=++cnt,d=(l+r)>>1;sum[k]=sum[k1]+sum[k2];
	if(l!=r) ls[k]=mrg(ls[k1],ls[k2],l,d),rs[k]=mrg(rs[k1],rs[k2],d+1,r);
	return k;
}

inline void init(){
	for(re int i=1;i<=tot;++i) if(fp[i]!=0x3f3f3f3f) upd(rt[i],1,n,fp[i]);
	for(re int i=1;i<=tot;++i) g[i]=fa[i];
	for(re int i=1,x=tp[i],y=fa[x];i<tot;y=fa[x=tp[++i]])
		fp[y]=min(fp[y],fp[x]),rt[y]=mrg(rt[y],rt[x],1,n);
}

inline int pre(int k,int l,int r,int x){
	if(x<l||!sum[k]) return 0;
	if(l==r) return l;
	int d=(l+r)>>1,res=pre(rs[k],d+1,r,x);
	return res?res:pre(ls[k],l,d,x);
}

inline bool check(int x,int y){return fp[y]-ml[y]<=pre(rt[x],1,n,fp[y]-1)-ml[x];}
inline void solve(){
	for(re int i=1,x=tp[i],y=fa[x];i<tot;y=fa[x=tp[++i]]){
		while(g[x]&&!check(g[x],x)) g[x]=fa[g[x]];
		if(ml[g[y]]>ml[g[x]]) g[y]=g[x];
	}
	for(re int i=1,x=tp[i];i<tot;x=tp[++i])
		dp[fa[x]]=max(dp[fa[x]],dp[x]),dp[g[x]]=max(dp[g[x]],dp[x]+1);
	printf("%d\n",dp[1]);
}

char s[N];
signed main(){
	memset(fp,0x3f,sizeof fp);
	scanf("%d%s",&n,s+1);
	for(re int i=1;i<=n;++i) ext(s[i]-'a',i);
	topo(),init(),solve();
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：6)

# [CF700E Cool Slogans](https://www.luogu.com.cn/problem/CF700E)

这是一道用后缀数组优化DP的神题，所以我们必须先抛开后缀数组，从DP的角度来想题。

首先，我们发现，对于一组合法的$s_1,\dots,s_n$，我们一定可以**掐头去尾**，使得$s_i$是$s_{i-1}$的$\text{Border}$，即首尾的一个相同子串。这很好理解——因为掐头去尾剩下的东西一定是原来的一个子串，而$s_i$本来就在$s_{i-1}$中出现了两次，故$s_i$的子串，无论掐成啥样，都必定会在$s_{i-1}$中仍然出现两次。

于是我们就可以设想DP状态了：令$f_i$表示以第$i$个字符开头的所有子串中，最多能套娃几层$\text{Border}$。则答案即为$\max\limits_{i=0}^{n-1}f_i$。

我们考虑如何求出$f_i$。显然，它的DP顺序应该是**倒着的**，因为长串只能由短串转移而来。

于是我们就可以设想出一种DP方程出来：

$f_i$可以由$f_j$转移而来，当且仅当$i<j$且$\operatorname{LCP}(i,j)\geq|s_j|$，其中$|s_j|$是$j$所代表的$\text{Border}$的长度。

这启发我们要记录一个$len_j$表示上述的$\text{Border}$长度。显然，这个$len_j$应是**越短越好**。

则我们的转移条件即为：$i<j\ \land\ \operatorname{LCP}(i,j)\geq len_j$。

------------

但我们应该想想，**这真的是充分必要条件吗**？如果$\operatorname{LCP}(i,j)<len_j$，就不可以转移了吗？这时候，如果我们适当减小$f_j$的话，它对应的$len_j$也会跟着减小，最终就有可能减小到$\leq\operatorname{LCP}$的地步，就可以转移了。那是不是我们对于每个$j$，就要二分出来可以转移的$f_j$了呢？

这看上去很有道理的样子——但我们的担心实际上**完全是多余**的。$f_j$的减小，就意味着$\text{Border}$套娃层数的减小。而套娃次数更少的状态，实际上**被保存在了其它位置**。

例如，我们有这样一条关系：$f_j\leftarrow f_k$，即$k$转移到$j$。

现在我们想尝试用$j$转移到$i$去，但发现$\operatorname{LCP}$太短不够。于是我们减小$f_j$。

但是$f_j$一减小，就相当于**退化成$f_k$了**，而$f_k$的状态，我们是**有备份的**，即$k$本身，它也可以转移到$i$去。因此，我们不用担心更小的$f_j$是否更优——它的祖先会解决这个问题的。

------------

好的我们现在回到转移本身。很明显$len_j$也是一个需要维护的值。或许你们会认为$len_i$可以同$f_i$一起转移。即，我们先求出$f_i$，然后找出所有$f_j=f_i-1$的位置，然后尝试用$len_j$更新$len_i$。

但是这又有问题了——之前我们减小$f_j$的想法，是否在这里就会实现？

例如，我们这里还是有一条$f_j\leftarrow f_k$。

现在我们又想转移$i$了。但是$j$仍然转移不了，我们就被迫从$f_k$转移来。显然，这里的$len_i$长度就应该是$k-i+len_k$。

但是，如果它可以从$j$转移来的话（当然$f_j$应该减小到$f_i-1$的大小），长度很有可能就成为了$j-i+len_j$。显然这个$len_j$应该等于$len_k$，毕竟$k$是$j$的祖先，则如果它们套娃层数一致，长度就应该一致。

而又应有$j<k$，故实际上$j-i+len_j<k-i+len_k$，应该从$j$转移而不是从$k$转移。

我们发现，之前在$f$的转移中不起效的情况，在这里却又起效了。应该如何应对呢？

------------

先从$len$的部分缓缓，我们先回到求出$f_i$的过程。这里我们又有两种想法，即填表法（由$i$考虑所有合法的$j$）与刷表法（由$j$转移到所有能转移的$i$）。如果我们选择前一种的话，不同的$j$的$\operatorname{LCP}$变化毫无规律，不好转移；而如果选择后一种，因为我们已经固定了$len_j$，所以我们只需要求出所有$\operatorname{LCP}(i,j)\geq len_j$的位置即可。依据$\text{LCP Lemma}$，这在后缀数组中**是从$rk_i$出发向左向右的一段区间**。于是我们只需要在后缀数组上二分求出这段区间，然后用线段树进行区间取$\max$即可。

然后我们就要考虑求出$len_i$了。显然，在求出$f_i$的过程中，我们可以顺手求出$len_j$，即所有$f_j=f_i-1$的$j$中，最小的$len$。这便是我们上文中“$len_j$应该等于$len_k$”那句话中，那个始终不变的$len_j$。我们仍然可以找出$\operatorname{LCP}(i,j)\geq len_j$的区间，然后找到区间里最小的那个$j$，则有$len_i=j-i+len_j$。关于区间里最小的$j$，因为我们同时还要要求$j>i$，所以仍然必须得用线段树实现。

则时间复杂度为$O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200100;
int res;
namespace Suffix_Array{
	int x[N],y[N],buc[N],sa[N],ht[N],rk[N],n,m,LG[N],mn[N][20];
	char s[N];
	bool mat(int a,int b,int k){
		if(y[a]!=y[b])return false;
		if((a+k<n)^(b+k<n))return false;
		if((a+k<n)&&(b+k<n))return y[a+k]==y[b+k];
		return true;
	}
	void SA(){
		for(int i=0;i<n;i++)buc[x[i]=s[i]]++;
		for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
		for(int i=n-1;i>=0;i--)sa[--buc[x[i]]]=i;
		for(int k=1;k<n;k<<=1){
			int num=0;
			for(int i=n-k;i<n;i++)y[num++]=i;
			for(int i=0;i<n;i++)if(sa[i]>=k)y[num++]=sa[i]-k;
			for(int i=0;i<=m;i++)buc[i]=0;
			for(int i=0;i<n;i++)buc[x[y[i]]]++;
			for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
			for(int i=n-1;i>=0;i--)sa[--buc[x[y[i]]]]=y[i];
			swap(x,y);
			x[sa[0]]=num=0;
			for(int i=1;i<n;i++)x[sa[i]]=mat(sa[i],sa[i-1],k)?num:++num;
			if(num>=n-1)break;
			m=num;
		}
		for(int i=0;i<n;i++)rk[sa[i]]=i;
		for(int i=0,k=0;i<n;i++){
			if(!rk[i])continue;
			if(k)k--;
			int j=sa[rk[i]-1];
			while(i+k<n&&j+k<n&&s[i+k]==s[j+k])k++;
			ht[rk[i]]=k;
		}
		for(int i=2;i<n;i++)LG[i]=LG[i>>1]+1;
		for(int i=1;i<n;i++)mn[i][0]=ht[i];
		for(int j=1;j<=LG[n-1];j++)for(int i=1;i+(1<<j)-1<n;i++)mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
	}
	int LCP(int x,int y){
		if(x>y)swap(x,y);
		x++;
		int k=LG[y-x+1];
		return min(mn[x][k],mn[y-(1<<k)+1][k]);
	}
	void Range(int x,int len,int &L,int &R){//ask for the range of elements that LCP[x,i]>=len is held.
		x=rk[x];
		int l,r;
		l=0,r=x;
		while(l<r){
			int mid=(l+r)>>1;
			if(LCP(mid,x)>=len)r=mid;
			else l=mid+1;
		}
		L=r;
		l=x,r=n-1;
		while(l<r){
			int mid=(l+r+1)>>1;
			if(LCP(mid,x)>=len)l=mid;
			else r=mid-1;
		}
		R=l;
	}
}
using namespace Suffix_Array;
struct SegTree{
	int f,len;
	SegTree(){f=1,len=1;}
	SegTree(int A,int B){f=A,len=B;}
	friend bool operator<(const SegTree &x,const SegTree &y){
		if(x.f!=y.f)return x.f<y.f;
		return x.len>y.len;
	}
};
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
namespace SG1{
	SegTree tag[N<<2];
	#define pushdown(x) tag[lson]=max(tag[lson],tag[x]),tag[rson]=max(tag[rson],tag[x]),tag[x]=SegTree()
	void modify(int x,int l,int r,int L,int R,SegTree sg){
		if(l>R||r<L)return;
		if(L<=l&&r<=R){tag[x]=max(tag[x],sg);return;}
		pushdown(x),modify(lson,l,mid,L,R,sg),modify(rson,mid+1,r,L,R,sg);
	}
	SegTree query(int x,int l,int r,int P){
		if(l==r)return tag[x];
		pushdown(x);
		return (P<=mid)?query(lson,l,mid,P):query(rson,mid+1,r,P);
	}
}
namespace SG2{
	int mn[N<<2];
	void pushup(int x){mn[x]=min(mn[lson],mn[rson]);}
	void modify(int x,int l,int r,int P){
		if(l>P||r<P)return;
		if(l==r){mn[x]=sa[P];return;}
		modify(lson,l,mid,P),modify(rson,mid+1,r,P),pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if(l>R||r<L)return 0x3f3f3f3f;
		if(L<=l&&r<=R)return mn[x];
		return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
	}
}
int main(){
	scanf("%d%s",&n,s),m='z',SA(),memset(SG2::mn,0x3f,sizeof(SG2::mn));
	for(int i=n-1,L,R;i>=0;i--){
		SegTree tmp=SG1::query(1,0,n-1,rk[i]);
		res=max(res,tmp.f);//in this phase, f is the real f, while len is still the former status'.
		if(tmp.f!=1){//need to get the real len.
			Range(i,tmp.len,L,R);
			tmp.len+=SG2::query(1,0,n-1,L,R)-i;
		}
		tmp.f++;
		Range(i,tmp.len,L,R);
		SG1::modify(1,0,n-1,L,R,tmp);
		SG2::modify(1,0,n-1,rk[i]);
	}
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：ニヒル (赞：6)

SAM好题  
首先我们假设我们能判断一个串在另一个串里有无出现两次  
此时的问题就变成了在parent树上的树型dp  
为什么一定在parent树上？  
考虑某个串a在他非parent树子树的节点对应的串b上出现了两次，那么这个串b肯定是由a子树里某个串加上一个后缀得到的，这样子显然不优  
树型dp怎么转移？  
大概就是如果这个串的某个祖先节点刚好在这里出现了两次，那么该点的dp值就是这个祖先节点的dp值+1  
找祖先的话就是各显神通了，倍增也行，双指针也行   
那么现在考虑怎么知道一个串在另一个串里出现两次  
显然每个串的最长值通过建SAM我们是可以知道的，同时一个出现位置的值是可以知道的  
那么我们就可以得到长串出现的一个区间的范围  
只要在这个范围里查短串是否出现两遍就可以了  
那么用线段树合并维护一个right集合，查询短串的right是不是在长度范围里出现两次即可，因为维护的是right，所以长度范围的前短串长度个点是不能算的，要去掉

代码如下：
```cpp
#include<bits/stdc++.h>
#define N 400040
#define lson tr[now].l
#define rson tr[now].r
using namespace std;

int n;
char s[200020];

struct SM
{
    struct point 
    {
        int son[26],len,mx,at,fa;
    }t[N];

    struct tree
    {
        int sum,l,r;
    }tr[N<<5];

    int last=1,cnt=1,gg=0;
    int tot=0;
    int rt[N];
    int top[N],dp[N];
    bool sz[N],vis[N];
    vector<int> g[N];

    void add(int c)
    {
        int p=last;
        int np=++cnt;
        t[np].len=t[p].len+1;
        t[np].at=++gg;
        sz[np]=1;
        while(p&&(!t[p].son[c]))
        {
            t[p].son[c]=np;
            p=t[p].fa;
        }
        if(!p) t[np].fa=1;
        else
        {
            int q=t[p].son[c],nq;
            if(t[q].len==t[p].len+1)
            {
                t[np].fa=q;
            }
            else
            {
                nq=++cnt;
                t[nq]=t[q];
                t[nq].len=t[p].len+1;
                t[np].fa=t[q].fa=nq;
                t[nq].at=t[np].at;
                while(p&&(t[p].son[c]==q))
                {
                    t[p].son[c]=nq;
                    p=t[p].fa;
                } 
            }
        }
        last=np;
    }

    void push_up(int now)
    {   
        tr[now].sum=tr[lson].sum+tr[rson].sum;
    }

    void insert(int &now,int l,int r,int pos,int val)
    {
        if(!now) now=++tot;
        if(l==r) 
        {
            tr[now].sum=val;
            return ;
        }
        int mid=(l+r)>>1;
        if(pos<=mid)
        {
            insert(lson,l,mid,pos,val);
        }
        else
        {
            insert(rson,mid+1,r,pos,val);
        }
        push_up(now);
    }

    int query(int now,int l,int r,int ll,int rr)
    {
        if(ll>rr) return 0;
        if(!now) return 0;
        if(ll<=l&&r<=rr)
        {
            return tr[now].sum;
        } 
        int mid=(l+r)>>1;
        if(rr<=mid)
        {
            return query(lson,l,mid,ll,rr);
        }
        else
        {
            if(ll>mid)
            {
                return query(rson,mid+1,r,ll,rr); 
            }
            else
            {
                return query(lson,l,mid,ll,mid)+query(rson,mid+1,r,mid+1,rr);
            }
        }
    } 

    int merge(int a,int b,int l,int r)
    {
        if(!a) return b;
        if(!b) return a;
        int now=++tot;
        if(l==r)
        {
            tr[now].sum=1;
            return now;
        }
        int mid=(l+r)>>1;
        tr[now].l=merge(tr[a].l,tr[b].l,l,mid);
        tr[now].r=merge(tr[a].r,tr[b].r,mid+1,r);
        push_up(now);
        return now;
    }

    int dfs(int now)
    {
        if(sz[now])
        {
            insert(rt[now],1,n,t[now].at,1);
        }
        for(int i=0;i<g[now].size();i++)
        {
            dfs(g[now][i]);
            rt[now]=merge(rt[now],rt[g[now][i]],1,n);
        }
    }

    int dfs1(int now)
    {
        if(query(rt[top[t[now].fa]],1,n,t[now].at-t[now].len+t[top[t[now].fa]].len,t[now].at-1))
        {
            dp[now]=dp[t[now].fa]+1;
            top[now]=now;
        }
        else
        {
            dp[now]=dp[t[now].fa];
            top[now]=top[t[now].fa];
        }
        for(int i=0;i<g[now].size();i++)
        {
            dfs1(g[now][i]);
        }
    }

    int print(int now,int l,int r)
    {
        if(l==r)
        {
            if(tr[now].sum) printf("%d ",l);
            return 0; 
        }
        int mid=(l+r)>>1;
        if(tr[lson].sum) print(lson,l,mid);
        if(tr[rson].sum) print(rson,mid+1,r);
    }

    int solve()
    {
        for(int i=1;i<=cnt;i++)
        {
            g[t[i].fa].push_back(i);
        }
        dfs(1); 
        for(int i=0;i<g[1].size();i++)
        {
            top[g[1][i]]=g[1][i];
            dp[g[1][i]]=1;
            for(int j=0;j<g[g[1][i]].size();j++)
            {
                dfs1(g[g[1][i]][j]);
            }
        }
        int ans=0;
        for(int i=1;i<=cnt;i++)
        {
            ans=max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
}sm;

int main()
{
    scanf("%d",&n);
    scanf("%s",s);
    n=strlen(s);
    for(int i=0;i<n;i++)
    {
        sm.add(s[i]-'a');
    }
    sm.solve();
} 
```


---

## 作者：1saunoya (赞：4)

### 题意:

我们定义 $\forall i ,s_i$ 是给定串 $S$ 的子串，且 $s_{i-1}$ 在 $s_{i}$ 要出现至少两次。求最大的 $k$，使得 $\forall i,s_i \in S$。

### sol:

我们考虑到，对于一个点 $i$，$fa_i$ 是 $i$ 的子串，并且是后缀，我们定义 $g_i$ 是上次匹配到的点，$f_i$ 是匹配到这个点的最长长度，那么一定是能匹配就匹配，这样显然是最优的，不能就复制父节点信息接着往下玩。


我们考虑到 $1$ ~ $i$ 的一条链上后缀都相同但是长度不同。

然后我们要考虑如果 $g_u$ 的子树包含 $v$，那么 $g_u$ 对应的字符串在 $v$ 对应的字符串 出现了一次，易证。

所以我们只需要线段树合并出来每个点 $i$ 的子树信息就可以了。就是说哪个出现过哪个没出现过。

然后的话我们就考虑一下另一次出现怎么求呢。显然你出现的位置是 $pos_v$ 那么我们要把 $pos_v$ 这个点去掉。并且我们要在 $[pos_v - len_v + len_{g_u} , pos_v - 1]$ 这段区间内找到点。

为什么，我们考虑一下，$len_v$ 是 $v$ 所对应的字符串的长度，那么 $len_{g_u}$ 同理，因为你的上个转移点是 $g_u$ 所以显然是 $g_u$ 但是长度至少为 $len_{g_u}$ 所以最后一个点必须在 $pos_v - len_v + len_{g_u}$ 后面。

代码挺好写的.jpg

### code:

```cpp
// clang-format off
// powered by c++11
// by Isaunoya
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i=(x);i<=(y);++i)
#define Rep(i,x,y) for(register int i=(x);i>=(y);--i)
using namespace std;using db=double;using ll=long long;
using uint=unsigned int;using ull=unsigned long long;
using pii=pair<int,int>;
#define Tp template
#define fir first
#define sec second
Tp<class T>void cmax(T&x,const T&y){if(x<y)x=y;}Tp<class T>void cmin(T&x,const T&y){if(x>y)x=y;}
#define all(v) v.begin(),v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
Tp<class T>void sort(vector<T>&v){sort(all(v));}Tp<class T>void reverse(vector<T>&v){reverse(all(v));}
Tp<class T>void unique(vector<T>&v){sort(all(v)),v.erase(unique(all(v)),v.end());}inline void reverse(string&s){reverse(s.begin(),s.end());}
const int SZ=1<<23|233;
struct FILEIN{char qwq[SZ],*S=qwq,*T=qwq,ch;
#ifdef __WIN64
#define GETC getchar
#else
inline char GETC(){return(S==T)&&(T=(S=qwq)+fread(qwq,1,SZ,stdin),S==T)?EOF:*S++;}
#endif
inline FILEIN&operator>>(char&c){while(isspace(c=GETC()));return*this;}inline FILEIN&operator>>(string&s){s.clear();while(isspace(ch=GETC()));if(!~ch)return*this;s=ch;while(!isspace(ch=GETC())&&~ch)s+=ch;return*this;}
inline FILEIN&operator>>(char*str){char*cur=str;while(*cur)*cur++=0;cur=str;while(isspace(ch=GETC()));if(!~ch)return*this;*cur=ch;while(!isspace(ch=GETC())&&~ch)*++cur=ch;*++cur=0;return*this;}
Tp<class T>inline void read(T&x){bool f=0;while((ch=GETC())<48&&~ch)f^=(ch==45);x=~ch?(ch^48):0;while((ch=GETC())>47)x=x*10+(ch^48);x=f?-x:x;}
inline FILEIN&operator>>(int&x){return read(x),*this;}inline FILEIN&operator>>(ll&x){return read(x),*this;}inline FILEIN&operator>>(uint&x){return read(x),*this;}inline FILEIN&operator>>(ull&x){return read(x),*this;}
inline FILEIN&operator>>(double&x){read(x);bool f=x<0;x=f?-x:x;if(ch^'.')return*this;double d=0.1;while((ch=GETC())>47)x+=d*(ch^48),d*=.1;return x=f?-x:x,*this;}
}in;
struct FILEOUT{const static int LIMIT=1<<22;char quq[SZ],ST[233];int sz,O,pw[233];
FILEOUT(){set(7);rep(i,pw[0]=1,9)pw[i]=pw[i-1]*10;}~FILEOUT(){flush();}
inline void flush(){fwrite(quq,1,O,stdout),fflush(stdout),O=0;}
inline FILEOUT&operator<<(char c){return quq[O++]=c,*this;}inline FILEOUT&operator<<(string str){if(O>LIMIT)flush();for(char c:str)quq[O++]=c;return*this;}
inline FILEOUT&operator<<(char*str){if(O>LIMIT)flush();char*cur=str;while(*cur)quq[O++]=(*cur++);return*this;}
Tp<class T>void write(T x){if(O>LIMIT)flush();if(x<0){quq[O++]=45;x=-x;}do{ST[++sz]=x%10^48;x/=10;}while(x);while(sz)quq[O++]=ST[sz--];}
inline FILEOUT&operator<<(int x){return write(x),*this;}inline FILEOUT&operator<<(ll x){return write(x),*this;}inline FILEOUT&operator<<(uint x){return write(x),*this;}inline FILEOUT&operator<<(ull x){return write(x),*this;}
int len,lft,rig;void set(int l){len=l;}inline FILEOUT&operator<<(double x){bool f=x<0;x=f?-x:x,lft=x,rig=1.*(x-lft)*pw[len];return write(f?-lft:lft),quq[O++]='.',write(rig),*this;}
}out;
#define int long long
struct Math{
vector<int>fac,inv;int mod;
void set(int n,int Mod){fac.resize(n+1),inv.resize(n+1),mod=Mod;rep(i,fac[0]=1,n)fac[i]=fac[i-1]*i%mod;inv[n]=qpow(fac[n],mod-2);Rep(i,n-1,0)inv[i]=inv[i+1]*(i+1)%mod;}
int qpow(int x,int y){int ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}int C(int n,int m){if(n<0||m<0||n<m)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int gcd(int x,int y){return!y?x:gcd(y,x%y);}int lcm(int x,int y){return x*y/gcd(x,y);}
}math;
// clang-format on
int n;
const int maxn = 4e5 + 54;
char s[maxn];

int rt[maxn];
struct SegMentTree {
  const static int maxnode = maxn << 5;
  int ls[maxnode], rs[maxnode], cnt;

  SegMentTree() { cnt = 0; }

  void upd(int& p, int l, int r, int x) {
    if (!p) p = ++cnt;
    if (l == r) return;
    int mid = l + r >> 1;
    if (x <= mid)
      upd(ls[p], l, mid, x);
    else
      upd(rs[p], mid + 1, r, x);
  }

  int merge(int x, int y) {
    if (!x || !y) return x | y;
    int qwq = ++cnt;
    ls[qwq] = merge(ls[x], ls[y]);
    rs[qwq] = merge(rs[x], rs[y]);
    return qwq;
  }

  int qry(int p, int a, int b, int l, int r) {
    if (!p) return 0;
    if (a <= l && r <= b) return 1;
    int mid = l + r >> 1, ans = 0;
    if (a <= mid) ans += qry(ls[p], a, b, l, mid);
    if (b > mid) ans += qry(rs[p], a, b, mid + 1, r);
    return ans;
  }
} smt;

int ans = 1;
struct SAM {
  int ch[maxn][26], fa[maxn], len[maxn], pos[maxn], las, cnt;
  SAM() { las = cnt = 1; }

  void add(int c, int id) {
    int p = las, np = las = ++cnt;
    pos[np] = id, len[np] = len[p] + 1, smt.upd(rt[np], 1, n, id);
    for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
    if (!p) {
      fa[np] = 1;
    } else {
      int q = ch[p][c];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        int nq = ++cnt;
        memcpy(ch[nq], ch[q], sizeof(ch[q]));
        pos[nq] = pos[q], fa[nq] = fa[q], fa[q] = fa[np] = nq, len[nq] = len[p] + 1;
        for (; p && ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
      }
    }
  }

  vector<int> g[maxn];
  void dfs(int u) {
    for (int v : g[u]) {
      dfs(v);
      rt[u] = smt.merge(rt[u], rt[v]);
    }
  }

  void build(char* s) {
    char* cur = s;
    int id = 0;
    while (*cur) {
      int c = (*cur++) - 'a';
      add(c, ++id);
    }
    rep(i, 2, cnt) g[fa[i]].pb(i);
  }

  int f[maxn], G[maxn];
  void dfs2(int u) {
    for (int v : g[u]) {
      if (fa[v] == 1) {
        f[v] = 1, G[v] = v;
      } else {
        if (smt.qry(rt[G[u]], pos[v] - (len[v] - len[G[u]]), pos[v] - 1, 1, n))
          f[v] = f[u] + 1, G[v] = v;
        else
          f[v] = f[u], G[v] = G[u];
      }
      dfs2(v);
    }
    cmax(ans, f[u]);
  }
} sam;

signed main() {
  // code begin.
  in >> n >> s, sam.build(s), sam.dfs(1), sam.dfs2(1);
  out << ans << '\n';
  return 0;
  // code end.
}
```

---

## 作者：Kinandra (赞：4)

标签: 字符串, 后缀自动机(SAM).

容易发现必定存在一种最佳方案使得 $s_i$ 时 $s_{i-1}$ 的后缀(事实上同时也可以是前缀), 那么我们就求这样的方案就好了.

我们对 $S$ 建立 SAM , 得到parent树, 那么我们就有一个显然的DP: 对于parent树上的每一个节点 $u$ , 找到最近的在 $u$ 中出现两次的祖先 $v$ , 那么 $u$ 的答案为 $v$ 的答案 $+1$ .

由于答案一次转移最多 $+1$, 所以我们直接取与 $u$ 父亲答案相同的最浅的祖先作为 $v$ 转移即可.

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char s[200005];

int lst[200005], ch[400005][26], len[400005], fa[400005], pos[400005], idcnt;
void ins(int c, int i) {
    int p = lst[i - 1], np = lst[i] = ++idcnt;
    len[np] = len[p] + 1, pos[np] = i;
    while (p && !ch[p][c]) ch[p][c] = np, p = fa[p];
    if (!p) return fa[np] = 1, void();
    int q = ch[p][c];
    if (len[q] == len[p] + 1) return fa[np] = q, void();
    int nq = ++idcnt;
    len[nq] = len[p] + 1, memcpy(ch[nq], ch[q], sizeof(ch[q]));
    fa[nq] = fa[q], fa[np] = fa[q] = nq, pos[nq] = pos[q];
    while (ch[p][c] == q) ch[p][c] = nq, p = fa[p];
}

int rt[400005], segcnt;
struct Seg {
    int ls[10000007], rs[10000007];
    void ins(int &k, int l, int r, int p) {
        k = ++segcnt;
        if (l == r) return;
        int mid = l + r >> 1;
        (p <= mid) ? ins(ls[k], l, mid, p) : ins(rs[k], mid + 1, r, p);
    }

    int merge(int x, int y) {
        if (!(x && y)) return x ^ y;
        int k = ++segcnt;
        ls[k] = merge(ls[x], ls[y]), rs[k] = merge(rs[x], rs[y]);
        return k;
    }

    bool check(int k, int l, int r, int st, int en) {
        if (!k || st > r || en < l) return 0;
        if (st <= l && en >= r) return 1;
        int mid = l + r >> 1;
        return check(ls[k], l, mid, st, en) ? 1
                                            : check(rs[k], mid + 1, r, st, en);
    }
} seg;

int cnt[200005], a[400005];
void topo_sort() {
    for (int i = 1; i <= idcnt; ++i) ++cnt[len[i]];
    for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= idcnt; ++i) a[cnt[len[i]]--] = i;
}

int f[400005];
int main() {
    scanf("%d%s", &n, s + 1);
    lst[0] = idcnt = 1;
    for (int i = 1; i <= n; ++i)
        ins(s[i] - 'a', i), seg.ins(rt[lst[i]], 1, n, i);
    topo_sort();
    for (int i = idcnt; i > 1; --i)
        rt[fa[a[i]]] = seg.merge(rt[fa[a[i]]], rt[a[i]]);
    int res = 1;
    for (int i = 2, u, v; i <= idcnt; ++i) {
        u = a[i], v = fa[u];
        if (v == 1) {
            f[u] = 1, fa[u] = u;
            continue;
        }
        seg.check(rt[fa[v]], 1, n, pos[u] - len[u] + len[fa[v]], pos[u] - 1)
            ? (f[u] = f[v] + 1, fa[u] = u)
            : (f[u] = f[v], fa[u] = fa[v]);
        res = max(res, f[u]);
    }
    printf("%d\n", res);
    return 0;
}
```


---

## 作者：Calculatelove (赞：3)

[CF 700E](http://codeforces.com/problemset/problem/700/E)。

## Description

给出一个长度为 $n$ 的字符串 $\mathrm{str}$。你需要构造一个尽量字符串序列 $s_1, s_2, \cdots, s_k$，满足：

- 对于任意 $1 \leq i \leq n$，$s_i$ 为 $\mathrm{str}$ 的子串。
- 对于任意 $1 < i \leq n$，$s_{i - 1}$ 在 $s_i$ 中至少出现了两次（可重叠）。

只需求出 $k$ 的最大值即可。

数据范围：$1 \leq n \leq 2 \times 10^5$。  
时空限制：$4000 \ \mathrm{ms} / 500 \ \mathrm{MiB}$。

## Solution

> #### 引理 1

> 一定存在一种最优方案，使得 $s_{i - 1}$ 为 $s_i$ 的 border。

> #### 证明

> 对于一个串 $s_i$，将其首尾多余的部分去掉，此时 $s_i$ 即为 $s_{i - 1}$ 的 border。按 $i$ 从大到小将 $s_i$ 的多余部分去掉即可得到满足该性质的方案。

根据「引理 1」，可以得知 $s_{i - 1}$ 为 $s_i$ 的严格后缀。考虑将原串的 SAM 建出。

> #### 引理 2

> 在 SAM 的 parent 树上，对于任意一个状态 $x$ 与其祖先状态 $y$，$y$ 表示的所有子串在 $x$ 表示的最长串的出现次数相同。

> #### 证明

> ![P2.png](https://s2.loli.net/2022/04/17/WkSscZQ4OPn9xpm.png)

> 反证法，考虑如图所示的子串结构。串 $S$ 是状态 $x$ 所表示的最长串；串 $T_1, T_2$ 是状态 $y$ 所表示的任意两个子串，这两个子串在 $S$ 中的出现次数不同，必然会出现如图所示的结构。此时可以构造一个串 $S'$ 来使得 $T_1, T_2$ 在 $S'$ 中的出现次数相同。

> 由于 $\mathrm{endpos}(x) \subsetneqq \mathrm{endpos}(y)$，则出现 $S$ 的地方，前面总会跟着一个串 $T_2$。这样的话会使得 $S, T_2$ 组合成一个 $S'$，可以推出 $\mathrm{endpos}(S) = \mathrm{endpos}(S')$，这与 $S$ 为状态 $x$ 所表示的最长串矛盾，故假设不成立。

> Q.E.D

根据「引理 2」，可以得知对于 SAM 的每个状态，我们都只需要记录其所表示的最长串的等级信息即可。

此时就可以在 parent 树上 dp，设 $f_i$ 表示从根节点到节点 $i$ 的最大等级，设 $g_i$ 表示从根节点到节点 $i$ 最大等级串的状态编号。

- 若 $x$ 所表示的最长串中出现了两次 $g_{\mathrm{Fa}_x}$ 所表示的最长串，则

$$
f_x = f_{{\mathrm{Fa}_x}} + 1
$$
$$
g_x = x
$$

- 否则

$$
f_x = f_{\mathrm{Fa}_x}
$$
$$
g_x = g_{\mathrm{Fa}_x}
$$

运用可持久化线段树合并维护 $\mathrm{endpos}$ 集合，来判断每次是否可以成功转移。

时间复杂度 $\mathcal{O}(n \log n)$。

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 200100;

int n;
char str[N];

namespace SGT {
	const int SIZE = 10001000;

	int cT;
	struct node {
		int lc, rc;
	} t[SIZE];

	void insert(int &p, int l, int r, int x) {
		p = ++ cT;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (x <= mid)
			insert(t[p].lc, l, mid, x);
		else
			insert(t[p].rc, mid + 1, r, x);
	}

	int merge(int p, int q) {
		if (!p || !q) return p ^ q;
		int x = ++ cT;
		t[x].lc = merge(t[p].lc, t[q].lc);
		t[x].rc = merge(t[p].rc, t[q].rc);
		return x;
	}

	bool ask(int p, int l, int r, int s, int e) {
		if (!p) return 0;
		if (s <= l && r <= e) return 1;
		int mid = (l + r) >> 1;
		if (s <= mid && ask(t[p].lc, l, mid, s, e)) return 1;
		if (mid < e && ask(t[p].rc, mid + 1, r, s, e)) return 1;
		return 0;
	}
}

int ans;

namespace SAM {
	const int SIZE = N * 2; 

	int cT = 1, Last = 1;
	struct node {
		int trans[26];
		int link, maxl;
	} t[SIZE];

	int root[SIZE], pos[SIZE];

	int tot, head[SIZE], ver[SIZE], Next[SIZE];
	void add_edge(int u, int v) {
		ver[++ tot] = v;    Next[tot] = head[u];    head[u] = tot;
	}

	void extend(int id, int c) {
		int p = Last,
			np = Last = ++ cT;

		SGT::insert(root[np], 1, n, id);
		pos[np] = id;

		t[np].maxl = t[p].maxl + 1;

		for (; p && t[p].trans[c] == 0; p = t[p].link) t[p].trans[c] = np;

		if (!p) {
			t[np].link = 1;
		} else {
			int q = t[p].trans[c];

			if (t[q].maxl == t[p].maxl + 1) {
				t[np].link = q;
			} else {
				int nq = ++ cT;

				t[nq] = t[q], t[nq].maxl = t[p].maxl + 1, pos[nq] = pos[q], t[np].link = t[q].link = nq;
				for (; p && t[p].trans[c] == q; p = t[p].link) t[p].trans[c] = nq;
			}
		}
	}

	void build_tree() {
		for (int i = 2; i <= cT; i ++)
			add_edge(t[i].link, i);
	}

	void dfs(int u) {
		for (int i = head[u]; i; i = Next[i]) {
			int v = ver[i];
			dfs(v);
			root[u] = SGT::merge(root[u], root[v]);
		}
	}

	int f[SIZE], g[SIZE];

	void dp(int u) {
		if (t[u].link == 1) {
			f[u] = 1, g[u] = u;
		} else if (u > 1) {
			int pa = t[u].link;
			if (SGT::ask(root[g[pa]], 1, n, pos[u] - t[u].maxl + t[g[pa]].maxl, pos[u] - 1)) {
				f[u] = f[pa] + 1, g[u] = u;
			} else {
				f[u] = f[pa], g[u] = g[pa];
			}
		}

		ans = std::max(ans, f[u]);

		for (int i = head[u]; i; i = Next[i]) {
			int v = ver[i];
			dp(v);
		}
	}
}

int main() {
	scanf("%d", &n);
	scanf("%s", str + 1);

	for (int i = 1; i <= n; i ++)
		SAM::extend(i, str[i] - 'a');

	SAM::build_tree();
	SAM::dfs(1);
	SAM::dp(1);

	printf("%d\n", ans);

	return 0;
}
```

---

## 作者：xzzduang (赞：3)

[传送门](https://codeforces.com/problemset/problem/700/E)

首先，我们可以强制 $s_{i-1}$ 是 $s_i$ 的后缀，这样是不会使答案变劣的，因为把 $s_{i}$ 后面不能和 $s_{i-1}$ 匹配的那段砍掉并不会影响答案。

所以我们选的 $s$ 其实是后缀自动机 Parent Tree 上的一条从根出发的链部分节点，且同个节点最多选一个（因为同个节点的不同串不可能满足出现 2 次的关系）。但是现在问题来了，我们怎么知道这个节点中应该选哪个，所以这里先要知道一个引理：

> 对于节点 $u$ 和节点 $v$ 满足 $u$ 是 $v$ 的祖先，若取出 $v$ 中最长的串，则 $u$ 中所有的串在此串中出现的位置是一样的。

神 iostream 给出了严谨的证明，所以我这里给出一个可能会形象具体的，方便大家感性理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/lt10gyke.png?x-oss-process=image/resize,m_lfit,h_270,w_425)

如图，线段代表的是 $v$ 中的那个最长串的出现位置，点代表 $u$ 中的串的出现位置，发现上面的结论不成立只有一种情况，即 $u$ 中某个较短的串塞的进线段里，较长的串塞不进去，就是如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/w8rpwm80.png?x-oss-process=image/resize,m_lfit,h_270,w_425)

蓝线代表那个较长的串，红线代表较短的，但是可以发现每一个线段前面都有一小段一样的蓝的，把那一小段蓝的加进线段里也会形成一个和 $v$ 的 endpos 相同的串，而且这个串比 $v$ 中最长串，也就是图中的那个线段要长，因为 endpos 一样，这个新串也应该在 $v$ 中，又因为它更长，这与图中线段是 $v$ 中最长的串矛盾，所以结论成立。

 我们选的那条链，深度最大的那个节点肯定贪心的选最长的，而深度第二大的因为深度最大的选了最长，根据引理，它选什么长度要么都可以要么都不行，所以它也应该贪心地选最长的......所以对于所有选的节点，我们都应该选最长。

接下来就可以直接 DP 了，$f_u$ 表示从根一直下来选到 $u$，且 $u$ 选了的最大答案，转移很显然是 $f(u)=\max\{f(fa_u),f(v)+1\}$ ，其中 $v$ 是 $u$ 的祖先且在 $u$ 中至少出现两次，考虑一个简单的优化：$f$ 显然是关于深度单调不减的，所以不可能有 $f(v)$ 能超过 $f(fa_u)$，其实我们只用管 $f(v)=f(fa_u)$ 的 $v$ 就好了，且这样的 $v$ 肯定是希望它越浅越好，乱搞一下维护出这样的 $v$。

至于判断是否出现了 2 遍，套路的线段树合并维护 endpos 即可。 

```cpp
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define N 400005
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
struct edge{
	int b,n;
}e[2*N];
int n,h[2*N],tot;
char s[N];
inline void charu(int a,int b){
	e[++tot].b=b,e[tot].n=h[a],h[a]=tot;
}
struct SuffixAutoMaton{
	int tail,pool,pos[2*N],nxt[2*N][26],fail[2*N],len[2*N];
	inline void init(){tail=pool=1,fail[1]=0;}
	inline void insert(int c){
		len[++pool]=len[tail]+1,pos[pool]=len[pool];
		int p=tail;tail=pool;
		for(;p && !nxt[p][c];p=fail[p]) nxt[p][c]=tail;
		if(!p) return (void)(fail[tail]=1);
		int q=nxt[p][c];
		if(len[p]+1==len[q]) return (void)(fail[tail]=q);
		len[++pool]=len[p]+1,fail[pool]=fail[q],pos[pool]=pos[q];
		memcpy(nxt[pool],nxt[q],sizeof(nxt[q]));
		fail[q]=fail[tail]=pool;
		for(;nxt[p][c]==q;p=fail[p]) nxt[p][c]=pool;
	}
}sam;
struct segmentTree{
	int ls,rs,sum;
}d[50*N];
int nd,rt[N*2];
void update(int &k,int l,int r,int x){
	k=++nd;
	if(l==r) return (void)(d[k].sum=1);
	int mid=l+r>>1;
	if(x<=mid) update(d[k].ls,l,mid,x);
	else update(d[k].rs,mid+1,r,x);
	d[k].sum=d[d[k].ls].sum+d[d[k].rs].sum;
}
int merge(int x,int y){
	if(!x || !y) return x|y;
	int k=++nd;
	d[k].sum=d[x].sum+d[y].sum;
	d[k].ls=merge(d[x].ls,d[y].ls);
	d[k].rs=merge(d[x].rs,d[y].rs);
	return k;
}
int query(int k,int l,int r,int x,int y){
	if(x<=l && r<=y) return d[k].sum;
	int mid=l+r>>1,res=0;
	if(x<=mid) res=query(d[k].ls,l,mid,x,y);
	if(mid+1<=y) res+=query(d[k].rs,mid+1,r,x,y);
	return res;
}
void dfs(int u){
	if(sam.pos[u]) update(rt[u],1,n,sam.pos[u]);
	for(int i=h[u];i;i=e[i].n){
		int v=e[i].b;
		dfs(v);
		rt[u]=merge(rt[u],rt[v]);
	}
}
int f[2*N],ans,lnk[2*N];
void solve(int u,int fa){
	if(u!=1){
		int p=lnk[fa];f[u]=f[p];
		if(p==1) f[u]++;
		else if(query(rt[p],1,n,sam.pos[u]-sam.len[u]+sam.len[p],sam.pos[u]-1)) f[u]++;
	}
	lnk[u]=(f[u]==f[fa]?lnk[fa]:u);
	lnk[1]=1;
	for(int i=h[u];i;i=e[i].n){
		int v=e[i].b;
		solve(v,u);
	}
	ans=max(ans,f[u]);
}
int main(){
	n=read();
	scanf("%s",s+1);
	sam.init();
	for(int i=1;i<=n;++i) sam.insert(s[i]-'a');
	for(int i=1;i<=sam.pool;++i) charu(sam.fail[i],i);
	dfs(1);
	solve(1,0);
	cout<<ans;
	return 0;
}

```



---

## 作者：Echidna (赞：3)

> 给出串 $S$ ，请问满足 $A_{n-1}$ 在 $A_n$ 中出现至少两次且都是 $S$ 子串的字符串序列 $A$ 的最长长度是多少？
>
> $1\le n\le 2\times 10^5$

这道题是 TLE_Automat 大佬给我的题。~~（在线膜 TAM %%）~~ 然后看了眼，好啊，不会啊，这看起来完全不可做啊。

但是稍微想一想之后，就可以从基本贪心取得一个结论：$A_{n-1}$ 必定是 $A_n$ 的后缀，因为如果不是的话你可以将 $A_n$ 的一个后缀删去。

接着从后缀链的性质可以看出来，$A_{n-1}$ 和 $A_n$ 必定在同一后缀链上的两个等价类中出现，这也就意味着 $A$ 序列上的字符串必定都在同一后缀链的等价类中出现。

在这个方向开始构想之后，就有几个结论便需要我们证明。

​		$\text{Conclusion 1}$  不可能存在 $A_n$ 和 $A_n-1$ 在同一个等价类出现的情况。

​	证明：如果存在这种情况的话，那么由 $A_n$ 和 $A_{n-1}$ 在同一等价类的条件可以得出 $A_n$ 有一个 $\text{endpos}$ 恰好在自己内。所以，这个模式会一直向左右延伸，直到串的尽头，而这时，$A_n$ 和 $A_{n-1}$ 也不可能 $\text{endpos}$ 相同，因此结论成立。

这个结论其实也说明，一个等价类内的任意两个字符串最多以某一方向包含 $1$ 次。

​		$\text{Conclusion 2}$  在后缀链上跳跃时，只要选定了一个起点，总是向上跳最矮的高度总是最优的。

​	证明：显然，不证了。

通过这两个结论，我们发现，我们要做的其实就是对于每一个等价类，找到一个离它最近的 parent 树上祖先满足它的这个祖先可以在它出现两次。现在的问题也许你已经发现了，我们刚刚的描述对于字符串和等价类十分混淆，这其实是因为我们还没有确定等价类和字符串在这个问题中的关系。换言之：给你两个等价类，你怎么在每一个等价类内选出一个字符串然后判定它们两个是否以某种方向出现两次呢？

​		$\text{Conclusion 3}$  为一个等价类作代表的字符串是恰好是这个等价类中最长的字符串，即，

​		如果 $\text{str}(u)\mathop{\not\subset}\limits^\text{Twice}str(v)$ ，那么不存在 $s\in u$ 使得 $s\mathop{\subset}\limits^\text{Twice}str(v)$ ，最短的也不行。

​	证明：首先，等价类 $v$ 选出自己最长的字符串 $str(v)$ 是很明智的。我们现在只需要证明无论等价类 $u$ 选出最长的或是最短的字符串都无关结果即可。

​	若存在这么两个等价类 $u$ 和 $v$ ，$\text{str}(u)=A+B$ ，$B$ 在 $\operatorname{str}(v)$ 中出现两次，而 $A+B$ 则只有一次。

​	我们考虑两种情况：第一种情况是 $\text{str}(v)$ 的所有出现只有一次前面恰好有 $A$  。这种情况下，$A+B$ 的 $\text{endpos}$ 显然跟 $B$ 的$\text{endpos}$ 不同，等价类 $u$ 不存在；第二种情况是 $\text{str}(v)$ 的所有出现前面都恰好有 $A$  ，此时 $A+str(v)$ 的 $\text{endpos}$ 恰好与 $v$ 的 $\text{endpos}$ 一致，等价类 $v$ 不存在，结论一定成立。

至于刚刚的这个结论以及其证明是怎么想出来的，实际上我是瞎 jr 找例子试出这个结论之后再想办法构造证明的，这个结论非常不显然。

于是，我们用每个等价类的 $\text{str}$ 来代替这个等价类是正确的，这也暗示 $A_{-1}$ 一定是某一个等价类的 $\text{str}$ 。

现在，我们假设给定两个节点的 $\text{str}$ 我们判定其中一个是否在另一个出现两次的时间复杂度为 $f(n)$ 。我们现在只关心我们最少要判定多少次才能对每一个点都找到它的最近可以跳的祖先。

![](https://cdn.luogu.com.cn/upload/image_hosting/0ai8uq79.png?x-oss-process=image/resize,m_lfit,h_1000,w_400)

我们考虑这么一棵 parent 树。请问，节点 $4$ 的跳跃边有没有可能指向 $3$ 呢？那有没有可能指向 $1$ 呢？

答案是，不可能指向 $3$ ，但是可能指向 $1$ 。具体为什么请您独立思考，这个问题非常简单，写出证明是在这里浪费空间。

或者，我们形式化地表达这个规律：我们设 $\text{jump}(x)$ 表示节点 $x$ 的跳跃边的最终节点。那么
$$
\text{dep}(\text{jump}(x))=\min_{e\in son_x}\{\text{dep}(\text{jump}(e))\}
$$
所以，这个式子有什么用吗？你会发现，如果 parent 树恰好是条链，这个式子的意义就是尺取算法，而尺取算法的判定数是 $O(n)$ 级别的。那么，我们把尺取放到树上，这个算法的时间复杂度是什么呢？这里可以使用势能法来证明，但是扰动法却更简单一点。

由于树是一条链时判定数是 $O(n)$ 的，并且在你加入了一条新链之后，除了新链以外的其他部分的判定数只减不增，而新链这个部分的判定数仍是 $O(size)$ 的，于是添加一条链后判定数仍为 $O(n)$ ，其中 $n$ 为现在树的节点个数。

现在我们考虑如何进行判定。像 3.6 的套路一样，维护 $\text{endpos}$ 集，判定是否 $u$ 两次包含 $v$ 时只需要在 $u$ 的 $\text{endpos}$ 中随便找出来一个值 $x$ ，然后看是否在 $[x-\text{len}(u)+1,x]$ 内存在两个 $\text{endpos}(v)$ 的元素即可，上述操作均可在 $O(\log |S|)$ 内完成，而 parent 树的节点数又是 $O(|S|)$ 的，于是总时间复杂度为 $O(|S| \log |S|)$ ，是可接受的范围。

找到 $\text{jump}$ 链接之后的 dp 非常简单，我觉得大家都会，所以不再浪费空间了。

~~最后吐槽：为什么要用玄学 DP 呢，势能分析数据结构多香啊~~


---

## 作者：TLE_Automat (赞：3)

题意题面已经写的很清楚了，下面直接上解题过程。

## Step $1$ :

看到题目很难下手，不妨反过来想，**假定**我们已经找到了一个最长的答案，如下图：

![](https://s4.ax1x.com/2022/02/18/HockEn.md.png)

（因为 $s_2$ 在 $s_1$ 中出现至少 $2$ 次，$s_3$ 在 $s_2$ 中出现至少两次，所以 $s_2 , s_3$ 画了两遍） 

我们可以发现，把 $s_3$ 最右边的 $s_1 , s_2$ 全砍去也是合法答案，并且不会比之前的答案更劣，如下图：

​                     ![](https://s4.ax1x.com/2022/02/18/HocLMF.md.png) 

所以我们通过构造的方式证明了：

- 一定存在一个最优解，使得 $s_{i+1}$ 是 $s_i$ 的后缀。 

这让我们联想到了后缀自动机上建出的 $\text{parent}$ 树，因为在这颗树上，父节点的 $\text{endpos}$ 集合所代表的所有串，一定是子节点 $\text{endpos}$ 集合所代表的所有串的后缀。

## Step $2$ :

在上一步中，我们想到了 $\text{parent}$ 树，那怎么才能在这棵树上构造出一个最长且满足题意的序列呢？

我们不妨先考虑 $s_i$ 与 $s_{i+1}$ 之间的关系。（为了简洁，下文所说的**树**若不作特殊说明，均指 $\text{parent}$ 树）

1. $s_i$ 与 $s_{i+1}$ 可能来自树上同一结点 $u$ 所代表的等价类中的两个不同后缀。但这种情况是**不成立**的！

   考虑反证，如果成立，即 $s_{i+1}$ 在 $s_i$ 中不仅作为后缀出现，还作为非后缀的子串出现，那么这个子串的右端点会形成一个新的$\text{endpos}$ 集合（如果不形成新的，可以无限套娃直到形成新的），这就与 $s_i$ 与 $s_{i+1}$ 属于同一个等价类矛盾。

2. $s_{i+1}$ 为结点 $x$ 所代表的等价类中的后缀，$s_i$ 为 $y$ 结点所代表的等价类中的后缀，且 $x$ 是 $y$ 的祖先。这种情况显然是**成立**的！ 

   但值得注意的是，$x$ 所代表的等价类中的任意一个后缀跟 $s_i$ 的匹配都是等价的，不会存在 $x$ 中一个后缀是 $s_i$ 的非后缀子串而另一个后缀不是的情况，证明同上。

   还有就是对于一个 $x$ 的 $\text{endpos}$ 集合中的任意一个元素的后缀，他与 $s_i$ 的匹配也是等价的。

所以现在我们只要线段树合并出树上每个结点的 $\text{endpos}$ 集合，然后如何 $\text{dp}$ 其就很 $\text{trivial}$ 了。

 ```cpp
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) ((int)((x).size()))
#define mkp make_pair
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=2e5+10;
const int MAXT=4e5+10;

namespace SAM
{	
	int len[MAXT],fa[MAXT];
	int nxt[MAXT][26],ep[MAXT];
	int sz,lst;

	inline void add(char ch,int pos)
	{
		int c=ch-'a';
		
		int cur=sz++;
		len[cur]=len[lst]+1;
        ep[cur]=pos;

		int p=lst;
		for(;p!=-1 && !nxt[p][c];p=fa[p]) 
			nxt[p][c]=cur;
		
		if(p==-1) fa[cur]=0;
		else
		{
			int q=nxt[p][c];
			if(len[p]+1==len[q]) fa[cur]=q;
			else
			{
				int clone=sz++;
				fa[clone]=fa[q];
                ep[clone]=ep[q];
                memcpy(nxt[clone],nxt[q],sizeof(nxt[q]));
				len[clone]=len[p]+1;
                
				for(;p!=-1 && nxt[p][c]==q;p=fa[p])
					nxt[p][c]=clone;
				fa[q]=fa[cur]=clone;
			}
		}
		lst=cur;
	}
	
	inline void build(char *s,int n)
	{
		fa[0]=-1; sz=1;
		len[0]=lst=0;
		for(int i=1;i<=n;i++)
			add(s[i],i);
	}
}
using SAM::fa;
using SAM::len;
using SAM::ep;

struct Segment_tree
{
    int cnt_id=0;
    int ls[MAXT*43],rs[MAXT*43];
    bool sum[MAXT*43];

    inline void push_up(int root){ sum[root]=sum[ls[root]]|sum[rs[root]]; }
    inline void update(int &root,int l,int r,int idx)
    {
        if(!root) root=++cnt_id;
        if(l==r) return sum[root]=true,(void)0;

        int mid=(l+r)>>1;
        if(idx<=mid) update(ls[root],l,mid,idx);
        else update(rs[root],mid+1,r,idx); 
        push_up(root);
    }
    inline bool query(int root,int l,int r,int sp,int ep)
    {
        if(!root) return false;
        if(sp<=l && r<=ep) return sum[root];
        int mid=(l+r)>>1;
        bool res=false;
        if(sp<=mid) res|=query(ls[root],l,mid,sp,ep);
        if(ep>mid) res|=query(rs[root],mid+1,r,sp,ep);
        return res;
    }
    inline int merge(int x,int y,int l,int r)
    {
        if(!x || !y) return x^y;
        int cur=++cnt_id;
        if(l==r) return sum[cur]=sum[x]|sum[y],cur;

        int mid=(l+r)>>1;
        ls[cur]=merge(ls[x],ls[y],l,mid);
        rs[cur]=merge(rs[x],rs[y],mid+1,r);
        return push_up(cur),cur;
    }

} T;

int n;
char s[MAXN];

int rt[MAXT];
vector<int> G[MAXT];
inline void dfs_edpos(int u)
{
    if(ep[u]) T.update(rt[u],1,n,ep[u]);
    for(int v : G[u])
    {
        dfs_edpos(v);
        rt[u]=T.merge(rt[u],rt[v],1,n);   
    }
}

int ans;
int dp[MAXT],tp[MAXT];
inline void dfs_dp(int u)
{
    for(int v : G[u])
    {
        if(!u) dp[v]=1,tp[v]=v;
        else
        {
            dp[v]=dp[u]; tp[v]=tp[u];
            if(T.query(rt[tp[u]],1,n,ep[v]-len[v]+len[tp[u]],ep[v]-1))
                dp[v]++,tp[v]=v;
        }
        ans=max(ans,dp[v]);
        dfs_dp(v);
    }
}

int main()
{
	scanf("%d%s",&n,s+1);
    SAM::build(s,n);

    for(int i=1;i<SAM::sz;i++)
        G[fa[i]].push_back(i);
    dfs_edpos(0);
    dfs_dp(0);
    printf("%d\n",ans);

	return 0;
}

 ```









---

## 作者：FZzzz (赞：3)

好题。

感觉有些地方其他题解讲的不是很清楚，这里来讲一下。

首先给出一个性质：一定存在一个最优的方案，使得 $s_i$ 是 $s_{i+1}$ 的后缀。

证明：如果不是，把 $s_i$ 在 $s_{i+1}$ 中最后一次出现的位置后面都砍掉，答案不会更差。

好的现在我们就可以愉快地在 SAM 上 dp 了。设 $dp_i$ 为以第 $i$ 个节点代表的字符串开始，最多能够拼一个多长的序列……

诶不对啊，这样一个节点是有可能代表多个字符串的啊？

这样是没有区别的。如果你不想看证明你可以感性理解一下，如果想看的话可以去@iostream 神仙的题解。

好的现在我们可以考虑转移了。然后我们可以贪心得转移到它 parent 树上的第一个在它里面出现了两次的节点，这样做的正确性容易证明。

等等我们怎么去判断一个节点是不是在它里面出现了两次呢？

线段树合并处理一下 endpos 集合即可，具体做法不难想这里不再赘述。

这样我们就可以在 parent 树上倍增或者树剖套二分找出这个节点了，然后就可以转移了，复杂度 $O(n\log^2n)$。

这种东西多半是过不了的……然后我就不会了，看题解。

题解并没有说，但是其实采用了一种类似于双指针的东西，记录每个点的转移点的下面的一个点。如果发现可以转移到这个点，就转移到这个点。

但是这样的话，如果下面多个点都可以转移，那不就亏了吗？我其实也想过类似的东西，但是就因为这种想法卡住了。

后来想了一下，其实是不会的。

可以用归纳法证明：如果一个点 $u$ 上面的点全都按这种方法做了没有出锅，那么假设这个点会出锅。假设它转移到了上面那个点 $v$ 下面的某一个点 $w$，那么根据这种做法，$w$ 一定是无法转移到 $v$ 的，并且 $w$ 的转移点一定和 $v$ 的转移点相同。所以 $u$ 直接转移到 $v$ 不会亏。

这样的话就可以一路转移下来了。算上线段树，复杂度 $O(n\log n)$。

还是有一点细节的，并且注意这里的线段树合并要可持久化。我的写法好像空间常数有一点大，不过能过就行。

code：
```cpp
#include<algorithm>
#include<map>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n;
char s[maxn];
struct node{
	int l,r;
	node* ch[2];
	int sum;
	node(int l,int r):l(l),r(r),sum(0){
		ch[0]=ch[1]=0;
	}
	void modify(int x,int k){
		sum+=k;
		if(l<r){
			int mid=l+(r-l)/2;
			if(x<=mid){
				if(!ch[0]) ch[0]=new node(l,mid);
				ch[0]->modify(x,k);
			}
			else{
				if(!ch[1]) ch[1]=new node(mid+1,r);
				ch[1]->modify(x,k);
			}
		}
	}
	int query(int ql,int qr){
		if(ql<=l&&qr>=r) return sum;
		else{
			int ans=0;
			if(ch[0]&&ql<=ch[0]->r) ans+=ch[0]->query(ql,qr);
			if(ch[1]&&qr>=ch[1]->l) ans+=ch[1]->query(ql,qr);
			return ans;
		}
	}
};
node* merge(node* a,node* b){
	if(!a) return b;
	if(!b) return a;
	node* x=new node(a->l,a->r);
	x->sum=a->sum+b->sum;
	x->ch[0]=merge(a->ch[0],b->ch[0]);
	x->ch[1]=merge(a->ch[1],b->ch[1]);
	return x;
}
node* rt[maxn*2];
int sz,last,link[maxn*2],len[maxn*2],pos[maxn*2];
map<char,int> nxt[maxn*2];
vector<int> ch[maxn*2];
void init(){
	sz=1;
	last=0;
	link[0]=-1;
	len[0]=0;
	rt[0]=new node(0,n);
	rt[0]->modify(0,1);
	pos[0]=0;
}
void extend(char c){
	int cur=sz++;
	len[cur]=len[last]+1;
	rt[cur]=new node(0,n);
	rt[cur]->modify(len[cur],1);
	pos[cur]=len[cur];
	int p=last;
	while(p>=0&&!nxt[p].count(c)){
		nxt[p][c]=cur;
		p=link[p];
	}
	if(p<0) link[cur]=0;
	else{
		int q=nxt[p][c];
		if(len[p]+1==len[q]) link[cur]=q;
		else{
			int clone=sz++;
			len[clone]=len[p]+1;
			link[clone]=link[q];
			nxt[clone]=nxt[q];
			rt[clone]=0;
			pos[clone]=0;
			while(p>=0&&nxt[p][c]==q){
				nxt[p][c]=clone;
				p=link[p];
			}
			link[q]=link[cur]=clone;
		}
	}
	last=cur;
}
void dfs1(int u){
	for(int i=0;i<ch[u].size();i++){
		int v=ch[u][i];
		dfs1(v);
		rt[u]=merge(rt[u],rt[v]);
		pos[u]=max(pos[u],pos[v]);
	}
}
int d[maxn*2],c[maxn*2];
void dfs2(int u){
	if(u==0){
		d[u]=0;
		c[u]=0;
	}
	else{
		int v=c[link[u]];
		if(rt[v]->query(pos[u]-len[u]+len[v],pos[u])>=2){
			d[u]=d[link[u]]+1;
			c[u]=u;
		}
		else{
			d[u]=d[link[u]];
			c[u]=v;
		}
	}
	for(int i=0;i<ch[u].size();i++) dfs2(ch[u][i]);
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	scanf("%s",s);
	init();
	for(int i=0;i<n;i++)  extend(s[i]);
	for(int i=1;i<sz;i++) ch[link[i]].push_back(i);
	dfs1(0);
	dfs2(0);
	int ans=0;
	for(int i=0;i<sz;i++) ans=max(ans,d[i]);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：crashed (赞：2)

# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/CF700E)看题目。   
# 分析
&emsp;&emsp;由于这个问题与子串相关，那么我们就先把后缀自动机给建出来。  
&emsp;&emsp;题目条件非常特殊——“出现至少两次”。而 fail 树上一个状态的祖先状态，根据定义，至少会在当前状态中出现一次。我们便可以知道，**答案所对应的状态在 fail 树上一定呈祖孙关系**。  
&emsp;&emsp;我们可以用倍增法，求出状态$S$的祖先上**第一个在$S$中出现两次以上的状态**：先倍增找到最后一个只出现一次的串，它的父亲即是我们所求。我们称这个状态为$pre(S)$。    
&emsp;&emsp;按照这个关系我们就可以设计 DP ：  
&emsp;&emsp;$f(u)$：以$u$作为末状态的字符串序列的最大长度。   
&emsp;&emsp;转移显然：   
$$f(u)=1+\max_{pre(v)=u}f(v)$$
&emsp;&emsp;问题转化为了，如何判断祖先状态有没有出现多次。  
&emsp;&emsp;我们使用一个暴力的方法——先用**线段树合并**得到每个点上的$end-pos$集合，再进行检查。  
&emsp;&emsp;对于状态$S$，它有祖先状态$S'$。由于$S$在原串出现一次，$S'$就必然会跟着出现，我们就可以只针对某一个特殊的出现位置检查——比如，$S$的第一个出现位置$fir(S)$。接着，$S'$在$S$中出现两次以上等价于：$\exists p\in end-pos(S'),p\in[fir(S)-len(S)+len(S'),fir(S))$，即存在$S'$的出现位置，满足它不属于$end-pos(S)$，但却包含在了从$fir(S)$开始的$S$串里面。这个便是在$end-pos$上的区间查询问题，可以根据已有线段树信息解决。  
&emsp;&emsp;综合以上方法，求$pre$总时间$O(n\log_2^2n)$， DP 时间$O(n)$。总时间$O(n\log_2^2n)$。  
# 代码
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>

const int MAXN = 4e5 + 5, MAXLOG = 20, MAXS = MAXN * 50;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

int f[MAXN][MAXLOG];
bool s[MAXS]; int lch[MAXS], rch[MAXS];
int dp[MAXN], seq[MAXN], ID;
int ch[MAXN][26], fa[MAXN], mx[MAXN], head[MAXN], rot[MAXN], fir[MAXN];
int N, lg2, rt, lst, tot, cnt, siz;
char S[MAXN];

void upt( const int x ) { s[x] = s[lch[x]] | s[rch[x]]; }
void copy( int a, int b ) { fa[a] = fa[b], mx[a] = mx[b], memcpy( ch[a], ch[b], sizeof ch[b] ); }

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void expand( const char c )
{
	int x = c - 'a', p = lst, cur = ++ tot;
	mx[cur] = mx[lst] + 1, lst = cur;
	while( p && ! ch[p][x] ) ch[p][x] = cur, p = fa[p];
	if( ! p ) { fa[cur] = rt; return ; }
	int q = ch[p][x];
	if( mx[q] == mx[p] + 1 ) { fa[cur] = q; return ; }
	int nq = ++ tot; copy( nq, q );
	mx[nq] = mx[p] + 1, fa[q] = fa[cur] = nq;
	while( p && ch[p][x] == q ) ch[p][x] = nq, p = fa[p];
}

void update( int &u, const int l, const int r, const int pos )
{
	if( ! u ) u = ++ siz;
	if( l == r ) { s[u] = true; return ; }
	int mid = l + r >> 1;
	if( pos <= mid ) update( lch[u], l, mid, pos );
	else update( rch[u], mid + 1, r, pos );	
	upt( u );
}

bool query( const int u, const int l, const int r, const int segL, const int segR )
{
	if( ! u ) return false;
	if( segL <= l && r <= segR ) return s[u];
	int mid = l + r >> 1, ret = false;
	if( segL <= mid ) ret |= query( lch[u], l, mid, segL, segR );
	if( mid < segR ) ret |= query( rch[u], mid + 1, r, segL, segR );
	return ret;
}

int merg( int u, int v )
{
	if( ! u || ! v ) return u + v;
	int cur = ++ siz;
	lch[cur] = merg( lch[u], lch[v] );
	rch[cur] = merg( rch[u], rch[v] );
	s[cur] = s[u] | s[v];
	return cur;
}

void DFS( const int u )
{
	seq[++ ID] = u;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
	{
		DFS( v = Graph[i].to );
		rot[u] = merg( rot[u], rot[v] );
		fir[u] = MIN( fir[u], fir[v] );
	}
}

int main()
{
	rt = lst = ++ tot;
	memset( fir, 0x3f, sizeof fir );
	read( N ), scanf( "%s", S + 1 );
	for( int i = 1 ; i <= N ; i ++ ) 
		expand( S[i] ), 
		update( rot[lst], 1, N, i ), fir[lst] = i;
	for( int i = 2 ; i <= tot ; i ++ ) addEdge( fa[i], i );
	DFS( rt );
	lg2 = log2( tot );
	for( int i = 1 ; i <= tot ; i ++ ) f[i][0] = fa[i];
	for( int j = 1 ; j <= lg2 ; j ++ )
		for( int i = 1 ; i <= tot ; i ++ )
			f[i][j] = f[f[i][j - 1]][j - 1];
	for( int i = tot, u, p ; i ; i -- )
	{
		u = p = seq[i];
		for( int k = lg2 ; ~ k ; k -- )
			if( f[p][k] > rt && ! query( rot[f[p][k]], 1, N, fir[u] - mx[u] + mx[f[p][k]], fir[u] - 1 ) )
				p = f[p][k];
		p = fa[p];
		dp[p] = MAX( dp[p], dp[u] + 1 );
	}
	write( dp[rt] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：LinkyChristian (赞：2)

洛谷的代码显示有点阴间，在[我的博客](https://lookcatbox.github.io/post/ti-jie-cf700e-cool-slogans/)获得更好的阅读体验。

~~串串题！~~

个人感觉本题和[CF1063F](https://www.luogu.com.cn/problem/solution/CF1063F) 很像，特别是关于相邻串之间的条件，可以先去看看这题。

考虑在同样满足条件的情况下，$s_{i-1}$ 是 $s_i$ 的后缀的情况一定比 $s_{i-1}$ 不是 $s_i$ 后缀的情况优。

证明：

> 如果 $s_{i-1}$ 不是 $s_i$ 的后缀，那么我们把  $s_i$ 中， $s_{i-1}$ 第二次出现位置的结尾之后的字符全部删掉，得到 $s_i'$ 。则 $s_{i-1}$ 和 $s_i'$ 依旧满足条件，且由于 $s_i'$ 是 $s_i$ 的子串，$s_i'$ 与 $s_{i+1}$ 依旧满足条件，对整个序列的合法性不造成影响。

因此我们只考虑 $s_{i-1}$ 是 $s_i$ 后缀的情况。

考虑建立后缀自动机。对于后缀自动机的 parent tree 而言，每个点 $i$ 的 $fa_i$ 所代表的最长串都是点 $i$  所代表的最长串的严格后缀。我们先只考虑从 $fa_i$ 向 $i$ 贡献。既然 $fa_i$ 作为 $i$ 的后缀，那它第二次出现的位置已经确定了，只需要考虑它是否有在前面的位置出现过即可。设点 $i$ 所代表的最长串的第一次出现位置为 $p_i$ ，计算  $fa_i$ 的 $endpos$ 集合是否在 $[p_i-len_i+len_{fa_i},p_i-1]$ 中有元素即可。

我们考虑用线段树合并维护每个点的 $endpos$ 集合。考虑一个点的 $endpos$ 集合由自己的所有儿子的 $endpos$ 集合合并而来，且当且仅当 **该点所代表的最长串是整个串的一个前缀时** 会缺少最长串第一次出现的位置，故从儿子合并上来后加入最长串第一次出现的位置即可。

现在来证明一个结论：**对于一个 $f_i$ 而言，当 $f_i$ 的最长串符合条件时，$f_i$ 中的所有串符合条件。当 $f_i$ 的最长串不符合条件时，$f_i$ 中的所有串都不符合条件。**

证明：

> 首先第一点很好证，由于 $f_i$ 中的所有其它串都是 $f_i$ 的最长串的后缀，因此只要 $f_i$ 的最长串符合条件其也一定符合条件。
>
> 对于第二点，我们假设 $f_i$ 的最长串不在 $i$ 的最长串中出现两次，而 $f_i$ 所代表的另一个更小的串在 $i$ 的最长串中出现了两次。由于两个串的 $endpos$ 集合相同，因此必然可以在 $i$ 的最长串的前面添加一串字符得到字符串 $w$ ，使得 $f_i$ 所代表的的最长串在 $w$ 中出现两次。由于 $i$ 的最长串是 $w$ 的后缀，因此 $w$ 属于 $i$ 的儿子。但是由于每个 $i$ 的最长串都必定为一个 $w$ 的后缀，所以 $endpos_i \in endpos_w$ ，这点证明 $w$ 属于 $i$ 自身或 $i$ 的祖先，与之前推导出的 $w$ 属于 $i$ 的儿子矛盾，假设不成立。

设 $f_i$ 为考虑到 $i$ 时序列的最长长度，$g_i$ 为考虑到 $i$ 时序列结尾的位置。如果 $i$ 的最长串与 $g_{fa_i}$ 满足条件，则 $f_i = f_{fa_i}+1$ ，且 $g_i=i$ ，否则 $f_i=f_{fa_i}$ ，$g_i=g_{fa_i}$ 。将后缀自动机的节点拓扑排序一下从后往前 $dp$ 即可。

$Code$

```cpp
#include<bits/stdc++.h>
#define N 600010
#define mid (l+r)/2
using namespace std;
int n;
char s[N];
int ls[N<<5],rs[N<<5],cnt,rt[N];
void update(int &k,int l,int r,int pos) {
	if(!k) k=++cnt;
	if(l==r) return ;
	if(pos<=mid) update(ls[k],l,mid,pos);
	else update(rs[k],mid+1,r,pos);
}
int merge(int x,int y,int l,int r) {
	if(!x||!y) return x+y;
	int now=++cnt;
	if(l!=r) {
		ls[now]=merge(ls[x],ls[y],l,mid);
		rs[now]=merge(rs[x],rs[y],mid+1,r);
	}
	return now;
}
int query(int k,int l,int r,int L,int R) {
    if(!k||l>R||r<L) return 0;
    if(L<=l&&r<=R) return 1;
    if(R<=mid) return query(ls[k],l,mid,L,R);
    else if(L>mid) return query(rs[k],mid+1,r,L,R);
    else return query(ls[k],l,mid,L,R)||query(rs[k],mid+1,r,L,R);
}

struct SAM {
	int tr[N][30],fa[N],lst,tot,pos[N],len[N];
	SAM(){lst=tot=1;}
 	void add(int c,int w) {
		int p=lst,np=++tot;
		len[np]=len[p]+1,pos[np]=w,lst=np;
		update(rt[np],1,n,w);
		while(p&&!tr[p][c]) tr[p][c]=np,p=fa[p];
		if(!p) {fa[np]=1;return ;}
		int q=tr[p][c];
		if(len[p]+1==len[q]) {fa[np]=q;return ;}
		int nq=++tot;
		len[nq]=len[p]+1;
		fa[nq]=fa[q],pos[nq]=pos[q],fa[q]=fa[np]=nq;
		for(int i=0; i<26; i++) tr[nq][i]=tr[q][i];
		while(p&&tr[p][c]==q) tr[p][c]=nq,p=fa[p];
	}
	int buc[N],rk[N];
	void topo() {
		for(int i=1; i<=tot; i++) buc[len[i]]++;
		for(int i=1; i<=n; i++) buc[i]+=buc[i-1];
		for(int i=1; i<=tot; i++) rk[buc[len[i]]--]=i; 
	}
}sam;
int read() {
	int res=0,f=1;char ch=getchar();
	while(!isdigit(ch)) f=ch=='-'?-1:1,ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0',ch=getchar();
	return f*res;
}
int f[N],g[N],ans;
int main()
{
	n=read();
	scanf("%s",s+1);
	for(int i=1; i<=n; i++) sam.add(s[i]-'a',i);
	sam.topo();
	for(int i=sam.tot; i>1; i--) {
		int u=sam.rk[i],v=sam.fa[u];
		rt[v]=merge(rt[v],rt[u],1,n);
	}
	for(int i=2; i<=sam.tot; i++) {
		int u=sam.rk[i],v=sam.fa[u];
		if(v==1) f[u]=1,g[u]=u;
		else if(query(rt[g[v]],1,n,sam.pos[u]-sam.len[u]+sam.len[g[v]],sam.pos[u]-1)) f[u]=f[v]+1,g[u]=u;
		else f[u]=f[v],g[u]=g[v];
		ans=max(ans,f[u]);
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：封禁用户 (赞：1)

建出 ```SAM```，在 parent 树上 ```dp```，$dp[i]$ 表示到第 $i$ 个点，最多选了多少个子串，那么如果 $f(a[i])$ 在 i 中出现了两次，就可以 $+1$ 后转移，否则直接继承 $f(a[i])$ 的值即可。

　　那么如何判断一个串是否在另一个串中出现了两次？

　　后缀自动机上每个点表示多个串，如果点 A 对应的串在点 B 对应的串中出现了两次，那么设 B 的结尾节点是 $R_1,R_2,...,R_k$，那么从这些结尾位置任选一个，设为 $pos$，满足 $pos-len[B]+len[A] \sim pos$，$A$ 的 $right$ 集合中，至少满足有两个 right 在这个区间中。

这个```dp```的好妙妙妙啊。

　　那么首先从```dp```的过程说起。这个```dp```感觉不太像```dp```，倒像是模拟。

　　我们从一个点 A 出发，设这个点的对应的最长的串是 aba，然后向下走。这个点一定至少包含两个儿子结点。假设它有两个儿子节点，分别是 $x,y$。

　　我们首先向 $x$ 走，存在这一条边就说明了 $A$ 的 right 集合和 $x$ 的不同，且 $A$ 包含 $x$。然后我们判断 $x$ 对应的子串是否有两个 $A$，如果有，那让 $f[x]=f[A]+1$ 即可。没有的话，我们记录下 $A$ 这个位置，然后继续往下走，判断走到的每个点对应的子串是否有两个 $A$，而不是有两个 $f(a[i])$。

　　因为 $A$ 在这里分叉了，并且有 $x,y$ 两个儿子，说明 A(aba) 在整个串中出现的位置至少有两次，前面的字符不同，假设是这样 $....caba.....daba.....$ 那么往下走的过程是在当前的串上向前延伸的过程，一定会延伸到两个 $aba$ 都包含了，然后转移。（这里 $x,y$ 中只有一个会延伸到两个同时包含）。
  ```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cctype>
#include<set>
#include<queue>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;

inline int read() {
    int x=0,f=1;char ch=getchar();for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=x*10+ch-'0';return x*f;
}

const int N = 400005;
int fa[N], ch[N][26], len[N], xl[N], pos[N], tmp[N], f[N], top[N];
int ls[N * 25], rs[N * 25], Root[N];
int tot, Index = 1, Last = 1, n;
char s[N];

void update(int l,int r,int &rt,int p) {
    if (!rt) rt = ++tot;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    if (p <= mid) update(l, mid, ls[rt], p);
    else update(mid + 1, r, rs[rt], p);        
}
int Merge(int x,int y) {
    if (!x || !y) return x + y;
    int z = ++tot; // ÕâÀï±ØÐëÒªÐÂ½¨Ò»¸öµã£¬ÒòÎªÒÔÇ°µÄµã»¹ÓÐÓÃ 
    ls[z] = Merge(ls[x], ls[y]);
    rs[z] = Merge(rs[x], rs[y]); 
    return z;
}
int query(int l,int r,int rt,int L,int R) {
    if (!rt) return 0;
    if (L <= l && r <= R) return 1;
    int mid = (l + r) >> 1;
    if (L <= mid && query(l, mid, ls[rt], L, R)) return 1;
    if (R > mid && query(mid + 1, r, rs[rt], L, R)) return 1;
    return 0;
}
void extend(int c,int i) {
    int NP = ++Index, P = Last; pos[NP] = i;
    len[NP] = len[P] + 1;
    for (; P && !ch[P][c]; P = fa[P]) ch[P][c] = NP;
    if (!P) fa[NP] = 1;
    else {
        int Q = ch[P][c];
        if (len[Q] == len[P] + 1) fa[NP] = Q;
        else {
            int NQ = ++Index;
            len[NQ] = len[P] + 1;
            pos[NQ] = pos[Q]; // !!! 
            memcpy(ch[NQ], ch[Q], sizeof ch[Q]);
            fa[NQ] = fa[Q];
            fa[NP] = fa[Q] = NQ;
            for (; P && ch[P][c] == Q; P = fa[P]) ch[P][c] = NQ;
        }
    }
    Last = NP;
    update(1, n, Root[NP], i);
}
int main() {
    freopen("a.in", "r", stdin);
    n = read();
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i) extend(s[i] - 'a', i);
    for (int i = 1; i <= Index; ++i) tmp[len[i]] ++;
    for (int i = 1; i <= n; ++i) tmp[i] += tmp[i - 1];
    for (int i = Index; i >= 1; --i) xl[tmp[len[i]]--] = i;
    for (int i = Index; i > 1; --i) {
        int x = xl[i];
        Root[fa[x]] = Merge(Root[fa[x]], Root[x]);
    }
    int ans = 1;
    for (int i = 2; i <= Index; ++i) {
        int x = xl[i], y = fa[x];
        if (y == 1) { f[x] = 1, top[x] = x; continue; }
        int z = query(1, n, Root[top[y]], pos[x] - len[x] + len[top[y]], pos[x] - 1);
        if (z) f[x] = f[y] + 1, top[x] = x;
        else f[x] = f[y], top[x] = top[y];
        ans = max(ans, f[x]);
    }
    cout << ans;
}
```


---

## 作者：lupengheyyds (赞：0)

# 重生之我在子串问题上 dp——CF700E Cool Slogans 题解

首先可以分析出 $s_{i-1}$ 一定是 $s_i$ 的 border。考虑可以把首尾多余的位置删掉变成 border，这样更优。问题变成了求所有字串 border 链的最大值，直接 KMP 是 $\mathcal O(n^2)$ 的。

考虑 dp。设 $f_i$ 表示以位置 $i$ 开头的字符串中最长的 border 链长，$len_i$ 表示取到 $f_i$ 的最短子串长度。考虑一组转移 $j\to i$ 的条件，发现为 $j>i\land \text{LCP}(i,j)\ge len_j$，这由 border 的定义可以导来。

但是，会不会我们可以适当减少 $f_j$，使得 $len_i$ 同步减少，以便实现 $j\to i$ 的成功转移呢？设 $j$ 是从 $k$ 转移而来，我们就可以将 $len_j$ 减小为 $len_k$。这样一来，如果 $j\to i$ 可以转移，那么 $k\to i$ 的转移也是可以的。所以不用担心这个问题。

考虑如何优化转移。首先从后往前扫描线，可以发现满足条件 $\text{LCP}(i,j)\ge len_j$ 的 $i$ 在 SA 上形如连续的一段，而我们可以通过二分将这个区间求出来然后区间取 $\max$，单点求值即可。

考虑如何求出 $len_i$。可以发现若最终转移为 $j\to i$ 则应该有 $len_i=j-i+len_j$。但此时有一个问题，如果是 $len_j$ 将为 $len_k$ 后产生的 $j\to i$ 的转移，就有 $j-i+len_k<k-i+len_k$，此时 $j$ 的缩小就不能忽略了，怎么办？

假设 $len_j$ 缩短至 $len_j'$ 后产生转移 $j\to i$，$len_k$ 缩短至 $len_k'$ 后产生转移 $k\to i$，一定有$\text{LCP}(i,j)\ge len'_j,\text{LCP}(i,k)\ge len_k'$，于是得出 $\text{LCP}(j,k)\ge \min(len_j',len_k')$。根据定义，设缩短后 $j,k$ 的值为 $f_j',f_k'$ 则有 $f_j'=f_k'=res$，由于以 $j,k$ 开头的前 $\min(len_j',len_k')$ 个字符已经可以产生 $res$ 的贡献，根据 $len$ 最小的定义，有 $len_j'=len_k'$。于是就证明了所有以相同 $f$ 值转移到 $i$ 的 $j$，其缩短后的 $len'_j$ 都相同，那么我们可以直接取 $len_k=len'_k$ 的 $len_k$ 值（即不用缩短的那个）。

于是只需要在得到 $f_i$ 同时得到 $len'_j$，再在 SA 上找到满足 $\text{LCP}(i,j)\ge len'_j$ 的区间 $[L,R]$，设这个区间中的最小可转移下标为 $p$（即 $p>i$ 的最小的 $p$），有 $len_i=p-i+len_j'$。

于是便解决了此题，时间复杂度 $\mathcal O(n\log n)$，空间复杂度 $\mathcal O(n)$。

---

## 作者：MaxBlazeResFire (赞：0)

神仙串串科技题。

考虑建出 $\rm SAM$ 后跑线段树合并，得到每个节点的 $\rm endpos$ 集合。首先一个明显的结论是，每个节点内最多选出一个串，若同一节点内有一个串能在另一个串中出现两次，它们的 $\rm endpos$ 集合不可能一样。

然后就是对于最终的序列中连续两个串 $s_{i-1},s_i$，若 $s_{i-1}$ 不是 $s_i$ 的后缀，则显然存在将 $s_i$ 缩短的不劣的方案。因此我们只考虑 $s_{i-1}$ 是 $s_i$ 后缀的情况，也即 $s_{i-1}$ 所在节点位于 $s_i$ 所在节点 $\rm link$ 树上的父亲。

由上面两个结论可知，最终答案是 $\rm parent$ 树上一条合法的祖先链长度。

于是考虑在 $\rm link$ 树上跑树形 $\rm dp$，记 $f_i$ 表示在 $i$ 的祖先链上能选出最多的合法的答案，考虑转移。

首先，$f_x$ 至少为 $f_{link_x}$ 且最多为 $f_{link_x}+1$，由上面结论易证。那么什么时候 $f_x=f_{link_x}+1$ 呢？

考虑 $x$ 祖先链上 **任意一个** $f_u=f_{link_x}$ 的节点 $u$（当然这样满足条件的 $u$ 也是一条祖先链），如何知道 $u$ 中是否存在一个子串，在 $x$ 中的某个子串中出现了至少 $2$ 次呢？

首先，我们只需要考虑 $x$ 中的最长串，这是显然的；而实际上，我们也只需要考虑 $u$ 中的最长串，容易通过 $u$ 中所有串的 $\rm endpos$ 集合相同证明。问题转化为判断 $u$ 中最长串是否在 $x$ 最长串中出现了至少 $2$ 次。考虑 $u$ 是 $x$ 的真后缀，那么对于任意一个 $x$ 的 $\rm endpos$ 集合中的元素 $w$，我们只需要知道 $u$ 中是否存在一个元素 $v$ 使得 $v\in[w-maxlen_x+maxlen_u,w-1]$ 即可，这个 $w$ 确实可以随便选（我还想了半天），可以在建树的时候预处理；剩下的只需要在 $u$ 的权值线段树上查一个区间即可。

问题来了，是否对于每一个 $u$ 都要做一遍然后取最值呢？答案是否定的，只需要取深度最浅的满足 $f_u=f_{link_x}$ 的 $u$ 就行了。原因可以从实现反推：$u$ 的 $\rm endpos$ 集合是它子树内所有点的超集，在查询实现的时候必然不劣。因此我们额外记录 $g_x$ 为满足上述条件的 $u$。

于是神题结束，复杂度 $O(n\log n)$，瓶颈是线段树合并与查询。

坑点 $1$：线段树合并需要使用新建节点的可持久化形式，因为要支持随时回访任意历史版本。

坑点 $2$：根节点没有串，上述“真后缀”命题不成立。所以 $\rm dp$ 过程中所有父亲为根节点的点要特判。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 400005
#define LOGN 55

int cnt[MAXN * LOGN],lc[MAXN * LOGN],rc[MAXN * LOGN],rt[MAXN];
int n,Nodecnt,Ans;
char s[MAXN];

inline void push_up( int x ){ cnt[x] = cnt[lc[x]] + cnt[rc[x]]; }

void modify( int &t , int l , int r , int x , int k ){
	if( !t ) t = ++Nodecnt;
	if( l == r ){ cnt[t] += k; return; }
	int mid = ( l + r ) >> 1;
	if( x <= mid ) modify( lc[t] , l , mid , x , k );
	else modify( rc[t] , mid + 1 , r , x , k );
	push_up( t );
}

int merge( int u , int v , int l , int r ){
	if( !u || !v ) return u + v;
	int newnode = ++Nodecnt;
	if( l == r ){ cnt[newnode] = cnt[u] + cnt[v]; return newnode; }
	int mid = ( l + r ) >> 1;
	lc[newnode]	= merge( lc[u] , lc[v] , l , mid );
	rc[newnode] = merge( rc[u] , rc[v] , mid + 1 , r );
	push_up( newnode );
	return newnode;
}

int query( int t , int l , int r , int Ql , int Qr ){
	if( !t ) return 0;
	if( Ql <= l && r <= Qr ) return cnt[t];
	int mid = ( l + r ) >> 1;
	if( Qr <= mid ) return query( lc[t] , l , mid , Ql , Qr );
	if( Ql > mid ) return query( rc[t] , mid + 1 , r , Ql , Qr );
	return query( lc[t] , l , mid , Ql , Qr ) + query( rc[t] , mid + 1 , r , Ql , Qr );
}

struct SAM{
	int nodecnt,nxt[MAXN][26],link[MAXN],maxlen[MAXN],pos[MAXN];
	vector<int> E[MAXN];
	inline void init(){ nodecnt = 1; }
	inline int insert( int last , int ch , int id ){
		int cur = ++nodecnt,p = last; maxlen[cur] = maxlen[p] + 1;
		pos[cur] = id;
		modify( rt[cur] , 1 , n , id , 1 );
		for( ; p && !nxt[p][ch] ; p = link[p] ) nxt[p][ch] = cur;
		int q = nxt[p][ch];
		if( !q ) link[cur] = 1;
		else if( maxlen[q] == maxlen[p] + 1 ) link[cur] = q;
		else{
			int clone = ++nodecnt; maxlen[clone] = maxlen[p] + 1;
			memcpy( nxt[clone] , nxt[q] , sizeof( nxt[clone] ) );
			for( int x = p ; x && nxt[x][ch] == q ; x = link[x] ) nxt[x][ch] = clone;
			link[clone] = link[q],link[q] = link[cur] = clone;
		}
		return cur;
	}
	int deg[MAXN],f[MAXN],g[MAXN];
	inline void build(){
		for( int i = 2 ; i <= nodecnt ; i ++ ) E[link[i]].emplace_back( i ),deg[link[i]] ++;
		queue<int> Q;
		for( int i = 1 ; i <= nodecnt ; i ++ ) if( !deg[i] ) Q.push( i );
		while( !Q.empty() ){
			int u = Q.front(); Q.pop();
			rt[link[u]] = merge( rt[link[u]] , rt[u] , 1 , n );
			pos[link[u]] = pos[u];
			if( !--deg[link[u]] ) Q.push( link[u] );
		}
	}
	inline void dp( int x ){
		if( x == 1 ) f[x] = 0,g[x] = 1;
		else if( link[x] == 1 ) f[x] = 1,g[x] = x;
		else{
			if( query( rt[g[link[x]]] , 1 , n , pos[x] - maxlen[x] + maxlen[g[link[x]]] , pos[x] - 1 ) )
				f[x] = f[link[x]] + 1,g[x] = x;
			else f[x] = f[link[x]],g[x] = g[link[x]];
		}
		for( int v : E[x] ) dp( v );
		Ans = max( Ans , f[x] );
	}
}Sam;

signed main(){
	Sam.init();
	scanf("%d",&n); scanf("%s",s + 1);
	for( int i = 1 , last = 1 ; i <= n ; i ++ ) last = Sam.insert( last , s[i] - 'a' , i );
	Sam.build(); Sam.dp( 1 );
	printf("%d\n",Ans);
	return 0;
}
```

---

## 作者：SoyTony (赞：0)

子串重复出现的问题，自然要考虑 SAM。

为了更契合 SAM 以及 $\mathrm{endpos}$ 相关的性质，我们发现如果把 $s_{i-1}$ 在 $s_i$ 中第一次出现的开头到第二次出现的结尾这一部分作为新的 $s_i$ 一定是不劣的，这样的 $s_i$ 更短，更好满足下一次匹配。

比较显然的事情是答案（指根据上面修改后的答案）一定位于后缀链接树的一条链上，且同一个节点最多出现一次（$\mathrm{endpos}$ 相同，不可能有题目要求的关系），于是从短到长，即从根到叶子计算。

首先常规地用线段树合并维护出 $\mathrm{endpos}$ 集合，剩下的算法流程在此基础上展开。

容易看出，如果拿出 $u$ 节点 $\mathrm{endpos}$ 的第一个元素，即可判断 $u$ 节点是否存在子串可以作为下一个 $s_i$。

贪心地思考，如果某一节点有多个子串满足条件，那么选取最短的一个是最优的。

根据上面两条信息，注意到在已知 $s_{i-1}$ 的来源 $u$ 的基础上，判断 $v$ 能否作为 $s_i$ 的信息实际是 $O(1)$ 的，即拿出 $v$ $\mathrm{endpos}$ 中的第一个元素与 $u$ 中满足条件的最短子串判断。

判断其实相当简单，设 $v$ $\mathrm{endpos}$ 中的一个元素为 $j$，找到 $j$ 在 $u$ $\mathrm{endpos}$ 中的前驱 $pre$，如果 $[pre-|s_{i-1}|+1,j]$ 这个子串是在 $v$ 内的，就说明 $v$ 可以作为 $s_i$，且 $s_i$ 最优选择就是上面这个子串，反之则不能。

所以只需要线段树查询前驱，复杂度是 $O(n\log n)$。

---

## 作者：Leasier (赞：0)

这里涉及到一般子串，看上去很不可做。

人类智慧地，我们可以注意到以下结论：

- 存在一种最优方案，使得 $\forall 2 \leq i \leq k$，$s_{i - 1}$ 为 $s_i$ 后缀。

证明：我们随意取一种最优方案，对于任意一个不满足条件的 $i$，我们可以删去 $s_i$ 的一个后缀使得满足上述条件，而此时 $s_i$ 在 $s_{i + 1}$ 中的出现次数也不会减少。

看到后缀，考虑建出 SAM 的 fail 树。现在我们考虑在这棵树上 dp。

设 $dp_u$ 表示 $s_k = \text{any string in endpos}(u)$ 时的 $k_{\max}$。这个状态的正确性得益于同一个 endpos 等价类内部的串互相要么恰好出现一次，要么不出现。

初值：$dp_{root} = 1$。

转移：$dp_u = dp_v + 1$，其中 $v$ 为 fail 树上 $u$ 的祖先中第一个在 $u$ 的等价类中出现至少两次的等价类。

答案：$\displaystyle\max_{i} dp_i$。

现在问题变为如何快速转移。我们可以将这个转移改写成一个更加容易实现的形式：

- 维护 $from_u$ 表示 $u$ 的祖先中上一次匹配到对应 $v$ 的点。
- 转移时，若 $from_{fa_u}$ 在 $u$ 中出现恰好一次，则 $dp_u = dp_{fa_u}, from_u = from_{fa_u}$；否则，$dp_u = dp_{fa_u} + 1, from_u = u$。正确性显然，因为一条祖先到后代的链上的 dp 值一定单调不降。

现在问题变为如何对应 $u$ 的祖先 $v$，快速判断 $v$ 在 $u$ 中是否只出现一次。为了方便，我们取 endpos 等价类中最长者 $S, T$。

根据 fail 树的定义有 $S[len_u - len_v + 1, len_u] = T$，则我们只需要看还有没有其他的位置满足条件即可。

那这里“其他的位置”需要满足什么条件呢？设 $u$ 的其中一个出现位置的右端点为 $pos_u$，我们所求的一个合法右端点为 $r$。

- $r - len_v + 1 \geq pos_u - len_u + 1$。
- $r < pos_u$。

合起来可以得到 $pos_u - len_u + len_v \leq r \leq pos_u - 1$。

于是我们线段树合并预处理子树内的结尾位置并在判断时查询子树内在上述区间中是否存在结尾位置即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int nxt;
	int end;
} Edge;

typedef struct {
	int ls;
	int rs;
	int sum;
} Node;

int lst = 1, sam_id = 1, cnt = 0, seg_id = 0;
int len[400007], nxt[400007][27], fa[400007], pos[400007], head[400007], root[400007], dp[400007], from[400007];
char s[200007];
Edge edge[400007];
Node tree[7600007];

inline int insert(int ch){
	int u = lst, v = lst = ++sam_id;
	len[v] = len[u] + 1;
	while (u != 0 && nxt[u][ch] == 0){
		nxt[u][ch] = v;
		u = fa[u];
	}
	if (u == 0){
		fa[v] = 1;
		return v;
	}
	int w = nxt[u][ch];
	if (len[w] == len[u] + 1){
		fa[v] = w;
		return v;
	}
	int x = ++sam_id;
	len[x] = len[u] + 1;
	fa[x] = fa[w];
	fa[v] = fa[w] = x;
	for (register int i = 1; i <= 26; i++){
		nxt[x][i] = nxt[w][i];
	}
	while (nxt[u][ch] == w){
		nxt[u][ch] = x;
		u = fa[u];
	}
	return v;
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

inline void update(int x){
	tree[x].sum = tree[tree[x].ls].sum + tree[tree[x].rs].sum;
}

void insert(int &x, int l, int r, int pos){
	if (x == 0) x = ++seg_id;
	if (l == r){
		tree[x].sum++;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid){
		insert(tree[x].ls, l, mid, pos);
	} else {
		insert(tree[x].rs, mid + 1, r, pos);
	}
	update(x);
}

int merge(int x, int y){
	if (x == 0) return y;
	if (y == 0) return x;
	int z = ++seg_id;
	tree[z].ls = merge(tree[x].ls, tree[y].ls);
	tree[z].rs = merge(tree[x].rs, tree[y].rs);
	update(z);
	return z;
}

void dfs1(int u, int n){
	if (pos[u] != 0) insert(root[u], 1, n, pos[u]);
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		dfs1(x, n);
		root[u] = merge(root[u], root[x]);
		if (pos[u] == 0) pos[u] = pos[x];
	}
}

int get_sum(int x, int L, int R, int l, int r){
	if (x == 0) return 0;
	if (l <= L && R <= r) return tree[x].sum;
	int mid = (L + R) >> 1, ans = 0;
	if (l <= mid) ans = get_sum(tree[x].ls, L, mid, l, r);
	if (r > mid) ans += get_sum(tree[x].rs, mid + 1, R, l, r);
	return ans;
}

void dfs2(int u, int n){
	for (register int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (u == 1){
			dp[x] = 1;
			from[x] = x;
		} else if (get_sum(root[from[u]], 1, n, pos[x] - len[x] + len[from[u]], pos[x] - 1) == 0){
			dp[x] = dp[u];
			from[x] = from[u];
		} else {
			dp[x] = dp[u] + 1;
			from[x] = x;
		}
		dfs2(x, n);
	}
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	scanf("%s", &s[1]);
	for (register int i = 1; i <= n; i++){
		pos[insert(s[i] - 'a' + 1)] = i;
	}
	for (register int i = 2; i <= sam_id; i++){
		add_edge(fa[i], i);
	}
	dfs1(1, n);
	dfs2(1, n);
	for (register int i = 2; i <= sam_id; i++){
		ans = max(ans, dp[i]);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

首先，$s_{i-1}$ 都是 $s_i$ 的后缀的情况不会影响答案，因为如果不是后缀的话，把 $s_{i}$ 后面的不与 $s_{i-1}$ 匹配的全部删掉，从而 $s_i$ 会变短，答案不会更劣。因为是后缀，考虑套 SAM。

设 $f_i$ 为在 SAM 上的 parent tree 从上往下 dp 的时候状态 $i$ 的最大答案，$ls_i$ 为 $f_i$ 情况下上一个字符串在哪一个状态（因为状态 $i$ 不一定会被用）。考虑从父节点 $fa(x)$ 到 $x$ 的转移，如果父节点的串在子节点出现了 $\ge 2$ 次，$f_x$ 就可以加 $1$，否则不能加。因此我们只需要判断能否出现 $\ge 2$ 次就可以了。

我们考虑维护每一个节点的 endpos，对于 $x$ 的 endpos 中的一个位置 $p$，$fa(x)$ 对应的所有字串都是在 $p$ 出一定出现的（因为 $fa(x)$ 的 endpos 包含 $x$ 的 endpos）。因此，我们要找到一个不是 $p$ 的位置就可以了。对于这一个 $p$，我们就是要保证在 $[p-len(x)+len(fa(x)),p-1]$ 中又出现一次就可以了。（为什么呢？因为我们是选什么 $p$ 都可以，选最后的一个的话，前一个出现的右边的限制就显然是 $p-1$；左边的限制的话要保证 $fa(x)$ 对应的子串的左端点不能小于 $x$ 的，还有就是 $fa(x)$ 对应的所有字串在 $x$ 表示的最长串里面的匹配情况是等价的，所以我们都取最长的）

维护 endpos 集合可以直接用线段树。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 4e5+5;

struct tnode {
	int l,r;
} t[N<<5];

int rt[N],f[N],ls[N];
int tot;

int ins(int l,int r,int x){
	int k=++tot;
	if (l==r){
		return k;
	}
	int mid=l+r>>1;
	if (x<=mid){
		t[k].l=ins(l,mid,x);
	}
	else{
		t[k].r=ins(mid+1,r,x);
	}
	return k;
}

int uni(int p,int q){
	if (!p || !q){
		return p+q;
	}
	int k=++tot;
	t[k].l=uni(t[p].l,t[q].l);
	t[k].r=uni(t[p].r,t[q].r);
	return k;
}

int qy(int k,int l,int r,int ql,int qr){
	if (!k){
		return 0;
	}
	if (ql<=l && r<=qr){
		return 1;
	}
	int mid=l+r>>1;
	int res=0;
	if (ql<=mid){
		res|=qy(t[k].l,l,mid,ql,qr);
	}
	if (qr>mid){
		res|=qy(t[k].r,mid+1,r,ql,qr);
	}
	return res;
}

struct sam {
	int tot,n,lst;
	struct node {
		int len,ch[26],fa;
	} t[N];
	int pos[N];
	void ins(int c,int id){
		int p=lst,np=++tot;
		t[np].len=t[p].len+1;
		pos[np]=id;
		lst=np;
		while (~p && !t[p].ch[c]){
			t[p].ch[c]=np;
			p=t[p].fa;
		}
		if (!~p){
			t[np].fa=0;
			return;
		}
		int q=t[p].ch[c];
		if (t[q].len==t[p].len+1){
			t[np].fa=q;
			return;
		}
		int nq=++tot;
		t[nq]=t[q];
		t[nq].len=t[p].len+1;
		pos[nq]=pos[q];
		t[q].fa=t[np].fa=nq;
		while (~p && t[p].ch[c]==q){
			t[p].ch[c]=nq;
			p=t[p].fa;
		}
	}
	void bd(string x){
		t[0].fa=-1;
		x=" "+x;
		for (int i=1; i<x.size(); i++){
			ins(x[i]-'a',i);
		}
	}
	int c[N],b[N];
	void sort(){
		for (int i=1; i<=tot; i++){
			c[t[i].len]++;
		}
		for (int i=1; i<=n; i++){
			c[i]+=c[i-1];
		}
		for (int i=1; i<=tot; i++){
			b[c[t[i].len]--]=i;
		}
	}
} sm;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin>>n;
	string s;
	cin>>s;
	sm.n=n;
	sm.bd(s);
	sm.sort();
	s=" "+s;
	int cur=0;
	for (int i=1; i<=n; i++){
		cur=sm.t[cur].ch[s[i]-'a'];
		rt[cur]=ins(1,n,i);
	}
	for (int i=sm.tot; i>=1; i--){
		rt[sm.t[sm.b[i]].fa]=uni(rt[sm.t[sm.b[i]].fa],rt[sm.b[i]]);
	}
	int ans=1;
	for (int i=1; i<=sm.tot; i++){
		int x=sm.b[i];
		if (!sm.t[x].fa){
			f[x]=1;
			ls[x]=x;
		}
		else{
			if (qy(rt[ls[sm.t[x].fa]],1,n,sm.pos[x]-sm.t[x].len+sm.t[ls[sm.t[x].fa]].len,sm.pos[x]-1)){
				f[x]=f[sm.t[x].fa]+1;
				ls[x]=x;
			}
			else{
				f[x]=f[sm.t[x].fa];
				ls[x]=ls[sm.t[x].fa];
			}
			ans=max(ans,f[x]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

