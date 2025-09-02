# Zip-line

## 题目描述

\$\$

#### 题目大意：
给定一个长度为$n$的序列以及$m$个操作，每个操作形如“$a_i~b_i$”，表示将序列中第$a_i$个数改为$b_i$。

对于每个操作，求出序列的最长严格上升子序列长度。

**注意：每个操作之间彼此独立。（即每次操作未进行时的序列是输入时的原序列，而不是上一次操作后得到的序列）**

## 样例 #1

### 输入

```
4 4
1 2 3 4
1 1
1 4
4 3
4 5
```

### 输出

```
4
3
3
4
```

## 样例 #2

### 输入

```
4 2
1 3 2 6
3 5
2 4
```

### 输出

```
4
3
```

# 题解

## 作者：_acat_ (赞：19)

[题目传送门](https://www.luogu.com.cn/problem/CF650D)

这道题我们可以先求出以第 $i$ 个数结尾的 LIS 长度 $d[i]$。

同理反着求一遍也可以求出以第 $i$ 个数开头的 LIS 长度。

回到本题，对于每次修改 $a[i]=x$。

很显然有2种情况：

1. 新的 LIS 包含 a[i]。

2. 新的 LIS 不包含 a[i]。

所以我们先求一定包含 $a[i]$ 的 LIS，预处理出以第 $i$ 个数结尾的 LIS：$left[i]$ 和以第 $i$ 个数开头的 LIS：$right[i]$。

现在我们只要求出左边 $\max(left[j])$ 和右边 $\max(right[j])$，两者长度相加再加 $1$ 就是包含 $a[i]$ 的新 LIS 了！

如果这个值大于原序列的 LIS，那它就是答案，输出即可。

接下来我们分析 LIS 不包含 $x$ 的情况：

1. 如果修改的数在原序列的 LIS 中，则不包含修改的数的 LIS 一定会减少 $1$。

2. 如果修改的数不在原序列的 LIS 中，则不包含修改的数的 LIS 则不会变化。

于是这道题就变成了对于序列中的每个数，判断其是否出现在 LIS 中。

先用之前的思路算出包含 $a[i]$ 的 lis：$len[i]=max(left)+1+\max(right)$。

如果 $len[i]$ 等于原序列的 LIS，那么 $i$ 可能出现在 LIS 中。

那如果 i 可能出现，就又如果存在 $j<i$ 且 $a[j]\geqslant a[i]$ 且 $j$ 可能出现在LIS中，当然 $i$ 也可能不出现在 LIS 中。

同理如果存在 $j>i$ 且 $a[j]\leq a[i]$ 且 j 可能出现在 LIS 中，
那么 $i$ 可以不出现在LIS中。

所以如果 $i$ 不满足可以不出现在 LIS 中的条件，则 $i$ 一定出现在 LIS 中。

则对于每次修改 $a[i]=x$，先计算包含 $x$ 的LIS长度。如果比原序列 LIS 大，则一定是答案。

否则，如果 $i$ 可以不出现，则 LIS 不变，否则如果 $i$ 一定出现，则 LIS 会减少 $1$。

回过头来，它就是计算 $\max(left[j])$，也就是经典二维数点问题。

对 $a[j],x$ 排序。从小到大枚举 $x$，把 $a[j]<x$ 的 $left[j]$ 插入树状数组的第 $j$ 个位置。

所以我们把维护更新和询问树状数组的加法变成求 $max$，问题就转化成了求前缀最大值。

这样我们就可以解决这道题了！

---

## 作者：奇米 (赞：18)

## 题解- CF650D Zip-line

* **题目意思**

 就是给你个序列以及多次操作，每次把$ai$换做$bi$求一遍$lis$（操作之间互不影响）
 
 * $Sol$
 
 显然每次修改暴力做$lis$是不可行的复杂度至少为$O(n^2 \log n )$。于是我们要思考每次修改会对答案形成怎样的影响。
 
 先对原序列每个点做一遍以他为结束的$lis$记为$fi$，以他作为起始的$lis$记为$gi$。易得原序列的$lis$就为$max\{fi+gi-1\}$。
 
 每次对于修改一个值分几种情况来考虑 （思路借鉴 霜雪谦年 的题解），我们记修改过后的$fi$为$fi'$，$gi'$同理。
 
 对于$+1$的情况如果$fi'+gi'+1>ans$那就更新答案
 
 对于$-1$的情况相对复杂一点。我们要先判断此次修改的点是否为原序列$lis$的必经之点，判断的方法很简单如果$fi+gi-1=ans$，并且这样的情况有且只有一种。
 
 剩余的就是不变的情况了。于是我们这道题目就做完了。求$lis$可以使用树状数组来实现$fi$正着$gi$倒着即可并且要离散化一下就可以了。用离线来实现。
 
 * $Code$
 
```cpp
#include <bits/stdc++.h>
#define lowbit(x) x&(-x)
using namespace std;

const int N=800005;

int n,m,ans,f[N],g[N],tr[N];
int a[N],b[N],res[N],cs[N],cnt;

struct number {
	int id,x,val;
	int f,g;
	inline bool friend operator < (const number &a,const number &b) {
		if(a.x==b.x) return a.val<b.val;
		return a.x<b.x;
	}
};
number q[N];

inline int read() {
	int sum=0; char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) 
		sum=sum*10+(ch^48),ch=getchar();
	return sum;
}

inline void jia(int x,int v) {
	while(x<=cnt) {
		tr[x]=max(tr[x],v);
		x+=lowbit(x);
	}
}

inline int query(int x) {
	int ret=0;
	while(x) {
		ret=max(ret,tr[x]);
		x-=lowbit(x);
	}
	return ret;
}

int main() {
	n=read(),m=read();
	cnt=n;
	for ( int i=1;i<=n;i++ ) {
		a[i]=read();
		b[i]=a[i];
	}
	for ( int i=1;i<=m;i++ ) {
		q[i].id=i;
		q[i].x=read();
		q[i].val=read();
		b[++cnt]=q[i].val;
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for ( int i=1;i<=n;i++ ) a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	for ( int i=1;i<=m;i++ ) q[i].val=lower_bound(b+1,b+cnt+1,q[i].val)-b;
	for ( int i=1;i<=n;i++ ) {
		f[i]=query(a[i]-1)+1;
		jia(a[i],f[i]);
	}
	memset(tr,0,sizeof(tr));
	for ( int i=n;i>=1;i-- ) {
		g[i]=query(cnt-a[i])+1;
		jia(cnt-a[i]+1,g[i]);
	}
	for ( int i=1;i<=n;i++ ) ans=max(ans,f[i]+g[i]-1);
	for ( int i=1;i<=n;i++ ) if(f[i]+g[i]-1==ans) cs[f[i]]++;
	sort(q+1,q+m+1);
	memset(tr,0,sizeof(tr));
	int now=1;
	for ( int i=1;i<=m;i++ ) {
		while(now<q[i].x) {
			jia(a[now],f[now]);
			now++;
		}
		q[i].f=query(q[i].val-1);
	}
	memset(tr,0,sizeof(tr));
	now=n;
	for ( int i=m;i>=1;i-- ) {
		while(now>q[i].x) {
			jia(cnt-a[now]+1,g[now]);
			now--;
		}
		q[i].g=query(cnt-q[i].val);
		if(q[i].f+q[i].g+1>ans) res[q[i].id]=q[i].f+q[i].g+1;
	}
	for ( int i=1;i<=m;i++ ) if(!res[q[i].id]) {
		if(f[q[i].x]+g[q[i].x]==ans+1&&cs[f[q[i].x]]==1&&q[i].f+q[i].g+1<ans) res[q[i].id]=ans-1;
		else res[q[i].id]=ans;
	}
	for ( int i=1;i<=m;i++ ) printf("%d\n",res[i]);
}
```



---

## 作者：mrsrz (赞：10)

记 $f_i$ 表示以 $i$ 结尾的最长严格上升子序列长度，$g_i$ 表示以 $i$ 开头的最长严格上升子序列长度。

求 $f$ 和 $g$ 就是一个普通的 LIS 问题，可以使用单调队列等做法，时间复杂度 $O(n\log n)$。

对于每一个询问 $u,v$，它会修改掉一个数。那么我们考虑两种情况：LIS 中包含这个数，或者 LIS 中不包含这个数。

- 包含的情况。

  这种情况较好处理。我们只要能求出在 $u$ 之前结尾且结尾的数小于 $v$ 的 LIS 长度 $a$，以及在 $u$ 之后开头且开头的数大于 $v$ 的 LIS 长度 $b$，那么 $a+b+1$ 就是其贡献。

  将询问离线以后，在求 $f$ 和 $g$ 的同时按照一样的方法就可以得到 $a$ 和 $b$。

  时间复杂度 $O(m\log n)$。

- 不包含的情况。

  令 $h_i$ 表示不包含 $i$ 时原序列的 LIS，那么对于询问 $u,v$，答案只需要对 $h_u$ 取 $\max$ 就好了。

  那么如何求出 $h_i$ 呢？

  对于 $h_i$，我们要找到 $u,v$ 满足 $u\lt i\lt v$，$a_u\lt a_v$，并且 $f_u+g_v$ 最大。

  考虑分治。令当前中点为 $x$。我们考虑对每个在 $[l,x]$ 中的 $f$，找到一个在 $[x+1,r]$ 中的 $g$ 并使结果最大。这样可以更新 $h_{l..x}$。右半边同理可得。

  那么我们可以枚举 $i\in[l,x]$，在 $[x+1,r]$ 中二分出第一个满足 $a_i\lt a_k$ 的 $k$，然后对 $g_{k..r}$ 求最大值 $g_0$。然后 $f_i+g_0$ 的结果可以更新到 $h_{i+1..x}$，这个可以直接更新到 $h_{i+1}$ 上然后求后缀最大值得到。

  需要排序和二分，那么时间复杂度就是 $O(n\log^2 n)$。

  考虑进一步优化。

  首先这个排序可以分治的同时进行归并。

  然后这个二分也可以省。我们按 $a_i$ 从大到小枚举 $i$，那么 $a_k$ 也是不断变小的，双指针维护即可。$g$ 的最值也可以直接维护。

  于是时间复杂度为 $O(n\log n)$。

算法的总时间复杂度为 $O((n+m)\log n)$，空间复杂度为 $O(n+m)$。

## Code：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
const int N=4e5+10;
int pre[N],suf[N],n,m,a[N],ans[N],res[N];
vector<pair<int,int> >vc[N];
int sta[N],top,cov[N];
pair<int,int>d[N],tmp[N];
void solve(int l,int r){
	if(l==r){
		return;
	}
	const int mid=(l+r)/2;
	solve(l,mid),solve(mid+1,r);
	for(int i=mid,nw=0,it=r;i>=l;--i){
		while(it>mid&&d[i].first<d[it].first)nw=max(nw,suf[d[it--].second]);
		cov[d[i].second+1]=pre[d[i].second]+nw;
	}
	for(int i=l+1;i<=mid;++i)cov[i]=max(cov[i],cov[i-1]);
	for(int i=l;i<=mid;++i)res[i]=max(res[i],cov[i]);
	for(int i=l;i<=mid+1;++i)cov[i]=0;
	for(int i=mid+1,nw=0,it=l;i<=r;++i){
		while(it<=mid&&d[i].first>d[it].first)nw=max(nw,pre[d[it++].second]);
		cov[d[i].second-1]=suf[d[i].second]+nw;
	}
	for(int i=r-1;i>mid;--i)cov[i]=max(cov[i],cov[i+1]);
	for(int i=mid+1;i<=r;++i)res[i]=max(res[i],cov[i]);
	for(int i=mid;i<=r;++i)cov[i]=0;
	int itL=l,itR=mid+1,it=l;
	while(itL<=mid&&itR<=r)
	if(d[itL]<d[itR])tmp[it++]=d[itL++];else tmp[it++]=d[itR++];
	while(itL<=mid)tmp[it++]=d[itL++];
	while(itR<=r)tmp[it++]=d[itR++];
	for(int i=l;i<=r;++i)d[i]=tmp[i];
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	for(int i=1;i<=m;++i){
		int p,x;
		scanf("%d%d",&p,&x);
		vc[p].emplace_back(x,i);
		ans[i]=1;
	}
	for(int i=1;i<=n;++i){
		res[i]=top;
		for(auto it:vc[i]){
			int v=it.first,id=it.second;
			int len=lower_bound(sta,sta+top+1,v)-sta-1;
			ans[id]+=len;
		}
		int t=lower_bound(sta,sta+top+1,a[i])-sta;
		if(t>top)sta[++top]=a[i];
		else sta[t]=min(sta[t],a[i]);
		pre[i]=t;
	}
	sta[top=0]=1e9+7;
	for(int i=n;i;--i){
		res[i]=max(res[i],top);
		for(auto it:vc[i]){
			int v=it.first,id=it.second;
			int len=lower_bound(sta,sta+top+1,v,greater<int>())-sta-1;
			ans[id]+=len;
		}
		int t=lower_bound(sta,sta+top+1,a[i],greater<int>())-sta;
		if(t>top)sta[++top]=a[i];
		else sta[t]=max(sta[t],a[i]);
		suf[i]=t;
	}
	for(int i=1;i<=n;++i)d[i]=make_pair(a[i],i);
	solve(1,n);
	for(int i=1;i<=n;++i)
	for(auto it:vc[i])ans[it.second]=max(ans[it.second],res[i]);
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：L0vely_NaiL0ng (赞：6)

经典结论：

- 对于最长严格上升子序列（LIS），我们常常记强选第 $i$ 个数前 $i$ 个数的 LIS 为 $f_i$，强选第 $i$ 个数后 $i$ 个数的 LIS 为 $g_i$，如果 $f_i + g_i - 1 = ans$，$i$ 在某些 LIS 中（显然一个序列可以有多个 LIS），且 $i$ 一定在 LIS 的第 $f_i$ 位（考虑反证，根据 $f_i$ 的极大性）。所以得到判断 $i$ 是否是 LIS 的必经点的充要条件：$f_i + g_i - 1 = ans$ 且 对于 $f_i + g_i - 1 = ans$ 的所有点 $i$ 不存在除 $i$ 之外的一个 $j$ 满足 $f_i = f_j$。

同样的，我们先求出 $f$ 和 $g$ 数组，记未修改的 LIS 长度为 $lans$。

- Case 1：修改的位置 $i$ 在新的 LIS 上，修改后的值为 $v$，那么这种情况答案为 $\max(f_j + 1 + g_k)$ 其中 $j < i < k, a_j < v < a_k$。

- Case 2：$i$ 是 LIS 的必经点，这种情况新的 LIS 为 $lans - 1$；否则为 $lans$。

$f$ 和 $g$ 还有 $lans$ 以及 Case 1 都可以用线段树轻松解决（Case 1 考虑离线做），Case 2 根据经典结论 $O(n)$ 扫一遍就行了，整个问题时间复杂度 $O(n \log n)$。

```
#include <bits/stdc++.h>
#define For(i, x, y) for (int i = (x); i <= (y); i++)
#define lb lower_bound
#define ls (p << 1)
#define rs (p << 1 | 1)
#define cmax(x, y) x = max(x, y)
#define mid ((l + r) >> 1)
#define foR(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
const int N = 4e5 + 5, M = 8e5 + 5;
int n, m, a[N], val[M], tot, f[N], g[N], ans[N], lans, t[M << 2], F[N], G[N], lst[N];
bool flag[N];
struct node {
	int x, v, id;
	bool operator < (const node &i) const {
		return x < i.x;
	} 
} q[N];
void change(int l, int r, int x, int p, int v) {
	if (l == r) {
		cmax(t[p], v); return;
	}
	if (x <= mid) change(l, mid, x, ls, v);
	else change(mid + 1, r, x, rs, v);
	t[p] = max(t[ls], t[rs]);
}
int query(int l, int r, int x, int y, int p) {
	if (x > y) return 0;
	if (l >= x && r <= y) return t[p];
	int res = 0;
	if (x <= mid) res = query(l, mid, x, y, ls);
	if (y > mid) cmax(res, query(mid + 1, r, x, y, rs));
	return res;
}
void P1() {
	For (i, 1, n) {
		f[i] = query(1, tot, 1, a[i] - 1, 1) + 1;
		change(1, tot, a[i], 1, f[i]);
	}
	memset(t, 0, sizeof t);
	foR (i, n, 1) {
		g[i] = query(1, tot, a[i] + 1, tot, 1) + 1;
		change(1, tot, a[i], 1, g[i]);
	}
	memset(t, 0, sizeof t);
	For (i, 1, n) cmax(lans, f[i] + g[i] - 1);
}
void P2() {
	sort(q + 1, q + m + 1);
	int now = 1;
	For (i, 1, m) {
		while (now < q[i].x) {
			change(1, tot, a[now], 1, f[now]); now++;
		}
		F[q[i].id] = query(1, tot, 1, q[i].v - 1, 1);
	}
	memset(t, 0, sizeof t); now = n;
	foR(i, m, 1) {
		while (now > q[i].x) {
			change(1, tot, a[now], 1, g[now]); now--;
		}
		G[q[i].id] = query(1, tot, q[i].v + 1, tot, 1);
	}
	For (i, 1, m) ans[i] = F[i] + G[i] + 1;
}
void P3() {
	For (i, 1, n) {
		if (lst[f[i]] == -1 || f[i] + g[i] - 1 != lans) continue;
		if (lst[f[i]]) {
			flag[lst[f[i]]] = 0; lst[f[i]] = -1;
		} else {
			flag[i] = 1; lst[f[i]] = i;
		}
	}
}
signed main() {
	//freopen("1.in", "r", stdin);
	scanf("%d%d", &n, &m);
	For (i, 1, n) scanf("%d", &a[i]), val[++tot] = a[i];
	For (i, 1, m) {
		scanf("%d%d", &q[i].x, &q[i].v); q[i].id = i; val[++tot] = q[i].v;
	}
	sort(val + 1, val + tot + 1); tot = unique(val + 1, val + tot + 1) - val - 1;
	For (i, 1, n) a[i] = lb(val + 1, val + tot + 1, a[i]) - val;
	For (i, 1, m) q[i].v = lb(val + 1, val + tot + 1, q[i].v) - val;
	P1(); P2(); P3();                                                                                                                                                                                            
	For (i, 1, m) {
		if (flag[q[i].x]) cmax(ans[q[i].id], lans - 1);
		else cmax(ans[q[i].id], lans);
	}
	For (i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：robin12138 (赞：6)


[**题目传送门**：CF650D Zip-line](https://www.luogu.org/problem/CF650D)

 [**更好的阅读体验**](https://www.cnblogs.com/wmq12138/p/11740738.html)
 
题目大意：给一个序列$a$，多次询问(独立)，问把$a_x$ 变为 $y$ 后序列的$LIS$

首先发现答案只可能+$1$，-$1$，不变
先用树状数组求出来原序列的$LIS$，设$f_i$表示以$a_i$为结尾的$LIS$，$g_i$表示以$a_i$为开头的$LIS$

$1.$ +$1$的情况：由于只改变了$a_i$，所以只要看经过i的LIS即可：
设$f'$为满足$j<i,a_j<a_i'$的最大$f_j$，$g'$为满足 $j>i,a_j>a_i$的最大$g_j$
若$f'+g'+1>$原$LIS$，则$Ans=f'+g'+1$

$2.$ -$1$的情况：首先$i$一定是关键点，即是$LIS$的必经之路，然后判断一下$f'+g'+1$是否小于原$LIS$
判断关键点：
对于$f_i+g[i]=ans$的点 记其 $f_i$ 出现次数+1
一个点是关键点：当且仅当 $f_i+g_i-1 = Ans$ 且 这样的$f_i$只出现过一次

求$f_i$ 和 $g_i$ 的过程不用说，裸的树状数组求$LIS$

求$f'$ ：将询问离线，按x从小到大排序

求$g'$ ：倒过来再扫一次即可
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define rint register int
#define il inline
#define For(i,j,k) for(register int i=(j);i<=(k);++i)
#define Rep(i,j,k) for(register int i=(j);i>=(k);--i)

il int read(int x=0,int g=1,char ch='0')
{
    while(!isdigit(ch=getchar())) if(ch=='-') g=-1;
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return g*x;
}

const int N=8e5+5;
int a[N],b[N],g[N],f[N],c[N],cnt[N];
//g[i]：以第i个为开头，f[i]：以第i个为结尾的上升子序列长度
int n,m,ans,tmp,Ans[N];
struct node {int a,b,id,g,f;}q[N];
bool operator <(const node &n1,const node &n2) { return n1.a==n2.a?n1.b<n2.b:n1.a<n2.a; }

il void add(int x,int d) { for(;x<=tmp;x+=x&-x) c[x]=max(c[x],d); }
il int query(int x) { int ret=0; for(;x;x-=x&-x) ret=max(ret,c[x]); return ret; }
il void cls(int *c) { For(i,0,tmp) c[i]=0; }

il void work()
{
    sort(q+1,q+m+1);
    int t=1; cls(c); 
    For(i,1,m)
    {
        while(t<q[i].a) add(a[t],f[t]),++t;
        q[i].f=query(q[i].b-1);
    }
    
    t=n; cls(c);
    Rep(i,m,1)
    {
        while(t>q[i].a) add(tmp-a[t]+1,g[t]),--t;
        q[i].g=query(tmp-q[i].b);
        if(q[i].g+q[i].f+1>ans) Ans[q[i].id]=q[i].g+q[i].f+1;
    }

    For(i,1,m) if(!Ans[q[i].id])
    {
        if(f[q[i].a]+g[q[i].a]-1==ans&&cnt[f[q[i].a]]==1&&q[i].g+q[i].f+1<ans)
            Ans[q[i].id]=ans-1;
        else Ans[q[i].id]=ans;
    }
}

int main()
{   
    tmp=n=read(); m=read();
    For(i,1,n) b[i]=a[i]=read();
    For(i,1,m) q[i].a=read(),q[i].b=read(),q[i].id=i,b[++tmp]=q[i].b;
    sort(b+1,b+tmp+1); tmp=unique(b+1,b+tmp+1)-b-1;
    For(i,1,n) a[i]=lower_bound(b+1,b+tmp+1,a[i])-b;
    For(i,1,m) q[i].b=lower_bound(b+1,b+tmp+1,q[i].b)-b;//离散化
    ++tmp;
    For(i,1,n) f[i]=query(a[i]-1)+1,add(a[i],f[i]); cls(c);
    Rep(i,n,1) g[i]=query(tmp-a[i])+1,add(tmp-a[i]+1,g[i]);
    For(i,1,n) ans=max(ans,f[i]+g[i]-1);
    For(i,1,n) if(f[i]+g[i]-1==ans) ++cnt[f[i]];
    work();

    For(i,1,m) printf("%d\n",Ans[i]);
    return 0;
}

```

---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/650/problem/D) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF650D)

