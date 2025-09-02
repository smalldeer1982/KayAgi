# Interval GCD

## 题目描述

给定一个长度为 $N$ 的数列 $a$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1. `C l r d`，表示把 $a_l,a_{l+1},…,a_r$ 都加上 $d$。
2. `Q l r`，表示询问 $a_l,a_{l+1},…,a_r$ 的最大公约数（$\gcd$）。

对于每个询问，输出一个整数表示答案。

## 说明/提示

对于 $100\%$ 的测试数据，$N \le 5\times10^5$，$M \le 10^5$，$1 \le a_i \le 10^{18}$，$|d| \le 10^{18}$，保证数据在计算过程中不会超过 long long 范围。

## 样例 #1

### 输入

```
5 5
1 3 5 7 9
Q 1 5
C 1 5 1
Q 1 5
C 3 3 6
Q 2 4```

### 输出

```
1
2
4```

# 题解

## 作者：mlvx (赞：24)

### 题意

区间加，求区间最大公约数。

### 分析

先考虑本题的单点加形式。

挺简单的，直接在线段树上维护区间最大公约数即可。

那如何把区间加转化成单点加呢？

差分。

线段树每个叶子节点都表示一个差分后的值。

为什么差分之后的最大公约数和原来的是一样的呢？

易知 $\gcd\{a\}=\gcd\{\gcd(a_1,a_2),\gcd(a_2,a_3),\dots,\gcd(a_{n-1},a_{n})\}$。

又由 $\gcd(x,y)=\gcd(x,y-x)$ 得 $\gcd\{a\}=\gcd\{\gcd(a_1,a_2-a_1),\gcd(a_2,a_3-a_2),\dots,\gcd(a_{n-1},a_n-a_{n-1})\}$。

整理一下又得 $\gcd\{a\}=\gcd\{a_1,a_2-a_1,a_2,a_3-a_2,\dots,a_{n-1},a_n-a_{n-1}\}$。

发现 $a_2,a_3,\dots,a_{n-1}$ 都被两边的项给囊括了，所以这些都可以不要。

也就得到了 $\gcd\{a\}=\gcd\{a_1,a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1}\}$。

最后，由于是差分数组的最大公约数，区间公约数还要带上一个 $a_l$，可以线段树上再维护一个和，也可以再搞个树状数组，查询的时候就是 $\gcd\{a_l,\gcd_{i=l+1}^r a_i-a_{i-1}\}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pl (p<<1)
#define pr (p<<1|1)
const int N=5e5+10;
struct Tree{ll sum,gcd;}tr[N<<2];
int n,q,l,r;ll v,a[N];char op;
void push_up(int p){tr[p]={tr[pl].sum+tr[pr].sum,__gcd(tr[pl].gcd,tr[pr].gcd)};}//上放标记
void build(int l,int r,int p){//建树
	if(l==r)return tr[p]={a[l]-a[l-1],a[l]-a[l-1]},void();//将差分存进去
	int mid=l+r>>1;
	build(l,mid,pl),build(mid+1,r,pr),push_up(p);
}void update(int l,int r,int k,ll v,int p){//单点加
	if(l==r)return tr[p].sum+=v,tr[p].gcd+=v,void();
	int mid=l+r>>1;
	if(k<=mid)update(l,mid,k,v,pl);
	else update(mid+1,r,k,v,pr);
	push_up(p);
}ll query_sum(int l,int r,int le,int ri,int p){//区间和
	if(l>=le&r<=ri)return tr[p].sum;
	int mid=l+r>>1;ll ret=0;
	if(le<=mid)ret+=query_sum(l,mid,le,ri,pl);
	if(ri>mid)ret+=query_sum(mid+1,r,le,ri,pr);
	return ret;
}ll query_gcd(int l,int r,int le,int ri,int p){//区间最大公约数
	if(l>=le&r<=ri)return tr[p].gcd;
	int mid=l+r>>1;ll ret=0;
	if(le<=mid)ret=__gcd(ret,query_gcd(l,mid,le,ri,pl));
	if(ri>mid)ret=__gcd(ret,query_gcd(mid+1,r,le,ri,pr));
	return ret;
}int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,n,1);
	while(q--){
		cin>>op>>l>>r;
		if(op=='C')cin>>v,update(1,n,l,v,1),r!=n&&(update(1,n,r+1,-v,1),1);
		else cout<<abs(__gcd(query_gcd(1,n,l+1,r,1),query_sum(1,n,1,l,1)))<<'\n';//记得取绝对值
	}return 0;
}
```

---

## 作者：forever_nope (赞：22)

注意到，我们的线段树在维护 $\gcd$ 的时候，

+ 容易完成单点修改，而区间修改难以完成。

于是，我们考虑将区间修改，替换为单点修改。

那么这就是差分，我们把原数组替换为其差分数组。

然而，我们需要区间 $\gcd$，下面是性质：

+ 序列的 $\gcd$ 等于其差分序列的 $\gcd$ 这一性质。

考虑证明，

### 考虑 $n=2$

此时，序列为，

$$
A_1,A_2
$$

我们根据更相减损术，

$$
\gcd(A_1,A_2)=\gcd(A_1,A_2-A_1)
$$

注意到这个就是差分的形式。

### 考虑 $n=3$

此时，序列为，

$$
A_1,A_2,A_3
$$

我们列出式子，根据 $\gcd$ 的性质，

$$
\begin{aligned}
\gcd(A_1,A_2,A_3)&=\gcd[\gcd(A_1,A_2),\gcd(A_2,A_3)]\\
&=\gcd[\gcd(A_1,A_2-A_1),\gcd(A_2,A_3-A_2)]\\
&=\gcd[\gcd(A_1,A_2),\gcd(A_2-A_1,A_3-A_2)]\\
&=\gcd[\gcd(A_1,A_2-A_1),\gcd(A_2-A_1,A_3-A_2)]\\
&=\gcd(A_1,A_2-A_1,A_3-A_2)
\end{aligned}
$$

注意到这个就是差分的形式。

### 考虑任意 $n$

此时，序列为，

$$
A_1,A_2,\dots,A_n
$$

我们列出，

$$
\begin{aligned}
\gcd(A_1,A_2,\dots,A_n)&=\gcd[\gcd(A_1,A_2),\gcd(A_2,A_3),\dots,\gcd(A_{n-1},A_n)]\\
&=\gcd[\gcd(A_1,A_2-A_1),\dots,\gcd(A_{n-1},A_n-A_{n-1})]\\
&=\gcd(A_1,A_2-A_1,A_3-A_2,\dots,A_n-A_{n-1})
\end{aligned}
$$

这个可以类比上一个得出。

### 具体实现

注意要维护前缀和，因为差分是以某个序列（而不是全局）中第一个元素为基准的。

注意如果 $l=r$ 需要特判。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl "\n"
#define gcd(x, y) __gcd(abs(x), abs(y))

constexpr int N = 5e5 + 10;

#define int ll
using ll = long long;

int n, m, ori[N];

// ----------------------------------------------------------------------------

#define ls(k) ((k) << 1)
#define rs(k) ((k) << 1 | 1)

struct node {
    int l, r;
    int sum, v;
} a[N << 2];

void push_up(int k) {
    a[k].sum = a[ls(k)].sum + a[rs(k)].sum;
    a[k].v = gcd(a[ls(k)].v, a[rs(k)].v);
}

void action(int k, int v) {
    a[k].sum += v, a[k].v += v;
}

void build(int k, int l, int r) {
    a[k].l = l, a[k].r = r;
    if (l == r) return action(k, ori[l] - ori[l - 1]);
    int mid = l + r >> 1;
    build(ls(k), l, mid), build(rs(k), mid + 1, r);
    push_up(k);
}

void add(int k, int x, int v) {
    int l = a[k].l, r = a[k].r;
    if (l == r) return action(k, v);
    int mid = l + r >> 1;
    // [l, mid] [mid + 1, r]
    if (x <= mid) add(ls(k), x, v);
    else add(rs(k), x, v);
    push_up(k);
}

pair<int, int> query(int k, int p, int q) {
    int l = a[k].l, r = a[k].r;
    if (l >= p && r <= q) return make_pair(a[k].sum, a[k].v);
    int mid = l + r >> 1;
    // [l, mid] [mid + 1, r]
    if (q <= mid) return query(ls(k), p, q);
    if (p >= mid + 1) return query(rs(k), p, q);
    auto z = query(ls(k), p, q), y = query(rs(k), p, q);
    return make_pair(z.first + y.first, gcd(z.second, y.second));
}

// ----------------------------------------------------------------------------

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    copy_n(istream_iterator<int>(cin), n, ori + 1);
    build(1, 1, n);
    while (m--) {
        string op;
        int l, r, d;
        cin >> op >> l >> r;
        if (op == "Q") {
            if (l == r) cout << query(1, 1, r).first << endl;
            else {
                int st = query(1, 1, l).first;
                int ed = query(1, l + 1, r).second;
                cout << gcd(st, ed) << endl;
            }
        }
        else {
            cin >> d;
            add(1, l, d);
            if (r != n) add(1, r + 1, -d);
        }
    }
    return 0;
}
```

