# Flat Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abl/tasks/abl_d

数列 $ A_1,\ A_2,\ ...,\ A_N $ と整数 $ K $ が与えられます。

以下の条件を満たす数列 $ B $ の長さとして考えられる最大値を出力してください。

- $ B $ は $ A $ の (連続とは限らない) 部分列である。
- どの $ B $ の隣り合う要素の差の絶対値も $ K $ 以下である。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 300,000 $
- $ 0\ \leq\ A_i\ \leq\ 300,000 $
- $ 0\ \leq\ K\ \leq\ 300,000 $
- 入力は全て整数である。

### Sample Explanation 1

たとえば、 $ B\ =\ (1,\ 4,\ 3,\ 6,\ 9,\ 7,\ 4) $ は条件を満たします。 - これは $ A\ =\ (1,\ 5,\ 4,\ 3,\ 8,\ 6,\ 9,\ 7,\ 2,\ 4) $ の部分列です。 - 全ての隣り合う要素の差の絶対値 ($ |1-4|,\ |4-3|,\ |3-6|,\ |6-9|,\ |9-7|,\ |7-4| $) は $ K\ =\ 3 $ 以下です。

## 样例 #1

### 输入

```
10 3
1
5
4
3
8
6
9
7
2
4```

### 输出

```
7```

# 题解

## 作者：Genius_Star (赞：5)

### 思路：

考虑动态规划。

定义 $dp_i$ 表示以第 $i$ 个数结尾的最长子序列长度，则状态转移方程为：

$$dp_i=\max\limits_{j=1}^{i-1}([|a_i-a_j| \le d]dp_j+1)$$

发现不好优化，再定义以 $i$ 结尾的最长子序列长度，则状态转移为：

$$dp_i=\max\limits_{j=\max(0,a_i-d)}^{\min(5 \times 10^5,a_i+d)}(dp_j+1)$$

则线段树优化即可。