我怕不是个 nt……一开始忽略了”询问独立“这个条件……然后就一直在想有什么办法维护全局 LIS……心态爆炸

首先离散化。预处理出以每个点为结尾的 LIS 长度 $f_i$，以及以每个点为开头的 LIS 长度 $g_i$。

不难发现每次只修改一个元素，故每次询问的答案只可能是原序列 LIS 的长度 $mx\pm 1$。

我们不妨来探究什么情况下询问的答案为 $mx+1$，什么情况下询问的答案为 $mx-1$。

$+1$ 的情况比较容易，只可能是存在一个通过 $a_i$ 的长度为 $mx+1$ 的上升序列，如果我们记 $f'_i$ 为将 $a_i$ 位置上的值换成 $b_i$ 后，以 $a_i$ 结尾的 LIS 的长度，$g'_i$ 为将 $a_i$ 位置上的值换成 $b_i$ 后，以 $a_i$ 开头的 LIS 的长度，那么新序列中经过 $a_i$ 的上升序列的长度最大值即为 $f'_i+g'_i-1$，故若 $f'_i+g'_i-1=mx+1$，则新的 LIS 长度为 $mx+1$。

$-1$ 的情况相对来说比较困难，新序列 LIS 的长度为 $mx-1$ 需要两个条件，一是经过 $a_i$ 的 LIS 长度 $<mx$，二是所有长度为 $mx$ 的上升子序列都经过 $a_i$。条件一比较容易检验，还是记 $f'_i$ 为将 $a_i$ 位置上的值换成 $b_i$ 后，以 $a_i$ 结尾的 LIS 的长度，那么经过 $a_i$ 的 LIS 长度就是 $f'_i+g'_i-1$。比较麻烦的是条件二，一种可能的处理方式是在求 $f_i$ 的同时求出 $ed_i$ 表示有多少个长度为 $f_i$ 的上升子序列以 $i$ 结尾，$st_i$ 表示有多少个长度为 $g_i$ 的上升子序列以 $i$ 开头，那么总共有 $\dfrac{1}{mx}\sum\limits_{i}st_ied_i[f_i+g_i-1=mx]$ 个长度为 $mx$ 的 LIS。检验是否所有长度为 $mx$ 的上升子序列都经过 $a_i$ 需要满足两个条件，一是 $f_{a_i}+g_{a_i}-1=mx$，二是经过 $a_i$ 的 LIS 的个数等于长度为 $mx$ 的 LIS 的总个数，即 $st_ied_i=\dfrac{1}{mx}\sum\limits_{i}st_ied_i[f_i+g_i-1=mx]$，由于 LIS 的个数很多，故这里的 $f_i,g_i$ 需模上一个大质数，如 $998244353$ 等，这个实现起来略有些困难，就不展开讲解了（估计 CF 上此题 `hashing` 的 tag 就是留给这个解法的罢）。

