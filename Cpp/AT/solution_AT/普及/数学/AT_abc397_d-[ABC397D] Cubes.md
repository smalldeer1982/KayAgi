# [ABC397D] Cubes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc397/tasks/abc397_d

给定一个正整数 $N$。请判断是否存在满足 $x^3 - y^3 = N$ 的正整数对 $(x, y)$。若存在，请输出其中一个这样的 $(x, y)$。

## 说明/提示

### 约束条件

- $1 \leq N \leq 10^{18}$
- 输入均为整数

### 样例解释 1

因为 $12^3 - 11^3 = 397$，所以 $(x, y) = (12, 11)$ 是正确答案之一。

### 样例解释 2

不存在满足 $x^3 - y^3 = 1$ 的正整数对 $(x, y)$，因此输出 `-1`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
397```

### 输出

```
12 11```

## 样例 #2

### 输入

```
1```

### 输出

```
-1```

## 样例 #3

### 输入

```
39977273855577088```

### 输出

```
342756 66212```

# 题解

## 作者：yuhong056 (赞：5)

# AT\_abc397\_d \[ABC397D] Cubes 题解

题意：给定 $N$（$N \le 10^{18}$），求出一对正整数 $X,Y$ 满足 $X^3-Y^3=N$，或报告无解。

## 一开始的思路：暴力

枚举 $Y$，求是否有满足条件的 $X$，如果快要超时就报告无解。

```cpp
bool is_cbr(ll s) {
	ll cbr = cbrt(s);
	return(cbr * cbr * cbr == s);
}

int main(){
	cin >> n;
	for(ll i = 1; i <= 1e6; i++) {
		if(is_cbr(n + i * i * i)) {
			cout << cbrt(n + i * i * i) << ' ' << i;
			return 0;
		}
	}
	cout << -1;
	return 0;
}
```

十个测试点 WA ，原因：精度误差、long long 范围。

## 正确的思路

这个 $X^3-Y^3$ 看起来很棘手，我们将它进行因式分解。将其看作两个立方体体积之差，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/divh65sj.png)

剩下的体积我们将其分拆：

![](https://cdn.luogu.com.cn/upload/image_hosting/z99zhoh5.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uv2cu9v4.png)

红色体积为 $x^2 \times (x-y)$，绿色体积为 $x \times y \times (x-y)$，蓝色体积为 $y^2 \times (x-y)$。

相加得：$X^3-Y^3=x^2 \times (x-y) + x \times y \times (x-y) + y^2 \times (x-y) = (x-y)(x^2+xy+y^2)$ 有了因式分解，就可以枚举 $x-y$ 了。

设 $t$ 为 $x-y$，因为 $t^2=x^2-2xy+y^2 < x^2+xy+y^2$，所以 $t^2 \times t < t(x^2+xy+y^2) = N$，由此可知 $t^3 < N$。

知道了 $t$ 的范围，就可以开始判定 $t$ 是否合法了。

如果 $N$ 不能被 $t$ 整除，非法。

$t^2=x^2-2xy+y^2，N \div t=x^2+xy+y^2$，两式相减，可得：

$$(x^2+xy+y^2) - (x^2-2xy+y^2) = (x^2 - x^2) + (xy + 2xy) + (y^2 - y^2) = 3xy$$ 

所以 $N \div t - t^2 = 3xy$。如果式子的结果不能被 $3$ 整除，必然不合法。

知道了 $x-y,xy$，方程就好解了。

$\begin{aligned}
 (x-y)^2+4xy &= x^2-2xy+y^2+4xy \\
 &= x^2+2xy+y^2 \\
 &= (x+y)^2
\end{aligned}$

现在已知 $x+y,x-y$，就可以轻松求出 $x$ 与 $y$ 了。

## 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 3e5 + 35, MAXT = 1e6;

ll n;

int main(){
	cin >> n;
	for(ll i = 1; i * i * i < n; i++) {//i = x - y;
//		cout << i << ' ';
		if(n % i)continue;
		ll j = n / i - i * i;//j = 3xy;
//		cout << j << ' ';
		if(j % 3)continue;
		j /= 3;
		ll x_add_y = sqrt(i * i + j * 4);//x_add_y = x + y;
//		cout << x_add_y << '\n';
		if((i + x_add_y) % 2)continue;
		if(x_add_y - i < 2)continue;//如果 y = 0，不符合题意。
		ll x = (i + x_add_y) / 2, y = (x_add_y - i) / 2;
		if(x * x + x * y + y * y == n / i){ //最后判断一下
			cout << x << ' ' << y;
			return 0;
		}
	}
	cout << -1;
	return 0;
}
```

这是本蒟蒻的第一篇题解，管理员大大求过！

---

## 作者：Clover_Lin (赞：4)

在博客内阅读效果更佳：<https://blog.csdn.net/ArmeriaLeap/article/details/146286412>。

