# The Fair Nut's getting crazy

## 题目描述

Fair Nut 发现了一个长度为 $n$ 的整数数组 $a$。我们称子数组 $l \ldots r$ 为数组中下标从 $l$ 到 $r$ 的一段连续元素，即 $a_l, a_{l+1}, a_{l+2}, \ldots, a_{r-1}, a_{r}$。

没人知道原因，但他称一对子段为“好对子”当且仅当满足以下条件：

1. 这两个子段不能嵌套。也就是说，每个子段都必须包含一个不属于另一个子段的元素（下标）。
2. 两个子段有交集，并且交集中的每个元素在每个子段中只出现一次。

例如，$a=[1, 2, 3, 5, 5]$。对子 $(1 \ldots 3; 2 \ldots 5)$ 和 $(1 \ldots 2; 2 \ldots 3)$ 是好对子，但 $(1 \ldots 3; 2 \ldots 3)$ 和 $(3 \ldots 4; 4 \ldots 5)$ 不是（子段 $1 \ldots 3$ 包含了 $2 \ldots 3$，整数 $5$ 同时属于两个子段，但在子段 $4 \ldots 5$ 中出现了两次）。

请你帮助 Fair Nut 计算好对子段的数量！由于答案可能很大，请输出对 $10^9+7$ 取模后的结果。

## 说明/提示

在第一个样例中，只有一对好子段：$(1 \ldots 2, 2 \ldots 3)$。

在第二个样例中，有四对好子段：

- $(1 \ldots 2, 2 \ldots 3)$
- $(2 \ldots 3, 3 \ldots 4)$
- $(2 \ldots 3, 3 \ldots 5)$
- $(3 \ldots 4, 4 \ldots 5)$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 1 2 3
```

### 输出

```
4
```

# 题解

## 作者：Owen_codeisking (赞：5)

~~CF 上这题好像 3500，像极了洛谷的恶意评分~~

首先枚举交集 $[l,r]$，然后计算每个交集的答案。

定义

$\text{pre}_i$ 为数值和 $a_i$ 相同，最靠近 $i$ 且 $<i$ 的位置，若不存在为 $0$。

$\text{suc}_i$ 为数值和 $a_i$ 相同，最靠近 $i$ 且 $>i$ 的位置，若不存在为 $n+1$。

记 

$$f(i,j)=\max(\text{pre}_i,...,\text{pre}_j)+1$$

$$g(i,j)=\min(\text{suc}_i,...,\text{suc}_j)-1$$

则

$$ans=\sum_{i=1}^n\sum_{j=i}^n [i\ge f(i,j)][g(i,j)\ge j](i-f(i,j))\times (g(i,j)-j)$$

考虑怎么算这个答案。

我们先枚举 $i$。这个 $f(i,j)$ 不降，$g(i,j)$ 不升，一定有一个最大的 $j$，使得 $[i,i],...,[i,j]$ 计入答案。我们发现对于 $i_1<i_2$，$j_1<j_2$，这样就可以双指针计算 $j$。

现在的问题就是对于每个 $i$，怎么快速计算

$$\sum_{k=i}^j (i-f(i,k))\times (g(i,k)-k)$$

现在把括号拆开

$$=\sum_{k=i}^j g(i,k)-i\times \sum_{k=i}^j k-\sum_{k=i}^j f(i,k)\times g(i,k)+\sum_{k=i}^j f(i,k)\times k$$

这些东西可以在线段树上搞。每次 $i$ 左移时，把所有值取 $\max/\min$ 的操作换成区间赋值。

现在你需要维护几种操作：

1. 对 $a/b$ 序列区间赋值

2. 求 $a/b$ 序列区间和

3. 求 $a/b$ 序列区间 $(a/b)_i\times i$ 和

4. 求 $a_i\times b_i$ 和

时间 $\mathcal{O}(n\log n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=100005;
const int inf=0x3f3f3f3f;
const int mod=1000000007;
int n,a[maxn],mp[maxn],lst[maxn],cnt[maxn],pre[maxn],suc[maxn],fp[maxn],fs[maxn],sta[maxn],top;
ll sum[maxn<<2][4],lazy[maxn<<2][2];
inline ll sum_2(ll x) { return x*(x+1)/2; }
inline ll S(int l,int r) { return sum_2(r)-sum_2(l-1); }
#define ls (rt<<1)
#define rs (rt<<1|1)
inline void pushup(int rt) { for(int i=0;i<4;i++) sum[rt][i]=sum[ls][i]+sum[rs][i]; }
inline void pushlazy(int rt,int l,int r,int z,int op)
{
	sum[rt][2]=sum[rt][op^1]*z;
	sum[rt][op]=(ll)(r-l+1)*z;
	lazy[rt][op]=z;
	if(op==0) sum[rt][3]=z*S(l,r);
}
inline void pushdown(int rt,int l,int r)
{
	int mid=(l+r)>>1;
	if(lazy[rt][0])
	{
		pushlazy(ls,l,mid,lazy[rt][0],0);
		pushlazy(rs,mid+1,r,lazy[rt][0],0);
		lazy[rt][0]=0;
	}
	if(lazy[rt][1])
	{
		pushlazy(ls,l,mid,lazy[rt][1],1);
		pushlazy(rs,mid+1,r,lazy[rt][1],1);
		lazy[rt][1]=0;
	}
}
void update(int rt,int l,int r,int x,int y,int z,int op)
{
	if(x<=l && r<=y) { pushlazy(rt,l,r,z,op); return; }
	pushdown(rt,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) update(ls,l,mid,x,y,z,op);
	if(y>mid) update(rs,mid+1,r,x,y,z,op);
	pushup(rt);
}
ll query(int rt,int l,int r,int x,int y,int z)
{
	if(x>y) return 0;
	if(x<=l && r<=y) return sum[rt][z];
	pushdown(rt,l,r);
	int mid=(l+r)>>1; ll ans=0;
	if(x<=mid) ans+=query(ls,l,mid,x,y,z);
	if(y>mid) ans+=query(rs,mid+1,r,x,y,z);
	return ans;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),mp[i]=a[i];
	sort(mp+1,mp+n+1);
	int tot=unique(mp+1,mp+n+1)-mp-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(mp+1,mp+tot+1,a[i])-mp,pre[i]=lst[a[i]]+1,lst[a[i]]=i;
	for(int i=1;i<=tot;i++) lst[i]=n+1;
	for(int i=n;i;i--) suc[i]=lst[a[i]]-1,lst[a[i]]=i;
	for(int i=n;i;i--)
	{
		while(top && pre[i]>pre[sta[top]]) top--;
		fp[i]=top?sta[top]-1:n,sta[++top]=i;
	}
	top=0;
	for(int i=n;i;i--)
	{
		while(top && suc[i]<suc[sta[top]]) top--;
		fs[i]=top?sta[top]-1:n,sta[++top]=i;
	}
	ll ans=0;
	for(int i=n,j=n;i;i--)
	{
		update(1,1,n,i,fp[i],pre[i],0);
		update(1,1,n,i,fs[i],suc[i],1);
		cnt[a[i]]++;
		while(cnt[a[i]]>1) cnt[a[j]]--,j--;
		(ans+=query(1,1,n,i,j,3)+i*query(1,1,n,i,j,1)-i*S(i,j)-query(1,1,n,i,j,2))%=mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
} 
```