这里给出一个较为简便的做法，首先 $f_{a_i}+g_{a_i}-1=mx$ 是必要条件，如果 $f_{a_i}+g_{a_i}-1\neq mx$ 那肯定不满足条件，其次关于 LIS 有一个性质，那就是若 $f_i+g_i-1=mx$，对于所有经过 $i$ 的 LIS，该 LIS 中第 $f_i$ 大的元素一定是 $i$。考虑反证法，设 $i$ 是这样的 LIS 中第 $j$ 个元素，若 $j<f_i$，那么在 $i$ 后面的元素有 $mx-j>g_i$ 个，而根据 $g_i$ 的定义知以 $i$ 开头的 LIS 长度最大为 $g_i$，矛盾，$j>f_i$ 的情况也同理。考虑对于不经过 $i$ 的 LIS，这样的 LIS 中第 $f_i$ 大的元素是什么，根据之前的分析知假设第 $f_i$ 大的元素是 $j$，那么一定有 $f_j=f_i$。也就是说如果 $f_j=f_{a_i},j\neq a_i$ 的 $j$ 存在，那 $a_i$ 就不符合题意。故只需开一个桶 $c_i$ 表示有多少 $f_j=i$ 的 $j$ 并检验 $c_{f_{a_i}}=1$ 即可。

