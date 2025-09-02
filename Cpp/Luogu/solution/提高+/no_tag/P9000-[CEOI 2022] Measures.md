# [CEOI 2022] Measures

## 题目描述

有 $N$ 个站在数轴上的人，他们的初始位置分别为 $a_1,a_2,\ldots,a_N$，他们可以以 $1$ 个单位长度每秒的速度移动。

因为众所周知的原因，他们需要保持社交距离，也就是说在任两个人之间距离至少为 $D$。

Alenka 设计了一个 app 来快速求出这 $N$ 个人通过移动来保持社交距离的最小时间，现在她想要添加一个新功能：支持动态加入一个位置为 $b_i$ 的人。

你需要实现一个程序完成这个功能。

## 说明/提示

### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/f3fmckzt.png)

### 数据规模与约定

对于全部数据，$1\le D,a_1,\ldots,a_N,b_1,\ldots,b_M\le 10^9$。

| Subtask 编号 |                         特殊限制                         | 分数 |
| :----------: | :-----------------------------------------------------: | :--: |
|     $1$      |            $0\le N\le 2000$，$1\le M\le 10$             | $10$ |
|     $2$      |        $0\le N\le 2\times 10^5$，$1\le M\le 10$         | $14$ |
|     $3$      | $N=0$，$1\le M\le 2\times 10^5$，$b_1\le \cdots\le b_M$ | $35$ |
|     $4$      |             $N=0$，$1\le M\le 2\times 10^5$             | $41$ |

## 样例 #1

### 输入

```
2 1 2
1 3
2```

### 输出

```
1```

## 样例 #2

### 输入

```
0 5 3

1 2 3 4 5```

### 输出

```
0 1 2 3 4```

## 样例 #3

### 输入

```
3 3 3
3 3 3
3 3 3```

### 输出

```
4.5 6 7.5```

# 题解

## 作者：C_Pos_Princess (赞：6)

## 题意
有 $N$ 个站在数轴上的人，他们的初始位置分别为 $a_1,a_2,\ldots,a_N$，他们可以以 $1$ 个单位长度每秒的速度移动。

因为众所周知的原因，他们需要保持社交距离，也就是说在任两个人之间距离至少为 $D$。

Alenka 设计了一个 app 来快速求出这 $N$ 个人通过移动来保持社交距离的最小时间，现在她想要添加一个新功能：支持动态加入一个位置为 $b_i$ 的人。

你需要实现一个程序完成这个功能。


## 题解

这种任意元素之间关系的题目，我们可以写成一种统一的形式。

让数组升序排列。对于任意的 $i\le j$，满足：
$$
\frac{D(j-i)-(a_j-a_i)}{2}\le t
$$

化简得到：
$$
\frac{(a_i-D\times i)-(a_j-D\times j)}{2}\le t
$$

那最终的答案就是这个式子的最大值，相信很多题解都写了这个思路了，接下来我讲一下实现过程。

我们只需要维护出来这个差值，而这个值本身多少并不重要，所以在一个数字更新的时候，只会影响到前面位置的值，具体地也就是使前面位置的相对差值加上 $D$，这就变得非常好写。

这里注意这种情况的话 $lazy$ 其实是不用下传的，只需要更新答案的时候加进去就好了。因为已经加入的数值也不会发生更改了。

