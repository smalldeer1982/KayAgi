# [ABC269F] Numbered Checker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc269/tasks/abc269_f

$ N $ 行 $ M $ 列のグリッドがあり、上から $ i $ 行目、左から $ j $ 列目のマス $ (i,j) $ には整数 $ (i-1)\ \times\ M\ +\ j $ が書かれています。  
 このグリッドに、以下の操作を施します。

- 全てのマス $ (i,j) $ について、 $ i+j $ が奇数ならそのマスに書かれている数字を $ 0 $ に書き換える。

操作後のグリッドについて、$ Q $ 個の質問に答えてください。  
 $ i $ 個目の質問は以下の通りです:

- 以下の条件を全て満たすマス $ (p,q) $ 全てについて、そこに書かれている整数を全て足し合わせた値を $ 998244353 $ で割った余りを求めよ。
  - $ A_i\ \le\ p\ \le\ B_i $
  - $ C_i\ \le\ q\ \le\ D_i $

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N,M\ \le\ 10^9 $
- $ 1\ \le\ Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ B_i\ \le\ N $
- $ 1\ \le\ C_i\ \le\ D_i\ \le\ M $

### Sample Explanation 1

この入力では、グリッドは以下の通りです。 !\[\](https://img.atcoder.jp/abc269/81d92debe7aa949266f3a00cff13b513.png) この入力には $ 6 $ つの質問が含まれます。 - $ 1 $ 個目の質問の答えは $ 0+3+0+6+0+8+0+11+0=28 $ です。 - $ 2 $ 個目の質問の答えは $ 1+0+9+0+17=27 $ です。 - $ 3 $ 個目の質問の答えは $ 17+0+19+0=36 $ です。 - $ 4 $ 個目の質問の答えは $ 14 $ です。 - $ 5 $ 個目の質問の答えは $ 0 $ です。 - $ 6 $ 個目の質問の答えは $ 104 $ です。

### Sample Explanation 2

$ 1 $ 個目の質問について、マス $ (10^9,10^9) $ に書かれている整数は $ 10^{18} $ ですが、それを $ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
5 4
6
1 3 2 4
1 5 1 1
5 5 1 4
4 4 2 2
5 5 4 4
1 5 1 4```

### 输出

```
28
27
36
14
0
104```

## 样例 #2

### 输入

```
1000000000 1000000000
3
1000000000 1000000000 1000000000 1000000000
165997482 306594988 719483261 992306147
1 1000000000 1 1000000000```

### 输出

```
716070898
240994972
536839100```

## 样例 #3

### 输入

```
999999999 999999999
3
999999999 999999999 999999999 999999999
216499784 840031647 84657913 415448790
1 999999999 1 999999999```

### 输出

```
712559605
648737448
540261130```

# 题解

## 作者：wnsyou (赞：3)

# [Numbered Checker](https://www.luogu.com.cn/problem/AT_abc269_f)

## 题意

有一个 $n\times m$ 的方格矩阵，左上角是 $(1,1)$，右下角是 $(n,m)$，每个方格中都有一个整数，其中 $(x,y)$ 中的数字为：

- 如果 $x+y$ 是奇数，则 $(x,y)$ 中的数字为 $0$。
- 否则，$(x,y)$ 中的数字为 $(x-1)\times m + y$。

有 $Q$ 组询问，每组询问给定四个整数 $a,b,c,d$，求所有满足要求的 $(i,j)$ 中的数字之和：

- $a \leqslant i \leqslant b$。
- $c \leqslant j \leqslant d$。

答案对 $998244353$ 取模。

## 思路

等差数列求和。

### 对于每组询问

暴力时间复杂度：$O(n\times m)$，爆炸。

#### 推导壹

就拿第一个样例举例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/29sdqal1.png)

可以很明显地发现，奇数行与偶数行排列虽然不太一样，但两者**都是[等差数列](https://baike.baidu.com/item/等差数列/1129192?fr=aladdin)，**且公差为 $2$。

经过仔细地推导(不给推导过程，自己推去)，我们可以发现：

- 对于 $a+c$ 为奇数的情况下：
  - 第 $a$ 行的等差数列首项为 $(a,c+1)$，项数为 $\frac{d-c+1}{2}$。
  - 第 $a+1$ 行的等差数列首项为 $(a+1,c)$，项数为 $1+\frac{d-c}{2}$。
- 对于 $a+c$​ 为偶数的情况下：
  - 第 $a$ 行的等差数列首项为 $(a,c)$，项数为 $\frac{d-c}{2}+1$。
  - 第 $a+1$ 行的等差数列首项为 $(a+1,c+1)$，项数为 $\frac{d-c+1}{2}$。

(以上除法均需带有向下取整)。

时间复杂度：$O(n)$，还是不够优秀。

#### 推导贰

![](https://cdn.luogu.com.cn/upload/image_hosting/7qu2bltq.png)

可以发现，行与行之间**也是等差数列！**公差为 $2m$。

令当前询问第 $a$ 行的等差数列之和为 $sum$，项数为 $p$；第 $a+1$ 行的等差数列之和为 $num$，项数为 $q$。

还是不给推导过程，答案就可以变成两个等差数列：

- 第一个：以 $sum$ 为首项，公差为 $2\times m\times p$，项数为 $\frac{b-a}{2}+1$。
- 第二个：以 $num$ 为首项，公差为 $2\times m\times q$，项数为 $\frac{b-a+1}{2}$。

求出两个等差数列之和，将其加起来就是答案啦，注意取模细节。

时间复杂度：$O(1)$。

## 复杂度

- 时间：$O(Q)$。
- 空间：$O(1)$。

## Code

```cpp
#include <iostream>

using namespace std;
using ll = long long;

const int mod = 998244353;

ll n, m, t, a, b, c, d, p, q, sum, num;

ll id (ll x, ll y) { // 将坐标转数值
  return ((x - 1) * m + y) % mod;
}

ll Sum (ll s, ll d, ll n) { // 等差数列求和公式
  return (s * n + n * (n - 1) / 2 % mod * d % mod) % mod;
}

int main () {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> n >> m >> t; t; t--) {
    cin >> a >> b >> c >> d;
    p = (d - c + 1) / 2, q = (d - c) / 2 + 1;
    if ((a + c) % 2) {
      sum = Sum(id(a, c + 1), 2, p), num = Sum(id(a + 1, c), 2, q); // 套用公式
    } else {
      swap(p, q);
      sum = Sum(id(a, c), 2, p), num = Sum(id(a + 1, c + 1), 2, q);
    }
    cout << (Sum(sum, 2 * m * p % mod, (b - a) / 2 + 1) + Sum(num, 2 * m * q % mod, (b - a + 1) / 2)) % mod << '\n'; // 各种取模细节
  }
  return 0;
}
```

---

## 作者：liangbowen (赞：2)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc269_f)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17374600.html)

题解区的方法思维难度都过大（？），提供一种极其容易的方法。

## 思路

题目就是求 $\sum\limits_{i=x_1}^{x_2}\sum\limits_{j=y_1}^{y_2}a_{i,j}$。所以很容易想到先算 $\sum\limits_{j=y_1}^{y_2}a_{i,j}$。

这个并不困难：
+ 如果 $i$ 是奇数，那一行应该形如 $x, 0, x+2, 0, x+4, 0, \cdots$ 这样子的。所以等差数列求和一下 $x+(x+2)+(x+4)+\cdots+\text{end}$ 即可。
+ 如果 $i$ 是偶数，那一行应该形如 $0, x, 0, x+2, 0, x+4, \cdots$ 这样子的。同样的等差数列，只是首项末项改一下就行。

于是可以被实现为 $f(i, l, r)$，具体见文末代码。答案就变成了 $\sum\limits_{i=x_1}^{x_2}f(i,y_1,y_2)$。

然后考虑如何快速计算。

![](https://cdn.luogu.com.cn/upload/image_hosting/vww3e8mq.png?x-oss-process=image)

发现公差固定。所以对于 $i$ 同奇偶的那些行来说，他们的 $f(i)$ 也是呈等差数列的。

所以随便实现一下就做完了。代码会比别的办法的代码好理解很多。注意 $\div 2$ 使用逆元实现。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int mod = 998244353, inv = 499122177; //inv是指除以2 
int n, m;
int f(int id, int l, int r) //id行[l,r]列，总和
{
	if (id & 1) //奇数列 
	{
		int st = (l & 1) ? l : l + 1, ed = (r & 1) ? r : r - 1;
		if (st > ed) return 0;
		int cnt = (ed - st) / 2 + 1;
		int tmp = 1ll * (id - 1) * m % mod; st = (tmp + st) % mod, ed = (tmp + ed) % mod;
		return 1ll * (st + ed) * cnt % mod * inv % mod;
	}
	else //偶数列 
	{
		int st = (l & 1 ^ 1) ? l : l + 1, ed = (r & 1 ^ 1) ? r : r - 1;
		if (st > ed) return 0;
		int cnt = (ed - st) / 2 + 1;
		int tmp = 1ll * (id - 1) * m % mod; st = (tmp + st) % mod, ed = (tmp + ed) % mod;
		return 1ll * (st + ed) * cnt % mod * inv % mod;
	}
}
void solve()
{
	int x1, y1, x2, y2, ans = 0;
	scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
	//for (int i = x1; i <= x2; i++) ans = (ans + f(i, y1, y2)) % mod;
	
	int st = (x1 & 1) ? x1 : x1 + 1, ed = (x2 & 1) ? x2 : x2 - 1; //奇数行 
	if (st <= ed)
	{
		int cnt = (ed - st) / 2 + 1;
		ans += 1ll * (f(st, y1, y2) + f(ed, y1, y2)) * cnt % mod * inv % mod, ans %= mod;
	}
	st = (x1 & 1 ^ 1) ? x1 : x1 + 1, ed = (x2 & 1 ^ 1) ? x2 : x2 - 1; //偶数行 
	if (st <= ed)
	{
		int cnt = (ed - st) / 2 + 1;
		ans += 1ll * (f(st, y1, y2) + f(ed, y1, y2)) * cnt % mod * inv % mod, ans %= mod;
	}
	printf("%d\n", ans);
}
int main()
{
	int q; scanf("%d%d%d", &n, &m, &q);
	while (q--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Mikefeng (赞：2)

## [ABC269F] Numbered Checker

### 题面翻译

给定一个 $N\times M$ 的矩阵 $A$，有 

$$A_{i,j}=
\begin{cases}
(i-1)M+j&((i+j)\bmod 2=0) \\
0&((i+j)\bmod 2=1)
\end{cases}
$$

给定 $Q$ 次询问，每次询问给出 $X_1,X_2,Y_1,Y_2$。求以 $(X_1,Y_1)$ $(X_2,Y_2)$ 为左上角和右下角的矩形的元素之和。对 $998244353$ 取模。

## 做法

二维差分可得：
$$sum_{a,b,c,d}=sum_{1,1,c,d}-sum_{1,1,a-1,d}-sum_{1,1,c,b-1}+sum_{1,1,a-1,b-1}$$
$\begin{alignedat}{3}sum_{1,1,n,m}
&=\sum_{i=1}^n\sum_{j=1}^m A_{i,j}
\\&=\sum_{i=1}^n\sum_{j=1}^m \left[\ (i+j)\bmod 2=0\ \right]\left((i-1)\times M+j\right)
\\&=\sum_{i=1}^n (i-1)\times M\times\lfloor\frac{m+i\bmod2}{2}\rfloor+\sum_{j=1}^m j\times\lfloor\frac{n+j\bmod2}{2}\rfloor
\end{alignedat}$

等差数列求和即可。
## 代码

```cpp
const ll p=998244353;
inline ll read(){
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x;
}
ll N,M,q;
inline ll val(ll l,ll r){
	ll num=(r-l)/2+1;
	return num*(l+r)/2%p;
}
inline ll sum(ll n,ll m){
	if(!n||!m) return 0;
	ll res=0;
	res=(res+(n*(n-1)/2)%p*(m/2)%p*M%p)%p;
	res=(res+(m*(m+1)/2)%p*(n/2)%p)%p;
	if(m&1){
		if(n&1)	res=(res+val(0,n-1)*M%p)%p;
		else res=(res+val(0,n-2)*M%p)%p;
	}
	if(n&1){
		if(m&1) res=(res+val(1,m))%p;
		else res=(res+val(1,m-1))%p;
	}
	return res;
}
int main(){
	N=read();M=read();q=read();
	while(q--){
		ll a=read(),c=read(),b=read(),d=read();
		ll ans=sum(c,d)-sum(a-1,d)-sum(c,b-1)+sum(a-1,b-1);
		printf("%lld\n",(ans%p+p)%p);
	}
	return 0;
}

