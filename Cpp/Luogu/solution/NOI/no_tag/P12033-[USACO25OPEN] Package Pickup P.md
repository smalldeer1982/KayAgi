# [USACO25OPEN] Package Pickup P

## 题目描述

**注意：本题的时间限制为 4 秒，是默认值的 2 倍。**

农夫约翰（Farmer John）按照以下奇怪的方式在数轴上分布了奶牛和包裹：

*   农夫约翰选择一个数字 $M$（$1 \le M \le 10^{18}$）。
*   农夫约翰选择 $N$（$1 \le N \le 2 \cdot 10^4$）个区间 $[L_i, R_i]$ 来分布奶牛（$1 \le L_i \le R_i \le 10^{18}$）。然后他在位置 $L_i, L_i + M, L_i + 2M, \dots, R_i$ 放置奶牛。保证 $R_i - L_i$ 是 $M$ 的倍数。
*   农夫约翰选择 $P$（$1 \le P \le 2 \cdot 10^4$）个区间 $[A_j, B_j]$ 来分布包裹（$1 \le A_j \le B_j \le 10^{18}$）。然后他在位置 $A_j, A_j + M, A_j + 2M, \dots, B_j$ 放置包裹。保证 $B_j - A_j$ 是 $M$ 的倍数。

一旦奶牛和包裹分布完毕，农夫约翰想知道奶牛们捡起所有包裹需要多长时间。每一秒，农夫约翰可以用他方便的对讲机（walkie talkie）向**一头**奶牛发出指令，让其从当前位置向左或向右移动一个单位。如果一头奶牛移动到包裹所在的位置，它就能捡起该包裹。农夫约翰想知道，奶牛们捡起所有包裹所需的最少时间（以秒为单位）。

## 说明/提示

### 样例 1 解释

在上面的测试用例中，假设奶牛和包裹从左到右编号。农夫约翰可以按照以下步骤在 22 秒内捡起所有包裹：

*   向奶牛 1 发出 3 次向左指令，使其捡起包裹 1。
*   向奶牛 3 发出 3 次向右指令，使其捡起包裹 7。
*   向奶牛 2 发出 4 次向右指令，使其捡起包裹 5。
*   向奶牛 1 发出 10 次向右指令，使其捡起包裹 2、3 和 4。
*   向奶牛 2 发出 2 次向右指令，使其捡起包裹 6。

### 测试点限制

*   测试点 3-4：保证奶牛和包裹的总数不超过 $2 \cdot 10^5$。
*   测试点 5-10：保证 $N, P \le 500$。
*   测试点 11-13：保证包裹或奶牛的区间均不相交。
*   测试点 14-20：无额外限制。

## 样例 #1

### 输入

```
100 3 7
10 10
20 20
30 30
7 7
11 11
13 13
17 17
24 24
26 26
33 33```

### 输出

```
22```

## 样例 #2

### 输入

```
2 1 1
1 5
2 6```

### 输出

```
3```

# 题解

## 作者：raincity (赞：5)

## 题意

数轴上的一些整点上放了牛和草。你每秒可以选择一头牛，令其向左或向右移动一个单位长度。每当一头牛和一捆草位于同一个位置时，牛就会吃掉这捆草。求吃完所有草的最短时间。

牛和草的初始位置以特殊方式给出：给定一个常量 $m$。对于牛，给出 $n$ 个区间 $[l, r]$，表示 $l, l + m, l + 2m, \dots, r$ 这些位置放了牛，保证 $m \mid (r - l)$。对于草同理。

## 分析

先考虑 Subtask 1，即牛和草的总数不超过 $2 \times 10^5$ 时怎么做。

考虑分析一头牛的行为。一头牛可以吃光它经过的所有位置上放的草，而它经过的所有位置是一段区间。并且，牛经过了整个区间，当且仅当它经过了区间的左右端点，因此固定区间时一头牛的代价很容易计算出来。

考虑分析所有牛的行为。通过调整法可以发现，可以认为任意两头牛的区间都是不交的。

考虑一个很暴力的转化：把数轴按照牛和草初始所在的位置分段，则最优解中每一段中所有边经过的次数相等，且均为 $0, 1, 2$。因此直接枚举的状态量非常少。

