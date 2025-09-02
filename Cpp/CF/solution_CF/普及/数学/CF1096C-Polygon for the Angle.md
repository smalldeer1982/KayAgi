# Polygon for the Angle

## 题目描述

You are given an angle $ \text{ang} $ .

The Jury asks You to find such regular $ n $ -gon (regular polygon with $ n $ vertices) that it has three vertices $ a $ , $ b $ and $ c $ (they can be non-consecutive) with $ \angle{abc} = \text{ang} $ or report that there is no such $ n $ -gon.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1096C/a07369ed7e451bdcca3873a15baacc5b09a55799.png)If there are several answers, print the minimal one. It is guarantied that if answer exists then it doesn't exceed $ 998244353 $ .

## 说明/提示

The answer for the first query is on the picture above.

The answer for the second query is reached on a regular $ 18 $ -gon. For example, $ \angle{v_2 v_1 v_6} = 50^{\circ} $ .

The example angle for the third query is $ \angle{v_{11} v_{10} v_{12}} = 2^{\circ} $ .

In the fourth query, minimal possible $ n $ is $ 180 $ (not $ 90 $ ).

## 样例 #1

### 输入

```
4
54
50
2
178
```

### 输出

```
10
18
90
180
```

# 题解

## 作者：nydzsf_qwq (赞：7)

这题其实根本不需要枚举任何东西。

正 $n$ 边形每个内角都是 $\dfrac{(n-2)\times180^{\circ}}{n}$，每个角都被分成了 $n-2$ 份。

这 $n$ 个点显然是公园的，每条边又相等，所以分出的 $n-2$ 个角所对的弧都是相等的。

所以这 $n-2$ 个角相等，都为 $\dfrac{180^\circ}{n}$。

因此就要求 $\dfrac{\alpha}{\dfrac{180^\circ}{n}}=\dfrac{\alpha n}{180^\circ}$ 为整数。

设 $(\alpha,180)=d$，$\alpha=\alpha'd$，$180=\beta'd$，则 $(\alpha',\beta')=1$ 且 $\dfrac{\alpha'n}{\beta'}$ 为整数。

所以 $\beta'\mid \alpha'n$，又 $(\alpha',\beta')=1$，所以 $\beta'\mid n$。

然而还有一个条件，就是 $\alpha\le \dfrac{(n-2)\times180^{\circ}}{n}$，解一下不等式即可得到 $n\ge \dfrac{360^\circ}{180^\circ-\alpha}$，即 $n\ge \left\lceil\dfrac{360^\circ}{180^\circ-\alpha}\right\rceil$。

因此最终结果为 $n_{\min}=\left\lceil\dfrac{\left\lceil\dfrac{360^\circ}{180^\circ-\alpha}\right\rceil}{\dfrac{180^\circ}{(\alpha,180)}}\right\rceil\cdot\dfrac{180^\circ}{(\alpha,180)}$。

