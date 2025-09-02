# Partition Game

## 题目描述

You are given an array $ a $ of $ n $ integers. Define the cost of some array $ t $ as follows:

 $ $$$cost(t) = \sum_{x \in set(t) } last(x) - first(x), $ $  </p><p>where  $ set(t) $  is the set of all values in  $ t $  without repetitions,  $ first(x) $ , and  $ last(x) $  are the indices of the first and last occurrence of  $ x $  in  $ t $ , respectively. In other words, we compute the distance between the first and last occurrences for each distinct element and sum them up.</p><p>You need to split the array  $ a $  into  $ k $  consecutive segments such that each element of  $ a$$$ belongs to exactly one segment and the sum of the cost of individual segments is minimum.

## 说明/提示

In the first example, we can divide the array into $ [1,6,6,4] $ and $ [6,6,6] $ . Cost of $ [1,6,6,4] $ will be $ (1-1) + (3 - 2) + (4-4) = 1 $ and cost of $ [6,6,6] $ will be $ 3-1 = 2 $ . Total cost would be $ 1 + 2 = 3 $ .

In the second example, divide the array into $ [5,5],[5],[5,2,3] $ and $ [3] $ . Total Cost would be $ 1 + 0 + 0 + 0 = 1 $ .

## 样例 #1

### 输入

```
7 2
1 6 6 4 6 6 6```

### 输出

```
3```

## 样例 #2

### 输入

```
7 4
5 5 5 5 2 3 3```

### 输出

```
1```

# 题解

## 作者：meyi (赞：18)

一道有趣的决策单调性dp。

先推出暴力dp式子：定义 $f_{i,j}$ 为当前最后一块为第 $j$ 块，且该块右端点为 $i$ 时的最小代价，则有 $f_{i,j}=\min\limits_{k<i}\{f_{k,j-1}+cost(k+1,i)\}$。

感性证明一下决策单调性，也就是 $cost(i,j)+cost(i+1,j+1)\leq cost(i+1,j)+cost(i,j+1)$：若有一个元素 $x$ 同时在 $i$ 和 $j+1$ 处出现，则 $x$ 对 $cost(i,j+1)$ 的贡献比其他的大，其余情况下，$x$ 对两边的贡献一定相等，可以同时减去，则只剩同时在 $i$ 和 $j+1$ 处出现的 $x$ 对右边的贡献，得证。

但直接分治决策单调性dp的时间复杂度是 $O(kn^2\log n)$ 的，甚至不如暴力dp，发现瓶颈在于计算 $cost$。模拟一下分治过程，由当前状态转至子状态时有大量重复计算，考虑莫队思想，移动左右指针并计算贡献，可以证明每次计算 $cost$ 的均摊时间复杂度为常数级别。于是时间复杂度降至 $O(kn\log n)$，可以通过本题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int inf=0x3f3f3f3f,maxk=110,maxn=35e4+10;
int a[maxn],cnt,f[maxn][maxk],lst[maxn],m,n,nxt[maxn],pl=1,pre[maxn],pr,vis[maxn],sum;
inline int calc(int l,int r){
	while(pl<l){
		if(nxt[pl]<=pr)sum-=nxt[pl]-pl;
		++pl;
	}
	while(pl>l){
		--pl;
		if(nxt[pl]<=pr)sum+=nxt[pl]-pl;
	}
	while(pr<r){
		++pr;
		if(pre[pr]>=pl)sum+=pr-pre[pr];
	}
	while(pr>r){
		if(pre[pr]>=pl)sum-=pr-pre[pr];
		--pr;
	}
	return sum;
}
void solve(int l,int r,int L,int R,int now){
	if(l>r||L>R)return;
	ri mid=l+r>>1,val=inf,pos;
	for(ri i=L;i<mid&&i<=R;++i){
		ri tmp=f[i][now-1]+calc(i+1,mid);
		if(tmp<val)pos=i,val=tmp;
	}
	f[mid][now]=val;
	solve(l,mid-1,L,pos,now);
	solve(mid+1,r,pos,R,now);
}
int main(){
	scanf("%d%d",&n,&m);
	for(ri i=1;i<=n;++i)scanf("%d",a+i);
	for(ri i=1;i<=n;++i)f[i][0]=inf,pre[i]=lst[a[i]],lst[a[i]]=i;
	for(ri i=1;i<=n;++i)lst[a[i]]=n+1;
	for(ri i=n;i;--i)nxt[i]=lst[a[i]],lst[a[i]]=i;
	for(ri i=1;i<=m;++i)solve(1,n,0,n,i);
	printf("%d",f[n][m]);
	return 0;
}
```


---

## 作者：Cutest_Junior (赞：17)

## 题解 CF1527E 【Partition Game】

### 题意

+ 一个数组的代价为：对于所有在数组里的数 $x$，数组中最后一个值为 $x$ 的索引和第一个值为 $x$ 的索引的绝对差之和；
+ 给出一个长度为 $n$ 的数组 $a$，分成 $k$ 个连续段，求最小代价和；
+ $1\le a_i\le n\le35000$，$1\le k\le \min(n,100)$。

### 做法

设 $dp_{i,j}$ 为前 $i$ 个数分成 $j$ 个连续段需要的最小代价。

枚举最后一段的长度，可推出式子：$dp_{i,j}=\min\limits_{k=1}^i(dp_{k-1,j-1}+cost(k,i))$，其中 $cost(i,j)$ 表示把 $a_i,a_{i+1},\dots,a_{j-1},a_j$ 划成一段的代价。

考虑 $cost(i,j)$ 的求法。

若 $a_i,a_{i+1},\dots,a_{j-1}$ 中有任意数等于 $a_j$，则 $cost(i,j)=cost(i,j-1)+j-last_{a_j}$，其中 $last_{a_j}$ 表示 $a_j$ 最后一次出现的索引。

若没有，则显然 $cost(i,j)=cost(i,j-1)$。

然后就得到了一个 $O(kn^2)$ 的做法。

考虑优化，观察递推式 $dp_{i,j}=\min\limits_{k=1}^i(dp_{k-1,j-1}+cost(k,i))$，$dp_{i+1,j}=\min\limits_{k=1}^{i+1}(dp_{k-1,j-1}+cost(k,i+1))$，发现前半部分 $dp_{k-1,j-1}$ 是不变的，后半部分当且仅当 $k\le last_{a_{i+1}}$ 时才会改变，且改变的值恒为 $j-last_{a_j}$。

可以考虑维护一个数据结构，支持修改一个数，区间加一个数，区间求最小值。

直接线段树，复杂度已经是 $O(kn\log n)$，可过。

### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int inf = (1 << 30) - 1;

const int N = 4e4 + 5;

int a[N];

const int K = 105;

struct Tree {
	Tree *ls, *rs;
	int minn, lazy;
	
	Tree() {
		minn = 0, lazy = 0;
	}
	
	void update(int k) {
		minn += k;
		lazy += k;
	}
	
	void merge(Tree t1, Tree t2) {
		minn = min(t1.minn, t2.minn);
	}
} seg[(N * K) << 1];
int tot;

void build(Tree *t, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	t->ls = &seg[++tot];
	t->rs = &seg[++tot];
	build(t->ls, l, mid);
	build(t->rs, mid + 1, r);
}

void pushdown(Tree *t) {
	t->ls->update(t->lazy);
	t->rs->update(t->lazy);
	t->lazy = 0;
}

void change(Tree *t, int l, int r, int x, int y, int k) {
//	printf("c %d %d %d %d %d\n", l, r, x, y, k);
	if (x <= l && r <= y) {
		t->update(k);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(t);
	if (x <= mid) {
		change(t->ls, l, mid, x, y, k);
	}
	if (mid < y) {
		change(t->rs, mid + 1, r, x, y, k);
	}
	t->merge(*t->ls, *t->rs);
}

Tree query(Tree *t, int l, int r, int x, int y) {
//	printf("q %d %d %d %d\n", l, r, x, y);
	if (x <= l && r <= y) {
		return *t;
	}
	int mid = (l + r) >> 1;
	pushdown(t);
	Tree ans;
	ans.minn = inf;
	if (x <= mid) {
		ans.merge(ans, query(t->ls, l, mid, x, y));
	}
	if (mid < y) {
		ans.merge(query(t->rs, mid + 1, r, x, y), ans);
	}
//	printf("a %d %d %d %d %d\n", l, r, x, y, ans.minn);
	return ans;
}

int dp[N][K];

int last[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	tot = k;
	memset(dp, 0x3f, sizeof dp);
	for (int j = 1; j <= k; ++j) {
		build(&seg[j], 1, n);
//		dp[0]
	}
	dp[0][0] = 0;
//	printf("i");
	for (int i = 1; i <= n; ++i) {
//		printf("%d ", last[a[i]]);
//		printf("%d\n", i);
		for (int j = 1; j <= min(i, k); ++j) {
//			printf("C %d %d %d %d\n", j, i, i, dp[i - 1][j - 1]);
//			printf("%d ", j);
			change(&seg[j], 1, n, i, i, dp[i - 1][j - 1]);
//	printf("p");
			if (last[a[i]]) {
//				printf("C %d %d %d %d\n", j, 1, last[a[i]], i - last[a[i]]);
				change(&seg[j], 1, n, 1, last[a[i]], i - last[a[i]]);
			}
//			printf("Q %d %d %d\n", j, 1, i);
//	printf("t");
			dp[i][j] = query(&seg[j], 1, n, 1, i).minn;
//			printf("%d ", dp[i][j]);
		}
//		printf("\n");
		last[a[i]] = i;
	}
	int minn = inf;
	for (int j = 1; j <= k; ++j) {
		minn = min(minn, dp[n][j]);
	}
	printf("%d", minn);
//	printf("\n%d", dp[0][1]);
}
```

