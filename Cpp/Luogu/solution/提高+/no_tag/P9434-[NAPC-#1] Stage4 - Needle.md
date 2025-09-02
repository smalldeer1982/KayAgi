# [NAPC-#1] Stage4 - Needle

## 题目背景

> ![](https://cdn.luogu.com.cn/upload/image_hosting/jiio1vp7.png)
>
> — s10

## 题目描述

平面上有 $n$ 个**位置互不相同**的刺。刺有上下左右这 $4$ 种朝向。

定义一个【阴间刺】（其实就是削过的 sf 刺）为满足以下条件的有序刺**对** $(s_1,s_2,s_3)$：
- $s_1$ 朝右，$s_2$ 朝左，$s_3$ 朝上。
- $x(s_1)<x(s_2)\leqslant x(s_3)$。
- $y(s_2)>y(s_1)>y(s_3)$。
- $x(s_2)-x(s_1)\leqslant d$。

其中 $x(s)$ 和 $y(s)$ 分别表示刺 $s$ 的横坐标和纵坐标；$d$ 为 kid 的宽度，在单组测试点中为常量。

坐标系 $x$ 轴正方向为从左到右，$y$ 轴正方向为从下到上。

![](https://cdn.luogu.com.cn/upload/image_hosting/tzih4wjx.png) ![](https://cdn.luogu.com.cn/upload/image_hosting/4wr5yfhz.png)

上图是 $d\geqslant 2$ 时两个阴间刺的例子。~~虽然第二个刺型中 s3 对 kid 的跳跃没有影响/oh~~

给出 $n$ 个刺的位置和朝向，请你告诉 kid 有多少（他跳不过去的）阴间刺。

显然朝下的刺在本题内是没有意义的。

## 说明/提示

### 【数据范围】

**本题采用捆绑测试。**
$$
\def\r{\cr\hline}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c|c}
\textbf{Subtask} & id= & {\sum n\leqslant} & \textbf{Other Constraints} & \textbf{Score}\r
\textsf1 & 1\sim 7 & 3\times10^4 & n\leqslant 30 & 10 \r
\textsf2 & 31\sim45 & 10^4 & - & 25 \r
\textsf3 & 8\sim10,16\sim17 & 10^5 & d=10^9 & 20 \r
\textsf4 & 18\sim20 & 3\times10^5 & d=1 & 10 \r
\textsf5 & 11\sim15,21\sim30 & 3\times10^5 & - & 35 \r
\end{array}
$$

其中 $\sum n$ 表示单测试点内所有 $n$ 的总和。

对于 $100\%$ 的数据，$1\leqslant T\leqslant 2\times10^3$，$1\leqslant n\leqslant 3\times10^5$，$\sum n\leqslant 3\times10^5$，$1\leqslant d\leqslant 10^9$，$1\leqslant x,y\leqslant 10^9$，$(x,y)$ 互不相同，$c\in\{\texttt U, \texttt D, \texttt L, \texttt R \}$。

#### 【提示】

$\textbf{Sub}{\textsf2}$ 的 $O(n^2\log n)$ 做法和 $O(n^2)$ 做法都可以想想，可能都有些提示性……？qwq

### 【样例 #1-1 & #1-2 解释】

见【题目描述】中**两**幅图。

注意 #1-2 中 $d=1$，所以 kid 可以简单地钻缝过去，不算阴间。

### 【样例 #1-3 解释】

![](https://cdn.luogu.com.cn/upload/image_hosting/ha8w6ljz.png)

$4$ 个阴间刺分别为：$\Big((1,3),(2,4),(2,1)\Big),\Big((1,2),(2,4),(2,1)\Big),\Big((1,2),(2,3),(2,1)\Big),\Big((1,3),(2,4),(3,2)\Big)$
即 $(5,6,1),(2,6,1),(2,4,1),(5,6,3)$（数字代表刺的下标：$i$ 代表第 $i$ 个刺）。

### 【样例 #1-4 解释】

![](https://cdn.luogu.com.cn/upload/image_hosting/q988yxmg.png)

$6$ 个阴间刺分别为 $(2,1,7),(4,1,7),(4,3,6),(4,3,7),(4,3,8),(5,3,8)$。

【样例 #2】见附件，该样例除 $id=0$ 外满足 $\text{Subtask }\textsf1$ 的所有限制。

## 样例 #1

### 输入

```
4 0
3 1
2 1 U
1 2 R
2 3 L
3 1
4 1 U
1 2 R
3 4 L
6 4
2 1 U
1 2 R
3 2 U
2 3 L
1 3 R
2 4 L
8 9
4 5 L
1 4 R
3 4 L
2 3 R
1 2 R
3 2 U
4 2 U
3 1 U
```

### 输出

```
1
0
4
6```

## 样例 #2

### 输入

```
见附件中的 s4/ex.in```

### 输出

```
见附件中的 s4/ex.out```

# 题解

## 作者：Elleryqueen (赞：5)

&emsp;作为验题人，有理由来写一篇题解。

&emsp;首先肯定要先将这些刺进行排序，于是按照直觉以 $x$ 为第一关键字从小到大， $y$ 为第二关键字从大到小排序。然后再来分析题目：令 $s_1(x_1,y_1)$, $s_2(x_2,y_2)$, $s_3(x_3,y_3)$。显然，向下的刺肯定是没用的。我们从 $s_2$ 进行分析，发现对于每个 $s_2$，实际上是要找到其左下角有多少个满足条件的 $s_1$ 且每个 $s_1$ 有多少个 $s_3$ 可以与其匹配。可以知道 $s_1$ 一定在 $s2$ 左下角， $s_3$ 一定在 $s_1$ 右下角，那么可以分别求解，对于每个 $s_2$ 直接求其左下方的矩形 $(x_2-d,-\infty ),(x_2-1,y_2-1)$ 中有多少个 $s_1$ 即可，而对于每个 $s_1$ 的贡献即为其右下方的矩形 $(x_2,y_1-1),(\infty ,-\infty )$ 中 $s_3$ 的数量。每次暴力查询的复杂度肯定是无法接受的，那么我们需要寻找一下优化。可以发现如果按照之前的方法排序，再进行遍历的话，每一行 $s_1$ 的数量是递增的， 每一行 $s_3$ 的数量是递减的，而且查询矩形 $(x_2-d,-\infty ),(x_2-1,y_2-1)$ 的右边界只会一直向右， $(x_2,y_1-1),(\infty,-\infty)$ 的左边界也只会一直向右，那么我们就可以将查询矩形 $x$ 轴的部分压缩掉，每次只用查询 $(-\infty ,y_2-1]$ 和 $[y_1-1,\infty )$ 这两段区间即可。

&emsp;于是可以想到线段树。使用两棵线段树，第一棵用来维护每一行 $s_3$ 个数的变化，第二棵线段树用来维护每一行 $s_1$ 数量的变化以及每一行 $s_1$ 产生的贡献。每一行 $s_1$ 产生的贡献即为 该行 $s_1$ 的个数 $\times$ 区间 $(-\infty,y1_1]$ 中 $s_3$ 的个数。但是，随着遍历时 $s_2$ 的横坐标增大，会有很多 $s_3$ 不再满足 $x_2 \leq x_3$ 的条件，不能算作答案。如何规避这一点呢，不难发现，我们每遍历到一个向上的刺，这个刺就再也不可能作为答案了，因为剩余所有的 $s_2$ 都不会满足 $x_2 \leq x_3$。那么每当我们遇到 $s_3$，就需要减去其之前产生的贡献。考虑可以与其匹配的 $s_1$ , 都在其左上角方，也就是对其左上方每一行中每一个 $s_1$ 都会产生一个贡献，由于我们第二棵线段树维护的是每一行 $s_1$ 产生的贡献，那么每一行新的贡献就相当于是 该行原贡献 $-$ 该行 $s_1$ 的数量。那么每减去一个 $s_3$ 的贡献，就相当于在线段树上做了一遍区间操作而已。

&emsp;最后一个限制就是 $x_2-x_1\leq d$，考虑如何维护。很简单，遍历的同时将 $s_1$ 塞到一个队列里，每次碰到 $s_2$，就拿队头判断，如果队头的 $s_1$ 不满足条件，就减去其贡献，把它弹出，再继续比较，直到队头满足条件即可。单个 $s_1$ 的贡献也很好求，相当于在第一棵线段树中做区间求和，然后在到第二棵线段树上进行单点修改即可。

&emsp;如此看来，遍历所有点的复杂度为 $O(n)$,每个点上会进行的操作皆是在线段树上进行，都是 $O(\log{n})$ 的复杂度，所以总复杂度为 $O(n \log{n})$，虽然常数巨大，但也是能跑过的，其余不懂的就直接看代码吧。

```cpp
#include<bits/stdc++.h>
#define fir first
#define sed second
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
const int N=3e5+10;
int T,id,n,d;
struct node
{
	int xx,yy;
	int type;
	bool operator<(const node aa)const
	{
		if(xx==aa.xx) return yy>aa.yy;
		else return xx<aa.xx;
	}
}a[N];
struct Node
{
	int l,r;
	int si,add_si;
	LL val,add_val;
	int tag;
};
int b1[N],b2[N],c[N];
int tot;
map<int,int> mp1,mp2;
int cnt1,cnt2;
LL ans;
struct Tree
{
	Node tr[N*4];
	void push_up(int pos)
	{
		tr[pos].si=tr[pos<<1].si+tr[pos<<1|1].si;
		tr[pos].val=tr[pos<<1].val+tr[pos<<1|1].val;
	}
	void push_del(int pos,int val)
	{
		tr[pos].val=tr[pos].val-(LL)tr[pos].si*val;
		tr[pos].tag+=val;
	}
	void push_si(int pos,int val)
	{
		tr[pos].si+=val;
		tr[pos].add_si+=val;
	}
	void push_val(int pos,LL val)
	{
		tr[pos].val+=val;
		tr[pos].add_val+=val;
	}
	void push_down(int pos)
	{
		if(tr[pos].tag)
		{
			push_del(pos<<1,tr[pos].tag);
			push_del(pos<<1|1,tr[pos].tag);
			tr[pos].tag=0;
		}
		if(tr[pos].add_si)
		{
			push_si(pos<<1,tr[pos].add_si);
			push_si(pos<<1|1,tr[pos].add_si);
			tr[pos].add_si=0;
		}
		if(tr[pos].add_val)
		{
			push_val(pos<<1,tr[pos].add_val);
			push_val(pos<<1|1,tr[pos].add_val);
			tr[pos].add_val=0;
		}
	}
	void build(int pos,int l,int r)
	{
		if(l>r) return ;
		tr[pos].l=l,tr[pos].r=r;
		tr[pos].si=tr[pos].val=0;
		tr[pos].tag=0;
		if(l==r)
		{
			tr[pos].si=c[l];
			return ;
		}
		int mid=l+r>>1;
		build(pos<<1,l,mid);
		build(pos<<1|1,mid+1,r);
		push_up(pos);
	}
	int query_si(int pos,int l,int r)
	{
		if(tr[pos].l>=l&&tr[pos].r<=r)
			return tr[pos].si;
		push_down(pos);
		int mid=tr[pos].l+tr[pos].r>>1;
		int sum=0;
		if(mid>=l) sum+=query_si(pos<<1,l,r);
		if(mid<r) sum+=query_si(pos<<1|1,l,r);
		return sum; 
	}
	LL query_val(int pos,int l,int r)
	{
		if(tr[pos].l>=l&&tr[pos].r<=r){
			return tr[pos].val;
		}
		push_down(pos);
		int mid=tr[pos].l+tr[pos].r>>1;
		LL sum=0;
		if(mid>=l) sum+=query_val(pos<<1,l,r);
		if(mid<r) sum+=query_val(pos<<1|1,l,r);
		return sum;
	}
	void modify_si(int pos,int xx,int val)
	{
		if(tr[pos].l==xx&&tr[pos].r==xx){
			tr[pos].si+=val;
			return ;
		}
		push_down(pos);
		int mid=tr[pos].l+tr[pos].r>>1;
		if(mid>=xx) modify_si(pos<<1,xx,val);
		else modify_si(pos<<1|1,xx,val);
		push_up(pos);
	}
	void modify_val(int pos,int xx,LL val)
	{
		if(tr[pos].l==xx&&tr[pos].r==xx){
			tr[pos].val+=val;
			return ;
		}
		push_down(pos);
		int mid=tr[pos].l+tr[pos].r>>1;
		if(mid>=xx) modify_val(pos<<1,xx,val);
		else modify_val(pos<<1|1,xx,val);
		push_up(pos);
	}
	void modify(int pos,int l,int r)
	{
		if(tr[pos].l>=l&&tr[pos].r<=r){
			push_del(pos,1);
			return ;
		}
		push_down(pos);
		int mid=tr[pos].l+tr[pos].r>>1;
		if(mid>=l) modify(pos<<1,l,r);
		if(mid<r) modify(pos<<1|1,l,r);
		push_up(pos);
	}
}tr1,tr2;
deque<PII > q;
int main()
{
	scanf("%d %d",&T,&id);
	while(T--)
	{
		tot=0,cnt1=cnt2=0;
		ans=0;
		mp1.clear();
		mp2.clear();
		while(!q.empty()) q.pop_front();
		scanf("%d %d",&n,&d);
		for(int i=1;i<=n;i++)
		{
			int xx,yy;
			char op[3];
			scanf("%d %d",&xx,&yy);
			scanf("%s",op);
			if(op[0]=='R'){
				a[++tot]={xx,yy,1};
				b1[tot]=xx,b2[tot]=yy;
			}
			else if(op[0]=='L'){
				a[++tot]={xx,yy,2};
				b1[tot]=xx,b2[tot]=yy;
			}
			else if(op[0]=='U'){
				a[++tot]={xx,yy,3};
				b1[tot]=xx,b2[tot]=yy;
			}
		}
		sort(a+1,a+1+tot);
		sort(b1+1,b1+1+tot);
		sort(b2+1,b2+1+tot);
		for(int i=1;i<=tot;i++){
			if(i==1||b1[i]!=b1[i-1]) mp1[b1[i]]=++cnt1;
			if(i==1||b2[i]!=b2[i-1]) mp2[b2[i]]=++cnt2;
		}
		for(int i=1;i<=cnt2;i++) c[i]=0;
		tr1.build(1,1,cnt2);
		for(int i=1;i<=tot;i++){
			if(a[i].type==3) c[mp2[a[i].yy]]++;
		}
		tr2.build(1,1,cnt2);
		for(int i=1;i<=tot;i++){
			if(a[i].type==1){
				int u=mp2[a[i].yy];
				if(u==1) continue ;
				int sum=tr2.query_si(1,1,u-1);
				tr1.modify_val(1,u,(LL)sum);
				tr1.modify_si(1,u,1);
				q.push_back(make_pair(a[i].xx,a[i].yy));
			}else if(a[i].type==2){
				while(!q.empty())
				{
					if(a[i].xx-q.front().fir>d){
						int u=mp2[q.front().sed];
						if(u>1){
							int sum=tr2.query_si(1,1,u-1);
							tr1.modify_val(1,u,(LL)sum*-1LL);
							tr1.modify_si(1,u,-1);
						}
						q.pop_front();
					}else break ;
				}
				int u=mp2[a[i].yy];
				if(u==1) continue ;
				LL sum=tr1.query_val(1,1,u-1);
				ans+=sum;
			}else{
				int u=mp2[a[i].yy];
				tr2.modify_si(1,u,-1);
				if(u==cnt2) continue ;
				tr1.modify(1,u+1,cnt2);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Graphcity (赞：1)

不妨把 $s_2$ 看成向下的刺，那么 $s_1,s_2$ 就会产生交点。$s_3$ 唯一的条件就是在这个交点的右下角。

扫描线，从左往右扫描交点并统计贡献。双指针可以找到符合范围的 $s_1$ 和 $s_3$。设 $a_i$ 为当前 $y=i$ 的 $s_1$ 个数，$b_i$ 为当前 $y<i$ 的 $s_3$ 个数，那么对于一个 $y=k$ 的 $s_2$，它射出去的交点能够产生 $\sum_{i=1}^{k-1}a_i\times b_i$ 的贡献。

使用线段树维护 $a_i,b_i$。需要支持单点修改 $a_i$，区间修改 $b_i$，区间查询 $\sum_i a_i\times b_i$ 的值。这个很简单，只要再多维护一个 $\sum_{i}a_i$ 即可。时间复杂度 $O(n\log n)$。

**[Code](https://www.luogu.com.cn/paste/6ty1w14k)**

---

## 作者：ckain (赞：1)

按 $x$ 坐标从小到大顺序扫描。

题目要求合法三元组 $(R, L, U)$ 的个数，我们对于每个 $R$ 维护其组成的合法二元组 $(R, L)$ 个数。  
具体地，发现若扫描到了一个 $L(x_l, y_l)$，它会与之前 $y$ 坐标小于自己的 $R$ 构成二元组。我们对于 $R$ 维护一个以 $y$ 坐标为关键字段平衡树 $T$。那么有 $T$ 中 $y < y_l$ 的节点二元组个数 $+1$。但其实还有限制：二元组 $(R, L)$ 的横坐标距离差不超过 $d$。考虑增加一颗平衡树 $T^{\prime}$。那么每次修改前将 $T$ 中距离 $L$ 超过了 $d$ 的 $R$ 放到 $T^{\prime}$ 中。

然后每次扫描到 $U(x_u, y_u)$ 时，查询 $T$ 和 $T^{\prime}$ 中 $y$ 坐标 $>y_u$ 部分的二元组个数和即可。

code：
```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
const int N=3e5+5;
mt19937 rng(time(0));
#define cl(u) t[u].ls
#define cr(u) t[u].rs
struct Fhq_node{
	int ls, rs, rd;
	pii key;
	int v, s, sz, tg;
} t[N];
int rt1, rt2;
inline void add(int u, int d){
	t[u].v+=d;
	t[u].s+=t[u].sz*d;
	t[u].tg+=d;
}
inline void pu(int u){
	t[u].sz=t[cl(u)].sz+t[cr(u)].sz+1;
	t[u].s=t[cl(u)].s+t[cr(u)].s+t[u].v;
}
inline void pd(int u){
	if(t[u].tg){
		if(cl(u)) add(cl(u), t[u].tg);
		if(cr(u)) add(cr(u), t[u].tg);
		t[u].tg=0;
	}
}

void split(int u, pii k, int &x, int &y){
	if(!u){
		x=y=0;
		return;
	}
	pd(u);
	if(t[u].key<=k){
		x=u;
		split(cr(u), k, cr(u), y);
	}
	else{
		y=u;
		split(cl(u), k, x, cl(u));
	}
	pu(u);
}
int merge(int u, int v){
	if(!u || !v) return u|v;
	if(t[u].rd>t[v].rd){
		pd(u);
		cr(u)=merge(cr(u), v);
		pu(u);
		return u;
	}
	else{
		pd(v);
		cl(v)=merge(u, cl(v));
		pu(v);
		return v;
	}
}

inline int que(int &rt, int _y){
	int L, R, re;
	split(rt, {_y, INT_MAX}, L, R);
	re=t[R].s;
	rt=merge(L, R);
	return re;
}
inline void create(int u, int _x, int _y){
	t[u]={
		0, 0, rng(),
		{_y, _x},
		0, 0, 1, 0
	};
}
inline void Mg(int &rt, int u){
	int L, R;
	split(rt, t[u].key, L, R);
	rt=merge(merge(L, u), R);
}
#undef cl
#undef cr

int T, id, n, d;

const int Key[]={0, 3, 1, 2};
struct node{
	int x, y, opt;
	inline bool operator <(const node &o)const{
		return (x!=o.x)? x<o.x:Key[opt]<Key[o.opt];
	}
} p[N];

queue<int> q;

signed main(){
	T=rd(), id=rd();
	while(T--){
		int n=rd(), d=rd();
		for(int i=1; i<=n; i++){
			p[i].x=rd(), p[i].y=rd();
			char ch;
			cin>>ch;
			if(ch=='R') p[i].opt=1;
			else if(ch=='L') p[i].opt=2;
			else if(ch=='U') p[i].opt=3;
			else p[i].opt=0;
		}
		sort(p+1, p+1+n);
		int sum=0;
		queue<int> q;
		for(int i=1; i<=n; i++){
			if(!p[i].opt) continue;
			int x=p[i].x, y=p[i].y;
			if(p[i].opt==1){
				create(i, x, y);
				Mg(rt1, i);
				q.push(i);
			}
			else if(p[i].opt==2){
				while(q.size()){
					int u=q.front();
					if(p[u].x<x-d){
						int L, R, Md;
						pii _key={p[u].y, p[u].x};
						split(rt1, _key, L, R);
						split(L, {_key.fr, _key.sc-1}, L, Md);
						Mg(rt2, Md);
						rt1=merge(L, R);
						q.pop();
					}
					else break;
				}
				int L, R;
				split(rt1, {y-1, INT_MAX}, L, R);
				if(L) add(L, 1);
				rt1=merge(L, R);
			}
			else{
				int ans=que(rt1, y)+que(rt2, y);
				sum+=ans;
			}
		}
		printf("%lld\n", sum);
		
		for(int i=1; i<=n; i++){
			t[i]={
				0, 0, 0,
				{0, 0},
				0, 0, 0, 0
			};
		}
		while(q.size()) q.pop();
		rt1=rt2=0;
	}
	return 0;
}

```

---

## 作者：y_kx_b (赞：1)

## Stage4 - Needle

预计难度：\*2300 左右，蓝。

前置芝士：线段树。

~~说实话，照理来说这个阴间刺是纵横+珠峰，照理来说纵横的话应该更窄才对（也就是说，照理应该 $x(s_1)<x(s_3)\leqslant x(s_2)$ 才对）但是也不知道为啥，可能最近脑子一直不太清醒吧 qwq。~~


---

### $\textbf{Sub }{\sf1}\textbf:$ $n\leqslant30$。
直接 $n^3$ 暴力枚举然后判断是否合法即可。

有个小常数暴力做法就是先把刺分类然后扫，常数差不多是 $\dfrac1{27}$ 的样子？

（其实下面的做法都有个差不多 $\dfrac1{27}$ 的常数，因为 $n$ 个刺包含了三种刺，每种刺数量可以看作是 $\dfrac n3$ 的。时间复杂度是这三种刺数量的乘积，$abc\leqslant\left(\frac{a+b+c}3\right)^3$，所以每种刺的数量越偏离 $\dfrac n3$ 代码就会跑得越快（）。）

### $\textbf{Sub ?:}$ $O(n^2\log^2n)$。

首先观察这个条件：

- $x(s_1)<x(s_2)\leqslant x(s_3)$。
- $y(s_2)>y(s_1)>y(s_3)$。
- $x(s_2)-x(s_1)\leqslant d$。

然后可以发现可以枚举 $s_1$ 和 $s_2$，可以快速得到符合要求的 $s_3$ 数量。

可以离散化之后用二维线段树啥的统计（？）

不知道，没写过，也懒得写了。~~反正这题解也是比赛前半天赶出来的（不是）。~~

### $\textbf{Sub }{\sf2}\textbf:$ $O(n^2\log n)$。
考虑枚举 $s_1$ 和 $s_2$ 之后相当于就是算 $x$ 比某个值大且 $y$ 比某个值小的点（$s_3$）的数量。

发现挺像二维偏序，于是把每对合法的 $(s_1, s_2)$ 二元组都抽象成一个点进行二维偏序。那么以 $x$ 从大到小排序，$y$ 从小到大排序，离散化纵坐标然后直接树状数组即可。

时间复杂度是 $O(n^2\log n)$，不过感觉和下面这个 $O(n^2)$ 跑的差不多快，懒得卡了，摆烂！

这个做法唯一缺点就是空间复杂度是 $O(n^2)$ 的，~~差点没在本地编译成功。~~

[code](https://www.luogu.com.cn/paste/7acgwh2j).

---
\* 我们直入主题吧。
### $\textbf{Sub }{\sf2}\textbf:$ $\sum n\leqslant10^4$（$O(n^2)$）。

观察这个条件：

- $x(s_1)<x(s_2)\leqslant x(s_3)$。
- $y(s_2)>y(s_1)>y(s_3)$。
- $x(s_2)-x(s_1)\leqslant d$。

受上面的 $O(n^2\log n)$ 启发我们把刺按 $x$ 坐标排序，然后从左往右进行处理（如同一横坐标上有多个刺则这些刺从上到下处理）。

那么这时第一个条件显然满足，然后发现 $s_2$ 和 $s_3$ 中间是没有任何与 $s_1$ 无关的限制的。也就是说，我们可以把 $s_2$ 和 $s_3$ 分开统计：

遇到一个 $s_2$ 时把它下面并且横坐标与其不超过 $d$ 的所有遇到过的 $s_1$ 打上一层标记（可以叠加）。这个标记的含义是：这个 $s_1$ **当前**已经和上面多少个 $s_2$ 配对。

这样的话，遇到 $s_3$，只需要统计它上面的所有遇到过的 $s_1$ 的标记数量之和就可以了。为什么呢？考虑固定 $s_3$ 和它上面的一个 $s_1$，此时贡献就是合法的 $s_2$ 数目。容易发现这个数目仅与 $s_1$ 有关（前提是 $x(s_1)<x(s_2)\leqslant x(s_3)$ 也就是说我们有序处理每个刺），所以上述方法是正确的。

（遇到过的 $s_1$ 指 被扫到过的。因为没扫到的朝右的刺要么就是横坐标大，要么是纵坐标小。）

维护每个朝右的刺（$s_1$）上的标记，直接暴力即可。

[code](https://www.luogu.com.cn/paste/io2vshpf).

### $\textbf{Sub }{\sf5}\textbf:$ $\sum n\leqslant3\times10^5$（$O(n\log n)$）。

考虑用数据结构维护以上过程。

那么对纵坐标开一棵线段树，维护每个纵坐标上的可贡献的刺的个数和标记总个数，需要支持以下操作：

- 在一个纵坐标添加或删除一个朝右的刺；
- 把 $[1,x)$ 区间的所有朝右的刺打上一层标记（即对于每个纵坐标内要把标记个数加上刺的个数）；
- 统计 $(x,+\infty)$ 区间内的标记总数。

至于 $d$ 的限制，因为如果一个朝右的刺和当前刺的横坐标距离已经超过 $d$ 了，那么这个朝右的刺的标记数量一定不变了，那么我们可以用一个队列维护当前还可能有贡献的朝右的刺，每次移动扫描线的时候查看队头的刺是否满足要求（距离 $\leqslant d$），若不满足要求，则线段树上删除这个刺（但不清空标记数量：因为这个刺可能对向下的刺产生贡献）。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {ll x; scanf("%lld", &x); return x;}
const int N = 314514;
int n;
struct Needle {
	int x, y; char dir;
	friend bool operator <(Needle a, Needle b) {
		// 保证从左到右扫描，从上到下处理
		if(a.x == b.x) return a.y > b.y;
		return a.x < b.x;
	}
}need[N];
int que[N]; int hh = -1, tt = 0;
namespace Discretization {//对所有刺的纵坐标进行离散化
	int b[N], idx2;
	void do_it() {
		for(int i = 1; i <= n; i++) b[i - 1] = need[i].y;
		sort(b, b + n);
		idx2 = unique(b, b + n) - b;
		for(int i = 1; i <= n; i++)
			need[i].y = lower_bound(b, b + idx2, need[i].y) - b + 1;
	}
}
namespace segtree {
	struct segnode {
		int l, r, lc, rc;
		ll sum, tag;
		//sum：该纵坐标当前有多少个可以和朝左的刺（L刺）配对的朝右的刺（R刺）
		//tag：该纵坐标内的R刺有多少个标记
		//维护其区间和。
		ll flag;//懒标记，表示上次 pushdown 到子树后又进行了 flag 次 add() 的修改。
		segnode(){}
		segnode(int a, int b, int c, int d):
		l(a), r(b), lc(c), rc(d), sum(0), tag(0), flag(0) {}
		void addsum(ll cnt) {sum += cnt;}
		void addtag(ll cnt = 1) {tag += sum * cnt; flag += cnt;}
	}T[N << 1]; int idx3 = 0;
	void pushup(int u) {
		T[u].sum = T[T[u].lc].sum + T[T[u].rc].sum;
		T[u].tag = T[T[u].lc].tag + T[T[u].rc].tag;
	}
	void pushdown(int u) {
		if(T[u].flag) {
			T[T[u].lc].addtag(T[u].flag);
			T[T[u].rc].addtag(T[u].flag);
			T[u].flag = 0;
		}
	}
	int constructor(int l, int r) {
		if(l > r) return -1;
		int u = ++idx3;
		if(l == r) return T[u] = segnode(l, r, -1, -1), u;
		int mid = (l + r) >> 1;
		return T[u] = segnode(l, r, constructor(l, mid), constructor(mid + 1, r)), pushup(u), u;
	}
	void modisum(int u, int p, ll val) {
		if(T[u].l == T[u].r) return T[u].addsum(val);
		pushdown(u);
		int mid = (T[u].l + T[u].r) >> 1;
		if(mid >= p) modisum(T[u].lc, p, val);
		if(mid < p) modisum(T[u].rc, p, val);
		return pushup(u);
	}
	void moditag(int u, int l, int r) {
		if(l > r) return;
		if(T[u].l >= l && T[u].r <= r) return T[u].addtag();
		pushdown(u);
		int mid = (T[u].l + T[u].r) >> 1;
		if(mid >= l) moditag(T[u].lc, l, r);
		if(mid < r) moditag(T[u].rc, l, r);
		return pushup(u);
	}
	ll query(int u, int l, int r) {
		if(l > r) return 0;
		if(T[u].l >= l && T[u].r <= r) return T[u].tag;
		pushdown(u);
		int mid = (T[u].l + T[u].r) >> 1;
		ll ans1 = 0, ans2 = 0;
		if(mid >= l) ans1 = query(T[u].lc, l, r);
		if(mid < r) ans2 = query(T[u].rc, l, r);
		return ans1 + ans2;
	}
}
bool major(int Testcase = 1) {
	hh = -1, tt = 0; segtree::idx3 = 0;
	n = read(); int d = read();
	for(int i = 1; i <= n; i++) {
		need[i].x = read(), need[i].y = read();
		char ch = getchar(); while(ch > 'Z' || ch < 'A') ch = getchar();
		need[i].dir = ch;
	}
	sort(need + 1, need + n + 1);
	Discretization::do_it();
	segtree::constructor(1, n);
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		while(hh >= tt && need[que[tt]].x < need[i].x - d) {
			int &v = need[que[tt++]].y;
			//do sth for v
			segtree::modisum(1, v, -1);//删除一个R刺
		}
		switch(need[i].dir) {
			case 'R': {
				que[++hh] = i;
				segtree::modisum(1, need[i].y, 1);//添加一个R刺
				break;
			}
			case 'L': {
				segtree::moditag(1, 1, need[i].y - 1);//区间纵坐标内的每个R刺打上一层标记
				break;
			}
			case 'U': {
				ans += segtree::query(1, need[i].y + 1, n);
				break;
			}
		}
	}
	printf("%lld\n", ans);
	return Testcase;
}
int main() {
	int T = read(), id = read(); while(T--) major();
}
```

---