---

## 作者：zhoumurui (赞：10)

## 题面展示

给定一个长度为 $N$ 的数列 $A$，以及 $M$ 条指令，每条指令可能是以下两种之一：

1. `C l r d`，表示把 $A[l],A[l+1],…,A[r]$ 都加上 $d$。
2. `Q l r`，表示询问 $A[l],A[l+1],…,A[r]$ 的最大公约数(GCD)。

对于每个询问，输出一个整数表示答案。

$N \le 500000$，$M \le 100000$， $1 \le A[i] \le 10^{18}$，$|d| \le 10^{18}$，保证数据在计算过程中不会超过 long long 范围。

## 题目思路

作为一道区间操作题，我们考虑使用线段树，[不会线段树的请移步这里](https://www.luogu.com.cn/problem/solution/P3372)。



用线段树维护 $\gcd_{i=l}^r A[i] $ 是较为方便的，和区间和类似处理即可，问题在于区间加的懒标记难以维护。

考虑逃避维护懒标记的问题。

接下来我们需要证明一个公式，不需要证明过程的可以直接拉下去看结论。

引理1：

$$ \gcd(a,b) = \gcd(a,b-a)$$

证明：设 $\gcd(a,b) = d$，
$\displaystyle \frac {a}{d}=a_1$，
$\displaystyle \frac {b}{d}=b_1$，

那么显然 $\gcd(a_1,b_1) = 1$，

而且 $a = a_1 \times d$，$b = b_1 \times d$，

这意味着 $b-a = (b_1 - a_1) \times d$，

因此 $\gcd(a,b-a) = \gcd(a_1,b_1 - a_1) \times d$，

假设 $\gcd(a_1,b_1 - a_1) = d_1 > 1$，

那么 $d_1 \mid a_1$，$d_1 \mid b_1 - a_1$，

那么 $d_1 \mid b_1$，

所以 $d_1  \mid  \gcd(a_1,b_1)$，

所以 $ d_1 \le \gcd(a_1,b_1) = 1 $，

与 $d_1 > 1$ 矛盾。

因此，$\gcd(a_1,b_1 - a_1) = 1$，

于是，$ \gcd(a,b) = \gcd(a,b-a)=d $。

引理2：

$$ \gcd_{i=l}^r (a[i]) = \gcd(a[l],\gcd_{i=l+1}^r (a[i]-a[i-1])) (l<r)$$

证明：用数学归纳法。

当 $r = l + 1$ 时，由引理1知成立。

假设当 $r = l + k$ （$k$ 为正整数）时原式成立，

即 $ \gcd_{i=l}^{l+k} (a[i]) = \gcd(a[l],\gcd_{i=l+1}^{l+k} (a[i]-a[i-1]))$，

那么当 $r = l + k + 1$ 时：

$ \gcd_{i=l}^{l+k+1} (a[i])$

$= \gcd(a[l],\gcd_{i=l+1}^{l+k+1} (a[i]))$

$= \gcd(a[l],a[l+1],\gcd_{i=l+1}^{l+k+1} (a[i]-a[i-1]))$ （使用归纳假设）

$= \gcd(\gcd(a[l],a[l+1]),\gcd_{i=l+1}^{l+k+1} (a[i]-a[i-1]))$  

$= \gcd(\gcd(a[l],a[l+1]-a[l]),\gcd_{i=l+1}^{l+k+1} (a[i]-a[i-1]))$ （使用引理1）

$= \gcd(a[l],a[l+1]-a[l],\gcd_{i=l+1}^{l+k+1} (a[i]-a[i-1]))$

$= \gcd(a[l],\gcd_{i=l}^{l+k+1} (a[i]-a[i-1]))$

也成立。

由第一数学归纳法，证明了$ \gcd_{i=l}^r (a[i]) = \gcd(a[l],\gcd_{i=l+1}^r (a[i]-a[i-1])) (l<r)$。

这就是我们需要的结论啦。这意味着我们无须维护区间加，只要做差分数组并维护单点加就可以了。

由于公式中还有一个 $a[l]$ 需要处理，考虑再维护一个区间和，这样这题的思路就清楚了。



## 核心代码展示

#### 线段树

```cpp
struct node{
int l,r,gcd,sum;
};
struct segment_tree{
node t[2000005];
void pushup(int rt){
  t[rt].sum=t[rt*2].sum+t[rt*2+1].sum;
  t[rt].gcd=askgcd(t[rt*2].gcd,t[rt*2+1].gcd);
}
void build(int rt,int l,int r){
  t[rt].l=l;
  t[rt].r=r;
  if (l==r){
    t[rt].sum=t[rt].gcd=a[l]-a[l-1];
    return;
  }
  int mid=(l+r)/2;
  build(rt*2,l,mid);
  build(rt*2+1,mid+1,r);
  pushup(rt);
}
void add(int rt,int k,int x){
  if (t[rt].l>k||t[rt].r<k)return;
  if (t[rt].l==k&&t[rt].r==k){
    t[rt].gcd+=x;
    t[rt].sum+=x;
    return;
  }
  add(rt*2,k,x);
  add(rt*2+1,k,x);
  pushup(rt);
}
int sum(int rt,int l,int r){
  if (t[rt].l>r||t[rt].r<l)return 0;
  if (t[rt].l>=l&&t[rt].r<=r){
    return t[rt].sum;
  }
  return sum(rt*2,l,r)+sum(rt*2+1,l,r);
}
int query(int rt,int l,int r){
  if (t[rt].l>r||t[rt].r<l)return 0;
  if (t[rt].l>=l&&t[rt].r<=r){
    return abs(t[rt].gcd);
  }
  return askgcd(query(rt*2,l,r),query(rt*2+1,l,r));
}
}T;
```
#### 主函数
```cpp
  cin>>n>>m;
  for (int i=1;i<=n;i++)cin>>a[i];
  T.build(1,1,n);
  for (int i=1;i<=m;i++){
    cin>>op;
    if (op=='Q'){
      cin>>l>>r;
      cout<<abs(askgcd(T.query(1,l+1,r),T.sum(1,1,l)))<<endl;
    }
    else{
      cin>>l>>r>>d;
      T.add(1,l,d);
      if (r!=n)T.add(1,r+1,-d);
    }
  }
  return 0;
}
```

---

## 作者：Vitamin_B (赞：5)

upd:感谢 @[hhce2012](/user/928986) 指正。
# 思路
先给出关于 $\gcd$ 的几条性质：
- $\gcd(a,b,c)=\gcd(a,\gcd(b,c))$；
- 根据辗转相减法，不难得出 $\gcd(a_1,a_2,a_3,\dots,a_n)=\gcd(a_1,a_2-a_1,a_3-a_2,a_4-a_3,\dots,a_n-a_{n-1})$；
- 根据上述两条结论，不难推出 $\gcd\limits_{i=l}^ra_i=\gcd(a_l,\gcd\limits_{i=l+1}^{r}a_i)$。

于是，我们就可以建立一棵线段树，用于维护 $l\sim r$ 的差的 $\gcd$，即 $\gcd\limits_{i=l}^{r-1}(a_{i+1}-a_i)$。然后至于合并子节点，我们可以这样推出柿子：$tr_x=\gcd\limits_{i=l}^{r-1}(a_{i+1}-a_i)=\gcd[\gcd\limits_{i=l}^{mid-1}(a_{i+1}-a_i),\gcd\limits_{i=mid+1}^{r-1}(a_{i+1}-a_i),a_{mid+1}-a_{mid}]=\gcd(\gcd(tr_L,tr_R),a_{mid+1}-a_{mid})$。至于区间加操作，则可以在线段树里套一个树状数组差分解决（当然你也可以选择套一个线段树，但是我懒）。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, l, r;
ll tr[2000005], tree[2000005], k, a[500005];
char op;
void add (int x, ll y) {
	while (x <= n)
		tree[x] += y, x += x & -x;
	return ;
}
ll find (int x) {
	ll sum = 0;
	while (x)
		sum += tree[x], x ^= x & -x;
	return sum;
}
void build (int x, int l, int r) {
	if (l == r) {
		add (l, a[r] - a[l - 1]);
		return ;
	}
	int mid = l + r >> 1, left = x << 1, right = left | 1;
	build (left, l, mid), build (right, mid + 1, r);
	tr[x] = __gcd (__gcd (tr[left], tr[right]), abs (find (mid + 1) - find (mid)));
	return ;
}
void change (int x, int l, int r, int L, int R) {
	if (l == L && r == R) {
		add (l, k), add (r + 1, -k);
		return ;
	}
	int mid = l + r >> 1, left = x << 1, right = left | 1;
	if (R <= mid)
		change (left, l, mid, L, R);
	else if (L > mid)
		change (right, mid + 1, r, L, R);
	else
		change (left, l, mid, L, mid), change (right, mid + 1, r, mid + 1, R);
	tr[x] = __gcd (__gcd (tr[left], tr[right]), abs (find (mid + 1) - find (mid)));
	return ;
}
ll find (int x, int l, int r, int L, int R) {
	if (l == L && r == R)
		return __gcd (abs (find (l)), tr[x]);
	int mid = l + r >> 1, left = x << 1, right = left | 1;
	if (R <= mid)
		return find (left, l, mid, L, R);
	if (L > mid)
		return find (right, mid + 1, r, L, R);
	return __gcd (__gcd (find (left, l, mid, L, mid), find (right, mid + 1, r, mid + 1, R)), abs (find (mid + 1) - find (mid)));
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i];
	build (1, 1, n);
	while (m --) {
		cin >> op >> l >> r;
		if (op == 'C')
			cin >> k, change (1, 1, n, l, r);
		else
			cout << find (1, 1, n, l, r) << '\n';
	}
	return 0;
}
```

---

## 作者：wjl1100 (赞：2)

## [原题传送门](https://www.luogu.com.cn/problem/P10463)

## 思路

### 前置知识

[差分](https://blog.csdn.net/Cooperia/article/details/118864683)（可以参照这位大佬的博客）

首先我们可以发现这道题如果是一个单点修改，区间查询的题就会非常简单，可以当作一个板子题去做。

所以我们的任务就是把区间修改转换为单点修改，这时我们就会想到差分思想。

我们先来证明一下一个数列的最大公约数也是其差分数列的最大公约数。

已知 $\gcd(a,b)=\gcd(a,-a)$,$\gcd(a_1,a_2,a_3)= \gcd ( \gcd (a_1,a_2), \gcd (a_2,a_3))$，那么 $\gcd(a_1,a_2,a_3)=\gcd(\gcd(a_1,a_2-a_1),\gcd(a_2,a_3-a_2))$，所以 $\gcd(a_1,a_2,a_3)=\gcd(\gcd(a_1,a_2),\gcd(a_2-a_1,a_3-a_2))$，接着展开第一个，与第二个合并，就可得到 $\gcd(a_1,a_2,a_3)=\gcd(a_1,a_2-a_1,a_3-a_2)$，我们还可以将这个结论推广到整个数列，这时我们就可以发现这就是它的差分数组。

所以我们就可以将一次区间修改变成两次单点修改，用线段数维护就行，同时注意这里的公式中第一项为 $a_1$，所以我们还需要用树状数组维护 $a_1$ 的值（也可以用线段树维护）。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x7f7f7f7f
#define mod 1000000007
using namespace std;
const int maxn = 1e6 + 100;
inline int read() {
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x) {
	if(x < 0) x = ~(x - 1) , putchar('-');
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
inline void writeh(int x) {
	write(x);
	putchar('\n');
}
inline void writek(int x) {
	write(x);
	putchar(' ');
}
int n , m , a[maxn] , l , r , d , sum[maxn] , c[maxn];
char opt;
inline int lowbit(int x) {
	return x & (-x);
}
inline void add(int i , int x) {
	for(int j = i; j <= n; j += lowbit(j)) sum[j] += x;
}
inline int query_sum(int i) {
	int ans = 0;
	for(int j = i; j; j -= lowbit(j)) ans += sum[j];
	return ans;
}
struct node {
	int l , r , gcd;
}tr[maxn << 2];
inline int gcd(int a , int b) {
	return b ? gcd(b , a % b) : abs(a);
}
inline void up(int id) {
	tr[id].gcd = gcd(tr[id << 1].gcd , tr[id << 1 | 1].gcd);
}
inline void build(int id , int l , int r) {
	tr[id].l = l;
	tr[id].r = r;
	if(l == r) {
		tr[id].gcd = c[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(id << 1 , l , mid);
	build(id << 1 | 1 , mid + 1 , r);
	up(id);
}
inline void update(int id , int k , int sum) {
	if(tr[id].l > k || tr[id].r < k) return ;
	if(tr[id].l == tr[id].r) {
		tr[id].gcd += sum;
		return ;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(k <= mid) update(id << 1 , k , sum);
	else update(id << 1 | 1 , k , sum);
	up(id);
}
inline int query(int id , int l , int r) {
	if(tr[id].l > r || tr[id].r < l) return 0;
	if(tr[id].l >= l && tr[id].r <= r) return tr[id].gcd;
	return gcd(query(id << 1 , l , r) , query(id << 1 | 1 , l , r));
}
signed main(){
	n = read();
	m = read();
	for(int i = 1; i <= n; i++) a[i] = read() , c[i] = a[i] - a[i - 1] , add(i , c[i]);
	build(1 , 1 , n);
	for(int i = 1; i <= m; i++) {
		cin >> opt;
		if(opt == 'Q') {
			l = read();
			r = read();
			writeh(gcd(query_sum(l) , query(1 , l + 1 , r)));
		}else {
			l = read();
			r = read();
			d = read();
			update(1 , l , d);
			update(1 , r + 1 , -d);
			add(l , d);
			add(r + 1 , -d);
		}
	}
	return !("wjl1100 qwq");
} 
```

