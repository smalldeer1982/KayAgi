# [ABC330E] Mex and Update

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc330/tasks/abc330_e

長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。  
 以下の $ Q $ 個のクエリに、与えられる順番で対応してください。

$ k $ 番目のクエリは以下の形式で与えられます。

> $ i_k $ $ x_k $

- まず、 $ A_{i_k}\ =\ x_k $ と変更する。この変更は以降のクエリにも引き継がれる。
- その後、 $ A $ の $ \rm{mex} $ を出力する。
  - $ A $ の $ \rm{mex} $ とは、 $ A $ に含まれない最小の非負整数を指す。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,Q\ \le\ 2\ \times\ 10^5 $
- $ 0\ \le\ A_i\ \le\ 10^9 $
- $ 1\ \le\ i_k\ \le\ N $
- $ 0\ \le\ x_k\ \le\ 10^9 $
 
### Sample Explanation 1

最初、数列 $ A $ は $ (2,0,2,2,1,1,2,5) $ です。 この入力では、 $ 5 $ つのクエリを処理します。 - $ 1 $ 番目のクエリで $ A_4\ =\ 3 $ と変更し、 $ A=(2,0,2,3,1,1,2,5) $ となりました。 - この時点で、 $ A $ の $ \rm{mex} $ は $ 4 $ です。 - $ 2 $ 番目のクエリで $ A_4\ =\ 4 $ と変更し、 $ A=(2,0,2,4,1,1,2,5) $ となりました。 - この時点で、 $ A $ の $ \rm{mex} $ は $ 3 $ です。 - $ 3 $ 番目のクエリで $ A_6\ =\ 3 $ と変更し、 $ A=(2,0,2,4,1,3,2,5) $ となりました。 - この時点で、 $ A $ の $ \rm{mex} $ は $ 6 $ です。 - $ 4 $ 番目のクエリで $ A_8\ =\ 1000000000 $ と変更し、 $ A=(2,0,2,4,1,3,2,1000000000) $ となりました。 - この時点で、 $ A $ の $ \rm{mex} $ は $ 5 $ です。 - $ 5 $ 番目のクエリで $ A_2\ =\ 1 $ と変更し、 $ A=(2,1,2,4,1,3,2,1000000000) $ となりました。 - この時点で、 $ A $ の $ \rm{mex} $ は $ 0 $ です。

## 样例 #1

### 输入

```
8 5
2 0 2 2 1 1 2 5
4 3
4 4
6 3
8 1000000000
2 1```

### 输出

```
4
3
6
5
0```

# 题解

## 作者：yhx0322 (赞：6)

## Description
给出一个长度为 $N$ 的序列 $A$，有 $Q$ 次询问，每次输入两个整数 $i,k$，表示将 $A$ 序列中下标为 $i$ 的数字改为 $x$。

每次询问输出序列的 $\text{mex}$。$\text{mex}$ 指的是序列中最小的没有出现过的数字。

## Solution
这道题如果用 `set` 存储已经出现过的数，每次删除、查找时间复杂度较高。

把问题做一个转化：可以存储没有出现过的数字！

用一个 `map` 标记每个数字出现的次数，每次询问将 $mp_{a_i}$ 减 $1$，并且将 $mp_k$ 加 $1$。如果发现 $mp_{a_i} = 0$，这样就将原来的数字放到 `set` 中。

或者说 $mp_k > 1$，便将 $k$ 从 `set` 中删除即可。

## Code
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 10;
int n, a[N];
int q;
unordered_map<int, int> t;
set<int> st;

signed main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        t[a[i]]++;
    }
    for (int i = 0; i <= n * 2; i++) {
        if (t[i] != 0) continue;
        st.insert(i);
    }
    while (q--) {
        int i, x;
        cin >> i >> x;
        t[a[i]]--;
        if (t[a[i]] == 0) st.insert(a[i]);
        a[i] = x;
        if (t[a[i]] == 0) st.erase(a[i]);
        t[a[i]]++;
        cout << *st.begin() << '\n';
    }
    return 0;
}    
```

---

## 作者：Otue (赞：5)

例题：[mex](https://atcoder.jp/contests/abc330/tasks/abc330_e)

## 法一

用 set 来求。注意到一个序列 mex 不会超过 n，则若有大于 n 的数可赋值为 n+1。

先把 0 至 n+1 所有数加进 set，来看删除和加入两种操作：

* 加入 $x$ 操作：
	在 set 中删除 $x$，前提是 x 这个数出现第一次。
   

* 删除 $x$ 操作：
	在 set 中加入 $x$，前提是 x 这个数是剩下的唯一一个 $x$。
    
* 查询操作：只需要查询 set 里的第一个数。
    
加入操作代码：

```c++
void insert(int x) {
	if (cnt[x] == 0) {
		s.erase(s.find(x));
	}
	cnt[x]++;
}
```

删除操作代码：

```c++
void delet(int x) {
	if (cnt[x] == 1) s.insert(x);
	cnt[x]--;
}
```

此题目完整代码：

```c++
int n, q, a[N], cnt[N];
set<int> s;

void insert(int x) {
	if (cnt[x] == 0) {
		s.erase(s.find(x));
	}
	cnt[x]++;
}

void delet(int x) {
	if (cnt[x] == 1) s.insert(x);
	cnt[x]--;
}

int main() {
	cin >> n >> q;
	s.insert(0);
	for (int i = 1; i <= n; i++) cin >> a[i], s.insert(i);
	s.insert(n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] > n + 1) a[i] = n + 1;
		insert(a[i]);
	}
	while (q--) {
		int x, v;
		cin >> x >> v;
		if (v > n) v = n + 1;
		delet(a[x]);
		insert(v);
		cout << *s.begin() << endl;
		a[x] = v;
	}
}
```

## 法二

开一个权值线段树，加入删除直接在这个数的值域上操作，查询需要查询第一个是 $0$ 的位置。可以二分前缀最小值。

但是，此题值域特别大，需要离散化。那就麻烦很多了：先要离线把所有需要操作的数加入离散数组里，但这还不够。如果需要操作一个数 $x$，则需要加入 $x,x+1$ 两个数。另外，需要加入 $0$。

```c++
#pragma GCC optimize(2)
#pragma GCC optimize(3)