---

## 作者：FiraCode (赞：11)

## 题解思路：
我们可以用 dp，状态转移为：
$$dp_{i , j} = \min\{dp_{k , j - 1} + w_{k + 1 , i}\}$$
但时间复杂度至少为 $\mathcal{O(n^2k)}$。
我们怎么用数据结构去优化呢？
1.    我们就按 $j$ 分层。
每次从 $j - 1$ 的状态推出 $j$。
则 $f_i=dp_{i , j - 1}$。
而 $g_i = \min(f_k + w_{k + 1 , i})$。
2.  怎么维护：
设 $h_k = f_k + w_{k + 1 , i}$。
当 $i \to i + 1$。
分两种情况：
> 1.当前数没有出现过，则贡献为 $0$。
> 2.若他出现过，那么他的贡献就是加上了 $i + 1 -$ 上一次出现的位置。

这就是前缀加以及前缀最小值。

那么我们用线段树来维护 $h$ 数组即可。
## AC CODE:
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef int ll;
const int N = 35100;
int n , k;
int last[N] , pre[N] , f[N];
struct node {
	ll t;
	ll val;
}seg[N * 4];
int a[N];
void update (int id) {
	seg[id].val = min(seg[id * 2].val , seg[id * 2 + 1].val);
}
void settag (int id , int t) {
	seg[id].val = seg[id].val + t;
	seg[id].t = seg[id].t + t;
}
void pushdown (int id) {
	if (seg[id].t != 0) {//标记非空
		settag (id * 2 , seg[id].t);
		settag (id * 2 + 1 , seg[id].t);
		seg[id].t = 0;
	}
}
void build (int id , int l , int r) {
	seg[id].t = 0;
	if (l == r) {
		seg[id].val = f[l];
	}else {
		int mid = (l + r) >> 1;
		build (id * 2 , l , mid);
		build (id * 2 + 1 , mid + 1 , r);
		update (id);
	}
}
void modify (int id , int l , int r , int ql , int qr , int t) {
	if (l == ql && r == qr){ settag(id , t); return;}
	int mid = (l + r) / 2;
	pushdown (id);
	if (qr <= mid) modify (id * 2 , l , mid , ql , qr , t);
	else if (ql > mid) modify (id * 2 + 1 , mid + 1 , r , ql , qr , t);
	else {
		modify (id * 2 , l , mid , ql , mid , t);
		modify (id * 2 + 1 , mid + 1 , r, mid + 1 , qr ,t);
	}
	update (id);
}
ll query (int id , int l , int r , int ql , int qr) {
	if (l == ql && r == qr) return seg[id].val;
	int mid = (l + r) / 2;
	pushdown (id);
	if (qr <= mid) return query (id * 2 , l , mid , ql , qr);
	else if (ql > mid) return query (id * 2 + 1 , mid + 1 , r , ql , qr);
	else {
		return min(query (id * 2 , l , mid , ql , mid) , query (id * 2 + 1 , mid + 1 , r, mid + 1 , qr));
	}
}
int main() {
	scanf ("%d%d" , &n , &k);
	for (int i = 1; i <= n; ++ i) {
		scanf ("%d" , &a[i]);
		last[i] = pre[a[i]];
		pre[a[i]] = i;
	}
	f[0] = 0;
	for (int i = 1; i <= n; ++ i) f[i] = 1 << 30;
	for (int j = 1; j <= k; ++ j) {
		build (1 , 0 , n);
		for (int i = 1; i <= n; ++ i) {
			if (last[i] != 0) modify (1 , 0 , n , 0 , last[i] - 1 , i - last[i]);
			f[i] = query (1 , 0 , n , 0 , i - 1);
		}
	}	
	printf ("%d\n" , f[n]);
	return 0;
}
```

---

## 作者：Refined_heart (赞：4)

### 题外话

这题决策单调性我打出表来不太满足啊……不太懂

以及我并不太懂这题如何证明凸性……但是这样写它确实 A 了。

至于如何猜凸性……其实一开始想猜决策单调性，但是表它不符合四边形不等式，于是就寄了。然后又不能斜率优化，枚举做法只剩下凸性了。

### 题解

首先我们合理猜测其具有凸性。我们可以考虑 wqs 二分。

我们二分一个分段代价。然后我们考虑设 $f(i)$ 表示以 $i$ 结尾的最小分段代价，$cont(i)$ 表示这样分段的最小段数。

我们考虑如何优化转移。朴素转移显然是枚举上一个位置，我们考虑线段树优化转移，同时维护一下 $cont$ 属性，如果值相同就选择分段数目最小的。维护每个颜色上一次的出现位置，记为 $pre(v).$ 那么每次修改，相当于给 $[1, pre(v)]$ 都加上一个 $i - pre(v)$ 的贡献。线段树维护区间加即可。

那么我们可以达到 $O(n\log n\log V)$ 的复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
#define fi first
#define se second
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int N = 2e5 + 10;
const int inf = (1 << 30);
namespace SGT {
	int tag[N];
	struct Node {
		mutable int val, cnt;
		Node (int val_ = 0, int cnt_ = 0) {
			val = val_; cnt = cnt_;
		}
	} maxn[N];
	Node operator + (Node x, int y) {
		x.val += y;
		return x;
	}
	inline Node max(Node x, Node y) {
		if(x.val == y.val) return x.cnt > y.cnt ? x : y;
		return x.val < y.val ? x : y;
	}
	void pushup(int x) {
		maxn[x] = max(maxn[x << 1], maxn[x << 1 | 1]);
	}
	inline void pushr(int x, int v) {
		maxn[x].val += v;
		tag[x] += v;
	}
	inline void pushdown(int x) {
		if(tag[x]) {
			int &p = tag[x];
			pushr(x << 1, p);
			pushr(x << 1 | 1, p);
			p = 0;
		}
	}
	void changep(int x, int L, int R, int p, int v, int c) {
		if(L == R) {
			maxn[x].val += v;
			maxn[x].cnt += c;
			return ;
		}
		int mid = (L + R) >> 1; pushdown(x);
		if(p <= mid) changep(x << 1, L, mid, p, v, c);
		else changep(x << 1 | 1, mid + 1, R, p, v, c);
		pushup(x);
	}
	void change(int x, int L, int R, int l, int r, int v) {
		if(L >= l && R <= r) return pushr(x, v), void();
		int mid = (L + R) >> 1; pushdown(x);
		if(l <= mid) change(x << 1, L, mid, l, r, v);
		if(mid < r) change(x << 1 | 1, mid + 1, R, l, r, v);
		pushup(x);
	}
	Node query(int x, int L, int R, int l, int r) {
		if(l > r) return Node(0, 0);
		if(L >= l && R <= r) return maxn[x];
		int mid = (L + R) >> 1;
		Node ans = Node(0, 0); pushdown(x); 
		if(l <= mid) ans = query(x << 1, L, mid, l, r);
		if(mid < r) ans = max(ans, query(x << 1 | 1, mid + 1, R, l, r));
		return ans;
	}
	void build(int x, int L, int R) {
		tag[x] = 0; maxn[x] = Node(0, 0);
		if(L == R) return ;
		int mid = (L + R) >> 1; 
		build(x << 1, L, mid);
		build(x << 1 | 1, mid + 1, R);
	}
}
using namespace SGT;
int n, K, a[N], pre[N];
int f[N], cont[N];
bool check(int mid, int op = 0) {
	SGT :: build(1, 1, n + 1);
	for(int i = 0; i <= n; ++i) f[i] = cont[i] = pre[i] = 0;
	for(int i = 1; i <= n; ++i) {
		if(!pre[a[i]]) {
			pre[a[i]] = i;
		}
		else {
			change(1, 1, n + 1, 1, pre[a[i]], i - pre[a[i]]);
			pre[a[i]] = i;
		}
		Node tmp = query(1, 1, n + 1, 1, i);
		cont[i] = tmp.cnt + 1;
		f[i] = tmp.val + mid;
		changep(1, 1, n + 1, i + 1, f[i], cont[i]);
	}
	if(op == 1) {
		f[n] -= K * mid;
		cout << f[n] << '\n';
		exit(0);
	}
	return cont[n] >= K;
}
signed main() {
	freopen("in.txt","r",stdin);
	n = read(); K = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	int l = -1000000000, r = 1000000000, ans = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	check(ans, 1);
	return 0;
}
```