---

## 作者：P2441M (赞：2)

## 题意简述
给出长度为 $n$ 的序列 $a$。你需要从该序列中选出两个非空的子段，这两个子段满足：
- 两个子段非包含关系；
- 两个子段存在交且位于两个子段交中的元素在每个子段中只能出现一次。

求共有多少种不同的子段选择方案。输出总方案数对 $10^9 + 7$ 取模后的结果。

选择子段 $[a, b],[c, d]$ 与选择子段 $[c, d],[a, b]$ 被视为是相同的两种方案。

对于所有数据，$1\leq n\leq 10^5, -10^9\leq a_i\leq 10^9$。

## 题解
设 $a<c\leq b<d$。一个很 naive 的想法就是枚举交集区间 $[c,b]$，预处理每个位置 $i$ 前面/后面第一个与 $a_i$ 值相同的位置 $pre_i/nxt_i$，我们有 $a\geq\max_{i=c}^b\{pre_i\}+1$ 和 $d\leq \min_{i=c}^b\{nxt_i\}-1$，所以此时能选出的子段方案数即为 $((c-1)-mx)(mn-(b+1))$。

扫描线优化一下。我们对 $R$ 做扫描线，然后对每个 $L$ 维护交集区间为 $[L,R]$ 时的子段方案数，然后用线段树维护区间和累计到答案上。我们需要维护
$$
\begin{align*}
&\sum ((L-1)-mx)(mn-(R+1)) \\
=&\sum (L-1)mn-(L-1)(R+1)-mx\times mn+(R+1)mx \\
=&\sum (L-1)mn-(R+1)\sum(L-1)-\sum mx\times mn+(R+1)\sum mx
\end{align*}
$$
所以我们需要在线段树的每个节点上维护 $\sum (L-1)mn,\sum mx,\sum mn,\sum mx\times mn$。

$R\leftarrow R+1$ 后 $mn$ 和 $mx$ 会对应发生变化，对于这类变化有经典的套路：注意到我们需要维护后缀最值，考虑**单调栈**，以 $mx$ 为例，当我们加入一个数 $a_R$ 时，$mx$ 是成段变化的，具体来说，我们维护一个栈内元素**单调递减**的单调栈，设栈顶为 $top$，那么实际上它蕴含了一个后缀最值信息
$$\max_{i=stk_{top-1}+1}^{stk_{top}}=a_{stk_{top}}$$
当 $a_{stk_{top}}\leq a_R$ 时，我们弹出栈顶，同时更新这一段的 $mx\leftarrow a_R$，这样就可以正确地维护好 $mx$ 了，$mn$ 同理。我们只在弹出栈顶时进行 $1$ 次区间覆盖，因此区间覆盖的总次数为 $O(n)$。

线段树和单调栈相配合就做完了。时间复杂度 $O(n\log{n})$。