```


---

## 作者：TernaryTree (赞：2)

**以下把行列相加为奇数的格子称为“黑格”，其他称为“白格”。我们不把黑格染成 $0$，仍保留原数。我们求的是白格之和。**

要求一个矩形的元素和，首先想到的是前缀和。因此我们只需要实现一个函数 $s(x,y)$ 表示左上角为 $(1,1)$ 右下角为 $(x,y)$ 的白格之和。

考虑对奇偶性分类讨论。

- ### 当 $x,y$ 皆为偶数时：

情况大概是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/k5ft1sh0.png)

我们对其分成若干个 $2\times 2$ 的小块，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/dlrhfcj8.png)

显然，每个小块的左上角和右下角是“白格”，右上角和左下角是“黑格”。我们设左上角是 $x$，右下角是 $y$，则右上角的黑格是 $x+1$，左下角黑格是 $y-1$。这个时候我们发现，黑格和等于白格和，都是 $x+y$，也就是说，当 $x,y$ 都是奇数时，白格之和等于黑格之和，也就意味着白格之和等于总和的一半。而总和是

$$
\begin{aligned}
&\sum_{i=1}^{x}\sum_{j=1}^y(i-1)m+j \\
= &\sum_{i=1}^{x}\sum_{j=1}^yim-m+j \\
= &\sum_{i=1}^{x}\sum_{j=1}^yim-\sum_{i=1}^{x}\sum_{j=1}^ym+\sum_{i=1}^{x}\sum_{j=1}^yj \\
= &my\sum_{i=1}^{x}i-xym+x\sum_{j=1}^yj \\
= &\dfrac12mxy(x+1)-xym+\dfrac12xy(y+1)\\
\end{aligned}
$$

所以白格之和就是

$$
\dfrac12mxy(x+1)-xym+\dfrac12xy(y+1)
$$

- ### 当 $x$ 为偶数 $y$ 为奇数时：

显然可以切成两块来考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/114cm5o6.png)

左边转换成了 $s(x,y-1)$，考虑右边怎么计算。

设右边的白格之和为 $S$，黑格之和为 $T$。

仍然把右边继续分割成 $2\times 1$ 的小块。

![](https://cdn.luogu.com.cn/upload/image_hosting/rx89bjsn.png)

一共有 $\dfrac12 x$ 块，每个小块中有一个黑格和一个白格。显然，同一块中的黑格比白格多 $m$。也就是说，$T-S=\dfrac12 xm$。

而我们还需要知道 $S+T$。这个很显然可以列出一个算式：

$$
\begin{aligned}
S+T&=\sum_{i=1}^x (i-1)m+y \\
&=\sum_{i=1}^x im-m+y \\
&=m\sum_{i=1}^x i-\sum_{i=1}^xm+\sum_{i=1}^xy \\
&=\dfrac12mx(x+1)-xm+xy \\
\end{aligned}
$$

由此我们得到了一个二元一次方程组，解得

$$S=\dfrac12(\dfrac12mx(x+1)-xm+xy-\dfrac12 xm)$$

于是答案为 

$$s(x,y-1)+\dfrac12(\dfrac12mx(x+1)-xm+xy-\dfrac12 xm)$$

- ### 当 $x$ 为奇数 $y$ 为偶数时：

这回还是切成两块，而且比上一种情况还要简单些。

![](https://cdn.luogu.com.cn/upload/image_hosting/tuyqimjr.png)

还是熟悉的切成几个 $1\times 2$ 的小块：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gf0ayz7.png)

仍然设这一小条白格之和为 $S$，黑格之和为 $T$。

显然有 $\dfrac12 y$ 块，每块黑格都比白格多 $1$，所以总的有 $T-S=\dfrac12 y$。

然后还是愉快地算总和：

$$
\begin{aligned}
S+T&=\sum_{j=1}^y(x-1)m+j \\
&=(x-1)my+\sum_{j=1}^yj \\
&=(x-1)my+\dfrac12 y(y+1) \\
\end{aligned}
$$

然后解得

$$S=\dfrac12((x-1)my+\dfrac12 y(y+1)-\dfrac12 y)$$

答案为

$$s(x-1,y)+\dfrac12((x-1)my+\dfrac12 y(y+1)-\dfrac12 y)$$

- ### 当 $x,y$ 都为奇数时：

根据二维前缀和的式子，有

$$s(x,y)=s(x-1,y)+s(x,y-1)-s(x-1,y-1)+a(x,y)$$

显然在本题里面 $a(x,y)=(x-1)m+y$。并且前面三种我们都处理好了。

答案即为

$$s(x-1,y)+s(x,y-1)-s(x-1,y-1)+(x-1)m+y$$

***

当然这题还有一点非常毒瘤。不知道为什么，如果你边算边模的话结果会有点问题，我也不知道是不是我实现的问题。所以我开了 `__int128`，最后输出再取模。

```cpp
#include <bits/stdc++.h>
#define int __int128