---

## 作者：V1mnkE (赞：2)

为表示方便，我们令 $last_{a_x}$ 表示 $a_x$ 上一次出现的位置。

首先可以用肉眼看出一个 $\text{dp}$，$dp_{i,j}$ 表示前 $i$ 个位置分割为 $j$ 个子段的最小代价，有显然的状态转移方程：
$$f_{i,j}=\min_{k=1}^{i}(f_{k-1,j-1}+val(k,i))$$

其中 $val(k,i)$ 表示以第 $k$ 个数字到第 $i$ 个数字作为一个字段的代价。

来看一下 $val(k,i)$ 怎么求：

若 $a_k$ 到 $a_{i-1}$ 中没有数等于 $a_i$，那么加入 $a_i$ 的代价为 $0$。显然， $val(k,i)=val(k,i-1)$。

反之，则 $val(k,i)=val(k,i-1)+(i-last_{a_i})$，因为 $a_{last_{a_i}}$ 到它的上一个的代价已经算过了，再往前也是，所以只用加上这次的代价。

注意到 $val(k,i)$ 可以预处理，此时我们得到了一个 $O(n^2k)$ 的做法。

接下来考虑优化，再回头看一眼状态转移方程，$f_{k-1,j-1}$ 这一部分是不变的，$val(k,i)$ 这一部分只有在 $k\le last_{a_i}$ 时才会改变，且值恒为 $i-last_{a_i}$。

~~观察到 CF 上的标签有数据结构~~，我们考虑用数据结构来维护 $f$ 数组，需要支持区间加、区间查询最小值，然后发现线段树就可以了，枚举 $j$，每次重建一颗线段树，这样还可以压掉一维，时间复杂度 $O(kn\log n)$。

