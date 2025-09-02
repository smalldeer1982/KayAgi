# [ARC039C] 幼稚園児高橋君

## 题目描述

在一个向四周无限延伸的平面上有一个人，一开始设个人在$(0,0)$

现在这个人将会进行$N$次移动，每次移动都会选择上下左右中的一个方向，然后走到这个方向上第一个没有被走到的整点

问最后这个人在哪里

## 说明/提示

$1\le N=|S|\le 200000$
走过的路径为$(0,0)(1,0)(-1,0)(-1,1)$

## 样例 #1

### 输入

```
3
RLU```

### 输出

```
-1 1```

## 样例 #2

### 输入

```
7
RURDRUL```

### 输出

```
0 1```

## 样例 #3

### 输入

```
25
RLRLRLRLRLRLURLRLRLRLRLRL```

### 输出

```
-12 1```

# 题解

## 作者：AC_love (赞：1)

很简单的链表练习题，其他题解有点把问题复杂化了。

不考虑爆空间的情况下我们该怎么做？可以直接开四个 $(4 \times 10^5)^2$ 大小的数组记录每个点往上下左右走会走到哪里。当我们走到一个新的点的时候，把当前这个点删除，具体做法是：

- 这个点右面的点的左面的点（原本是这个点自身）修改为这个点左面的点。
- 这个点左面的点的右面的点（原本是这个点自身）修改为这个点右面的点。
- 这个点上面的点的下面的点（原本是这个点自身）修改为这个点下面的点。
- 这个点下面的点的上面的点（原本是这个点自身）修改为这个点上面的点。

非常简单，实现起来也很容易，唯一的缺点是空间爆了。

但我们发现：我们可能走到的点是 $O(n^2)$ 级别的，但实际上我们会走的点只有 $O(n)$ 级别。因此没必要开一个 $O(n^2)$ 的数组，我们直接用 `map` 来存储信息即可。