#include <bits/stdc++.h>
using namespace std;

//#define int long long
const int N = 2e6 + 5; 
int n, q, a[N], t[N], l, l2, tmp[N];
int x[N], y[N];
map<int, int> vis, vs;


struct edge {
	int l, r, sum, lazy, minn;
}tree[N * 4];

void push_up(int p) {
	tree[p].minn = min(tree[p << 1].minn, tree[p << 1 | 1].minn);
}

void push_down(int p) {
	if (tree[p].lazy) {
		tree[p << 1].lazy += tree[p].lazy;
		tree[p << 1 | 1].lazy += tree[p].lazy;
		tree[p << 1].minn += tree[p].lazy;
		tree[p << 1 | 1].minn += tree[p].lazy;
		tree[p].lazy = 0;
	}
}

void build(int p, int l, int r) {
	tree[p].l = l, tree[p].r = r;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	push_up(p);
}

void modify(int p, int l, int r, int v) {
	if (l <= tree[p].l && tree[p].r <= r) {
		tree[p].minn += v;
		tree[p].lazy += v;
		return;
	}
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (l <= mid) modify(p << 1, l, r, v);
	if (r > mid) modify(p << 1 | 1, l, r, v);
	push_up(p); 
}

int query_min(int p, int l, int r) {
	if (l <= tree[p].l && tree[p].r <= r) return tree[p].minn;
	push_down(p);
	int mid = (tree[p].l + tree[p].r) >> 1, res = 1e9;
	if (l <= mid) res = min(res, query_min(p << 1, l, r));
	if (r > mid) res = min(res, query_min(p << 1 | 1, l, r));
	return res;
}

int flg, cnt;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) cin >> a[i], t[++l] = a[i], t[++l] = a[i] + 1;
	for (int i = 1; i <= q; i++) {
		cin >> x[i] >> y[i];
		t[++l] = y[i];
		t[++l] = y[i] + 1;
	}
	t[++l] = 0;
	for (int i = 1; i <= l; i++) tmp[i] = t[i];
	sort(t + 1, t + l + 1);
	l2 = l;
	l2 = unique(t + 1, t + l + 1) - t - 1;
	for (int i = 1; i <= l; i++) {
		int k = lower_bound(t + 1, t + l2 + 1, tmp[i]) - t;
		vis[tmp[i]] = k;
		vs[k] = tmp[i];
	}
	build(1, 1, l);
	for (int i = 1; i <= n; i++) modify(1, vis[a[i]], vis[a[i]], 1);
	for (int i = 1; i <= q; i++) {
		modify(1, vis[a[x[i]]], vis[a[x[i]]], -1);
		modify(1, vis[y[i]], vis[y[i]], 1);
		
		a[x[i]] = y[i];
		int L = 1, R = l;
		while (L < R) {
			int mid = (L + R + 1) >> 1;
			if (query_min(1, 1, mid) >= 1) L = mid;
			else R = mid - 1; 
		} 
		if (query_min(1, 1, 1) == 0) cout << 0 << endl;
		else cout << vs[L] + 1 << endl;
	}
}
/*
2 1
0 10
1 0
*/

