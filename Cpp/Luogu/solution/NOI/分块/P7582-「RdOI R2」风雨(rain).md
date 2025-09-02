# 「RdOI R2」风雨(rain)

## 题目背景

经历过风雨的洗礼，小 Soup 才更懂得珍惜。他认为所有的一切对他来说都有重要的意义。为了能让这一切被自己牢牢铭记，小 Soup 决定用一些手段将它们记录下来。  

[$\text\color{white}{真正的题目背景}$](https://z3.ax1x.com/2021/03/29/c9xbLj.gif)


## 题目描述

小 Soup 在这段时间中记录了 $n$ 个有意义的东西，他把它们用字符串表示了出来，第 $i$ 个东西被表示成 $s_i$，并定义了它的价值 $a_i$。下面，小 Soup 会进行 $m$ 次操作。  
操作 $1$：小 Soup 将区间 $l,r$ 里的 $a_i$ 都加上一个常数 $k$。  
操作 $2$：小 Soup 将区间 $l,r$ 里的 $a_i$ 都赋值成一个常数 $k$。  
操作 $3$：小 Soup 给出了一段回忆，这段回忆形成了一个字符串 $S$，他想求 $S$ 在区间 $l,r$ 中的意义有多大。定义 $cnt_i$ 为 $s_i$ 在 $S$ 中的出现次数，则 $S$ 在区间 $l,r$ 中的意义为 $\sum\limits_{i=l}^r cnt_i\times a_i$。

## 说明/提示

**样例 $1$ 解释**

对于第一次询问，$s_1$ 出现了 $1$ 次，对价值贡献为 $1$；$s_2$ 出现了 $1$ 次，对价值贡献为 $2$；$s_3$ 出现了 $2$ 次，对价值贡献为 $2$，总价值为 $5$。  
对于第二次询问，$s_1$ 出现了 $2$ 次，对价值贡献为 $4$；$s_2$ 出现了 $1$ 次，对价值贡献为 $2$，总价值为 $6$。 

---

**数据范围**

|数据编号|$\sum s,\sum S$|$n,m$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim 2$|$\le5\times10^3$|$10^3$|$\diagdown$|
|$3\sim 4$|$\le2\times 10^5$|$3\times10^4$|没有 $1$ 操作|
|$5\sim 8$|$\le2\times 10^5$|$3\times10^4$|没有 $1,2$ 操作|
|$9\sim 13$|$\le2\times 10^5$|$3\times10^4$| $\diagdown$|

对于 $100\%$ 的数据，$1\le n,m\le3\times10^4,k\ge 1,\sum |S|,\sum |s|\le2\times10^5$，任何时刻 $1\le a_i\le2\times10^4$，保证只会出现 $a,b,c$ 三种字符。

## 样例 #1

### 输入

```
3 4
ab 1
ba 2
a 1
3 1 3 aba
1 1 2 1
2 2 3 2
3 1 2 abab```

### 输出

```
5
6```

## 样例 #2

### 输入

```
6 6
aba 3
ba 2
aa 2
c 1
abac 4
ab 2
3 2 5 abac
2 3 5 3
3 4 6 abc
1 2 3 1
3 1 3 aabaa
3 2 5 aabac```

### 输出

```
7
5
14
13```

## 样例 #3

### 输入

```
6 3
b 1
aa 8
cc 9
cac 8
ab 10
a 7
2 1 3 2
3 1 4 acac
3 1 6 ccaba```

### 输出

```
8
28```

# 题解

## 作者：abruce (赞：16)

感觉 AC 自动机可以出很毒瘤的数据结构题啊，可是为什么没人出啊。/kk  
难度和码量大致相当于一个比较简单的 Ynoi 吧。  
### 20pts  
直接暴力维护 $a_i$，暴力 KMP 即可。  
### 40pts  
线段树上每个节点开一个 AC 自动机，然后统计出现次数就可以了，时间复杂度 $O(nlogn)\sim O(nlog^2n)$。  
### 60pts  
似乎可以用 ODT 维护权值，然后将问题转化为区间内字符串在大串出现次数，线段树即可。注意上一个部分分不能用这种方法。  
## 100pts  
前置知识：[e-Government](https://www.luogu.com.cn/problem/CF163E)  
首先肯定是要建 AC 自动机的。区间加，区间推平，线段树？可是这个怎么 pushup 啊。我们想到另一种支持区间加，区间推平的数据结构——分块。让我们看分块怎么支持以上的操作。  
首先，我们每 $\sqrt{n}$ 个串建一个 AC 自动机，同时建出它的 fail 树。对于初始的 $a_i$ 我们像 e-Government 那样用一个树状数组进行子树加，单点查询。这样，我们在边角修改的时候也可以对树状数组进行操作。  
对于整块的修改，我们需要多记录一个 $tag$ 数组和一个 $dlt$ 数组。区间整块推平时，我们将 $dlt$ 数组修改为那个值，同时将 $tag$ 置为 $1$，代表这个区间已经被推平。区间加的时候，我们只需要对 $dlt$ 进行操作即可。  
在查询的时候，我们对于边角，直接暴力 KMP 即可。对于整块，我们分成两种情况产生贡献。  
如果这个区间 $tag$ 为 $1$，我们只需要查询这个块的所有串的出现次数和乘上 $dlt$ 即可。如果 $tag$ 为 $0$，则不仅需要查询这个块的所有串的出现次数和乘上 $dlt$，还需要在树状数组中进行查询。  
设字符串总长度为 $L$，则总时间复杂度 $O(L\sqrt{n}\log L)$，代码细节比较多，有点长，写的时候注意。  
```cpp
#include<bits/stdc++.h>
#define addtag(i,k) a[i]+=k,add(l[bj[i]],k),add(r[bj[i]]+1,-k)//给 i 的贡献加上 k
#define chtag(i,k) add(l[bj[i]],k-a[i]),add(r[bj[i]]+1,a[i]-k),a[i]=k//将 i 的贡献改为 k
using namespace std;
typedef long long ll;
inline int read() {
	int __x=0,__f=1;
	char __c=getchar();
	while(__c<'0'||__c>'9') {
		if(__c=='-')__f=-1;
		__c=getchar();
	}
	while(__c>='0'&&__c<='9') {
		__x=__x*10+__c-'0';
		__c=getchar();
	}
	return __x*__f;
}
inline void write(ll __x) {
	if(__x<0) {
		putchar('-');
		__x=-__x;
	}
	if(__x>=10)write(__x/10);
	putchar(__x%10+'0');
}
inline string readstr() {
	char __ch=getchar();
	string __st1="";
	while (__ch<'0'||__ch>'z')
		__ch=getchar();
	while (__ch>='0'&&__ch<='z')
		__st1+=__ch,__ch=getchar();
	return __st1;
}
const int maxn=2e5+5,mod=1e9+7;
struct edge {
	int next,to;
} e[maxn*2];
int t[maxn][3],fail[maxn],h[maxn],v[maxn],dlt[maxn],bj[maxn],l[maxn],r[maxn],bel[maxn],n,m,cnt,tot,pos,rt[maxn],lb[maxn],rb[maxn],nxt[maxn],sqrtn,sn;
ll c[maxn],a[maxn],tag[maxn];
string s[maxn];
queue<int> q;
void addedge(int x,int y) {
	e[++cnt].next=h[x];
	e[cnt].to=y;
	h[x]=cnt;
}
void insert(const string &s,int rot,int u) {
	int root=rot,len=s.length(),y;//插入以 rot 为根的 Trie 中
	for(register int i=0; i<len; i++) {
		y=s[i]-'a';
		if(!t[root][y]) {
			t[root][y]=++tot;
		}
		root=t[root][y];
	}
	v[root]++;
	bj[u]=root;
}
void getfail(int rot) {
	for(register int i=0; i<3; i++) {
		t[0][i]=rot;
	}
	q.push(rot);
	while(!q.empty()) {
		int u=q.front(),f=fail[u];
		q.pop();
		v[u]+=v[f];
		for(register int i=0; i<3; i++) {
			int j=t[u][i];
			if(!j) {
				t[u][i]=t[f][i];
				continue;
			}
			fail[j]=t[f][i];
			q.push(j);
		}
	}
}//构建 Trie 图
void dfs(int u) {
	l[u]=++pos;
	for(register int i=h[u]; i; i=e[i].next) {
		int j=e[i].to;
		dfs(j);
	}
	r[u]=pos;
}
void add(int x,int v) {
	while(x<=pos)c[x]+=v,x+=x&(-x);
}
ll ask(int x) {
	ll sum=0;
	while(x)sum+=c[x],x-=x&(-x);
	return sum;//答案需要开 long long
}
void clrtag(int w) {
	int v;
	for(register int i=lb[w]; i<=rb[w]; i++)v=0,tag[w]?v=dlt[w]:v=a[i]+dlt[w],chtag(i,v);//将这个区间的 dlt 清空，以便维护出 a_i 的真实值
	dlt[w]=tag[w]=0;
}
void add(int lx,int ry,int k) {
	int x=bel[lx],y=bel[ry],v;
	if(x==y) {
		if(tag[x])clrtag(x);
		for(register int i=lx; i<=ry; i++)addtag(i,k);
		return;
	}
	if(tag[x])clrtag(x);
	for(register int i=lx; i<=rb[x]; i++)addtag(i,k);
	if(tag[y])clrtag(y);
	for(register int i=lb[y]; i<=ry; i++)addtag(i,k);
	for(register int i=x+1; i<=y-1; i++)dlt[i]+=k;
}
void change(int lx,int ry,int k) {
	int x=bel[lx],y=bel[ry],v;
	if(x==y) {
		if(dlt[x])clrtag(x);
		for(register int i=lx; i<=ry; i++)chtag(i,k);
		return;
	}
	if(dlt[x])clrtag(x);
	for(register int i=lx; i<=rb[x]; i++)chtag(i,k);
	if(dlt[y])clrtag(y);
	for(register int i=lb[y]; i<=ry; i++)chtag(i,k);
	for(register int i=x+1; i<=y-1; i++)dlt[i]=k,tag[i]=1;
}
ll getkmp(string s,string t) {
	s=' '+s,t=' '+t;
	ll sum=0;
	nxt[1]=0;
	int n=s.length()-1,m=t.length()-1;
	for(register int i=2,j=0; i<=n; i++) {
		while(j>0&&s[i]!=s[j+1]) {
			j=nxt[j];
		}
		if(s[i]==s[j+1])j++;
		nxt[i]=j;
	}
	for(register int i=1,j=0; i<=m; i++) {
		while(j>0&&(j==n||t[i]!=s[j+1]))j=nxt[j];
		if(t[i]==s[j+1])j++;
		sum+=j==n;
	}
	return sum;
}
ll query(int lx,int ry,const string &st) {
	int x=bel[lx],y=bel[ry];
	ll ans=0;
	if(x==y) {
		for(register int i=lx; i<=ry; i++)if(s[i].length()<=st.length())ans+=getkmp(s[i],st)*(tag[x]?dlt[x]:a[i]+dlt[x]);
		return ans;
	}
	for(register int i=lx; i<=rb[x]; i++)if(s[i].length()<=st.length())ans+=getkmp(s[i],st)*(tag[x]?dlt[x]:a[i]+dlt[x]);
	for(register int i=lb[y]; i<=ry; i++)if(s[i].length()<=st.length())ans+=getkmp(s[i],st)*(tag[y]?dlt[y]:a[i]+dlt[y]);//注意此处必须先判谁的长度更长，否则复杂度会退化
	for(register int i=x+1; i<=y-1; i++) {
		int u=rt[i],len=st.length();
		for(register int j=0; j<len; j++) {
			u=t[u][st[j]-'a'];
			ans+=dlt[i]*v[u]+(!tag[i])*ask(l[u]);//在没有 tag 的情况下才在树状数组查询
		}
	}
	return ans;
}
int main() {
	int op,x,y,z;
	string st;
	n=read(),m=read();
	sqrtn=int(sqrt(n));
	sn=n/sqrtn+(n%sqrtn!=0);
	for(register int i=1; i<=sn; i++)lb[i]=(i-1)*sqrtn+1,rb[i]=min(i*sqrtn,n),rt[i]=++tot;
	for(register int i=1; i<=n; i++)bel[i]=(i-1)/sqrtn+1;
	for(register int i=1; i<=n; i++)s[i]=readstr(),a[i]=read(),insert(s[i],rt[bel[i]],i);
	for(register int i=1; i<=sn; i++)getfail(rt[i]);
	for(register int i=1; i<=tot; i++)addedge(fail[i],i);
	for(register int i=1; i<=sn; i++)dfs(rt[i]);
	for(register int i=1; i<=n; i++)add(l[bj[i]],a[i]),add(r[bj[i]]+1,-a[i]);//初始需要插入a_i
	while(m--) {
		op=read(),x=read(),y=read();
		switch(op) {
			case 1: {
				z=read(),add(x,y,z);
				break;
			}
			case 2: {
				z=read(),change(x,y,z);
				break;
			}
			case 3: {
				st=readstr(),write(query(x,y,st)),putchar('\n');
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Flying2018 (赞：10)

## 题意

给定 $n$ 个字符串 $s_i$，每个字符串有一个权值 $w_i$。

定义一个函数 $f(s,t)$ 表示 $t$ 在 $s$ 中的出现次数。

$q$ 次操作，支持将 $w_i$ 区间加/区间覆盖，询问一个字符串 $T$ 和 $l,r$，求 $\sum_{i=l}^{r}f(T,s_i)w_i$。

## 题解

作者并没有真正实现过这个算法，可能算法存在一定问题，如有问题请指出（轻喷）。

首先观察到区间推平并不是很好维护，考虑用一个珂朵莉树来处理。具体来说，每次将一段区间 $(l,r,v)$ 推平成为 $v'$ 可以转化成将 $[l,r]$ 加上 $v'-v$。可以证明这样转化后操作总数仍然是 $O(n)$ 的，因为任意一次操作最多使总转化操作增加三。

由于这里有区间加操作且没有保证数据随机，不能直接用 set，可能要手写一棵平衡树来支持区间加的操作。~~不过据说数据是随的~~。

这部分复杂度为 $O(n\log n)$。

接下来考虑建出 AC 自动机，记录每次询问每次匹配到的所有点（匹配点个数是 $|L_i|$ 的）。显然查询 $[l,r]$ 可以差分为查询 $[1,r]$ 的值减去 $[1,l-1]$。

如果我们给每个串的终止节点编一个号，那么一次询问等于询问一个点到根路径上编号 $\leq k_i$ 的点的权值和。当然串有可能相等，这个特殊处理一下即可。

这样题意转化为：给你一棵树，点有编号，支持将 $[l_i,r_i]$ 中的点 $+v_i$，查询一个点到根路径上所有编号 $\leq k_i$ 的权值和。

感觉不是很能 $n\text{ polylog } n$ 的样子，考虑 [APIO 桥梁](https://www.luogu.com.cn/problem/P5443) 的套路：将询问修改离线，每 $B$ 个分为一块。

考虑对于块内，暴力处理每个修改对询问的影响。可以用可持久化线段树统计出一个点到根路径上小于某个编号的点的个数，那么一次修改对一个询问的影响可以在 $O(\log n)$ 时间处理，复杂度 $O(nB\log n)$。

其实可以大力将所有操作离线，按 dfs 序处理所有查询，那么实际上有 $O(nB)$ 次查询操作但是只有 $O(n)$ 次修改操作，直接值域分块即可做到 $O(nB+n\sqrt n)$。

对于块间，我们记录一个差分数组，每过一个块就暴力从上往下更新一遍所有点的值，这部分复杂度 $O(\frac{n^2}{B})$。

取 $B=n$，可得复杂度为 $O(n\sqrt n)$。

后面瓶颈部分理论常数极小，且代码量不大。代码量主要在于第一部分。

---

## 作者：Reunite (赞：5)

没有营养的恶心题。

## 一
---

发现这个东西不是很好维护，注意到 $n,m$ 的范围较小，考虑根号算法。这里我使用的是序列分块。看到多模匹配，考虑 ACAM。

设块长为 $B$，我们对于每一个块内的所有串建出 ACAM，并建出 fail 树，结尾点上挂上权值。先考虑查询的情况：

- 整块查询。直接在每一个块的 ACAM 上跑文本串，一个块的答案即为 fail 树上匹配点到根的带权结尾点的和。这样不是很好算，可以反过来考虑每个结尾点对哪些点有贡献，显然是一个子树加，单点求和的形式，可以直接上树状数组维护。注意树状数组需要提前预处理好，这样才能保证一个整块查询的复杂度是 $O(|S|\log_2|s_i|)$。

- 散块查询。考虑此时段内最多只有 $B$ 个结尾点，可以撤销不在询问区间内的贡献，查询后再还原即可。这样复杂度是 $O(B\log_2|s_i|+|S|\log_2|s_i|)$。

## 二
---

现在引入区间加和区间覆盖操作，但也不是很难，我们分别考虑这两种操作会造成哪些影响。

- 区间加。若我们在维护上述信息的同时顺带维护一下匹配数量，那么散块直接暴力重构，整块打加法标记，询问时再加上匹配数与加法标记的乘积即可。

- 区间覆盖。类似地，散块暴力重构，整块打覆盖标记，并**清空加法标记**。询问时若发现有覆盖标记，则答案为匹配数乘上加法、覆盖的标记和。

重构复杂度是 $O(B\log_2|s_i|)$，打标记复杂度为 $O(\frac{n}{B})$。

## 三
---

具体实现方面，我们对于每一个块维护两个树状数组，以便进行子树加权值，子树加 $1$，以及一些单点查询操作。写的时候要注意常数因子以及标记与标记之间的**相互影响**。

总时间复杂度比较复杂，平衡复杂度后大概可以认为在 $O(n\sqrt {n\log_2n})$ 到 $O(n\sqrt n\log_2n)$ 之间（$n$ 仅代表一个大概的数据范围）。

代码不是很好写。$B$ 取 $[150,300]$ 可得较优秀时间效率。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define ll long long
using namespace std;

int n,m,tot,B=150,len;
char c[200005];
int bl[30005];
int lf[30005];
int rt[30005];
int it[30005];
int dfn[200005];
int sz[200005];
int fail[200005];
int son[200005][6];
int s[30005];
int ad[30005];
int tg[30005];
vector <int> g[200005];

struct BIT{
	int n;
	vector <int> t;
	inline void add(int x,int k){while(x<=n) t[x]+=k,x+=x&-x;return ;}
	inline int ask(int x){int s=0;while(x) s+=t[x],x^=x&-x;return s;}
};

struct node{
	int rt,tm;
	BIT t1,t2;

	inline int insert(){
		int u=rt,len=strlen(c+1);
		for(int i=1;i<=len;i++){
			if(!son[u][c[i]-'a']) son[u][c[i]-'a']=++tot;
			u=son[u][c[i]-'a'];
		}
		return u;
	}

	inline void init(int u){dfn[u]=++tm,sz[u]=1;for(int v:g[u]) init(v),sz[u]+=sz[v];}

	inline void rebuild(int l,int r,int k){
		for(int i=l;i<=r;i++)
			t1.add(dfn[it[i]],1*k),t1.add(dfn[it[i]]+sz[it[i]],-1*k),
			t2.add(dfn[it[i]],s[i]*k),t2.add(dfn[it[i]]+sz[it[i]],-s[i]*k);
		return ;
	}

	inline void build(int l,int r){
		queue <int> q;
		for(int i=0;i<3;i++)
			if(son[rt][i]) fail[son[rt][i]]=rt,q.push(son[rt][i]);
			else son[rt][i]=rt;
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<3;i++){
				int v=son[u][i];
				if(!v) son[u][i]=son[fail[u]][i];
				else fail[v]=son[fail[u]][i],q.push(v);
			}
		}
		for(int i=rt+1;i<=tot;i++) g[fail[i]].emplace_back(i);
		init(rt);
		t1.t.resize(tm+1);
		t2.t.resize(tm+1);
		t1.n=t2.n=tm;
		rebuild(l,r,1);
		return ;
	}

}a[2005];

inline void addforsmall(int l,int r,int id,int x){
	a[id].rebuild(lf[id],rt[id],-1);
	if(tg[id]) for(int i=lf[id];i<=rt[id];i++) s[i]=tg[id];
	if(ad[id]) for(int i=lf[id];i<=rt[id];i++) s[i]+=ad[id];
	tg[id]=ad[id]=0;
	for(int i=l;i<=r;i++) s[i]+=x;
	a[id].rebuild(lf[id],rt[id],1);
	return ;
}

inline void coverforsmall(int l,int r,int id,int x){
	a[id].rebuild(lf[id],rt[id],-1);
	if(tg[id]) for(int i=lf[id];i<=rt[id];i++) s[i]=tg[id];
	if(ad[id]) for(int i=lf[id];i<=rt[id];i++) s[i]+=ad[id];
	tg[id]=ad[id]=0;
	for(int i=l;i<=r;i++) s[i]=x;
	a[id].rebuild(lf[id],rt[id],1);
	return ;
}

inline ll askforsmall(int l,int r,int id){
	ll sum=0;
	a[id].rebuild(lf[id],rt[id],-1);
	if(tg[id]) for(int i=lf[id];i<=rt[id];i++) s[i]=tg[id];
	if(ad[id]) for(int i=lf[id];i<=rt[id];i++) s[i]+=ad[id];
	tg[id]=ad[id]=0;
	a[id].rebuild(l,r,1);
	int u=a[id].rt;
	for(int i=1;i<=len;i++){
		u=son[u][c[i]-'a'];
		sum+=a[id].t2.ask(dfn[u]);
	}
	a[id].rebuild(lf[id],l-1,1);
	a[id].rebuild(r+1,rt[id],1);
	return sum;
}

inline ll askforbig(int l,int r,int id){
	int cnt=0,u=a[id].rt;
	ll sum=0;
	for(int i=1;i<=len;i++){
		u=son[u][c[i]-'a'];
		sum+=a[id].t2.ask(dfn[u]);
		cnt+=a[id].t1.ask(dfn[u]);
	}
	if(tg[id]) sum=1ll*cnt*tg[id];
	if(ad[id]) sum+=1ll*cnt*ad[id];

	return sum;
}

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	// freopen("qwq.in","r",stdin);
	// freopen("qwq.out","w",stdout);
	in(n),in(m);
	for(int i=1;i<=n;i++) bl[i]=(i+B-1)/B;
	for(int i=1;i<=n;i++) rt[bl[i]]=i;
	for(int i=n;i>=1;i--) lf[bl[i]]=i;
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		in(s[i]);
		if(lf[bl[i]]==i) a[bl[i]].rt=++tot;
		it[i]=a[bl[i]].insert();
		if(rt[bl[i]]==i) a[bl[i]].build(lf[bl[i]],rt[bl[i]]);
	}
	while(m--){
		int op;
		in(op);
		if(op==1){
			int l,r,x;
			in(l),in(r),in(x);
			if(bl[l]==bl[r]){addforsmall(l,r,bl[l],x);continue;}
			addforsmall(l,rt[bl[l]],bl[l],x);
			addforsmall(lf[bl[r]],r,bl[r],x);
			for(int i=bl[l]+1;i<=bl[r]-1;i++) ad[i]+=x;
			continue;
		}
		if(op==2){
			int l,r,x;
			in(l),in(r),in(x);
			if(bl[l]==bl[r]){coverforsmall(l,r,bl[l],x);continue;}
			coverforsmall(l,rt[bl[l]],bl[l],x);
			coverforsmall(lf[bl[r]],r,bl[r],x);
			for(int i=bl[l]+1;i<=bl[r]-1;i++) ad[i]=0,tg[i]=x;
			continue;
		}
		if(op==3){
			int l,r;
			in(l),in(r);
			scanf("%s",c+1);
			len=strlen(c+1);
			if(bl[l]==bl[r]){printf("%lld\n",askforsmall(l,r,bl[l]));continue;}
			ll sum=askforsmall(l,rt[bl[l]],bl[l])+askforsmall(lf[bl[r]],r,bl[r]);
			for(int i=bl[l]+1;i<=bl[r]-1;i++) sum+=askforbig(lf[i],rt[i],i);
			printf("%lld\n",sum);
		}
	}

	return 0;
}

```

---

## 作者：OldDriverTree (赞：4)

比较套路的题，自己想了一会儿就想出来了。

# Solution
首先这个东西如果用线段树维护显然是不太能合并的。

所以考虑分块，对于每块分别建一个 $\text{AC}$ 自动机，对于修改 $a_i$，我们就在这个块内的 $fail$ 树上进行子树修改，对于在一个查询，我们就把这个串在 $\text{AC}$ 自动机上走一下，并对经过的点进行单点查询，这个东西显然可以用 $\text{BIT}$ 维护。对于区间修改或区间查询，整块随便打个 $\text{tag}$，询问随便处理一下就行了，散块的修改或查询先把 $\text{tag}$ 下放，块内重构一下就行了。

时间复杂度 $O(len\sqrt n\log len)$。
# Code
```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
const int N=30001,M=175,S=2e5+M;
struct node { int son[3],fail,cnt; }T[S];
int n,m,tot,a[N],pos[N],BIT[S],L[S],R[S];
int bel[N],fir[M],lst[M],add[M],cov[M];
vector<int> g[S];

void insert(string s,int rt,int id)
{
	for (char c:s) {
		int &p=T[rt].son[c-'a'];
		if (!p) p=++tot; rt=p;
	}
	T[rt].cnt++,pos[id]=rt;
}
void build(int rt)
{
	queue<int> q; for (int i=0;i<3;i++)
	if (T[rt].son[i]) T[T[rt].son[i] ].fail=rt,
	q.push(T[rt].son[i]); else T[rt].son[i]=rt;
	while (!q.empty() ) {
		int u=q.front(); q.pop(); for (int i=0;i<3;i++)
		if (T[u].son[i]) T[T[u].son[i] ].fail=T[T[u].fail].son[i],
		q.push(T[u].son[i]); else T[u].son[i]=T[T[u].fail].son[i];
		T[u].cnt+=T[T[u].fail].cnt,g[T[u].fail].push_back(u);
	}
}
void dfs(int u) { L[u]=++tot; for (int v:g[u]) dfs(v); R[u]=tot; }
int query(int x,int res=0) { while (x) res+=BIT[x],x&=x-1; return res; }
void update(int x,int y) { while (x<=tot) BIT[x]+=y,x+=x&-x; }

void rebuild(int id)
{
	for (int i=fir[id];i<=lst[id];i++) {
		update(L[pos[i] ],-a[i]),update(R[pos[i] ]+1,a[i]);
		if (cov[id]) a[i]=cov[id]; a[i]+=add[id];
		update(L[pos[i] ],a[i]),update(R[pos[i] ]+1,-a[i]);
	}
	cov[id]=add[id]=0;
}
void change(int l,int r,int x)
{
	if (bel[l]==bel[r]) {
		rebuild(bel[l]); for (int i=l;i<=r;i++)
		a[i]+=x,update(L[pos[i] ],x),update(R[pos[i] ]+1,-x);
		return;
	}
	rebuild(bel[l]),rebuild(bel[r]);
	for (int i=l;i<=lst[bel[l] ];i++)
	update(L[pos[i] ],x),update(R[pos[i] ]+1,-x),a[i]+=x;
	for (int i=fir[bel[r] ];i<=r;i++)
	update(L[pos[i] ],x),update(R[pos[i] ]+1,-x),a[i]+=x;
	for (int i=bel[l]+1;i<bel[r];i++) add[i]+=x;
}
void modify(int l,int r,int x)
{
	if (bel[l]==bel[r]) {
		rebuild(bel[l]); for (int i=l;i<=r;i++)
		update(L[pos[i] ],x-a[i]),update(R[pos[i] ]+1,a[i]-x),a[i]=x;
		return;
	}
	rebuild(bel[l]),rebuild(bel[r]);
	for (int i=l;i<=lst[bel[l] ];i++)
	update(L[pos[i] ],x-a[i]),update(R[pos[i] ]+1,a[i]-x),a[i]=x;
	for (int i=fir[bel[r] ];i<=r;i++)
	update(L[pos[i] ],x-a[i]),update(R[pos[i] ]+1,a[i]-x),a[i]=x;
	for (int i=bel[l]+1;i<bel[r];i++) add[i]=0,cov[i]=x;
}
int query(int id,string s)
{
	int rt=id,sum=0,cnt=0;
	for (char c:s) {
		rt=T[rt].son[c-'a'];
		if (!cov[id]) sum+=query(L[rt]);
		cnt+=T[rt].cnt;
	}
	if (cov[id]) return (cov[id]+add[id])*cnt;
	else return sum+add[id]*cnt;
}
int Query(int l,int r,string s)
{
	rebuild(bel[l]),rebuild(bel[r]);
	for (int i=fir[bel[l] ];i<l;i++) update(L[pos[i] ],-a[i]),update(R[pos[i] ]+1,a[i]);
	for (int i=r+1;i<=lst[bel[r] ];i++) update(L[pos[i] ],-a[i]),update(R[pos[i] ]+1,a[i]);
	int ans=0; for (int i=bel[l];i<=bel[r];i++) ans+=query(i,s);
	for (int i=fir[bel[l] ];i<l;i++) update(L[pos[i] ],a[i]),update(R[pos[i] ]+1,-a[i]);
	for (int i=r+1;i<=lst[bel[r] ];i++) update(L[pos[i] ],a[i]),update(R[pos[i] ]+1,-a[i]);
	return ans;
}
main()
{
	cin.tie(0),cout.tie(0),cin>>n>>m;
	int block=sqrt(n); tot=(n-1)/block+1;
	for (int i=1;i<=n;i++) {
		string s; cin>>s>>a[i];
		insert(s,bel[i]=(i-1)/block+1,i);
		if (!fir[bel[i] ]) fir[bel[i] ]=i;
		lst[bel[i] ]=i;
	}
	tot=0; for (int i=1;i<=bel[n];i++) build(i),dfs(i);
	for (int i=1;i<=n;i++) update(L[pos[i] ],a[i]),update(R[pos[i] ]+1,-a[i]);
	while (m--) {
		int o,l,r,x; cin>>o>>l>>r;
		if (o==1) cin>>x,change(l,r,x);
		else if (o==2) cin>>x,modify(l,r,x);
		else { string s; cin>>s,cout<<Query(l,r,s)<<endl; }
	}
	return 0;
}
```

---

## 作者：Hoks (赞：4)

## 前言
思路不是很难的一道 ACAM 题，但是实现方面有点困难，注意细节。

不知道为什么我写了 $4.6$ KB。

广告：[串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
首先看到题意查询 $s_{l\sim r}$ 在 $S$ 中的出现次数，首先想到了 [CF587F](https://www.luogu.com.cn/problem/CF587F)。

尝试类似的根号分治方法？

接着被这题的字符串带权值且带修改创飞了。

接着发现这题比较特殊的一点，字符集只有 $a,b,c$ 且 $n$ 范围较小，甚至还给了 $2s$。

考虑下最基础的 ACAM 是怎么统计出现次数的：

- 把模式串插入 ACAM 里，构建 Fail 树后对着每个模式串末尾节点子树加。

- 接着对于查询串扔到 ACAM 上跑，加上每个点的权值。

这个方法考虑树状数组维护即可。

不难发现这个方法在字符串带权值的时候还是适用的，把子树加的值从 $1$ 改为其权值即可。

接着考虑怎么给这个玩意带修改。

子树加的东西，要是修改就只能单个改，做不了一点。

所以考虑万能的分块（结合上面较小的数据范围也可以推出来复杂度里大概会带个根号了）。

我们考虑对 $n$ 个字符串分块为 $\sqrt{n}$ 个长度为 $\sqrt{n}$ 的字符串，对于每块字符串建一个 ACAM。

那么一次修改/覆盖操作就被我们拆分为了如何处理整块和散块。

基础分块方法，对于散块直接在树状数组上每个点子树修改，整块打标记即可。

接着考虑怎么查询：

- 对于散块，直接大力上 KMP 查询。

- 对于整块，直接把字符串扔到整块的 ACAM 上跑然后一路加单点权值。

~~貌似也不是 too hard？~~

然后我就把 $tag$ 和 $lz$ 数组写反挂到 $49$ 了。

**P.S.：散块跑 KMP 前先判断长度，不然复杂度会寄。**
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,M=3e4+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,block,a[M],len[M],nxt[N];
int tag[M],lz[M],bl[M],l[M],r[M],rt[M];
int ed[N],dfn[N],si[N];
char t[N],ss[N];string s[M];vector<int>e[N];
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    inline void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    inline int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    inline void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
}tt;
struct ACAM
{
	struct node{int nxt,ed,v[3];}t[N];int tot=0,cnt=0;
	inline void insert(char s[],int n,int u,int id)
	{
		for(int i=1;i<=n;i++){if(!t[u].v[s[i]-'a']) t[u].v[s[i]-'a']=++tot;u=t[u].v[s[i]-'a'];}
		ed[id]=u;t[u].ed++;
	}
	inline void build(int x)
	{
		queue<int>q;for(int i=0;i<3;i++) t[0].v[i]=x;q.push(x);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			e[t[u].nxt].emplace_back(u);t[u].ed+=t[t[u].nxt].ed;
			for(int i=0;i<3;i++)
				if(t[u].v[i]) t[t[u].v[i]].nxt=t[t[u].nxt].v[i],q.push(t[u].v[i]);
				else t[u].v[i]=t[t[u].nxt].v[i];
		}
	}
	inline void dfs(int u){dfn[u]=++cnt;si[u]=1;for(auto v:e[u]) dfs(v),si[u]+=si[v];}
}ac;
namespace fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void print(int x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) print(x/10);
		putchar(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='c'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}using namespace fast_IO;
inline void mdf(int i,int w){a[i]+=w;tt.mdf(dfn[ed[i]],dfn[ed[i]]+si[ed[i]]-1,w);}
inline void cov(int i,int w){tt.mdf(dfn[ed[i]],dfn[ed[i]]+si[ed[i]]-1,w-a[i]);a[i]=w;}
inline void pushdown(int x,int y){for(int i=l[y];i<=r[y];i++) cov(i,tag[x]?lz[x]:a[i]+lz[x]);lz[x]=tag[x]=0;}
inline void modify(int x,int y,int w)
{
	int L=bl[x],R=bl[y];
	if(!(L^R))
	{
		if(tag[L]) pushdown(L,x);
		for(int i=x;i<=y;i++) mdf(i,w);
		return ;
	}
	if(tag[L]) pushdown(L,x);for(int i=x;i<=r[x];i++) mdf(i,w);
	if(tag[R]) pushdown(R,y);for(int i=l[y];i<=y;i++) mdf(i,w);
	for(int i=L+1;i<R;i++) lz[i]+=w;
}
inline void cover(int x,int y,int w)
{
	int L=bl[x],R=bl[y];
	if(!(L^R))
	{
		if(lz[L]) pushdown(L,x);
		for(int i=x;i<=y;i++) cov(i,w);
		return ;
	}
	if(lz[L]) pushdown(L,x);for(int i=x;i<=r[x];i++) cov(i,w);
	if(lz[R]) pushdown(R,y);for(int i=l[y];i<=y;i++) cov(i,w);
	for(int i=L+1;i<R;i++) lz[i]=w,tag[i]=1;
}
namespace KMP
{
	inline void kmp(char s[],int n,int nxt[])
	{
		for(int i=2,j=0;i<=n;i++)
		{
			while(j&&s[i]!=s[j+1]) j=nxt[j];
			if(s[i]==s[j+1]) j++;
			nxt[i]=j;
		}
	}
	inline int findstr(int n,int m,char s1[],char s2[],int nxt[])
	{
		int j=0,res=0;kmp(s2,m,nxt);
		for(int i=1;i<=n;i++)
		{
			while(j!=0&&s2[j+1]!=s1[i]||j==m) j=nxt[j];
			if(s2[j+1]==s1[i]) j++;res+=j==m;
		}
		return res;
	}
}
using namespace KMP;
inline void zh(int x){for(int i=1;i<=len[x];i++) t[i]=s[x][i];}
inline int query(int x,int y,char ss[],int n)
{
	int L=bl[x],R=bl[y],res=0;
	if(!(L^R))
	{
		for(int i=x;i<=y;i++) if(len[i]<=n) zh(i),res+=findstr(n,len[i],ss,t,nxt)*(tag[L]?lz[L]:a[i]+lz[L]);
		return res;
	}
	for(int i=x;i<=r[x];i++)if(len[i]<=n) zh(i),res+=findstr(n,len[i],ss,t,nxt)*(tag[L]?lz[L]:a[i]+lz[L]);
	for(int i=l[y];i<=y;i++)if(len[i]<=n) zh(i),res+=findstr(n,len[i],ss,t,nxt)*(tag[R]?lz[R]:a[i]+lz[R]);
	for(int i=L+1,u=rt[i];i<R;i++,u=rt[i])
		for(int j=1;j<=n;j++)
			u=ac.t[u].v[ss[j]-'a'],res+=lz[i]*ac.t[u].ed+(!tag[i])*tt.query(dfn[u]);
	return res;
}
inline void get(int i){s[i]=" ";for(int j=1;j<=len[i];j++) s[i]+=t[j];}
signed main()
{
	n=read(),m=read();block=sqrt(n);
	for(int i=1;i<=n;i++) bl[i]=(i-1)/block+1,l[i]=(bl[i]-1)*block+1,r[i]=min(bl[i]*block,n);
	for(int i=1;i<=bl[n];i++) rt[i]=++ac.tot;
	for(int i=1;i<=n;i++) rd(t,len[i]),get(i),a[i]=read(),ac.insert(t,len[i],rt[bl[i]],i);
	for(int i=1;i<=bl[n];i++) ac.build(rt[i]),ac.dfs(rt[i]);tt.n=N;
	for(int i=1;i<=n;i++) tt.mdf(dfn[ed[i]],dfn[ed[i]]+si[ed[i]]-1,a[i]);
	for(int i=1,op,x,y,w;i<=m;i++)
	{
		op=read(),x=read(),y=read();
		if(op==1) modify(x,y,read());
		else if(op==2) cover(x,y,read());
		else w=0,rd(ss,w),print(query(x,y,ss,w)),puts("");
	}
	return 0;
}
```

---

## 作者：yinianxingkong (赞：2)

单看询问就是一个 ACAM 题，但 ACAM 大小和长度有关，不适合合并，这里考虑分块。

显然散块询问可以跑 KMP，整块可以建 ACAM 暴力求祖先链的值，难点就在重构上了。

首先你发现这是一个单点修改祖先链查值，DFS 序树状数组就可以 $O(n\sqrt{n}\log n)$。

进一步，我们只关心关键点，建虚树以后直接暴力重构就是 $O(n\sqrt{n})$ 的。

值得一提的是，本题的虚树只需要统计祖先链信息，所以所谓虚树只需要记一个祖先链最近关键点和拓扑序即可。

代码实现时注意可能会有多个本质相同的子串。不难写，效率还蛮高的，最优解第一页。有需求私信。

---

## 作者：FZzzz (赞：2)

没啥含金量的题，但是为啥题解区没有正常做法。

以下假定 $n$ 与 $m$ 同阶，$L=\sum|s|$ 与 $\sum|S|$ 同阶。

建出 AC 自动机，快进到转化为以下问题：
> 给定一个长为 $n$ 的序列 $a$，一棵 $O(L)$ 个节点的树，一个长为 $n$ 的节点序列 $c$，支持 $O(n+L)$ 次以下三种操作：
> - 对 $a$ 区间加。
> - 对 $a$ 区间赋值。
> - 给定区间 $[l,r]$ 和节点 $u$，记 $P(u,v)$ 为 $u$ 是 $v$ 的祖先，求 $\sum\limits_{l\le i\le r,P(c_i,u)}a_i$。

考虑对序列分块，记块长为 $B$。以下我们考虑一个块，我们想要以 $O(1)$ 的时间处理每个覆盖这个块的操作，以 $O(B)$ 的时间处理每个与这个块相交但不覆盖这个块的操作。

称使得块内存在某个 $c_i=u$ 的节点 $u$ 为关键点，那么只有 $O(B)$ 个关键点。对于一个询问的节点，我们只关心它的祖先中离它最近的关键点。

对于覆盖这个块的修改，我们想要直接打上整体赋值和整体加的标记。考虑这个标记对某次对节点 $u$ 的询问的影响，这只取决于有多少个 $i$ 使得 $c_i$ 是 $u$ 的祖先。

于是，我们在最开始以 $O(L)$ 时间对每个节点预处理出它的祖先中离它最近的关键点。再以 $O(B)$ 的时间对每个关键点 $u$ 预处理出，有多少个 $i$ 使得 $c_i$ 是 $u$ 的祖先，以及一次对整个块以及 $u$ 的询问的答案。

对于覆盖整个块的修改，直接打标记，否则以 $O(B)$ 的时间重新计算每个 $a_i$ 和上述信息。对于覆盖整个块的询问，可以直接 $O(1)$ 计算这个块的贡献，否则也可以以 $O(B)$ 的时间计算贡献。具体实现细节不赘述

取 $B=O(\sqrt n)$，可以得到 $O(L|\Sigma|+(n+L)\sqrt n)$ 的时间复杂度。但是由于我们要对每个块存储每个点上面最近的关键点，空间是根号的，而这题只开了 64M。我没有想到什么好办法，但是至少可以离线逐块处理，空间复杂度 $O(n+L|\Sigma|)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-') f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=3e4+5,maxl=2e5+5;
int n,m,c[maxn],a[maxn];
char s[maxl];
int opt[maxn],l[maxn],r[maxn];
vector<int> k[maxn];
int sz=1,nxt[maxl][3],fa[maxl];
vector<int> g[maxl];
int insert(char* s){
	int l=strlen(s+1),u=1;
	for(int i=1;i<=l;i++){
		int c=s[i]-'a';
		if(!nxt[u][c]) nxt[u][c]=++sz;
		u=nxt[u][c];
	}
	return u;
}
void build(){
	queue<int> q;
	for(int i=0;i<3;i++) if(nxt[1][i]){
		fa[nxt[1][i]]=1;
		q.push(nxt[1][i]);
	}
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=0;i<3;i++)
			if(nxt[u][i]){
				fa[nxt[u][i]]=nxt[fa[u]][i];
				q.push(nxt[u][i]);
			}
			else nxt[u][i]=nxt[fa[u]][i];
	}
	for(int i=2;i<=sz;i++) g[fa[i]].push_back(i);
}
int S,B,L,R,ass,add,pre[maxl];
vector<int> vec;
ll sum[maxl];
int d[maxl];
void dfs(int u){
	if(pre[u]){
		sum[u]+=sum[pre[fa[u]]];
		d[u]+=d[pre[fa[u]]];
		vec.push_back(u);
	}
	else pre[u]=pre[fa[u]];
	for(int v:g[u]) dfs(v);
}
void modify(int l,int r,bool tp,int k){
	if(ass>=0) for(int i=L;i<=R;i++) a[i]=ass;
	for(int i=L;i<=R;i++) a[i]+=add;
	ass=-1;
	add=0;
	for(int i=l;i<=r;i++) a[i]=tp?k:a[i]+k;
	for(int u:vec) sum[u]=0;
	for(int i=L;i<=R;i++) sum[c[i]]+=a[i];
	for(int u:vec) sum[u]+=sum[pre[fa[u]]];
}
ll s2[maxl];
ll query(int l,int r,int u){
	for(int u:vec) s2[u]=0;
	for(int i=l;i<=r;i++)
		s2[c[i]]+=(ass>=0?ass:a[i])+add;
	ll s=0;
	while(u){
		s+=s2[u];
		u=pre[fa[u]];
	}
	return s;
}
ll ans[maxn];
int main(){
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		c[i]=insert(s);
		a[i]=read();
	}
	build();
	for(int i=1;i<=m;i++){
		opt[i]=read();
		l[i]=read();
		r[i]=read();
		if(opt[i]!=3) k[i].push_back(read());
		else{
			scanf("%s",s+1);
			int l=strlen(s+1),u=1;
			for(int j=1;j<=l;j++)
				k[i].push_back(u=nxt[u][s[j]-'a']);
		}
	}
	S=sqrt(n);
	B=(n-1)/S+1;
	for(int T=1;T<=B;T++){
		L=S*(T-1)+1;
		R=min(S*T,n);
		ass=-1;
		add=0;
		memset(pre,0,sizeof(pre));
		vec.clear();
		memset(sum,0,sizeof(sum));
		memset(d,0,sizeof(d));
		for(int i=L;i<=R;i++){
			pre[c[i]]=c[i];
			sum[c[i]]+=a[i];
			d[c[i]]++;
		}
		dfs(1);
		for(int i=1;i<=m;i++)
			if(opt[i]!=3){
				if(l[i]>R||r[i]<L) continue;
				if(l[i]<=L&&r[i]>=R){
					if(opt[i]==1) add+=k[i][0];
					else{
						ass=k[i][0];
						add=0;
					}
				}
				else modify(max(l[i],L),min(r[i],R),opt[i]==2,k[i][0]);
			}
			else{
				if(l[i]>R||r[i]<L) continue;
				if(l[i]<=L&&r[i]>=R) for(int u:k[i]){
					int x=pre[u];
					ans[i]+=(ass>=0?1ll*ass*d[x]:sum[x])+1ll*add*d[x];
				}
				else for(int u:k[i])
					ans[i]+=query(max(l[i],L),min(r[i],R),pre[u]);
			}
	}
	for(int i=1;i<=m;i++) if(opt[i]==3) printf("%lld\n",ans[i]);
#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
#endif
	return 0;
}
```
翻了一下提交记录，好像还是有老哥写比较阳间的不带 log 做法的。

---

## 作者：Prean (赞：2)

吊 打 标 算

千万不要像我这样第一次分块修改完之后忘记做前缀和调了一个晚自习~~他说风雨中这点痛算什么，擦干泪不要怕，至少我们还有梦~~（

首先弄明白一件事：区间 ACAM 可以看做是所有串的 ACAM 只保留区间串对节点贡献的信息，仍然可以使用所有串的 ACAM 的转移边。

于是我们可以使用 ACAM 套线段树，每颗线段树维护这个节点会受到区间哪些位置的串的贡献。

但是这这样有一个问题，修改操作不太容易实现。

那么我们还需要再套一层数据结构来解决这个修改。区间询问一般考虑线段树和分块。线段树的话修改操作会涉及过多的节点，所以我们选择分块。

设块长为 $B$。对每个块的 ACAM 维护两种类型的值：$V[u]$ 表示不计算整体加 $tag$ 的权值之和，$c[u]$ 表示这个节点包含的串的个数。

对于整块，区间加操作就直接加，如果是赋值那就清空 $V$ 然后令 $tag$ 等于赋的值。

我们是很容易通过这两个数组来计算一个节点的权值的。对于整块我们可以这样做到 $O(\sum|S|\frac{n}{B})$ 个询问操作。

散块的修改操作需要暴力进行，涉及到的 ACAM 节点个数是 $O(\sum|s|)$ 级别的。不过可以知道需要修改的 ACAM 节点是 $O(B)$ 个。所以修改操作是 $O(mB)$ 个。

但是询问就比较麻烦了。前面提到可以将区间 ACAM 看做是所有串的 ACAM 只保留区间串对节点贡献的信息，所以对于每个块的 ACAM 都套上一颗线段树，维护哪些串贡献这个节点。

但是查询的时候只能暴力把这个集合弄出来一个一个加。不过由于加的是字符串的信息所以是 $O(1)$ 维护的。

查询散块的复杂度为 $O(\sum|S|B)$。

注意到前面的询问次数过多，线段树这种东西是不能胜任的，考虑对 dfn 序分块。

每次修改相当于子树加，也就是区间加。我们将 fail 树的 dfn 序分成块长为 $T$ 的块。每次修改暴力加后缀，然后 $O(B)$ 次操作结束后进行一个块的前缀和。

那么就是 $O(\sum|S|\frac{n}{B}+mBT+\frac{\sum|S|m}{T})$，$T$ 取 $\sqrt{\frac{\sum|S|}{B}}$ 可以得到 $O(\sum|S|\frac{n}{B}+m\sqrt{\frac{\sum|S|}{B}})$ 的复杂度。

$B$ 取 $\sqrt{n}$ 即可得到 $O(\sum|S|\sqrt{n}+\frac{m}{\sqrt[4]{n}}\sqrt{\sum|S|})$ 的复杂度。

线段树合并的话，序列长度其实只有 $\lfloor\sqrt{30000}\rfloor=173$，这玩意儿还不如去用 bitset。空间几乎是线性的，不会被卡。

补充：bitset 部分的时间和空间都是 $O(\sum|S|\frac{\sqrt{n}}{w})$。
```cpp
#include<cstring>
#include<cstdio>
#include<bitset>
#include<cmath>
typedef long long ll;
const int M=2e5+5;
int n,m,B,P,tot,a[M];char S[M],T[M],*s[M],*t[M];int lens[M],lent[M];
int sums,sumt;int L[M],R[M],pos[M];int opt[M],l[M],r[M],k[M];
namespace Solve{
	int dfc,V[M],c[M],l[M],r[M],pos[M],fail[M],trans[M][3];std::bitset<180>bit[M];
	int _s[M<<1],_tim[M<<1],_S[M<<1];int _pos[M<<1],_L[M<<1],_R[M<<1];
	int*ns=_s,*ntim=_tim,*nS=_S,*npos=_pos,*nL=_L,*nR=_R;
	int cnt,h[M];
	struct Edge{
		int v,nx;
	}e[M];
	inline void Add(const int&u,const int&v){
		e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
	}
	inline int Insert(int u,char*s,const int&v,const int&n){
		for(int i=0;i<n;++i){
			const int&c=s[i]-97;
			if(!trans[u][c])trans[u][c]=++tot;u=trans[u][c];
		}
		V[u]+=v;++c[u];return u;
	}
	struct Block{
		int m,rt,tag,T,a[190],tim[190],end[190];
		struct BLOCK{
			int n,B,T,*s,*tim,*S;int*pos,*L,*R;bool typ;
			inline void init(const int&N){
				s=ns;tim=ntim;S=nS;pos=npos;L=nL;R=nR;n=N;
				ns+=n+5;ntim+=n+5;nS+=n+5;npos+=n+5;nL+=n+5;nR+=n+5;
				for(int i=1;i<=n;++i){
					pos[i]=(i-1)/B+1;
					L[i]=(pos[i]-1)*B+1;R[i]=pos[i]*B;if(R[i]>n)R[i]=n;
				}
			}
			inline void Add(int x,const int&V){
				for(int i=x;i<=R[x];++i){
					if(tim[i]^T)tim[i]=T,s[i]=0;s[i]+=V;
				}
			}
			inline void update(){
				for(int i=1;i<=pos[n];++i){
					if(tim[R[(i-1)*B+1]]^T)tim[R[(i-1)*B+1]]=T,s[R[(i-1)*B+1]]=0;S[i]=S[i-1]+s[R[(i-1)*B+1]];
				}
				typ=false;
			}
			inline int Qry(const int&x){
				if(tim[x]^T)tim[x]=T,s[x]=0;return typ?0:S[pos[x]-1]+s[x];
			}
			inline void Clear(){
				++T;
			}
		}block;
		inline void Build(const int&L,const int&R){
			for(int i=L;i<=R;++i)a[i-L+1]=::a[i],bit[end[i-L+1]=Insert(rt,::s[i],a[i-L+1],lens[i])][i-L+1]=1;
		}
		inline void init(const int&n){
			block.B=ceil(sqrt(sumt/B));block.init(m);
			for(int i=1;i<=n;++i)block.Add(l[end[i]],a[i]),block.Add(r[end[i]]+1,-a[i]);block.update();
		}
		inline void Add(const int&V){
			tag+=V;
		}
		inline void Cover(const int&V){
			block.Clear();++T;tag=V;block.typ=true;
		}
		inline void Add(const int&V,const int&L,const int&R){
			for(int i=L;i<=R;++i){
				if(tim[i]^T)tim[i]=T,a[i]=0;
				block.Add(l[end[i]],V);block.Add(r[end[i]]+1,-V);a[i]+=V;
			}
			block.update();
		}
		inline void Cover(const int&V,const int&L,const int&R){
			for(int i=L;i<=R;++i){
				if(tim[i]^T)tim[i]=T,a[i]=0;
				block.Add(l[end[i]],V-a[i]-tag);block.Add(r[end[i]]+1,-(V-a[i]-tag));a[i]=V-tag;
			}
			block.update();
		}
		inline ll Qry(char*s,const int&n){
			int u(rt);ll ans(0);
			for(int i=0;i<n;++i){
				u=trans[u][s[i]-97];
				ans+=block.Qry(l[u])+1ll*tag*c[u];
			}
			return ans;
		}
		inline ll Qry(char*s,const int&n,const int&L,const int&R){
			int u(rt);ll ans(0);
			for(int i=0;i<n;++i){
				u=trans[u][s[i]-97];
				for(int i=bit[u]._Find_next(L-1);i<=R;i=bit[u]._Find_next(i)){
					if(tim[i]^T)tim[i]=T,a[i]=0;ans+=a[i]+tag;
				}
			}
			return ans;
		}
	}block[190];
	inline void DFS(const int&u){
		if(fail[u]){
			V[u]+=V[fail[u]];c[u]+=c[fail[u]];bit[u]|=bit[fail[u]];
			pos[u]=pos[fail[u]];
		}
		l[u]=++dfc;++block[pos[u]].m;for(int E=h[u];E;E=e[E].nx)DFS(e[E].v);r[u]=dfc;
	}
	inline void Build(){
		static int L,R,q[M];L=1;
		for(int u=1;u<=P;++u){
			for(int c=0;c<3;++c){
				if(trans[u][c])q[++R]=trans[u][c],fail[trans[u][c]]=u;
				else trans[u][c]=u;
			}
		}
		while(L<=R){
			const int&u=q[L++];
			for(int c=0;c<3;++c){
				if(trans[u][c])q[++R]=trans[u][c],fail[trans[u][c]]=trans[fail[u]][c];
				else trans[u][c]=trans[fail[u]][c];
			}
		}
		for(int u=1;u<=tot;++u)Add(fail[u],u);
		for(int u=1;u<=P;++u)DFS(u),dfc=0;
	}
}
signed main(){
	scanf("%d%d",&n,&m);s[0]=S;t[0]=T;B=sqrt(n);P=(n+B-1)/B;
	for(int i=1;i<=n;++i){
		scanf("%s%d",s[i]=s[i-1]+lens[i-1],a+i);lens[i]=strlen(s[i]);sums+=lens[i];
	}
	for(int i=1;i<=m;++i){
		scanf("%d%d%d",opt+i,l+i,r+i);t[i]=t[i-1]+lent[i-1];
		if(opt[i]==3)scanf("%s",t[i]),lent[i]=strlen(t[i]);else scanf("%d",k+i);sumt+=lent[i];
	}
	for(int i=1;i<=n;++i){
		pos[i]=(i-1)/B+1;L[i]=(pos[i]-1)*B+1;R[i]=pos[i]*B;if(R[i]>n)R[i]=n;
	}
	for(int i=1;i<=P;++i)Solve::block[i].rt=++tot,Solve::pos[i]=i;
	for(int i=1;i<=P;++i)Solve::block[i].Build(L[(i-1)*B+1],R[(i-1)*B+1]);Solve::Build();
	for(int i=1;i<=P;++i)Solve::block[i].init(R[(i-1)*B+1]-L[(i-1)*B+1]+1);
	for(int i=1;i<=m;++i){
		const int&l=::l[i],&r=::r[i],&k=::k[i];
		if(opt[i]==1){
			const int&q=pos[l],&p=pos[r];
			if(q==p)Solve::block[q].Add(k,l-L[l]+1,r-L[r]+1);
			else{
				Solve::block[q].Add(k,l-L[l]+1,R[l]-L[l]+1);Solve::block[p].Add(k,1,r-L[r]+1);
				for(int i=q+1;i<=p-1;++i)Solve::block[i].Add(k);
			}
		}
		if(opt[i]==2){
			const int&q=pos[l],&p=pos[r];
			if(q==p)Solve::block[q].Cover(k,l-L[l]+1,r-L[r]+1);
			else{
				Solve::block[q].Cover(k,l-L[l]+1,R[l]-L[l]+1);Solve::block[p].Cover(k,1,r-L[r]+1);
				for(int i=q+1;i<=p-1;++i)Solve::block[i].Cover(k);
			}
		}
		if(opt[i]==3){
			const int&q=pos[l],&p=pos[r];
			const int&len=lent[i];char*t=::t[i];
			if(q==p)printf("%lld\n",Solve::block[q].Qry(t,len,l-L[l]+1,r-L[l]+1));
			else{
				ll ans=Solve::block[q].Qry(t,len,l-L[l]+1,R[l]-L[l]+1)+Solve::block[p].Qry(t,len,1,r-L[r]+1);
				for(int i=q+1;i<=p-1;++i)ans+=Solve::block[i].Qry(t,len);
				printf("%lld\n",ans);
			}
		}
	}
}
```

---

## 作者：devout (赞：1)

理论上复杂度更优的做法，但是我人傻常数大，死活卡过不去。。。

这种问题显然想 ACAM。

于是对于所有 $s_i$ 建立 AC 自动机，查询就是拿 $S$ 在自动机上跑，每次求一个 fail 树上的链求和，设 $\sum |s_i|=L$。

链求和可以考虑转欧拉序，注意到实际上有用的点只有 $O(n)$ 个而不是 $O(L)$ 个。

发现修改不太好维护，所以考虑分块，设块长为 $B$。

考虑散块贡献的处理：

我们用线段树维护 $a_i$，询问直接暴力。

修改复杂度为 $O(m\log n)$，询问复杂度为 $O(LB\log n)$。

考虑整块贡献的处理：

对于一个块，我们开一个线段树维护 $i\in[l,r]$ 的区间内的 $cnt_i\times a_i$

因为 $cnt$ 是不变的，所以可以直接维护，复杂度为 $O(\dfrac{nm}{B}\log n)$

查询我们注意到，对于一个串，他在一个块里查询的区间是一样的，所以可以只查一次，复杂度为 $O(\dfrac{nm}{B}\log n+\dfrac{nL}{B})$。

平衡一下复杂度，$B=\sqrt\dfrac{nm}{L}$ 的时候应该是最优的，复杂度为 $O(\sqrt{nmL}\log n+L\sqrt L)$，理论上可以通过并且复杂度更优

但是跑的特别慢，只能拿 35 分。

```cpp
#include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;
typedef double db;

# define chkmax(a,b) a=max(a,b)
# define chkmin(a,b) a=min(a,b)
# define PII pair<int,int>
# define mkp make_pair

const int N=6e4+5;
const int M=2e5+5;

template<typename T> void read(T &x){
    x=0;int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,B,bl;
string s[M];
int a[N],b[N];
int L[N],R[N],pos[N];
int euler[N],in[M],ou[M];
int ac[M][3],fail[M],tot;
int head[M],cnt;
ll out[N];

struct Edge{
    int to,next;
}e[M<<1];

void add(int x,int y){
    e[++cnt]=(Edge){y,head[x]},head[x]=cnt;
}

struct misaka{
    int opt,l,r,k;
    string s;
}Q[N];

vector<int> T[M];

struct node{
    int cnt,abc,sum,tag,cov;
}seg[N<<2];

void insert(string s,int i){
    int len=s.size(),u=0;
    for(int i=0;i<len;i++){
        int j=s[i]-'a';
        if(!ac[u][j])ac[u][j]=++tot;
        u=ac[u][j];
    }
    T[u].push_back(i);
}

void construct(){
    queue<int> q;
    Rep(i,0,2)if(ac[0][i])q.push(ac[0][i]);
    while(!q.empty()){
        int u=q.front();q.pop();
        Rep(i,0,2)
            if(ac[u][i])fail[ac[u][i]]=ac[fail[u]][i],q.push(ac[u][i]);
            else ac[u][i]=ac[fail[u]][i];
    }
}

void dfs(int u,int fa){
    in[u]=tot+1;
    for(auto v:T[u])euler[++tot]=v;
    ou[u]=tot;
    RepG(i,u){
        int v=e[i].to;
        if(v==fa)continue;
        dfs(v,u);
    }
    for(auto v:T[u])euler[++tot]=-v;
}

# define lc (u<<1)
# define rc (u<<1|1)

void pusht(int u,int k){
    seg[u].sum+=k*seg[u].cnt;
    seg[u].tag+=k;
}

void pushc(int u,int k){
    seg[u].sum=seg[u].cnt*k;
    seg[u].tag=0;
    seg[u].cov=k;
}

void pushdown(int u){
    if(seg[u].cov){
        if(seg[lc].abc)pushc(lc,seg[u].cov);
        if(seg[rc].abc)pushc(rc,seg[u].cov);
        seg[u].cov=0;
    }
    if(seg[u].tag){
        if(seg[lc].abc)pusht(lc,seg[u].tag);
        if(seg[rc].abc)pusht(rc,seg[u].tag);
        seg[u].tag=0;
    }
}

void build(int u,int l,int r){
    seg[u].tag=seg[u].cov=0;
    if(l==r){
        seg[u].abc=abs(b[l]);
        seg[u].cnt=b[l];
        seg[u].sum=a[l]*b[l];
        return;
    }
    int mid=l+r>>1;
    build(lc,l,mid);
    build(rc,mid+1,r);
    seg[u].abc=seg[lc].abc+seg[rc].abc;
    seg[u].cnt=seg[lc].cnt+seg[rc].cnt;
    seg[u].sum=seg[lc].sum+seg[rc].sum;
}

void update(int u,int l,int r,int ql,int qr,int k){
    if(!seg[u].abc)return;
    if(l>=ql&&r<=qr){
        pusht(u,k);
        return;
    }
    pushdown(u);
    int mid=l+r>>1;
    if(ql<=mid)update(lc,l,mid,ql,qr,k);
    if(qr>mid)update(rc,mid+1,r,ql,qr,k);
    seg[u].sum=seg[lc].sum+seg[rc].sum;
}

void modify(int u,int l,int r,int ql,int qr,int k){
    if(!seg[u].abc)return;
    if(l>=ql&&r<=qr){
        pushc(u,k);
        return;
    }
    pushdown(u);
    int mid=l+r>>1;
    if(ql<=mid)modify(lc,l,mid,ql,qr,k);
    if(qr>mid)modify(rc,mid+1,r,ql,qr,k);
    seg[u].sum=seg[lc].sum+seg[rc].sum;
}

int query(int u,int l,int r,int ql,int qr){
    if(!seg[u].abc)return 0;
    if(l>=ql&&r<=qr)return seg[u].sum;
    pushdown(u);
    int mid=l+r>>1;ll res=0;
    if(ql<=mid)res+=query(lc,l,mid,ql,qr);
    if(qr>mid)res+=query(rc,mid+1,r,ql,qr);
    return res;
}

int ask(int l,int r,int ql,int qr){
    int res=0;
    if(pos[l]==pos[r]){
        Rep(i,l,r)
            if(abs(euler[i])>=ql&&abs(euler[i])<=qr)
            if(euler[i]>0)res+=query(1,1,n,euler[i],euler[i]);
            else res-=query(1,1,n,-euler[i],-euler[i]);
        return res;
    }
    Rep(i,L[pos[r]],r)
        if(abs(euler[i])>=ql&&abs(euler[i])<=qr)
        if(euler[i]>0)res+=query(1,1,n,euler[i],euler[i]);
        else res-=query(1,1,n,-euler[i],-euler[i]);
    return res;
}

int main()
{
    # ifdef YuukiYumesaki
    freopen("testdata.in","r",stdin);
    freopen("test1.out","w",stdout);
    # endif
    memset(head,-1,sizeof(head));
    read(n),read(m);
    Rep(i,1,n){
        cin>>s[i];
        read(a[i]);
    }
    Rep(i,1,n)insert(s[i],i);
    construct();
    Rep(i,1,tot)add(fail[i],i);
    assert(!(tot>2e5));
    int tmp=tot;
    tot=0;
    dfs(0,0);
    B=sqrt(n*m/2e5);
    Rep(i,1,tot)pos[i]=(i-1)/B+1;
    bl=pos[tot];
    Rep(i,1,bl)L[i]=(i-1)*B+1,R[i]=i*B;
    R[bl]=tot;
    Rep(i,1,m){
        read(Q[i].opt),read(Q[i].l),read(Q[i].r);
        if(Q[i].opt==3)cin>>Q[i].s;
        else read(Q[i].k);
    }
    Rep(i,1,n)b[i]=1;
    build(1,1,n);
    Rep(x,1,m){
        int l=Q[x].l,r=Q[x].r,k=Q[x].k;
        if(Q[x].opt==1)update(1,1,n,l,r,k);
        else if(Q[x].opt==2)modify(1,1,n,l,r,k);
        else{
            int u=0,len=Q[x].s.size();
            for(int i=0;i<len;i++){
                u=ac[u][Q[x].s[i]-'a'];
                out[x]+=ask(1,ou[u],l,r);
            }
        }
    }
    Rep(i,1,n)b[i]=0;
    Rep(x,1,bl){
        Rep(i,L[x],R[x])
            if(euler[i]>0)b[euler[i]]++;
            else b[-euler[i]]--;
        build(1,1,n);
        Rep(y,1,m){
            int l=Q[y].l,r=Q[y].r,k=Q[y].k;
            if(Q[y].opt==1)update(1,1,n,l,r,k);
            else if(Q[y].opt==2)modify(1,1,n,l,r,k);
            else{
                int u=0,len=Q[y].s.size();
                int val=query(1,1,n,l,r);
                for(int i=0;i<len;i++){
                    u=ac[u][Q[y].s[i]-'a'];
                    if(pos[ou[u]]>x)out[y]+=val;
                }
            }
        }
        Rep(i,L[x],R[x])
            if(euler[i]>0)b[euler[i]]--;
            else b[-euler[i]]++;
    }
    Rep(i,1,m)if(Q[i].opt==3)printf("%lld\n",out[i]);
    return 0;
}
/*
3 1
ab 1
ba 2
a 1
3 1 3 aba

*/
```

---

## 作者：cike_bilibili (赞：0)

简单分块题。

首先这题是一个多串匹配问题，我们考虑上 AC 自动机，考虑暴力一点的做法，就是建出在区间 $[l,r]$ 内的 AC 自动机，然后将模式串在上面匹配时，加上 fail 祖先链上的所有 endpos 的贡献，这样有 $O(n^2)$ 的做法。

可是这题多组询问，而且还带修，我们肯定要上数据结构快速查询修改，看数据范围有 $n,m \le 3 \times 10^4$，大概率是根号算法，可能还要带个 $\log$，于是考虑分块。

先不考虑修改操作，我们将每一个块内的所有串放在一起建一个 AC 自动机，我们将模式串放上去匹配，散块可以用 hash 或 kmp 之类的匹配算法暴力计算，时间复杂度 $O(\sum |S| \cdot \sqrt n )$。

考虑修改操作，首先是区间加操作，整块打标记，散块暴力重构，注意不能将整个 fail 树重构，因为复杂度不均摊，所以用树上差分的方式改树状数组就行了。

赋值操作也一样，注意如果一个区间被赋过值了，区间加就直接加复制标记就行了。

时间复杂度 $O(\sqrt n \sum |S| \log( \sum |s| ))$。

---