## 题目大意
[给定一个正整数 $N$，求两个正整数 $x$ 和 $y$ 满足 $x^3-y^3=n$。](https://atcoder.jp/contests/abc397/tasks/abc397_d)
## 思路
直接枚举会超时，考虑把式子变形。下面是我的演算过程：
$$
\because n\le10^{18}\\
\therefore 1\le x,y\le2\cdot10^6\\
x^3-y^3=n\\
(x-y)\cdot (x^2+xy+y^2)=N\\
(x-y)\cdot [(x+y)^2-xy]=N\\
(x-y)\cdot [(x+y)^2-\frac{(x+y)^2-(x-y)^2}{4}]=N\\
令\ x+y=a,\ x-y=b\\
\therefore b\cdot (a^2-\frac{a^2-b^2}{4})=N\\
b\cdot \frac{3a^2+b^2}{4}=N\\
b\cdot(3a^2+b^2)=4N
$$
所以我们可以直接枚举 $N$ 的因数 $b$，因为上述式子也可以变形为 $3a^2b+b^3=4N$，所以 $b^3<4N$。接下来，我们考虑是否有一个正整数 $a$。可以根据式子算出 $3a^2$，然后看 $\sqrt{a^2}$ 的值是否是一个正整数。

判断可以直接用 C++ 语言中的 `sqrt` 函数，注意需要 `#include <cmath>` 或者使用万能头文件。但是这个函数本质上是二分，带 `log`，虽然不影响通过本题，但是还是有些慢的。我曾经试过预处理，但是不行，因为把平方数打表打出来就已经超时了，所以还是用系统函数吧。
## 代码实现
已 AC，提交记录：[Submission #63817473](https://atcoder.jp/contests/abc397/submissions/63817473)，其实跑得还是挺快的（6ms）。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;

long long n;

long long sqr(long long a)
{
	long long ret = sqrt(a);
	if (ret * ret != a)
		return -1;
	return ret;
}

int main()
{
	cin >> n; n *= 4;
	for (long long b = 1; b * b * b <= n; b++)
	{
		if (n % b != 0) continue;
		long long a = n / b - 1LL * b * b;
		if (a % 3) continue; a /= 3;
		a = sqr(a); if (a == -1) continue;
		if (a % 2 != b % 2) continue;
		long long x = (a + b) / 2;
		long long y = (a - b) / 2;
		if (x < 1 || y < 1) continue;
		cout << x << " " << y << endl;
		return 0;
	}
	cout << "-1" << endl;
	return 0;
}
```

如有更好的做法欢迎提出！本次 D 题推式子千万别推错了，不过样例也应该过不了，所以在发现出 bug 的时候检查一下式子。

---

## 作者：KobeBeanBryantCox (赞：4)

# AT_abc397_d [ABC397D] Cubes 题解

-----------------

[题目传送门](https://www.luogu.com.cn/problem/AT_abc397_d)。

给出两种做法，一种正经，一种乱搞。大家一定不要学乱搞做法啊！

-----------------

## 题意

给定 $1\le n\le 10^{18}$，求满足 $x^3-y^3=n$ 的正整数 $x,y$，若没有，输出 $-1$。

-----------------

## 正经做法

$x^3-y^3=n$。

$(x-y)(x^2+xy+y^2)=n$。

令 $d=x-y$，则 $x=y+d$。

代入得 $d((y+d)^2+(y+d)y+y^2)=n$。

化简得 $y\times(d+y)=\dfrac{n-d^3}{3d}$。

考虑枚举 $d$，要先判断 $n\bmod d=0$ 和 $(n-d^3)\bmod (3d)=0$，不成立直接跳过。

然后得到了 $\dfrac{n-d^3}{3d}$。

考虑去二分最大的 $y$ 使得 $y\times(d+y)\le\dfrac{n-d^3}{3d}$。

然后判断 $y\times(d+y)=\dfrac{n-d^3}{3d}$ 成不成立，不成立直接跳过。

求出了 $y$，则 $x=n+y^3$，开三次根号看看结果是不是整数即可，是的话直接输出答案。

循环到最后还没出答案就输出 $-1$。

由于我的代码用的是 `__int128` 所以开三次根号还要用二分避免精度问题。

复杂度 $O(n^{\frac 1 3}\log V)$，$V$ 是二分的上界，我定的很大，小一点没尝试过能不能过。

[AC 记录](https://atcoder.jp/contests/abc397/submissions/63861568)。

------------------

## 乱搞做法

$x^3-y^3=(x-y)(x^2+xy+y^2)=n$。

令 $a=x-y$，$b=x^2+xy+y^2$。

有方程组 $\left\{\begin{matrix}
x-y=a \\
x^2+xy+y^2=b
\end{matrix}\right.$。


解得 $x=\dfrac{3a+\sqrt{3(4b-a^2)}}{6}$，$y=\dfrac{-3a+\sqrt{3(4b-a^2)}}{6}$（这里 $x$ 和 $y$ 都取的是正根）。

然后发现 $n$ 的因子一定[不多](https://oeis.org/A066150)，$10^{18}$ 内最多是 $103680$。

所以直接枚举 $a\times b=n$。

解 $x$ 和 $y$ 看是不是有解，且是正整数解即可。

但是不能暴力枚举检验，时间复杂度接受不了。

所以用 [Pollard-Rho](https://www.luogu.com.cn/problem/P4718) 来预处理。

由于我的代码还是使用 `__int128` 所以还是要二分开二次根号。

~~时间复杂度 $\sout{O(\text{玄学})}$~~，期望是 $O(n^{\frac 1 4}+2^d\log 2^d+103680(\log103680+\log n))$，但是 $d$（Pollard-Rho 分出来的质因数总数）的大小很玄学，貌似不超过 $20$，这我也不会算，有算出来的大佬评论一下吧。

[AC 记录](https://atcoder.jp/contests/abc397/submissions/63855821)。

但是它跑得飞快，比正经做法好像还要快。

-----------------

## 后记

若错误或不清，欢迎评论或私信。

---

## 作者：xixisuper (赞：3)

# AT_abc397_d [ABC397D] Cubes 题解

算是近几场里面难度较大的一个 D 了。

## 思路

简单来说就是告诉你一个 $N$，让你找到一组正整数 $(x,y)$，满足：

$$
x^3-y^3=N
$$

保证满足 $N\le10^{18}$。

这一眼看过去很不可做啊，你发现你也没什么好方法限制 $x,y$ 的范围，所以寄出文化课解方程大杀器**换元**，把 $x\gets y+a$，于是就有：

$$
\begin{aligned}
(y+a)^3-y^3&=N\\
3ay^2+3a^2y+a^3&=N
\end{aligned}
$$

发现左边的三项都是正的，**所以 $a^3$ 一定小于 $N$**，那么 $a<N^{\frac{1}{3}}$，而这个范围是**可以枚举的**！

然后问题就转换为了给定一个关于 $y$ 的一元二次方程，判断这个方程是否存在 $y$ 的正整数解，这不就是初中数学题了吗？直接上求根公式即可。

当然这时你发现直接 $\frac{-b\pm\sqrt{b^2-4ac}}{2a}$ 在运算过程中可能会炸 `long long`（当然也可以用 `__int128`，但是因为涉及到开方运算，不能直接用 `sqrt()`，这十分的不优），这是你不想看到的，所以你还可以继续把这个方程变形。

$$
\begin{aligned}
3ay^2+3a^2y+a^3&=N\\
3a(y^2+ay)&=N-a^3\\
y^2+ay&=\frac{N-a^3}{3a}
\end{aligned}
$$

此时令 $c\gets -\frac{N-a^3}{3a},\Delta\gets a^2-4c$，就可以直接在 `long long` 范围下使用求根公式求出 $y$ 的值了！

注意，对于一个 $a$ 来说，如下情况不存在 $y$ 的正整数解：

- $3a\nmid (N-a^3)$
- $\sqrt{\Delta}\notin \N$
- $2\nmid(\sqrt{\Delta}-a)$

如果上述条件都不满足，那么一定存在一个满足条件的 $y$：

$$
y=\frac{-a+\sqrt{\Delta}}{2}
$$

最后输出 $y+a$ 和 $y$ 即可，时间复杂度 $O(N^{\frac{1}{3}})$。

## 代码

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	ll N;cin>>N;
	for(ll a=1;a*a*a<N;a++){
		ll c=N-a*a*a;
		if(c%(3*a)!=0) continue;
		c/=(3*a);
		ll delta=a*a+4*c,T=sqrt(delta);
		if(T*T!=delta) continue;
		if((T-a)%2) continue;
		if(T-a<=0) continue;
		ll X=(T-a)/2,Y=X+a;
		cout<<Y<<' '<<X;
		return 0;
	}
	cout<<"-1";
	return 0;
} 
```

---

## 作者：yyycj (赞：2)

## 题目简述
给定正整数 $N$，判断是否存在 $x$ 与 $y$ 使得 $x^{3}-y^{3}=N$。

## 主要思路
数学题。$x^{3}-y^{3}$ 通过立方差公式可得：
$$(x-y)(x^{2}+xy+y^{2})$$

设正整数 $z=x-y$，为了满足 $(x-y)(x^{2}+xy+y^{2})=n$，所以 $z$ 为 $n$ 的因数，将 $x=y+z$ 代入：
$$z[(y+z)^{2}+(y+z)y+y^{2}]=z(y^{2}+2yz+z^{2}+y^{2}+yz+y^{2})=z(3y^{2}+3yz+z^{2})$$
得到方程：
$$z(3y^{2}+3yz+z^{2})=n$$
再得到：
$$3y^{2}+3yz+(z^{2}-\frac{n}{z})=0$$
此时使用判别式为：
$$\Delta = (3z)^{2}-4\cdot3\cdot(z^{2}-\frac{n}{z})=9z^{2}-12z^{2}+\frac{12n}{z}=-3z^{2}+\frac{12n}{z}$$
那么
$$y=\frac{-3z+\sqrt{\Delta}}{6}$$
为了使 $y$ 为正整数，$\Delta$ 一定为非负的完全平方数。即
$$-3z^{2}+\frac{12n}{z}\ge0\Rightarrow \frac{12n}{z}\ge3z^{2}\Rightarrow 4n\ge z^{3}$$

接下来就可以开始枚举 $z$ 了，刚才得到 $4n\ge z^{3}$，所以枚举直到 $z^{3}>4n$，接下来判断
1. $z$ 是否为 $n$ 的因数。
2. 判断 $\Delta$ 是否为非负的完全平方数。
3. 判断 $y$ 是否为正整数。

以上条件都满足，则称为找到了一组 $x$ 与 $y$，$x=y+z$，立即输出并结束程序即可。

如果枚举完所有的 $z$ 后仍没有找到合适的答案，则输出 `-1`。

注：这种写法本题会炸 `long long`，但开 `unsigned long long` 即可。

## AC Code
```cpp
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long double db;
typedef unsigned long long ll;
const int INT_INF = 0x3f3f3f3f;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
// ----------------------------

// ----------------------------

// ----------------------------


int main() {
	ll n; cin >> n;
	// ----------------------------
	ll d, s, y, x;
	for (ll z = 1; z * z * z <= n * 4; z++) {
		if (n % z != 0) continue;
		d = -3 * z * z + 12 * (n / z);
		if (d < 0) continue;
		s = sqrt(d);
		if (s * s != d) continue;
		y = (-3 * z + s) / 6;
		if (y <= 0) continue;
		x = y + z;
		cout << x << ' ' << y;
		return 0;
	}
	// ----------------------------
	cout << -1;
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[AT_abc397_d [ABC397D] Cubes](https://www.luogu.com.cn/problem/AT_abc397_d)

招笑主播看成了 $x^3+y^3$，还在暗自嘲笑水题一道。

### 题意简述

求出一组 $x^3-y^3=N$，或报告无解。

### 做题过程

设 $a=x-y$，$b=x^2+xy+y^2$，根据立方差公式 $ab=N$。

考虑枚举 $a$，证明下取值范围：

$b=x^2+xy+y^2>(x-y)^2$，所以 $a^3<N$。

由于主播只会解一元二次方程，所以代入 $x=y+a$，得到：

$b=(y+a)^2+(y+a)y+y^2=3y^2+3ay+a^2$，即：

$3y^2+3ay+(a^2-b)=0$。

解方程得 $y=\dfrac{-3a\pm\sqrt{\Delta}}{6}$，其中 $\Delta=12b-3a^2$。

只有当 $\Delta$ 为完全平方数时，方程可能有整数解，所以要判断。同时 $y$ 是正整数，所以只能取正的 $\sqrt{\Delta}$。

因此判断 $\sqrt{\Delta}-3a$ 是否是 $6$ 的倍数即可求出 $y$。

$x$ 为 $y+a$，所以再判断一下是否都是正整数即可。

### 代码编写

注意结果可能很大，所以请使用 `__int128` 或 `double`。

```cpp
#include<iostream>
#include<cmath>
using namespace std;
void write(__int128 x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int main(){
	long long n;
    cin>>n;
    for(__int128 a=1,b,x,y;a*a*a<n;a++){
    	b=n/a;
    	if(a*b==n){//3y^2+3ay+(a^2-b)=0
    		double d=12*b-3*a*a;
    		__int128 k=sqrt(d);
    		if(k*k==d){
    			y=k-3*a;
    			if(y%6==0){
    				y/=6;
    				x=y+a;
    				if(x>0&&y>0){
    					write(x);
    					putchar(' ');
    					write(y);
    					return 0;
					}
				}
			}
		}
	}
	cout<<-1;
    return 0;
}
```

[AC on At](https://atcoder.jp/contests/abc397/submissions/63851549)。

---

## 作者：LionBlaze (赞：1)

首先我们思考能不能直接枚举 $x$ 和 $y$。

但是这俩邪恶的玩意儿并没有显然的上界。

显然 $x$ 和 $y$ 尽量接近时（差 $1$）则差最小，如果给定差则 $x$ 和 $y$ 最大。

假设 $x=y+1$，则 $(y+1)^3-y^3$ 是一个二次多项式，故时间复杂度是 $\mathcal O(\sqrt N)$ 级别的，无法承受。

上面的推导启发我们设 $x=y+k$。

一通推导猛如虎，我们知道 $k(3y^2 + 3yk + k^2) = N$。这样显然左式大于等于 $k^3$，故枚举 $k$ 是 $\mathcal O(\sqrt[3] N)$ 级别的。

那么我们知道了 $k$（显然 $k$ 需要是 $N$ 的因数），就可以列方程了。

$$ 3y^2 + 3ky + \left(k^2 - \dfrac{N}{k}\right) = 0 $$

使用求根公式。注意到求根公式中有根号，所以如果 $\sqrt \Delta$ 不是整数，则这种情况直接无解，因为 $\sqrt \Delta$ 不是整数而 $b,a$ 是整数，则 $\dfrac{-b \pm \sqrt \Delta}{2a}$ 不可能是整数，然而 $x,y$ 是正整数。

具体地，我们注意到 $\Delta = 9k^2 + 12(\frac{N}{k}-k^2)$。使用大脑思考就可以知道，最大是 $9k^2+\frac{12N}{k}$，当 $k=1$ 时达到 $12N$，超出 C/C++ 中的 `long long` 类型，需要使用 `unsigned long long`（Python 等自带高精度的语言就无此问题）。

同时，因为 $k^3 \le N$，所以 $\Delta\ge 0$ 恒成立，无需判断。

因为 C/C++ 的 `sqrt` 函数有精度问题（其它语言我不太清楚，不过应该多多少少都有一些精度问题吧），所以我们需要自己实现一个二分计算。

在二分 $\sqrt m$ 过程中，因为我们知道的二分上界就是 $m$，故 $\text{mid}^2$ 会达到一个 `long long * long long` 的级别，可以用 `__int128`，但是为了可移植性可以把 $\text{mid}^2 \ge m$ 转化为 $\text{mid} \ge \dfrac{m}{\text{mid}}$。

[Accepted](https://atcoder.jp/contests/abc397/submissions/63815671)。同时吐槽一下洛谷 RMJ。

---

## 作者：wrh316 (赞：1)

### 思路
首先，利用立方差公式 $x^3 - y^3 = (x - y)(x^2 + xy + y^2)$，将问题转化为寻找两个因数的组合。

然后，枚举可能的差值 $i = x - y$，并检查 $i$ 是否为 $n$ 的因数。

最后，对于每个合法的 $i$，构造二次方程并求解 $y$，验证是否存在正整数解。

因为 $i$ 的范围最高可达到 $\sqrt[3]{4n}$，所以，枚举 $i$ 时到 $4n + 2$ 即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
bool check(ull n) {
    ull s = sqrt(n);
    return (s * s == n);
}
void calc(ull n) {
    ull maxn = cbrt(4 * n) + 2;
    for (ull i = 1; i <= maxn; i++) {
        if (n % i != 0) continue;
        ull k = n / i;
        ull tmp = 12 * k - 3 * i * i;
        if (tmp < 0) continue;
        if (!check(tmp)) continue;
        ull s = sqrt(tmp);
        if ((s - 3 * i) % 6 != 0) continue;
        ull y = (s - 3 * i) / 6;
        if (y <= 0) continue;
        if (3 * y * y + 3 * y * i + i * i != k) continue;
        cout << (y + i) << " " << y;
        return ;
    }
    cout << "-1";
    return ;
}
int main() {
    ull n;
    cin >> n;
    calc(n);
    return 0;
}
```

---

## 作者：kairuigg (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc397_d)

### 题目大意
给定一个整数 $N$ $(1\le N\le 10^{18})$，判断是否存在一对整数 $(x,y)$，使得 $x^3-y^3=N$，如果存在请输出这样的一对 $(x,y)$，不存在请输出 $-1$。
### 思路
看到立方差，我们想到立方差公式 $x^3-y^3=(x-y)\times(x^2+xy+y^2)$。我们发现 $x-y$ 并不好看所以我们考虑换元。我们将 $x-y$ 换成 $d$，那么我们就可以得到 $x=d+y$，那么立方差公式就变成 $d\times[(y+d)^2+(y+d)y+y^2]$，所以我们只需要判断上式是否等于 $n$ 就可以了。我们发现左边的式子是三次的，所以我们枚举 $d$ 到 $10^6$ 就可以了。我们将 $d$ 除到右边，那么我们就需要判断 $(y+d)^2+(y+d)y+y^2=\frac{n}{d}$ 是否成立。将式子化简后就变成 $3y^2+3yd+d^2-\frac{n}{d}=0$，我们发现这是个一元二次方程，所以我们只需要用求根公式将两个根求出来，若根是正整数那么就说明有解，若将 $d$ 从 $1$ 枚举到 $10^6$ 都没有正整数根，那么就说明没有解，直接输出 $-1$。
### Code
一定记得开```unsigned long long```，不然会溢出！！！
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    #define int unsigned long long
    int n;
    cin>>n;
    int mx=pow(n,1.0/3);
    for(int d=1;d<=mx;d++){
        if(n%d!=0){
            continue;
        }
        int dis=-3*d*d+(12*n)/d;
        if(dis<0){
            continue;
        }
        int s=sqrt(dis);
        if(s*s!=dis){
            continue;
        }
        int y1=(-3*d+s)/6;
        int y2=(-3*d-s)/6;
        if(y1>0&&!((-3*d+s)%6)){
            int x=y1+d;
            if(x*x*x-y1*y1*y1==n){
                cout<<x<<" "<<y1;
                return 0;
            }
        }
        if(y2>0&&!((-3*d-s)%6)) {
            int x =y2+d;
            if (x*x*x-y2*y2*y2==n){
                cout<<x<<" "<<y2;
                return 0;
            }
        }
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：lyx128 (赞：0)

本体考虑使用立方差公式：$x^3-y^3=(x-y)(x^2+xy+y^2)=N$。

我们考虑对输入的 $N$ 进行因数分解（设 $k$ 是 $N$ 的一个因子），即可得出 $x-y=k$ 和 $(x^2+xy+y^2)=\frac{N}{k}$。

移项可得 $x=k+y$，带回 $(x^2-xy+y^2)=\frac{N}{k}$ 可得 $3y^2+3ky+k^2=\frac{N}{k}$，便可考虑解出本方程的正根 $y$ ，最后求出 $x$ 的值。

其它题解所写的二分和直接求根的方法较慢（乱搞除外），我们考虑使用高速的牛顿迭代法，它可以以 $O(\log \log E)$（$E$ 为精度要求）的速度求出各类由平滑函数式构成的方程，如自然常数 $e$，甚至是 $\pi$。

那么，我们就开始推导吧！以下为标准式 $x_i=x_{i-1}-\frac{f(x_{i-1})}{f'(x_{i-1})}$，其中 $f(x_{i-1})$ 表示当 $x=x_{i-1}$ 时 $y$ 的值，而 $f'(x_{i-1})$ 为值为 $x_{i-1}$ 时的函数导数，众所周知函数 $ax^k$ 的导数为 $a k x^{k-1}$，所以对于一个二次函数 $f(x)=ax^2+bx+c$ 的导数 $f'(x)$ 为 $2ax+b$。

于是，便可以写出一份~~快到起飞~~的代码了，写的时候请注意精度问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;

double f(ll a,ll b,ll c,double x){
	return (double)a*x*x+(double)b*x+(double)c;
}

double df(ll a,ll b,ll c,double x){
	return (double)2*a*x+(double)b;
}

double newton(ll a,ll b,ll c){
	double x=1;
	while(abs(df(a,b,c,x))<=1e-4)
		x=(ll)rand()*rand();
	for(int i=1;i<=50&&abs(f(a,b,c,x))>=1e-4;i++)
		x=x-f(a,b,c,x)/df(a,b,c,x);
	return x;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(ll k=1;k*k*k<=n;k++)
		if(!(n%k)){
			double res=newton(3,3*k,k*k-n/k);
			if(res-floor(res)<=1e-3&&res>=1){
				cout<<k+(ll)res<<" "<<(ll)res<<"\n";
				return 0;
			}
		}
	cout<<-1<<"\n";
	return 0;
}
```

最后，推荐几道可以用牛顿迭代法实现的板子题：
- [AT_code_formula_2014_qualA_a 立方数](https://www.luogu.com.cn/problem/AT_code_formula_2014_qualA_a)
- [UVA10428 The Roots](https://www.luogu.com.cn/problem/UVA10428)

---

## 作者：Tjaweiof (赞：0)

# AT_abc397_d 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc397_d)

根据题意 $n=x^3-y^3=(x-y)(x^2+xy+y^2)$，设 $u=x-y$，于是

$$
\begin{aligned}

&n\\

=&x^3-y^3\\

=&(x-y)(x^2+xy+y^2)\\

=&u(x^2+x(x-u)+(x-u)^2)\\

=&3ux^2-3u^2x+u^3\\

\end{aligned}
$$

于是我们只需要枚举 $n$ 的因数 $u$，然后解一个一元二次方程 $3ux^2-3u^2x+u^3-n=0$，并判断 $x$ 是否为整数就行了。

可是枚举 $n$ 的因数至少需要 $O(\sqrt n)$，时间会炸。

我们发现当 $u>10^6$ 时 $n=(x-y)(x^2+xy+y^2)\ge ux^2\ge u^3>10^{18}$，所以直接不管。

## Code
赛时想的是 $O(\sqrt n)$+卡常，所以代码有点难看，但是应该还是能看懂的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
long long n;
void f(__int128 i){
	__int128 i2 = i * i, i4 = i2 * i2;
	double d = (i * n << 3) + (i * n << 2) - (i4 << 1) - i4;
	__int128 q = sqrt(d);
	__int128 x = ((i2 << 1) + i2 + q) / ((i << 2) + (i << 1));
	if (q * q != d || ((i2 << 1) + i2 + q) % ((i << 2) + (i << 1)) || x - i <= 0){
		return;
	}
	cout << (long long)x << " " << (long long)(x - i);
	exit(0);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (long long i = 1; i * i <= n && i <= 1e6; i++){
		if (n % i){
			continue;
		}
		f(i);
		if (i * i != n){
			f(n / i);
		}
	}
	cout << "-1";
	return 0;
}
```

---

## 作者：rzt123 (赞：0)

# [Cubes](https://atcoder.jp/contests/abc397/tasks/abc397_d)

标签：数学、枚举

## 题目大意

给你一个数 $N$ , 求出一个数对 $(x,y)$ 满足 $x^3-y^3=N$。

## 分析

首先由立方差公式可得 $x^3-y^3=(x-y)(x^2+xy+y^2)=N$ 也就是说 $x-y$ 和 $x^2+xy+y^2$ 都必须是 $N$ 的因数。相当于我们要找一对数 $(a,b)$ 使得 $a \times b=N$ 并且 $a=x-y , b=x^2+xy+y^2$。

接下来就要开始推式子了。

因为 $a=x-y$ 所以 $x=a+y$。

将其带入 $b=x^2+xy+y^2$ 得 $b=(a+y)^2+(a+y)y+y^2 = 3y^2+3ay+a^2$。

我们可以枚举 $N$ 的所有因数对 $(a,b)$，然后判断是否有正整数 $y$。

具体的我们要解一个一元二次方程 $3y^2+3ay+a^2-b=0$。

设这个方程的判别式为 $D=(3a)^2-12(a^2-b)=-3a^2+12b$。

要使方程有解 $D$ 必须非负 既 $-3a^2+12b\ge0$ 解得 $b\ge \frac{a^2}{4}$，也就是说当我们枚举的 $a,b$ 必须要满足这个式子，如果不对直接跳过即可。

由于 $y$ 是正整数，那么判别式 $D$ 就必须是完全平方数，设 $D=k^2$，则 $y=\frac{-3a\pm k}{6}$ 那么 $-3a\pm k$ 必须是正整数，并且是 $6$ 的倍数。

则 $y$ 有两个解 $y_1=\frac{-3a+k}{6}$ 和 $y_2=\frac{-3a-k}{6}$ 但是由于 $a,k,y$ 都是正整数，所以 $y_2$ 一定是负数，直接舍弃掉。

自此我们成功求出了 $y$ 那么 $x$ 直接算即可。

那么这道题就这样结束了吗？并非，我们注意到 $N\le 10^{18}$ 那么枚举因数是 $O(\sqrt{N})$ 的，很明显不行。

那么我们就要确定 $a$ 的范围，刚才我们得出 $b \ge \frac{a^2}{4}$ 既 $\frac{N}{a} \ge \frac{a^2}{4}$ 移项得 $a^3\le 4N$ 那么 $a$ 的范围就是 $a \le \sqrt[3]{4N}$。

总结一下，这题的步骤为

1. 枚举一个数 $a$ , 其中 $a \le \sqrt[3]{N}$。
2. 判断 $a$ 是否为 $N$ 的因数，若是计算 $b=\frac{N}{a}$ 并判断 $a,b$ 是否满足 $b \ge \frac{a}{4}$
3. 检查判别式是否为完全平方数
4. 解一元二次方程 $3y^2+3ay+a^2-b=0$，判断 $y$ 是否为正整数

[code](https://atcoder.jp/contests/abc397/submissions/63832398)

---

## 作者：da_ke (赞：0)

> fyy 是一个珂愛的女孩子。
>
> 她从一个长 $x$ 的立方体中扣掉一个长 $y$ 的立方体，使得剩下的体积为 $N$。问是否存在这样的方案。
>
> 即解不定方程 $x^3-y^3=N$。

珂愛的我发现 $(x-y)(x^2+xy+y^2)=N$。

设 $x-y=d$，配方化简：$d[(x-y)^2+3xy]=d(d^2+3xy)=d^3+3dxy=N$。

先确定 $d$ 的范围，$d^3=N-3dxy\leq N,d\leq \sqrt[3]{N}$。

不慌，刚才的 $(x-y)(x^2+xy+y^2)=N$ 中，$d,x^2+xy+y^2$ 都应当是 $N$ 的因数，自然也都是**整数**，于是 $x^2+xy+y^2=\dfrac{N}{d}$。同时 $N \equiv 0 \pmod d$。

$x=y+d$，带入得 $(y+d)^2+y(y+d)+y^2-\dfrac{N}{d}=3y^2+3dy+d^2-\dfrac{N}{d}=0$。将 $y$ 看为主元，可解出 $(x,y)$。

$d$ 可以直接枚举，然后解一元二次方程即可。这道题告诉我们一个方法：$N\leq 10^{18}$ 时可以用 $O(\sqrt[3]{N})$ 得算法解决。

最后用大蟒蛇实现一下：[提交记录](https://atcoder.jp/contests/abc397/submissions/63830230)。

```python
import math

N = int(input())
D = int(round(N ** (1/3))) + 1

for d in range(1, D + 1):
    if N % d == 0:
        k = N // d
        a = 3
        b = 3 * d
        c = d * d - k
        dt = b**2 - 4 * a * c 
        if dt < 0:
            continue
        sd = math.isqrt(dt) 
        if sd * sd != dt:  
            continue
        y = (-b + sd) // (2 * a) 
        if y > 0 and (a * y * y + b * y + c) == 0: 
            x = y + d
            print(x, y)
            exit(0)
print(-1)

# 路虽远行则将至，事虽难做则必成。
```

注：这个思路用 `C++` 应该也不会卡精度的。

終。

---

## 作者：cyq32ent (赞：0)

初中数学题。

$N=x^3-y^3=(x-y)((x-y)^2+3xy)$，所以 $xy=\frac{\frac N{x-y}-(x-y)^2}3$。又由于 $x,y>0$，所以 $x=\frac {x-y+\sqrt{(x-y)^2+4xy}}2$，$y=\frac {-(x-y)+\sqrt{(x-y)^2+4xy}}2$。由于 $(x-y)^3<(x-y)((x-y)^2+3xy)=x^3-y^3=N$，所以只需枚举 $x-y$，然后计算出相应的 $x$ 与 $y$ 即可。我们事实上不用判断整除，因为我们只需再判断一次 $x^3-y^3$ 是否真的为 $N$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	using ll=long long;
	ll N;
	cin>>N;
	for(ll a=1;a*a*a<N;a++){
		ll d=sqrt((4*N/a+a*a)/3);
		ll x=(a+d)>>1,y=(-a+d)>>1;
		if(x*x*x-y*y*y==N)cout<<x<<' '<<y<<endl,exit(0);
	}cout<<-1;
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 0 - 前言

这数学题实在是太难评了哇哇哇。比赛最后二十秒才过。

[![](https://pic1.imgdb.cn/item/67d58f6f88c538a9b5bed30c.png)](https://pic1.imgdb.cn/item/67d58f6f88c538a9b5bed30c.png)

# Part 1 - 题目大意

善良的数学 Hu 老师给你一个正整数 $N$ 作为家庭作业。你的任务是判断是否存在一对正整数 $(x,y)$，使得 $x^3 - y^3 = N$。如果存在这样的一对，请告诉 Hu 老师。

由于 Hu 老师非常善良，$1 \le N \le 10^{18}$。

没有特指任何人哈，如有雷同纯属巧合。

# Part 2 - 算法思路

## 2-1 尝试枚举两数之一

拿到题目后你可能会以为 $x \le \sqrt[3]{N}$，但是这道题目的要求与 $x^3+y^3=N$ 是本质不同的。

可以考虑极端情况，也就是 $x=y+1$，此时可以发现 $x$ 会高达 $\sqrt{N}$ 级别，显然是不能枚举的。

于是，你破防了。

## 2-2 从两数之差下手

让我们转化一下思路。既然给了你时间，肯定是得枚举点啥的，对吧？

两个数之间有啥关系呢，无非就是加减乘除，然而题面里是立方差，那我们也来看看两数之差。

你可以试一试，会发现 $x-y \le 2 \times 10^6$。如果你不想停留在仅仅是感性理解，可以尝试一下数学证明。

## 2-3 数学证明，启动！

求证：已知正整数 $x, y$ 满足 $x^3 - y^3 \le 10^{18}$，试证明 $x - y \le 2 \times 10^6$。

证明：利用立方差公式，将 $x^3 - y^3$ 分解为：

$$x^3 - y^3 = (x - y)(x^2 + xy + y^2)$$

根据题意，有：

$$(x - y)(x^2 + xy + y^2) \le 10^{18}$$

令 $x = y + k$，其中 $k = x - y \ge 1$，代入原式得：

$$k \cdot \left( (y + k)^2 + (y + k)y + y^2 \right) \le 10^{18}$$

展开并整理：

$$k \cdot (3y^2 + 3ky + k^2) \le 10^{18}$$

将上式视为关于 $y$ 的二次不等式：

$$3k \cdot y^2 + 3k^2 \cdot y + (k^3 - 10^{18}) \le 0$$

该不等式存在解的必要条件是判别式非负。

计算判别式：

$$D = (3k^2)^2 - 4 \cdot 3k \cdot (k^3 - 10^{18}) = -3k^4 + 12 \times 10^{18}k$$

要求 $D \ge 0$，即：

$$3k^4 + 12 \times 10^{18}k \ge 0 \implies k^3 \le 4 \times 10^{18}$$

对 $k^3 \le 4 \times 10^{18}$ 两边开立方，得：

$$k \le (4 \times 10^{18})^{\frac{1}{3}} = 4^{\frac{1}{3}} \times 10^6 \approx 1.5874 \times 10^6$$

由于 $1.5874 \times 10^6 < 2 \times 10^6$，因此 $k \le 2 \times 10^6$。

## 2-4 从枚举差值到二分答案

聪明的你发现这个差非常的小，说明可以枚举。

我们假设这个差是 $k$，那么 $y=x-k$。于是呢，根据单调性，我们可以考虑二分一下这个 $x$，来使得 $x^3-(x-k)^3$ 逼近 $N$。就是二分出最大的 $x$，满足 $x^3-(x-k)^3 \le N$。

然后我们判断一下这个二分出的 $x$ 是否满足 $x^3-(x-k)^3=N$ 就可以啦。

根据前面我们算出的答案上限，二分的上限可以调为 $\sqrt{N}$。

## 2-5 时间和空间复杂度

空间复杂度显然是优秀的 $O(1)$。

根据我们的证明，这个 $k$ 的上限就是 $4N^{\frac{1}{3}}$。二分显然是 $\log \sqrt{N}$。

所以去掉常数，此题的时间复杂度是 $O(N^{\frac{1}{3}}\log \sqrt{N})$。很抽象对吧。

# Part 3 - 代码实现

你们要的代码来了，快读快写就不放了。

似乎是要开 `long long` 和 `__int128` 之类的，不然可能会见祖宗。

```cpp
ll tc = 1;
__int128 n;
__int128 s3(__int128 x) {
	return x * x * x;
}

void init() {
	;
}

void solve() {
	init();
	n = read();
	for (ll i = 1; i <= 2e6; i++) {
		ll l = i + 1, r = 1e9, res = 1e9;
		while (l <= r) {
			ll m = (l + r) >> 1;
			if (s3(m) - n > s3(m - i)) {
				r = m - 1;
			} else {
				l = m + 1;
				res = m;
			}
		}
		l = res;
		r = l - i;
		if (s3(l) - n == s3(r)) {
			write(l), putchar(' '), write(r);
			return;
		}
	}
	write(-1);
}
```

完结撒花！这么好的题解就点点赞吧！

---