using namespace std;

struct ios {
    inline char read() {
        static const int inlen = 1 << 18 | 1;
        static char buf[inlen], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, inlen, stdin)), s == t ? -1 : *s++;
    }
    template<typename T> inline ios& operator>> (T &x) {
        static char c11, boo;
        for (c11 = read(), boo = 0; !isdigit(c11); c11 = read()) {
            if (c11 == -1) return *this;
            boo |= c11 == '-';
        }
        for (x = 0; isdigit(c11); c11 = read()) x = x * 10 + (c11 ^ '0');
        boo && (x = -x);
        return *this;
    }
} fin;

struct exios {
    template<typename _CharT, typename _Traits = char_traits<_CharT>>
    struct typ {
        typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
    };

    friend exios &operator<<(exios &out, int num) {
        if (num < 0) putchar('-'), num = -num;
        if (num >= 10) out << num / 10;
        putchar(num % 10 + '0');
        return out;
    }

    friend exios &operator<<(exios &out, const char * s) { printf("%s", s); return out; }
    friend exios &operator<<(exios &out, string s) { cout << s; return out; }
    friend exios &operator<<(exios &out, typ<char>::end e) { puts(""); return out; }
} fout;

const int maxn = 1e3 + 1;
const int mod = 998244353;

int n, m, q;

