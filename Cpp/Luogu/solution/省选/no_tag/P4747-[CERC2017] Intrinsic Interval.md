# [CERC2017] Intrinsic Interval

## 题目描述

对于正整数 $1,2,3 \cdots n$ 的一个排列 $\pi$，若它的一个子串 $\pi[a..b]$ 排序后是连续正整数，则称 $\pi[a..b]$ 是一个“区间”。例如对排列 $pi={3,1,7,5,6,4,2}$，子串 $\pi[3..6]$ 是一个“区间”（因为它包含 $4,5,6,7$），$\pi[1..3]$ 则不是。

一个子串的“本征区间”是包含该子串的最短区间。“包含”是指：若 $\pi[x..y]$ 的本征区间是 $\pi[a..b]$，则 $a \le x \le y \le b$。

给定一个排列 $\pi$ 及其 $m$ 个子串，求每个子串的“本征区间”。

## 样例 #1

### 输入

```
7
3 1 7 5 6 4 2
3
3 6
7 7
1 3
```

### 输出

```
3 6
7 7 
1 7```

## 样例 #2

### 输入

```
10
2 1 4 3 5 6 7 10 8 9
5
2 3
3 7
4 7
4 8
7 8
```

### 输出

```
1 4
3 7
3 7
3 10
7 10
```

# 题解

## 作者：i207M (赞：20)

今天考试正好考了这道题，~~然后我就因为读错题爆零了~~，回去钻研博客，发篇题解。

写在之前：这道题可以用图论的方法解决，具体思想是用线段树优化区间连边，然后缩scc...balabala

~~上面的我不会~~

我们把题干里描述的区间成为“好区间”。一条性质：好区间的交也是好区间。

处理这种问题，一个利器就是**离线之后线段树扫描线**。

**设当前扫描线扫描到r**，关键就是如何维护$[l,r]$是否为好的区间。

我先说方法，再说证明：

建立一棵线段树，维护最大值和最大值出现的最靠右的位置。**设线段树上每个点的权值为val[i]**，则初值为$val[i]=i$

从左到右扫描，设$p[v]$表示权值v出现的位置。执行下面的代码，其中upd为区间+1.

```cpp
if(a[i]>1&&p[a[i]-1]<=i) upd(1,p[a[i]-1]);
if(a[i]<n&&p[a[i]+1]<=i) upd(1,p[a[i]+1]);
```

那么，**如果$val[l]==r$，则$[l,r]$是“好区间”**。

证明：

如果区间长度为2，即$val[r-1]=r$，那么显然$a[r-1]=a[r]-1 \text{ or } a[r]+1$

如果$val[l]==r$，那么$val[l]$处被++了$r-l$次。也就是说，在$[l,r]$区间内，存在$r-l$个相邻的数对。根据咕咕原理，权值区间一定是连续的。

换一种理解，如果$[l,r]$的权值区间为$[c,d]+[e,f],e-d>1$，那么d和e就不能贡献“相邻的数对”，所以$val[l]$被覆盖的次数一定$<r-l$次。


询问按L从大到小排序。

----------------

```cpp
#define N 100005
#define M N*4
#define ls (x<<1)
#define rs (x<<1|1)
#define gm int mid((l+r)/2)
int n,a[N],p[N];
const int rt=1;
int mx[M],pos[M],laz[M];
il void up(int x)
{
	mx[x]=max(mx[ls],mx[rs]);
	pos[x]=mx[ls]>mx[rs]?pos[ls]:pos[rs];
}
il void down(int x)
{
	if(laz[x])
	{
		mx[x]+=laz[x];
		if(rs<M)
		{
			laz[ls]+=laz[x],laz[rs]+=laz[x];
		}
		laz[x]=0;
	}
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		mx[x]=pos[x]=l;
		return;
	}
	gm;
	build(ls,l,mid), build(rs,mid+1,r);
	up(x);
}
void upd(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
	{
		++laz[x];
		down(x);
		return;
	}
	gm; down(x);
	if(ql<=mid) upd(ls,l,mid,ql,qr);
	else down(ls);
	if(qr>mid) upd(rs,mid+1,r,ql,qr);
	else down(rs);
	up(x);
}
int al,ar;
void ask(int x,int l,int r,int ql,int qr)
{
	down(x);
	if(ql<=l&&r<=qr)
	{
		if(mx[x]>=ar)
		{
			al=pos[x],ar=mx[x];
		}
		return;
	}
	gm;
	if(ql<=mid) ask(ls,l,mid,ql,qr);
	if(qr>mid) ask(rs,mid+1,r,ql,qr);
}
pairint ans[N];
bool judge(pairint x,int r)
{
	ar=-1; ask(rt,1,n,1,x.fi);
	if(ar==r)
	{
		ans[x.se]=mp(al,ar);
		return 1;
	}
	return 0;
}
vector<pairint>g[N];
priority_queue<pairint>s;
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("out.out","w",stdout);
#endif
	in(n);
	for(ri i=1; i<=n; ++i) in(a[i]),p[a[i]]=i;
	int cntq; in(cntq);
	for(ri i=1,l,r; i<=cntq; ++i)
	{
		in(l),in(r);
		g[r].pb(mp(l,i));
	}
	build(rt,1,n);
	for(ri i=1; i<=n; ++i)
	{
		if(a[i]>1&&p[a[i]-1]<=i) upd(rt,1,n,1,p[a[i]-1]);
		if(a[i]<n&&p[a[i]+1]<=i) upd(rt,1,n,1,p[a[i]+1]);
		for(const pairint &v:g[i]) s.push(v);
		while(!s.empty())
		{
			if(judge(s.top(),i)) s.pop();
			else break;
		}
	}
	for(ri i=1; i<=cntq; ++i) out(ans[i].fi,' '),out(ans[i].se);
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：18)

这题真的是一道思维好题。（感谢$i207M$神犇提供的思路qwq）

首先显而易见的有这个好区间的$max-min=r-l$，不过要做这题光有这个还不够，做这种题的时候就不能把这堆数完全当做离散量来处理，我们还需要找出一些别的性质。

我们发现包含着这段区间的好区间可能会有很多吧，考虑两个包着这个区间的好区间$[l_1,r_1]$和$[l_2,r_2]$，我们只讨论不包含的情况（因为包含的话外层那个区间肯定是没用的），不妨设$l_2>l_1$，那么这两个区间的交$[l_2,r_1]$也是包含着这个询问区间的。既然他是两个好区间的交，我们不妨考虑这样一个问题：$[l_2,r_1]$为什么既能和$[l_1,l_2-1]$拼成一个好区间，又能和$[r_1+1,r_2]$拼成一个好区间？我们发现$[l_2,r_1]$居然也是一个好区间！假如他不好的话，也就是说中间不连续，那么它最多只能和一边的区间拼成好区间。那么我们可以断言，**从$r$开始的第一个能够包住$[l,r]$的好区间的右端点对应的最短能够包住$[l,r]$的好区间就是唯一的答案**（~~这话好绕口啊……~~）。

于是就可以有这样一个思路，我们维护一个扫描线，把这些区间离线下来，然后想办法找出当前点$i$对应的右端点的好区间按照$l$的顺序（用个set维护）直接处理掉。那么考虑如何找所有可行的左端点。

其实题面上已经给了我们一个非常好的提示：


 _若它的一个子串 $\pi[a..b]$ 排序后是连续正整数，则称 $\pi[a..b]$ 是一个“好区间”。_
 
我们发现把这玩意排序之后相邻的两项差为1对吧，那么这个好区间$[l,r]$有多少无序二元组$(i,j)$是相邻两项或者绝对值为1呢？显然就是$r-l$，显然对于无序二元组可以在靠后的那个位置统计。那么我们就可以把好区间换个定义了：

_在$[l,r]$内有$r-l$个无序二元组的区间_

那么我们现在枚举的是$r$，那么直接找$l$后面有多少个二元组即可。于是我们可以把式子变形，不妨设$val[l]$为$l$后面有多少个合法的二元组，那么显然就有$val[l]+l=r$当且仅当$[l,r]$为好区间。于是我们就可以换一种角度进行统计：开一个初始值为下标的线段树，然后我们在扫描线的时候如果发现$a_{i-1}$或者$a_{i+1}$在$i$前面就把1~他们的位置进行区间加，显然值为$i$的位置就是可行的好区间。

那么我们该如何在处理询问的时候找出区间内等于$i$的最后一个位置呢？表面上看起来是不可做的，但是不难发现一个区间内最多只会有$r-l$个合法的二元组（其实就是把他们排序一下看然后就不可能再多了），也就是说等于$i$的位置是区间内的最大值，既然是最大值就可以在线段树上乱搞了。

上代码~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
#define ls(_o) (_o<<1)
#define rs(_o) ((_o<<1)|1)
#define up(_o) maxn[_o]=max(maxn[ls(_o)],maxn[rs(_o)])
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	void print(int num){
		if(num>=10)print(num/10);putchar(num%10+'0');
	}
	int ansl[100001],ansr[100001];
	typedef struct _qj{
		int l;int r;int id;
		friend bool operator <(const _qj &a,const _qj &b){
			if(a.l==b.l)return(a.id<b.id);
			return(a.l<b.l);
		}
	}qj;
	set<qj> st;
	int ints[100001],pos[100001],maxn[1000001],adds[1000001];
	inline void down(int tree){
		if(!adds[tree])return;
		int cjr=adds[tree];
		adds[tree]=0;
		adds[ls(tree)]+=cjr;adds[rs(tree)]+=cjr;
		maxn[ls(tree)]+=cjr;maxn[rs(tree)]+=cjr;
	}
	int query(int rl,int rr,int l,int r,int tree,int num){//cout<<tree<<endl;
		down(tree);int mid=(l+r)>>1;
		if(rl>rr)return(-1);
		if(rl==l&&rr==r){
			if(maxn[tree]!=num)return(-1);if(l==r)return(l);
			if(maxn[rs(tree)]==num)return(query(mid+1,r,mid+1,r,rs(tree),num));
			return(query(l,mid,l,mid,ls(tree),num));
		}
		if(rl>mid)return(query(rl,rr,mid+1,r,rs(tree),num));
		if(rr<=mid)return(query(rl,rr,l,mid,ls(tree),num));
		int cjr=query(mid+1,rr,mid+1,r,rs(tree),num);
		if(cjr!=-1)return(cjr);
		return(query(rl,mid,l,mid,ls(tree),num));
	}
	vector<qj> vec[100001];
	void inc(int rl,int rr,int l,int r,int tree){
		if(rl==l&&rr==r){
			adds[tree]++;maxn[tree]++;return;
		}
		int mid=(l+r)>>1;down(tree);
		if(rl>mid)inc(rl,rr,mid+1,r,rs(tree));else{
			if(rr<=mid)inc(rl,rr,l,mid,ls(tree));else{
				inc(rl,mid,l,mid,ls(tree));
				inc(mid+1,rr,mid+1,r,rs(tree));
			}
		}up(tree);
	}
	void build(int l，int r,int tree){
		if(l==r){
			maxn[tree]=l;return;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls(tree));
		build(mid+1,r,rs(tree));up(tree);
	}
	typedef set<qj>::iterator it;
	void ywymain(){
		int n=get();
		for(register int i=1;i<=n;i++)pos[ints[i]=get()]=i;
		int m=get();
		for(register int i=1;i<=m;i++){
			int l=get(),r=get();
			qj cjr;cjr.l=l;cjr.r=r;cjr.id=i;
			vec[r].push_back(cjr);
		}
		build(1,n,1);
		for(register int i=1;i<=n;i++){
			if(ints[i]!=1&&pos[ints[i]-1]<i)inc(1,pos[ints[i]-1],1,n,1);
			if(ints[i]!=n&&pos[ints[i]+1]<i)inc(1,pos[ints[i]+1],1,n,1);
			for(register int j=0;j<vec[i].size();j++){
				st.insert(vec[i][j]);
			}
			while(st.begin()!=st.end()){
				it lp=st.end();lp--;qj me=*lp;
				int cjr=query(1,me.l,1,n,1,i);
				if(cjr==-1)break;
				ansl[me.id]=cjr;
				ansr[me.id]=i;st.erase(lp);
			}
		}
		for(register int i=1;i<=m;i++)print(ansl[i]),putchar(' '),print(ansr[i]),putchar('\n')；
	}
}
int main(){
	ywy::ywymain();return(0);//再见程序
}
```

