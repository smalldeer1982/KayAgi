# 「HMOI R1」文化课

## 题目背景

有一群人在参加 CPS0202。由于作弊可以使得省队名额减一，所以他们准备作弊祸害他人，然后高考考全省第二。

但是由于他们非常菜，高考考不到全省第二，所以他们需要你来指导他们作弊。

fz 编不下去了，恳请 PD 帮他写个崩 3 的背景。

## 题目描述

$n$ 个人正在会考。由于他们假装自己退役了，所以下午的 CPS0202 跟他们没啥关系。

目前第 $i$ 个人有一个得分 $a_i$，想要及格需要拿到 $l_i$ 分。而为了不被老师怀疑，他的分数不能超过 $r_i$。

你可以组织若干场作弊。这些作弊是同时进行的，所以不能有人同时参加两场或以上的作弊。每场作弊在连续的一段考生中进行，他们的分数都变为他们中分数最高的人的分数。

求最多能使多少人及格且不被怀疑。

## 说明/提示

在 $[2,3]$ 组织一场作弊，可以使所有人满足条件。

本题采用捆绑测试。
- Subtask 1（$5$ 分）：$n\le5$；
- Subtask 2（$5$ 分）：$n\le100$；
- Subtask 3（$10$ 分）：$n\le8\times10^3$；
- Subtask 4（$30$ 分）：$l_i=r_i$；
- Subtask 5（$20$ 分）：$a_i\le a_{i+1}$；
- Subtask 6（$30$ 分）：无特殊性质。

对于 $100\%$ 的数据，$1\le n\le 10^5$，$1\le a_i\le n$，$1\le l_i\le r_i\le n$。

-------

- Idea: FZzzz
- Solution: FZzzz
- Code: FZzzz
- Data: FZzzz

## 样例 #1

### 输入

```
6
1 1 4 5 1 4
1 1
4 5
1 4
1 5
1 1
4 4
```

### 输出

```
6
```

# 题解

## 作者：Miko35 (赞：7)

upd：改正了一处笔误（将 `l` 打成了 `1`）

验题人又来水题解了。

```cpp
for(rgi i=1;i<=n;++i){
	for(rgi j=1;j<=i;++j)dp[i]=max(dp[i],dp[j-1]+sum(j,i,ma[j][i]));
}
```

考虑这个 $n^2$ 的 dp，其中 $dp_i$ 表示前 $i$ 个数的答案，$\textrm{sum}(l,r,x)$ 表示“将 $[l,r]$ 都改为 $x$ 取得的收益”，$ma_{l,r}$ 表示 $[l,r]$ 的 range_max。

看似不大能优化，其实是可以的。记 $s_{l,r}=\textrm{sum}(l,r,ma_{l,r})$，也就是“在 $[l,r]$ 举行一场作弊的收益”。令 $t$ 时刻的 $S_i$ 表示 $s_{i,t}$，只要我们在 dp 的过程中能随着时间有效维护 $S$ 数组，就可以使用线段树优化这个 dp 解决问题。

考虑分开计算每个人的贡献。对于一个人 $(a_x,l_x,r_x)$，它对一个区间 $[L,R]$ 产生贡献当且仅当 $ma_{L,R}\in [l_x,r_x],x\in [L,R]$。

把它写成 $\max(ma_{L,x},ma_{x,R})\in [l_x,r_x]$，换句话说也就是：$ma_{L,x},ma_{x,R}$ 都要 $\leq r_x$，且其中至少一个 $\geq l_x$。

我们分别预处理出 $ma_{L,x},ma_{x,R}\in [l_x,r_x]$ 的 $L,R$ 的范围，记为 $[Ll_x,Lr_x],[Rl_x,Rr_x]$。所以当 $i\in[x,Rl_x)$ 时，$L$ 的范围是 $[Ll_x,Lr_x]$；当 $i\in[Rl_x,Rr_x]$ 时，$L$ 的范围是 $[Ll_x,x]$；当 $i>Rr_x$ 时，没有贡献。

我们在 $i$ 到达几个临界点的时候，通过线段树的区间加操作更新 $x$ 的贡献区间即可。

这样的复杂度是 $O(n \log n)$，可以通过此题。

核心代码：

