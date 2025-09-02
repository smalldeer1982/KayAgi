# [BalticOI 热身赛] Roses

## 题目背景

因为特殊原因，本题目另外 $24$ 组数据请在 [这里](https://www.luogu.com.cn/problem/U127462) 提交。

Valentine 是人赢。

## 题目描述

现在 Valentine 要给他的 $N$ 个妹子买玫瑰花，现在 Valentine 面前有两家店，每一家店有无数朵玫瑰花，但是他们按束卖。第一家店一束花里有 $A$ 朵，每一束花要用 $B$ 块钱。第二家店一束花里有 $C$ 朵，每一束花要用 $D$ 块钱。

求 Valentine 至少买 $N$ 朵花最少需要花多少钱。

至少可以这么理解，假如 $M>N$，但是买 $M$ 朵花的钱比买 $N$ 朵花的少，Valentine 就会买 $M$ 朵花，并把多出来的花给其他妹子，没错，Valentine 很花心。

## 说明/提示

#### 样例说明

对于样例 $1$，Valentine 可以选择在第二家店买 $2$ 束花。

对于样例 $2$，Valentine 可以选择在第一家店买 $1$ 束花，在第二家店买 $2$ 束花。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$N,A,B,C,D \le 1000$。
- Subtask 2（80 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N \le 10^{15}$，$1 \le A,B,C,D \le 10^5$，保证答案不超过 $10^{18}$。

#### 说明

翻译自 [BalticOI 2020 Day0 B Roses](http://www.boi2020.lv/data/tasks/en/day0/roses.pdf)。

与 BalticOI 2012 Day0 A 内容一致。

## 样例 #1

### 输入

```
5 1 4 3 6```

### 输出

```
12```

## 样例 #2

### 输入

```
22 2 3 10 14```

### 输出

```
31```

# 题解

## 作者：sysong (赞：9)

# 题解 P6767 [BalticOI 2020/2012 Day0] Roses

用一种奇怪的姿势过了这题，还成了当时最优解，写一篇题解纪念一下。

## 题意

要买$N$朵花，每$A$朵$B$元，每$C$朵$D$元，问最少要花多少元。

## 思路

### 注意：开 $long\ long$ !

### 因为$N \le 10^{18}$

首先挑便宜的买，然而——会多买，所以考虑用另外一种替换掉多余部分。

所以，我们可以写出代码片段：

---

($ll$代替$long\ long$,$ld$代替$long\ double$)

```c++
ll n=rd(),a=rd(),b=rd(),c=rd(),d=rd(),ans=1e18;			// a,b,c,d 严格按照题目要求， ans 记录最小值

ld x=b*1.0/a,y=d*1.0/c;									// x,y 分别为 a,b 种花的单价

if(x>y)swap(a,c),swap(b,d);								// 如果 a 的单价贵，那么交换，保证 a 的单价低

ll s=(n+a-1)/a;											// 单价低的至少要买 s 束
														// 这里 +a-1 相当于 ceil 函数

for(R ll i=s,k;i>=0;i--)								// 总共有 s 种不过于浪费的买法
{
	k=i*b+max((ll)0,n-i*a+c-1)/c*d;						// i*b 表示 a 种的总价格，
    													// n-i*a 表示剩余需要花的朵数，同上求出总价格
	if(k<ans)ans=k;										// 打擂台选取最小值
}

printf("%lld\n",ans);
```
---
然后，我们就这样提交，然而——取得了[TLE](https://www.luogu.com.cn/record/39102559)的好成绩，还有一个点过不了。



怎么办呢？

我们发现，当我们把多买的部分替换掉之后，$k$是会增加的（本来就挑便宜的买的嘛）

那是不是——

---

```c++
for(R ll i=s,k,f=1;i>=0&&f;i--)							// 在这里设置一个 flag f ，如果价格开始增加，
														// 那么就不用再循环下去了
{
	k=i*b+max((ll)0,n-i*a+c-1)/c*d;
	if(k<ans)ans=k;
	else f=0;											// 相当于 break; 
}
```
---
继续——[WA](https://www.luogu.com.cn/record/39102541)



难道没有办法了吗？

还有什么问题？

我们再次发现（太难了）：

我们拿掉的部分加上新买的部分，可能还是会多买。

~~看来也许我们是冤枉他了~~

怎么解决呢？

我们看到上面那位dalao写了个$lcm$（最小公倍数）来限制循环次数，实际上不需要。

**因为$A,C \le 10^{5}$！**

**我们最多只要循环$10^{5}$就足以计算可能最优的情况了！**

**（求$lcm$还要花时间，而且$A$,$C$的$lcm$还可能比$10^{5}$大）**


那么就很简单了

### $C++\ \ \ Code$

---

```c++
#include <bits/stdc++.h>
#define R register
#define gc() getchar()
#define ll long long
#define ld long double
using namespace std;

inline ll rd(){
	R ll x=0;R char c=gc();
	while(c>'9'||c<'0')c=gc();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;
}																// 快读加速

int main(){
	ll n=rd(),a=rd(),b=rd(),c=rd(),d=rd(),ans=1e18;
	ld x=b*1.0/a,y=d*1.0/c;
	if(x>y)swap(a,c),swap(b,d);
	ll s=(n+a-1)/a;
	for(R ll i=s,k,f=100000;i>=0&&f;i--,f--)					// 用 f 来限制循环次数
		{
			k=i*b+max((ll)0,n-i*a+c-1)/c*d;
			if(k<ans)ans=k;
		}
	printf("%lld\n",ans);
	return 0;
}
```
---
### 终于$AC$了！（另外$24$组数据也已过）
---

###### 码字不易，望通过！

***by jsntsys***

$2020.10.3$



---

## 作者：zjh111111 (赞：4)

[$link$](https://www.luogu.com.cn/problem/P6767)

$ps:$ $a\ $ $c$ 为每束的朵数，$b\ $ $d$ 为每束的钱

设 $a\ $ $b$ 比 $c\ $ $d$性价比高，即

$$\frac{b}{a}<\frac{d}{c}$$

$$bc<ad$$

显然买 $a$ 束 $c$ （$ad$块钱）不如买 $c$ 束 $a$ （$bc$块钱），所以枚举性价比低的个数即可。

复杂度$\mathcal{O(a)}$

```cpp
#include <bits/stdc++.h>
#define int long long //注意long long
using namespace std;
template <typename T>
inline void read(T &x) {
	char c = getchar(); int w = 1; x = 0;
	while (!isdigit(c))
		(c == '-') && (w = -w), c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
	x *= w;
}

int n, a, b, c, d, ans = 1e18;
inline int gcd(int x, int y) {
	return (!y) ? x : gcd(y, x % y);
}
signed main() {
	freopen("roses.in", "r", stdin);
	freopen("roses.out", "w", stdout);
	read(n); read(a); read(b); read(c); read(d);
	if (a*d < b*c) swap(a, c), swap(b, d);
	for (register int i=0; i<=a/gcd(a, c); ++i) {//到a也一样
		int x = n-c*i, res = i*d;
		if (x > 0) res += ((x-1)/a+1)*b;//类似于分块中的i号在第(i-1)/a+1块中
		ans = min(ans, res);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：3)

先买性价比高的花一定最优。假设 $a$ 朵 $b$ 元性价比最高，那么有 $\dfrac{b}{a}<\dfrac{d}{c}$，同乘 $ac$，得 $a\times d>b\times c$。先计算按每组 $a$ 朵买的花费，再去枚举买了 $x$ 组 $c$ 朵的情况。

直接枚举肯定会超时，那么考虑如何找到枚举的上界。如果 $x\times c=y\times a$，就意味着我们可以通过买 $y$ 组 $a$ 朵的方式做到比买 $x$ 组 $c$ 朵更优，因为后者性价比高。所以枚举到 $\dfrac{a}{\gcd(a,c)}$ 即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,c,d,ans=1145141919810000;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int getcost(int sum,int flo,int cost){
	if(sum<=0)return 0;
	if(sum%flo==0)return sum/flo*cost;
	else return (sum/flo+1)*cost;
}
signed main(){
	//freopen("std.in","r",stdin);
	n=read();a=read();b=read();c=read();d=read();
	//b/a<d/c->ad>bc
	if(a*d<b*c){
		swap(a,c);
		swap(b,d);
	}
	int k=a/__gcd(a,c);//枚举上限
	ans=getcost(n,a,b);
	for(int i=1;i<=k;i++){
		ans=min(ans,i*d+getcost(n-i*c,a,b));
	} 
	cout<<ans;
	return 0;
}


```


---

## 作者：WarningQAQ (赞：3)

# 题解 P6767 【[BalticOI 2020/2014 Day0] Roses】

看到这题让我想到了小学的学生外出乘车选车。

~~建议难度评个**普及/提高-**~~。
### 分析：
定义 $x$ , $y$ 分别是第一家和第二家店一朵玫瑰花的价格，
先只买每朵价格比较小的一家店，记录为 $ans$ 。

再计算两家店每束花的最小公倍数确定枚举次数，
然后枚举更换每束花后的价格来跟 $ans$ 进行比较。更新 $ans$ 。

------------
### 光说不行，得上代码：
```cpp
#include "cstdio"
#include "algorithm"
#include "iostream"
long long n, a1, a2, b1, b2, ans, go;
int main() {
    std::cin >> n >> a1 >> b1 >> a2 >> b2;
    long double x = b1 * 1.0 / a1, y = b2 * 1.0 / a2;
    if (x < y)
        std::swap(a1, a2), std::swap(b1, b2);//为了方便之后的枚举
    ans = (n + a2 - 1) / a2 * b2;
    go = a2 / std::__gcd(a1, a2);
    for (long long i = go; i >= 0; i--) {
        long long t = i * b1;
        if (n - i * a1 >= 0)
            t = t + (n - i * a1 + a2 - 1) / a2 * b2;
        ans = std::min(ans, t);
    }
    std::cout << ans;
    return 0;
}

```

------------

Valentine 是人赢。

---

## 作者：happy_dengziyue (赞：1)

### 1 思路

我们不妨设 $a$ 朵 $b$ 元方案是**性价比最高**的，即 $\dfrac{b}{a}\le\dfrac{d}{c}$，可以化为 $a\times d\ge b\times c$。

我们要先算出只买 $a$ 朵方案要多少钱，以备后面比较。但我们肯定不能只买 $a$ 朵方案。我们还要枚举一遍 $c$ 朵方案花费多少钱。

设买 $i$ 组 $c$ 朵方案，我们要从 $1$ 枚举到 $i\times c\le n$，最多枚举 $\dfrac{n}{c}$ 次，时间绝对爆炸。

如果 $i\times c\equiv0(\operatorname{mod}a)$，那么很明显，与之于买 $i$ 组 $c$ 朵方案，不如买 $\dfrac{i\times c}{a}$ 组 $a$ 方案。因为：

$$\begin{aligned}a\times d\ge&b\times c\\i\times d\ge&\dfrac{i\times c\times b}{a}\end{aligned}$$

所以，我们让 $i$ 只枚举到 $\dfrac{a}{\operatorname{gcd}(a,c)}$ 即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
long long n;
long long a;
long long b;
long long c;
long long d;
long long k;
long long ans;
long long gcd(long long a,long long b){
	if(!b)return a;
	return gcd(b,a%b);
}
long long cst(long long n,long long a,long long b){
	if(n<=0)return 0;//坑点
	if(n%a)return (n/a+1)*b;
	return n/a*b;
}
long long mi(long long a,long long b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("P6767_1.in","r",stdin);
	freopen("P6767_1.out","w",stdout);
	#endif
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
	if(a*d<c*b){//交换
		a^=c^=a^=c;
		b^=d^=b^=d;
	}//然后选a朵b元是更优的
	ans=cst(n,a,b);//全选便宜的花费
	k=a/gcd(a,c);
	for(long long i=1;i<=k;++i){//枚举买i组c朵d元的花费
		ans=mi(ans,i*d+cst(n-i*c,a,b));
	}
	printf("%lld\n",ans);
	return 0;
}
```

[记录传送门（前 $100$ 组数据）](https://www.luogu.com.cn/record/69012057)

[记录传送门（后 $24$ 组数据）](https://www.luogu.com.cn/record/69012086)

By **dengziyue**

---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15719217.html)

# 题目大意

需要买 $n$ 朵花，现在有两家花店，价格分别是：$b$ 元每 $a$ 朵花和 $d$ 元买 $c$ 朵花。

给定 $n,a,b,c,d$，求最小价钱。

# 题目分析

两家花店单枝花的价格分别为：$\dfrac{b}{a}$ 元/朵、$\dfrac{d}{c}$ 元/朵。

设第一家花店的单价比第二家低，则有：$\dfrac{b}{a}<\dfrac{d}{c}$。

两边同时 $\times ac(ac>0)$ 得 $b\cdot c<d\cdot a$。

----
求解部分。

我们枚举在单价较高的花店买花的个数 $i$，这一家花店为 $i\times c$，于是另一家花店的就是 $n-c\times i$。

答案即为 $\min\{i\times d+[n-c\times i>0]\times(\dfrac{n-c\times i-1}{a}+1)\times b\}(0\le i\le \dfrac{a}{\gcd(a,c)})$。

其中 $[....]$ 表示 `[` 和 `]` 之间的逻辑语句是否为真。

---
注意事项：

+ 不开 `________` 见 `______`。

+ 最开始需保持第一家花店的单价低于第二家，如果不满足，交换即可。

# 代码

```cpp
//2021/12/22

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <climits>//need "INT_MAX","INT_MIN"

#include <cstring>//need "memset"

#include <algorithm>

#define int long long

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

#define speed_up() cin.tie(0),cout.tie(0)

#define endl "\n"

#define Input_Int(n,a) for(register int i=1;i<=n;i++)scanf("%d",a+i);

#define Input_Long(n,a) for(register long long i=1;i<=n;i++)scanf("%lld",a+i);

#define mst(a,k) memset(a,k,sizeof(a))

namespace Newstd
{
	inline int read()
	{
		int x=0,k=1;
		char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				k=-1;
			}
			ch=getchar();
		}
		while(ch>='0' && ch<='9')
		{
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		return x*k;
	}
	inline void write(int x)
	{
		if(x<0)
		{
			putchar('-');
			x=-x;
		}
		if(x>9)
		{
			write(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int INF=0x3f3f3f3f3f3f3f;

int n,a,b,c,d;

inline int gcd(int a,int b)
{
	if(b==0)
	{
		return a;
	}
	
	return gcd(b,a%b);
}

#undef int

int main(void)
{
	#define int long long
	
	n=read(),a=read(),b=read(),c=read(),d=read();
	
	if(a*d<b*c)
	{
		swap(a,c);
		
		swap(b,d);
	}
	
	int ans=INF;
	
	for(register int i=0;i<=a/gcd(a,c);i++)
	{
		int x=n-c*i,t=i*d;
		
		if(x>0)
		{
			t+=((x-1)/a+1)*b;
		}
		
		ans=min(ans,t);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：Genshineer (赞：0)

翻了一下已有的题解，似乎没有针对此题本质即线性规划做的题解，故作分享。

可以由此题抽象出一类问题的模型，做训练的效果还是非常好的。

## 题意简述

要选择 $N$ 个物品，有两种方案，每花费 $C$ 元可以买 $A$ 个，每花费 $D$ 元可以买 $B$ 个。

## 分析

对于这一题，题目有明确提示，可以买**大于等于** $N$ 朵花，于是不妨设花费 $A$ 元的次数为 $x_{1}$，花费 $C$ 元的次数为 $x_{2}$，于是得到不等式：

$$Ax_{1}+Cx_{2}\geq N(x_{1},x_{2}\geq 0)$$ 

于是题目转化为在满足上述条件的前提下求多项式 $Bx_1+Dx_2$ 的最小值。

让我们重新审视这个过程：

- 由题意得到多个变量。

- 得到包含所有变量的条件，并且条件是关于变量的线性不等式。

- 要求一个包含变量的**一次**多项式（PS：大部分情况下线性可以理解成变量次数为 $1$）的最值。

不难发现，这是一个经典的[线性规划](https://oi-wiki.org/math/linear-programming/)问题，即在线性**约束条件**下线性**目标函数**极值问题（引自[OI-Wiki](https://oi-wiki.org/math/linear-programming/#:~:text=%E7%A0%94%E7%A9%B6-,%E7%BA%BF%E6%80%A7%E7%BA%A6%E6%9D%9F%E6%9D%A1%E4%BB%B6%E4%B8%8B%E7%BA%BF%E6%80%A7%E7%9B%AE%E6%A0%87%E5%87%BD%E6%95%B0%E6%9E%81%E5%80%BC%E9%97%AE%E9%A2%98,-%E7%9A%84%E6%96%B9%E6%B3%95%E6%80%BB%E7%A7%B0)）。

名词解释：

1. 约束条件就是题目中变量要满足的的条件，例如此题即为 $Ax_{1}+Cx_{2}\geq N$ 与 $x_{1},x_{2}\geq 0$，一般情况下若无特殊说明，变量为非负整数即 $x_i \in N^+$ 是默认条件（结合线性规划这个问题模型本身就用来解决实际问题这一背景就很好理解了）。

2. 目标函数就是要求的式子构成的函数，此题可以看成 $z=Bx_1+Dx_2$。

## 求解

了解的问题的本质后，首先要将线性规划转化为**标准型**，即：目标函数取**最大值**（PS：这里网上各个教程不太相同，取更为通用的**最大值**进行讲解，网上也有讲解最小值的，可以查找一下加深理解）；所有的约束条件均为等式。

要怎么做呢？

对于目标函数的处理不难想到将原来的目标 $\min z=Bx_1+Dx_2$ 转化为 $-(\max z=-Bx_1-Dx_2)$，因此只要求出 $\max z=-Bx_1-Dx_2$ 就可以得到答案。

而对于条件 $Ax_{1}+Cx_{2}\geq N$，我们可以引入一个人工变量 $x_{3}$，同样 $x_3\geq0$，因为目标函数 $z$ 中不含有 $x_3$ 项，因此 $x_3$ 的取值不会影响结果。不妨先**假设**约束条件是**大于等于**，例如 $x_1+x_2\geq0$，那么很容易想到在 $x_3\geq0$ 的前提下直接在原式上加入 $x_3$ 项变为 $x_1+x_2+x_3=0$ 也符合条件，因为原目标函数**只可能**含有原本出现的 $x_1$ 和 $x_2$ 变量，所以 $x_3$ 的引入和取值都对结果没有任何影响。类比于此，可以得到对于**小于等于**这一条件我们可以在原约束的左侧做一个减去一个人工变量 $x_3$ 的处理，此时约束条件就可以变成 $Ax_1+Bx_2-x_3=N$。显然，等式是比不等式要好处理得多的。

此时我们就得到了这一题线性规划的标准型如下：

$
\max z=-Bx_1-Dx_2
$

$s.t.
\left\{
\begin{aligned}
Ax_1+Cx_2-x_3=N\cr
x_i\geq0,i=1,2,3
\end{aligned}
\right.$

同时可以将标准型转化为**矩阵**形式。

$\begin{bmatrix}-B & -D & 0 & 0\cr A & C & -1 & N\end{bmatrix}$

解释：线性规划标准型的矩阵形式第一行表示目标函数，除最后一项外均表示函数中对应变量的系数，其中人工变量均为 $0$，这样才不会影响结果。接下来每一行对应一个**等式**约束，除最后一项外均表示约束中对应变量的系数，最后一项表示等式右边的常数项。

至此线性规划模型就完成了建立，对于标准型的求解，可以套用[单纯形](https://oi-wiki.org/math/simplex/)算法的模板进行求解，这里不再赘述。由于矩阵唯一确定为 $2\times4$ 的矩阵，此时的时间复杂度近似常数，是一个相当优秀的算法。

---

## 作者：XXXxm (赞：0)

##### 本蒟蒻头一回写题解希望各位大佬不要嫌弃

#### [听说博客观赏更加](https://www.luogu.com.cn/blog/shencowbiantai/ti-xie-p6767-balticoi-20202012-day0-roses)

这道题一拿过来看到标签 ： 枚举、 **最大公约数 gcd**？ (原谅本弱一开始就没搞懂为什么和 ~~gcd~~ 有关系) 

那就照着题意模拟呗：

- 比较两种买法花的单价。
- 将较小值存在 $a$ 和 $b$ 中便于接下来枚举。
-  _a_ 买 $num$ 束，剩下的花用 _c_ 来买 $num$ 是 _a_ 至少要买的数量。
- **for 循环**枚举 $num$  取每次枚举的最小价格
- 高兴输出结果。

很好喜提 **TLE**。

然后我开始思考，想到原因可能就是因为 **gcd**？

于是我听了同机房数学大佬的解释，其实枚举到 $cnt = \dfrac{a}{\gcd(a,c)}$ 就已经 OK 了。

还有一点，大家要记得开 **long long**。

以下附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, a, c, b, d, num;
int main() {
	scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
	//计算两比较种方式一朵花的价格来买
	long double x = b * 1.0 / a;
	long double y = d * 1.0 / c;
	if (x < y) { //习惯将a存较优的值便于枚举
		swap(a, c);
		swap(b, d);
	}


	ll ans = (n + c - 1) / c * d;

	num = c / __gcd(a, c);
	for (ll i = num; i >= 0; i--) {
		ll t = i * b;
		if (n - i * a >= 0)
			t = t + (n - i * a + c - 1) / c * d;
		ans = min(ans, t);
	}


	printf("%lld",ans);
	return 0;
}
```


------------

 _祝各位大佬都一遍切掉这道水题_ 。

---

