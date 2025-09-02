# [JOIG 2024] 感染シミュレーション / Infection Simulation

## 题目描述

昨天，$N$ 位顾客光顾了 EGOI 自助餐厅。顾客编号从 $1$ 到 $N$，顾客 $i(1\le i\le N)$ 到达时间为 $L_i$，离开时间为 $R_i$。今天，我们发现有一位顾客来店时感染了目前在 JOI 国流行的新型传染病 X。

传染病 X 的**传染性**用整数 $x$ 表示。具体来说，对于 $1\le i\le N$，当顾客 $i$ 与一个或多个感染者同时进入餐厅的累计总时间至少达到 $x$ 时，顾客 $i$ 就会成为新感染者。

现在，由于 JOI 国采取了严格的感染控制措施，因此必须确定感染者人数。然而，问题在于调查组并不知道哪些人感染了传染病，而代表传染性的整数 $x$ 的值也是未知数。

因此，EGOI 自助餐厅经理理惠决定对于 $Q$ 种情况，分别求出最终会有多少顾客被感染。在第 $j(1\le j\le Q)$ 种情况下，最初只有顾客 $P_j$ 受到感染，传染性为 $X_j$。

根据到店顾客的信息，求出每种情况下最终的感染人数。注意，即使受感染的人数是在他们离开餐厅时被感染的，也应包括在内。此外，还假定一旦顾客感染了传染病 X，他就不能再被感染。

## 说明/提示

#### 【样例解释 #1】

在第 $1$ 个询问中，初始的感染者是顾客 $1$，传染性为 $15$，因此感染的传播方式如下

- 在时间 $10$，顾客 $1$ 到达餐厅；
- 在时间 $20$，顾客 $2$ 到达餐厅；
- 在时间 $35$，顾客 $2$ 与顾客 $1$ 同时出现在餐厅累计时间为 $15$，顾客 $2$ 被感染；
- 在时间 $40$，顾客 $1$ 离开餐厅；
- 在时间 $45$，顾客 $3$ 到达餐厅；
- 在时间 $60$，顾客 $3$ 与顾客 $2$ 同时出现在餐厅累计时间为 $15$，顾客 $3$ 被感染；与此同时，顾客 $3$ 离开餐厅；
- 在时间 $70$，顾客 $4$ 到达餐厅；
- 在时间 $80$，顾客 $2$ 离开餐厅；
- 在时间 $95$，顾客 $4$ 与顾客 $2$ 同时出现在餐厅累计时间为 $10$，因此顾客 $4$ 未感染；与此同时，顾客 $4$ 离开餐厅。

最终顾客 $1,2,3$ 被感染，共 $3$ 人，故第 $1$ 个询问答案为 $3$。

该样例满足子任务 $4,5,6,8,9,10$ 的限制。

#### 【样例解释 #2】

- 在第 $1$ 个询问中，$7$ 个顾客 $1,2,3,4,6,7,8$ 最终被感染，答案为 $7$。
- 在第 $2$ 个询问中，$1$ 个顾客 $1$ 最终被感染，答案为 $1$。
- 在第 $3$ 个询问中，$5$ 个顾客 $2,3,4,7,8$ 最终被感染，答案为 $5$。

该样例满足子任务 $2,3,4,5,6,10$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $1,2,3,5,6,8,10$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $4,5,6,9,10$ 的限制。

#### 【样例解释 #5】

该样例满足子任务 $4,5,6,7,8,9,10$ 的限制。

#### 【样例解释 #6】

该样例满足子任务 $4,5,6,7,8,10$ 的限制。

#### 【样例解释 #7】

该样例满足子任务 $4,5,6,7,9,10$ 的限制。

#### 【数据范围】

- $1\le N\le 10^5$；
- $0\le L_i<R_i\le 10^9(1\le i\le N)$；
- $1\le Q\le 10^5$；
- $1\le P_j\le N(1\le j\le Q)$；
- $1\le X_j\le 10^9(1\le j\le Q)$。

#### 【子任务】