## 代码
代码不是很好写，所以放一下主要部分。
```cpp
struct SegTree {
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
	struct Node { ll sum[4], tg[2]; } nodes[(N << 2) + 5];
	void push_up(int p) {
		for (int i = 0; i < 4; ++i)
			nodes[p].sum[i] = (nodes[ls(p)].sum[i] + nodes[rs(p)].sum[i]) % MOD;
	}
	void make_change(int p, int l, int r, ll v, int tp) {
		nodes[p].sum[2] = nodes[p].sum[tp ^ 1] * v % MOD;
		nodes[p].sum[tp] = v * (r - l + 1) % MOD;
		if (!tp) nodes[p].sum[3] = v * (1ll * (l + r) * (r - l + 1) / 2 % MOD) % MOD;
		nodes[p].tg[tp] = v;
	}
	void push_down(int p, int l, int r) {
		int mid = (l + r) >> 1;
		for (int i = 0; i <= 1; ++i) {
			if (!nodes[p].tg[i]) continue;
			make_change(ls(p), l, mid, nodes[p].tg[i], i),
			make_change(rs(p), mid + 1, r, nodes[p].tg[i], i);
			nodes[p].tg[i] = 0;
		}
	}
	ll query(int p, int l, int r, int x, int y, int tp) {
		if (x <= l && y >= r) return nodes[p].sum[tp];
		push_down(p, l, r);
		int mid = (l + r) >> 1;
		ll res = 0;
		if (x <= mid) res = query(ls(p), l, mid, x, y, tp);
		if (y > mid) res = (res + query(rs(p), mid + 1, r, x, y, tp)) % MOD;
		return res;
	}
	void change(int p, int l, int r, int x, int y, ll v, int tp) {
		if (x <= l && y >= r) { make_change(p, l, r, v, tp); return; }
		push_down(p, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid) change(ls(p), l, mid, x, y, v, tp);
		if (y > mid) change(rs(p), mid + 1, r, x, y, v, tp);
		push_up(p);
	}
#undef ls
#undef rs
} sgt;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i], da[++sz] = a[i];
    sort(da + 1, da + sz + 1); sz = unique(da + 1, da + sz + 1) - (da + 1);
    for (int i = 1; i <= n; ++i) {
    	a[i] = lower_bound(da + 1, da + sz + 1, a[i]) - da;
    	pre[i] = pos[a[i]] + 1; pos[a[i]] = i;
	}
	for (int i = 1; i <= sz; ++i) pos[i] = n + 1;
	for (int i = n; i; --i) nxt[i] = pos[a[i]] - 1, pos[a[i]] = i;
	for (int i = n; i; --i) {
        while (top && pre[stk[top]] < pre[i]) --top; 
        fp[i] = top ? stk[top] : n + 1; stk[++top] = i; 
    }
    top = 0; 
    for (int i = n; i; --i) {
        while (top && nxt[stk[top]] > nxt[i]) --top; 
        fn[i] = top ? stk[top] : n + 1; stk[++top] = i; 
    }
    for (int l = n, r = n; l; --l) {
    	if (l < fp[l]) sgt.change(1, 1, n, l, fp[l] - 1, pre[l], 0);
    	if (l < fn[l]) sgt.change(1, 1, n, l, fn[l] - 1, nxt[l], 1); 
    	++cnt[a[l]];
    	while (cnt[a[l]] > 1) --cnt[a[r--]];
    	ans = (ans + sgt.query(1, 1, n, l, r, 1) * l % MOD) % MOD; 
    	ans = (ans + sgt.query(1, 1, n, l, r, 3)) % MOD; 
        ans = (ans - sgt.query(1, 1, n, l, r, 2)) % MOD; 
        ans = (ans - 1ll * l * (1ll * (l + r) * (r - l + 1) / 2 % MOD)) % MOD; 
	}
	cout << (ans + MOD) % MOD;
    return 0;
}
```

---

## 作者：SegTree (赞：2)

思维难度很简单的一个题，就是有点难写。

首先刻画一下条件：

+ $l_1<l_2\le r_1<r_2$
+ $\min_{j\in [l_2,r_1]}nxt_j>r_2$
+ $\max_{j\in [l_2,r_1]}pre_j<l_1$

于是枚举 $l_2,r_1$ 就可以做到 $O(n^2)$。不难想到枚举 $r_1$ 扫一遍，记 $a_i=\max_{j\in [i,r_1]}nxt_j,b_i=\min_{j\in [i,r_1]}pre_j$，则答案为 $(i-1-a_i)(b_i-r_1-1)=(i-1)b_i-(i-1)(r_1-1)-a_ib_i+a_i(r_1-1)$。

只需要做 $a$ 的 chkmax 和 $b$ 的 chkmin，且都有单调性可以线段树上二分找出操作的左端点变成区间赋值，并在线段树上维护 $\sum (i-1)b_i,a_ib_i,a_i,b_i$ 即可。时间复杂度单 $\log$。