---

## 作者：¶凉笙 (赞：16)

## [题解] [CERC2017]Intrinsic Interval

> [点此看题](https://www.luogu.com.cn/problem/P4747)

> 如果你做过类似的一类模型题，你确实会认为这道思维题，其实就是一道套路题。

### 建模

见到此类**给你一些区间，求解合法区间**个数或者是什么的问题，可以往这里想。

1. 把询问区间按照右端点排序。

2. 从左到右依次枚举右端点，用数据结构来维护左端点。

当然，最重要的是第二步，第一步是**离线思想**，第二步是**统计思想**。

通常，在并非特别复杂的情况下，第二步的数据结构采用线段树即可，但具体的不是用什么，而是怎么维护。

那么就需要发现题目性质：本征区间为**极差减去区间长度等于 $-1$ 的且包含询问区间的一个区间**，或者说，满足 $max-min=r-l$，注意 $r-l$ 并不是区间长度。

发现这个关键性质，就可以考虑线段树维护这个东西了。
$$
max-min-(r-l)\geq0
$$
当取等时，这就是一个合法的左端点，因此可以维护这个东西的最小值来判断。

这个模型关键的是第三步：

3. 考虑加入当前右端点对已有的左端点的影响。

通俗的讲，加入当前右端点 $r$ 后，之前所有的 $[l,r-1]$ 的区间都会扩展一个单位，这需要我们在线段树上更新左端点的信息，也就是更新 $max,min,(r-l)$ 这三个信息。

$r-l$ 不用说，肯定是 $+1$，那么整个维护的值 $-1$。

对于 $max,min$ 的维护，设 $l_1,l_2$ 依次为 $r$ **从右往左数第一个比 $a_r$ 大和比 $a_r$ 小的位置**，对于这类问题，可以用单调栈维护（比较常见）。

那么处于 $[l_1+1,r]$ 的这部分左端点，它们到右端点 $r$ 的最大值都会取到 $a_r$，可以在维护单调栈的时候进行撤销，然后再把 $a_r$ 的值更新进去。

具体来说，对于单调栈（不妨设单调递减）中相邻的两个点 $u,v$，$[u+1,v-1]$ 这一段的值均 $\leq a_v$ .

在维护单调栈单调性的同时，顺便维护一下撤销的东西即可。

最后就是查询，有一个结论是：

**如果当前的 $r$ 对应于一个合法的最大的 $l$，那么这个 $[l,r]$ 就是最小的区间。**

证明自己反证法证一下。

而这个题也可以有一个变式：

如果不是排列了怎么办？

借用 HH的项链 的思想，**区间数颜色的关键在于在最后一次出现的位置统计答案**，因此记录 $last$ 更换一下 $r-l$ 的维护即可。

[Continuous Intervals](https://codeforces.com/gym/102222/problem/L)，可以说是加强版，需要区间数颜色并且维护合法区间的个数。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
inline T read(){
	T x=0;char ch=getchar();bool fl=false;
	while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return fl?-x:x;
}
#include <vector>
#include <set>
const int maxn = 1e5 + 10;
#define Pair pair<int,int>
#define mp make_pair
namespace Tree{
struct tree{
	int l,r;
	int mn,tag;
}t[maxn<<2];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
inline void pushup(int p){
	t[p].mn=min(t[ls].mn,t[rs].mn);
}
inline void pushdown(int p){
	if(!t[p].tag)return ;
	t[ls].mn+=t[p].tag;t[rs].mn+=t[p].tag;
	t[ls].tag+=t[p].tag;t[rs].tag+=t[p].tag;
	t[p].tag=0;
}
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r)return t[p].mn=l,void();
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(p);
}
void update(int p,int x,int y,int val){
	int l=t[p].l,r=t[p].r;
	if(x>y)return ;
	if(x<=l && r<=y){
		t[p].mn+=val;t[p].tag+=val;return ;
	}
	pushdown(p);
	if(x<=mid)update(ls,x,y,val);
	if(y>mid)update(rs,x,y,val);
	pushup(p);
}
int query(int p,int x,int y){
	int l=t[p].l,r=t[p].r;
	if(t[p].mn>0)return -1;
	if(l==r)return l;
	pushdown(p);
	if(y>mid && !t[rs].mn){
		int res=query(rs,x,y);
		if(res!=-1)return res;
	}
	if(x<=mid && !t[ls].mn)return query(ls,x,y);
	return -1;
}
}using namespace Tree;
int n,m,a[maxn];
int stk1[maxn],stk2[maxn],top1,top2;
vector<Pair> pos[maxn];
multiset<Pair> s;
Pair ans[maxn];
#define read() read<int>()
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=read();
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		pos[r].emplace_back(l,i);
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int x,y;
		while(top1 && a[stk1[top1]]<a[i]){
			y=stk1[top1];top1--;
			x=stk1[top1]+1;
			update(1,x,y,-a[y]);
		}
		x=stk1[top1]+1;y=i;
		update(1,x,y,a[y]);
		stk1[++top1]=i;
		while(top2 && a[stk2[top2]]>a[i]){
			y=stk2[top2];top2--;
			x=stk2[top2]+1;
			update(1,x,y,a[y]);
		}
		x=stk2[top2]+1;y=i;
		update(1,x,y,-a[y]);
		stk2[++top2]=i;
		update(1,1,n,-1);
		for(auto x:pos[i])s.insert(x);
		while(s.size()){
			auto it=s.end();it--;
			int l=it->first,res=query(1,1,l);
			if(res==-1)break;
			s.erase(it);
			ans[it->second].first=res;
			ans[it->second].second=i;
		}
	}
	for(int i=1;i<=m;i++)printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