---

## 作者：z_yq (赞：2)

# 题意
给出两个操作，分别是：

- `C l r d`，表示把 $A_l,A_{l+1},\ldots,A_{r}$ 都加上 $d$。
- `Q l r`，表示询问 $A_l,A_{l+1},\ldots,A_{r}$ 的最大公约数（GCD）。

每一次询问都需要给出一个答案，求这个值。

# 思路

由于 $\gcd(x_1,x_2-x_1,x_3-x_2,\ldots,x_n-x_{n-1})=\gcd(x_1,x_2,\ldots,x_n)$，所以当区间 $[a,b]$ 加 $k$ 时，相当于 $\gcd(x_2-x_1,x_3-x_2,\ldots,x_n-x_{n-1})$ 不变，则可以使用线段树维护这个值，再和 $x_1$ 取最大公约数即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lson(x) x<<1
#define rson(x) x<<1|1
using namespace std;
const ll N=5e5+9;
struct node
{
	ll lt,rt,gcd,sum;
}tr[4*N];
ll n,m,a[N];
inline void push_up(ll id)
{
	tr[id].sum=tr[lson(id)].sum+tr[rson(id)].sum;
	tr[id].gcd=__gcd(tr[lson(id)].gcd,tr[rson(id)].gcd); 
}
inline void build(ll id,ll l,ll r)
{
	tr[id].lt=l;tr[id].rt=r;
	if(l==r)
		return tr[id].gcd=tr[id].sum=a[l]-a[l-1],void();
	ll mid=l+r>>1;
	build(lson(id),l,mid);
	build(rson(id),mid+1,r);
	push_up(id);
}
inline void change(ll id,ll p,ll d)
{
	if(p==tr[id].lt && tr[id].rt==p)
		return tr[id].gcd=tr[id].sum=tr[id].sum+d,void();
	ll mid=tr[id].lt+tr[id].rt>>1;
	if(p<=mid) change(lson(id),p,d);
	else change(rson(id),p,d);
	push_up(id);
}
inline node query(ll id,ll l,ll r)
{
	if(l>r)
		return {0};
	if(l<=tr[id].lt && tr[id].rt<=r)
		return tr[id];
	ll mid=tr[id].lt+tr[id].rt>>1;
	if(r<=mid) return query(lson(id),l,r);
	else if(l>mid) return query(rson(id),l,r);
	else 
	{
		node tmp,left=query(lson(id),l,r),right=query(rson(id),l,r);
		tmp.sum=left.sum+right.sum;
		tmp.gcd=__gcd(left.gcd,right.gcd); 
		return tmp;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1ll,1ll,n);
	while(m--)
	{
		char x;
		cin>>x;
		if(x=='Q')
		{
			ll l,r;cin>>l>>r;
			cout<<abs(__gcd(query(1,1,l).sum,query(1,l+1,r).gcd))<<endl;
		}
		else
		{
			ll d,l,r;
			cin>>l>>r>>d;
			change(1,l,d);
			if(r<n) change(1,r+1,-d);
		}
	}
	return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：2)