int s(int x, int y) {
    int xx = x * (x + 1) / 2;
    int yy = y * (y + 1) / 2;
    if (x % 2 == 0 && y % 2 == 0) {
        return ((m * y * xx + x * yy - x * y * m) / 2);
    } else if (x % 2 == 0 && y % 2 == 1) {
        return (s(x, y - 1) + (m * xx + x * y - x * m - x * m / 2) / 2);
    } else if (x % 2 == 1 && y % 2 == 0) {
        return (s(x - 1, y) + (y * m * (x - 1) + yy - y / 2) / 2);
    } else {
        return (s(x - 1, y) + s(x, y - 1) - s(x - 1, y - 1) + (x - 1) * m + y);
    }
}

signed main() {
    fin >> n >> m;
    fin >> q;
    while (q--) {
        int a, c, b, d;
        fin >> a >> c >> b >> d;
        fout << (s(c, d) - s(c, b - 1) - s(a - 1, d) + s(a - 1, b - 1)) % mod << endl;
    }
    return 0;
}
```

---

## 作者：TankYu (赞：0)

怒调三小时，写题解纪念之。

子矩阵查询可以差分一下变成查询 $(1,1)$ 到 $(x,y)$。

注意到每一行内部均构成等差数列，然后，所有奇数行的行和也构成等差数列，所有偶数行的行和也构成等差数列。

考虑直接算出来。

第一行我们只选取奇数，即对首项 $1$，末项 $y - [y \equiv 0 \pmod 2]$，公差 $2$ 的等差数列求和。

第二行我们只选取 **偶数列** 上的数，即对首项 $m+2$，末项 $m + y - [y \equiv 1 \pmod 2]$，公差 $2$ 的等差数列求和。

然后一共有 $\lfloor \dfrac{x + 1}{2} \rfloor$ 个奇数行，两行和的差就是 $2\times m$ 乘上一行有多少个数。

偶数行类似，一共有 $\lfloor \dfrac{x}{2} \rfloor$ 个偶数行，两行和的差也是 $2\times m$ 乘上一行有多少个数。

于是对这两种情况分别求和即可。

可能细节很多，下面的实现中给了一个比较方便的调试。

变量名的意义：

- `flst` 表示第一行最后有贡献的数是什么。
- `sfst`、`slst` 表示第二行第一个和最后一个有贡献的数。
- `fl`，`sl` 表示第一，二行的和。
- `co`，`ce` 表示奇数行和偶数行的个数。
- `fans`，`sans` 表示奇数行贡献和偶数行贡献。

```cpp
#include <iostream>
using namespace std;
#define LL long long
const LL mod = 998244353;
LL i2 = 499122177;
LL n, m;

