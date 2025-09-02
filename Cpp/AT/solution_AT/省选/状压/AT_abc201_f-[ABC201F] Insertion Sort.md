# [ABC201F] Insertion Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc201/tasks/abc201_f

$ 1 $ から $ N $ までの番号が振られた $ N $ 人の人が左右一列に並んでいます。はじめ、左から $ i $ 番目の人の番号は $ P_i $ です。

あなたの目標は、以下の $ 3 $ 種類の操作を繰り返すことで人々が左から番号の昇順で並んでいるようにすることです。これらの操作は、任意の順に何回でも（$ 0 $ 回でもよい）行うことができます。

- 整数 $ i\ (1\ \leq\ i\ \leq\ N) $ を選ぶ。コスト $ A_i $ を払い、人 $ i $ を好きな位置に移動させる。
- 整数 $ i\ (1\ \leq\ i\ \leq\ N) $ を選ぶ。コスト $ B_i $ を払い、人 $ i $ を左端に移動させる。
- 整数 $ i\ (1\ \leq\ i\ \leq\ N) $ を選ぶ。コスト $ C_i $ を払い、人 $ i $ を右端に移動させる。

目標を達成するまでに支払う合計コストを最小化してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ \leq\ N $
- $ 1\ \leq\ A_i,B_i,C_i\ \leq\ 10^9 $
- $ P_i\ \neq\ P_j\ (i\ \neq\ j) $
- 入力は全て整数

### Sample Explanation 1

コスト $ C_3=6 $ を払って人 $ 3 $ を右端に動かすことで、人々を昇順に並び替えることができます。 これより合計コストが低い並び替え方は存在しないので、答えは $ 6 $ となります。

### Sample Explanation 2

以下の順に操作を行うことで最小値を達成可能です。 - コスト $ B_1=8 $ を払い、人 $ 1 $ を左端に移動させる。 - コスト $ C_5=5 $ を払い、人 $ 5 $ を右端に移動させる。 - コスト $ C_6=2 $ を払い、人 $ 6 $ を右端に移動させる。

## 样例 #1

### 输入

```
3
3 1 2
9 3 5
8 6 4
9 4 6```

### 输出

```
6```

## 样例 #2

### 输入

```
6
2 6 5 3 4 1
10 8 16
30 2 10
10 17 8
11 27 22
8 6 5
15 29 2```

### 输出

```
15```

## 样例 #3

### 输入

```
9
3 8 4 7 6 9 1 5 2
7976 3696 9706
768 8807 8521
1133 8683 7120
1189 3331 2259
900 7451 1159
6126 2639 7107
5540 8253 2891
8417 4220 9091
8732 1417 1540```

### 输出

```
15865```

## 样例 #4

### 输入

```
12
11 9 1 12 2 7 3 5 10 4 6 8
3960 3158 9029
6521 6597 7581
5688 2299 2123
4946 4298 9122
394 4350 9142
3098 7151 2039
8525 3758 6155
6970 3658 9353
9780 1778 3608
6065 5562 923
9701 5524 6482
9395 6016 705```

### 输出

```
20637```

# 题解

## 作者：Tx_Lcy (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc201_f)

难度：$2484$。

好像跟现有题解思考过程不太一样，不过码写出来是一样的。

## 思路

我们先让 $B_i,C_i$ 都与 $A_i$ 取 $\min$，这样往左移，往右移都一定不劣于任意移。

假如我们已经确定了我们要进行哪些操作，顺序是如何的。

我们可以按照如下顺序执行：整体向左移，整体向右移，任意移。

设向左移的数颜色为 $1$，向右移的数颜色为 $2$，任意移或不移的数颜色为 $3$。

则执行完整体向左移和整体向右移后操作原序列会变成：$1...13...32...2$。

简单地贪心一下，其中整体向左移一定是 $p_i$ 大的先向左移，整体向右移一定是 $p_i$ 小的先向右移，因为这样可以保证左边的一段和右边的一段都是有序的。

然后我们发现往左移的数在值域上是一段前缀，往右移的数在值域上是一段后缀。

为啥呢？假设往左移的数是值域上一段前缀扣掉一些点，那么这些点不管是往右移了，还是没有移动，还是要移回来，插入到往左移的数中间。这是一个任意移操作，而由于我们可以另这个数跟着往左移的数一起往左移，且往左移操作一定是不劣与任意移的，所以原命题成立，往右移也是同理的。

这样我们同时也证明了中间那些任意移或不移的数在值域上也是连续的。

我们考虑固定哪些数往左移，哪些数往右移，如何计算中间段的贡献。