```



















---

## 作者：AzusaCat (赞：10)

给定一个长为 $n$ 的排列，有 $q$ 次询问，每次询问包含位置区间 $[l,r]$ 的长度最短的连续段是多少，连续段的定义为排序后值域连续，可以证明解存在且唯一。$n,q\leqslant 10^5$。

引理：若两个连续段有交，则它们的交也是连续段。
证明：从值域上考虑，两个区间的交还是一个区间。

我们给出一个暴力做法：对每个询问 $[l,r]$，从左向右枚举答案的右端点，如果存在以当前右端点为右端点，包含询问区间的连续段，取最短的作为答案即可。
正确性证明：首先我们一定可以得到答案，考虑反证，设得到的答案为 $[l_1,r_1]$，实际答案为 $[l_2,r_2]$：

- 若 $r_1\geqslant r_2$，根据算法过程我们会找到 $[l_2,r_2]$。
- 若 $r_1<r_2$，则有 $l\geqslant l_2>l_1$，由引理可知 $[l_2,r_1]$ 也是一个合法的连续段，矛盾。

这也说明了解的唯一性。

考虑优化这个过程，对询问离线，按右端点从小到大排序，现在右端点从左到右扫描，扫描到某个位置把所有右端点等于当前位置的询问加入到待询问集合中。

注意到一个区间是连续段当且仅当 $mx-mn-len=-1$，三者分别是区间最大/小值和区间长度。维护一棵线段树，下标表示以该位置为左端点，$mx-mn-len$ 的值，并维护区间最小值和最小值最靠右的位置。考虑右端点向右移动 $1$ 后信息的变化，$mx,mn$ 使用两个单调栈维护，同时在线段树上区间加，$len$ 为区间减 $1$，所以线段树只需要支持区间加。

同时可以发现如果左端点更靠右的当前没有答案，那么靠左的也没有，于是按照左端点从大到小尝试询问，不合法直接 break，询问在线段树上查询最靠右的 $-1$ 即可。复杂度 $O(n\log n+q\log n+q\log q)$。

记得比较要完全！或者用 multiset。

[提交记录](https://www.luogu.com.cn/record/51684531)。

---

## 作者：AKPC (赞：9)

析合树好题，不会的可以去看 [OI wiki](https://oi-wiki.org//ds/divide-combine/)，还是蛮详细的，以下一些定义的解释也在这里面。

我们考虑对排列建出析合树。

对于给定的区间 $[l,r]$，不难发现包含 $[l,r]$ 的最短**本原连续段**即析合树上 $[l,l]$ 与 $[r,r]$ 对应节点的 $\text{lca}$，且是唯一的。这个很显然，因为关于本排列的所有**本原连续段**要么互相包含，要么互无交集。

那么需要考虑通过**本原连续段** $[a,b]$ 找到答案，可以分类讨论处理：

- 如果 $[a,b]$ 对应节点是**析点**，因为析点儿子序列所有长度 $\geq2$ 的**严格**子段均不为连续段，且如果可以找到长度 $=1$ 的连续段，那么 $[a,b]$ 就不可能为 $[l,l]$ 和 $[r,r]$ 的 $\text{lca}$。故不存在儿子序列的**严格**子段为答案，答案只能是 $[a,b]$。
- 如果是**合点**，可以在排序后的儿子序列上二分，令 $a'$ 为儿子序列从右往左第一个满足左端点 $\leq a$ 的儿子的左端点，$b'$ 为儿子序列从左往右第一个满足右端点 $\geq b$ 的儿子的右端点。显然，$a',b'$ 可以二分，答案为 $[a',b']$。

时间复杂度 $\Theta(n\log n)$，[code](/paste/k3xio68s)。

---

## 作者：__er (赞：6)

析合树解法，缺点是代码确实有点长，优点是基于析合树看这个问题就变得非常显然了。

析合树是一种方便处理**连续段**$^1$相关问题的数据结构，我们简单介绍一下流程：

对于给定的序列，连续段的数量是 $O(n^2)$ 的，显然不可能用 $O(n^2)$ 的连续段来构造析合树，于是引入**本原连续段**$^2$，容易发现，如果两个连续段之间没有包含关系，那么他们一定各自独立，且**任意一个连续段都可以被一个或多个本原连续段组成**，由于原序列是 $1 \sim n$ 的一个排列，故原序列也是一个本原连续段，而且是所有本原连续段中最大的那个。

于是以原序列为根节点，其他本原连续段为其他结点，包含关系作为边，建得一棵析合树，注意现在的结点不再是一个数而是一个区间，单个数 $x$ 可以看成形如 $[x,x]$ 的区间。

- 合点：将一个结点的儿子结点按值域离散化后组成的排列有序，则这个结点为合点。

- 析点：不满足合点性质的点。

使用增量法建树，时间复杂度 $O(n \log n)$。

考虑用一个栈维护前 $i-1$ 个结点（注意栈中的结点数目不一定为 $i-1$），对于第 $i$ 个结点：

1. 尝试与栈顶结点连边，如果可以连边则结束，将栈顶结点当作第 $i$ 个结点考量。
2. 尝试与栈顶结点合并，如果可以合并则结束，将合并后的结点当作第 $i$ 个结点考量。

连边很简单，考虑合并操作：

首先考虑另一个问题：我如何知道一个子段是连续段？

通过连续段的定义，我们很容易推出判定条件：区间极差与区间长度的差为 $-1$。

不难想到使用 ST表 维护这个区间极差，时间复杂度 $O(n\log n)-O(1)$。

显然这样维护静态区间是很好处理的，但是增量的过程中，区间是在不断变化的，这样单纯寻找这样一个条件就不现实了。

对它进行一个移项，令 $q_k$ 为区间 $[k,i]$ 中极差与区间长度的差再减一，这样我们的条件就变成了 $q_k=0$。

令 $pos$ 为满足这个条件且包含当前结点所表示区间的左端点最大值，发现这个形式很像单调栈，于是增量的过程使用单调栈来维护。要获取这个 $pos$，只需要知道 $q$ 中满足 $q_i=0$ 的 $i$ 的最大值即可。查询 $q_i=0$ 可以变为查找 $q_i$ 的最小值，$pos$ 即为这个最小值所在的位置。

当下次增量操作开始，所有存储的区间长度均会增加一，所以我们对 $q$ 全体减一来维护，既要查询最小值，又要区间减，于是考虑使用线段树来维护 $q$。

最后具体到这个题目来说，我们找到给定 $l_i,r_i$ 所对应结点的 $\rm LCA$。如果此结点为合点，答案为 $l_i,r_i$ 对应形成的儿子区间；如果此节点为析点，答案即为它所对应的区间。

$Code:$
```cpp
#include <bits/stdc++.h>
int n, m, tx, ty, a[100001];
int min[400001], lazy[400001];
struct SegmentTree {
    inline int ls(int &x) {return x << 1;}
    inline int rs(int &x) {return x << 1 | 1;}
    void maintain(int x, int val) {min[x] += val, lazy[x] += val;}
    void pushup(int x) {min[x] = std::min(min[ls(x)], min[rs(x)]);}
    void pushdown(int x) {maintain(ls(x), lazy[x]), maintain(rs(x), lazy[x]), lazy[x] = 0;}
    void modify(int x, int l, int r, int ql, int qr, int val) {
        if (l > ql || r < qr)return;
        if (l >= ql && r <= qr) {return maintain(x, val);}
        pushdown(x); int mid = l + r >> 1;
        if (qr <= mid)modify(ls(x), l, mid, ql, qr, val);
        else if (ql > mid)modify(rs(x), mid + 1, r, ql, qr, val);
        else modify(ls(x), l, mid, ql, mid, val), modify(rs(x), mid + 1, r, mid + 1, qr, val);
        pushup(x);
    }
    void modify(int x, int y, int val) {modify(1, 1, n, x, y, val);}
    int query_pos(int x, int l, int r) {
        if (l == r)return l;
        pushdown(x); int mid = l + r >> 1;
        if (!min[ls(x)])return query_pos(ls(x), l, mid);
        else return query_pos(rs(x), mid + 1, r);
    }
} seg;
struct STRMQ {
    int max[100001][21], min[100001][21];
    void init() {
        for (int i = 1; i <= n; i++)max[i][0] = min[i][0] = a[i];
        for (int j = 1; j <= 20; j++)for (int i = 1; i <= n - (1 << j) + 1; i++)max[i][j] = std::max(max[i][j - 1], max[i + (1 << (j - 1))][j - 1]), min[i][j] = std::min(min[i][j - 1], min[i + (1 << (j - 1))][j - 1]);
    }
    int query_range(int l, int r) {
        int k = std::__lg(r - l + 1);
        return std::max(max[l][k], max[r - (1 << k) + 1][k]) - std::min(min[l][k], min[r - (1 << k) + 1][k]);
    }
} ST;
struct LCA {
    std::vector<int> g[200001];
    int dep[200001], fa[200001][21];
    void dfs(int u) {
        for (int i = 1; (1 << i) <= dep[u]; i++)fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (auto v : g[u])dep[v] = dep[u] + 1, fa[v][0] = u, dfs(v);
    }
    int calc(int u, int d) {
        for (int i = 0; i <= 20 && d; i++)if ((1 << i)&d)d ^= (1 << i), u = fa[u][i];
        return u;
    }
    int lca(int u, int v) {
        if (dep[u] < dep[v])std::swap(u, v);
        u = calc(u, dep[u] - dep[v]);
        if (u == v)return u;
        for (int i = 20; ~i; i--)if (fa[u][i] != fa[v][i])u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
} lca;
int l[200001], r[200001], q[200001], id[200001], st[100001], st1[100001], st2[100001], tp, tp1, tp2, c, pos, cur, root;
std::bitset<200001> type;
struct DividingAndConquer {
    inline bool valid(int l, int r) {return (ST.query_range(l, r) == (r - l));}
    void build() {
        for (int i = 1; i <= n; i++) {
            for (; tp1 && a[i] <= a[st1[tp1]]; tp1--)seg.modify(st1[tp1 - 1] + 1, st1[tp1], a[st1[tp1]]);
            for (; tp2 && a[i] >= a[st2[tp2]]; tp2--)seg.modify(st2[tp2 - 1] + 1, st2[tp2], -a[st2[tp2]]);
            seg.modify(st1[tp1] + 1, i, -a[i]), seg.modify(st2[tp2] + 1, i, a[i]), st1[++tp1] = st2[++tp2] = i;
            id[i] = ++c, l[c] = r[c] = i, pos = seg.query_pos(1, 1, n), cur = c;
            while (tp && l[st[tp]] >= pos) {
                if (type[st[tp]] && valid(q[st[tp]], i))r[st[tp]] = i, q[st[tp]] = l[cur], lca.g[st[tp]].push_back(cur), cur = st[tp--];
                else if (valid(l[st[tp]], i))type[++c] = true, l[c] = l[st[tp]], r[c] = i, q[c] = l[cur], lca.g[c].push_back(st[tp--]), lca.g[c].push_back(cur), cur = c;
                else {
                    lca.g[++c].push_back(cur);
                    do lca.g[c].push_back(st[tp--]); while (tp && !valid(l[st[tp]], i));
                    l[c] = l[st[tp]], r[c] = i, lca.g[c].push_back(st[tp--]), cur = c;
                }
            }
            st[++tp] = cur, seg.modify(1, i, -1);
        }
        root = st[1];
    }
    std::pair<int, int> query(int ql, int qr) {
        int x = id[ql], y = id[qr], L = lca.lca(x, y);
        if (type[L])ql = l[lca.calc(x, lca.dep[x] - lca.dep[L] - 1)], qr = r[lca.calc(y, lca.dep[y] - lca.dep[L] - 1)];
        else ql = l[L], qr = r[L];
        return std::make_pair(ql, qr);
    }
} dividing;
signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; i++)std::cin >> a[i];
    ST.init(), dividing.build(), lca.dfs(root);
    for (std::cin >> m; m; m--) {
        std::cin >> tx >> ty;
        auto [ansl, ansr] = dividing.query(tx, ty);
        std::cout << ansl << " " << ansr << "\n";
    }
    return 0;
}
```
连续段$^1$：值域连续的区间，即 $[l,r]$ 满足 $\nexists x,y \in [l,r],k \notin [l,r],a_x<a_k<a_y$。

本原连续段$^2$：对于一个连续段，如果在原序列中所有的连续段中，不存在其他的连续段和它相交且并不属于它，那么认为这个连续段是本原连续段。

---

## 作者：zhengrunzhe (赞：5)

提供一个**析合树**

处理连续段问题的利器

具体学习可以看[oiwiki](https://oi-wiki.org/ds/divide-combine/)写的非常详细

用到了一个$st$表，一个线段树，一个能找$lca$的玩意和三个单调栈

然后我就写了$class$套$class$套$struct$还指针的吊炸天封装

找$lca$的玩意我用了树剖，同时还要找到一个点到$lca$路径上，从$lca$倒着数的第二个点记作$pre(x,lca)$

对于一个询问$[l,r]$，找到$l$,$r$在析合树上的点$l->x$,$r->y$，然后找到$z=lca(x,y)$，如果z是合点，答案是$[L[pre(x,z)],R[pre(y,z)]]$
```cpp
#include<cstdio>
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const type min(const type &a,const type &b)
{
	return a<b?a:b;
}
const int N=1e5+10;
int n,m,a[N];
class Divide_Combine_Tree
{
	private:
		template<int maxn,int logn>class ST_Table
		{
			private:
    			int log2[maxn],pow2[logn],mn[maxn][logn],mx[maxn][logn];
    		public:
  				inline const void build(int n,int *a)
				{
    				for (int i=pow2[0]=1;i<logn;i++)pow2[i]=pow2[i-1]<<1;
    				for (int i=2;i<=n;i++)log2[i]=log2[i>>1]+1;
    				for (int i=1;i<=n;i++)mn[i][0]=mx[i][0]=a[i];
    				for (int j=1;j<logn;j++)
      				for (int i=1;i+pow2[j]-1<=n;i++)
	        			mn[i][j]=min(mn[i][j-1],mn[i+pow2[j-1]][j-1]),
    		    		mx[i][j]=max(mx[i][j-1],mx[i+pow2[j-1]][j-1]);
  				}
	  			inline const int querymin(int l,int r)
  				{
  					int k=log2[r-l+1];
  					return min(mn[l][k],mn[r-pow2[k]+1][k]);
  				}
  				inline const int querymax(int l,int r)
  				{
		  			int k=log2[r-l+1];
  					return max(mx[l][k],mx[r-pow2[k]+1][k]);
	  			}
		};
		ST_Table<N,17>st;
		class Segment_Tree
		{
			private:
				struct tree
				{
					int mn,add;
					tree *lson,*rson;
					inline const void plus(int w)
					{
						mn+=w;add+=w;
					}
					inline const void pushup()
					{
						mn=min(lson->mn,rson->mn);
					}
					inline const void pushdown()
					{
						if (add)
							lson->plus(add),
							rson->plus(add),
							add=0;
					}
					inline const void update(int l,int r,int L,int R,int w)
					{
						if (l>R||r<L)return;
						if (l>=L&&r<=R)return plus(w);
						pushdown();
						int mid=l+r>>1;
						lson->update(l,mid,L,R,w);
						rson->update(mid+1,r,L,R,w);
						pushup();
					}
					inline const int query(int l,int r)
					{
						if (l==r)return l;
						pushdown();
						int mid=l+r>>1;
						if (!lson->mn)return lson->query(l,mid);
						else rson->query(mid+1,r);
					}
				}*root,memory_pool[N<<1],*tail;
				inline const void build(tree *&p,int l,int r)
				{
					p=tail++;
					if (l==r)return;
					int mid=l+r>>1;
					build(p->lson,l,mid);
					build(p->rson,mid+1,r);
				}
			public:
				inline const void build()
				{
					tail=memory_pool;build(root,1,n);
				}
				inline const void update(int l,int r,int w)
				{
					root->update(1,n,l,r,w);
				}
				inline const int query()
				{
					return root->query(1,n);
				}
		}sgt;
		template<int maxn>class Heavy_Light_Decomposition
		{
			private:
				int head[maxn],edc,next[maxn],to[maxn],top[maxn],wson[maxn],size[maxn],dep[maxn],fa[maxn],dfn[maxn],dot[maxn];
				inline const void dfs(int p)
				{
					size[p]=1;
					for (int i=head[p];i;i=next[i])
					{
						int son=to[i];
						fa[son]=p;dep[son]=dep[p]+1;
						dfs(son);size[p]+=size[son];
						if (size[son]>size[wson[p]])wson[p]=son;
					}
				}
				inline const void dfs(int p,int tp)
				{
					top[p]=tp;dot[dfn[p]=++*dfn]=p;
					if (wson[p])dfs(wson[p],tp);
					for (int i=head[p];i;i=next[i])
						if (!top[to[i]])
							dfs(to[i],to[i]);
				}
			public:
				inline const void build(int root)
				{
					dfs(root);dfs(root,root);
				}
				inline const void addedge(int u,int v)
				{
					next[++edc]=head[u];to[head[u]=edc]=v;
				}
				inline const int lca(int a,int b)
				{
					while (top[a]^top[b])
						dep[top[a]]>dep[top[b]]
						?a=fa[top[a]]:b=fa[top[b]];
					return dep[a]<dep[b]?a:b;
				}
				inline const int pre(int p,int lca)
				{
					int last=p;
					while (top[p]^top[lca])p=fa[last=top[p]];
					return p==lca?last:dot[dfn[lca]+1];
				}
		};
		Heavy_Light_Decomposition<N<<1>hld;
		inline const bool canmerge(int l,int r)
		{
			return st.querymax(l,r)-st.querymin(l,r)==r-l;
		}
		bool com[N<<1];
		int s1[N],s2[N],s[N],top1,top2,top,id[N],l[N<<1],r[N<<1],m[N<<1];
	public:
		inline const void build()
		{
			st.build(n,a);sgt.build();
    		for (int i=1;i<=n;i++)
			{
    			for (;top1&&a[i]<=a[s1[top1]];top1--)sgt.update(s1[top1-1]+1,s1[top1],a[s1[top1]]);
    			for (;top2&&a[i]>=a[s2[top2]];top2--)sgt.update(s2[top2-1]+1,s2[top2],-a[s2[top2]]);
				sgt.update(s1[top1]+1,i,-a[i]);s1[++top1]=i;
    			sgt.update(s2[top2]+1,i,a[i]);s2[++top2]=i;
    			id[i]=++*id;l[*id]=r[*id]=i;
    			int lm=sgt.query(),now=*id;
    			while (top&&l[s[top]]>=lm)
				{
      				if (com[s[top]]&&canmerge(m[s[top]],i))
					{
						r[s[top]]=i;
						hld.addedge(s[top],now);
						now=s[top--];
						continue;
					}
      				if (canmerge(l[s[top]],i))
      				{
					  	com[++*id]=1;
						l[*id]=l[s[top]];r[*id]=i;m[*id]=l[now];
						hld.addedge(*id,s[top--]);hld.addedge(*id,now);
						now=*id;
						continue;
					}
        			hld.addedge(++*id,now);
        			do hld.addedge(*id,s[top--]);while (top&&!canmerge(l[s[top]],i));
        			l[*id]=l[s[top]];r[*id]=i;
					hld.addedge(*id,s[top--]);
        			now=*id;
    			}
    		s[++top]=now;
    		sgt.update(1,i,-1);
  		}
  		hld.build(s[1]);
  	}
  	inline const void query(int a,int b)
  	{
  		int x=id[a],y=id[b],z=hld.lca(x,y);
  		if (com[z])printf("%d %d\n",l[hld.pre(x,z)],r[hld.pre(y,z)]);
  		else printf("%d %d\n",l[z],r[z]);
  	}
}dct;
int main()
{
	read(n);
	for (int i=1;i<=n;i++)read(a[i]);
	read(m);
	dct.build();
	for (int l,r;m--;)read(l),read(r),dct.query(l,r);
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：4)

