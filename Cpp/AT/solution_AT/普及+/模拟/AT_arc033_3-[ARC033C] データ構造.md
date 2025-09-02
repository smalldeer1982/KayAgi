# [ARC033C] データ構造

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc033/tasks/arc033_3

数の集合 $ S $ に対する以下のクエリを処理してください。

- タイプ $ 1 $ ： $ S $ に数 $ X $ を追加する。
- タイプ $ 2 $ ： $ S $ に含まれる数のうち $ X $ 番目に小さい数を答え、その数を $ S $ から削除する。

## 样例 #1

### 输入

```
5
1 11
1 29
1 89
2 2
2 2```

### 输出

```
29
89```

## 样例 #2

### 输入

```
12
1 8932
1 183450
1 34323
1 81486
1 127874
1 114850
1 55277
1 112706
2 3
1 39456
1 52403
2 4```

### 输出

```
55277
52403```

# 题解

## 作者：喵仔牛奶 (赞：3)

## Preface

平衡树模板题怎么可以没有可爱的替罪羊树题解呢![](//图.tk/q)

## Solution

前置芝士：[二叉搜索树](https://www.luogu.com.cn/problem/solution/P5076)。

操作 1、2 可以直接套用二叉搜索树的插入和删除，但是这样最坏复杂度可以卡到 $\mathcal{O}(n^2)$，和暴力没有区别。

二叉搜索树：[测评记录](https://www.luogu.com.cn/record/100290335)。

为什么呢？试一下这组数据：

```
200000
200000 199999 199998 199997 .... 5 4 3 2 1
```

这样的数据 BST 会一至插入到最左，就退化成了链，我们需要一种操作来保持 BST 的平衡。

### 平衡因子

我们可以通过重构一部分子树来保持 BST 的平衡。

我们引入平衡因子 $\alpha=\dfrac{\max\{siz_{L_u},siz_{R_u}\}}{siz_u}$，其中 $u$ 是一个节点，$siz_u$ 表示 $u$ 子树内的树个数，$L_u,R_u$ 表示 $u$ 的左右儿子。平衡因子越大，表示该子树越不平衡。

当平衡因子 $\alpha$ 大于一个定值（通常取 $0.6\sim0.9$）时，我们需要重构该子树以保持平衡。

## 重构

由 BST 的性质，我们知道一棵 BST 的任意子树的中序遍历都是不减数列，所以我们先把这个数列记录下来：

```
int tot, cur[N];
void dfs(int u) {
	if (!u) return;
	dfs(tree[u].ls);
	if (tree[u].cnt) cur[tot ++] = u;
	dfs(tree[u].rs);
}
```

重构的时候，为了尽可能平衡，一个节点的两个儿子平分这个节点所掌管的区间。这样 $|siz_{L_u}-siz_{R_u}|\leq1$，非常平衡。

```cpp
int build(int l, int r) {
	int mid = (l + r) >> 1;
	if (l >= r) return 0;
	tree[cur[mid]].ls = build(l, mid);
	tree[cur[mid]].rs = build(mid + 1, r);
	push_up(cur[mid]);
	return cur[mid];
}
```

最后套一下。

```cpp
inline void rebuild(int& u) {
	tot = 0, dfs(u);
	if (u == rt) rt = u = build(0, tot);
	else u = build(0, tot);
}
```

### 删除

替罪羊树采用惰性删除，即 `tree[u].cnt --`。

```cpp
void del(int u, int val) {
	if (!u) return;
	if (tree[u].val == val) tree[u].cnt --;
	if (val < tree[u].val) del(tree[u].ls, val);
	if (val > tree[u].val) del(tree[u].rs, val);
	push_up(u);
}
```


但是这样会带来一个问题：大量的空节点会耗费许多时间，还会影响重构。我们需要把重构再加上一个条件：

当 $\dfrac{tot_{u}}{siz_{u}}$ 小于一个定值（通常取 $0.6\sim0.9$）时，也进行重构。其中 $tot$ 是 $u$ 子树里非空节点个数。

我们可以写出一个是否需要重构的函数：

```cpp
bool isBad(int u) {
		return tree[u].cnt && 
        	(alpha * tree[u].tot <= double(max(tree[tree[u].ls].tot, tree[tree[u].rs].tot))
			|| double(tree[u].tsiz) < alpha * tree[u].tot);
	}
```

## Code

替罪羊树，[120ms](https://www.luogu.com.cn/record/100290086)。

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
struct ScapegoatTree {
	const double alpha = 0.6666; // 这里 alpha 是取的那个定值qwq
	struct node {
		int val, ls, rs, cnt, tot, siz, tsiz;
	} tree[N];
	int cnt, tot, rt, cur[N];
	bool isBad(int u) {
		return tree[u].cnt && (alpha * tree[u].tot <= double(max(tree[tree[u].ls].tot, tree[tree[u].rs].tot))
			|| double(tree[u].tsiz) < alpha * tree[u].tot);
	}
	void push_up(int u) {
		tree[u].tot = tree[tree[u].ls].tot + tree[tree[u].rs].tot + 1;
		tree[u].siz = tree[tree[u].ls].siz + tree[tree[u].rs].siz + tree[u].cnt;
		tree[u].tsiz = tree[tree[u].ls].tsiz + tree[tree[u].rs].tsiz + bool(tree[u].cnt);
	}
	void dfs(int u) {
		if (!u) return;
		dfs(tree[u].ls);
		if (tree[u].cnt) cur[tot ++] = u;
		dfs(tree[u].rs);
	}
	int build(int l, int r) {
		int mid = (l + r) >> 1;
		if (l >= r) return 0;
		tree[cur[mid]].ls = build(l, mid);
		tree[cur[mid]].rs = build(mid + 1, r);
		push_up(cur[mid]);
		return cur[mid];
	}
	inline void rebuild(int& u) {
		tot = 0, dfs(u);
		if (u == rt) rt = u = build(0, tot);
		else u = build(0, tot);
	}
	int insert(int u, int val) {
		if (!u) {
			u = ++ cnt;
			if (!rt) rt = u;
			tree[u].val = val;
			tree[u].siz = tree[u].cnt = 1;
		} else {
			if (tree[u].val == val) tree[u].cnt ++;
			if (val < tree[u].val) tree[u].ls = insert(tree[u].ls, val);
			if (val > tree[u].val) tree[u].rs = insert(tree[u].rs, val);
			push_up(u);
			if (isBad(u)) rebuild(u);
		}
		return u;
	}
	void del(int u, int val) {
		if (!u) return;
		if (tree[u].val == val) tree[u].cnt --;
		if (val < tree[u].val) del(tree[u].ls, val);
		if (val > tree[u].val) del(tree[u].rs, val);
		push_up(u);
	}
	int Kth(int u, int k) {
		if (!u) return INT_MAX;
		if (tree[tree[u].ls].siz >= k) return Kth(tree[u].ls, k);
		if (tree[tree[u].ls].siz + tree[u].cnt >= k) return tree[u].val;
		return Kth(tree[u].rs, k - tree[tree[u].ls].siz - tree[u].cnt);
	}
} T;
int q, opt, u;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
	cin >> q;
	for (int i = 1; i <= q; i ++) {
		cin >> opt >> u;
		if (opt == 1) T.insert(T.rt, u);
		if (opt == 2) {
		    int res = T.Kth(T.rt, u);
		    cout << res << '\n', T.del(T.rt, res);
		}
	}
	return 0;
}

```


---

## 作者：tanghg (赞：1)

发现大小只有 $2\times 10^5$，且值域也只有这么大。所以考虑用树状数组维护一个桶表示 $x$ 的值是否出现。每一次查询就二分，对于一个中点 $x$ 查看桶的前缀和与 $x$ 进行大小比较，也就是现在小于等于 $m$ 的有几个。时间复杂度 $O(n\log^2 n)$，虽然慢一些但是非常好写且仍能通过。
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register ll i=(a);i<=(b);++i)
using namespace std;
typedef int ll;
const ll MAXN=2e5+5;
ll n;
ll t[MAXN];
#define lb(x) (x&(-x))
void add(ll x,ll v){
    while(x<=200000){
        t[x]+=v;
        x+=lb(x);
    }
}
ll qry(ll x){
    ll ans=0;
    while(x){
        ans+=t[x];
        x-=lb(x);
    }
    return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	rep(_,1,n){
	    ll op,x;
	    cin>>op>>x;
	    if(op==1){
	        add(x,1);
	    }else{
	        ll l=1,r=200000,ans=0;
	        while(l<=r){
	            ll mid=(l+r)>>1,val=qry(mid);
	            if(val<x){
	                l=mid+1;
	            }else{
	                ans=mid;
	                r=mid-1;
	            }
	        }
	        add(ans,-1);
	        cout<<ans<<endl;
	    }
	}
	return 0;
}
```

---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc033_3)

一道数据结构题。

我们需要写一个数据结构支持插入、删除与查询第 $k$ 小。我们发现一种叫**平衡树**的数据结构可以支持这些操作。

但是手写平衡树太麻烦了，有没有什么简单快捷的办法呢？

有的兄弟，有的。我们可以使用 pbds 库。

我们先加入加入头文件 `#include <bits/extc++.h>`。再 `using namespace __gnu_pbds;`。

pbds 库中的平衡树也就是 `tree` 支持查询排名以及其他杂七杂八的操作，具体有兴趣的可以自行搜索。在这道题中我们只需要用到以下三种操作：

- `insert(x)`：将元素 $x$ 加入平衡树中。
- `erase(x)`：将元素 $x$ 从平衡树中删除。
- `find_by_order(k)`：返回平衡树中排名为 $k$ 的元素迭代器。

### Code
```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ {
    #define SP(n, x) std :: setprecision(n) << std :: fixed << x
    #define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
    #define fst first
    #define snd second
    template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
using namespace __gnu_pbds;
int q;
tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> tr;
int main() {
    // freopen("InName.in", "r", stdin);
    // freopen("OutName.out", "w", stdout);
    ios :: sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            tr.insert(x);
        }
        else {
            int x;
            cin >> x;
            cout << *tr.find_by_order(x - 1) << '\n';
            tr.erase(*tr.find_by_order(x - 1));
        }
    }
    return 0;
}
```

---

## 作者：Stonkin (赞：1)

### 题意：

翻译里面有。

### Solve:

平衡树的解法都被其他人写烂了，写一篇权值线段树的题解。

顾名思义，权值线段树维护的就是数字的值本身，由于题目保证 $x\leqslant 2\times 10^5$，因此直接开一个大小为 $2\times 10^5$ 的权值线段树即可

 首先先要确定权值线段树维护什么：我们令权值线段树每个点维护该点对应区间内有几个数

 这部分的代码如下：

 
```cpp
struct Node {
    int l, r;//区间
    int val;//数字出现次数
  };
```

 接下来实现操作：

 对于操作一：添加一个数，直接找到这个数开始的只包含它本身的区间，把出现次数加一，如下：

 
```cpp
void add(int u, int val, int num) {
    if (tr[u].l == tr[u].r) {//假如找到了这个长度为1的区间
      tr[u].val += num;//计数器+tag
      return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (val <= mid)//找这个值应该在哪个区间
      add(u << 1, val, num);
    else
      add(u << 1 | 1, val, num);
    push_up(u);
  }
```

对于操作二：先找到这个数，然后把它删掉。

删掉一个数可以直接用上面的代码，让计数器加 $-1$ 即可。

找数字的代码：

```cpp
int query_num(int u, int k) {//k是在这个区间内的排名
    if (tr[u].l == tr[u].r) return tr[u].l;//区间就是值域，找到长为1的区间就找到了这个值
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (k <= tr[u << 1].val) return query_num(u << 1, k);//确定这个值应该在哪个区间
    return query_num(u << 1 | 1, k - tr[u << 1].val);//如果在右区间，就把左区间内的数字数量减去，剩余数字就是在这个区间内的排名
  }
```

 
 _备注：个人习惯于把线段树封装到结构体里面，不喜勿喷。_ 

 最后是你们喜闻乐见的完整代码：

 
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct Segment {
  struct Node {
    int l, r;
    int val;
  };
  int n;
  vector<Node> tr;
  Segment(int _n) : n(_n), tr(vector<Node>(n << 2)) {}

  void push_up(int u) { tr[u].val = tr[u << 1].val + tr[u << 1 | 1].val; }

  void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) {
      tr[u].val = 0;
      return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
  }//如果你不把区间端点写进结构体就不需要这个函数

  void add(int u, int val, int num) {
    if (tr[u].l == tr[u].r) {
      tr[u].val += num;
      return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (val <= mid)
      add(u << 1, val, num);
    else
      add(u << 1 | 1, val, num);
    push_up(u);
  }

  int query_num(int u, int k) {
    if (tr[u].l == tr[u].r) return tr[u].l;
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (k <= tr[u << 1].val) return query_num(u << 1, k);
    return query_num(u << 1 | 1, k - tr[u << 1].val);
  }
};

int n;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> n;
  Segment tr(N);//封装进结构体之后要额外召唤一遍线段树
  tr.build(1, 1, N - 5);
  for (int i = 1, type, val; i <= n; i++) {
    cin >> type >> val;
    if (type == 1)
      tr.add(1, val, 1);
    else {
      int res = tr.query_num(1, val);
      printf("%d\n", res);
      tr.add(1, res, -1);
    }
  }
  return 0;
}
```

---

## 作者：COsm0s (赞：1)

## 思路

维护一个**有序**序列。

+ 使用 `vector`，有自带插入和删除函数。

+ 在插入时，使用二分降低复杂度。

+ 在删除时，直接调用 `erase` 函数，$O(n)$ 处理，因为数据量不大，所以可以过。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> v;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while(T --) {
		int p, x;
		cin >> p >> x;
		if(p == 1) v.insert(lower_bound(v.begin(), v.end(), x), x);//lower_bound：二分查找大于等于x的第一个位置。
		else {
			cout << v[x - 1] << '\n';
			v.erase(v.begin() + x - 1);//删除函数
		}
	}
	return 0;
}
```


---

## 作者：_cbw (赞：0)

基础权值线段树练习题。

迭代好想捏，迭代好写捏，迭代不容易错捏，迭代快捏，迭代拿最优解捏。

## 做法

注意到题面中有一个重要的条件：$1 \le X_i \le 2 \times 10^5 (1 \le i \le q)$。这启发我们用权值线段树加线段树上二分解决这题。

维护一颗线段树，节点上存储的不再是集合的区间信息（因为这题重要的是值而不是位置），而是值在该区间的数的个数。形式化的，线段树上的区间 $[l, r]$ 表示 $|\{S \cap [l, r]\}|$。

下面设操作的值为 $x$，值域为 $V$。

### 操作 1

线段树单点加 $1$。注意是 `update(x)` 而不是 `update(i)`，因为这颗线段树维护的是值。

### 操作 2

考虑在线段树上二分。从代表 $[1, V]$ 的 $1$ 号点开始，走到一个代表 $[l, r]$ 的节点时：

- 首先将该节点存储的值减 $1$，因为答案在此区间，所以个数会减少。
- 若 $l = r$，则 $l$ 即为所求，返回即可。
- 否则，若左儿子的值 $\ge x$，进入左儿子。因为左儿子代表的值域小于右儿子，且其中有解。
- 否则，令 $x \gets x - \mathrm{lsiz}$，进入右儿子。其中 $\mathrm{lsiz}$ 表示左儿子的值。

## 代码

因为 $1$、$2$ 操作都保证合法，可以提前知道节点的变化值，所以可以使用迭代方法。如果你理解了上面的话应该不难明白这一点。

加不加快读（目前）都比其它提交快得多。

```cpp
#include <iostream>
#define MAXN 200000
using namespace std;

int tr[MAXN << 2 | 7];

inline void update(const int pos)
{
    int id = 1, l = 1, r = MAXN, mid;
    while (true)
    {
        ++tr[id];
        if (l == r)
            return;
        mid = (l + r) >> 1, id <<= 1;
        if (pos <= mid)
            r = mid;
        else
            id |= 1, l = mid + 1;
    }
}
inline int query(int k)
{
    int id = 1, l = 1, r = MAXN, mid;
    while (true)
    {
        --tr[id];
        if (l == r)
            return l;
        mid = (l + r) >> 1, id <<= 1;
        if (tr[id] >= k)
            r = mid;
        else
            k -= tr[id], l = mid + 1, id |= 1;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int q, op, x;
    cin >> q;
    while (q--)
    {
        cin >> op >> x;
        if (op == 1)
            update(x);
        else
            cout << query(x) << '\n';
    }
    return 0;
}
```

---

## 作者：PigNotFound (赞：0)

平衡树模板怎么能没有最好写的 01trie 树呢？
首先，01trie 树是可以自动排序的。左边小，右边大。

所以，我们在每个节点记录左子树的大小，查询排名就是经过的结点左子树的大小之和。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Pig = 4e5 + 10;
struct BST{
    ll tr[Pig][2], l_size[Pig], r_size[Pig], cnt = 0;
    void insert(ll n) {
        ll p = 0;
        for (ll i = 63; i >= 0; i--) {
            if ((n >> i) & 1)
                r_size[p]++;
            else
                l_size[p]++;
            if (!tr[p][(n >> i) & 1])
                tr[p][(n >> i) & 1] = ++cnt;
            p = tr[p][(n >> i) & 1];
        }
    }
    void del(ll n) {
        ll p = 0;
        for (ll i = 63; i >= 0; i--) {
            if ((n >> i) & 1)
                r_size[p]--;
            else
                l_size[p]--;
            p = tr[p][(n >> i) & 1];
        }
    }
    ll get_rank(ll n) {
        ll p = 0, res = 0;
        for (ll i = 63; i >= 0; i--) {
            if ((n >> i) & 1)
                res += l_size[p];
            p = tr[p][(n >> i) & 1];
            if (!p)
                break;
        }
        return res;
    }
    ll get_num(ll n) {
        ll p = 0, res = 0;
        for (ll i = 63; i >= 0; i--) {
            ll flag = 0;
            if (n > l_size[p]) {
                res |= (1 << i);
                n -= l_size[p];
                flag = 1;
            }
            p = tr[p][flag];
            if (!p)
                break;
        }
        return res;
    }
    ll forward(ll n) {
        return get_num(get_rank(n));
    }
    ll backward(ll n) {
        return get_num(get_rank(n + 1) + 1);
    }
};
BST tr;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll q;
    cin >> q;
    for (; q; q--) {
        ll op, x;
        cin >> op >> x;
        if (op == 1)
            tr.insert(x);
        else {
            int c = tr.get_num(x);
            cout << c << endl;
            tr.del(c);
        }
    }
    return 0;
}

