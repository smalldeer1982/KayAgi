# [AGC027B] Garbage Collector

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc027/tasks/agc027_b

すぬけ君は掃除ロボットを使って部屋を掃除することにしました。

数直線上に $ N $ 個のゴミが落ちています。 左から $ i $ 番目のゴミは位置 $ x_i $ にあります。 これらのゴミを位置 $ 0 $ にあるゴミ箱に入れたいです。

ゴミの位置に関して、$ 0\ <\ x_1\ <\ x_2\ <\ ...\ <\ x_{N}\ \leq\ 10^{9} $ が成立します。

掃除ロボットははじめ位置 $ 0 $ にいます。ロボットは数直線上を自由に動くことができ、ゴミのある位置にいくとゴミを拾うことができます。 ゴミは同時に何個でも運ぶことでき、ゴミ箱の位置に行くとゴミをゴミ箱に入れることができます。ゴミをゴミ箱以外の場所に置くことは許されません。

ロボットがゴミを拾う、あるいは($ 1 $ 個以上の)ゴミをゴミ箱に入れるとき $ X $ だけエネルギーを消費します。ゴミをゴミ箱に入れるときに消費するエネルギーはゴミの個数にかかわらず $ X $ です。 また、ロボットが $ k $ 個のゴミを運んでいるとき、距離 $ 1 $ だけ移動するのに $ (k+1)^{2} $ だけエネルギーを消費します。

$ N $ 個のゴミを全てゴミ箱に入れるために必要なエネルギーの最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^{5} $
- $ 0\ <\ x_1\ <\ ...\ <\ x_N\ \leq\ 10^9 $
- $ 1\ \leq\ X\ \leq\ 10^9 $
- 与えられる入力は全て整数

### 部分点

- $ N\ \leq\ 2000 $ を満たすデータセットに正解した場合、$ 400 $ 点が与えられる。

### Sample Explanation 1

\- $ 10 $ のエネルギーを消費して、位置 $ 10 $ に移動する - $ 100 $ のエネルギーを消費して、ゴミを取る - $ 36 $ のエネルギーを消費して、位置 $ 1 $ に移動する - $ 100 $ のエネルギーを消費して、ゴミを取る - $ 9 $ のエネルギーを消費して、位置 $ 0 $ に移動する - $ 100 $ のエネルギーを消費して、$ 2 $ つのゴミをゴミ箱に入れる このように行動したとき、消費したエネルギーは $ 10+100+36+100+9+100=355 $ となります。

## 样例 #1

### 输入

```
2 100
1 10```

### 输出

```
355```

## 样例 #2

### 输入

```
5 1
1 999999997 999999998 999999999 1000000000```

### 输出

```
19999999983```

## 样例 #3

### 输入

```
10 8851025
38 87 668 3175 22601 65499 90236 790604 4290609 4894746```

### 输出

```
150710136```

## 样例 #4

### 输入

```
16 10
1 7 12 27 52 75 731 13856 395504 534840 1276551 2356789 9384806 19108104 82684732 535447408```

### 输出

```
3256017715```

# 题解

## 作者：WitheredZeal (赞：2)

## 题意  

一个数轴上有 $n$ 个垃圾，它们的位置分别为 $x_1,x_2,…,x_n(0<x_1<x_2<…<x_n\le10^9)$，有一个机器人开始时在位置 $0$ 上，它每个时刻可以选择左右移动或者捡起一个垃圾，当它回到位置 $0$ 时可以把手上的垃圾都扔掉。

当机器人手上有 $k$ 个垃圾时，走 $1$ 的距离需要消耗的 $(k+1)^2$ 的能量，机器人单次捡垃圾或者丢垃圾都需要 $x$ 的能量。

求机器人把所有垃圾都扔到垃圾桶里最少需要多少能量。

$n \le 2 \times 10^5$

## 题解  
  


首先假设我们从位置 $0$ 出发**一次性**捡了 $m$ 个垃圾，位置分别是 $p_1,p_2 \cdots p_m$。  
显然最优方案是，先走到 $p_m$，然后往前走，经过一个垃圾就捡起来。  

简要证明：考虑每段 $p_i \to p_{i+1}$ 和 $p_{i+1} \to p_i$，一定至少经过 $2$ 次，而 $p_{i+1} \to p_i$ 的最后一次经过时，手上一定至少有 $i+1$ 及后面的所有垃圾，因此该方法是下界。  

