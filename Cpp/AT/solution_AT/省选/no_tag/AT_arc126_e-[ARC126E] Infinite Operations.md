# [ARC126E] Infinite Operations

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc126/tasks/arc126_e

$ N $ 項からなる正整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ と $ Q $ 個のクエリが与えられます。$ i $ 番目のクエリは、以下のようなものです：

- 整数 $ x_i,\ y_i $ （ただし $ 1\leq\ x_i\leq\ N $）が与えられる。$ A_{x_i} $ を $ y_i $ に変更する。

クエリで数列が変更されるたびに、以下の問題の答えを $ \mod\ 998244353 $ で求めてください（注記参照）。

> 数列 $ A $ に対して以下の操作を $ n $ 回行うとき、獲得できる総得点の最大値を $ f(n) $ とする。
> 
> - $ A_i\leq\ A_j $ となる $ i,\ j $ および $ A_i\ +\ 2x\ \leq\ A_j $ となる**非負実数** $ x $ を選ぶ。
> - $ A_i $ に $ x $ を加え、$ A_j $ から $ x $ を引く。
> - $ x $ 点を獲得する。
> 
> 極限 $ \displaystyle\ \lim_{n\to\infty}\ f(n) $ が存在することが証明できる。この値を求めよ。

## 说明/提示

### 注記

求める極限は必ず有理数となることが証明できます。またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P,\ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\times\ Q\equiv\ P\pmod{998244353} $ かつ $ 0\leq\ R\ <\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ 1\leq\ Q\leq\ 3\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- $ 1\leq\ x_i\leq\ N $
- $ 1\leq\ y_i\leq\ 10^9 $

### Sample Explanation 1

$ 1 $ つめのクエリにより、数列は $ (5,\ 5,\ 5) $ へと変更されます。この場合任意の $ n $ に対して $ f(n)\ =\ 0 $ となり、答えは $ 0 $ となります。 $ 2 $ つめのクエリにより、数列は $ (5,6,5) $ へと変更されます。操作は例えば以下のように進行します。 - $ (i,j,x)\ =\ (3,2,0.4) $ と選ぶ。数列を $ (5,\ 5.6,\ 5.4) $ へ変更し、$ 0.4 $ 点を獲得する。 - $ (i,j,x)\ =\ (1,2,0.3) $ と選ぶ。数列を $ (5.3,\ 5.3,\ 5.4) $ へ変更し、$ 0.3 $ 点を獲得する。 上の方法では $ 2 $ 回の操作により $ 0.7 $ 点を獲得しており、$ f(2)\ \geq\ 0.7 $ であることがわかります。 この場合、獲得できる総得点は $ 1 $ を超えることはなく、操作回数を増やしていき最適な方法で操作を行うことで、獲得できる総得点を限りなく $ 1 $ に近づけることが可能であることが証明できます。したがって $ \displaystyle\ \lim_{n\to\infty}\ f(n)\ =\ 1 $ となります。

## 样例 #1

### 输入

```
3 4
7 5 5
1 5
2 6
1 7
3 5```

### 输出

```
0
1
2
2```

## 样例 #2

### 输入

```
2 4
1 2
2 5
1 3
1 2
2 3```

### 输出

```
2
1
499122178
499122177```

# 题解

## 作者：EuphoricStar (赞：4)

