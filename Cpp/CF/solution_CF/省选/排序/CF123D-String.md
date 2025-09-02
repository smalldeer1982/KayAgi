# String

## 题目描述

You are given a string $ s $ . Each pair of numbers $ l $ and $ r $ that fulfill the condition $ 1<=l<=r<=|s| $ , correspond to a substring of the string $ s $ , starting in the position $ l $ and ending in the position $ r $ (inclusive).

Let's define the function of two strings $ F(x,y) $ like this. We'll find a list of such pairs of numbers for which the corresponding substrings of string $ x $ are equal to string $ y $ . Let's sort this list of pairs according to the pair's first number's increasing. The value of function $ F(x,y) $ equals the number of non-empty continuous sequences in the list.

For example: $ F(babbabbababbab,babb)=6 $ . The list of pairs is as follows:

 $ (1,4),(4,7),(9,12) $

Its continuous sequences are:

- $ (1,4) $
- $ (4,7) $
- $ (9,12) $
- $ (1,4),(4,7) $
- $ (4,7),(9,12) $
- $ (1,4),(4,7),(9,12) $

Your task is to calculate for the given string $ s $ the sum $ F(s,x) $ for all $ x $ , that $ x $ belongs to the set of all substrings of a string $ s $ .

## 说明/提示

In the first sample the function values at $ x $ equal to "a", "aa", "aaa" and "aaaa" equal 10, 6, 3 and 1 correspondingly.

In the second sample for any satisfying $ x $ the function value is 1.

## 样例 #1

### 输入

```
aaaa
```

### 输出

```
20
```

## 样例 #2

### 输入

```
abcdef
```

### 输出

```
21
```

## 样例 #3

### 输入

```
abacabadabacaba
```

### 输出

```
188
```

# 题解

## 作者：Rushroom (赞：6)

萌萌的多重经验 string 捏。

### 前置芝士

> 后缀数组
>
> 并查集

### 做法

先枚举子串长度，根据 OI-wiki 上的这一条定理：

$\operatorname{lcp}(sa_i,sa_j)=\min\{height_{i+1\dots j}\}$

可知，如果 $\forall l \le i \le r,height_i<=len$，那么这个长度为 $len$ 的子串就出现了 $r-l+2$ 次（后缀 $(l-1)\dots r$）。

问题转化成：给定子串长度 $len$，求出 $height$ 数组中每段满足上述条件的长度。

很明显不能对于每个 $len$ 单独扫一遍，其实在计算 $len=k$ 时，可以利用 $len=k+1$ 时的结果，只需要再考虑那些 $height_i=k$ 的情况，然后把 $i-1$ 和 $i$ 所在的块合并即可。可以用并查集维护。

具体说一下计算答案：

先将答案初始设为 $\frac{n(n+1)}{2}$（不考虑重复的情况）。当合并大小分别为 $x$ 和 $y$ 的两个连通块时，答案加上 $len\cdot (val(x+y)-val(x)-val(y))$，其中 $val(n)=\frac{n(n+1)}{2}$。乘上 $len$ 是因为要处理 $1\dots len$ 的情况。