观察一下它走的每段路程的权值，以 $m=5$ 为例：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jvej4hb9.png)  
黄色的即为多出来需要走的路的权值。  
实际上是 $6p_1 + 4p_2 + 2p_3$，即为 $2\sum _{i=1}^{m-2}i p_{m-1-i}$

现在假设我们已经确定了，我们总共只丢了 $k$ 次垃圾，那么少用的 $x$ 已经确定了，我们需要最小化我们多走的能量。  
可以证明，答案就是，将下标模 $k$ 同余的垃圾都分为一组，然后一次性拿掉。  

简要证明：考虑我们一定试图让下标考后的坐标，系数尽量小。因此从后往前的系数应该依次为 $2k$ 个 $0$，$k$ 个 $2$，$k$ 个 $4$……  


我们枚举 $k$ 就能得到一个 $O(n^2)$ 的做法了，要是在正式比赛中就能获得 [400 分](https://atcoder.jp/contests/agc027/submissions/26504014)的好成绩了！  

部分分代码：  
```cpp
int n,X,ans,res;
int x[N];
signed main()
{
	rd(n);rd(X);res=inf;ans=n*X;
	for (int i=1;i<=n;i++) rd(x[i]),ans+=5*x[i];
	reverse(x+1,x+n+1);
	for (int k=1;k<=n;k++)
	{
		int tmp=k*X;
		for (int i=1;i<=n;i++) tmp+=2*max((i-1)/k-1,0LL)*x[i];
		res=min(res,tmp);
	}
	cout<<ans+res<<endl;
}
```
-------------

这个做法太拉了，我们要试图去优化它。  

我们观察上面部分分的代码，里面有这么一个东西：  
`for (int i=1;i<=n;i++) tmp+=2*max((i-1)/k-1,0LL)*x[i];`  
但是我们想，所有的 $\lfloor  \frac i k \rfloor$ 是不是总共只会变化不超过 $O(n \sqrt n)$ 次？  
那么我们当 $k$ 改变的时候，直接继承上一次的答案，再把需要改变的给改变了，是不是就行了？  

总复杂度 $O(n \sqrt n)$。  

然而，直接这么写[似乎被卡常了](https://atcoder.jp/contests/agc027/submissions/26504186)。 

---------------

我们来试图优化一下常数：  

我们求分成 $k$ 组时 $tmp-kX$。  
将 $x$ 数组 reverse 后，有它 $ =2  \sum _{i=1}^n \max(\lfloor \frac {i-1} k \rfloor-1,0) x_i = 2(\sum _{i=1}^n \lfloor \frac {i-1} k \rfloor x_i - \sum _{i=k+1}^n x_i)$  
我们需要干的就是快速求出 $t_k =\sum _{i=1}^n \lfloor \frac{i-1} k \rfloor x_i$。  

我们不放入 `vector` 里面，而是差分后直接算，这样常数会小一点。  

[然而它 WA 了](https://atcoder.jp/contests/agc027/submissions/26505105)。  

----------------

为什么会 WA 呢，我们把第 13 个测试点下载下来看看，本地开 `-fsanitize=undefined` 运行一下。  

`runtime error: signed integer overflow: 135806551569375 + 9223312156527645800 cannot be represented in type 'long long int'`  

居然爆 `long long` 了，被埋伏了一手。  

我们可以用 `__int128`，但是这样可能就会因为常数太大而过不去了。  

毛咕咕一下，发现这种情况下 $k$ 不可能很小，那么特判一下就过了。

严谨的下界不是很好估计，下面这份代码能 AC 但是可以叉掉。   

```cpp

int n,X;
long long ans,res;
int x[N],a[N];
long long s[N],t[N];
signed main()
{
	rd(n);rd(X);res=inf;ans=1ll*n*X;
	for (int i=1;i<=n;i++) rd(x[i]),ans+=5ll*x[i];
	reverse(x+1,x+n+1);
	for (int i=0;i<n;i++) for (int j=1;j<=i;j=(i/(i/j))+1) if (n<=3000 || j>=10) t[j]+=1ll*i/j*x[i+1],t[i/(i/j)+1]-=1ll*i/j*x[i+1];
	for (int i=1;i<=n;i++) t[i]+=t[i-1];
	for (int i=1;i<=n;i++) s[i]=s[i-1]+x[i];
	for (int k=1;k<=n;k++)
	{
		if (n>3000 && k<10) continue;
		long long tmp=1ll*k*X+2ll*(t[k]-(s[n]-s[k]));
		res=min(res,tmp);
	}
	cout<<ans+res<<endl;
}
```
-----------------

但是上面这个做法还是不够优秀，我们还可以继续优化。  

实际上这个做法应该比上面那个做法更简单，是我菜了。  

我们可以直接计算 $t_k$ 的。  

回忆一下：$t_k =\sum _{i=1}^n \lfloor \frac{i-1} k \rfloor x_i$。  
这个 $\lfloor \frac {i-1} k\rfloor $ 只有 $\lfloor \frac n k\rfloor$ 种取值，我们可以枚举它，然后相当于算一段区间的和。  
前缀和优化之后复杂度是调和级数 $O(n \log n)$。  

```cpp
__int128 n,X;
__int128 ans,res;
__int128 x[N],a[N];
__int128 s[N*2],t[N];
signed main()
{
	rd(n);rd(X);res=inf;ans=1ll*n*X;
	for (__int128 i=1;i<=n;i++) rd(x[i]),ans+=5ll*x[i];
	reverse(x+1,x+n+1);
	for (__int128 i=1;i<=n;i++) s[i]=s[i-1]+x[i];
	for (__int128 k=1;k<=n;k++)
	{
		for (__int128 i=1;i<=n/k;i++) t[k]+=i*(s[min(1ll*i*k+k,1ll*n)]-s[i*k]);
		__int128 tmp=1ll*k*X+2ll*(t[k]-(s[n]-s[k]));
		res=min(res,tmp);
	}
	wt(ans+res);
}
```


---

## 作者：AC_love (赞：0)

考虑如果我们要走一次收集一些垃圾，怎么收集最优。

显然应该先走到最右面，捡起最右面的垃圾，然后往左走，依次收集路上的所有垃圾即可。

我们来计算一下这样做的代价。

捡起一个垃圾和扔掉垃圾的代价是个定值，这玩意算着没啥意思，咱先忽略它。

当我们要一次性收集位置在 $x_1 > x_2 > \cdots > x_m$ 的垃圾时，我们所需的代价是：

$$x_1 + \sum_{i = 1}^m(x_i - x_{i + 1})(i + 1)^2$$

其中令 $x_{m + 1} = 0$。

我们把括号拆开看看会得到什么：

$$\begin{aligned}x_1 + \sum_{i = 1}^m(x_i - x_{i + 1})(i + 1)^2 &= x_1 + \sum_{i = 1}^m(x_i - x_{i + 1})(i^2 + 2i + 1) \\ &= x_1 + \sum_{i = 1}^mx_i(i^2 + 2i + 1) - \sum_{i = 1}^mx_{i + 1}(i^2 + 2i + 1) \\ &= x_1 + \sum_{i = 1}^mx_ii^2 + 2\sum_{i = 1}^mx_ii + \sum_{i = 1}^mx_i - \sum_{i = 1}^mx_{i + 1}i^2 - 2\sum_{i = 1}^mx_{i + 1}i - \sum_{i = 1}^mx_{i + 1} \\ &= 5x_1 + \sum_{i = 2}^mx_ii^2 + 2\sum_{i = 2}^mx_ii + \sum_{i = 2}^mx_i - \sum_{i = 2}^{m}x_i(i - 1)^2 - 2\sum_{i = 2}^{m}x_i(i - 1) - \sum_{i = 2}^{m}x_i \\ &= 5x_1 + \sum_{i = 2}^mx_i(2i + 1) \end{aligned}$$

因此这一段的贡献其实就是：

$$5x_1 + \sum_{i = 2}^mx_i(2i + 1)$$

这么写看起来不太直观，我们可以把 $\sum$ 拆掉看得更直观一些：

$$5x_1 + 5x_2 + 7x_3 + 9x_4 + \cdots$$

显然越往前系数越小，因此我们会尽量把比较大的 $x$ 放在前面。

那么我们就能得到一个做法：

先把 $x$ 从大到小排序。枚举一个 $k$，第 $1 \sim k$ 个垃圾前面系数都是 $5$，第 $k + 1 \sim 2k$ 个垃圾前面系数都是 $5$，第 $2k + 1 \sim 3k$ 个垃圾前面系数都是 $7$，以此类推。然后我们针对每个 $k$ 计算一下此时的代价，给所有 $k$ 的代价取 $\min$ 就是答案。

$k$ 要从 $1$ 枚举到 $n$，暴力处理每个数属于哪个区间，这个东西的复杂度是 $O(n^2)$，有点垃圾，能优化吗？

显然可以，由于 $[1, k]$ 这个区间所有垃圾系数都是 $5$，我们只要求出 $5\sum_{i = 1}^k x_i$ 就行了。这个东西是可以利用前缀和优化 $O(1)$ 求的。

同理，我们只要 $O(\dfrac{n}{k})$ 的复杂度就能求出某个 $k$ 的答案。

$k$ 从 $1$ 枚举到 $n$ 的过程中，这个总复杂度是：

$$O(n + \dfrac{n}{2} + \dfrac{n}{3} + \cdots + \dfrac{n}{n})$$

把 $n$ 提出来：

$$O(n \times (1 + \dfrac{1}{2} + \dfrac{1}{3} + \cdots + \dfrac{1}{n}))$$

不难发现括号里的东西就是调和级数，可以看作 $\log n$。

因此最后的总复杂度为 $O(n \log n)$。

[code](https://atcoder.jp/contests/agc027/submissions/59746619)

---

## 作者：naught (赞：0)

# [AGC027B] Garbage Collector

## 题意

原题翻译已经很不错了，这里不再赘述。

## 思路

>推论：每次取的垃圾数量应尽可能均分。

#### 证明

![](https://cdn.luogu.com.cn/upload/image_hosting/rduvoyzh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，假设有 $4$ 个垃圾需要被捡起，有两种取法：

* 取一号垃圾+取二三四号垃圾。

* 取一二号垃圾+取二三号垃圾。

前者所需能量为：$\displaystyle 20x_1+16x_2+9x_3+4x_4$。

后者所需能量为：$\displaystyle 18x_1+13x_2+9x_3+4x_4$。

由于保证所有 $x_i$ 均大于 $0$，所以后者明显更优。然后使用归纳法很容易证明推论是正确的。

之后思路就很清晰了，每次从 $1$ 到 $n$ 枚举 $k$，计算每段垃圾所需能量之和。

但是如何计算呢？

暴力计算式子很裸，由于我们一定是走到最后一个要取的垃圾再开始取垃圾，我们将 $x$ 数组 `reverse` 一下，那么所需能量即为：

$$

x_1+\sum_{i=1}^{n} ((i+1)^2+p_i-p_{i+1})

$$

其实这个是可以化简的：

$$

x_1+\sum_{i=1}^{n} ((i+1)^2+p_i-p_{i+1}) = 5x_1+\sum_{i=2}^{n}(2i+3) \times p_i

$$

这样，对于每个 $k$，前缀和处理价值即可，每个 $k$ 的复杂度是 $\displaystyle O(\frac{n}{k})$，故总复杂度为 $\displaystyle O(n \ln(n))$。

其他疑问见代码。

## 代码

```cpp
// written by Naught

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 it;
// #define int long long
#define Maxn 400005
#define p2(x) (1ll*(x)*(x))
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define fr(i, r, l) for (int i = l; i >= r; --i)
// #define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
// char buf[1<<21], *p1 = buf, *p2 = buf;
// inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
// inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
void train() {ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);}

int n, d[Maxn];
it ans = 2e24, x, s[Maxn];

void ct(it x)
{
    string anss;
    while(x)
    {
        anss = char(x%10+'0') + anss;
        x /= 10;
    }
    cout << anss << '\n';
}

int main()
{
    train();
    ll nn, xx;
    // n = read(), x = read();
    cin >> nn >> xx;
    n = nn, x = xx;
    fo(i, 1, n) cin >> d[i];
    reverse(d+1, d+n+1);
    fo(i, 1, n) s[i] = s[i-1]+d[i];
    fo(k, 1, n)
    {
        it res = k*x+5*s[k];
        fo(i, 2, (n+k-1)/k) res += (2*i+1)*(s[min(i*k, n)]-s[(i-1)*k]);
        ans = min(ans, res);
    }
    // cout << ans + x*n;
    ans += x*n;
    ct(ans);
    return 0;
}
/*
*/
```

## Tips

因为会爆 `long long`，所以建议使用 `__int128`。

---

