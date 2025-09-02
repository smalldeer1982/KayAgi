# [AGC034C] Tests

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_c

高橋くんと青木くんは $ 1 $ から $ N $ までの番号がついたテストを受けようとしています。 二人はこのテストの結果を使って勝負することにしました。 具体的には、次のようにして勝敗を決めます。

- 高橋くんが各テスト $ i $ について、その重要度 $ c_i $ を決める。ただしこの値は $ l_i $ 以上 $ u_i $ 以下の整数である必要がある。
- $ \sum_{i=1}^{N}\ c_i\ \times $ (高橋くんのテスト $ i $ の点数) を $ A $, $ \ $ $ \sum_{i=1}^{N}\ c_i\ \times $ (青木くんのテスト $ i $ の点数) を $ B $ とする。 $ A\ \geq\ B $ なら高橋くんの勝ち、$ A\ <\ B $ なら青木くんの勝ち。

高橋くんはエスパーなので、青木くんがテスト $ i $ で $ b_i $ 点をとることがわかっています。

高橋くんはこのままだとすべてのテストで $ 0 $ 点をとってしまいますが、 $ 1 $ 時間勉強するごとに、好きなテストの点数を $ 1 $ だけ上げることができます。($ 1 $ 時間単位でしか勉強できません。) ただしテストはすべて **$ X $ 点満点**なので、 $ X $ より大きい点数にすることはできません。