考虑判定一个 $0, 1, 2$ 的方案是否合法。考虑找充要条件。列几个条件可以发现，合法当且仅当：

- 草两侧两条线段不同时为 $0$，不分别为 $1$ 和 $2$。
- 牛两侧两条线段不同时为 $1$，不同时为 $2$。
- 每个非 $0$ 的段至少经过一头牛。

用这个充要条件容易写出 DP。设 $f_{i, j}$（$j \in [0, 4]$）表示：考虑了与前 $i$ 个牛和草相邻的边，

- $j = 0$：最后一段未经过牛，最后一条边权值为 $1$。
- $j = 1$：最后一段未经过牛，最后一条边权值为 $2$。
- $j = 2$：最后一段已经过牛，最后一条边权值为 $1$。
- $j = 3$：最后一段已经过牛，最后一条边权值为 $2$。
- $j = 4$：最后一条边权值为 $0$。

转移是容易的。注意特判同一个位置有两头牛的情况，此时两头牛可以分别移动。

然后一般情况是容易的。观察到 $m$ 为定值，考虑每次跳过一个周期。本质不同的周期个数是 $O(n)$ 的。转移可以用 $(\min, +)$ 矩阵乘法描述。线段树 + 快速幂即可，复杂度 $O(n \log m)$，带 $5^3$ 的常数。

## 实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define all(x) begin(x), end(x)
#define sz(x) int((x).size())

using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;

struct Mat {
    ll a[5][5];

    Mat operator*(const Mat &b) const {
        Mat ans;
        memset(ans.a, 0x3f, sizeof ans.a);
        rep (i, 0, 4)
            rep (j, 0, 4)
                rep (k, 0, 4)
                    ans.a[i][k] = min(ans.a[i][k], a[i][j] + b.a[j][k]);
        return ans;
    }

    static Mat Make(int b, ll d) {
        Mat ans;
        memset(ans.a, 0x3f, sizeof ans.a);
        if (b == 0) {
            fill(all(ans.a[2]), d);
            fill(all(ans.a[3]), 2 * d);
            memset(ans.a[4], 0, sizeof ans.a[4]);
        } else if (b == 1) {
            ans.a[2][1] = ans.a[2][2] = ans.a[2][4] = d;
            ans.a[3][0] = ans.a[3][3] = ans.a[3][4] = 2 * d;
            memset(ans.a[4], 0, sizeof ans.a[4]);
        } else {
            ans.a[0][0] = ans.a[0][4] = d;
            ans.a[1][1] = ans.a[1][4] = 2 * d;
            ans.a[2][2] = d;
            ans.a[3][3] = 2 * d;
            ans.a[4][2] = ans.a[4][3] = 0;
        }
        return ans;
    }
};

struct I {
    ll c, g;
    ll bg, ed;
    int b;
    Mat mul;

    I operator+(const I &x) const {
        if (c == 0 && g == 0 && x.c == 0 && x.g == 0)
            return {.ed = ed + x.ed};
        if (c == 0 && g == 0) {
            I ans = x;
            ans.bg += ed;
            return ans;
        }
        if (x.c == 0 && x.g == 0) {
            I ans = *this;
            ans.ed += x.ed;
            return ans;
        }
        return {c + x.c, g + x.g, bg,
                x.ed,    x.b,     x.mul * Mat::Make(b, ed + x.bg) * mul};
    }

    I operator*(ll n) const {
        assert(n >= 0);
        I ans = {}, add = *this;
        for (; n > 0; n >>= 1) {
            if ((n & 1) == 1)
                ans = ans + add;
            add = add + add;
        }
        return ans;
    }
};

vector<ll> raw;

struct SegT {
    static constexpr int N = (1 << 16) + 10;

    int n;
    I t[2 * N];

    void Build() {
        n = sz(raw) == 2 ? 1 : 2 << (31 ^ __builtin_clz(sz(raw) - 2));
        rep (i, 0, n - 1) {
            t[i + n] = {.ed = i <= sz(raw) - 2 ? raw[i + 1] - raw[i] : 0};
            memset(t[i + n].mul.a, 0x3f, sizeof t[i + n].mul.a);
            rep (j, 0, 4)
                t[i + n].mul.a[j][j] = 0;
        }
        for (int i = n - 1; i >= 1; --i)
            t[i] = t[2 * i] + t[2 * i + 1];
    }