// 虽然不加入 x+1 可以过掉 34/35 个点，但是会被这组数据卡掉
```

---

## 作者：xxr___ (赞：3)

### 思路：
用一个集合维护没有出现的点，先预处理输入中没有出现的点，然后在询问时特判将要被替换掉的数的出现次数，如果出现次数大于一，那么就 `continue` 因为尽管这个数被替换掉了，仍有这个数的存在；否则就将这个数加入集合中。然后再讲将要换成的数的出现次数加一，最后输出集合的首元素。
#### 细节：
- 因为要输出第一个序列中没有出现的数，也就是说要输出集合中最小的元素，所以每次插入需要排序，复杂度太高，因此可以用 `set` 来模拟这个过程，因为 `set` 是自带排序的。
- 将要替换的数的范围较大，用普通数组会占据大量空间，因此可以用 `map` 实现。
### [赛时代码](https://atcoder.jp/contests/abc330/submissions/47941096)

---

## 作者：ACtheQ (赞：2)

# E - Mex and Update 题解

赛时没做出来，有点可惜。

### 思路

首先我们用一个桶 `mp`，统计 $a_i$ 出现的次数。

这是你可能会问了，$1 \le a_i \le 10^9$，这怎么用桶呀？

别着急，我们知道 $mex$ 操作最大的值为 $n$，因为只能覆盖到 $0 \sim n-1$。

所以我们只用存 $a_i \le n$ 的 $a_i$ 就可以了。

我们用个 `set` 把所有 $mp_i=0$ 的 $i$ 都给存进 `set`。

对于每次操作，取出 $a_i$，放进 $k$。

把 $k$ 从 `set` 里拿出来，如果 $mp_{a_i}=0$ 在 `set` 里放进 $a_i$。

不放代码

---

## 作者：Genius_Star (赞：2)

### 题意：

支持单点修改，全局查询 $\text{MEX}$。

### 思路：

一个小诈骗题，考场上写树状数组套可持久化线段树 $200+$ 行成功 WA 掉。

诈骗点：**最多只会有 $2 \times 10^5$ 个数，所以 $\text{MEX}$ 肯定只会在 $0 \sim 2 \times 10^5$ 之间。**

所以说，我们只需要考虑 $A_i \le 2 \times 10^5$ 的部分。

定义 $f_i$ 为第 $i$ 个数的出现次数，对于每个 $i$，初始将 $f_{a_i}+1$。

先将 $0 \sim 2 \times 10^5$ 中出现次数为 $0$ 的数丢进一个集合 $S$ 中。（集合 $S$ 中的数都是值域范围内没有出现过的数）

每次单点修改 $a_x=y$ 时，先将 $a_x$ 之前的贡献清楚，即将 $f_{a_x}-1$。

判断 $f_{a_x}$ 是否为 $0$，是的话那么就可能是 $\text{MEX}$，丢进 $S$ 中。

然后添加 $y$ 的贡献，即将 $f_y+1$，如果 $y$ 之前在 $S$ 中，那么久需要将 $y$ 在集合中删除。

每次操作后输出集合 $S$ 中最小的数即可。

时间复杂度：$O(N \log W)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,INF=1e12;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,q,x,y;
ll a[N],f[N]; 
set<ll> S;
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]<=N)
		  f[a[i]]++;
	}
	for(int i=0;i<N;i++)
	  if(!f[i])
	    S.insert(i);
	while(q--){
//		write(*S.begin());
//		putchar('\n');
		x=read(),y=read();
		if(a[x]<=N){
			f[a[x]]--;
			if(!f[a[x]])
			  S.insert(a[x]);
		}
		a[x]=y;
		if(a[x]<=N){
			S.erase(a[x]);
			f[a[x]]++;
		}
		write(*S.begin());
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：HDS_Acenaphthylene (赞：2)

## 题目大意
给定一个长度为 $N$ 的序列和 $Q$ 次单点修改，求出每次修改后的 $\text{mex}$ 值。

一个序列的 $\text{mex}$ 值定义为最小的满足 $x\in \mathbb N$ 且 $x$ 未在序列中出现的 $x$ 值。

## 做法
在线询问、序列操作，这样的题最优雅的算法就是数据结构。

考虑两棵权值线段树，$T_1$ 记录每种值是否出现， $T_2$ 记录每种值出现的数量，修改 $T_2$ 时判断是否修改 $T_1$。序列的 $\text{mex}$ 值即最小的满足 $\sum_{i=0}^xT_{1_i} < x$ 的 $x$ 值，二分即可。总时间复杂度 $O(N\log M + Q\log^2 M)$，$M$ 为值域。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int l, r, ans, tag;
	node *lc, *rc;
	node(int le, int ri) {
		l = le, r = ri;
		ans = tag = 0;
		lc = rc = NULL;
	}
	void insert(int x) {
		//cout << "INS" << l << " " << r <<" " << x << endl;
		ans ++;
		if(l == r)
			return;
		int mid = (l + r) >> 1;
		if(x <= mid) {
			if(lc != NULL)
				lc->insert(x);
			else {
				lc = new node(l, mid);
				lc->insert(x);
			}
		}
		else {
			if(rc != NULL)
				rc->insert(x);
			else {
				rc = new node(mid + 1, r);
				rc->insert(x);
			}
		}
	}
	void del(int x) {
		ans --;
		if(l == r)
			return ;
		int mid = (l + r) >> 1;
		if(x <= mid) {
			if(lc != NULL)
				lc->del(x);
			else {
				lc = new node(l, mid);
				lc->del(x);
			}
		}
		else {
			if(rc != NULL)
				rc->del(x);
			else {
				rc = new node(mid + 1, r);
				rc->del(x);
			}
		}
	}
	int query(int le, int ri) {
		//cout << "QUE" << le << " " << ri << endl;
		if(le == l && ri == r)
			return ans;
		int ret = 0;
		int mid = (l + r) >> 1;
		if(lc != NULL && le <= mid)
			ret += lc->query(le, min(mid, ri));
		if(rc != NULL && ri > mid)
			ret += rc->query(max(le, mid + 1), ri);
		return ret;
	}
	int queryp(int x) {
		if(l == r)
			return l;
		int mid = (l + r) >> 1;
		if(lc != NULL && x > query(l, mid))
			x -= query(l, mid);
		else if(lc != NULL)
			return lc->queryp(x);
		else
			return rc->queryp(x);
		return rc->queryp(x);
	}
	int pre(int x) {
		if(x == 1)
			return 1;
		return queryp(query(1, x - 1));
	}
	int nxt(int x) {
		return queryp(query(1, x) + 1);
	}
} *root, *root2;
int a[200005];
signed main() {
	root = new node(0, 1000000005), root2 = new node(0, 1000000005);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1;i <= n;i ++) {
		int x;
		cin >> x;
		a[i] = x;
		root -> insert(x);
		if(root2 -> query(x, x) == 0)root2 -> insert(x);
	}
	for(int i = 1;i <= q;i ++) {
		int x, y;
		cin >> x >> y;
		root -> del(a[x]);
		if(root -> query(a[x], a[x]) == 0)root2 -> del(a[x]);
		a[x] = y;
		if(root -> query(y, y) == 0)root2 -> insert(y);
		root -> insert(y);
		int l = 0, r = 1000000001, ans = r;
		while(l <= r){
			int mid = (l + r) >> 1;
			if(root2 -> query(0, mid) < mid + 1)
				ans = min(ans, mid),
				r = mid - 1;
			else l = mid + 1;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：MornStar (赞：2)

## [ABC330E] Mex and Update

## 题意
有一个长度为 $n$ 的序列和 $q$ 次操作。

每次操作修改序列里的一个数，输出每次操作后序列的 $\operatorname{mex}$。

## 思路

容易发现，$\operatorname{mex}$ 不会大于 $n$。（因为序列里只有 $n$ 个数）

所以想到用桶维护 $\le n$ 的每个数的个数。（代码里为了方便就直接用的 $2 \times 10^5$ 了）

如果有数字 $i$，就将其加入树状数组。没有了就删除。

然后在树状数组上二分，如果区间 $[0,k]$ 的和等于 $k+1$ 则这个区间符合要求，左端点右移。

ps：因为树状数组的 $0$ 号位无法被访问求和，所以可以把所有数加一（即把一当做零），从一开始算 $\operatorname{mex}$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[200010],num[200010],tree[200010];
inline int lb(int x){return x&(-x);}
void change(int x,int val){while(x<=200002){tree[x]+=val,x+=lb(x);}}
long long query(int x,int ret=0){while(x){ret+=tree[x],x-=lb(x);}return ret;}
void in(long long x){
	if(x>200000)	return;
	if(!num[x])	change(x+1,1);
	num[x]++;
}
void era(long long x){
	if(x>200000)	return;
	if(num[x]==1)	change(x+1,-1);
	num[x]--;
}
long long find(){
	if(!num[0])	return -1;//二分搜索不到，所以特判
	int l=0,r=200000;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(query(mid+1)==mid+1)	l=mid;
		else	r=mid-1;
	}
	return l;
};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)	cin>>a[i],in(a[i]);
	for(int i=1,pos,v;i<=m;i++){
		cin>>pos>>v;
		era(a[pos]);in(v);a[pos]=v;
		cout<<find()+1<<"\n";
	}
}
```


