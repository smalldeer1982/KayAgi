# [USACO21OPEN] United Cows of Farmer John G

## 题目描述

农夫约翰合牛国（The United Cows of Farmer John，UCFJ）将要选派一个代表队参加国际牛学奥林匹克（International bOvine olympIad，IOI）。

有 $N$
头奶牛参加了代表队选拔。她们站成一行，奶牛 $i$ 的品种为 $b_i$。

代表队将会由包含至少两头奶牛的连续区间组成——也就是说，对于满足 $1\le l<r\le N$
的奶牛 $l\dots r$。最边上的奶牛会被指定为**领队**。为了避免种内冲突，每一名领队都必须与代表队的其他成员（**包括领队**）品种不同。

请帮助 UCFJ 求出他们可以选派参加 IOI 的代表队的方法数。 

## 说明/提示

#### 样例解释

每一代表队对应以下的一对领队：
$$(1,2),(1,3),(1,4),(1,7),(2,3),(2,4),(3,4),(4,5),(4,6),(4,7),(5,6),(5,7),(6,7).$$

#### 数据范围与约定

$1\le N\le 2\times 10^5$ 。

## 样例 #1

### 输入

```
7
1 2 3 4 3 2 5```

### 输出

```
13```

# 题解

## 作者：_zy_ (赞：10)

## [题目传送门](https://www.luogu.com.cn/problem/P7527)

**题目大意：**

求区间 $[l,r]$ 的数的种类。

对于以i为开头的方案数，只要保证让结尾不等于这段区间的数字，也即让结尾是该数字靠前出现的位置。

**代码实现**

可以从 $n$ 到 $ 1$ 枚举开头。

不断更新靠前的位置。


- **树状数组维护种类**

更改：


定义数组 $tre$e 表示种类数，当有一个新元素加入时，现将上一个位置上的种类数 -1，然后再让新加入的位置种类数 +1。

（一开始的位置可以设置成 $n+1$ ）

查询：

先前位置的前一个元素的种类数。

### 时间复杂度： $\mathcal{O}_{nlogn}$

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack> 
#define lowbit(x) x & -x;
#define int long long 
#define N 400010
using namespace std;
int re() {
	int p=0; char i=getchar();
	while(i<'0'||i>'9')	i=getchar();
	while(i>='0'&&i<='9')	p=p*10+i-'0',i=getchar();
	return p;
}
int n,ans;
int a[N],f[N];
int tree[N];
int ask(int x) {
	int sum=0;
	while(x>0) {
		sum+=tree[x];
		x-=lowbit(x);
	}
	return sum;
}
void add(int x,int k)
{
	while(x<=2*n) {
		tree[x]+=k;
		x+=lowbit(x);
	}	
}
signed main()
{
	n=re();
	for(int i=1;i<=n;i++) {
		a[i]=re();
		f[i]=n+1;
	}
	for(int i=n;i>=1;i--)
	{
		ans+=ask(f[a[i]]-1);
		add(f[a[i]],-1);
		f[a[i]]=i;
		add(f[a[i]],1);
	}
	cout<<ans<<endl;
}
```
**如有不妥，请不要吝啬您的评论。**

$qwq$

[双倍经验](https://www.luogu.com.cn/problem/P1972)

[三倍经验](https://www.luogu.com.cn/problem/SP3267)



---

## 作者：pigstd (赞：7)

提供一个简单的 $O(n\log n)$ 写法，感觉这题还是蛮套路的。

对于每只牛 $i$，提前预处理出当它作为左端点或者右端点的时候，往右或者往左最远能到哪里，设为 $r_i,l_i$。这个过程可以用一个桶正反扫一遍解决。

考虑一个 $[a,b]$ 什么时候满足条件：$r_a\ge b \And l_b \le a$。考虑枚举左端点 $a$，那么就需要迅速算出 $[a,r_a]$ 之间所有满足 $l_b \le a$ 的 $b$ 的数量。

新建一个数组 $c$，$c_i$ 表示在此时，$l_i $ 是否 $\le a$。那么从大到小枚举 $i$，每次让所有 $l_x = i+1$ 的 $c_x$ 设置成 $0$（即减一），显然每个数只会减去一次。这部分过程可以用 `vector` 解决。

$[a,r_a]$ 之间所有满足 $l_b \le a$ 的 $b$ 的数量就相当于 $\displaystyle \sum_{i=a}^{r_a} c_i$。单点修改，区间查询，你想到了什么？

用树状数组维护 $c$ 就可以了。一开始 $c_i=1$。注意到长度至少为 $2$，而每个形如 $[a,a]$ 的区间都会被统计到，那么把答案减去 $n$ 就可以了。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define WT int T=read();while(T--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int M=2e5+10;
int n,a[M],t[M],l[M],r[M],ans;
vector<int>v[M];

struct BIT
{
	int c[M];
	int lowbit(int x){return x&(-x);}
	void add(int x,int k){for (int i=x;i<=n;i+=lowbit(i))c[i]+=k;}
	int ask(int x)
	{
		int res=0;
		for (int i=x;i>=1;i-=lowbit(i))res+=c[i];
		return res;
	}
	int query(int l,int r){return ask(r)-ask(l-1);}
}T;

signed main()
{
	n=read();
	for (int i=1;i<=n;i++)
		a[i]=read(),l[i]=t[a[i]]+1,t[a[i]]=i;
	for (int i=1;i<=n;i++)t[i]=0;
	for (int i=n;i>=1;i--)
		r[i]=t[a[i]]==0?n:t[a[i]]-1,t[a[i]]=i;
	for (int i=1;i<=n;i++)
		T.add(i,1),v[l[i]].pb(i);
	for (int i=n;i>=1;i--)
	{
		for (int j=0;j<v[i+1].size();j++)
		{
			int x=v[i+1][j];
			T.add(x,-1);
		}ans=ans+T.query(i,r[i]);
	}cout<<ans-n<<endl;
	return 0;
}
```