## 代码
```cpp
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
using namespace std;
struct node {
	int l, r;
	int minn, maxx;
	int num;
	int lazy;
} tr[N << 2];

int n, m, d;
void pushup(int rt) {
	tr[rt].minn = tr[rt].lazy + min(tr[rt << 1].minn, tr[rt << 1 | 1].minn);
	tr[rt].maxx = tr[rt].lazy + max(tr[rt << 1].maxx, tr[rt << 1 | 1].maxx);
	tr[rt].num = max(max(tr[rt << 1].num, tr[rt << 1 | 1].num), tr[rt << 1].maxx - tr[rt << 1 | 1].minn);
}


void build(int rt, int l, int r) {
	tr[rt].l = l;
	tr[rt].r = r;
	tr[rt].minn = INF;
	tr[rt].maxx = -INF;
	if (l == r) {
		return;
	}
	int mid =  l + r >> 1;
	build(rt << 1, l, mid);
	build(rt << 1 | 1, mid + 1, r);
}




void update(int rt, int x, int k) {
	if (tr[rt].l == tr[rt].r) {
		tr[rt].minn = tr[rt].maxx = k + tr[rt].lazy;
		return;
	}
	int mid = tr[rt].l + tr[rt].r >> 1;
	if (x <= mid) update(rt << 1, x, k);
	else {
		tr[rt << 1].maxx += d;
		tr[rt << 1].minn += d;
		tr[rt << 1].lazy += d;
		update(rt << 1 | 1, x, k);
	}
	pushup(rt);
}


int a[N];
pii s[N];
int id[N];
signed main() {

	read(n, m, d);
	for (int i = 1; i <= n + m; i++) {
		read(a[i]);
		s[i] = {a[i], i};
	}

	sort(s + 1, s + 1 + n + m);
	for (int i = 1; i <= n + m; i++)
		id[s[i].second] = i;

	build(1, 1, n + m);
	for (int i = 1; i <= n + m; i++) {
		update(1, id[i], a[i]);
		if (i > n) {
			write(tr[1].num / 2);
			if (tr[1].num & 1) printf(".5");
			SP;
		}
	}


	return 0;
}


```

---

## 作者：win114514 (赞：6)

### 思路

简单题。

考虑任意两点之间的限制。

任意两点合法时必须要满足：

$$\frac{D(j-i)-(a_j-a_i)}{2}\le t（i\le j）$$

所以答案即为：

$$\max_{i \le j}\frac{D(j-i)-(a_j-a_i)}{2}$$

使用线段树简单维护即可。

时间复杂度：$O((n+m)\log (n+m))$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;

int n, m, d, a[N], id[N];
long long t[N], g[N], mn[N], mx[N];
pair<int, int> s[N];