[代码](https://codeforces.com/contest/1083/submission/295830838)。

---

## 作者：cwfxlh (赞：1)

# [CF1083D](https://www.luogu.com.cn/problem/CF1083D)     
先对序列里面的数离散化。记 $nxt_i$ 为下一个与 $a_i$ 相等的位置，如果没有就是 $n+1$，$lst_i$ 为上一个与 $a_i$ 相等的位置，如果没有就是 $0$。一个区间 $[l,r]$ 中每个数只出现一次等价于 $\max_{i\in[l,r]}lst_i<l\le r<\min_{i\in[l,r]}nxt_i$。        

枚举两区间交，令当前的交为 $[l,r]$，且 $[l,r]$ 中每个元素只出现一次，则交为 $[l,r]$ 的合法区间对数为 $(l-\max_{i\in[l,r]}lst_i-1)(\min_{i\in[l,r]}nxt_i-r-1)$。这可以通过计算选择两个区间左右端点的方案来得到。这个式子可以化为：    

$$\min nxt\times(l-1)+\max lst\times(r+1)-\min nxt\times\max lst-(l-1)(r+1)$$      

对左端点从大到小扫描线，则 $\min nxt$ 和 $\max lst$ 是单调的，每次进行一次前缀推平。固定 $l$ 求和的时候，$\min nxt\times(l-1)$ 和 $(l-1)(r+1)$ 是好求的，ST 表二分可以求出最靠右的合法区间端点，然后求和 $\min nxt$ 即可。$\max lst$ 可以通过对右端点从小到大扫描线求和。$\min nxt\times\max lst$ 可以在任意一次扫描线中，维护两个值的推平过程，使用线段树即可维护两个序列乘积的值。复杂度 $O(n\log n)$。     

代码：     

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int n,a[200003],ans,lsh[200003],totll,lst[200003],nxt[200003],apr[200003],lft,rgt,mid;
map<int,int>mp;
int stk[200003][3],tots;
int STmin[23][200003],STmax[23][200003],fsp[200003],lg[200003];
int QueryMin(int l,int r){if(l>r)return n+1;return min(STmin[lg[r-l+1]][l],STmin[lg[r-l+1]][r-fsp[lg[r-l+1]]+1]);}
int QueryMax(int l,int r){if(l>r)return 0;return max(STmax[lg[r-l+1]][l],STmax[lg[r-l+1]][r-fsp[lg[r-l+1]]+1]);}
struct SegT{
	int st;
	int ed;
	int sumA;
	int sumB;
	int tpAmk;
	int tpBmk;
	int sum;
}T[1000003];
void build(int now,int l,int r){
	T[now].st=l;
	T[now].ed=r;
	T[now].sumA=T[now].sumB=0;
	T[now].tpAmk=T[now].tpBmk=-1;
	T[now].sum=0;
	if(l==r)return;
	build(now*2,l,((l+r)>>1));
	build(now*2+1,((l+r)>>1)+1,r);
	return;
}
void pushup(int now){
	T[now].sumA=(T[now*2].sumA+T[now*2+1].sumA)%MOD;
	T[now].sumB=(T[now*2].sumB+T[now*2+1].sumB)%MOD;
	T[now].sum=(T[now*2].sum+T[now*2+1].sum)%MOD;
	return;
}
void addmkA(int now,int val){
	T[now].tpAmk=val;
	T[now].sumA=val*(T[now].ed-T[now].st+1)%MOD;
	T[now].sum=val*T[now].sumB%MOD;
	return;
}
void addmkB(int now,int val){
	T[now].tpBmk=val;
	T[now].sumB=val*(T[now].ed-T[now].st+1)%MOD;
	T[now].sum=val*T[now].sumA%MOD;
	return;
}
void pushdown(int now){
	if(T[now].tpAmk!=-1){
		addmkA(now*2,T[now].tpAmk);
		addmkA(now*2+1,T[now].tpAmk);
		T[now].tpAmk=-1;
	}
	if(T[now].tpBmk!=-1){
		addmkB(now*2,T[now].tpBmk);
		addmkB(now*2+1,T[now].tpBmk);
		T[now].tpBmk=-1;
	}
	return;
}
void modifyA(int now,int l,int r,int val){
	if(T[now].st>=l&&T[now].ed<=r){
		addmkA(now,val);
		return;
	}
	if(T[now].st>r||T[now].ed<l)return;
	pushdown(now);
	modifyA(now*2,l,r,val);
	modifyA(now*2+1,l,r,val);
	pushup(now);
	return;
}
void modifyB(int now,int l,int r,int val){
	if(T[now].st>=l&&T[now].ed<=r){
		addmkB(now,val);
		return;
	}
	if(T[now].st>r||T[now].ed<l)return;
	pushdown(now);
	modifyB(now*2,l,r,val);
	modifyB(now*2+1,l,r,val);
	pushup(now);
	return;
}
int QueryA(int now,int l,int r){
	if(T[now].st>r||T[now].ed<l)return 0;
	if(T[now].st>=l&&T[now].ed<=r)return T[now].sumA;
	pushdown(now);
	return (QueryA(now*2,l,r)+QueryA(now*2+1,l,r))%MOD;
}
int QueryB(int now,int l,int r){
	if(T[now].st>r||T[now].ed<l)return 0;
	if(T[now].st>=l&&T[now].ed<=r)return T[now].sumB;
	pushdown(now);
	return (QueryB(now*2,l,r)+QueryB(now*2+1,l,r))%MOD;
}
int Query(int now,int l,int r){
	if(T[now].st>r||T[now].ed<l)return 0;
	if(T[now].st>=l&&T[now].ed<=r)return T[now].sum;
	pushdown(now);
	return (Query(now*2,l,r)+Query(now*2+1,l,r))%MOD;
}
int getsum(int l,int r){return ((r-l+1)*(l+r)/2)%MOD;}
signed main(){
	ios::sync_with_stdio(false);
	for(int i=0;i<=30;i++)fsp[i]=(1<<i);
	for(int i=2;i<=200000;i++)lg[i]=lg[i>>1]+1;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(mp[a[i]]==0){
			lsh[++totll]=a[i];
			mp[a[i]]=totll;
		}
	}
	sort(lsh+1,lsh+totll+1);
	for(int i=1;i<=totll;i++)mp[lsh[i]]=i;
	for(int i=1;i<=n;i++)a[i]=mp[a[i]];
	for(int i=1;i<=n;i++)apr[i]=0;
	for(int i=1;i<=n;i++){
		lst[i]=apr[a[i]];
		apr[a[i]]=i;
	}
	for(int i=1;i<=n;i++)apr[i]=0;
	for(int i=n;i;i--){
		nxt[i]=apr[a[i]];
		if(nxt[i]==0)nxt[i]=n+1;
		apr[a[i]]=i;
	}
	for(int i=1;i<=n;i++)STmin[0][i]=nxt[i],STmax[0][i]=lst[i];
	for(int i=1;fsp[i]<=n;i++){
		for(int j=1;j+fsp[i]-1<=n;j++)STmin[i][j]=min(STmin[i-1][j],STmin[i-1][j+fsp[i-1]]),STmax[i][j]=max(STmax[i-1][j],STmax[i-1][j+fsp[i-1]]);
	}
	build(1,1,n);
	for(int i=n,j=n;i;i--){
		while(QueryMin(i,j)<=j)j--;
		ans=(ans-(i-1)*getsum(i+1,j+1))%MOD;
		lft=i;
		rgt=j;
		while(lft<rgt){
			mid=((lft+rgt)>>1)+1;
			if(QueryMin(i,mid)==nxt[i])lft=mid;
			else rgt=mid-1;
		}
		modifyA(1,i,lft,nxt[i]);
		ans=(ans+(i-1)*QueryA(1,i,j))%MOD;
	}
	
	build(1,1,n);
	for(int i=1,j=1;i<=n;i++){
		while(QueryMax(j,i)>=j)j++;
		lft=j;
		rgt=i;
		while(lft<rgt){
			mid=((lft+rgt)>>1);
			if(QueryMax(mid,i)==lst[i])rgt=mid;
			else lft=mid+1;
		}
		modifyA(1,lft,i,lst[i]);
		ans=(ans+(i+1)*QueryA(1,j,i))%MOD;
	}
	build(1,1,n);
	for(int i=n,j=n;i;i--){
		while(QueryMin(i,j)<=j)j--;
		lft=i;
		rgt=j;
		while(lft<rgt){
			mid=((lft+rgt)>>1)+1;
			if(QueryMin(i,mid)==nxt[i])lft=mid;
			else rgt=mid-1;
		}
		modifyA(1,i,lft,nxt[i]);
		lft=i;
		rgt=j;
		while(lft<rgt){
			mid=((lft+rgt)>>1)+1;
			if(QueryMax(i,mid)==lst[i])lft=mid;
			else rgt=mid-1;
		}
		modifyB(1,i,lft,lst[i]);
		ans=(ans-Query(1,i,j))%MOD;
	}
	ans%=MOD;
	ans+=MOD;
	ans%=MOD;
	cout<<ans;
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：1)

