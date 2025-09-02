# [ARC159D] LIS 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc159/tasks/arc159_d

数列 $ X $ があります。初め、$ X $ は空です。  
 高橋君は $ i=1,2,\ldots,N $ の順に次の操作をしました。

- $ X $ の末尾に $ l_i,l_i+1,\ldots,r_i $ をこの順番で追加する。
 
操作後の $ X $ の狭義単調増加部分列の長さの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ l_i\ \leq\ r_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

操作後の $ X $ は $ (1,2,3,4,10,11,7,8,9,10) $ です。 この数列の $ 1,2,3,4,7,8,9,10 $ 項目からなる部分列は狭義単調増加であり、かつこれが長さが最大のものです。

### Sample Explanation 2

操作後の $ X $ は $ (1,1,1,1) $ です。

## 样例 #1

### 输入

```
4
1 1
2 4
10 11
7 10```

### 输出

```
8```

## 样例 #2

### 输入

```
4
1 1
1 1
1 1
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
1
1 1000000000```

### 输出

```
1000000000```

# 题解

## 作者：良心WA题人 (赞：15)

## 前言

垃圾 D 题，现在 AtCoder 的某些题目越来越烂了。不过不太理解为什么赛时没几个人过。

## 题意

给定一个用一堆 $l_i,l_i+,...,r_i$ 拼起来的序列，求最长上升子序列长度。

## 思路

令 $f_i$ 表示以 $r_i$ 结尾的最长上升子序列长度。则 $f_i=\max(\max\{r_i+f_j-r_j|r_j\ge l_i\},\max\{r_i-l_i+1+f_j|r_j<l_i\})$。

然后这个显然可以离散化 $l_i$ 和 $r_i$ 后用两棵权值线段树分别维护 $f_i$ 和 $f_i-r_i$ 的最大值。就结束了。

