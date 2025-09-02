# Neko does Maths

## 题目描述

Neko 喜欢因子。在最近的一节数论课上，他从数学老师那里得到了一个有趣的练习题。

Neko 有两个整数 $a$ 和 $b$。他的目标是找到一个非负整数 $k$，使得 $a+k$ 和 $b+k$ 的最小公倍数尽可能小。如果有多个最优的 $k$，他需要选择最小的那个。

鉴于他的数学天赋，Neko 在这个问题上毫无压力地得到了 Wrong Answer。你能帮他解决这个问题吗？

## 说明/提示

在第一个测试样例中，应选择 $k=2$，因为 $6+2$ 和 $10+2$ 的最小公倍数是 $24$，这是可能的最小最小公倍数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 10
```

### 输出

```
2```

## 样例 #2

### 输入

```
21 31
```

### 输出

```
9```

## 样例 #3

### 输入

```
5 10
```

### 输出

```
0```

# 题解

## 作者：ljc20020730 (赞：13)

不妨设$a>b$ 

显然$lcm(a+k,b+k)=\frac{(a+k)(b+k)}{gcd(a+k,b+k)}$

由辗转相减法可知$gcd(a,b)=gcd(b,a-b)$，

所以原式可化为$lcm(a+k,b+k)=\frac{(a+k)(b+k)}{gcd(b+k,a-b)}$

对于$a-b$的值是定值，那么我们就可以枚举$a-b$的因子$w$然后反过来O(1)求出最小的$k$就行了。

若$b \%  w = 0$ 那么 $k = 0$ 否则 $k = (\left \lfloor \frac{b}{w} \right \rfloor + 1)w-b$

复杂度$ O(\sqrt{a-b}) $

---

## 作者：Sincerin (赞：6)

[题目传送门！](https://www.luogu.com.cn/problem/CF1152C)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-cf1152c)

## 题意

给定两个正整数 $a$ 和 $b$，试求出最小的非负整数 $k$ 使得 $\operatorname{lcm}(a+k,b+k)$ 最小。
- 注：其中 $\operatorname{lcm}(a+k,b+k)$ 表示  $a+k$ 和 $b+k$ 的最小公倍数。

- $1 \leq a,b  \leq 10^9$。

## 解析


首先我们要了解关于最小公倍数的几个知识点。

- 给定非负整数 $a$ 和 $b$，若正整数 $d \mid a$ 且 $d \mid b$ ，则称 $d$ 为 $a$ 和 $b$ 的公约数。$a$ 和 $b$ 的公约数中最大的一个叫做 $a$ 和 $b$ 的最大公约数，记作 $\operatorname{gcd}(a,b)$。

- 给定正整数 $a$ 和 $b$，若非负整数 $n$ 满足 $a \mid n$ 且 $b \mid n$，则称 $n$ 为 $a$ 和 $b$ 的公倍数。$a$ 和 $b$ 的公倍数中最小的一个正整数叫做 $a$ 和 $b$ 的最小公倍数，记作 $\operatorname{lcm}(a,b)$。

知道了最小公倍数的定义，我们还要想办法去计算它。首先由最大公约数和最小公倍数的定义可知， $\operatorname{lcm}(a,b)=\large \frac{a \times b}{\operatorname{gcd}(a,b)}$。（想看详细证明过程的同学可以戳[这里](https://www.cnblogs.com/dtyblog/p/12773826.html)）所以我们可以先求出 $\operatorname{gcd}(a,b)$。


#### 1.更相减损术

这个算法出自《九章算术》，当 $a \geq b$ 且 $a,b \in \mathbb{N^+}$ 时，$\operatorname{gcd}(a,b)=\operatorname{gcd}(a,a-b)=\operatorname{gcd}(b,a-b)$，现在我们来证明一下。

记 $\operatorname{gcd}(a,b)=d$，则 $a$ 和 $b$ 可以表示为 $x_1\times d$ 和 $x_2\times d$。因为 $a \geq b$，所以 $x_1 \geq x_2$，所以 $a-b=(x_1-x_2)\times d \geq 0$，所以$\operatorname{gcd}(a,b)=\operatorname{gcd}(a,a-b)=\operatorname{gcd}(b,a-b)=d$。

#### 2.欧几里得算法

也就是大家耳熟能详的辗转相除法啦！当 $a,b \in \mathbb{N^+}$ 时，$\operatorname{gcd}(a,b)=\operatorname{gcd}(b,a \bmod b)$。

这个没有什么好证明的，因为这里的取余运算仅仅是相当于多做了几次减法而已。值得注意的是欧几里得算法的时间复杂度为 $\Theta( \log (a+b))$。

在这里提供我最喜欢的递归式写法。

```cpp
inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
inline int lcm(int a,int b){
	return a/gcd(a,b)*b;//先算a/gcd(a,b)再乘上b可以有效防止溢出。
}
```

回到题目。根据更相减损术，可知 $\operatorname{lcm}(a+k,b+k)\large= \frac{(a+k) \times (b+k)}{\operatorname{gcd}(a+k,b+k)}=\frac{(a+k) \times (b+k)}{\operatorname{gcd}(a+k,(a+k)-(b+k))}=\frac{(a+k) \times (b+k)}{\operatorname{gcd}(a+k,a-b)}$。

由于 $b \geq 1$ 且 $k \geq 0$，所以 $a+k \gt a-b$。也就是说 $\operatorname{gcd}(a+k,a-b) \in [1,a-b]$。我们只需要在这个区间枚举每一个 $d \mid (a-b)$，求出其对应的 $k$ 即可。

因为 $\operatorname{gcd}(a+k,b+k)=d$，所以 $(a+k) \bmod d=0$。也就是说 $k=d-(a \bmod d)$。暴力计算此时的 $\operatorname{lcm}(a+k,b+k)$ 并更新答案即可。该算法时间复杂度为 $\Theta(\operatorname{d}(\sqrt{a-b}) \times \log(a+b))$。

- 注：其中 $\operatorname{d}(x)$ 表示 $x$ 的因子个数。
 
## AC Code

```cpp
//C++14 (GCC 9) 851B 15ms 8.00KB
#include<iostream>
#include<cstdio>
#include<algorithm> 
#define _ 1
using namespace std; 
#define int long long//防止见祖宗
int n,m,a,b,k,w1,w2,ans,lcm1; 
inline int gcd(int a,int b)//greatest common divisor 
{
	return b?gcd(b,a%b):a;
}
inline int lcm(int a,int b)//least common multiple 
{
	return a/gcd(a,b)*b;
}
inline void check(int k)//检验k 
{
	if(lcm(a+k,b+k)<lcm1)//如果lcm(a+k,b+k)更小，就更新k 
	{
		lcm1=lcm(a+k,b+k);//update
		ans=k;
	}
}
signed main(void)
{
	scanf("%lld%lld",&a,&b);
	if(a<b) swap(a,b);//保证a>=b 
	n=a-b; 
	lcm1=lcm(a,b);//当k=0时的值 
	for(register int i=1;i*i<=n;++i)//试除求因子 
	{
		if(n%i==0)
		{
			w1=i; w2=(n/i);//两个因子成对出现 
			k=w1-(a%w1);//求出k 
			check(k); 
			if(w1!=w2)//特判完全平方数 
			{
				k=w2-(a%w2);//求出k 
				check(k);
			}
		}
	}
	printf("%lld\n",ans); 
	return !(0^_^0);//完结撒花！ 
}

