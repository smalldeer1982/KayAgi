# [ABC254F] Rectangle GCD

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_f

正整数 $ N $ と長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ と $ B=(B_1,B_2,\dots,B_N) $ が与えられます。

$ N\ \times\ N $ のマス目があります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と呼びます。$ 1\ \le\ i,j\ \le\ N $ を満たす整数の組 $ (i,j) $ に対し、マス $ (i,j) $ に $ A_i\ +\ B_j $ が書かれています。以下のクエリを $ Q $ 個処理してください。

- $ 1\ \le\ h_1\ \le\ h_2\ \le\ N,1\ \le\ w_1\ \le\ w_2\ \le\ N $ を満たす整数の組 $ h_1,h_2,w_1,w_2 $ が与えられる。左上隅が $ (h_1,w_1) $、右下隅が $ (h_2,w_2) $ である矩形領域に含まれる整数の最大公約数を求めよ。

## 说明/提示

### 制約

- $ 1\ \le\ N,Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i,B_i\ \le\ 10^9 $
- $ 1\ \le\ h_1\ \le\ h_2\ \le\ N $
- $ 1\ \le\ w_1\ \le\ w_2\ \le\ N $
- 入力はすべて整数である。

### Sample Explanation 1

マス $ (i,j) $ に書かれている整数を $ C_{i,j} $ とします。 $ 1 $ 個目のクエリについて、$ C_{1,2}=4,C_{1,3}=6,C_{2,2}=6,C_{2,3}=8 $ なのでこれらの最大公約数の $ 2 $ が答えとなります。

## 样例 #1

### 输入

```
3 5
3 5 2
8 1 3
1 2 2 3
1 3 1 3
1 1 1 1
2 2 2 2
3 3 1 1```

### 输出

```
2
1
11
6
10```

## 样例 #2

### 输入

```
1 1
9
100
1 1 1 1```

### 输出

```
109```

# 题解

## 作者：Gyc_Fisher (赞：6)

# Rectangle GCD 题解