前置知识：[线段树](https://www.luogu.com.cn/article/j1ge1oon)以及 $\gcd$ 的性质相关。

第一眼看到区间加，肯定想到懒标记。但第二眼再看到区间 $\gcd$，发现必须暴力更新叶节点。

怎么解决？转换成单点修改不就解决了么！

这就要用到这么一个性质：

$$\gcd(a_l,a_{l + 1},\cdots,a_{r - 1},a_r) = \gcd(a_l,a_{l + 1} - a_l,\cdots,a_{r - 1} - a_{r - 2},a_r - a_{r - 1})$$

发现右边那一串不就是 $a$ 的差分数组吗！

既然是差分数组，那么在原数组上的区间修改不就相当于差分数组上的单点修改吗！

这样我们就成功地把区间修改转化成了单点修改。

具体实现上需要注意，线段树只能查询 $\gcd(a_{l + 1} - a_l,\cdots,a_{r - 1} - a_{r - 2},a_r - a_{r - 1})$，计这个结果为 $ans$，那么真正的答案应该是 $\gcd(a_l,ans)$。

$a_l$ 在差分数组上对应前缀和，所以在线段树上额外维护一个区间和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l + r) >> 1)
#define lchild (root << 1)
#define rchild ((root << 1) + 1)
using namespace std;
const int N = 5e5 + 9;
int n,m;
int a[N],b[N],c[N];
string op;int l,r,d;
struct node{
	int val;
} t[N << 2];
int GCD(int a,int b){
	return b ? GCD(b,a % b) : abs(a);
}
bool in_range(int l,int r,int L,int R){
	return L <= l && r <= R;
}
bool out_range(int l,int r,int L,int R){
	return l > R || r < L;
}
void push_up(int root){
	t[root].val = GCD(t[lchild].val,t[rchild].val);
}
void build(int root,int l,int r){
	if(l == r){
		t[root].val = b[l];
		return;
	}
	build(lchild,l,mid);
	build(rchild,mid + 1,r);
	push_up(root);
}
void update(int root,int l,int r,int k,int v){
	if(r < k || l > k)
		return;
	if(l == r){
		t[root].val += v;
		return;
	}
	if(k <= mid)
		update(lchild,l,mid,k,v);
	else
		update(rchild,mid + 1,r,k,v);
	push_up(root);
}
int query(int root,int l,int r,int L,int R){
	if(out_range(l,r,L,R))
		return 0;
	if(in_range(l,r,L,R))
		return t[root].val;
	return GCD(query(lchild,l,mid,L,R),query(rchild,mid + 1,r,L,R));
}
int lowbit(int x){
	return x & (-x);
}
int sum(int x){
	int ret = 0;
	for(int i = x;i;i -= lowbit(i))
		ret += c[i];
	return ret;
}
void add(int x,int y){
	for(int i = x;i <= n;i += lowbit(i))
		c[i] += y;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		b[i] = a[i] - a[i - 1];
		add(i,b[i]);
	}
	build(1,1,n);
	while(m--){
		cin >> op >> l >> r;
		if(op == "C"){
			cin >> d;
			update(1,1,n,l,d);
			update(1,1,n,r + 1,-d);
			add(l,d);
			add(r + 1,-d);
		}
		else
			cout << GCD(sum(l),query(1,1,n,l + 1,r)) << '\n';
	}
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：1)