高橋くんが勝つために必要な最小の勉強時間を出力してください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ X\ ≦\ 10^5 $
- $ 0\ ≦\ b_i\ ≦\ X $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ ≦\ l_i\ ≦\ u_i\ ≦\ 10^5 $ $ (1\ \leq\ i\ \leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

例えば次のようにするのが最適です。 - $ c_1\ =\ 3,\ c_2\ =\ 1 $ とする。 - テスト $ 1 $ で $ 100 $ 点、テスト $ 2 $ で $ 15 $ 点とるように勉強する。 このとき $ A\ =\ 3\ \times\ 100\ +\ 1\ \times\ 15\ =\ 315 $, $ B\ =\ 3\ \times\ 85\ +\ 1\ \times\ 60\ =\ 315 $ なので高橋くんが勝ちます。

## 样例 #1

### 输入

```
2 100
85 2 3
60 1 1```

### 输出

```
115```

## 样例 #2

### 输入

```
2 100
85 2 3
60 10 10```

### 输出

```
77```

## 样例 #3

### 输入

```
1 100000
31415 2718 2818```

### 输出

```
31415```

## 样例 #4

### 输入

```
10 1000
451 4593 6263
324 310 6991
378 1431 7068
71 1757 9218
204 3676 4328
840 6221 9080
684 1545 8511
709 5467 8674
862 6504 9835
283 4965 9980```

### 输出

```
2540```

# 题解

## 作者：Mophie (赞：9)

首先显然 $s$ 越大能构造出的答案越大。

因此答案是单调的，考虑二分。

首先因为 $c_i$ 是可以在 $[l_i, r_i]$ 中取的。

那么因为要使得 $\sum^{n}_{i = 1}c_i(a_i - b_i)$ 最大。假设 $\{a_i\}$ 已经求出，那么当 $a_i \le b_i$ 时 $c_i=l_i$，$a_i > b_i$ 时 $c_i = r_i$ 时是最优的。

因此 $c_i$ 也就定了下来。

然后又发现一个性质：有且只有一个 $a_i$ 能取 $0, x$ 之外的值。

这个也很好说明。因为若有两个 $i,j$ 中 $a_i, a_j$ 都不取 $0, x$ 的话，考虑 $a_i, b_i$ 的大小比较。

若 $b_i > a_i$，则将 $a_i-1,a_j+1$ 必然不劣。

若 $b_i \le a_i$，则将 $a_i+1,a_j-1$ 必然不劣。

这两个的话证起来都极其容易，故不多赘述。

所以最优的必然是一堆 $x$，一堆 $0$，还有一个 $a_i$ 取余数。

那么就枚举那个取余数的 $i$，其他的贪心即可。

详细代码如下：

```cpp
/*
    长弓背负，仙女月鹫，
	梦中徐来，长夜悠悠。
	今宵共君，夜赏囃子，
	盼君速归，长夜悠悠。
	睡意袭我，眼阖梦徭，
	睡意袭我，意归襁褓。
	手扶卓揭，仙女水狃，
	盼君速归，长夜悠悠。
	今宵共君，戏于西楼，
	盼君速归，长夜悠悠。
	睡意袭我，涟锜池留，
	睡意袭我，意归海角。
					                  ——《ever17》
*/
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int sum = 0, nega = 1;
	char ch = getchar();
	while (ch > '9'||ch < '0')
	{
	    if (ch == '-') nega = -1;
		ch = getchar();
	}
	while (ch <= '9'&&ch >= '0') sum = sum * 10 + ch - '0', ch = getchar ();
	return sum * nega;
}
const int N = 1e5 + 9;
struct point
{
	int l, u, b, val;
	// val -> 对答案的差值贡献最大 
}a[N];
int n, x, res, sum[N];
//sum -> 前缀和优化， res -> 全部取 0 的值 
inline int get_val(int pos, int p)
{
	if(p <= a[pos].b) return a[pos].l * (p - a[pos].b);
	else return a[pos].u * (p - a[pos].b);
}//取 p 的值 
inline bool cmp(point xxx, point yyy)
{
	return xxx.val > yyy.val;
}
inline int check(int p)
{
	int pep = p / x, tot = p % x, now, ans = res;
	// pep -> 能取 x 的个数
	// tot -> 取余数
	// ans -> s = p 时的最值 
	if(pep == n) return sum[pep] + res;  
	for (int i = 1; i <= n; i++)
	{
		now = 0;
		if(i <= pep) now = res + sum[pep + 1] - get_val(i, x) + get_val(i, tot);
		else now = res + sum[pep] - get_val(i, 0) + get_val(i, tot);
		ans = max(ans, now);
	}
	return ans;
}
signed main()
{
	n = read(), x = read();
	for (int i = 1; i <= n; i++) a[i].b = read(), a[i].l = read(), a[i].u = read();
	for (int i = 1; i <= n; i++) a[i].val = get_val(i, x) - get_val(i, 0), res += get_val(i, 0);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].val;
	int l = 0, r = 0, ans = 0;
	for (int i = 1; i <= n; i++) r += a[i].b;
	// 显然答案最大为 bi 的和 
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid) >= 0) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}


```



---

## 作者：Rainybunny (赞：6)

&emsp;&emsp;[更好的阅读体验 owo~](https://www.cnblogs.com/rainybunny/p/14284256.html)

# $\mathcal{Description}$

&emsp;&emsp;[Link](https://www.luogu.com.cn/problem/AT4993).

&emsp;&emsp;给定非负整数序列 $\{l_n\},\{r_n\},\{b_n\},X$，求最小的 $s$，使得存在非负整数序列 $\{a_n\},\{c_n\}$，满足 $a_i\le X$，$\sum_{i=1}^na_i=s$，$c_i\in[l_i,r_i]$，且
$$
\sum_{i=1}^nc_i(a_i-b_i)\ge0
$$
&emsp;&emsp;所有输入均 $\le10^5$。

# $\mathcal{Solution}$

&emsp;&emsp;显然二分 $s$，仅需做到检测某个 $s$ 是否合法。下令 $w=\sum_{i=1}^nc_ia_i$。

&emsp;&emsp;假设 $\{a_n\}$ 已经确定，那么所有满足 $a_i\ge b_i$ 的 $c_i=r_i$，其余 $c_i=l_i$。考虑初始时所有 $a_i=0,c_i=l_i$，现在把 $s$ 个 $1$ 挨个加到一些 $a_i$ 上。当 $a_i<b_i$ 时，对 $w$ 贡献 $l_i$（此时 $c_i$ 仍取 $l_i$）；当 $a_i=b_i$ 时，对 $w$ 贡献由  $l_i$ 转为 $r_i$（$c_i$ 变成 $r_i$）；继续增加，对 $w$ 贡献 $r_i$。最终仅需比较 $w$ 和 $\sum_{i=1}^nl_ib_i$ 的大小。

&emsp;&emsp;所以问题抽象为：有 $n$ 个分段函数 $f_{1..n}(x)$，满足
$$
f_i(x)=\begin{cases}l_ix&x\in[0,b_i]\cap\mathbb N\\
l_ib_i+r_i(x-b_i)&x\in(b_i,X]\cap\mathbb N
\end{cases}
$$
&emsp;&emsp;仅需钦定 $\{x_n\}$，使得 $\sum_{i=1}^nf_i(x_i)$ 取最大。

&emsp;&emsp;考虑贪心，不难证明：至多有一个 $0<x_i<X$。直接枚举哪一个 $0<x_i<X$，贪心地选取最大的 $f_i(X)$，即可 $\mathcal O(n)$ 检测。最终复杂度 $\mathcal O(n\log\sum_{i=1}^nb_i)$。

## $\mathcal{Code}$

```cpp
/* Clearink */

#include <cstdio>
#include <algorithm>

#define rep( i, l, r ) for ( int i = l, repEnd##i = r; i <= repEnd##i; ++i )
#define per( i, r, l ) for ( int i = r, repEnd##i = l; i >= repEnd##i; --i )

inline int rint () {
	int x = 0, f = 1; char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () ) f = s == '-' ? -f : f;
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = x * 10 + ( s ^ '0' );
	return x * f;
}

typedef long long LL;

const int MAXN = 1e5;
int n, x, b[MAXN + 5], l[MAXN + 5], r[MAXN + 5], ord[MAXN + 5];
LL full[MAXN + 5];

inline LL contr ( const int i, const int s ) {
	return s <= b[i] ? 1ll * s * l[i]
		: 1ll * l[i] * b[i] + 1ll * ( s - b[i] ) * r[i];
}

inline void init () {
	std::sort ( ord + 1, ord + n + 1, []( const int i, const int j ) {
		return contr ( i, x ) > contr ( j, x );
	} );
	rep ( i, 1, n ) full[i] = full[i - 1] + contr ( ord[i], x );
}

inline LL calc ( const LL scr ) {
	/*
	 * let's come up with a greedy algorithm!
	 * */
	int fcnt = scr / x, rest = scr % x;
	LL ret = 0;
	rep ( i, 1, n ) { // score on exam <ord[i]> is <rest>.
		LL cur = contr ( ord[i], rest );
		if ( i > fcnt ) cur += full[fcnt];
		else cur += full[fcnt + 1] - contr ( ord[i], x );
		ret = cur > ret ? cur : ret;
	}
	return ret;
}

int main () {
	n = rint (), x = rint ();
	LL sum = 0, sb = 0;
	rep ( i, 1, n ) {
		ord[i] = i;
		b[i] = rint (), l[i] = rint (), r[i] = rint ();
		sum += 1ll * b[i] * l[i], sb += b[i];
	}
	init ();
	LL lef = 0, rig = sb;
	while ( lef < rig ) {
		LL mid = lef + rig >> 1;
		if ( calc ( mid ) >= sum ) rig = mid;
		else lef = mid + 1;
	}
	printf ( "%lld\n", lef );
	return 0;
}

```


---

## 作者：Super_Cube (赞：1)

# Solution

为了让值更大，肯定是当 $a_i\ge b_i$ 时 $c_i$ 取 $r_i$，否则取 $l_i$。

设 $f_i(x)$ 表示当 $a_i=x$ 时的贡献，有 $f_i(x)=\begin{cases}l_ix&x\le b_i\\r_i(x-b_i)+l_ib_i&x>b_i\end{cases}$，把询问改为 $\sum f_i(x)\ge\sum l_ib_i$。

如果存在 $i,j$ 使得 $a_i,a_j$ 的取值都不为 $0$ 或 $X$ 是不优的，因为选择 $c$ 更大的位置使其 $a$ 加一，另外一个位置减一会使得和更大。所以按照 $f_i(X)$ 从大到小排序。

通过二分找到 $s$。假设现在正在判断 $m$ 是否合法，枚举 $a_i=m\bmod X$ 的位置计算 $\sum f_i(x)$ 的最大值，看是否不小于 $\sum l_ib_i$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
int m;
struct node{
	int b,l,r;
	inline ll calc(int x)const{
		return x<=b?1ll*l*x:1ll*r*(x-b)+1ll*l*b;
	}
	inline bool operator<(const node&_)const{
		return calc(m)>_.calc(m);
	}
}a[100005];
ll s[100005];
int n;
ll S;
inline bool check(ll lim){
	static int x,y;
	if((x=lim/m)>=n)return s[n];
	y=lim-x*m;
	static ll res;res=0;
	for(int i=1;i<=x;++i)
		res=std::max(res,s[x+1]-(s[i]-s[i-1])+a[i].calc(y));
	for(int i=x+1;i<=n;++i)
		res=std::max(res,s[x]+a[i].calc(y));
	return res>=S;
}
ll l,r,ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d%d%d",&a[i].b,&a[i].l,&a[i].r),S+=1ll*a[i].l*a[i].b;
	std::stable_sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i].calc(m);
	r=1e10;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：小木虫 (赞：1)

### Preface  
一道比较好的朴素思维题。  
### Problem  
给定非负整数序列 $\{l_n\},\{r_n\},\{b_n\},X$，求最小的 $s$，使得存在非负整数序列 $\{a_n\},\{c_n\}$，满足 $a_i\le X$，$\sum_{i=1}^na_i=s$，$c_i\in[l_i,r_i]$，且
$$
\sum_{i=1}^nc_i(a_i-b_i)\ge0
$$
所有输入均 $\le10^5$。
### Solution  
首先你发现，$s$ 若变大显然不劣，则题目中要求的条件有可二分性，所以我们二分转 check。  
然后你发现 $l,r$ 的决策很弱智，显然是 $(a_i-b_i)<0$ 的时候选择 $l$，否则选择 $r$。  

我们先将负的贡献整体拆出来，即 $\sum_{i=1}^n l_ib_i$。  
则我们发现，对于一个元素 $i$，定义 $f_i(x)$ 为当 $a_i=x$ 时该元素对于条件的贡献。  

则有：  
$$f_i(x)=l_i\times \min(b_i,x)+r_i\times \max(x-b_i,0)$$  
这显然是一个分段函数，接下来我们考虑如何分配 $s$ 这个总和。  
考虑调整，对于两个元素 $i,j$，我们每次使 $a_i-1,a_j+1$ 或 $a_i+1,a_j-1$。  

容易发现的是，由于这是一个变陡的分两段的函数，我们可以直接对其进行分类讨论：  

若目前 $f_i$ 的取值在缓坡上，且 $f_j$ 的取值在陡坡上：  
若 $l_i<r_j$，则一直做 $a_i-1,a_j+1$ 是更优的。  
若 $l_i>r_j$，由于 $l\leq r$，则一直做 $a_i+1,a_j-1$ 是更优的。  

若目前 $f_i$ 的取值在陡坡上，且 $f_j$ 的取值在缓坡上：  
由于 $i,j$ 不区分，这种情况和上面的讨论是对称的。  

则我们知道，若我们目前的 $a$ 可以做一次上述操作，或者说存在 $i,j$，使得 $a_i>0$ 并且 $a_j<x$，则这种情况一定不是最优的。  

然后我们发现了一个极好的限制：$a$ 一定由若干个 $0$，若干个 $x$，以及最多一个不属于以上两者的元素组成。  

那么我们发现这个另类的元素的大小是一定的，即 $s\mod x$，并且 $a_i$ 取值为 $x$ 的元素的个数为 $\lfloor \frac{s}{x}\rfloor$。  
我们可以枚举这个另类的元素是哪个，然后排序后贪心地选取 $x$ 的取值在哪个元素上。  

时间复杂度为 $O(n\log \sum b_i)$。  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,x,l[N],r[N],b[N],id[N];
int f(int a,int X){return l[a]*min(b[a],X)+r[a]*max(X-b[a],0ll);}
bool cmp(int a1,int a2){return f(a1,x)>f(a2,x);}
bool check(int s){
	int R=s%x,m=min(n,s/x);
	int sum=0;
	for(int i=1;i<=m;i++)
		sum+=f(id[i],x);
	int Max=sum;
	for(int i=1;i<=m;i++)
		Max=max(Max,f(id[i],R)-f(id[i],x)+f(id[m+1],x)+sum);
	for(int i=m+1;i<=n;i++)
		Max=max(Max,f(id[i],R)+sum);
	sum=Max;
	for(int i=1;i<=n;i++)
		sum-=l[i]*b[i];
	return sum>=0;
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++)
		cin>>b[i]>>l[i]>>r[i],id[i]=i;
	sort(id+1,id+1+n,cmp);
	int l=0,r=1e18;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}cout<<l;
	return 0;
}