时间复杂度：$O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=500500;
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
struct Node{
	ll l,r;
	ll Max;
}X[N<<2];
ll n,d,dp[N],ans=1;
ll a[N];
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	if(l==r)
	  return ;
	ll mid=(X[k].l+X[k].r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void add(ll k,ll i,ll v){
	if(X[k].l==i&&i==X[k].r){
		X[k].Max=max(X[k].Max,v);
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  add(k<<1,i,v);
	else
	  add(k<<1|1,i,v);
	pushup(k);
}
ll qurey(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].Max;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return qurey(k<<1,l,r);
	else if(l>mid)
	  return qurey(k<<1|1,l,r);
	else
	  return max(qurey(k<<1,l,mid),qurey(k<<1|1,mid+1,r));
}
int main(){
	n=read(),d=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	build(1,0,5e5);
	dp[1]=1;
	add(1,a[1],1);
	for(int i=2;i<=n;i++){
		dp[i]=max(1ll,qurey(1,max(0ll,a[i]-d),min((ll)5e5,a[i]+d))+1);
		ans=max(ans,dp[i]);
		add(1,a[i],dp[i]);
	}
	write(ans);
	return 0;
}
```

---

## 作者：xiaomuyun (赞：5)

- [洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abl_d)
- [AtCoder 题目传送门](https://atcoder.jp/contests/abl/tasks/abl_d)

## 思路分析

数据结构优化 dp。

设 $dp_i$ 为以 **数字** $i$ 结尾的子序列的最大可能长度，则容易得出转移方程：

$$
dp_i=\Big(\max\limits_{j=a_i-k}^{a_i+k}dp_j\Big)+1
$$

答案 $r$ 即为（设 $A$ 数列最大值为 $v$）：

$$
r=\max\limits_{i=0}^v dp_i
$$

## 代码实现

注意到暴力转移的时间复杂度是 $\mathcal{O}(n^2)$ 的，无法通过 $n>10000$ 的大部分数据。因此使用线段树等数据结构优化，最多可以将暴力转移优化到 $\mathcal{O}(n\log_2 n)$。

```cpp
// Problem: D - Flat Subsequence
// URL: https://atcoder.jp/contests/abl/tasks/abl_d
// Start Time: 2023-09-04 13:43:48
// 
// Powered by CP Editor (https://cpeditor.org)

#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#define int long long
//#pragma comment(linker,"/stack:200000000")
//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
struct fio{//快读部分，请忽略。
	#define isdigit(x) (x>='0'&&x<='9')
	char buf[1<<20],*p1,pbuf[1<<20],*p2,*pp;fio():p1(buf),p2(buf),pp(pbuf){}~fio(){fwrite(pbuf,1,pp-pbuf,stdout);}
	inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++;}
	inline void pc(const char &c){if(pp-pbuf==1<<20)fwrite(pbuf,1,1<<20,stdout),pp=pbuf;*pp++=c;}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	template<class T>
	inline void read(T &x){long double tmp=1;bool sign=0;char ch=gc();x=0;for(;!isdigit(ch);ch=gc())if(ch=='-')sign=1;for(;isdigit(ch);ch=gc())x=x*10+(ch-'0');if(ch=='.')for(ch=gc();isdigit(ch);ch=gc())tmp/=10.0,x+=tmp*(ch-'0');if(sign)x=-x;}
	inline void read(char *s){char ch=gc();for(;blank(ch);ch=gc());for(;!blank(ch);ch=gc())*s++=ch;*s=0;}
	inline void read(char &c){for(c=gc();blank(c);c=gc());}
	template<class T>
	inline void write(T x){if(x<0)x=-x,pc('-');int sta[30];int top=0;do sta[top++]=x%10,x/=10;while(x);while(top)pc(sta[--top]+'0');}
}io;
#define read io.read
#define write io.write
#define gc io.gc
#define pc io.pc
#define endn pc(' ')
#define endl pc('\n')
#define inf 0x3f3f3f3f
#define inff 0x3f3f3f3f3f3f3f3f
#define mod 998244353
#define mod2 1000000007
const int maxn=3e5+2;
int n,k,a[maxn],t[maxn*4],mx,res=1;
void update(int o,int l,int r,int x,int v){//使用的数据结构我推荐线段树或者分块，这里使用的是线段树。
	if(l==r){
		t[o]=max(t[o],v);
		return ;
	}
	int mid=l+(r-l)/2;
	if(x<=mid) update(o*2,l,mid,x,v);
	else update(o*2+1,mid+1,r,x,v);
	t[o]=max(t[o*2],t[o*2+1]);
	return ;
}
int query(int o,int l,int r,int x,int y){
	if(y<l||r<x) return 0;
	if(x<=l&&r<=y) return t[o];
	int mid=l+(r-l)/2;
	return max(query(o*2,l,mid,x,y),query(o*2+1,mid+1,r,x,y));
}
signed main(){
	// ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	read(n),read(k);
	for(int i=1;i<=n;++i){
		read(a[i]);
		mx=max(a[i],mx);//预处理出数列的最大值。
	}
	for(int i=1;i<=n;++i){
		if(i==1){
			update(1,0,mx,a[1],1);
			continue;
		}
		int cur=query(1,0,mx,max(0ll,a[i]-k),min(mx,a[i]+k))+1;
		//将查询出来的结果加一即为 dp[i] 的值。
		res=max(cur,res);
		update(1,0,mx,a[i],cur);//记得再次丢进线段树，方便下次查询。
	}
	write(res),endl;
	return 0;
}
```

---

## 作者：Milthm (赞：2)

这是 abc339_e 的原题，甚至代码不用改就能 AC……

注：以下称 $a$ 序列为 $b$。

_____



看到这个最长子序列，就很容易想到动态规划。

所以我们设 $dp_i$ 表示前 $i$ 个数相邻两数绝对差不超过 $d$ 的最长子序列。设 $k_i$ 表示目前所有 $dp_j(j<i)$ 中 $b_j$ 值与 $b_i$ 绝对差不超过 $d$ 的最大值，则 $dp_i=k_i+1$。

这东西直接转移是 $O(n^2)$ 的，显然会超时。

考虑你有一个数组，此时如果当前 $dp_i$ 值转移完了，你就把它的值放到数组第 $b_i$ 个位置（与原来的数取最大值）。然后每次 $k_i$ 实际上就是数组上 $b_i-d$ 至 $b_i+d$ 之间的最大值。

你观察这个过程，发现可以用线段树优化（你甚至不需要建树）。时间复杂度 $O(n \log n)$。

### AC code

实现的时候 $b_i-d$ 要判越界。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
int n,d,b[N],dp[N],ans,a[N*4];
void update(int x,int l,int r,int k,int qwq){
	if(l==r){
		a[x]=max(a[x],qwq);return;
	}
	int mid=(l+r)>>1;
	if(k<=mid)update(x*2,l,mid,k,qwq);
	else update(x*2+1,mid+1,r,k,qwq);
	a[x]=max(a[x*2],a[x*2+1]);
}
int query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return a[x];
	int mid=(l+r)>>1,ans=0;
	if(ql<=mid)ans=max(ans,query(x*2,l,mid,ql,qr));
	if(qr>mid)ans=max(ans,query(x*2+1,mid+1,r,ql,qr));
	return ans;
} 
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;++i)scanf("%lld",&b[i]);
	for(int i=1;i<=n;++i){
		dp[i]=query(1,1,N-4,max(1ll,b[i]-d),b[i]+d)+1;
		update(1,1,N-4,b[i],dp[i]);ans=max(ans,dp[i]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：SkyWave (赞：1)

# 思路

首先考虑 $O(n^2)$ dp。设 $f[i]$ 以 $i$ 结尾的最长合法子序列的长度。于是很自然列出转移方程为 $f[i] = \max\{[i < j \wedge \lvert a[i] - a[j] \rvert \le k] \times f[j] + 1\}$。接下来我们就想怎么优化这个式子。

诶也先别急着一步优化成复杂度正确。我们想一下，如果它是一道 OI 题，出题人是不是有可能放一个值域做法部分分？我们尝试思考一下 $O(nk)$ 的 dp 怎么做。我们在从左往右做的过程中，设 $g[i]$ 为使得 $a[p] = i$ 的 $f[p]$ 的最大值，那么 $f[i] = \max([j\in[a[i] - k, a[i] + k]] \times g[j] + 1)$，之后再用 $f[i]$ 试着更新 $g[a[i]]$ 即可。但因为如果序列中有两个数相同，那么后出现的一定能拼在前面那个数的后面，所以必定更优，直接赋值即可。从左往右做的过程中自然保证了 $i < j$，所以限制条件都满足，正确。时间复杂度为 $O(nk)$。

我们再想一下 $O(nk)$ 中解法我们在干一件什么事。$f[i] = \max([j\in[a[i] - k, a[i] + k]] \times g[j] + 1)$，也就是查询一个 $g$ 一段区间的最大值。$g[a[i]] = f[i]$，也就是单点修改。

区间最大值，单点修改，我们想到什么？没错！这道题现在就被我们转换成了一道比较基础的线段树运用来优化 dp，lazytag 都用不到。每次查询一次最大值再单点修改，时间复杂度为 $O(n \log k)$。

# 代码

提供一个很简单的实现

```cpp
#include <iostream>
using namespace std;

