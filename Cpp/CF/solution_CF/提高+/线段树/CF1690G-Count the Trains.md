# Count the Trains

## 题目描述

**【题目大意】**

铁轨上有 $n$ 节车厢，每节车厢在各自的引擎驱动下可以达到一个最高速度，记录在一个序列 $\{a_i\}$ 里. 车厢从左到右的编号依次为 $1$ 到 $n$.

现在让这些车厢向左尽可能快地开动，要求靠右的车厢实际速度不能超过靠左的车厢. 这样便会形成若干段速度一致的连续数节车厢，称这样的一段为**一节火车**. 例如序列 $a=[10,13,5,2,6]$ 对应的车厢的实际运行速度为 $[10,10,5,2,2]$，形成了 $3$ 节火车.

在车厢行驶时，依次收到了 $m$ 条形如 $k\ d$ 的信息，表示第 $k$ 节车厢的最高速度因引擎老化而下降了 $d$. 请维护这个过程中火车的总节数，每次收到信息后输出.

## 说明/提示

所有数值均为整数.

$t∈[1,10^4];$

$n,m∈[1,10^5];$

$a_i∈[0,10^9](\forall i∈[1,n]);$

$k_j∈[1,n],\ d_j∈[0,a_{k_j}](\forall j∈[1,m])$.

所有测试用例的 $n$ 的总和及 $m$ 的总和均不超过 $10^5$.

## 样例 #1

### 输入

```
3

4 2
6 2 3 7
3 2
4 7

5 4
10 13 5 2 6
2 4
5 2
1 5
3 2

13 4
769 514 336 173 181 373 519 338 985 709 729 702 168
12 581
6 222
7 233
5 117```

### 输出

```
3 4 
4 4 2 3 
5 6 6 5```

# 题解

## 作者：sunkuangzheng (赞：6)

简单题，建议降绿 qwq。

$\textbf{1.1 Hints}$

- $\textbf{1.1.1 Hint 1}$

解决 $m=0$。

- $\textbf{1.1.2 Hint 2}$

当一节火车的速度降低时，只会影响它及它后面的车厢。

- $\textbf{1.1.3 Hint 3}$

一次操作时，只需要考虑每节火车的车头。

- $\textbf{1.1.4 Hint 4}$

使用 set 解决问题。

$\textbf{1.2 Solution}$

当 $m=0$ 时，显然我们可以记录上一节车头的速度从而 $\mathcal O(n)$ 解决问题。

类似的，一节车厢是否会成为一节火车的车头取决于上一节车头的速度，也就是前面的车厢的状态不会被改变。当车厢 $k$ 操作时，首先向后遍历车头 $x$，如果 $a_x \ge a_k - d$，那么 $x$ 将不再是车头。然后比较新车厢和这节车厢前的第一个车头 $y$，若 $a_y> a_k - d$，那么 $k$ 将成为新车头。

容易发现上述过程可以使用 set 解决。初始时最多有 $\mathcal O(n)$ 个车头，每次操作最多增加一个车头，因此设 $n,m$ 同阶，复杂度均摊是 $\mathcal O(n \log n)$。

