# [ARC169D] Add to Make a Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc169/tasks/arc169_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます． $ A $ の各要素は $ 0 $ 以上 $ N-1 $ 以下の整数です．

あなたは以下の操作を $ 0 $ 回以上行うことができます．

- $ A $ の中からちょうど $ M $ 個の要素を選ぶ． そして，選んだ要素の値をそれぞれ $ 1 $ 増加させる． 増加させたあとに値が $ N $ になっている要素があれば，その値を $ 0 $ に変更する．
 
あなたの目標は $ A $ を $ (0,1,\cdots,N-1) $ の順列にすることです． 目標が達成可能か判定し，可能ならば必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 250000 $
- $ 1\ \leq\ M\ \leq\ N-1 $
- $ 0\ \leq\ A_i\ \leq\ N-1 $
- 入力される値はすべて整数．
 
### Sample Explanation 1

以下のように操作すると $ 2 $ 回の操作で目標を達成できます． - 初期状態: $ A=(0,1,1) $ - $ 1 $ 回目の操作: $ A_1,A_2 $ を選んで操作を行い，$ A=(1,2,1) $ になる． - $ 2 $ 回目の操作: $ A_2,A_3 $ を選んで操作を行い，$ A=(1,0,2) $ になる． $ 2 $ 回未満の操作で目標を達成することはできないため，答えは $ 2 $ になります．

## 样例 #1

### 输入

```
3 2
0 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5 2
0 4 2 3 1```

### 输出

```
0```

## 样例 #3

### 输入

```
4 2
0 0 1 2```

### 输出

```
-1```

## 样例 #4

### 输入

```
20 15
5 14 18 0 8 5 0 10 6 5 11 2 10 10 17 9 8 14 4 4```

### 输出

```
10```

# 题解

## 作者：Aigony (赞：8)