    void Upd(int x, ll c, ll g) {
        x += n;
        t[x].c += c, t[x].g += g;
        if (t[x].c > 1) {
            t[x].b = 0;
        } else if (t[x].c > 0) {
            t[x].b = 1;
        } else if (t[x].g > 0) {
            t[x].b = 2;
        }
        while (x > 1) {
            x >>= 1;
            t[x] = t[2 * x] + t[2 * x + 1];
        }
    }

    I Qry() {
        return t[1];
    }
} sgt;

ll m;
int n, p;

struct E {
    ll t, c, g;

    bool operator<(E x) const {
        return t < x.t;
    }
};

vector<E> e;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cin >> m >> n >> p;
    raw = {0, m};

    rep (i, 1, n) {
        ll l, r;
        cin >> l >> r;
        raw.push_back(l % m);
        e.push_back({l, 1, 0}), e.push_back({r + m, -1, 0});
    }

    rep (i, 1, p) {
        ll l, r;
        cin >> l >> r;
        raw.push_back(l % m);
        e.push_back({l, 0, 1}), e.push_back({r + m, 0, -1});
    }

    sort(all(raw));
    raw.erase(unique(all(raw)), end(raw));
    sort(all(e));
    sgt.Build();
    I ans = {};
    ll lst = -1;
    for (auto [t, c, g] : e) {
        if (lst != -1)
            ans = ans + sgt.Qry() * (t / m - lst);
        lst = t / m;
        sgt.Upd(lower_bound(all(raw), t % m) - begin(raw), c, g);
    }

    ll f[5];
    rep (i, 0, 4)
        f[i] = ans.mul.a[i][4];
    if (ans.b <= 1)
        cout << *min_element(all(f)) << '\n';
    else
        cout << min(f[2], f[3]) << '\n';
}
```

---

## 作者：SDSXC (赞：1)

首先我们考虑 Subtask 1 怎么做。

我们先处理出每个人和物品的位置。

然后我们考虑一个人的策略，一个人的移动轨迹一定是形如一个区间，那么每个人在他的管辖区间中一定是在初始位置的一边走两次(一个来回)，另外一边走一次(单程)。并且所有人的管辖区间一定不交。

我们设计 dp，$f_{i,0/1/2/3/4}$，分别表示从开始以第 $i$ 个位置结尾的区间，最后一段是：

* 人不经过(两人管辖区间的间隔)
* 人经过1次，未经过人的初始位置
* 人经过2次，未经过人的初始位置
* 人经过1次，已经过人的初始位置
* 人经过2次，已经过人的初始位置

转移是容易的。

我们发现转移仅仅与第 $i$ 个位置是人还是物，以及 $i$ 与 $i-1$ 之间的距离有关。

因此，我们容易发现，我们按照每 $M$ 格分块，每一块与上一块的转移不同一定满足这一块或其上一块中有题中给定的 $N+P$ 个区间的端点，因此本质不同的块不超过 $O(N+P)$ 个。

所以我们把转移写成 $(\min,+)$ 矩阵乘法的形式，然后使用线段树维护当前区间端点所在块的矩阵。考虑如何从一个区间端点跳到下一个，其中经过若干个完整的长为 $M$ 的块以及开头和结尾的一些散块，整块我们使用矩阵快速幂，散块使用线段树查询，然后把这个端点涉及位置在线段树上修改了，这样我们就可以快速完成从一个端点跳到下一个端点了，而这样的端点只有 $O(N+P)$ 个。

所以总的复杂度是 $O((N+P)(\log (N+P)+\log \frac{L}{M}))$，$L$ 表示数轴的长度，由于包含一个 $5\times5$ 的矩阵乘法所以常数很大。

最后是一些需要注意的实现细节。首先你在块中添加或者删除一个位置的时候是会影响到后一个位置的，因为它到前一个位置的距离变了，还有就是每个区间的第一个是可能与后面位置不同的，需要特殊处理。可能同一个位置上有多个物品或人，可以在离散化的时候强制钦定一个顺序。

代码比较难写。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3fll
#define N 40009
#define ll long long
#define ls (rt<<1)
#define rs (rt<<1|1)
using namespace std;
struct mat{
	ll a[5][5];
	void init(){memset(a,0x3f,sizeof(a));}
	mat operator*(const mat b){
		mat ret;ret.init();
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				for(int k=0;k<5;k++)ret.a[i][k]=min(ret.a[i][k],a[i][j]+b.a[j][k]);
			}
		}
		return ret;
	}
} tr[N<<2];
mat get(int x,ll y){
	mat ret;ret.init();
	if(x==2){
		for(int i=0;i<=4;i++)ret.a[i][i]=0;
	}
	else if(x==1){
		ret.a[3][0]=y<<1,ret.a[3][2]=y<<1,ret.a[4][0]=y,ret.a[4][1]=y;
		ret.a[3][3]=0,ret.a[3][4]=0,ret.a[4][3]=0,ret.a[4][4]=0;
	}
	if(!x){
		ret.a[0][3]=ret.a[0][4]=0;
		ret.a[1][0]=ret.a[1][1]=y;
		ret.a[2][0]=ret.a[2][2]=y<<1;
		ret.a[3][3]=y;
		ret.a[4][4]=y<<1;
	}
	return ret;
}
inline void up(int rt){tr[rt]=tr[rs]*tr[ls];}
void build(int rt,int l,int r){
	tr[rt]=get(2,0);
	if(l!=r){
		int mid=(l+r>>1);
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
}
void upd(int rt,int l,int r,int x,mat v){
	if(l==r)tr[rt]=v;
	else{
		int mid=(l+r>>1);
		if(x<=mid)upd(ls,l,mid,x,v);
		else upd(rs,mid+1,r,x,v);
		up(rt);
	}
}
mat qry(int rt,int l,int r,int ql,int qr){
	if(ql>r||qr<l)return get(2,0);
	else if(ql<=l&&qr>=r)return tr[rt];
	else{
		int mid=(l+r>>1);
		return qry(rs,mid+1,r,ql,qr)*qry(ls,l,mid,ql,qr);
	}
}
ll M;int n,m,tot;
struct node1{
	int typ;
	ll l,r;
	bool operator<(const node1 &b){
		return l%M<b.l%M;
	}
} a[N];
struct node2{
	int id,typ;
	ll pos;
	bool operator<(const node2 &b){
		return pos<b.pos||(pos==b.pos&&id<b.id);
	}
} b[N<<1];
set<int> st;
mat qpow(mat x,ll y){
	mat z=get(2,0);
	while(y){
		if(y&1)z=z*x;
		x=x*x;y>>=1;
	}
	return z;
}
ll ps[N];
ll d[N];int tp[N];
bool is[N];
mat sum(ll x,int idx,ll y,int idy){
	if(x>y||x==y&&idx>idy)return get(2,0);
	if(x==y){
		return qry(1,1,n,idx,idy);
	}
	else if(x==y-1){
		return qry(1,1,n,1,idy)*qry(1,1,n,idx,n);
	}
	else{
		return qry(1,1,n,1,idy)*qpow(tr[1],y-x-1)*qry(1,1,n,idx,n);
	}
}
inline void findnxt(ll &x,int &y){
	if(y==n){++x,y=1;}
	else ++y;
}
inline void findlst(ll &x,int &y){
	if(y==1){--x,y=n;}
	else --y;
}
inline ll getpos(ll x,int y){
	return x*M+ps[y];
}
ll ans[5]={INF,INF,INF,INF,INF};
void add(mat tmp){
	for(int j=0;j<5;j++){
		for(int k=0;k<5;k++){
			tmp.a[j][k]+=ans[k];
		}
	}
	for(int j=0;j<5;j++){
		ans[j]=INF;
		for(int k=0;k<5;k++){
			ans[j]=min(ans[j],tmp.a[j][k]);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>M>>n>>m;
	for(int i=1;i<=n;i++){
		ll x,y;cin>>x>>y;
		a[++tot]=node1{1,x,y};
	}
	for(int i=1;i<=m;i++){
		ll x,y;cin>>x>>y;
		a[++tot]=node1{0,x,y};
	}sort(a+1,a+tot+1);
	for(int i=1;i<=tot;i++){
		ps[i]=a[i].l%M;
		b[i*2-1]=node2{i,a[i].typ,a[i].l};
		b[i<<1]=node2{i,a[i].typ,a[i].r+M};
	}n=tot;tot<<=1;sort(b+1,b+tot+1);
	b[0]=b[1];build(1,1,n);ll lst=b[1].pos/M;int lid=b[1].id;
	if(b[1].typ)ans[3]=ans[4]=0;else ans[0]=0;
	st.insert(lid);upd(1,1,n,lid,get(b[1].typ,M));d[lid]=M;
	is[lid]=1;tp[lid]=b[1].typ;
	for(int i=2;i<=tot;i++){
		int nid=b[i].id;ll now=b[i].pos/M;
		findlst(now,nid);findnxt(lst,lid);
		add(sum(lst,lid,now,nid));findnxt(now,nid);findlst(lst,lid);
		if(is[nid]){
			st.erase(nid);
			upd(1,1,n,nid,get(2,0));
			if(!st.empty()){
				auto it=st.upper_bound(nid);
				if(it==st.end())it=st.begin();
				int t=*it;
				d[t]+=d[nid];
				upd(1,1,n,t,get(tp[t],d[t]));
			}
			d[nid]=tp[nid]=0;
		}
		else{
			d[nid]=ps[nid];tp[nid]=b[i].typ;
			bool flag=0;
			if(!st.empty()){
				auto it=st.lower_bound(nid);
				if(it==st.begin())it=st.end(),d[nid]+=M;--it;
				d[nid]-=ps[*it];
			}else d[nid]=M,flag=1;
			if(!st.empty()){
				auto it=st.upper_bound(nid);
				if(it==st.end())it=st.begin();
				int t=*it;
				d[t]-=d[nid];
				upd(1,1,n,t,get(tp[t],d[t]));
			}
			if(flag)add(get(tp[nid],getpos(now,nid)-getpos(lst,lid)+M));
			else add(get(tp[nid],d[nid]));
			upd(1,1,n,nid,get(tp[nid],d[nid]));
			st.insert(nid);is[nid]=1;
		}
		lid=nid;lst=now;
	}
	cout<<min(ans[3],ans[4])<<"\n";
	return 0;
}
```

