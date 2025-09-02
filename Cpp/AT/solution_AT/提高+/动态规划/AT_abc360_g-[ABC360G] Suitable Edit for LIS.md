# [ABC360G] Suitable Edit for LIS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc360/tasks/abc360_g

長さ $ N $ の整数列 $ A $ が与えられます。高橋くんは、 $ 1 $ 回だけ次の操作をします。

- $ 1 $ 以上 $ N $ 以下の整数 $ x $ と、任意の整数 $ y $ を選ぶ。$ A_x $ を $ y $ に置き換える。
 
操作をした後の $ A $ の最長増加部分列の長さとしてあり得る最大の値を求めてください。

  最長増加部分列とは？ 列 $ A $ の部分列とは $ A $ の要素をいくつか抜き出して元の順に並べてできる列を指します。

 列 $ A $ の最長増加部分列とは、 $ A $ の狭義単調増加な部分列のうち列の長さが最大のものを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
 
### Sample Explanation 1

与えられた数列 $ A $ の LIS の長さは $ 2 $ です。例えば $ A_1 $ を $ 1 $ に置き換えると、操作後の $ A $ の LIS の長さが $ 3 $ になり、これが最大です。

## 样例 #1

### 输入

```
4
3 2 2 4```

### 输出

```
3```

## 样例 #2

### 输入

```
5
4 5 3 6 7```

### 输出

```
4```

# 题解

## 作者：Halberd_Cease (赞：9)

不用数据结构维护的做法。

考虑对二分求 LIS 的方法进行改造。

