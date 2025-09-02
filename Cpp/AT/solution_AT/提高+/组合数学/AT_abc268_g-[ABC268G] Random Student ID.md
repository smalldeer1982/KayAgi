# [ABC268G] Random Student ID

## 题目描述

**题目大意**

有 $n$ 个学生，第 $i$ 个学生的名字是一个字符串 $S_i$，编号是 $i$。

接下来校长要按照一种绝妙的字典序来对这 $n$ 个学生的名字排序。他随机选取一个 $\tt{a}\sim\tt{z}$ 的排列，定为 $P$。$P$ 中越早出现的字母，他的字典序就越小。

对于每一个学生，求出他的期望排名，对 $998244353$ 取模。

## 说明/提示

对于所有数据，我们保证 $S_i$ 只由小写字母组成，并且这些学生的名字互不相同。$n\geqslant 2$，字符串总长度不超过 $5\times 10^5$。

## 样例 #1

### 输入

```
3
a
aa
ab```

### 输出

```
1
499122179
499122179```

## 样例 #2

### 输入

```
3
a
aa
aaa```

### 输出

```
1
2
3```

# 题解

## 作者：liangbowen (赞：7)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc268_g)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17435701.html)

很牛逼的题目，这题是要从定义出发，而非 DP，但是想到这一点不简单（我太菜了）。

## 思路

考虑两个名字 $s$ 与 $t$。

+ 如果 $s$ 是 $t$ 的前缀，根据字典序的规则，$t$ 必然比 $s$ 靠前。即 $0$。
+ 如果 $t$ 是 $s$ 的前缀，同理，$s$ 比 $t$ 靠前。即 $1$。
+ 否则，对于任意一个位置，$s$ 与 $t$ 都是等概率更靠前的。即 $\dfrac 12$。

所以只要找到一个串有多少个前后缀即可。假设第 $i$ 个串有 $a_i$ 个前缀串，$b_i$ 个后缀串，答案即为

$$\sum\limits_{i=1}^n b_i + (n-a_i-b_i-1) \times \dfrac 12$$