```cpp
#include<bits/stdc++.h>
#define ls o<<1
#define rs o<<1|1 
using namespace std;
const int maxn=35005;
int t[maxn<<2],tag[maxn<<2];
int n,k,lst[maxn],a[maxn],f[maxn],pre[maxn];
int ans;
void add(int o,int val){
	t[o]+=val;
	tag[o]+=val;
	return ;
}
void pushup(int o){
	t[o]=min(t[ls],t[rs]);
	return ;
}
void pushdown(int o){
	add(ls,tag[o]);
	add(rs,tag[o]);
	tag[o]=0;
	return ;
}
void build(int o,int l,int r){
	tag[o]=0;
	if(l==r){
		t[o]=f[r];
		return ;
	}
	int mid=l+r>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(o);
}
void update(int o,int l,int r,int x,int y,int val){
	if(x<=l&&r<=y){
		add(o,val);
		return ;
	}
	pushdown(o);
	int mid=l+r>>1;
	if(x<=mid)update(ls,l,mid,x,y,val);
	if(y>mid)update(rs,mid+1,r,x,y,val);
	pushup(o);
}
void query(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		ans=min(ans,t[o]);
		return ;
	}
	pushdown(o);
	int mid=l+r>>1;
	if(x<=mid)query(ls,l,mid,x,y);
	if(y>mid)query(rs,mid+1,r,x,y);
	return ;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		lst[i]=pre[a[i]];
		pre[a[i]]=i;
	}
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(int i=1;i<=k;i++){
		build(1,0,n);
		for(int j=1;j<=n;j++){
			if(lst[j]!=0)update(1,0,n,0,lst[j]-1,j-lst[j]);
			ans=INT_MAX;
			query(1,0,n,0,j-1);
			f[j]=ans;
		}
	}
	cout<<f[n];
		
}
```


---

## 作者：final_trump (赞：2)

# CF1527E Partition Game

提供一个不需要脑子的决策单调性做法

首先从一个 naive 的 dp 方程写起：设 $f_{k,i}$ 表示将前 $i$ 个元素划分为 $k$ 段的最小代价，则有 $f_{k,i}=\min_{j<i}\{f_{k-1,j}+calc(j+1,i)\}$ ,即枚举转移点并计算中间贡献。对于那个 $calc$ 函数，好像并没有能够快速在线计算出它的方法，而我们决策单调性的转移又必须依赖于该函数。但是，这个决策是分层的，也就是我们大可不必用什么单调栈+wqs二分之类的麻烦东西，转而代之的是一个更好写的分治优化决策单调性。设函数 $solve(l,r,x,y)$ 是能够计算出区间 $[l,r]$ ，最优决策点在 $[x,y]$ 之间的所有 $f_i$ , 分治时只需枚举 $f_{mid}$ 的最优决策点 $b$ , 并递归处理 $solve(l,mid-1,x,b)$ 和 $solve(mid+1,r,b,y)$ 。

现在关键在于 $calc$ 函数的设计。观察代码中的函数调用，发现每次调用时它的左端点是递增的。这样我们有一个莫队的思路。值得注意的是，虽然莫队是离线的，但未经排序的莫队是在线的，而其左端点单调递增保证了其一层的移动指针复杂度是线性的。对于每一个数，我们记录一个双端队列，代表在当前区间中该数出现位置的下标集合，则其产生的贡献为 队尾-队首。每次移动时暴力更新每个数的答案即可，更新复杂度 $O(1)$ 。

对于算法的总时间复杂度，每次枚举 $k$ 分治的时间复杂度为 $O(n\log n)$ ，其中包括了枚举转移点的复杂度以及移动指针的复杂度。所以总时间复杂度为 $O(kn \log n)$ 。

注意莫队的转移顺序，否则可能会引起一些意想不到的错误。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lxl;
const int MAXN=35005,MAXK=105;
const int INF=2147483647;

int n,m;
int a[MAXN];
lxl f[MAXN][MAXK];
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-f;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int l=1,r;
lxl tmp;
deque<int> pos[MAXN];
inline int calcdis(int c){
	if(pos[c].size()<=1) return 0;
	return pos[c].back()-pos[c].front();
}

inline int calc(int x,int y){
    while(l>x) --l,tmp-=calcdis(a[l]),pos[a[l]].push_front(l),tmp+=calcdis(a[l]);
    while(r<y) ++r,tmp-=calcdis(a[r]),pos[a[r]].push_back(r),tmp+=calcdis(a[r]);
	while(l<x) tmp-=calcdis(a[l]),pos[a[l]].pop_front(),tmp+=calcdis(a[l]),++l;
    while(r>y) tmp-=calcdis(a[r]),pos[a[r]].pop_back(),tmp+=calcdis(a[r]),--r;
    return tmp;
}

int level;
void solve(int l,int r,int x,int y){
    if(l>r||x>y) return;
    int mid=(l+r)>>1,b;
    for(register int i=x;i<=min(y,mid);++i)
        if(calc(i+1,mid)+f[i][level-1]<f[mid][level]) f[mid][level]=calc(i+1,mid)+f[i][level-1],b=i;
    solve(l,mid-1,x,b);solve(mid+1,r,b,y);
}

int main(){
	register int i,j;
    n=read(),m=read();
    for(i=1;i<=n;++i) a[i]=read();
    for(i=0;i<=n;++i)
        for(j=0;j<=m;++j) f[i][j]=INF;
    f[0][0]=0;
    for(level=1;level<=m;++level) solve(1,n,0,n-1);
    printf("%lld",f[n][m]);
    return 0;
}
```



---

## 作者：睿智的憨憨 (赞：1)

## 解法分析

一种颜色的贡献是始末区间的长度，而断成连续的子段意味着中间有一些由相邻两点组成的小段区间，它们的区间长度的贡献被撤销了，总贡献最小就相当于撤销贡献最大，于是我们称撤销贡献为价值。

设 $f_{i,j}$ 表示 $[1,i]$ 被断成 $j$ 段时的最大价值。$f_{i,j}$ 从 $f_{k,j-1}$ 转移而来。固定 $j$，当 $i$ 向右挪动时，记 $p$ 表示上一个和 $i$ 颜色相同的位置，则从 $[p,i-1]$ 中选择上一子段右端点的价值增加了 $i-p$；从 $[1,p-1]$ 中选择上一子段右端点的价值不变。区间加，区间取 $\max$，可以用线段树优化，时间复杂度 $O(nk \log n)$。

## 参考代码

```
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pushf push_front
#define pushb push_back
#define popf pop_front
#define popb pop_back
#define lowbit(x) (x-(x&(x-1)))
using namespace std;
const int N = 35010;

int n, K, a[N], lst[N], pre[N];
ll f[N][110];//f[i][j]表示考虑了前 i 个数，分了 j 组最大价值和 
ll ans;

struct SegTree{
	ll val[4 * N], tag[4 * N];
	void build(int x, int l, int r){
		val[x] = tag[x] = 0;
		if (l == r)
			return ;
		int mid = (l + r) >> 1;
		build(2 * x, l, mid);
		build(2 * x + 1, mid + 1, r);
	}
	void pushup(int x){
		val[x] = max(val[2 * x], val[2 * x + 1]);
	}
	void pushdown(int x){
		val[2 * x] += tag[x], val[2 * x + 1] += tag[x];
		tag[2 * x] += tag[x], tag[2 * x + 1] += tag[x];
		tag[x] = 0;
	}
	void mdf(int x, int l, int r, int L, int R, int v){
		if (R < l || r < L)
			return ;
		if (L <= l && r <= R){
			val[x] += v;
			tag[x] += v;
			return ;
		}
		pushdown(x);
		int mid = (l + r) >> 1;
		mdf(2 * x, l, mid, L, R, v);
		mdf(2 * x + 1, mid + 1, r, L, R, v);
		pushup(x);
	}
} st;