inline void upd(int p, int l, int r, int x, int v) {
  if(l == r) return mn[p] = mx[p] = v + g[p], void();
  int mid = (l + r) >> 1, ls = mid << 1, rs = mid << 1 | 1;
  if(x <= mid) upd(ls, l, mid, x, v);
  else mn[ls] += d, mx[ls] += d, g[ls] += d, upd(rs, mid + 1, r, x, v);
  mn[p] = g[p] + min(mn[ls], mn[rs]);
  mx[p] = g[p] + max(mx[ls], mx[rs]);
  t[p] = max({t[ls], t[rs], mx[ls] - mn[rs]});
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> d;
  memset(mn, 0x1f, sizeof mn);
  memset(mx, 0xef, sizeof mx);
  for (int i = 1; i <= n + m; i++)
    cin >> a[i], s[i] = {a[i], i};
  sort(s + 1, s + n + m + 1);
  for (int i = 1; i <= n + m; i++) id[s[i].second] = i;
  for (int i = 1; i <= n + m; i++) {
    upd(1, 1, n + m, id[i], a[i]);
    if(i > n) cout << t[1] / 2 << (t[1] & 1 ? ".5 " : " ");
  }
  return 0;
}
```

---

## 作者：Exp10re (赞：4)

挑战本题最幽默做法。

## 解题思路

以下默认 $a$ 升序。

在第 $t$ 秒，第 $i$ 人与第 $j$ 人 $(i\lt j)$ 之间每一个人都能拉开至少 $D$ 的距离，当且仅当 $\frac {(a_i-Di)-(a_j-Dj)} {2} \leq t$。

故答案 $t$ 的最小值为 $\max\limits_{i\lt j} \frac {(a_i-Di)-(a_j-Dj)} {2}$。

记 $w_i=a_i-Di$。

静态的话遍历一遍，$w$ 中每一个 $i$ 的前缀最大值减去后缀最小值的最大值即为答案。

动态插入的话我们考虑该插入操作对 $w$ 的影响：其中一个位置会多出一个数，后面的位置都减去 $D$。

动态插入，区间加，考虑块状链表。

每一块维护块内答案，最大值，最小值。

查询时枚举所有块，答案中 $i$ 在块左端，$j$ 在块右端的情况即为该块之前所有块的前缀最大值减去包括该块之后所有块的后缀最小值。

枚举所有块，得到上述情况的最大答案，然后与所有块的答案求最大值即为最终结果。

---

## 作者：MarsCheng (赞：3)

好像很多题解没有讲怎样推式子，这里讲一下。

首先可以注意到一个点就是某一个点向左移动，就相当于其他的所有点向右移动，时间是相同的。所以可以假设每一个点都只向右移动。

于是可以贪心，设 $a_i$ 是排序后的点，$f_i$ 为 $i$ 最终的位置，可有

$$
f_1 = a_1
$$
$$
f_i = \max(a_i, f_{i-1}+d)
$$
每一个点移动了 $f_i - a_i$ 个单位，同时因为所有的点可以同时平移，所以可以把所有的 $f_i$ 同时加一个数。

由于最后的答案是每个点移动的路程的最大值，所以实际上答案就是 $f_i - a_i$ 的极差除以 $2$。其中因为 $f_1 - a_1$ 始终为 $0$，所以极差就等于最大值。

怎么找最大值呢？我们先看 $f_i$ 的式子，把递归展开，发现它相当于

$$
f_i = \max_{j \leq i}(a_j + (i - j)d)
$$
化简得
$$
f_i = \max_{j \leq i}(a_j - jd) + id
$$
带入答案式
$$
\max_{1 \leq i \leq n}(\max_{j \leq i}(a_j - jd) - (a_i - id))
$$
继续化简，得到
$$
\max_{j \leq i}((a_j - jd) - (a_i - id))
$$
于是就可以拿着线段树维护一下，可以参考其它题解的实现。

---

## 作者：WZWZWZWY (赞：3)

很好一道题。~~在看完各个题解之后终于会了。~~

以最左边的点为参照物，则其他的点会相对向右运动到如图的指定位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/pbzx1pul.png)

显然，答案就是运动最远的点所耗费的时间。

不过有的点初始时可能超过了指定位置，要往回走吗？不需要，只要以每个点为参照物，都计算一遍，取最大值就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/1os6ho0h.png)

如图，答案即为 $(j-i)\times D-(a_j-a_i)$。

求对于每个 $1\le i\le j\le n+m$，上述式子的最大值即可。

转换一下，$(j-i)\times D-(a_j-a_i)=(a_i-i\times D)-(a_j-j\times D)$，求这个式子的最大值，要让减号前面最大，后面最小。

接下来就是如何实现的问题了。

设数轴上第 $i$ 个点的权值 $w_i$ 为 $a_i-i\times D$。

先记录所有点的坐标从小到大排序后的位置，这样就对应到数轴上的从 $1$ 到 $n+m$。然后再根据输入的顺序依次加入点到数轴上的对应位置，接着用点的权值来更新数轴上的区间最小值和最大值，可以用线段树维护，根据区间的左边一段的答案、右边一段答案、左边最大值减去右边最小值的结果来更新答案。

但是其实还有个问题：若直接用点在最终的数轴上的坐标来求 $w_i$ 会出问题。一个点在数轴对应的位置是 $i$，但在加入的时候，可能并不是数轴上从左往右第 $i$ 个数。

也就是说，这样算出来的 $w_i$ 其实是所有点加完之后的这个点的权值，但是题目让我们求每次加入一个点后的答案，应该用这个点此时是坐标上的第几个点来算。

所以，我们要维护出一个点每次在数轴上是第几个点，然后计算 $w_i$……吗？不用，观察 $w_i$ 的定义，$w_i=a_i-i\times D$，即前面有几个点就减少几个 $D$。一开始所有 $w_i$ 为 $a_i$，每次加入时，把这个点及其之后的点的权值减少 $D$ 就可以了。


---


代码：

```
#include <bits/stdc++.h>
#define int long long
#define PII pair <int, int> 
using namespace std;

const int N = 1e6 + 5;

struct node {
	int id, x;
} a[N], b[N];

bool cmp(node a, node b) {
	return a.x < b.x;
}

int n, m, d; 

struct Sgt {
	map <PII, int> tid;
	int cnt, maxx[N], minn[N], ans[N], g[N]; // g[]: d的数量 
	
	void init() {
		for (auto &u : minn) u = 1e18;
		for (auto &u : maxx) u = -1e18;
	}
	