显然是 trie 板子，直接做即可。注意 $\dfrac 12$ 用逆元处理。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 5e5 + 5, mod = 998244353, inv = 499122177; //inv 是 2 的逆元，也就是 x/2
namespace Trie {
	int tr[N][26], cnt[N]; bool ed[N];
	int j, idx;
	void insert(string s)
	{
		j = 0;
		for (char si : s)
		{
			int i = si - 'a';
			if (!tr[j][i]) tr[j][i] = ++idx;
			j = tr[j][i], cnt[j]++;
		}
		ed[j] = true;
	}
	int query(string s)
	{
		j = 0; int ans = 0;
		for (char si : s) ans += ed[j], j = tr[j][si - 'a'];
		return ans;
	}
}; using namespace Trie;
string a[N];
int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], insert(a[i]);
	for (int i = 1; i <= n; i++)
	{
		int pre = query(a[i]), suf = cnt[j];
		cout << (1 + pre + (1ll * (n - pre - suf) * inv % mod)) % mod << '\n';
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：EastPorridge (赞：3)

AtCoder 真的好喜欢出这种吓人题呢。

### 题目分析：

所有排列情况下的期望排名，考虑一下贡献。

针对于当前串 $S$，另一个串排在它的哪里可以讨论，如果是它的前缀，则在任意情况下都在 $S$ 的前面，贡献就是 $1$；如果是串 $S$ 的后缀，则贡献永远是 $0$；否则，它要么在 $S$ 的前面，要么不在，就是 $\frac {1}{2}$。设前缀个数为 $a$，后缀个数为 $b$，则表达出来就是

$$a \times1+ b \times 0 + \frac {n-a-b}{2}$$

这玩意很好搞，放 trie 树上跑就可以了，最后记得加 $1$。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10,mod=998244353,i2=499122177;
int tr[N][26]; string a[N]; bitset<N> st;
#define int long long
int n,cnt[N],idx,ans;
void insert(int id)
{
	int p=0;
	for(auto i : a[id])
	{
		if(! tr[p][i-'a']) tr[p][i-'a']=++idx;
		p=tr[p][i-'a']; cnt[p]++;
	}
	st[p]=1;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) cin>>a[i],insert(i);
	for(int i=1;i<=n;i++)
	{
		ans=0; int p=0;
		for(auto t : a[i]) {if(st[p]) ans++; p=tr[p][t-'a'];}
		printf("%lld\n",1ll*(ans+(n-ans-cnt[p])*i2%mod+1)%mod);
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

期望是假的。只需要求每种字典序下的排名和。再除以 $26!$ 即真实答案。

考虑排名的定义。在一种字典序的定义下，如果存在 $j$ 个字符串 $k$ 满足 $S_k < S_i$。那么 $i$ 的排名就是 $j+1$。

所以只需要对于每个对 $(i, k)$（$i \ne k$），计算有多少种字典序的定义满足 $S_k < S_i$。将这个值累加进 $i$ 的答案。最后输出时别忘 $+1$ 才能得到真实排名。

那么问题是，有多少种字典序的定义能满足 $S_k < S_i$ 呢？

分类讨论一下：

- 如果 $S_k$ 是 $S_i$ 的前缀。那么 $26!$ 种方案都合法。
- 否则，如果 $S_i$ 是 $S_k$ 的前缀。那么合法方案数为 $0$。
- 否则，令 $l = \operatorname{lcp}(S_i,S_k)$。那么一定有 $l + 1
\le \min( |S_i|, |S_k|)$，而且 $S_{i,l+1} \ne S_{k,l+1}$。不难发现只要确定了 $S_{i,l+1}, S_{k,l+1}$ 的大小关系就能确定 $S_i,S_k$ 的大小关系。

  我们希望 $S_k < S_i$，也就是在字典序的定义里，$S_{k,l+1}$ 需要比 $S_{i,l+1}$ 更靠前。不难发现总共的 $26!$ 种方案里，恰有一半满足这个条件。也就是说方案数为 $26!/2$。

于是得到了一个简单平方级别的解决方案。考虑优化。

注意到，我们只需要求有多少 $k$ 满足是 $S_i$ 的前缀，以及有多少 $k$ 满足 $S_i$ 是 $S_k$ 的前缀。知道这两个值，也就是前两种情况的方案数后，第三种情况可以用 $n$ 减出来。

形式化的，令有 $a$ 个 $k$ 满足 $S_k$ 是 $S_i$ 的前缀，$b$ 个 $k$ 满足 $S_i$ 是 $S_k$ 的前缀，则：

$$
ans_i = 26! \times a + 0 \times b + (n-a-b)\times 26!/2
$$

而 $a, b$ 的求解见 [字典树](https://www.luogu.com.cn/problem/P8306)。

代码：<https://atcoder.jp/contests/abc268/submissions/59691152>

---

## 作者：shinkuu (赞：1)

挺不错的一道题。

题目是有关若干字符串的字典序的问题，~~而且数据范围和总字符数有关~~，优先想到 trie。先建出 trie 树，然后考虑如何算排名。

直接算某个串的排名显然是不太可能的，因为如果在 trie 树的上层确定了字典，是会有后效性的。于是转换思路，发现 $rank_i=\sum [j<i]+1$。这启示我们可以分开 trie 的每一层，看这一层的不同字典会对 $\sum [j<i]$ 产生多少影响。

容易发现，确定字典等同于改变若干子树的先后顺序。还可以发现，对于两个子树 $i,j$，$i$ 在 $j$ 前面的概率都是 $\frac{1}{2}$。所以定义字符串结尾位置的集合为 $S$，$c_i=\begin{cases}1&i\in S\\ 0&\text{Otherwise.}\end{cases}$ 记 $siz_i$ 为以 $i$ 为根的子树中 $c_i$ 之和。则这一层对结尾在子树 $i$ 中的所有串排名的贡献就是 $\frac{siz_{fa_i}-siz_i-c_{fa_i}}{2}$。因为结尾不在该子树或 $fa_i$ 的串都有 $\frac{1}{2}$ 的可能在它前面。

除此之外，还要考虑每个结尾字符的祖先。这些点一定比该串字典序小，有固定 $1$ 的贡献。

code：

```cpp
int n,m,tot,id[N],tr[N][27];
int siz[N],dp[N],ans[N];
char s[N];
inline int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
const int inv2=qpow(2,mod-2);
void insert(char *str,int pos){
	int m=strlen(str+1),u=0;
	rep(i,1,m){
		int v=str[i]-'a';
		if(!tr[u][v])
			tr[u][v]=++tot;
		u=tr[u][v];
	}
	id[u]=pos;
}
void dfs1(int u){
	siz[u]=id[u]>0;
	rep(i,0,25){
		int v=tr[u][i];
		if(!v)
			continue;
		dfs1(v);
		siz[u]+=siz[v];
	}
}
void dfs2(int u){
	if(id[u])
		ans[id[u]]=dp[u];
	rep(i,0,25){
		int v=tr[u][i];
		if(!v)
			continue;
		dp[v]=Mod(dp[u]+(id[u]>0),1ll*(siz[u]-siz[v]-(id[u]>0))*inv2%mod);
		dfs2(v);
	}
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%s",s+1);
		insert(s,i);
	}
	dfs1(0);
	dfs2(0);
	rep(i,1,n){
		printf("%d\n",ans[i]+1);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：lfxxx (赞：0)

我们考虑建立出字典树。

定义 $dp_u$ 表示期望意义下比由字典树上点 $u$ 到根组成的串小的字符串数量，显然可以从上往下转移 $dp_u = dp_fa + cnt_fa + \sum_{k \in son_u \setminus v} P(k < v) \times sz_k$。

现在唯一的问题是如何求解 $P(k < v)$，注意到字典树上每一层贡献独立，而且随机一个排列一个字符在另一个字符之前的概率总是 $\frac{1}{2}$，所以实际上 $P(k < v)$ 一定为 $\frac{1}{2}$，那么直接从上往下转移即可。


```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&(-x))
using namespace std;
const int mod = 998244353;
const int maxn = 5e5+114;
int ch[maxn][26],tot,sz[maxn],cnt[maxn],dp[maxn],id[maxn],n;
string S[maxn];
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res=res*res%mod;
	if(b%2==1) res=res*a%mod;
	return res;
}
int I;// 1/2
int rt;
void ins(string s,int pos){
	int u=rt;
	for(char c:s){
		sz[u]++;
		if(ch[u][c-'a']==0) ch[u][c-'a']=++tot;
		u=ch[u][c-'a'];
	}
	sz[u]++;
	cnt[u]++;
	id[pos]=u;
	return ;
}
void DP(int u){
	if(u==0) return ;
	for(int i=0;i<26;i++){
		if(ch[u][i]!=0){
			int v=ch[u][i];
			dp[v]=(dp[u]+(sz[u]-cnt[u]-sz[v])*I%mod+cnt[u])%mod;
			DP(v);
		}
	}
}
signed main(){
	I=qpow(2,mod-2);
	cin>>n;
	rt=++tot;
	for(int i=1;i<=n;i++){
		cin>>S[i];
		ins(S[i],i);
	}
	DP(rt);
	for(int i=1;i<=n;i++) cout<<(dp[id[i]]+1)%mod<<'\n';
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

## 3.[[ABC268G] Random Student ID](https://www.luogu.com.cn/problem/AT_abc268_g) 2000+

### 题意

给你 $n$ 个姓名，随机一个字母表的排列 $p$ 并且把每个字符 $a_{i,j}$ 修改为 $p_{a_{i,j}}$，求每个学生的字典序排名期望。

### 思路

字典序的东西，考虑字典树。字典树这个东西只需要考虑树间相对顺序，就能出答案。

对于每个字符串求解。考虑一个节点 $p$，落在其子树里面的所有字符串个数设之为 $s[p]$，若 $p$ 的下一个后继为 $q$，如何对于层间求解？

对于层间的答案，有不落在 $q$ 子树内的串个数为 $s[p]-s[q]$，因为随机双射的性质，使得它有一半的概率出现在 $q$ 之前，一半的概率出现在 $q$ 之后，这是自然的空间对称美。

所以答案就是 $\frac{1}{2}\sum s[p]-s[q]$ 吗？

发现算漏了一些东西。我们发现其前缀个数，因为再怎么随机映射字母表都不会改变前缀关系，加上了就行了。

时间复杂度 $O(|S|)$。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I n,cnt=1;const I N=5e5+10;
I t[N][26],s[N],c[N];string a[N];
V ins(string&ss){I p=1;++s[1];
	for(char i:ss){
		I&q=t[p][i-'a'];
		if(!q)q=++cnt;
		++s[p=q];}++c[p];}
I qry(string&ss){I sss=0,ans=0,p=1;
	for(char i:ss){
		I&q=t[p][i-'a'];
		sss+=s[p]-c[p];p=q;sss-=s[q];
		ans+=c[p];}
	return(1ll*sss*499122177+ans)%998244353;}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	fo(i,1,n)cin>>a[i],ins(a[i]);
	fo(i,1,n)printf("%d\n",qry(a[i]));
	return 0;}
```



---

## 作者：_sunkuangzheng_ (赞：0)

好像题解区还没有这个做法。（？

我们对 $n$ 个字符串建出 trie 树，考虑子树内同层节点的相互贡献。记 $siz_u$ 表示 $u$ 子树内字符串的数量，则这一层内，其兄弟节点 $v$ 对 $u$ 排名的总贡献等于 $\sum\limits_{v \ne u} \dfrac{1}{2}siz_v$，$\dfrac{1}{2}$ 表示 $v$ 子树的字典序有 $\dfrac{1}{2}$ 在 $u$ 前面。贡献可以简单的在 trie 树上 dfs 统计。

最终，我们把每一个字符串在 trie 树上经过的点的贡献加起来，即为排名的期望。

$2$ 的逆元是 $499122177$，可以直接使用，不用写快速幂啦 qwq。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 09.11.2023 07:52:00
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
#define int long long
using namespace std;
const int N = 5e5+5,po = 499122177,mod = 998244353;
int t,n,ch[N][27],tot = 1,val[N],siz[N];vector<int> g[N];string s[N];
void ins(string &t){
    int s = 1;
    for(char c : t){
        if(!ch[s][(int)(c-'a')]) ch[s][(int)(c-'a')] = ++tot,g[s].push_back(tot);
        s = ch[s][(int)(c-'a')];
    }val[s] ++,siz[s] ++;
}void dfs(int u){
    int sm = 0;
    for(int v : g[u]) dfs(v),siz[u] += siz[v],sm += siz[v];
    for(int v : g[u]) val[v] = (val[v] + po * (sm - siz[v])) % mod; 
}int qry(string &t){
    int s = 1,ans = 0;
    for(char c : t)
        ans = (ans + val[s]) % mod,s = ch[s][(int)(c-'a')];
    return (ans + val[s]) % mod;
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> s[i],ins(s[i]);
    dfs(1);
    for(int i = 1;i <= n;i ++) cout << qry(s[i]) << "\n";
}
```

---

## 作者：Tsawke (赞：0)

#  [[ABC268G] Random Student ID](https://www.luogu.com.cn/problem/AT_abc268_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC268G)

## 题面

给定 $ n $ 名学生的名字 $ S_i $，保证不重复。现在随机一个 $ a \rightarrow z $ 的排列作为字典序的偏序关系，求每个同学排名的期望，对 $ 998244353 $ 取模。

## Solution

这一题可以说确实很高妙，确实没想到还可以这么处理。

第一眼以为是一些类似 期望DP 的东西，然后想了半天也没想到什么复杂度正确的做法，实际上这道题是从期望的意义去找性质。

首先我们考虑对于一个串 $ S $ 的期望排名，若存在串 $ S $ 的前缀串 $ T $，那么显然串 $ T $ 无论字典序的偏序关系如何都会在 $ S $ 之前，所以一定会贡献 $ 1 $。

而若存在 $ S $ 是 $ T $ 的前缀，那么显然 $ T $ 在 $ S $ 之后，则贡献一定为 $ 0 $。

对于其它的情况，显然会由 $ \texttt{LCP} $ 之后的第一个不同的字符决定，而对于这种显然在所有字典序关系中两者的偏序关系的概率是相同的，所以此时的贡献为 $ \dfrac{1}{2} $。那么对于字符串 $ S $，若其前缀串有 $ x $ 个，满足有 $ S $ 前缀的串有 $ y $ 个，那么答案即为：
$$
x \times 1 + y \times 0 + (n - x - y - 1) \times \dfrac{1}{2} + 1
$$
然后对于求前缀，显然可以通过 Trie树 解决，同时也可以考虑一些更简单的方法：

开一个 `unordered_set`，往里面丢每个串的哈希值，然后对于每个串的每个前缀的哈希在里面查一下然后记录即可，最终复杂度 $ O(\sum \lvert S_i \rvert) $。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)
#define BASE (31ll)