如果你不会二分求 LIS，请[自行搜索](https://www.bing.com/search?q=%E6%9C%80%E9%95%BF%E4%B8%8A%E5%8D%87%E5%AD%90%E5%BA%8F%E5%88%97&FORM=ANNTA1&PC=PCMEDGEDP)。

我们维护两个数组 $f1_i$ 和 $f2_i$ 分别表示当前修改了/没修改 $A_i$ 的值，长度为 $i$ 的最长上升子序列末尾数字最小的值。

两个数组直接加入数的操作是简单的，我们考虑对于每一个位置如何将 $f2$ 用 $f1$ 进行修改。在枚举每一位的时候，我们都可以选择将这一位变成任何数（没有操作过时），显然应该将当前位变成 $f1$ 中最长上升子序列末尾的最小值 $+1$，这样可以得到上升子序列长度 $+1$，并且贪心来说，使当前长度的末位最小。

考虑更新的顺序，对于每一位时，先将 $f1$ 最长上升子序列的长度和末尾最小值取出放入辅助变量，然后分别更新 $f1$ 和 $f2$，此举是为了防止互相更新。最后再用刚取出的值更新 $f2$。

由于 $f1$ 最长上升子序列长度最多比 $f2$ 少 $1$，因此需要更新 $f2$ 的长度一定是 $f2$ 的长度或者 $f2$ 的长度 $+1$，又因为 $f1$ 的每一位必定严格不小于 $f2$，所以每次更新后的 $f2$ 数组依然满足单调性。

[submission](https://atcoder.jp/contests/abc360/submissions/55126126)，代码很短，不压行的情况下不到 1KB。

---

## 作者：Milthm (赞：6)

开幕先致敬一下经典：

![](https://cdn.luogu.com.cn/upload/image_hosting/ivgq0yoz.png)

时隔高达 $6$ 场 abc，LIS 问题它又回来了！

感觉和 E 差不多难吧，虽然我赛时没做。
_____

这种题先求两个东西，就是以 $i$ 为起点的 LIS 长度和以 $i$ 为终点的 LIS 长度，分别记为 $L_i$ 和 $R_i$。这部分可以用树状数组求出，具体可看我的 SP57 [题解](https://www.luogu.com.cn/article/ebs8w5k0)。

然后考虑枚举修改第 $i$ 个位置，则第 $i$ 次修改后包含 $a_i$ 的 LIS 最长为：

$$L_{i+1}+\max_{1\le j<i,a_j+2\le a_{i+1}}\{R_j\}+1$$

然后对于每个 $i$ 取这个式子最大值就行了。但是要注意的是你还要特判前面或后面不取 LIS 的情况，这一点在求出 $L_i,R_i$ 的时候就可以解决掉。

以及，直接做是 $O(n^2)$ 的，所以还是考虑用树状数组进行优化，就可以通过了。

然而，普通的实现方式需要进行复杂的离散化，且可能需要多判断一些东西，所以我们可以用 `unordered_map` 充当树状数组，不离散化直接做。然后再分析一下这样做的复杂度：

时间复杂度：如果你把 `unordered_map` 的复杂度视为常数的话，时间复杂度是 $O(n\log a_i)$。

空间复杂度：每次最多在哈希表上多产生 $O(\log a_i)$ 的节点，所以空间复杂度也是 $O(n\log a_i)$。

综上，这种算法可以通过本题。

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
const int inf=1e9+7;
unordered_map<int,int>c;
int n,a[N],l[N],r[N],ans;
void add(int x,int k){
	while(x<=inf){
		c[x]=max(c[x],k);x+=x&-x;
	}
}
int ask(int x){
	int ans=0;
	while(x){
		ans=max(ans,c[x]);x-=x&-x;
	}
	return ans;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i){
		r[i]=ask(a[i]-1)+1;
		add(a[i],r[i]);
		ans=max(ans,r[i]+(i!=n));
	}
	c.clear();
	for(int i=n;i>=1;--i){
		l[i]=ask(inf-a[i]-1)+1;
		add(inf-a[i],l[i]);
		ans=max(ans,l[i]+(i!=1));
	}
	c.clear();
	for(int i=1;i<=n;++i){
		int k=ask(a[i+1]);
		ans=max(ans,l[i+1]+k+1);
		add(a[i]+2,r[i]);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：汪汪队队长1 (赞：5)

我的思路有点复杂，但我觉得应该更容易想到。

先考虑 dp 做法：

$dp[i][0]$ 表示最后一位是 $a[i]$ 的 LIS 中**不包含**修改的数字的最长长度，$dp[i][1]$ 表示最后一位是 $a[i]$ 的  LIS 中**包含**修改的数字的最长长度。

那么 $dp[j][0]$ 和 $dp[i][0]$，$dp[j][1]$ 和 $dp[i][1]$ 之间的递推很简单。

$$dp[i][0]=\max_{j=1}^{i-1}dp[j][0]+1,a[j]<a[i]$$
$$dp[i][1]=\max_{j=1}^{i-1}dp[j][1]+1,a[j]<a[i]$$
接下来考虑 $dp[i][0]$ 和 $dp[i][1]$ 之间的转化，可以看一下最后一个样例，当 $a[j]=a[i]-1$ 时或 $j=i-1$ 时，无法在中间修改一个的数字，其余情况都可以。

因此，转移式为：
$$dp[i][1]=\max_{j=1}^{i-2}dp[j][0]+2,a[j]<a[i]-1$$
此时时间复杂度为 $O(n^2)$。

接下来考虑优化，$a[j]<a[i]$ 的条件很容易想到用树状数组。

因为考虑到 $dp[i][1]$ 由 $dp[j][0],j<i-1$ 转移来，所以我们可以延迟插入，在遍历到 $i$ 时插入 $dp[i-1][0]$ 和 $dp[i-1][1]$。这样就可以只用 $2$ 个树状数组。

下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define lb (i&(-i))
using namespace std;
const int N=2e5+10,M=998244353;
int n,q,t0[N],dp[N][2],a[N],ans,b[N],t1[N];
void add(int t[],int x,int d){
	for(int i=x;i<=q;i+=lb)
		t[i]=max(t[i],d);
	return;
}
int query(int t[],int x){
	int s=0;
	for(int i=x;i>=1;i-=lb)
		s=max(s,t[i]);
	return s;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
		dp[i][0]=1;
		if(i>1)dp[i][1]=2;
		else dp[i][1]=-99999999;
	}
	sort(b+1,b+1+n);
	q=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		int k=lower_bound(b+1,b+1+q,a[i])-b;
		dp[i][0]=max(dp[i][0],query(t0,k-1)+1);
		dp[i][1]=max(dp[i][1],query(t1,k-1)+1);
		if(i>1)
			if(b[k-1]!=b[k]-1)dp[i][1]=max(dp[i][1],query(t0,k-1)+2);
			else dp[i][1]=max(dp[i][1],query(t0,k-2)+2);
	//	cout<<b[k-2]<<' '<<b[k-1]<<' '<<dp[i][1]<<'\n';
		if(a[i-1]<a[i])
			dp[i][0]=max(dp[i][0],dp[i-1][0]+1),
			dp[i][1]=max(dp[i][1],dp[i-1][1]+1);
		ans=max(dp[i][1],ans);
		if(i<n)ans=max(dp[i][0]+1,ans);
		else ans=max(dp[i][0],ans);
		if(i!=1){		
			add(t0,lower_bound(b+1,b+1+q,a[i-1])-b,dp[i-1][0]);
			add(t1,lower_bound(b+1,b+1+q,a[i-1])-b,dp[i-1][1]);
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：incra (赞：5)

### Solution
套路题。

显然一个 LIS 能拆成两段分开考虑，那么考虑求出以 $i$ 为起点和结尾的 LIS 的长度，分别设为 $f_i,g_i$。

接下来贪心的考虑，在 $f_i$ 最长的条件下，选择 $a_i$ 最小的一定最优，$g_i$ 同理。

注意离散化 $x$ 的时候要加上 $x-1$ 和 $x+1$，否则赛时会在最后一个点 WA。

给个 Hack：

input：
```
4
1 3 3 6
```
Answer：
```
4
```

Upd 被 Hack 了，感谢 [@Genius_Star](https://www.luogu.com.cn/user/979266)。

input：
```
8
1 2 3 100 1 5 6 7
```
Answer：
```
7
```

原代码为何会错：当枚举到 $i=4$ 时，$a_{i-1}\ge a_{i+1}$，会直接跳过，而正确做法是 $i-1$ 所在 LIS 往前跳，直到 $a_{x}<a_{i+1}$，显然暴力跳会 TLE，但是不难发现可以倍增优化，于是就通过了。
### Code
[Link1](https://atcoder.jp/contests/abc360/submissions/55113001)（后来被 Hack 的代码，两个代码建议一起对比着看）。

[Link2](https://atcoder.jp/contests/abc360/submissions/55136937)。

---

## 作者：tallnut (赞：4)

首次场切 G 题！！
# 简化版题目解法
先来看一下该题的简化版。
> 所有条件均和原题一样，除了要求**子序列必须连续**。

~~这个简化版是一道原题，我在场上把题目看成了这个简化版，结果白吃了 $3$ 发罚时。~~

思路是先计算两个数组 $l,r$，$l_i$ 和 $r_i$ 分别表示以 $i$ 元素结尾的 LIS 长度和以 $i$ 元素开头的 LIS 长度。这个可以一遍递推扫出来。那么对于每个元素，枚举以下 $3$ 种情况：
- 以当前这个元素结束 LIS。长度为 $l_{i-1}+1$。
- 以当前这个元素开始 LIS。长度为 $r_{i+1}+1$。
- 如果 $a_{i+1}-a_{i-1}\ge 2$，可以把当前元素修改为介于 $a_{i+1}$ 和 $a_{i-1}$ 之间，把前后两个 LIS 拼起来。长度为 $l_{i-1}+r_{i+1}+1$。
# 原题解法
再来看原题。这个比简化版复杂一些 ~~（废话）~~，允许子序列不连续。

这样 $l,r$ 数组就没法一遍 $\Theta(n)$ 求出来了。正常直接枚举求最大值需要 $\Theta(n^2)$，无法承受。可以先离散化之后用权值线段树（不是求和，是求最值）在 $\Theta(n\log n)$ 时间内求出来。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/163602891)。
```cpp
// NOTE: "[EDIT]" means you should edit this part by yourself
#include <bits/stdc++.h>
// [EDIT] please enable this line if there are many tests
//#define MULTITEST
using namespace std;
// [EDIT] if you want to copy some templates, please paste them here
namespace tallnut{template<typename T>void discretize(T a[],int n){T b[n+1];for(int i=1;i<=n;i++)b[i]=a[i];std::sort(b+1,b+n+1);int len=std::unique(b+1,b+n+1)-b-1;for(int i=1;i<=n;i++)a[i]=std::lower_bound(b+1,b+len+1,a[i])-b;}}
namespace tallnut{template<int N,typename T>class segtree2{private:struct node{int l;int r;T a;}t[N<<2];inline int ls(int p){return(p<<1);}inline int rs(int p){return((p<<1)|1);}inline void push_up(int p){t[p].a=std::max(t[ls(p)].a,t[rs(p)].a);}void build_p(T arr[],int p,int l,int r){t[p].l=l;t[p].r=r;if(l==r){t[p].a=arr[l];return;}int mid=(l+r)>>1;build_p(arr,ls(p),l,mid);build_p(arr,rs(p),mid+1,r);push_up(p);}void modify_p(int p,int k,T x){if(t[p].l==t[p].r){t[p].a=std::max(t[p].a,x);return;}int mid=(t[p].l+t[p].r)>>1;if(k<=mid)modify_p(ls(p),k,x);else modify_p(rs(p),k,x);push_up(p);}T query1_p(int p,int k){if(t[p].l==t[p].r)return t[p].a;int mid=(t[p].l+t[p].r)>>1;if(k<=mid)return query1_p(ls(p),k);else return query1_p(rs(p),k);}T query2_p(int p,int l,int r){if(t[p].l>r||t[p].r<l)return 0;if(l<=t[p].l&&t[p].r<=r)return t[p].a;return std::max(query2_p(ls(p),l,r),query2_p(rs(p),l,r));}public:segtree2(){memset(t,0,sizeof t);}void build(T arr[]){build_p(arr,1,1,N-1);}void modify(int k,T x){modify_p(1,k,x);}T query1(int k){return query1_p(1,k);}T query2(int l,int r){return query2_p(1,l,r);}};}
typedef long long ll;
#define rep1(i,x,y) for (int i = (x);i <= (y);i++)
#define rep2(i,x,y) for (int i = (x);i >= (y);i--)
#define rep3(i,x,y,z) for (int i = (x);i <= (y);i += (z))
#define rep4(i,x,y,z) for (int i = (x);i >= (y);i -= (z))
#define cl(a) memset(a,0,sizeof(a))
// [EDIT] define some constants here
const int N = 2e5 + 10;
// [EDIT] define some variables, arrays, etc here
int n,ans;
int a[N],b[N],l[N],r[N],nulla[N];
tallnut::segtree2<N,int> f1,f2;
// [EDIT] a function to solve the problem
void solve()
{
    //input
    cin >> n;
    rep1(i,1,n)
        cin >> a[i];
    //solve
    rep1(i,1,n)
        b[i] = a[i];
    tallnut::discretize(b,n);
    //计算l
    f1.build(nulla);
    rep1(i,1,n)
    {
        l[i] = f1.query2(1,b[i] - 1) + 1;
        f1.modify(b[i],l[i]);
    }
    //计算r
    f2.build(nulla);
    rep2(i,n,1)
    {
        r[i] = f2.query2(b[i] + 1,n) + 1;
        f2.modify(b[i],r[i]);
    }
    rep1(i,1,n)
    {
        ans = max(ans,l[i - 1] + 1);
        ans = max(ans,r[i + 1] + 1);
        if (a[i + 1] - a[i - 1] > 1)
            ans = max(ans,l[i - 1] + r[i + 1] + 1);
    }
    //output
    cout << ans;
}
int main()
{
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif
    int t;
#ifdef MULTITEST
    cin >> t;
#else
    t = 1;
#endif
    while (t--)
        solve();
#ifndef ONLINE_JUDGE
    cout << "\n---------------\n";
    system("pause");
#endif
}
```

---

## 作者：ma_niu_bi (赞：4)

### [ABC360G] Suitable Edit for LIS 题解

### 思路

中间修改的数可以把两段 LIS 合并在一起。

预处理出 $f_i$ 和 $g_i$ 分别表示以 $i$ 结尾的 LIS 和以 $i$ 开头的 LIS。
$$
f_i=\max_{j=1}^{i-1} f_j+1(a_j<a_i)
$$
可以使用线段树优化。$g$ 同理。

求出 $f$ 和 $g$ 后：
$$
ans=\max_{i}((\max_{j}f_j)+g_i+1)
$$
即把 $i$ 和 $j$ 中间的某一个数改变后，以 $j$ 结尾的 LIS 和以 $i$ 开头的 LIS 可以合并。

$i$ 和 $j$ 需要满足的关系是：
$$
j<i-1
$$
和
$$
a_j<a_i-1
$$
只有满足这两个条件时中间才能放进一个新数。

同样可以使用线段树优化。

注意答案不一定需要两个 LIS 合并，也可以是一个 LIS 前或后加一个数，有两个数据卡了这个。

一些细节见代码注释。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1) 
using namespace std;
const int N = 2e6 + 5;
struct segt {
    struct node {int l, r, v;} t[N << 2];
    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r, t[p].v = 0;
        if (l == r) return ;
        build(ls, l, mid);
        build(rs, mid + 1, r);
    }
    void modify(int p, int id, int v) {
        if (t[p].l == t[p].r) {t[p].v = v;return ;}
        if (id <= t[ls].r) modify(ls, id, v);
        else modify(rs, id, v);
        t[p].v = max(t[ls].v, t[rs].v);
    }
    int query(int p, int l, int r) {
        if (l <= t[p].l && t[p].r <= r) return t[p].v;
        int ret = 0;
        if (l <= t[ls].r) ret = max(ret, query(ls, l, r));
        if (r >= t[rs].l) ret = max(ret, query(rs, l, r));
        return ret;
    }
} T;
int n, cnt, ans, mxg, mxf, a[N], b[N], f[N], g[N];
int id(int x) {return lower_bound(b + 1, b + cnt + 1, x) - b;}
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        b[++ cnt] = a[i];
        b[++ cnt] = a[i] - 1; // 需要使用这些值
        b[++ cnt] = a[i] - 2; // 也要离散化
        b[++ cnt] = a[i] + 1;
    }
    b[++ cnt] = LONG_LONG_MIN, b[++ cnt] = LONG_LONG_MAX; // 防止越界
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    T.build(1, 1, cnt);
    for (int i = 1; i <= n; i ++) { // 求 f
        ans = max(ans, mxf + 1); // LIS 后加数
        f[i] = T.query(1, 1, id(a[i] - 1)) + 1;
        T.modify(1, id(a[i]), f[i]);
        ans = max(ans, f[i]);
        mxf = max(mxf, f[i]);
    }
    T.build(1, 1, cnt);
    for (int i = n; i >= 1; i --) { // 求 g
        ans = max(ans, mxg + 1); // LIS 前加数
        g[i] = T.query(1, id(a[i] + 1), cnt) + 1;
        T.modify(1, id(a[i]), g[i]);
        mxg = max(mxg, g[i]);
    }
    T.build(1, 1, cnt);
    for (int i = 2; i <= n; i ++) { // 统计答案
        ans = max(ans, T.query(1, 1, id(a[i] - 2)) + 1 + g[i]);
        T.modify(1, id(a[i - 1]), f[i - 1]);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Expert_Dream (赞：2)

比较简单的 G 题。

很一眼，但是细节有一些多。

LIS 很熟悉吧？想要 $O(n \log n)$ 可以直接上线段树对吧。

一次操作？好吧，可做了。

我们把区间拆成三段。

前面一段是一个 LIS，后面是一个 LIS，然而中间是更换的数。

我们可以先处理一下 $f_i$ 代表从 $1$ 到 $i$ 的 LIS 是多少。$g_i$ 代表从 $i$ 到 $n$ 的 LIS 是多少。这比较简单，直接在值域上维护着线段树就行啦。值域比较大，先离散化在处理即可。

然后我们在处理 $g_i$ 的时候顺便更行答案，线段树中记录了后面的 LIS 最大值，然后再与 $f_i$ 拼接一下，把他原来没有离散化的比一下大小看中间是否可以插入一个数。再取最大值的答案即可。

不过还有两种情况，就是只有两段，是前面 LIS 拼新的数，或者后面的 LIS 拼新的数。

```cpp
// LUOGU_RID: 163613124
// Author: Expert_Dream
// Copyright (c) 2024 Expert_Dream All rights reserved.
// Problem: G - Suitable Edit for LIS
// Contest: AtCoder - AtCoder Beginner Contest 360
// URL: https://atcoder.jp/contests/abc360/tasks/abc360_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Date: 2024-06-30 20:00:31

// #pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
// #include <atcoder/all>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define x0 _x0_
#define y1 _y1_
#define endl '\n'
#define re register
#define pb push_back
#define vi vector<int>
#define pq priority_queue
#define mem(a,x) memset((a),(x),sizeof(a))
#define debug(x) cout<<"debug:"<<x<<endl;
#define sz(s) (int)(s.size())
#define all(a) a.begin(),a.end()
#define rd(l,r) (myrand()%(r-l+1)+l)
#define print(x) {cout<<x<<endl;return;}
#define For(x,y,z) for(int x = y;x <= z;x++)
#define For_(x,y,z) for(int x = y;x >= z;x--)
#define between(x, flo, top) (flo <= x && x <= top)
// #define double long double
using namespace std;
// using namespace atcoder;
mt19937 myrand(time(0));
template <typename Type> void get_min(Type &w1,const Type w2) { if(w2<w1) w1=w2; } 
template <typename Type> void get_max(Type &w1,const Type w2) { if(w2>w1) w1=w2; }
template <typename Type> Type up_div(Type w1,Type w2) { return (w1/w2+(w1%w2?1:0)); }//向上取整
template <typename Type> Type gcd(Type a,Type b) {long long i=__builtin_ctz(a),j=__builtin_ctz(b),x=i>j?j:i,y;b>>=j;while(a){a>>=i;y=b-a;i=__builtin_ctz(y);b=a<b?a:b;a=y<0?-y:y;}return b<<x;}
template <typename Type> Type lcm(Type a,Type b) {return a/gcd(a,b)*b;}
template <typename Type> Type ksm(Type a,Type b) {int res=1;while(b){if(b&1) res=res*a;a=a*a;b>>=1;}return res;}
template <typename Type> Type ksm(Type a,Type b,Type mod) {int res=1;while(b){if(b&1) res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return res%mod;}
namespace FastIO {template <typename T = int>inline T read() {T s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-')w=-1;c=getchar();}while(isdigit(c))s=(s<<1)+(s<<3)+(c^48),c=getchar();return s*w;}template <typename T>inline void read(T &s){s=0;int w=1;char c=getchar();while(!isdigit(c)){if(c=='-')w=-1;c=getchar();}while(isdigit(c))s=(s<<1)+(s<<3)+(c^48),c=getchar();s*=w;}template <typename T, typename... Args> inline void read(T &x, Args &...args) {read(x), read(args...);}template <typename T>inline void write(T x,char ch = '\n') {if(x<0)x=-x,putchar('-');static char stk[200];int top=0;do{stk[top++]=x%10+'0',x/=10;}while(x);while(top)putchar(stk[--top]);putchar(ch);return;}template <typename T, typename... Args> inline void write(T x, Args ...args) {write(x,' '), write(args...);}template <typename Type> void Write(vector<Type> v) {for(auto it:v)write(it,' ');puts("");}}
using namespace FastIO;
#define int long long
const int mod = 998244353,inf = 0x3f3f3f3f,N = 2e5+5,M = 1e6+5,K = 3000+5;// 1000000007
const long long linf = 0x3f3f3f3f3f3f3f3f;
struct seg{
	struct node{int l,r,Max,lazy;}t[N<<2];
	void build (int p,int l,int r){//建树 
		t[p].l = l,t[p].r = r;
		if(l == r) {t[p].Max = 0;return ;}	
		int mid = (l+r) >> 1;
		build(p<<1,l,mid),build(p<<1|1,mid + 1,r);
		t[p].Max = max(t[p<<1].Max , t[p<<1|1].Max);
	}void Add(int p,int x){
		t[p].lazy = max(t[p].lazy,x),t[p].Max=max(t[p].Max,x);
	}void pushdown(int p){
		if(t[p].lazy != 0 && t[p].l != t[p].r)
			Add(p<<1,t[p].lazy),Add(p<<1|1,t[p].lazy),t[p].lazy = 0;
	}void update(int p,int l,int r,int x){//区间修改
		pushdown(p); if(l <= t[p].l && t[p].r <= r){Add(p,x); return ;}
		int mid = (t[p].r + t[p].l) >> 1;
		if(l <= mid) update(p<<1,l,r,x); 
		if(r > mid) update(p<<1|1,l,r,x);
		t[p].Max  = max(t[p<<1].Max,t[p<<1|1].Max) ;
	}void modify(int p,int x,int v){//单点修改
		if(t[p].l == t[p].r){t[p].Max=max(v,t[p].Max);return;}
		int mid = (t[p].l + t[p].r )>> 1;
		if(x <= mid) modify(p<<1 ,x ,v);
		else modify(p<<1|1,x,v);
		t[p].Max = max(t[p<<1].Max,t[p<<1|1].Max);
	}int query(int p,int l,int r){//区间查询
		if(l <= t[p].l && t[p].r <= r) return t[p].Max;
		pushdown(p);
		int mid=(t[p].l+t[p].r)>>1,ans = 0;
		if(mid>=l) ans=max(ans,query(p<<1,l,r));
		if(mid<r) ans=max(ans,query(p<<1|1,l,r));
		return ans;
	}
}F,G;
int f[N],g[N];
int a[N];int n;
int u[N],b[N];
void solve(){
	cin >> n;For(i,1,n) cin >> a[i];
	if(n==1){
		cout<<1<<endl;return ;
	}
	F.build(1,0,n+6),G.build(1,0,n+6);

	For(i,1,n) u[i]=a[i];
	
	sort(u+1,u+1+n);
	int un=unique(u+1,u+1+n)-u-1;
	For(i,1,n) b[i] = lower_bound(u+1,u+1+un,a[i])-u;
	int ans=1;
	For(i,un+1,n) u[i]=0;
	
	For(i,1,n){
		f[i] = F.query(1,0,b[i]-1) + 1;
		F.modify(1,b[i],f[i]);
		if(i<n)ans=max(ans,f[i]+1);
	}

	For_(i,n,1){
		g[i] = G.query(1,b[i]+1,n+5) + 1;
		if(i > 1 && i < n && u[b[i-1]+1] > 0&&u[b[i-1]+1] <= n)ans=max(ans,f[i-1] + G.query(1,b[i-1]+1+(u[b[i-1]]+1==u[b[i-1]+1]),n+5) + 1);
		// cout<<i<<" "<<f[i]<<" "<<G.query(1,b[i]+1+(u[b[i]]+1==u[b[i]+1]),n)<<endl;
		G.modify(1,b[i],g[i]);
		if(i>1&&a[i] > 0)ans=max(ans,g[i]+1);
	}
	
	// For(i,1,n) cout<<f[i]<<" "<<g[i]<<endl;
	
	cout<<min(ans,n);
	
	
}signed main(){
	// freopen("std.in","r",stdin);
	// freopen("std.out","w",stdout);
	// ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	// read(T);
	For(_,1,T) solve();
	return 0;
}

```

由于细节比较多，放一些 HACK 数据在这，大家手玩就可以知道答案。

```
5
1 2 3 5 4
```

```
3
1 3 3
```

```
4
1 3 2 4
```

```
3 
3 3 3 
```

```
3
3 2 1
```

---

## 作者：Targanzqq (赞：1)

### 主要算法：树状数组的基础应用
这是一道经典的 LIS 问题，对于 $n\le 2\times 10^5$ 的数据范围，我们考虑树状数组优化 dp。

对于这个题，我们可以想到把要求的 LIS 分成三部分，一部分是修改点左侧的序列，一个是修改点右侧的序列，一个是修改点本身。我们可以分别处理。

我们开两个数组 $f_1,f_2$ 表示以某个点为结尾或开头的最长 LIS 长度。我们对于当前点来说，要找到值和坐标都小于当前点的数，那么我们在处理树状数组的时候改成前缀 $\max$ 值即可。$f_1$ 相对好求，处理 $f_2$ 的时候需要先把它倒过来，然后原来的 LIS 变成了最长下降子序列，我们把它的每个值变成相反数，然后再加上一个值域最大值，就能处理这类问题了。

都处理好以后，我们可以枚举一个点表示右侧序列的开头，根据贪心思想，我们修改它的上一个点能得到最优方案。设 $a_i$ 修改后为 $k$，则有 $k\le a_{i+1}$。设我们要找的左侧序列终点为 $j$，则有 $a_j<k<a_{i+1}$，则有 $a_j\le a_{i+1}-2$。这个性质也符合维护前缀 $\max$ 值的树状数组的性质。当我们枚举到 $n$ 时，前面的数就可以随便选了，所以我们给 $a_{n+1}$ 赋予一个尽可能大的值（大于 $10^9$ 即可）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e9+7 
#define N 300000
using namespace std;

int n,a[N],f1[N],f2[N],ans;

struct tree_array{
	unordered_map<int,int> c[5];
	int lb(int x){return x&(-x);}
	void change(int i,int num,int op){for(;i<=INF;i+=lb(i))c[op][i]=max(c[op][i],num);}
	int query(int i,int op){int res=0;for(;i>=1;i-=lb(i))res=max(res,c[op][i]);return res;}
}tr;

void solve1(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		f1[i]=tr.query(a[i]-1,1)+1;
		tr.change(a[i],f1[i],1);
	}
}
void solve2(){
	int cnt=0;
	for(int i=1;i<=n;i++)a[i]=INF-a[i];
	for(int i=n;i>=1;i--){
		f2[i]=tr.query(a[i]-1,2)+1;
		tr.change(a[i],f2[i],2);
	}
	for(int i=1;i<=n;i++)a[i]=INF-a[i];
}

void solve3(){
	int res=0;
    for(int i=1;i<=n;i++){
	    res=tr.query(a[i+1]-2,3)+f2[i+1]+1;
    	tr.change(a[i],f1[i],3);
    	ans=max(ans,res);
	}
	cout<<ans;
} 

signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[n+1]=INF;
	solve1();
	solve2();
	solve3();
}
```

---

## 作者：FXT1110011010OI (赞：1)

## 分析

没有修改的情况下，可以用树状数组求出 $f_i$ 表示从前往后，以 $a_i$ 结尾的最长上升子序列长度；$g_i$ 表示从后往前，以 $a_i$ 结尾的最长下降子序列长度。

考虑修改，我们枚举子序列中修改的数的 **前一个** 位置，记为 $i$，那么修改的数的 **后一个** 位置最小要是 $a_i + 2$（因为是严格上升，要将修改的位置修改为 $a_i + 1$），可以在求 $g$ 数组的同时进行维护。

具体见代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int n;
int a[N], lsh[N], tot;
int tr[N], f[N], g[N];

int find(int x) {return lower_bound(lsh + 1, lsh + 1 + tot, x) - lsh;}

int lowbit(int x) {return x & -x;}

void modify(int x, int v) {for (int i = x; i <= tot; i += lowbit(i)) tr[i] = max(tr[i], v);}

int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res = max(res, tr[i]);
    return res;
}

void modify2(int x, int v) {for (int i = x; i; i -= lowbit(i)) tr[i] = max(tr[i], v);};

int query2(int x)
{
    int res = 0;
    for (int i = x; i <= tot; i += lowbit(i)) res = max(res, tr[i]);
    return res;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
        lsh[i] = a[i];
    }
    sort(lsh + 1, lsh + 1 + n);
    tot = unique(lsh + 1, lsh + 1 + n) - lsh - 1;
    for (int i = 1; i <= n; i ++ ) a[i] = find(a[i]);
    memset(tr, 0, sizeof tr);
    for (int i = 1; i <= n; i ++ )
    {
        f[i] = query(a[i] - 1) + 1;
        modify(a[i], f[i]);
    }
    int res = 0;
    for (int i = 1; i <= n; i ++ ) res = max(res, f[i]);
    memset(tr, 0, sizeof tr);
    for (int i = n; i; i -- ) // 修改的前一个位置为 i - 1
    {
        if (i > 1) res = max(res, f[i - 1] + 1 + query2(find(lsh[a[i - 1]] + 2)));
        else res = max(res, query2(1) + 1);
        g[i] = query2(a[i] + 1) + 1;
        modify2(a[i], g[i]);
    }
    printf("%d\n", res);
    return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：1)

这道题实际上不难，当然是相对于其他同级题目。

我们考虑答案要么是原答案序列增加而来，要么是首尾拼接，然后考虑使用常数小的树状数组维护动态规划，正反跑两边，边跑边记录，答案最多也就在原序列答案上加一，还是好做的。

具体的，正着一遍时考虑能否插入一个使得答案增加，反着同理，然后树状数组优化下。然后考虑正反两边，直接枚举插入点就行，复杂度总的 $O(n\log n)$，对了别用哈希，过不了，按有篇题解哈希那哥们很难写过，有个点估计卡哈希。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5,maxn=1e9+123;
int n,a[N],f[N],g[N],ans,c[4*N],b[4*N],m;
void add(int x,int y,int op){
	if(op)for(;x<=m;x+=x&(-x))c[x]=max(c[x],y);
	else for(;x;x-=x&(-x))c[x]=max(c[x],y);
}
int query(int x,int op){
	int ans=-1e9;
	if(op)for(;x;x-=x&(-x))ans=max(ans,c[x]);
	else for(;x<=m;x+=x&(-x))ans=max(ans,c[x]);
	return ans;
}
int find(int x){
	return lower_bound(b+1,b+1+m,x)-b;
}
int c1[N],c2[N],c3[N],c4[N];
int main(){
	ios::sync_with_stdio(false);
	
	
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1;i <= n;i++)cin >> a[i];
    for(int i = 1 ; i <= n ; i++ ){
        b[i*4-3]=a[i],b[i*4-2]=a[i]-1,b[i*4-1]=a[i]+2,b[i*4]=a[i]+1;
    }
    sort(b+1,b+1+4*n);
    m=unique(b+1,b+1+4*n)-b-1;
    for(int i = 1;i <= n;i++){
        c1[i]=find(a[i]-1);
        c2[i]=find(a[i]);
        c3[i]=find(a[i]+1);
        c4[i]=find(a[i]+2);
    }
	for(int i = 1;i <= n;i++){
		f[i]=max(1,query(c1[i],1)+1);
		add(c2[i],f[i],1);
		ans=max(ans,f[i]+(bool)(i!=n));
	}
    memset(c,0,sizeof(c));
	for(int i = n;i >= 1;i--){
		g[i]=max(1,query(c3[i],0)+1);
		add(c2[i],g[i],0);
		ans=max(ans,g[i]+(bool)(i!=1));
	}
    memset(c,0,sizeof(c));
	for(int i = n-2;i >= 1;i--){
		add(c2[i+2],g[i+2],0);
		ans=max(ans,query(c4[i],0)+f[i]+1);
	}
	cout << ans;
	return 0;
}

```

---

## 作者：M1saka16I72 (赞：1)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc360-g.html)

第一次场切 G（虽然被 after_contest 叉了），纪念一下。

## 思路

贪心地，考虑最优秀的操作一定是修改中间的一个元素，把左右两边的 LIS 接在一起。

于是可以预处理每个以每个下标 $i$ 开头 / 结尾的最长 LIS 长度 $R_i$ 和 $L_i$，然后枚举右边 LIS 开头的下标 $r$，代表修改 $a_{r-1}$ 的值，则答案为 $\max^{n+1}_{r=2}\{R_r+\max_{l=0}^{r-2}\{L_l\}(a_l+1<a_r)+1\}$。

预处理和统计答案使用离散化 + 线段树优化 dp 实现即可，时间复杂度为 $\mathcal{O}(n\log n)$。

需要注意的是统计答案时，应先将 $a_0$ 设为极小值，$a_{n+1}$ 设为极大值，这样就可以分别覆盖到左边的 LIS 为空和右边的 LIS 为空的情况，after_contest 叉的也就是这两种边界情况。

## 代码

[link](https://atcoder.jp/contests/abc360/submissions/55109290)

---

## 作者：lfxxx (赞：1)

注意到改变一个位置的值带来的影响是将原先序列中的 LIS 长度加 $1$ 以及将两个 LIS 拼起来。

考虑对于每个位置维护出 $pre_i,suf_i$ 分别表示以这个位置开头或者结尾的 LIS 长度，这一步就用正常维护 LIS 的方法维护即可，我这里用的是哈希表树状数组维护前缀后缀 $\max$。

让后注意到两个 LIS 可以拼起来一定是形如 $i < i+1 < j$ 且 $a_i < a_i+1 < a_j$ 然后我们把 $pre_i$ 与 $suf_j$ 拼起来的形式，仍然可以从后往前扫的同时用一个树状数组维护后缀 $\max$ 统计。

时间复杂度 $O(n \log V)$ 由于使用了哈希表，常数比较大，但是很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+114;
const int top = 1e9+114;
unordered_map<int,int> tr;
int a[maxn],n;
int pre[maxn],suf[maxn];
int ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        int now=a[i]-1;
        pre[i]=1;
        while(now>0){
            pre[i]=max(pre[i],tr[now]+1);
            now-=(now&(-now));
        }
        now=a[i];
        while(now<=top){
            tr[now]=max(tr[now],pre[i]);
            now+=(now&(-now));
        }
        ans=max(ans,pre[i]);
        if(i!=n) ans=max(ans,pre[i]+1);
    }
    tr.clear();
    for(int i=n;i>=1;i--){
        int now=a[i]+1;
        suf[i]=1;
        while(now<=top){
            suf[i]=max(suf[i],tr[now]+1);
            now+=(now&(-now));
        }
        now=a[i];
        while(now>0){
            tr[now]=max(tr[now],suf[i]);
            now-=(now&(-now));
        }
        ans=max(ans,suf[i]);
        if(i!=1) ans=max(ans,suf[i]+1);
    }
    tr.clear();
    for(int i=n-2;i>=1;i--){
        int now=a[i+2];
        while(now>0){
            tr[now]=max(tr[now],suf[i+2]);
            now-=(now&(-now));
        }
        now=a[i]+2;
        while(now<=top){
            ans=max(ans,tr[now]+pre[i]+1);//拼接
            now+=(now&(-now));
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

考虑求出以 $a_i$ 结尾和以 $a_i$ 开始的最长上升子序列长度 $dp_i,f_i$。

对于 $dp$，可以先离散化，然后值域线段树求解；$f$ 就是反着来做一遍即可。

那么我们可以钦定将第 $i$ 个位置进行修改，那么我们为了使得答案最优，可以令 $a_i \gets a_{i-1}+1$，此时的最优答案为 $dp_{i-1} + 1 + f_{nxt_i}$。

其中 $nxt_i$ 表示在 $i+1$ 后的位置中第一个大于 $a_i+1$ 的值的位置，可以单调栈求解。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
const ll N=2e5+10;
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
ll n,s,ans;
ll a[N],b[N],dp[N],f[N],nxt[N];
stack<pair<ll,ll>> stk;
ll Find(ll x){
	ll l=1,r=s;
    while(l<r){
        ll mid=(l+r)>>1;
        if(b[mid]>=x) 
		  r=mid;
        else 
		  l=mid+1;
    }
    return l;
}
void pushup(ll k){
	X[k].Max=max(X[k<<1].Max,X[k<<1|1].Max);
} 
void build(ll k,ll l,ll r){
	X[k].Max=0;
	X[k].l=l,X[k].r=r;
	if(l==r)
	  return ;
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
void update(ll k,ll i,ll v){
	if(X[k].l==i&&X[k].r==i){
		X[k].Max=max(X[k].Max,v);
		return ;
	}
	ll mid=(X[k].l+X[k].r)>>1;
	if(i<=mid)
	  update(k<<1,i,v);
	else
	  update(k<<1|1,i,v);
	pushup(k);
}
ll query(ll k,ll l,ll r){
	if(X[k].l==l&&X[k].r==r)
	  return X[k].Max;
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return query(k<<1,l,r);
	else if(l>mid)
	  return query(k<<1|1,l,r);
	else
	  return max(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
}
int main(){
	a[0]=-2e9;
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=a[i];
	}
	for(int i=n;i>=0;i--){
		while(!stk.empty()&&stk.top().first<=a[i]+1){
			if(stk.top().first>a[i-1]+1&&!nxt[i-1])
			  nxt[i-1]=stk.top().second;
			stk.pop();
		}
		if(!stk.empty())
		  nxt[i]=stk.top().second;
		if(i!=n)
		  stk.push({a[i+1],i+1});
	}
	sort(b+1,b+n+1);
	s=unique(b+1,b+n+1)-(b+1); 
	build(1,1,s);
	for(int i=1;i<=n;i++)
	  a[i]=Find(a[i]);
	update(1,a[1],1);
	dp[1]=1;
	for(int i=2;i<=n;i++){
		ll x=a[i];
		if(x==1)
		  update(1,x,1);
		else
		  update(1,x,query(1,1,x-1)+1);
		dp[i]=query(1,x,x);
	}
	ans=X[1].Max;
	for(int i=0;i<(N<<2);i++)
	  X[i].Max=0;
	update(1,a[n],1);
	f[n]=1;
	for(int i=n-1;i>=1;i--){
		ll x=a[i];
		if(x==s)
		  update(1,x,1);
		else
		  update(1,x,query(1,x+1,s)+1);
		f[i]=query(1,x,x);		
	}
	for(int i=0;i<n;i++)
	  ans=max(ans,dp[i]+1+f[nxt[i]]);
	write(ans);
	return 0;
} 
```

---

## 作者：Masterwei (赞：1)

由于题面只说需改一个数，我们考虑对此事下文章。直接枚举修改的位置是不行的，因为我们并不知道修改为多少是最优的。考虑枚举修改的数在其后面选择的最长上升子序列的起始位置 $i$，这样我们可以贪心判断修改的数为 $a_i-1$，在找前缀的最长上升子序列即可。

赛后被 hack 了，因为忘记最后一个数修改后成为答案的情况了。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
  int x=0;bool f=0;char ch=getchar();
  while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
  while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
  return f?-x:x;
}
const int Maxn=2e5+5,V=1e9+2;
int n,a[Maxn];
int ans=0;
struct seg{
	int root[Maxn],cnt;
	struct Tree{int ls,rs,data;}t[Maxn*100];
	void change(int&x,int y,int l,int r,int d,int p){
		x=++cnt;t[x]=t[y];if(l==r)return void(t[x].data=p);
		int mid=l+r>>1;
		if(mid>=d)change(t[x].ls,t[y].ls,l,mid,d,p);
		else change(t[x].rs,t[y].rs,mid+1,r,d,p);
		t[x].data=max(t[t[x].ls].data,t[t[x].rs].data);
	}
	int query(int x,int l,int r,int L,int R){
		if(L>R)return 0;
		if(L<=l&&r<=R)return t[x].data;
		int mid=l+r>>1,res=0;
		if(mid>=L)res=query(t[x].ls,l,mid,L,R);
		if(mid<R)res=max(res,query(t[x].rs,mid+1,r,L,R));
		return res;
	}
}pre,nxt;
int main(){
	n=read();
	if(n==1){
		puts("1");
		return 0;
	}
	for(int i=1;i<=n;i++)a[i]=read(),pre.change(pre.root[i],pre.root[i-1],1,V,a[i],pre.query(pre.root[i-1],1,V,1,a[i]-1)+1);
	for(int i=n;i;i--)nxt.change(nxt.root[i],nxt.root[i+1],1,V,a[i],nxt.query(nxt.root[i+1],1,V,a[i]+1,V)+1);
	for(int i=2;i<=n;i++){
//		printf("%d:%d\n",i,nxt.query(nxt.root[i],1,V,a[i]+1,V)+1+pre.query(pre.root[i-2],1,V,1,a[i]-1)+1);
		ans=max(ans,nxt.query(nxt.root[i],1,V,a[i]+1,V)+1+pre.query(pre.root[i-2],1,V,1,a[i]-2)+1);
	}
	ans=max(ans,pre.query(pre.root[n-1],1,V,1,V)+1);
	printf("%d\n",ans);
	return 0;
}

```

---

