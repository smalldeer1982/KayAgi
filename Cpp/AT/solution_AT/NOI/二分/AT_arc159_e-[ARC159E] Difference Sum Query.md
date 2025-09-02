# [ARC159E] Difference Sum Query

## 题目描述

给定一个正整数 $N$ 和 $M$ 组正整数对 $(a_0, b_0), \ldots, (a_{M-1}, b_{M-1})$（请注意 $a_i, b_i$ 的下标从 $0$ 开始）。

此外，存在如下定义的非负整数序列 $X=(x_1, \ldots, x_N)$。

- $x_i$ 的确定方式如下：
  1. 令 $l=1, r=N, t=0$。
  2. 令 $m=\left\lfloor \dfrac{a_{t \bmod M} \times l + b_{t \bmod M} \times r}{a_{t \bmod M} + b_{t \bmod M}} \right\rfloor$（$\lfloor x \rfloor$ 表示不超过 $x$ 的最大整数）。若 $m=i$，则令 $x_i=t$ 并结束步骤。
  3. 若 $l \leq i < m$，则令 $r=m-1$，否则令 $l=m+1$。$t$ 的值加 $1$，回到步骤 2。

对于 $i=1,2,\ldots,Q$，请计算 $\sum_{j=c_i}^{d_i-1} |x_j - x_{j+1}|$ 的值。
在本题的约束下，可以证明答案不会超过 $10^{18}$。

## 说明/提示

## 限制条件

- $2 \leq N \leq 10^{15}$
- $1 \leq M \leq 100$
- $1 \leq a_i, b_i \leq 1000$
- $\max \left( \dfrac{a_i}{b_i}, \dfrac{b_i}{a_i} \right) \leq 2$
- $1 \leq Q \leq 10^4$
- $1 \leq c_i < d_i \leq N$
- 所有输入均为整数

## 样例解释 1

$X=(1,2,0,1,2)$。例如，$x_1$ 的确定过程如下：

- 令 $l=1, r=5(=N), t=0$。
- 令 $m=3\left(=\left\lfloor \dfrac{1 \times 1 + 1 \times 5}{1+1} \right\rfloor\right)$。
- 因为 $l \leq 1 < m$，所以 $r=2(=m-1)$，$t$ 增加到 $1$。
- 令 $m=1\left(= \left\lfloor \dfrac{1 \times 1 + 1 \times 2}{1+1} \right\rfloor \right)$。$m=1$，所以 $x_1=1(=t)$，过程结束。