	void fz(int l, int r, int p, int x) { // 赋值 
		int &id = tid[{l, r}], mid = (l + r) / 2;
		if (!id) id = ++cnt;
		
		if (l == r) {
			maxx[id] = minn[id] = x - g[id] * d;
			return ;
		}
		
		int &lid = tid[{l, mid}], &rid = tid[{mid + 1, r}];
		
		if (!lid) lid = ++cnt;
		if (!rid) rid = ++cnt;
		
		if (p <= mid) {
			g[rid] ++; maxx[rid] -= d; minn[rid] -= d;
			fz(l, mid, p, x);
		} else fz(mid + 1, r, p, x);
	
		maxx[id] = max(maxx[lid], maxx[rid]) - g[id] * d;
		minn[id] = min(minn[lid], minn[rid]) - g[id] * d;
		ans[id] = max({ans[lid], ans[rid], maxx[lid] - minn[rid]});
	}
} tr;

signed main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    cin >> n >> m >> d;
    
    for (int i = 1; i <= n + m; i++) {
    	cin >> a[i].x;
    	b[i] = {i, a[i].x};
	}
	sort(b + 1, b + 1 + n + m, cmp);
	for (int i = 1; i <= n + m; i++) {
		int p = b[i].id;
		a[p].id = i;
	}
	
	tr.init();
	for (int i = 1; i <= n + m; i++) {
		int id = a[i].id;
		tr.fz(1, n + m, id, a[i].x);
		if (i > n) cout << tr.ans[1] / 2 << (tr.ans[1] & 1 ? ".5 " : " ");
	}
	
	return 0;
}