[更好的阅读体验 qwq](https://www.cnblogs.com/ying-xue/p/arc169.html)

设序列 $A$ 操作得到未被取模的最终序列 $B$，那么 $B$ 应当满足如下条件：
- $B_i\ge A_i$；
- $B_i\bmod N$ 两两不同；
- 令 $S=\sum\limits_{i=1}^n (B_i-A_i)$，有 $S\bmod M=0$；
- $\max\{B_i-A_i\}\le \frac{S}{M}$。


考虑第三个条件，在一定的操作次数下 $\max\{B_i-A_i\}$ 越小越容易满足条件。将 $A$ 序列升序排序，最优的对应关系一定是将 $B$ 也升序排序。

发现答案只和 $S$ 的值有关，有结论：若有解，一定存在一种最优方案形如 $B=(x,x+1,\cdots ,x+N)$。

使用调整法证明。假设我们有一个最优的 $B$ 序列，且 $B_N-B_1>N$。那么令 $B_1\gets B_N-N,B_N\gets B_1+N$，依次对照上文的所有条件：

- 首先因为 $B_N-N>B_1$，新的 $B_1$ 比原来大。同时因为 $B_1>A_1,A_N-A_1<N$，有 $B_1+N>A_N$，满足条件 1。
- 加减 $N$ 不改变取模后的值。
- 总和没变，$S$ 不变。
- $B_N-A_N$ 一定变小。前者有 $B_N-A_N>B_N-N-A_1$，所以也变小，满足条件。

综上，这样调整后得到的新序列仍合法。

那么我们只需考虑最小化 $x$ 的值。

根据第一个条件可以得到 $x$ 的下界。第四个条件 $x$ 每增加 $1$，不等式左侧增加 $1$，右侧增加 $\frac{N}{M}$。因为 $N>M$，第四个条件也为 $x$ 提供了下界。

接下来令 $x$ 满足第三个条件即可，发现 $x$ 和 $x+N$ 是等价的，$x$ 可以直接枚举 $N$ 次。

时间复杂度是 $\mathcal{O}(n)$。

```cpp
#define int long long
const int N=2.5e5+5;
int n,m,a[N],sum,x;
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) x=max(x,a[i]-i+1);
	for(int i=1;i<=n;i++) sum+=(x+i-1)-a[i];
	bool flag=0;
	for(int i=0;i<=n;i++) if((sum+n*i)%m==0) {x+=i,sum+=n*i,flag=1;break;}
	if(!flag) {printf("-1\n");return 0;}
	int mx=0;
	for(int i=1;i<=n;i++) mx=max(mx,x+i-1-a[i]);
	while(mx>sum/m) mx+=m/__gcd(n,m),sum+=n*m/__gcd(n,m);
	printf("%lld\n",sum/m);
	return 0;
}
```

---

## 作者：Wuyanru (赞：6)

一道有趣结论题，但是感觉官方题解说的真的有点糊。

[题目链接](https://www.luogu.com.cn/problem/AT_arc169_d)。

## 题意

给定一个长度为 $ n $ 的数组 $ a_i $ 与一个数字 $ m $，你可以进行若干次操作：

选中 $ m $ 个数字，并将他们 $ +1 $，若有数字到达 $ n $，则将这个数字变为 $ 0 $。

求将 $ a $ 变为一个 $ 0\sim n-1 $ 的排列的最小次数，或输出无解。

$ 1\le n\le 2.5\times 10^5 $。

$ 1\le m<n $。

$ 0\le a_i<n $。

## 题解

我们假设 $ a_i $ 在值为 $ n $ 时不会变成 $ 0 $，并令最后第 $ i $ 个位置上的数为 $ b_i $，那么我们的最终目标是让 $ b_i\bmod n $ 互不相等。

设 $ s=\sum\limits_{i=1}^nb_i-a_i $，考虑 $ b $ 合法的条件：

1. $ m|s $；
2. $ \forall 1\le i\le n:a_i\le b_i $；
3. $ \forall 1\le i\le n:b_i-a_i\le \dfrac{s}{m} $。

看起来不好计算。

考虑在步数最小的情况下，我们求出一个 $ \sum b_i^2 $ 最小的 $ b $。

可以证明，这个 $ b $ 一定是 $ (x,x+1,\dots,x+n-1) $ 的一个排列，其中 $ x $ 为某个自然数，可以使用反证法来证明，证明如下：

设当前 $ b $ 合法，满足步数最小且 $ \sum b_i^2 $ 最小，若此时 $ b $ 不是上述所说的排列，则存在 $ b_i-b_j>n $。

令 $ b'_i\gets b_j+n $，$ b'_j\gets b_i-n $（注意这里赋值的 $ i,j $ 交换了）。

由于 $ b'^2_i+b'^2_j=b_j^2+b_i^2+2n^2+2nb_j-2nb_i=b_i^2+b_j^2+2n(n+b_j-b_i)<b_i^2+b_j^2 $，所以 $ \sum b_i^2 $ 会变小。

以前三个条件仍然满足：

1. $ b'_i+b'_j=b_j+n+b_i-n=b_i+b_j $，所以 $ s $ 不变，所以仍然有 $ m|s $；

2. $ b'_i=b_j+n\ge n>a_i $

   $ b'_j=b_i-n>b_j\ge a_j $

   所以仍然有 $ b'_i\ge a_i $，$ b'_j\ge a_j $；

3. $ b'_i-a_i=b_j+n-a_i<b_i-a_i\le \dfrac{s}{m} $ 

   $ b'_j-a_j=b_i-n-a_i<b_i-a_i\le \dfrac{s}{m} $

   所以仍然有  $ b'_i-a_i\le \dfrac{s}{m} $，$ b'_j-a_j\le \dfrac{s}{m} $。

综上所述，步数最小且 $ \sum b_i^2 $ 最小的 $ b $ 一定为 $ (x,x+1,\dots,x+n-1) $ 的排列的形式。

也就是说，我们只需要考虑 $ b $ 为 $ (x,x+1,\dots,x+n-1) $ 的排列的形式。

首先我们将 $ a_i $ 从小到大排序，不难发现，此时的 $ b $ 递增是一定是最优的。

所以我们只需要找出一个最小的 $ x $，使得 $ b_i=x+i-1 $ 的 $ b $ 满足上面的条件。

再次观察条件，发现条件 $ 2,3 $ 给出的是 $ x $ 的下界，设 $ p=\dfrac{n(n+1)}{2} $。

对于条件 $ 2 $，有 $ b_i\ge a_i\Longleftrightarrow x+i-1\ge a_i\Longleftrightarrow x\ge a_i-i+1 $。

对于条件 $ 3 $，有 $ b_i-a_i\le \dfrac{s}{m}\Longleftrightarrow x+i-1-a_i\le \dfrac{nx+p}{m}\Longleftrightarrow x\ge \left\lceil\dfrac{m(i-1-a_i)-p}{n-m}\right\rceil $。

条件 $ 1 $ 则给出了关于 $ x $ 的额外限制，设 $ g=\gcd(n,m) $。

$ m|s\Longleftrightarrow m|nx+p\Longleftrightarrow\exists k\in \mathbb{N}:km=nx+p\Longleftrightarrow \exists k\in \mathbb{N}:\dfrac{km}{g}=\dfrac{nx}{g}+\dfrac{p}{g}\Longleftrightarrow \dfrac{m}{g}|\dfrac{nx}{g}+\dfrac{p}{g} $。

首先，若 $ g\nmid p$，则无解；否则，可以暴力枚举，算出 $ x\bmod \dfrac{m}{g} $ 的值（不存在则无解）。

结合三个条件，便可以算出最小的 $ x $，便能算出最小的操作次数。

## 代码

```c++
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int a[250001];
ll s,ans;
int n,m;
int main()
{
    n=read(),m=read(),ans=-inf;
    for(int i=1;i<=n;i++) s+=(a[i]=read());
    sort(a+1,a+n+1);
    for(int i=n;i;i--) ans=max(ans-1,(ll)a[i]);
    for(int i=1;i<=n;i++)
    {
        ll A=(ll)n*(n-1)/2-s,B=(i-1)-a[i];
        ans=max(ans,(m*B-A+n-m-1)/(n-m));
    }
    ll C=(s-(ll)n*(n-1)/2%m+m)%m;int val=-1,g=__gcd(n,m);
    for(int i=0;i<m/g;i++) if((ll)n/g*i%(m/g)*g==C){ val=i;break;}
    if(val==-1){ printf("-1\n");return 0;}
    ans=(ans-val+(m/g)-1)/(m/g)*(m/g)+val;
    printf("%lld\n",((ll)n*(n-1)/2+ans*n-s)/m);
    return 0;
}
```

感谢观看！

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc169_d)

**题目大意**

> 给定 $a_1\sim a_n$，每次操作可以给 $m$ 个不同的 $ a_i$ 加一（在 $\bmod n$ 意义下），求至少几次操作能让 $a$ 变成 $0\sim n-1$ 的排列。
>
> 数据范围：$n\le 2.5\times 10^5$。

**思路分析**

考虑在不 $\bmod n$ 意义下确定最终的 $b_i$，要满足如下条件：

- $a_i\le b_i$。
- $b_i\bmod n$ 互不相同。
- 记 $S=\sum b_i-a_i$，那么 $m\mid S$。
- $\max \{b_i-a_i\}\le \dfrac Sm$。

首先只有第一个条件和 $b$ 的相对顺序有关，为了满足这个条件，显然同时将 $a,b$ 升序排列最优。

然后考虑第四个条件，对于一组合法解 $b_1\sim b_n$，如果 $b_n-b_1\ge n$，那么调整 $b_1\gets b_n-n,b_n\gets b_1+n$。

显然不影响条件一、二、三的合法性，且此时 $b_n-a_n$ 会变小，且 $b'_1-a_1=b_n-a_1-n<b_n-a_n$，因此 $\max\{b_i-a_i\}$ 也会变小。

因此这样调整一定更优，最终一定有 $b_n-b_1<n$，即 $b_i$ 是连续的一段，存在一个 $x$ 使得 $b_i=x+i-1$。

那么逐个满足条件即可，先找到 $\max a_i-i+1$，然后调整到最近的 $x$ 使得 $\dfrac{n(2x+n-1)}2\equiv \sum a_i\pmod m$。

找到此时的 $k=\max\{b_i-a_i\}$，如果 $k> \dfrac Sm$，那么接下来就会进行若干次调整，每次会令 $x$ 加上 $d=\dfrac{m}{\gcd(n,m)}$。

此时 $k$ 加上 $\dfrac m{\gcd(n,m)}$，且 $\dfrac Sm$ 加上 $\dfrac{n}{\gcd(n,m)}$，由于 $n>m$ 因此这个调整总能结束。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2.5e5+5;
int n,m,a[MAXN],g;
ll sum,k=0;
signed main() {
	scanf("%d%d",&n,&m),g=__gcd(n,m);
	for(int i=0;i<n;++i) scanf("%d",&a[i]),sum+=a[i];
	if((1ll*n*(n-1)/2-sum)%g) return puts("-1"),0;
	sort(a,a+n);
	for(int i=0;i<n;++i) k=max(k,(ll)a[i]-i);
	sum=(2*k+n-1)*n/2-sum;
	while(sum%m) ++k,sum+=n;
	ll mx=0,d=m/__gcd(n,m),c=n*d/m;
	for(int i=0;i<n;++i) mx=max(mx,k+i-a[i]);
	if(mx>sum/m) {
		ll cur=(mx-sum/m-1)/(c-d)+1;
		printf("%lld\n",sum/m+cur*c);
	} else printf("%lld\n",sum/m);
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

考虑去除 $A_i$ 对 $N$ 取模的限制，现在问题转化为了使得 $A_i \bmod N$ 的值两两不同。

首先我们考虑对于一个序列 $B$，$A$ 可以在经过若干次操作后得到其的充要条件是什么：

- $A_i \le B_i$
- $\sum\limits_{i}\left(B_i - A_i\right) \mid M$
- $\forall i \rightarrow B_i - A_i \le \frac{\sum\limits_{i}\left(B_i - A_i\right)}{M}$

我们将 $A$ 按升序排列，接下来我们尝试证明最优的 $B$ 一定是 $\left(x, x + 1, \cdots, x + N - 1\right)$ 经过重排后得到的。其中 $x$ 为 $B$ 序列的最小元素。

首先可以发现，满足上述性质的 $B$ 一定满足 $\sum B_i^2$ 最小。我们可以发现，若存在 $i, j$ 满足 $B_i - B_j > N$，那么执行 $B_i \leftarrow B_j + N, B_j \leftarrow B_i + N$（注意 $i, j$ 的交换）一定可以仍然使得方案合法且 $\sum B_i^2$ 更优。

进而我们得到了一个做法：枚举 $x$，找到最小的使得其合法的 $x$。其中合法的定义是通过 $x$ 得到的 $B$ 序列一定满足上述三个条件。

其中第一个条件限制了 $x$ 的下界。

第二个条件可以转化为：$\sum\limits_{1 \le i \le N}\left(i - 1 - A_i\right) + Nx \equiv 0 \pmod M$。因此我们可以枚举 $x$，直到其满足这个条件。

第三个条件同样限制了 $x$ 的最小值，因此若当前方案不满足第三个条件，我们尝试在满足前两个条件的基础上调整 $x$ 的取值使得其满足第三个条件。不难发现每一次调整的 $\Delta x$ 一定满足 $N \times \Delta x \equiv 0\pmod M$，因此可以得到最小的 $\Delta x = \frac{M}{\gcd\left(N, M\right)}$。在此基础上调整即可。

复杂度 $\mathcal{O}(N)$。

---

## 作者：HHH6666666666 (赞：0)

不会推结论？没关系。

首先将 $A$ 排序，显然我们可以假设在加的过程中 $A$ 中所有数的相对大小关系不变。如果不考虑取模的话，最终答案的 $A$ 一定严格单调递增且相邻元素之差为 $1$。那么我们只要确定 $A$ 中第一项即可确定整个序列。

构造序列 $B$，满足 $2 \leq i \leq n,B_{i-1}-B_i=1$，则 $A$ 可通过若干次操作到达 $B$ 当且仅当以下条件全部满足：

（令 $S=\sum\limits_{i=1}^{n} B_i-A_i$）

1. $1 \leq i \leq n, A_i \leq B_i$。

2. $m \mid S$。

3. $\max\limits_{i=1}^{n}B_i-A_i \leq \frac{S}{m}$。

第一与第二条显然，第三条是常见结论。

排除不可能满足条件 $2$ 的情况后，问题转化为如何找到最小的 $B_1$。首先，找出满足条件 $1$ 的 $B_1$ 的最小值，再找到不小于它且满足条件 $2$ 的最小值。假设这个值使得当前序列 $B$ 的和为 $S_0$，则根据条件 $2$，最小答案的和必为 $S_0+k\times\operatorname{lcm}(n, m)$。发现 $k$ 增大时条件 $3$ 不等号右侧增长速率大于左侧，二分查找这个 $k$ 即可。

```
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 2.5e5 + 10;

int n, m;
int a[MAXN];

signed main() {
	ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i], ++a[i];
    sort(a + 1, a + n + 1);
    int t = 0;
    for (int i = 1; i <= n; ++i) t = max(t, a[i] - i);
    ll h = 0, s = 0;
    for (int i = 1; i <= n; ++i) h = max<ll>(h, t + i - a[i]), s += t + i - a[i];
    bool f = false;
    ll temp = s;
    for (int j = 0; j <= n; ++j, temp += n) f |= temp % m == 0;
    if (!f) { cout << -1 << endl; return 0; }
    ll lcm = (ll) n * m / __gcd(n, m);
    int now = 0;
    while (s % m) ++now, s += n;
    ll l = 0, r = 1e9, step = lcm / m;
    while (l < r) {
        ll mid = (l + r) >> 1;
        if (mid * step + s / m >= h + mid * lcm / n + now) r = mid;
        else l = mid + 1;
    }
    cout << l * step + s / m << endl;
    return 0;
}

```

---