对于 $(c_i, d_i)$，例如 $(c_1, d_1)$，答案为 $\sum_{j=c_i}^{d_i-1} |x_j - x_{j+1}| = |x_1-x_2| = 1$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 1
1 1
3
1 2
2 4
3 5```

### 输出

```
1
3
2```

## 样例 #2

### 输入

```
1000000000000000 2
15 9
9 15
3
100 10000
5000 385723875
150 17095708```

### 输出

```
19792
771437738
34191100```

# 题解

## 作者：Alan_Zhao (赞：5)

## 题解

题面写得很抽象，但其实就是在做一个类似于二分的东西。考虑建出一棵二叉搜索树，当我们二分到一个深度为 $t$ 且区间为 $[l,r]$ 的点时，设 $f(l,r,t)$ 表示 $l,r,t$ 通过题面上那个式子算出的 $m$ 的值，我们让 $f(l,f(l,r,t)-1,t+1),f(f(l,r,t)+1,r,t+1)$ 成为 $f(l,r,t)$ 的左右儿子。

这样，$x_i$ 的值就是二叉搜索树上点 $i$ 的深度。并且，由于这棵二叉树的中序遍历是 $1,2,\dots,N$，所以对于任意两个编号相邻的点 $i,i+1$，$i$ 和 $i+1$ 一定有祖先后代关系。于是 $|x_i-x_{i+1}|$ 就是二叉搜索树上点 $i$ 和 $i+1$ 的距离。

所以 $\mathrm{ans}=\sum_{i=c}^{d-1} \operatorname{dist}(i,i+1)$。因为 $\mathrm{ans}+\operatorname{dist}(c,d)$ 就是 $c,c+1,\dots,d$ 这些点构成的虚树的边数乘二（这里的虚树算上那些只有一个儿子的点），而这个虚树只由两部分点构成：

- $c,c+1,\dots,d$；
- $c\leadsto d$ 的路径上所有编号不在 $[c,d]$ 间的点。

于是我们只需要算出 $\operatorname{dist}(c,d)$，以及 $c\leadsto d$ 的路径上编号不在 $[c,d]$ 间的点的个数，即可求出答案。

由于保证了 $\max(a_i/b_i,b_i/a_i)\le 2$，所以每次二分至少会干掉 $\frac{1}{3}$ 的区间长度，所以二叉搜索树的深度是 $O(\log N)$ 的。所以暴力求出需要的信息即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
using ll = long long;
const int M = 105;
ll n; int m, q, a[M], b[M];
ll LCA(ll u, ll v) {
	ll l = 1, r = n; int t = 0;
	for (;; ++t) {
		ll mid = (l * a[t % m] + r * b[t % m]) / (a[t % m] + b[t % m]);
		if (max(u, v) < mid) r = mid - 1;
		else if (min(u, v) > mid) l = mid + 1;
		else return mid;
	}
}
int Dep(ll u) {
	ll l = 1, r = n; int t = 0;
	for (;; ++t) {
		ll mid = (l * a[t % m] + r * b[t % m]) / (a[t % m] + b[t % m]);
		if (u < mid) r = mid - 1;
		else if (u > mid) l = mid + 1;
		else return t;
	}
}
int Get(ll u, int dlca, ll x) {
	int res = 0, t = 0;
	ll l = 1, r = n;
	for (;; ++t) {
		ll mid = (l * a[t % m] + r * b[t % m]) / (a[t % m] + b[t % m]);
		if ((mid > max(u, x) || mid < min(u, x)) && t >= dlca) ++res;
		if (u < mid) r = mid - 1;
		else if (u > mid) l = mid + 1;
		else return res;
	}
}
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> m;
	For(i, 0, m - 1) cin >> a[i] >> b[i];
	cin >> q;
	For(kase, 1, q) {
		ll c, d; cin >> c >> d;
		ll lca = LCA(c, d), dep = Dep(lca);
		ll ans = (d - c + Get(c, dep, d) + Get(d, dep, c)) * 2 - (Dep(c) + Dep(d) - dep * 2);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：namelessgugugu (赞：4)

#### 题意

有 $n$ 个数，以及 $m$ 个数对 $(a_0, b_0), (a_1, b_1), \dots, (a_{m - 1}, b_{m-1})$，保证 $\max\{\frac{a_i}{b_i}, \frac{b_i}{a_i}\} \leq 2$。

对于每个数 $i$，有一个值 $x_i$，其计算方式如下：

 1. 初始时令 $l = 1, r = n, t = 0$；
 2. 定义 $mid = \lfloor \frac{l \cdot a_{t \bmod m} + r \cdot b_{t \bmod m}}{a_{t \bmod m} + b_{t \bmod m}}\rfloor$；
 3. 如果 $mid = i$，则令 $x_i = t$ 并退出；
 4. 如果 $i < mid$，则令 $r \gets mid - 1$，否则令 $l \gets mid + 1$。令 $t \gets t + 1$，并返回第二步。
 
有 $q$ 次询问，每一次给定一个数对 $(l_i, r_i)$，求解 $\sum\limits_{i = l_i}^{r_i - 1} |x_i - x_{i + 1}|$。

$1 \leq n \leq 10^{15}, 1 \leq m \leq 100, 1 \leq a_i, b_i \leq 1000$。

#### 题解

可以发现其实上述那个流程就是在做一个二分，只是每次取的 $mid$ 并不一定是 $l$ 和 $r$ 的中点，而是按照 $a:b$ 的比例分的。注意到无论 $i$ 是什么，只要 $(l, r)$ 不变，那对应的 $mid$ 也不会变，这说明二分的过程对于每个点而言构成了一个线段树（或者说二叉搜索树更好一点）的结构，每一次二分就是在线段树上往下走一步，$x_i$ 就是树上点 $i$ 的深度。

继续观察，发现在一颗这样的线段树上，点 $i$ 和点 $i+1$ 一定会构成祖先关系。因为如果它们的 LCA 是另一个点 $c$ 的话，这个点 $c$ 一定满足 $i < c < i + 1$，显然这样的整数 $c$ 是不存在的。于是可以发现这两个点的深度之差其实就是从点 $i$ 走到点 $i + 1$ 经过的边数。实际询问要求的就是在树上从 $l_i$ 走到 $l_i + 1$，再走到 $l_i + 2$，……，最后走到 $r_i$ 经过的边数。

假装我们一开始是从这棵树的根节点先走到 $l_i$，走到 $r_i$ 后再回到根节点。考虑把所有 $l_i$ 到 $r_i$ 的点和根节点全部拉出来建虚树，可以发现每个在虚树上的边都恰好被经过了两次。这是因为，由于我们从根节点开始走，对于一个在虚树上的边 $(u, v)$，不妨设 $v$ 是 $u$ 的父亲，那么对于点 $u$ 的子树（这颗子树对应一个区间 $[x, y]$），一定会走进去一次，然后在这个子树里不停地走，再走出来一次，如果多次从子树 $u$ 里面出入的话，就会发现 $[x, y]$ 显然不是一个区间。

所以，我们只需要求出这个虚树上有多少个点，然后要减去从根走到 $l_i$ 和从 $r_i$ 走到根的花费，这在一颗线段树上是容易 $O(dep)$ 做的，其中 $dep$ 表示树的深度。注意到保证了 $\max\{\frac{a_i}{b_i}, \frac{b_i}{a_i}\} \leq 2$，所以每次二分区间长度至少会乘上 $\frac{2}{3}$，故深度是 $\log_{1.5} n$ 级别的，最后的复杂度就是 $O(q \log n)$。

#### 代码

```cpp
#include <cstdio>
typedef long long ll;
const int N = 105;
ll n;
int m, q, a[N], b[N];
int getdep(int dep, ll l, ll r, ll p)
{
    ll mid = (l * a[dep % m] + r * b[dep % m]) / (a[dep % m] + b[dep % m]);
    if(mid == p)
        return dep;
    if(p < mid)
        return getdep(dep + 1, l, mid - 1, p);
    return getdep(dep + 1, mid + 1, r, p);
}
ll calc(int dep, ll l, ll r, ll ql, ll qr)
{
    if(l > r || l > qr || r < ql)
        return 0;
    if (l >= ql && r <= qr)
        return (r - l + 1);
    ll mid = (l * a[dep % m] + r * b[dep % m]) / (a[dep % m] + b[dep % m]);
    return 1 + calc(dep + 1, l, mid - 1, ql, qr) + calc(dep + 1, mid + 1, r, ql, qr);
}
int main(void)
{
    scanf("%lld%d", &n, &m);
    for (int i = 0; i < m;++i)
        scanf("%d%d", a + i, b + i);
    scanf("%d", &q);
    for (int i = 1; i <= q;++i)
    {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        ll ans = (calc(0, 1, n, l, r) - 1) * 2 - getdep(0, 1, n, l) - getdep(0, 1, n, r);
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Schi2oid (赞：2)

本题核心在于如何证明一个区间 $[l,r]$ 内的点在二叉搜索树（结点按照中序遍历编号）上构成的斯坦纳树，其包含的所有结点要么编号在区间内，要么位于区间最左端一点到最右端一点的路径上。其他题解并没有给出详细的相关证明。其余内容其他题解已经很详尽了，在此不在提及。

**引理**：二叉搜索树两个结点的 LCA 的编号介于这两个结点的编号之间。

证明：我们可以将这棵树看成一个自叶子向根不断合并的过程，那么这两个结点应该在它们的 LCA 处被合并。那么两个结点的 LCA 应该满足这两个结点的编号一个比其小，一个比其大，或者两个结点呈现祖孙关系，因为它们应该在 LCA 处被合并。证毕。

此时，我们考虑结点 $v<l$，另一侧同理。假设结点 $v$ 位于 $[l,r]$ 某两个点 $x\rightarrow y$ 的路径上，但是不位于 $l\rightarrow r$ 的路径上。由于树可以看作合并的过程，所以 $lca(l,r)$ 一定是 $lca(x,y)$ 的祖先或两个结点相同。因此，在 $l\rightarrow r$ 路径上一定存在一个 $v'$ 与 $v$ 深度相同，且 $v'\le v$。由于 $v'\not = v$，所以根据**引理**，存在 $l,r$ 中一点和 $x,y$ 中一点，它们的 LCA 位于 $[v’,v]$。而 $[v’,v]$ 位于 $[l,r]$ 之外，与**引理**矛盾，证毕。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc159_e)

**题目大意**

> 给定 $n,m$，定义 $x\in[1,n]$ 的深度 $f(x)$ 为：
>
> - 初始 $[l,r]=[1,n]$。
> - 第 $i$ 次操作求出 $l,r$ 按 $a_{i\bmod m} : b_{i\bmod m}$ 的比例的中点 $mid$。
> - 如果 $x=mid$，那么 $x$ 深度为 $i$，否则递归 $[l,mid-1]$ 或 $[mid+1,r]$。
>
> $q$ 次询问 $[l,r]$，求出 $\sum_{i=l}^{r-1}|f(i+1)-f(i)|$。
>
> 数据范围：$n\le 10^{15},m\le 100,q\le 10^{4},2\min(a_i,b_i)\ge\max(a_i,b_i)$。

**思路分析**

注意到每次操作实际上是在树上二分，可以建出类似线段树的结构，由于 $\dfrac{a_i}{b_i}\le 2$，那么每次区间缩小至少 $\dfrac 13$，最大深度为 $\mathcal O(\log_{1.5}n)$。

那么 $i,i+1$ 显然是祖先后代关系。

答案里的边显然是 $l\sim r$ 虚树上的点。并且每条边访问两次，但 $l\to r$ 路径上的访问 $1$ 次。

那么可以转化为 $rt\to l\sim rt\to r$ 的链并大小乘以二，减去 $l,r$ 的深度。

求 $[l,r]$ 链并大小类似线段树直接做即可。

时间复杂度 $\mathcal O(q\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,q,a[105],b[105];
ll dep(ll x,ll l,ll r,ll i) {
	ll mid=(l*a[i%m]+r*b[i%m])/(a[i%m]+b[i%m]);
	if(x<mid) return dep(x,l,mid-1,i+1);
	if(mid<x) return dep(x,mid+1,r,i+1);
	return i;
}
ll cnt(ll ql,ll qr,ll l,ll r,ll i) {
	if(ql<=l&&r<=qr) return r-l+1;
	ll mid=(l*a[i%m]+r*b[i%m])/(a[i%m]+b[i%m]),ans=1;
	if(ql<mid) ans+=cnt(ql,qr,l,mid-1,i+1);
	if(mid<qr) ans+=cnt(ql,qr,mid+1,r,i+1);
	return ans;
}
signed main() {
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<m;++i) scanf("%lld%lld",&a[i],&b[i]);
	scanf("%lld",&q);
	for(ll l,r;q--;) {
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",2*(cnt(l,r,1,n,0)-1)-dep(l,1,n,0)-dep(r,1,n,0));
	}
	return 0;
}
```

---

## 作者：zyn_ (赞：0)

# [ARC159E] Difference Sum Query

## 题目大意

有 $M$ 个二元组 $(a_0,b_0),\dots,(a_{M-1},b_{M-1})$，$\max(\dfrac{a_i}{b_i},\dfrac{b_i}{a_i})\le 2$。

长度为 $N$ 的序列 $\{X_N\}$，按如下方法生成：

1. $l\gets 1$，$r\gets N$，$t\gets 0$。

2. $m\gets\lfloor\dfrac{a_{t\bmod M}\times l+ b_{t\bmod M}\times r}{a_{t \bmod M}+b_{t \bmod M}}\rfloor$，若 $m=i$ 则 $X_i\gets t$，结束。

3. 若 $i\lt m$ 令 $r\gets m-1$，否则 $l\gets m+1$。然后 $t\gets t+1$。

$Q$ 次询问，每次给定 $c_i,d_i$，求 $\sum_{j=c_i}^{d_i-1}|X_j-X_{j+1}|$。

### $X_i$ 究竟是怎么生成的？

考虑将生成的过程写成一个**递归函数**：

```cpp
void find(int t,int l,int r,int i){
	int m=(a[t%M]*l+b[t%M]*r)/(a[t%M]+b[t%M]);
	if(m==i)return;//found
	if(i<m)find(t+1,l,mid-1,i);
	if(i>m)find(t+1,mid+1,r,i);
}
```

有点像**二叉搜索树**的查找？

不妨将这个生成过程画成一棵二叉搜索树，以 $N=15$，$M=1$，$a_0=b_0=1$ 为例：

![bst](https://cdn.luogu.com.cn/upload/image_hosting/hwkumzz4.png)

发现 $X_i$ 即为树上 $i$ 号结点的深度。（**设根结点深度为 $0$**）

又发现 $i$ 和 $i+1$ 必为祖先关系。所以 $|X_i-X_{i+1}|$ 即为从 $i$ 到 $i+1$ 的路径经过的边数。

所以 $\sum_{j=c_i}^{d_i-1}|X_j-X_{j+1}|$ 即为从 $c_i$ 到 $c_i+1$，到 $c_i+2$，……，到 $d_i-1$，到 $d_i$ 所经过的总边数。

### 如何计算这条路径的长度？

观察一下这条路径，以 $(c_i,d_i)=(1,6)$ 为例：

![path](https://cdn.luogu.com.cn/upload/image_hosting/kwowthyc.png)

1. 所有经过的边都在从根结点到 $x$ 的路径上，其中 $c_i\le x\le d_i$。也就是说，所有经过的边都在以根结点和 $c_i$ 到 $d_i$ 号结点组成的虚树上。

2. 在从根到 $\operatorname{LCA}(c_i,d_i)$ 的路径上的边不被经过。

3. 在从根到 $c_i$ 或在从根到 $d_i$ 的路径上，但不符合第二条的边被经过一次。

4. 符合第一条但不符合第二、三条的边被经过两次。

由此，我们可以得到这条路径的长度。设以根结点和 $c_i$ 到 $d_i$ 号结点组成的虚树有 $k$ 个结点；则其有 $k-1$ 条边。定义 $rt$ 为根结点，$\operatorname{dist}(i,j)$ 为 $i$ 到 $j$ 的路径长度。那么路径长度可以表示为

$$
2(k-1)-\operatorname{dist}(i,\operatorname{LCA}(i,j))-\operatorname{dist}(j,\operatorname{LCA}(i,j))-2\operatorname{dist}(rt,\operatorname{LCA}(i,j))
=2(k-1)-\operatorname{dist}(rt,i)-\operatorname{dist}(rt,j)
$$

虚树大小和结点到根的距离，可以递归（类似二叉搜索树或线段树）求出。

$\max(\dfrac{a_i}{b_i},\dfrac{b_i}{a_i})\le 2$ 保证了这棵树的平衡，使树高为 $O(\log n)$ 级别。因此递归的时间复杂度为 $O(\log n)$，总时间复杂度为 $O(q\log n)$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100009
#define ll long long
ll n,l,r,a[N],b[N],x[N],y[N];
int m,q;
int dep(ll f,ll pl,ll pr,ll p){
	x[f]=p;
	ll mid=(pl*a[f]+pr*b[f])/(a[f]+b[f]);
	if(mid==p)return f+1;
	return p<mid?dep(f+1,pl,mid-1,p):dep(f+1,mid+1,pr,p);
}
ll query(ll f,ll pl,ll pr){
	if(l<=pl&&pr<=r)return pr-pl+1;
	ll mid=(pl*a[f]+pr*b[f])/(a[f]+b[f]),res=1;
	if(l<mid)res+=query(f+1,pl,mid-1);
	if(r>mid)res+=query(f+1,mid+1,pr);
	return res;
}
int main(){
	scanf("%lld%d",&n,&m);
	for(int i=0;i<m;++i)scanf("%lld%lld",&a[i],&b[i]);
	for(int i=m;i<=N-9;++i)a[i]=a[i-m],b[i]=b[i-m];
	scanf("%d",&q);
	while(q--)scanf("%lld%lld",&l,&r),printf("%lld\n",(query(0,1,n)<<1)-dep(0,1,n,l)-dep(0,1,n,r));
	return 0;
}
```

---

## 作者：云浅知处 (赞：0)

首先不难发现 $x_i=O(\log N)$，这是因为每次我们会把区间长度缩小至少 $2/3$。

**考虑建树**，第 $i$ 层的区间由 $[l,r]$ 算出 $m$，连向 $[l,m-1],[m+1,r]$。那么 $x_i$ 就是点 $i$ 的深度。

**注意到这棵树的中序遍历就是 $1,2,\cdots,N$。**因此 $i,i+1$ 一定互为祖孙关系，那么要求的其实就是 $\sum_{i=l}^{r-1} \text{dist}(i,i+1)$。发现这就是 $l,l+1,\cdots,r$ 中所有点形成的虚树大小的两倍减去 $\text{dist}(l,r)$。

考虑算哪些点在虚树上。模拟一下从 $l$ 走到 $r$ 的过程，发现会先往右儿子方向走若干步（可能是 $0$ 步），然后跳到祖先，再遍历剩下的点，最后可能会在 $r-1$ 到 $r$ 的时候回到某个祖先处，再走一步右儿子然后一路往左走回到 $r$。于是，虚树上的点数就是 $r-l+1$ 再加上 $l\to\text{LCA},r\to\text{LCA}$ 这两条链上不在区间 $[l,r]$ 内的点。

由于树高只有 $O(\log N)$，两条链上只有 $O(\log N)$ 个点，总的复杂度就是 $O(Q\log N)$。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=1e9+7;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
int randint(int l,int r){return rand()*rand()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int M=1005;
int n,q,m,a[M],b[M];
int get(int l,int r,int t){
	return (l*a[t%m]+r*b[t%m])/(a[t%m]+b[t%m]);
}
vector<int> getNodes(int x){
	vector<int>v;
	int l=1,r=n,t=0,m=get(l,r,t);v.emplace_back(m);
	while(m!=x){
		if(m<x)l=m+1,t++,m=get(l,r,t);
		else r=m-1,t++,m=get(l,r,t);
		v.emplace_back(m);
	}
	return v;
}

int query(int l,int r){
	vector<int>L=getNodes(l),R=getNodes(r);
	int z=get(1,n,0),p=0;
	while(p<L.size()&&p<R.size()&&L[p]==R[p])z=L[p++];
	int ans=r-l+1;
	for(int i=p;i<L.size();i++)ans+=(L[i]<l||L[i]>r);
	for(int i=p;i<R.size();i++)ans+=(R[i]<l||R[i]>r);
	ans--,ans*=2,ans-=(L.size()-p+R.size()-p);
	return ans;
}

signed main(void){

#ifdef YUNQIAN
	freopen("in.in","r",stdin);
#endif

	n=read(),m=read();
	for(int i=0;i<m;i++)a[i]=read(),b[i]=read();
	q=read();while(q--){
		int l=read(),r=read();
		cout<<query(l,r)<<'\n';
	}

	return 0;
}
```

---