$\textbf{1.3 Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int t,n,m,a[maxn],k,d;
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n >> m;set<int> s;
        for(int i = 1;i <= n;i ++) 
            if(cin >> a[i],!s.size() || a[i] < a[*(--s.end())]) s.insert(i);
        while(m --){
            cin >> k >> d;int b = a[k] - d;
            while(s.lower_bound(k) != s.end() && a[*s.lower_bound(k)] >= b) s.erase(*s.lower_bound(k));
            if(s.lower_bound(k) == s.begin() || a[*(--s.lower_bound(k))] > b) s.insert(k);
            a[k] -= d,cout << s.size() << " ";
        }cout << "\n";
    }
}
```



---

## 作者：ImALAS (赞：5)

[传送门qwq](https://www.luogu.com.cn/problem/CF1690G)

# Analysis

首先会发现，题目中其实就是把原序列变成了一个单调递减的序列。

而且，“一节火车”其实就是一个区间，每次操作就是把区间拆开再重组。

观察一下，发现这不就是珂朵莉树的操作吗 Σ(⊙▽⊙"a。

那么珂以考虑用珂朵莉树维护所有的区间。

读入数据后先遍历一遍整个序列，将其转换成一个个区间存入珂朵莉树。

每次 $a_k \gets a_k-d$ 后，判断一下当前 $k$ 位置的速度和 $a_k$ 的大小关系，如果 $a_k$ 比这个速度还小，就用珂朵莉树拆开 $k$ 所在区间，再暴力地往后更新。

听起来很暴力，但它的时间复杂度是有保障的。

经过我们的若干次操作，最多会有 $n+m$ 个区间。

发现在上述算法中，被遍历过的区间一定会被删除。

换言之，最后至多会删除 $n+m$ 个区间，那么我们最多只会遍历到 $n+m$ 个区间。

`STL set` 单次操作时间复杂度 $O(\log n)$，那么总体的时间复杂度就是 $O((n+m)\log n)$。

# Code

大佬们的代码一个比一个快，只有我人傻常数大 QAQ。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define Chtholly set<node>::iterator
#define pb emplace_back
const int maxn = 1e5 + 5;
int n,m;
int a[maxn],cov[maxn];
vector<int> ans;
struct node {
	int l,r;
	mutable int v;
	node() {
		l = r = 0;
		v = 0;
	}
	node(int l,int r = 0,int v = 0):l(l),r(r),v(v){}
	bool operator < (const node& p)const {
		return l < p.l;
	}
};
set<node> s;
int check(int pos) {
	Chtholly it = s.lower_bound(node(pos));
	if(it != s.end()&&it -> l == pos)return it -> v;
	-- it;
	return it -> v;
}
Chtholly split(int pos) {
	Chtholly it = s.lower_bound(node(pos));
	if(it != s.end()&&it -> l == pos)return it;
	-- it;
	if(it -> r < pos)return s.end(); 
	int l = it -> l;
	int r = it -> r;
	int v = it -> v; 
	s.erase(it);
	s.insert(node(l , pos - 1 , v));
	return s.insert(node(pos , r , v)).first;
}
void modify(int pos,int val) {
	Chtholly itl = split(pos),it;
	int cnt = 0;
	for(it = itl;it != s.end();++ it) {
		if(it -> v < val)break ;
		cnt += it -> r - it -> l + 1;
	}
	if(it != itl)s.erase(itl , it);
	s.insert(node(pos , pos + cnt - 1 , val));
	return ;
}
void work() {
	s.clear();
	scanf("%d%d",&n,&m);
	ans.clear();
	for(int i = 1;i <= n;++ i)scanf("%d",&a[i]);
	int lst = 1;
	for(int i = 2;i <= n;++ i) {
		if(a[i] >= a[lst])continue ;
		s.insert(node(lst , i - 1 , a[lst]));
		lst = i;
	}
	s.insert(node(lst , n , a[lst]));
	for(int i = 1;i <= m;++ i) {
		int k,d;
		scanf("%d%d",&k,&d);
		a[k] -= d;
		if(check(k) > a[k])modify(k , a[k]);
		ans.pb(s.size());
	}
	for(auto v : ans)printf("%d ",v);
	puts("");
	return ;
}
int main() {
	int T;
	scanf("%d",&T);
	while(T --)work();
	return 0;
} 
```

完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：lingfunny (赞：5)

# CF1690[G. Count the Trains](https://codeforces.com/contest/1690/problem/G)

~~div.3 unrated，没打，就看了眼题~~

题意：求贪心严格下降子序列的长度，带修，但是修改是减少值。

会发现这个修改是单调的，直观上珂朵莉树应该可以直接维护。