```cpp
for(rgi i=1;i<=n;++i){
	if(a[i][0]>r[i])continue;
	ll[i]=lr[i]=rl[i]=rr[i]=i;
	for(rgi w=LOG;~w;--w){
		chg(rl[i],w,l[i]-1,1),chg(rr[i],w,r[i],1);
		chg(lr[i],w,l[i]-1,-1),chg(ll[i],w,r[i],-1);
	}
	if(a[lr[i]][0]<l[i])--lr[i];
	if(a[rl[i]][0]<l[i])++rl[i];
	v[i].push_back(opt{ll[i],lr[i],1});
	v[rl[i]].push_back(opt{lr[i]+1,i,1});
	v[rr[i]+1].push_back(opt{ll[i],i,-1});
}
for(rgi i=1;i<=n;++i){
	for(opt o:v[i])upd(o);
	upd(opt{i+1,i+1,ans=qry(1,0,n,0,n)});
}
```




---

## 作者：Leasier (赞：5)

前置芝士：[ST 表](https://oi-wiki.org/ds/sparse-table/)、[线段树](https://oi-wiki.org/ds/seg/)

首先有一个暴力 dp。设 $dp_i$ 表示前 $i$ 个人作弊所得最大贡献。

初值：$dp_0 = 0$。

转移：$dp_i = \displaystyle\max_{j = 1}^i (dp_{j - 1} + w_{j, i})$。

答案：$dp_n$。

为了优化这个 dp，考虑动态维护 $dp_{j - 1} + w_{j, i}$ 的区间 $\max$。

考虑一个位置 $i$ 对答案产生贡献的区间 $[p, q]$。

先判掉 $a_i > r_i$ 这种不可能产生贡献的情况。

根据题给条件，$p \leq i \leq q, l_i \leq \displaystyle\max_{j = p}^q a_j \leq r_i$。

直接考虑两个端点是不方便的，考虑只固定 $i$，分开讨论 $p, q$。

对于 $p$，显然有 $\displaystyle\max_{j = p}^i a_j \leq r_i$；对于 $q$，显然有 $\displaystyle\max_{j = i}^q a_j \leq r_i$。

据此我们可以定出一个粗略的 $p, q$ 范围 $l_1 \leq p \leq i \leq q \leq r_2$。

对于下界 $l_i$ 的限制，只要左右两边之一满足即可。对于 $p$，显然有 $\displaystyle\max_{j = p}^i a_j \leq l_i$；对于 $q$，显然有 $\displaystyle\max_{j = i}^q a_j \leq l_i$。

$l_1, l_2, r_1, r_2$ 均可用 ST 表 + 二分求出。

有了上述限制，我们来进一步讨论范围。

假定我们现在在计算 $dp_k$。

- $l_2 = 0, r_1 \neq 0$

1. $k < r_1$

显然没有贡献。

2. $r_1 \leq k \leq r_2$

此时我们已然选择了 $r_1$ 以满足下界，则 $p = l_1, q = i$。

3. $k > r_2$

显然没有贡献。

- $l_2 \neq 0, r_1 = 0$

1. $k < i$

显然没有贡献。

2. $i \leq k \leq r_2$

此时我们只需要满足上界即可，则 $p = l_1, q = l_2$。

3. $k > r_2$

显然没有贡献。

- $l_2, r_1 \neq 0$

1. $k < i$

显然没有贡献。

2. $i \leq k < r_1$

此时我们必须选择 $l_2$ 才能满足下界，则 $p = l_1, q = l_2$。

3. $r_1 \leq k \leq r_2$

此时我们只需要满足上界即可，则 $p = l_1, q = i$。

4. $k > r_2$

显然没有贡献。

时间复杂度为 $O(n \log n)$。

注意要特判一下 $l_1 > l_2$ 的情况。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef struct {
	int l;
	int r;
	int tag;
	int max;
} Node;

typedef struct Modification_tag {
	int l;
	int r;
	int val;
	Modification_tag(int l_, int r_, int val_){
		l = l_;
		r = r_;
		val = val_;
	}
} Modification;

int a[100007], st[100007][17], dp[100007];
Node tree[400007];
vector<Modification> v[100007];

inline void init(int n){
	int m = log2(n);
	for (register int i = 1; i <= n; i++){
		st[i][0] = a[i];
	}
	for (register int i = 1; i <= m; i++){
		int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
		for (register int j = 1; j <= t1; j++){
			st[j][i] = max(st[j][id], st[j + t2][id]);
		}
	}
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}

inline int get_max1(int l, int r){
	int t = log2(r - l + 1);
	return max(st[l][t], st[r - (1 << t) + 1][t]);
}

inline void pushdown(int x){
	int ls = x * 2, rs = x * 2 + 1;
	tree[ls].tag += tree[x].tag;
	tree[ls].max += tree[x].tag;
	tree[rs].tag += tree[x].tag;
	tree[rs].max += tree[x].tag;
	tree[x].tag = 0;
}

inline void update(int x){
	tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
}

void add(int x, int l, int r, int k){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag += k;
		tree[x].max += k;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) add(x * 2, l, r, k);
	if (r > mid) add(x * 2 + 1, l, r, k);
	update(x);
}