```

[AC Record](https://www.luogu.com.cn/record/119646617)




---

## 作者：学委 (赞：5)

注意到：

- 最小公倍数是积除以最大公约数。

- 不管增加多少，两者之差始终为 b - a。

  两者的最大公约数必然是 b - a 的因数之一。辗转相除法就是这么用的。
  
- 枚举 b - a 的因数，指定其为目标最大公约数，于是容易求出最小增量。枚举时更新答案。

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using std::swap;
 
typedef long long LL;
 
LL a, b, ans = 2e18, k = 0;
 
void gate(LL gcd) {
  int t =  b / gcd + (b % gcd != 0);
  int add = gcd * t - b;
  if ((b + add) / gcd * (a + add) < ans)
    ans = (b + add) / gcd * (a + add), k = add;
}
 
int main() {
  scanf("%I64d %I64d", &a, &b);
  if (a > b)
    swap(a, b);
  if (a == b) {
    puts("0");
    return 0;
  }
  LL d = b - a;
  if (b % d == 0) {
    puts("0");
    return 0;
  }
  int s = sqrt(d);
  for (int i = 1; i <= s; ++i)
    if (d % i == 0) {
      gate(i);
      gate(d / i); 
    }
  printf("%I64d\n", k);
  return 0;
}
```

---