template < typename T = int >
inline T read(void);

int N;
int cntx[510000], cnty[510000];
ll inv_2;
string S[510000];
unordered_map < unll, int > idx;

ll qpow(ll a, ll b){
    ll ret(1), mul(a);
    while(b){
        if(b & 1)ret = ret * mul % MOD;
        b >>= 1;
        mul = mul * mul % MOD;
    }return ret;
}

int main(){
    inv_2 = qpow(2, MOD - 2);
    N = read();
    for(int i = 1; i <= N; ++i){
        cin >> S[i];
        unll cur(0);
        for(auto c : S[i])(cur *= BASE) += c;
        idx.insert({cur, i});
    }
    for(int i = 1; i <= N; ++i){
        unll cur(0);
        for(auto c : S[i]){
            (cur *= BASE) += c;
            if(idx.find(cur) != idx.end())++cntx[i], ++cnty[idx[cur]];
        }cntx[i]--, cnty[i]--;
    }
    for(int i = 1; i <= N; ++i)
        printf("%lld\n", (cntx[i] + (N - cntx[i] - cnty[i] - 1) * inv_2 % MOD + 1) % MOD);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_18 初稿

---

## 作者：Take_A_Single_6 (赞：0)

很智慧的一道期望题。  
期望一般就是三种做法：期望的定义，终态逆推，期望线性性质。本题第三种显然不行，第二种在尝试的时候发现不好设计，考虑从期望的定义入手。  
考虑两个字符串 $s_1$ 和 $s_2$ 进行比较，有三种可能性：  
- $s_1$ 是 $s_2$ 的前缀，显然 $s_1$ 排在 $s_2$ 前。
- $s_2$ 是 $s_1$ 的前缀，显然 $s_1$ 排在 $s_2$ 后。
- 存在一个 $lcp(s_1,s_2)+1$ 的位置，两串该位置字符不同，显然谁在前都可能，概率为 $\frac{1}{2}$。

对于一个字符串的排名，我们设 $x1$ 表示有多少字符串是它的前缀，$x_2$ 表示它是多少字符串的前缀，那么它的排名即为 $1+x_1+\frac{n-x_1-x_2}{2}$。  
除法用逆元算一下，$x_1$ 直接查询字典树，$x_2$ 在建立字典树的时候统计一下有多少字符串经过了这个 $end$ 即可。  
代码如下：  

```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 998244353
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int n,nd[maxn][26],sz,val[maxn],siz[maxn],inv2=499122177;//逆元
string s[maxn];
void ins(string ss)
{
	int u=0;
	for(char i:ss)
	{
		if(!nd[u][i-'0'])nd[u][i-'0']=++sz;
		u=nd[u][i-'0'],siz[u]++;//x2
	}
	val[u]++;//x1
}
pr query(string ss)
{
	int u=0,sum=0;
	for(char i:ss)sum+=val[u],u=nd[u][i-'0'];
	return mk(sum,u);
}//sum和end都需要
signed main()
{
	n=read();
	pr x;
	for(int i=1;i<=n;i++)cin>>s[i],ins(s[i]);
	for(int i=1;i<=n;i++)x=query(s[i]),write((1+x.fir+(n-x.fir-siz[x.sec])*inv2%mod)%mod),puts("");
    return 0;
}
```

---

