# Grouped Carriages

## 题目描述

Pak Chanek observes that the carriages of a train is always full on morning departure hours and afternoon departure hours. Therefore, the balance between carriages is needed so that it is not too crowded in only a few carriages.

A train contains $ N $ carriages that are numbered from $ 1 $ to $ N $ from left to right. Carriage $ i $ initially contains $ A_i $ passengers. All carriages are connected by carriage doors, namely for each $ i $ ( $ 1\leq i\leq N-1 $ ), carriage $ i $ and carriage $ i+1 $ are connected by a two-way door.

Each passenger can move between carriages, but train regulation regulates that for each $ i $ , a passenger that starts from carriage $ i $  cannot go through more than $ D_i $ doors.

Define $ Z $ as the most number of passengers in one same carriage after moving. Pak Chanek asks, what is the minimum possible value of $ Z $ ?

## 说明/提示

One strategy that is optimal is as follows:

- $ 5 $ people in carriage $ 1 $ move to carriage $ 4 $ (going through $ 3 $ doors).
- $ 3 $ people in carriage $ 5 $ move to carriage $ 3 $ (going through $ 2 $ doors).
- $ 2 $ people in carriage $ 6 $ move to carriage $ 5 $ (going through $ 1 $ door).
- $ 1 $ person in carriage $ 6 $ moves to carriage $ 7 $ (going through $ 1 $ door).

The number of passengers in each carriage becomes $ [2,4,5,5,4,5,4] $ .

## 样例 #1

### 输入

```
7
7 4 2 0 5 8 3
4 0 0 1 3 1 3```

### 输出

```
5```

# 题解

## 作者：Small_Tang (赞：7)

这是一个二分 + 贪心的做法。

很容易能联想到可以二分答案，每次考虑对于二分的 $mid$ 作为车厢的上限，判断是否容载的下。

那么对于从 $1$ 到 $n$，我们考虑尽可能将 $1$ 号车间装满，然后是 $2$ 号车间……最后是 $n$ 号车厢。

我们想到，如果乘客只能往后而不能往前的话，我们就只用从前往后把多出来的人数往后推就可以了。但可惜这题不是，但还是有一个办法能解决乘客能往前跑。

若第 $i$ 间车厢的要求是 $d_i$， 那么我们可以假设这批人换了一个位置，让他们只会往后面跑：他们的起点位于 $i-d_i$，而他们最远能去到 $i+d_i$ 间车厢。换句话说，左端点 $l_i$ 为 $i-d_i$，右端点 $r_i$ 为 $i+d_i$ 。

考虑用优先队列维护，枚举第 $i$ 个车厢，把 $l_j \le i$ 的车厢全部加入优先队列。然后将 $r_j$ 最小的车厢的人尽可能塞进当前车厢，判断是否将所有 $r_j\le i$ 的车厢给弹出优先队列就好了。注意记得清空优先队列和结尾的一些特判。复杂度 $O(n \log n \log a_i)$

---

献上我丑陋的代码：

```cpp
//love lotuses forever!
#include<bits/stdc++.h>
#define lot signed
#define Max 200100
#define int long long
#define dg(a) ((a)<'0'||(a)>'9')
using namespace std;

void read(int &r)
{
    r=0;char ch,f='t';ch=getchar();
    while(dg(ch)){f=ch;ch=getchar();}
    while(!dg(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
    if(f=='-')r=-r;
}

int n;
struct node{int x,l,r;}p[Max];
bool cmp(node _a,node _b){return _a.l<_b.l;}
bool operator<(node _a,node _b){return _a.r>_b.r;}
priority_queue<node>q;

bool check(int x)
{
    int pos=0;
    while(!q.empty())q.pop();
    for(int i=1;i<=n;i++)
    {
        while(pos<n&&p[pos+1].l<=i)
        {
            pos++;
            q.push(p[pos]);
        }

        int tot=x;
        while(tot&&!q.empty())
        {
            node u=q.top();
            q.pop();
            if(tot>=u.x)tot-=u.x;
            else
            {
                u.x-=tot;
                tot=0;
                q.push(u);
            }
        }
        
        while(!q.empty()&&!q.top().x)q.pop();
        if(!q.empty()&&q.top().r<=i)return 0;
    }
    if(!q.empty())return 0;
    return 1;
}

lot main()
{
    read(n);
    for(int i=1;i<=n;i++)read(p[i].x);
    for(int i=1;i<=n;i++)
    {
        int x;read(x);
        p[i].l=i-x;
        p[i].r=i+x;
    }

    sort(p+1,p+n+1,cmp);
    int l=0,r=1e9,x=1e9,mid;

    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(mid)){x=mid;r=mid-1;}
        else l=mid+1;
    }
    printf("%lld\n",x);
    return 0;
}
```