[题面](https://www.luogu.com.cn/problem/AT_abc254_f)

拿到题首先考虑到暴力（本蒟蒻怕之后写错了，写个暴力方便对拍）：

1.处理出这个 $n\times n$ 的网格图中每个格子的权值，复杂度 $O(n^2)$：

```cpp
int board[MAXN][MAXN];//只能开到1e3*1e3级别
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        board[i][j]=a[i]+b[j];//a[i],b[j]含义同题干
	}
}
```

2.再在 $q$ 次询问中遍历要求矩形中的所有数，并求他们的 $\gcd$：

```cpp
int h1,h2,w1,w2;
scanf("%d%d%d%d",&h1,&h2,&w1,&w2);
int G=board[h1][w1];
for(int i=h1;i<=h2;i++){
    for(int j=w1;j<=w2;j++){
        G=__gcd(G,board[i][j]);//c++库函数中有gcd函数（即__gcd()）,因为使用了汇编语言，导致其比一般的手写gcd快（更快的放在题解最后）
	}
}
printf("%d\n",G);
```

暴力的思路大致如上，加上 $q$ 次询问，复杂度为 $O(n^3)$。

但是啊，我们小小的看一眼数据范围，啊？2e5！嘶~，暴力好像整不过去。

OK 啊，肯定需要优化我们的算法。

在此之前，我们回到求 $\gcd$ 的过程：一种很通用的方式是[辗转相除法](https://zhuanlan.zhihu.com/p/324578532)。

但除法可以看作一个数不断的减去另一个数，所以就有以下的推论：
$$
\gcd(a,b)=\gcd(b-a,a)
$$
好，那么好，回到问题本身，我们可以发现一些性质：

见图，我们注意看用红线圈出来的数：
![](https://cdn.luogu.com.cn/upload/image_hosting/mo8mbety.png)



发现一个事情：这几个数的差分数组与原 $a$ 序列的差分数组是一样的都是只有 $2$ 和 $-3$ 两个元素。也就是说在看同一列的时候可以把这一列看作原数组整体加上一个值。

这个性质推广到同一行的数也是可以的。

结合上文的推论我们可以把以下的式子（我们需要求的一行的结果，$x$ 为这一行统一加的值）：
$$
\gcd(b_1+x,b_2+x,...,b_n+x)
$$
转化成：
$$
\gcd(b_1+x,b_2-b_1,b_3-b_2,...,b_n-b_{n-1})
$$
除开第一项，我们发现后面的数正是这一行（$b$ 数组）的差分数组的每一项，而我们又知道，这个差分数组是不会改变的，也就是说每一行在求 $gcd$ 会有重复的部分,但我们只需要用一次（$\gcd(x,x)=x$）。所以可以直接 $O(n)$ 的预处理出来。

此时我们只需要求每一行的第一项的 $\gcd$：
$$
\gcd(b_1+a_1,b1+a_2,...,b_1+a_n)
$$
如法炮制一下，变成：
$$
\gcd(b_1+a_1,a_2-a_1,a_3-a_2,...,a_n-a_{n-1})
$$
又发现除开第一项，剩下的数是这一列（$a$ 数组）的差分数组的每一项，这个差分数组也不会改变，我们也可以预处理出来。

化简到最后，我们发现针对一个左上角为 $(h_1,w_1)$，右下角为 $(h_n,w_n)$ 矩形区间的 $\gcd$，只需要求：
$$
\gcd(h_1+w_1,\gcd(h_2-h_1,h_3-h_2,...,h_n-h_{n-1}),\gcd(w_2-w_1,w_3-h_2,...,w_n-w_{n-1}))
$$
到这里有些小朋友就要问了：啊，后头两个 $\gcd$ 又要 $O(n)$ 求，加上 $q$ 次询问不就成 $O(n^2)$ 的算法了吗，不就  TLE 了吗？

后面的是两个差分数组的中间几项，我们可以在最开始就预处理出来。

又有小朋友要问了：啊，我是要查一个区间的 $\gcd$ 啊，你预处理之后还不是要 $O(n)$ 查，总复杂度不又成 $O(n^2)$ 了吗？

再看一眼数据，$2 \times10^5$，$O(n\log n)$ 的完美数据大小，又涉及到区间查找，线段树它不就来了吗。

到这里，本题的解法也很明了了：

1.分别预处理出 $a$ 数组和 $b$ 数组的差分数组，用线段树去存差分数组上的区间 $\gcd$。

2.针对每次询问，只需要求：$\gcd(h_1+w_1,\gcd(h_2-h_1,h_3-h_2,...,h_n-h_{n-1}),\gcd(w_2-w_1,w_3-h_2,...,w_n-w_{n-1}))$

附上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 200010
using namespace std;
int n,m;
int a[MAXN],b[MAXN];
int del[MAXN],delta[MAXN];
struct SG{
	int l,r;
	int data;//a的差分数组
	int datb;//b的差分数组
}t[MAXN<<2];
void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].data=delta[l];
		t[p].datb=del[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].data=__gcd(t[p*2+1].data,t[p*2].data);//存区间gcd
	t[p].datb=__gcd(t[p*2+1].datb,t[p*2].datb);
}
int querya(int p,int l,int r){//查a的差分数组的区间gcd
	if(l<=t[p].l&&t[p].r<=r){
		return t[p].data;
	}
	int mid=(t[p].l+t[p].r)>>1;
	int ans=0;
	if(mid>=l) ans=querya(p*2,l,r);
	if(mid<r){
		if(ans!=0) ans=__gcd(ans,querya(p*2+1,l,r));
		else ans=querya(p*2+1,l,r);
	}
	return ans;
}
int queryb(int p,int l,int r){//查b的差分数组的区间gcd
	if(l<=t[p].l&&t[p].r<=r){
		return t[p].datb;
	}
	int mid=(t[p].l+t[p].r)>>1;
	int ans=0;
	if(mid>=l) ans=queryb(p*2,l,r);
	if(mid<r){
		if(ans!=0) ans=__gcd(ans,queryb(p*2+1,l,r));
		else ans=queryb(p*2+1,l,r);
	}
	return ans;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		delta[i]=abs(a[i]-a[i-1]);
	}
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		del[i]=abs(b[i]-b[i-1]);
	}
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l1,r1,l2,r2;
		scanf("%lld%lld%lld%lld",&l1,&l2,&r1,&r2);
		int ans=a[l1]+b[r1];
		ans=__gcd(ans,queryb(1,r1+1,r2));
		ans=__gcd(ans,querya(1,l1+1,l2));
		printf("%lld\n",ans);
	}
	return 0;
}
```

代码上可能有一些实现上冗余的部分（写丑了），还有其实不用开 long long，因为最大也就到 $2 \times 10^9$，int 完全存的下。

最后附上之前说的巨快的 $\gcd$:

```cpp
inline int gcd(int x,int y){
	if(!(x&&y))return x|y;
	int a=__builtin_ctz(x);
	int b=__builtin_ctz(y);
	int c=a>b?b:a,d;
	y>>=b;
	while(x){
		x>>=a;
		d=y-x;
		a=__builtin_ctz(d);
		if(x<y) y=x;
		x=d>=0?d:-d; 
	}
	return y<<c;
}
```
本蒟蒻第一次写题解，如有错误，望指正。


---

## 作者：Powerless233 (赞：4)

## Description
给定两个序列 $A$ ， $B$ 。现有一个矩阵 $C$， $C_{i,j}=A_{i}+B_{j}$。

给出 $Q$ 次询问，每次询问 $h1,h2,w1,w2$ 子矩阵中所有元素的 gcd。
## Analysis
一个求区间 gcd 的 trick。

根据更相减损法，对于 $\gcd(a,b)$，有 $\gcd(a,b)=\gcd(a,b-a)$。

那么把这个原则应用到序列上，有 $\gcd(a_{i},a_{i+1})=\gcd(a_{i},a_{i+1}-a_{i})$。

对于一段连续的区间 $[ l,r ]$ ，有 $\gcd(a_{l}.a_{l+1},\dots,a_{r})=\gcd(a_{l},a_{l+1}-a_{l}.\dots,a_{r}-a_{r-1})$。

即，原序列区间上的 gcd 可以转化为 先在差分数组上求 gcd，再与区间左端点求 gcd。在本题中，每一行的差分数组（除第一项）是相同的，因此后者可以只在单行上做处理就能求得子矩阵 gcd。
 
同理，在行上的处理方法可以同样扩展到列上。因此，对于子矩阵 $h1,h2,w1,w2$ 的 gcd，我们可以将其转化为 $\gcd(\gcd(a_{h1+1}-a_{i},\dots,a_{h2}-a_{h2-1}),\gcd(b_{w1+1}-b_{w1},\dots,b_{w2}-b_{w2-1}),a_{h1}+b_{w1})$。

单个序列的区间 gcd 可以通过 st 表或者线段树维护。

## Code
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
inline LL read()
{
	LL res = 0, fl = 1;
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9'))
	{
		if (ch == '-')
			fl = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		res = (res << 3) + (res << 1) + ch - '0', ch = getchar();
	return res * fl;
}
inline LL max(LL a, LL b) { return a > b ? a : b; }
inline LL min(LL a, LL b) { return a < b ? a : b; }
const LL inf = 0x3f3f3f3f;
const LL N = 2e5 + 5;
int n, q, a[N], b[N], ga[N][21], gb[N][21];
inline int gcda(int x, int y)
{
	if (x > y)
		return 0;
	int t = log2(y - x + 1);
	return __gcd(ga[x][t], ga[y - (1 << t) + 1][t]);
}
inline int gcdb(int x, int y)
{
	if (x > y)
		return 0;
	int t = log2(y - x + 1);
	return __gcd(gb[x][t], gb[y - (1 << t) + 1][t]);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		b[i] = read();
	for (int i = 1; i <= n; i++)
		ga[i][0] = abs(a[i] - a[i - 1]);
	for (int i = 1; i <= n; i++)
		gb[i][0] = abs(b[i] - b[i - 1]);
	for (int t = 1; t <= 20; t++)
	{
		for (int i = 1; i + (1 << t - 1) - 1 <= n; i++)
		{
			ga[i][t] = __gcd(ga[i][t - 1], ga[i + (1 << t - 1)][t - 1]);
			gb[i][t] = __gcd(gb[i][t - 1], gb[i + (1 << t - 1)][t - 1]);
		}
	}
#define l1 Powerless
#define r1 Powerless2
#define l2 Powerless23
#define r2 Powerless233//防止关键字冲突
	int l1, r1, l2, r2, res, resa, resb;
	while (q--)
	{
		l1 = read(), l2 = read(), r1 = read(), r2 = read();
		resa = gcda(l1 + 1, l2);
		resb = gcdb(r1 + 1, r2);
		res = __gcd(resa, resb);
		res = __gcd(res, a[l1] + b[r1]);
		cout << res << '\n';
	}
	return 0;
}

```