## 作者：lgx57 (赞：4)

熟知一个结论：

$$\operatorname{lcm}(a,b)=\frac{ab}{\gcd(a,b)}$$

那么题目中的式子便可以化为：

$$\operatorname{lcm}(a+k,b+k)=\frac{(a+k)(b+k)}{\gcd(a+k,b+k)}$$


不妨设 $a>b$。

注意到 $\gcd(a+k,b+k)=\gcd(a+k,a-b)$。[不懂的看这里](https://baike.baidu.com/item/%E8%BE%97%E8%BD%AC%E7%9B%B8%E5%87%8F/7529647?fr=ge_ala)

由于 $a-b$ 的值是固定的，我们只需要枚举 $\gcd(a+k,a-b)$ 的值，找出最小的 $k$ 再计算 $\operatorname{lcm}$ 即可。

时间复杂度：$O(\sqrt{\max(a,b)})$

[code](https://www.luogu.com.cn/paste/7amwotkl)

---

## 作者：mulberror (赞：3)

# 自己写的所有题解
[【传送门】](https://www.cnblogs.com/chhokmah/p/10768012.html)  
# 题目大意
给你$a$和$b$，求最小的$k$使$a+k$和$b+k$的最小公倍数最小。

# 题解
数论水题一道。  
$lcm(a+k,b+k)=\frac{(a+k)\times (b+k)}{gcd(a+k,b+k)}$  
辗转相减法可得：$gcd(a+k,b+k)=gcd(a+k,b-a)$。  
那么很明显的是$b-a$是一个定值，而且答案和$b-a$的约数有关，那么我们就枚举$b-a$的约数，然后暴力判断是否满足答案就可以了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll linf = 1ll << 62; 
ll a, b, c, ans = linf, ret = linf;
void check(ll x) {
	ll ta = ceil((db)a/x)*x;;
	ll tb = ta + c;
	ll tmp = ta * tb / x;
	if (tmp == ret) {
		if (ta - a < ans) ans = tmp;
	} 
	else if (tmp < ret) ans = ta - a, ret = tmp;
}
int main() {
	cin >> a >> b; 
	if (a == b) { cout << 0 << endl; return 0; }
	if (a > b) swap(a, b);
	c = b - a; ll sq = sqrt(c);
	for (int i = 1; i <= sq; i ++) {
		if (c % i == 0) { check(i); check(c / i); }
	}
	cout << ans << endl; 
	return 0;
}
```

---

## 作者：Bai_Kking (赞：1)

# 题解 CF1152C Neko does Maths

## 思路

### 前置知识点：

$$
\operatorname{lcm}(a+k,b+k)={{(a+k)(b+k)}\over \gcd(a+k,b+k)}
$$



我们就可以将问题转换为求 $\gcd(a+k,b+k)$。

但是如果考虑这样的形式就要同时注意两个变量：$a+k$ 和 $b+k$，这是非常困难的。

根据**扩展欧几里得算法**易知：
$$
\gcd(a+b,a)=\gcd((a+b)-a,a)=\gcd(a,b)
$$
不妨设 $a>b$，则有：
$$
\gcd(a+k,b+k)=\gcd(a-b,a+k)
$$
这样我们只需要考虑 $b+k$ 的取值就可以了。

这样，我们的思路就很清晰了：只需要找到一个 $k$，使得上式最大即可。

又考虑到 $a-b$ 是定值，我们可以枚举 $a-b$ 的每个因数 $p$，则一定有 $p \mid \gcd(a-b,a+k)$，那么一定有：
$$
a+k\equiv0\pmod{p}
$$
变形得到：
$$
k\equiv-a\pmod{p}
$$
注：代码实现`k=(p-a%p)%p;`

由此，对于每个 $p$ 都可以找到一个最小的 $k$，将 $k$ 代回原式，就可以算出每一个解，比较最小值即可。

因为遍历 $p$ 只需要找到 $\sqrt{a-b}$，所以时间复杂度为 $O(\sqrt{a-b})$。

## Code:

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
//	freopen("lcm.in","r",stdin);
//	freopen("lcm.out","w",stdout);
	ll a,b;
	scanf("%lld%lld",&a,&b);
	ll tt=abs(a-b);
	ll minn=(1LL<<62);
	ll pos;
	for(int i=1;i*i<=tt;i++){//只需枚举到根号
		if(tt%i==0){
			ll k1=(i-a%i)%i;
			ll k2=((tt/i)-a%(tt/i))%(tt/i);//k1,k2枚举
			ll ans1=(a+k1)/__gcd(a+k1,b+k1)*(b+k1);
			ll ans2=(a+k2)/__gcd(a+k2,b+k2)*(b+k2);//算出两者原式的值
			if(minn>ans1){
				minn=ans1;
				pos=k1;
			}
			if(minn>ans2){
				minn=ans2;
				pos=k2;
			}//比较
		}
	}
	printf("%lld",pos);
	return 0;
}
```

提示：目前版本代码只能在 `C++20` 通过，如果有知道原因的大佬可以在评论区留言，谢谢！

完结撒花！

---

## 作者：loser_seele (赞：1)

首先设 $ a \leq b $。

然后辗转相除得到 $ \gcd(a+k,b+k)=\gcd(b-a,a+k) $，又因为有 $ res=\operatorname{lcm}(a,b)=\frac{a \times b}{\gcd(a,b)} $，所以只需要枚举 $ \gcd $ 可能的值，而这个值显然只能是 $ res $ 的约数，否则结果不符不整除其中一个数。然后取符合条件的最小的 $ a,b $，算出所有 $ \operatorname{lcm} $ 之后取最小值即可。注意特判边界情况。

实现上，有比暴力更优秀的做法。先跑 Pollard-rho 分解质因数，然后 dfs 枚举每个质因子对应的指数算出所有约数，由唯一分解定理不难得知这样枚举一定不重不漏。然后对每个约数按上述过程计算取最小值即可。

时间复杂度 $ \mathcal{O}(d(b-a)) $，可以通过。其中 $ d(x) $ 表示 $ x $ 的约数个数。

[提交记录](https://codeforces.com/contest/1152/submission/194292210)

---

## 作者：james1BadCreeper (赞：1)

要求的是 $\text{lcm}(a+k,b+k)=\dfrac{(a+k)(b+k)}{\gcd(a+k,b+k)}=\dfrac{(a+k)(b+k)}{\gcd(b+k,a-b)}$，那么假设 $a>b$，$\gcd(b+k,a-b)$ 的值一定是 $a-b$ 的约数。那么我们枚举 $a-b$ 的约数 $i$ 并计算出让 $i$ 是 $b+k$ 的约数的最小 $k$ 即可，时间复杂度为 $O(\sqrt{a-b})$。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int gcd(int x, int y) { if (y == 0) return x; return gcd(y, x % y); }
long long lcm(int x, int y) { return 1ll * x / gcd(x, y) * y; }

int a, b, k;
long long ans;

int calc(int x) {
    if (b % x == 0) return 0;
    return x - b % x;
}
void upd(int t) {
    long long tmp = 1ll * (a + t) / gcd(b + t, a - b) * (b + t);
    if (tmp < ans) ans = tmp, k = t;
    else if (tmp == ans) k = min(k, t);
}

int main(void) {
    scanf("%d%d", &a, &b); if (a < b) swap(a, b);
    ans = lcm(a, b), k = 0;
    for (int i = 1; i * i <= a - b; ++i)
        if ((a - b) % i == 0) {
            int t = calc(i); upd(t);
            t = calc((a - b) / i); upd(t);
        }
    printf("%d\n", k);
    return 0;
}
```

---

## 作者：linjinkun (赞：0)

我的代码似乎有点长……

设 $a>b$，那么 $\operatorname{lcm}(a+k,b+k) = \frac{(a+k)(b+k)}{\gcd(a+k,b+k)}$。运用[更相减损术](https://www.cnblogs.com/aininot260/p/9479732.html)化简：

$$\operatorname{lcm}(a+k,b+k) = \frac{(a+k)(b+k)}{\gcd(b+k,a-b)}$$

于是我们可以求 $a-b$ 的因数或 $b+k$ 的因数，但 $k$ 还未确定，所以只能求 $a-b$ 的因数，比如我们已经找到了一个 $a-b$ 的因数 $s$，那么必须要使 $(b+k) \bmod s = 0$，由于 $b$ 和 $s$ 已经确定了，那么只需要求 $k$，如果 $b$ 是 $s$ 的倍数，那么 $k = 0$，否则，$k = (\lfloor\frac{b}{s} \rfloor+1) \times s-b$，应该很好理解吧。所以我们只需要找到一个 $s$，使得 $\operatorname{lcm}(a+k,b+k)$ 最小。

代码（一定要看，有详细注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//要开long long 
int minn = 1e18,minnn;
signed main()
{
	int a,b;
	scanf("%lld %lld",&a,&b);
	if(a<b)//必须满足a>b
	{
		swap(a,b);
	}
	int t = a-b;
	for(int i = 1;i*i<=t;i++)//找a-b的因子
	{
		if(t%i == 0)
		{
			int k;
			if(b%i == 0)
			{
				k = 0;
			}
			else
			{
				k = ((b/i)+1)*i-b;//计算
			}
			int s = (a+k)/__gcd(a+k,b+k)*(b+k);//求lcm(a+k,b+k)
			if(minn>s)//如果最小公倍数比答案小
			{
				minn = s;
				minnn = k;//记录下k
			}
			if(minn == s)//如果和答案一样
			{
				if(minnn>k)//并且k比之前的小
				{
					minnn = k;
				}
			}
			if(b%(t/i) == 0)//因数是成对出现的，下面的跟之前没有任何区别
			{
				k = 0;
			}
			else
			{
				k = (b/(t/i)+1)*(t/i)-b;
			}
			s = (a+k)/__gcd(a+k,b+k)*(b+k);
			if(minn>s)
			{
				minn = s;
				minnn = k;
			}
			if(minn == s)
			{
				if(minnn>k)
				{
					minnn = k;
				}
			}
		}
	}
	printf("%lld",minnn);
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 前置知识

1. $\operatorname{lcm}(x,y)=\frac{xy}{\gcd(x,y)}$；
2. 当 $x>y$ 时，$\gcd(x,y)=\gcd(x,x-y)$。 

## 思路

不妨设 $\gcd(x,0)=x$，且 $a\ge b$。转换题意：

$$
\begin{aligned}
\operatorname{lcm}(a+k,b+k)
&=\frac{(a+k)(b+k)}{\gcd(a+k,b+k)}\\
&= \frac{(a+k)(b+k)}{\gcd(a+k,a-b)}
\end{aligned}
$$

考虑枚举 $a-b$ 的因数 $x$，钦定其为 $\gcd(a+k,a-b)$，则 $a+k\equiv 0\pmod x$。由于要让最终结果最小，那么我们需要让 $k$ 最小，则 $k=(x-a\bmod x)\bmod x$。直接暴力更新答案即可。

时间复杂度 $\sqrt V$，其中 $V$ 表示值域，足以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
int a,b,ans = 2e18,ansk;
inline void work(int x)
{
	int k = (x-a%x)%x,w = (a+k)*(b+k)/x;
	if(w<ans) ans = w,ansk = k;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(a),read(b);
	if(a<b) swap(a,b);
	int x = a-b;
	for(int i = 1;i*i<=x;i++)
		if(x%i==0) work(i),work(x/i);
	write(ansk);
	return 0;
}
```

---

