# Pillars

## 题目描述

Marmot found a row with $ n $ pillars. The $ i $ -th pillar has the height of $ h_{i} $ meters. Starting from one pillar $ i_{1} $ , Marmot wants to jump on the pillars $ i_{2} $ , ..., $ i_{k} $ . ( $ 1<=i_{1}<i_{2}<...<i_{k}<=n $ ). From a pillar $ i $ Marmot can jump on a pillar $ j $ only if $ i<j $ and $ |h_{i}-h_{j}|>=d $ , where $ |x| $ is the absolute value of the number $ x $ .

Now Marmot is asking you find out a jump sequence with maximal length and print it.

## 说明/提示

In the first example Marmot chooses the pillars $ 1 $ , $ 2 $ , $ 3 $ , $ 5 $ with the heights $ 1 $ , $ 3 $ , $ 6 $ , $ 4 $ . Another jump sequence of length $ 4 $ is $ 1 $ , $ 2 $ , $ 4 $ , $ 5 $ .

## 样例 #1

### 输入

```
5 2
1 3 6 7 4
```

### 输出

```
4
1 2 3 5 
```

## 样例 #2

### 输入

```
10 3
2 1 3 6 9 11 7 3 20 18
```

### 输出

```
6
1 4 6 7 8 9 
```

# 题解

## 作者：Priori_Incantatem (赞：5)

### 题目大意
给出一个长度为 $n$ 的序列 $a$ 和一个参数 $m$，要求求出一个最长的子序列，满足相邻元素的差大于等于 $m$

### 解题思路

本题跟LIS的 $\operatorname{O}(n\log n)$ 做法非常相似，需要用到桶。

首先，我们要将 $a[i]$ 离散化。
设 $f[i]$ 表示以 $a[i]$ 结尾的最长满足条件的子序列的长度，$pre[i]$ 表示 $f[i]$ 从 $f[pre[i]]$ 转移过来。  
朴素转移：$f[i]=\max\limits_{|b[i]-b[j]\ge m|}\{f[j]\}+1$。  
这里的 $b[i]$ 表示离散化之前的 $a[i]$。

我们考虑用桶优化：  
设桶 $bin[j]$ 表示以 $j$ 结尾的序列的最长长度，$pos[j]$ 表示与 $bin[j]$ 对应的结尾元素的编号。  
由于 $a[i]$ 已经被离散化了，我们需要用二分查找出与 $i$ 最接近的 $l[i],r[i]$，满足 $1\le l[i] \le i \le r[i] \le n$，且 $a[i]-a[l[i]] \ge  m$ 且 $a[r[i]]-a[i] \ge m$。

那么，转移方程就变成了 $f[i]=\max\limits_{1 \le j \le l[i] \operatorname{or} r[i] \le j \le n} \{ bin[j] \}+1$。  
由于涉及到区间最值，我们可以用线段树维护，总时间复杂度 $\operatorname{O}(n \log n)$。  
注意每次要更新 $bin$ 和 维护 $pre[i]$。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int Maxn=100000+10,inf=0x3f3f3f3f;
const int Maxm=Maxn<<2;
int maxv[Maxm],p[Maxm];
long long a[Maxn],b[Maxn];
int f[Maxn],pre[Maxn];
int n,m,idcnt;
map <long long,int> id;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void push_up(int k)
{
	if(maxv[k<<1]>maxv[k<<1|1])
	maxv[k]=maxv[k<<1],p[k]=p[k<<1];
	else maxv[k]=maxv[k<<1|1],p[k]=p[k<<1|1];
}
void modify(int k,int l,int r,int pos,int u,int v)
{
	if(l==r)
	{
		maxv[k]=u,p[k]=v;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)modify(k<<1,l,mid,pos,u,v);
	else modify(k<<1|1,mid+1,r,pos,u,v);
	push_up(k);
}
int query(int k,int l,int r,int x,int y,int &pos)
{
	if(x<=l && r<=y)
	{
		pos=p[k];
		return maxv[k];
	}
	int mid=(l+r)>>1,tot,cnt;
	int u,v;tot=cnt=0;
	if(x<=mid)tot=query(k<<1,l,mid,x,y,u);
	if(mid<y)cnt=query(k<<1|1,mid+1,r,x,y,v);
	if(tot>cnt){pos=u;return tot;}
	else {pos=v;return cnt;}
}
void calc(int i,int &x,int &y)
{
	int l=1,r=i;
	if(b[i]-b[l]<m){x=0;goto GG;}
	while(l<r)
	{
		int mid=(l+r)>>1;
		++mid;
		if(b[i]-b[mid]<m)r=mid-1;
		else l=mid;
	}
	x=l;
	GG:
	l=i,r=idcnt;
	if(b[r]-b[i]<m){y=0;goto FF;}
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(b[mid]-b[i]<m)l=mid+1;
		else r=mid;
	}
	y=l;
	FF:;
}
void dfs(int x)
{
	if(pre[x])dfs(pre[x]);
	printf("%d ",x);
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	a[i]=b[i]=read();
	sort(b+1,b+1+n);
	for(int i=1;i<=n;++i)
	{
		b[++idcnt]=b[i];
		id[b[idcnt]]=idcnt;
		int j=i+1;
		while(j<=n && b[i]==b[j])++j;
		i=j-1;
	}
	for(int i=1;i<=n;++i)
	{
		int x,y,pos;
		calc(id[a[i]],x,y);
		f[i]=1;
		if(x)
		{
			int tmp=query(1,1,idcnt,1,x,pos);
			if(tmp+1>f[i])
			f[i]=tmp+1,pre[i]=pos;
		}
		if(y)
		{
			int tmp=query(1,1,idcnt,y,idcnt,pos);
			if(tmp+1>f[i])
			f[i]=tmp+1,pre[i]=pos;
		}
		modify(1,1,idcnt,id[a[i]],f[i],i);
	}
	int ans=-1,pos;
	for(int i=1;i<=n;++i)
	if(f[i]>ans)
	ans=f[i],pos=i;
	printf("%d\n",ans);
	dfs(pos);
	putchar('\n');
	return 0;
}
```


---

## 作者：E_huan (赞：4)

## 线段树优化DP

#### 线段树优化 DP：

一般是对于一个 $O(n^2)$ 的DP，状态数为 $O(n)$ 或者可以化成 $O(n)$（比如 $f[i][j]$ 中 $i$ 的含义是考虑到第几个，这一维度可以省略），转移是区间操作（从区间最值转移/给区间加减/求和......），就可以用线段树优化，把转移变成 $O(\log n)$，总时间复杂度变成 $O(n \log n)$。（当然 $O(n^2)$ 转移变成 $O(\log n)$ 也不是一个死范围，比如 CF597C 就是 $O(n^2k)$ 转移变成 $O(nk \log n)$ ，而 $k≤10$，时间复杂度仍然可以接受）。

#### 本题：

首先不难发现一个 $O(n^2)$ 的 DP：

$f[i]$ 表示考虑前 $i$ 个数，子序列末尾是 $i$ 的最长序列。

转移就枚举前一位的位置 $j$：$f[i]=\max\limits_{|a[i]-a[j|≤d \land 1≤j<i }\{f[j]\}+1$。

发现虽然转移本身看起来不是区间求 $max$，但其实它们的值域是两个区间（比 $a[i]$ 小至少 $d$，比 $a[i]$ 多至少 $d$）。可以用权值线段树维护，每次考虑完 $i$ 就把 $f[i]$ 放到线段树的 $a[i]$ 位置即可。本题需要记录方案，DP 的时候记录方案即可。

$a[i]$ 的值域很大，可以离散化或者动态开点。

#### 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll res=0; bool f=0;
    char ch=getchar();
    while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) res=res*10+(ch^'0'),ch=getchar();
    return f?-res:res;
}
const int N=100010;
int n,d,cnt;
ll a[N],num[N];
int f[N],g[N];
typedef pair<int,int> pii;
#define v first
#define id second 
pii mx[N<<2];
pii query(int u,int l,int r,int ql,int qr)
{
    if(ql>qr) return {-1,0};
    if(ql<=l&&r<=qr) return (mx[u].v ? mx[u] : make_pair(-1,0));
    //如果是0说明根本没有（有的话至少是1）。
    //没有就要返回-1，保证存方案是对的

    int mid=(l+r)>>1;
    if(ql<=mid&&qr>mid) return max(query(u<<1,l,mid,ql,qr),query(u<<1|1,mid+1,r,ql,qr));
    else if(ql<=mid) return query(u<<1,l,mid,ql,qr);
    else return query(u<<1|1,mid+1,r,ql,qr);
}
void modify(int u,int l,int r,int pos,pii v)
{
    if(l==r) {mx[u]=max(mx[u],v); return;}
    int mid=(l+r)>>1;
    if(pos<=mid) modify(u<<1,l,mid,pos,v);
    else modify(u<<1|1,mid+1,r,pos,v);
    mx[u]=max(mx[u<<1],mx[u<<1|1]);
}
void print()
{
    int mx=0;
    for(int i=1;i<=n;i++) if(f[i]>f[mx]) mx=i;
    printf("%d\n",f[mx]);
    vector<int> ans;
    ans.push_back(mx);
    while(g[mx]) mx=g[mx],ans.push_back(mx);
    reverse(ans.begin(),ans.end());
    for(int x:ans) printf("%d ",x); puts("");
}
int main()
{
    n=read(),d=read();
    for(int i=1;i<=n;i++) num[i]=a[i]=read();
    sort(num+1,num+n+1);
    cnt=unique(num+1,num+n+1)-num-1;
    for(int i=1;i<=n;i++) 
    {
        int x=lower_bound(num+1,num+cnt+1,a[i])-num;
        int l=upper_bound(num+1,num+cnt+1,a[i]-d)-num-1;
        int r=lower_bound(num+1,num+cnt+1,a[i]+d)-num;
        pii ans=max({{0,0},query(1,1,cnt,1,l),query(1,1,cnt,r,cnt)});//{0,0}表示自己作为开头
        f[i]=ans.v+1,g[i]=ans.id;
        modify(1,1,cnt,x,{f[i],i});
    }
    print();
    return 0;
}
```