LL calc(LL x, LL y) // (1,1)~(x,y)
{
    if (x == 0 || y == 0)
    {
        return 0;
    }
    LL flst = y - (y % 2 == 0), slst = m + y - (y % 2 == 1), sfst = m + 2;
    LL fl = (flst + 1) * (flst / 2 + 1) % mod * i2 % mod;
    if (x == 1)
    {
        return fl % mod;
    }
    // cout << flst << ' ' << slst << ' ' << sfst << ' ' << (slst - sfst) / 2 + 1 << '\n';
    LL sl = (slst + sfst) % mod * (((slst - sfst) / 2 + 1) % mod) % mod * i2 % mod;
    LL co = (x + 1) / 2, ce = x / 2;
    LL fans = ((fl + fl) % mod + (co - 1) * (flst / 2 + 1) % mod * 2 % mod * m % mod) % mod * co % mod * i2 % mod;
    LL sans = ((sl + sl) % mod + (ce - 1) * (((slst - sfst) / 2 + 1) % mod) % mod * 2 % mod * m % mod) % mod * ce % mod * i2 % mod;
    // cout << x << ' ' << y << '\n'
    //      << fl << ' ' << sl << '\n'
    //      << co << ' ' << ce << '\n'
    //      << fans << ' ' << sans << '\n'
    //      << (fans + sans) % mod << '\n'
    //      << '\n';
    // cout << '(' << 2 * sl << '+' << (ce - 1) << '*' << (slst - sfst) / 2 + 1 << '*' << 2 << '*' << m << ")*" << ce << '*' << i2 << "\n\n";
    return (LL)((fans + sans) % mod);
}