const int V = 3e5;

int tree[(V + 1) << 2];
inline void pushup(int pos) {
    tree[pos] = max(tree[pos << 1], tree[pos << 1 | 1]);
}
void pointModify(int x, int v, int l = 0, int r = V, int pos = 1) {
    if (l == r) {
        tree[pos] = max(tree[pos], v);
        return ;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
        pointModify(x, v, l, mid, pos << 1);
    } else {
        pointModify(x, v, mid + 1, r, pos << 1 | 1);
    }
    pushup(pos);
}
int rangeMax(int x, int y, int l = 0, int r = V, int pos = 1) {
    if (x <= l && r <= y) {
        return tree[pos];
    }
    int res = 0;
    int mid = (l + r) >> 1;
    if (x <= mid) {
        res = max(res, rangeMax(x, y, l, mid, pos << 1));
    }
    if (y >= mid + 1) {
        res = max(res, rangeMax(x, y, mid + 1, r, pos << 1 | 1));
    }
    return res;
}

int main(int argc, const char * argv[]) {
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        pointModify(x, 1 + rangeMax(max(0, x - d), min(x + d, V)));//实际上用不到 a 和 dp 数组，线段树上面就存了以前状态的信息
    }
    printf("%d\n", rangeMax(0, V));
    return 0;
}

```

---

## 作者：stripe_python (赞：1)

线段树优化 DP 的板子。

# 题意
给定一个数列，求出它最长的子序列，满足相邻元素之差不大于 $k$。

# 分析

对于这类最长子序列的题目，有一个 DP 套路，设 $dp_i$ 表示以 $a_i$ 结尾的最长合法子序列长度，则有

$$
dp_i=\max_{j=1}^{j<i} dp_j+1
$$

其中，$|a_i-a_j| \le k$。

Code：

```cpp
#include <bits/stdc++.h>
#define N 300005
using namespace std;

int n, k, a[N], dp[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k; for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (abs(a[i] - a[j]) <= k) dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    cout << *max_element(dp + 1, dp + n + 1);
    return 0;
}
```

喜提 [TLE](https://www.luogu.com.cn/record/146153252)。

显然，上述思路的复杂度为 $O(n^2)$，考虑优化。

考虑下面的过程：

```cpp
for (int j = 1; j < i; j++) {
    if (abs(a[i] - a[j]) <= k) dp[i] = max(dp[i], dp[j] + 1);
}
```

什么样的 $j$ 可以转移呢？

当且仅当 $a_j \in [a_i-k, a_i+k]$ 时，可以进行转移。此时，题目被转化成了一个 RMQ 问题，需要单点修改，区间查询最值，想到线段树。

AC Code 如下，注意边界条件。

```cpp
#include <bits/stdc++.h>
#define N 300005
using namespace std;