---

## 作者：chenhanzheapple (赞：2)

# [传送门](https://www.luogu.com.cn/problem/AT_abc254_f)

## 思路
  众所周知，最大公因数有一个重要的性质，更相减损术。即 $\gcd(a,b) = \gcd(a,b-a)$。如果求多个数的最大公因数，式子可以推广到：$\gcd(a,b,c) = \gcd(a,b-a,c-a)$。

  然后考虑左上角为 $(x1,y1)$，右上角为 $(x2,y2)$ 的矩阵的最大公因数。
  最开始的矩阵如下：

|$a_{x1}+b_{y1}$|$a_{x1}+b_{y1+1}$|$\ldots$|$a_{x1}+b_{y2}$|
|:-:|:-:|:-:|:-:|
|$a_{x1+1}+b_{y1}$|$a_{x1+1}+b_{y1+1}$|$\ldots$|$a_{x1+1}+b_{y2}$|
|$\ldots$|$\ldots$|$\ldots$|$\ldots$|
|$a_{x2}+b_{y1}$|$a_{x2}+b_{y1+1}$|$\ldots$|$a_{x2}+b_{y2}$|

对每一行进行更相减损术后可以发现，对于每一行，除了第一项不变以外，其他项都变为了形如 $b_i-b_{i-1}$ 的项。这个式子很像差分数列。

再对每一列进行更相减损术后可以发现，对于每一列，除了第一项不变以外，其他项都变为了形如 $a_i-a_{i-1}$ 的项。

因此，总的来看最后变化完成的矩阵，可以发现，对于除每一列，值都是相同的。

所以，对于每个询问，答案是 $\gcd(a_{x1}+b_{y1},\gcd\{a_i-a_{i-1}\},\gcd\{b_i-b_{i-1}\})$。

对于 $\gcd\{a_i-a_{i-1}\}$ 和 $\gcd\{b_i-b_{i-1}\}$，可以使用线段树去维护，因为 ~~学校在练习倍增~~ 没有修改操作，所以我使用了更简单的 ST 表。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[200005],b[200005],f[200005][25],g[200005][25];
int gcd(int l,int r){
    int k = log2(r-l+1);
    return __gcd(f[l][k],f[r-(1<<k)+1][k]);
}
int gcd2(int l,int r){
    int k = log2(r-l+1);
    return __gcd(g[l][k],g[r-(1<<k)+1][k]);
}
int main(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=2;i<=n;i++){
    	f[i][0] = a[i]-a[i-1];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    for(int i=2;i<=n;i++){
    	g[i][0] = b[i]-b[i-1];
    }
	for(int j=1;j<=19;j++){
	    for(int i=1;i<=n-(1<<j)+1;i++){
	        f[i][j] = __gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
	    }
	}
	for(int j=1;j<=19;j++){
	    for(int i=1;i<=n-(1<<j)+1;i++){
	        g[i][j] = __gcd(g[i][j-1],g[i+(1<<(j-1))][j-1]);
	    }
	}
    while(q--){
        int x,y,x2,y2;
        cin >> x >> x2 >> y >> y2;
        int ans = a[x]+b[y];
        if(x+1<=x2){//注意判断越界
        	ans = __gcd(ans,gcd(x+1,x2));
        }
        if(y+1<=y2){
        	ans = __gcd(ans,gcd2(y+1,y2));
        }
        cout << abs(ans) << endl;
    }
    return 0;
}

```

---

## 作者：wwxxbb (赞：1)

## 思路

### 1. 暴力

显然有 $\mathcal{O}(qn^2)$ 做法， 对 $a,b$ 数组除掉 $\gcd$ 后特判倍数是否为 $1$ 可以快一点（但还会TLE）。因为前面数的 $\gcd$ 为 $1$ 可以推出所求区间的 $\gcd$ 一定为 $1$，具体见我的暴力代码。

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;

int n, q, a[N], b[N];

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int ans = gcd(a[1], b[1]);
    for (int i = 2; i <= n; i++) ans = gcd(ans, gcd(a[i], b[i]));
    for (int i = 1; i <= n; i++) a[i] /= ans, b[i] /= ans;
    
    while (q--) {
        int h1, h2, w1, w2;
        cin >> h1 >> h2 >> w1 >> w2;
        int base = a[h1] + b[w1];
        for (int i = h1; i <= h2; i++)
            for (int j = w1; j <= w2; j++) {
                base = gcd(base, a[i] + b[j]);
                if (base == 1) goto END; // 优化在此
            }
        END: cout << base * ans << '\n';
    }
    return 0;
}
```

### 2. 正解

先来介绍一个求区间 $\gcd$ 的小技巧。

由更相减损法，$\gcd(a, b) = \gcd(a, b - a)$，拓展到数组 $a$，$\gcd(a_1, a_2,\cdots, a_n) = gcd(a_1, a_2-a_1, a_3-a_2, \cdots, a_n - a_{n-1})$。所以我们只需要预处理好差分数组，计算时算第一个数与差分数组的 $\gcd$ 即可。

而我们要求的是：
$$
\gcd_{i=h_1}^{h_2}(\gcd_{j=w_1}^{w_2}(a_i+b_j))
$$
拓展到了二维。其实就是求两次一维的情况。
发现除了最初始的位置，剩下的差分数组都是相同的，所以只需求一列即可。~~图我懒得画。~~