---

## 作者：Tang_poetry_syndrome (赞：1)

## [ABC330E] Mex And Update
一道简单题。
### 思路
首先 $N$ 个数的 Mex，容易想出最坏情况下 Mex 值为 $N$，数列即 $0,1,\dots,n-1$。  
由于数据范围 $N\le2\times10^5$，加上 `set` 有去重与排序的效果，考虑用 `unordered_map` 记录每个数字在数列中的出现次数，`set` 维护数列未出现的 $x(0\le x\le2\times10^5)$，每轮答案即为 `set` 的首个元素。同时因为前面说到 Mex 最大值为 $N$，因此数列中再大的数也和 $N+1$ 一样，不对答案造成影响，将其化为 $N+1$ 以防越界。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
const int N=2e5+10,INF=INT_MAX,Mod=998244353;
void gtmax(ll a,ll &b){if(a>b)b=a;}
void gtmin(ll a,ll &b){if(a<b)b=a;}
int n,Q,a[N],now;
unordered_map<int,int>cnt;
set<int>s;
int main()
{
   ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>Q;
	f(i,1,n)
	{
		cin>>a[i];
		if(a[i]<=2e5)cnt[a[i]]++;
	}
	f(i,0,2e5)if(!cnt[i])s.insert(i);
	while(Q--)
	{
		int ik,xk;
		cin>>ik>>xk;
		xk=min(200001,xk);
		cnt[a[ik]]--,cnt[xk]++;
		if(cnt[xk]==1&&s.find(xk)!=s.end())s.erase(xk);
		if(cnt[a[ik]]==0)s.insert(a[ik]);
		a[ik]=xk;
		cout<<*s.begin()<<'\n';
	}
	return 0;
}
```
[提交记录](https://atcoder.jp/contests/abc330/submissions/47934025)

---

## 作者：CheZiHe929 (赞：1)

# AT_abc330_e 题解

### 题目链接

[Atcoder](https://atcoder.jp/contests/abc330/tasks/abc330_e)

[Luogu](https://www.luogu.com.cn/problem/AT_abc330_e)

### 简要题意

给定一个长度为 $n$ 的序列 $a$ 和 $q$ 次操作，每次操作给定一个 $i$ 和一个 $x$，表示把 $a_i$ 的值修改为 $x$（这一改动将带入后续查询），每次操作完后输出未在 $a$ 序列中出现的最小非负整数。

### 简要思路

用一个 `set` 记录未在序列 $a$ 中出现的数，用一个 `map` 记录一个数在序列 $a$ 中出现的次数。

注意到序列 $a$ 中最多有 $n$ 个整数，所以答案区间也只可能是 $0$ 到 $n$，所以我们先把这些数加入到 `set` 中，之后输入的数再从 `set` 中删除。

对于查询操作，每次删除 `set` 中的 $k$ 值，而且如果 $a_i$ 已经不在序列 $a$ 中那么就将其加入到 `set` 中即可。每次输出 `set` 开头的元素即可。

详见代码及注释。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
const int MAXN=2e5+5;

int n,q;
std::set<int> s;//用来存储不在序列 a 中的数
std::map<int,int> m;//用来存储一个数在序列 a 中出现的次数
int a[MAXN];

signed main(){
	std::cin>>n>>q;
	for(int i=0;i<=n;i++)s.insert(i);//先将 0~n 加入到 set 中
	
	for(int i=1;i<=n;i++){
		std::cin>>a[i];
		m[a[i]]++;//计数++
		s.erase(a[i]);//出现在序列 a 中，set 删掉
	}
	
	while(q--){
		int i,k;
		std::cin>>i>>k;
		m[a[i]]--;
		m[k]++;//更改其出现次数
		
		if(!m[a[i]])s.insert(a[i]);//如果序列 a 中没有 a[i] 了就把它加入到 set 中
		s.erase(k);//删除 set 中的 k
		std::cout<<*(s.begin())<<endl;//输出 set 的开头（注意其是指针）
		a[i]=k;//修改数值
	}
	return 0;
}
```

### AC 记录