int n, k, a[N];

template <class T>
class SegmentTree {
#define ls (rt << 1)
#define rs (rt << 1 | 1)
private:
    int n;
    T maxn[(N << 2) + 1];
    
    void pushup(int rt) {
        maxn[rt] = max(maxn[ls], maxn[rs]);
    }
    
    void build(int l, int r, int rt) {
        if (l == r) return (void) (maxn[rt] = 0);
        int mid = (l + r) >> 1;
        build(l, mid, ls), build(mid + 1, r, rs);
        pushup(rt);
    }
    
    void update(int i, const T c, int l, int r, int rt) {
        if (l == r) return (void) (maxn[rt] = max(maxn[rt], c));
        int mid = (l + r) >> 1;
        if (i <= mid) update(i, c, l, mid, ls);
        else update(i, c, mid + 1, r, rs);
        pushup(rt);
    }
    
    T query(int tl, int tr, int l, int r, int rt) {
        if (tl <= l && r <= tr) return maxn[rt];
        int mid = (l + r) >> 1; T res(0);
        if (tl <= mid) res = max(res, query(tl, tr, l, mid, ls));
        if (tr > mid) res = max(res, query(tl, tr, mid + 1, r, rs));
        return res;
    }
    
public:
    explicit SegmentTree(int _n) : n(_n) {build(1, n, 1);}
    void update(int i, const T c) {update(i, c, 1, n, 1);}
    T query(int l, int r) {return query(l, r, 1, n, 1);}
    
#undef ls
#undef rs
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k; for (int i = 1; i <= n; i++) cin >> a[i];
    int m = *max_element(a + 1, a + n + 1);
    SegmentTree<int> sgt(m);
    for (int i = 1; i <= n; i++) {
        sgt.update(a[i], sgt.query(max(1, a[i] - k), min(m, a[i] + k)) + 1);
    }
    cout << sgt.query(0, m);
    return 0;
}
```

线段树优化后，复杂度为 $O(n \log w)$，其中 $w$ 是 $a_i$ 的值域。可以通过本题。

---

## 作者：冷却心 (赞：1)

## 题意

给定长度为 $N$ 的序列 $A_1, A_2, \cdots,A_n$ 和整数 $K$。

问 最长能满足如下要求的序列 $B$ 的长度为多少。

- $B$ 是 $A$ 的子序列。

- $B$ 中任意两个相邻元素之差不大于 $K$。

## 解法

显然的，这是一个 LIS 问题的变形，把最长上升子序列的判断条件改为相邻元素差不大于 $K$。

状态 $dp_i$ 表示以 $A_i$ 结尾的满足要求的子序列最长的长度。

$dp_i$ 初始为 $1$。（就它自己一个元素）。

转移方程：如果 $j < i$ 且 $\left|A_i - A_j\right| \leq K$，则 $dp_i = \max(dp_i,dp_j + 1)$。

时间复杂度： $O(n^2)$。

如下代码：

```cpp
for (LL i = 1; i <= n; i ++){
	LL res = 0;
	for (LL j = 1; j < i; j ++)
		if (abs(A[i] - A[j]) <= K)
			res = max(res, dp[j]);
	dp[i] = res + 1;
	ans = max(ans, dp[i]);
}
```

但是 $n \leq 300000$，会 TLE。

考虑优化。

可发现 $0 \leq A_i \leq 300000$。

又可发现上述代码中：

```
for (LL j = 1; j < i; j ++)
	if (abs(A[i] - A[j]) <= K)
		res = max(res, dp[j]);