[**Code**](https://www.luogu.com.cn/paste/vn4vrdzl)

### 多重经验

SA+并查集，经典 trick，只不过是改改式子。

> [P2178 [NOI2015] 品酒大会](https://www.luogu.com.cn/problem/P2178)
>
> [P4248 [AHOI2013]差异](https://www.luogu.com.cn/problem/P4248)
>
> [CF802I Fake News (hard)](https://www.luogu.com.cn/problem/CF802I)

---

## 作者：Alex_Wei (赞：5)

> XV. [CF123D String](https://www.luogu.com.cn/problem/CF123D)

> 题意简述：给出 $s$，求所有 $s$ 的子串 $p$ 在 $s$ 中的出现位置的所有子串个数，**字符串**的重复子串只算一次。

本文节选自 [我的 SAM 刷题笔记](https://www.cnblogs.com/alex-wei/p/Suffix_Automaton_Involution.html)，编号为 XV。

---

这是什么板子题？

对 $s$ 建出 SAM 可以自动去重，考虑每个状态 $p$，它所表示的字串个数为 $len(p)-len(link(p))$，出现次数为 $p$ 在 $link$ 树上的子树所包含的终止节点个数（终止节点是 $s$ 所有前缀在 SAM 上表示的状态），记为 $ed_p$。那么答案为 $\sum_{i=1}^{cnt} \frac{ed_p(ed_p+1)}{2}\times (len(p)-len(link(p)))$。

时间复杂度线性。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x,v) memset(x,v,sizeof(x))

const int N=2e5+5;
const int S=26;

int cnt,las,son[N][S],ed[N],fa[N],len[N],buc[N],id[N];
void clear(){
	mem(son,0),mem(ed,0),mem(fa,0),mem(len,0),mem(buc,0);
	cnt=las=1;
} void ins(char s){
	int p=las,cur=++cnt,it=s-'a';
	len[cur]=len[p]+1,las=cur,ed[cur]=1;
	while(!son[p][it])son[p][it]=cur,p=fa[p];
	if(!p)return fa[cur]=1,void();
	int q=son[p][it];
	if(len[p]+1==len[q])return fa[cur]=q,void();
	int cl=++cnt;
	fa[cl]=fa[q],fa[q]=fa[cur]=cl,len[cl]=len[p]+1;
	memcpy(son[cl],son[q],sizeof(son[q]));
	while(son[p][it]==q)son[p][it]=cl,p=fa[p];
} ll build(char *s){
	int n=strlen(s+1); clear();
	for(int i=1;i<=n;i++)ins(s[i]);
	for(int i=1;i<=cnt;i++)buc[len[i]]++;
	for(int i=1;i<=n;i++)buc[i]+=buc[i-1];
	for(int i=cnt;i;i--)id[buc[len[i]]--]=i;
	for(int i=cnt;i;i--)ed[fa[id[i]]]+=ed[id[i]];
	ll ans=0;
	for(int i=1;i<=cnt;i++)ans+=1ll*ed[i]*(ed[i]+1)/2*(len[i]-len[fa[i]]);
	return ans;
}

int n;
char s[N];
int main(){
	scanf("%s",s+1),cout<<build(s)<<endl; 
	return 0;
}
```

---

## 作者：chenxia25 (赞：2)

这个题感觉还算有点意思。是个远古场的 2300，感觉无论如何现在评的话也得有 2400 吧。

看到关于要区分本质不同字符串的，想到 SA，在排好序的后缀数组上遍历搞事情。

我们考虑枚举贡献子串的长度。那么显然 $hi$ 数组上连续 $\geq len$ 表示连续一段相等的这么长的子串。于是可以在每个位置将它放进要割裂这个位置的那个 `vector` 里，从小到大枚举 $len$，用一个 `set` 维护相等段同时维护总贡献即可。注意把 $n-len+2\sim n$ 这些无效的减掉。

---

## 作者：攀岩高手 (赞：2)

## 题意 ##

枚举字符串 $s$ 的每一个本质不同的子串 $ss$ ，令 $cnt(ss)$ 为子串 $ss$ 在字符串 $s$ 中出现的个数，求

$$ \sum \frac{cnt(ss)\times [cnt(ss)+1]}{2} $$

## 思路 ##

- 后缀数组 + 单调栈；
- 将 $s$ 的后缀排序，求出 $height$ 数组；
- **每个后缀的每个前缀都是原字符串的一个子串**；
- 则 $height$ 数组中连续不小于 $k$ 的一段就包含了一些长度为 k 的重复子串；
- 维护递增的单调栈统计答案。单调栈本身的意义是：栈内的每一个元素到当前元素为止，没有比它小的元素。将这一性质应用到后缀数组上，则表示这个元素的 $height$ 就是这一段的最长公共前缀长度；
- 可是这么做可能会重复统计答案。一个更长的公共前缀会被包含它的较短一些的公共前缀再次统计它的前若干个子串。所以我们真正统计的子串个数应该是：

`当前元素LCP长度 - max(栈中下一个元素的LCP长度, 即将加入的元素的LCP长度)`

## 代码 ##

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN=110000;
const int MAXS=256;
int n; char a[MAXN];
int sa[MAXN], rnk[2*MAXN], rnk1[2*MAXN];
int st[MAXS], cnt[MAXN], tmp[MAXN];
int height[MAXN], top;
struct Node
{
    int id, val;
    Node(int i=0, int v=0): id(i), val(v) {}
} sta[MAXN];
int main()
{
//	freopen("CF123D.in", "r", stdin);
//	freopen("CF123D.out", "w", stdout);
    scanf("%s", a+1); n=strlen(a+1);
    memset(st, 0, sizeof st);
    memset(rnk, 0, sizeof rnk);
    for (int i=1; i<=n; i++) st[a[i]]=1;
    for (int i=1; i<MAXS; i++) st[i]+=st[i-1];
    for (int i=1; i<=n; i++) rnk[i]=st[a[i]];
    for (int k=0, p=1; k<n&&p<=n; p<<=1)
    {
        memset(cnt, 0, sizeof cnt);
        for (int i=1; i<=n; i++) cnt[rnk[i+p]]++;
        for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
        for (int i=n; i>=1; i--) tmp[cnt[rnk[i+p]]--]=i;
        memset(cnt, 0, sizeof cnt);
        for (int i=1; i<=n; i++) cnt[rnk[i]]++;
        for (int i=1; i<=n; i++) cnt[i]+=cnt[i-1];
        for (int i=n; i>=1; i--) sa[cnt[rnk[tmp[i]]]--]=tmp[i];
        memcpy(rnk1, rnk, sizeof rnk1);
        rnk[sa[1]]=k=1;
        for (int i=2; i<=n; i++)
        {
            if (rnk1[sa[i]]!=rnk1[sa[i-1]]||rnk1[sa[i]+p]!=rnk1[sa[i-1]+p])
                k++;
            rnk[sa[i]]=k;
        }
    }
    height[n+1]=0;
    for (int i=1, k=0; i<=n; i++)
    {
        if (rnk[i]==1)
        {
            height[rnk[i]]=k=0;
            continue;
        }
        if (--k<0) k=0;
        while (a[i+k]==a[sa[rnk[i]-1]+k]) k++;
        height[rnk[i]]=k;
    }
    long long ans=0;
    for (int i=1; i<=n; i++)
    	ans+=n-sa[i]+1-max(height[i], height[i+1]);
    top=0;
    for (int i=1; i<=n+1; i++)
    {
    	int t=i;
        while (top>0&&height[i]<sta[top-1].val)
        {
            int l=i-sta[--top].id+1;
            int k=sta[top].val-max(height[i], top>0?sta[top-1].val:0);
            ans+=1ll*l*(l+1)/2*k;
            t=min(t, sta[top].id);
        }
        if (top==0||height[i]>sta[top-1].val)
            sta[top++]=Node(t, height[i]);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：gcx12012 (赞：1)

#### 题目大意
给定一个字符串 $s$，定义 $cnt(a)$ 为子串 $a$ 在 $s$ 中出现的次数,求
$$\sum \frac{cnt(a)(cnt(a)+1)}{2}$$


------------

#### 思路
后缀排序想必大家都会吧。

设 $n=|s|$，求出 $height$ 数组以后，我们发现我们要求的答案是这么一个东西

$$\frac{n(n+1)}{2}+\sum_{i=1}^n\sum_{j=i}^n\min(height_i,height_{i+1},...,height_j)$$
对于后面的式子，这里提供一个麻烦但是好理解的倍增求法。


------------
#### 做法
首先我们把 $height$ 数组对应的 ST 表预处理出来。

然后设 $l_i$ 为左边第一个比 $height_i$ 小的 $height_{l_i}$,如果没有我们设 $l_i=0$。

枚举每一个点 $i$，我们暴力跳到它的上级 $l_i$ 并使答案加上 $height_i\times (i-l_i)$，直到 $i=0$ 为止。

这样的时间复杂度是 $O(n^2)$ 的，我们还需要进一步的优化。

由定义可知 $l_i<i$，于是它们的关系构成了一棵树。

我们预处理出 $i$ 的 $2^j$ 级祖先 $f_{i,j}$ 以及从 $i$ 跳到 $f_{i,j}$ 对答案的贡献 $val_{i,j}$，然后往上一直跳跳到 $0$ 为止即可。

这样的时间复杂度是 $O(n\log_2n)$ 的，可以通过。


------------
#### 代码
```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define For(i,a,b) for(ll i=a;i<=b;i++)
#define Rof(i,a,b) for(ll i=a;i>=b;i--)
#define N 200010
#define pb push_back
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define SP fixed<<setprecision(12)
#define mk make_pair
#define pque priority_queue

using namespace std;
ll st[N][20],lg[N],l[N],f[N][20],val[N][20],height[N];
char s[N];
int sa[N],rk[N<<1],prerk[N<<1],cnt[N],id[N];
int n;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll qry(int l,int r){
	int k=lg[r-l+1];
	return min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
	cin>>(s+1);
	n=strlen(s+1);
	For(i,1,n) cnt[rk[i]=s[i]]++;
	For(i,1,127) cnt[i]+=cnt[i-1];
	Rof(i,n,1) sa[cnt[rk[i]]--]=i;
	memcpy(prerk+1,rk+1,n*sizeof(int));
	for(int i=1,p=0;i<=n;i++){
		if(prerk[sa[i]]==prerk[sa[i-1]]) rk[sa[i]]=p;
		else rk[sa[i]]=++p;
	}
	for(int m=1;m<n;m<<=1){
		memset(cnt,0,sizeof(cnt));
		memcpy(id+1,sa+1,n*sizeof(int));
		For(i,1,n) cnt[rk[id[i]+m]]++;
		For(i,1,n) cnt[i]+=cnt[i-1];
		Rof(i,n,1) sa[cnt[rk[id[i]+m]]--]=id[i];
	//-----------------------------------------------------	
		memset(cnt,0,sizeof(cnt));
		memcpy(id+1,sa+1,n*sizeof(int));
		For(i,1,n) cnt[rk[id[i]]]++;
		For(i,1,n) cnt[i]+=cnt[i-1];
		Rof(i,n,1) sa[cnt[rk[id[i]]]--]=id[i];
		memcpy(prerk+1,rk+1,n*sizeof(int));
	//-----------------------------------------------------	
		int now=0;
		for(int i=1,p=0;i<=n;i++){
			if(prerk[sa[i]]==prerk[sa[i-1]] && prerk[sa[i]+m]==prerk[sa[i-1]+m]) rk[sa[i]]=p;
			else rk[sa[i]]=++p;
			now=p;
		}
		if(now==n) break;
	}
	//For(i,1,n) printf("%d ",sa[i]);
	for(int i=1,k=0;i<=n;i++){
		if(rk[i]==1){
			height[rk[i]]=k=0;
			continue;
		}
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		height[rk[i]]=k;
	}
	//For(i,1,n) printf("%d ",height[i]);
	ll ans=1ll*n*(n+1)/2;
	/*
	For(i,1,n){
		For(j,i,n){
			int mn=1e9;
			For(k,i,j) mn=min(mn,height[k]);
			ans+=1ll*mn;
		}
	}
	cout<<ans<<endl;
	*/
	For(i,1,n) st[i][0]=height[i];
	For(i,2,n) lg[i]=lg[i>>1]+1;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	For(i,1,n){
		if(qry(1,i)==height[i]) continue;
		int now=i;
		Rof(j,19,0){
			if(now-(1<<j)<1) continue;
			if(qry(now-(1<<j),i)==height[i]) now-=(1<<j);
		}
		l[i]=now-1;
	}
	For(i,1,n) f[i][0]=l[i],val[i][0]=height[i]*(i-l[i]);
	For(j,1,19){
		For(i,1,n){
			f[i][j]=f[f[i][j-1]][j-1];
			val[i][j]=val[i][j-1]+val[f[i][j-1]][j-1];
		}
	}
	For(i,1,n){
		int now=i;
		Rof(j,19,0){
			if(f[now][j]){
				ans+=val[now][j];
				now=f[now][j];
			} 
		}
	}
	cout<<ans;
   	return 0;
}

```


---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

标签里面不包含 SAM，惹

这道题目需要处理不同子串，很快想到后缀结构 ~~，在这里我继续用 SAM~~

首先，注意到在计算 $f$ 里面 ”排序“ 一点作用都没有，应为仅仅关心出现位置序列的子串个数。子串个数又仅仅依赖这个序列多长 - 具体说，如果序列长度是 $n$，子串个数是

$$f(n) = \frac{n(n+1)}{2}$$

那现在题目求的东西是 给定模式串 $S$，求
$$\sum_{s}f(s\text{ 在 }S\text{ 里面出现次数})$$
对与所有字符串 $s$。显然如果 $s$ 在 $S$ 里面不出现，对答案没有贡献，所以就考虑 $S$ 中所有本质不同子串。

SAM 的一个重要功能是维护一个字符串在一个固定模式串里面出现次数，这个计算方法是 `cnt[i]=` 后缀树上这个节点有多少个字符串的后缀节在它子树里面。

问题是在 SAM 里面的一个节点可能对应很多个字符串。这些对应的字符串都是 ["$endpos$-相似"](https://cp-algorithms.com/string/suffix-automaton.html)，所以 `cnt` 都一样，只需要计算每一个节点对应多少子串。

每一个在 SAM 上从初始节点开始的一个路径表示一个子串，所以每个节点对应的字符串就是有多少个从初始节点开始，本节点结束的路径 - 这个直接用 DAG 上 DP 求即可。

最后直接乘上贡献得到答案。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

namespace SAM {
	constexpr int MAXN = 100005;
	constexpr int MAXT = 177;
	struct state {
		int len, lnk, cnt;
		map<int, int> nxt;
	} st[MAXN*2];
	int sz, last;
	int mknode(int fro = -1) {
		int nd = sz++;
		if(fro != -1) {
			st[nd].len = 0;
			st[nd].nxt = st[fro].nxt;
			st[nd].lnk = st[fro].lnk;
			st[nd].cnt = 0;
		} else {
			st[nd].nxt.clear();
			st[nd].lnk = 0;
			st[nd].len = 0;
			st[nd].cnt = 1;
		}
		return nd;
	}
	int K; int lgest = -1, rightest = -1;
	void init() {
		sz = last = 0;
		mknode(); st[0].len = 0, st[0].lnk = -1;
		lgest = rightest = -1;
	}
	void ext(int c) {
		int cur = mknode();
		st[cur].len = st[last].len+1;
		int p = last;
		while(p != -1 && !st[p].nxt.count(c)) st[p].nxt[c] = cur, p = st[p].lnk;
		if(p == -1) st[cur].lnk = 0;
		else {
			int q = st[p].nxt[c];
			if(st[p].len + 1 == st[q].len) st[cur].lnk = q;
			else {
				int cl = mknode(q);
				st[cl].len = st[p].len + 1; st[cur].lnk = st[q].lnk = cl;
				while(p != -1 && st[p].nxt[c] == q) st[p].nxt[c] = cl, p = st[p].lnk;
			}
		}
		last = cur;
	}
	int aray[MAXN*2];
	int _ljt[MAXN*2];
	vector<int> REE[MAXN*2];
	ll ljt(int u) {
		if(_ljt[u] != -1) return _ljt[u];
		_ljt[u] = 0;
		for(int& k:REE[u]) _ljt[u] += ljt(k);
//		if(_ljt[u] != 1) cout << u << ' ' << _ljt[u] << endl;
		return _ljt[u];
	}
	ll makelpo() {
		rep(i, sz-1) aray[i] = i+1;
		sort(aray, aray+sz, [&](const int&l, const int&r){return st[l].len > st[r].len;});
		rep(i, sz-1) st[st[aray[i]].lnk].cnt += st[aray[i]].cnt;
		rep(i, sz) for(auto& k:st[i].nxt) REE[k.se].pb(i); 
		memset(_ljt, -1, sizeof _ljt);
		_ljt[0] = 1;
		ll ans = 0;
		rep(i, sz) if(st[i].len) ans += 1ll * ljt(i) * st[i].cnt * (st[i].cnt + 1) / 2;
		return ans;
	}
}

char buf[100005];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    gstr(buf);
	int n = strlen(buf);
	SAM::init();
	rep(i, n) SAM::ext(buf[i] - 'a');
	print(SAM::makelpo());
}
```

---

## 作者：lleo (赞：1)

/*
这题考察的是对后缀数组求得LCP的运用，不会后缀数组请先去找模板题学一下
*/

```
#include<bits/stdc++.h>
#define maxn 100005
#define rep(i,a,b) for(long long i=a;i<=b;i++)
#define rrep(i,a,b) for(long long i=a;i>=b;i--)
#define inf 0x3f3f3f3f
using namespace std;
long long n;
int m;
int sa[maxn],rank[maxn],tmp[maxn],tax[maxn];
long long dp[maxn];
long long h[maxn];
long long j,k;
int cnt;
char c[maxn];
long long ans;
int Min;

int t[maxn<<2];

//线段树维护区间最小值 
int pushup(int rt){
	t[rt]=min(t[rt<<1],t[rt<<1|1]);
}

void update(int l,int r,int rt,int x,int y){
	if(l==r){
		t[rt]=y;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(l,mid,rt<<1,x,y);else update(mid+1,r,rt<<1|1,x,y);
	pushup(rt);
}

int query(int l,int r,int rt,int ll,int rr){
	if(ll<=l&&rr>=r){
		return t[rt];		
	}
	int s=inf;
	int mid=(l+r)>>1;
	if(ll<=mid)s=min(s,query(l,mid,rt<<1,ll,rr));
	if(rr>mid)s=min(s,query(mid+1,r,rt<<1|1,ll,rr));
	return s;
}

void rsort(){  //基数排序 
	memset(tax,0,sizeof(tax));
	rep(i,1,n)tax[rank[tmp[i]]]++;
	rep(i,1,m)tax[i]+=tax[i-1];
	rrep(i,n,1)sa[tax[rank[tmp[i]]]--]=tmp[i];  //要从尾到头循环，保证在之前的顺序下再次排序 
}

int main(){
	scanf("%s",&c);
	n=strlen(c);
	rep(i,1,n){
		rank[i]=c[i-1];
		tmp[i]=i;
		m=max(m,int(c[i-1]));
	}
	rsort();
	
	for(k=1;k==1||rank[sa[n]]<n;k<<=1){
		m=rank[sa[n]];
		cnt=0;
		rep(i,n-k+1,n)tmp[++cnt]=i;
		rep(i,1,n)if(sa[i]>k)tmp[++cnt]=sa[i]-k;
		rsort();
		swap(tmp,rank);
		rank[sa[1]]=1;
		rep(i,2,n)rank[sa[i]]=rank[sa[i-1]]+!(tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+k]==tmp[sa[i-1]+k]);
	}
	j=0;
	rep(i,1,n){
		if(j)j--;
		if(rank[i]==n)continue;
		for(;c[i+j-1]==c[sa[rank[i]+1]+j-1];j++);
		h[rank[i]]=j;
	}
	
	/*
	可以发现答案为：
	ans=1+2+3+...+n;
	rep(i,1,n-1)
		rep(j,i+1,n-1)
			ans+=min(h[i],h[i+1],h[i+2],...,h[j]);
	但这样是n方的算法，所以要考虑优化
	
	首先这样是单独计算的，浪费了之前计算结果。为了把之前计算结果利用起来，考虑从末尾向头计算，并用dp[]数组记录下来
	所以程序可以改成这样 ：
	ans=1+2+...+n;
	Min=inf;	//Min维护从n到i的最小值 
	rrep(i,n-1,1){
		if(h[i]<=Min)	//h[i]为i到n-1的最小值
		dp[i]=h[i]*(n-i),Min=h[i]	// dp[i]=min(h[i])+min(h[i],h[i+1])+...+min(h[i],h[i+1],...,h[n-1])=h[i]*(n-i)
		else{
			j=min(pos[0 to h[i]-1)	
			//寻找第一个比h[i]小的位置，即在i到j-1中h[i]最大，在j到n-1中min(h[i to j])+...+min(h[i to n-1])=min(h[j to j])+...+min(h[j to n-1])=dp[j] 
			dp[i]=h[i]*(j-i)+dp[j]
		}
		ans+=dp[i];
		pos[h[i]]=i;	pos[i]表示h[]中i最早出现的位置 
	}
	但这样仍然是n方的，再用线段树维护pos[]区间最小值，复杂度就变为nlogn了 
	*/
	
	memset(t,0x3f,sizeof(t));
	Min=inf;
	ans=n*(n+1)/2;
	rrep(i,n-1,1){
		if(h[i]<=Min){
			dp[i]=(h[i])*(n-i);
			Min=h[i];
		}
		else{
			k=query(0,n-1,1,0,h[i]-1);
			dp[i]=dp[k]+(h[i])*(k-i);
		}
		ans+=dp[i];
		update(0,n-1,1,h[i],i);
	}
	
	cout<<ans<<endl;
}
```

---

## 作者：L_zaa_L (赞：0)

## 前置知识
你得先学会后缀自动机（至少这个题解是用后缀自动机，如果你想用后缀数组做也可以）

[后缀自动机学习笔记](https://zhuanlan.zhihu.com/p/665086302)

## 思路
后缀自动机的每个节点都代表一个类，我们不需要算出每个字符串出现的次数，之用算出类出现的次数即可（类里面包含很多个字符串）。

对于每一个子串的出现次数，我们可以利用 parent 树进行计算。

对于每一次插入，一个类出现次数增加，当且仅当这是当前的后缀，也就是把这个点的 parent 链都加一。

之间将每个节点按照字符串最长的字符串的长度进行排序（一个等价类中，出现的次数一定相同，可以不算小的，节约时间）。

从下往上更新即可每个后缀出现的次数即可，很明显最开始的赋值只需要原串的后缀赋值即可，不能附多了。

然后就是我们算出了一个类的出现次数之后呢，需要我们算出一个类中有多少个字符串，字符串的个数很容易能想到是 $len_i-len_{lnk_i}$，直接相乘即可。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
long long ans;
int lnk[4000005];
map<int,int>ch[4000005];
int len[4000005],last=1,tot=1;
int siz[4000005];
void insert(int c)
{
	int p=last,cur=++tot;
	last=cur;
	len[cur]=len[p]+1;
	for(;p&&!ch[p].count(c);p=lnk[p]) ch[p][c]=cur;//沿着last的后缀链接跳，找到可以转移的，同时连边
	if(!p) lnk[cur]=1;//如果到了根节点，说明之前没有出现过c，也就构成不了新的等价类
	else{
		int q=ch[p][c];
		if(len[p]+1==len[q]) lnk[cur]=q;
		else{
			int copy=++tot;//将原有的一个节点进行分裂
			len[copy]=len[p]+1;//更新最长长度
			lnk[copy]=lnk[q];//更新后缀链接
			ch[copy]=ch[q];//出边直接继承
			lnk[q]=lnk[cur]=copy;//
			for (;ch[p].count(c)&&p;p=lnk[p]){
				if(ch[p][c]==q)ch[p][c]=copy;//分入边
				else break;
			}
		}	
	}
	siz[cur]=1;
}
int tag[2000005],a[2000005];
void query(){
	for(int i=1;i<=tot;i++) tag[len[i]]++;
	for(int i=1;i<=tot;i++) tag[i]+=tag[i-1];
	for(int i=1;i<=tot;i++) a[tag[len[i]]--]=i;//将树按照子树大小进行排序，方便从下往上更新（越往下子串长度越大）
	//这里运用的是基数排序
	for(int i=tot;i>=1;i--) siz[lnk[a[i]]]+=siz[a[i]];//从下往上进行更新。
	return;
}
signed main(){
	string s;
	cin>>s;
	for(int i=0;i<(int)s.size();i++){
		insert(s[i]-'a');
	}
	query();
	long long ans=0;
	for(int i=tot;i>=1;i--){
		ans+=1ll*siz[a[i]]*(siz[a[i]]+1)/2*(len[a[i]]-len[lnk[a[i]]]);//每个类的贡献就是，类的出现次数乘上字符串的个数
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Gaode_Sean (赞：0)

由于题面中出现了“子串”这个词，我们很容易想到用后缀数组解决此题。

依照套路先求出 SA 数组以及 rank 数组，并在此基础上求出 height 数组（$\text{height}_i=\text{LCP}(\text{sa}_{i},\text{sa}_{i-1})$）。

对于一个长度为 $\text{len}$ 的子串，如果它在字符串中出现了 $x$ 次，那么一定能找到一个 $k$，使得 $\min \{ \text{height}_{k \dots k+x-2} \} \ge \text{len}$。

我们可以枚举子串的长度 $\text{len}$，但是复杂度会爆炸。

考虑使用并查集。具体地，我们从大到小枚举 $\text{len}$，对于 $\text{height}_i=\text{len}$ 的情况，合并 $i$ 和 $i-1$ 两个块。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
vector<int> vec[N];
int n,m=122;
int x[N],y[N],sa[N],c[N],rk[N],he[N],fa[N];
ll ans,sz[N];
char s[N];
int get(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=get(fa[x]);
}
void SA()
{
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=2;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=2;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y),num=x[sa[1]]=1;
		for(int i=2;i<=n;i++)
		{
			if(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]) x[sa[i]]=num;
			else x[sa[i]]=++num;
		}
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]>1)
		{
			if(k) k--;
			while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
			he[rk[i]]=k;
			vec[he[rk[i]]].push_back(rk[i]);
		}
	}
}
void solve()
{
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
	ans=1ll*n*(n+1)/2ll;
	for(int i=n-1;i>=0;i--)
	{
		for(int j=0;j<vec[i].size();j++)
		{
			int x=vec[i][j];
			int a=get(x),b=get(x-1);
			ans+=((sz[a]+sz[b])*(sz[a]+sz[b]+1)-sz[a]*(sz[a]+1)-sz[b]*(sz[b]+1))*1ll*i/2ll;
			sz[a]+=sz[b],sz[b]=0,fa[b]=a;
		}
	}
	printf("%lld",ans);
}
int main()
{
	scanf("%s",s+1); n=strlen(s+1);
	SA();
	solve();
	return 0;
}
```

---

## 作者：JK_LOVER (赞：0)

## 题意
给出字符串 $s$ ,定义子串 $a$ 在 $s$ 中的出现次数为 $cnt(a)$ ，求 $\sum\frac{cnt(a)\times(cnt(a)+1)}{2}$ 。[$QAQ$](https://www.luogu.com.cn/blog/xzc/solution-cf123d)
## 分析
$\text{SAM}$ 板子题。

- 考虑每个串的出现次数应该是该等价类可以到达的所以终止节点的大小，也就是 $\text{endpos}$ 集合的大小。

- 考虑一个等价类有多少个子串，可以在 $\text{DAWG}$ 上做 $dp$ ，也可以根据后缀链接的性质该节点的子串数为 $\text{len(a)-len(link(a))}$ 。

- 只需要遍历每个节点就可以了，时间复杂度为 $O(n)$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXLEN = 2000011;
struct SAM{
	struct Node{
		int len,link,si;
		unordered_map<int,int> nxt;
	};
	Node st[MAXLEN << 1];
	int si,last;
	void init(){
		st[0].len = 0;
		st[0].link = -1;
		si++;
		last = 0;
	}
	void insert(int c){
		int cur = si++;
		st[cur].si = 1;
		st[cur].len = st[last].len + 1;
		int p = last;
		while(p != -1 && !st[p].nxt[c]){
			st[p].nxt[c] = cur;
			p = st[p].link;
		}
		if(p == -1) {
			st[cur].link = 0;
		}
		else 
		{
			int q = st[p].nxt[c];
			if(st[p].len + 1 == st[q].len)
			{
				st[cur].link = q;
			}
			else 
			{
				int clone = si++;
				st[clone].len = st[p].len + 1;
				st[clone].nxt = st[q].nxt;
				st[clone].link = st[q].link;
				while(p != -1 && st[p].nxt[c] == q)
				{
					st[p].nxt[c] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
}sam;
const int N = 1000010;
int head[N<<1],cnt,nxt[N<<2],to[N<<2];
void build(){
	for(int i = 1;i < sam.si;i++)
	{
		int x = sam.st[i].link,y = i;
		to[++cnt] = y;nxt[cnt] = head[x];head[x] = cnt;
	}
}
long long ans = 0;
void dfs(int u){
	for(int i = head[u];i;i = nxt[i]){
		dfs(to[i]);sam.st[u].si+=sam.st[to[i]].si;
	}
	if(u == 0) return;
	long long cnt = 1LL * sam.st[u].si;
	ans += cnt * (cnt + 1) / 2 * (-sam.st[sam.st[u].link].len + sam.st[u].len);
}
char ch[N];
int main()
{
	scanf("%s",ch);
	int L = strlen(ch);
	sam.init();
	for(int i = 0;i < L;i++) sam.insert((int)ch[i]-'a');
	build();
	dfs(0);
	cout << ans << endl;
	return 0;
}
```


---

## 作者：huayucaiji (赞：0)

这个题和 CF811D 很像，代码只有一点点不同。~~题解也几乎一模一样~~

首先看到子串的问题容易想到后缀数组，所以我们可以先对字符串求一遍后缀数组以及 `height` 数组。
我们其实可以想得到单调栈。我们可以考虑对于 `height` 数组维护一个单调递增的栈。一旦我们要弹出栈顶元素时，我们就知道他一定会对答案做出新贡献，即 $cnt(s,p)>1$。我们只需要把这些有新贡献的串的个数算出来，然后把其他只出现过一次的串的数量统计出来，答案就算出来了。

时间复杂度 $O(n\log n+n)$。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=1e5+10; 

int n,m;
int sa[MAXN],rnk[MAXN],height[MAXN],tmp[MAXN],a[MAXN],b[MAXN],cnt[MAXN];
char s[MAXN];

void bucket_sort(int v[]) {
	fill(cnt,cnt+m+1,0);
	for(int i=1;i<=n;i++) {
		cnt[v[i]+1]++;
	}
	for(int i=1;i<=m;i++) {
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=n;i++) {
		tmp[++cnt[v[sa[i]]]]=sa[i];
	}
	for(int i=1;i<=n;i++) {
		sa[i]=tmp[i];
	}
}

void get_sa() {
	for(int i=1;i<=n;i++) {
		rnk[i]=tmp[i]=s[i];
		sa[i]=i;
	}
	sort(tmp+1,tmp+n+1);
	m=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++) {
		rnk[i]=lower_bound(tmp+1,tmp+m+1,rnk[i])-tmp;
	}
	
	for(int l=1;l<n;l<<=1) {
		for(int i=1;i<=n;i++) {
			a[i]=rnk[i];
			b[i]=(i+l<=n? rnk[i+l]:0);
		}
		bucket_sort(b);
		bucket_sort(a);
		
		m=0;
		for(int i=1;i<=n;i++) {
			if(a[sa[i]]!=a[sa[i-1]]||b[sa[i]]!=b[sa[i-1]]) {
				m++;
			}
			rnk[sa[i]]=m;
		}
	}
}

void get_height() {
	int h=0;
	for(int i=1;i<=n;i++) {
		if(h) {
			h--;
		}
		if(rnk[i]==1) {
			continue;
		}
		
		int p=i+h;
		int q=sa[rnk[i]-1]+h;
		
		while(p<=n&&q<=n&&s[p]==s[q]) {
			p++;
			q++;
			h++;
		}
		height[rnk[i]]=h;
	}
}

int solve() {
	int ans=0;
	stack<int> stk;
	for(int i=2;i<=n+1;i++) {
		while(!stk.empty()&&height[stk.top()]>height[i]) {
			int y=height[stk.top()];
			int x=height[i];
			stk.pop();
			int z=(stk.empty()? 0:height[stk.top()]);
			int len=i-(stk.empty()? 1:stk.top())-1;
			ans+=(y-max(x,z))*(len*(len+1)/2);
            //计算新的贡献
		}
		stk.push(i);
	}
	return ans+n*(n+1)/2;
}

signed main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	
	get_sa();
	get_height();
	
	printf("%lld\n",solve());
	return 0;
}


```

---