```

---

## 作者：cheng2010 (赞：0)

# データ構造
## 思路
插入？查询排名？删除？平衡树模板啊！如果你还不知道什么是平衡树的话，请点[这里](https://www.luogu.com.cn/problem/P3369)。

现在这题就非常简单了，这里用的是 FHQ-treap。

## code
```cpp
#include<bits/stdc++.h>
#define tp_rt treap.root
#define INF 2147483647 
using namespace std;
const int N=1e5+7;
struct Treap
{
	int siz,lson,rson,rnd,val;
}tree[N<<1];
struct FHQ_treap
{
	int cnt,root;
	inline void change(int x)
	{
		tree[x].siz=tree[tree[x].lson].siz+tree[tree[x].rson].siz+1;
	}
	inline void split_val(int now,int key,int &x,int &y)
	{
		if(!now)
		{
			x=y=0;
			return ;
		}
		if(tree[now].val<=key)
		{
			x=now;
			split_val(tree[now].rson,key,tree[now].rson,y);
		}
		else
		{
			y=now;
			split_val(tree[now].lson,key,x,tree[now].lson);
		}
		change(now);
	}
	inline void split_siz(int now,int sz,int &x,int &y)
	{
		if(!now)
		{
			x=y=0;
			return ;
		}
		if(tree[tree[now].lson].siz<sz)
		{
			x=now;
			split_siz(tree[now].rson,sz-tree[tree[now].lson].siz-1,tree[now].rson,y);
		}
		else
		{
			y=now;
			split_siz(tree[now].lson,sz,x,tree[now].lson);
		}
		change(now);
	}
	inline int merge(int x,int y)
	{
		if(!x||!y) return x|y;
		if(tree[x].rnd<tree[y].rnd)
		{
			tree[x].rson=merge(tree[x].rson,y);
			change(x);
			return x;
		}
		tree[y].lson=merge(x,tree[y].lson);
		change(y);
		return y;
	}
	inline int join(int x)
	{
		tree[++cnt]=(Treap){1,0,0,rand(),x};
		return cnt;
	}
	inline void ins(int &rt,int x)
	{
		int r1,r2;
		split_val(rt,x,r1,r2);
		rt=merge(merge(r1,join(x)),r2);
	}
	inline void del(int &rt,int x)
	{
		int r1,r2,r3;
		split_val(rt,x,r1,r2);
		split_val(r1,x-1,r1,r3);
		r3=merge(tree[r3].lson,tree[r3].rson);
		rt=merge(merge(r1,r3),r2);
	}
	inline int rank(int &rt,int x)
	{
		int r1,r2;
		split_val(rt,x-1,r1,r2);
		int ans=tree[r1].siz;
		rt=merge(r1,r2);
		return ans;
	}
	inline int kth(int &rt,int k)
	{
		k++;
		int r1,r2,pos;
		split_siz(rt,k,r1,r2);
		pos=r1;
		while(tree[pos].rson)
			pos=tree[pos].rson;
		merge(r1,r2);
		return tree[pos].val;
	}
	inline int pre(int &rt,int x)
	{
		int r1,r2,pos;
		split_val(rt,x-1,r1,r2);
		pos=r1;
		while(tree[pos].rson) pos=tree[pos].rson;
		merge(r1,r2);
		return tree[pos].val;
	}
	inline int nxt(int &rt,int x)
	{
		int r1,r2,pos;
		split_val(rt,x,r1,r2);
		pos=r2;
		while(tree[pos].lson) pos=tree[pos].lson;
		merge(r1,r2);
		return tree[pos].val;
	}
	inline void init()
	{
		srand(time(NULL));
		root=cnt=0;
		ins(root,INF);
		ins(root,-INF);
	}
}treap;
int T;
int main()
{
	scanf("%d",&T);
	treap.init();
	while(T--)
	{
		int opt,x;
		scanf("%d %d",&opt,&x);
		if(opt==1)
		{
			treap.ins(tp_rt,x);
		}
		else
		{
			int y=treap.kth(tp_rt,x);
			printf("%d\n",y);
			treap.del(tp_rt,y);
		}
	}
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意
见[这里](https://www.luogu.com.cn/problem/AT_arc033_3)。
# 方法
怎么能没有 FHQ 呢？

由于只是添加和查询排名，所以直接用平衡树模板。

~~又是没动脑子的一道题~~。

# Code
```cpp
// LUOGU_RID: 159826333
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e05 * 2 + 7;

int n;

int Root;

int tot;

struct FHQ_Treap {
    int siz;
    int lson, rson;
    int pri;
    int key;
} tree[MAXN];

int create(int key)
{
    int root = ++tot;
    tree[root].lson = tree[root].rson = 0;
    tree[root].siz = 1;
    tree[root].pri = rand();
    tree[root].key = key;
    return root;
}

void update(int p)
{
    return (void) (tree[p].siz = tree[tree[p].lson].siz + tree[tree[p].rson].siz + 1);
}

void Split(int p, int key, int &x, int &y)
{
    if(!p)
    {
        return (void) (x = y = 0);
    }
    if(tree[p].key <= key)
    {
        x = p;
        Split(tree[p].rson, key, tree[p].rson, y);
    }
    else
    {
        y = p;
        Split(tree[p].lson, key, x, tree[p].lson);
    }
    update(p);
    return ;
}

int merge(int x, int y)
{
    if(!x or !y)
    {
        return x + y;
    }
    if(tree[x].pri > tree[y].pri)
    {
        tree[x].rson = merge(tree[x].rson, y);
        update(x);
        return x;
    }
    else
    {   
        tree[y].lson = merge(x, tree[y].lson);
        update(y);
        return y;
    }
}

void Insert(int key)
{
    int x, y;
    Split(Root, key - 1, x, y);
    Root = merge(merge(x, create(key)), y);
    return ;
}

void Dele(int key)
{
    int x, y, z;
    Split(Root, key, x, z);
    Split(x, key - 1, x, y);
    if(y)
    {
        y = merge(tree[y].lson, tree[y].rson);
    }
    Root = merge(merge(x, y), z);
    return ;
}

int Rank(int key)
{
    int x, y;
    int ans;
    Split(Root, key - 1, x, y);
    ans = tree[x].siz + 1;
    Root = merge(x, y);
    return ans;
}

int keyans(int rk)
{
    int root = Root;
    while(1)
    {
        if(tree[tree[root].lson].siz + 1 == rk)
        {
            break;
        }
		else if(tree[tree[root].lson].siz + 1 > rk)
		{
			root = tree[root].lson;
		}
		else
		{
			rk -= tree[tree[root].lson].siz + 1;
			root = tree[root].rson;
		}
    }
    return tree[root].key;
}

int pre(int key)
{
    int x, y, root;
    int ans;
    Split(Root, key - 1, x, y);
    root = x;
    while(tree[root].rson)
        root = tree[root].rson;
    ans = tree[root].key;
    Root = merge(x, y);
    return ans;
}

int nxt(int key)
{
    int x, y, root;
    int ans;
    Split(Root, key, x, y);
    root = y;
    while(tree[root].lson)
        root = tree[root].lson;
    ans = tree[root].key;
    Root =  merge(x, y);
    return ans;
}

signed main()
{
    // freopen("a.out", "w", stdout);
    scanf("%d", &n);
    
    for(int i = 1; i <= n; i++)
    {
    	int type, x;
    	scanf("%d%d", &type, &x);
    	if(type == 1)
    	{
    		Insert(x);
		}
		else
		{
			int k = keyans(x);
			printf("%d\n", k);
			Dele(k);
		}
	}
    
    return 0;
}
```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc033_3)

替罪羊树模板题怎么能没有亲爱的 splay 呢？

### 前置芝士

splay 是一种基于二叉搜索树的算法。

什么是二叉搜索树呢？我们想象有这么一个序列：


```
1 9 4 5 0 8
```

![](https://cdn.luogu.com.cn/upload/image_hosting/td582bg1.png)

可以发现两点：

1. 二叉搜索树的中序遍历即原序列。

2. 左儿子比爸爸小，右儿子比爸爸大。

可以发现，二叉搜索树的时间复杂度平均优于普通搜索，但是最坏情况下，我们会构造出一种特殊的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/pkzvmal8.png)

它是 $O(n)$ 的，因此，我们需要一种树来让二叉搜索树保持平衡，这就是所谓平衡树。

平衡树有很多种，比如 treap、fhq-treap、替罪羊树等等，但是我们这里要介绍的是 splay。

splay 的操作很简单，说白了就是依靠把一个结点旋转到另一个节点来保持平衡，具体来说，是把 $x$ 设为他爷爷的儿子，把 $x$ 的一个儿子设为他爸爸的儿子，最后把 $x$ 设为他爸爸的爸爸，这个过程不能乱。

查询时，只需要按照二分的思路查询。

```cpp
void find(int x)
{
	int u=root;
	if(!u)return;
	while(T[u].ch[x>T[u].val]&&x^T[u].val)u=T[u].ch[x>T[u].val];
	splay(u,0);
}
```

添加时，先二分，再添加。

```cpp
void insert(int x)
{
	int u=root,fa=0;
	while(u&&x^T[u].val)fa=u,u=T[u].ch[x>T[u].val];
	if(u)T[u].cnt++;
	else
	{
		u=++tot;
		if(fa)T[fa].ch[x>T[fa].val]=u;
		T[u].fa=fa;
		T[u].siz=T[u].cnt=1;
		T[u].ch[0]=T[u].ch[1]=0;
		T[u].val=x;
	}
	splay(u,0);
}
```


删除时，先二分，再删除，把子树变个爸爸。

```cpp
void erase(int x)
{
	int last=next_bound(x,0);
	int next=next_bound(x,1);
	splay(last,0),splay(next,last);
	int del=T[next].ch[0];
	if(T[del].cnt>1)T[del].cnt--,splay(del,0);
	else T[next].ch[0]=0;
} 
```

以上操作都需要 splay，把当前结点 splay 到根节点，而 splay 需要把当前的儿子数更改，也就是 update 操作，这个操作类似线段树的 pushup，也就是把自己的儿子树设为左儿子的儿子树和右儿子的儿子树的和加上本身这个数的出现次数。

最后贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,root,tot;
struct SPLAY
{
	int fa,siz,cnt,val,ch[2];
}T[111111];
void update(int x)//更新儿子数量
{
	T[x].siz=T[T[x].ch[0]].siz+T[T[x].ch[1]].siz+T[x].cnt; 
}
void rotate(int x)//splay中的旋转操作
{
	int y=T[x].fa;
	int z=T[y].fa;
	int w=T[y].ch[1]==x;
	T[z].ch[T[z].ch[1]==y]=x;
	T[x].fa=z;
	T[y].ch[w]=T[x].ch[w^1];
	T[T[x].ch[w^1]].fa=y;
	T[x].ch[w^1]=y;
	T[y].fa=x;
	update(y),update(x);
}
void splay(int x,int goal)//splay不断把结点往上旋转
{
	for(;T[x].fa^goal;rotate(x))
	{
		int y=T[x].fa;
		int z=T[y].fa;
		if(z^goal)
		{
			if(T[y].ch[1]^x^T[z].ch[1]^y)rotate(x);
			else rotate(y);
		}
	}
	if(!goal)root=x;
}
void find(int x)
{
	int u=root;
	if(!u)return;
	while(T[u].ch[x>T[u].val]&&x^T[u].val)u=T[u].ch[x>T[u].val];
	splay(u,0);
}
void insert(int x)
{
	int u=root,fa=0;
	while(u&&x^T[u].val)fa=u,u=T[u].ch[x>T[u].val];
	if(u)T[u].cnt++;
	else
	{
		u=++tot;
		if(fa)T[fa].ch[x>T[fa].val]=u;
		T[u].fa=fa;
		T[u].siz=T[u].cnt=1;
		T[u].ch[0]=T[u].ch[1]=0;
		T[u].val=x;
	}
	splay(u,0);
}
int next_bound(int x,int f)//前驱和后继就是先找到大的/小的，然后反着跳
{
	find(x);
	int u=root;
	if(T[u].val>x&&f)return u;
	if(T[u].val<x&&(!f))return u;
	u=T[u].ch[f];
	while(T[u].ch[f^1])u=T[u].ch[f^1];
	return u;
}
void erase(int x)
{
	int last=next_bound(x,0);
	int next=next_bound(x,1);
	splay(last,0),splay(next,last);
	int del=T[next].ch[0];
	if(T[del].cnt>1)T[del].cnt--,splay(del,0);
	else T[next].ch[0]=0;
} 
int kelement(int x)//不断判断当前左边的儿子数是否大于k，如果大于则在右子树找，否则在左子树找
{
	int u=root; 
	if(T[u].siz<x)return 0;
	while(1145)
	{
		int y=T[u].ch[0];
		if(x>T[y].siz+T[u].cnt)x-=T[y].siz+T[u].cnt,u=T[u].ch[1];
		else if(T[y].siz>=x)u=y;
		else return T[u].val;
	}
}
int main()
{
	cin>>n;
	insert(1e9);
    insert(-1e9);
	while(n--)
	{
		int x,y;
		scanf("%d %d",bitand x,bitand y);
		if(x==1)insert(y);
		if(x==2)
		{
			int f=kelement(tot-y);
			printf("%d\n",f);
			erase(f);
		}
	}
	return 0;
}
```


---

## 作者：ZXXS (赞：0)

データ構造

使用 vector 构造有序序列，名字为 vec 。

加入:
找大于第二个数的最小数，在其前面插入。
```ruby
vec.insert((lower\_bound(vec.begin(),vec.end(),b)),b);
```
查询:
直接输出第 $b-1$ 项。
```ruby
write(vec[b-1]);
```
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void write(int x)//快写
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
inline int read()//快读
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
    return x*f;
}
vector<int> vec; //vector动态数组
int main()
{
	vec.clear();//习惯清空
	int T=read();//T次操作
	while(T--)
	{
		int a=read(),b=read();
		if(a==1)//第一种情况
		{
			vec.insert((lower_bound(vec.begin(),vec.end(),b)),b);//lower_bound找大于b的最小数，在其前面插入
		}
		else//第二种情况
		{
			write(vec[b-1]);//输出第b-1项，-1是因为vec从第0项开始存
			vec.erase(vec.begin()+b-1);//删除
			putchar('\n');//换行
		}
	}
    return 0;
}

```



---

## 作者：Griseo_nya (赞：0)

其实这道题可以用平衡树来过，但蒟蒻不太会写平衡树，于是想到了一种可以在某种程度上替代平衡树的方法——维护一个有序的数组。

下面介绍一下用到的 STL 函数：

`deque` : 同 `vector` ,可以理解为动态长度数组。下标从 $0$ 开始。

`lower_bound` : 在有序序列里找到大于等于所给项的第一个数，返回这个数的迭代器（可以理解为指针）。

`vec.erase(vec.begin()+i)` : 删除第 $i+1$ 个数。

`deque::insert()` : 在指定迭代器处添加给定的数。

然后关于代码的讲解就在代码注释里了。

还不懂可以看[这个](https://www.luogu.com.cn/blog/specialflag/solution-p3369)。

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> qwq;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int op,x;
		scanf("%d%d",&op,&x);
		switch(op){
			
			case(1):
				qwq.insert((lower_bound(qwq.begin(),qwq.end(),x)),x);	//从 qwq 开头到结尾查询第一个大于等于 x 的数的位置，并把 x 插入到该位置（其余数后移）
				break;
			case(2):
				printf("%d\n",qwq[x-1]);					//输出第 x 小的数
				qwq.erase(qwq.begin()+x-1);						//删掉第x 小的数
				break;
	}
	}
	return 0;
}
```


---

## 作者：X_WT (赞：0)

搜**上帝造题的七分钟**的时候搜到的，觉得题目描述很简单就想写……


------------


### 题面：
	
  	类型1：添加数X;
	类型2：输出并删除集合中第x小的数;（保证x小于集合大小）
    数据范围在N=200000以内……
   
   

------------

    
正好会线段树，~~不如瞎搞一波？~~

用sumv[ i ]表示1到i的数字个数和，维护一下就好了

然后找第x大的数的时候，易证单调性，二分一下就好

上代码吧，细节代码有：


```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int X=0,w=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')	w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		X=(X<<3)+(X<<1)+c-'0';
		c=getchar();
	}
	return X*w;
}//位运算快读
const int N=200010;
int sumv[N<<2],k,x,n,lef,rig,mid,ans;
inline void pushup(int o){sumv[o]=sumv[o<<1]+sumv[o<<1|1];}
inline void update(int o,int l,int r,int q,int v){
	if(l==r){sumv[o]+=v;return ;}
	int mid=(l+r)>>1;
	if(q<=mid)	update(o<<1,l,mid,q,v);
	else		update(o<<1|1,mid+1,r,q,v);
	pushup(o);
}//加入的时候v=1,删除的时候v=-1，毕竟一次改一个数
inline int querysum(int o,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)	return sumv[o];
	int ans=0,mid=(l+r)>>1;
	if(ql<=mid)	ans+=querysum(o<<1,l,mid,ql,qr);
	if(qr>mid)	ans+=querysum(o<<1|1,mid+1,r,ql,qr);
	return ans;
}//线段树
int main(){
	n=read();
	for(register int i=1;i<=n;++i){
		k=read();x=read();
		if(k==1){
			update(1,1,N,x,1);
		}//加入数字
		else{
			lef=1;rig=N;ans=N;
			while(lef<rig){
				mid=(lef+rig)>>1;
				int tmp=querysum(1,1,N,1,mid);
				if(tmp<x){
					lef=mid+1;
				}
				else{
					ans=mid;rig=mid;
				}
			}
			printf("%d\n",ans);
			update(1,1,N,ans,-1);//更新一下集合，扔掉一个
		}
	}
	return 0;
}
```
然后似乎数据保证了每个T都不相同？虽然我看不懂日文，但是好像说了什么 **保証される** ……

---