---

## 作者：Thunder_S (赞：4)

[可能更好的阅读体验。](https://www.cnblogs.com/Livingston/p/15141078.html)

## Solution

自然的想法是枚举每个位置作为左端点，往后扩展，更新答案。

其实可以考虑遍历每个位置，求出以这个位置为右端点的方案数。

首先处理出每个数字上次出现的位置 $last_i$，那么对于右端点 $i$，合法的左端点只能在 $last_i+1$ 到 $i-1$ 中找。

当遍历到每个点时，我们令它的权值为 1，代表着这个点可以作为一种左端点的方案。

同时令它的上一个点的权值为 0，因为它无法再次成为左端点。

最后对于右端点 $i$，它的贡献就是 $last_i+1$ 到 $i-1$ 里 1 的个数。

单点修改，区间查询，随便搞个线段树或者树状数组即可。

时间复杂度 $O(n\log n)$​。

## Code

```cpp
#include<cstdio>
#define ll long long
#define N 200005
using namespace std;
int n,a[N],t[N],pre[N],tree[N<<2];
ll ans;
void modify(int now,int l,int r,int p,int v)
{
	if (l==p&&r==p)
	{
		tree[now]=v;
		return;
	}
	int mid=(l+r)>>1;
	if (p<=mid) modify(now<<1,l,mid,p,v);
	else modify(now<<1|1,mid+1,r,p,v);
	tree[now]=tree[now<<1]+tree[now<<1|1];
}
int query(int now,int l,int r,int p,int q)
{
	if (l>=p&&r<=q) return tree[now];
	int mid=(l+r)>>1;
	int res=0;
	if (p<=mid) res+=query(now<<1,l,mid,p,q);
	if (q>mid) res+=query(now<<1|1,mid+1,r,p,q);
	return res;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;++i)
	{
		pre[i]=t[a[i]];
		t[a[i]]=i;
	}
	for (int i=1;i<=n;++i)
	{
		modify(1,0,n,pre[i],0);
		modify(1,0,n,i,1);
		ans+=(ll)query(1,0,n,pre[i]+1,i);
	}
	printf("%lld\n",(ll)ans-n);
	return 0;
}
```



---

## 作者：Microperson (赞：4)

### [题目](https://www.luogu.com.cn/problem/P7527)
### 题目大意：
就是寻找从$1$到$n$中有多少对"领队",保证区间内不含有两端元素。
### 解题思路：
其实这道题和[HH的项链](https://www.luogu.com.cn/problem/P1972)很像，但是这道题没有多次询问，就不用排序处理了（~~相对简单~~）。

- 第一步，我们要思考如何做才能跑过$10^5$，显然$n^2$暴力肯定不行的，一般都是要带$log$级别的，而且还是要处理一段序列上的东西，那我们自然而然就想到的是树状数组、线段树了。
- 第二步，我们想应如何用这来处理（在这里我用的是树状数组）。从$1$到$n$处理?还是从$n$到$1?$,这里到这来还是比较好处理的。
- 第三步，如何进行树状数组维护。我们发现我们只需要计算出$l$到$r$之间有多少个品种就表示领队数（自己考虑一下）。所以只需要倒着扫一遍，同时处理$ans$和$c[x]$就行了。
### 新鲜出炉的code：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define N 500010
#define int long long
using namespace std;
int n,b[N],a[N],c[N],ans;

int lowbit(int x){
	return x & -x; 
}

void add(int x,int y){
	for(;x<=n;x+=lowbit(x)) c[x]+=y;
}


int ask(int x){
	int ans=0;
	for(;x;x-=lowbit(x)) ans+=c[x];
	return ans;
}
//以上是树状数组基本操作
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		a[i]=n+1;  //开始时要都赋为n+1,因为要倒着来;
	}
	for(int i=n;i>=1;i--){
		ans+=ask(a[b[i]]-1);  
		add(a[b[i]],-1);  //当出现重复数字时，将原来加过的减回去。
		add(i,1); //将重复的改为下一个，或是将新的种类加入
		a[ b[i] ]=i;//更改位置
	} //这里为什么要先加再更改？请读者自行体会，毕竟代码都是自己经过思考后才出来的，可以根据样例推一下
	cout<<ans<<endl;
	return 0;
}
```
如有不妥之处还请指正。

---

## 作者：tiger2005 (赞：2)

### 题意简述

给定一个序列 $a_i$，求出区间个数 $[l,r]\ (l<r)$，使得 $a_l$ 不等于其他的数字，$a_r$ 不等于其他的数字。

### 分析

根据第一个限制，我们求出在 $i$ 后面第一个和 $a_i$ 一样的位置 $\operatorname{nxt}[i]$，同理定义 $\operatorname{prv}[i]$。那么对于每一个左端点，右端点的取值范围就在 $(l,\operatorname{nxt}[l])$ 中间。

考虑到对于一个右端点 $r$ 的限制就是 $\operatorname{prv}[r] \leq l$，那么我们只需要求出在这个范围中满足这个条件的数字个数就行。

解决方法有很多。你可以将 $(i,\operatorname{prv}[i])$ 作为一个点进行二维数点，使用 CDQ 分治或者树状数组解决，也可以直接用可持久化线段树维护 $\operatorname{prv}$ 数组求出答案。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
int tr[4000010];
int c[4000010][2],nn;
int ad(int o,int l,int r,int p){
	int ret=++nn;
	c[ret][0]=c[o][0];
	c[ret][1]=c[o][1];
	tr[ret]=tr[o]+1;
	if(l==r)	return ret;
	int m=(l+r)>>1;
	if(p<=m)	c[ret][0]=ad(c[o][0],l,m,p);
	else	c[ret][1]=ad(c[o][1],m+1,r,p);
	return ret;
}
int que(int o1,int o2,int l,int r,int ll,int rr){
	if(ll<=l && r<=rr)	return tr[o2]-tr[o1];
	int m=(l+r)>>1;
	int ret=0;
	if(ll<=m)	ret+=que(c[o1][0],c[o2][0],l,m,ll,rr);
	if(rr>m)	ret+=que(c[o1][1],c[o2][1],m+1,r,ll,rr);
	return ret;
}
int N,A[200010],B[200010];
int prv[200010],nxt[200010],rt[200010];
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++)	scanf("%d",&A[i]);
	for(int i=1;i<=N;i++)	B[i]=0;
	for(int i=1;i<=N;i++){
		if(B[A[i]]==0)	prv[i]=1;
		else	prv[i]=B[A[i]];
		B[A[i]]=i;
	}
	for(int i=1;i<=N;i++)	B[i]=0;
	for(int i=N;i;i--){
		if(B[A[i]]==0)	nxt[i]=N+1;
		else	nxt[i]=B[A[i]];
		B[A[i]]=i;
	}
	for(int i=1;i<=N;i++)
		rt[i]=ad(rt[i-1],1,N,prv[i]);
	long long ans=0;
	for(int i=1;i<=N;i++)
		ans+=que(rt[i],rt[nxt[i]-1],1,N,1,i);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：ZaireEmery (赞：1)

考虑枚举左端点 $l$，设下一个和 $l$ 品种相同的牛的位置为 $next$。

根据题意，在 $l$ 到右端点 $r$ 之间，不能存在一头牛和 $l$ 品种相同，所以 $r < next$。

容易发现，$b[r]$ 和 $b[l],...,b[r-1]$ 都不同，当且仅当 $b[r]$ 在 $b[l],...,b[r]$ 中第一次出现。所以，对于每一种在 $l+1$ 到 $next-1$ 中出现的品种，其第一次出现的位置都可以被作为右端点。右端点的数量即为在 $l+1$ 到 $next-1$ 中出现的品种的数量。

这题就被转化成了一个区间数颜色题，可以用莫队求解。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
int a[200010],cnt[200010],cur;
vector<int> v[200010];
vector<pair<int,int> > p;
bool cmp(pair<int,int> a,pair<int,int> b){
	if(a.first/500!=b.first/500)
		return a.first<b.first;
	return a.second<b.second;
}
void add(int x){
	cnt[x]++;
	if(cnt[x]==1)
		cur++;
}
void del(int x){
	cnt[x]--;
	if(cnt[x]==0)
		cur--;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		v[i].push_back(0);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		v[a[i]].push_back(i);
	}
	for(int i=1;i<=n;i++)
		v[i].push_back(n+1);
	for(int i=1;i<=n;i++)
		for(int j=2;j<v[i].size();j++)
			if(v[i][j-1]<v[i][j]-1)
				p.push_back(make_pair(v[i][j-1]+1,v[i][j]-1));
	sort(p.begin(),p.end(),cmp);
	int l=1,r=0;
	for(int i=0;i<p.size();i++){
		while(l<p[i].first){
			del(a[l]);
			l++;
		}
		while(l>p[i].first){
			l--;
			add(a[l]);
		}
		while(r<p[i].second){
			r++;
			add(a[r]);
		}
		while(r>p[i].second){
			del(a[r]);
			r--;
		}
		ans+=cur;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：yaoxi (赞：1)

# **USACO 2021 US Open, Gold**
## **Problem 1. United Cows of Farmer John (FJ联合牛)**
----

### **题目描述**
Farmer John有 $N$ 头奶牛参选International bOvine Olympiad (IOI?)代表团 $(1 \le N \le 2 \times 10 ^ 5)$ . 它们站成一排，第 $i$ 头牛的品种为 $b_i$ .

代表团是一个至少有两头牛的连续子序列，即区间 $[l, r]$ 中的牛，满足 $1 \le l < r \le N$ . 子序列两端的牛即为代表团的领导。为了避免种族歧视，每个领导必须与其余的代表团成员有着不同的品种(包括另一个领导)。

帮助UCFJ (FJ联合牛) 确定选择代表团的方案数以发送给IOI。

### **输入格式**
第一行一个整数 $N$ .

第二行包括 $N$ 个整数 $b_1, b_2, ..., b_N$ , 均在区间 $[1, N]$ 中。

### **输出格式**
一行一个整数，即选取代表团的方案数。

**注意：最终的答案可能需要64位整型数字(例如C++中的long long)**

### **样例输入**
```
7
1 2 3 4 3 2 5
```

### **样例输出**
```
13
```

### **样例解释**
有一下几种可能的领导者方案:
$$(1,2),(1,3),(1,4),(1,7),(2,3),(2,4),(3,4),(4,5),(4,6),(4,7),(5,6),(5,7),(6,7).$$

### **数据**
- 测试点 1-3  保证 $N \le 100$ .
- 测试点 4-8  保证 $N \le 5000$ .
- 测试点 9-20 无特殊要求.

供题人: Benjamin Qi

题目翻译: yaoxi-std

----
## **题解**
前8个点直接暴力

很显然，对于每个子序列的左端点，其右端点的下标一定小于后一个与左端点同品种的牛的下标。并且右端点的前一个同品种的牛的下标小于这个子序列的左端点。即用 $pre_i$ 表示第 $i$ 头牛前一个种类为 $b_i$ 的牛的下标（如果没有则为 $0$ ），用 $nxt_i$ 表示第 $i$ 头牛后一个种类为 $b_i$ 的牛的下标（如果没有则为 $N + 1$ ）。对于合法的区间 $[l, r]$ , 有
$$nxt_l > r$$
$$pre_r < l$$

考虑用线段树来维护一个序列，这个序列的第 $i$ 项表示下标为 $i$ 的奶牛的前一个同品种的牛的下标是否小于当前的左端点，即 $pre_i$ 是否小于 $l$，然后从左到右枚举这个左端点，每次查询之后更新左端点这头奶牛，即将线段树下标为 $nxt_l$ 的节点加一。

时间复杂度 $O(n \log n)$ .

代码如下:

```cpp
/**
 * @file:           ucfj.cpp
 * @author:         yaoxi-std
 * @description:    ucfj.cpp
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define resetIO(x) { freopen(x".in", "r", stdin); freopen(x".out", "w", stdout); }
template<class T> inline void read(T &x){
    T f = 1; x = 0; char ch = getchar();
    for( ; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -f;
    for( ; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= f;
}
template<class T> inline void write(T x){
    if(x < 0) { putchar('-'); x = -x; }
    if(x > 9) write(x / 10); putchar((x % 10) ^ 48);
}
const int maxn = 2e5+5;
const int inf = 1LL << 60;
// 线段树模版，其实不需要区间修改的
#define li i << 1
#define ri (i << 1) | 1
#define lson li, l, mid
#define rson ri, mid + 1, r
struct SegTree{
    int nd[maxn << 2], lazy[maxn << 2], len[maxn << 2];
    void pushup(int i){
        nd[i] = nd[li] + nd[ri];
    }
    void getdown(int i, int val){
        nd[i] += val * len[i];
        lazy[i] += val;
    }
    void pushdown(int i){
        if(lazy[i]){
            getdown(li, lazy[i]);
            getdown(ri, lazy[i]);
            lazy[i] = 0;
        }
    }
    void build(int i, int l, int r){
        nd[i] = lazy[i] = 0; len[i] = r - l + 1;
        if(l == r) return;
        int mid = (l + r) >> 1;
        build(lson); build(rson);
        pushup(i);
    }
    void update(int i, int l, int r, int ql, int qr, int val){
        if(l > r) return;
        if(ql <= l && r <= qr){
            getdown(i, val);
            return;
        }
        int mid = (l + r) >> 1;
        if(ql <= mid) update(lson, ql, qr, val);
        if(qr > mid) update(rson, ql, qr, val);
        pushup(i);
    }
    int query(int i, int l, int r, int ql, int qr){
        if(l > r) return 0;
        if(ql <= l && r <= qr) return nd[i];
        int mid = (l + r) >> 1, ret = 0;
        pushdown(i);
        if(ql <= mid) ret += query(lson, ql, qr);
        if(qr > mid) ret += query(rson, ql, qr);
        return ret;
    }
} tr;
int n, b[maxn], pre[maxn], nxt[maxn], lst[maxn];
pair<int, int> qry[maxn];
signed main(){
    // 读入
    read(n);
    for(int i=1; i<=n; i++) read(b[i]);
    // 预处理pre和nxt数组，即前一头和后一头同品种奶牛的位置
    for(int i=1; i<=n; i++) lst[i] = 0;
    for(int i=1; i<=n; i++){
        pre[i] = lst[b[i]];
        lst[b[i]] = i;
    }
    for(int i=1; i<=n; i++) lst[i] = n + 1;
    for(int i=n; i>=1; i--){
        nxt[i] = lst[b[i]];
        lst[b[i]] = i;
    }
    // 构造初始线段树
    tr.build(1, 1, n);
    int ans = 0;
    for(int i=1; i<=n; i++)
        if(pre[i] == 0)
            tr.update(1, 1, n, i, i, 1);
    // 主算法部分，枚举左端点
    for(int i=1; i<=n; i++){
        int l = i + 1, r = nxt[i] - 1;
        // 查询区间[l,r]的合法右端点数量
        ans += tr.query(1, 1, n, l, r);
        // 更新
        if(nxt[i] >= 1 && nxt[i] <= n)
            tr.update(1, 1, n, nxt[i], nxt[i], 1);
    }
    // 输出
    write(ans); putchar('\n');
    return 0;
}
```

---

## 作者：冷笑叹秋萧 (赞：0)

#  [USACO21OPEN] United Cows of Farmer John G
## 题意
问存在多少个区间 $[l,r]$ ，使 $b[l],b[r]$ 不等于区间内的所有数（ $b[l] ≠ b[r]$ ）。
## 题解
仔细阅读题目，我们可以发现其实可以把题目转化一下。

假设 $b[i]$ 是队头的领队，在合法的情况下，这个队列是不能有其他等于 $b[i]$ 的数的，也就是说，最多可以延伸到数字 $b[i]$ 上一个出现的位置减一。

那么这个题目就变成了数一段区间有多少种数字的问题了。

设 $last[i]$ 表示数字 $i$ 上一个出现的位置（初值赋值为 $n+1$ 即可）。

从 $n\sim1$ 扫，找出 $b[i]$ 与 $last[b[i]]-1$ 之间有多少个合法的数字（关于队尾的领队在之前就会处理过），将 $last[b[i]]$ 的值删除（因为队尾的领队也不能和队伍中的其他的数一样），更新 $last[b[i]]$ 的值，再插入这个位置。

然后我们可以发现其中的操作是只有单点修改，区间查询，所以随便用个线段树或者树状数组写写就行了（本人写的是线段树）。

~~其实这题还可以无脑套主席树模板，但是我不会。~~ 
## CODE
```cpp
#include<cstdio>
#include<string>
#define R register int
#define N 200005
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
int n,last[N],b[N];
ll tree[N<<2],ans;
int max(int a,int b) {return a>b?a:b;}
int min(int a,int b) {return a<b?a:b;}
void read(int &x)
{
	x=0;int f=1;char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();x*=f;
}
ll sum(int u,int l,int r,int x,int y)
{
	if (l>=x && r<=y) return tree[u];
	int mid=l+r>>1;ll res=0;
	if (x<=mid) res+=sum(u<<1,l,mid,x,y);if (y>mid) res+=sum(u<<1|1,mid+1,r,x,y);
	return res;
}
void ins(int u,int l,int r,int k,int x)
{
	if (l==r) {tree[u]+=x;return;}
	int mid=l+r>>1;
	if (k<=mid) ins(u<<1,l,mid,k,x);else ins(u<<1|1,mid+1,r,k,x);
	tree[u]=tree[u<<1]+tree[u<<1|1];
}
int main()
{
	read(n);
	for (R i=1;i<=n;++i) read(b[i]),last[i]=n+1;
	for (R i=n;i;--i)
	{
		ans+=sum(1,1,n+1,1,last[b[i]]-1);
		ins(1,1,n+1,last[b[i]],-1);
		last[b[i]]=i;ins(1,1,n+1,i,1);
	}
	printf("%lld\n",ans);
 	return 0;
}
```


---

## 作者：White_gugu (赞：0)

题意
-
求出满足一段区间中区间首和区间尾的数仅仅在此区间出现过一次的所有合法区间数。

方法
-
看数据范围，明显的 $O(n \log n)$ 

首先我们可以预处理出来 $b_{i}$ 可达的最左边和最右边，记为 $last_{i}$ 和 $next_{i}$  。

但是暴力去求解似乎是 $O(n^2)$ 的。。。肯定会被卡掉，所以观察数据范围，发现每一个 $b_{i}$ 都在 $[1,N]$ ，所以建立数组记录每一个种类最近出现的位置就可以线性求了。

根据题目限制，对于一组合法的 $i$ ， $j$ ，一定有：

 $last_{j}<i$ 且 $next_{i}>j$
 
我们将样例的每一个 $i$ 的对应区间画出来：

![](https://cdn.luogu.com.cn/upload/image_hosting/w1jtk0xs.png)

可以发现，对于每一组以 $i$ 为开头， $j$ 为结尾的合法区间，当且仅当 $j$ 的对应区间包含 $i$ 且 $i$ 的对应区间包含 $j$ 。



这时很容易想到线段树，但是总不能建 $n$ 棵线段树一一维护某一包含权值的区间数吧。。。

换一种思路来表示以 $i$ 为开头的合法区间数，发现合法区间数为：

$sum_{i+1,next_{i}}=sum_{i+1,n}-sum_{next_{i}+1,n}$

（ $sum_{a,b}$ 表示在 $a$ ~ $b$ 中对应区间包含 $i$ 的区间数）

这样，我们就找到了方法：

先将所有的对应区间进行线段树区间 $+1$ ，之后枚举   $i$ ，表示以 $i$ 为开头的方案数，每一次都要先把 $i$ 的对应区间 $-1$ ，不然会算重，这样就可以算出 $sum_{i+1,n}$ 了。

对于 $sum_{next_{i}+1,n}$ 我们可以先打上标记，等到枚举到时进行类似操作就可以了。

代码
-

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int b[200200];
bool bz[200200];
int last[200200];
int next[200200];
int to[200200];
long long tree[2000200];
long long tag[2000200];
int pop[200200];
long long ans=0;
void pushup(int k,int len1,int len2)
{
	tree[k*2]+=tag[k]*len1;
	tree[k*2+1]+=tag[k]*len2;
	tag[k*2]+=tag[k];
	tag[k*2+1]+=tag[k];
	tag[k]=0;
}
void add(int k,int l,int r,int L,int R,int x)
{
	if(L<=l&&r<=R)
	{
		tree[k]+=x;
		tag[k]+=x;
		return;
	}
	int mid=(l+r)/2;
	if(tag[k]!=0)
	pushup(k,mid-l+1,r-mid);
	if(L>mid)
	add(k*2+1,mid+1,r,L,R,x);
	else if(R<=mid)
	add(k*2,l,mid,L,R,x);
	else
	add(k*2,l,mid,L,mid,x),add(k*2+1,mid+1,r,mid+1,R,x);
	tree[k]=tree[k*2]+tree[k*2+1];
}
int query(int k,int l,int r,int d)
{
	if(l==r)
	return tree[k];
	int mid=(l+r)/2;
	if(tag[k])
	pushup(k,mid-l+1,r-mid);
	if(d<=mid)
	return query(k*2,l,mid,d);
	else 
	return query(k*2+1,mid+1,r,d);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		if(bz[b[i]])
		{
			last[i]=to[b[i]]+1;
			next[to[b[i]]]=i-1;
			to[b[i]]=i;
		}
		else
		{
			bz[b[i]]=1;
			to[b[i]]=i;
			last[i]=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(bz[b[i]])
		next[to[b[i]]]=n;
	}
	for(int i=1;i<=n;i++)
	add(1,1,n,last[i],next[i],1);
	for(int i=1;i<=n;i++)
	{
		add(1,1,n,last[i],next[i],-1);
        pop[next[i]+1]=i;
        ans=(ans+query(1,1,n,i));
        if(pop[i])
        ans=ans-query(1,1,n,pop[i]);
	}
	printf("%lld",ans);
}
```



---

## 作者：李若谷 (赞：0)



~~整场比赛就做出来这道题。~~

首先维护每一个数左边第一个和它相同的数的坐标。
设做个坐标为$l$，那么显然满足要求的数只可能在$l+1 \sim i-1$中，其中$i$是当前数的坐标。（这个是满足区间内没有一个和右端点相同的数）。

在$l+1 \sim i-1$中，假设存在一个数$x$出现若干次，那么只有在最后面的那个$x$作为左端点才能满足区间中没有数与左端点相同。

所以只需要维护区间不同个数即可。

这个可以仿照 [HH的项链](https://www.luogu.com.cn/problem/P1972)
的方法，用树状数组维护。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int N = 5*1e5+5;
int n,m;
long long ans = 0;
int vis[N],tree[N];
int last[N];


struct Cow
{
    int breed;
    int pos;
}a[N],b[N];

inline void read(int &x){
    char ch=getchar();int f=1;x=0;
    while(!isdigit(ch) && ch^'-') ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    x*=f;
}



bool cmp2(Cow x, Cow y)
{
    if(x.breed == y.breed) return x.pos < y.pos;
    return x.breed < y.breed;
}

inline int lowbit(int x){
    return x&(-x);
}

void modify(int p,int v){
    for(;p<=n;p+=lowbit(p))
        tree[p]+=v;
}

inline int query(int p){
    int res=0;
    for(;p;p-=lowbit(p))
        res+=tree[p];
    return res;
}

int main(){
    read(n);
    for(int i=1;i<=n;++i) {read(a[i].breed);a[i].pos = i;b[i].breed = a[i].breed;b[i].pos = a[i].pos;}

    sort(a+1,a+n+1,cmp2);
    for(int i=1;i<=n;i++)
    {
        if(a[i].breed == a[i-1].breed) last[a[i].pos] = a[i-1].pos;
        else last[a[i].pos] = 0;
    }
    int pow=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=pow;j<=i;++j){
            if(vis[b[j].breed]) modify(vis[b[j].breed],-1);
            modify(j,1);
            vis[b[j].breed]=j;
        }
        pow = i+1;
        ans += query(i-1)-query(last[i]);
    }
    
    cout<<ans<<endl;
    
    return 0;
}
```



------------
题外话

感觉这次金组题好难啊啊啊。。。


---

## 作者：7KByte (赞：0)

这里是单 $\log$ 做法。

首先我们固定右端点，可行的左端点就是区间颜色数，可以直接莫队解决。

同时区间数颜色可以离线树状数组或主席树解决。

我们对于每个点计算 $nxt_i$ 表示下一个颜色相同的位置，$pre_i$ 表示上一个颜色相同的位置。

那么固定右端点 $i$ 后，满足条件的左端点 $j$ 满足 $j>pre_i\ \land\ nxt_j>i$ 。不难发现这就是一个二维偏序，直接做即可。

时间复杂度$\rm O(N\log N)$

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,c[N],nxt[N],pre[N],u[N];
struct node{
	int s,l,r;
}a[N<<6];
#define ls a[x].l
#define rs a[x].r
#define S a[x].s
int idx,rt[N];
int build(int l,int r){
	int x=++idx;
	if(l==r)return x;
	int mid=(l+r)>>1;
	ls=build(l,mid);
	rs=build(mid+1,r);
	return x;
}
int change(int y,int l,int r,int pos,int val){
	int x=++idx;a[x]=a[y];a[x].s+=val;
	if(l==r)return x;
	int mid=(l+r)>>1;
	if(mid>=pos)ls=change(a[y].l,l,mid,pos,val);
	else rs=change(a[y].r,mid+1,r,pos,val);
	return x;
}
int ask(int x,int l,int r,int L,int R){
	if(L>=l&&R<=r)return S;
	int mid=(L+R)>>1,sum=0;
	if(mid>=l)sum+=ask(ls,l,r,L,mid);
	if(mid<r)sum+=ask(rs,l,r,mid+1,R);
	return sum;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&u[i]);
	rep(i,1,n){
		if(c[u[i]])pre[i]=c[u[i]],nxt[c[u[i]]]=i;
		c[u[i]]=i;
	}
	rt[0]=build(1,n);long long ans=0;
	//rep(i,1,n)printf("%d ",nxt[i]);putchar('\n');
	//rep(i,1,n)printf("%d ",pre[i]);putchar('\n');
	rep(i,1,n){
		ans+=ask(rt[i-1],1,i,1,n);
		if(pre[i])ans-=ask(rt[pre[i]],1,i,1,n);
		rt[i]=change(rt[i-1],1,n,i,1);
		if(nxt[i])rt[i]=change(rt[i],1,n,nxt[i],-1);
		//cout<<ans<<endl;
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：cmll02 (赞：0)

我们思考对于一个右端点 $i$，有哪些状态是合法的。

显然整个区间不能包含其他的 $a_i$。

对于每一种出现的品种，都是一种可行的方案。

那直接区间数颜色即可。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#define int long long
/*char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)*/
inline int read()
{
	int num = 0,f=1; char c = getchar();
	while (c<48 || c>57)f=(c=='-'?-1:f),c = getchar();
	while (c >= 48 && c <= 57)num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
	return num*f;
};
int ans; 
const int B=305;
int a[1000005],b[1000005],c[1000005];
struct qaq{
	int l,r,i,lB;
	bool operator<(const qaq& b)const
	{
		return (lB==b.lB)?(((lB)&1)?r<b.r:r>b.r):l<b.l;
	}
}q[1000005];
/*
inline void add(int k)
{
	(b[a[k]]++)?0:ans++;
}
inline void rmv(int k)
{
	(--b[a[k]])?0:ans--;
}*/
/*#define rmv(k) ans-=!(--b[a[(k)]])
#define add(k) ans+=!(b[a[(k)]]++)*/
inline void rmv(int k)
{
    ans-=!(--b[a[k]]);
}
inline void add(int k)
{
	ans+=!(b[a[k]]++);
}
int d[5000005];
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int lst[1000005],pre[100005*4];
signed main()
{
	int n=read(),anss=0;
	//int m=read();
	//puts("Pf");
	for(int i=1;i<=n;i++)
    {
        a[i]=read();
        pre[i]=lst[a[i]];
        lst[a[i]]=i;
    }
	for(int i=2;i<=n;i++)q[i].l=pre[i]+1,q[i].lB=q[i].l/B,q[i].r=i-1,q[i].i=i;
	std::sort(q+2,q+1+n);
	register int cl=1,cr=0;
	for(register int i=2;i<=n;i++)
	{
		int L=q[i].l,R=q[i].r;
		while(cl<L)rmv(cl++);
		while(cl>L)add(--cl);
		while(cr>R)rmv(cr--);
		while(cr<R)add(++cr);
        anss+=ans;
        //printf("%lld %lld : %lld\n",L,R,ans);
		//printf("%d\n",ans);
		/*int p=gcd(ans-R+L-1,(R-L)*(R-L+1));
		if(p==0)
		{
		    c[q[i].i]=0;d[q[i].i]=1;
		    continue;
		}
		c[q[i].i]=(ans-R+L-1)/p;
		d[q[i].i]=(R-L)*(R-L+1)/p;*/
	}
    printf("%lld\n",anss);
//	for(int i=1;i<=m;i++)printf("%lld/%lld\n",c[i],d[i]);
}
```

---