[Atcoder](https://atcoder.jp/contests/abc330/submissions/47955487)

[Luogu](https://www.luogu.com.cn/record/136932350)

**THE END.**

**THANK YOU.**

---

## 作者：无钩七不改名 (赞：1)

~~调了半个多小时，吃了四发 RE 的罚时，就因为没 ``return``~~。

赛时本来写的 ``set``，但是因为没想到 $\rm{mex}$ 的性质而以为自己思路假了，然后直接离线做，暴打线段树。

离散化所有可能出现的 $a_i$ 和 $a_i-1(a_i-1\ge 0)$ 和 $\max a_i+1$。建立线段树，节点左边界 $l_i$ 右边界 $r_i$ 范围就是离散化后的数的范围，我们设 $sum_i$ 表示在该点代表的区间内的数量不为 $0$ 的数的数量，如果 $sum_i\le r_i-l_i$，就证明 $\rm{mex}$ 在这个区间内。直接线段树修改查询即可。

具体看代码吧。

### 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=200005,M=800005;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int n,q,a[N];
int ans,x[N],y[N];
int lsh[M],cnt,c[M],cnt2;

struct emm{
	int l,r,lx,rx;
	int sum,qwq;
}t[M<<2];

void build(int x,int l,int r){
	t[x].l=l;t[x].r=r;
	t[x].lx=c[l];t[x].rx=c[r];
	if(l==r)return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	return;
}
void add(int x,int y,int z){
	if(t[x].lx>y||t[x].rx<y)return;
	if(t[x].lx==t[x].rx){
		t[x].qwq+=z;
		t[x].sum=(t[x].qwq>0);
		return;
	}
	add(x<<1,y,z);
	add(x<<1|1,y,z);
	t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
	return;
}
int find(int x){
	//cout<<"find:"<<x<<" "<<t[x].lx<<" "<<t[x].rx<<" "<<t[x].sum<<'\n';
	if(t[x].r==t[x].l)return t[x].rx;
	if(t[x<<1].sum<t[x<<1].r-t[x<<1].l+1)return find(x<<1);
	else return find(x<<1|1);
}

int main(){
	n=read();q=read();
	for(int i(1);i<=n;++i)a[i]=read(),lsh[++cnt]=a[i];
	for(int i(1);i<=q;++i){
		x[i]=read(),y[i]=read();
		lsh[++cnt]=y[i];
	}
	lsh[++cnt]=0;
	sort(lsh+1,lsh+1+cnt);
	cnt=unique(lsh+1,lsh+1+cnt)-lsh-1;
	lsh[cnt+1]=lsh[cnt]+1;++cnt;
	for(int i(1);i<=cnt;++i){
		if(lsh[i-1]+1<lsh[i])c[++cnt2]=lsh[i-1]+1;
		c[++cnt2]=lsh[i];
	}
	//for(int i(1);i<=cnt2;++i)cout<<c[i]<<" ";puts("");
	build(1,1,cnt2);
	for(int i(1);i<=n;++i)add(1,a[i],1);
	for(int i(1);i<=q;++i){
		add(1,a[x[i]],-1);
		add(1,y[i],1);
		a[x[i]]=y[i];
		printf("%d\n",find(1));
	}
	return 0;
}
```


---

## 作者：Register_int (赞：1)

首先，由于最多只有 $n$ 个不同的数，所以答案最大也只有 $n$。考虑维护一个没出现过的正整数的集合 $S$，以及有出现过的数的出现次数。每次修改时，如果变动的数值 $>n$ 则不用理会，否则在对应的位置插入/删除这个值即可。查询时直接输出 $S$ 中的最小值，时间复杂度 $O(n\log n)$。

# AC 代码 

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

set<int> s; int cnt[MAXN];

int n, q, a[MAXN];

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i <= n; i++) s.insert(i);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), s.erase(a[i]);
	for (int i = 1; i <= n; i++) if (a[i] <= n) cnt[a[i]]++;
	for (int x, y; q--;) {
		scanf("%d%d", &x, &y);
		if (a[x] <= n && !--cnt[a[x]]) s.insert(a[x]);
		if (y <= n && !cnt[y]++) s.erase(y); a[x] = y;
		printf("%d\n", *s.begin());
	}
}
```

---

## 作者：1234567890sjx (赞：1)

简单题。

考虑用一个权值线段树来维护所有 $\le n$ 的数是否出现过，再开一个桶记录每一个 $\le n$ 的数的出现次数。

查询的时候按照套路二分 `mex` 的值 $p$，如果从 $0\sim p$ 中的所有值都出现过了恰好一次，那么 `mex` 一定不会比 $p$ 小，否则一定不会比 $p$ 大。

时间复杂度 $O(n\log^2n)$。

---

## 作者：Imken (赞：1)

仔细分析一下 $\operatorname{MEX}$，大概是不难发现下列性质的：

- 任意 $n$ 个数字的 $\operatorname{MEX}$ 不大于 $n$。

因此，我们可以维护一个 `set`，里面只用维护 $0\sim n$ 里面**没有出现**的数字，大于 $n$ 的直接忽略即可；每次查询的时候输出这个 `set` 里面最小元素的值就行了。

具体请参见代码：

```cpp
using ll = long long;

set<ll> st;

ll nc[200015];
ll cnt[200015];
int n, q;

int x;
ll val;

// 这里用一个较大的值作为上界是因为赛时没有想清楚边界
// 其实深入想一下发现其实并不影响
const int MAXN = 2e5 + 10;

int main()
{
	cin >> n >> q;
	for (int i = 0; i <= MAXN; i++)
		st.insert(i);

	for (int i = 1; i <= n; i++) {
		cin >> nc[i];
		if (nc[i] <= MAXN) {
			st.erase(nc[i]);
			cnt[nc[i]]++;
		}
	}
	while (q--) {
		cin >> x >> val;
		if (nc[x] <= MAXN) {
			cnt[nc[x]]--;
			if (cnt[nc[x]] == 0)
				st.insert(nc[x]);
		}
		nc[x] = val;
		if (val <= MAXN) {
			if (cnt[val] == 0)
				st.erase(val);
			cnt[val]++;
		}
		cout << *st.begin() << '\n';
	}
}
```


---

## 作者：Pink_Cut_Tree (赞：1)

# AT_abc330_e [ABC330E] Mex and Update 题解

赛时没想出来，赛后补的。

### `mex` 的通用求法。
 
维护一个 `set` 代表没出现过的数，由于 `set` 内部数据单调，每次询问时输出 `*st.begin()` 即可。

再用一个 `ds[]` 数组代表每个数字出现的次数。

要插入时，`ds[m]++,st.erase(m)`，代表将 $m$ 的出现次数加 $1$ 并从“未出现过的数”的集合里删去 $m$。

要删除时，`ds[m]--,if(ds[m]==0) st.insert(m)`，代表将 $m$ 的出现次数减 $1$，如果减为 $0$ 则，则在“未出现过的数”的集合里插入 $m$。

### 解析

上面的代码还有一个问题，值域太大，`set` 有可能装不下，那我们怎么办呢？

观察数据范围，$n,q\leq 2\times 10^5$，所以整个数列的 `mex` 不可能超过 $2\times 10^5+1$，所以我们只需维护大小为 $2\times 10^5+1$ 的 `ds` 数组即可。

如果遇到大于 $2\times 10^5+1$ 的数，则强制将它变成 $2\times 10^5+1$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
set<int>st; //没出现过的 
int n,q;
int a[N],ds[N],x,m;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=min(a[i],200001);
		ds[a[i]]++;
	}
	for(int i=0;i<=2e5+1;i++){
		st.insert(i);
	}
	for(int i=1;i<=n;i++){
		st.erase(a[i]);
	}
	while(q--){
		cin>>x>>m;
		ds[a[x]]--;
		if(ds[a[x]]==0){
			st.insert(a[x]);
		}
		m=min(m,200001);
		a[x]=m;
		if(ds[m]==0){
			st.erase(m);
		}
		ds[m]++;
		cout<<*st.begin()<<"\n";
	}
return 0;
}
```


---

## 作者：紊莫 (赞：1)

## 题意简述

动态维护全局 mex。

## 做法

首先注意到 mex 的一个性质，也就是一个长度为 $n$ 的区间的 mex 最大为 $n+1$，证明比较简单，此处略。  

因此，我们可以把所有大于 $n$ 的数都改为 $n+1$，这不会影响答案。

转化完成后考虑如何维护，这里使用 ``set`` 来维护**未出现的数字**，同时加入计数数组，每个数第一次出现和最后一次删除时改变 ``set`` 内的情况。


## 代码

[赛时代码](https://atcoder.jp/contests/abc330/submissions/47918597)。

注意点是 mex 是可能为 $0$ 的，所以 $0$ 也应该在 ``set`` 里，因为这个吃了一个罚时。

---

## 作者：DengDuck (赞：0)

这题感觉有点太板了，维护 MEX 的方法比较经典，考虑用一个 `set` 维护所有的未出现的数字，由于数字的数量不会超过 $2\times 10^5$ 种，所以 `set` 维护的数字也只需要维护 $[1,2\times 10^5]$，这样可以保证 `set` 始终不为空。

然后再用一个 `map` 维护数组中所有数字出现的次数，修改比较好做，然后如果一种没有的元素出现就在 `set` 种删除，有一种元素在数组中删没了就在 `set` 中加回去。

然后每次调用 `set` 最小值即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2e5+5;
LL n,q,a[N];
map<LL,LL>ma;
set<LL>s;
int main()
{
	cin>>n>>q;
	for(int i=1;i<=N-5;i++)s.insert(i);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ma[a[i]]++;
		if(s.count(a[i]))s.erase(a[i]);
	}
	while(q--)
	{
		LL x,y;
		cin>>x>>y;
		ma[a[x]]--;
		if(ma[a[x]]==0)s.insert(a[x]);
		a[x]=y;
		ma[a[x]]++;
		if(s.count(a[x]))s.erase(a[x]);	
		cout<<(*s.begin())<<endl;
	}
}
```