枚举两个子段相交的部分，然后尝试统计答案。设 $pre_i,nxt_i$ 代表 $a_i$ 上一次和下一次出现的位置，则答案为：

$$
\sum_{l=1}^{n}\sum_{r=l}^{n}\max\{0,l-\operatorname{maxpre}(l,r)-1\}\times \max\{0,\operatorname{minnxt}(l,r)-r-1\}
$$

枚举 $l$，$\operatorname{maxpre}(l,r)$ 单调不降，$\operatorname{minnxt}(l,r)$ 单调不升，于是双指针扫 $r$ 即可。记 $f(l,r)=\operatorname{maxpre}(l,r)+1$，$g(l,r)=\operatorname{minnxt}(l,r)-1$。一个 $l$ 可以找到最大的 $r$ 使得 $[l,l],[l,l+1],\cdots,[l,r]$ 被计入答案，现在的问题是计算：

$$
\begin{aligned}
{} & \sum_{i=l}^r (l-f(l,i)) \times(g(l,i)-i)\\
= & \sum_{i=l}^r l\times g(l,i)+i\times f(l,i)-f(l,i)g(l,i)-l\times i
\end{aligned}
$$

线段树维护当前左端点下 $f,g$ 以及相关信息，倒序枚举 $l$，这样变成了加入信息。由于 $f,g$ 是存在单调性的，每次实际被修改的实际上是连续的一段，所以没必要直接上 Beats。以 $f$ 为例，找到 $pre_i>pre_l,i>l$ 的最小 $i$，$[l,i)$ 染成 $pre_l$，单调栈找出这个位置即可。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

int n; 
int a[100005], mptot, pre[100005], nxt[100005], pos[100005]; 
unordered_map<int, int> mp; 
int cnt[100005]; 
int S(int l, int r) { return 1ll * (l + r) * (r - l + 1) / 2 % P; }