[code](https://atcoder.jp/contests/arc039/submissions/59489888)

---

## 作者：ケロシ (赞：1)

非常好数据结构题。

首先考虑 `L` 操作，假设现在高桥君现在 $(x,y)$，那么这个操作相当于移动到第 $y$ 行中很坐标比 $x$ 小且最大的没有到过的位置。

这个在 $x$ 左边且要最靠右，这个很明显可以通过二分处理，但是这个到过的位置非常稀疏，没到过的位置非常的多，所以考虑动态开点线段树，在线段树上二分，对于一个线段树区间 $[l,r]$，先递归 $[mid+1, r]$，如果有答案则返回，没有就递归 $[l,mid]$。

对于 `R` 操作的话反一下即可，对于 `DU` 操作也是等价一样的。

时间复杂度 $O(n\log n)$。

```cpp
const int N = 2e5 + 10;
const int V = 2e5 + 5;
const int M = 1e7 + 5;
const int INF = 1e9 + 7;
int n;
string s;
int rt[N << 1][2], ls[M], rs[M], F[M], tot;
void pushup(int u) {
	F[u] = F[ls[u]] + F[rs[u]];
}
void insert(int &u, int l, int r, int p) {
	if(!u) u = ++tot;
	if(l == r) {
		F[u] = 1;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) insert(ls[u], l, mid, p);
	else insert(rs[u], mid + 1, r, p);
	pushup(u);
}
int query_l(int u, int l, int r, int p) {
	if(!u) return r;
	if(r - l + 1 == F[u]) return INF;
	int mid = l + r >> 1;
	if(p <= mid + 1) return query_l(ls[u], l, mid, p);
	int val = query_l(rs[u], mid + 1, r, p);
	if(val != INF) return val;
	return query_l(ls[u], l, mid, p);
}
int query_r(int u, int l, int r, int p) {
	if(!u) return l;
	if(r - l + 1 == F[u]) return INF;
	int mid = l + r >> 1;
	if(p >= mid) return query_r(rs[u], mid + 1, r, p);
	int val = query_r(ls[u], l, mid, p);
	if(val != INF) return val;
	return query_r(rs[u], mid + 1, r, p);
}
void add(int x, int y) {
	insert(rt[x + V][0], -V, V, y);
	insert(rt[y + V][1], -V, V, x);
}
void solve() {
	cin >> n;
	cin >> s; s = ' ' + s;
	int px = 0, py = 0;
	add(px, py);
	FOR(i, 1, n) {
		if(s[i] == 'L') {
			px = query_l(rt[py + V][1], -V, V, px);
		}
		if(s[i] == 'R') {
			px = query_r(rt[py + V][1], -V, V, px);
		}
		if(s[i] == 'U') {
			py = query_r(rt[px + V][0], -V, V, py);
		}
		if(s[i] == 'D') {
			py = query_l(rt[px + V][0], -V, V, py);
		}
		add(px, py);
	}
	cout << px << " " << py << endl;
}
```

---

## 作者：ran_qwq (赞：0)

对每行每列开个 set，维护出现过的连续段。

更新坐标时，如果是水平方向在水平方向的 set 中找连续段，竖直方向同理。设当前位置处在的连续段为 $[l,r]$，若往左则跳到 $l-1$，往右跳到 $r+1$。

往 set 插入当前坐标时，分讨左边右边有没有挨着已有区间，如果有就删掉已有区间并更新。

```cpp
int n,cx,cy; string s; set<pii> sx[N*2],sy[N*2];
void ins(set<pii> &st,int x) {
	auto it=st.lb({x,INF});
	if(it==st.begin()&&it==st.end()) st.insert({x,x});
	else if(it==st.begin()) {
		auto [l,r]=*it;
		if(l==x+1) st.erase(it),st.insert({x,r});
		else st.insert({x,x});
	} else if(it==st.end()) {
		auto [l,r]=*prev(it);
		if(r==x-1) st.erase(prev(it)),st.insert({l,x});
		else st.insert({x,x});
	} else {
		auto [l,r]=*it; auto [p,q]=*prev(it);
		if(q==x-1&&l==x+1) st.erase(prev(it)),st.erase(it),st.insert({p,r});
		else if(q==x-1) st.erase(prev(it)),st.insert({p,x});
		else if(l==x+1) st.erase(it),st.insert({x,r});
		else st.insert({x,x});
	}
}
void QwQ() {
	n=rd(),cin>>s,ins(sx[N],0),ins(sy[N],0);
	for(char c:s)
		if(c=='R') {
			auto [l,r]=*prev(sx[cy+N].lb({cx,INF}));
			cx=r+1,ins(sx[cy+N],cx),ins(sy[cx+N],cy);
		} else if(c=='L') {
			auto [l,r]=*prev(sx[cy+N].lb({cx,INF}));
			cx=l-1,ins(sx[cy+N],cx),ins(sy[cx+N],cy);
		} else if(c=='U') {
			auto [l,r]=*prev(sy[cx+N].lb({cy,INF}));
			cy=r+1,ins(sy[cx+N],cy),ins(sx[cy+N],cx);
		} else {
			auto [l,r]=*prev(sy[cx+N].lb({cy,INF}));
			cy=l-1,ins(sy[cx+N],cy),ins(sx[cy+N],cx);
		}
	wr(cx," "),wr(cy,"\n");
}
```

---

## 作者：2020kanade (赞：0)

来一篇相对邪门一点的。

我们考虑对于每行或每列，高桥走过的位置可以构成若干极大同色连通块也就是颜色段，并且某时刻高桥一定在这些颜色段上的某处。

因此，行走的目标位置一定是当前行或列对应的颜色段集合中，高桥所在的颜色段的右端点加一或左端点减一（只针对发生变化的坐标而言）。

显然，行走的坐标值域为 $O(n)$ 级别，因此每行和每列分别开一个 ```std::set```，用这共 $2n$ 个 ```std::set``` 维护若干颜色段即可。

颜色段的维护部分详见代码。

时间复杂度 $\Theta(n\log n)$。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
struct node
{
	int l,r;
	node(int x):l(x),r(x) {}
	node(int l,int r):l(l),r(r) {}
	const bool operator <(const node& c) const
	{
		return r<c.r;
	}
};
set<node> rs[N],cs[N];
void insert(set<node> &s,int x)
{
	auto nd=node(x);
	auto it=s.insert(nd).first,it2=it;++it2;
	if(it!=s.begin())
	{
		auto it3=it;--it3;
		node px=*it3;
		if(px.r+1==x)
		{
			s.erase(it3),s.erase(it);
			it=s.insert(node(px.l,x)).first;
			it2=it;++it2;
		}
	}
	if(it2!=s.end())
	{
		node px=*it2;
		if((*it).r+1==px.l)
		{
			int al=(*it).l,ar=(*it2).r;
			s.erase(it2),s.erase(it);
			it=s.insert(node(al,ar)).first;
		}
	}
}
int askprev(set<node> s,int x)
{
	auto it=s.lower_bound(node(x));
	return (*it).l-1;
}
int asknxt(set<node> s,int x)
{
	auto it=s.lower_bound(node(x));
	return (*it).r+1;
}
void solve()
{
	int ax=0,ay=0;
	cin>>n;string opt;
	cin>>opt;
	insert(rs[n+ax],ay);insert(cs[n+ay],ax);
	for(auto x:opt)
	{
		if(x=='U')
		{
			ax=askprev(cs[n+ay],ax);
			insert(rs[n+ax],ay);insert(cs[n+ay],ax);
		}
		else if(x=='D')
		{
			ax=asknxt(cs[n+ay],ax);
			insert(rs[n+ax],ay);insert(cs[n+ay],ax);
		}
		else if(x=='L')
		{
			ay=askprev(rs[n+ax],ay);
			insert(rs[n+ax],ay);insert(cs[n+ay],ax); 
		}
		else if(x=='R')
		{
			ay=asknxt(rs[n+ax],ay);
			insert(rs[n+ax],ay);insert(cs[n+ay],ax);
		}
	}
	cout<<ay<<' '<<ax*-1<<endl;
}
int main()
{
	syncoff();
 	t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：Watanabe (赞：0)

牛马链表题，相信做完之后你一定会跟我一样~~神清气爽~~。

## 思路

题目叙述的比较清楚了，相当于我们往一个方向走时，要维护这个方向上第一个没有走过的点。考虑暴力，直接 for 循环往要走的方向一直走，时间复杂度 $O(n^2)$，肯定过不去。

考虑进行优化。先考虑水平方向上走（竖直方向上同理），我们会发现若一段连续的点 $(i,j),(i+1,j),(i+2,j),(i+3,j)\cdots(i+k-1,j),(i+k,j)$ 都被走过，那么只有 $(i,j),(i+k,j)$ 这两个点有用。因为我们不可能走到已经走过的点上，所以我们在左右走动时，不可能直接跳过 $(i,j)$  或 $(i+k,j)$ 去走到它们中间的点。所以我们考虑在水平方向上维护两个链表，分别记录点 $(i,j)$ **左边第一个没走过的点的右边那个点**和**右边第一个没走过的点的左边那个点**（相当于该区间的左右端点），移动时更改答案坐标并加入当前点就好了（竖直方向上同理维护两个链表）。

注意，有个坑点：

我们假设加入当前点，且正在维护它的左边区间左端点，那么它的右边区间右端点的左端点可能也会更新。相当于没加入它之前，左区间和右区间分开，加入之后两个区间合并到一起，自然要维护。

## 代码实现

这里采用二维 map，时间复杂度 $O(n \log ^ 2 n)$，但是跑得还挺快？（雾）

其实可以用一维 map，具体实现不再赘述，复杂度少个 $\log$。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define re register

using namespace std;
const int N=2e5+10;
int n,len,x,y;
string s;
map < int ,map<int,int> > hl,hr,hu,hd,f; 

inline int read(){char cr=getchar();int x_=0,fui=1;while(cr<48){if(cr=='-')fui=-1;cr=getchar();}while(cr>47)x_=(x_*10)+(cr^48),cr=getchar();return x_*fui;}
inline void mwrite(int aq){if(aq>9)mwrite(aq/10);putchar((aq%10)|48);}
inline void write(int af,char cr){mwrite(af<0?(putchar('-'),af=-af):af);putchar(cr);}

inline void add(int x,int y)
{
	f[x+N][y+N]=1;
	if(!f[x-1+N][y+N]) hl[x+N][y+N]=x+N;
	else 
	{
		hl[x+N][y+N]=hl[x-1+N][y+N];
		if(!f[x+1+N][y+N])
		hr[hl[x-1+N][y+N]][y+N]=x+N;
		else
		hr[hl[x-1+N][y+N]][y+N]=hr[x+1+N][y+N];
	}
	if(!f[x+1+N][y+N]) hr[x+N][y+N]=x+N;
	else 
	{
		hr[x+N][y+N]=hr[x+1+N][y+N];
		if(!f[x-1+N][y+N])
		hl[hr[x+1+N][y+N]][y+N]=x+N;
		else
		hl[hr[x+1+N][y+N]][y+N]=hl[x-1+N][y+N];
	}
	if(!f[x+N][y-1+N]) hd[x+N][y+N]=y+N;
	else 
	{
		hd[x+N][y+N]=hd[x+N][y-1+N];
		if(!f[x+N][y+1+N])
		hu[x+N][hd[x+N][y-1+N]]=y+N;
		else 
		hu[x+N][hd[x+N][y-1+N]]=hu[x+N][y+1+N];
	}
	if(!f[x+N][y+1+N]) hu[x+N][y+N]=y+N;
	else 
	{
		hu[x+N][y+N]=hu[x+N][y+1+N];
		if(!f[x+N][y-1+N])
		hd[x+N][hu[x+N][y+1+N]]=y+N;
		else
		hd[x+N][hu[x+N][y+1+N]]=hd[x+N][y-1+N];
	}
}
inline int go_left(int x,int y)
{
	int nw;
	if(!f[x-1+N][y+N]) 
	{
		hl[x+N][y+N]=x-1+N;
		nw=x+N;
	}
	else
	{
		nw=hl[x+N][y+N]=hl[x-1+N][y+N];
	}
	return nw;
}
inline int go_rignt(int x,int y)
{
	int nw;
	if(!f[x+1+N][y+N]) 
	{
		hr[x+N][y+N]=x+1+N;
		nw=x+N; 
	}
	else
	{
		nw=hr[x+N][y+N]=hr[x+1+N][y+N];
	}
	return nw;
}
inline int go_down(int x,int y)
{
	int nw;
	if(!f[x+N][y-1+N]) 
	{
		hd[x+N][y+N]=y-1+N;
		nw=y+N;
	}
	else
	{
		nw=hd[x+N][y+N]=hd[x+N][y-1+N];
	}
	return nw;
}
inline int go_up(int x,int y)
{
	int nw;
	if(!f[x+N][y+1+N]) 
	{
		hu[x+N][y+N]=y+1+N;
		nw=y+N;
	}
	else
	{
		nw=hu[x+N][y+N]=hu[x+N][y+1+N];
	}
	return nw;
}
signed main() 
{
    n=read();
    cin>>s;
    len=s.length();
    f[N][N]=1;
    hl[N][N]=N,hr[N][N]=N,hu[N][N]=N,hd[N][N]=N;
    for(re int i=0;i<len;++i)
    {
    	if(s[i]=='L') x=go_left(x,y)-N-1;
    	if(s[i]=='R') x=go_rignt(x,y)-N+1;
    	if(s[i]=='U') y=go_up(x,y)-N+1;
    	if(s[i]=='D') y=go_down(x,y)-N-1;
    	if(!f[x+N][y+N]) add(x,y);
	}
	write(x,' '),write(y,'\n');
    return 0;
}
```


---