---

## 作者：cqbzlzm (赞：0)

### Description

农夫约翰（Farmer John）按照以下奇怪的方式在数轴上分布了奶牛和包裹：

*   农夫约翰选择一个数字 $M$（$1 \le M \le 10^{18}$）。
*   农夫约翰选择 $N$（$1 \le N \le 2 \cdot 10^4$）个区间 $[L_i, R_i]$ 来分布奶牛（$1 \le L_i \le R_i \le 10^{18}$）。然后他在位置 $L_i, L_i + M, L_i + 2M, \dots, R_i$ 放置奶牛。保证 $R_i - L_i$ 是 $M$ 的倍数。
*   农夫约翰选择 $P$（$1 \le P \le 2 \cdot 10^4$）个区间 $[A_j, B_j]$ 来分布包裹（$1 \le A_j \le B_j \le 10^{18}$）。然后他在位置 $A_j, A_j + M, A_j + 2M, \dots, B_j$ 放置包裹。保证 $B_j - A_j$ 是 $M$ 的倍数。

一旦奶牛和包裹分布完毕，农夫约翰想知道奶牛们捡起所有包裹需要多长时间。每一秒，农夫约翰可以用他方便的对讲机（walkie talkie）向**一头**奶牛发出指令，让其从当前位置向左或向右移动一个单位。如果一头奶牛移动到包裹所在的位置，它就能捡起该包裹。农夫约翰想知道，奶牛们捡起所有包裹所需的最少时间（以秒为单位）。