/*
(a[i]-i*D)-(a[j]-j*D)
*/
```

突然想起我“不会写线段树”的设定，所以我写的是带编号的分治（

还有什么不懂的可以问我哦。

---

## 作者：Inui_Sana (赞：3)

被教练要求写这题题解。

像这种多次询问一个东西的问题，先考虑怎么 $O(n)$ 计算一个询问的答案，再想维护方法。

考虑如果已知当前答案为 $k$，怎么找到一组合法的 $a_i$ 的位置。此时所有 $a_i$ 移动过后的 $a'_i$ 可以到达 $[a_i-k,a_i+k]$。考虑按照这些区间的左端点排序（其实也就是按 $a_i$ 排序），贪心的，让每一个 $a_i$ 都移动到尽可能左，但不超过限制的位置，即 $a'_i=\max(a_i-k,a'_{i-1}+D)$。

考虑这启发我们什么。发现如果 $\exists j<i,\frac{a_i-a_j+2k}{i-j}<D$，则 $[i,j]$ 内一定会有两个 $a_i$ 之间无法取到 $D$ 的距离，则不符合条件。

这个条件是充分的。必要性也是显然的。常见的问题是，如果 $[i,j]$ 之间，大部分靠近 $a_i$，但是 $a_{j-1}$ 离 $a_j$ 远，不会导致某些不符合条件的方案判断错误码？事实上是不会的，因为这样 $[i,j]$ 的一个子区间一定会被判断为不符合条件。

接下来转化一下这个式子：

$$\frac{a_i-a_j+2k}{i-j}\ge D$$

$$\Leftrightarrow a_i-a_j+2k\ge Di-Dj$$

令 $f_i=a_i-Di$，则有：

$$\Leftrightarrow f_j-f_i\le 2k$$

即 $k\ge\max\limits_{i>j}\frac{f_j-f_i}{2}$。

然后考虑怎么维护。先将所有 $a_i,b_i$ 离线下来求出排名，然后每次操作就是在 $p_i$ 位置插入一个 $a_i$，将 $j>p_i$ 的位置 $j$ 对应排名都加上 $1$，也就是 $f_j\to f_j-D$，求 $\max\limits_{i>j}\frac{f_j-f_i}{2}$。

发现前两个可以简单线段树维护，但是后两个不好搞。不过发现，在位置 $p$ 插入一个数只会影响 $i\ge p,j\le p$ 的 $i,j$ 的 $f_i-f_j$，于是直接 $ans\to\max(ans,\max_{j\le p} f_j-\min_{i\ge p} f_i)$ 即可。线段树维护区间 $\max,\min$。时间复杂度 $O(n\log n)$。

code：

```cpp
int n,m,k,a[N];
pii b[N];
struct SGT{
	ll mn[N<<2],mx[N<<2],tag[N<<2];
	il void pushup(int o){
		mn[o]=min(mn[o<<1],mn[o<<1|1]);
		mx[o]=max(mx[o<<1],mx[o<<1|1]);
	}
	il void reset(int o,ll k){
		mn[o]+=k,mx[o]+=k;
		tag[o]+=k;
	}
	il void pushdown(int o){
		reset(o<<1,tag[o]),reset(o<<1|1,tag[o]);
		tag[o]=0;
	}
	void update(int l,int r,int o,int x,int y,ll k){
		if(l>=x&&r<=y){
			reset(o,k);
			return;
		}
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid){
			update(l,mid,o<<1,x,y,k);
		}
		if(y>mid){
			update(mid+1,r,o<<1|1,x,y,k);
		}
		pushup(o);
	}
	void upd(int l,int r,int o,int x,ll k){
		if(l==r){
			mn[o]=mx[o]=k;
			return;
		}
		pushdown(o);
		int mid=(l+r)>>1;
		if(x<=mid){
			upd(l,mid,o<<1,x,k);
		}else{
			upd(mid+1,r,o<<1|1,x,k);
		}
		pushup(o);
	}
	ll queryMin(int l,int r,int o,int x,int y){
		if(r<x||l>y){
			return 1ll*inf*inf;
		}
		if(l>=x&&r<=y){
			return mn[o];
		}
		pushdown(o);
		int mid=(l+r)>>1;
		return min(queryMin(l,mid,o<<1,x,y),queryMin(mid+1,r,o<<1|1,x,y));
	}
	ll queryMax(int l,int r,int o,int x,int y){
		if(r<x||l>y){
			return -1ll*inf*inf;
		}
		if(l>=x&&r<=y){
			return mx[o];
		}
		pushdown(o);
		int mid=(l+r)>>1;
		return max(queryMax(l,mid,o<<1,x,y),queryMax(mid+1,r,o<<1|1,x,y));
	}
}T;
struct BIT{
	int tr[N];
	#define lb(x) (x&(-x))
	il void upd(int x,int y){
		while(x<=n+m){
			tr[x]+=y;
			x+=lb(x);
		}
	}
	il int qry(int x){
		int ret=0;
		while(x){
			ret+=tr[x];
			x-=lb(x);
		}
		return ret;
	}
}R;
void Yorushika(){
	read(n,m,k);
	rep(i,1,n+m){
		read(a[i]);
		b[i]=Mp(a[i],i);
	}
	sort(b+1,b+n+m+1);
	mems(T.mn,0x3f),mems(T.mx,-0x3f);
	ll ans=0;
	rep(i,1,n+m){
		int x=lower_bound(b+1,b+n+m+1,Mp(a[i],i))-b;
		int y=R.qry(x-1)+1;
		R.upd(x,1);
		T.update(1,n+m,1,x+1,n+m,-k);
		T.upd(1,n+m,1,x,a[i]-1ll*k*y);
		ans=max(ans,T.queryMax(1,n+m,1,1,x)-T.queryMin(1,n+m,1,x,n+m));
		if(i>n){
			if(ans&1){
				printf("%lld.5 ",ans/2);
			}else{
				printf("%lld ",ans/2);
			}
		}
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

注意 sub2 存在 $n+m=2\times10^5+10$ 的数据。

---

## 作者：EnofTaiPeople (赞：3)

考虑如何计算静态答案。

设花费的最小时间是 $t$，按坐标排序后，第一个人左移 $t$ 步最优，而后面的人也依次需要尽量向左移动。

设第 $i$ 个人从 $c_i$ 移动到了 $c'_i$，下一个人会从 $c_{i+1}$ 尽量向 $c'_i+D$ 移动。

如果 $c_{i+1}<c'_i+D$ 并且无法移动到 $c'_i+D$，我们就失败了。

否则，我们会移动到 $c_{i+1}-t,c'_i+D$ 中较大的一个。

思考这样一个过程，$c'_l=c_l-t$，然后 $\forall i\in(l,r],c'_i\ge c'_{i-1}+D$，于是，$c'_r\ge c_l-t+D(r-l)$，但是，$c'_r\le c_r+t$，所以 $c_l-t+D(r-l)\le c_r+t$，$2t\ge c_l-c_r+D(r-l)$。

问题是，如果 $\exist i\in(l,r],c_i=c_i-t$ 怎么办？这时候你会发现答案在 $l=i$ 的时候统计了。

所以对于所有 $l\le r$ 计算出 $2t$ 的最小值除以二就是答案。

你会发现这个 $c_l-c_r+D(r-l)$ 的式子可以差分之后写成最大字段和的形式，即 $a_i=c_i-c_{i+1}+D$，求出 $\sum\limits_{i=l}^{r-1}a_i$ 就是答案，我们需要求这个数组 $a$ 的最大子段和。

离线下来排序，用链表串联所有人的坐标，从后往前依次删除、修改，倒序求出答案，再反过来输出就好了。

使用线段树维护最大子段和，时间复杂度 $O(n\log n)$，空间 $O(n)$。

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

一个数轴上初始时有 $n$ 个人，分别位于位置 $a_i$。有 $m$ 个人会依次加入数轴，位置分别为 $b_i$。在每个人加入后的局面，求出下列问题的答案。

- 找出最小的 $T$ 满足：如果每个人最多移动 $T$ 的距离，可以使得任意两人的距离至少为 $D$。

## 题目分析

既可以往左，又可以往右，使得分析变得很复杂，不过我们只需要先假设所有人都往左走了 $T$ 的长度。这样相对位置不变，人们只能往右走 $2T$ 的距离，这样就可以贪心了：

- 从左往右扫，每个人都希望在与前面的人距离大于等于 $D$ 的前提下，尽量往左靠。

设当前数组排好序，最后第 $i$ 个人最后的位置是 $d_i$，则 $d_1=a_1,d_i=\max(d_{i-1}+D,a_i)$，答案就是 $\frac{\max(d_i-a_i)}{2}$。

通过简单分析可以发现 $d_i$ 的式子相当于 $\max\limits_{j\le i}(a_j+(i-j)D)$，整理后答案就变成了 $\frac{\max\limits_{j\le i}(iD-a_i-(jD-a_j))}{2}$，设 $w_i=iD-a_i$，则这是经典的分治：当前区间的答案分成左区间的答案，右区间的答案，和 $j,i$ 跨中间线的答案，使用线段树即可维护，复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline signed read(){signed s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N =5e5+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,int b){if(!b)return 1;int c=qp(a,b>>1);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,K,a[N],b[N];
struct node{
	int x,k;
}c[N];
int ps[N];
inline bool cmp(node a,node b){
	return a.k<b.k;
}
struct seg{
	int w,mx,mn,ans,laz;
}xd[N<<2];
inline void update(int x,int k){//加入了一个节点 
	xd[x].w=1,xd[x].mx=xd[x].mn=k,xd[x].ans=0;
}
inline void getup(int x){
	xd[x].w=xd[L].w+xd[R].w,xd[x].mx=max(xd[L].mx,xd[R].mx),xd[x].mn=min(xd[L].mn,xd[R].mn);
	xd[x].ans=max({xd[L].ans,xd[R].ans,xd[R].mx-xd[L].mn});
}
inline void ins(int x,int k){//节点加 
	if(xd[x].w)xd[x].mx+=k,xd[x].mn+=k,xd[x].laz+=k; 
}
inline void pushdown(int x){
	ins(L,xd[x].laz),ins(R,xd[x].laz),xd[x].laz=0;
}
inline void insert(int x,int l,int r,int p,int k){
	if(l==r)return update(x,k),void();
	pushdown(x);
	p<=mid?insert(lc,p,k):insert(rc,p,k);
	getup(x);
}
inline void build(int x,int l,int r){
	if(l==r)return xd[x]={0,-llf,llf,0,0},void();
	build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int Ll,int Rr,int k){
	if(Ll>Rr||!xd[x].w)return;
	if(OK)return ins(x,k),void();
	pushdown(x);
	if(Ll<=mid)modify(lc,Ll,Rr,k);
	if(Rr>mid)modify(rc,Ll,Rr,k);
	getup(x);
}
inline int query(int x,int l,int r,int Rr){
	if(r<=Rr)return xd[x].w;
	pushdown(x);
	if(Rr<=mid)return query(lc,Rr);
	return xd[L].w+query(rc,Rr);
}
inline void subtaskall(){
	int pr=n;
	repm(i)a[++n]=b[i];
	repn(i)c[i]={i,a[i]};
	sort(c+1,c+n+1,cmp);
	build(Root);
	repn(i)ps[c[i].x]=i;
	repn(i){
		int P=query(Root,ps[i])+1;
		insert(Root,ps[i],P*K-a[i]);
		modify(Root,ps[i]+1,n,K);
		if(i>pr){
			pf(xd[1].ans/2);
			if(xd[1].ans&1)putchar('.'),putchar('5');
			putchar(' ');
		}
	}
}
inline void Main(){
	n=read(),m=read(),K=read();
	repn(i)a[i]=read();
	repm(i)b[i]=read();
	subtaskall();
}
signed main(){
	int T=1;
	while(T--)Main(); 
	return 0;
}

```

---

## 作者：Daniel1234 (赞：1)

# 思路
另一种思路。

考虑一个标准序列，第 $i$ 项为 $i \times d$，考虑每个位置与每一项的差，容易发现差的极差即为限定两两距离为 $d$ 的最小时间。

但现在限制是 $\geq d$？

可以转化为任意后缀加任意值后全局的极差。(其实一段区间间隔 $+1$，等价于这段区间的右端点和右端点右边的所有点向右平移一格，即后缀 $+1$。而这个过程可以重复多次）

考虑静态怎么做。可以先选择最大的一个，记为 $i$，然后在他后面找第二大的记为 $j$，$i+1 \to j$ 可以加上 $a_i-a_j$ ，然后找第三大的，记为 $k$ ，$j+1 \to k$可以加上 $a_i-a_k$，以此类推。

这个序列可以暴力维护，因为一个点只会进、出序列一次，这里我用了链表和线段树维护。

其他就是线段树板子啦。

# 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k;
int a[500005], b[500005];
int rka[500005], rkb[500005];
struct point{
    int op, i;
    int v;
    point(){}
    point(int x, int y, int z){
        op = x;
        i = y;
        v = z;
    }
}c[500005];
int cnt;
struct point_f{
    int mn;
    int tag;
    int num;
    point_f(){
        mn = 1e18;
        tag = 0;
        num = 0;
    }
}f[2000005];
int pre[500005], suf[500005];
int en;
struct point_k{
    int bel, mn;
    point_k(){
        bel = mn = 0;
    }
}f_k[2000005];
bool cmp(point x, point y){
    return x.v < y.v;
}
void down(int now){
    if(f[now].tag){
        f[now<<1].tag += f[now].tag;
        f[now<<1|1].tag += f[now].tag;
        f[now<<1].mn += f[now].tag;
        f[now<<1|1].mn += f[now].tag;
        f[now].tag = 0;
    }
}
void up(int now){
    f[now].mn = min(f[now<<1].mn, f[now<<1|1].mn);
}
void change_f(int now, int l, int r, int x, int y, int z){
    if(x > y)return;
    if(x <= l && r <= y){
        f[now].mn += z;
        f[now].tag += z;
        return;
    }
    down(now);
    int mid = l+r>>1;
    if(x <= mid)change_f(now<<1, l, mid, x, y, z);
    if(y > mid)change_f(now<<1|1, mid + 1, r, x, y, z);
    up(now);
}
void init_f(int now, int l, int r, int x, int y){
    f[now].num++;
    if(l == r){
        f[now].mn = y;
        return;
    }
    down(now);
    int mid = l+r>>1;
    if(x <= mid)init_f(now<<1, l, mid, x, y);
    else init_f(now<<1|1, mid + 1, r, x, y);
    up(now);
}
int query_f(int now, int l, int r, int x, int y){
    if(x > y)return 0;
    if(x <= l && r <= y)return f[now].num;
    int ss = 0;
    int mid = l+r>>1;
    if(x <= mid)ss += query_f(now<<1, l, mid, x, y);
    if(y > mid)ss += query_f(now<<1|1, mid + 1, r, x, y);
    return ss;
}
int query_min(int now, int l, int r, int x, int y){
    if(x > y)return 1e18;
    if(x <= l && r <= y){
        return f[now].mn;
    }
    down(now);
    int mid = l+r>>1;
    int mn = 1e18;
    if(x <= mid)mn = min(mn, query_min(now<<1, l, mid, x, y));
    if(y > mid)mn = min(mn, query_min(now<<1|1, mid + 1, r, x, y));
    return mn;
}
void init_k(int now, int l, int r, int x, int op){
    if(l == r){
        if(op == 0){
            f_k[now].mn = -1e18;
        }else{
            int L = pre[x] + 1, R = x;
            f_k[now].mn = query_min(1, 1, n + m, R, R) - query_min(1, 1, n + m, L, R);
        }
        return;
    }
    int mid = l+r>>1;
    if(x <= mid)init_k(now<<1, l, mid, x, op);
    else init_k(now<<1|1, mid + 1, r, x, op);
    f_k[now].mn = max(f_k[now<<1].mn, f_k[now<<1|1].mn);
}
void down_bel(int now){
    if(f_k[now].bel){
        f_k[now<<1].bel = f_k[now].bel;
        f_k[now<<1|1].bel = f_k[now].bel;
        f_k[now].bel = 0;
    }
}
void change_k(int now, int l, int r, int x, int y, int z){
    if(x > y)return;
    if(x <= l && r <= y){
        f_k[now].bel = z;
        return;
    }
    down_bel(now);
    int mid = l+r>>1;
    if(x <= mid)change_k(now<<1, l, mid, x, y, z);
    if(y > mid)change_k(now<<1|1, mid + 1, r, x, y, z);
}
int query_bel(int now, int l, int r, int x){
    if(l == r){
        return f_k[now].bel;
    }
    down_bel(now);
    int mid = l+r>>1;
    if(x <= mid)return query_bel(now<<1, l, mid, x);
    return query_bel(now<<1|1, mid + 1, r, x);
}
void add_k(int place){
    int nw = query_bel(1, 1, n + m, place);
    if(place == nw)return;
    if(!nw){
        pre[place] = en;
        suf[en] = place;
        en = place;
    }else{
        pre[place] = pre[nw];
        suf[pre[place]] = place;
        suf[place] = nw;
        pre[nw] = place;
    }
    change_k(1, 1, n + m, pre[place] + 1, place, place);
    init_k(1, 1, n + m, place, 1);
    if(suf[place])init_k(1, 1, n + m, suf[place], 1);
}
void del_k(int place){
    init_k(1, 1, n + m, place, 0);
    change_k(1, 1, n + m, pre[place] + 1, place, suf[place]);
    int ss = suf[place];
    if(place == en){
        pre[place] = suf[place] = 0;
        en = pre[place];
        suf[en] = 0;
    }else{
        pre[suf[place]] = pre[place];
        suf[pre[place]] = suf[place];
        pre[place] = suf[place] = 0;
    }
    if(ss)init_k(1, 1, n + m, ss, 1);
}
void del(int nw){
    if(!nw)return;
    while(nw && pre[nw] && query_min(1, 1, n + m, pre[nw], pre[nw]) <= query_min(1, 1, n + m, nw, nw))del_k(pre[nw]);
}
void add(int place, int val){
    int p = query_f(1, 1, n + m, 1, place) + 1;
    change_f(1, 1, n + m, place + 1, n + m, k);
    int nw = query_bel(1, 1, n + m, place + 1);
    init_f(1, 1, n + m, place, p * k - val);
    if(nw)init_k(1, 1, n + m, nw, 1);
    if(!nw || p * k - val > query_min(1, 1, n + m, nw, nw))add_k(place);
    del(place);
    del(nw);
}
void print(){
    int ans = f_k[1].mn;
    if(ans&1)printf("%lld", ans/2), printf(".5 ");
    else printf("%lld ", ans/2);
}
signed main(){
    // freopen("move.in", "r", stdin);
    // freopen("move.out", "w", stdout);
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        c[++cnt] = point(0, i, a[i]);
    }
    for(int i = 1; i <= m; i++){
        scanf("%lld", &b[i]);
        c[++cnt] = point(1, i, b[i]);
    }
    sort(c + 1, c + 1 + cnt, cmp);
    for(int i = 1; i <= cnt; i++){
        if(!c[i].op)rka[c[i].i] = i;
        else rkb[c[i].i] = i;
    }
    for(int i = 1; i <= n; i++)add(rka[i], a[i]);
    for(int i = 1; i <= m; i++){
        add(rkb[i], b[i]);
        print();
    }
    return 0;
}
```

---