可以使用 $\left\lceil\dfrac{p}{q}\right\rceil=\left\lfloor\dfrac{p+q-1}{q}\right\rfloor$ 来省略向上取整的函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,alpha,tmp1,tmp2,ans;
int gcd(int a,int b) {
    if(b==0) return a;
    return gcd(b,a%b);
}
int main() {
	cin>>T;
	while(T--) {
		cin>>alpha;
		tmp1=180/gcd(alpha,180);
		tmp2=(360+180-alpha-1)/(180-alpha);
		ans=(tmp2+tmp1-1)/tmp1*tmp1;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Heartlessly (赞：5)

## Description

$T$ 组数据。给定一个角度 $\theta$，请你寻找一个正 $n$ 边形，满足这个正 $n$ 边形上存在三个顶点 $A,B,C$（可以不相邻），使得 $\angle ABC=\theta$ 。请输出最小的 $n$ 。保证 $n$ 不超过 $998244353$ 。

$(1 \leq T \leq 180,1 \leq \theta < 180)$

## Solution

正 $n$ 边形是存在外接圆的，且 $n$ 个顶点把圆分成 $n$ 段等长的弧（下文中均称作基本弧），每段基本弧对应的圆心角是 $\left( \frac{360}{n} \right)^\circ$，圆周角是 $\left( \frac{180}{n} \right)^\circ$（圆心角的一半）。

![VO5d9P.png](https://s2.ax1x.com/2019/06/19/VO5d9P.png)

从这个正 $n$ 边形上选 $3$ 个点 $A,B,C$，我们可以看做选择顶点 $B$ 和弧 $\widehat{AC}$ 。弧 $\widehat{AC}$ 对应的圆周角就是 $\angle ABC$（与顶点 $B$ 无关，因为同弧所对的圆周角相等）。弧 $\widehat{AC}$ 的长度一定是基本弧的 $x$ 倍，其中 $x$ 是一个正整数，且不超过 $n - 2$（否则顶点 $B$ 没有位置），所以弧 $\widehat{AC}$ 所对的圆周角就是 $\left( \frac{180x}{n} \right)^\circ$ 。显然我们可以枚举 $n$ 和 $x$，求出正 $n$ 边形可以得到的所有角度。

$n$ 的下界显然是 $3$，$n$ 的上界是什么呢？

很容易发现当 $n = 360$ 时，$\theta$ 可以等于 $1^\circ \sim 179^\circ$ 中的任意一个角度。所以只要枚举到 $360$ 就好了。注意所给的 $\theta$ 是正整数，所以枚举时要满足 $180x$ 能被 $n$ 整除。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 180;
int t, n, theta[MAXN + 5];

int main() {
    for (int i = 3; i <= 360; ++i)//枚举正 n 边形 
        for (int j = 1; j <= i - 2; ++j)//枚举 x 
            if (180 * j % i == 0 && !theta[180 * j / i])//不能有小数 
                theta[180 * j / i] = i;//i 就是 θ=(180 * j / i)°时最小的 n 
    for (read(t); t; --t) {
        read(n);
        write(theta[n]);
        putchar('\n');
    }
    return 0;
}
```



---

## 作者：一扶苏一 (赞：3)

## Description

给定一个角度 $\theta$，请你寻找一个正 $n$ 边型，满足在这个正 $n$ 边型上找三个顶点 $A,B,C$ （可以不相邻），使得 $\angle ABC~=~\theta$ 。请输出最小的 $n$。保证 $n$ 不超过 $998244353$。多组数据。

注意给出的 $\theta$ 是使用角度制表示的。

## Input

第一行是数据组数 $T$

下面 $T$ 行，每行一个整数 $\theta$，代表给出的角度

## Output

对于每组数据输出一行代表答案

## Hint

$1~\leq~T~\leq~180~,~1~\leq~\theta~<~180$。

## Solution

#### 多边形内角和定理：

对于一个有 $n$ 个顶点的凸多边形 $n~\geq~3$，其内角和为 $(n~-~2)~\times~180^\circ$。

证明略。这大概是初中定理吧……大概方法是显然一个 $n$ 边型可以分成 $(n~-~2)$ 个三角形，每个三角形的内角和是 $180^\circ$。至于证明可以分成 $(n~-~2)$ 个三角形，对 $n$ 做数学归纳即可。

由于这是一个正 $n$ 边型，所以一个角的度数为 $\frac{n-2}{n}~\times~180^\circ$

同时它连向其他每个顶点的线段平分这个角，所以它连向相邻两个顶点的线段组成的角的度数为 $\frac{n-2}{(n-2)n}~\times~180^\circ~=~\frac{1}{n}~\times~180^\circ$

我们设选择的点 $A$ 和点 $C$ 中间相隔了 $(k-1)$ 个顶点 $(k~\leq~n~-~2)$，于是这些一共组成了 $k$ 个角度如上的角。列得方程如下（角度略去）：

$$\frac{k}{n}~\times~180~=~\theta$$

移项得

$$k~\times~180~=~\theta~\times~n$$

我们设 $s~=~\gcd(\theta~,~180)$，然后等式两侧同除 $s$，得

$\frac{180}{s}~\times~k~=~\frac{\theta}{s}~\times~n$

由于$\frac{180}{s}~\perp~\frac{\theta}{s}$，所以 $k~=~\frac{\theta}{s}~,~n~=~\frac{180}{s}$

考虑这种情况下我们要求 $k~\leq~n~-~2$，但是如果算出来不是这样怎么办：如果答案为 $n$ 时满足上式，则答案为 $xn(x~\in~Z^+)$ 时一定也满足上式。于是我们不断加 $n$ 直到合法即可。

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 200010;
const int MOD = 998244353;

int n;
ll ans;
char MU[maxn];

int main() {
	freopen("1.in", "r", stdin);
	qr(n);
	for (rg int i = 1; i <= n; ++i) do {MU[i] = IPT::GetChar();} while ((MU[i] > 'z') || (MU[i] < 'a'));
	MU[0] = MU[1]; MU[n + 1] = MU[n];;
	int pos = n; while (MU[pos] == MU[0]) --pos;
	int k = n - pos;
	for (rg int i = 1; i <= n; ++i) if (MU[i] == MU[i - 1]) {
		++ans;
	} else break;
	ans = (ans * k) % MOD;
	++ans;
	for (rg int i = 1; i <= n; ++i) if (MU[i] == MU[i - 1]) ++ans; else break;
	for (rg int i = n; i; --i) if (MU[i] == MU[i + 1]) ++ans; else break;
	qw(ans % MOD, '\n', true);
	return 0;
}
```



---

## 作者：zhangzirui66 (赞：2)

## 闲话
本文同步发布在 [cnblogs](https://www.cnblogs.com/zhangzirui66)。

---

观察到角度最多只有 $360$ 度，可以预处理。

外层循环 $3 \sim 360$，计算答案。

正多边形可以构造外接圆，圆心角即为 $\frac{360}{i}$，根据圆周角定理，圆周角是圆心角的一半，即 $\frac{180}{i}$。

内层循环 $A$ 与 $C$ 距离点数即可，注意只能枚举到 $n - 2$，距离为 $j$，角度显然为 $j \times \frac{180}{i}$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, ans[185];
//ans[i] 代表正 i 边形的答案
int main(){
    cin >> t;
    for(int i = 3; i <= 360; i ++){
        for(int j = 1; j <= i - 2; j ++){
            if(180 * j % i == 0 && !ans[180 * j / i]) ans[180 * j / i] = i;
//          须整除                 没有计算过         首次答案显然最优
        }
    }
    while(t --){
        cin >> n;
        if(ans[n]) cout << ans[n] << "\n";
        else cout << "-1\n";//无解
    }
    return 0;
}
```

---

## 作者：LJC00118 (赞：1)

答案本质上是把一个圆切成答案份

那么圆心角确定了，就可以算出一个圆周角的大小，如果切成 360 份可以拼出任意角度，所以枚举这个角度即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie();
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

int T;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	read(T); while(T--) {
		int d; read(d); int ans = -1;
		for(register int i = 3; i <= 23333; i++) {
			if(d * i % 180 == 0 && d <= 180 - 360 / (double)i) {
				ans = i; break;
			}
		}
		print(ans, '\n');
	}
	return 0;
}
```

---

## 作者：porse114514 (赞：1)

# [CF1096C Polygon for the Angle](https://www.luogu.com.cn/problem/CF1096C) 题解
## 题目大意
给定一个角度 $ang$，求一个 $n$，使正 $n$ 边形的一个点连接对角线后能组成这个角。
## 题目分析
首先，题目输入的是角，但要求的是边数，所以我们需要找到边于角的关系：

1. 因为正多边形外角和为 $360^{\circ}$，所以正 $n$ 边形的一个外角等于 $360^{\circ} \div n$，所以**正 $n$ 边形的一个内角为** $\large180^{\circ}-360^{\circ} \div n$。
2. 当正 $n$ 边形两个点的距离为 $x$ 时，两点间连线与两点间边组成了 $x+1$ 边形，内角和为 $180^{\circ}\times (x-1)$，内角中包含两个连线与边的相等的夹角与 $x-1$ 个正 $n$ 边形内角，所以连线与边的夹角为$\large\frac{180^{\circ}\times (x-1)-(x-1)(180^{\circ}-360^{\circ} \div n)}{2}$，化简得**连线与边的夹角为**$\large\frac{\large180^{\circ}\times (x-1)}{\large n}$。
3. 由第二点我们发可得，设 $x$ 与同侧两点 $y,z$ 的距离分别为 $p,q\,(p>q)$，所以 $∠yxz=\large\frac{180^{\circ}\times (p-1)}{n}-\large\frac{180^{\circ}\times (q-1)}{n}=\large\frac{180^{\circ}\times (p-q)}{n}$，也就是 $\large∠yxz$ **等于 $x$ 与与 $x$ 距离 $p-q+1$ 的点的连线与 $x$ 的夹角**。换句话说，**任何中间两个连线的角都可以被转化为边与连线的角**。

有了这些，我们就可以设未知数并列方程：

设 $n$ 边形中两个距离为 $x$ 的点的连线与边的夹角为 $ang$，则：
$$ang=\frac{180^{\circ}\times (x-1)}{n}$$
移项得：
$$n=\frac{180^{\circ}\times (x-1)}{ang}$$
所以当 $180^{\circ}\times (x-1)$ 整除 $ang$ 时，$n$（答案）为整数，此时就找到了答案。

所以我们只需要从 $2$ 开始枚举 $x$（因为如果 $x=1$，那就不是对角线），当 $180^{\circ}\times (x-1)$ 整除 $ang$ 时输出就行了。

因为 $(x-1)\times ang$ 一定整除 $ang$，所以一次询问的时间复杂度为 $O(ang)$，总复杂度为 $O(ang\times t)$，完全能跑过去。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,ang,x,n;
signed main()
{
	cin >> t;
	while(t--)
	{
		//n = (180x - 180) / ang
		cin >> ang;
		x = 2;//注意，这里初始化为2，原因见前文题目分析 
		while(1)
		{
			if((x * 180 - 180) % ang == 0)//如果答案为整数 
			{
				n = (x * 180 - 180) / ang;
				if(n > x)//这里一定要特判，因为如果x>=n,那么就不是对角线了 
				{
					cout << (x * 180 - 180) / ang << '\n';
					break;
				}
			}
			x++;
		}
	}
	return 0;
}
```
## 都看到这里了，点一个小小的赞呗

---

## 作者：npqenqpve (赞：1)

### 题意：

给定一个角度值，问最少在正几边形中可以找到三个点 $A$ ，$B$ ，$C$ ，使 $∠ABC$ 为这个角度值，如果不存在这个正 $n$ 边形，则输出 $-1$ ，有多组数据。

### 思路：

- 首先可以发现不可能数据使得程序输出 $-1$ ，因为任意 $1^{\circ}\leq\theta<180^{\circ}$ 都可以由一个正 $360$ 边形得出。
- 然后可以发现对于任意正 $n$ 边形 $(n>2)$ 所能凑出的最小角度一定是![](https://cdn.luogu.com.cn/upload/image_hosting/282z7og3.png?x-oss-process=image/resize,m_lfit,h_1000,w_1250)

像 $∠EDA$ 这样的，（有点难以描述这个最小角）
$$
\theta=\frac{180^{\circ}}{n}
$$
最大角比较显然，就是这个正多边形的内角，可以发现能组成的所有角一定能被最小角整除，这个角必然是 $k$ $(k>0)$ 个最小的角组成的
$$
\theta=\frac{k}{n}\times180^{\circ}
$$
整理可得 $n\times\theta=k\times180^{\circ}$ ，那么可以考虑枚举 $n$ ，如果出现 $n\times\theta$ 可以被 $180^{\circ}$ 整除，且 $\theta$ 小于正 $n$ 边形能凑出的最大角，即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int min,max;
}a[365];
int main()
{
	for(int i=3;i<=360;i++)
	{
		a[i].min=180/i;
		a[i].max=(i-2)*180/i;
	}
	int t;cin>>t;
	while(t--)
	{
		int n;cin>>n;
		int ans=360;
		for(int i=3;i<360;i++)
		{
			if(n*i%180==0&&n<=a[i].max)
			{
				ans=i;break;
			}
		}
		cout<<ans<<"\n";
	}
}
```

---