```


---

## 作者：DJRzjl (赞：1)

显然二分 $s$，然后我们仅需判断某个 $s$ 是否合法，也就是求此时 $w=\sum_{i=1}^n(a_i-b_i)c_i$ 的最大值是否大于等于 $0$。

假设 $a$ 已经确定，那么显然满足 $a_i\ge b_i$ 的 $i$ 取 $c_i=r_i$，其余 $c_i=l_i$。

考虑开始所有 $a_i$ 均为 $0$，所以 $c_i$ 均为 $l_i$，$w=-\sum_{i=1}^nl_ib_i$，把 $s$ 个 $1$ 依次加进去。对于某个 $a_i$ 变为 $a_i+1$，当：

- $a_i < b_i$，此时 $w$ 加上 $l_i$；
- $a_i=b_i$，此时 $c_i$ 转为 $r_i$，$i$ 对 $w$ 的贡献突变为 $r_i$，而原本 $i$ 对 $w$ 的贡献为 $-l_ib_i+l_ib_i=0$，所以相当于在原贡献上加 $r_i$；
- $a_i > b_i$，此时 $w$ 加上 $r_i$。

于是不断给某个 $a_i$ 加一，$w$ 的变化为 $+l_i,+l_i,\cdots,+r_i,+r_i$。$i$ 对 $w$ 的贡献关于 $a_i$ 可以看作一个分段函数，两段均为一次函数且第二段斜率大于第一段。

即有 $n$ 个分段函数 $f_{1..n}(x)$：
$$
f_i(x)=\begin{cases} l_i~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~x\in[0,b_i]\cap \mathbb Z\\ l_ib_i+r_i(x-b_i)~~~~~~~~~~x\in(b_i,d]\cap\mathbb Z \\ \end{cases}
$$
不难发现 $f_i(x)$ 就是 $i$ 对 $w$ 贡献加上常数 $l_ib_i$，而 $\sum_{i=1}^n f_i(x_i)=w+\sum_{i=1}^nl_ib_i$。

然后我们仅需钦定 $x_{1,2,\cdots n}$，和为 $s$，使最后 $\sum_{i=1}^n f_i(x_i)$ 最大，判断其是否大于等于 $\sum_{i=1}^nl_ib_i$，这就等同于判断 $w_{max}$ 是否大于等于 $0$。

可以证明，最多存在一个 $i$，使得 $0<a_i<d$，而其它的要么取 $a_i=d$，要么取 $a_i=0$。

因为若存在两个这样的 $i$，我们显然可以通过调整其中一个加一，另一个减一，使他们对 $w$ 的贡献和更大。

贪心地考虑，显然我们优先让 $f_i(d)$ 最大的 $i$ 满足 $a_i=d$，直到剩余的 $s$ 小于 $d$，然枚举某个 $a_i=s$ 计算最大值即可。 



---

## 作者：Unnamed114514 (赞：0)

显然 $a_i$ 变大一定不劣，考虑二分 $s$。

首先 $c_i$ 肯定是两个端点之一，假设已经确定 $a_i$，不妨得到 $c_i$ 的取值。

- 若 $a_i\le b_i$，$c_i$ 取 $l_i$。

- 若 $a_i>b_i$，$c_i$ 取 $r_i$。

**Lemma**：至多存在一个 $a_i$ 满足 $a_i\ne X,a_i\ne 0$。

**Proof**：反证法。不妨假设有 $i,j$ 且 $a_i\ne0,a_j\ne 0$，容易发现一个增一个减贡献一定不劣，此时一定会存在一个数变成 $X$ 或变成 $0$。

对于剩下的 $s\bmod X$，可以用同样的方法证明都会施加到同一个数上，枚举这个数，然后用前缀和分别算取 $0$ 的和取 $X$ 的即可。

---

## 作者：LiveZoom (赞：0)

这题显然是二分 $s$，另外两篇题解也说到了，这里我想再详细解释一下二分里面的 check 函数怎么写。

- ## 结论证明

这题有一个结论：当 $\{a_n\}$ 取最优解时，那么这个序列中只有一个数不等于 $0$ 也不等于 $X$。

证明：

> 令 $F=\sum\limits_{i=1}^{n}{c_i(a_i-b_i)}$。

> 假设 $\{a_n\}$ 有两个数 $a_i$ 和 $a_j$，使得他们都不等于 $0$ 和 $X$。那么不妨设 $c_i\leq c_j$。

> 此时让 $a_i-1$，$a_j+1$，序列总和不变，而 $\Delta F=c_j-c_i\geq 0$，所以这么变化会使答案更优。

> 然后重复这个操作，直到 $a_i$ 和 $a_j$ 中有一个到达 $0$ 或 $X$ 时，就是最优的。

> 这个时候只有最多 $1$ 个数不等于 $0$ 也不等于 $X$。

然后这个结论就证完了，这道题目也就做完一大半了。

还有一个小结论就是：当 $a_i\geq b_i$ 时，$c_i=r_i$。否则 $c_i=l_i$。这个很显然，就不证了。

- ## 二分函数写法

令 $r=s \bmod x, q=\bigg\lfloor\dfrac{s}{x}\bigg\rfloor$。

首先可以假设所有的 $a_i$ 均等于 $0$，然后把 $a_i$ 从 $0$ 变到 $x$ 的变化量数组求出来，然后一一枚举哪个 $a_i=r$。

这时如果 $i\leq q$，则需要从 $1\sim q+1$ 中先减去 $\Delta_i$，再加上新的 $\Delta_i=c_i\times(r-b_i)$，最后这个和就是总的 $\Delta$。

否则就只需要让 $1\sim q$ 的和加上 $\Delta_i=c_i\times(r-b_i)$ 就是总的 $\Delta$。

还有，注意特判 $q=n$ 的情况。

代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define db(x) cerr << #x << '=' << x << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define dbg debug("*** Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)

using namespace std;

using ll = long long;

const int kMaxN = 1e5 + 5;

struct Node {
  ll c, d, yy, b, l, r;
} a[kMaxN] ;

int n, x;
int b[kMaxN], l[kMaxN], r[kMaxN];
ll yy[kMaxN], sum[kMaxN], c[kMaxN], d[kMaxN];

bool cmp(Node a, Node b) {
  return a.yy > b.yy;
}

bool check(ll s) {
  int q = s / x, rr = s % x; ll ss = 0, ret = -1e18;
  for (int i = 1; i <= n; ++i) {
    a[i].c = 1ll * l[i] * (-b[i]); // 这个就是当 a[i] 取 0 的值。
    a[i].d = 1ll * r[i] * (x - b[i]); // 这个则是当 a[i] 取 x 的值。
    a[i].yy = a[i].d - a[i].c; // 这个是增加量
    a[i].b = b[i];
    a[i].l = l[i];
    a[i].r = r[i];
    ss += a[i].c;
  }
  sort(a + 1, a + 1 + n, cmp);
  for (int i = 1; i <= n + 1; ++i) {
    sum[i] = sum[i - 1] + a[i].yy; // 这个就是增加量数组的前缀和
  }
  if (q == n) return ss + sum[n] >= 0; // 注意特判
  if (s == 0) return ss >= 0;
  for (int i = 1; i <= n; ++i) {
    ll tmp = 1ll * (rr <= a[i].b ? a[i].l : a[i].r) * (rr - a[i].b), kk = 0; // tmp 表示当 a[i]=r 时，c[i]*(a[i]-b[i]) 的值
    if (i <= q) {
      kk = (sum[q + 1] - a[i].yy) + (tmp - a[i].c) + ss; // tmp - a[i].c 就是当前的增加量
    } else {
      kk = sum[q] + (tmp - a[i].c) + ss;
    }
    ret = max(ret, kk);
  }
  return ret >= 0;
}

int main() {
  cin >> n >> x;
  for (int i = 1; i <= n; ++i) {
    cin >> b[i] >> l[i] >> r[i];
  }
  ll L = -1, R = 1ll * n * x + 1, res;
  while (L + 1 < R) {
    ll mid = (L + R) >> 1;
    if (check(mid)) R = res = mid;
    else L = mid;
  }
  cout << res << endl;
  return 0;
}
```

---