---

## 作者：Hadtsti (赞：2)

### 题意简述
给出长度为 $n(1\le n\le 10^5)$ 的序列 $a_i(1\le a_i\le 10^{15})$，求 $a_i$ 的最长的一个子序列 $\{b_1,b_2,\cdots,b_m\}$，满足 $\forall i\in[1,m),|b_i-b_{i+1}|\ge d$（$d$ 为给定数且 $d\le 10^9$）。

### 题目分析

裸的 DP 是好想的。类似于经典的 LIS 问题，设 $f_i$ 为 $a_i,a_{i+1},\cdots,a_n$ 满足题意的子序列的最长长度。那么我们只需要倒着求 $f_i$，对每个 $f_i$ 有 $\displaystyle f_i=\max_{j=i+1,|a_i-a_j|\ge d}^n\{f_j+1\}$，直接求是 $O(n^2)$ 的。至于具体数列，只需要对每个 $i$ 记录更新它的 $j$ 即可。

考虑优化。注意到 $|a_i-a_j|\ge d\Leftrightarrow a_j\in [1,a_i-d]\cup[a_i+d,10^{15}]$。那么我们只需要找到满足 $j\ge i$ 且 $a_j$ 在上述区间中的最大的 $f_j$ 即可。考虑离散化后使用线段树维护，仍是倒着求 $f_i$。对于 $f_i$，先区间查询线段树中值域在 $[1,a_i-d]\cup[a_i+d,10^{15}]$ 的最大 $f$ 值，然后单点修改 $a_i$ 对应的 $f$ 值为 $f_i$。注意维护时顺便记录一下区间里最大的 $f_j$ 对应的 $j$。总时间复杂度 $O(n\log n)$。具体细节见代码。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,nt[100010],mx=1,mxid=1;
long long d,a[100010],b[100010];
struct node
{
	int mx,mxid;//mx：区间最大 f 值，mxid：区间最大 f 值对应的 j 
}tr[400010];//线段树结点 
node calc(node a,node b)//合并两个结点 
{
	node c;
	if(a.mx>b.mx)
	{
		c.mx=a.mx;
		c.mxid=a.mxid;
	}
	else
	{
		c.mx=b.mx;
		c.mxid=b.mxid;
	}	
	return c;
}
void pushup(int p)//子结点更新父节点 
{
	tr[p]=calc(tr[p<<1],tr[p<<1|1]);
}
void build(int p,int l,int r)//建树 
{
	if(l==r)
	{
		tr[p].mx=-1;//初始 f 全设为 -1。 
		tr[p].mxid=0;
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void change(int p,int x,int v,int id,int l,int r)//单点修改 
{
	if(l==r)
	{
		if(v>tr[p].mx)//注意 a_i 可能有重复值，因此是取 max 不是直接赋值 
		{
			tr[p].mx=v;
			tr[p].mxid=id;
		}
		return;
	}
	int mid=l+r>>1;
	if(mid>=x)
		change(p<<1,x,v,id,l,mid);//改左子结点 
	else
		change(p<<1|1,x,v,id,mid+1,r);//改右子结点 
	pushup(p);
}
node query(int p,int L,int R,int l,int r)//区间查询 
{
	if(r<L||l>R)
		return (node){-1,0}; //区间无交集返回无解 
	if(l>=L&&r<=R)
		return tr[p];//区间全包含就直接返回答案 
	int mid=l+r>>1;
	if(mid<L)
		return query(p<<1|1,L,R,mid+1,r);//只查询左子结点 
	else if(mid>=R)
		return query(p<<1,L,R,l,mid);//只查询右子结点 
	else
		return calc(query(p<<1,L,R,l,mid),query(p<<1|1,L,R,mid+1,r));//合并子结点的查询答案 
}
int main()
{
	scanf("%d%lld",&n,&d);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;//离散化 
	build(1,1,m);
	for(int i=n;i>=1;i--)
	{
		node ans=calc(query(1,1,upper_bound(b+1,b+m+1,a[i]-d)-b-1,1,m),query(1,lower_bound(b+1,b+m+1,a[i]+d)-b,m,1,m)); //查询 [1,a_i-d]∪[a_i+d,+∞] 的最大 f 
		if(ans.mx!=-1)//如果有 f 就从那个 f 更新 
		{
			if(ans.mx>=mx)
				mx=ans.mx+1,mxid=i;//更新答案 
			change(1,lower_bound(b+1,b+m+1,a[i])-b,ans.mx+1,i,1,m);//单点修改 
			nt[i]=ans.mxid;//记录从哪个 f 过来的 
		}
		else//否则答案为 1 
			change(1,lower_bound(b+1,b+m+1,a[i])-b,1,i,1,m);//直接修改 
	}
	printf("%d\n",mx);//更新答案 
	while(mxid)//输出序列 
		printf("%d ",mxid),mxid=nt[mxid];
	return 0;
}
```


---

## 作者：legendgod (赞：2)

[CF474E Pillars](https://www.luogu.com.cn/problem/CF474E)

首先考虑一个暴力的 Dp。

设 $f(i)$ 表示当前位置为 $i$ 并且选当前位置作为结尾的最大长度。

可以得到转移方程 $f(i) = 1 + \sum_{k = 1} ^ {i - 1} f(k)[|h_i - h_k| \ge d]$。

然后会想到一个比较显然的方法，就是使用树状数组来维护。具体来说就是维护一个比当前位置大的 $\max$ 和比当前位置小的 $\max$。

然后发现值域很大不能通过值域直接维护，但是对于判定转移是否合法肯定是需要记录值的。

所以我们会考虑将其离散化一下，然后考虑维护离散化后的值。

如果将其排序一下，我们可以找到比当前值小的符合条件的最大位置，和比当前值大的符合条件的最小位置。之后使用线段树维护一下区间最大值就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;

//#define Fread
//#define Getmod

#ifdef Fread
char buf[1 << 21], *iS, *iT;
#define gc() (iS == iT ? (iT = (iS = buf) + fread (buf, 1, 1 << 21, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
#define getchar gc
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
	for(; '0' <= c && c <= '9';c = getchar()) x = (x * 10) + (c ^ 48);
	x *= f;
}

#ifdef Getmod
const int mod  = 1e9 + 7;
template <int mod>
struct typemod {
    int z;
    typemod(int a = 0) : z(a) {}
    inline int inc(int a,int b) const {return a += b - mod, a + ((a >> 31) & mod);}
    inline int dec(int a,int b) const {return a -= b, a + ((a >> 31) & mod);}
    inline int mul(int a,int b) const {return 1ll * a * b % mod;}
    typemod<mod> operator + (const typemod<mod> &x) const {return typemod(inc(z, x.z));}
    typemod<mod> operator - (const typemod<mod> &x) const {return typemod(dec(z, x.z));}
    typemod<mod> operator * (const typemod<mod> &x) const {return typemod(mul(z, x.z));}
    typemod<mod>& operator += (const typemod<mod> &x) {*this = *this + x; return *this;}
    typemod<mod>& operator -= (const typemod<mod> &x) {*this = *this - x; return *this;}
    typemod<mod>& operator *= (const typemod<mod> &x) {*this = *this * x; return *this;}
    int operator == (const typemod<mod> &x) const {return x.z == z;}
    int operator != (const typemod<mod> &x) const {return x.z != z;}
};
typedef typemod<mod> Tm;
#endif

template <typename T,typename... Args> inline void r1(T& t, Args&... args) {
    r1(t);  r1(args...);
}

#define int long long
const int maxn = 2e5 + 5;
const int maxm = maxn << 1;

int n, m;
int f[maxn], pre[maxn];
int a[maxn];

struct Node {
    int id, val;
    Node(void) {id = 0, val = 0;}
    Node(int a, int b) {id = a, val = b;}
}t[maxn << 2];

Node merge(Node a, Node b) {
    if(a.val > b.val) return a;
    else return b;
}

struct Seg_1 {
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    #define mid ((l + r) >> 1)
    void Insert(int p,int l,int r,int pos, Node c) {
        if(l == r) return t[p] = merge(t[p], c), void();
        if(pos <= mid) Insert(ls, l, mid, pos, c);
        else Insert(rs, mid + 1, r, pos, c);
        t[p] = merge(t[ls], t[rs]);
    }

    Node Ask(int p,int l,int r,int ll,int rr) {
        if(ll <= l && r <= rr) return t[p];
        Node res;
        if(ll <= mid) res = merge(res, Ask(ls, l, mid, ll, rr));
        if(mid < rr) res = merge(res, Ask(rs, mid + 1, r, ll, rr));
        return res;
    }

    #undef ls
    #undef rs
    #undef mid

}T;

int c[maxn], len;

int getl(int pos) {
    int val = c[a[pos]];
    int l(1), r(len), mid, ans(-1);
    while(l <= r) {
        mid = (l + r) >> 1;
        if(val - c[mid] >= m) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    return ans;
}

int getr(int pos) {
    int val = c[a[pos]];
    int l(1), r(len), mid, ans(-1);
    while(l <= r) {
        mid = (l + r) >> 1;
        if(c[mid] - val >= m) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    return ans;
}

signed main() {
//    freopen("S.in", "r", stdin);
//    freopen("S.out", "w", stdout);
    int i, j;
    r1(n, m);
    for(i = 1; i <= n; ++ i) r1(a[i]), c[i] = a[i];
    sort(c + 1, c + n + 1);
    len = unique(c + 1, c + n + 1) - c - 1;
    for(i = 1; i <= n; ++ i) a[i] = lower_bound(c + 1, c + len + 1, a[i]) - c;
    int ans(-1), pos(0);
    for(i = 1; i <= n; ++ i) {
        int L = getl(i), R = getr(i);
        Node res;
        if(L != -1) res = merge(res, T.Ask(1, 1, len, 1, L));
        if(R != -1) res = merge(res, T.Ask(1, 1, len, R, len));
        f[i] = res.val + 1;
        pre[i] = res.id;
        Node s = Node (i, f[i]);
        T.Insert(1, 1, len, a[i], s);
        if(f[i] > ans) ans = f[i], pos = i;
    }
    printf("%lld\n", ans);
    vector<int> vc;
    while(pos) {
//        printf("%d ", pos);
        vc.push_back(pos);
        pos = pre[pos];
    }
    reverse(vc.begin(), vc.end());
    for(auto v : vc) printf("%lld ", v);
    puts("");
	return 0;
}

```


---

## 作者：___OccDreamer___ (赞：1)

### 题意

题目翻译已经挺清晰的了，好评！

### Solution

$O(n^2)$：

依题意，容易联想到最长上升子序列（没想到也没关系），考虑最朴素的 dp：设 $f_i$ 表示以 $a_i$ 结尾的满足条件的最长子序列。

$$f_{i}=\max_{j<i,|b_i-b_j|\geq d}\{f_j\}+1$$

$O(n\log n)$：

考虑如何优化，由于 $|b_i-b_j|\geq d$ 的条件，没有办法像最长上升子序列一样通过修改 dp 状态+二分来优化（或者有，但蒟蒻没想到）。

考虑这个限制条件与权值有关，每次转移需要用到最大值，想到用权值线段树来优化。

- 修改操作：每次在线段树上下标为 $a_i$ 处，拆入 $f_i$ 。

- 查询操作：我们把绝对值拆开，得：$b_j\leq b_i-d$ 或 $b_j \geq b_i+d$，这样就变成了询问区间最大值。

关于方案，我们在线段树上再维护一个区间最大值的位置，每次求 $f_i$ 时，再记录一下前驱 $pre_i$。最后逆推方案。

不一定要动态开点，把 $a_i,a_i+d,a_i-d$ 都离散化就行。

### Code

```cpp
#include<bits/stdc++.h>
#define cout cerr
#define ll long long
#define mid (l+r>>1)
using namespace std;
const int N=1e5+5;
const int M=4e5+5;
const int T=M<<2;
int n,tot;
ll d,a[M],b[M],f[N];
int ans[N],pre[N],cnt;
ll mx;
int id;
struct node {
	ll maxx;
	int pos;
	node(){maxx=0,pos=0;};
	bool friend operator < (const node &x,const node &y) {
		return x.maxx<y.maxx;
	}
}tr[T];
ll read() {
	ll x=0,f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
void write(ll x) {
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
void pushup(int rt) {
	tr[rt]=max(tr[rt<<1],tr[rt<<1|1]);
}
void sett(int rt,int l,int r,int p,ll v,int id) {
	if(l==r) {
		if(v>tr[rt].maxx) tr[rt].maxx=v,tr[rt].pos=id;
		return ;
	}
	if(p<=mid) sett(rt<<1,l,mid,p,v,id);
	else sett(rt<<1|1,mid+1,r,p,v,id);
	pushup(rt);
}
node qmax(int rt,int l,int r,int L,int R) {
	if(L<=l&&R>=r) {
		return tr[rt];
	}
	node ret;
	if(L<=mid) ret=max(ret,qmax(rt<<1,l,mid,L,R));
	if(R>mid) ret=max(ret,qmax(rt<<1|1,mid+1,r,L,R));
	return ret;
}
void print(int x) {
	while(x) {
		ans[++cnt]=x;
		x=pre[x];
	}
	for(int i=cnt;i>=1;i--) {
		write(ans[i]),printf(" ");
	}
}
int main()
{
	n=read(),d=read();
	for(int i=1;i<=n;i++) {
		b[i]=a[i]=read();
		b[i+n]=a[i+n]=a[i]-d,b[i+2*n]=a[i+2*n]=a[i]+d;
	}
	sort(b+1,b+3*n+1);
	tot=unique(b+1,b+3*n+1)-b-1;
	for(int i=1;i<=3*n;i++) a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	f[1]=1;sett(1,1,tot,a[1],1,1);
	for(int i=2;i<=n;i++) {
		node x,y,z;
		x=qmax(1,1,tot,1,a[i+n]),y=qmax(1,1,tot,a[i+2*n],tot);
		z=max(x,y);
		f[i]=z.maxx+1,pre[i]=z.pos;
		sett(1,1,tot,a[i],f[i],i);
	}
	for(int i=1;i<=n;i++) {
		if(mx<f[i]) mx=f[i],id=i;
	}
	write(mx),puts("");
	print(id);
	return 0;
}
```

完结撒花✿ヽ(°▽°)ノ✿。

---

## 作者：__stick (赞：1)

# 题意
给出一个序列 $a$ 求出 $a$ 的一个最长的子序列，满足相邻两数的差值大于等于 $d$ 。
# 思路
简单的数据结构优化 dp。

首先我们写出暴力，$F_{i,j}$ 表示考虑到第 $i$ 个数，结尾的数是 $j$ 的方案数，则转移不难写出：
$$
F_{i,a_i}=\max_{|a_i-k|\ge d}\{F_{i-1,k}\}+1
$$

转移可以在离散化后做到 $O(n^2)$ 。并不能通过本题。

发现这个题的式子优化非常简单， $|j-k|\ge d$ 可以变成 $j-k\ge d$ 或 $k-j\ge d$  也就是 $k\le j-d $ 或者 $k\ge j+d$ 。

此时我们只需要一个支持区间操作的数据结构维护一下这个操作即可，这里题解中没有人使用平衡树维护，于是我来~~水~~了。

具体一点，使用 fhq_treap ，每个节点维护一个最大 dp 值，每次按照 val 分裂出来的两棵树，左边的小于等于 val，右边的大于等于 val，于是先按照 $a_i-d$ 分裂，从左边的最大值进行转移，再按照 $a_i+d-1$ （一定记得减一） 进行分裂，取右边的最大值进行转移。

由于要输出方案，记录最大值同时要记录对应位置。

# code

不懂的可以看代码。

发现并不比线段树和树状数组长。
```cpp
const int MAXN=1e5+10;
ll a[MAXN];
struct node
{
	int l,r,pr;
	ll key;
	pair<int,int> mmax,w;
}t[MAXN*3];
int tt;
#define ls t[p].l
#define rs t[p].r
inline void cmax(int& x,int y){x<y?x=y,1:0;}
inline void push_up(int p)
{
	t[p].mmax=t[p].w;
	if(ls)cmax(t[p].mmax,t[ls].mmax);
	if(rs)cmax(t[p].mmax,t[rs].mmax);
}
inline void split(int p,ll w,int&x,int& y)
{
	if(!p)return x=y=0,void();
	if(t[p].key<=w)x=p,split(rs,w,t[x].r,y);
	else y=p,split(ls,w,x,t[y].l);
	push_up(p);
}
int merge(int x,int y)
{
	if(!x||!y)return x^y;
	if(t[x].pr<t[y].pr)return t[x].r=merge(t[x].r,y),push_up(x),x;
	else return t[y].l=merge(x,t[y].l),push_up(y),y;
}
mt19937 gen(114514);
inline void insert(int& rt,ll key,int w,int i)
{
	tt++;
	t[tt]={0,0,(int)gen(),key,{w,i},{w,i}};
	int x,y;
	split(rt,key-1,x,y);
	rt=merge(merge(x,tt),y);
}
pii pre[MAXN];
signed main()
{
 	int n=R(),d=R();
 	for(int i=1;i<=n;i++)a[i]=R();
 	int rt=0;
 	pii ans={0,0};
 	for(int i=1;i<=n;i++)
 	{
 		int x,y;
 		split(rt,a[i]-d,x,y);
 		cmax(pre[i],t[x].mmax);
 		rt=merge(x,y);
 		split(rt,a[i]+d-1,x,y);// 记得减一 
 		cmax(pre[i],t[y].mmax);
 		rt=merge(x,y);//记得合并 
 		insert(rt,a[i],pre[i].first+1,i);
 		cmax(ans,{pre[i].first+1,i});
	}
	cout<<ans.first<<'\n';
	int u=ans.second;
	vi res;
	while(u) res.push_back(u),u=pre[u].second;
	reverse(res.begin(),res.end());
	for(int x:res)cout<<x<<' ';
	return 0;
}
```


---

## 作者：glorious_dream (赞：1)

### 题目大意：

给定一段序列 $a$，找出其一个子序列 $b$，使其长度最大，并且满足条件 $\mid b[i+1]-b[i] \mid $ $\geq d$，其中 $d$ 是题目中给定的数。

### 算法分析：

首先看到题目给的条件，可以想到求最长上升子序列的 $O(n \log n)$ 做法(本人习惯用树状数组)。

设 $f_i$ 表示以 $i$ 结尾的符合题目要求的子序列的最大长度，一个 $O(n^2)$ 的做法是 $f[i] = max(f[j]+1)$，其中需要满足 $j<i$ 并且 $\mid a[i]-a[j] \mid \geq d$。

但这道题的数据范围，是需要用 $O(n \log n)$ 的做法来通过。

由于对于一个位置 $i$，能被转移到的位置是有限的，必须满足 $\mid a[i]-a[j] \mid \geq d$，把绝对值打开可以得到 $a[i] \geq a[j]+d$ 或 $a[i] \leq a[j]-d$，可以发现被能转移到的区间被分为了两部分，$1$ 到 $a[j]-d$ 和 $a[j]+d$ 到给定的上界。所以我们可以维护一个线段树来记录区间最大值。

这时我们的 $f_i$ 可以通过线段树求两个区间的最大值的最大值 $+1$ 来转移。

上述是查询操作，接下来看修改操作。已知当前点 $i$，把 $a_i$ 作为下标，$f_i$ 作为值来进行修改，把影响到的节点的区间最大值进行比较并修改。

最后一步，考虑如何统计答案。由于让我们输出最长子序列的下标，我们可以另外用一个数组 $pre_i$，来记录当前点的 $f_i$ 值是由前面哪一个点转移过来的。然后一直跳 $pre$ 数组，用一个栈记录，最后把栈中的元素输出即可。

注意！这道题的数据范围不能直接传统线段树，需要动态开点。

### 总代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <stack>
#define re register
#define int long long
#define drep(a,b,c) for(re int a(b) ; a>=(c) ; --a)
#define rep(a,b,c) 	for(re int a(b) ; a<=(c) ; ++a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 1e5+10;
const int maxn = 1e15;
int n,d,root,cnt,ans,anspos;
int a[M],f[M],pre[M];
struct tree{
	int ls,rs,id,val;
}t[M*40];
#define ls t[k].ls
#define rs t[k].rs
inline void pushup(int k){ //更新节点信息 
	if(t[ls].val > t[rs].val) t[k].val = t[ls].val,t[k].id = t[ls].id;
	else t[k].val = t[rs].val,t[k].id = t[rs].id;
}
inline void modify(int &k,int l,int r,int x,int val,int id){
	if(!k) k=++cnt; //需要动态开点 
	if(l == r){
		if(val > t[k].val) t[k].val = val,t[k].id = id; //更新 
		return;
	}
	int mid = (l+r)>>1;
	if(x<=mid) modify(ls,l,mid,x,val,id);
	else modify(rs,mid+1,r,x,val,id);
	pushup(k); //常规操作 
}
inline tree query(int k,int l,int r,int x,int y){
	if(!k || y<x) return (tree){0,0,0,0};
	if(x<=l && r<=y) return t[k];
	int mid = (l+r)>>1;
	tree res1 = (tree){0,0,0,0},res2 = (tree){0,0,0,0};
	if(x<=mid) res1 = query(ls,l,mid,x,y);
	if(y>mid) res2 = query(rs,mid+1,r,x,y); 
	if(res1.val < res2.val) res1.val = res2.val,res1.id = res2.id; //需要找到最大值 
	return res1;
}
signed main(){
	n=read(),d=read();
	rep(i,1,n) a[i] = read();
	rep(i,1,n){
		tree tmp1 = query(root,1,maxn,1,a[i]-d);
		tree tmp2 = query(root,1,maxn,a[i]+d,maxn); //注意，是两个区间，要取这两个区间的最大值 
		if(tmp1.val < tmp2.val) swap(tmp1,tmp2); //把tmp1记为答案 
		f[i] = tmp1.val + 1; //进行dp修改 
		pre[i] = tmp1.id; //标转移到i的位置 
		if(ans < f[i]) ans=f[i],anspos=i; //最后输出的答案 
		modify(root,1,maxn,a[i],f[i],i); //需要把a[i]当成下标，f[i]当成值进行修改 
	}
	printf("%lld\n",ans);
	stack<int> s; //如上述所说，记录答案 
	for(re int i(anspos) ; i ; i=pre[i]) s.push(i); //一直跳pre就行 
	while(!s.empty()) printf("%lld ",s.top()),s.pop();
	return 0;
}
```


---

## 作者：wkjwkj (赞：1)

本题是一道典型的用数据结构优化 $\mathtt{dp}$ 的题目。

由题意可知，不难看出状态转移方程：$f[i]=\max\limits_{|h[i]-h[j]|\ge m\&\& 0<j<i}\{f[j]\}+1$

 所以不难写出 $O(n^2)$ 的暴力 $\mathtt{dp}$ 。

接下来我们考虑对转移进行优化。

将状态转移方程改写：$f[i]=\max\limits_{(h[i]-h[j]\ge m||h[i]-h[j]\le -m)\&\& 0<j<i}\{f[j]\}+1$

随着 $i$ 的增大，决策集合内的元素只增不少，$i$ 的前驱均有可能成为决策点，但我们关心的只是最大值，且注意到状态转移方程的条件为两个区间，这就启发了我们采用权值线段树来维护满足条件的最大值，即类似于树状数组求逆序对的过程。

值得注意的是，本题要求输出方案，所以在线段树查询最值时，需维护最大值所在点，得出答案后通过转移逆推方案。

$\mathtt{AC}$ 代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MP make_pair
#define PA pair<int,int>
#define F first
#define S second
using namespace std;
struct SgT{
	int l,r;
	int ans,pos;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define ans(x) t[x].ans
	#define pos(x) t[x].pos
}t[1200005];
int n,d;
ll h[100005];
int f[100005];
ll b[300005];
int tot;
int pre[100005];
void build(int p,int l,int r)
{
	l(p)=l,r(p)=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
void change(int p,int x,int i)
{
	if(l(p)==r(p)){
		if(f[i]>ans(p))ans(p)=f[i],pos(p)=i;
		return;
	}
	int mid=(l(p)+r(p))>>1;
	if(x<=mid)change(p*2,x,i);
	else change(p*2+1,x,i);
	if(ans(p*2)>ans(p*2+1))ans(p)=ans(p*2),pos(p)=pos(p*2);
	else ans(p)=ans(p*2+1),pos(p)=pos(p*2+1);
}
PA ask(int p,int l,int r)
{
	if(l<=l(p)&&r(p)<=r)return MP(pos(p),ans(p));
	int mid=(l(p)+r(p))>>1;
	int val=-(1<<30),id;
	if(l<=mid){
		PA x=ask(p*2,l,r);
		val=x.S,id=x.F;
	}
	if(r>mid){
		PA x=ask(p*2+1,l,r);
		if(x.S>val)val=x.S,id=x.F;
	}
	return MP(id,val);
}
void dfs(int x)
{
	if(pre[x]==0){
		printf("%d ",x);
		return;
	}
	dfs(pre[x]);
	printf("%d ",x);
}
int lsh(ll x)
{
	return lower_bound(b+1,b+tot+1,x)-b;
}
int main()
{
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++)scanf("%lld",&h[i]),b[++tot]=h[i],b[++tot]=max(h[i]-d,0LL),b[++tot]=h[i]+d;
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-(b+1);
	int ans=0;
	build(1,1,tot);
	for(int i=1;i<=n;i++)
	{
		PA x=ask(1,0,max(lsh(h[i]-d),0)),y=ask(1,lsh(h[i]+d),tot);
		if(x.S>y.S){
			f[i]=x.S+1;
			pre[i]=x.F;
		}
		else f[i]=y.S+1,pre[i]=y.F;
		change(1,lsh(h[i]),i);
		ans=max(ans,f[i]);
	}
	//puts("");
	printf("%d\n",ans);
	int st;
//	for(int i=1;i<=n;i++)
//		printf("%d ",pre[i]);
	for(int i=1;i<=n;i++)if(ans==f[i]){
		st=i;
		//printf("%d\n",st);
		break;
	}
	dfs(st);
	return 0;
}
```





---

## 作者：__Hacheylight__ (赞：1)

数据结构优化 $dp$ 的题目都很套路

设 $f[i]$ 表示取到 $i$ 且 $i$ 必取的最大长度

那么显然：

$$
f(i)=\max\limits_{j=1}^i(f(j))+1~(|h_i-h_j| \ge d)
$$

直接枚举 $O(n^2)$ 考虑优化

拆去绝对值后发现其实就是 $h_j \le h_i-d$ 或 $h_j \ge h_i+d$。相当于对两个区间查询最大值

对 $h$ 进行离散化后可以二分位置，之后就可以用数据结构优化了

可以是一个线段树或两颗树状数组，我选择后者

时间复杂度 $O(n~log~n)$

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <numeric>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define loop(s, v, it) for (s::iterator it = v.begin(); it != v.end(); it++)
#define cont(i, x) for (int i = head[x]; i; i = e[i].nxt)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define all(x) x.begin(), x.end()
#define ub upper_bound
#define lb lower_bound
#define pq priority_queue
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define iv inline void
#define enter cout << endl
#define siz(x) ((int)x.size())
#define file(x) freopen(#x".in", "r", stdin),freopen(#x".out", "w", stdout)
typedef long long ll ;
typedef unsigned long long ull ;
typedef pair <int, int> pii ;
typedef vector <int> vi ;
typedef vector <pii> vii ;
typedef queue <int> qi ;
typedef queue <pii> qii ;
typedef set <int> si ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
const double eps = 1e-7 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n, d, tt ;
int tmp[N], a[N], bit1[N], bit2[N], ans[N], to[N] ;

void lsh() {
	rep(i, 1, n) tmp[i] = a[i] ;
	sort(tmp + 1, tmp + n + 1) ;
	tt = unique(tmp + 1, tmp + n + 1) - (tmp + 1) ;
}

int Max(int a, int b) {
	return ans[a] < ans[b] ? b : a ;
}

void add1(int x, int y) {
	for (; x <= tt; x += lowbit(x)) bit1[x] = Max(bit1[x], y) ;
}

int ask1(int x) {
	int ans = 0 ;
	for (; x; x -= lowbit(x)) ans = Max(bit1[x], ans) ;
	return ans ;
}

void add2(int x, int y) {
	for (; x <= tt; x += lowbit(x)) bit2[x] = Max(bit2[x], y) ;
}

int ask2(int x) {
	int ans = 0 ;
	for (; x; x -= lowbit(x)) ans = Max(bit2[x], ans) ;
	return ans ;
}

signed main(){
	scanf("%lld%lld", &n, &d) ;
	rep(i, 1, n) scanf("%lld", &a[i]) ;
	lsh() ;
	per(i, n, 1) {
		int x = lb(tmp + 1, tmp + tt + 1, a[i] + d) - tmp ;
		int y = ub(tmp + 1, tmp + tt + 1, a[i] - d) - (tmp + 1) ;
		int res = Max(ask1(y), ask2(tt - x + 1)) ;
		ans[i] = ans[res] + 1 ;
		to[i] = res ;
		int pos = lb(tmp + 1, tmp + tt + 1, a[i]) - tmp ;
		add1(pos, i) ;
		add2(tt - pos + 1, i) ;
	}
//	rep(i, 1, n) cout << ans[i] << " " ; enter ;
	int s = 0 ;
	rep(i, 1, n) s = Max(s, i) ;
	printf("%lld\n", ans[s]) ;
	while (s) {
		printf("%lld ", s) ;
		s = to[s] ;
	}
	enter ;
	return 0 ;
}

/*
写代码时请注意：
	1.ll？数组大小，边界？数据范围？
	2.精度？
	3.特判？
	4.至少做一些
思考提醒：
	1.最大值最小->二分？
	2.可以贪心么？不行dp可以么
	3.可以优化么
	4.维护区间用什么数据结构？
	5.统计方案是用dp？模了么？
	6.逆向思维？
*/


```



---

## 作者：xfrvq (赞：0)

首先这个东西还是长得比较像最长上升子序列 $\tt LIS$ 的，然后我们考虑一下 $\tt LIS$ 是怎么做的。

> 设 $f_i$ 为以 $i$ 为最后一位的 $\tt LIS$ 最大长度，转移就 $f_i=\max\{f_j\}+1$ 其中 $j\lt i,a_j\lt a_i$。
> 
> 然后这是 $n^2$，我们考虑优化一下。
>
> + 跑一遍扫描线，过程中维护一棵 $\texttt{FHQ-Treap}$，按 $a_i$ 为权值分裂，维护子树 $f_i$ 最大值 $F$。
> + 通过平衡树，先分裂出 $\lt a_i$ 的平衡树子树，这时转移为  $f_i=F+1$。
> + 最后记得往平衡树里面加入 $i,a_i,f_i$。

那这个也是类似，只不过分裂出的是 $(-\infty,a_i-d]$ 以及 $[a_i+d,+\infty)$ 的子树。

不过你要维护答案子序列，这个可以考虑在平衡树里记录最大值位置，转移时记录一个 $p_i=j$ 代表 $f_i$ 是从 $f_j$ 转移过来的。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e5 + 5;

int n,d,pos[N];
vector<int> P;

namespace FHQ{
	int rt,lc[N],rc[N],tot;
	int siz[N],pri[N];
	pair<int,int> num[N],sum[N];
	int a,b,c;
	ll val[N];
	
	int cnode(ll v,int p,int x){ 
		siz[++tot] = 1,pri[tot] = rand(),val[tot] = v;
		return num[tot] = sum[tot] = make_pair(x,p),tot;
	}
	
	void psu(int i){
		siz[i] = siz[lc[i]] + 1 + siz[rc[i]];
		sum[i] = max({sum[lc[i]],num[i],sum[rc[i]]});
	}
	
	int mrg(int x,int y){
		if(!x || !y) return x + y;
		if(pri[x] < pri[y]) return rc[x] = mrg(rc[x],y),psu(x),x;
		else return lc[y] = mrg(x,lc[y]),psu(y),y;
	}
	
	void spl(int i,ll k,int &x,int &y){
		if(!i) return void(x = y = 0);
		if(val[i] <= k) x = i,spl(rc[i],k,rc[i],y);
		else y = i,spl(lc[i],k,x,lc[i]);
		psu(i);
	}
	
	void upd(ll v,int p,int x){
		spl(rt,v,b,c);
		spl(b,v - 1,a,b);
		b = cnode(v,p,x);
		rt = mrg(mrg(a,b),c);
	}
	
	auto qry(ll l,ll r){
		spl(rt,r - 1,b,c);
		spl(b,l,a,b);
		auto ret = max(sum[a],sum[c]);
		rt = mrg(mrg(a,b),c);
		return ret;
	}
}

int main(){
	scanf("%d%d",&n,&d);
	for(int i = 1;i <= n;++i){
		ll x; scanf("%lld",&x);
		auto[v,p] = FHQ::qry(x - d,x + d);
		FHQ::upd(x,i,v + 1),pos[i] = p;
	}
	auto[x,p] = FHQ::sum[FHQ::rt];
	printf("%d\n",x);
	for(;p;p = pos[p]) P.push_back(p);
	for(int p : P | ranges::views::reverse) printf("%d ",p);
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

~~为啥 *2000 紫啊。~~

好的大家都会 $O(n^2)$ 求 $\mathtt{LIS}$ 吧，那这题你就会做了。

和最长上升子列一样的套路，令 $f_i$ 表示以 $i$ 结尾的最长符合要求的子序列的最长长度。

转移就是 $f_i=\max\limits_{j=1}^{i-1}\{[a_j\in\mathbb{N^*\backslash (a_i-d+1,a_i+d-1)](f_j+1)}\}$。

然后对于这东西我们可以用一棵权值线段树在 $dp$ 时维护值域上的 $dp$ 值，然后 $O(\log n)$ 查询以某个值域内的值结尾的最长符合要求的自序列的长度。

考虑如何记录答案，对于每个下标 $i$ 记录一个 $pr_i=j$ 表示 $f_i$ 从 $f_j$ 处转移最优，然后最后只要找到 $i$ 使得 $f_i$ 最大，从 $i$ 一直往前跳 $pr$，然后开一个栈记录即可。

时间复杂度 $O(n\log w)$，注意要动态开点。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
struct segtree { int lc, rc, vl, id; } tr[maxn << 6];
int n, d, tot, rt, a[maxn], pre[maxn], f[maxn], ans, val;

#define ls tr[x].lc
#define rs tr[x].rc
#define mid ((l + r) >> 1)

void update(int l, int r, int p, int c, int id, int &x) {
	if (!x) x = ++tot;
	if (l == r) { 
		if (tr[x].vl < c) tr[x].vl = c, tr[x].id = id;
		return; 
	}
	if (p <= mid) update(l, mid, p, c, id, ls);
	else update(mid + 1, r, p, c, id, rs);
	if (tr[ls].vl > tr[rs].vl) tr[x].vl = tr[ls].vl, tr[x].id = tr[ls].id;
	else tr[x].vl = tr[rs].vl, tr[x].id = tr[rs].id;
}

segtree query(int l, int r, int s, int t, int x) {
	if (!x || t < s) return (segtree) { 0, 0, 0, 0 };
	if (s <= l && r <= t) return tr[x];
	segtree res = (segtree) { 0, 0, 0, 0 };
	if (s <= mid) res = query(l, mid, s, t, ls);
	if (t > mid) {
		segtree tp = query(mid + 1, r, s, t, rs);
		if (res.vl < tp.vl) res.vl = tp.vl, res.id = tp.id;
	}
	return res;
}

signed main() {
	n = read(), d = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) {
		segtree tp = query(1, 1e15, 1, a[i] - d, rt);
		segtree tp1 = query(1, 1e15, a[i] + d, 1e15, rt);
		if (tp.vl < tp1.vl) tp.vl = tp1.vl, tp.id = tp1.id;
		f[i] = tp.vl + 1;
		pre[i] = tp.id;
		if (val < f[i]) {
			val = f[i];
			ans = i;
		}
		update(1, 1e15, a[i], f[i], i, rt);
//		cout << f[i] << endl;
	}
	write(val), puts("");
	stack<int> st;
	for (int i = ans; i; i = pre[i]) st.push(i);
	while (!st.empty()) write(st.top()), st.pop(), putchar(' ');
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16000360.html)

树状数组优化 $\rm dp$。

# 题目大意

- 给定序列 $h$，长度为 $n$。
- 找出一个 $h$ 序列的子序列 $b$（设其长度为 $m$），使得
    - 对于任意的 $1\le i\lt m$，有 $|b_{i+1}-b_i|\ge d$。
    - $m$ 最大。
    - 其中 $d$ 是给定的。
- 您的程序要输出 $m$ 和序列 $b$ 在序列 $h$ 中每个数的下标（下标从 $1$ 开始）。
- $1\le n\le 10^5$，$0\le d\le 10^9$，$1\le h_i\le 10^{15}$。若 $b$ 不唯一，输出任意一种。

# 题目分析

因为 $a$ 范围很大，所以先排序去重到 $b$ 数组。

令 $dp_i$ 表示取到了第 $i$ 个数且第 $i$ 个数必选的最大长度。

然后有一个很裸的 $\mathcal{O(n^2)}$ 思路，转移方程为 $dp_i=\max\{dp_j\}+1(1\le j\lt i,|h_i-h_j|\ge d)$，枚举即可。

但这是 $\rm codeforces$，不会给部分分。我们考虑优化，通过观察数据范围可以猜测应该是 $\mathcal{O(n\log n)}$ 或 $\mathcal{O(n\sqrt{n})}$ （极限 $3e7$），又看到 $\max\{dp_j\}$ 和 $1\le j\lt i$，可以自然地想到数据结构优化。

但是还有很麻烦的限制，就是 $|h_i-h_j|\ge d$，即 $h_i-h_j\ge d$ 或 $h_j-h_i\ge d$，再换一下就是 $h_j\le h_i-d$ 或 $h_j\ge h_i+d$。

然后在 $b$ 中二分找到大于等于 $h_i+d$ 的第一个位置 $l$，二分找到小于等于 $h_i-d$ 的第一个位置 $r$。随后需要知道 $h_j$ 在区间 $[1,l]$ 或 $[r,\operatorname{upper}\_\operatorname{limit}]$ 内的 $\max\{dp_j\}$。

线段树和树状数组都可以维护，但树状数组代码容易些所以我选树状数组。~~其实是因为不会写~~

用两个树状数组维护这个最大值即可，注意因为一维树状数组（二维树状数组 `√` 都不用）只能维护前缀最大值，所以 $[r,\operatorname{upper}\_\operatorname{limit}]$ 需要转换为 $[1,\operatorname{upper}\_\operatorname{limit}-r+1]$。

输出方案直接记录一下转移过来的下标，然后用栈输出即可。

# 代码

```cpp
//2022/3/12
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <stack>
#define int long long
#define enter putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
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

const int ma = 1e5 + 5;
int a[ma],b[ma],dp[ma],pre[ma];
//dp[i]:取到了第 i 个数且第 i 个数必选的最大长度
stack<int>ans;
int n,m,num;
struct BIT {
	int tr[ma];
	#define lowbit(x) (x & -x)
	inline int max(int x,int y) {
		return dp[x] >= dp[y] ? x : y;
	}
	inline void update(int x,int k) {
		for (;x <= num;x += lowbit(x)) {
			tr[x] = max(tr[x],k);
		}
	}
	inline int query(int x) {
		int res = 0;
		for (;x;x -= lowbit(x)) {
			res = max(res,tr[x]);
		}
		return res;
	}
	#undef lowbit
} bit1,bit2;
#undef int
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	#define int long long
	n = read(),m = read();
	for (register int i = 1;i <= n; ++ i) a[i] = b[i] = read();
	sort(b + 1,b + n + 1);
	num = unique(b + 1,b + n + 1) - b - 1;
	for (register int i = 1;i <= n; ++ i) {
		int l = upper_bound(b + 1,b + num + 1,a[i] - m) - b - 1,r = lower_bound(b + 1,b + num + 1,a[i] + m) - b;
		int res = max(bit1.query(l),bit2.query(num - r + 1));
		dp[i] = dp[res] + 1,pre[i] = res;
		int pos = lower_bound(b + 1,b + num + 1,a[i]) - b;
		bit1.update(pos,i),bit2.update(num - pos + 1,i);
	}
	int now = 0;
	for (register int i = 1;i <= n; ++ i) {
		if (dp[now] < dp[i]) {
			now = i;
		}
	}
	printf("%lld\n",dp[now]);
	while (now) {
		ans.push(now);
		now = pre[now];
	}
	while (!ans.empty()) {
		printf("%lld ",ans.top());
		ans.pop();
	}

	return 0;
}
```

---