不难发现不移动的数一定是一个上升子序列，这样我们就可以直接 $\rm DP$ 了，用树状数组优化这个 $\rm DP$ 可以做到 $\mathcal O(n^2 \log n)$ 的时间复杂度。

写完这个之后，我瞪着这个奇怪的区间带权最长上升子序列瞪了 $20 \min$，发现完全不会优化。

然后，我发现我们可以把前面的：$1...13...3$ 并到一个 $\rm DP$ 状态里算，不需要枚举 $1,3$ 的分割点。

设 $f_i$ 表示前面 $i$ 个点是 $1..13..3$ 的最小代价，然后我们加上 $\sum_{j=i+1}^n C_j$ 之后就是当前的答案。

$f_i$ 的转移也是简单的：$f_i=\min(\sum_{j=1}^i B_j,f_k+\sum_{j=k+1}^{i-1} A_j)$，其中 $k < q_i$（$q_i$ 表示值为 $i$ 的数在原数组里的编号）。

然后可以直接树状数组优化转移，时间复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&-x)
int const N=2e5+10;
int p[N],q[N],f[N],pre[N],suf[N],a[N],b[N],c[N],sum[N];
struct Tree_Array{
    int c[N];
    int query(int x){int res=1e18;while (x) res=min(res,c[x]),x-=lowbit(x);return res;}
    void update(int x,int v){while (x<N) c[x]=min(c[x],v),x+=lowbit(x);}
}T;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    memset(T.c,0x3f,sizeof(T.c));
    int n;cin>>n;
    for (int i=1;i<=n;++i) cin>>p[i],q[p[i]]=i;
    for (int i=1;i<=n;++i) cin>>a[i]>>b[i]>>c[i],b[i]=min(b[i],a[i]),c[i]=min(c[i],a[i]);
    for (int i=1;i<=n;++i) pre[i]=pre[i-1]+b[i];
    for (int i=n;i>=1;--i) suf[i]=suf[i+1]+c[i];
    for (int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    int ans=1e18,res=0;
    for (int i=1;i<=n;++i){
        f[q[i]]=min(pre[i-1],T.query(q[i]-1)+sum[i-1]);
        ans=min(ans,suf[i+1]+f[q[i]]);
        T.update(q[i],f[q[i]]-sum[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：songhongyi (赞：10)

官方题解做法。

显然一个人只会移动一次，因为多次反复横跳没有什么意义。

我们考虑那些没有移动的人，显然至少存在一个。证明只需考虑把编号最大的一个向左移动的固定住，显然至少可以减少这一个人的代价。

那我们不难发现，不移动的人相当于把原来的人按照编号划分成了若干个区间。具体地说，在固定的人确定为 $S_1<S_2<\cdots S_k$ 后，你的策略应该是：

* 编号小于 $S_1$ 的从大到小放到左边，代价为 $\min(A_i,B_i)$；
* 编号大于 $S_k$ 的从小到大放到右边，代价为 $\min(A_i,C_i)$；
* 其余的放到对应的位置上，代价为 $A_i$。

问题变成随意安排一个人是否不动，最小化代价和。因为 $S$ 中的数在原序列中也要升序，所i有从小到大考虑的话，前面人的安排不影响后面的人，即问题没有后效性。

因而我们可以进行 dp。设 $dp_i$ 表示考虑到编号不超过 $i$ 的人，且满足 $i\in S$ 的最小代价和。

不难得到转移方程：
$$
dp_i = \min \left (\sum_{j=1}^{i-1} \min (A_j,B_j),\min_{j<i,p'_{j}<p'_{i}}\left(dp_j+\sum_{k=j+1}^{i-1}A_k\right)\right )
$$


其中 $p'$ 是原排列的逆。前半部分表示令 $i$ 为第一个固定住的，后半部分表示枚举前一个固定的人 $j$。

最后的答案应该是：
$$
\min _{1\le i\le n} \left(dp_i+\sum_{j=i+1}^n \min(A_j,C_j)\right)
$$


两个求和都可以通过前缀和解决，但是后半部分因为要枚举 $j$，复杂度为 $O(n^2)$，无法通过。我们试图进行优化。

考虑将常数分离出来。我们设 $sum_i = \sum _{j=1}^i A_j$，则有：
$$
dp_j+\sum_{k=j+1}^{i-1}A_k=dp_j+sum_{i-1}-sum_j
$$
我们将 $dp_j-sum_j$ 视为一个整体，将 $sum_{i-1}$ 移到这个问题等价于在二维偏序中找最小值。我们在一个数据结构中动态地实现这些事情：

* 查询 $p'_i$ 前的前缀最小值；
* 将 $p'_i$ 的值设为 $dp_i-sum_i$。

显然一个线段树可以维护这件事情。复杂度 $O(n \log n)$。

参考代码：

```cpp
//
// Problem: [ABC201F] Insertion Sort
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_abc201_f
// Memory Limit: 1 MB
// Time Limit: 2000 ms

#include <iostream>
#define lson x * 2
#define rson x * 2 + 1
using namespace std;
int p[ 200010 ], pos[ 200010 ];
int a[ 200010 ], b[ 200010 ], c[ 200010 ];
long long int tree[ 800010 ];
void pushup( int x )
{
    tree[ x ] = min( tree[ lson ], tree[ rson ] );
}
void build( int x, int l, int r )
{
    if ( l == r )
    {
        tree[ x ] = 0x3f3f3f3f3f3f3f3f;
    }
    int mid = ( l + r ) / 2;
    build( lson, l, mid );
    build( rson, mid + 1, r );
}
void update( int x, int l, int r, int p, long long int v )
{
    if ( l == r )
    {
        tree[ x ] = min( tree[ x ], v );
        return;
    }
    int mid = ( l + r ) / 2;
    if ( p <= mid )
    {
        update( lson, l, mid, p, v );
    }
    else
    {
        update( rson, mid + 1, r, p, v );
    }
    pushup( x );
}
long long int query( int x, int l, int r, int p )
{
    if ( r <= p )
    {
        return tree[ x ];
    }
    int mid = ( l + r ) / 2;
    if ( p <= mid )
    {
        return query( lson, l, mid, p );
    }
    else
    {
        return min( tree[ lson ], query( rson, mid + 1, r, p ) );
    }
}
void updatet( int x, int l, int r, int p, long long int v )
{
    tree[ p ] = v;
}
long long int queryt( int x, int l, int r, int p )
{
    long long int ans = tree[ p ];
    for ( int i = 1; i < p; i++ )
    {
        ans = min( ans, tree[ i ] );
    }
    return ans;
}
long long int suma[ 200010 ], sumab[ 200010 ], sumac[ 200010 ];
long long int dp[ 200010 ];
int main()
{
    int n;
    cin >> n;
    for ( int i = 1; i <= n; i++ )
    {
        cin >> p[ i ];
        pos[ p[ i ] ] = i;
    }
    for ( int i = 1; i <= n; i++ )
    {
        cin >> a[ i ] >> b[ i ] >> c[ i ];
        suma[ i ] = suma[ i - 1 ] + a[ i ];
        sumab[ i ] = sumab[ i - 1 ] + min( a[ i ], b[ i ] );
        sumac[ i ] = sumac[ i - 1 ] + min( a[ i ], c[ i ] );
    }
    for ( int i = 1; i <= n; i++ )
    {
        dp[ i ] = sumab[ i - 1 ];
        dp[ i ] = min( dp[ i ], query( 1, 1, n, pos[ i ] ) + suma[ i - 1 ] );
        update( 1, 1, n, pos[ i ], dp[ i ] - suma[ i ] );
    }
    long long int ans = 0x3f3f3f3f3f3f3f3f;
    for ( int i = 1; i <= n; i++ )
    {
        ans = min( ans, dp[ i ] + sumac[ n ] - sumac[ i ] );
    }
    cout << ans << endl;
}
```



---

## 作者：KazamaRuri (赞：2)

题意清晰，不再赘述。

## 分析

一道看上去就是 dp 或者贪心的题。

先做一个小处理，将 $ b_i $ 和 $ c_i $ 分别对 $ a_i $ 取 $ \min $，方便我们计算单纯往左右移动的最小花费。

我们不会想去动那些“高花费”的人，所以思考：在最小花费的排序中，总有些人是没有动过的，并且这些数一定构成了一个单调上升的子序列。想象一下，值域上被子序列划分成很多段，它们是不可移动的，在第一个断点前面那一段，必须要把数组里的下标移到断点对应的位置之前（左边），这会花费我们 $ \sum b $ 的代价移动；最后一个断点后面的段要花费 $ \sum c $ 的代价；被断点“夹”住的点往左或右是不确定的，需要 $ \sum a $ 的代价。定义状态 $ f_i $ 表示以 $ i $ 做为最后一个“断点”或者说上升子序列的结尾排序的最小花费。记 $ p_i $ 为排序前编号为 $ i $ 的人对应的位置。从上升子序列入手，得到状态转移方程：
$$
f_i = \min( \sum_{k=1}^{i-1} b_k ,\min_{ j \le i \, , \, p_j \le p_i } f_j + \sum_{k=j+1}^{i-1} a_k )
$$
后面那一坨东西是一个明显的二维偏序，用权值树状数组维护一下 $ f_j - sum_j $ 的最小值，让查询结果加上 $ sum_{i-1} $ 就可以了（$ sum $ 为 $ a $ 的前缀和）。别忘了还要把最后一个断点后那一段加上去，最后的答案就是：
$$
\min( f_i + \sum_{j=i+1}^{n} c_j )
$$

## 代码

没有刻意压行。

```cpp
// Liberty/.
#include <iostream>
using namespace std;

typedef long long ll;
const int N=2e5+5; const ll inf=0x3f3f3f3f3f3f3f3f;
int n,p[N]; ll sa[N],sb[N],sc[N],t[N],dp[N],ans=inf;
inline int lb(int x){ return x&-x; }
void upd(int x,ll k){ for(;x<=n;x+=lb(x)) t[x]=min(t[x],k); }
ll ask(int x){ ll ret=inf; for(;x;x-=lb(x)) ret=min(ret,t[x]); return ret; }
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) t[i]=inf,
		scanf("%d",&x),p[x]=i;
	for(int i=1,a,b,c;i<=n;i++)
		scanf("%d%d%d",&a,&b,&c),
		sa[i]=sa[i-1]+a,
		sb[i]=sb[i-1]+min(a,b),
		sc[i]=sc[i-1]+min(a,c);
	for(int i=1;i<=n;i++)
		ans=min(ans,(dp[i]=min(sb[i-1],ask(p[i])+sa[i-1]))+sc[n]-sc[i]),
		upd(p[i],dp[i]-sa[i]);
	return printf("%lld",ans),0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

令 $a_{p_i}=i$，那么 $a_i$ 表示 $i$ 号位最终站的人应该为 $a_i$。

使 $B_i\gets\min(B_i,A_i),C_i\gets\min(C_i,A_i)$。

观察到有一些点是不必移动的，所以设 $dp_i$ 表示编号在 $1\sim i$ 且 $a_i$ 不动时排好序的代价。转移为：$dp_i=\displaystyle\min\left(\sum_{j<i}B_j,\sum_{j<i,a_j<a_i}\left(dp_j+\sum_{j<k<i}A_k\right)\right)$。最后答案为 $\displaystyle\min\left(dp_i+\sum_{j>i}C_j\right)$。

对 $A,B$ 做前缀和，转移就可以拆成一个只与 $j$ 有关的部分和只与 $i$ 有关的部分，把 $a$ 当作下标放入权值树状数组中维护前缀最小值就可以了。对 $C$ 做后缀和，统计答案也是容易的。

# Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
inline int lowbit(int x){
	return x&-x;
}
ll bit[200005];
int n;
inline void upd(int x,ll y){
	for(;x<=n;x+=lowbit(x))bit[x]=std::min(bit[x],y);
}
inline ll ask(int x){
	ll res=4e18;
	for(;x;x^=lowbit(x))res=std::min(res,bit[x]);
	return res;
}
ll dp[200005];
int a[200005],b[200005],c[200005];
int p[200005];
ll ans;
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;++i)
		scanf("%d",&x),p[x]=i;
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&a[i],&b[i],&c[i]),
		b[i]=std::min(b[i],a[i]),c[i]=std::min(c[i],a[i]);
	memset(bit+1,63,n<<3);
	for(int i=1;i<=n;++i){
		static ll S=0,s=0;
		dp[i]=std::min(S,ask(p[i])+s);
		S+=b[i];s+=a[i];
		upd(p[i],dp[i]-s);
	}
	ans=4e18;
	for(int i=n;i;--i){
		static ll S=0;
		ans=std::min(ans,dp[i]+S);
		S+=c[i];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Reunite (赞：1)

挺好的典题。

## 一
---

首先，每个人显然只会移动一次，否则可以通过调整证明不优。但还是不好做，联想到序列上操作的题常见的套路：一定有一些值不变/存在新序列中。稍加思考发现是对的，最终情况一定是移动部分点之后，剩下的恰好不再需要移动。有这两个性质就可以 dp 了。

假设我们钦定编号为 $x_1,x_2 \cdots x_k$ 为不动点，$q_i$ 为原排列的逆，则一定有 $\forall i<j,q_{x_i}<q_{x_j}$，因为这些点不能移动，必须保证相对升序。剩下的点必须移动，对于 $i<x_1$ 的 $i$，可以从大到小的选择 $\min(A_i,B_i)$ 进行移动，$i>x_k$ 的同理，其余的只能通过也必须通过 $A_i$ 移动，因此有：

$$f_i=\min(\sum_{j=1}^{i-1}\min(A_j,B_j),\min_{j<i \wedge q_j<q_i}(f_j+\sum_{k=j+1}^{i-1} A_k))$$

预处理前缀和，有：

$$f_i=\min(S_{i-1},\min_{j<i \wedge q_j<q_i}(f_j-s_j)+s_{i-1})$$

左边的好做，右边的话，把括号内的看成一个整体，注意到我们不断在查一段前缀的 $\min$，只需要一个树状数组维护前缀 $\min$ 即可。

最后算答案还要枚举最后一个钦定的点，然后加上一段 $\min(A_i,C_i)$ 的后缀和。

---
## 二
---

时间复杂度 $O(n\log_2n)$，空间线性。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

int n;
int p[200005];
int q[200005];
int A[200005];
int B[200005];
int C[200005];
int s[200005];
int S[200005];
int f[200005];
int t[200005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void add(int x,int k){while(x<=n) t[x]=min(t[x],k),x+=x&-x;return ;}
inline int ask(int x){int s=1e18;while(x) s=min(s,t[x]),x^=x&-x;return s;}

signed main(){
	in(n);
	for(int i=1;i<=n;i++) in(p[i]),q[p[i]]=i;
	for(int i=1;i<=n;i++){
		in(A[i]),in(B[i]),in(C[i]);
		s[i]=s[i-1]+A[i];
		S[i]=S[i-1]+min(A[i],B[i]);
	}
	memset(t,0x3f,sizeof(t));
	for(int i=1;i<=n;i++){
		f[i]=min(S[i-1],ask(q[i])+s[i-1]);
		add(q[i],f[i]-s[i]);
	}
	int ans=1e18;
	for(int i=n;i>=1;i--) S[i]=S[i+1]+min(A[i],C[i]);
	for(int i=1;i<=n;i++) ans=min(ans,f[i]+S[i+1]);
	printf("%lld\n",ans);

	return 0;
}
```

---

## 作者：AKPC (赞：0)

显然可以把 $B_i,C_i$ 分别与 $A_i$ 取 $\min$。

不难发现，最优方案一定会有一些点不曾移动，考虑记录 $dp_i$ 表示不动编号 $i$ 的节点将 $[1,i]$ 区间内的编号排序的最小代价。

显然，一种方案将 $[1,i)$ 区间内的编号按从大到小的顺序放在最前面。另一种方案则是选择一个 $t\in[1,i)$ 且 $p_t<p_i$ 的转移点 $t$，但转移时 $(t,i)$ 范围内的编号仍然需要排序，这只能用任意插入位置的方式来做。由此得到转移方程：

$$dp_i=\min(\sum_{j=1}^{i-1}B_j,\min_{t\in[1,i),p_t<p_i}(dp_t+\sum_{j=t+1}^{i-1}A_j))$$

其中，$A,B$ 的区间和显然可以前缀和优化，而选择转移点 $t$ 的部分是二维偏序问题，可以权值树状数组维护。

因为将一个编号放在最后面的操作并没有使用，所以答案取 $dp_n$ 是不合理的。考虑加上这个操作，不难发现答案即为：

$$\min_{i=1}^n(dp_i+\sum_{j=i+1}^nC_i)$$

同样，$C$ 的区间和使用前缀和优化。

[code](/paste/o2e97nef)。

---

## 作者：Unnamed114514 (赞：0)

首先显然可以令 $b_i\gets\min\{a_i,b_i\},c_i\gets\min\{a_i,c_i\}$。

注意到实际上我们关心的是每个编号的位置，所以我们可以得到排列 $q$，满足 $q_{p_i}=i$。

然后你定义 $f_i$ 为钦定编号为 $i$ 的点不动的答案，枚举上一个编号不动的点 $j$ 转移即可，$(i,j)$ 的点都是移动到中间的，所以求 $a$ 的和。

然后还有就是 $i$ 是第一个的情况，这个时候 $[1,i)$ 都会移动到最前面，所以就是 $[1,i)$ 的 $b$ 的和。

求解答案的时候，找到最后一个不动的点 $i$，然后面的点移动到最后面，加上 $(i,n]$ 的 $c$ 的和。

单点赋值区间 `min`，用树状数组优化即可。

---