至于怎么求 $f_i,g_i$……就按照套路把询问挂在 $a_i$ 处，然后按照树状数组求 LIS 的套路扫描一遍即可。时间复杂度 $n\log n$。

~~那问题就来了，如果这题询问不独立怎么做呢？~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=4e5;
int n,qu,key[MAXN*2+5],uni[MAXN*2+5],num=0,cnt=0;
int a[MAXN+5],x[MAXN+5],y[MAXN+5];
int v[MAXN+5],nxt[MAXN+5],hd[MAXN+5],item_n=0;
void ins(int p,int q){v[++item_n]=q;nxt[item_n]=hd[p];hd[p]=item_n;}
int getnum(int x){
	int l=1,r=num;
	while(l<=r){
		int mid=(l+r)>>1;
		if(uni[mid]==x) return mid;
		if(uni[mid]<x) l=mid+1;
		else r=mid-1;
	}
}
int f[MAXN+5],g[MAXN+5],qf[MAXN+5],qg[MAXN+5],c[MAXN+5];
int t[MAXN*2+5];
void add(int x,int v){for(int i=x;i<=num;i+=(i&(-i))) chkmax(t[i],v);}
int query(int x){int ret=0;for(int i=x;i;i&=(i-1)) chkmax(ret,t[i]);return ret;}
int main(){
	scanf("%d%d",&n,&qu);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),key[++cnt]=a[i];
	for(int i=1;i<=qu;i++) scanf("%d%d",&x[i],&y[i]),ins(x[i],i),key[++cnt]=y[i];
	sort(key+1,key+cnt+1);
	for(int i=1;i<=cnt;i++) if(key[i]!=key[i-1]) uni[++num]=key[i];
	for(int i=1;i<=n;i++) a[i]=getnum(a[i]);
	for(int i=1;i<=qu;i++) y[i]=getnum(y[i]);
	for(int i=1;i<=n;i++) f[i]=query(a[i]-1)+1,add(a[i],f[i]);
	memset(t,0,sizeof(t));
	for(int i=n;i;i--) g[i]=query(num-a[i])+1,add(num-a[i]+1,g[i]);
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++){
		for(int e=hd[i];e;e=nxt[e]){
			int id=v[e];qf[id]=query(y[id]-1)+1;
		} add(a[i],f[i]);
	}
	memset(t,0,sizeof(t));
	for(int i=n;i;i--){
		for(int e=hd[i];e;e=nxt[e]){
			int id=v[e];qg[id]=query(num-y[id])+1;
		} add(num-a[i]+1,g[i]);
	}
	int mx=0;
	for(int i=1;i<=n;i++) chkmax(mx,f[i]+g[i]-1);
	for(int i=1;i<=n;i++) if(f[i]+g[i]-1==mx) c[f[i]]++;
	for(int i=1;i<=qu;i++){
		if(qf[i]+qg[i]-1>mx) printf("%d\n",qf[i]+qg[i]-1);
		else if(qf[i]+qg[i]-1<mx&&f[x[i]]+g[x[i]]-1==mx&&c[f[x[i]]]==1) printf("%d\n",mx-1);
		else printf("%d\n",mx);
	}
	return 0;
}
```



---

## 作者：APOI (赞：1)

# 题解

先离散化一波。
首先10分做法可以直接暴力DP
记f[i]表示前i个数的LIS，那么寻找之前所有满足a[i] > a[j] 的j，另f[i]=max(f[j]+1,1)。

对于20分，注意到这是一个经典问题，为了之后的几档分数，我们这里选择可以用树状数组来进行优化。即求前缀中比它小的数的和。
每次处理一个数，就插入一个数。
这样，每次我们暴力修改，暴力求LIS能有50分。


考虑2，不经过这点的LIS。
显然答案要么是原来的len，要么是len-1。
这样我们只需要判断是否每一个LIS都必须经过它。
首先需要判断这个点是否能成为LIS的一部分。
设这个点的位置是i，要满足这个条件必须满足以i结束的最长上升子序列的长度加上以i开始的最长上升子序列的长度是原来的LIS-1。

同时，你要保证它是唯一的。
比如对于`1 2 2 3`，中间的两个2就不是唯一的。
怎么判断是否是唯一的？就是只有它能够转移到最后面，也就是如果存在（i,j）满足都可能成为LIS的一部分的，如果以i结束的LIS的长度和以j结束的LIS长度相同，那么i和j就可以互相替换。


代码如下

```cpp