## 分析
考虑对于 $[l,r]$，如何求出包住它的长度最短的好区间。

做法就是用一个指针从 $r$ 向右扫，每次查询以当前指针为右端点的最短的能包住 $[l,r]$ 的好区间。

第一个查询到的就是想要的区间。

一定不会存在一个与这个区间交叉的区间更优的情况。

因为这种情况两个区间交叉的部分一定会在之前被查询到。

这样的话就可以把所有的询问离线下来，按照右端点从小到大排序依次处理。

只需要快速地查询长度最短的好区间即可。

这可以用线段树去维护。

我们把线段树的节点定义为以某个点为左端点，以扫到的点为右端点的区间中连续区间的个数。

线段树要维护的信息就是连续区间个数的最小值以及区间加和操作中的 $lazy$ 标记。

每次从右边新加入一个点 $i$ 时，我们把区间 $[1,i]$ 整体加 $1$。

代表此时又多了一个不连续的区间。

此时我们去找 $a[i]+1$ 和 $a[i]-1$ 的位置，如果它们的位置在 $i$ 的左边，我们就把 $[1,wz[a[i]-1]]$ 或者 $[1,wz[a[i]+1]]$ 整体减一，代表包含 $a[i]+1$ 或者 $a[i]-1$ 的区间可以与 $a[i]$ 合并形成一个大区间。