int main()
{
    cin >> n >> m;
    int t;
    cin >> t;
    while (t--)
    {
        int sx, sy, ex, ey;
        cin >> sx >> ex >> sy >> ey;
        LL ans = calc(ex, ey) - calc(sx - 1, ey) - calc(ex, sy - 1) + calc(sx - 1, sy - 1);
        ans %= mod;
        ans += mod;
        ans %= mod;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Tsawke (赞：0)

#  [[ABC269F] Numbered Checker](https://www.luogu.com.cn/problem/AT_abc269_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC269F)

## 题面

存在 $ n \times m $ 的网格图，在里面按照从左至右，从上至下的顺序填写 $ [1, n \times m] $ 所有数，然后使所有行数与列数之和为奇数的格子中的数推平为 $ 0 $。$ q $ 次询问求子矩形权值和。

## Solution

尝试简单推一下式子，显然对于奇数行，为 $ 1 + km, 3 + km, 5 + km, \cdots $，偶数行同理。对于多行相加，奇数行则 $ k = 0, 2, 4, \cdots $，偶数行同理。也就是说我们讨论奇偶之后，对一行里做一下等差数列求和然后乘上奇数行行数，对 $ k $ 做一遍等差数列求和然后乘上奇数列列数和 $ m $ 即可。

同时注意对于偶数的求和需要全部转为偶数，反之全部转为奇数。

同时也可以用简单的容斥思想，每次计算左上角为 $ 1 $ 的四个矩形的值并处理，但实现难度与此方法接近。

同时整个过程中仅需 `long long` 即可，等差数列求和的除以 $ 2 $ 不需要用逆元，适当取模后也不需要用 `__int128_t`。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD (998244353ll)

template < typename T = int >
inline T read(void);

int N, M;

ll QueryOdd(ll l, ll r){
    if(!(l & 1))++l;
    if(!(r & 1))--r;
    if(l > r)return 0;
    return (((l + r) * (((r - l) >> 1) + 1)) >> 1) % MOD;
}
ll QueryEven(ll l, ll r){
    if(l & 1)++l;
    if(r & 1)--r;
    if(l > r)return 0;
    return (((l + r) * (((r - l) >> 1) + 1)) >> 1) % MOD;
}
ll CntOdd(ll l, ll r){
    if(!(l & 1))++l;
    if(!(r & 1))--r;
    if(l > r)return 0;
    return (((r - l) >> 1) + 1) % MOD;
}
ll CntEven(ll l, ll r){
    if(l & 1)++l;
    if(r & 1)--r;
    if(l > r)return 0;
    return (((r - l) >> 1) + 1) % MOD;
}

int main(){
    N = read(), M = read();
    int Q = read();
    while(Q--){
        ll ans(0);
        int a = read(), b = read(), c = read(), d = read();
        (ans += QueryOdd(c, d) * CntOdd(a, b) % MOD) %= MOD;
        (ans += ((QueryOdd(a, b) - CntOdd(a, b) + MOD) % MOD) * CntOdd(c, d) % MOD * M % MOD) %= MOD;
        (ans += QueryEven(c, d) * CntEven(a, b) % MOD) %= MOD;
        (ans += ((QueryEven(a, b) - CntEven(a, b) + MOD) % MOD) * CntEven(c, d) % MOD * M % MOD) %= MOD;
        printf("%lld\n", ans);
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

update-2023_01_25 初稿

---