int T[400005][4], tag[400005][2]; 
inline void pushup(int o) {
    for (int i = 0; i < 4; ++i) 
        T[o][i] = (T[o << 1][i] + T[o << 1 | 1][i]) % P; 
}
inline void maketag(int o, int l, int r, int k, int type) {
    T[o][2] = 1ll * T[o][type ^ 1] * k % P; 
    T[o][type] = 1ll * k * (r - l + 1) % P; 
    if (type == 0) T[o][3] = 1ll * k * S(l, r) % P; 
    tag[o][type] = k; 
}
inline void pushdown(int o, int l, int r) {
    int mid = l + r >> 1; 
    for (int i = 0; i < 2; ++i) if (tag[o][i]) 
        maketag(o << 1, l, mid, tag[o][i], i), 
        maketag(o << 1 | 1, mid + 1, r, tag[o][i], i), 
        tag[o][i] = 0; 
}
void update(int o, int l, int r, int x, int y, int k, int type) {
    if (x <= l && r <= y) return maketag(o, l, r, k, type); 
    pushdown(o, l, r); int mid = l + r >> 1; 
    if (x <= mid) update(o << 1, l, mid, x, y, k, type); 
    if (mid < y) update(o << 1 | 1, mid + 1, r, x, y, k, type); 
    pushup(o); 
}
int query(int o, int l, int r, int x, int y, int type) {
    if (x <= l && r <= y) return T[o][type]; 
    pushdown(o, l, r); int mid = l + r >> 1, ans = 0; 
    if (x <= mid) ans = query(o << 1, l, mid, x, y, type); 
    if (mid < y) ans = (ans + query(o << 1 | 1, mid + 1, r, x, y, type)) % P; 
    return ans; 
}

