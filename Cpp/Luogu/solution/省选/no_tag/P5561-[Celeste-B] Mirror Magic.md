# [Celeste-B] Mirror Magic

## 题目背景

> ...

> 呼吸。

> 你能站起来，Madeline

> 想想羽毛。你能拯救 Theo

## 题目描述

镜之神庙是一座有魔力的神庙，在这里你能一窥自己心灵的真相。

Theo 被困在了一面镜子里。当 Madeline 尝试去拯救 Theo 时，神庙里的"生物"们给她出了一道难题，这道难题是这样的：

神庙的"生物"们准备了 $n$ 串草莓，这些草莓的长度之和 $<= 10^6$，现在它们可以执行这样一些操作：

$1\ x\ l\ r$，表示将编号 $x$ 的草莓串的子草莓串 $[l,r]$ 复制一份，插入当前的草莓集合中，保证草莓串 $x$ 的长度 $>=r$。

$2\ k$，表示删除第 $k$ 次操作插入的草莓串，保证第 $k$ 次操作为插入并且此时第 $k$ 次操作插入的草莓串在集合中。

"生物"们认为和谐的味道才是美味的。在执行任意一次操作之后，"生物"们想要知道当前集合中所有草莓串的美味度(即 $LCP$ - 最长公共前缀)。（若集合为空，则美味度 $0$，若集合中只有一个草莓串，则美味度为草莓串的长度）

为了方便表达，我们把每一种草莓表示为一个**小写英文字母**。

多年以后，Madeline 又来到了镜之神庙，想要回忆多年前自己的登山旅途，可是她已经不记得自己当年是怎么解决那道谜题的了，你能帮帮她找到谜题的答案吗？

## 说明/提示

样例解释：

第一次操作后，集合为 $\{"abccccd"\}$,$LCP=7$

第二次操作后，集合为 $\{"abccccd","abccddc"\}$,$LCP=4$

第三次操作后，集合为 $\{"abccccd","abccddc","acbbcad"\}$,$LCP=1$

第四次删除了第三次插入的串，故 $LCP=4$

第五次删除了第二次插入的串，故 $LCP=7$

令 $len$ 等于 $n$ 个串的长度之和。总有 $len \leq 10^6$

Subtask $1$($10$ Pts), $n \leq 5, q = 10$

Subtask $2$($30$ Pts), $n \leq 10^6, q = 10^6$, 保证每次插入的是串的一个前缀

Subtask $3$($10$ Pts), $n \leq 10^6, q = 10^5$, 不含 $2$ 操作, **保证询问为随机生成**

Subtask $4$($50$ Pts), $n \leq 10^6, q = 10^6$

提示：你可以根据 $q$ 判断 Subtask 编号



## 样例 #1

### 输入

```
3
abccccd
abccddc
acbbcad
5
1 1 1 7
1 2 1 7
1 3 1 7
2 3
2 2
```

### 输出

```
7
4
1
4
7
```

# 题解

## 作者：lzqy_ (赞：1)

每个子串出现的时间都是一段区间，考虑线段树分治。

线段树的每个节点动态维护当前 $\text{LCP}$ 对应的子串，每次加入新串时更新。

那么瓶颈变为求任意两个子串的 $\text{LCP}$。

先把所有串接在一起建反串 SAM。

一个观察是任意子串 $\text{LCP}$ 可以看作两端后缀的 $\text{LCP}$ 对子串长度取 $\min$。因此，预处理出每段后缀在反串 SAM 上的位置，然后用 $O(n\log n)-O(1)$ LCA 即可做到 $O(n\log n)$ 的总复杂度。