如果一个区间是合法的，那么连续区间个数就是一，线段树上记录的最小值就是一。

在线段树上二分查找即可。

## 代码
``` cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<set>
#define rg register
inline int read(){
	rg int x=0,fh=1;
	rg char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=1e5+5;
struct trr{
	int l,r,mmin,laz;
}tr[maxn<<2];
void push_up(rg int da){
	tr[da].mmin=std::min(tr[da<<1].mmin,tr[da<<1|1].mmin);
}
void push_down(rg int da){
	if(tr[da].laz){
		tr[da<<1].laz+=tr[da].laz;
		tr[da<<1|1].laz+=tr[da].laz;
		tr[da<<1].mmin+=tr[da].laz;
		tr[da<<1|1].mmin+=tr[da].laz;
		tr[da].laz=0;
	}
}
void build(rg int da,rg int l,rg int r){
	tr[da].l=l,tr[da].r=r;
	if(l==r) return;
	rg int mids=(l+r)>>1;
	build(da<<1,l,mids),build(da<<1|1,mids+1,r);
}
void xg(rg int da,rg int l,rg int r,rg int val){
	if(tr[da].l>=l && tr[da].r<=r){
		tr[da].laz+=val,tr[da].mmin+=val;
		return;
	}
	push_down(da);
	rg int mids=(tr[da].l+tr[da].r)>>1;
	if(l<=mids) xg(da<<1,l,r,val);
	if(r>mids) xg(da<<1|1,l,r,val);
	push_up(da);
}
int cx(rg int da,rg int l,rg int r){
	if(tr[da].l!=tr[da].r) push_down(da);
	if(tr[da].l>=l && tr[da].r<=r){
		if(tr[da].mmin==1){
			if(tr[da].l==tr[da].r) return tr[da].l;
			else if(tr[da<<1|1].mmin==1) return cx(da<<1|1,l,r);
			else return cx(da<<1,l,r);
		} else {
			return -1;
		}
	}
	rg int mids=(tr[da].l+tr[da].r)>>1,tmp1=-1,tmp2=-1;
	if(l<=mids) tmp1=cx(da<<1,l,r);
	if(r>mids) tmp2=cx(da<<1|1,l,r);
	if(tmp2!=-1) return tmp2;
	else return tmp1;
}
int n,a[maxn],wz[maxn],ansl[maxn],ansr[maxn],m;
struct jie{
	int l,r,id;
}b[maxn];
bool cmp(rg jie aa,rg jie bb){
	return aa.r<bb.r;
}
struct asd{
	int l,id;
	asd(){}
	asd(rg int aa,rg int bb){
		l=aa,id=bb;
	}
	friend bool operator <(const asd& A,const asd& B){
		if(A.l==B.l) return A.id<B.id;
		return A.l>B.l;
	}
};
std::set<asd> s;
int main(){
	n=read();
	for(rg int i=1;i<=n;i++) a[i]=read();
	for(rg int i=1;i<=n;i++) wz[a[i]]=i;
	m=read();
	for(rg int i=1;i<=m;i++){
		b[i].l=read(),b[i].r=read(),b[i].id=i;
	}
	std::sort(b+1,b+m+1,cmp);
	build(1,1,n);
	rg int now=1;
	for(rg int i=1;i<=n;i++){
		xg(1,1,i,1);
		if(a[i]>1 && wz[a[i]-1]<i) xg(1,1,wz[a[i]-1],-1);
		if(a[i]<n && wz[a[i]+1]<i) xg(1,1,wz[a[i]+1],-1);
		while(now<=m && b[now].r==i){
			s.insert(asd(b[now].l,b[now].id));
			now++;
		}
		while(!s.empty()){
			rg int tmp1=s.begin()->l,tmp2=s.begin()->id,tmp3;
			tmp3=cx(1,1,tmp1);
			if(tmp3==-1) break;
			s.erase(s.begin());
			ansl[tmp2]=tmp3,ansr[tmp2]=i;
		}
	}
	for(rg int i=1;i<=m;i++) printf("%d %d\n",ansl[i],ansr[i]);
	return 0;
}
```

---

## 作者：Rusalka (赞：4)

## CERC2017 Intrinsic Interval



去年做过的题，今天一看居然忘了怎么做。对着自己的代码想了半天才会，然后发现这题很有意思。



#### 简要题意

给定长度为 $n$ 的排列 $P$。

定义 $P$ 的区间 $[L,R]$ 是好区间，当且仅当将 $P_L,P_{L+1},P_{L+2}\dots P_{R}$ 排序后，相邻两个元素之差都为 $1$。

现有 $q$ 次询问，每次询问，包含区间 $l,r$ 的最小的好区间 的左右端点；也即求出 $L,R$，使得：

1. 区间 $[L,R]$ 是好区间；
2. $1 \le L \le l\le r\le R \le n$。

在此基础上使得 $R-L$ 最小。

$n,q \le 10^5$。



### 题解

答案区间显然是存在且唯一的。

首先证明一个性质：

- 若 $[l_1, r_1]$ 和 $[l_2,r_2]$ 都是好区间，且 $l_1 \le l_2 \le r_1 \le r_2$（即两区间有交），则 $[l_1, r_2]$ 也是好区间。

证明：考虑区间 $[l_2,r_1]$，它既包含在 $[l_1,r_1]$ 中元素组成的连续段中，也包含在 $[l_2,r_2]$ 中元素组成的连续段中。于是需要容斥一下：区间 $[l_1, r_2]$ 内，满足 $|P_{i}-P_{j}|=1$ 的无序对 $(i,j)$ 的数量为 $(r_1-l_1) + (r_2-l_2) - (r_1-l_2) = r_2 - l_1$，也即区间 $[l_1, r_2]$ 为好区间。



对于 $P$ 中相邻元素 $P_{i}, P_{i+1}$，考虑求出将 $\min(P_{i},P_{i+1})$ 到 $\max(P_{i},P_{i+1})$ 之间所有元素都包含的最小区间，记作 $ml_{i}$ 和 $mr_i$。通过预处理排名数组的区间最小/最大值即可查询。那么如果询问区间包含 $[i,i+1]$，则 $[ml_i, mr_{i}]$ 都必须包含其中。这可以图论建模，有向边 $x\to y$ 的意义为若 $x$ 在区间中，则 $y$ 也必须在区间中。