时间复杂度 $O(n\log_2n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NN=2e5+4;
int f[NN],l[NN],r[NN];
struct node
{
	struct segment_tree
	{
		int l,r,v;
	}tr[NN<<3];
	void pushup(int u)
	{
		tr[u].v=max(tr[u<<1].v,tr[u<<1|1].v);
	}
	void build(int u,int l,int r)
	{
		tr[u]={l,r,0};
		if(l==r)
		{
			tr[u].v=-1e9;
			return;
		}
		int mid=l+(r-l)/2;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
		pushup(u);
	}
	void modify(int u,int p,int v)
	{
		if(tr[u].l==tr[u].r)
		{
			tr[u].v=max(tr[u].v,v);
			return;
		}
		int mid=tr[u].l+(tr[u].r-tr[u].l)/2;
		if(p<=mid)
			modify(u<<1,p,v);
		else
			modify(u<<1|1,p,v);
		pushup(u);
	}
	int query(int u,int l,int r)
	{
		if(tr[u].l>=l&&tr[u].r<=r)
			return tr[u].v;
		int mid=tr[u].l+(tr[u].r-tr[u].l)/2,res=-1e9;
		if(l<=mid)
			res=max(res,query(u<<1,l,r));
		if(r>mid)
			res=max(res,query(u<<1|1,l,r));
		return res;
	}
}A,B;
signed main()
{
	int n;
	scanf("%lld",&n);
	vector<int>nums;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&l[i],&r[i]);
		nums.push_back(l[i]);
		nums.push_back(r[i]);
	}
	nums.push_back(0);
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	A.build(1,1,nums.size());
	B.build(1,1,nums.size());
	A.modify(1,1,0);
	B.modify(1,1,0);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int pl=lower_bound(nums.begin(),nums.end(),l[i])-nums.begin()+1,pr=lower_bound(nums.begin(),nums.end(),r[i])-nums.begin()+1;
		f[i]=max(f[i]+r[i]-l[i]+1+A.query(1,1,pl-1),f[i]+r[i]+B.query(1,pl,pr));
		ans=max(ans,f[i]);
		A.modify(1,pr,f[i]);
		B.modify(1,pr,f[i]-r[i]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：namelessgugugu (赞：9)

垃圾题。

#### 题意

初始时有一个空序列 $A$，接下来 $n$ 次操作，每次给定 $l_i, r_i$，然后把 $l_i, l_i + 1, l_i + 2, \dots, r_i$ 依次插入 $A$ 的末尾，求最终 $A$ 的严格最长上升子序列。

$1 \leq n \leq 2 \cdot 10^5, 1 \leq l_i \leq r_i \leq 10^9$。

#### 题解

考虑用二分 + 栈的做法去求 LIS。如果当前的栈是 $s$，插入一整个区间 $[l_i, r_i]$ 时，假设插入 $l_i$ 时把 $s_p$ 替换成 $l_i$，那么插入 $l_i + 1$ 时就会把 $s_{p + 1}$ 替换成 $l_i + 1$，以此类推，最后插入 $r_i$ 的时候会把 $s_{p + r_i - l_i}$ 替换成 $r_i$（如果当前栈的大小为 $k$，那么 “把 $s_{k + 1}$ 替换成 $x$” 就表示往 $s$ 后面压入一个数 $x$）。

于是可以发现这个栈一定是由若干段区间拼起来的，每次插入一个新区间的时候，会删除一些区间，修改 $O(1)$ 个区间，再插入 $1$ 个新区间，这是容易用 `set` 维护的。由于每个区间只会被插入一次，删除一次，总复杂度是 $O(n \log n)$ 的。

#### 代码

```cpp
#include <cstdio>
#include <set>
int n;
std::set<std::pair<int, int>> st; 
int main(void)
{
	scanf("%d", &n);
	for(int i = 1, l, r;i <= n;++i)
	{
		scanf("%d%d", &l, &r);
		auto it = st.lower_bound({l + 1, 0});
		if(it != st.begin())
			l = std::max(std::prev(it)->second + 1, l);
		if(l > r)
			continue;
		int rem = r - l + 1;
		while(rem && it != st.end())
			if(it->second - it->first + 1 <= rem)
				rem -= (it->second - it->first + 1), st.erase(it++);
			else
				st.insert({it->first + rem, it->second}), rem = 0, st.erase(it); 
		st.insert({l, r});
	}
	int ans = 0;
	for(auto pr : st)
		ans += pr.second - pr.first + 1;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：2huk (赞：6)

> 给定 $n$ 个操作，每次操作给出 $l,r$，并在 $a$ 序列里依次添加 $i\in[l,r]$。
>
> 求最后 $a$ 的最长上升子序列。
>
> $1 \le n \le 2 \times 10^5$，$1 \le l \le r \le 10^9$。

设计初始 DP：设 $f_i$ 表示以 $r_i$ 结尾的最长上升子序列的长度，则对于一个前面的区间 $[l_j, r_j]$，转移如下：

- 若 $r_j < l_i$，也就是两个区间没有交集，那么我们可以直接把 $[l_i, r_i]$ 接到 $[l_j, r_j]$ 后面。即 $f_i = f_j + r_i - l_i + 1$；

  ![](https://cdn.luogu.com.cn/upload/image_hosting/ckd9lcia.png)

- 若 $r_j \ge l_i$，也就是两个区间存在交集，那么直接把把 $[l_i, r_i]$ 接到 $[l_j, r_j]$ 后面是不可取的，因为这会导致 $[l_i, r_j]$ 这一段区间重复。所以我们需要将这一段区间去掉。即 $f_i = f_j + (r_i - l_i + 1) - (r_j - l_i + 1) = f_j + r_i - r_j$。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/4x5rj46m.png)

因此总转移为：
$$
f_i = \max_{j = 1}^{i - 1}\left\{\begin{matrix}f_j + r_i - l_i + 1  &, r_j < l_i\\ f_j + r_i - r_j & ,r_j \ge l_i\end{matrix}\right.
$$


直接转移复杂度是 $\Theta(n^2)$ 的。因此可以数据结构优化，比如线段树。

我们维护两颗线段树，均以 $r_i$ 作下标，其中第一颗线段树维护 $f_i$，第二颗线段树维护 $f_j - r_j$。那么转移时这需要在第一颗线段树的 $[1, l_i - 1]$ 的下标内找最大值，并在第二颗线段树的 $[l_i, r_i]$ 找最大值并取更大即可。

计算完后需要在当前下标位置更新。

注意计算前需要离散化。

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 400010;

int n, l[N], r[N];
int L[N], R[N], b[N], cnt, len;
int f[N];

struct Tree
{
	struct Node
	{
		int l, r, v;
	}tr[N << 2];
	
	#define ls (u << 1) 
	#define rs (u << 1 | 1)
	
	void pushup(int u)
	{
		tr[u].v = max(tr[ls].v, tr[rs].v);
	}
	
	void build(int u, int l, int r)
	{
		tr[u] = {l, r, (int)-2e9};
		if (l == r) return;
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
	}
	
	void modify(int u, int x, int d)
	{
    if (tr[u].l > x || tr[u].r < x) return;
		if (tr[u].l == tr[u].r) tr[u].v = max(tr[u].v, d);
		else
		{
			int mid = tr[u].l + tr[u].r >> 1;
			if (x <= mid) modify(ls, x, d);
			else modify(rs, x, d);
			pushup(u);
		}
	}
	
	int query(int u, int l, int r)
	{
    if (l > r || tr[u].l > r || tr[u].r < l) return -2e9;
		if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
		int mid = tr[u].l + tr[u].r >> 1, res = -2e9;
		if (l <= mid) res = query(ls, l, r);
		if (r > mid) res = max(res, query(rs, l, r));
		return res;
	}
}A, B;

main()
{
	cin >> n;
	
	for (int i = 1; i <= n; ++ i )
		cin >> l[i] >> r[i],
		b[ ++ cnt] = l[i], b[ ++ cnt] = r[i];
	
	sort(b + 1, b + cnt + 1);
	len = unique(b + 1, b + cnt + 1) - b - 1;
	
	for (int i = 1; i <= n; ++ i )
		L[i] = lower_bound(b + 1, b + len + 1, l[i]) - b,
		R[i] = lower_bound(b + 1, b + len + 1, r[i]) - b;
	
	A.build(1, 1, len), B.build(1, 1, len);
	
	for (int i = 1; i <= n; ++ i )
	{
		f[i] = max({
			r[i] - l[i] + 1,
			A.query(1, 1, L[i] - 1) + r[i] - l[i] + 1,
			B.query(1, L[i] + 1, R[i] - 1) + r[i]
		});
		
		A.modify(1, R[i], f[i]);
		B.modify(1, R[i], f[i] - r[i]);
	}
	
	cout << *max_element(f + 1, f + n + 1);
	
	return 0;
}
```

---

## 作者：xhhhh36 (赞：4)

[传送门](https://www.luogu.com.cn/problem/AT_arc159_d)

可以发现对于每一个区间 $l,r$，在求 $a$ 的最长严格上升子序列的时候若要使用这个区间作为结尾，当 $r$ 作为最长严格上升子序列的结尾时最优。

那么就可以进行 dp，设 $dp_{i}$ 为以 $r_i$ 为结尾的最长严格上升子序列的长度，那么 $dp_i$ 就可以在 $dp_j(1\le j\le i-1)$ 的答案后面加上第 $i$ 个序列的一部分进行转移。
- 当 $r_j\ge r_i$ 时，$dp_i$ 无法在 $dp_j$ 的基础上增加任何数，只能取 $l_i$ 到 $r_i$ 这一段。
- 否则当 $r_j\ge l_i$ 时，$dp_i$ 可以在 $dp_j$ 的基础上增加 $r_j+1$ 到 $r_i$ 这一段。
- 否则 $r_j<l_i$，此时 $dp_i$ 可以将 $l_i$ 到 $r_i$ 这一段全部加在 $dp_j$ 后面。

所以：$dp_i=\max(\max\{dp_j+r_i-r_j|l_i\le r_j < r_i\},\max\{dp_j+r_i-l_i+1|r_j<l_i\})$。

但是这样转移是 $O(n^2)$ 的，可以考虑用权值线段树维护 $dp_j$ 和 $dp_j-r_j$ 的最大值，每次 $O(\log n)$ 查询，总时间复杂度为 $O(n \log n)$。因为 $l_i$ 和 $r_i$ 的值较大，所以要使用离散化。
# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n;
struct node
{
	int l,r;
}a[N];
int dp[N],k,ans;
map<int,int> m;
int b[N*2],cnt;
struct type
{
	struct tree
	{
		int l,r,mx;
	}tr[N*8];
	void push_up(int u)
	{
		tr[u].mx=max(tr[u*2].mx,tr[u*2+1].mx);
	}
	void build(int u,int l,int r)
	{
		tr[u].l=l;
		tr[u].r=r;
		if (l==r)
		{
			tr[u].mx=INT_MIN;
			return;
		}
		int mid=l+r>>1;
		build(u*2,l,mid);
		build(u*2+1,mid+1,r);
		push_up(u);
	}
	void update(int u,int c,int k)
	{
		if (tr[u].l>c||tr[u].r<c) return;
		if (tr[u].l==tr[u].r)
		{
			tr[u].mx=max(tr[u].mx,k);
			return;
		}
		update(u*2,c,k);
		update(u*2+1,c,k);
		push_up(u);
	}
	int query(int u,int l,int r)
	{
		if (tr[u].l>=l&&tr[u].r<=r)
		{
			return tr[u].mx;
		}
		if (tr[u].l>r||tr[u].r<l)
		{
			return INT_MIN;
		}
		return max(query(u*2,l,r),query(u*2+1,l,r));
	}
}t1,t2;
signed main()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
		b[i*2-1]=a[i].l,b[i*2]=a[i].r;
	}
	sort(b+1,b+1+n*2);
	for (int i=1;i<=n*2;i++)
	{
		if (!m[b[i]]) m[b[i]]=++cnt;
	}
	t1.build(1,0,cnt);
	t2.build(1,0,cnt);
	t1.update(1,0,0);
	for (int i=1;i<=n;i++)
	{
		dp[i]=max(t1.query(1,0,m[a[i].l]-1)+a[i].r-a[i].l+1,t2.query(1,m[a[i].l],m[a[i].r])+a[i].r);
		t1.update(1,m[a[i].r],dp[i]);
		t2.update(1,m[a[i].r],dp[i]-a[i].r); 
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Iratis (赞：4)

~~首先题目都叫 LIS 了，显然可以试试 dp。~~

这题放在 D 是离谱的，赛时多亏第一眼不会 C 才开了这题（bushi

首先发现倘若一段之后能接上下一段，则接上一定优，不妨设计 $ f_i $ 表示以 $ r_i $ 结尾的 LIS 的长度。

转移则十分好办：

若 $ r_j<l_i $，$ f_i=f_j+r_i-l_i+1 $。

若 $ r_j>l_i $，$ f_i=f_j+r_i-r_j $。

然后就发现可以线段树优化 dp。

代码如下：

```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
#define int long long
#define md(a) a=(a%mod+mod)%mod
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
const int N=400005,inf=1e16;
int n,m,l[N],r[N],rl[N],rr[N],f[N],cnt,b[N];
struct S
{
	struct Seg{int l,r,dat;}tree[N*4];
	void pushup(int v){tree[v].dat=max(tree[v*2].dat,tree[v*2+1].dat);}
	void build(int v,int l,int r)
	{
		tree[v]={l,r,-inf};if(l==r)return ;
		int mid=l+r>>1;build(v*2,l,mid),build(v*2+1,mid+1,r);
	}
	void add(int v,int x,int d)
	{
		if(tree[v].l>x||tree[v].r<x)return ;
		if(tree[v].l==tree[v].r)return void(tree[v].dat=max(tree[v].dat,d));
		add(v*2,x,d),add(v*2+1,x,d),pushup(v);
	}
	int ask(int v,int l,int r)
	{
		if(tree[v].l>r||tree[v].r<l)return -inf;
		if(l<=tree[v].l&&tree[v].r<=r)return tree[v].dat;
		return max(ask(v*2,l,r),ask(v*2+1,l,r));
	}
}A,B;
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&l[i],&r[i]),b[++cnt]=l[i],b[++cnt]=r[i];
	sort(b+1,b+cnt+1),m=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++)rl[i]=lower_bound(b+1,b+m+1,l[i])-b;
	for(int i=1;i<=n;i++)rr[i]=lower_bound(b+1,b+m+1,r[i])-b;
	A.build(1,1,m),B.build(1,1,m);
	for(int i=1;i<=n;i++)
	{
		f[i]=r[i]-l[i]+1,f[i]=max(f[i],A.ask(1,1,rl[i]-1)+r[i]-l[i]+1);
		f[i]=max(f[i],B.ask(1,rl[i]+1,rr[i]-1)+r[i]),A.add(1,rr[i],f[i]),B.add(1,rr[i],f[i]-r[i]);
	}
	int ans=0;for(int i=1;i<=n;i++)ans=max(ans,f[i]);cout<<ans;
	return 0;
}
```

---

## 作者：RNTBW (赞：4)

### PART 0

wtcl。

## PART 1

给出 $n$ 组数 $l_i,r_i$，求依次把 $\forall j\in[l_i,r_i]$ 拼起来的序列的 LIS。

## PART 2

首先，这是一道线段树优化 dp。

没错，就是 dp。

我们首先想朴素的 dp 方程。

考虑设 $dp_i$ 表示以 $r_i$ 为结尾的 LIS。

肯定是要枚举之前的 $j$ 并尝试将当前这段区间加到区间 $j$ 后面去。

那么就有两种情况：

1. $r_j<l_i$：

这种情况就说明 $r_j$ 的后一个数就是 $l_i$，所以整个区间 $i$ 都可以接上去。

那么新加的长度就是区间 $i$ 的长度。

$dp_i=dp_j+(r_i-l_i+1)$

2. $r_j\ge l_i$。

这种情况就说明新加的是 $r_j,r_j+1,....,r_i$，区间 $i$ 只有部分可以加上去。

那么新加的长度就是 $r_j+1,....,r_i$，即 $r_i-r_j$。

$dp_i=dp_j+(r_i-r_j)$

综上，$dp_i=\max _{j=1}^{i-1}\begin{cases} dp_j+r_i-l_i+1(r_j<l_i)\\ dp_j-r_j+r_i(r_j\ge l_i)\end{cases}$

但是这样做是 $O(n^2)$ 的。

## PART 3

我们考虑线段树优化。

根据上个式子，我们可以发现与 $j$ 相关的有 $dp_j,dp_j-r_j$ 两项。

所以我们可以用两棵下标为 $r_j$ 的权值线段树维护 $dp_j$ 与 $dp_j-r_j$。

这样我们每次只需要取出 $1\to l_i-1$ 范围内最大的 $dp_j$ 与 $l_i\to r_i$ 范围内最大的 $dp_j-r_j$，加上后面那堆之后取个 $\max$ 即可。

## PART 4

需要离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200001
int z[N<<3][3],l[N],r[N];//val:离散化之后的r[i]
int n,m,i,j,k,s,now,ans,cnt;
vector<int> val;
//z[p][1]维护dp[j]
//z[p][2]维护dp[j]-r[j]
void make_tree(int p,int l,int r,int now)
{
	z[p][now]=-1e9;
	if(l==r)return;
	z[p][now]=0;
	int mid=(l+r)>>1;
	make_tree(p<<1,l,mid,now);
	make_tree(p<<1|1,mid+1,r,now);
	z[p][now]=max(z[p<<1][now],z[p<<1|1][now]);
}
void add(int p,int l,int r,int d,int to,int now)
{
	if(l==r)
	{
		z[p][now]=max(z[p][now],d);
		return;
	}
	int mid=(l+r)>>1;
	if(to>mid)add(p<<1|1,mid+1,r,d,to,now);
	else add(p<<1,l,mid,d,to,now);
	z[p][now]=max(z[p<<1][now],z[p<<1|1][now]);
}
int query(int p,int l,int r,int k,int s,int now)
{
	if(k<=l&&r<=s)return z[p][now];
	int mid=(l+r)>>1,ans=-1e9;
	if(k<=mid)ans=max(ans,query(p<<1,l,mid,k,s,now));
	if(s>mid)ans=max(ans,query(p<<1|1,mid+1,r,k,s,now));
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		val.push_back(l[i]);
		val.push_back(r[i]);//l[i],r[i]都需要离散化
	}
	val.push_back(0);
	sort(val.begin(),val.end());
	val.erase(unique(val.begin(),val.end()),val.end());
	m=val.size();//离散化用了vector,其实可以用数组
	make_tree(1,1,m,1);
	make_tree(1,1,m,2);
	add(1,1,m,0,1,1);
	add(1,1,m,0,1,2);
	for(i=1;i<=n;i++)
	{
		k=lower_bound(val.begin(),val.end(),l[i])-val.begin()+1;
		s=lower_bound(val.begin(),val.end(),r[i])-val.begin()+1;//查询离散化之后的l[i],r[i]
		now=max(query(1,1,m,1,k-1,1)+r[i]-l[i]+1,query(1,1,m,k,s,2)+r[i]);
		ans=max(ans,now);//now即为当前的dp[i],只不过省略了dp数组
		add(1,1,m,now,s,1);
		add(1,1,m,now-r[i],s,2);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：2)

小清新 dp 优化。

定义 $dp_i$ 为以 $r_i$ 结尾的最长上升子序列长度。

我们可以从两种线段转移到 $i$，一种是和 $i$ 有交的，一种是没交的，这两种转移的贡献计算方式是截然不同的。

所以我们对这两种转移方式分别列出转移方程。

$$f_{i}=\displaystyle\max_{j=1}^{i-1} f_j+r_i-r_j\ (l_i\le r_j)$$

$$g_{i}=\displaystyle\max_{j=1}^{i-1} g_j+r_i-l_i+1\ (l_i> r_j)$$

那么 $dp_i=\max(f_i,g_i)$。

答案即为 $\displaystyle\max_{i=1}^{n} dp_i$。

不过直接暴力转移是 $O(n^2)$ 的，得去优化。

由于它只需要前缀最值或者后缀最值，所以可以直接用树状数组简单维护，维护方法不多赘述，因为太典了。

然后就做完了，复杂度 $O(n \log_2 n)$。

---

## 作者：littlebug (赞：1)

## Solution

首先考虑暴力 dp，设 $f_i$ 为只考虑前 $i$ 段，第 $i$ 段必选的答案，考虑上一个选的段是否与当前段有交，则有转移：

$$
f_i = \max _{j = 1} ^{i - 1}
\begin{cases}
f_j + r_i - r_j & l_i \le r_j \\
f_j + r_i - l_i + 1 & l_i > r_j
\end{cases}
$$

然后发现可以拆成两个前缀后缀最大值，于是 BIT 维护就行了（后缀把顺序倒过来就变成了前缀）。

## Code

```cpp
int n,l[N],r[N],f[N],lsh[N<<1],num;

struct __BIT
{
	int v[N<<1];
	il void upd(int pos,int x){for(int i=pos;i<=num;chmax(v[i],x),i+=i&-i);}
	il int q(int pos){int res=-inf; for(int i=pos;i;chmax(res,v[i]),i-=i&-i); return res;}
} t1,t2;

signed main()
{
	read(n),_::r(l,r,n);
	
	rep(i,1,n) lsh[(i<<1)-1]=l[i],lsh[i<<1]=r[i];
	sort(lsh+1,lsh+(n<<1)+1);
	num=unique(lsh+1,lsh+(n<<1)+1)-lsh-1;
	auto h=[](int x){return lower_bound(lsh+1,lsh+num+1,x)-lsh;};
	
	rep(i,0,num+1) t1.v[i]=-inf;
	
	rep(i,1,n)
	{
		f[i]=max(t1.q(num-h(l[i])+1)+r[i],max(t2.q(h(l[i])-1),0ll)+r[i]-l[i]+1);
		t1.upd(num-h(r[i])+1,f[i]-r[i]),t2.upd(h(r[i]),f[i]);
	}
	
	write(mxele(f+1,f+n+1));
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：toolong114514 (赞：1)

# AT_arc159_d [ARC159D] LIS 2 题解
以前机房某场模拟赛的 T3，~~因为 dp 转移写得太狗屎赛时没调出正解~~。
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/AT_arc159_d)
## 解题思路
定义 $f_i$ 为以第 $i$ 个单调递增段的最右端为结尾的最长上升子序列长度。

容易发现最优解的结尾一定是某个单调递增段的最右端，否则我们可以继续往后面填数，答案一定不优。

接下来考虑转移的方式。

只有右端点比当前段右端点小才能转移。

转移的类型又分为两种：

- 两个区间没有交集，直接加上当前区间长
- 两个区间有交集，加上二者右端点之差。

我们现在可以愉快地写出转移方程了：

$$f_i=\max_{j=0}^{i-1}\{\begin{cases}f_j+r_i-l_i+1 & r_j<l_i\\f_j+r_i-r_j & l_i\le r_j\\0 & \operatorname{otherwise}\end{cases}\}$$

（特别地，我们规定 $f_0=l_0=r_0=0$）

最后答案就是对所有 $f_i$ 取 $\max$。

直接朴素转移是 $O(n^2)$ 的，无法通过 $n\le2\times10^5$ 的数据，考虑线段树优化。

开两颗权值线段树，一颗维护 $f_i$ 的最大值，另一颗维护 $f_i-r_i$ 的最大值，每求出一个 $f_i$ 就以 $r_i$ 为下标插入线段树中，求 $f_i$ 时根据 $r_i$ 和转移方程查询即可。

还有些设最小值之类的细节问题，注意一下就行。

时间复杂度约为 $O(n\log n)$，可以通过本题。

代码很好写。
## 参考代码
```cpp
#include<iostream>
using namespace std;
#define int long long
const int INF=0x7fffffffffffffff;
const int LIM=1e9;
const int N=2e6+10;
struct node{
	int ln,rn;
}a[N];
int f[N];
int n,ans;
struct ccf{
	int lson,rson,maxn;
}tree1[4*N],tree2[4*N];
int root1,root2,tmr1,tmr2;
void push_up1(int pos){
	tree1[pos].maxn=max(tree1[tree1[pos].lson].maxn,tree1[tree1[pos].rson].maxn);
}
void upd1(int &pos,int l,int r,int dot,int x){
	if(!pos) pos=++tmr1;
	if(l==r){
		tree1[pos].maxn=x;
		return;
	}
	int mid=(l+r)/2;
	if(dot<=mid) upd1(tree1[pos].lson,l,mid,dot,x);
	else upd1(tree1[pos].rson,mid+1,r,dot,x);
	push_up1(pos);
}
int ask1(int pos,int l,int r,int lft,int rgt){
	if(lft>rgt||!pos||rgt<l||r<lft) return 0;
	if(lft<=l&&r<=rgt) return tree1[pos].maxn;
	int mid=(l+r)/2;
	return max(ask1(tree1[pos].lson,l,mid,lft,rgt),ask1(tree1[pos].rson,mid+1,r,lft,rgt));
}
void push_up2(int pos){
	tree2[pos].maxn=max(tree2[tree2[pos].lson].maxn,tree2[tree2[pos].rson].maxn);
}
void upd2(int &pos,int l,int r,int dot,int x){
	if(!pos) pos=++tmr2;
	if(l==r){
		tree2[pos].maxn=x;
		return;
	}
	int mid=(l+r)/2;
	if(dot<=mid) upd2(tree2[pos].lson,l,mid,dot,x);
	else upd2(tree2[pos].rson,mid+1,r,dot,x);
	push_up2(pos);
}
int ask2(int pos,int l,int r,int lft,int rgt){
	if(!pos||rgt<l||r<lft) return -INF;
	if(lft<=l&&r<=rgt) return tree2[pos].maxn;
	int mid=(l+r)/2;
	return max(ask2(tree2[pos].lson,l,mid,lft,rgt),ask2(tree2[pos].rson,mid+1,r,lft,rgt));
}
signed main(){
	ios::sync_with_stdio(false);
	tree2[0].maxn=-INF;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].ln>>a[i].rn;
	}
	for(int i=1;i<=n;i++){
		f[i]=max(ask1(root1,1,LIM,1,a[i].ln-1)+a[i].rn-a[i].ln+1,ask2(root2,1,LIM,a[i].ln,a[i].rn-1)+a[i].rn);
		upd1(root1,1,LIM,a[i].rn,f[i]);
		upd2(root2,1,LIM,a[i].rn,f[i]-a[i].rn);
	}
	for(int i=1;i<=n;i++){
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```
[本代码可以通过 AT 的评测。](https://www.luogu.com.cn/record/164866375)

Written by [toolong114514](www.luogu.com/user/477821) on 2024/7/9.

---

## 作者：HHH6666666666 (赞：1)

提供一个避开分类讨论的小结论~~没什么用~~。

令 $f_i$ 表示以 $i$ 结尾的 LIS 长度，则添加线段时对于每个 $i \in [l,r],f_i=\max\limits_{j<i}f_j+1$。

实际上可以强化成 $f_i=\max\limits_{j<l}f_j+i-l+1$。

证明显然：令 $g_i=\max\limits_{j=1}^if_j$，则 $\forall i>0,g_i \le g_{i-1}+1$。则可得 $\forall i \in [l,r], g_i \le g_{l-1}+i-l+1$，$i$ 对 $f_x(x>i,x \in [l,r])$ 的贡献为： 

$$f_i+1 \le g_i+1 \le g_{l-1}+i-l+2\le g_{l-1}+x-l+1$$

得证。

问题变成区间加一次函数和查询区间内单点最值。线段树维护即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;
const int LGN = 50;

int n;
struct Segment {
    int ls, rs;
    int max, maxb;
    Segment() { maxb = -1e9; }
} a[MAXN * LGN];
int idx, root;

#define Max(x, y) x = max(x, y)
#define mid ((L + R) >> 1)
void maxit(int p, int b, int L, int R) {
    if (!p) return;
    a[p].maxb = max(a[p].maxb, b);
    a[p].max = max({a[p].maxb + R, a[a[p].ls].max, a[a[p].rs].max});
    return;
}
void pushdown(int p, int L, int R) {
    if (!a[p].ls) a[p].ls = ++idx;
    if (!a[p].rs) a[p].rs = ++idx;
    maxit(a[p].ls, a[p].maxb, L, mid);
    maxit(a[p].rs, a[p].maxb, mid + 1, R);
    return;
}
void pushup(int p, int L, int R) {
    a[p].max = max({a[p].maxb + R, a[a[p].ls].max, a[a[p].rs].max});
    return;
}
void add(int &p, int l, int r, int b, int L = 1, int R = 1e9) {
    if (!p) p = ++idx;
    if (l <= L && R <= r) { maxit(p, b, L, R); return; }
    pushdown(p, L, R);
    if (l <= mid) add(a[p].ls, l, r, b, L, mid);
    if (mid < r) add(a[p].rs, l, r, b, mid + 1, R);
    pushup(p, L, R);
    return;
}
int query(int p, int l, int r, int L = 1, int R = 1e9) {
    if (!p || l > r) return 0;
    if (l <= L && R <= r) return a[p].max;
    pushdown(p, L, R);
    int res = 0;
    if (l <= mid) Max(res, query(a[p].ls, l, r, L, mid));
    if (mid < r) Max(res, query(a[p].rs, l, r, mid + 1, R));
    return res;
}

signed main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    while (n--) {
        int l, r; cin >> l >> r;
        int t = query(root, 1, l - 1);
        add(root, l, r, t + 1 - l);
    }
    cout << query(root, 1, 1e9) << endl;
    return 0;
}

```

---

## 作者：大眼仔Happy (赞：1)

独立做出此题，但是认为自己没有石粒。

~~所以这肯定就是一个线段树优化 dp 的板题。~~

先考虑朴素 dp，设 $f_i$ 表示选了第 $i$ 段为最后一段的最大长度。枚举上一个选择的 $j$，则有几种情况：

- $r_j<l_i$：说明没有重复，直接就是 $f_{j}+len_i$。

- $l_i\le r_j<r_i$：说明 $j$ 和 $i$ 有重复，贡献为 $f_j+r_i-r_j$。

- $r_j>r_i$：直接超过了，不能贡献。

时间复杂度 $O(n^2)$。

但是上面那个柿子明显的感觉就是可以用权值线段树优化啊？！不就是区间操作吗？我们首先对 $l,r$ 离散化（线段树的下标），然后对于第一种情况，区间求最值 $f_j$，对于第二种情况，区间求最值 $(f_j-r_j)$。得到 $f_i$ 之后又更新两颗线段树即可。这样就做到 $O(n\log n)$ 了。

注意的是，由于第一种情况中也有 $j=0$，所以第一颗线段树只用清零，而第二颗线段树赋 $-\infty$（不过似乎不这么做也可以？），还有线段树别 $ql>qr$。

upd : 第二次推导完全比第一次自己瞎搞清晰很多，更加论证了自己是彩笔的事实了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=4e5+5;
const ll inf=1e18;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,l;ll f[N],ans,arr[N],c[N];
struct node{ll l,r;}d[N],pos[N];
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
struct Segment_Tree
{
	ll t[N<<2];
	void build(int k,int l,int r,ll v)
	{
		t[k]=v;if(l==r)return;
		build(ls,l,mid,v);build(rs,mid+1,r,v);
	}
	void upd(int k,int l,int r,int q,ll v)
	{
		if(l==r)return t[k]=max(t[k],v),void();
		if(q<=mid)upd(ls,l,mid,q,v);
		else upd(rs,mid+1,r,q,v);
		t[k]=max(t[ls],t[rs]);
	}
	ll ask(int k,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr)return t[k];
		ll res=-inf;
		if(ql<=mid)res=max(res,ask(ls,l,mid,ql,qr));
		if(qr>mid)res=max(res,ask(rs,mid+1,r,ql,qr));
		return res;
	}
}T1,T2;
int main(){
	n=read();
	for(int i=1;i<=n;i++)d[i]=(node){read(),read()};
	for(int i=1;i<=n;i++)arr[i]=d[i].l,arr[i+n]=d[i].r;
	memcpy(c,arr,sizeof(c));
	sort(c+1,c+1+2*n);l=unique(c+1,c+1+2*n)-c-1;
	for(int i=1;i<=2*n;i++)arr[i]=lower_bound(c+1,c+1+l,arr[i])-c;
	for(int i=1;i<=n;i++)pos[i]=(node){arr[i],arr[i+n]};
	T2.build(1,1,n*2,-inf);
	for(int i=1;i<=n;i++)
	{
		ll res1=(pos[i].l>1?T1.ask(1,1,n*2,1,pos[i].l-1):0);
		res1+=d[i].r-d[i].l+1;
		ll res2=T2.ask(1,1,n*2,pos[i].l,pos[i].r)+d[i].r;
		f[i]=max(res1,res2);
		T1.upd(1,1,n*2,pos[i].r,f[i]);
		T2.upd(1,1,n*2,pos[i].r,f[i]-d[i].r);
		ans=max(ans,f[i]);
	}
	printf("%lld",ans);
	return 0;
}
/*
首先对 d[j].r<d[i].l 这一部分找出最大的 f[j]，然后加上 i 这一段 
对于 j 与 i 的相交的，答案就是最大的 f[j]-d[j].r+d[i].r
对 d 离散化 --> pos，然后数据结构记录 r
*/
/*
5
1 3
2 4
3 5
5 5
6 7
*/
```


---

## 作者：junee (赞：0)

# AT_arc159_d [ARC159D] LIS 2 题解

## 前置知识

线段树，动态规划。

## 题目分析

首先思考我们是肯定不可能直接最后一起跑 LIS 这是显然的。

思考一个过程我取一段 $[x,y],(l_i \le x \le y \le r_i)$，那么我取 $[x,r_i]$ 答案是不劣的，这是显然的。

所以我们每次操作后的 LIS 一定是以某一个 $r$ 为结尾的。

那么我们不妨设 $f_i$ 表示以 $r_i$ 为结尾的 LIS。考虑如何转移：

假设我们从 $f_j$ 转移，此时会有两种情况：

- $[l_i,r_i]$ 与 $[l_j,r_j] $ 无交，这是好做的。

$$f_i=f_j+r_i-l_i+1$$

- $[l_i,r_i]$ 与 $[l_j,r_j]$ 有交。

$$f_i=f_j+r_i-l_i+1-(r_j-l_i+1)$$

化简一下，得到：

$$f_i=f_j-r_j+r_i$$

这样你就得到一个 $O(n^2)$ 可以直接转移的式子。

考虑如何优化，无交集本质上是要找到最大的一个满足要求的 $f_j$ ，有交集本质是找到最大的一个满足要求的 $f_j-r_j$。

所以你的数据结构需要支持单点修改，区间查询最大值，写一个你喜欢的数据结构即可。

时间复杂度为 $O(n\log n)$。

## Code

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
#include<vector>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
const int N=2e5+10,inf=1e9;
int n;
int ans=0,f[N];
struct opt{
	int l,r,L,R;
}op[N];
vector<int>nums;
int find(int x){
	return lower_bound(nums.begin(),nums.end(),x)-nums.begin()+1;
}
struct DS{
	struct node{
		int l,r;
		int mx;
	}tr[N*2*4];
	void pushup(int u){
		tr[u].mx=max(tr[u<<1].mx,tr[u<<1|1].mx);
	}
	void build(int u,int l,int r){
		tr[u]={l,r,-inf};
		if(l==r)return;
		int mid=(l+r)>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
	void modify(int u,int pos,int k){
		if(tr[u].l==tr[u].r){
			tr[u].mx=max(tr[u].mx,k);
			return;
		}
		int mid=(tr[u].l+tr[u].r)>>1;
		if(pos<=mid)modify(u<<1,pos,k);
		else modify(u<<1|1,pos,k);
		pushup(u);
	}
	int query(int u,int l,int r){
		if(tr[u].l>=l&&tr[u].r<=r){
			return tr[u].mx;
		}
		int mid=(tr[u].l+tr[u].r)>>1,res=-inf;
		if(l<=mid)res=query(u<<1,l,r);
		if(r>mid)res=max(res,query(u<<1|1,l,r));
		return res;
	}
}seg1,seg2;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		int l,r;cin>>l>>r;
		op[i]={l,r,0,0};
		nums.push_back(l);
		nums.push_back(r);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(int i=1;i<=n;i++){
		op[i].L=find(op[i].l);
		op[i].R=find(op[i].r);
	}
	seg1.build(1,1,nums.size()+1);
	seg2.build(1,1,nums.size()+1);
	for(int i=1;i<=n;i++){
		int l=op[i].l,r=op[i].r,L=op[i].L,R=op[i].R;
		f[i]=max(r-l+1,max(seg1.query(1,1,L-1)+r-l+1,seg2.query(1,L+1,R-1)+r));
		seg1.modify(1,R,f[i]);
		seg2.modify(1,R,f[i]-r);
	}
	for(int i=1;i<=n;i++)ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：RAND_MAX (赞：0)

不难发现若是选到了一段 $l,r$ 的结尾，将 $l$ 到 $r$ 全选一定不劣。于是启发我们进行 DP。

我们设 $f_i$ 为必选第 $i$ 段结尾的最长上升子序列长度，最终答案即为 $\max\limits_{i=1}^nf_i$。思考如何转移，我们考虑将第 $i$ 段拼在以第 $j$ 段结尾的最长上升子序列之后的答案。首先我们有 $r_i\ge r_j$，接下来分类讨论。若 $l_i>r_j$，那么说明拼在一起的序列仍是单调递增的，那么答案即为 $f_j+r_i-l_i+1$；若 $l_i\le r_j$，那么拼后的最长上升子序列显然是在以第 $j$ 段结尾的最长上升子序列后拼上 $[r_j+1,r_i]$ 之间的数，可以证明没有更优选法，那么这种情况的答案即为 $f_j+r_i-r_j$。所以得到转移方程 $f_i=\max((\max\limits_{r_j<l_i}f_j)+r_i-l_i+1,(\max\limits_{l_i\le r_j\le r_i}(f_j-r_j))+r_i)$。用线段树处理即可。由于 $l,r\le 10^9$，所以还需离散化。

```cpp
#include<bits/stdc++.h>
#define N 200000
#define int long long
#define R read()
#define lb x&(-x)
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
int n,m,l[200010],r[200010],f[200010],id[200010];
int b[200010],pl[200010],pr[200010],sum,ans;
const int inf=1e18;
struct node
{
	int l,r,mx;
}tr[2000010][2];
void upd(int u,int y)
{
	tr[u][y].mx=max(tr[u<<1][y].mx,tr[u<<1|1][y].mx);
}
void build(int u,int l,int r,int y)
{
	tr[u][y]={l,r,-inf};
	if(l==r) return;
	int mid=l+r>>1;
	build(u<<1,l,mid,y);
	build(u<<1|1,mid+1,r,y);
	upd(u,y);
}
void add(int u,int q,int x,int y)
{
	if(tr[u][y].l==tr[u][y].r)
	{
		tr[u][y].mx=max(x,tr[u][y].mx);
		return;
	}
	int mid=tr[u][y].l+tr[u][y].r>>1;
	if(q<=mid) add(u<<1,q,x,y);
	else add(u<<1|1,q,x,y);
	upd(u,y);
}
int que(int u,int l,int r,int y)
{
	if(l>r) return -inf;
	if(l<=tr[u][y].l&&tr[u][y].r<=r) return tr[u][y].mx;
	int mid=tr[u][y].l+tr[u][y].r>>1,mm=-inf;
	if(l<=mid) mm=max(mm,que(u<<1,l,r,y));
	if(r>mid) mm=max(mm,que(u<<1|1,l,r,y));
	return mm;
}
signed main()
{
	n=R;
	for(int i=1;i<=n;i++) b[++m]=l[i]=R,r[i]=b[++m]=R;
	sort(b+1,b+m+1);
	int len=unique(b+1,b+m+1)-b-1;
	for(int i=1;i<=n;i++) pl[i]=lower_bound(b+1,b+len+1,l[i])-b;
	for(int i=1;i<=n;i++) pr[i]=lower_bound(b+1,b+len+1,r[i])-b;
	build(1,0,m,0),build(1,0,m,1),add(1,0,0,0),add(1,0,0,1);
	for(int i=1;i<=n;i++)
	{
		f[i]=max(que(1,0,pl[i]-1,0)+r[i]-l[i]+1,que(1,pl[i],pr[i],1)+r[i]+1);
		add(1,pr[i],f[i],0),add(1,pr[i],f[i]-r[i]-1,1);
		ans=max(ans,f[i]);
	}
	write(ans,'\n');
 	return 0;
}

```

---

## 作者：Xy_top (赞：0)

不一样的垃圾题目的垃圾做法。

回想 $O(n\log n)$ 求 LIS 的方法：

设 $f_i$ 为拼成长度为 $i$ 的最长上升子序列第 $i$ 个位置最小是多少，转移很简单不再赘述。

搬到这一道题目来，首先区间很长，还要修改一长串，可以用动态开点线段树。

二分的时候是单点查询，但是插入的地方出问题了，一插入就是一长串连续的。

此时需要用到一个技巧，做差分，这样就相当于插入 ``x 1 1 1 1 1 1 1 1 1 ...``。

于是只需要支持查前缀和以及区间覆盖，有没有更好的数据结构我不知道，但是线段树可以。

直接这么做的话瓶颈在二分的时候还要查询，两个 log 可能过不去，但由于查的是前缀和，可以使用线段树上二分。

至此，这道题做完了。

---

