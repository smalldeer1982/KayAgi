# Pashmak and Parmida's problem

## 题目描述

Parmida is a clever girl and she wants to participate in Olympiads this year. Of course she wants her partner to be clever too (although he's not)! Parmida has prepared the following test problem for Pashmak.

There is a sequence $ a $ that consists of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Let's denote $ f(l,r,x) $ the number of indices $ k $ such that: $ l<=k<=r $ and $ a_{k}=x $ . His task is to calculate the number of pairs of indicies $ i,j $ $ (1<=i&lt;j<=n) $ such that $ f(1,i,a_{i})&gt;f(j,n,a_{j}) $ .

Help Pashmak with the test.

## 样例 #1

### 输入

```
7
1 2 1 1 2 2 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
3
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```

# 题解

## 作者：MeowScore (赞：7)

[传送门 qwq](https://www.luogu.com.cn/problem/CF459D)

线段树题解。写题解的人可爱不毒瘤。

性质挺诈骗的……这个 $f(i,j,x)$ 看起来会有什么奇妙性质，但是再仔细一考虑发现这玩意儿直接就能预处理了！

后面要开桶，还要建权值线段树，所以现在你默认这些数已经离散过了。

我们建立一个数组 $pre$。其中 $pre_i=f(1,i,a_i)$，直接顺着扫原数组，拿个桶记录一下每个数字出现的次数。$pre_i$ 就等于扫过 $i$ 之后 $a_i$ 出现的次数。

再建一个数组 $suf$。其中 $suf_i=f(j,n,a_j)$，逆着扫同样求。

这时候题意就变成了：给出两个长度为 $n$ 的数组 $pre$ 和 $suf$，求出有多少对 $(i,j)$ 满足 $i<j$ 且 $pre_i>suf_j$。类似于逆序对的东西。

我们不妨倒着枚举数组 $suf$，显然每枚举一次，$pre$ 中就有一个元素被淘汰掉（不再满足 $i<j$ 这条性质）。当 $suf$ 数组枚举到第 $i$ 位，枚举过的部分恰好是可能与 $pre_{i-1}$ 产生答案的全部元素，做到了不重不漏。然后我们在枚举过的部分中求出小于 $pre_{i-1}$ 的数的个数即可，权值线段树可以完成这项工作。每次枚举完 $suf$ 数组的一个元素，就立刻塞到权值线段树里。然后进行查询，累加答案即可。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
const int N=1000100;
int a[N],b[N];
int cmp(int x,int y){
	return x<y;
}
int pre[N],suf[N],t[N];
int n;
int res;
int ans;
int st[N*4];
void add(int root,int l,int r,int x){
	if(l==r){
		st[root]++;
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)
		add(root*2,l,mid,x);
	else
		add(root*2+1,mid+1,r,x);
	st[root]=st[root*2]+st[root*2+1];
}
void ask(int root,int l,int r,int x,int y){
	if(l>=x&&r<=y){
		res+=st[root];
		return;
	}
	int mid=(l+r)/2;
	if(mid>=x)
		ask(root*2,l,mid,x,y);
	if(mid+1<=y)
		ask(root*2+1,mid+1,r,x,y);
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=a[i];
	}
	sort(b+1,b+n+1,cmp);
	int m=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++){
		int x=lower_bound(b+1,b+n+1,a[i])-b;
		a[i]=x;
	}
	for(int i=1;i<=n;i++){
		t[a[i]]++;
		pre[i]=t[a[i]];
	}
	memset(t,0,sizeof(t));
	for(int i=n;i>=1;i--){
		t[a[i]]++;
		suf[i]=t[a[i]];
	}
	for(int i=n;i>=2;i--){
		add(1,1,n,suf[i]);
		res=0;
		if(pre[i-1]-1)
			ask(1,1,n,1,pre[i-1]-1);
		ans+=res;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：EndSaH (赞：6)

利用 $(unordered)map$ 辅助, 一开始就预处理出 $f(1,i,a_i)$ 和 $f(j,n,a_j)$, 再利用树状数组或归并排序求出逆序对即可.

总时间复杂度 $O(nlogn)$.

---

## 作者：_雪绒花_ (赞：5)

看完题面，最后一句话吸引了我的注意：

> 求有多少对 $i,j$ 满足 $f(1,i,a_i) >f(j,n,a_j)$ 且 $i < j$。

这不是逆序对吗？

~~然后我们就可以A掉这道题了。~~

可经过分析后，我们发现不论是归并排序还是树状数组，求逆序对数量的时间复杂度都为 $O(nlogn)$，这就代表我们需要在 $O(1)$ 的时间内求出 $f(i,j,x)$。

真的是这样吗？

再看看题目的要求，我们发现题目中只需要使用 $f(1,i,a_i)$ 和 $f(i,n,a_i)$ 两种值，所以不难想到进行预处理。

进行预处理之后，我们发现这个逆序对还有别于正常的逆序对，所以需要特殊讨论。

因为归并排序本人不太会，所以给出一种使用树状数组求解的方法：

考虑每个 $i$ 对答案的贡献，根据题目要求，只有存在 $j>i$ 且 $f(j,n,a_j)<f(1,i,a_i)$ 时这个 $j$ 才对于 $i$ 合法，于是按照倒叙将每个大于 $i$ 的 $j$ 的值 $f(j,n,a_j)$ 插入树状数组，之后再求出小于 $f(1,i,a_i)$ 的值的数量即可。

这时发现 $a_i$ 的值域貌似是 $1e9$，于是需要离散化。

可能我讲的不好，不够细致，还是不懂的话请看代码（带注释）：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll MAXN = 1000005;
 
//单点修改，区间查询的树状数组 
ll n;
ll sum[MAXN];

inline ll lowbit(ll x) {
    return x & -x;
}

void update(ll x) {
    while (x <= n) {
        sum[x]++;
        x += lowbit(x);
    }
}

ll query(ll x) {
    ll result = 0;
    while (x) {
        result += sum[x];
        x -= lowbit(x);
    }
    return result;
}

ll a[MAXN], b[MAXN];
ll pre[MAXN], suc[MAXN], cnt[MAXN];
//pre[i]代表f(1,i,a[i])，suc[i]代表f(i,n,a[i])，cnt为辅助计算的数组 

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    //离散化 
    sort(b + 1, b + n + 1);
    ll len = unique(b + 1, b + n + 1) - b - 1;
    for (ll i = 1; i <= n; i++) {
        a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    }
    //预处理pre数组和suc数组，具体代表的值见上 
    for (ll i = 1; i <= n; i++) {
        pre[i] = ++cnt[a[i]];
    }
    for (ll i = 1; i <= len; i++) {
        cnt[i] = 0;
    }
    for (ll i = n; i >= 1; i--) {
        suc[i] = ++cnt[a[i]];
    }
    //树状数组求逆序对数量 
    ll ans = 0;
    for (ll i = n; i >= 1; i--) {
    //倒叙计算是为了树状数组中维护的所有j都大于当前的i  
        ans += query(pre[i] - 1);
        //求所有小于f(1,i,a[i])的数量 
        update(suc[i]);
        //再将f(i,n,a[i])插入树状数组，进行接下来的维护 
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：MVP_Harry (赞：3)

感觉前两篇题解都不是特别详细...

看到数据范围$n \le 10^6$，而$O(n)$又不太可能，想到这题的主要思路就是预处理 + 树状数组。

第一步必须是离散化，因为$a[i] \le 10^9$。

第二步则是根据题意，处理出$f(1, i, a[i])$以及$f(i, n, a[i])$。这一步在离散化之后很好处理，用前缀和正反扫一遍即可。

第三步，利用树状数组求解。可以回想一下树状数组是如何处理逆序对的，这里我们从后往前扫，每到一个数$a[i]$，就先求出$\text{sum}(f[i][0])$，然后再$\text{update}(f[i][1], 1)$。其中，$\text{sum}$和$\text{update}$对应树状数组中的函数。如果没搞清楚的话，需要仔细想一想。

代码如下：

```
#include<bits/stdc++.h>
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)
#define per(i, m, n) for (int i = m; i >= n; i--)
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define INF 0x3f3f3f3f
using namespace std;

const int maxn = 1e6 + 5;

int a[maxn], b[maxn], N, cnt[maxn], occurence[maxn][2], t[maxn];

// 1. Compression
// 2. Use prefix sum to find the number f
// 3. Use BIT

inline int lowbit(int x) {
    return x & (-x);
}

int sum(int x) {
    int ans = 0;
    while (x != 0) {
        ans += t[x];
        x -= lowbit(x);
    }
    return ans;
}

void update(int x, int k) {
    while (x <= N) {
        t[x] += k;
        x += lowbit(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i, 1, N) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + N + 1);
    int len = unique(b + 1, b + N + 1) - b - 1;
    rep(i, 1, N) a[i] = lower_bound(b + 1, b + len + 1, a[i]) - b;
    ll ans = 0;
    rep(i, 1, N) {
        occurence[i][0] = ++cnt[a[i]];
    }
    memset(cnt, 0, sizeof cnt);
    per(i, N, 1) {
        occurence[i][1] = ++cnt[a[i]];
    }
    per(i, N, 1) {
        ans += sum(occurence[i][0] - 1);
        update(occurence[i][1], 1);
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：DennyQi (赞：3)

先离散化。然后正反两遍用树状数组维护出$f$。于是得到了两个序列$A_i=f(1,i,a_i)$和$B_i=f(i,n,a_i)$。于是对于每个$i$，我们要求出$A_i > B_j(j \in [i+1,n])$的$j$的个数。再次利用树状数组维护即可

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#define int long long
using namespace std;
const int N = 1000010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
struct D{ int idx,val,rnk; }a[N];
int n,ans,v[N],p,A[N],B[N];
inline bool cmp1(const D& A, const D& B){
	return A.val < B.val;
}
inline bool cmp2(const D& A, const D& B){
	return A.idx < B.idx;
}
inline void add(int i, int k){
	for(; i <= n; i += i&(-i)){
		v[i] += k;
	}
}
inline int query(int i){
	int res = 0;
	for(; i > 0; i -= i&(-i)){
		res += v[i];
	}
	return res;
}
signed main(){
	// freopen("file.in","r",stdin);
	n = read();
	for(int i = 1; i <= n; ++i){
		a[i].val = read();
		a[i].idx = i;
	}
	sort(a+1,a+n+1,cmp1);
	a[1].rnk = p = 1;
	for(int i = 2; i <= n; ++i){
		a[i].rnk = (a[i].val==a[i-1].val) ? p : ++p;
	}
	sort(a+1,a+n+1,cmp2);
	for(int i = 1; i <= n; ++i){
		add(a[i].rnk,1);
		A[i] = query(a[i].rnk)-query(a[i].rnk-1);
	}
	memset(v,0,sizeof(v));
	for(int i = n; i >= 1; --i){
		add(a[i].rnk,1);
		B[i] = query(a[i].rnk)-query(a[i].rnk-1);
	}
	// for(int i = 1; i <= n; ++i) printf("%d ",A[i]);
	// 	printf("\n");
	// for(int i = 1; i <= n; ++i) printf("%d ",B[i]);
	// 	printf("\n");
	memset(v,0,sizeof(v));
	for(int i = 1; i <= n; ++i){
		add(B[i],1);
	}
	for(int i = 1; i < n; ++i){
		add(B[i],-1);
		ans += query(A[i]-1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：CSP_Sept (赞：2)

### 题意

给定数列 $a$，定义 $f(l,r,x)=\sum_{i=l}^r[a_i=x]$，求出二元组 $(i,j)$ 的对数，使得

$$
f(1,i,a_i)>f(j,n,a_j)\land 1\le i<j\le n
$$

### 题解

考虑到我们只会使用到与 $f$ 有关的两个值：$f(1,i,a_i),f(i,n,a_i)$，开个 map 可以 $O(n\log n)$ 预处理。

然后我们就可以考虑寻找新概念逆序对。

考虑扫描一遍 $i$，每次加入一个新的 $i$ 对答案的贡献。

显然，我们存储所有 $f(i,n,a_i)$ 的值，每个 $i$ 对答案的贡献就是**在区间 $[i+1,n]$ 中查找小于 $f(1,i,a_i)$ 的数的个数**。

而这显然是一个经典套路，我们可以拆分询问为 $[1,i],[1,n]$，离线处理统计答案即可。

当然这样需要树状数组，由于值域太大，考虑离散化，这样的话预处理也没必要开 map 了。

### 代码片段

```cpp
for(int i = 1 ; i <= n ; i++)
		cnt[a[i]]++, pre[i] = cnt[a[i]], sur[i] = sum[a[i]] - pre[i] + 1;
for(int i = 1 ; i <= n ; i++)
	q[i].push_back({-1, pre[i]}),
	q[n].push_back({ 1, pre[i]});
for(int i = 1 ; i <= n ; i++){
	add(sur[i], 1);
	for(auto t : q[i])
		ans += t.op * query(t.x - 1);
}
```

其中 sum 是每个 $a_i$ 出现的总次数。

[完整代码（152666992）](https://codeforces.com/contest/459/submission/152666992)

Source：Sept 省选 R1 原题模拟 D1T2（

---

## 作者：includer (赞：1)

### [你可以回顾下题面](https://www.luogu.com.cn/problem/CF459D)    [可能更好的阅读体验](https://www.luogu.com.cn/blog/JZYblog/solution-cf459d)

### 首先读题

- 给出长度为 $n(1\le n\le10^6)$ 的序列 $a(1\le a_i\le10^9)$。
- $f(i,j,x)$ 表示 $a_i\dots a_j$ 中 $x$ 的出现次数。
- 求有多少对 $i,j$ 满足 $f(1,i,a_i) > f(j,n,a_j)$ 且 $i < j$。

### 考虑预处理

既然题目只要我们求特定的 $f$ ，便想到可以用一个桶来维护每一个值出现的次数。

这样就可以**线性**求出需要用到的 $f$ 。

**需要注意** 数据范围有 $10^9$ 直接开桶要用 $map$ ，个人建议先离散化一下。

### 考虑求解

先看数据范围，$1 \le n \le 10^6$ ，如果 $n^2$ 暴力枚举显然会超时。

考虑如何做更优：怎样快速维护后缀桶。

考虑用[权值线段树](https://blog.csdn.net/yanweiqi1754989931/article/details/117380913)维护：当前位于第 $i$ 位，对于所有的 $n \le j \le i$ ，每一个值 $f(j,n,a_j)$ 出现的次数，这样就可以查询 $f(i...n,n,a_{i..n})$ 中所有比 $f(1,i-1,a_i)$ 小的值。

从后往前枚举每一个 $i$ ，每次插入操作复杂度 $O(\log_2{n})$ ，查询复杂度 $O(\log_2{n})$ ，总复杂度 $O(n \times \log_2{n})$ ，可以通过此题。

### Code Time

大家都是好谷民，**不可以ctj**哟。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int n,f1[N],f2[N],ans,tot,ton[N];
struct o{int v,p;};
o b[N],a[N];
struct tree{int l,r,v;};
tree t[N*4];//记得开4倍
bool cmp(o a,o b){return a.v<b.v;}
void build(int l,int r,int k){
	t[k].l=l,t[k].r=r;
	if(l==r)return;
	int mid=(l+r)/2;
	build(l,mid,k*2);
	build(mid+1,r,k*2+1);
}
void add(int k,int x){//单点修改
	int l=t[k].l,r=t[k].r;
	t[k].v++;
	if(l==r)
		return;
	int mid=(l+r)/2;
	if(mid>=x)
		add(k*2,x);
	else
		add(k*2+1,x);
}
void ask(int k,int x){//区间查询
	int l=t[k].l,r=t[k].r;
	if(r<x){
		ans+=t[k].v;
     //查到所需值，累加答案
		return;
	}
	int mid=(l+r)/2;
	ask(k*2,x);
	if(mid+1<x)
		ask(k*2+1,x);//分成两部分询问
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].v,a[i].p=i;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		b[a[i].p].p=a[i].p;
		if(a[i].v>a[i-1].v)
			b[a[i].p].v=++tot;
		else
			b[a[i].p].v=tot;
	}
	for(int i=1;i<=n;i++)
		f1[i]=++ton[b[i].v];
	memset(ton,0,sizeof ton);
	for(int i=n;i>0;i--)
		f2[i]=++ton[b[i].v];
  	//以上为输入+离散化
	build(1,1000000,1);//建树
	for(int i=n-1;i>0;i--){
		add(1,f2[i+1]);//将后缀值插入
		ask(1,f1[i]);//查询
	}
	cout<<ans;
	return 0;
}
```

### 完结撒花 ！！！

**（admin大大审核辛苦了！~~求过~~）**

---

## 作者：QCurium (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF459D)

挺好的题，虽然没有下传操作，但是也想了一会。

## 题意

$f(i,j,x)$ 表示 $a_i\dots a_j$ 中 $x$ 的出现次数，求有多少对 $i,j$ 满足 $f(1,i,a_i) > f(j,n,a_j)$ 且 $i < j$。

## 题目分析

统计 $f(1,i,a_i)$ 和 $f(j,n,a_j)$ 我们只需要跑两遍循环，至于如何存储，我们考虑**离散化**或者 **map**，也可以两个都用，~~比如我~~。

我们考虑用线段树，来存储大小相同的 $f(j,n,a_j)$ 出现的次数。

每次循环，我们将 $f(i,n,a_i)$ 这个位置减一，然后查询 $[1,f(1,i,a_i)-1]$，统计答案。

## Code

```cpp
#include<bits/stdc++.h>
#define Kagamine namespace
#define Rin std
#define ll long long
#define ull unsigned long long
#define base 200807
#define mod 212370440130137903
using Kagamine Rin;
const ull N=1e6+5;
ull n,ans=0,as[N],t[N],pr[N],ls[N];
unordered_map<ull,ull> pre,lst,tj;
struct node{
	ull l,r;
	ull sum;
}a[N<<2];
void push_up(ull aa){
	a[aa].sum=a[aa<<1].sum+a[aa<<1|1].sum;
}
void build(ull aa,ull l,ull r){
	a[aa].l=l;
	a[aa].r=r;
	if(l==r){
		a[aa].sum=tj[l];
		return ;
	}
	ull mid=(l+r)>>1;
	build(aa<<1,l,mid);
	build(aa<<1|1,mid+1,r);
	push_up(aa);
}
void modify(ull aa,ull lr){
	if(a[aa].l==a[aa].r){
		a[aa].sum--;
		return ;
	}
	ull mid=(a[aa].l+a[aa].r)>>1;
	if(lr<=mid)
		modify(aa<<1,lr);
	else
		modify(aa<<1|1,lr);
	push_up(aa);
}
ull query(ull aa,ull l,ull r){
	if(a[aa].l>=l&&a[aa].r<=r)
		return a[aa].sum;
	ull asd=0,mid=(a[aa].l+a[aa].r)>>1;
	if(l<=mid)
		asd+=query(aa<<1,l,r);
	if(r>mid)
		asd+=query(aa<<1|1,l,r);
	return asd;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ull i=1;i<=n;i++){
		cin>>as[i];
		t[i]=as[i];
	}
	sort(t+1,t+n+1);
	ull m=unique(t+1,t+n+1)-t-1;
	for(ull i=1;i<=n;i++)
		as[i]=lower_bound(t+1,t+m+1,as[i])-t;
	for(ull i=1;i<=n;i++)
		pr[i]=++pre[as[i]];
	for(ull i=n;i>=1;i--){
		ls[i]=++lst[as[i]];
		tj[ls[i]]++;
	}
	build(1,1,n);
	for(ull i=1;i<=n;i++){
		modify(1,ls[i]);
		if(pr[i]-1<1) continue;
		ans+=query(1,1,pr[i]-1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定一个 $n$ 个元素的序列 $a$，设 $f(i, j, x)$ 表示 $a_i \sim a_j$ 中 $x$ 出现次数，求有多少对 $i, j$ 满足 $i < j$ 且 $f(1, i, a_i) > f(j, n, a_j)$。

## 解法

令 $p_i =f(1, i, a_i), g_i = f(i, n, a_i)$，那么我们可以将这些操作转化成逆序对问题。

$O(n)$ 处理 $p, g$ 序列，$O(n \log n)$ 值域线段树维护逆序对个数即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define int unsigned long long

const int N = 1e6 + 5;

int n, a[N], cnta[N], cntb[N];
int ca[N], cb[N];
vector<int> b;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, sum;
	}tr[N << 2];
	void push_up(int u)
	{
		tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int x)
	{
		if (tr[u].l == tr[u].r)
		{
			tr[u].sum++;
			return;
		}
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) update(u << 1, x);
		else update(u << 1 | 1, x);
		push_up(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].sum;
		int mid = tr[u].l + tr[u].r >> 1, res = 0;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res += query(u << 1 | 1, l, r);
		return res;
	}
};

SegmentTree seg;

int main()
{
	scanf("%llu", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%llu", &a[i]);
		b.push_back(a[i]);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
	for (int i = 1; i <= n; i++)
	{
		ca[a[i]]++;
		cnta[i] = ca[a[i]];
	}
	for (int i = n; i >= 1; i--)
	{
		cb[a[i]]++;
		cntb[i] = cb[a[i]];
	}
	int ans = 0;
	seg.build(1, 1, n);
	for (int i = n; i >= 1; i--)
	{
		ans += seg.query(1, 1, cnta[i] - 1);
		seg.update(1, cntb[i]);
	}
	printf("%llu\n", ans);
	return 0;
}
```


---

## 作者：Saber_Master (赞：0)

[CF459D Pashmak and Parmida's problem](https://www.luogu.com.cn/problem/CF459D)

考虑到本题有关函数为$f(1, i, a_i)$和$f(j, n, a_j)$,不难看出这两个函数的值只与$i, j$的值有关，也就是一元函数.于是我们可以将问题简化，拆分成两个更简单的一元函数.$$f_1(i)=f(1, i, a_i)$$  $$f_2(i)=f(i, n, a_i)$$

这个直接维护$cnt$数组扫两遍就可以轻松求出.

接下来问题转化为：已知两个序列$f_1, f_2$,问有多少个点对$(i, j)$满足$f_1(i)<f_2(j)$且$i<j$.典型二维偏序，倒序扫描树状数组维护即可.

$O(nlogn)$

核心代码

```cpp
ll n, num[N], lsh[N], h;
ll f1[N], f2[N], p1[N], p2[N];

namespace bit{
	ll f[N];
	
	inline void add(ll x){
		for (; x<=n; x+=x&-x) ++f[x];
	}
	
	inline ll ask(ll x){
		ll res=0;
		for (; x; x-=x&-x) res+=f[x];
		return res;
	}
}

long long res;
int main(){
	read(n);
	for (R ll i=1; i<=n; i++) read(num[i]), lsh[++h]=num[i];
	sort(lsh+1, lsh+h+1);
	h=unique(lsh+1, lsh+h+1)-lsh-1;
	for (R ll i=1; i<=n; i++)
		num[i]=lower_bound(lsh+1, lsh+h+1, num[i])-lsh;
	for (R ll i=1; i<=n; i++) f1[i]=++p1[num[i]];
	for (R ll i=n; i; i--) f2[i]=++p2[num[i]];
	for (R ll j=n; j; j--){
		res+=bit::ask(f1[j]-1);
		bit::add(f2[j]);
	}
	writeln(res);
}
```


---

## 作者：Cylete (赞：0)

首先$a_i <= 10^9$先离散化

一个很$naive$的想法是先$O(n)$预处理除所有的$f(1, i, a_i)$和$f(j, n, a_j)$分别存在$f_1$和$f_2$中

我们考虑一个位置$i$对答案的贡献

显然只有$f_2[j] < f_1[i]$的$j$才对答案有贡献

那我们就可以维护一个树状数组

倒着枚举统计答案即可

```cpp
const int N = 1e6 + 10;

int n, ans;
int a[N], lsh[N], qaq;
int num1[N], num2[N], f1[N], f2[N];
int tree[N];

inline void add(int x)
{
	for(; x <= n; x += x & -x) tree[x] += 1;
}

inline int ask(int x)
{
	int res = 0;
	for(; x; x -= x & -x) res += tree[x];
	return res;
}

signed main()
{
	read(n);
	for(R int i = 1; i <= n; i++) read(a[i]), lsh[i] = a[i];
    //离散
	sort(lsh + 1, lsh + n + 1);
	qaq = unique(lsh + 1, lsh + n + 1) - lsh - 1;
	for(R int i = 1; i <= n; i++) a[i] = lower_bound(lsh + 1, lsh + qaq + 1, a[i]) - lsh;
    //预处理f1 f2
	for(R int i = 1; i <= n; i++)
	{
		num1[a[i]]++;
		f1[i] = num1[a[i]];
	}
	for(R int i = n; i >= 1; i--)
	{
		num2[a[i]]++;
		f2[i] = num2[a[i]];
	}
    //倒着枚举统计答案
	for(R int i = n; i >= 1; i--)
	{
		ans += ask(f1[i] - 1);
		add(f2[i]);
	}
	writeln(ans);
	return 0;
}
```

---