1. （$2$ 分）$L_i=0(1\le i\le N)$，$R_i=10(1\le i\le N)$，$Q\le 5$；
2. （$3$ 分）$L_i=0(1\le i\le N)$，$Q\le 5$；
3. （$6$ 分）$L_i=0(1\le i\le N)$；
4. （$10$ 分）$N\le 500$，$Q\le 5$，$R_i\le 500(1\le i\le N)$，$X_j\le 500(1\le j\le Q)$；
5. （$11$ 分）$N\le 500$，$Q\le 5$；
6. （$16$ 分）$Q\le 5$；
7. （$13$ 分）$P_j=1(1\le j\le Q)$，$L_1<L_2<\cdots<L_N$，$R_1<R_2<\cdots<R_N$；
8. （$14$ 分）$P_j=1(1\le j\le Q)$；
9. （$15$ 分）$R_i-L_i(1\le i\le N)$ 的最小值大于或等于 $X_j(1\le j\le Q)$ 的最大值；
10. （$10$ 分）无附加限制。

## 样例 #1

### 输入

```
4
10 40
20 80
45 60
70 95
1
1 15```

### 输出

```
3```

## 样例 #2

### 输入

```
8
0 30
0 90
0 80
0 60
0 20
0 40
0 70
0 50
3
1 30
1 40
4 50```

### 输出

```
7
1
5```

## 样例 #3

### 输入

```
5
0 10
0 10
0 10
0 10
0 10
4
1 9
1 10
1 11
1 1000000000```

### 输出

```
5
5
1
1```

## 样例 #4

### 输入

```
7
38 61
13 27
10 54
22 56
49 75
27 47
70 99
1
3 10```

### 输出

```
6```

## 样例 #5

### 输入

```
10
10 20
11 21
13 23
16 26
20 30
25 35
31 41
38 48
46 56
80 90
4
1 3
1 6
1 8
1 10```

### 输出

```
8
5
3
1```

## 样例 #6

### 输入

```
7
10 54
38 61
13 27
22 56
49 75
27 47
70 99
5
1 3
1 6
1 9
1 12
1 15```

### 输出

```
7
6
6
6
4```

## 样例 #7

### 输入

```
7
38 61
13 27
10 54
22 56
49 75
27 47
70 99
5
1 10
2 10
3 10
4 10
5 10```

### 输出

```
4
6
6
5
2```

# 题解

## 作者：VainSylphid (赞：2)