推广的辗转相除法 $\gcd(a_1,a_2,\dots,a_n)=\gcd(a_1,a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1})$。

于是可以尝试将原数组差分，然后修改就是单点修改，非常简单。

这里可以把查询拆成两部分，第一是区间 $[l+1,r]$ 的 $\gcd$，第二是区间 $[1,l]$ 的和来求 $a_l$。

然后线段树可以轻松维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int t[2000010],p[2000010];
int a[500010],b[500010];
void creat(int a[],int l,int r,int root=1){
	if(l==r){
		t[root]=a[l],p[root]=a[l];
		return;
	}
	int mid=l+r>>1;
	creat(a,l,mid,root*2);
	creat(a,mid+1,r,root*2+1);
	t[root]=__gcd(t[root*2],t[root*2+1]);
	p[root]=p[root*2]+p[root*2+1];
}
void update(int u,int v,int root=1,int x=1,int y=n+1){
	if(u==x && x==y){
		t[root]+=v,p[root]+=v;
		return;
	}
	int mid=x+y>>1;
	if(u<=mid) update(u,v,root*2,x,mid);
	if(u>mid) update(u,v,root*2+1,mid+1,y);
	t[root]=__gcd(t[root*2],t[root*2+1]);
	p[root]=p[root*2]+p[root*2+1];
}
int ask(int l,int r,int root=1,int x=1,int y=n+1){
	if(x>=l && y<=r) return t[root];
	int mid=x+y>>1,tot=0;
	if(l<=mid) tot=ask(l,r,root*2,x,mid);
	if(r>mid) tot=__gcd(tot,ask(l,r,root*2+1,mid+1,y));
	return tot;
}
int sum(int l,int r,int root=1,int x=1,int y=n+1){
	if(x>=l && y<=r) return p[root];
	int mid=x+y>>1,tot=0;
	if(l<=mid) tot+=sum(l,r,root*2,x,mid);
	if(r>mid) tot+=sum(l,r,root*2+1,mid+1,y);
	return tot;
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i]-a[i-1];
	creat(b,1,n+1);
	while(m--){
		char k;
		cin>>k;
		if(k=='C'){
			int l,r,v;
			cin>>l>>r>>v;
			update(l,v),update(r+1,-v);
		}
		if(k=='Q'){
			int l,r;
			cin>>l>>r;
			cout<<abs(__gcd(sum(1,l),ask(l+1,r)))<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：_ImposterX_ (赞：1)

## 置顶：感谢 @mahiro_zcy 佬帮忙调代码 orz

题解区都在写线段树，我来一发分块。

事实证明，$O(n\sqrt n)$ 是可以草过这道题的，而且时间充裕，实战不加卡常优化就能跑到 1s 以内。

至于远离，@mlvx 的[文章](https://www.luogu.com.cn/article/icod8sab)里讲得很清楚，其他的题解也可以参考，这里不再赘述。

设 $d_i = a_{i+1} - a_i$，也就是 $a$ 的差分数组。每次操作区间加的时候，只会改变 $d_{l-1}$ 和 $d_r$，而中间的部分不受影响。考虑对 $d$ 进行分块处理，用 $gcd_k$ 表示第 $k$ 块中 $d$ 的最大公约数。每次修改 $d_{l-1}, d_r$ 的时候，改动的部分其实就是 $l-1$ 和 $r$ 所在的块的最大公约数。

那就好维护了，直接对 $d_{l-1}$ 和 $d_r$ 的块重新算一遍最大公约数就行了。

对原数组的区间修改就更好维护了。散块暴力加，整块用 $add_k$ 表示第 $k$ 块被整体加了多少。$a_i$ 的实际值就是 $a_i + add_{k}$。

细节较多，详见代码。代码中有很多区间类似于 $l \sim r-1$ 或 $l-1 \sim r$ 的循环。具体原理可以手玩样例，或者联系作者。

```cpp
#include <bits/stdc++.h>

const int MAXN = 5e5 + 5;
typedef long long ll;

void ckmax(ll &x, ll y) {x = std::max(x, y);}
void ckmin(ll &x, ll y) {x = std::min(x, y);}

ll read() {
	ll x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -f; c = getchar();}
	while(c >= '0' && c <= '9') {x = (x << 1) + (x << 3) + c - '0'; c = getchar();}
	return f * x;
}

ll n, m, s;
ll a[MAXN], d[MAXN];
//d[i] = a[i + 1] - a[i]
ll belong[MAXN], add[MAXN], gcd[MAXN];
//belong[i] 表示第 i 个位置属于哪个块，add[i] 表示第 i 个块被整体加了多少，gcd[i] 表示第 i 个块的 d 的 gcd

int main() {
	std::ios::sync_with_stdio(false);
	n = read(), m = read();
	s = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read(), belong[i] = i / s + 1;
	for (int i = 1; i < n; i++) d[i] = a[i + 1] - a[i];
	ll nowgcd = 1;
	for (int i = 1; i < n; i++) {
		if(belong[i] != belong[i - 1]) {
			gcd[belong[i - 1]] = nowgcd;
			nowgcd = d[i];
		}
		else 
			nowgcd = std::gcd(nowgcd, d[i]);
	}
	if(!gcd[belong[n - 1]])
		gcd[belong[n - 1]] = nowgcd;
    //预处理 gcd
    // for (int i = 1; i <= n; i++) std::cout << belong[i] << " \n"[i == n];
	while(m--) {
		char c = getchar();
		if(c == 'Q') {
			ll l = read(), r = read();
			if(belong[l] == belong[r]) {
                //散块，这里可以直接暴力求
				ll nowgcd = a[l] + add[belong[l]];
				for (int i = l + 1; i <= r; i++)
					nowgcd = std::gcd(nowgcd, a[i] + add[belong[l]]);
				std::cout << llabs(nowgcd) << '\n';
			}
			else {
                //散块
				ll nowgcd = a[l] + add[belong[l]];
				for (int i = l; i <= r - 1 && belong[i] == belong[l]; i++)
					nowgcd = std::gcd(nowgcd, d[i]);
				for (int i = r - 1; i >= l && belong[r - 1] == belong[i]; i--)
					nowgcd = std::gcd(nowgcd, d[i]);

                //整块
				for (int i = belong[l] + 1; i < belong[r - 1]; i++)
					nowgcd = std::gcd(nowgcd, gcd[i]);
				
				std::cout << llabs(nowgcd) << '\n';
			}
		}
		else {
			ll l = read(), r = read(), x = read();
			if(belong[l - 1] == belong[r]) {
				//散块
				for (int i = l; i <= r; i++) {
					a[i] += x;
				}
				d[l - 1] += x;
				d[r] -= x;
				--l;//要修改的其实是 l-1 ~ r
				ll i = l;
				while(belong[i] == belong[l]) i--;
				i++;
                //跳到区间左端点
				ll nowgcd = d[i];
				for (; belong[i] == belong[l] && i < n; i++) {
					nowgcd = std::gcd(nowgcd, d[i]);
				}
				gcd[belong[l]] = nowgcd;
                //更新这个块的gcd
                for (i = r; belong[i] == belong[r]; i--);
				i++;
                //跳到 r 所在块左端点
				nowgcd = d[i];
				for (; belong[i] == belong[r] && i < n; i++) {
					nowgcd = std::gcd(nowgcd, d[i]);
				}
				gcd[belong[r]] = nowgcd;
                //更新 r 所在块的 gcd
			}
			else {
				for (int i = l; i <= r && belong[l] == belong[i]; i++)
					a[i] += x;
                for (int i = r; i >= l && belong[r] == belong[i]; i--)
                    a[i] += x;
				for (int j = belong[l] + 1; j < belong[r]; j++) {
					add[j] += x;
				}
                //先改原区间的值
				d[l - 1] += x;
				d[r] -= x;
				//差分

                //以下原理同上
				--l;
				ll i = l;
				while(belong[i] == belong[l]) i--;
				i++;
				ll nowgcd = d[i];
				for (; belong[i] == belong[l] && i < n; i++) {
					nowgcd = std::gcd(nowgcd, d[i]);
				}
				gcd[belong[l]] = nowgcd;
                //更新左端点所在块
				
				for (i = r; belong[i] == belong[r]; i--);
				i++;
                //跳到 r 所在块左端点
				nowgcd = d[i];
				for (; belong[i] == belong[r] && i < n; i++) {
					nowgcd = std::gcd(nowgcd, d[i]);
				}
				gcd[belong[r]] = nowgcd;
                //更新 r 所在块的 gcd
			}
		}
	}
	return 0;
}
```

---

## 作者：dutianchen1 (赞：1)

## 思路
首先，我们需要根据本题所需维护的大量数据和多次修改，并且这些数据满足**区间可加性**，分析得知本题可以使用**线段树**维护这些数据。

然后，就是如何使用线段树去维护数据。对于操作一，单点修改值，可以在其他简单模版题上详细了解，此处不多做解释。

而对于操作二，区间查询 $\gcd$，我们需要了解或者自行分析得出（利用归纳法即可证明）：
$$
\gcd(a,b,c)=\gcd(a-0,b-a,c-b)
$$

这种规律不仅在求三个数的 $\gcd$ 时满足，也可以推广到求任意个正整数的 $\gcd$ 的情况。

再根据式子中每个数变化后等价的形式，联想到差分数组维护原数组，再线段树去维护差分数组的区间 $\gcd$。

如此，我们就可以只需要进行两次单点修改便可以维护线段树，避免了区间修改。

最后，为了方便计算，规定 $\gcd(a,0)=\gcd(0,a)=0$。

------------
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
const ll INF = LONG_LONG_MAX;
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll abs1(ll a){return a>=0?a:-a;}
inline ll lowbit(ll x){return x&-x;}
ll num[N];
ll cf[N];//差分数组
ll t[N];//树状数组 
ll n,m;
inline ll sum(ll a)
{
	ll ret=0;
	for(;a;a-=lowbit(a))ret+=t[a];
  	return ret;
}
void add(ll x,ll y){for(;x<=n;x+=lowbit(x))t[x]+=y;}
struct SegmentTree{
	struct node
	{
		ll l,r;
		ll dat;
		ll add;
	}tr[N<<2];
	#define lc (pos<<1)
	#define rc (pos<<1|1)
	#define mid ((l+r)>>1)
	#define mid1 ((tr[pos].l+tr[pos].r)>>1)
	void bulid(int pos,int l,int r)
	{
		tr[pos].l=l;tr[pos].r=r;
		if(l==r){tr[pos].dat=cf[l];return ;}
		bulid(lc,l,mid);
		bulid(rc,mid+1,r);
		tr[pos].dat=gcd(tr[lc].dat,tr[rc].dat);
	}
	void change(ll pos,ll x,ll val)
	{
	    if(tr[pos].l==tr[pos].r)
		{
            tr[pos].dat+=val;
            return;
        }
        //spread(pos);
        if(x<=tr[lc].r) change(lc,x,val);
        else change(rc,x,val);
        tr[pos].dat=gcd(tr[lc].dat,tr[rc].dat);   
	}
	ll query(ll pos,ll L,ll R)
	{
		if(L<=tr[pos].l&&tr[pos].r<=R){return abs1(tr[pos].dat);}
    	ll ret=0;
    	if(L<=tr[lc].r) ret=gcd(ret,query(lc,L,R));
    	if(R>=tr[rc].l) ret=gcd(ret,query(rc,L,R));
    	return abs1(ret);
	}
}T;
char s;
int main()
{
	cin.tie(0);cout.tie(0);
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		num[i]=read();
		cf[i]=num[i]-num[i-1];
	}
	T.bulid(1,1,n);
	for(int i=1;i<=m;i++)
	{
		ll x,y;
		cin>>s>>x>>y;
		if(s=='Q')
		{
			if(x>=y)cout<<num[x]+sum(x)<<'\n';
			else cout<<gcd(T.query(1,x+1,y),num[x]+sum(x))<<'\n';
		}
		else
		{
			ll val=read();
			T.change(1,x,val);
			if(y<n) T.change(1,y+1,-val);
			add(x,val);
			add(y+1,-val);
		}
	}
	return 0;
} 
/*
5 5
1 3 5 7 9
Q 1 5
C 1 5 1
Q 1 5
C 3 3 6
Q 2 4

*/
```

---

## 作者：YZren (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10463)

# 思路

- 注意到本题求区间修改和区间最大公约数，很明显如果直接用线段树维护肯定要超时，所以需要思考最大公约数的特点。

- 显然 $\gcd(a,b)=\gcd(a,b-a)$ 并且 $\gcd(a_1,a_2,a_3)=\gcd(\gcd(a_1,a_2),\gcd(a_2,a_3))$，推广一下可得 
$$\gcd(a_1,a_2,a_3,\dots,a_{n-1},a_n)=\gcd(\gcd(a_1,a_2),\gcd(a_2,a_3),\dots,\gcd(a_{n-1},a_n))=\gcd(a_1,a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1})$$
 所以用差分。

- 这样可以用两棵线段树，一棵就正常维护和，另一棵单点修改维护差分数组的最大公约数。

## 第一棵线段树 Code

```cpp
struct node{
		int l,r,sum,lazy;
	} tree[maxn<<2];
	inline void push__up(int rt){tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;}
	inline void pushdown(int rt){
		tree[rt<<1].lazy+=tree[rt].lazy; tree[rt<<1|1].lazy+=tree[rt].lazy;
		tree[rt<<1].sum+=(tree[rt<<1].r-tree[rt<<1].l+1)*tree[rt].lazy;
		tree[rt<<1|1].sum+=(tree[rt<<1|1].r-tree[rt<<1|1].l+1)*tree[rt].lazy;
		tree[rt].lazy=0;
	}
	inline void build(int rt,int l,int r){
		tree[rt].l=l; tree[rt].r=r;
		if(l==r){
			tree[rt].sum=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid); build(rt<<1|1,mid+1,r);
		push__up(rt);
	}
	inline void update(int rt,int l,int r,int val){
		if(tree[rt].l>r||tree[rt].r<l) return ;
		if(tree[rt].l>=l&&tree[rt].r<=r){
			tree[rt].lazy+=val;
			tree[rt].sum+=(tree[rt].r-tree[rt].l+1)*val;
			return ;
		}
		if(tree[rt].lazy) pushdown(rt);
		update(rt<<1,l,r,val); update(rt<<1|1,l,r,val);
		push__up(rt);
	}
	inline int query(int rt,int l,int r){
		if(tree[rt].l>r||tree[rt].r<l) return 0;
		if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].sum;
		if(tree[rt].lazy) pushdown(rt);
		return query(rt<<1,l,r)+query(rt<<1|1,l,r);
	}
```

## 第二棵线段树 Code

```cpp
struct node{
		int l,r,gcd;
	} tree[maxn<<2];
	inline void pushup(int rt){tree[rt].gcd=Gcd(tree[rt<<1].gcd,tree[rt<<1|1].gcd);}
	inline void build(int rt,int l,int r){
		tree[rt].l=l; tree[rt].r=r;
		if(l==r){
			tree[rt].gcd=C[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid); build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	inline void update(int rt,int l,int r,int val){
		if(tree[rt].l>r||tree[rt].r<l) return ;
		if(tree[rt].l==tree[rt].r){
			tree[rt].gcd+=val;
			return ;
		}
		update(rt<<1,l,r,val); update(rt<<1|1,l,r,val);
		pushup(rt);
	}
	inline int query(int rt,int l,int r){
		if(tree[rt].l>r||tree[rt].r<l)return 0;
		if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].gcd;
		return Gcd(query(rt<<1,l,r),query(rt<<1|1,l,r));
	}
```

这样此题结。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,k) for(int i=j;i<=k;i++)
#define F(i,j,k) for(int i=j;i>=k;i--)
const int maxn=5e5+10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void write(int x){
	if(x<0) {x=~(x-1); putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n=read(),m=read(),a[maxn],C[maxn];
inline int Gcd(int x,int y){return !y?abs(x):Gcd(y,x%y);}
namespace query_sum{
	struct node{
		int l,r,sum,lazy;
	} tree[maxn<<2];
	inline void push__up(int rt){tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;}
	inline void pushdown(int rt){
		tree[rt<<1].lazy+=tree[rt].lazy; tree[rt<<1|1].lazy+=tree[rt].lazy;
		tree[rt<<1].sum+=(tree[rt<<1].r-tree[rt<<1].l+1)*tree[rt].lazy;
		tree[rt<<1|1].sum+=(tree[rt<<1|1].r-tree[rt<<1|1].l+1)*tree[rt].lazy;
		tree[rt].lazy=0;
	}
	inline void build(int rt,int l,int r){
		tree[rt].l=l; tree[rt].r=r;
		if(l==r){
			tree[rt].sum=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid); build(rt<<1|1,mid+1,r);
		push__up(rt);
	}
	inline void update(int rt,int l,int r,int val){
		if(tree[rt].l>r||tree[rt].r<l) return ;
		if(tree[rt].l>=l&&tree[rt].r<=r){
			tree[rt].lazy+=val;
			tree[rt].sum+=(tree[rt].r-tree[rt].l+1)*val;
			return ;
		}
		if(tree[rt].lazy) pushdown(rt);
		update(rt<<1,l,r,val); update(rt<<1|1,l,r,val);
		push__up(rt);
	}
	inline int query(int rt,int l,int r){
		if(tree[rt].l>r||tree[rt].r<l) return 0;
		if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].sum;
		if(tree[rt].lazy) pushdown(rt);
		return query(rt<<1,l,r)+query(rt<<1|1,l,r);
	}
}
namespace query_gcd{
	struct node{
		int l,r,gcd;
	} tree[maxn<<2];
	inline void pushup(int rt){tree[rt].gcd=Gcd(tree[rt<<1].gcd,tree[rt<<1|1].gcd);}
	inline void build(int rt,int l,int r){
		tree[rt].l=l; tree[rt].r=r;
		if(l==r){
			tree[rt].gcd=C[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(rt<<1,l,mid); build(rt<<1|1,mid+1,r);
		pushup(rt);
	}
	inline void update(int rt,int l,int r,int val){
		if(tree[rt].l>r||tree[rt].r<l) return ;
		if(tree[rt].l==tree[rt].r){
			tree[rt].gcd+=val;
			return ;
		}
		update(rt<<1,l,r,val); update(rt<<1|1,l,r,val);
		pushup(rt);
	}
	inline int query(int rt,int l,int r){
		if(tree[rt].l>r||tree[rt].r<l)return 0;
		if(tree[rt].l>=l&&tree[rt].r<=r) return tree[rt].gcd;
		return Gcd(query(rt<<1,l,r),query(rt<<1|1,l,r));
	}
}
inline void work(){
	f(i,1,n) a[i]=read(),C[i]=a[i]-a[i-1];
	query_sum::build(1,1,n); query_gcd::build(1,1,n+1);
	while(m--){
		char ch; std::cin>>ch;
		int x=read(),y=read(),z;
		if(ch=='C'){ 
			z=read();
			query_sum::update(1,x,y,z);
			query_gcd::update(1,x,x,z);
			query_gcd::update(1,y+1,y+1,-z);
		}
		else write(abs(Gcd(query_sum::query(1,x,x),query_gcd::query(1,x+1,y)))),putchar('\n');
	}
}
signed main(){work();return !!!!!("YZren");}
```

---

## 作者：FlyPancake (赞：1)

## [P10463 Interval GCD 题解](https://www.luogu.com.cn/problem/P10463)

### Idea

辗转相减法（[前置知识](https://baike.baidu.com/item/%E8%BE%97%E8%BD%AC%E7%9B%B8%E5%87%8F/7529647)）：

$$\gcd(a, b) = \gcd(a, b-a)$$

推广到 $n$ 项：

$$\gcd(a_1, a_2, \dots, a_n) = \gcd(a_1, a_2-a_1, a_3-a_2,\dots, a_n-a_{n-1})$$

看到题意中把 $A_l, A_{l+1}, \dots, A_r$ 都加上 $d$，自然想到差分。

令差分完之后的数组为 $B$，那么 $\gcd(B_{l+1}, B_{l+2}, \dots, B_r) = \gcd(A_{l+1}, A_{l+2}, \dots A_r)$，而 $\gcd(B_l,B_{l+1}) \neq \gcd(A_l, A_{l+1})$，所以 $A_l$ 需要单独维护。

以下用线段树维护差分数组的 $\gcd$，用树状数组维护差分数组，最后通过前缀和求得 $A_l$。

注意开 long long。

### Code

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 5e5+5;
#define lowbit(x) x&(-x)
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define gcd(x, y) abs(__gcd((x), (y)))

int n, m;
ll a[N], cha[N], c[N];
struct node{
    int l, r;
    ll v;
}tr[N<<2];

void add(int x, ll y){
    while(x <= n){
        c[x] += y;
        x += lowbit(x);
    }
}

ll sum(int x){
    ll ret = 0;
    while(x){
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}

void pushup(int x){
    tr[x].v = gcd(tr[ls(x)].v, tr[rs(x)].v);
}

void buildtr(int x, int l, int r){
    tr[x].l = l, tr[x].r = r;
    if(l == r){
        tr[x].v = cha[l];
        return;
    }
    int mid = (l+r) >> 1;
    buildtr(ls(x), l, mid);
    buildtr(rs(x), mid+1, r);
    pushup(x);
}

void upd(int x, int tar, ll d){
    if(tr[x].l > tar || tr[x].r < tar)
        return;
    if(tr[x].l == tr[x].r && tr[x].l == tar){
        tr[x].v += d;
        return;
    }
    int mid = (tr[x].l+tr[x].r) >> 1;
    if(tar<=mid) upd(ls(x), tar, d);
    upd(rs(x), tar, d);
    pushup(x);
}

ll query(int x, int l, int r){
    if(tr[x].l > r || tr[x].r < l)
        return 0;
    if(tr[x].l >= l && tr[x].r <= r)
        return tr[x].v;
    return gcd(query(ls(x), l, r), query(rs(x), l, r));
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        cha[i] = a[i] - a[i-1];
        add(i, cha[i]);
    }
    buildtr(1, 1, n);
    while(m--){
        char op; int l, r; cin>>op>>l>>r;
        if(op == 'C'){
            ll d; cin>>d;
            upd(1, l, d);
            upd(1, r+1, -d);
            add(l, d);
            add(r+1, -d);
        } else if(op == 'Q'){
            cout<<gcd(sum(l), query(1, l+1, r))<<"\n";
        }
    }
    return 0;
}
```

---

## 作者：Toorean (赞：0)

给出数列 $a$，多次操作与查询：区间加，区间查 $\gcd$。

由更相减损术，对于整数 $a,b$，我们有：$\gcd(a,b)=\gcd(a,b-a)$。

实际上，我们可以将这个性质推广到 $n$ 项，即：$\gcd(a_1,a_2,\cdots,a_n)=\gcd(a_1,a_2-a_1,\cdots,a_n-a_{n-1})$，用数学归纳法可证明。

于是我们构造差分数组 $b$，$b_i=a_i-a_{i-1}$，上式即 $\gcd(a_L,\cdots,a_R)=\gcd(a_L,b_{L+1},\cdots,b_R)$，这是查询操作，其中 $a_L=\sum\limits_{i=1}^L b_i$。

而在 $a$ 的区间 $[l,r]$ 上的加操作，即为其差分数组 $b$ 上 $b_l$ 与 $b_{r+1}$ 的单点修改操作。

综上，我们只需要用一个数据结构维护差分数组 $b$ 的区间和、区间 $\gcd$ 并可以实现单点修改。注意，由于差分数组内可能出现负数的情况，因此我们需要再给出答案时取绝对值。

---