那么把 $i$ 向区间 $[ml_i, mr_i]$ 中的所有点连边。则若 $i$ 在区间中，则 $i$ 所在的强连通分量中的结点都必须在区间中。Tarjan + 缩点后，就可以在 DAG 上 拓扑排序或 dfs 求出缩点后每个结点所牵连的区间大小（即选了该结点后，有多大的区间必须被选），把这个区间记为结点的答案区间。

现在考虑一次询问 $[l,r]$。那么根据上面的结论，$[l,l+1], [l+1,l+2]\dots[r-1,r]$ 的对应结点的答案区间的并。维护区间可达的最左端点和最右端点即可查询。



### 代码实现

实现中，建图可以使用线段树优化；区间最小值、最大值、最左端点和最右端点都可以使用 ST 表处理。

``` cpp
#include <cstdio>
#include <iostream>
#include <cstring>

#define minn 0
#define maxx 1

using namespace std;

const int MAXN = 100010;

namespace STtable
{

int lg[MAXN];
inline void getLg(int n)
{
	lg[0] = -1;
	for(int i=1;i<=n;i++)
		lg[i] = lg[i>>1] + 1;
}

int f[2][MAXN][24];
inline void build(int n)
{
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			f[minn][i][j] = min(f[minn][i][j-1], f[minn][i+(1<<j-1)][j-1]);
			f[maxx][i][j] = max(f[maxx][i][j-1], f[maxx][i+(1<<j-1)][j-1]);
		}
}
inline int qrymax(int l, int r)
{
	if(l > r) return 0;
	int k = lg[r-l+1];
	return max(f[maxx][l][k], f[maxx][r-(1<<k)+1][k]);
}
inline int qrymin(int l, int r)
{
	if(l > r) return 0;
	int k = lg[r-l+1];
	return min(f[minn][l][k], f[minn][r-(1<<k)+1][k]);
}

}
using STtable::getLg;
using STtable::build;
using STtable::qrymax;
using STtable::qrymin;

struct edge{
	int ne, to;
}g[MAXN<<3];
int head[MAXN<<2], num = 0;
inline void join(int a, int b)
{
	g[++num].ne = head[a];
	head[a] = num;
	g[num].to = b;
}

int ind[MAXN];

struct node{
	int l, r;
}t[MAXN<<2];
int maxn = 0;
void buildtree(int l, int r, int k)
{
	t[k].l = l; t[k].r = r;
	if(l == r)
	{
		ind[l] = k;
		return ;
	}
	int mid = l+r>>1;
	join(k, k<<1); join(k, k<<1|1);
	buildtree(l, mid, k<<1);
	buildtree(mid+1, r, k<<1|1);
}
void addEdge(int l, int r, int pos, int k)
{
	if(t[k].l >= l && t[k].r <= r)
	{
		if(pos != k) join(pos, k);
		return ;
	}
	int mid = t[k].l+t[k].r>>1;
	if(l <= mid) addEdge(l, r, pos, k<<1);
	if(r >= mid+1) addEdge(l, r, pos, k<<1|1);
}

int dfn[MAXN<<2], low[MAXN<<2], cnt = 0, stk[MAXN<<2], top = 0;
int pos[MAXN<<2], tot = 0;
bool vis[MAXN<<2];

void tarjan(int u)
{
	dfn[u] = low[u] = ++cnt;
	vis[u] = 1;
	stk[++top] = u;
	for(int i=head[u];i;i=g[i].ne)
	{
		int v = g[i].to;
		if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		pos[u] = ++tot;
		vis[u] = 0;
		while(stk[top] != u)
		{
			pos[stk[top]] = tot;
			vis[stk[top]] = 0;
			--top;
		}
		--top;
	}
}
struct newedge{
	int ne, to;
}e[MAXN<<3];
int fir[MAXN<<2];
inline void joinnew(int a, int b)
{
	e[++num].ne = fir[a];
	fir[a] = num;
	e[num].to = b;
}
inline void rebuild()
{
	num = 0;
	for(int u=1;u<=maxn;u++)
	{
		for(int i=head[u];i;i=g[i].ne)
		{
			int v = g[i].to;
			if(pos[u] != pos[v]) joinnew(pos[u], pos[v]);
		}
	}
}

int vl[2][MAXN<<2], nw[2][MAXN<<2];

void dfs(int u)
{
	if(vis[u]) return ;
	vis[u] = 1;
	for(int i=fir[u];i;i=e[i].ne)
	{
		int v = e[i].to;
		dfs(v);
		nw[minn][u] = min(nw[minn][u], nw[minn][v]);
		nw[maxx][u] = max(nw[maxx][u], nw[maxx][v]);
	}
}

int n, m, p[MAXN], tmp[MAXN];

int main()
{
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]);
	buildtree(1, n, 1);
	getLg(n);
	for(int i=1;i<=n;i++)
		STtable::f[minn][p[i]][0] = STtable::f[maxx][p[i]][0] = i;
	build(n);
	maxn = (n<<2)-1;
	for(int i=1;i<n;i++)
	{
		int x = min(p[i], p[i+1]), y = max(p[i], p[i+1]);
		vl[minn][i] = qrymin(x, y);
		vl[maxx][i] = qrymax(x, y);
		addEdge(vl[minn][i], vl[maxx][i]-1, ind[i], 1);
	}
	for(int i=1;i<=maxn;i++)
		if(!dfn[i]) tarjan(i);
	rebuild();
	for(int i=1;i<=tot;i++)
		nw[minn][i] = n+1, nw[maxx][i] = 0;
	for(int i=1;i<n;i++)
	{
		nw[minn][pos[ind[i]]] = min(nw[minn][pos[ind[i]]], vl[minn][i]);
		nw[maxx][pos[ind[i]]] = max(nw[maxx][pos[ind[i]]], vl[maxx][i]);
	}
	memset(vis, 0, sizeof(vis));
	for(int i=1;i<=tot;i++)
		dfs(i);
	for(int i=1;i<n;i++)
		for(int j=0;j<2;j++)
			STtable::f[j][i][0] = nw[j][pos[ind[i]]];
	build(n-1);
	scanf("%d",&m);
	while(m--)
	{
		int l, r;
		scanf("%d%d",&l,&r);
		if(l == r) printf("%d %d\n",l,r);
		else printf("%d %d\n",qrymin(l, r-1),qrymax(l, r-1));
	}
	return 0;
}
```



---

## 作者：kai586123 (赞：3)