### Solution

从牛和从草的移动上去考虑都不好搞，考虑刻画牛的轨迹，用一段路被牛走过的次数 0 或 1 或 2 来刻画。

寻找一个 012 序列合法的充要条件：

1. 草两侧线段不是 00 不是 12 不是 21
2. 牛两侧线段不是 11 不是 22
3. 每个非 0 段要至少经过一头牛

可以 dp，设 $f_{i,j}$,$j\in[0,4]$ 表示：

1. $j=0$：最后一段未经过牛，最后一条边权值为 1。
2. $j=1$：最后一段未经过牛，最后一条边权值为 2。
3. $j=2$：最后一段已经过牛，最后一条边权值为 1。
4. $j=3$：最后一段已经过牛，最后一条边权值为 2。
5. $j=4$：最后一条边权值为 0。

转移简单。

考虑优化，注意到把数轴按照 M 分段，牛和草分布不同的段实际只有 $O(n)$ 个。

可以用 $(\min,+)$ 处理转移，用线段树维护当前长为 M 的区间的转移矩阵。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MAXN = 4e4, inf = 1e18;
int m, n, p;
struct ddd {
    int pos, cow, grass;
} ;
vector<ddd> vec;
vector<int> B;

struct matrix {
    int a[5][5];
    /*
    j = 0 : 最后一段未经过牛，最后一条边权值为 1
    j = 1 : 最后一段未经过牛，最后一条边权值为 2
    j = 2 : 最后一段已经过牛，最后一条边权值为 1
    j = 3 : 最后一段已经过牛，最后一条边权值为 2
    j = 4 : 最后一条边权值为 0
    */
    matrix() {
        memset(a, 0x3f, sizeof(a));
    }
    matrix friend operator * (matrix a, matrix b) {
        matrix c;
        for (int i = 0; i < 5; i ++)
            for (int k = 0; k < 5; k ++)
                for (int j = 0; j < 5; j ++)
                    c.a[i][j] = min(c.a[i][j], a.a[i][k] + b.a[k][j]);
        return c;
    }
    void print() {
        for (int i = 0; i < 5; i ++) {
            for (int j = 0; j < 5; j ++) {
                cout<<a[i][j]<<' ';
            }cout<<endl;
        }cout<<endl;
    }
};
matrix make(int op, int d) {
    matrix a;
    if (op == 2) { // 草
    /*
        1----
        -2---
        --1-0
        ---20
        12---
    */
        a.a[0][0] = 1 * d;
        a.a[1][1] = 2 * d;
        a.a[2][2] = 1 * d;
        a.a[2][4] = 0;
        a.a[3][3] = 2 * d;
        a.a[3][4] = 0;
        a.a[4][0] = 1 * d;
        a.a[4][1] = 2 * d;
        return a;
    }
    if (op == 1) { // 一头牛
    /*
        ---20
        --1-0
        ---20
        --1-0
        --120
    */   
        a.a[0][3] = 2 * d;
        a.a[0][4] = 0;
        a.a[1][2] = 1 * d;
        a.a[1][4] = 0;
        a.a[2][3] = 2 * d;
        a.a[2][4] = 0;
        a.a[3][2] = 1 * d;
        a.a[3][4] = 0;
        a.a[4][2] = 1 * d;
        a.a[4][3] = 2 * d;
        a.a[4][4] = 0;
        return a;
    }
    if (op == 0) { // 两头牛
    /*
        --120
        --120
        --120
        --120
        --120
    */   
        a.a[0][2] = 1 * d;
        a.a[0][3] = 2 * d;
        a.a[0][4] = 0;
        a.a[1][2] = 1 * d;
        a.a[1][3] = 2 * d;
        a.a[1][4] = 0;
        a.a[2][2] = 1 * d;
        a.a[2][3] = 2 * d;
        a.a[2][4] = 0;
        a.a[3][2] = 1 * d;
        a.a[3][3] = 2 * d;
        a.a[3][4] = 0;
        a.a[4][2] = 1 * d;
        a.a[4][3] = 2 * d;
        a.a[4][4] = 0;
        return a;
    }
}
struct node {
    int cow, grass, pre, suf, op;
    /*
    0 : 2 头牛
    1 : 1 头牛
    2 ：草
    */
    matrix f;
    node(){cow=grass=pre=suf=op=0;}
    node(int a,int b,int c,int d,int e,matrix ff){cow=a,grass=b,pre=c,suf=d,op=e,f=ff;}
    node friend operator + (node a, node b) {
        if (a.cow == 0 && a.grass == 0 && b.cow == 0 && b.grass == 0) {
            return {0, 0, 0, a.suf + b.suf, 0, matrix()};
        }
        if (a.cow == 0 && a.grass == 0) {
            b.pre += a.suf;
            return b;
        }
        if (b.cow == 0 && b.grass == 0) {
            a.suf += b.suf;
            return a;
        }
        return {a.cow + b.cow, a.grass + b.grass, a.pre, b.suf, b.op, a.f * make(a.op, a.suf + b.pre) * b.f};
    }
    