---

## 作者：Milthm (赞：0)

~~事情是这样的，我昨天打开 AT，发现有比赛，但是时间不多了。我前面题都没看，直接开这道题，写了个值域线段树，然后没调出来。~~

大家都看到了，线段树和平衡树等数据结构是比较容易写挂的，所以我们很容易就联想到去用 STL。观察这题，发现可以用 `set` 实现。

先想一下我们怎么去暴力的搞：直接开桶记录每一个数出现的次数，从 $0$ 开始扫，次数为 $0$ 的就是要求的答案。

还有一个优化，就是答案肯定不会超过 $n$，所以超过 $n$ 的数都标记成 $n+1$ 就可以。

这样是 $O(nq)$，过不去。考虑怎么用 `set` 进行优化。正难则反，把没出现过的数放到 `set` 里面。插入时如果当前数的计数器为 $0$，那么说明数是新加进来的，我们把这个数 `erase` 掉。同样，删除时如果当前数的计数器为 $1$，那说明马上这个数就没了，把它 `insert` 进去。

然后这题的操作可以拆成一个插入和一个删除，因为 `set` 自带排序，每次求的答案就是 `set` 的第一个数。然后这题就做完了。

### AC code

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,x,cnt[N*2],id,a[N*2];
set<int>s;
int main(){
	cin>>n>>m;
	for(int i=0;i<=N;++i)s.insert(i);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]>n)a[i]=n+1;
		if(cnt[a[i]]==0)s.erase(a[i]);
		++cnt[a[i]];
	}
	while(m--){
		cin>>id>>x;
		if(cnt[a[id]]==1)s.insert(a[id]);
		--cnt[a[id]];
		if(x>n)x=n+1;
		a[id]=x;
		if(cnt[x]==0)s.erase(x);
		++cnt[x];
		cout<<*s.begin()<<'\n';
	}
	
	return 0;
}