int st[100005], tot; 
int fp[100005], fn[100005]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; 
        if (mp.find(a[i]) == mp.end()) mp[a[i]] = ++mptot; 
        a[i] = mp[a[i]]; 
        pre[i] = pos[a[i]] + 1, pos[a[i]] = i; 
        // cerr << a[i] << " "; 
    }
    // cerr << "\n"; 
    for (int i = 1; i <= mptot; ++i) pos[i] = n + 1; 
    for (int i = n; i >= 1; --i) nxt[i] = pos[a[i]] - 1, pos[a[i]] = i; 
    for (int i = n; i >= 1; --i) {
        while (tot && pre[st[tot]] < pre[i]) --tot; 
        fp[i] = tot ? st[tot] : n + 1; st[++tot] = i; 
    }
    tot = 0; 
    for (int i = n; i >= 1; --i) {
        while (tot && nxt[st[tot]] > nxt[i]) --tot; 
        fn[i] = tot ? st[tot] : n + 1; st[++tot] = i; 
    }
    int ans = 0; 
    for (int l = n, r = n; l >= 1; --l) {
        // cout << l << " " << fp[l] - 1 << " " << pre[l] << " UPD PRE\n"; 
        // cout << l << " " << fn[l] - 1 << " " << nxt[l] << " UPD NXT\n"; 
        if (l < fp[l]) update(1, 1, n, l, fp[l] - 1, pre[l], 0); 
        if (l < fn[l]) update(1, 1, n, l, fn[l] - 1, nxt[l], 1); 
        ++cnt[a[l]]; 
        while (cnt[a[l]] > 1) --cnt[a[r--]]; 
        ans = (ans + 1ll * l * query(1, 1, n, l, r, 1)) % P; 
        ans = (ans + query(1, 1, n, l, r, 3)) % P; 
        ans = (ans - query(1, 1, n, l, r, 2)) % P; 
        ans = (ans - 1ll * l * S(l, r)) % P; 
        // printf("%lld\n", 1ll * l * query(1, 1, n, l, r, 1)); 
        // printf("%lld\n", query(1, 1, n, l, r, 3)); 
        // printf("%lld\n", query(1, 1, n, l, r, 2)); 
        // printf("%lld\n", 1ll * l * S(l, r)); 
        cerr << 1ll * l * query(1, 1, n, l, r, 1) + query(1, 1, n, l, r, 3) - query(1, 1, n, l, r, 2) - 1ll * l * S(l, r) << " " << l << " " << r << "\n"; 
    }
    cout << (ans + P) % P << "\n"; 
    return 0; 
}
```

---

## 作者：Cxny (赞：1)

*3500。（心虚）

枚举相交区间计算贡献。记 $anc_i$ 为 $a_i$ 上一次出现的位置（不存在则为 $0$），$nxt_i$ 同理。

令 $pre(i,j)=\max_{k=i}^j\{anc_k\}+1,suf(i,j)=\min_{k=i}^j\{nxt_k\}-1$，则答案即为
$$
\sum_{i=1}^n\sum_{j=i}^n[pre(i,j)<i][j<suf(i,j)](i-pre(i,j))(suf(i,j)-j)
$$
显然，随着 $i$ 递增，**最右侧有效右端点**单调不降。于是可以双指针维护 $i,j$。

删除元素相对麻烦，考虑倒序枚举左端点，动态维护 $pre$ 和 $suf$。

当加入 $i$ 时，$pre(i,j)=max\{pre(i+1,j),anc_i\},suf(i,j)=\min\{suf(i+1,j),nxt_i\}$。

注意到 $pre$ 和 $suf$ 具有单调性，可以二分或单调栈求出最右侧的 $pre(i,j)$ 使得 $pre(i,j)=anc_i$，然后区间赋值。$suf$ 同理。

接下来考虑答案。固定左端点 $i$ ，记最大有效右端点为 $j$，展开。
$$
\sum_{j=i}^r(i-pre(i,j))(suf(i,j)-j)=i\sum_{j=i}^rsuf(i,j)-i\sum_{j=i}^rj+\sum_{j=i}^rjpre(i,j)-\sum_{j=i}^rpre(i,j)suf(i,j)
$$
线段树维护 $\sum pre,\sum suf,\sum pre\cdot suf,\sum i\cdot pre$，区间推平即可。

难度集中在代码难度。

[代码](https://codeforces.com/contest/1083/submission/185139911)太丑了，就不贴了。

---

## 作者：I_am_Accepted (赞：1)

\*3500？\*1500！

离散化，求出前驱（$pre$，没有则为 $0$）后继（$suc$，没有则为 $n+1$），枚举中间交的区间。

对于每个左端点 $l$，我们可以轻松求出最大的 $r$ 使得 $[l,r]$ 区间内每个数最多出现一次。

倒序枚举 $l$，设 $r$ 上限为 $rlim$，则贡献为
$$
\sum_{r=l}^{rlim}(l-1-\max(pre_l,\dots,pre_r))(\min(suc_l,\dots,suc_r)-r-1)
$$
由于倒序枚举，尝试维护
$$
p_i=\max(pre_l,\dots,pre_i)
$$
$$
s_i=\min(suc_l,\dots,suc_i)
$$
则原式
$$
\begin{aligned}
=&-\frac{(l-1)(l+rlim+2)(rlim-l+1)}{2}+\sum_{r=l}^{rlim}p_r(r+1)+s_r(l-1)-p_rs_r
\\=&C+\sum_{r=l}^{rlim}p_r(r+1)+(l-1)\sum_{r=l}^{rlim}s_r-\sum_{r=l}^{rlim}p_rs_r
\end{aligned}
$$
$l$ 向左移动后，我们找到 $pre_i>pre_l,i>l$ 的最小 $i$，将 $[l,i)$ 的 $p$ 全赋值为 $pre_l$，$suc$ 同理。

要维护：

* 区间内 $\sum (i+1)p_i$。

* 区间内 $\sum s_i$。

* 区间内 $\sum p_is_i$。

* $p$ 区间赋值。

* $s$ 区间赋值。

线段树即可，虽然标记有点多。

复杂度 $O(n\log n)$，好写的，不压主体 80 多行。

---

## 作者：XZhuRen (赞：0)

真正的简单题，唐 *3500。

考虑一个区间 $[l,r]$ 造成的贡献，则有 $pre\le L<l\le r<R\le nxt$。

则考虑扫描线维护所有的 $pre,nxt$。

直接上线段树 beats，维护两个序列以及对位乘法就秒了，实现细节写一下，以防不给过：

维护：

$$premx,nxtmn,presum,nxtsum,lsum$$

以及 $\sum_{i\in[l,r]} i\cdot nxtmn_i$，$\sum_{i\in [l,r]}premx_i\cdot nxtmn_i$。

答案为：

$$(presm-lsum)\cdot r
	+sum\{l\cdot nxt\}-sum\{pre\cdot nxt\}$$

从最早合法左端点查即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll1;
const ll1 mod=1e9+7;
const int N=1e5+5;
const int M=4e5+5;
int n;
int a[N];
namespace sgt{
	#define ls (o<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	#define len (r-l+1)
	int L[M],R[M];
	int mnpre[M],mxpre[M];
	int mnnxt[M],mxnxt[M];
	ll1 spre[M],snxt[M];
	ll1 sl[M],slnxt[M],spn[M],tgpre[M],tgnxt[M];
	void pushup(int o){
		mnpre[o]=min(mnpre[ls],mnpre[rs]);
		mxpre[o]=max(mxpre[ls],mxpre[rs]);
		mnnxt[o]=min(mnnxt[ls],mnnxt[rs]);
		mxnxt[o]=max(mxnxt[ls],mxnxt[rs]);
		slnxt[o]=slnxt[ls]+slnxt[rs];
		spn[o]=spn[ls]+spn[rs];
		spre[o]=spre[ls]+spre[rs];
		snxt[o]=snxt[ls]+snxt[rs];
	}
	void build(int o,int l,int r){
		sl[o]=1ll*(l+r)*(r-l+1ll)/2ll;
		L[o]=l,R[o]=r;
		if(l==r){
			spre[o]=mnpre[o]=mxpre[o]=1;
			snxt[o]=mnnxt[o]=mxnxt[o]=n;
			slnxt[o]=1ll*l*n;
			spn[o]=n;
			return;
		}
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(o);
	}
	void covpre(int o,ll1 x){
		int l=L[o],r=R[o];
		mnpre[o]=mxpre[o]=tgpre[o]=x;
		spre[o]=x*len;
		spn[o]=x*snxt[o];
	}
	void covnxt(int o,ll1 x){
		int l=L[o],r=R[o];
		mnnxt[o]=mxnxt[o]=tgnxt[o]=x;
		snxt[o]=x*len;
		slnxt[o]=sl[o]*x;
		spn[o]=spre[o]*x;
	}
	void pushdown(int o){
		int l=L[o],r=R[o];
		if(tgpre[o])covpre(ls,tgpre[o]),covpre(rs,tgpre[o]);
		if(tgnxt[o])covnxt(ls,tgnxt[o]),covnxt(rs,tgnxt[o]);
		tgpre[o]=tgnxt[o]=0;
	}
	void chkpre(int o,int lt,int rt,int x){
		if(mnpre[o]>=x)return;
		int l=L[o],r=R[o];
		if(l>=lt&&r<=rt){
			if(mxpre[o]<x){covpre(o,x);return;}
			pushdown(o);
			chkpre(ls,lt,rt,x),chkpre(rs,lt,rt,x);
			pushup(o);
			return;
		}
		pushdown(o);
		if(lt<=mid)chkpre(ls,lt,rt,x);
		if(rt>mid)chkpre(rs,lt,rt,x);
		pushup(o);
	}
	void chknxt(int o,int lt,int rt,int x){
		if(mxnxt[o]<=x)return;
		int l=L[o],r=R[o];
		if(l>=lt&&r<=rt){
			if(mnnxt[o]>x){covnxt(o,x);return;}
			pushdown(o);
			chknxt(ls,lt,rt,x),chknxt(rs,lt,rt,x);
			pushup(o);
			return;
		}
		pushdown(o);
		if(lt<=mid)chknxt(ls,lt,rt,x);
		if(rt>mid)chknxt(rs,lt,rt,x);
		pushup(o);
	}
	ll1 getsum(int o,int lt,int rt){
		int l=L[o],r=R[o];
		//+(sum{pre}-sum{l})*rt
		//+sum{l*nxt}-sum{pre*nxt}
		if(l>=lt&&r<=rt)
			return (spre[o]-sl[o])*rt+slnxt[o]-spn[o];
		ll1 res=0;
		pushdown(o);
		if(lt<=mid)res+=getsum(ls,lt,rt);
		if(rt>mid)res+=getsum(rs,lt,rt);
		return res;
	}
	#undef ls
	#undef rs
	#undef mid
	#undef len
}
int pre[N],nxt[N];
int Lts[N];
void init(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	map<int,int>mps;
	for(int i=1;i<=n;i++){
		pre[i]=mps[a[i]];
		mps[a[i]]=i;
	}
	mps.clear();
	for(int i=n;i>=1;i--){
		nxt[i]=mps[a[i]]?mps[a[i]]:n+1;
		mps[a[i]]=i;
	}
	multiset<int,greater<int> >pres;
	Lts[0]=1;
	for(int i=1;i<=n;i++){
		Lts[i]=Lts[i-1];
		pres.insert(pre[i]);
		while(Lts[i]<=(*pres.begin()))
			pres.erase(pre[Lts[i]++]); 
	}
}
void work(){
	ll1 Ans=0;
	sgt::build(1,1,n);
	for(int r=1;r<=n;r++){
		sgt::chkpre(1,1,r,pre[r]+1);
		sgt::chknxt(1,1,r,nxt[r]-1);
		// cout<<sgt::getsum(1,Lts[r],r)<<" ";
		(Ans+=sgt::getsum(1,Lts[r],r)%mod)%=mod;
	}
	printf("%lld\n",Ans);
}
int main(){
	init();
	work();
	return 0;
}
/*
要求交独立：
则：
假设当前选定区间 [l,r]，首先要求 [l,r] 是独立区间，即 pre<l<=r<nxt
然后要求：计数 pre<L<l<r<R<nxt
首先要求区间合法，则我们记录一个指针
lft=最左端的使得 minpre<lft 的指针。
即   sum{(l-pre)*(nxt-r)}
	=sum{l*nxt}+sum{pre*r}-sum{pre*nxt}-sum{l*r}
	=
	+(sum{pre}-sum{l})*r
	+sum{l*nxt}-sum{pre*nxt}
维护这个对位即可，可以用 sgt 维护
感觉没了
直接对于每个计数即可
相当于叠加一下右边的长度到上面。
维护一下对位乘法
注意全部减去 Lsum*r
*/
```