    node friend operator ^ (node a, int b) {
        
        node ans;
        // a.f.print();
        
        // cout<<b<<endl;
        while (b) {
            if (b & 1) ans = ans + a;
            a = a + a;
            b >>= 1;
        }
        // ans.f.print();
        return ans;
    }
};
namespace fhz {
    node seg[MAXN * 4 + 5];
    void pushup(int id) {
        seg[id] = seg[id << 1] + seg[id << 1 | 1];
        return ;
    }
    void build(int id, int l, int r) {
        if (l == r) {
            seg[id].suf = B[l + 1] - B[l];
            for (int i = 0; i < 5; i ++)
                seg[id].f.a[i][i] = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        pushup(id);
        // cout<<l<<' '<<r<<' '<<seg[id].suf<<endl;
        return ;
    }
    void modify(int id, int l, int r, int x, int cow, int grass) {
        if (l == r) {
            seg[id].cow += cow;
            seg[id].grass += grass;
            if (seg[id].cow >= 2) seg[id].op = 0;
            else if (seg[id].cow == 1) seg[id].op = 1;
            else seg[id].op = 2;
            return ;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) modify(id << 1, l, mid, x, cow, grass);
        else modify(id << 1 | 1, mid + 1, r, x, cow, grass);
        pushup(id);
        return ;
    }
    node query() {
        return seg[1];
    }
}

signed main() {
    // #ifndef LOCAL
    //     freopen("package.in", "r", stdin);
    //     freopen("package.out", "w", stdout);
    // #endif
    scanf("%lld%lld%lld", &m, &n, &p);
    for (int i = 1; i <= n; i ++) {
        int l, r; scanf("%lld%lld", &l, &r);
        B.push_back(l % m);
        vec.push_back({l, 1, 0});
        vec.push_back({r + m, -1, 0});
    }
    B.push_back(0); B.push_back(m);
    for (int i = 1; i <= p; i ++) {
        int l, r; scanf("%lld%lld", &l, &r);
        B.push_back(l % m);
        vec.push_back({l, 0, 1});
        vec.push_back({r + m, 0, -1});
    }
    sort(B.begin(), B.end()); B.erase(unique(B.begin(), B.end()), B.end());
    fhz::build(1, 0, B.size() - 2);

    sort(vec.begin(), vec.end(), [](ddd a, ddd b) {
        return a.pos < b.pos;
    });
    int lst = -1;
    node ans;
    for (auto tmp : vec) {
        int pos = tmp.pos, grass = tmp.grass, cow = tmp.cow;
        if (lst != -1 && (pos / m - lst) != 0) {
            // cout<<ans.cow<<' '<<ans.grass<<endl;
            ans = ans + (fhz::query() ^ (pos / m - lst));
        }
        // ans.f.print();
        lst = pos / m;
        fhz::modify(1, 0, B.size() - 2, lower_bound(B.begin(), B.end(), pos % m) - B.begin(), cow, grass);
    }
    if (ans.op == 2) { // 草
        int rr = min(ans.f.a[4][2], ans.f.a[4][3]);
        cout<<rr;
    } else {
        int rr = min({ans.f.a[4][0], ans.f.a[4][1], ans.f.a[4][2], ans.f.a[4][3], ans.f.a[4][4]});
        cout<<rr;
    }
    return 0;
}
```

---