简单题，第一部分做的比[critnos](https://www.luogu.com.cn/user/203623)的题解弱智但是也能过，第二部分比他的简单一点。

考虑怎么刻画题目给的这个东西，容易发现我们其实是要找到最后离开餐厅的感染者 $Q$，然后把从初始感染者 $P$ 进入餐厅的时刻 $S$ 到最后感染者 $Q$ 离开的时间 $T$ 这段时间内的感染者全部找出来。

那么首先考虑怎么找到最后一个人，这是比较容易的。首先特判掉初始感染者传染不了任何人的情况（$R-L<X$）。一个显然的观察是，随着 $X$ 减小，最后一个感染者离开的时间是单调不降的。不妨对每个人钦定一个唯一的后继，具体的，对于第 $i$ 个人，我们找到一个 $j$ 使得 $R_j > R_i$ 并且 $L_j$ 最小，然后钦定 $j$ 是 $i$ 的后继，这样我们就可以倍增维护向跳需要的最大 $X$ 值。

那么接下来我们需要维护的是有多少个 $[L,R]$ 与 $[S,T]$ 的交不小于 $X$。这是容易的，注意到符合条件的区间一定满足 $S+X\leq R\leq T$ 并且长度不小于 $X$，因为由第一部分可知不存在右端点大于 $T$ 的符合条件区间。这是二维偏序，扫描线即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
	ll L,R;
}t[100005];
ll n,m,p[100005],f[18][100005],g[18][100005],b[400005],tot;
bool cmp(ll A,ll B)
{
	return t[A].R < t[B].R;
}
struct quest{
	ll L,R,X;
}q[100005];
vector<quest> v[400005];
vector<ll> c[400005];
ll d[400005];
void update(ll x)
{
	while(x <= tot)
		d[x]++,x += (x & (-x));
}
ll query(ll x)
{
	ll ret = 0;
	while(x)
		ret += d[x],x -= (x & (-x));
	return ret;
}
ll ans[100005];
int main()
{
	scanf("%lld",&n);
	for(ll i = 1;i <= n;i++)
		scanf("%lld%lld",&t[i].L,&t[i].R),p[i] = i,b[++tot] = t[i].R,b[++tot] = t[i].R - t[i].L;
	sort(p + 1,p + 1 + n,cmp);
	ll pos = n,to = p[n];
	for(ll i = n;i;i--)
	{
		while(pos > 0 && t[p[pos]].R > t[p[i]].R)
		{
			if(t[p[pos]].L < t[to].L)
				to = p[pos];
			pos--;
		}
		f[0][p[i]] = to,g[0][p[i]] = t[p[i]].R - t[to].L;
		for(ll j = 1;j < 18;j++)
			f[j][p[i]] = f[j - 1][f[j - 1][p[i]]],g[j][p[i]] = min(g[j - 1][p[i]],g[j - 1][f[j - 1][p[i]]]);
	}
	scanf("%lld",&m);
	for(ll i = 1;i <= m;i++)
	{
		ll P,X;
		scanf("%lld%lld",&P,&X);
		if(t[P].R - t[P].L < X)
		{
			ans[i] = 1;
			continue;
		}
		ll tmp = P;
		for(ll j = 17;j >= 0;j--)
			if(g[j][tmp] >= X)
				tmp = f[j][tmp];
		q[i] = {t[P].L + X - 1,t[tmp].R,X},b[++tot] = t[P].L + X - 1,b[++tot] = X - 1;
	}
	sort(b + 1,b + 1 + tot);
	tot = unique(b + 1,b + 1 + tot) - b - 1;
	for(ll i = 1;i <= m;i++)
	{
		if(ans[i])
			continue;
		ll t1 = lower_bound(b + 1,b + 1 + tot,q[i].L) - b;
		ll t2 = lower_bound(b + 1,b + 1 + tot,q[i].R) - b;
		ll t3 = lower_bound(b + 1,b + 1 + tot,q[i].X - 1) - b;
		v[t1].push_back({t3,-1,i}),v[t2].push_back({t3,1,i});
	}
	for(ll i = 1;i <= n;i++)
	{
		ll t1 = lower_bound(b + 1,b + 1 + tot,t[i].R) - b;
		ll t2 = lower_bound(b + 1,b + 1 + tot,t[i].R - t[i].L) - b;
		c[t1].push_back(t2);
	}
	ll ccnt = 0;
	for(ll i = 1;i <= tot;i++)
	{
		for(auto j : c[i])
			update(j),ccnt++;
		for(auto j : v[i])
			ans[j.X] += j.R * (ccnt - query(j.L));
	}
	for(ll i = 1;i <= m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Miss_SGT (赞：1)

提供一个好写简洁的写法。

不难发现，对于一个询问 $i$ 店里存在感染者的时间是一个区间，设其为 $[l_i,r_i)$，其中 $l_i$ 一定等于$L_{P_i}$。假如我们能求出 $r_i$，那么就变成了一个二维数点问题：

满足 $R_j - L_j \ge X_i,R_j \in [l_i+X_i,r_i]$ 的 $j$ 个数。

$r_i$ 实际上是能感染的人的 $R$ 的最大值。考虑暴力怎么求：动态维护 $r_i$，每次贪心的找到 $r_i - L \ge X_i$ 的 $R$ 最大的进行感染，然后将 $r_i$ 赋值为 $R$，直到找不到或 $R \le r_i$。

想一下发现不需要 $R$ 最大，只需要保证 $R > r_i$ 也一定能找到。于是抛开了 $X_i$ 对找 $r_i$ 的限制，就可以预处理了。对于每个点 $x$ 排序后找到 $R$ 大于它的 $L$ 最小的点 $y$，向其连一条边权为 $R_x - L_y$ 的有向边，整个构成一个内向森林。求 $r_i$ 就是跳 $P_i$ 的祖先直到边权小于 $X_i$，可以倍增，也可以在扫描线的同时用并查集维护。

然后关键部分就完了。最后将询问的 $X_i$ 从大到小排序，用两个指针分别维护 $R - L  \ge X$ 的人加入树状数组和并查集向父亲合并，做扫描线即可。小常数 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,l[N],r[N],fa[N],f[N],w[N],idx;
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
struct node{
	int x,y;
	inline bool operator<(node b)const{return x<b.x;}
}a[N],b[N],c[N],d[N];
int t[N],ans[N],p[N];
inline void add(int x,int y){for(;x<=idx;x+=x&-x) t[x]+=y;}
inline int query(int x){
	int ans=0;
	for(;x;x-=x&-x) ans+=t[x];
	return ans;
}
int main(){
	read(n);
	for(int i=1;i<=n;++i) read(l[i]),read(r[i]),w[++idx]=r[i],a[i]=(node){r[i],i};
	sort(w+1,w+idx+1);
	idx=unique(w+1,w+idx+1)-w-1;
	sort(a+1,a+n+1);
	node lt={1<<30,0};
	for(int i=n;i;){
		int j=i;
		while(j&&a[j].x==a[i].x) fa[a[j--].y]=lt.y;
		while(i>j) lt=min(lt,(node){l[a[i].y],a[i].y}),--i;
	}
	for(int i=1;i<=n;++i){
		f[i]=i;
		if(fa[i]) c[i]=(node){r[i]-max(l[fa[i]],l[i]),i};
		else c[i].x=-1;
		d[i]=(node){r[i]-l[i],i};
		r[i]=lower_bound(w+1,w+idx+1,r[i])-w;
	}
	read(q);
	for(int i=1;i<=q;++i){
		read(p[i]),read(b[i].x);
		b[i].y=i;
	}
	sort(b+1,b+q+1);
	sort(c+1,c+n+1);
	sort(d+1,d+n+1);
	for(int i=q,j=n,k=n;i;--i){
		while(j&&c[j].x>=b[i].x) f[c[j].y]=fa[c[j].y],--j;
		while(k&&d[k].x>=b[i].x) add(r[d[k--].y],1);
		if(w[r[p[b[i].y]]]-l[p[b[i].y]]<b[i].x){ans[b[i].y]=1;continue;}
		ans[b[i].y]=query(r[find(p[b[i].y])])-query(lower_bound(w+1,w+idx+1,l[p[b[i].y]]+b[i].x)-w-1);
	}
	for(int i=1;i<=q;++i) print(ans[i]),pc('\n');
	flush();
	return 0;
}
```

---

## 作者：critnos (赞：1)

水题解/se

显然存在被感染的时刻是一个区间。考虑求出这个区间。显然可以把被其他人的区间包含的区间去掉。对于一个询问，这个人的区间是 $[L,R]$，那么求出最小的 $r_i>R$，先判一下这个人是否被感染。然后容易找到第一个 $j>i$ 满足 $l_j-r_{j-1}>x$，那么求出的区间就是 $[L,r_{j-1}]$，记做 $[l,r]$。

然后要求和 $[l,r]$ 交长度 $\ge x$ 的区间数量，这个是可以 $1\log $ 的。不妨设 $r-l\ge x$。考虑求交的长度 $<x$ 的数量，那么区间长度 $<x$ 是一定会被统计的。如果区间长度 $\ge x$，那么只可能是右端点 $<l+x$ 或左端点 $>r-x$。这类也只是一个二维偏序。于是做两次二维偏序即可。

---

## 作者：To_our_starry_sea (赞：0)

### Solution

一种时空复杂度为 $O(n\log V)$ 的在线做法，其中 $V$ 表示 $l_i$ 与 $r_i$ 的值域。

显然由于时间不能倒流，所以对于每一个感染者，其只能向后传染。不难发现，最终存在传染者的时间必然是一段连续的区间，不妨设其为 $[L, R]$，对于一个人的就餐时间 $[l_i, r_i]$ 与传染性 $x$，其会被感染的充要条件是 $r_i - l_i \ge x$ 且 $r_i - L \ge x$。注意这里区间的长度与常规的理解不一致，在题面中写的也不是非常清楚。发现这个东西就是一个二维数点，其他题解大多离线然后二维数点，不过这里选择用可持久化线段树来在线维护。

接下来我们只用求出 $L$ 与 $R$ 的值即可。$L$ 显然是初始感染者 $p$ 的 $l_p$，因为时光显然不能倒流。对于 $R$ 的计算其实是本题一个重要的思维要点。考虑对于一个人 $i$，其时间区间为 $[l_i, r_i]$。我们钦定满足 $r_j > r_i$ 且 $l_j$ 最小的 $j$ 为 $i$ 的后继，容易发现若从 $i$ 可以向右拓展感染区间，则 $r_j$ 一定合法，这个东西可以按照 $r_i$ 排序完后单调队列维护。这样我们就可以倍增向右跳，从而求出最大的 $R$。接着按照前述方法在线回答询问即可。

本题 $[l_i, r_i]$ 值域很大，如果不想离线离散化的话，动态开点亦可。若 $n$ 与 $q$ 同阶，值域为 $V$，则时空复杂度均为 $O(n\log V)$，似乎比离线跑两次二维数点还快一些。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
int n, q, cnt = 0, tot = 0, b[MAXN], nxt[MAXN][20], w[MAXN][20], rt[MAXN], to[MAXN];
struct node {
	int l, r, id;
	inline bool operator < (const node &b) {
		if (r != b.r) return r < b.r;
		else return l < b.l;
	}
} a[MAXN];
struct Segment_Tree {
	int ls, rs, w;
} tr[MAXN * 32];
vector<int> pos[MAXN];
stack<int> sta;
inline void change(int &rt, int x, int l, int r, int way) {
	rt = ++cnt;
	tr[rt] = tr[x], tr[rt].w++;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (way <= mid) change(tr[rt].ls, tr[x].ls, l, mid, way);
	else change(tr[rt].rs, tr[x].rs, mid + 1, r, way);
}
inline int query(int rt, int l, int r, int qx, int qy) {
	if (qx <= l && r <= qy) return tr[rt].w;
	int mid = (l + r) >> 1, res = 0;
	if (qx <= mid) res = query(tr[rt].ls, l, mid, qx, qy);
	if (qy > mid) res += query(tr[rt].rs, mid + 1, r, qx, qy);
	return res;
}
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-')
		   f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}
int main() {
	n = read();
	int maxn = 0;
	for (int i = 1; i <= n; i++) a[i].l = read(), a[i].r = read(), a[i].id = i, maxn = max(maxn, a[i].r), b[++tot] = a[i].r;
	sort(a + 1, a + n + 1);
	a[0].l = maxn + 1, a[0].r = 0;
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	deque<int> Q;
	for (int i = n; i >= 1; i--) {
		int way = lower_bound(b + 1, b + tot + 1, a[i].r) - b;
		pos[way].push_back(i), to[a[i].id] = i;
		if (!Q.empty()) nxt[i][0] = Q.front();
	    while (!Q.empty() && a[Q.back()].l >= a[i].l) Q.pop_back();
	    Q.push_back(i);
		if (a[nxt[i][0]].l < a[i].r) w[i][0] = a[i].r - a[nxt[i][0]].l;
		else nxt[i][0] = 0;
		for (int j = 1; j <= 18; j++) nxt[i][j] = nxt[nxt[i][j - 1]][j - 1], w[i][j] = min(w[i][j - 1], w[nxt[i][j - 1]][j - 1]); 
	}
	for (int i = 1; i <= tot; i++) {
		rt[i] = rt[i - 1];
		for (auto id : pos[i]) change(rt[i], rt[i], 0, maxn, a[id].r - a[id].l);
	}
	q = read();
	while (q--) {
		int P = read(), x = read();
		P = to[P];
		if (a[P].r - a[P].l < x) {
			puts("1");
			continue;
		}
		int now = P;
		for (int j = 18; j >= 0; j--) {
			if (w[now][j] >= x) now = nxt[now][j];
		}
		int way1 = lower_bound(b + 1, b + tot + 1, a[now].r) - b, way2 = lower_bound(b + 1, b + tot + 1, a[P].l + x) - b - 1;
		int ans = query(rt[way1], 0, maxn, x, maxn) - query(rt[way2], 0, maxn, x, maxn);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