---

## 作者：qczrz6v4nhp6u (赞：0)

第一道 \*3500 也是第一道独立做的 \*3500。不过显然虚高。

Fun：P8868 做魔怔了，推这题的时候多维护了一个历史和。

### Solution

记 $\text{pre}_i$ 表示 $i$ 之前最后一个与 $a_i$ 相同的数的位置（如果没有则为 $0$），$\text{suc}_i$ 表示 $i$ 之后第一个与 $a_i$ 相同的数的位置（如果没有则为 $n+1$）。

设 $1\le a< b\le c< d\le n,u=\max_{b\le i\le c}\text{pre}_i,v=\min_{b\le i\le c}\text{suc}_i$，则 $[a,c],[b,d]$ 合法当且仅当 $[b,c]$ 内没有重复元素出现且 $u<a$ 且 $d<v$。

对于每一个合法的 $[b,c]$ 统计合法的数对 $(a,d)$ 个数，总和即为答案。不难发现每个 $[b,c]$ 的贡献是 $(b-u-1)(v-c-1)$。

考虑钦定 $c$。显然可以单调栈维护 $u,v$。由于使得 $[b,c]$ 合法的 $b$ 一定是一个区间且左端点单调不降，我们可以双指针维护 $b$ 合法的区间。

于是我们就转化成了这样一个问题：维护两个序列 $A,B$，支持分别对 $A,B$ 区间加，查询区间 $\sum A_iB_i$。

显然嗯造线段树，对于每个节点维护区间长度，$\sum A_i$，$\sum B_i$，$\sum A_iB_i$，标记维护 $A,B$ 加了多少即可。并没有其他题解所说的区间赋值。

[提交记录](https://codeforces.com/contest/1083/submission/232918606)。因为写了一堆封装，常数大的跟 sh 一样，喜提 CF 倒三以及洛谷倒一。

---