首先我们求一下行：
$$
\gcd(a_{h_1}+b_{w_1},(a_{h_1}+b_{w_1+1})-(a_{h_1}+b_{w_1}),\cdots,(a_{h_1}+b_{w_2})-(a_{h_1}+b_{w_2-1}))
$$
消掉 $a_{h_1}$ 后：
$$
\gcd(a_{h_1}+b_{w_1},b_{w_1+1}-b_{w_1},\cdots,b_{w_2}-b_{w_2-1})
$$
即为：
$$
\gcd(a_{h_1}+b_{w_1},\gcd_{i=w_1+1}^{w_2}(b_i-b_{i-1})
$$
列也是同理，这里直接放出结果
$$
\gcd(a_{h_1}+b_{w_1},\gcd_{i=h_1+1}^{h_2}(a_i-a_{i-1}))
$$
综合上述二式得到：
$$
\text{query}=\gcd(a_{h_1}+b_{w_1},\gcd_{i=h_1+1}^{h_2}(a_i-a_{i-1})),\gcd_{j=w_1+1}^{w_2}(b_j-b_{j-1}))
$$
区间查询想到线段树和st表，所以用它们维护区间 $\gcd$。时间复杂度 $\mathcal{O}(n\log{n})$

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, LOG = 18; // 2 ^ 18 大概超过 2e5

int n, q, a[N], b[N];
int da[N][LOG], db[N][LOG];

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int querya(int l, int r) {
    if (l > r) return 0;
    int k = log2(r - l + 1);
    return gcd(da[l][k], da[r - (1 << k) + 1][k]);
}

int queryb(int l, int r) {
    if (l > r) return 0;
    int k = log2(r - l + 1);
    return gcd(db[l][k], db[r - (1 << k) + 1][k]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], da[i][0] = abs(a[i] - a[i - 1]);
    for (int i = 1; i <= n; i++) cin >> b[i], db[i][0] = abs(b[i] - b[i - 1]);
    for (int j = 1; j <= LOG; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            da[i][j] = gcd(da[i][j - 1], da[i + (1 << j - 1)][j - 1]);
            db[i][j] = gcd(db[i][j - 1], db[i + (1 << j - 1)][j - 1]);
        }
    while (q--) {
        int h1, h2, w1, w2;
        cin >> h1 >> h2 >> w1 >> w2;
        cout << gcd(a[h1] + b[w1], gcd(querya(h1 + 1, h2), queryb(w1 + 1, w2))) << '\n';
    }
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

> 小贴士：随机选点可以过 62 个点，总共只有 72 个点。

我们要求的式子是这样的：

$$
\gcd_{i=h_1}^{h_2}(\gcd_{j=w_1}^{w_2}(a_i+b_j))
$$

不难让人往同余上想，但是这是错的，正解是辗转相减法。

根据辗转相减法，我们让每一项都减去前一项，第一项不处理，不难得原式为：

$$
\gcd(\gcd_{i=h_1}^{h_2}(a_{h_1}+b_{w_1}),\gcd_{i={w_1+1}}^{w_2}(b_{i}-b_{i-1}))
$$

同理，对于左边部分，我们还是让每一项都减去前一项，第一项不处理，继续处理：

$$
\gcd(a_{h_1}+b_{w_1},\gcd_{i={h_1+1}}^{h_2}(a_{i}-a_{i-1}),\gcd_{i={w_1+1}}^{w_2}(b_{i}-b_{i-1}))
$$

这个式子就很好求了，可以用线段树维护。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std; 
const LL N=3e5;
struct node
{
	LL l,r,ta,tb;
}t[N*10];
LL n,m,a[N],b[N],h1,h2,w1,w2;
LL gcd(LL x,LL y)
{
	if(!y)return x;
	return gcd(y,x%y);
}
void pushup(LL pos)
{
	t[pos].ta=gcd(t[pos*2].ta,t[pos*2+1].ta);
	t[pos].tb=gcd(t[pos*2].tb,t[pos*2+1].tb);
}
void build(LL pos,LL l,LL r)
{
	t[pos].l=l,t[pos].r=r;
	if(l==r)
	{
		t[pos].ta=abs(a[l]-a[l-1]);
		t[pos].tb=abs(b[l]-b[l-1]);
		return;
	}
	LL mid=(l+r)/2;
	build(pos*2,l,mid);
	build(pos*2+1,mid+1,r);
	pushup(pos);
}
LL querya(LL pos,LL l,LL r)
{
	if(r<l)return 0;
	if(l<=t[pos].l&&t[pos].r<=r)return t[pos].ta;
	if(r<t[pos].l||t[pos].r<l)return 0;
	return gcd(querya(pos*2,l,r),querya(pos*2+1,l,r));
}
LL queryb(LL pos,LL l,LL r)
{
	if(r<l)return 0;
	if(l<=t[pos].l&&t[pos].r<=r)return t[pos].tb;
	if(r<t[pos].l||t[pos].r<l)return 0;
	return gcd(queryb(pos*2,l,r),queryb(pos*2+1,l,r));
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b[i]);
	}
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld%lld%lld",&h1,&h2,&w1,&w2); 
		LL d=a[h1]+b[w1],t1=querya(1,h1+1,h2),t2=queryb(1,w1+1,w2);
		d=gcd(d,t1);
		d=gcd(d,t2);
		printf("%lld\n",d); 
	} 
}
```

---

## 作者：Conan15 (赞：0)

更相减损术，配合线段树。

显然 $\gcd(x, y) = \gcd(x, y - x)$，推广到序列上就有 $\gcd\{a_1, a_2, a_3, \dots, a_n\} = \gcd\{a_1, a_2 - a_1, a_3 - a_2, \dots, a_n - a_{n-1}\}$。\
由于本题中 $c_{i,j} = a_i + b_j$，需要求 $c$ 中一个子矩阵的最大公约数，观察到 $a_i,b_j$ 中很多地方是重复出现的，所以考虑使用更相减损术把它们“删掉”。\
即我们对每一行使用一次更相减损术，再对每一列使用一次更相减损术，会发现其实产生的新矩阵有很多重复项。（建议自己手模）\
于是硬维护 $a,b$ 序列的查分数组的区间 $\gcd$ 即可。可以用线段树或 ST 表。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n, q;

struct Solve {
    int a[N], b[N]; // a 原 b 差 
    void init() { for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = abs(a[i] - a[i - 1]); }
    struct Tree {
        int l, r, g;
    } tr[N << 2];
    void pushup(int u) { tr[u].g = gcd(tr[u << 1].g, tr[u << 1 | 1].g); }
    void build(int u, int l, int r) {
        tr[u].l = l, tr[u].r = r;
        if (l == r) return tr[u].g = b[l], void();
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
    int query(int u, int l, int r) {
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].g;
        int mid = tr[u].l + tr[u].r >> 1;
        if (r <= mid) return query(u << 1, l, r);
        if (l > mid) return query(u << 1 | 1, l, r);
        return gcd( query(u << 1, l, r), query(u << 1 | 1, l, r) );
    }
} t1, t2;

int main() {
    scanf("%d%d", &n, &q);
    t1.init(), t2.init();
    t1.build(1, 1, n), t2.build(1, 1, n);
    while (q--) {
        int x, y, xx, yy; scanf("%d%d%d%d", &x, &xx, &y, &yy);
        if (x == xx && y == yy) printf("%d\n", t1.a[x] + t2.a[y]);
        else if (x == xx) {
            int f = t1.a[x] + t2.a[y], g = t2.query(1, y + 1, yy);
            printf("%d\n", gcd(f, g) );
        } else if (y == yy) {
            int f = t1.a[x] + t2.a[y], g = t1.query(1, x + 1, xx);
            printf("%d\n", gcd(f, g));
        } else {
            int f = t1.a[x] + t2.a[y], g = t1.query(1, x + 1, xx), h = t2.query(1, y + 1, yy);
            printf("%d\n", gcd(f, gcd(g, h) ) );
        }
    }
    return 0;
}
```