算是对[这篇博客](https://blog.csdn.net/qq_42101694/article/details/120434808)的补充吧。

设 $a_1 \le a_2 \le \cdots \le a_n$。

发现最优操作中一定是**对相邻的数进行操作**，因为如果 $a_j$ 想把 $x$ 给 $a_i$（$i < j$），最优是依次操作 $(j-1,j,x),(j-2,j-1,x),...,(i,i+1,x)$。这样 $x$ 就能造成 $(j-i)x$ 的得分。

最后全部数一定会无限趋近于 $\bar{a}$。考虑所有用到 $(i-1,i)$ 的操作的得分（拆贡献）。$i \sim n$ 的数如果想把一些量给 $1 \sim i-1$，就必须要用到 $(i-1,i)$。那么贡献为：

$$\sum\limits_{j=i}^n a_j - \bar{a}$$

什么意思呢？如果 $a_i < \bar{a}$，意味着 $\sum\limits_{j=1}^{i-1} \bar{a} - a_j > 0$，它们想要变成 $\bar{a}$ 必须要跟 $i$ 右边的大于平均值的数操作，所以贡献是 $\sum\limits_{j=1}^{i-1} \bar{a} - a_j = \sum\limits_{j=i}^n a_j - \bar{a}$；否则 $\sum\limits_{j=i}^n a_j - \bar{a} > 0$，它们想要变成 $\bar{a}$ 必须要跟 $i$ 左边的小于平均值的数换，所以贡献是 $\sum\limits_{j=i}^n a_j - \bar{a}$。

这样我们得到了最终的答案：

$$ans = \sum\limits_{i=1}^n i \times a_i - \frac{n+1}{2} \sum\limits_{i=1}^n a_i$$

右项容易维护，问题变成了维护左项即 $\sum\limits_{i=1}^n i \times a_i$。注意因为前面的讨论假定 $a_1 \le a_2 \le \cdots \le a_n$，所以这里的 $i$ 实际上是排名（为了保证排名不重复需要强制重复的数按位置排序），所以单点修改相当于是加入/删除一个数。而加入/删除一个数又会让比他大的数的排名 $+1/-1$。

拓展一下，可以看成是维护 $\sum\limits_{i=1}^n x_iy_i$，每次区间加 $x_i$ 或 $y_i$。这个可以用线段树做，每个结点维护 $\sum x_i, \sum y_i, \sum x_i y_i$ 即可。时间复杂度 $O((n + q) \log (n + q))$。

[code](https://atcoder.jp/contests/arc126/submissions/40979284)

---

## 作者：Rosabel (赞：2)

在求解式子部分与其他题解不同。

先考虑静态问题。

这题看上去直接在序列上操作是没有啥拓展空间的，那就排完序再做。假设此时升序排序后的数组为 $a_i$。

那么就来找性质了。观察整个序列，假设序列 $a$ 依 $x$ 被分为 $[1,x],[x+1,n]$ 两个部分。$\bar{a_A}=\frac{\sum_{i\in[1,x]}a_i}{x},\bar{a_B}=\frac{\sum_{i\in[x+1,n]}a_i}{n-x}$。操作 $(i,j)$ 可以分成两种，分别是 $i,j$ 在同一个部分和 $i,j$ 在两个不同的部分。最终状态一定是 $\bar{a}$ 。前者操作 $\bar{a_A}$ 和 $\bar{a_B}$ 值不会变，后者操作会使得 $\bar{a_A}$ 和 $\bar{a_B}$ 靠的更近。显然，一个序列的离散程度越大，所能产生的贡献必然越大。既然要离散程度最大化，那么后者操作选取靠中间的 $a_{mid},a_{mid+1}$ 能使得划分的两个部分离散程度最大化。

将一个序列通过若干次操作变为相同元素序列的操作叫做 **归并** 操作。

为了方便我们统计信息，可以将 $[1,x],[x+1,n]$ 先归并再做处理。即此处做分治。设被分治区间为 $[l,r]$，分治点为 $mid$。假设区间 $[l,mid],[mid+1,r],[l,r]$ 的平均值分别为 $x_1,x_2,x_3$，同时令 $y_1=mid-l+1,y_2=r-mid,y_3=r-l+1$。要想对 $[l,r]$ 归并，需要若干次对 $a_{mid},a_{mid+1}$ 进行操作，对于区间 $[l,mid]$，每一次操作完 $[l,mid]$ 区间的元素变为形如 ${p,p,\dots,p,p+k}(k\gt 0)$，然后再对这个序列进行归并。显然有 $w_1=\sum k=(x_3-x_1)y_1=(x_2-x_3)y_2$。区间 $[mid+1,r]$ 同理。

那我们已将问题简化成求解 ${p,p,\dots,p,p+k}(k\gt 0)$ 的贡献。不妨设 $g(n,k)$ 表示 $n$ 个元素最后一个增量为 $k$ 的代价。显然有 $g(1,k)=0$。考虑 $n\ge 2$ 的情况。步骤即为最后两个元素进行 $x=\frac{k}{2}$ 的操作，然后执行 $[1,n-1],k=\frac{k}{2}$ 的子问题，最后执行 $[1,n],k=\frac{k(n-2)}{2(n-1)}$ 的操作。可以得出递推式：
$$
g(n,k)=\frac{k}{2}+g(n-1,\frac{k}{2})+g(n,\frac{k(n-2)}{2(n-1)})
$$
先证明 $g(n)$ 是一个关于 $k(k\gt 0)$ 的正比例函数。

归纳法证明。$n=1$ 时，$g(1)$ 和 $x=0$ 等价，显然是正比例函数。

$n\ge 2$ 时，假设此时 $g(n-1)$ 已经证明为正比例函数，设 $g(n-1,k)=Ck,F=g(n)$。
$$
F(k)=\frac{k}{2}+Ck\cdot\frac{1}{2}+F(\frac{k(n-2)}{2(n-1)})
$$
假设 $F$ 为正比例函数，令 $P$ 为其斜率，有：
$$
F(k)=Pk=\frac{k}{2}+Ck\cdot\frac{1}{2}+P\cdot\frac{k(n-2)}{2(n-1)}
$$
解得 $P=(C+1)\cdot\frac{n}{n-1}$，即能找到与 $k$ 无关的 $P$ 使 $F(k)=Pk$，所以 $g(n)$ 为正比例函数。

设 $a_i$ 为正比例函数 $g(i)$ 的斜率。

然后有对于 $i=1,a_i=0$ 和 $i\gt 1,a_i=(a_{i-1}+1)\frac{i}{i-1}$。故：
$$
g(n,k)=a_nk
$$
其中 $a_n$ 可以递推求得。

在线怎么办呢？实际在数组中待过的元素个数为 $n+q$，离散化后可以用线段树维护这个需要支持单点修改的分治结构。

[code](https://atcoder.jp/contests/arc126/submissions/59053479)

给珂爱的小妹妹点个赞吧 qwq

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc126_e)

**题目大意**

> 给定长度为 $n$ 的序列 $a$，定义一次操作为 $a_i\gets a_i-x,a_j\gets a_j+x$，产生 $x$ 的收益，需要保证 $a_i-2x\ge a_j$。
>
> 支持 $q$ 次单点修改，动态维护最大收益。
>
> 数据范围：$n,q\le 3\times 10^5$。

**思路分析**

猜测答案为 $\dfrac 12\sum_{i<j}|a_i-a_j|$，这是可以证明的：

> 每次操作 $(i,j)$ 的贡献都会减小 $x$，而 $a_k>a_{i}+x$ 就会让 $(i,k)$ 贡献 $-x$，可以抵消 $(j,k)$ 贡献增量，同理 $a_k<a_j-x$ 的贡献会抵消。
>
> 因此一次代价为 $x$ 的操作至少会让上式 $-x$。

构造方案是容易的，每次取出排序后相邻的两个元素操作即可。

维护 $\sum |a_i-a_j|$ 直接主席树维护值域区间元素数量和元素和，合并左右区间时计算跨越区间的 $(i,j)$ 对贡献。

时间复杂度 $\mathcal O((n+q)\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5,MOD=998244353,V=1e9,i2=(MOD+1)/2;
struct Segt {
	int tot,ls[MAXN*60],rs[MAXN*60],siz[MAXN*60];
	ll sum[MAXN*60],val[MAXN*60];
	void psu(int p) {
		siz[p]=siz[ls[p]]+siz[rs[p]];
		sum[p]=(sum[ls[p]]+sum[rs[p]])%MOD;
		val[p]=(val[ls[p]]+val[rs[p]]+sum[rs[p]]*siz[ls[p]]-sum[ls[p]]*siz[rs[p]])%MOD;
	}
	void ins(int x,int op,int l,int r,int &p) {
		if(!p) p=++tot;
		if(l==r) return siz[p]+=op,sum[p]=(sum[p]+op*x)%MOD,void();
		int mid=(l+r)>>1;
		x<=mid?ins(x,op,l,mid,ls[p]):ins(x,op,mid+1,r,rs[p]);
		psu(p);
	}
}	T;
int n,q,a[MAXN],rt;
signed main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),T.ins(a[i],1,1,V,rt);
	for(int x,y;q--;) {
		scanf("%d%d",&x,&y);
		T.ins(a[x],-1,1,V,rt);
		T.ins(a[x]=y,1,1,V,rt);
		printf("%lld\n",(T.val[rt]+MOD)*i2%MOD);
	}
	return 0;
}
```

---

## 作者：Lgx_Q (赞：1)

[link](https://www.luogu.com.cn/problem/AT_arc126_e)

只需要手玩 + 大力猜就能做的题。

我们可以猜测：选择两个数操作，一定把他们变成两者的平均数。这个结论的可信度非常大。

设 $g(a_1,a_2,...,a_n)$ 表示 $a_{1...n}$ 的答案。

我们不妨先尝试点简单的，对于两个数 $x,y$，钦定 $x\le y$，显然有 $g(x,y)=\dfrac {y-x}2$。

对于三个数 $x,x,y(x\le y)$，我们选择任意一个 $x$ 与 $y$ 操作一遍，变为 $x,\dfrac {x+y}2,\dfrac{x+y}2$，则 $g(x,x,y)=\frac {y-x}2 +g(x,\frac {x+y}2,\frac {x+y}2)$。操作有对称性，所以 $g(x,\frac {x+y}2,\frac {x+y}2)=g(\frac {x+y}2,\frac{x+y}2,y)=g(\frac{x+y}2,y,y)$。

设 $h_0(d)=g(x,x+d,x+d)$，则 $h_0(d)=\frac 12 d+h_0(\frac d2)$，极限取到 $h_0(d)=d$。

对于三个数 $x,y,z(x\le y\le z)$，我们有三种方法：

+ 先操作 $x,z$，变为 $g(\frac{x+z}2, \frac{x+z}2,y)$。

+ 先操作 $x,y$，变为 $g(\frac{x+y}2, \frac{x+y}2,z)$。

+ 先操作 $y,z$，变为 $g(\frac{y+z}2, \frac{y+z}2,x)$。

我们计算一下，三种的得分分别是 $\frac{z-x}2+|\frac{x+z}2-y|,\space z-x,\space z-x$，容易发现前者一定不优于后两者，猜测存在一种最优策略，每次只操作相邻的数字。

后面两种方法的得分相同，猜测相邻数字的操作顺序对答案没有影响。

对于 $x,x,y,y(x\le y)$，根据上面猜的结论，我们先操作一对 $(x,y)$，得到两个 $\frac{x+y}2$。然后再把操作后得到的两个数分别与另外两个数操作，那么 $g(x,x,y,y)=y-x+g(x+\frac{x+y}4,x+\frac{x+y}4,y-\frac{x+y}4,y-\frac{x+y}4)$。

设 $h_1(d)=g(x,x,x+d,x+d)$，则 $h_1(d)=d+h_1(\frac d2)$，极限取到 $h_1(d)=2d$。

对于 $x,y,y,y(x\le y)$，我们操作一对 $(x,y)$，得到 $g(x,y,y,y)=\frac {y-x}2+g(\frac{x+y}2,\frac{x+y}2,y,y)=\frac {3(y-x)}2$。

我们猜测：有 $n$ 个 $x$ 和 $m$ 个 $y$，且 $x\le y$，答案为 $nm\cdot\frac{y-x}2$。

维护一棵动态开点线段树，每次左右儿子合并时，视为左右边所有数都变成了各自的平均数，然后根据上面的结论计算即可，时间复杂度 $O(n\log V)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pir pair<ll,ll>
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
using namespace std;
const ll maxn=3e5+10, mod=998244353, M=1e9;
ll n,m,sum[maxn*60],res[maxn*60],inv[maxn],tot,lc[maxn*60],rc[maxn*60],cnt[maxn*60],a[maxn],rt;
void modify(ll &p,ll l,ll r,ll x,ll v){
	if(!p) p=++tot;
	if(l==r){
		cnt[p]+=v;
		sum[p]+=x*v; sum[p]%=mod;
		return;
	} ll mid=l+r>>1;
	if(x<=mid) modify(lc[p],l,mid,x,v);
	else modify(rc[p],mid+1,r,x,v);
	sum[p]=(sum[lc[p]]+sum[rc[p]])%mod, cnt[p]=cnt[lc[p]]+cnt[rc[p]];
	res[p]=(res[lc[p]]+res[rc[p]]+cnt[rc[p]]%mod*cnt[lc[p]]%mod*(sum[rc[p]]*
	inv[cnt[rc[p]]]%mod-sum[lc[p]]*inv[cnt[lc[p]]]%mod))%mod;
}
int main(){
	scanf("%lld%lld",&n,&m);
	inv[1]=1;
	for(ll i=2;i<=n;i++) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	for(ll i=1,x;i<=n;i++){
		scanf("%lld",&x); modify(rt,1,M,x,1); a[i]=x;
	}
	while(m--){
		ll x,y; scanf("%lld%lld",&x,&y);
		modify(rt,1,M,a[x],-1);
		modify(rt,1,M,y,1); a[x]=y;
		printf("%lld\n",(res[rt]+mod)*inv[2]%mod);
	}
	return 0;
}
```

---

## 作者：shiruoyu114514 (赞：0)

脑电波题。

>断言：令 $D = \sum \limits_{i=1}^n \sum \limits_{j=1}^n |a_i-a_j|$，即每个点到其它所有点的距离之和，则答案为 $\frac{1}{4}D$。
>
>证明：我们可以把每次操作拆成若干次操作，使得每次操作过后，不会有一对 $p,q$ 满足在操作前有 $a_p<a_q$，在操作后有 $a_p>a_q$。
>
>当我们操作下标 $i,j(a_i<a_j)$ 相互靠近 $x$ 距离时，由于只有 $i,j$ 被改了，所以受到影响的只有所有点与 $i,j$ 之间的距离。
>
>对于 $i$ 左边的数 $l$，即 $a_l<a_i$，贡献为 $a_i-a_l+a_j-a_l$。由于 $a_i \leftarrow a_i+x$，$a_j \leftarrow a_j-x$，所以 $l$ 的贡献不会改变。
>
>对于中间的数 $m$，即 $a_i<a_m<a_j$，贡献为 $a_m-a_i+a_j-a_m=a_j-a_i$，变化后 $m$ 的贡献会减少 $2x$。
>
>对于右边的数 $r$，即 $a_j<a_r$，贡献为 $a_r-a_i+a_r-a_j$，变化后 $r$ 的贡献不变。
>
>而 $i,j$ 本身的贡献会减少 $4x$。
>
>所以每次贡献至少减少 $4x$，并且当且仅当中间没有数，即 $i,j$ 相邻时取等。
>
>于是得证。

单点修改并维护每个点的贡献时，我们只需要分别知道左边的数的个数与和值，右边的个数与和值即可。权值线段树维护即可。时间复杂度 $O(n \log n)$。

---

## 作者：_zdc_ (赞：0)

不妨把 $a$ 排序。

考虑一个特殊情况：$a_1=a_2=\cdots=a_{n-1}=0$，$a_n=x$。不妨设此时答案为 $F(n,x)$。

可以递归把 $a_2,a_3,\cdots,a_{n}$ 全部变为 $\dfrac{x}{n-1}$，然后全部取相反数后就是相同问题。可以归纳证明 $F(n,x)$ 的下界是 $\dfrac{(n-1)x}{2}$。

对于一般情况，考虑依次加入每个元素，然后把所有数操作到相同，然后就是特殊情况。加入 $a_i$ 时，前 $i-1$ 个数都是 $\dfrac{pre_{i-1}}{i-1}$，其中 $pre$ 为 $a$ 的前缀和数组。那么加入 $i$ 的贡献就是 $\dfrac{i-1}{2}\times(a_i-\dfrac{pre_{i-1}}{i-1})$。

经过一些化简后，这种方案构造出的收益可以表示为 $\sum\limits_{i=1}^na_i\times i-\dfrac{n+1}{2}\times\sum a$。可以离散化后树状数组维护做到 $(n+q)\log(n+q)$。

对于这个方案最优的证明，可以考虑设置初始势能 $\sum\limits_{i=1}^na_i\times i$，那么每次获得 $x$ 的收益时，势能总会减少 $\ge x$。并且有结束时势能为 $\dfrac{n+1}{2}\times\sum a$，因此答案也不会超过两者的差。

```cpp
#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
using namespace std;
void file() {
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
}
using ll = long long;

namespace QwQ {
  const int kMod = 998244353;
  const int inv2 = (kMod + 1) / 2;

  void Add(int& x, int y) { ((x += y) >= kMod) && (x -= kMod); }
  void Sub(int& x, int y) { ((x -= y) < 0) && (x += kMod); }
  int Sum(int x, int y) { return Add(x, y), x; }
  int Dif(int x, int y) { return Sub(x, y), x; }
  
  const int kN = 6e5 + 5;
  int n, q, o;
  array<int, kN> a, b, ord;

  struct Upd {
    int x, y;
    Upd() {  }
  };
  array<Upd, kN> upd;

  struct BIT {
    array<ll, kN> tr;
    void update(int x, ll v) {
      for(; x < kN; x += (x & -x))
        tr[x] += v;
    }
    ll query(int x) {
      ll ans = 0;
      for(; x; x &= (x - 1))
        ans += tr[x];
      return ans;
    }
  }bit1, bit2;

  int main() {
    // file();
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      b[++o] = a[i];
    }
    for(int i = 1; i <= q; i++) {
      cin >> upd[i].x >> upd[i].y;
      b[++o] = upd[i].y;
    }
    sort(b.data() + 1, b.data() + o + 1);
    o = unique(b.data() + 1, b.data() + o + 1) - b.data() - 1;
    auto find = [&](int x) -> int {
      return lower_bound(b.data() + 1, b.data() + o + 1, x) - b.data();
    };
    for(int i = 1; i <= n; i++)
      a[i] = find(a[i]);
    for(int i = 1; i <= q; i++)
      upd[i].y = find(upd[i].y);
    for(int i = 1; i <= o; i++)
      if(b[i] >= kMod) b[i] -= kMod;
    int sum = 0, ans = 0;
    iota(ord.data() + 1, ord.data() + n + 1, 1);
    sort(ord.data() + 1, ord.data() + n + 1,
      [&](int x, int y) -> bool {
        return a[x] < a[y];
      }
    );
    for(int i = 1; i <= n; i++) {
      int x = ord[i];
      bit1.update(a[x], 1);
      bit2.update(a[x], b[a[x]]);
      Add(sum, b[a[x]]);
      Add(ans, (ll)i * b[a[x]] % kMod);
    }
    for(int i = 1; i <= q; i++) {
      int x = upd[i].x, y = upd[i].y;
      Sub(ans, bit1.query(a[x]) * b[a[x]] % kMod);
      Sub(ans, Dif(sum, bit2.query(a[x]) % kMod));
      bit1.update(a[x], -1);
      bit2.update(a[x], -b[a[x]]);
      Add(sum, Dif(b[y], b[a[x]])), a[x] = y;
      bit1.update(a[x], 1);
      bit2.update(a[x], b[a[x]]);
      Add(ans, bit1.query(a[x]) * b[a[x]] % kMod);
      Add(ans, Dif(sum, bit2.query(a[x]) % kMod));
      cout << ((ans * 2ll - (ll)sum * (n + 1)) % kMod + kMod) * inv2 % kMod << "\n";
    }
    return 0;
  }
} // QwQ

int main() { return QwQ::main(); }
```

---

## 作者：shinkuu (赞：0)

非常有趣的脑电波题。

首先显然我们要会算一个序列的答案。这个操作很难直接模拟，所以可以考虑设计一个势能函数 $f(a)$，把序列的变化转化成 $f(a)$ 的变化，从而求出操作次数。

而想要找到一个合适的势能，则可以考虑从结束状态入手。结束状态 $f(a)=0$，所有 $a_i$ 相同，也就是两两之间距离为 $0$。考虑令 $f(a)=\sum_{1\le i\le j\le n}|a_i-a_j|$。

先把 $a_i$ 排序。考虑对 $i,j(i<j)$ 操作一个 $\Delta$ 之后变成 $a'$，$f(a)$ 的变化。容易发现，$\forall k>j,a_k'-a_j'=a_k-a_j+\Delta,a_k'-a_i'=a_k-a_i-\Delta$，相抵消之后不变。而 $\forall k,i<k<j$，可以发现 $a_k-a_i+a_j-a_k=a_j-a_i=a_j'-a_i'-2\Delta$，对于 $a_j-a_i$ 则也是减少了 $2\Delta$。不难发现当且仅当 $j=i+1$ 时，势能减少的最少，为 $2\Delta$，也就是每次消耗 $2\Delta$ 的势能获得 $\Delta$ 的价值。

于是得到结论：答案为 $\frac 12\sum_{1\le i\le j\le n}a_j-a_i$。剩下的部分是 trivial 的，随便用一个线段树维护一下即可。重要的还是如何转化这个问题。

code：

```cpp
int n,m,k=1e9,a[N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
struct node{
	int cnt,sum,ans;
	node operator+(const node &rhs)const{
		return {cnt+rhs.cnt,Mod(sum,rhs.sum),Mod(Mod(ans,rhs.ans),1ll*rhs.sum*cnt%mod)};
	}
};
struct SGT{
	node tr[M];
	int rt=0,cur,ls[M],rs[M];
	il void up(int u){
		tr[u]=tr[ls[u]]+tr[rs[u]];
	}
	void upd(int l,int r,int &u,int x,int y){
		if(!u){
			u=++cur;
		}
		if(l==r){
			tr[u].cnt+=y;
			tr[u].sum=1ll*(l%mod+mod)*tr[u].cnt%mod;
			tr[u].ans=1ll*(l%mod+mod)*((1ll*tr[u].cnt*(tr[u].cnt+1)/2)%mod)%mod;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			upd(l,mid,ls[u],x,y);
		}else{
			upd(mid+1,r,rs[u],x,y);
		}
		up(u);
	}
}T,R;
void Yorushika(){
	read(n,m);
	rep(i,1,n){
		read(a[i]);
		T.upd(1,k,T.rt,a[i],1),R.upd(-k,-1,R.rt,-a[i],1);
	}
	const int iv2=(mod+1)/2;
	while(m--){
		int x,y;read(x,y);
		T.upd(1,k,T.rt,a[x],-1),R.upd(-k,-1,R.rt,-a[x],-1);
		T.upd(1,k,T.rt,a[x]=y,1),R.upd(-k,-1,R.rt,-a[x],1);
		printf("%lld\n",1ll*Mod(T.tr[1].ans,R.tr[1].ans)*iv2%mod);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：hsaht2426 (赞：0)

#### 前言：

大力手摸+贪心。

#### 思路：

先想点**简单的**。

$n=2$：显然只能合并，$ans=|a_1-a_2|$。

$n=3$：考虑抽象出操作序列，大力贪心看看什么是不优的。

顺着题目操作的条件排序一下，把比较**特殊的** $(1,3)$ 操作拿出来分析，因为它可以被其他表示。具体地，考虑 $(a,b,c) \to (a+x,b,c-x)$ (此处并不一定有 $a+x \le b \le c-x$)的过程：可以变一部分为 $(a,b,c) \to (a+y,b-y,c) \to (a+y,b,c-y)$，使得代价增加 $y$。我们发现这其实是可以递推的，于是可以得到结论：如果 $x \le b-a$ 价值即可变成 $2x$。

如果 $x > b-a$？显然最终可以变成 $(b,b,a+c-b)$ 或 $(a+c-b,b)$，这个时候代价会增加 $2 \times \min(b-a,c-b)$。这时我们发现这个时候第一个数或第二个数操作是不重要的，因其值相等，所以后面同理可以继续推直到"消耗"完 $x$。所以我们得到了一些等价的操作，但可以使价值从 $x$ 变成 $2x$。

综上，对非相邻位置操作一定是不优的。并且事实上这个结论适用于原题面。所以直接考虑原版。

原版：

然后我们只需要处理这个价值。按操作分组，考虑所有 $(i-1,i)$ 操作的得分。分讨一下：

- $a_i \le \bar a$：此时所有 $i$ 以下的位置均有贡献，显然为$\sum\limits_{j=1}^{i-1} \bar{a} - a_j = \sum\limits_{j=i}^n a_j - \bar{a}$。

- $a_i > \bar a$：此时所有 $i$ 以上的位置均有贡献，显然为 $\sum\limits_{j=i}^n a_j - \bar{a}$。

直接加一起，即为 $\sum\limits_{i=1}^n i \times a_i - \frac{n+1}{2} \sum\limits_{i=1}^n a_i$。

最后考虑单点修改，这东西线段树/平衡树都可以随便维护。时间复杂度 $O((n+q) \log (n+q))$。

---

## 作者：loser_seele (赞：0)

官方题解写的太难看懂了。于是来写一个简单一点的版本。

首先我们需要证明：设 $ F(x)=\sum_{i=1}^n \sum_{j=i+1}^n \left| a_i-a_j \right| $，那么答案为 $ \frac{F(x)}{2} $。

不难发现题目中的数组顺序无关紧要，于是先从小到大排序。

定义一次操作为好的当且仅当操作两个相邻的元素。

我们发现：一次价值为 $ x $ 的操作至少使得 $ F(x) $ 减少 $ 2x $，而一次好的操作使得 $ F(x) $ 恰好减少 $ 2x $。

证明：首先显然不被操作的数之间相互不影响贡献，所以只讨论其他数与操作下标 $ i,j $ 之间的贡献。

对于第二种情况，我们发现其他的数到达 $ i,j $ 两个端点的总贡献没有改变，总是 $ a_i+a_j $，而减少的贡献只来自于 $ i,j $ 之间的距离变为 $ 0 $，得证。

第一种情况类似，但是由于假设 $ i,j $ 中间插入了数，发现这个数到达 $ i,j $ 的距离之和显然大于到达区间中点的距离的两倍（表示在数轴上之和不难理解，这里略去，或者写出代数证明也可以。），于是命题得证。

接下来我们证明经过若干次操作总能使得 $ F(x)=0 $。

这个更加简单，$ F(x)=0 $ 的条件是所有数相等，那么在这个条件达成之前必定存在某个下标相邻的数不一样，则操作后 $ F(x) $ 总会减小。

于是问题转化为了：支持单点修改和查询 $ F(x) $。

不带修的情况不难想，只需要维护 $ \sum \left| x-a \right| $ 即可，$ a $ 表示原数组中的元素。这个可以拆成 $ a \leq x $ 和 $ a>x $ 两种情况讨论，以下默认 $ a \leq x $。

发现这个维护一下 $ a \leq x $ 的数字和其出现次数即可，因为值域较大，用动态开点线段树即可解决。

单点修改同理，把一次修改操作拆成删除和加入即可。

时间复杂度同动态开点线段树，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long md=998244353;
long long n,q,sz[303030*60],sm[303030*60],a[303030],ans[303030*60];
int t,nwt,l[303030*60],r[303030*60];
void up(int k)
{
	sz[k]=sz[l[k]]+sz[r[k]];
	sm[k]=sm[l[k]]+sm[r[k]];
	sm[k]%=md;
	ans[k]=ans[l[k]]+ans[r[k]]+sm[r[k]]*sz[l[k]]%md+(md-sm[l[k]])*sz[r[k]]%md;
	ans[k]%=md;
}
void gx(int ll,int rr,int &x,int p,int v)
{
	if(x==0)
	{
		t++;
		x=t;
	}
	if(ll==rr)
	{
		sz[x]+=v;
		sm[x]+=(md+v)*p%md;
		sm[x]%=md;
		return;
	}
	int mid=(ll+rr)/2;
	if(p<=mid)
		gx(ll,mid,l[x],p,v);
	else
		gx(mid+1,rr,r[x],p,v);
	up(x);
}
int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		gx(1,1000000000,nwt,a[i],1);
	}
	for(int i=1;i<=q;i++)
	{
		long long x,y;
		cin>>x>>y;
		gx(1,1000000000,nwt,a[x],-1);
		a[x]=y;
		gx(1,1000000000,nwt,a[x],1);
		cout<<ans[1]*((md+1)/2)%md<<endl;
	}
}
```


---