```


---

## 作者：guanyf (赞：0)

### 题意
- 给定一个长度为 $n$ 的序列 $a$，有 $q$ 次查询，每次查询给定两个数 $x,y$，表示把 $a_x$ 改成 $y$。对于每个查询，你都要输出这个序列的 $\operatorname{mex}$（序列中未出现的最小的非负整数）。

- $1 \le n,q \le 2 \cdot 10 ^ 5,0 \le a_i \le 10 ^ 9$

### 思路
先说一个结论：一个长度为 $n$ 的序列 $\operatorname{mex}$ 不可能超过 $n$。考虑最劣的情况：所有数分别是 $0,1,2,3,\dots,n-1$，那么 $\operatorname{mex}$ 也只会是 $n$。

然后我们就可以发扬 STL 智慧，用一个 `unordered_map` 维护每个数出现的次数，再用一个 `set` 维护所有 $n$ 以内的没有在 $a$ 中出现的值（$0$ 也算）。每次操作就相当于是把 $a_x$ 的出现次数减一，$y$ 的出现次数加一。只有当 $a_x \le n$ 且 $a_x$ 的出现次数为 $0$ 时，才需要 `set.insert(a[x])`。同理，只有当 $y \le n$ 且 $y$ 的出现次数为 $1$ 时，才需要 `set.erase(set.find(y))`。

然后直接输出最小值就行了。

时间复杂度：$\operatorname{O}(q \log n)$

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5, INF = 1e18;
int n, q, a[MAXN];
unordered_map<int, int> vis;
set<int> st;
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i]]++;
  for (int i = 0; i <= n; i++) {
    if (!vis[i]) st.insert(i);
  }
  for (int x, y; q--;) {
    cin >> x >> y;
    vis[a[x]]--;
    if (!vis[a[x]] && a[x] <= n) st.insert(a[x]);
    if (!vis[y] && y <= n) st.erase(st.find(y));
    vis[y]++, a[x] = y;
    cout << *(st.begin()) << '\n';
  }
  return 0;
}
```


---

## 作者：Crazyouth (赞：0)

**分析**

我们可以把当前存在的数全部开桶统计存在的个数，再开一个 set，set 内的元素都是 $a$ 数组中不存在的自然数。初始时，把 $0\sim 2\times10^5$ 中不在 $a$ 内的数都丢进 set，因为 $a$ 数组不可能全部涵盖这些数。然后每次更新的时候更新 $a$，桶，set 三个容器，查询时输出 set 内最前面的数即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
set<int> st;
int a[int(2e5+10)];
int main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]++;
	for(int i=0;i<=2e5+10;i++) if(!mp[i]) st.insert(i);
	while(q--)
	{
		int ind,k;
		cin>>ind>>k;
		mp[a[ind]]--;
		if(!mp[a[ind]]) st.insert(a[ind]);
		a[ind]=k;
		st.erase(k);
		mp[k]++;
		cout<<(*st.begin())<<endl;
	}
	return 0;
}

---

## 作者：zengziqvan (赞：0)

# 题意翻译

给定一个长度为 $N$ 的序列 $a$ 与 $Q$ 次询问，对于第 $k$ 次操作：

- 给定 $i_k$ 与 $x_k$，表示将 $a_{i_k}$ 修改为 $x_k$。

- 输出当前序列进行 $mex$ 运算的结果，运算即当前序列中未出现的最小自然数。

$1\le N,Q \le 2\times 10^5$。

# 题目分析
设集合 $mexs$ 表示在 $1\sim N+Q$ 中在序列中没有出现过的数，则 mex 操作等价于取出 $mexs$ 中最小的数字。

考虑将原始序列的初始未出现的、小于等于 $N+Q$ 的所有未在原数列的数字全部插入 $mexs$ 中。

因为要修改 $Q$ 次，而原序列概率从 $0\sim N-1$ 的所有数全部包含，所以是 $N+Q$。

再将原数列中每个出现过的数的个数全部记录至 cnt 中（map或离散化）。

每次修改等价于添加一个数以及删除一个数。

对于添加操作，可能添加在 $mexs$ 中出现过的数字，故此数字在 $mexs$ 中要删除。

对于删除操作，要删除的数字可能被删除后不在原序列中出现，故要通过 cnt 判断并决定是否插入 $mexs$ 中。

注意：这两种操作都要改变记录的 cnt。

总体时间复杂度 $O(N\log N+Q\log N)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
int n,mex=1e9,q,maxx,a[200010];
set<int>s,mexs;
set<int>::iterator it;
map<int,int>mp;
map<int,int>::iterator it2;
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a[i],s.insert(a[i]),mp[a[i]]++,maxx=max(maxx,a[i]);
	for(int i=0;i<=n+q;++i) {
		if(!mp.count(i)) 
			mexs.insert(i);
	}
	for(int i=1;i<=q;++i) {
		int x,y;
		cin>>x>>y;
		maxx=max(maxx,y);
		mp[y]++;
		it=mexs.find(y);
		if(it!=mexs.end()) 
			mexs.erase(it);
		mp[a[x]]--;
		if(!mp[a[x]]) {
			mp.erase(a[x]);
			s.erase(a[x]);
			mexs.insert(a[x]);
		}
		a[x]=y;
		cout<<*mexs.begin()<<"\n";
	}
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# 思路

易发现 $\operatorname{mex}(A_1,A_2,\dots,A_N) \le N$，于是我们可以只关注 $0 \sim N$ 的情况。可以用一个 multiset 维护当前 $A$ 序列中 $0 \sim N$ 的元素，以及一个 set 维护 $A$ 序列中 $0 \sim N$ 中没有出现的元素，还有一个数组记录 $0 \sim N$ 中每个数在 $A$ 序列中出现的次数。

每次询问时，输出 set 中最小的第一位即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
multiset<ll> yes;
set<ll> no;
ll a[200023], b[200023];

int main() {
    ll n, q;
    scanf("%lld %lld", &n, &q);
    for (ll i = 1; i <= n; i++) {
    	ll x;
    	scanf("%lld", &x);
    	a[i] = x;
    	if (x <= n) {
    		yes.insert(x);
    		b[x]++;
		}
	}
    for (ll i = 0; i <= n; i++) {
    	if (b[i] == 0) {
    		no.insert(i);
		}
	}
	while (q--) {
		ll p, x;
		scanf("%lld %lld", &p, &x);
		if (a[p] <= n) {
			b[a[p]]--;
			yes.erase(yes.find(a[p]));
			if (b[a[p]] == 0) {
				no.insert(a[p]);
			}
		}
		a[p] = x;
		if (x <= n) {
			yes.insert(x);
			b[x]++;
			if (no.find(x) != no.end()) {
				no.erase(x);
			}
		}
		printf("%lld\n", *no.begin());
	}
	return 0;
}