#include<bits/stdc++.h>
using namespace std;
#define maxn 400005
#define IL inline
#define RG register
#define rep(i,a,b) for(RG int i=(a);i<(int)(b);++i)
#define Rep(i,a,b) for(RG int i=(a);i<=(int)(b);++i)
#define Dep(i,a,b) for(RG int i=(a);i>=(int)(b);--i)
#define pc putchar
#define gc getchar
using namespace std;
inline int read(){
    RG int x=0;RG char f=0;RG char c=gc();
    for(;!isdigit(c);c=gc())f|=(c=='-');
	for(;isdigit(c);c=gc())x=(x<<1)+(x<<3)+(c^48);
    return f?-x:x;
}
vector<int> q[maxn];
int lm[maxn*2],rm[maxn*2],wzp[maxn*2],a[maxn];
int n,m,N,ask[maxn],ans[maxn],f[maxn],g[maxn],cnt[maxn],qid[maxn];
IL void Max(int &a,int b){if(a<b)a=b;}
IL void A2l(int x,int v){for(;x<=N;x+=x&-x) Max(lm[x],v);}
IL void A2r(int x, int v){for(;x>0;x-=x&-x) Max(rm[x],v);}
IL int Qml(int x){int v=0;for(;x>0;x-=x&-x) Max(v,lm[x]); return v;}
IL int Qmr(int x){int v=0;for(;x<=N;x+=x&-x) Max(v,rm[x]); return v;}
int main() {
    n = read(),m = read();
    Rep(i,1,n)wzp[++N] = a[i] = read();
    Rep(i,1,m){
    	qid[i] = read(),ask[i] = read();
        q[qid[i]].push_back(i);
        wzp[++N] = ask[i];
        ans[i] = 1;
    }
    sort(wzp+1,wzp+N+1);
    N = unique(wzp+1,wzp+N+1) - wzp-1;
    Rep(i,1,n) a[i] = lower_bound(wzp+1,wzp+1+N,a[i])-wzp;
    Rep(i,1,m) ask[i] = lower_bound(wzp+1,wzp+1+N,ask[i])-wzp;
    int lgst = 0;
    Rep(i,1,n){
    	for(unsigned e=0;e<q[i].size();++e){
    		int j=q[i][e];
        	ans[j] += Qml(ask[j]-1);
    	}
        f[i] = Qml(a[i]-1)+1;
        A2l(a[i],f[i]); lgst = max(lgst, f[i]);
    }
    Dep(i,n,1){
    	rep(e,0,q[i].size())
			ans[q[i][e]] += Qmr(ask[q[i][e]]+1);
        g[i] = Qmr(a[i]+1)+1; A2r(a[i], g[i]);
    }
    long long Ans = 0;
    Ans ^= lgst;
    Rep(i,1,n) if(f[i]+g[i]==lgst+1) ++ cnt[f[i]];
    Rep(i,1,m)
        if(f[qid[i]] + g[qid[i]] == lgst + 1 && 1 == cnt[f[qid[i]]])
			printf("%lld\n",(long long)max(ans[i], lgst-1)) ;
		else
			printf("%lld\n",(long long)max(ans[i], lgst));
    return 0;
}
}```

---

## 作者：kernel_panic (赞：0)

## 思路

考虑替换序列中的一个元素对 LIS 的影响．设原序列的 LIS 长度为 $k$，由于我们每次只会替换一个元素，所以对于替换后的序列，LIS 长度只有 $3$ 种取值：$k - 1$，$k$，$k + 1$．

考虑对于询问 $i$，替换后序列的 LIS 的长度何时会取到这些值．假设我们已经计算出了包含 $b_i$ 的 LIS 的长度 $t$：

1. 若 $t \ge k$，那么答案显然为 $\max\{t, k\}$．
2. 若 $t < k$，我们发现答案为 $t$ 的充要条件是替换 $h_{a_i}$ 这一操作破坏了原序列中所有 LIS，否则答案仍然为 $k$．这一条件等价于对于序列中所有可能的 LIS，出现在 LIS 的某一位上的元素只有 $h_{a_i}$．

考虑如何计算 $t$．我们可以预处理出 $f_i$、$g_i$，分别表示以 $h_i$ 结束的 LIS 长度和以 $h_i$ 开头的 LIS 长度．考虑用 $b_i$ 连接两个上升序列，得到 LIS，我们有 $t = \max\limits_{j < a_i, h_j < b_i} f_j + 1 + \max\limits_{a_i < j, b_i < h_j} g_j$，这个 $\max$ 是二维数点的形式，扫描线一下就可以求出．

考虑如何判定 2 情况中答案是否为 $t$．我们可以计算出原序列的 LIS 中，$i$ 位置上能够填的元素数量，若这个数量为 $1$，那么替换 $i$ 位置上的元素就会破坏所有的 LIS．如何计算出这个数量？枚举位置 $i$，若 $f_i + g_i - 1 = k$，说明 $h_i$ 至少出现在了一个 LIS 中，且出现位置为 $f_i$，用一个桶计数即可．

## 代码

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

inline int rd() {
	int x = 0, f = 1, c = getchar();
	while (((c - '0') | ('9' - c)) < 0)
		f = c != '-', c = getchar();
	while (((c - '0') | ('9' - c)) > 0)
		x = x * 10 + c - '0', c = getchar();
	return f ? x : -x;
}

using pii = std::pair<int, int>;
const int N = 1e6;

int n, m, a[N + 5];
int b[N + 5], bct;

std::vector<pii> q[N + 5];
int ans[N + 5];

namespace fwt {
	int t[N + 5];
	inline int lowbit(int x) { return x & (-x); }
	inline void upd(int x, int d) {
		for (int i = x; i <= bct; i += lowbit(i)) {
			t[i] = std::max(t[i], d);
		}
	}
	inline int que(int x) {
		int res = 0;
		for (int i = x; i >= 1; i -= lowbit(i)) {
			res = std::max(res, t[i]);
		}
		return res;
	}
	inline void init() { memset(t, 0, sizeof(t)); }
}; // namespace fwt

int f[N + 5], g[N + 5], h[N + 5];

int pfx[N + 5], sfx[N + 5];

int main() {
	n = rd(), m = rd();
	for (int i = 1; i <= n; i++) {
		a[i] = rd();
		b[++bct] = a[i];
	}
	for (int i = 1; i <= m; i++) {
		int x = rd(), d = rd();
		q[x].emplace_back(d, i);
		b[++bct] = d;
	}
	std::sort(b + 1, b + 1 + bct);
	bct = std::unique(b + 1, b + 1 + bct) - b - 1;
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + 1 + bct, a[i]) - b;
		for (auto &[x, _] : q[i]) {
			x = std::lower_bound(b + 1, b + 1 + bct, x) - b;
		}
	}

	fwt::init();
	for (int i = 1; i <= n; i++) {
		f[i] = fwt::que(a[i] - 1) + 1;
		fwt::upd(a[i], f[i]);
	}
	fwt::init();
	for (int i = n; i >= 1; i--) {
		g[i] = fwt::que(bct - a[i]) + 1;
		fwt::upd(bct - a[i] + 1, g[i]);
	}

	int k = 0;
	for (int i = 1; i <= n; i++) k = std::max(k, f[i] + g[i] - 1);
	for (int i = 1; i <= n; i++) if (f[i] + g[i] - 1 == k) h[f[i]]++;
	fwt::init();
	for (int i = 1; i <= n; i++) {
		for (auto [x, id] : q[i]) {
			pfx[id] = fwt::que(x - 1);
		}
		fwt::upd(a[i], f[i]);
	}
	fwt::init();
	for (int i = n; i >= 1; i--) {
		for (auto [x, id] : q[i]) {
			sfx[id] = fwt::que(bct - x);
		}
		fwt::upd(bct - a[i] + 1, g[i]);
	}

	for (int i = 1; i <= n; i++) {
		for (auto [x, id] : q[i]) {
			if (pfx[id] + sfx[id] + 1 < k && f[i] + g[i] - 1 == k && h[f[i]] == 1) {
				ans[id] = k - 1;
			} else ans[id] = std::max(pfx[id] + sfx[id] + 1, k);
		}
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：LlLlCc (赞：0)

## 带修改$LIS$问题

题目特意标注每次询问是互相独立的，这也提示了我们可以离线来做这题

把每次修改用动态数组记录下来，当枚举到时在处理，求出修改后的值必选的最长上升子序列长度

我们分两类考虑：

- $a_i$可以不在原序列最长上升子序列中，答案即为原序列的最长上升子序列长度和修改后值必选的最长上升子序列长度取大

- $a_i$一定在原序列最长上升子序列中，答案即为原序列的最长上升子序列长度$-1$和修改后值必选的最长上升子序列长度取大

现在我们来解决如何求出修改后的值必选的最长上升子序列长度

我们可以先正着求一遍最长上升子序列，再反着求最长下降子序列即可

## code
```
#include<bits/stdc++.h>
#define maxn 400005
using namespace std;
int f[maxn],Ans,N,Q,a[maxn],q[15],x,Nn,n,m,L_[maxn],L[maxn],R[maxn],R_[maxn],Now,Mx,vis[maxn],b[maxn],data,S[maxn];
struct lc{
	int x,id;
};
vector<lc> s[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void Write(int x){
	if (!x){puts("0");return;}
	Nn=0;while (x){q[++Nn]=x%10,x/=10;}
	for (int i=Nn;i;i--) putchar('0'+q[i]);
	putchar('\n');
}
int main(){
	n=read(),Q=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++){
		if (a[i]>f[N]) f[++N]=a[i],L[i]=N;
		else{
			int l=1,r=N,X=0;
			while (l<=r){
				int mid=l+r>>1;
				if (f[mid]>=a[i]) X=mid,r=mid-1;
				else l=mid+1;
			}
		    if (X) f[X]=a[i],L[i]=X;
		    else L[i]=1;
		}
	}
	Ans=N;N=0;memset(f,0,sizeof f);
	for (int i=n;i;i--){
		if (a[i]<f[N]||!N) f[++N]=a[i],R[i]=N;
	    else{
	    	int l=1,r=N,X=0;
	    	while (l<=r){
	    		int mid=l+r>>1;
	    		if (f[mid]<=a[i]) X=mid,r=mid-1;
	    		else l=mid+1;
			}
			if (X) f[X]=a[i],R[i]=X;
			else R[i]=1;
		}
	}
	for (int i=1;i<=n;i++) if (L[i]+R[i]-1==N) vis[L[i]]++;
	for (int i=1;i<=n;i++)
	  if (L[i]+R[i]-1==N){
	  	if (vis[L[i]]!=1) b[i]=1;
	  	else b[i]=2;
	  }
	memset(L,0,sizeof L);memset(R,0,sizeof R);
	for (int i=1;i<=Q;i++){
		S[i]=read(),data=read();
		s[S[i]].push_back((lc){data,i});
	}
	N=0;memset(f,0,sizeof f);
	for (int i=1;i<=n;i++){
		int Size=s[i].size();
		for (int j=0;j<Size;j++){
			if (s[i][j].x>f[N]) L_[s[i][j].id]=N+1;
			else{
				int l=1,r=N,X=0;
				while (l<=r){
			    	int mid=l+r>>1;
		    		if (f[mid]>=s[i][j].x) X=mid,r=mid-1;
		    		else l=mid+1;
		    	}
		        if (X) L_[s[i][j].id]=X;
		        else L_[s[i][j].id]=1;
			}
		}
		if (a[i]>f[N]) f[++N]=a[i],L[i]=N;
		else{
			int l=1,r=N,X=0;
			while (l<=r){
				int mid=l+r>>1;
				if (f[mid]>=a[i]) X=mid,r=mid-1;
				else l=mid+1;
			}
		    if (X) f[X]=a[i],L[i]=X;
		    else L[i]=1;
		}
	}
	N=0;memset(f,0,sizeof f);
	for (int i=n;i;i--){
		int Size=s[i].size();
		for (int j=0;j<Size;j++){
			if (s[i][j].x<f[N]||!N) R_[s[i][j].id]=N+1;
			else{
				int l=1,r=N,X=0;
				while (l<=r){
			    	int mid=l+r>>1;
		    		if (f[mid]<=s[i][j].x) X=mid,r=mid-1;
		    		else l=mid+1;
		    	}
		        if (X) R_[s[i][j].id]=X;
		        else R_[s[i][j].id]=1;
			}
		}
		if (a[i]<f[N]||!N) f[++N]=a[i],R[i]=N;
	    else{
	    	int l=1,r=N,X=0;
	    	while (l<=r){
	    		int mid=l+r>>1;
	    		if (f[mid]<=a[i]) X=mid,r=mid-1;
	    		else l=mid+1;
			}
			if (X) f[X]=a[i],R[i]=X;
			else R[i]=1;
		}
	}
	for (int i=1;i<=Q;i++){
		if (b[S[i]]<2) Write(max(Ans,L_[i]+R_[i]-1));else
		Write(max(Ans,L_[i]+R_[i])-1);
	}
	return 0;
}
```


---

## 作者：Lunch (赞：0)

## [题意](http://codeforces.com/problemset/problem/650/D)

- 给你一个长为$n$的序列，$q$个询问，每次询问把位置$x$的值修改为$y$后的$LIS$,询问相互独立。

这个题观察一下性质，如果修改的位置原来属于$LIS$，那么这部分答案要么是$LIS$要么是$LIS - 1$。如果不是的话，那么查询一下这个数前面以一个小于它的数结尾的$LIS$，查询这个数后面以一个大于它的数开头的$LIS$。

这个过程可以用把询问按$y$排序后用树状数组实现，复杂度$O(n\log n)$。


```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
#define go(x, i) for(register int i = head[x]; i; i = nxt[i])
#define For(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define FOR(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(x) cout << #x << " = " << x << endl
#define mem(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))
#define min(a, b) (a < b ? a : b)
#define max(a, b) (b < a ? a : b)
#define inf (0x3f3f3f3f)
#define INF (1e18)
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define y1 orzorz

typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;
typedef std::pair<ll, int> PLI;
typedef std::pair<int, int> PII;
typedef long double ldb;
typedef double db;

namespace IO {
#define getc() ((S_ == T_) && (T_ = (S_ = Ch_) + fread(Ch_, 1, Buffsize, stdin), S_ == T_) ? 0 : *S_ ++)
#define putc(x) *nowps ++ = (x)
	const uint Buffsize = 1 << 15, Output = 1 << 23;
	static char Ch_[Buffsize], *S_ = Ch_, *T_ = Ch_;
	static char Out[Output], *nowps = Out;
	inline void flush(){fwrite(Out, 1, nowps - Out, stdout); nowps = Out;}
	template<class T>inline void read(T &_) {
		_ = 0; static char __; T ___ = 1;
		for(__ = getc(); !isdigit(__); __ = getc()) if(__ == '-') ___ = -1;
		for(; isdigit(__); __ = getc()) _ = (_ << 3) + (_ << 1) + (__ ^ 48);
		_ *= ___;
	}
	template<class T>inline void write(T _, char __ = '\n') {
		if(!_) putc('0');
		if(_ < 0) putc('-'), _ = -_;
		static uint sta[111], tp;
		for(tp = 0; _; _ /= 10) sta[++ tp] = _ % 10;
		for(; tp; putc(sta[tp --] ^ 48)); putc(__);
	}
	template<class T>inline bool chkmax(T &_, T __) {return _ < __ ? _ = __, 1 : 0;}
	template<class T>inline bool chkmin(T &_, T __) {return _ > __ ? _ = __, 1 : 0;}
	inline void procStatus() {
		std::ifstream t("/proc/self/status");
		std::cerr << std::string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
	}
}