int get_max2(int x, int pos){
	if (tree[x].r <= pos) return tree[x].max;
	int ans;
	pushdown(x);
	ans = get_max2(x * 2, pos);
	if (pos > ((tree[x].l + tree[x].r) >> 1)) ans = max(ans, get_max2(x * 2 + 1, pos));
	return ans;
}

void add(int x, int pos, int val){
	if (tree[x].l == tree[x].r){
		tree[x].max += val;
		return;
	}
	pushdown(x);
	if (pos <= ((tree[x].l + tree[x].r) >> 1)){
		add(x * 2, pos, val);
	} else {
		add(x * 2 + 1, pos, val);
	}
	update(x);
}

int main(){
	int n;
	cin >> n;
	build(1, 1, n);
	for (register int i = 1; i <= n; i++){
		cin >> a[i];
	}
	init(n);
	for (register int i = 1; i <= n; i++){
		int l, r;
		cin >> l >> r;
		if (a[i] > r) continue;
		int L = 1, R = i, l1 = 0, l2 = 0, r1 = 0, r2 = 0;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (get_max1(mid, i) <= r){
				R = mid - 1;
				l1 = mid;
			} else {
				L = mid + 1;
			}
		}
		L = 1;
		R = i;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (get_max1(mid, i) >= l){
				L = mid + 1;
				l2 = mid;
			} else {
				R = mid - 1;
			}
		}
		L = i;
		R = n;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (get_max1(i, mid) >= l){
				R = mid - 1;
				r1 = mid;
			} else {
				L = mid + 1;
			}
		}
		L = i;
		R = n;
		while (L <= R){
			int mid = (L + R) >> 1;
			if (get_max1(i, mid) <= r){
				L = mid + 1;
				r2 = mid;
			} else {
				R = mid - 1;
			}
		}
		if (l2 == 0 && r1 != 0){
			v[r1].push_back(Modification(l1, i, 1));
			v[r2 + 1].push_back(Modification(l1, i, -1));
		} else if (l2 != 0 && r1 == 0){
			if (l1 <= l2){
				v[i].push_back(Modification(l1, l2, 1));
				v[r2 + 1].push_back(Modification(l1, l2, -1));
			}
		} else {
			v[r2 + 1].push_back(Modification(l1, i, -1));
			if (l1 <= l2) v[i].push_back(Modification(l1, l2, 1));
			if (l2 < i) v[r1].push_back(Modification(l2 + 1, i, 1));
		}
	}
	for (register int i = 1; i <= n; i++){
		int size = v[i].size();
		for (register int j = 0; j < size; j++){
			add(1, v[i][j].l, v[i][j].r, v[i][j].val);
		}
		dp[i] = get_max2(1, i);
		if (i < n) add(1, i + 1, dp[i]);
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：Mobius127 (赞：4)

[题传](https://www.luogu.com.cn/problem/P7503)

先想一个巨 shaber 的暴力 DP：设 $f_{i}$ 为对前 $i$ 个人分段的最优解，则：

$$f_{i}=\max_{0\le j<i}\{f_{j}+\operatorname{W}(j+1, i)\}$$

其中：

$$\operatorname{W}(x, y)=\sum_{i=x}^y [l_i \le \max(x_j|j\in [x, y]) \le r_i]$$

暴力做显然是 $(n^2)$ 的，考虑优化。

如果考虑将决策中的 $i$ 右移一位，用线段树维护 $val_i(x)=f_{x-1}+\operatorname{W}(x, i)$ 的话，发现右移时无法快速修改有变化的位置（类似 $+1\ 0\ 0\ +1\dots$ 状物，不好维护）。

正难则反，考虑某个 $j$ 会对哪些决策位置 $(x, i)$ 有贡献。

我们将判断条件 $\max(x_p | p \in [x, i])$ 拆成两部分： $\max(x_p | p \in [x, j])$ 和 $\max(x_p | p \in [j, i])$。

不难画出下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0fis6r9e.png)

先考虑 $i\in [l2, r2]$，对于这一段位置，$i$ 已经满足了 $l_j \le \max(x_p | p \in [j, i]) \le r_j$，那么 $x$ 只要在 $[R_j, j]$ 之间即可。

然后是 $i\in [j, l2)$，此时 $x$ 就必须满足 $l_j \le \max(x_p | p \in [x, j]) \le r_j$，即 $x \in [r1, l1]$。

对于 $i > r2$，显然 $j$ 已经贡献不到了。

然后你就发现每个 $j$ 贡献到的 $i$ 是连续的，而且对于每个被贡献到的 $i$，函数 $\operatorname{W}$ 区间左端点 $x$ 也是连续的。

所以我们在 $j$ 处塞一个 $[r1, l1]$ 区间 +1 的操作，在 $l2$ 处塞一个 $(l1, j]$ 区间 +1 的操作（$[r1, l1]$ 在前面已经被加过一次了）。

然后在 $r2+1$ 的位置塞一个消除贡献的区间 -1 操作即可。

操作数显然是 $O(n)$ 的，$l1, l2, r1, r2$ 可以单调栈后二分找。

总复杂度 $O(n\log n)$。


### Code

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <vector>
#define st first
#define nd second
using namespace std;
typedef long long ll;
typedef pair <int, int> Pii;
const int INF=0x3f3f3f3f;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a, int b){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%mo)
		if(b&1) ret=1ll*ret*a%mo;
	return ret;
}
const int N=1e5+5;
namespace Segment{
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	int Mx[N*4], tag[N*4];
	void build(){
		memset(Mx, -9, sizeof(Mx));
		memset(tag, 0, sizeof(tag));
	}
	void upd(int k, int v){Mx[k]+=v, tag[k]+=v;}
	void pushdown(int k){if(tag[k]) upd(ls, tag[k]), upd(rs, tag[k]), tag[k]=0;}
	void pushup(int k){Mx[k]=max(Mx[ls], Mx[rs]);}
	void change(int k, int l, int r, int x, int v){
		if(l==r) return (void)(Mx[k]=max(Mx[k], v));pushdown(k);
		if(x<=mid) change(ls, l, mid, x, v);
		else change(rs, mid+1, r, x, v);
		pushup(k);
	}
	void modify(int k, int l, int r, int x, int y, int v){
		if(x>y) return ;//if(k==1) printf("make %d %d %d\n", x, y, v);
		if(x<=l&&r<=y) return upd(k, v);pushdown(k);
		if(x<=mid) modify(ls, l, mid, x, y, v);
		if(mid<y) modify(rs, mid+1, r, x, y, v);
		pushup(k);
	}
	#undef ls
	#undef rs
	#undef mid
}
int n, a[N], la[N], ra[N], f[N];
Pii L[N], R[N];
vector < pair<Pii, int> > op[N];
int sta[N], top=0;
int find(int x){
	int l=1, r=top, ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(a[sta[mid]]>=x) l=mid+1, ans=mid;
		else r=mid-1;
	}
	return sta[ans];
}
signed main(){
	n=read();
	for(int i=1; i<=n; ++i) a[i]=read();
	for(int i=1; i<=n; ++i) la[i]=read(), ra[i]=read();
	top=0;
	for(int i=1; i<=n; ++i){
		while(top&&a[sta[top]]<a[i]) --top;
		sta[++top]=i;L[i]=make_pair(find(la[i]), find(ra[i]+1)+1);
	}
	sta[top=0]=n+1;
	for(int i=n; i>=1; --i){
		while(top&&a[sta[top]]<a[i]) --top;
		sta[++top]=i;R[i]=make_pair(find(la[i]), find(ra[i]+1));
		// printf("(%d %d)\n", R[i].first, R[i].second-1);
	}
	for(int i=1; i<=n; ++i)
		if(a[i]<=ra[i])
			op[i].push_back(make_pair((Pii){L[i].nd, L[i].st}, 1)),
			op[R[i].st].push_back(make_pair((Pii){L[i].st+1, i}, 1)),
			op[R[i].nd].push_back(make_pair((Pii){L[i].nd, i}, -1));
	int ans=0;Segment :: build();
	for(int i=1; i<=n; ++i){
		// printf("for %d\n", i);
		Segment :: change(1, 1, n, i, f[i-1]);
		for(auto x : op[i])
			Segment :: modify(1, 1, n, x.st.st, x.st.nd, x.nd);
		f[i]=Segment :: Mx[1];
		// printf("find %d\n", f[i]);
		ans=max(f[i], ans);
	}
	printf("%d\n", ans);
	return 0;
}