int main(){
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		if (!pre[a[i]])
			pre[a[i]] = i;
		lst[a[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		ans += lst[i] - pre[i];
	//初值 
	//dp
	for (int j = 2; j <= K; j++){
		st.build(1, 1, n);
		memset(pre, 0, sizeof(pre));
		for (int i = 1; i <= n; i++){
			if (i >= j){
				st.mdf(1, 1, n, i - 1, i - 1, f[i - 1][j - 1]);
				if (pre[a[i]])
					st.mdf(1, 1, n, pre[a[i]], i - 1, i - pre[a[i]]);
				f[i][j] = st.val[1];
			}
			pre[a[i]] = i;
		}
	}
	//答案 
	ll mx = 0;
	for (int i = 0; i <= K; i++)
		mx = max(mx, f[n][i]);
	printf("%lld\n", ans - mx);
	return 0;
}
```

---

## 作者：gdf_yhm (赞：1)

[CF1527E](https://www.luogu.com.cn/problem/CF1527E)

[Partition Game](https://codeforces.com/problemset/problem/1527/E)

### 思路

dp 题。

设 $dp_{i,j}$ 表示前 $i$ 个数分为 $j$ 段的最小代价。

式子：

$dp_{i,j}=\min_{k=1}^{i-1} (dp_{k,j-1}+w(k+1,i))$

压一维：

$dp_{i}=\min_{k=1}^{i} (dp_{k-1}+w(k,i))$

其中，$w(i,j)$ 表示题目中的 $cost(sub(i,j))$。

问题在于快速求 $w(i,j)$。

设 $b_k=dp_{k-1}+w(k,i)$，则 $dp_i=\min_{k=1}^{i} dp_k$。每次转移需要求出数组 $b$ 的最小值。每个 $a_i$ 的对 $b$ 贡献是 $b_1$ 到 $b_{lst_{a_j}}$ 加上 $i-lst_{a_j}$，其中 $lst_i$ 是数值 $i$ 上次在 $a$ 中出现的位置。

所以要维护 $b$，区间加和最小值，使用线段树。

用上一轮的 $dp[]$ 值建树，从 $1$ 到 $n$，每读进一个 $a_i$，$upd$ 更新线段树，$que$ 询问最小值即为 $dp_i$。

$O(kn\log n)$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=35010;

int n,k,a[maxn];
int tree[maxn<<2],tag[maxn<<2],dp[maxn];
int lst[maxn],pre[maxn];
void build(int nd,int l,int r){
	if(l==r){
		tree[nd]=dp[l-1];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	tree[nd]=min(tree[ls],tree[rs]);
}
void push(int nd,int l,int r){
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	tree[ls]+=tag[nd];
	tag[ls]+=tag[nd];
	tree[rs]+=tag[nd];
	tag[rs]+=tag[nd];
	tag[nd]=0;
}
void updata(int nd,int l,int r,int x,int y,int w){
	if(l>=x&&r<=y){
		tree[nd]+=w;
		tag[nd]+=w;
		return ;
	}
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(x<=mid)updata(ls,l,mid,x,y,w);
	if(y>mid)updata(rs,mid+1,r,x,y,w);
	tree[nd]=min(tree[ls],tree[rs]);
}
int query(int nd,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		return tree[nd];
	}
	if(tag[nd])push(nd,l,r);
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(y<=mid)return query(ls,l,mid,x,y);
	if(x>mid)return query(rs,mid+1,r,x,y);
	return min(query(ls,l,mid,x,y),query(rs,mid+1,r,x,y));
}
void sovle(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		lst[i]=pre[a[i]];
		pre[a[i]]=i;
	}
	memset(dp,0x3f,sizeof(dp));dp[0]=0;
	for(int i=1;i<=k;i++){
		memset(tag,0,sizeof(tag));
		build(1,1,n);
		for(int j=1;j<=n;j++){
			if(lst[j])updata(1,1,n,1,lst[j],j-lst[j]);
			dp[j]=query(1,1,n,1,j);
		}
	}
	cout<<dp[n]<<"\n";
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

//	cin.tie(0);cout.tie(0);
//	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}
```

---

### 套路

[CF833B The Bakery](https://www.luogu.com.cn/problem/CF833B)

式子同样形如：$dp_{i}=\max_{k=1}^{i} (dp_{k-1}+w(k,i))$。

考虑每个 $a_i$ 对 $dp[]$ 的贡献。

```cpp
int n,k,a[maxn];
int tree[maxn<<2],dp[maxn],tag[maxn<<2];
int pre[maxn],lst[maxn];
void build(int nd,int l,int r){
  //同
	tree[nd]=max(tree[ls],tree[rs]);
}
void push(int nd,int l,int r){
  //同
}
void updata(int nd,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		tree[nd]++;tag[nd]++; 
		return ;
	}
  //同
	tree[nd]=max(tree[ls],tree[rs]);
}
int query(int nd,int l,int r,int x,int y){
  //同
	return max(query(ls,l,mid,x,y),query(rs,mid+1,r,x,y)); 
}
void sovle(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		lst[i]=pre[a[i]]+1;
		pre[a[i]]=i;
	}
	for(int i=1;i<=k;i++){
		memset(tree,0,sizeof(tree));
		memset(tag,0,sizeof(tag));
		build(1,1,n);
		for(int j=1;j<=n;j++){
			updata(1,1,n,lst[j],j);
			dp[j]=query(1,1,n,1,j);
		}
	}
	cout<<dp[n]<<"\n";
}
```


---

## 作者：Leap_Frog (赞：1)

### P.S.
一看这个题，一看这个数据范围，瞬间觉得它是[原题](https://www.luogu.com.cn/problem/CF833B)  
[前置](https://www.luogu.com.cn/blog/command-block/dp-di-jue-ce-dan-diao-xing-you-hua-zong-jie)  

### Solution.
~~会了前置你就做完了~~  
这类分割区间问题基本决策都单调。  
然后按照前置里的分治套指针暴跳法就做完了。  
统计贡献的话我们需要把贡献拆开算。  
最远两个数之间距离可以看作是每对最近数之间距离和。  
所以扩充右端点时如果上一个数大于左端点，就加上距离。  
然后收缩、左端点同理，最后直接套即可。  
具体见代码注释。  

### Coding.
```cpp
//是啊……你就是那只鬼了……所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:0;
}/*}}}*/
int n,K,a[35005],ls[35005],nx[35005],tn[35005],dp[105][35005],L,R,sm;
inline void move(int dl,int dr)
{//这个就是指针暴跳
	while(L<dl) sm-=nx[L]<=R?nx[L]-L:0,L++;
	while(L>dl) L--,sm+=nx[L]<=R?nx[L]-L:0;
	while(R<dr) R++,sm+=ls[R]>=L?R-ls[R]:0;
	while(R>dr) sm-=ls[R]>=L?R-ls[R]:0,R--;
}
inline void work(int l,int r,int dl,int dr,int dep)
{//这个就是之前的单调性分治
	int md=(l+r)>>1,dmd,vl=2e9;if(l>r||dl>dr) return;
	//printf("%d %d %d %d %d\n",l,r,dl,dr,dep);
	for(int i=dl;i<=md&&i<=dr;i++)
	{
		move(i,md);int nv=dp[dep-1][i-1]+sm;
		if(nv<vl) vl=nv,dmd=i;
	}
	dp[dep][md]=vl,work(l,md-1,dl,dmd,dep),work(md+1,r,dmd,dr,dep);
}
int main()
{
	read(n),read(K);for(int i=1;i<=n;i++) read(a[i]),tn[i]=n+1;
	for(int i=n;i;i--) nx[i]=tn[a[i]],tn[a[i]]=i;
	memset(tn,0,sizeof(tn));for(int i=1;i<=n;i++) ls[i]=tn[a[i]],tn[a[i]]=i;
	//以上预处理
	memset(dp[0],0x3f,sizeof(dp[0])),dp[0][0]=0;for(int i=1;i<=K;i++) work(1,n,1,n,i);
	//for(int i=1;i<=K;i++) for(int j=1;j<=n;j++) printf("%d%c",dp[i][j],j==n?'\n':' ');
	return printf("%d\n",dp[K][n]),0;
}
```

---

## 作者：LastKismet (赞：0)

# Sol
这是个经典的区间划分问题。DP 解决。

首先这道题是有决策单调性的，感性理解一下，我们要最小化代价，因此倘若扩大区间则必然会增多区间内的种类数，最优决策点若相较前一个左移，那前一个的最优决策点显然也理应左移不劣。

详细证明需要四边形不等式，推一下式子就行，这里省略。

然后考虑快速计算区间贡献，一个非常典的 trick 是类莫队暴力跳区间，在分治做法下这种操作的复杂度是正确的，大致 $O(n\log n)$ 级别。

记录下每个点前一位后一位同色的位置即可。移动边界时动态更新贡献。详见代码。

# Code
```cpp
int n,k;
int a[N];
int lst[N],nxt[N],tmp[N];
int f[K][N];
 
int L=1,R=0,ans=0;
int query(int l,int r){
    while(R<r)if(lst[++R]>=L)ans+=R-lst[R];
    while(L>l)if(nxt[--L]<=R)ans+=nxt[L]-L;
    while(R>r)if(lst[R--]>=L)ans-=R+1-lst[R+1];
    while(L<l)if(nxt[L++]<=R)ans-=nxt[L-1]-L+1;
    return ans;
}
inline void solve(int k,int l,int r,int pl,int pr){
    if(l>r)return;
    int m=l+r>>1,pm;f[k][m]=INT_MAX;
    rep(i,pl,min(pr,m))if(f[k][m]>f[k-1][i-1]+query(i,m)){
        f[k][m]=f[k-1][i-1]+query(i,m);
        pm=i;
    }
    solve(k,l,m-1,pl,pm);
    solve(k,m+1,r,pm,pr);
}
inline void Main(){
    read(n,k);
    rep(i,1,n)read(a[i]);
    rep(i,1,n)lst[i]=tmp[a[i]],tmp[a[i]]=i;
    rep(i,1,n)tmp[a[i]]=n+1;
    per(i,n,1)nxt[i]=tmp[a[i]],tmp[a[i]]=i;
    rep(i,1,n)f[1][i]=query(1,i);
    rep(t,2,k)solve(t,t,n,t,n);
    put(f[k][n]);
}
```

---

## 作者：xukehg (赞：0)

决策单调性是什么？没听说过。

先设计朴素 dp。定义 $dp_{i,j}$ 表示前 $i$ 个数划分为 $j$ 段且 $i$ 是最后一段的结尾。定义位置 $i$ 到 $j$ 的权值为 $\operatorname{calc(i,j)}$，则显然有转移：$dp_{i,j} = \min(dp_{i,j},dp_{k,j - 1} + \operatorname{calc}(k + 1,i))$。时间复杂度 $O(n ^ 2k)$，考虑优化。

观察 $dp_{k,j - 1} + \operatorname{calc}(k + 1,i)$ 的变化，发现如果新加入的 $i$ 存在前驱 $pre$，则对于 $k < pre$，$\operatorname{calc}(k + 1,i)$ 增加 $i - pre$。这是一个定值，所以考虑建 $k$ 棵线段树，第 $l$ 个线段树维护 $dp_{k,l} + \operatorname{calc}(k + 1,i)$。于是加入一个数转变为区间加操作，转移变为区间最小操作，可以轻易维护。注意先把 $i$ 的贡献加入到线段树，再去转移。时间复杂度 $O(nk\log n )$。

[记录。](https://codeforces.com/contest/1527/submission/293769173)

---

## 作者：Lvlinxi2010 (赞：0)

学校题单里的线段树优化 dp 题，来写一篇题解。

状态定义：$dp_{i,j}$ 表示前 $i$ 个数分成 $j$ 个连续子序列的最小代价和。

我们可以很容易列出一个朴素的 dp 转移方程：

$dp_{i,j}=\min\{dp_{k,j-1}+cost(k+1,i)\}(k<i)$

从大到小枚举 $k$ 可以做到 $\mathcal{O(n^2k)}$。

考虑优化，可以发现第 $j$ 层只和第 $j-1$ 层有关，我们从小到大枚举 $j$，再从小到大枚举 $i$，在枚举 $i$ 的过程中求出 $pre_{a_i}$，即 $a_i$ 上一次出现的位置（也可以在枚举前 $\mathcal{O(n)}$ 预处理）。

假设我们已经求出了 $cost(k+1,i-1)(k<i-1)$，那 $cost(k+1,i)$ 只有两种情况：

当 $k+1\leq pre_{a_i}$ 时，$cost(k+1,i)\leftarrow cost(k+1,i-1)+i-pre_{a_i}$。

当 $k+1>pre_{a_i}$ 时，$cost(k+1,i)\leftarrow cost(k+1,i)$。

用线段树维护 $dp_{k,j-1}+cost(k+1,i)$，支持区间加和区间查询最小值，总时间复杂度 $\mathcal{O(kn\log n)}$。

附上代码：

```cpp
#include<bits/stdc++.h>
#define FL(i,a,b) for(int i=(a);i<=(b);i++)
#define FR(i,a,b) for(int i=(a);i>=(b);i--)
#define ll long long
using namespace std;
const int MAXN = 35e3 + 10;
const int MR = 1e2 + 10;
int a[MAXN];
int pre[MAXN],f[MAXN];
struct Segment_Tree{
	#define ls (x<<1)
	#define rs (x<<1|1)
	struct node{
		int l,r,mn,tg;
		void tag(int x){
			mn+=x;
			tg+=x; 
		}
	}t[MAXN<<2];
	void pushup(int x){
		t[x].mn=min(t[ls].mn,t[rs].mn);
	}
	void pushdown(int x){
		if(t[x].tg){
			t[ls].tag(t[x].tg);
			t[rs].tag(t[x].tg);
		}
		t[x].tg=0;
	} 
	void build(int x,int l,int r){
		t[x].l=l,t[x].r=r,t[x].tg=0;
		if(l==r){
			t[x].mn=f[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	void update(int x,int l,int r,int k){
		if(l<=t[x].l&&t[x].r<=r){
			t[x].tag(k);
			return ;
		}
		int mid=(t[x].l+t[x].r)>>1;
		pushdown(x);
		if(l<=mid) update(ls,l,r,k);
		if(r>mid) update(rs,l,r,k);
		pushup(x);
	}
	int query(int x,int l,int r){
		if(l<=t[x].l&&t[x].r<=r) return t[x].mn;
		int mid=(t[x].l+t[x].r)>>1;
		pushdown(x);
		if(r<=mid) return query(ls,l,r);
		else if(l>mid) return query(rs,l,r);
		else return min(query(ls,l,r),query(rs,l,r));
	}
	#undef ls
	#undef rs
}T;
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	FL(i,1,n) scanf("%d",&a[i]);
	int now=0;
	f[0]=0;
	FL(i,1,n){
		if(pre[a[i]]) now+=i-pre[a[i]];
		f[i]=now;
//		printf("%d\n",f[i]);
		pre[a[i]]=i;
	}
	FL(j,2,k){
		T.build(1,0,n);
		memset(pre,0,sizeof(pre));
		FL(i,1,n){
			if(pre[a[i]]) T.update(1,0,pre[a[i]]-1,i-pre[a[i]]);
			f[i]=T.query(1,0,i-1);
			pre[a[i]]=i; 
		}
	}
	printf("%d\n",f[n]);
}
```

---

## 作者：Jerrywang09 (赞：0)

非常经典的线段树优化 DP。考虑分阶段 DP，先在外层枚举 $k$，然后对所有的 $f(k-1, i)$ 建线段树。

然后考虑贡献。设 $a_i$ 上一次出现是 $a_{pre}$，则有转移 $f(k, i)=\max(f(k, i), f(k-1, j)+i-pre)$，其中 $0\le j<pre$。这也就是对线段树上区间 $[0,pre-1]$ 区间加 $i-pre$，还需要一个区间最小值查询。

```cpp
// Title:  Partition Game
// Source: CF1527E
// Author: Jerrywang
#include <bits/stdc++.h>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=35005;
using namespace std;

int n, k, a[N], pre[N]; ll f[N];

struct node
{
	int l, r; ll x, add;
	void tag(ll y)
	{
		add+=y, x+=y;
	}
} t[N<<2];
#define lc p<<1
#define rc p<<1|1
void up(int p)
{
	t[p].x=min(t[lc].x, t[rc].x);
}
void down(int p)
{
	if(!t[p].add) return;
	t[lc].tag(t[p].add), t[rc].tag(t[p].add);
	t[p].add=0;
}
void build(int p, int l, int r)
{
	t[p]={l, r}; t[p].add=0;
	if(l==r)
	{
		t[p].x=f[l];
		return;
	}
	int mid=l+r>>1;
	build(lc, l, mid), build(rc, mid+1, r);
	up(p);
}
void modify(int p, int l, int r, int x)
{
	if(l<=t[p].l && t[p].r<=r) return t[p].tag(x);
	down(p); int mid=t[p].l+t[p].r>>1;
	if(l<=mid) modify(lc, l, r, x);
	if(r>mid)  modify(rc, l, r, x);
	up(p);
}
ll query(int p, int l, int r)
{
	if(l<=t[p].l && t[p].r<=r) return t[p].x;
	down(p); int mid=t[p].l+t[p].r>>1;
	if(r<=mid) return query(lc, l, r);
	if(l>mid)  return query(rc, l, r);
	return min(query(lc, l, r), query(rc, l, r));
}

int main()
{
#ifdef Jerrywang
	freopen("E:/OI/in.txt", "r", stdin);
#endif
	scanf("%d%d", &n, &k);
	rep(i, 1, n) scanf("%d", a+i);
	memset(f, 0x3f, sizeof f);
	f[0]=0;
	rep(kk, 1, k)
	{
		build(1, 0, n); memset(pre, 0, sizeof pre);
		rep(i, 1, n)
		{
			if(pre[a[i]]) modify(1, 0, pre[a[i]]-1, i-pre[a[i]]);
			f[i]=query(1, 0, i-1);
			pre[a[i]]=i;
		}
	}
	printf("%lld", f[n]);
	
	return 0;
}
```

---

## 作者：Leeb (赞：0)

### 题意简述

给出一个长度为 $n$ 的序列，将其划分成 $k$ 段，使得贡献和最小。

对于一段区间 $[l,r]$ 的贡献为：其中每个数字的最后一次出现的位置减去其第一次出现的位置。

### 解题思路

看到区间划分，立马想到 DP。令 $f_{i,j}$ 表示前 $i$ 个数划分为 $j$ 个区间的最优解。最初转移方程为：$f_{i,j}=\min\{f_{k,j-1}+\operatorname{calc}(k+1,i)\}$。

时间复杂度 $\Theta(n^2m)$，显然直接做会 TLE。

所以考虑用数据结构优化掉一层 $n$。

不难发现对于动规的第二位是可滚动的，所以不妨在固定第二维后，将第一维的信息甩到一棵线段树中去，这样就可以 $\Theta(\log n)$ 地维护区间最小值了。此时线段树中维护的实质上是 $f_i+\operatorname{calc}(i+1,now)$，$now$ 就是第一维更新到的位置，$\operatorname{calc}(l,r)$ 是区间 $[l,r]$ 的贡献。

查询的话，直接查询区间最小值即可。现在，问题转换为：在加入 $a_i$ 后，如何 update？

因为从前往后加入 $a_i$ 后，并不会影响 $a_i$ 首次出现的位置，只会影响 $a_i$ 最后一次出现的位置，所以我们记 $lst_{a_i}$ 为 $a_i$ 最后一次出现的位置，此时就将 $[0,now]$ 的区间分成了两段：$[0,lst_{a_i}),[lst_{a_i},now]$。为什么这样划分呢？

注意上面提到的，线段树中维护的信息是 $f_i+\operatorname{calc}(i+1,now)$，当此处的 $i$ 取到 $[lst_{a_i},now]$ 时，$\operatorname{calc}(i+1,now)=0$，即不做贡献，而当其取到 $[0,lst_{a_i})$ 时，$\operatorname{calc}(i+1,now)$ 全都加上了 $i-lst_{a_i}$，所以只需要用线段树区间更新即可。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 35005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
// #define int long long 
#define ll long long
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, k, a[N], dp[N], lst[N];
struct Tree {
    int l, r, val, lay;
    // Tree() {
    //     val = inf, lay = 0;
    // }
} tree[N << 2];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {
    n = in(), k = in();
    for (int i = 1; i <= n; ++i) a[i] = in();
    mem(dp, 0x3f); dp[0] = 0;
}
inline void push_up(int x) {
    tree[x].val = min(tree[ls].val, tree[rs].val);
}
inline void push_down(int x) {
    if (tree[x].lay) {
        int lay = tree[x].lay;
        tree[x].lay = 0;
        tree[ls].val += lay, tree[rs].val += lay;
        tree[ls].lay += lay, tree[rs].lay += lay;
    }
}
inline void build(int x, int l, int r) {
    tree[x].l = l, tree[x].r = r,
    tree[x].val = inf, tree[x].lay = 0;
    if (l == r) {
        tree[x].val = dp[l];
        return ;
    }   
    int mid = l + r >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    push_up(x);
}
inline void update(int x, int l, int r, int val) {
    if (tree[x].l > r || tree[x].r < l) return ;
    if (tree[x].l >= l && tree[x].r <= r) {
        tree[x].val += val, tree[x].lay += val;
        return ;
    }
    push_down(x);
    update(ls, l, r, val), update(rs, l, r, val);
    push_up(x);
}
inline int query(int x, int l, int r) {
    if (tree[x].l > r || tree[x].r < l) return inf;
    if (tree[x].l >= l && tree[x].r <= r) return tree[x].val;
    push_down(x);
    return min(query(ls, l, r), query(rs, l, r));
}
inline void work() {
    while (k--) {
        build(1, 0, n); mem(lst, 0);
        for (int i = 1; i <= n; ++i) {
            if (lst[a[i]])
                update(1, 0, lst[a[i]] - 1, i - lst[a[i]]);
            lst[a[i]] = i, dp[i] = query(1, 0, i - 1);
        }
    }
    out(dp[n], '\n');
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

## 作者：LCat90 (赞：0)

首先设 $dp_{i,j}$ 表示将前 $i$ 位划分成 $j$ 段的最小值。有转移：$dp_{i,j}=\min \{dp_{k-1,j-1}+\text{cost}(k,j)\}$。

$\text{cost(k,j)}$ 是比较好求的，复杂度共为 $O(n^2k)$。

考虑优化。我们以 $j$ 为转移的阶段。对于阶段 $j'$ 的 $i$，它由 $j'-1$ 阶段的 $k(k<i)$ 最小值转移而来。并且加上一些权值。

这些权值，我们可以在 $j'$ 上进行修改，查询则也是 $j'$ 上的，将这些答案更新到当前的 $j$ 阶段的 $dp$ 值，作为新的版本继续传承下去。这便是线段树优化 DP 的思路。

时间复杂度为 $O(nk\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3.5e4 + 5; 
int n, k, sb[N], dp[N], lst[N], a[N]; 
struct node { int l, r, tag, minn; } T[N << 2];
void pushup(int p) {
	if(T[p].tag) {
		T[p << 1].tag += T[p].tag, T[p << 1 | 1].tag += T[p].tag;
		T[p << 1].minn += T[p].tag, T[p << 1 | 1].minn += T[p].tag;
		T[p].tag = 0;
	}
}
void pushdown(int p) { 
	T[p].minn = min(T[p << 1].minn, T[p << 1 | 1].minn);
}
void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r, T[p].minn = 1e9, T[p].tag = 0;
	if(l == r) {
		T[p].minn = dp[l];
		return ;	
	}
	int mid = l + r >> 1; 
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushdown(p);
}
void update(int p, int l, int r, int x) {
	if(l <= T[p].l and T[p].r <= r) {
		T[p].tag += x;
		T[p].minn += x;
		return ;
	}
	pushup(p);
	int mid = T[p].l + T[p].r >> 1;
	if(l <= mid) update(p << 1, l, r, x);
	if(r > mid) update(p << 1 | 1, l, r, x);
	pushdown(p);
}
int query(int p, int l, int r) {
	if(l <= T[p].l and T[p].r <= r) return T[p].minn;
	pushup(p);
	int mid = T[p].l + T[p].r >> 1, ans = 1e9;
	if(l <= mid) ans = min(ans, query(p << 1, l, r));
	if(r > mid) ans = min(ans, query(p << 1 | 1, l, r));
	return ans;
} 
signed main() {	
	cin >> n >> k;
	for(int i = 1;i <= n; ++i) {
		cin >> a[i]; 
		lst[i] = sb[a[i]];
		sb[a[i]] = i;
	} 
    dp[0] = 0;
    for(int i = 1;i <= n; ++i) dp[i] = 1e9;
	for(int j = 1;j <= k; ++j) {
		build(1, 0, n); //cout << j << " ";
		for(int i = 1;i <= n; ++i) {
			if(lst[i]) update(1, 0, lst[i] - 1, i - lst[i]);
			dp[i] = query(1, 0, i - 1); // dp i,j = min dp k,j-1 + ...
           // cout << i << " " << dp[i] << "\n";
        }
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

* 设 $dp[i][j]$ 表示当前考虑到第 $i$ 段，第 $i$ 段末尾是 $j$ 的最小总代价，考虑怎么从 $dp[i - 1][]$ 转移到 $dp[i][]$。
* 考虑将一段的代价拆成，对于所有中间没有该数的相同的数对，它们的距离的和。
* 设一个数组 $b$，一开始 $b[] = dp[i - 1][]$。考虑预处理出 $last[i]$ 表示 $i$ 前面的第一个等于 $a[i]$ 的位置，从小往大枚举 $j$，考虑当 $j - 1$ 到 $j$ 的时候把 $a[j]$ 的贡献算进去，考虑 $a[j]$ 显然对 $b[1 \cdots last[j] - 1]$ 都有 $j - last[j]$ 的贡献，于是我们需要维护一个支持区间加和前缀求最小值的数据结构，用线段树即可。
* 时间复杂度 $\mathcal O(k n \log n)$。

```cpp
for (int i = 1; i <= n; i++) appear[a[i]].push_back(i);
    for (int i = 1; i <= n; i++) for (int j = 0; j < appear[i].size(); j++) if (j == 0) last[appear[i][j]] = 0; else last[appear[i][j]] = appear[i][j - 1];
    for (int i = 1; i <= n; i++) dp[i] = inf; dp[0] = 0;
    for (int i = 1; i <= k; i++) {
        SGT.Build(1, 0, n);
        for (int j = 1; j <= n; j++) {
            if (last[j] != 0) SGT.Modify(1, 0, last[j] - 1, j - last[j]);
            dp[j] = SGT.Query(1, 0, n, 0, j - 1);
        }
    }
```

---