但是本题过于卡空间，要把欧拉序求 LCA 换成树剖求 LCA。虽然变成了 $O(n\log ^2 n)$ 但其实比原先快了三分之一。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=2000010;
const int MAXN=4000010;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
struct edge{
	int v,to;
}e[maxn<<1];
int head[maxn],ecnt;
void addedge(int u,int v){
	e[++ecnt].v=v,e[ecnt].to=head[u],head[u]=ecnt;
}
struct sam{
	int ch[26],fa,len;
}a[maxn];
int loc[maxn],cnt=1,End=1;
void Insert(int c){
	int t=End,x=End=++cnt,nt=0,nx; a[x].len=a[t].len+1;
	loc[a[x].len]=x;//////////////////
	for(;t&&!nt;t=a[t].fa,nt=a[t].ch[c]) a[t].ch[c]=x;
	if(!t){a[x].fa=1;return ;}
	if(a[t].len+1==a[nt].len){a[x].fa=nt;return ;}
	nx=++cnt,a[nx].len=a[t].len+1;
	a[nx].fa=a[nt].fa,a[nt].fa=a[x].fa=nx;
	for(int i=0;i<26;i++) a[nx].ch[i]=a[nt].ch[i];
	for(;a[t].ch[c]==nt;t=a[t].fa) a[t].ch[c]=nx;
}
struct str{
	int l,r,tl,tr;
}A[maxn];
int sz[maxn],zson[maxn],dep[maxn],fa[maxn];
int dfn[maxn],DFN[maxn],top[maxn],idx;
void dfs1(int fath,int x){
//	printf("!!!%d\n",x);
	dep[x]=dep[fath]+1,fa[x]=fath;
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v^fath){
			dfs1(x,e[i].v),sz[x]+=sz[e[i].v];
			if(sz[zson[x]]<sz[e[i].v]) zson[x]=e[i].v;
		}sz[x]++; 
}
void dfs2(int x){
	dfn[x]=++idx,DFN[idx]=x;
	if(zson[fa[x]]^x) top[x]=x;
	else top[x]=top[fa[x]];
	if(zson[x]) dfs2(zson[x]);
	for(int i=head[x];i;i=e[i].to)
		if(e[i].v!=fa[x]&&e[i].v!=zson[x]) dfs2(e[i].v);
}
int dl[MAXN],dr[MAXN];
int n,m,q,L[maxn],R[maxn];
char c[maxn],C[maxn];
int lca(int x,int y){
	while(top[x]^top[y])
		dfn[top[x]]>dfn[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dfn[x]>dfn[y]?y:x;
}
int lcp(int i,int j){
	return a[lca(loc[n-i+1],loc[n-j+1])].len;
}
void Add(int i,int l,int r,int L,int R,int sl,int sr){
	if(l>=L&&r<=R){
		if(dl[i]&&dr[i]) dr[i]=dl[i]+min(lcp(dl[i],sl),min(dr[i]-dl[i]+1,sr-sl+1))-1;
		else dl[i]=sl,dr[i]=sr;
		return ;
	}int mid=l+r>>1;
	if(mid>=L) Add(i<<1,l,mid,L,R,sl,sr);
	if(mid<R) Add(i<<1|1,mid+1,r,L,R,sl,sr);
}
void Print(int i,int l,int r,int sl,int sr){
	if(dl[i]&&dr[i]){
		if(sl&&sr) sr=sl+min(lcp(dl[i],sl),min(dr[i]-dl[i]+1,sr-sl+1))-1;
		else sl=dl[i],sr=dr[i];
	}
	if(l==r){
		printf("%d\n",(sl&&sr)?sr-sl+1:0);
		return ;
	}int mid=l+r>>1;
	Print(i<<1,l,mid,sl,sr);
	Print(i<<1|1,mid+1,r,sl,sr);
}
int main(){
	m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",C+1);
		L[i]=R[i-1]+1,R[i]=L[i]+strlen(C+1)-1;
		for(int j=L[i];j<=R[i];j++) c[j]=C[j-L[i]+1];
	}n=strlen(c+1);
	for(int i=n;i;i--) Insert(c[i]-'a');
	for(int i=2;i<=cnt;i++)
		addedge(a[i].fa,i),addedge(i,a[i].fa);
	dfs1(0,1),dfs2(1);
	q=read();
	for(int i=1;i<=q;i++){
		int op=read(),x=read();
		if(op==1){
			A[i].l=L[x]+read()-1;
			A[i].r=L[x]+read()-1;
			A[i].tl=i;
		}
		else A[x].tr=i-1;
	}
	for(int i=1;i<=q;i++)
		if(!A[i].tr) A[i].tr=q;
	for(int i=1;i<=q;i++)
		if(A[i].l) Add(1,1,q,A[i].tl,A[i].tr,A[i].l,A[i].r);
	Print(1,1,q,0,0);
	return 0;
} 