贴贴 @Lotuses

---

## 作者：苏联小渣 (赞：6)

有一个比较小丑的思路。

最大值最小考虑二分答案。二分最大值 $m$，问题转化成了，每个车厢 $x$ 的人可以到达 $[\max(x-d_x,1),\min(x+d_x,n)]$，最后每个车厢的人数是否都能 $\le m$。

我们发现这是一个网络流的模型。具体而言，设一个点 $x$ 能到达的区间为 $[l_x,r_x]$，我们把每个车厢拆成左部点和右部点（分别记为 $lf_x,rg_x$），然后这样连边：

- 从源点向每个 $lf_x$ 连一条流量为 $a_x$ 的边，表示初始人数；

- 从每个 $lf_x$ 向 $rg_{l_x},...,rg_{r_x}$ 连一条流量为 $a_x$ 的边，表示最多 $a_x$ 个人走到这个车厢；

- 从每个 $rg_x$ 向汇点连一条流量为 $m$ 的边，表示每个车厢最终的人数上限。

最后跑这个图的最大流，判断是否等于初始总人数即可。

---

暴力连边肯定会炸，即便是用线段树优化建图也不行，考虑模拟网络流。

模拟网络流的第一步是**转最小割**，然后我们观察这个网络流图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nloj9b97.png)

我们发现，割去中间的边一定不优，因为其代价等于左边的边，也就是说可以通过割去左边的边获得更小的代价。

所以我们得出一个性质：最小割的边集只可能是左部边或右部边，不可能是中间的边，

考虑如果我们保留从源点连向 $lf_x$ 的边，那么 $rg_{l_x},rg_{l_x+1},...,rg_{r_x}$ 连向汇点的边都要被割去。换句话说，如果 $rg_l,rg_{l+1},...,rg_r$ 连向汇点的边都被割去了，那么所有满足 $[l_x,r_x] \subseteq [l,r]$ 的 $x$ 对应的左部边（也就是源点连向 $lf_x$ 的边）都不必被割去。现在，问题就转化成了，选择一些区间，使得代价最小。其中代价可以这样描述：区间长度 $\times m$ 加上所有 $a_x$ 的和，满足 $[l_x,r_x]$ 未被任何一个选中的区间包含。

考虑 dp。定义 $f_i$ 表示考虑完所有 $r_x \le i$ 的区间后的答案。如果初始时 $f_i$ 为人数总和，那么有转移：

$$f_i=\min_{j=0}^{i-1}\{f_j+m(i-j)-\sum_{x=1}^n ([[l_x,r_x] \subseteq [i+1,j]]\times a_x)\}$$

$$f_i=\min(f_i,f_{i-1})$$

（其中 $[A]$ 表示若 $A$ 为真则值为 $1$，否则为 $0$）

$m(i-j)$ 很好处理。考虑如何快速计算后面那一坨式子的答案。其实就是所有被 $[i+1,j]$ 包含的区间的值之和。考虑在 dp 的过程中扫描线，按照右端点从小到大把每一个 $[l_x,r_x]$ 加入贡献。假设当前加入 $[l_x,r_x]$ 的贡献，那么它会让所有满足 $i<l_x$ 的 $f_i$ 减去 $a_x$。现在我们要支持的就是区间修改，区间查询最小值，用线段树维护即可。时间复杂度 $O(n \log^2 n)$。