欢迎来博客踩踩[Baka's Blog](https://baka.online/cerc2017intrinsic-interval-tarjan%e7%ba%bf%e6%ae%b5%e6%a0%91%e5%bb%ba%e5%9b%be/)

这里是i207M神犇提到的线段树建图+缩点的做法。

感谢[fwat的题解](https://www.cnblogs.com/yqgAKIOI/p/10087038.html)，不过他写的太简略了，这篇题解略微详细一些。

我们考虑位置$i-1,i$，它们的值分别为$val[i-1],val[i]$。如果$i-1,i$这两个位置可以出现在一段“好”的区间中，那么，由好区间的定义，$[val[i],val[i+1]]$内的所有值，都需要在区间中出现。即，令$L,R$为$[val[i],val[i+1]]$内的所有值出现位置的左右端点，$[L,R]$都要在区间中出现。

用图中的边表示这个限制关系。$x \to y$的一条边，表示$x$出现的时候，$y$也要出现。

线段树优化建图，然后缩点。在DAG上DFS，求出每个点存在的时候，要求出现区间的范围。

对于一次询问$l,r$，$[l,r]$内每个范围的并就是答案。

这个需要用以下性质证明：

1. 如果有$a \leq b \leq c \leq d$，$[a,c],[b,d]$是好区间，那么$[a,d]$也是好区间。

考虑把好区间内部排序，那么它一定是个差为$1$的等差数列。所以，我们可以认为好区间就是区间内差为$1$的无序对$(i,j)$数量为$r-l$的区间。这么看就显然了。

2. $i-1,i$和$i,i+1$所限制范围是有交的。

由于两端区间有共同的数，这个性质也一定是成立的。

```cpp
#include <bits/stdc++.h>

#define ls(p) p << 1
#define rs(p) p << 1 | 1

inline int rd() {
	int a = 1, b = 0; char c = getchar();
	while (!isdigit(c)) a = c == '-' ? 0 : 1, c = getchar();
	while (isdigit(c)) b = b * 10 + c - '0', c = getchar();
	return a ? b : -b;
}

const int N = 400000 + 2333;

int n, m, val[N], pos[N];

struct Node {
	int l, r;
	Node() { l = 1e9; r = -l; }
	Node(int _l, int _r) {
		l = _l; r = _r;
	}
};

Node operator+(const Node &x, const Node &y) {
	return Node(std::min(x.l, y.l), std::max(x.r, y.r));
}

struct SegTree {
	Node t[N];
	
	void change(int p, int x, Node y, int L, int R) {
		if (L == R) return (void)(t[p] = y);
		int mid = (L + R) >> 1;
		if (x <= mid) change(ls(p), x, y, L, mid);
		else change(rs(p), x, y, mid + 1, R);
		t[p] = t[ls(p)] + t[rs(p)];
	}
	
	Node query(int p, int l, int r, int L, int R) {
		if (l <= L && r >= R) return t[p];
		int mid = (L + R) >> 1;
		if (l <= mid && r > mid)
			return query(ls(p), l, r, L, mid) + query(rs(p), l, r, mid + 1, R);
		if (l <= mid)
			return query(ls(p), l, r, L, mid);
		if (r > mid)
			return query(rs(p), l, r, mid + 1, R);
	}
} seg[2];

std::vector<int> G1[N], G2[N];

void build(int p, int L, int R) {
	if (L == R) return (void)(pos[L] = p);
	int mid = (L + R) >> 1;
	build(ls(p), L, mid);
	build(rs(p), mid + 1, R);
	G1[p].push_back(ls(p));
	G1[p].push_back(rs(p));
}

void addedge(int p, int l, int r, int L, int R, int q) {
	if (l <= L && r >= R) return (void)(G1[q].push_back(p));
	int mid = (L + R) >> 1;
	if (l <= mid) addedge(ls(p), l, r, L, mid, q);
	if (r > mid) addedge(rs(p), l, r, mid + 1, R, q);
}

Node t1[N], t2[N];

int dfn[N], low[N], ins[N], scc[N], stk[N], top, cnt, num;

void tarjan(int x) {
	dfn[x] = low[x] = ++num;
	ins[stk[++top] = x] = 1;
	for (auto y : G1[x]) {
		if (!dfn[y]) {
			tarjan(y);
			low[x] = std::min(low[x], low[y]);
		} else if (ins[y])
			low[x] = std::min(low[x], dfn[y]);
	}
	if (low[x] == dfn[x]) {
		int y; ++cnt;
		do {
			ins[y = stk[top--]] = 0;
			scc[y] = cnt;
		} while (x != y);
	}
}

bool vis[N];

void dfs(int x) {
	if (vis[x]) return;
	vis[x] = 1;
	for (auto y : G2[x]) {
		dfs(y);
		t2[x] = t2[x] + t2[y];
	}
}

int main() {
	n = rd(); build(1, 1, n);
	for (int i = 1; i <= n; ++i)
		val[i] = rd();
	for (int i = 1; i <= n; ++i)
		seg[0].change(1, val[i], { i, i }, 1, n);
	for (int i = 2; i <= n; ++i) {
		int x = std::min(val[i - 1], val[i]), y = std::max(val[i - 1], val[i]);
		t1[pos[i]] = seg[0].query(1, x, y, 1, n);
		addedge(1, t1[pos[i]].l + 1, t1[pos[i]].r, 1, n, pos[i]);
	}
	for (int i = 1; i < N; ++i)
		if (!dfn[i]) tarjan(i);
	for (int x = 1; x < N; ++x)
		for (auto y : G1[x]) if (scc[x] != scc[y])
			G2[scc[x]].push_back(scc[y]);
	for (int i = 1; i < N; ++i)
		t2[scc[i]] = t2[scc[i]] + t1[i];
	for (int i = 1; i <= cnt; ++i)
		dfs(i);
	for (int i = 2; i <= n; ++i)
		seg[1].change(1, i, t2[scc[pos[i]]], 1, n);
		
	m = rd();
	while (m--) {
		int l = rd(), r = rd();
		if (l == r) {
			printf("%d %d\n", l, r);
			continue;
		}
		Node ans = seg[1].query(1, l + 1, r, 1, n);
		printf("%d %d\n", ans.l, ans.r);
	}
	return 0;
}
```



---

## 作者：FZzzz (赞：2)

很有意思的一个题。

下面把题目中所提到的区间称为好区间。

首先看到题你可能会比较懵，为啥答案是唯一的呢？

考虑两个符合条件的好区间，然后你会发现他们的交也会符合条件。

也就是说如果我们的答案区间的右端点左边必定不存在任何一个点，使得存在一个以这个点为右端点的好区间能覆盖我们的询问区间。

那我们离线扫描线，维护以当前点为右端点的所有好区间。

怎么维护呢比较套路，你可以去看 CF526F 的题解。

所有的在这个位置第一次被覆盖的询问就可以直接计算答案，在线段树上二分出它左边第一个满足条件的好区间的左端点即可。

这里顺便讲一下怎么在线段树上区间二分：比较暴力的做法就是先找到被这个区间覆盖的所有节点，然后一个个枚举，枚举到第一个里面有符合条件的位置的话就在这个节点线段树二分。

那我们的难点就主要集中在如何找出所有可以直接处理答案的询问。这里我想了挺久。

建一个堆存下右端点在当前扫描到的点左边的所有询问，按询问左端点排序。然后线段树上可以维护最左边的好区间左端点。每次一直取堆顶直到堆顶询问的左端点小于最左的好区间端点即可。
```cpp
#include<queue>
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
const int maxn=1e5+5;
int n,m,a[maxn];
struct node{
	int l,r;
	node* ch[2];
	int mn,mmn,add;
	void pushup(){
		if(ch[0]->mn<=ch[1]->mn){
			mn=ch[0]->mn;
			mmn=ch[0]->mmn;
		}
		else{
			mn=ch[1]->mn;
			mmn=ch[1]->mmn;
		}
	}
	node(int l,int r):l(l),r(r),mn(l),mmn(l),add(0){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
		}
	}
	void pushtag(int k){
		add+=k;
		mn+=k;
	}
	void pushdown(){
		ch[0]->pushtag(add);
		ch[1]->pushtag(add);
		add=0;
	}
	void modify(int ql,int qr,int k){
		if(ql<=l&&qr>=r){
			pushtag(k);
			return;
		}
		pushdown();
		if(ql<=ch[0]->r) ch[0]->modify(ql,qr,k);
		if(qr>=ch[1]->l) ch[1]->modify(ql,qr,k);
		pushup();
	}
	void query1(int ql,int qr,vector<node*>& res){
		if(ql<=l&&qr>=r){
			res.push_back(this);
			return;
		}
		pushdown();
		if(ql<=ch[0]->r) ch[0]->query1(ql,qr,res);
		if(qr>=ch[1]->l) ch[1]->query1(ql,qr,res);
	}
	int query2(int x){
		if(l==r) return r;
		pushdown();
		if(ch[1]->mn<=x) return ch[1]->query2(x);
		else return ch[0]->query2(x);
	}
}*rt;
typedef pair<int,int> pii;
vector<pii> q[maxn];
int ansl[maxn],ansr[maxn];
int s1[maxn],top1=0,s2[maxn],top2=0;
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++) a[i]=readint();
	m=readint();
	for(int i=0;i<m;i++){
		int l,r;
		l=readint();
		r=readint();
		q[r].push_back(pii(l,i));
	}
	rt=new node(1,n);
	priority_queue<pii,vector<pii> > pq;
	for(int i=1;i<=n;i++){
		while(top1&&a[i]>a[s1[top1]]){
			rt->modify(s1[top1-1]+1,s1[top1],-a[s1[top1]]);
			top1--;
		}
		rt->modify(s1[top1]+1,i,a[i]);
		s1[++top1]=i;
		while(top2&&a[i]<a[s2[top2]]){
			rt->modify(s2[top2-1]+1,s2[top2],a[s2[top2]]);
			top2--;
		}
		rt->modify(s2[top2]+1,i,-a[i]);
		s2[++top2]=i;
		for(int j=0;j<(int)q[i].size();j++) pq.push(q[i][j]);
		while(!pq.empty()&&rt->mmn<=pq.top().first){
			ansr[pq.top().second]=i;
			vector<node*> res;
			rt->query1(1,pq.top().first,res);
			for(int j=(int)res.size()-1;j>=0;j--) if(res[j]->mn<=i){
				ansl[pq.top().second]=res[j]->query2(i);
				break;
			}
			pq.pop();
		}
	}
	for(int i=0;i<m;i++) printf("%d %d\n",ansl[i],ansr[i]);
	return 0;
}
```

---

## 作者：kkksc03wzl (赞：1)

# 真是一道美妙的思维好题

## 前言
今天高三学长给我们讲了这道题目，感觉十分巧妙，写一篇题解记录一下。

## STEP 0 
据说这道题有各种各样的高科技做法，比如说析合树、建图跑，~~但我通通不会。~~ 这里讲一个非常震撼的小清新做法。（其实也是多数人写这道题的做法）

## STEP 1
这种类型的区间要求看上去很不可做，所以我们先考虑把它离线下来，按照一定的扫描顺序去跑。但是具体怎么跑需要我们进一步对“好区间”的性质进行分析。

## STEP 2

### 注意到！
两个好区间的交一定也是个好区间。

因为好区间的下标编号和值域连续的，所以作为连续的序列编号和连续的值域，它们的交也一定会是连续的。

### 注意到！！
一个区间 $[l,r]$ 是好的的等价条件是 $r-l=k$ ，其中 $k$ 是连续数字对的个数。

这个等价条件其实是比较好理解的，~~但是没有逆天注意力谁能想到，，~~

当然，它还有一个等价条件是 $\max-\min=r-l$ ，使用两种不同的条件都可以做出本题，不过实现起来似乎第一个条件更好用一些。

## STEP 3

我们注意了这么多，总该考虑实现了吧。。

因为两个好区间的交也是好区间，所以如果有两个好区间 $[l_1,r_1]$ ，$[l_2,r_2]$，且满足 $l_1 \le l_2, r_1\le r_2$ ,都包含了要询问的区间，那么它们都不可能成为答案，因为它们的交 $[l_2,r_1]$ 是个长度更短且满足条件的好区间。所以我们只需要贪心的找右端点最靠左的可行区间就一定能找到答案。

于是我们以 $r$ 为扫描线，并且开一颗线段树实施维护当前扫描到 $r$ 时，对于每一个可能成为左端点的 $i$ 的$r-i-k$ 其中 $k$ 是对应区间中的连续正整数对的个数。

初始时我们把线段树上每个点赋成 $-i$ ，每扫描一个新的节点就把对应部分先区间加一，然后对于 $r$ 产生的新的连续正整数对的贡献加上。具体实现中有一些细节，都在代码里了（有注释）


```cpp
#include<bits/stdc++.h>
#define lson rt<<1
#define rson rt<<1|1
using namespace std;
int p[100005],ansl[100005],ansr[100005],id[100005];
struct que{
	int l,r,id;
	bool operator<(const que x)const{return l<x.l;}
}a[100005];
bool cmp(que a,que b){return a.r<b.r;}
struct node{int mn,laz,pos;}tr[100005<<2];
//一颗平平常常的记录最小值位置的线段树 
void pushup(int rt){
	tr[rt].mn=min(tr[lson].mn,tr[rson].mn);
	if(tr[rson].mn<=tr[lson].mn)tr[rt].pos=tr[rson].pos;
	else tr[rt].pos=tr[lson].pos;
}void pushdown(int rt){
	int k=tr[rt].laz;
	if(k){
		tr[lson].laz+=k,tr[lson].mn+=k;
		tr[rson].laz+=k,tr[rson].mn+=k;
		tr[rt].laz=0;
	}
}void update(int rt,int l,int r,int x,int y,int k){
	if(x<=l&&r<=y)return tr[rt].laz+=k,tr[rt].mn+=k,void();
	int mid=l+r>>1;
	pushdown(rt);
	if(x<=mid)update(lson,l,mid,x,y,k);
	if(y>mid)update(rson,mid+1,r,x,y,k);
	pushup(rt);
}int query(int rt,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tr[rt].mn==0?tr[rt].pos:-47;
	int ans=-47,mid=l+r>>1;
	pushdown(rt);
	if(x<=mid)ans=max(ans,query(lson,l,mid,x,y));
	if(y>mid)ans=max(ans,query(rson,mid+1,r,x,y));
	return ans;
}void build(int rt,int l,int r){
	tr[rt].laz=0;
	if(l==r)return tr[rt].mn=-l,tr[rt].pos=l,void();
	int mid=l+r>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	pushup(rt);
}priority_queue<que>now;//因为每一次询问的答案的右端点不确定，所以我们要开一个以左端点为序的优先队列 
int main(){
	int n,m;scanf("%d",&n);
	for(int i=1; i<=n; i++)scanf("%d",&p[i]),id[p[i]]=i;//记录排列中每一种数字的出现位置 
	scanf("%d",&m);
	for(int i=1; i<=m; i++)scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
	sort(a+1,a+1+m,cmp);
	int pos=1;
	build(1,1,n);
	for(int r=1; r<=n; r++){
		while(pos<=m&&a[pos].r<=r)now.push(a[pos++]);//把新产生的要处理的询问压到优先队列里 
		update(1,1,n,1,n,1);
		if(p[r]!=1&&id[p[r]-1]<r)update(1,1,n,1,id[p[r]-1],-1);
		if(p[r]!=n&&id[p[r]+1]<r)update(1,1,n,1,id[p[r]+1],-1);//对新产生的连续数对的贡献的计算 
		int tt=now.size();
		for(int i=0; i<tt; i++){
			que t=now.top();
			int as=query(1,1,n,1,t.l);
			if(as>0){//如果答案合法就记录 
				ansl[t.id]=as,ansr[t.id]=r;
				now.pop();
			}else{//否则就直接停掉，因为以左端点为序，所以合法性单调 
				break;
			}
		}
	}for(int i=1; i<=m; i++){
		printf("%d %d\n",ansl[i],ansr[i]);
	}
	return 0;
}//完结撒花 ^_^ 
```

---

## 作者：TTpandaS (赞：0)

建立出析合树后，对于查询 $x,y$，找到节点 $[x,x],[y,y]$ 的最近公共祖先 $a$，那么最后答案区间只会在 $a$ 的儿子这一层组成。

如果 $a$ 为析点，那么儿子们不能合并，所以答案就为 $[L_a,R_a]$。

否则在儿子中找到最大的 $L_b$ 满足 $L_b \leq l$，最小的 $R_c$ 满足 $R_c \geq r$，那么答案就为 $[L_b,R_c]$。

时间复杂度 $O(n \log n)$。

---

## 作者：Luciylove (赞：0)

注意到，**长度不同**的连续段如果有交，那么其是一个连续段。

然后我们注意到这样可以证明直接从左往右找第一个包住指定区间的区间是对的。

所以我们直接模拟这个过程即可，连续段可以按照套路，因为这是一个排列，所以直接使用扫描线 + 单调栈维护 $\max_{[l, r]} - \min_{[l, r]} = r - l$ 的地方。

那怎么找到呢？注意到移项后 $(\max_{[l, r]} - \min_{[l, r]}) - (r - l) \geq 0$，那么你直接维护最小值，然后直接线段树上二分即可。

时间复杂度 $O(n \log n)$。


```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc x << 1
#define rc x << 1 | 1

using namespace std;

typedef long long ll;
const int _ = 1e5 + 5;
int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}

int n, q;
int pL[_ << 2], pR[_ << 2];
int v[_ << 2], ad[_ << 2];

void apply (int x, int k) { v[x] += k, ad[x] += k; }
void pushdown (int x) {
	if (ad[x]) 
		apply(lc, ad[x]), apply(rc, ad[x]), ad[x] = 0;
}
void modify (int x, int l, int r, int ql, int qr, int k) {
	if (ql > qr) return ;
	if (ql <= l && r <= qr) return apply(x, k);
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) modify(lc, l, mid, ql, qr, k);
	if (qr > mid) modify(rc, mid + 1, r, ql, qr, k);
	return v[x] = min(v[lc], v[rc]), void();
}

vector <int> node;
void query (int x, int l, int r, int ql, int qr) {
	if (ql > qr) return ;
	if (ql <= l && r <= qr)  return pL[x] = l, pR[x] = r, node.push_back(x), void();
	int mid = (l + r) >> 1; pushdown(x);
	if (qr > mid)
		query(rc, mid + 1, r, ql, qr);
	if (ql <= mid)
		query(lc, l, mid, ql, qr);
	return ;
}
int queryM (int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return v[x];
	int mid = (l + r) >> 1, ret = 0x3f3f3f3f; pushdown(x);
	if (ql <= mid) ret = min(ret, queryM(lc, l, mid, ql, qr));
	if (qr > mid) ret = min(ret, queryM(rc, mid + 1, r, ql, qr));
	return ret;
}
int find (int x, int l, int r) {
	if (l == r) return l;
	int mid = (l + r) >> 1; pushdown(x);
	if (v[rc] > 0)
		return find(lc, l, mid);
	else 
		return find(rc, mid + 1, r); 
}
int qL (int l) {
	node.clear();
	query(1, 1, n, 1, l);
	for (int x : node) {
		// cout << x << " " << pL[x] << ' ' << pR[x] << endl;
		if (v[x] == 0) return find(x, pL[x], pR[x]);
	}
	return -1;
} 

int a[_], stk1[_], stk2[_], top1, top2;

struct reQuest {
	int l, id;
	bool operator < (const reQuest & x) const {
		return l < x.l;
	}
} ;

vector <reQuest> qv[_];
pair<int, int> ans[_];
priority_queue <reQuest> Q;

int main () {
	n = read();
	rep(i, 1, n) a[i] = read();
	q = read();
	rep(i, 1, q) {
		int l = read(), r = read();
		qv[r].push_back({l, i});
	}
	rep(i, 1, n) {
		modify(1, 1, n, i, i, i);
		modify(1, 1, n, 1, n, -1);


		while (top1 && a[stk1[top1]] > a[i])
			modify(1, 1, n, stk1[top1 - 1] + 1, stk1[top1], a[stk1[top1]]),
			top1 --;
		while (top2 && a[stk2[top2]] < a[i])
			modify(1, 1, n, stk2[top2 - 1] + 1, stk2[top2], -a[stk2[top2]]),
			top2 --;

		modify(1, 1, n, stk1[top1] + 1, i, -a[i]),
		modify(1, 1, n, stk2[top2] + 1, i, a[i]);
		stk1[++ top1] = i,
		stk2[++ top2] = i;

		for (auto x : qv[i]) Q.push(x);
		while (!Q.empty()) {
			auto [l, id] = Q.top();
			l = qL(l);
			if (l == -1) { break ; }
			ans[id] = {l, i}, Q.pop();
		} 
 	}
 	rep(i, 1, q) {
 		auto [l, r]  = ans[i];
 		printf("%d %d\n", l, r);
 	}
	return 0;
}
```

---