```

---

## 作者：MMXIandCCXXII (赞：0)

## 题目大意
给定长度为 $N$ 的序列，进行 $Q$ 次操作，每次给出一个 $i$ 和一个 $x$，表示将序列的第 $i$ 个数改为 $x$，每次操作后都要输出当前序列中没有的最小非负整数。
## 思路
首先想到用 `map` 存下每个数有几个，然后遍历找答案。但是这样明显是 $O(N^2\log N)$，死得很惨。再想，每次都要找最小，那我们把没有的数存到一个容器里，每次输出最小的不就行了？`set` 无疑是最好的选择，它可以自动排序，求出最小。同时，再用一个 `map`，维护每个数的个数，如果改动后这个数没有了，加入集合；如果这个数从没有变成了有，从集合中删除，实时调整即可。但是，序列中的数最大有 $10^9$，要是把 $10^9$ 以内没有的数都算进去，空间和时间都不允许，但仔细想想，最多才 $2\times 10^5$ 个数，最极端就是从 $0 \sim 199999$，这时的答案也才 $2\times 10^5$，所以我们，只用维护前 $2\times 10^5$ 个数的有无即可。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[200010];

set <int> st;
map <int, int> mp;

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
    	cin >> a[i];
    	mp[a[i]]++;
	}
	for (int i = 0; i <= 200000; i++)
	{
		if (mp[i] == 0) st.insert (i);
	}
	while (m--)
	{
		int i, x;
		cin >> i >> x;
		mp[a[i]]--;
		mp[x]++;
		if (mp[a[i]] == 0) st.insert (a[i]);
		if (mp[x] == 1 && x <= 200000) st.erase (x);
		a[i] = x;
		cout << *st.begin() << endl;
	}
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

容易想到如果修改一个数那么就是删除一个数后添加一个数。

删除一个数后的 mex 是很好更新的，而添加一个数后，如果这个数是原先的 mex，那么就找到这个数后第一个未出现的数，注意到 mex 一定在 $[0,n+1]$ 之间，所以可以使用线段树维护区间是否存在出现次数是 $0$ 的数，然后可以二分找。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,q,a[200005],x,y,cnt[200005],mex;
struct tree{
	int l,r,sum,flag;
}tr[800005];
void pushup(int u){
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
	tr[u].flag=tr[u<<1].flag|tr[u<<1|1].flag;
}
void build(int u,int l,int r){
	if(l==r){
		tr[u]={l,r,cnt[l]};
		if(cnt[l]==0)tr[u].flag=1;
		return;
	}
	tr[u]={l,r};
	int mid=l+r>>1;
	build(u<<1,l,mid),build(u<<1|1,mid+1,r);
	pushup(u);
}
void change(int u,int pos,int k){
	if(tr[u].l==tr[u].r){
		if(tr[u].sum==0)tr[u].flag=0;
		tr[u].sum+=k;
		if(tr[u].sum==0)tr[u].flag=1;
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(pos<=mid)change(u<<1,pos,k);
	else change(u<<1|1,pos,k);
	pushup(u);
}
int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)return tr[u].flag;
	int mid=tr[u].l+tr[u].r>>1,res=0;
	if(l<=mid)res|=query(u<<1,l,r);
	if(r>mid)res|=query(u<<1|1,l,r);
	return res;
}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<=n+1)cnt[a[i]]++;
	}
	for(int i=0;i<=n+1;i++)if(!cnt[i]){
		mex=i;
		break;
	}
	build(1,0,n+1);
	while(q--){
		cin>>x>>y;
		if(a[x]<=n+1){
			cnt[a[x]]--;
			if(cnt[a[x]]==0)mex=min(mex,a[x]);
			change(1,a[x],-1);
		}
		if(y<=n+1){
			cnt[y]++;
			change(1,y,1);
			if(y==mex){
				int l=y+1,r=n+1,ans=y; 
				while(l<=r){
					int mid=l+r>>1;
					if(!query(1,l,mid))ans=mid,l=mid+1;
					else r=mid-1;
				}
				mex=ans+1;
			}
		}
		a[x]=y;
		cout<<mex<<'\n';
	}
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 问题大意

给定一个长度为 $N$ 的序列 $A=(A_1,A_2,\dots,A_N)$。  
按照给定的顺序回答以下 $Q$ 个查询。

第 $k$ 个查询的格式如下：

-   首先，将 $A_{i_k}$ 更改为 $x_k$。这个更改会影响后续的查询。
-   然后，打印序列 $A$ 的 $\rm{mex}$。
    -   序列 $A$ 的 $\rm{mex}$ 是序列 $A$ 中不包含的最小的非负整数。
    
### 思路

~~这题看着难但实际上是个诈骗题。~~

这题它的 $\rm{mex}$ 最大不会超过 $2\times 10^5$ 所以我们就直接开个桶统计每个小于等于 $2\times 10^5$ 的数的个数。然后如果某个数没有出现那我们就把他扔到集合中。


### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pb(a) push_back(a)
using namespace std;
ll cnt[200005];
ll a[200005];
set<ll> st;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (a[i] <= 200000) {
			cnt[a[i]]++;
		}
	}
	for (int i = 0; i <= 200000; i++) {
		if (!cnt[i]) {
			st.insert(i);
		}
	}
	while (q--) {
		ll x, y;
		cin >> x >> y;
		if (a[x] <= 200000) {
			cnt[a[x]]--;
			if (!cnt[a[x]]) {
				st.insert(a[x]);
			}
		}
		a[x] = y;
		if (y <= 200000) {
			if (!cnt[y]) {
				st.erase(y);
			}
			cnt[y]++;
		}
		cout << *st.begin() << endl;
	}
	return 0;
}
~~~

---