---

## 作者：hjyowl (赞：0)

### 思路

让我们求：

$$\gcd_{i=h1}^{h2}\gcd_{i=w1}^{w2} a_i+b_j$$

因为最大公约数满足辗转相除的性质，所以说本质上我们要算的是：

$$\gcd (a_{h1}+b_{w1},\gcd_{i=h1+1}^{h2} (a_i-a_{i-1}),\gcd_{i=w1+1}^{w2} (b_i-b_{i-1}))$$

然后我们可以用线段树来维护 $a_i-a_{i-1}$ 和 $b_i-b_{i-1}$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x1 X1
#define y1 Y1
#define y2 Y2
#define x2 X2
const int N = 1000010;
struct owl{
	int l,r;
	int v1,v2;
}tr[N];
int a[N],b[N];
int x[N],y[N];
void pushup(int u){
	tr[u].v1 = __gcd(tr[u << 1].v1,tr[u << 1 | 1].v1);
	tr[u].v2 = __gcd(tr[u << 1].v2,tr[u << 1 | 1].v2);
}
void build(int u,int l,int r){
	tr[u].l = l,tr[u].r = r;
	if (l == r){
		tr[u].v1 = x[l],tr[u].v2 = y[l];
		return ;
	}
	int mid = l + r >> 1;
	build(u << 1,l,mid);
	build(u << 1 | 1,mid + 1,r);
	pushup(u);
}
pair<int,int>query(int u,int l,int r){
	if (l <= tr[u].l && tr[u].r <= r){
		return {tr[u].v1,tr[u].v2};
	}
	int mid = (tr[u].l + tr[u].r) >> 1;
	pair<int,int>res;
	res.first = res.second = 0;
	if (mid >= l){
		pair<int,int>t = query(u << 1,l,r);
		res = {__gcd(res.first,t.first),__gcd(res.second,t.second)};
	}
	if (mid < r){
		pair<int,int>t = query(u << 1 | 1,l,r);
		res = {__gcd(res.first,t.first),__gcd(res.second,t.second)};
	}
	return res;
}
int main(){
	int n,m;
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
		x[i] = abs(a[i] - a[i - 1]);
	}
	for (int i =1 ;i <=n ; i ++ ){
		cin >> b[i];
		y[i] = abs(b[i] - b[i - 1]);
	}
	build(1,1,n);
	for (int i = 1; i <= m; i ++){
		int x1,y1,x2,y2;
		cin >> x1 >> x2 >> y1 >> y2;
		int res = a[x1] + b[y1];
		res = __gcd(res,query(1,x1 + 1,x2).first);
		res = __gcd(res,query(1,y1 + 1,y2).second);
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：0)

## solution

这题有两个重点，一个是 `gcd` 的性质，一个是想到用类似 `RMQ` 的区间 `gcd`。

第一个点，如果我们求一个区间的最大公约数，那么有：
$$
\gcd(a_l, a_{l+1}, a_{l+2},\dots,a_{r-1}, a_r)=\gcd(a_l, a_{l+1}-a_l, a_{l+2}-a_{l+1},\dots,a_{r-1}-a{r-2}, a_r-a_{r-1})
$$

这就是辗转相除法，大家可以自行上网查询。然后我们把它放到表格中，对每行进行这个操作：