注意如果直接写可能会被卡常，改成 zkw 线段树就可以通过了。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n, l, r, ans, a[200010], b[200010];
ll tot, f[200010];
struct node{
	int l, x;
};
vector <node> lef[200010];
inline int read(){
	int s=0, w=1; char ch=getchar();
	while (ch<'0' || ch>'9'){
		if (ch=='-') w=-1; ch=getchar();
	}
	while (ch>='0' && ch<='9'){
		s=(s<<3)+(s<<1)+(ch^48); ch=getchar();
	}
	return s*w;
}
struct segment{
	#define lc(x) x<<1
	#define rc(x) x<<1|1
	ll d[800010];
	int M = 262144;
	ll min(ll x, ll y){return x<y?x:y;}
	void clear(){
		for (int i=1; i<=(M+1)*2; i++) d[i] = 0;
	}
	void upd(int k){
		ll tmp = min(d[lc(k)], d[rc(k)]);
		d[lc(k)] -= tmp, d[rc(k)] -= tmp, d[k] += tmp;
	}
	void modify(int l, int r, ll x){
		l ++, r ++;
		for (l+=M-1, r+=M+1; l^r^1; l>>=1, r>>=1){
			if (~l&1) d[l^1] += x;
			if (r&1) d[r^1] += x;
			upd(l>>1), upd(r>>1);
		}
		for (; l!=1; l>>=1) upd(l>>1);
	}
	ll query(int l, int r){
		l ++, r ++;
		l += M, r += M;
		ll la = 0, ra = 0;
		for (; (l^r)>1; l>>=1, r>>=1){
			la += d[l], ra += d[r];
			if (~l&1) la = min(la, d[l^1]); 
			if (r&1) ra = min(ra, d[r^1]);
		}
		ll ans = min(la+d[l], ra+d[r]);
		for (; l>1; ) ans += d[l>>=1];
		return ans;
	}
}S;
int check(int x){
	if (1LL * x * n < tot) return 0;
	S.clear();
	for (int i=1; i<=n; i++){
		f[i] = 0;
		S.modify(i, i, -1LL*i*x);
	}
	for (int i=1; i<=n; i++){
		for (int j=0; j<lef[i].size(); j++){
			int l = lef[i][j].l, val = lef[i][j].x;
			S.modify(0, l-1, -val);
		}
		f[i] = S.query(0, i-1) + 1LL * i * x;
		f[i] = min(f[i], f[i-1]);
		if (f[i] < 0) return 0;
		S.modify(i, i, f[i]);
	}
	return f[n] >= 0;
}
int main(){
	n=read();
	l = 1e9, r = 1e9;
	for (int i=1; i<=n; i++){
		a[i]=read();
		tot += a[i];
		l = min(l, a[i]);
	}
	for (int i=1; i<=n; i++){
		b[i]=read();
		int lx = max(i-b[i], 1), rr = min(i+b[i], n);
		lef[rr].push_back((node){lx, a[i]});
	}
	while (l <= r){
		int mid = l + r >> 1;
		if (check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf ("%d\n", ans);
	return 0;
}
```

最后还是要强烈谴责这题的卡常行径。

---

## 作者：huangrenheluogu (赞：2)

求解比较困难，转化为判定问题。

感觉这个二分答案比较显然，~~但是在 CSP 的时候就想不到~~，还是不要问为什么想到，就是看完题目就想到了。我感觉二分答案是个精巧的东西，毕竟判定比求解简单太多了，虽然这玩意儿需要一个 $\log$。所以，答案有单调性的时候可以往这方面想想看。

扯远了。看看 check 函数。

先处理出每一个车厢的 $l$ 和 $r$。

我们枚举每一个位置 $i$，最大化 $i$ 中的人数。那如果有多余 $mid$ 个人可以选，选哪些呢？

都可以选择的情况下，显然 $r$ 越小更优。这个真的是显然的，因为 $r$ 更大的有更多选择的余地。

我使用 map 对 $r$ 到数量进行 hash，但是 map 常数比较大。

现在看来可能优先队列更快？

复杂度 $O(n\log |\sum a_i|\log n)$，但是因为 map，所以常数比较大，谨慎使用。

[code](https://codeforces.com/contest/1866/submission/239062785)

注意：本代码是在 CF 上 GNU C++17 (64) 通过本题，洛谷上 C++14 无法通过，需要 C++17（但是 CF 可以直接过掉，应该没问题）。

---

## 作者：xiezheyuan (赞：1)

## 思路

首先看到最大值最小，套路地二分，转换为判定性问题。

然后考虑判定性问题，如何使所有车厢人数均小于一个数 $x$？

考虑网络流建模，对于每一个车厢，建立两个点 $A_i,B_i$：

- 对于每一个 $A_i$，连边 $(S,A_i,x)$ 表示一个车厢只有不多于 $x$ 个人。
- 对于可能的一种移动策略 $i\to j$，连边 $(A_j,B_i,+\infty)$。表示车厢内可能的人移动策略。
- 对于每一个 $B_i$，连边 $(B_i,T,a_i)$ 表示这个车厢原来有 $a_i$ 个人。

如果最大流等于总人数，则可以，否则不可以。

注意左部点右部点不能交换，否则贪心没有正确性（Hack：样例）。

然后考虑如何模拟这个最大流，我们枚举左部点，然后设定当前流量，模拟寻找增广路的过程（由于这个图除了源点汇点只有两层，所以不需要递归）。

如何选择增广边呢？贪心地选择流向编号小的边，因为本题区间第 $i$ 个移动区间一定包含 $i$，所以到了后面编号大的边所可以匹配地左部点一定不少于编号小的，所以这个结论是正确的。

时间复杂度 $O(n\log n\log \sum a_i)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5+5;
int n,a[N],d[N],L,R,all;
struct node{
	int r,cap;
	bool operator<(const node &x) const {return r > x.r;}
	node(int R, int Cap){r = R, cap = Cap;}
};
priority_queue<node> q;
vector<node> rg[N];

bool check(int x){
	while(!q.empty()) q.pop();
	int total = 0, cap = 0;
	for(int i=1;i<=n;i++){
		for(node j : rg[i]) q.push(j);
		cap = x;
		while(cap && !q.empty()){
			node now = q.top();
			q.pop();
			if(!now.cap || now.r < i) continue;
			int flow = min(cap, now.cap);
			now.cap -= flow;cap -= flow;total += flow;
			q.push(now);
		}
	}
//	cout<<total<<' '<<all<<' '<<x<<'\n';
	return total == all;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	all = accumulate(a + 1, a + n + 1, 0ll);
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<=n;i++){
		L = max(i - d[i], 1ll);
		R = min(i + d[i], n);
		rg[L].push_back({R, a[i]});
	}
	L = 0, R = all;
	while(L <= R){
		int mid = (L + R) >> 1;
		if(check(mid)) R = mid - 1;
		else L = mid + 1;
	}
	cout<<L;
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：1)

义眼顶真，关于求最小方案优先考虑二分，答案显然有单调性。

所以如何 `check`？

观察样例，手摸发现好像可以通过把 当前的空缺位置留到后面，以及用空缺的位置去补后面的多出来的人。

突然发现这样子是双向的，从前往后和从后往前两种“留空缺”的方案好像都有可能出现。那这样的话，这样子贪，反而有点像个反悔贪心。

但是呢，发现这样并不能合并反悔的部分，因为人过来了并不代表人变成从这个车厢开始的。于是反悔过程需要记录你从哪里来，就不能很好的合并贪心结果。

那么怎么办？

发现上文中 **人过来了并不代表人变成这个车厢的人** 这句话很重要。因为这句话，我们完全可以将 `check` 要求的问题转换一个意思。

理由：所有人都可以等价（等价的含义：无论他怎么移动（特别的，不移动也是）都是相同的情况，不会影响到别人的移动）的放置在一个**可以确定的范围内的车厢**内，而且放置位置唯一。

新的 `check`：

1. 有一些人构成的小组，这些小组的所有人都可以被单独分别放置在一个 $[i-d_i,i+d_i]$ 的车厢内。
2. 要求如何放置可以使所有车厢都不超过 $k$（即 `check` 系数）个人。

考虑重新贪心。对于所有原始车厢，预处理出移动的左右边界。按照左端点从小到大排序，这样在选择某一车厢 $x$ 的时候能确保所有 $l_i\le x$ 的原始车厢进入了考虑列表中。

从左到右考虑移动后的车厢，维护一个队列，使队列内的原始车厢都能移动到当前正在确定方案的车厢。

考虑的车厢向右移动时，对于一部分 $r_i<x_{new}$ 要被移出考虑队列（如果还没有放完就表明不够放）

所以，考虑维护的是一个按照 $r_i$ 从小到大的优先队列。每次尽可能的放 $r_i$ 最小的原始车厢进入当前车厢。

进入队列的所有当前车厢除了右端点之外等价。所以优先选右端点靠左的，才更有可能放完。

一个小小的证明：假设某一次选择时选择右端点靠右的更优。

对于某一次从靠左改为靠右，相当于从原先选择的靠左的连续块中挑出一个和后面靠右的其中一个交换。

当能找到在限制范围内的交换时，情况等价，不会更优；

当找不到限制范围内的交换时，会出现本来合法交换之后不合法的现象，不优。

因此不会更优。

于是就有了 `check` 的贪心方案，模拟即可。

```cpp
// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

#define int long long

const int maxn = 4e5 + 10;
int n, ix, c[maxn], ls[maxn], id[maxn];
struct Point {
    int l, r, id;
    bool operator < (const Point &y) const {
        return r > y.r;
    } 
} p[maxn];
std::priority_queue<Point> q;

bool check(int cap) {
    while (!q.empty()) q.pop();
    memcpy(ls, c, sizeof(int) * (n + 5));
    int idx = 1, cp;
    for (int i = 1; i <= n; i++) {
        if (!q.empty() && q.top().r < i) return 0;
        while (idx <= n && p[idx].l <= i) {
            q.push(p[idx++]);
        }
        cp = cap;
        while (cp && !q.empty()) {
            int dec = std::min(cp, ls[q.top().id]);
            cp -= dec;
            if (!(ls[q.top().id] -= dec)) q.pop();
        }
        while (!q.empty() && !ls[q.top().id]) q.pop();
    }
    return q.empty();
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(ls[i]);
        id[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        read(ix);
        p[i].l = i - ix; p[i].r = i + ix;
    }

    std::sort(id + 1, id + n + 1, [](int x, int y) {
        return p[x].l < p[y].l;
    });
    for (int i = 1; i <= n; i++) {
        c[i] = ls[id[i]];
    }
    std::sort(p + 1, p + n + 1, [](Point x, Point y) {
        return x.l < y.l;
    });
    int idx = 0;
    std::for_each(p + 1, p + n + 1, [&idx](Point &x) {
        x.id = ++idx;
    });

    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    writeln(r);
    return 0;
}
```
贴贴 @Small_Tang

---

## 作者：Svemit (赞：0)

[link](https://codeforces.com/problemset/problem/1866/G)

每个车厢的人可以到的是一段区间。

题面显然提示二分答案，二分答案 $x$，每个车厢可以承受 $x$ 个人，考虑如何 check 每个人能否都能到一个区间。

有一个比较显然的网络流来 check 的做法，原点向每个车厢连流量 $a_i$ 的边，每个车厢向自己能到的区间连边，然后每个区间再向汇点连流量为 $x$ 的边，检验是否满流即可。

但是直接建图显然会爆。

考虑贪心：从左往右扫，每次选择能匹配的最靠右的区间匹配。扫到一个点就把这个点作为左区间的区间全部塞进一个优先队列里，然后把当前这个点的 $x$ 个点尽量用完。

```cpp
int n;
int a[N], d[N];
vector<PII> g[N];
bool check(int x) {
	priority_queue<PII, vector<PII>, greater<PII> > q;
	rep(i, 1, n) {
		for(auto t : g[i]) if(t.se) {
			q.push(t);
		}
		int cur = x;
		while(cur > 0 && q.size()) {
			auto t = q.top();
			q.pop();
			if(t.fi < i) return false;
			int tmp = min(t.se, cur);
			t.se -= tmp, cur -= tmp;
			if(t.se) q.push(t);
		}
	}
	if(q.size()) return false;
	return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> d[i];
	rep(i, 1, n) {
		int l = max(1, i - d[i]), r = min(n, i + d[i]);
		g[l].push_back({r, a[i]});
	}
	int l = 0, r = 1e9, res = 1e9;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) res = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << res << '\n';
    return 0;
}
```

---