```

这一块就是一个 RMQ，求 $[A_i-K,A_i+K]$ 中 $dp_j$ 的最值。

可以用线段树优化 RMQ。

每次只要 `query` 一下 $[A_i-K,A_i+K]$ 中的最值即可。

最后在单点修改 $A_i$ 这个位置的元素 为 $dp_i$。
**要注意单点修改不是赋值，而是取最大值，可能有重复元素且比它大。**

还要注意值域的上界和下界，$A_i+K$ 可能大于 $300000$，$A_i-K$ 也可能 小于 $0$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define Fcin \
	ios :: sync_with_stdio(0);\
	cin.tie(0);cout.tie(0);
const LL N = 3e5 + 10;
const LL M = 300000;
LL n, K, A[N], dp[N], tree[(M + 10) * 4], ans = 0;

void pushup(LL p){
	tree[p] = max(tree[ls(p)], tree[rs(p)]);
	return ;
}

void build(LL p, LL l, LL r){
	if (l == r){
		tree[p] = 0;
		return ;
	}
	LL mid = (l + r) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	pushup(p);
	return ;
}

void update(LL p, LL l, LL r, LL x, LL k){
	if (l == r){
		tree[p] = max(tree[p], k);
		return ;
	}
	LL mid = (l + r) >> 1;
	if (x <= mid)
		update(ls(p), l, mid, x, k);
	else
		update(rs(p), mid + 1, r, x, k);
	pushup(p);
	return ;
}

LL query(LL p, LL l, LL r, LL x, LL y){
	if (x <= l && y >= r)
		return tree[p];
	LL mid = (l + r) >> 1, res = 0;
	if (x <= mid)
		res = max(res, query(ls(p), l, mid, x, y));
	if (y >= mid + 1)
		res = max(res, query(rs(p), mid + 1, r, x, y));
	return res;
}

int main(){
	Fcin;
	cin >> n >> K;
	for (LL i = 1; i <= n; i ++)
		cin >> A[i];
	build(1, 0, M);
	for (LL i = 1; i <= n; i ++){
		LL L = max(0LL, A[i] - K), R = min(M, A[i] + K);
		LL res = query(1, 0, M, L, R);
		dp[i] = res + 1;
		update(1, 0, M, A[i], dp[i]);
		ans = max(ans, dp[i]);
	}
	cout << ans;
	return 0;
}


```



---

## 作者：hhhppp (赞：0)

## 简述题意

给定序列 $A$，求出序列 $A$ 的子序列中，相邻数的差的绝对值小于等于 $k$ 的子序列的最大的长度。

## 思路

可以考虑动态规划。

对于每个 $dp_i$，我们定义 $dp_i$ 为以 $a_i$ 为结尾的最长的合法的子序列的长度，可得转移方程为 
$$
dp _i=\max_{j=min(1,a_i-k)}^{max(5×10^5,a_i+k)}dp_j+1
$$

可以发现，需要重复取最大值，可以考虑用权值线段树优化。

遍历时注意考虑上下界，下界不能为负数，上界不能超过 $5×10^5$。



## 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define le p<<1
#define ri (p<<1)|1
#define N 500000
#define int long long 
using namespace std;
int n,d,a[N+10],dp[N+10],ans;
struct tree{
	int l,r,maxn;
}t[N*4];
void tree_build(int p,int lf,int rt){
	t[p].l=lf;
	t[p].r=rt;
	if(lf==rt){
		return ;
	}
	int mid=(lf+rt)>>1;
	tree_build(le,lf,mid);
	tree_build(ri,mid+1,rt);
}
void tree_up(int p){
	t[p].maxn=max(t[le].maxn,t[ri].maxn);
}
void tree_update(int p,int x,int k){
	if(t[p].l==t[p].r&&t[p].l==x){
		t[p].maxn=max(t[p].maxn,k);
		return ;
	}
	int mid=(t[p].l+t[p].r)>>1;
	if(x<=mid) tree_update(le,x,k);
	else tree_update(ri,x,k);
	tree_up(p);
}
int tree_find(int p,int x,int y){
	if(x<=t[p].l&&t[p].r<=y){
		return t[p].maxn;
	}
	int mid=(t[p].l+t[p].r)>>1,imax=-1;
	if(x<=mid) imax=max(imax,tree_find(le,x,y));
	if(mid<y) imax=max(imax,tree_find(ri,x,y));
	return imax;
}
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	tree_build(1,1,N);
	for(int i=1;i<=n;i++){
		int l=a[i]-d,r=a[i]+d;
		if(l<=0) l=1;
		if(r>500000) r=500000;//上下界问题 
		dp[i]=max(dp[i],tree_find(1,l,r)+1);
		tree_update(1,a[i],dp[i]);//每次查询后要更新最大值，保证最后结果是正确的 
		ans=max(ans,dp[i]);
	}
	cout<<tree_find(1,1,N)<<endl;
	return 0;//完美结束 QAQ 
}
```

---

## 作者：zhujiangyuan (赞：0)

[Flat Subsequence](https://www.luogu.com.cn/problem/AT_abl_d)

首先很快想到一个 $O(n^2)$ 的 DP：

状态：设 $dp_i$ 为以 $a_i$ 为结尾的子序列的最大长度。

转移：若 $\left|a_i-a_j\le d\right|$，$dp_i=\max (dp_i,dp_j+1)$。

答案：$\max\limits_{i=1}^{n}dp_i$。

但是 $O(n^2)$ 的复杂度接受不了，考虑线段树优化 DP。使用权值线段树，下标为 $a_i$ 的值。查找 $a_i - d \sim a_i + d$ 之间 $dp$ 的最大值，然后更新即可。

时间复杂度 $O(n\log V)$，$V$ 为值域。

```cpp
// by zhujiangyuan 2024/4/16 
#include <bits/stdc++.h>
#define lowbit(x) x & -x
using namespace std;
typedef long long LL;
const int N = 5e5;
int n, d, a[N + 10];
struct Seg {
	int dat;
	#define dat(p) t[p].dat
	#define ls p << 1
	#define rs p << 1 | 1
}t[N * 4];
int query (int p, int l, int r, int L, int R) {
	if (L <= l && r <= R) return dat(p);
	int mid = (l + r) >> 1, res = 0;
	if (L <= mid) res = max (res, query (ls, l, mid, L, R));
	if (mid < R) res = max (res, query (rs, mid + 1, r, L, R));
	return res;
}
void modify (int p, int l, int r, int pos, int val) {
	if (l == r) { dat(p) = max (dat(p), val); return ;}
	int mid = (l + r) >> 1;
	if (pos <= mid) modify (ls, l, mid, pos, val);
	else modify (rs, mid + 1, r, pos, val);
	dat(p) = max (dat(ls), dat(rs));
}
int main()
{
//	freopen("lost.in", "r", stdin);
//	freopen("lost.out", "w", stdout);
	scanf("%d %d", &n, &d);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		int maxx = query (1, 1, N, max (a[i] - d, 1), min (a[i] + d, N));
		modify (1, 1, N, a[i], maxx + 1);
	}
	printf("%d", query(1, 1, N, 1, N));
	return 0;
}
```

upd 2024/4/18：感谢@[shangruolin](https://www.luogu.com.cn/user/774344)提醒，改正了代码中的一处不必要的地方，重新提交审核。

---

## 作者：LaoXu666 (赞：0)

这题很容易想得到 DP。

很容易想出暴力的转移方程：$f_i \gets \displaystyle \max f_j + 1 (0 \leqslant j < i,|a_j - a_i| \leqslant D)$ 

数据范围很大，这个 DP 的复杂度是 $\Theta(N^2)$ 的，肯定 TLE。

我们可以想到用线段树优化。

首先，因为转移方程是跟 $a_i$ 有关的，所以线段树编辑的时候可以用 $a_i$。然后，求最大值区间为 $[a_i -D, a_i+D]$。

现在就可以写出代码：

```cpp
#include <iostream>