using namespace std;
using namespace IO;

const int N = 5e5 + 10;

int st[N], ed[N], S[N], inlis[N];
int a[N], ans[N], Cnt[N], pos[N];
int n, q, cnt, top, join0, join1;

struct Join {
	int x, y, z;
	bool operator < (const Join &T) const {
		return x < T.x;
	}
}join[2][N];

struct Que {
	int x, y, id, tmp[2];
	bool operator < (const Que &T) const {
		return y < T.y;
	}
}Q[N];

struct Fenwick_Tree {
	int S[N], res;
	void update(int x, int y) {for(; x <= n; x += x & -x) chkmax(S[x], y);}
	int query(int x) {for(res = 0; x; x -= x & -x) chkmax(res, S[x]); return res;}
}T[2];

int main() {
#ifdef ylsakioi
	file("kite");
#endif

	read(n), read(q);
	For(i, 1, n) read(a[i]);
	For(i, 1, q) read(Q[i].x), read(Q[i].y), Q[i].id = i;
	sort(Q + 1, Q + q + 1);

	S[top = 0] = INT_MIN;
	For(i, 1, n) {
		if(a[i] > S[top]) S[ed[i] = ++ top] = a[i];
		else S[ed[i] = lower_bound(S + 1, S + top + 1, a[i], less<int>()) - S] = a[i];
		join[0][i] = Join{a[i], i, ed[i]};
	}
	S[top = 0] = INT_MAX;
	FOR(i, n, 1) {
		if(a[i] < S[top]) S[st[i] = ++ top] = a[i];
		else S[st[i] = lower_bound(S + 1, S + top + 1, a[i], greater<int>()) - S] = a[i];
		join[1][i] = Join{a[i], n - i + 1, st[i]};
	}

	sort(join[0] + 1, join[0] + n + 1), sort(join[1] + 1, join[1] + n + 1);

	For(i, 1, n) if(ed[i] + st[i] == top + 1) ++ Cnt[ed[i]], inlis[i] = 1;

	join0 = 1;
	For(i, 1, q) {
		ans[Q[i].id] = top - (inlis[Q[i].x] & (Cnt[ed[Q[i].x]] == 1));
		for(; join0 <= n && join[0][join0].x < Q[i].y; ++ join0)
			T[0].update(join[0][join0].y, join[0][join0].z);
		Q[i].tmp[0] = T[0].query(Q[i].x - 1);
	}
	join1 = n;
	FOR(i, q, 1) {
		for(; join1 >= 1 && join[1][join1].x > Q[i].y; -- join1) 
			T[1].update(join[1][join1].y, join[1][join1].z);
		Q[i].tmp[1] = T[1].query(n - Q[i].x);
		chkmax(ans[Q[i].id], Q[i].tmp[0] + Q[i].tmp[1] + 1);
	}

	For(i, 1, q) write(ans[i]);

	return flush(), 0;
}


```

---