```

---

## 作者：jockbutt (赞：4)

## 1.暴力

思考一种暴力的动态规划：

设 $ f_i $ 表示前 $ i $ 个数的答案，可以得出转移方程 $ f_i = f_j + sum_{i,j}$，其中 $ sum_{i,j} $ 表示 $ i $ 到 $ j $ 进行交流时这中间会有多少人达到符合要求的成绩。  
显然，这个 $ sum $ 是可以预处理出来的，这个暴力打牌的复杂度取决于你预处理的时间复杂度。

## 2.正解

考虑对于每一个位置参与贡献的区间。

首先，预处理出四个值，分别表示：  

第 $ i $ 个点左边第一个大于等于 $ l_i $ 的值的位置；  
左边第一个大于 $ r_i $ 的值的位置；  
右边第一个大于等于 $ l_i $ 的值的位置；  
右边第一个大于 $ r_i $ 的值的位置。

预处理可以用树状数组来维护。

然后枚举每个人，把他成功及格的最大区间每个数都加一，当枚举到了区间的最右点时，就把他的贡献给删去。区间修改和查询最大值这两个操作，可以用线段树维护，最后答案就是线段树中的最大值。

## 3.代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 1145141919
const int BUFFER=1<<20;
char RB[BUFFER],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER,stdin),RP=RB,*RP++):*RP++
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
const int maxn=2e5+10;
int a[maxn],l[maxn],r[maxn];
int c[maxn];
int mx[maxn<<2],tag[maxn<<2];
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
inline int lowbit(int x)	{return x&(-x);}
inline void add(int x,int d)	{for(;x;x-=lowbit(x))	c[x]=max(c[x],d);}
inline int getsum(int x)	{int s=0;for(;x<=n;x+=lowbit(x))	s=max(s,c[x]);return s;}
inline void pushup(int rt)	{mx[rt]=max(mx[ls],mx[rs])+tag[rt];}
void update(int rt,int l,int r,int L,int R,int d)
{
	if(L<=l&&r<=R)
	{
		mx[rt]+=d,tag[rt]+=d;
		return ;
	}
	if(L<=mid)	update(ls,l,mid,L,R,d);
	if(mid<R)	update(rs,mid+1,r,L,R,d);
	pushup(rt);
}
int ll[maxn],lr[maxn],rl[maxn],rr[maxn];
vector <int> u[maxn],v[maxn];
signed main(){
	n=read();
	for(int i=1;i<=n;++i)	a[i]=read();
	for(int i=1;i<=n;++i)	l[i]=read(),r[i]=read();
	for(int i=1;i<=n;++i)
	{
		add(a[i],i);
		ll[i]=getsum(l[i]),lr[i]=getsum(r[i]+1);
	}
	memset(c,0,sizeof(c));
	for(int i=n;i;--i)
	{
		add(a[i],n-i+1);
		rl[i]=n-getsum(l[i])+1,rr[i]=n-getsum(r[i]+1)+1;
		u[rl[i]].push_back(i),v[rr[i]].push_back(i);
	}
	for(int i=1;i<=n;++i)
	{
		// cerr << ll[i] << " " << lr[i] << endl;
		update(1,1,n,i,i,mx[1]);
		if(ll[i])	update(1,1,n,1,ll[i],1);
		if(lr[i])	update(1,1,n,1,lr[i],-1);
		for(int j : u[i])	if(ll[j]<j)	update(1,1,n,ll[j]+1,j,1);
		for(int j : v[i])	if(lr[j]<j)	update(1,1,n,lr[j]+1,j,-1);
	}
	cout << mx[1] << endl;
	return 0;
}
```


---