typedef int LL;

class SegmentTree {
public:
	LL Max[2000005];

	void Edit(LL NodeId, LL L, LL R, LL Pos, LL Val) {
		if (L == R) {
			Max[NodeId] = std::max(Max[NodeId], Val);
			return;
		}
		LL Mid = (L + R) / 2;
		if (Pos <= Mid) {
			Edit(NodeId * 2, L, Mid, Pos, Val);
		} else {
			Edit(NodeId * 2 + 1, Mid + 1, R, Pos, Val);
		}
		Max[NodeId] = std::max(Max[NodeId * 2], Max[NodeId * 2 + 1]);
	}

	LL GetMax(LL NodeId, LL L, LL R, LL QueryL, LL QueryR) {
		if (QueryL <= L && R <= QueryR) {
			return Max[NodeId];
		}
		if (QueryL > R || QueryR < L) return 0;
		LL Mid = (L + R) / 2;
		return std::max(GetMax(NodeId * 2, L, Mid, QueryL, QueryR),
						GetMax(NodeId * 2 + 1, Mid + 1, R, QueryL, QueryR));
	}
} ABC339E;

int N, D;
int Arr[500005], DP[500005];

int main() {
	std::cin >> N >> D;
	for (int i = 1; i <= N; i++) std::cin >> Arr[i];
	int Res = 0;
	for (int i = 1; i <= N; i++) {
		DP[i] = ABC339E.GetMax(1, 1, 500000, std::max(Arr[i] - D, 1), std::min(Arr[i] + D, 500000)) + 1;
		ABC339E.Edit(1, 1, 500000, Arr[i], DP[i]);
		Res = std::max(Res, DP[i]);
	}
	std::cout << Res << '\n';
	return 0;
}

