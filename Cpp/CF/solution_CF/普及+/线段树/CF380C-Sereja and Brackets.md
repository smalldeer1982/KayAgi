# Sereja and Brackets

## 题目描述

Sereja has a bracket sequence $ s_{1},s_{2},...,s_{n} $ , or, in other words, a string $ s $ of length $ n $ , consisting of characters "(" and ")".

Sereja needs to answer $ m $ queries, each of them is described by two integers $ l_{i},r_{i} $ $ (1<=l_{i}<=r_{i}<=n) $ . The answer to the $ i $ -th query is the length of the maximum correct bracket subsequence of sequence $ s_{li},s_{li}+1,...,s_{ri} $ . Help Sereja answer all queries.

You can find the definitions for a subsequence and a correct bracket sequence in the notes.

## 说明/提示

A subsequence of length $ |x| $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ x=s_{k1}s_{k2}...\ s_{k|x|} $ $ (1<=k_{1}<k_{2}<...<k_{|x|}<=|s|) $ .

A correct bracket sequence is a bracket sequence that can be transformed into a correct aryphmetic expression by inserting characters "1" and "+" between the characters of the string. For example, bracket sequences "()()", "(())" are correct (the resulting expressions "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

For the third query required sequence will be «()».

For the fourth query required sequence will be «()(())(())».

## 样例 #1

### 输入

```
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
```

### 输出

```
0
0
2
10
4
6
6
```

# 题解

## 作者：Meatherm (赞：22)

被昨天的比赛锤爆了，于是只能找点简单的数据结构题做做。

在 Codeforces 的 Problemset 找 $2100+$ 的数据结构题居然第一道就是这个，点开一看诶这不是[我出的题](https://www.luogu.com.cn/problem/U96295)么？果然随便出道题都能被找原题，自闭了。

-----

考虑线段树维护两个东西：区间 $[l,r]$ 内不能匹配的左括号数量 $Lsum_k$ 和右括号数量 $Rsum_k$。

对于叶节点，若原序列的这一位是 `(`，则 $Lsum_k=1,Rsum_k=0$；否则 $Lsum_k=0,Rsum_k=1$。

对于非叶子节点，设其左儿子为 $lc$，右儿子为 $rc$，则有：

$$Lsum_k=Lsum_{lc}+Lsum_{rc}-\min\{Lsum_{lc},Rsum_{rc}\}$$

$$Rsum_k=Rsum_{lc}+Rsum_{rc}-\min\{Lsum_{lc},Rsum_{rc}\}$$

若不能产生任何新的匹配，则不能匹配的左括号数量等于左右儿子不能匹配的左括号之和。观察到左儿子不能匹配的左括号可以和右儿子不能匹配的右括号可以匹配，所以应该减去可以匹配的数量 $\min\{Lsum_{lc},Rsum_{rc}\}$。对于右括号同理。

时间复杂度 $O(m \log n)$。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=1000010;
struct Tree{
    int Lsum,Rsum;
}tree[N<<2];
char s[N];
int n,m;
inline int lc(int x){
    return x<<1;
}
inline int rc(int x){
    return x<<1|1;
}
inline void pushup(int k){
    int New=std::min(tree[lc(k)].Lsum,tree[rc(k)].Rsum);
    tree[k].Lsum=tree[lc(k)].Lsum+tree[rc(k)].Lsum-New;
    tree[k].Rsum=tree[lc(k)].Rsum+tree[rc(k)].Rsum-New;
    return;
}
void build(int k,int l,int r){
    if(l==r){
        if(s[l]=='(')
            tree[k].Lsum=1;
        if(s[r]==')')
            tree[k].Rsum=1;
        return;     
    }
    int mid=(l+r)>>1;
    build(lc(k),l,mid);
    build(rc(k),mid+1,r);
    pushup(k);
    return;
}
Tree ask(int k,int l,int r,int L,int R){
    if(L<=l&&r<=R){
        return tree[k];
    }
    int mid=(l+r)>>1;
    if(L<=mid&&!(mid<R))
        return ask(lc(k),l,mid,L,R);
    if(!(L<=mid)&&mid<R)
        return ask(rc(k),mid+1,r,L,R);
    Tree Lc=ask(lc(k),l,mid,L,R),Rc=ask(rc(k),mid+1,r,L,R),Ans;
    int New=std::min(Lc.Lsum,Rc.Rsum);
    Ans.Lsum=Lc.Lsum+Rc.Lsum-New;
    Ans.Rsum=Lc.Rsum+Rc.Rsum-New;
    return Ans;
}
int main(void){
    scanf("%s",s+1);
    n=strlen(s+1);
    build(1,1,n);
    scanf("%d",&m);
    int l,r;
    while(m--){
        scanf("%d%d",&l,&r);
        Tree Ans=ask(1,1,n,l,r);
        printf("%d\n",(r-l+1)-Ans.Lsum-Ans.Rsum);
    }
    return 0;
}
```

---

## 作者：SunsetGlow95 (赞：11)

# CF380C Sereja and Brackets 题解

## 题意

每次询问一个区间的最大合法括号子序列长度。

## 分析

一般遇到合法括号序列，很多时候可以直接转化：

**每个左括号视为 $1$，右括号视为 $-1$。合法的序列中每个前缀和不为负数，且以 $0$ 结束。**

所以对于一段前缀和，先考虑是否存在负数，如果存在，就去掉相应数量的右括号。

不以 $0$ 结束，就去掉相应数量的左括号。

## 实现

一开始就直接维护整体的前缀和。那么，把单个区间的前缀和拎出来也就简单了。

默认是整个区间长度。查找负数直接用 RMQ 找个最小值即可。

注意，去掉右括号时要对整个区间的前缀和做对应的处理。

如果此时还不以 $0$ 结尾，就再去掉对应的左括号。

那么，这道题就被转化成了一个简单 RMQ！

假设区间长度是 $n$。$r=-\min(0,\min_{i=l}^{r}\{a_i\})$，而（未经变化的）整个区间的前缀和是 $s$。

那我的结论就是 $n-r-(s+r)$。

ST 表时间复杂度 $O(n\log n+m)$，线段树可以做到 $O(n+m\log n)$。

## 代码

ST 表都可以跑过去。更怪异的是，如果写错 ST 表，取 $r$ 的时候不考虑最后一个元素，那么只要在 $s+r$ 那里加上绝对值也可以过（具体可以推一推式子，错解我就不赘述了）。笑死了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 1000005;
const int MXLG = 20;
int st[MXN][MXLG], lg[MXN];
char str[MXN];
int N, M;

inline int query(int l, int r) {
	int g(lg[r - l + 1]);
	return min(st[l][g], st[r - (1 << g) + 1][g]);
}

int main() {
	cin >> (str + 1);
	N = strlen(str + 1);
	lg[1] = 0;
	for (int i(2); i <= N; ++i) lg[i] = lg[i >> 1] + 1;
	for (int i(1); i <= N; ++i) {
		if (str[i] == '(') st[i][0] = st[i - 1][0] + 1;
		else st[i][0] = st[i - 1][0] - 1;
	}
	for (int i(1); (1 << i) <= N; ++i) {
		for (int j(1); j + (1 << (i - 1)) <= N; ++j) {
			st[j][i] = min(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
		}
	}
	cin >> M;
	for (int l(0), r(0); M--; ) {
		cin >> l >> r;
		int nmin(-min(query(l, r) - st[l - 1][0], 0));
		cout << (r - l + 1) - nmin - (st[r][0] - st[l - 1][0] + nmin) << endl;
	}
	return 0;
}
```

---

## 作者：LJC00118 (赞：5)

考虑一个括号序列，我们把能匹配的括号全都删掉，剩下的括号一定形如 ))))))((((((((

我们考虑用线段树来维护一个区间内，左边有几个 )，右边有几个 (，能匹配几对括号，然后区间合并的时候计算一下能多匹配几对括号即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 1e6 + 5;

int n, m;

struct ele {
    int ans, left, right;
    ele (int a = 0, int b = 0, int c = 0) : ans(a), left(b), right(c) {}
};

ele merge(ele a, ele b) {
    ele ans;
    int val = min(a.right, b.left);
    a.right -= val; b.left -= val;
    ans.ans = a.ans + b.ans + val;
    ans.left = a.left + b.left;
    ans.right = a.right + b.right;
    return ans;
}

struct node_t {
    int l, r;
    ele val;
} p[N << 2];

char c[N];
void build(int u, int l, int r) {
    p[u].l = l; p[u].r = r;
    if(l == r) {
        p[u].val = ele(0, c[l] == ')', c[l] == '(');
        return;
    }
    int mid = (l + r) >> 1;
    build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
    p[u].val = merge(p[u << 1].val, p[u << 1 | 1].val);
}

ele query(int u, int l, int r) {
    if(l <= p[u].l && p[u].r <= r) return p[u].val;
    int mid = (p[u].l + p[u].r) >> 1; ele ans;
    if(mid >= l) ans = merge(ans, query(u << 1, l, r));
    if(mid + 1 <= r) ans = merge(ans, query(u << 1 | 1, l, r));
    return ans;
}

int main() {
    scanf("%s", c + 1); n = strlen(c + 1);
    build(1, 1, n);
    read(m); while(m--) {
        int l, r; read(l); read(r);
        print(query(1, l, r).ans << 1, '\n');
    }
    return 0;
}
```

---

## 作者：sinsop90 (赞：3)

题目大意:给定一个括号字符串, 进行 m 次查询, 每次查询一个区间中最长的合法括号子序列。

考虑将括号序列进行一次变换, 如果我们设 $($ 的权值为 $1$, $)$ 的权值为 $-1$, 我们会得到下面一个序列:

$())(())(())($ 变为 $1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1$。

那这有什么用呢?如果我们对这个序列做个前缀和 $pre$, 并数形结合一下, 我们或许能发现一些性质:

![](https://s2.loli.net/2022/01/23/E3ZBy85QdxGfTXe.png)

在这张图上, 如果我们选出一个在黑线之下的点, 它前面的右括号数量比左括号多。

同理, 黑线之上的点, 前面的右括号数量比左括号少。

也就是说, 如果我们任意选出两个点 $l, r$, 我们可以通过 $pre_l, pre_r$ 来确定区间内各种括号的数量。

接下来我们来关注这样一个问题:在下面这个区间中, 我们最多能选出多长的合法括号子序列呢?

![](https://s2.loli.net/2022/01/23/ZxQrYsmoc5lBCRN.png)

不妨设我们取出了 $x$ 个 $($ , $y$ 个 $)$, 而这个区间里有 $a$ 个 $($, $b$ 个 $)$。

我们有什么结论呢?显然 $x≥y$, $a≤b$, $x≤a$, $y≤b$。

整理得 $y ≤ a$, 当 $y$ 取最大值时, 还剩下 $b-a = h$ 个

所以说, 我们最多选出长度为 $2b$ 的合法括号子序列.

那如果在这个区间里 $)$ 的数量大于 $($ 呢？

同理得最多选出 $2a$ 个合法括号子序列, 也还剩下 $h$ 个 $($ 没有被选到。

那么, 这有什么用呢?

我们回到原本的那张图中:

![](https://s2.loli.net/2022/01/23/E3ZBy85QdxGfTXe.png)

如果我们现在要求区间 $[1, 10]$ 中的最长合法括号子序列。

这时我们选出 $7$ 这个点, 注意这是这个区间中的最低点。

我们发现, 区间 $[1,7]$ 和 $[8,10]$ 不就是我们刚刚所求出的问题吗?

因此对于 $[1,7]$ , $h$ 为 $1$, 因此可以选出 $7 - 1=6$ 长度的合法括号子序列。

对于 $[8,10]$ , $h$ 为 $1$, 因此可以选出 $3-1=2$ 长度的合法括号子序列。

注：对于区间的 $l$, 我们要看的是线段的起点, 而对于区间的 $r$, 我们要看的是终点。

我们将这两个答案加起来, $8$ 就是最终的答案。

你可能会问, 那如果前后舍弃的括号又拼成了合法括号子序列怎么办?

事实上, 前面我们只舍弃了右括号, 而后面我们只舍弃了左括号, 不可能拼成新的合法括号子序列。

因此我们只需要维护区间最小值得到 $h$ 即可。代码如下:

```
#include <bits/stdc++.h>
#define maxn 4000005
using namespace std;
char mp[maxn];
int n, minn[maxn], m;
int pre[maxn];
int ls(int p) {
	return p << 1;
}
int rs(int p) {
	return p << 1 | 1;
}
void pushup(int p) {
	minn[p] = min(minn[ls(p)], minn[rs(p)]);
}
void build(int p, int l, int r) {
	int mid = (l + r) >> 1;
	if(l == r) {
		minn[p] = pre[l];
		return;
	}
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	pushup(p);
}
int querymin(int l, int r, int p, int nl, int nr) {
	if(nl <= l && r <= nr) return minn[p];
	int mid = (l + r) >> 1, res = 2147483647;
	if(nl <= mid) res = min(res, querymin(l, mid, ls(p), nl, nr));
	if(nr > mid) res = min(res, querymin(mid + 1, r, rs(p), nl, nr));
	return res;
}
int main() {
	cin >> mp + 1;
	n = strlen(mp + 1);
	for(int i = 1;i <= n;i++) {
		if(mp[i] == '(') pre[i] = pre[i - 1] + 1;
		else pre[i] = pre[i - 1] - 1;//前缀和
	}
	build(1, 1, n);
	scanf("%d", &m);
	for(int i = 1;i <= m;i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		int k = querymin(1, n, 1, l, r);//线段树维护最小值
		printf("%d\n", r - l + 1 - abs(pre[r] - k) - abs(pre[l - 1] - k));
	}
}
```


---

## 作者：pldzy (赞：2)

补药线段树了！！发现题解区大多都是线段树的题解云云，所以来一篇经典折线模型（？）的题解。

~~顺便逼自己证明一下~~。

p.s. 关于下文提到的那个 01 串排序问题，其实也不难，不过想知道的友友可以私信找我要一下。这里就不加长篇幅了。

## Solution

就我目前所见，除了括号序列之外，还有 01 串排序问题也可以用折线模型抽象。左括号 $1$，右括号 $-1$。

考虑这个区间括号抽象出来的折线。显然的前置结论就是，**合法括号序列的折线必定是全部位于水平线之上的，且必定是从水平处出发，水平处结束**。水平线就是 $0$，也即我描灰的线。

所以如下图染绿色的部分所示，这些绿色三角必定本身是一个合法括号序列了，我们可以直接删掉它们，把剩下的折线合并到一起。也即我描红的折线。

一直重复这个过程，直到折线不存在尖角向上的三角形。此时的折线要么是一条直线，要么是尖角向下的三角形。发现剩下的部分我们再怎么样也无法继续匹配了。

所以最后的答案就是区间长度 减去 剩下无法继续匹配的折线的长度。

这个长度是什么？左侧的直线长度是 $-\min(0,mn)$，右侧的直线长度是 $h_r-mn$，$h_r$ 是结尾的折线高度，$mn$ 是折线的最低谷。也即我描蓝的部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/ibcy5n91.png)

所以用 st 表维护一下区间最小值就好了。

## Code

````cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define per(i, a, b) for(int i = (a); i >= (b); --i)

const int maxn = 1e6 + 5;

int n, s[maxn], st[21][maxn];

inline int qry(int l, int r){
	int k = log2(r - l + 1);
	return min(st[k][l], st[k][r - (1 << k) + 1]); 
}

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(NULL);
	string str; cin >> str;
	n = str.length(); str = " " + str;
	rep(i, 1, n) s[i] = s[i - 1] + (str[i] == '(' ? 1 : -1), st[0][i] = s[i]; 
	
	for(int j = 1; (1 << j) <= n; ++j) for(int i = 1; i + (1 << j) - 1 <= n; ++i)
		st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
	
	int m; cin >> m;
	while(m--){
		int l, r; cin >> l >> r;
		int ans = r - l + 1, mn = min(qry(l, r) - s[l - 1], 0);
		ans -= s[r] - s[l - 1] - mn * 2;
		cout << ans << '\n';
	}
	return 0;
}
````

## Proof

如果放完代码就结束了，可能得被喷。

为什么这样贪心是对的？

考虑调整法。如果某一次删除向上三角形时，我们留下了可以匹配的一对括号，没有直接匹配。

容易发现因为我们删除的都是尖角向上的三角形，画图就能发现在这个三角形内，不论是左括号还是右括号，和它匹配到的都是**最近的、能和它匹配的右/左括号**（说的不严谨，其实并不是严格最近，而是相对这个三角形以外的其他可匹配括号最近的）。

如果后面把它匹配了，匹配括号一定相对更远，所以运用调整法，把它调整到同一个三角内匹配，一定不劣。

其实线段树的底层思维也是这个啊，只是看起来自然所以没有啥题解真的去证明而已。

~~证得貌似不咋好，凑合一下~~。

---

## 作者：naroto2022 (赞：2)

# CF380C 题解

### 题面

[原题传送门（洛谷）](http://luogu.com.cn/problem/CF380C)

[原题传送门](https://codeforces.com/problemset/problem/380/C)

### 题意

给定一个长度为 $n$ 括号序列和 $q$ 个询问区间 $[l,r]$，对于每一个询问的区间中，要求出长度最长的为合法括号串的子串的长度。

### 思路

看到这种时间复杂度允许在 $O(n\log n)$ 的，有许多区间的题目自然想到线段树。

但是进一步思考发现维护区间最大合法括号序列似乎有点困难，于是考虑利用正难则反的思想，考虑线段树每个节点维护的节点维护区间中不合法的左括号数 $lsum$ 和不合法的右括号数 $rsum$。

如果想到这一步的话，那这道题基本就解决了。

首先先考虑初始化。

对于线段树中的叶子结点，单独一个肯定是不合法的，所以有如下两种情况。

- 若原序列中的位置为 `(`，则此节点 $lsum\gets1,rsum\gets0$。
- 若原序列中的位置为 `)`，则此节点 $lsum\gets0,rsum\gets1$。

接下来考虑如何区间合并。

其实也很简单，左儿子区间和右儿子区间中原本单独拿出来不合法的括号数合并起来可以凑成 $\min(lsum_{ls},rsum_{rs})$ 对合法的括号，所以在合并的区间中，左右括号的不合法数就要减去它，所以就有。

- $lsum_p\gets lsum_{ls}+lsum_{rs}-\min(lsum_{ls},rsum_{rs})$。

- $rsum_p\gets rsum_{ls}+rsum_{rs}-\min(lsum_{ls},rsum_{rs})$。

（其中 $p$ 是当前节点的编号。）

统计答案的时候也是同样的道理，最后输出询问区间的长度减去不合法括号数即可。

于是，就可以过了这道题啦。

### 代码

[AC记录](https://codeforces.com/problemset/submission/380/293218276)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e6+5;
ll n,q;
struct tree{
    ll lsum,rsum,l,r;
    void clear(){lsum=rsum=0;}
}t[MN<<2];
char ch[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void update(ll p){
    ll num=min(t[ls].lsum,t[rs].rsum);
    t[p].lsum=t[ls].lsum+t[rs].lsum-num;
    t[p].rsum=t[ls].rsum+t[rs].rsum-num;
}
void build(ll p, ll l, ll r){
    t[p].l=l;t[p].r=r;
    if(l==r){
        if(ch[l]=='(') t[p].lsum=1;
        else t[p].rsum=1;
        return;
    }
    ll mid=l+r>>1;
    build(ls,l,mid);build(rs,mid+1,r);
    update(p);
}
tree query(ll p, ll l, ll r){
    if(l<=t[p].l&&t[p].r<=r) return t[p];
    ll mid=(t[p].l+t[p].r)>>1;tree res;res.clear();
    if(r<=mid) return query(ls,l,r);
    if(l>mid) return query(rs,l,r);
    tree lc=query(ls,l,r),rc=query(rs,l,r);
    ll num=min(lc.lsum,rc.rsum);
    res.lsum=lc.lsum+rc.lsum-num;
    res.rsum=lc.rsum+rc.rsum-num;
    return res;
}
int main(){
    scanf("%s",ch+1);n=strlen(ch+1);
    build(1,1,n);
    q=read();while(q--){
        ll l=read(),r=read();
        tree ans=query(1,l,r);
        write((r-l+1)-ans.lsum-ans.rsum);putchar('\n');
    }
    return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF380C)
### 思路分析
我的第一篇线段树题解！

考虑用线段树维护 $l$ 表示这段区间内**不能匹配**的左括号数，$r$ 表示这段区间内的**不能匹配**的右括号数。

那么我们很容易得出转移：

```cpp
tree[x].l=tree[ls(x)].l+tree[rs(x)].l
tree[x].r=tree[ls(x)].r+tree[rs(x)].r
```
但是这样是错误的，因为左右儿子可能造成括号匹配，所以还应减去成功括号匹配的个数，更改后如下：
```cpp
tree[x].l=tree[ls(x)].l+tree[rs(x)].l-min(tree[ls(x)].l,tree[rs(x)].r);
tree[x].r=tree[ls(x)].r+tree[rs(x)].r-min(tree[ls(x)].l,tree[rs(x)].r);
```
随后就简单了，由于是字符串是静态，所以接下来我们来考虑答案。

很明显，既然一段区间内只有 $l$ 和 $r$ 不能匹配，那么就意味着其余已经匹配了，所以得出答案为：$(R-L+1)-l-r$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls(x) (x*2)
#define rs(x) (x*2+1)
#define mid (l+r)/2
const int N=4e6+4;
int a[N],n,lan[N];
struct nn{
	int l,r;
}tree[N];
string s;
void up(int x){
	tree[x].l=tree[ls(x)].l+tree[rs(x)].l-min(tree[ls(x)].l,tree[rs(x)].r);
	tree[x].r=tree[ls(x)].r+tree[rs(x)].r-min(tree[ls(x)].l,tree[rs(x)].r);
}
void build(int x,int l,int r){
	if(l==r){
		if(s[l]=='(')tree[x].l=1;
		else tree[x].r=1;
		return;
	}
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	up(x);
}
nn get(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R){
		return tree[x];
	}
	if(L<=mid&&mid+1>R){
		return get(ls(x),l,mid,L,R);
	}
	else if(mid+1<=R&&L>mid){
		return get(rs(x),mid+1,r,L,R);
	}
	nn ls=get(ls(x),l,mid,L,R);
	nn rs=get(rs(x),mid+1,r,L,R);
	nn ans;
	ans.l=ls.l+rs.l-min(ls.l,rs.r);
	ans.r=ls.r+rs.r-min(ls.l,rs.r);
	return ans;
}
main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s;
	n=s.size();
	s="#"+s;
	build(1,1,n);
	int T;
	cin>>T;
	while(T--){
		int x,y;
		cin>>x>>y;
		nn ans=get(1,1,n,x,y);
		cout<<(y-x+1)-ans.l-ans.r<<"\n";//答案
	}
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

随便找的题，直接爆锤了。

考虑一个区间的构成是由已匹配到的括号，未匹配到的左括号和未匹配到的右括号三部分组成。然后可以发现这样的构成是可以区间合并的，加上询问的也是一段区间，遂考虑线段树。

线段树维护三个值，已匹配到的括号的数量 $sum$，未匹配到的左括号数量 $lef$ 和未匹配到的右括号 $rig$。对于左区间 $l$ 和右区间 $r$ 合并成区间 $k$，定义可新匹配的括号数量为 $p=\min(lef_l,rig_r)$，公式是这样的：

$$sum_k=sum_l+sum_r+p$$

$$lef_k=lef_l+lef_r-p$$

$$rig_k=rig_l+rig_r-p$$

然后就维护这三个式子，就做完了。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define ll (k<<1)
#define rr (k<<1|1)
string s;
int n, m, a, b;
struct tree {
	int l, r, sum, lef, rig;
} t[4000005];
inline void pushup(int k) {
	t[k].sum = t[ll].sum + t[rr].sum;
	t[k].sum += min(t[ll].lef, t[rr].rig);
	t[k].lef = t[ll].lef - min(t[ll].lef, t[rr].rig) + t[rr].lef;
	t[k].rig = t[rr].rig - min(t[ll].lef, t[rr].rig) + t[ll].rig;
	return ;
}
void build(int k, int l, int r) {
	t[k].l = l, t[k].r = r;
	if (l == r) {
		if (s[l] == '(') t[k].lef++;
		else t[k].rig++;
		return ;
	}
	build(ll, l, mid);
	build(rr, mid + 1, r);
	pushup(k);
}
tree query(int k, int l, int r) {
	if (t[k].l > r || t[k].r < l) return {0, 0, 0, 0, 0};
	if (t[k].l >= l && t[k].r <= r) {
		return t[k];
	}
	tree le = query(ll, l, r), ri = query(rr, l, r), re;//分别对应上文的 l，r，k
	re.sum = le.sum + ri.sum;
	re.sum += min(le.lef, ri.rig);
	re.lef = le.lef - min(le.lef, ri.rig) + ri.lef;
	re.rig = ri.rig - min(le.lef, ri.rig) + le.rig;
	return re;
}
signed main() {
	cin >> s;
	n = s.length();
	s = ' ' + s;
	build(1, 1, n);
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		cout << query(1, a, b).sum * 2 << "\n";
	}
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

挺板子的 RMQ。

考虑用 $1$ 和 $-1$ 来处理括号序列，维护这一序列的前缀和。对于一段前缀和，先考虑是否存在负数，如果存在，就去掉相应数量的右括号。容易得到查询的答案为 $(r-l+1)+2\times\min_{i=l}^r a_i-\sum_{i=l}^r a_i$。显然可以使用线段树或 ST 表维护，时间复杂度分别为 $O(N+M\times\log N)$ 和 $O(N\times\log N+M)$。这里使用 ST 表。

[参考代码](https://codeforces.com/problemset/submission/380/296503784)

---

## 作者：ivyjiao (赞：0)

看标签，$2000$ 的 DS，考虑线段树。

考虑维护什么东西，显然维护拼不上的左括号数量和拼不上的右括号数量。

考虑合并左右区间，设 $b_u$ 为 $u$ 区间拼不上的左括号数量，$c_u$ 为 $u$ 区间拼不上的右括号数量，那么显然有 $b_u=b_{ls}+b_{rs},c_u=c_{ls}+c_{rs}$，再想到左儿子区间拼不上的左括号可能和右儿子拼不上的右括号拼上，数量为 $\min(b_{ls},c_{rs})$，所以得到：

$$b_u=b_{ls}+b_{rs}-\min(b_{ls},c_{rs})$$
$$c_u=c_{ls}+c_{rs}-\min(b_{ls},c_{rs})$$

查找的时候就把 $b$ 和 $c$ 改成左儿子和右儿子返回的答案，然后把这个式子在建树和查找的时候 pushup 一下就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
#define fi first
#define se second
#define ls u*2
#define rs u*2+1
using namespace std;
const int N=4e6+1;
char a[N];
int n,q,b[N],c[N],x,y;
void build(int u,int l,int r){
    if(l==r){
        if(a[l]=='(') b[u]=1;
        else c[u]=1;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    b[u]=b[ls]+b[rs]-min(b[ls],c[rs]);
    c[u]=c[ls]+c[rs]-min(b[ls],c[rs]);
}
PII query(int u,int l,int r,int L,int R){
    if(L<=l&&r<=R) return {b[u],c[u]};
    int mid=l+r>>1;
    PII ans={0,0},x={0,0},y={0,0};
    if(L<=mid) x=query(ls,l,mid,L,R);
    if(R>mid) y=query(rs,mid+1,r,L,R);
    ans.fi=x.fi+y.fi-min(x.fi,y.se);
    ans.se=x.se+y.se-min(x.fi,y.se);
    return ans;
}
int main(){
    scanf("%s",a+1);
    n=strlen(a+1);
    build(1,1,n);
    cin>>q;
    while(q--){
        cin>>x>>y;
        PII p=query(1,1,n,x,y);
        cout<<y-x+1-p.fi-p.se<<endl;
    }
}
```

---

## 作者：sLMxf (赞：0)

居然让我一遍过了......
# Pro
查询区间内最长合法序列。
# Sol
定义 $w1_u$ 表示不可匹配左括号，$w2_u$ 同理。

那么考虑如何从 $w1_l$ 和 $w1_r$ 推出 $w1_u$。

最容易想到的是 $w1_u=w1_l+w1_r$，但是作为一道不是板子题的题，怎么可能这么简单？

容易发现，我们遗漏了两边括号可以合并的括号对，这里一共有 $\min\{w1_l,w2_r\}$。

所以 $w1_u=w1_l+w2_r-\min\{w1_l,w2_r\}$。

然后查询时用同样的套路即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct Segment_tree{
	string s;
	int w1[4*1000005],w2[4*1000005];
	void pushup(int u)
	{
		w1[u]=w1[u*2]+w1[u*2+1]-min(w1[u*2],w2[u*2+1]);
		w2[u]=w2[u*2]+w2[u*2+1]-min(w1[u*2],w2[u*2+1]);
	}
	void build(int u=1,int l=1,int r=n)
	{
		if(l==r)
		{
			w1[u]=(s[l]=='(');
			w2[u]=(s[l]==')');
			return;
		}
		int mid=(l+r)/2;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u);
	}
	bool InRangeOf(int L,int R,int l,int r)
	{
		return (l<=L)&&(R<=r);
	}
	bool OutRangeOf(int L,int R,int l,int r)
	{
		return (L>r)||(R<l);
	}
	pair<int,int> query(int l,int r,int u=1,int L=1,int R=n)
	{
		if(InRangeOf(L,R,l,r)) return make_pair(w1[u],w2[u]);
		else if(!OutRangeOf(L,R,l,r))
		{
			int mid=(L+R)/2;
			pair<int,int> ls=query(l,r,u*2,L,mid),
						  rs=query(l,r,u*2+1,mid+1,R);
			return make_pair((ls.first+rs.first-min(ls.first,rs.second)),(ls.second+rs.second-min(ls.first,rs.second)));
		}
		else return make_pair(0,0);
	}
}a;
int main()
{
	cin>>a.s;
	n=a.s.size();
	a.s=" "+a.s;
	a.build();
	int q;
	cin>>q;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		cout<<(r-l+1-a.query(l,r).first-a.query(l,r).second)<<endl;
	}
	return 0;
}
```

---

## 作者：kind_aunt (赞：0)

这题应该不只绿吧，也有可能是我太菜了。
## 大意
给定长度为 $n$ 的括号序列，并给出 $q$ 个询问，对于每个询问，输入 $l$ 和 $r$，求 $[l,r]$ 中最长合法括号序列的长度。  
括号序列的定义：  
1. **空串**是合法括号序列。
2. 当 $a$ 为一个合法序列时，$(a)$ 也是一个合法括号序列。比如：`()(())` 是一个合法括号序列，那么 `(()(()))` 也是。
3. 当 $a$ 和 $b$ 都是合法括号序列时，$ab$ 也是。比如：`()` 和 `(())` 都是合法的，所以 `()(())` 是合法的（$ab$ 指的是两个序列拼起来，不是相乘）。
## 思路
个人认为这个思路有点难想，我们将 $treel_i$ 定义为编号为 $i$ 的节点，有多少个左括号不能匹配，$treer_i$ 同理。

由于左子树不能匹配的 `(` 一定可以与右子树不能匹配的 `)` 配对，所以在向上传递时还要减去 $\min(treel_l,treer_r)$。

在 query 函数中同理。
## Code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
string a;
int n,ll,rr;
const int N=1e6+5;
int treel[N<<2],treer[N<<2];
int ls(int x){return x<<1;}
int rs(int x){return x<<1|1;}
struct node{int l,r;};
node lll,rrr;
void push_up(int p)
{
	treel[p]=treel[ls(p)]+treel[rs(p)] -min(treel[ls(p)],treer[rs(p)]);
	treer[p]=treer[ls(p)]+treer[rs(p)]- min(treel[ls(p)],treer[rs(p)]);
}
void build(int s,int t,int p)
{
	if(s==t)
	{
		if(a[s]=='(') treel[p]=1,treer[p]=0;
		else treel[p]=0,treer[p]=1;
		return;
	}
	int mid=s+((t-s)>>1);
	build(s,mid,ls(p));
	build(mid+1,t,rs(p));
	push_up(p);
}
node query(int l,int r,int s,int t,int p)
{
	if(l<=s and t<=r) return (node){treel[p],treer[p]};
	int mid=s+((t-s)>>1);
	if(l<=mid and mid>=r) return query(l,r,s,mid,ls(p));
	else if(mid+1<=r and l>mid) return query(l,r,mid+1,t,rs(p));
	else
	{
		node lll=query(l,r,s,mid,ls(p));
		node rrr=query(l,r,mid+1,t,rs(p));
		node ans=(node){lll.l+rrr.l-min(lll.l,rrr.r),lll.r+rrr.r-min(lll.l,rrr.r)};
		return ans;
	}
}
signed main()
{
	cin>>a>>n;
	int len=a.size();
	a=' '+a;
	build(1,len,1);
	while(n--)
	{
		cin>>ll>>rr;
		node s=query(ll,rr,1,len,1);
		cout<<rr-ll+1-s.l-s.r<<'\n';
	}
	return 0;
}
```

---

## 作者：RegisterFault (赞：0)

## 题意

给定括号序列，求区间最长合法括号**子序列**长度。

## 分析

对于一段括号串，将其中能匹配的都去掉，就只剩下了形如 $\texttt{)))))(((((}$ 的形式。然后发现可以将两个括号串合并，得到一个新的括号串。方法即将第一段的 $\texttt{(}$ 和第二段的 $\texttt{)}$ 一起抠掉。这个显然可以用分块 / 线段树处理一下。时间复杂度 $O(n \log n)$ 或者 $O(n \sqrt n)$。

机房有学弟问能不能分块。所以我写的是分块实现。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int N = 1000010;
const int M = 100010;
const int INF = 2e9;
int pre[M], nxt[M], n, m;
int S[N], l[N], r[N], len[N], B;
char s[N];

int get(int x) {
	return x / B;
}
int init(int L, int R, int id) {
	int a = 0, b = 0, sum = 0;
	for (int i = L; i <= R; i ++ ) {
		if (s[i] == ')') {
			if (!a) b ++ ;
			else a -- , sum ++ ;
		} else a ++ ;
	}
	pre[id] = b, nxt[id] = a;
	return sum;
}
int query(int L, int R) {
	int lc = get(L), rc = get(R);
	if (lc == rc) {
		return init(L, R, get(n) + 1);
	} int sum = 0;
	sum += init(L, r[lc], get(n) + 1);
	sum += init(l[rc], R, get(n) + 2);
	int a = pre[get(n) + 1], b = nxt[get(n) + 1];
	for (int i = lc + 1; i <= rc - 1; i ++ ) {
		sum += S[i]; sum += min(b, pre[i]);
		int tmp = pre[i]; int t = min(b, tmp);
		tmp -= t, b -= t;
		a += tmp, b += nxt[i];
	}
	sum += min(b, pre[get(n) + 2]); return sum;
}
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	scanf("%d", &m);
	B = (int)sqrt(n);
	for (int i = 0; i < M; i ++ )
		l[i] = INF, r[i] = -INF;
	for (int i = 1; i <= n; i ++ ) {
		int c = get(i); len[c] ++ , l[c] = min(l[c], i), r[c] = max(r[c], i);
	}
	for (int i = get(1); i <= get(n); i ++ )
		S[i] = init(l[i], r[i], i);
	while (m -- ) {
		int L, R; scanf("%d%d", &L, &R);
		printf("%d\n", query(L, R) << 1);
	}
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

对于这个题我们可以考虑把合法的括号序列抽出来，会剩下什么？

很显然是形如 `)))..)))(((...(((` 的串，显然如果有其他的情况可以再匹配几对。

原题完全可以理解为对于一个区间 $[l,r]$，维护抽去合法的子序列之后剩下的这种序列有 $lv$ 个左括号，$rv$ 个右括号，匹配了 $vv$ 组括号，其中必然满足 $lv+rv+2vv=r-l+1$。

如何维护？我们重载 `+` 操作表示合并两个区间的答案。`)...)(...()...)(...(` 这样的区间，必然先将中间的抽掉，即多了 $\min(rv_1,lv_2)$ 的匹配数。然后更新一下 $lv,rv$ 即可，这里可以自己手推。

具体地，原来失配的右括号有 $lv_1+lv_2$ 个，此时有匹配了 $\min(rv_1,lv_2)$ 个，故为 $lv_1+lv_2-\min(rv_1,lv_2)$。

同理，失配的左括号为 $rv_1+rv_2-\min(rv_1,lv_2)$。

统计答案显然可以使用线段树做的。

```cpp 
#define lc(id) (id<<1)
#define rc(id) (id<<1|1)
#define mid (l+r>>1)
#define ls lc(id), l, mid
#define rs rc(id), mid+1, r
const int N=3e5+5, inf=2e9;
const ll illf=1e18;
int a[N];
int qt, n, i, j, k, l, r, m;
class echi
{
public:
	int l, r, lv, rv, vv;
	bool fl;
} tr[N<<2], res, EMPTY;
char str[N];
inline const echi &operator+(const echi &x, const echi &y)
{
	if(x.fl) return y;
	if(y.fl) return x;
	int vv=min(x.rv, y.lv);
	res.vv=x.vv+y.vv+vv;
	res.l=x.l; res.r=y.r;
	res.lv=x.lv+y.lv-vv;
	res.rv=x.rv+y.rv-vv;
//	printf("%d %d %d %d %d\n", x.lv, x.rv, y.lv, y.rv, vv);
	return res;
}
inline void build(int id, int l, int r)
{
	tr[id].l=l; tr[id].r=r;
	if(l==r)
	{
		if(str[l]==')') tr[id].lv=1;
		if(str[l]=='(') tr[id].rv=1;
		return ;
	}
	build(ls); build(rs);
	tr[id]=tr[lc(id)]+tr[rc(id)];
//	printf("%d %d\n", id, tr[id].vv);
}
inline echi query(int id, int l, int r, int ql, int qr)
{
	if(r<ql || qr<l) return EMPTY;
	if(ql<=l && r<=qr) return tr[id];
	return query(ls, ql, qr)+query(rs, ql, qr);
}
int main()
{
	EMPTY.fl=true;
	scanf("%s", str+1); n=strlen(str+1);
	build(1, 1, n);
	m=read();
	while(m--)
	{
		l=read(); r=read();
		printf("%d\n", 2*query(1, 1, n, l, r).vv);
	}
}

```

---

## 作者：ABookCD (赞：0)

# CF380C Sereja and Brackets 题解

小清新线段树题。


题目大意：给定一个括号序列，有 $m$ 个询问，对于每个询问，给出一个区间，求区间最长合法括号序列。

区间询问，容易想到线段树。

显然可以发现，从左右区间答案推出当前区间答案时，需要维护左右区间内左右括号的数量，用来计算新合成的合法序列。 

所以总共要维护 $3$ 个量：

$lans,rans,ans$

其中 $lans$ 表示当前区间内含有的未匹配的左括号数量，$rans$ 同理。

$ans$ 就是当前区间的答案。

考虑 pushup 操作，新区间内 $lans$ 就是左右区间 $lans$ 之和减去匹配成功的左括号个数。$rans$ 同理。

那么怎么求在 pushup 中计算匹配成功的括号个数呢？

答案是显然的：$\min(t[ls].lans,t[rs].rans)$，即左区间左括号和右区间右括号的最小值。

所以 pushup 操作代码就很好写出：

```cpp
void pushup(int id){
	t[id].lans=t[id<<1].lans+t[id<<1|1].lans-min(t[id<<1].lans,t[id<<1|1].rans);
	t[id].rans=t[id<<1].rans+t[id<<1|1].rans-min(t[id<<1].lans,t[id<<1|1].rans);
	t[id].ans=t[id<<1].ans+t[id<<1|1].ans+min(t[id<<1].lans,t[id<<1|1].rans)*2; 
	return ;
} 
```



query 操作有一点小细节，见代码吧（看了就很好理解）。

Code:

```c++
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,lans,rans,ans;
}t[400010];
char s[400010]; 
void pushup(int id){
	t[id].lans=t[id<<1].lans+t[id<<1|1].lans-min(t[id<<1].lans,t[id<<1|1].rans);
	t[id].rans=t[id<<1].rans+t[id<<1|1].rans-min(t[id<<1].lans,t[id<<1|1].rans);
	t[id].ans=t[id<<1].ans+t[id<<1|1].ans+min(t[id<<1].lans,t[id<<1|1].rans)*2; 
	return ;
} 
void build(int id,int l,int r){
	t[id].l=l;
	t[id].r=r;
	if(l==r){
		if(s[l]=='(') t[id].lans=1;
		else t[id].rans=1;
		t[id].ans=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	pushup(id);
}
node query(int id,int x,int y){
	if(x<=t[id].l&&t[id].r<=y){
		return t[id];
	}
	int mid=(t[id].l+t[id].r)>>1;
	node l,r,u;
	if(y<=mid) return query(id<<1,x,y);
	if(x>mid) return query(id<<1|1,x,y);
	l=query(id<<1,x,y);
	r=query(id<<1|1,x,y);
	u.l=l.l;
	u.r=r.r;
	u.lans=l.lans+r.lans-min(l.lans,r.rans);
	u.rans=l.rans+r.rans-min(l.lans,r.rans);
	u.ans=l.ans+r.ans+min(l.lans,r.rans)*2; 
	return u;
}
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	build(1,1,n);
	int q;
	scanf("%d",&q);
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(1,l,r).ans);
	}
} 
```

## 后记：

这题可以用 0-1 RMQ 优化到 $O(1)$ 询问，但我不会。

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16097295.html)

线段树模板题。

# 题目分析

给定一个括号串和 $m$ 次操作，每次操作求区间 $[l,r]$ 内最长合法括号**子序列**的长度。

# 题目分析

我们可以在普通线段树上再记录两个变量 $lnum,rnum$，分别表示区间内未匹配的左括号的数量和未匹配的右括号的数量。

于是有：

```cpp
inline void pushup(int p) {
	node[p].lnum = node[lson].lnum + node[rson].lnum - min(node[lson].lnum,node[rson].rnum);
	node[p].rnum = node[lson].rnum + node[rson].rnum - min(node[lson].lnum,node[rson].rnum);
}
```

对于左括号的统计：

设一非叶子节点为 $p$，其左儿子为 $ls$，右儿子为 $rs$，那么 $lnum_p=lnum_{ls}+lnum_{rs}$，但是我们会发现，如果两个区间合并到一起，这两个区间中没有合并成功的括号可能会再次合并成功。

举个例子：$ls$ 代表的区间子串为 `()((`，$rs$ 代表的区间子串为 `))()`，那么两个区间合并在一起后会变成 `()(())()`，会发现此时没有匹配失败的括号了，所以我们应该再减去能够匹配的括号数，显然只要有两个不同方向的括号就能匹配成功，所以应减去 $\min\{lnum_{ls},rnum_{rs}\}$。

右括号的统计同理。

# 代码

```cpp
//2022/2/12
//2022/4/3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int N = 1e6 + 5;
char str[N];
int n,m;
struct Segment_Tree {
	struct Node {
		int l,r;
		int lnum,rnum;
		//lnum:左括号多余的数量,rnum:有括号多余的数量
	} node[N << 2];
	#define lson (p << 1)
	#define rson (p << 1 | 1)
	inline void pushup(int p) {
		node[p].lnum = node[lson].lnum + node[rson].lnum - min(node[lson].lnum,node[rson].rnum);
		node[p].rnum = node[lson].rnum + node[rson].rnum - min(node[lson].lnum,node[rson].rnum);
	}
	inline void build(int p,int l,int r) {
		node[p].l = l,node[p].r = r;
		if (l == r) {
			if (str[l] == '(') {
				node[p].lnum = 1,node[p].rnum = 0;
			} else {
				node[p].lnum = 0,node[p].rnum = 1;
			}
			return;
		}
		int mid = l + r >> 1;
		build(lson,l,mid),build(rson,mid + 1,r);
		pushup(p);
	}
	inline Node query(int x,int y,int p) {
		if (x <= node[p].l && node[p].r <= y) {
			return node[p];
		}
		int mid = node[p].l + node[p].r >> 1;
		if (x <= mid && mid < y) {
			Node lans = query(x,y,lson),rans = query(x,y,rson),ans;
			ans.lnum = lans.lnum + rans.lnum - min(lans.lnum,rans.rnum);
			ans.rnum = lans.rnum + rans.rnum - min(lans.lnum,rans.rnum);
			return ans;
		}
		if (x <= mid) return query(x,y,lson);
		if (y > mid) return query(x,y,rson);
	}
	inline int getans(int l,int r) {
		Node ans = query(l,r,1);
		return r - l + 1 - ans.lnum - ans.rnum;
	}
	#undef lson
	#undef rson
} seg;
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	cin >> str + 1 >> m;
	n = strlen(str + 1);
	seg.build(1,1,n);
	while (m -- ) {
		int l,r;
		cin >> l >> r;
		cout << seg.getans(l,r) << "\n";
	}

	return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：0)

[引流。](https://www.cnblogs.com/AllWeKnow/p/15367413.html)

## 题目大意

维护一段长度 $|s|\leq 10^6$ 的括号串，需要回答 $m\leq 10^5$ 次询问，每次询问给定区间 $[l,r]$，求 $[l,r]$ 的**子序列**中最长的合法括号串长度。

## 分析

考虑一个括号串的子序列中最长的合法括号串长度，不妨分别计算其中没有匹配的左括号和右括号个数。

不妨分治计算其中左半子串与右半子串中没有匹配的左括号个数和右括号个数。

显然左半子串中没有匹配的左括号可以和右半子串中没有匹配的右括号进行匹配。进行合并时减掉即可。

由于是对于一个括号串的子串进行询问，自然而然地可以想到 Segment Tree。两个区间合并的过程实际上即 pushup 的过程。

如果说的不够清楚，可以用式子表示一下。下标 $l$ 表示未匹配的左括号，$r$ 表示未匹配的右括号。

$$\begin{cases}\text{tot}_l=\text{left son}_l+\text{right son}_l-\min(\text{left son}_l,\text{right son}_r)\\\text{tot}_r=\text{left son}_r+\text{right son}_r-\min(\text{left son}_l,\text{right son}_r)\end{cases}$$

## 代码

```cpp
#include<bits/stdc++.h>
#define HohleFeuerwerke using namespace std
#pragma GCC optimize(3,"Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#define int long long
HohleFeuerwerke;
inline int read(){
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) s=s*10+c-'0';
	return s*f;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar('0'+x%10);
}
const int MAXN=1e6+5;
int n,T;
char str[MAXN];
struct node{
	int l,r;
	int lsum,rsum;
}t[MAXN*4];
inline void update(int i){
	t[i].lsum=t[i*2].lsum+t[i*2+1].lsum-min(t[i*2].lsum,t[i*2+1].rsum);
	t[i].rsum=t[i*2].rsum+t[i*2+1].rsum-min(t[i*2].lsum,t[i*2+1].rsum);
	//由于左右区间合并时不能保证每一个左半区间没有匹配的左括号都对应右边没有匹配的右括号，做减法时取的是较小值。
}
inline void build(int i,int l,int r){
	t[i].l=l,t[i].r=r;
	if(l==r){
		if(str[l]=='(') t[i].lsum=1;
		if(str[l]==')') t[i].rsum=1;
		return;
	}
	int mid=(l+r)/2;
	build(i*2,l,mid); build(i*2+1,mid+1,r);
	update(i);
}
inline node query(int i,int l,int r){
	if(t[i].l>=l&&t[i].r<=r){
		return t[i];
	}
	int mid=(t[i].l+t[i].r)/2;
	if(l>mid) return query(i*2+1,l,r);//待查区间完全在 mid 右侧
	if(r<=mid) return query(i*2,l,r);//待查区间完全在 mid 左侧
	//注意这里和普通线段树只需要有交集就查的区别
	//如果待查区间在两边内都有
	node tl=query(i*2,l,r),tr=query(i*2+1,l,r);
	node ans;
	ans.lsum=tl.lsum+tr.lsum-min(tl.lsum,tr.rsum);
	ans.rsum=tl.rsum+tr.rsum-min(tl.lsum,tr.rsum);
	//实际上即合并左右子区间
	return ans;
}
signed main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	build(1,1,n);
	T=read();
	while(T--){
		int l=read(),r=read();
		node tmp=query(1,l,r);
		write((r-l+1)-tmp.lsum-tmp.rsum);
		//所求的是匹配的子序列长度。可以用总长-没有匹配的左括号个数-没有匹配的右括号个数来计算 
		puts("");
	}
	return 0;
}
```

---

## 作者：Cylete (赞：0)

首先$[l,r]$中合法的括号串长度就等于$r - l + 1 -$ 未匹配的$'(' - $ 未匹配的$')'$

考虑线段树维护一个区间内有多少未匹配的左括号和未匹配的右括号

合并的时候减去新匹配的括号数，即：

$tl[o] = tl[lson] + tl[rson] - min(tl[lson], tr[rson])$

$tr[o] = tr[lson] + tr[rson] - min(tl[lson], tr[rson])$

其中lson为左儿子rson为右儿子

每段区间处理完后等于删掉匹配的括号，只剩下类似 $))))(((($ 的（左右括号可有可无）

```cpp
inline void into() { ios::sync_with_stdio(false); }

#define int long long
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register
#define PP pair<int, int>
#define mp(x, y) make_pair(x, y)

const int N = 1e6 + 10;

char s[N];
int n, m;
//tl未未匹配的左括号数，tr为未匹配的右括号数
int tl[N << 2], tr[N << 2];
//合并
inline void pushup(int o)
{
	tl[o] = tl[lson] + tl[rson] - min(tl[lson], tr[rson]);
	tr[o] = tr[lson] + tr[rson] - min(tl[lson], tr[rson]);
}

inline void build(int o, int l, int r)
{
	if(l == r)
	{
		if(s[l] == '(') tl[o] = 1;
		else tr[o] = 1;
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(o);
}

inline PP ask(int o, int l, int r, int ql, int qr)
{
	if(ql <= l && r <= qr) return mp(tl[o], tr[o]);
	if(qr <= mid) return ask(lson, l, mid, ql, qr);
	if(ql > mid) return ask(rson, mid + 1, r, ql, qr);
	PP ls = ask(lson, l, mid, ql, qr), rs = ask(rson, mid + 1, r, ql, qr), res;
	res.first = ls.first + rs.first - min(ls.first, rs.second);
	res.second = ls.second + rs.second - min(ls.first, rs.second);
	return res;
}

int x, y;

signed main()
{
	into();
	cin >> s + 1;
	n = strlen(s + 1);
	build(1, 1, n);
	cin >> m;
	while(m--)
	{
		cin >> x >> y;
		PP ans = ask(1, 1, n, x, y);
		cout << (y - x + 1) - ans.first - ans.second << endl;
	}
	return 0;
}
```

---