![](https://cdn.luogu.com.cn/upload/image_hosting/i3i07e3w.png)

然后你就会发现，后面每列都一样！所以，算后面那些列的最大公约数只需求一行即可。然后对每列进行操作，你又会发现差不多的结果：只需求一列即可。

但是每次去算还是会超时，所以我们可以用类似 ST 表的方法求出每行每列的区间最大公约数，就可以 AC 啦。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define x1 first
#define y1 second
int a[200010], b[200010], fa[200010][20], fb[200010][20];

int faa(int l, int r)
{
    int k = log2 (1 + r - l);
    return __gcd (fa[l][k], fa[r - (1 << k) + 1][k]);
}

int fbb(int l, int r)
{
    int k = log2 (1 + r - l);
    return __gcd (fb[l][k], fb[r - (1 << k) + 1][k]);
}

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) fa[i][0] = abs (a[i] - a[i - 1]);
    for (int i = 1; i <= n; i++) fb[i][0] = abs (b[i] - b[i - 1]);
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            fa[i][j] = __gcd (fa[i][j - 1], fa[i + (1 << (j - 1))][j - 1]), fb[i][j] = __gcd (fb[i][j - 1], fb[i + (1 << (j - 1))][j - 1]);
    while (m--)
    {
        int x, x1, y, y1;
        cin >> x >> x1 >> y >> y1;
        int ans = a[x] + b[y];
        if (x != x1) ans = __gcd (faa (x + 1, x1), ans);
        if (y != y1) ans = __gcd (ans, fbb (y + 1, y1));
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：yinqy (赞：0)

根据题意，我们可以得到一个式子：
$$
\gcd_{i=h_1}^{h_2}(\gcd_{j=w_1}^{w_2}(a_i+b_j))
$$


自然而然地，我们的暴力思路就有了，直接根据上面这个式子直接进行 $\gcd$ 运算，时间复杂度为 $O(qn^2)$。

然而这个题的数据范围是 ${1\leq N,Q\leq 2\times 10^5}$，所以我们需要想一下其他思路。

在我们学习的 ${\gcd(a,b)}$ 的解法中，有一种是更相减损法 ${\gcd(a,b)=\gcd(a,b-a)}$。 这时我们再来根据这个知识点思考这道题：

**原式**：
$$
\begin{aligned}
&\gcd(a_{h_1}+b_{w_1},\text{ 	}a_{h_1}+b_{w_1+1},\text{ }a_{h_1}+b_{w_1+2},\text{ }\cdots,\text{ }a_{h_1}+b_{w_2})\\
&\gcd(a_{h_1+1}+b_{w_1},\text{ }a_{h_1+1}+b_{w_1+1},\text{ }a_{h_1+1}+b_{w_1+2},\text{ }\cdots,\text{ }a_{h_1+1}+b_{w_2})\\
&\vdots\\
&\gcd(a_{h_2}+b_{w_1},\text{ }a_{h_2}+b_{w_1+1},\text{ }a_{h_2}+b_{w_1+2},\text{ }\cdots,\text{ }a_{h_2}+b_{w_2})\\
\end{aligned}
$$

**更相减损法化简后**：
$$
\begin{aligned}
&\gcd(a_{h_1}+b_{w_1},\text{ }b_{w_1+1}-b_{w_1},\text{ }b_{w_1+2}-b_{w_1+1},\text{ }b_{w_1+3}-b_{w_1+2},\text{ }\cdots,\text{ }b_{w_2}-b_{w_2-1})\\
&\gcd(a_{h_1+1}+b_{w_1},\text{ }b_{w_1+1}-b_{w_1},\text{ }b_{w_1+2}-b_{w_1+1},\text{ }b_{w_1+3}-b_{w_1+2},\text{ }\cdots,\text{ }b_{w_2}-b_{w_2-1})\\
&\vdots\\
&\gcd(a_{h_2}+b_{w_1},\text{ }b_{w_1+1}-b_{w_1},\text{ }b_{w_1+2}-b_{w_1+1},\text{ }b_{w_1+3}-b_{w_1+2},\text{ }\cdots,\text{ }b_{w_2}-b_{w_2-1})\\
\end{aligned}
$$

**再进一步化简后**：
$$
\begin{aligned}
\gcd(a_{h_1}+b_{w_1},\text{ }b_{w_1+1}-b_{w_1},\text{ }b_{w_1+2}-b_{w_1+1},\text{ }b_{w_1+3}-b_{w_1+2},\text{ }\cdots,\text{ }b_{w_2}-b_{w_2-1})\\
\gcd(a_{h_1}+b_{w_1},\text{ }a_{h_1+1}-a_{h_1},\text{ }a_{h_1+2}-a_{h_1+1},\text{ }a_{h_1+3}-a_{h_1+2},\text{ }\cdots,\text{ }a_{h_2}-a_{h_2-1})\\
\end{aligned}
$$

**最后简单结合**：
$$
\begin{aligned}
\gcd(a_{h_1}+b_{w_1},\text{ }\gcd_{i=h_1+1}^{h_2}(a_i-a_{i-1}),\text{ }\gcd_{j=w_1+1}^{w_2}(b_j-b_{j-1}))\\
\end{aligned}
$$

我们现在就得到了一个简单明了的式子了。而这个式子由于与区间有关，所以我们就可以考虑用经常解决区间问题的 **线段树** 来进行区间查询，当然因为此题没有区间修改，就也可以用 **ST表** 来操作。我这里是用线段树做的。

### Code：
```cpp
#include<bits/stdc++.h>
#define ri register int
#define rll register long long
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int INF=0x3f3f3f3f;
const int N=2e5+10;
int n,T;
int a[N],b[N];

inline int gcd__(int a, int b){// 最快GCD的求法
	if(!a) return b;
	if(!b) return a;
	int az=__builtin_ctz(a), bz=__builtin_ctz(b),z=(az>bz?bz:az), diff;
	b>>=bz;
	while(a){
		a>>=az;
		diff=b-a;
		az=__builtin_ctz(diff);
		if(a<b) b=a;
		a=(diff<0?-diff:diff);
	}
	return b<<z; 
}

namespace SegmentTree{
    int a[N]={0};
    struct SG{
        struct node{
            int l,r;ll gcd;
            #define l(x) tree[x].l
            #define r(x) tree[x].r
            #define gcd(x) tree[x].gcd
        }tree[N<<2];
        void build(int p,int l,int r){
            l(p)=l, r(p)=r;
            if(l==r){ gcd(p)=(a[l]>=0? a[l]: -a[l]); return;}
            int mid=(l+r)>>1;
            build(p*2,l,mid);
            build(p*2+1,mid+1,r);
            gcd(p)=gcd__(gcd(p*2),gcd(p*2+1));
        }
        ll ask_gcd(int p,int l,int r){
            if(l<=l(p)&&r(p)<=r) return gcd(p);
            int mid=(l(p)+r(p))>>1;
            ll d=0;
            if(l<=mid) d=gcd__(d,ask_gcd(p*2,l,r));
            if(r>mid) d=gcd__(d,ask_gcd(p*2+1,l,r));
            return d;
        }	    
    }tr1,tr2;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>T;
    for(ri i=1;i<=n;i++) cin>>a[i], SegmentTree::a[i]=a[i]-a[i-1];
    SegmentTree::tr1.build(1,1,n);
    for(ri i=1;i<=n;i++) cin>>b[i], SegmentTree::a[i]=b[i]-b[i-1];
    SegmentTree::tr2.build(1,1,n);
    // 重定义一下变量名，防止与std中的变量名冲突
    #define x1 yinqyx1
    #define y1 yinqyy1
    #define x2 yinqyx2
    #define y2 yinqyy2
    int x1,x2,y1,y2,gcda,gcdb,ans;
    while(T--){
        cin>>x1>>x2>>y1>>y2;
        gcda=SegmentTree::tr1.ask_gcd(1,x1+1,x2);
        gcdb=SegmentTree::tr2.ask_gcd(1,y1+1,y2);
        ans=gcd__(gcda,gcdb), ans=gcd__(ans,a[x1]+b[y1]);
        cout<<ans<<'\n';
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

在考虑维护最小公约数的查询问题时，辗转相除法非常好用。

首先这道题的矩阵是 $10^5\times 10^5$ 的，这显然无法维护，而且矩阵是二维的，每一项都与 $a,b$ 两个数组有关，这不好维护。

如果我们可以通过变换使得查询可以拆成对于这两个数组的分别查询就好了。

我们考虑进行辗转相减法，将数组变成一个差分的形式，我们发现答案变成了对于 $a,b$ 查询的形式，这就易于查询了，式子如下： 

$$
\gcd(a_{l_1}+b_{r_1},\gcd_{i={l_1+1}}^{l_2}(a_{i}-a_{i-1}),\gcd_{i={r_1+1}}^{r_2}(b_{i}-b_{i-1}))
$$

我们可以考虑用各种数据结构来维护，比较推荐线段树，因为最小公约数有结合律，但是没有可加性，所以树状数组就不太好搞。

直觉上时间复杂度是 $O(n\log ^2 n)$ 的，但是仔细分析由于你线段树向上合并应该是越来越快的，感性上其实会接近 $O(n\log n)$。

---

## 作者：liangbowen (赞：0)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc254_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17398763.html)

这题 trick 就是更相减损术：$\gcd\{a_1, a_2, a_3, \cdots, a_n\} = \gcd\{a_1, a_2 - a_1, a_3 - a_2, \cdots, a_n - a_{n-1}\}$。

## 思路

有了这个 trick 之后这题就好做了。并不需要其他题解一样画表格，化简式子就行，过程并没有难点。

$$
\begin{aligned}
\text{answer}
& = \gcd\limits_{i=x1}^{x2}\Big(\normalsize\gcd\limits_{j=y_1}^{y_2} (a_i + b_j)\Big)\normalsize \\
& = \gcd\limits_{i=x1}^{x2}\Big(\gcd\{ a_i + b_{y_1}, a_i + b_{y_1+1}, a_i + b_{y_1+2}, \cdots, a_i + b_{y_2}\}\Big)\normalsize \\
& = \gcd\limits_{i=x1}^{x2}\Big(\gcd\{ a_i + b_{y_1}, \color{red}b_{y_1+1}-b_{y_1}, b_{y_1+2}-b_{y_1+1}, \cdots, b_{y_2}-b_{y_2-1}\color{black}\}\Big)\normalsize \\
& = \gcd\Big(\normalsize\color{red}b_{y_1+1}-b_{y_1}, b_{y_1+2}-b_{y_1+1}, \cdots, b_{y_2}-b_{y_2-1}\color{black}, \color{blue}\gcd\limits_{i=x_1}^{x_2}(a_i+b_{y_1})\color{black} \Big)\normalsize \\
& = \gcd\Big(\normalsize\color{red}\gcd\limits_{j=y_1+1}^{y_2} (b_j-b_{j-1})\color{black}, \color{blue}\gcd\{a_{x_1}+b_{y_1}, a_{y_1+1}-a_{y_1}, \cdots, a_{y_2}-a_{y_2-1}\} \color{black}\Big)\normalsize \\
& = \gcd\Big(\normalsize\color{red}\gcd\limits_{j=y_1+1}^{y_2} (b_j-b_{j-1})\color{black}, \color{blue}a_{x1}+b_{y1}, \gcd\limits_{i=x1+1}^{x2}(a_i-a_{i-1})\color{black}\Big)\normalsize \\
& = \gcd\Big(\normalsize a_{x1}+b_{y1}, \gcd\limits_{i=x1+1}^{x2}(a_i-a_{i-1}), \gcd\limits_{i=y_1+1}^{y_2} (b_i-b_{i-1})\Big)\normalsize \\
\end{aligned}
$$

综上，只需维护两个 DS，分别支持求 $(a_i - a_{i-1})$ 与 $(b_i - b_{i-1})$ 的区间 gcd。掏一手 ST 表拿下。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define y1 zltAKIOI
using namespace std;
const int N = 2e5 + 5;
int n, q;
int gcd(int x, int y) {return y == 0 ? x : gcd(y, x % y);}
struct ST {
	int gc[N][20];
	void build(int a[])
	{
		for (int i = 1; i <= n; i++) gc[i][0] = abs(a[i] - a[i - 1]);
		for (int j = 1; j <= 18; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				gc[i][j] = gcd(gc[i][j - 1], gc[i + (1 << (j - 1))][j - 1]);
	}
	int query(int l, int r)
	{
		if (l > r) return 0;
		int len = log2(r - l + 1);
		return gcd(gc[l][len], gc[r - (1 << len) + 1][len]);
	}
} A, B;
int a[N], b[N];
int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	A.build(a), B.build(b);
	while (q--)
	{
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
		printf("%d\n", gcd(gcd(A.query(x1 + 1, x2), B.query(y1 + 1, y2)), a[x1] + b[y1]));
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Tsawke (赞：0)

# [[ABC254F] Rectangle GCD](https://www.luogu.com.cn/problem/AT_abc254_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC254F)

## 题面

给定序列 $ a_n, b_n $，存在 $ n \times n $ 的网格图，令图上 $ (i, j) $ 位置的值为 $ a_i + b_j $。$ q $ 次询问给定 $ h_1, h_2, w_1, w_2 $，查询左上角为 $ (h_1, w_1) $，右下角为 $ (h_2, w_2) $ 的矩形中所有数的 $ \gcd $。

## Solution

挺好的一道水题，有一道类似的题，[AcWing 246 区间最大公约数](https://www.acwing.com/problem/content/description/247/)，简而言之就是实现区间加，区间求 $ \gcd $。这道题也是类似的。

首先有一个性质，更相减损术，即 $ \gcd(a, b) = \gcd(a, b - a) $。然后我们尝试列举一个以 $ (i, j) $ 为左上角，$ (x, y) $ 为右下角的矩形：

|   $ a_{i} + b_{j} $   |   $ a_{i} + b_{j + 1} $   |   $ a_{i} + b_{j + 2} $   | $ \cdots $ |   $ a_{i} + b_{y} $   |
| :-------------------: | :-----------------------: | :-----------------------: | :--------: | :-------------------: |
| $ a_{i + 1} + b_{j} $ | $ a_{i + 1} + b_{j + 1} $ | $ a_{i + 1} + b_{j + 2} $ | $ \cdots $ | $ a_{i + 1} + b_{y} $ |
| $ a_{i + 2} + b_{j} $ | $ a_{i + 2} + b_{j + 1} $ | $ a_{i + 2} + b_{j + 2} $ | $ \cdots $ | $ a_{i + 2} + b_{y} $ |
|      $ \cdots $       |        $ \cdots $         |        $ \cdots $         | $ \cdots $ |      $ \cdots $       |
|   $ a_{x} + b_{j} $   |   $ a_{x} + b_{j + 1} $   |   $ a_{x} + b_{j + 2} $   | $ \cdots $ |   $ a_{x} + b_{y} $   |

然后不难发现可以通过更相减损术，对这个矩形横向进行差分：

|   $ a_{i} + b_{j} $   | $ b_{j + 1} - b_j $ | $ b_{j + 2} - b_{j + 1} $ | $ \cdots $ | $ b_{y} - b_{y - 1} $ |
| :-------------------: | :-----------------: | :-----------------------: | :--------: | :-------------------: |
| $ a_{i + 1} + b_{j} $ | $ b_{j + 1} - b_j $ | $ b_{j + 2} - b_{j + 1} $ | $ \cdots $ | $ b_{y} - b_{y - 1} $ |
| $ a_{i + 2} + b_{j} $ | $ b_{j + 1} - b_j $ | $ b_{j + 2} - b_{j + 1} $ | $ \cdots $ | $ b_{y} - b_{y - 1} $ |
|      $ \cdots $       |     $ \cdots $      |        $ \cdots $         | $ \cdots $ |      $ \cdots $       |
|   $ a_{x} + b_{j} $   | $ b_{j + 1} - b_j $ | $ b_{j + 2} - b_{j + 1} $ | $ \cdots $ | $ b_{y} - b_{y - 1} $ |

发现除了最初始的位置，剩下的每一列都是相同的，所以我们不难想到，除了第一行第一列之外的数，会因为重复所以可以不用考虑。同时对于对应的第一列，也可以差分。最后就可以变成，对于一段查询，求的是序列 $ a $ 差分数组的 $ [w_1 + 1, w_2] $ 的 $ \gcd $，和序列 $ b $ 差分数组的 $ [h_1 + 1, h_2] $ 的 $ \gcd $，再和 $ a_{h_1} + b_{w_1} $ 做一下 $ \gcd $ 即可，记得判断 $ w_1 \neq w_2 $ 和 $ h_1 \neq h_2 $。

然后考虑如何快速维护区间的 $ \gcd $，这个东西也就可以直接挂在线段树上，或者因为没有修改，用 ST表 也行（不过我不喜欢 ST表，所以用的线段树维护）。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MAXN (210000)

template < typename T = int >
inline T read(void);

int N, Q;
int A[MAXN], B[MAXN], dA[MAXN], dB[MAXN];

class SegTree{
private:
    int tr[MAXN << 2];
    #define LS (p << 1)
    #define RS (LS | 1)
    #define MID ((gl + gr) >> 1)
public:
    void Pushup(int p){tr[p] = __gcd(tr[LS], tr[RS]);}
    void Build(bool flag, int p = 1, int gl = 1, int gr = N){//true - line(y), false - row(x)
        if(gl == gr)return tr[p] = flag ? dB[gl] : dA[gl], void();
        Build(flag, LS, gl, MID), Build(flag, RS, MID + 1, gr);
        Pushup(p);
    }
    int Query(int l, int r, int p = 1, int gl = 1, int gr = N){
        if(l <= gl && gr <= r)return tr[p];
        if(r <= MID)return Query(l, r, LS, gl, MID);
        if(l >= MID + 1)return Query(l, r, RS, MID + 1, gr);
        return __gcd(Query(l, r, LS, gl, MID), Query(l, r, RS, MID + 1, gr));
    }
}stLine, stRow;

int main(){
    N = read(), Q = read();
    for(int i = 1; i <= N; ++i)A[i] = read(), dA[i] = A[i] - A[i - 1];
    for(int i = 1; i <= N; ++i)B[i] = read(), dB[i] = B[i] - B[i - 1];
    stLine.Build(true), stRow.Build(false);
    while(Q--){
        int h1 = read(), h2 = read(), w1 = read(), w2 = read();
        int ans = A[h1] + B[w1];
        if(w1 != w2)ans = __gcd(ans, stLine.Query(w1 + 1, w2));
        if(h1 != h2)ans = __gcd(ans, stRow.Query(h1 + 1, h2));
        printf("%d\n", abs(ans));
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_06 初稿

---

## 作者：Raisetsu41 (赞：0)

有点意思，但是线段树写挂了，没赛场调出来。   

先把答案的式子表示出来，为了方便，把每一个横行的 $\gcd$ 表示成 $f(x)$ ，$f(x) = \gcd(a_x, a_x + b_i, a_x + b_{i + 1}, \dotsb, a_x + b_j)$，总的答案就是 $\gcd(f(i), f(i + 1), \dotsb, f(j))$。   

要用到一个数论知识 $\gcd(a_1, a_2, a_3, \dotsb, a_n) = \gcd(a_1, a_2 - a_1, a_3 - a_2, \dotsb, a_n - a_{n - 1})$。   

把 $f(x)$ 重新表示为 $f(x) = \gcd(a_x, b_i, b_{i + 1} - b_i, \dotsb, b_j - b_{j - 1})$，把后面那一块单独拎出来，记为 $g = \gcd(b_i, b_{i + 1} - b_i, \dotsb, b_j - b_{j - 1})$，因为是个矩形，所以每一个横行的 $g$ 的是一样的，答案就重新表示成了 $Ans = \gcd(g, a_x, a_{x + 1}, \dotsb, a_y)$。   
这个就变成了一条直线上的连续的关系，可以直接用两个线段树维护。   

---