```

---

## 作者：Loser_Syx (赞：0)

对于每个 $a_i$，我们所接受的上一个 $a_j$ 的范围在 $[a_i-d,a_i+d]$ 之间，发现是一段连续的区间，而我们需要求出 $dp_{j}$ 的最大值以转移 $dp_i$，于是考虑值域线段树维护 $a_j$，以 $dp_{j}$ 作为值存储，每次查询区间的最大值转移即可。

[代码](https://atcoder.jp/contests/abl/submissions/50027550)。

---

## 作者：T_TLucas_Yin (赞：0)

首先很容易想到暴力的 dp 做法，即对于每个位置，找到它之前的元素中，与它差的绝对值不超过 $K$ 的那些，取以它们结尾的最长子序列中长度最长的 $+1$，就是以该元素结尾的最长子序列。最后再遍历一遍所有元素，取最大值。

但是该方法用时是 $O(n^2)$，无法通过此题的大数据。所以考虑优化。我们发现输入、输出、遍历每个元素计算的复杂度都是 $O(n)$ 的，而从每个元素向前查找的操作却耽误了大量时间。如何把查找操作优化呢？我们发现，此题中每次查找的本质就是找 $a_i$ 前面在 $[a_i-K,a_i+K]$ 范围内的元素中，所得子序列长度的最大值。这其实就是一个区间查找。

我们可以建一棵线段树（其实是值域线段树），每个节点存储值域在 $[l,r]$ 范围内的元素所得区间长度最大值。这样就可以把查找操作优化到 $O(\log n)$。计算完每个节点后，再把该节点得到的最大值存入线段树中更新，然后计算下一个节点。最后依旧是遍历一遍输出结果。

感觉比其他题解浅显易懂些，希望给过 QWQ。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],f[1000005],t[4000005];//t是线段树。一定记得多开几倍
int Find(int root,int l,int r,int fl,int fr){//正常的查找操作，只不过区间是值域
	if(fl<=l&&r<=fr) return t[root];
	int mid=(l+r)>>1,maxn=0;
	if(fl<=mid) maxn=max(maxn,Find(root<<1,l,mid,fl,fr));
	if(fr>mid) maxn=max(maxn,Find(root<<1|1,mid+1,r,fl,fr));
	return maxn;
}
void build(int root,int l,int r,int k,int x){//将节点放入树中，还是跟模板一样
	if(l==r){
		t[root]=max(t[root],x);
		return;
	}
	int mid=(l+r)>>1;
	if(k<=mid) build(root<<1,l,mid,k,x);
	else build(root<<1|1,mid+1,r,k,x);
	t[root]=max(t[root<<1],t[root<<1|1]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		f[i]=Find(1,1,1000001,max(1,a[i]-m),a[i]+m)+1;
		build(1,1,1000001,a[i],f[i]);//先找再放
		
	}
	int maxn=0;
	for(int i=1;i<=n;i++) maxn=max(maxn,f[i]);//遍历一遍
	cout<<maxn;
	return 0;
}
```

---

## 作者：apiad (赞：0)

竟然是 ABC339E 原题，并且，这是一个黄！不可思议！

我们可以想到 Dp 策略 $dp_i$ 代表的是到 $i$ 这个下标，可以构造的最大长度，很显然这是 $O(n^2)$ 时间复杂度，当然过不去。考虑如何优化？

我们又发现了 $a_i$ 的值是 $10^5$ 级别。所以是不是可以存下来每一个值的一些信息呢？

我们有发现，这个 $i$ 点肯定是从 $a_i - d$ 到 $a_i + d$ 这个值范围内结尾的子序列才能拼上这个点，那我们是不是可以直接查询这个区间内每一个值作为子序列最长的多少呢？那么我们直接搬出线段树，区间修改最大值和单点查询即可。

我们找到这个区间内最大的子序列长度，然后加一拼在这里，继续维护线段树。

好题！

不，典题！

啊？原题！

要是不是重了那还不错的。

其实只需要给出主函数里的，线段树大家都有板子。