仔细分析一下，最开始最多有 $O(n)$ 段区间，每次修改会推平一段区间并创造一个新区间，区间总数是 $O(n+m)$ 的，用 `set` 或 `map` 实现多加个 $\log (n+m)$，总复杂度 $O(n\log n)$ （默认 $n,m$ 同阶），可以过。此处用 `map` 实现。[提交记录](https://codeforces.com/contest/1690/submission/159866719)。

~~珂朵莉树写起来真的又短又舒服~~

```cpp
// Problem: G. Count the Trains
// From: Codeforces - Codeforces Round #797 (Div. 3)
// URL: https://codeforces.com/contest/1690/problem/G
// Time: 2022-06-08 01:23
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 1e5+10;

int n, m, a[mxn];

map <int, int> mp;

inline void solve() {
	scanf("%d%d", &n, &m);
	map <int, int> ().swap(mp);
	mp[0] = 1.1e9; mp[n+1] = -1;
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	for(int i = 1, pre = 1.1e9; i <= n; ++i) if(a[i] < pre) pre = a[i], mp[i] = a[i];
	while(m--) {
		int k, d; scanf("%d%d", &k, &d);
		a[k] -= d; auto it = prev(mp.upper_bound(k));
		if(it -> second > a[k]) {
			if(it -> first != k) mp[k] = it -> second;
			it = mp.find(k);
			while(it -> second >= a[k]) it = mp.erase(it);
			mp[k] = a[k];
		}
		printf("%d%c", (int)mp.size()-2, " \n"[!m]);
	}
}

int main() {
	int tt;
	scanf("%d", &tt);
	while(tt--) solve();
}

---

## 作者：tuxuanming2024 (赞：4)

# 题目大意

$n$ 个数 $a_1,a_2,\cdots,a_n$，可生成一个序列 $b$ 满足： $i=1$ 时 $b_i=a_i$，$i \ge 2$ 时 $b_i = \min(a_i,b_{i-1})$。对于每个 $b$，规定连续的一段相同数字为一个块。如序列 $a=[10,13,5,2,6]$ 时，$b=[10,10,5,2,2]$，此时 $b$ 的块数为 $3$。有 $m$ 个操作，每个操作给出 $k,d$ 表示将 $a_k$ 的值减少 $d$（保证 $0 \le d \le a_k$）。求每个操作后生成的 $b$ 的块数。

# 题解

思维不够，数据结构来凑。

首先，对于 $a_k$，任然满足 $b_k=\min(a_k,b_{k-1})$，由于一次操作不会影响到前 $k-1$ 个元素，因此我们可以直接得到 $b_k$ 的值。

其次，考虑新的 $b_k$ 对后面答案的影响。根据题意得 $b$ 一定单调不升，所以我们可以在 $[k+1,n]$ 中二分找到最小的 $p$ 满足 $b_p \le b_k$，那么 $b_{k+1}$ 至 $b_{p-1}$ 之间的数一定大于 $b_k$，根据定义，我们需要将 $[k,p-1]$ 这一区间内的数全部改为 $b_k$。由于涉及到区间修改，我们可以使用线段树维护 $b$ 的值，进行单点查询和区间修改。

那么接下来就是更新答案了。

在线段树中，设当前节点 $x$ 维护 $[l,r]$ 之间的数，左儿子 $lc$ 维护 $[l,mid]$，右儿子 $rc$ 维护 $[mid+1,r]$，$ans_x$ 表示区间 $[l,r]$ 中的块的数量。我们可以再维护两个值 $lnum$ 表示当前区间最左边的数，$rnum$ 表示最右边的数，那么更新答案的方法如下：

$$ ans_x = ans_{lc}+ans_{rc}-[rnum_{lc}=lnum_{rc}]$$

# 代码

~~虽然长，但是能过题的算法都是好算法！~~

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=100005,INF=0x3f3f3f3f;
struct node {int l,r,res,lnum,rnum,bj;}t[N<<2];
int n,m,a[N],b[N];
void pushup(int x)
{
	t[x].res=t[x<<1].res+t[x<<1|1].res-(t[x<<1].rnum==t[x<<1|1].lnum); //更新答案
	t[x].lnum=t[x<<1].lnum;
	t[x].rnum=t[x<<1|1].rnum;
}
void pushdown(int x)
{
	if(t[x].bj!=-1)
	{
		t[x<<1].bj=t[x<<1].lnum=t[x<<1].rnum=t[x].bj;
		t[x<<1|1].bj=t[x<<1|1].lnum=t[x<<1|1].rnum=t[x].bj;
		t[x<<1].res=t[x<<1|1].res=1;
		t[x<<1].bj=t[x<<1|1].bj=t[x].bj;
		t[x].bj=-1;
	}
}
void build(int x,int l,int r)
{
	t[x].l=l,t[x].r=r,t[x].bj=-1;
	if(l==r)
	{
		t[x].res=1;
		t[x].lnum=t[x].rnum=b[l];
		return;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void change(int x,int l,int r,int y)
{
	if(r<t[x].l||l>t[x].r) return;
	if(l<=t[x].l&&r>=t[x].r)
	{
		t[x].res=1;
		t[x].lnum=t[x].rnum=t[x].bj=y;
		return;
	}
	pushdown(x);
	change(x<<1,l,r,y);
	change(x<<1|1,l,r,y);
	pushup(x);
}
int ask(int x,int y)
{
	if(t[x].l==t[x].r) return t[x].lnum;
	pushdown(x);
	int mid=t[x].l+t[x].r>>1;
	if(y<=mid) return ask(x<<1,y);
	else return ask(x<<1|1,y);
}
void solve()
{
	cin>>n>>m;
	b[0]=a[0]=INF;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=min(a[i],b[i-1]);
	}
	build(1,1,n);
	int k,d;
	while(m--)
	{
		cin>>k>>d;
		a[k]-=d;
		int x=min(a[k],ask(1,k-1));
		int l=k+1,r=n,mid,p=n+1; //为了使答案正确，初始时 p=n+1
		while(l<=r)
		{
			mid=l+r>>1;
			if(ask(1,mid)<=x) p=mid,r=mid-1;
			else l=mid+1;
		}
		change(1,k,p-1,x);
		cout<<t[1].res<<' ';
	}
	cout<<'\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```


---

## 作者：hzjnsy (赞：2)

来一个垃圾做法。

**[洛谷](https://www.luogu.com.cn/problem/CF1690G) [CF](https://codeforces.com/problemset/problem/1690/G)**

> - 给出长度为 $n$ 的数组 $a_1\sim a_n$，有 $m$ 次操作，每次操作给出 $k$ 和 $d$，表示将 $a_k\leftarrow a_k-d$。保证不会出现负数。
>
> - 你要动态维护一个数组 $b_1\sim b_n$，其中 $b_i=\min\limits_{j=1}^i a_j$。每次操作结束后，输出数组 $b$ 的颜色段数。颜色段数的定义为，$b$ 数组中 $b_i\ne b_{i-1}\,(i>1)$ 的位置的个数，再加上 $1$。
>
> - $t$ 组数据，$t\le10^4$，$\sum n,\sum m\le 10^5$。

考虑用线段树维护颜色段数。节点上维护 $lc,rc,cnt$ 表示这一段最左边的颜色，最右边的颜色，以及区间内部的颜色段数。合并两个信息 $u,v$（认为 $u$ 在左边）时，$lc$ 继承 $lc_u$，$rc$ 继承 $rc_v$，$cnt$ 则为 $cnt_u+cnt_v-[rc_u=lc_v]$。很好理解，拼接处的颜色相同两个段就被拼成一个了。

考虑 $b$ 什么时候会发生改变，怎么变。显然，当修改后 $a_i<b_{i-1}$ 的时候，$b_i$ 及其往后的一段会变成 $a_i$。具体往后多少呢，显然这一段的 $a$ 值都不小于 $a_i$。

再用一个线段树维护 $a$ 数组的区间最小值，支持单点修改和区间查询操作。我们发现，当左端点固定时，某一段的 $a$ 值随着区间的长度增大而**非升**。故二分出这个右端点。

得到区间后，在维护 $b$ 值的线段树上将该区间全部推平成 $a_i$。注意不覆盖的标记不要和值域重叠。

时间复杂度为 $\mathcal{O}(\sum m\log^2 n)$，空间复杂度为 $\mathcal{O}(\sum n+\sum m)$。

```cpp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define ls(x) ((x) << 1)
#define rs(x) (((x) << 1) | 1)
using namespace std; const int N = 1e5 + 5, inf = 2e9; int Q, n, m, a[N], b[N];
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x)
    { if (x > 9) write(x / 10); putchar(x % 10 + 48); }
template<class T> void print(T x, char ed = '\n') 
    { if (x < 0) putchar('-'), x = -x; write(x), putchar(ed); }
struct node {
    int lc, rc, cnt; bool ept; node() { ept = 1; }
    node operator+(const node &o) const {
        if (ept) return o; if (o.ept) return *this;
        node ret; ret.lc = lc, ret.rc = o.rc; ret.ept = 0;
        ret.cnt = cnt + o.cnt - (rc == o.lc); return ret;
    }
};
struct SegmentTree {
    int minn[N << 2];
    void build(int x, int l, int r) {
        if (l == r) return void(minn[x] = a[l]); 
        int mid = (l + r) >> 1; build(ls(x), l, mid); build(rs(x), mid + 1, r);
        minn[x] = min(minn[ls(x)], minn[rs(x)]); 
    }
    void modify(int x, int l, int r, int k, int v) {
        if (l == r) return void(minn[x] -= v); int mid = (l + r) >> 1;
        if (k <= mid) modify(ls(x), l, mid, k, v);
        else modify(rs(x), mid + 1, r, k, v); 
        minn[x] = min(minn[ls(x)], minn[rs(x)]); 
    }
    int query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return minn[x]; int mid = (l + r) >> 1, rt = inf;
        if (ql <= mid) rt = query(ls(x), l, mid, ql, qr);
        if (qr > mid) rt = min(rt, query(rs(x), mid + 1, r, ql, qr)); return rt;
    }
} t1;
struct SegmentTree2 {
    node seg[N << 2]; int tag[N << 2];
    void build(int x, int l, int r) {
        tag[x] = -1; seg[x].ept = 0;
        if (l == r) return seg[x].lc = seg[x].rc = b[l], seg[x].cnt = 1, void();
        int mid = (l + r) >> 1; build(ls(x), l, mid); build(rs(x), mid + 1, r);
        seg[x] = seg[ls(x)] + seg[rs(x)];
    }
    void upd(int x, int k) { tag[x] = seg[x].lc = seg[x].rc = k; seg[x].cnt = 1; }
    void down(int x) 
        { if (tag[x] != -1) upd(ls(x), tag[x]), upd(rs(x), tag[x]), tag[x] = -1; }
    void assign(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) return upd(x, v), void();
        int mid = (l + r) >> 1; down(x);
        if (ql <= mid) assign(ls(x), l, mid, ql, qr, v);
        if (qr > mid) assign(rs(x), mid + 1, r, ql, qr, v);
        seg[x] = seg[ls(x)] + seg[rs(x)];
    }
    node query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return seg[x]; 
        int mid = (l + r) >> 1; node rt; down(x);
        if (ql <= mid) rt = query(ls(x), l, mid, ql, qr);
        if (qr > mid) rt = rt + query(rs(x), mid + 1, r, ql, qr); return rt;
    }
} t2;
signed main() {
    for (read(Q); Q--;) {
        read(n), read(m); for (int i = 1; i <= n; ++i) read(a[i]), b[i] = a[i]; 
        t1.build(1, 1, n);
        for (int i = 2; i <= n; ++i) b[i] = min(b[i], b[i - 1]);
        t2.build(1, 1, n);
        for (int i = 1, k, d; i <= m; ++i) {
            read(k), read(d); t1.modify(1, 1, n, k, d); a[k] -= d;
            if (k != 1 && t2.query(1, 1, n, 1, k - 1).rc <= a[k]) 
                print(t2.seg[1].cnt, ' ');
            else {
                int l = k, r = n, f; 
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (t1.query(1, 1, n, k, mid) >= a[k]) f = mid, l = mid + 1;
                    else r = mid - 1;
                }
                t2.assign(1, 1, n, k, f, a[k]); print(t2.seg[1].cnt, ' ');
            }
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：__Deng_Rui_Song__ (赞：1)

# preface

本关考察你对 STL 的掌握。

# problem

[题目传送门](/problem/CF1690G)

# solution

你打开了这道题，看完题目，你马上想到可以使用珂朵莉树。（~~但作者不会~~）

你用珂朵莉树 AC 这道题后，想要一个更简单的做法。

你发现，车厢速度下降后，有两种变化：

- 对前面的变化：如果当前车厢的速度小于火车头，那么自己变成新的火车头。

- 对后面的变化：把后面所有大于等于自己的火车头删除。

所以，你决定用 set 维护火车头。

# code

为此，你写出了以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, a[100005];
set<int> st;
void solve() {
  st.clear();
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (st.empty() || a[*st.rbegin()] > a[i]) st.insert(i);
  }
  while (m--) {
    int x, d;
    cin >> x >> d;
    a[x] -= d;
    auto id = st.upper_bound(x);
    while (id != st.end() && a[*id] >= a[x]) id = st.erase(id);
    if (st.upper_bound(x) != st.begin() && a[*(--st.upper_bound(x))] > a[x]) st.insert(x);
    cout << st.size() << ' ';
  }
  cout << '\n';
}
int main() {
  for (cin >> t; t--; solve())
    ;
  return 0;
}
```

你过了样例，并通过了此题！

---

## 作者：中缀自动机 (赞：1)

题意：若一个非队首的数组元素大于其前一个元素，则它的值变为前一个元素，问最终一共有多少种数字。

------------

分析：可以用 map 存储数组元素，map 的大小就是答案。若位置 $i$ 的数 $x_i$ 大于位置 $i-1$ 的数 $x_{i-1}$ ，就把位置 $i$ 从 map 中去除。否则，就把位置 $i$ 后 $x_{i+j} > x_{i}$ 的点去除。每次输入 $k,d$，将位置 $k$ 重新加入 $map$ 当中执行相同的操作。因为每个数组元素只会减少不会增加，所以那些被删除的元素并不会因为位置 $k$ 的改变而重新有进入 map 的可能。


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;
void che(int id,int num){
	mp[id]=num;
	auto it=mp.find(id);
	if(it!=mp.begin()&&prev(it)->second<=it->second){
		mp.erase(it);
		return;
	}
	while(next(it)!=mp.end()&&next(it)->second>=it->second) mp.erase(next(it));
	return;
}
int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m,t,k,d;
	cin>>t;
	while(t--){
		mp.clear();
		cin>>n>>m;
		vector<int> vec(n+1,0);
		for(int i=1;i<=n;i++) cin>>vec[i],che(i,vec[i]);
		while(m--){
			cin>>k>>d;
			vec[k]-=d;
			che(k,vec[k]);
			cout<<mp.size()<<" ";
		}
		cout<<"\n";
	}
    return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16467350.html)  

[题目传送门](https://codeforces.com/problemset/problem/1690/G)  

### 题目大意
有一些车厢在铁轨上按照一定速度向左移动，从左到右编号 $1,2,\dots,n$。每节车厢的最大速度为 $v_i$。靠左边的车厢以最快的速度前进，右边的车厢速度不能超过左边车厢的速度。定义一节火车为一些前进速度相等的车厢。  
现在有 $T$ 个事件，每次第 $x$ 辆车的速度会减小 $y$，求每次事件发生之后火车的数量。  
### 题目解析
显然我们可以预处理出每节车厢的前进速度，以及火车的数量。  
对于每次修改，如果这节车厢的最大速度还是大于等于车厢现在的速度，那么火车节数不变，否则这节火车就会变成两段，同时这节火车右边的一些火车也会被并掉。  
我们考虑用数据结构来维护每一节车厢的速度。  

方法一：线段树  
这种方法比较好想，但是比较难写。  
首先不难发现需要维护区间最小值，同时支持找右边第一个小于这辆火车的速度的火车编号，还要支持单点修改。其实就是线段树的传统操作+线段树二分。

方法二：`set`  
显然一节火车是一个区间，把这些区间按照左端点排序插入到一个 `set` 中，同时记录这节火车的速度。修改的时候直接暴力把所有会被修改的区间删掉，合并，然后插进去。由于每次操作只会最多增加一个区间，并且如果向右查询的区间除了最后一个都会被删除合并，所以复杂度是正确的。

代码（方法二）：
```cpp
void work(){
	n=read(); T=read(); int i; for(i=1;i<=n;i++) v[i]=read(); now.l=1; now.v=v[1]; s=E;
	for(i=2;i<=n;i++) if(v[i]<now.v){ now.r=i-1; s.insert(now); now.v=v[i]; now.l=i; }
	now.r=n; s.insert(now); set<JTZ>::iterator it; while(T--){
		x=read(); y=read(); v[x]-=y;
		now.l=x; now.v=v[x]; it=s.lower_bound(now);
		if(it==s.end()||(*it).l>x) it--;
		if((*it).v<=v[x]){ print(s.size()),pc(' '); continue; }
		if((*it).l<now.l){
			tmp=*it; s.erase(it); if(tmp.l<=x-1) s.insert(mp(tmp.l,x-1,tmp.v));
			s.insert(mp(x,tmp.r,tmp.v)); it=s.lower_bound(now);
		}
		while((*it).v>=now.v){
			now.r=(*it).r; s.erase(it); it=s.lower_bound(now);
			if(it==s.end()){ now.r=n; break; }
		} s.insert(now); print(s.size()),pc(' ');
	} pc('\n'); return;
}
```

---

## 作者：C_Pos_Princess (赞：0)

## 题意

求一个序列的单调递减子序列的长度，其中带修改且是减法。

这里的单调递减子序列是从头算起，不是最长的，而是碰到更小的就更新的那种。

## 题解
我们记录数组 $b$，令 $b_i = \min(b_{i-1},a_i)$，将 $b$ 数组建一棵线段树。

其中要维护子序列的长度，这里合并区间的操作很妙。

维护三个东西：

- 左端点的数值
- 右端点的数值
- 答案

```cpp
void pushup(int rt) {
	tr[rt].sum = tr[rt << 1].sum + tr[rt << 1 | 1].sum - (tr[rt << 1].rnum == tr[rt << 1 | 1].lnum);
	tr[rt].lnum = tr[rt << 1].lnum;
	tr[rt].rnum = tr[rt << 1 | 1].rnum;
}
```

修改和查询就单点修改就行了，然后二分找当前数字的最小值可以维护到的位置，区间覆盖即可。

## 代码
```cpp
int t;
int n, m;
int a[N];
int b[N];
struct node {
	int l, r;
	int lazy;
	int lnum, rnum;
	int sum;
} tr[N << 2];

void pushup(int rt) {
	tr[rt].sum = tr[rt << 1].sum + tr[rt << 1 | 1].sum - (tr[rt << 1].rnum == tr[rt << 1 | 1].lnum);
	tr[rt].lnum = tr[rt << 1].lnum;
	tr[rt].rnum = tr[rt << 1 | 1].rnum;
}

void build(int rt, int l, int r) {
	tr[rt].l = l;
	tr[rt].r = r;
	tr[rt].lazy = -1;
	if (l == r) {
		tr[rt].lnum = tr[rt].rnum = b[l];
		tr[rt].sum = 1;
		return;
	}
	int mid = l + r >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
	pushup(rt);
}

int push_down(int rt) {
	int l = tr[rt].lazy;
	if (l != -1) {
		tr[rt << 1].sum = 1;
		tr[rt << 1 | 1].sum = 1;
		tr[rt << 1].lnum = tr[rt << 1].rnum = l;
		tr[rt << 1 | 1].lnum = tr[rt << 1 | 1].rnum = l;
		tr[rt << 1].lazy = l;
		tr[rt << 1 | 1].lazy = l;
		tr[rt].lazy = -1 ;
	}
}

int query_one(int rt, int x) {
	if (tr[rt].l == tr[rt].r) {
		return tr[rt].lnum;
	}
	push_down(rt);
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (x <= mid) return query_one(rt << 1, x);
	else return query_one(rt << 1 | 1, x);
}

void update(int rt, int l, int r, int k) {
	if (l <= tr[rt].l && r >= tr[rt].r) {
		tr[rt].lazy = k;
		tr[rt].sum = 1;
		tr[rt].lnum = tr[rt].rnum = k;
		return;
	}
	push_down(rt);
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (l <= mid) update(rt << 1, l, r, k);
	if (r > mid) update(rt << 1 | 1, l, r, k);
	pushup(rt);
}
int check(int rt, int x) {
	if (tr[rt].l == tr[rt].r) {
		return tr[rt].lnum;
	}
	push_down(rt);
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (x <= mid) return check(rt << 1, x);
	else return check(rt << 1 | 1, x);
}



int main() {
	read(t);
	while (t--) {
		read(n, m);
		a[0] = INF;
		b[0] = INF; 
		for (int i = 1; i <= n; i++) {
			read(a[i]);
			b[i] = min(a[i], b[i - 1]);
		}
		build(1, 1, n);
		while (m--) {
			int k, d;
			read(k, d);
			a[k]-=d;
			int num = query_one(1, k-1);
			num = min(num,a[k]);
			int l = k+1, r = n;
			int ans = n+1;
			while (l <= r) {
				int mid = l + r >> 1;
				if (check(1, mid) <= num) {
					r = mid - 1;
					ans = mid;
				} else {
					l = mid + 1;
				}
			}
			update(1, k, ans - 1, num);
//			cout << "SUM: ";
			write(tr[1].sum);
//			LF;
			SP;
		}
		LF;
	}


	return 0;
}

```

---