```

---

## 作者：ArrTue (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P5561)

#### 前置知识：

后缀数组求最长公共前缀。

#### 题意：

- 给出 $n$ 个字符串，一个字符串集合 $S$（初始为空），$q$ 次操作，每次操作分为两种：
	1. 将第 $x$ 个字符串的子串 $[l,r]$ 加入集合 $S$。
	2. 撤销第 $k$ 次操作。保证第 $k$ 次操作为操作 1 且未被撤销过。
- 每次操作后，询问集合内所有字符串的 $\text{LCP}$ 的长度。若集合为空，输出 0。

- 记字符串总长为 $m$，$n,m,q\le10^6$。

#### 分析：

前三个 Subtask 和正解无关，可直接从 Subtask 4 开始看。

**Subtask 1：**$n\le5$，$q=10$。

暴力。

**Subtask 2：**每次插入保证 $l=1$。

先考虑每次都会插入一整个字符串的情况。相当于求若干字符串的 $\text{LCP}$，字符串总长不超过 $10^6$。

考虑将所有字符串插入一棵 $\text{Trie}$ 中，则求 $\text{LCP}$ 转化为求 $\text{LCA}$，可以使用欧拉环游序解决。

**Subtask 3：**$q=10^5$，不含操作 2，询问随机生成。

若 $n=1$，则暴力期望时间复杂度为 $\mathcal O(m\log m)$。[证明 link](https://www.luogu.com.cn/paste/sx27ugfb)。

若 $n>1$，则更容易生成长度较短的询问，应当更快。

**Subtask 4：**

先考虑操作 1 中子串均为字符串后缀的情况。

此时询问相当于求若干字符串后缀的 $\text{LCP}$。将这些后缀按排名排序，可以发现这些后缀的 $\text{LCP}$ 即为排名最小的后缀与排名最大的后缀的 $\text{LCP}$。证明可以考虑反证法。

这样只需要维护排名的集合，每次询问时取出最小值和最大值，求一次 $\text{LCP}$ 即可。

再考虑非后缀情况。只需要当成后缀考虑，求出 $\text{LCP}$ 与子串长度的较小值即可。

---

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
#pragma GCC diagnostic ignored "-Wparentheses"
using namespace std;
typedef long long ll;
inline int read() {
	int res=0; bool k=1; char ch;
	while(!isdigit(ch=getchar())) k=ch^45;
	do res=res*10+(ch&15); while(isdigit(ch=getchar()));
	return k? res: -res;
}
inline int max_(const int a, const int b) {return a>b? a: b;}
inline int min_(const int a, const int b) {return a<b? a: b;}

const int mN=1e6+9, mD=22;
int n, m, lg[mN], mn[mD][mN];
char c[mN], *en[mN];
//将所有字符串拼接成一个 c
//en[i] 表示第 i 个字符串的结束位置
int qn[mN][2];
multiset<int> S, len;
//S 记录排名，len 记录长度

//begin 板子
int buc[mN], ork, rk[2][mN*2], sa[mN], t1[mN], t2[mN];
inline void get_buc(int *a) {
	memset(buc, 0, ork+1<<2);
	rep(i, 1, m) ++buc[a[i]];
	rep(i, 1, ork) buc[i]+=buc[i-1];
}
void get_sa() {
	rep(i, 1, m) rk[0][i]=c[i];
	ork=127+(m&1);
	int t=0, *a;
	for(; t<=lg[m] && ork^m; ++t) {
		get_buc((a=rk[t&1])+(1<<t));
		rep(i, 1, m) t1[buc[a[i+(1<<t)]]--]=i;
		get_buc(a);
		for(int i=m; i>=1; --i) t2[buc[a[t1[i]]]--]=t1[i];
		ork=0;
		rep(i, 1, m) {
			if(a[t2[i]]!=a[t2[i-1]] || a[t2[i]+(1<<t)]!=a[t2[i-1]+(1<<t)]) ++ork;
			rk[t&1^1][t2[i]]=ork;
		}
	}
	a=rk[0];
	if(t&1) memcpy(a, rk[1], m+1<<2);
	rep(i, 1, m) sa[a[i]]=i;
	rep(i, 1, m) for(int &j=mn[0][a[i]]=max_(mn[0][a[i-1]]-1, 0); c[i+j]==c[sa[a[i]+1]+j]; ) ++j;
	rep(t, 1, lg[m]) rep(i, 1, m-(1<<t)+1) mn[t][i]=min_(mn[t-1][i], mn[t-1][i+(1<<t-1)]);
}
//end 板子

int main() {
	rep(i, 2, mN-1) lg[i]=lg[i>>1]+1;
	en[0]=c;
	rep(i, 1, n=read()) scanf("\n%s", en[i-1]+1), en[i]=en[i-1]+strlen(en[i-1]+1);
	m=en[n]-c, get_sa();
	rep(i, 1, read()) {
		if(read()==1) {
			int x=read(), l=read(), r=read();
			S.insert(qn[i][0]=rk[0][en[x-1]-c+l]), len.insert(qn[i][1]=r-l+1);
		} else {
			int x=read();
			S.erase(S.find(qn[x][0])), len.erase(len.find(qn[x][1]));
		}
		if(S.empty()) {puts("0"); continue;}
		int l=*S.begin(), r=(*--S.end())-1, ans=*len.begin();
		//l 为最小排名，r 为最大排名，ans 为最小长度
		if(l<=r) ans=min_(ans, min_(mn[lg[r-l]][l], mn[lg[r-l]][r-(1<<lg[r-l])+1]));
		//若 l>r，即集合中只有一种后缀，则 LCP 即为长度，而 len 中已经记录了长度
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Nagato__Yuki (赞：0)

# Solution
考虑对反串建广义 SAM。可以把题目转化一下，变成求一堆后缀的 LCP，加上一个长度的限制，这个长度限制用 `multiset` 维护就行了。然后这一堆后缀的 LCP ，就是其在反串的 SAM 上对应的点在 parent tree 上的 LCA，我们知道一堆点的 LCA 就是这些点中 dfs 序最小的点和最大的点的 LCA，所以也用一个 `multiset` 存 dfs 序，修改是容易的，每次询问取最小的和最大的点求 LCA 即可。这里用树剖求 LCA，时间复杂度 $\mathcal O(n\log n)$，非常好写。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mxn 2000010
#define link(x) sam[x].link
#define len(x) sam[x].len
#define nxt(x) sam[x].nxt
#define id(x) sam[x].id
#define pb push_back
#define I inline
struct node{int nxt[27],link,len;}sam[mxn];
struct oper{int opt,l,r,k;}op[mxn];
int n,q,lst,c,tim,len[mxn],id[mxn],Ans[mxn];
int dfn[mxn],dep[mxn],fa[mxn],top[mxn],son[mxn],sze[mxn];
multiset<int> lenn,dfnn;
int p2[mxn],*pos[mxn];
char p1[mxn],*s[mxn];
vector<int> t[mxn];
// sam 板子
I int insert(int x){
    if(nxt(lst)[x]&&len(nxt(lst)[x])==len(lst)+1)
        {lst=nxt(lst)[x];return lst;}
    int p=lst,u=++c;len(u)=len(p)+1;
    while(p&&!nxt(p)[x])nxt(p)[x]=u,p=link(p);
    if(!p){link(u)=1,lst=u;return u;}
    int q=nxt(p)[x],cl;
    if(len(q)==len(p)+1){link(u)=q,lst=u;return lst;}
    if(p==lst)cl=u;else cl=++c,link(u)=cl;
    sam[cl]=sam[q],len(cl)=len(p)+1,link(q)=cl;
    while(p&&nxt(p)[x]==q)nxt(p)[x]=cl,p=link(p);
    lst=u;return u;
}
// 树剖求 lca
I void dfs1(int u,int f){
    dfn[u]=++tim,sze[u]=1;
    fa[u]=f,id[tim]=u,dep[u]=dep[f]+1;
    for(int v:t[u]){
        dfs1(v,u),sze[u]+=sze[v];
        if(sze[v]>sze[son[u]])son[u]=v;
    }
}
I void dfs2(int u,int Top){
    top[u]=Top;
    if(son[u])dfs2(son[u],Top);
    for(int v:t[u]){
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}
I int lca(int u,int v){
    u=id[u],v=id[v];
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])v=fa[top[v]];
        else u=fa[top[u]];
    }
    if(dep[u]<dep[v])return u;
    else return v;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    c=1,cin>>n;int lsum=1;
    for(int i=1;i<=n;i++){
        cin>>p1+lsum,lst=1;
        s[i]=p1+lsum-1,pos[i]=p2+lsum-1;
        len[i]=strlen(p1+lsum),lsum+=len[i];
        for(int j=len[i];j;j--)
            pos[i][j]=insert(s[i][j]-'a'+1);
    }
    for(int i=2;i<=c;i++)t[link(i)].pb(i);
    dfs1(1,0),dfs2(1,1),cin>>q;
    int sze=0;
    for(int i=1;i<=q;i++){
        int opt,l,r,k;cin>>opt;
        if(opt==1)
            cin>>k>>l>>r,op[i]={opt,l,r,k},
            lenn.insert(r-l+1),
            dfnn.insert(dfn[pos[k][l]]);
        else
            cin>>k,l=op[k].l,r=op[k].r,k=op[k].k,
            lenn.erase(lenn.find(r-l+1)),
            dfnn.erase(dfnn.find(dfn[pos[k][l]]));
        if(dfnn.size()==0){cout<<0<<'\n';continue;}
        l=*dfnn.begin(),r=*(--dfnn.end()),k=*lenn.begin();
        cout<<min(k,len(lca(l,r)))<<'\n';
    }
    return 0;
}

```

![](https://cdn.luogu.com.cn/upload/image_hosting/dyxjzqx2.png)

---