```cpp
void solve(){
	cin >> n >> k;
	for(int i =1;i<=n;i++)cin>>a[i];
	build(1,1,N-3);
	for(int i = 1;i <= n;i++){
		int tmp = query(1,max(0ll,a[i]-k),a[i]+k);//区间查询。
		dp[i]=tmp+1;
		modify(1,a[i],dp[i])//单点修改
		ans=max(ans,dp[i]);
	}cout<<ans;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

线段树模板题。

一眼 DP。定义状态函数 $\mathit{f}_i$ 表示前 $i$ 个数中，必选 $\mathit{A}_i$ 时 $B$ 的最大长度。则有转移方程：$\mathit{f}_i=\max\{f_j |((1\le j \le i-1 )\land (-k \le A_i-A_j \le k))\}+1$。答案就是 $\max\limits_{i=1}^{n} \mathit{f}_i$。

很显然暴力枚举 $j$ 的复杂度是 $O(n^2)$ 的，考虑优化。使用线段树维护区间 $[A_i-k,A_i+k]$ 的最大 $f$ 的值。在转移 $\mathit{f}_i$ 的时候一定能保证找出来的这个最大值是在 $\mathit{f}_1$ 到 $\mathit{f}_{i-1}$ 中出现过的（$0$ 除外）。这个的复杂度是 $O(n\log n)$，能过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

const int N=3e5+10,inf=3e5;
int n,k,a[N];
int f[N],ans;
struct node{
	int l,r,mx;
}tr[(inf|1)<<2];

il void up(int now){tr[now].mx=max(tr[now<<1].mx,tr[now<<1|1].mx);}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) return ;
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
}
il void insert(int now,int x,int k){
	if(tr[now].l==tr[now].r) tr[now].mx=max(tr[now].mx,k);
	else{
		int mid=tr[now].l+tr[now].r>>1;
		if(x<=mid) insert(now<<1,x,k);
		else insert(now<<1|1,x,k);
		up(now);
	}
}
il int query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now].mx;
	int maxx=0,mid=tr[now].l+tr[now].r>>1;
	if(l<=mid) maxx=max(maxx,query(now<<1,l,r));
	if(mid<r) maxx=max(maxx,query(now<<1|1,l,r));
	return maxx;
}

il void solve(){
	cin>>n>>k;
	for(re int i=1;i<=n;++i) cin>>a[i];
	build(1,0,inf);
	for(re int i=1;i<=n;++i){
		f[i]=query(1,max(0LL,a[i]-k),min(inf,a[i]+k))+1;
		insert(1,a[i],f[i]),ans=max(ans,f[i]);
	}
	cout<<ans;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：lkjzyd20 (赞：0)

## 思路

一道线段树优化 dp 题。

设 $dp_i$ 表示以第 $i$ 个数字结尾的最长选数列长度，则 $dp_i=\max(dp_i, dp_j)+1$，其中 $j<i$ 且 $| a_i-a_j | \leq K$。 

时间复杂度为 $O(n^2)$。

代码如下：

```cpp
int ans = 0;
rep(i, 1, n)
{
    dp[i] = 1;
    rep(j, 1, i - 1)
        if(abs(a[i] - a[j]) <= k)
            dp[i] = max(dp[i], dp[j] + 1);
    ans = max(ans, dp[i]);
}
cout << ans << endl;
```


但是 $n \leq 300000$，会 **TLE**，考虑优化。

又可发现上述代码中：

```cpp
rep(j, 1, i - 1)
    if(abs(a[i] - a[j]) <= k)
        dp[i] = max(dp[i], dp[j] + 1);
```
这不就是求 $a_i-k,a_i+k$ 之间的最值呀！

可以用线段树来进行维护，最后记得修改 $dp_i$ 的值即可。

## 代码如下

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
#define me0(a); memset(a, 0, sizeof a);
#define me3(a); memset(a, 0x3f, sizeof a);
#define PII pair<int, int>

const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;

inline void read(int &n)
{
    bool w = 0;
    char c = getchar();
    for(; c < 48 || c > 57; c = getchar())
        w = c == 45;
    for(n = 0; c >= 48 && c <= 57; c = getchar())
        n = n * 10 + c - 48;
    n = w ? -n : n;
}

inline void write(int x, char a)
{
    char c[40], s = 0;
    if(x < 0) putchar(45), x = -x;
    for(; x ;) c[s ++] = x % 10, x /= 10;
    if(!s) putchar(48);
    for(; s -- ;) putchar(c[s] + 48);
    putchar(a);
}

const int MAXN = 300001, M = 300000;
#define ls num + num
#define rs num + num + 1
int sum[MAXN << 2], p[MAXN], addans = -INF;
void update(int num) {sum[num] = max(sum[ls] , sum[rs]);}
void ask(int num, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		addans = max(addans, sum[num]);
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= x) ask(ls, l, mid, x, y);
	if(mid < y) ask(rs, mid + 1, r, x, y);
}
void change(int num, int l, int r, int pos, int val)
{
	if(l == r)
	{
		sum[num] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) change(ls, l, mid, pos, val);
	else change(rs, mid + 1, r, pos, val);
	update(num);
}
int n, k, ans;
int dp[MAXN];
int a[MAXN];
main()
{
    read(n); read(k);
    rep(i, 1, n) read(a[i]);
    rep(i, 1, n)
	{
		int L = max(0ll, a[i] - k), R = min(M, a[i] + k);
        ask(1, 0, M, L, R);
		dp[i] = addans + 1;
		change(1, 0, M, a[i], dp[i]);
		ans = max(ans, dp[i]);
        addans = -INF;
	}
	cout << ans;
}
```

---

