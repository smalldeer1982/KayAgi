# [ARC111A] Simple Math 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_a

正整数 $ N,\ M $ が与えられます。$ \lfloor\ \frac{10^N}{M}\ \rfloor $ を $ M $ で割った余りを求めてください。

  $ \lfloor\ x\ \rfloor $ について $ \lfloor\ x\ \rfloor $ は、 $ x $ を超えない最大の整数を表します。例としては次のようになります。 - $ \lfloor\ 2.5\ \rfloor\ =\ 2 $
- $ \lfloor\ 3\ \rfloor\ =\ 3 $
- $ \lfloor\ 9.9999999\ \rfloor\ =\ 9 $
- $ \lfloor\ \frac{100}{3}\ \rfloor\ =\ \lfloor\ 33.33...\ \rfloor\ =\ 33 $

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ M\ \leq\ 10000 $

### Sample Explanation 1

$ \lfloor\ \frac{10^1}{2}\ \rfloor\ =\ 5 $ なので、$ 5 $ を $ 2 $ で割った余りの $ 1 $ を出力します。

## 样例 #1

### 输入

```
1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
2 7```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000000000000 9997```

### 输出

```
9015```

# 题解

## 作者：PineappleSummer (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc111_a)

如题，这是一道简单数学题。

首先推式子：

$$\begin{aligned}

&\left\lfloor\frac{10^n}{m}\right\rfloor\pmod m 

\\&\equiv \left\lfloor\frac{10^n}{m}\right\rfloor-km 

\\&\equiv \left\lfloor\frac{10^n}{m}-km\right\rfloor
\\&\equiv \left\lfloor\frac{10^n-km^2}{m}\right\rfloor \\&\equiv\left \lfloor \frac{10^n \bmod m^2}{m}\right\rfloor(k \in \mathbb{Z})\end{aligned}$$

所以需要算出来 $10^n \bmod m^2$，快速幂即可。

c++ 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
long long quick_pow(ll x,ll y,ll p)//快速幂
{
    if(y==0) return 1;
    ll res=quick_pow(x,y>>1,p)%p;
    if(y&1) return res*res%p*x%p;
    else return res*res%p;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	cout<<quick_pow(10,n,m*m)/m;
	return 0;
}
```
Python 代码，自带 `pow` 函数，可实现取余：
```python
n, m = map(int, input().split())
print(pow(10, n, m * m) // m)
```

---

## 作者：Pink_Cut_Tree (赞：3)

# AT_arc111_a [ARC111A] Simple Math 2 题解

### 前情提要

由于你谷的 RMJ 效果很炸裂，在洛谷上似乎交了就是 UKE。

[AC in AtCoder](https://atcoder.jp/contests/arc111/submissions/45965298)。

Upd on $2023.09.26$：标题写错，谢罪。

### 注意

首先我们要明确一个事实，就是数据范围超级大，无法把答案算出来。

大佬们可以想到快速幂，但是~~快速幂似乎没法解决这类问题~~。

但真的是这样吗？

### 正解

给出一个猜想：

$\left  \lfloor \frac{10^n}{m} \right \rfloor =\left  \lfloor \frac{10^n \bmod m^2}{m} \right \rfloor$

下面我们证明它，从右边的式子推出左边的式子：

$\left  \lfloor \frac{10^n \bmod m^2}{m} \right \rfloor \equiv \left  \lfloor \frac{10^n -km^2}{m} \right \rfloor \equiv \left  \lfloor \frac{10^n}{m} \right \rfloor-km \equiv \left  \lfloor \frac{10^n}{m} \right \rfloor (\pmod m)$

$(k\in \mathbb{Z})$

（数学公式，不带句号，请见谅）

所以我们可以直接计算 $\left  \lfloor \frac{10^n \bmod m^2}{m} \right \rfloor$ 的值。

### 快速幂~~科普~~

快速幂是一种时间复杂度为 $\text{O}(\text{ log }n)  $，计算 $x^y \text{ mod }p$ 的算法。

推荐：[P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)。

快速幂的思路就是对于一个 $a^k$，有 $\left\{\begin{matrix}
a^{k}=\displaystyle a^{\frac{k}{2} }\times a^{\frac{k}{2} } & (k\equiv 0 \pmod{2} ) 
\\a^{k}=\displaystyle a^{\left \lfloor \frac{k}{2}  \right \rfloor  }\times a^{\left \lfloor \frac{k}{2}  \right \rfloor  }\times a & \text{ otherwise }
\end{matrix}\right.$

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define ll long long
ll n,m;
ll ksm(ll x,ll y,ll p){
	ll ans=1;
	while(y){
	    if(y&1){
	    	ans=ans*x%p;
		}
	    x=x*x%p;
	    y>>=1;
	}
return ans;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	cout<<ksm(10,n,m*m)/m;
return 0;
} 
```


---

## 作者：Red_river (赞：2)

### 题目大意

这道题呢就是给你两个数，就是 $n$ 和 $m$ 然后让你求：
 $\left \lfloor \frac{10^n}{m} \right \rfloor \equiv \left \lfloor \frac{10^n \bmod m^2}{m} \right \rfloor \pmod m$。

证明：分子减一个 $m^2$ 的倍数，使它变成一个 $10^n$，就可以将分子上的 $\bmod$ $m$ 消去。

所以我们可以很容易的想到这道题其实就是一道快速幂，但只不过是需要边算边模的快速幂罢了，所以这道题考察的就是数论和快速幂，但同时也要注意要边算边模，否则就会超出数据范围，自然而然答案也就错了。

### CODE
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
#define N 50005
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
ll n,m,k,jk,ans,sum,num;
ll dis[N],vis[N],wis[N],f[N];
void read(ll &x)
{
	x=0;int ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=ff;return;
}

void write(ll x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}

int main()
{
	read(n),read(m);
	ll result=1;
 	int base=10,power=n,p=m*m;
	while(power>0)
	{
		if(power&1) result=result*base%p;
		base=base*base%p;
		power>>=1;
	}
	write((result%p)/m%m);
	return 0;
}
```

---

## 作者：666yuchen (赞：2)

> 给定两个数 $n$ 和 $m$。

> 输出 $\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$ 的值。

> $n \le 10^{18},m \le 10^4$。



------------


因为数据范围太大，无法直接暴力。

我们断言：从 $10^n$ 中减去 $m^2$ 的倍数对答案没有任何影响。

下面我将推导出这个结论。

$$\begin{aligned}&\left\lfloor\frac{10^n \bmod m^2}{m}\right\rfloor \pmod  m \\&\equiv \left\lfloor\frac{10^n-km^2}{m}\right\rfloor \pmod m\\&\equiv \left\lfloor\frac{10^n}{m}\right\rfloor-km \pmod m \\&\equiv \left\lfloor\frac{10^n}{m}\right\rfloor \pmod m \end{aligned}$$

其中 $k \in \mathbb Z$。

时间复杂度 $\mathcal O(\log n)$。


------------


```cpp
#define int long long
int n,m,res=1;
int ksm(int x,int y,int mod)//快速幂
{
  int aaa=1;
  while(y)
  {
    if(y&1)aaa=aaa*x%mod;
    x=x*x%mod;
    y>>=1;
  }
  return aaa;
}
signed main()
{
  cin>>n>>m;
  cout<<ksm(10,n,m*m)/m;//公式
  return 0;
}
```

---

## 作者：_txb_ (赞：1)

### 题目：[[ARC111A] Simple Math 2](https://www.luogu.com.cn/problem/AT_arc111_a)

## 题意：
给出我们 $n$ 和 $m$，让我们求出 $\left\lfloor\dfrac{10^n}{m}\right\rfloor\bmod{m}$ 的值。
## 思路：
因为 $n$ 很大，所以就想到了快速幂，根据其他大佬我们已知 $\left\lfloor\dfrac{10^n}{m}\right\rfloor\bmod{m}=\left\lfloor\dfrac{10^n\bmod m^2}{m}\right\rfloor \bmod m$，直接就可以用快速幂来写。

### 推导过程：
这个，$\left\lfloor\dfrac{10^n\bmod m^2}{m}\right\rfloor \bmod m$

等于，$\left\lfloor\dfrac{10^n-km^2}{m}\right\rfloor \bmod m$

也就相当与，$\left\lfloor\dfrac{10^n}{m}-km^2\right\rfloor \bmod m$

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;//十年oi一场空，不开longlong见祖宗 
long long f(long long x,long long y,long long mod)
{
	long long ans=1%mod;
	x%=mod;
	while(y)
	{
		if(y&1) ans=ans*x%mod;
		y>>=1;//用位运算加快速度 
		x=x*x%mod;
	}
	return ans;
}
int main()
{
    cin>>n>>m;
    cout<<f(10,n,m*m)/m%m;//根据公式 
    return 0;
}
```

---

## 作者：yzm0325 (赞：1)

# [ARC111A] Simple Math 2 题解

## 题目大意

给定两个数 $n,m$，求 $\lfloor \frac{10^n}{m} \rfloor \bmod m$ 的值。

## 思路

一看数据范围有点可怕，不能直接快速幂。

那么我们设法证明：把这个式子对 $m^2$ 取模不影响结果。

取模后，原式等于

$$\lfloor \frac{10^n \bmod m^2}{m} \rfloor \pmod m$$

设 $k$ 为在条件 $\lfloor \frac{10^n-km^2}{m} \rfloor \geq 0$ 成立下的最大非负整数，那么式子可以继续转换成：

$$\lfloor \frac{10^n-km^2}{m} \rfloor \pmod m$$

把 $\lfloor \frac{km^2}{m} \rfloor$ 约分后提到外面去，得：

$$\lfloor \frac{10^n}{m} \rfloor-km \pmod m$$

此时 $km$ 是 $m$ 的倍数，可以直接消掉。得证。

接下来搬出快速幂模板就结束了！

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m;
ll powermod(ll a, ll b, const ll p) { // 快速幂模板
    ll base = a, ans = 1;
    while(b > 0) {
        if(b & 1) ans = (ans * base % p) % p;
        base = (base % p * base % p) % p;
        b >>= 1;
    }
    return ans % p;
}
int main() {
    cin >> n >> m;
    cout << powermod(10, n, m * m) / m; // 题目给的式子
    return 0; // 完结撒花！！（题外话：竟然不 UKE 了）
}
```

---

## 作者：ZXXS (赞：1)

一道数学题。

### 解法

$$\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor \bmod m$$

相当于
$$\left\lfloor\frac{10^n-k\times m^2}{m}\right\rfloor \bmod m$$
也就是
$$\left\lfloor\frac{10^n}{m}-k\times m^2\right\rfloor \bmod m$$
即
$$\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor \bmod m$$

------------
### 结论
$$\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$$
就相当于
$$\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor \bmod m$$

### 实现
$10^n\bmod m^2$ 使用快速幂，上下的模拟

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//int会炸
using namespace std;
int n,m;
int f(int x,int y,int Mod)//快速幂模板
{
	int ans=1%Mod;
	x%=Mod;
	while(y)
	{
		if(y&1)
		{
			ans=ans*x%Mod;
		}
		y>>=1;
		x=x*x%Mod;
	}
	return ans;
}
signed main()//用signed类型
{
    cin>>n>>m;
    cout<<f(10,n,m*m)/m%m<<endl;//上面的公式
    return 0;
}
```

---

## 作者：_czy (赞：1)

## 思路

$10^n(n\le10^{18})$，一眼快速幂。

不过，发现它没有取模，需要高精？

但是，后面有一个取模，考虑将它移进来。

因为有一个除数，所以，我们将模数与除数相乘，防止对答案造成影响。

就变成了：

$$\lfloor\frac{10^n\bmod m^2}{m}\rfloor$$

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
int m;
int qpow(ll y,int p){
	ll s=1,x=10;
	while(y){
		if(y&1)s=s*x%p;
		x=x*x%p,y>>=1;
	}
	return s;
}
int main(){
	scanf("%lld%d",&n,&m);
	printf("%d",qpow(n,m*m)/m);
}
```

---

## 作者：pfrig729 (赞：1)

### 分析
看到 $n \le 10^{18}$ 之后就能知道不能暴力，考虑使用快速幂。但是快速幂模板是需要一个东西取余的，这里没有，就需要我们转换一下。

$\left \lfloor \frac {10^n}{m} \right \rfloor \bmod m$

$=(\left \lfloor \frac {10^n}{m} \right \rfloor - km)\bmod m$

$=\left \lfloor \frac {10^n - km^2}{m} \right \rfloor \bmod m$

$=\left \lfloor \frac {10^n \bmod m^2}{m} \right \rfloor \bmod m$

所以我们在求快速幂的时候对 $m^2$ 取余就可以了。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n;
int m;
inline long long _(int a,long long k,int p)
{
    long long res=1%p;
    while(k)
    {
        if(k&1)res=(long long)res*a%p;
        a=(long long)a*a%p;
        k>>=1;
    }
    return res;
}
int main()
{
	scanf("%lld%d",&n,&m);
	printf("%lld",_(10,n,m*m)/m%m);
	return 0;
}
```

---

## 作者：FreedomKing (赞：1)

鉴定为数学题。

### 题目大意

给定两个整数 $n$ 和 $m$，请你输出 $\left\lfloor\dfrac{10^n}{m}\right\rfloor\bmod{m}$ 的值，但是 $1\le n\le 10^{18}$。

### 思路

数据范围蛮唬人的，不能直接套快速幂，考虑推出变式，使求幂的时候能有模数。

我们设一个非负整数 $k$，以 $-km$ 代替取模，则由原式可得

$$\left\lfloor\dfrac{10^n}{m}\right\rfloor-km$$

将 $km$ 放入分数内得

$$\left\lfloor\dfrac{10^n-km^2}{m}\right\rfloor$$

最后，再把取模还原回来得

$$\left\lfloor\dfrac{10^n\bmod{m^2}}{m}\right\rfloor$$

这样就解决了取模的问题，用快速幂输出即是答案。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,t,k;
inline int qpow(int x,int p,int mod){
	x=(p?x:1);
	mod=(mod?mod:LONG_LONG_MAX);
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (x*t)%mod;
}
signed main(){
	cin>>n>>m;
	cout<<floorl(qpow(10,n,(m*m))/m);
	return 0;
}
```

---

## 作者：zhanghaosong (赞：1)

# AT_arc111_a [ARC111A] Simple Math 2 题解

一眼快速幂。

### 思路介绍

由楼上楼下的介绍，我们已经知道

$\left  \lfloor \frac{10^n}{m} \right \rfloor \equiv \left  \lfloor \frac{10^n \bmod m^2}{m} \right \rfloor \pmod m$

也很好证明，理由是分子减一个 $m^2$ 的倍数，使它变成一个 $10^n$，就可以将分子上的 $\bmod m$ 消去。

所以我们可以计算 $\left \lfloor \frac{10^n}{m} \right \rfloor $ 的值。

### 快速幂

实现过程：

计算 $a^b$：

如果 $b$ 是 $2$ 的倍数，则 $a^b={(a^\frac{b}{2}})^2$；

否则，$a^b=\displaystyle a^{\left \lfloor \frac{b}{2}  \right \rfloor  }\times a^{\left \lfloor \frac{b}{2}  \right \rfloor  }\times a$。

记得边乘边取模！

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
long long x,y;
long long ksm(long long a,long long b,long long mod){ //计算快速幂
	long long ans=1;
	while(b){
	    if(b&1){
	    	ans=ans*a%mod;
		}
	    a=a*a%mod;
	    b>>=1;
	}
return ans;
}
int main(){
	cix>>x>>y;
	cout<<ksm(10,x,y*y)/y;
return 0;
} 
```


---

## 作者：ruanwentao666 (赞：1)

# AT_arc111_a 题解
[题目](https://www.luogu.com.cn/problem/AT_arc111_a)

## 问题转化
题目中的式子不方便我们计算，所以我们要把式子变形。

首先给出结论：$\lfloor \frac{10^n}{m} \rfloor \bmod m$ 与 $\lfloor \frac{10^n \bmod m^2}{m} \rfloor \bmod m$ 恒等。

我们来证明一下这个结论：

首先我们知道 $10^n \bmod m^2$ 可以写成 $10^n - k \times m^2$ $(k \in Z)$

所以 $\lfloor \frac{10^n \bmod m^2}{m} \rfloor \bmod m$ 可化为 $\lfloor \frac{10^n - k \times m^2}{m} \rfloor \bmod m$

化简，得：
$$\lfloor \frac{10^n}{m} -k \times m \rfloor \bmod m$$

通过模运算的法则，可得：
$$\lfloor \frac{10^n}{m} \rfloor \bmod m - k \times m \bmod m$$

因为 $k \times m \bmod m$ 的值为0，所以原式可化为：
$$\lfloor \frac{10^n}{m} \rfloor \bmod m$$

所以$\lfloor \frac{10^n}{m} \rfloor \bmod m$ 与 $\lfloor \frac{10^n \bmod m^2}{m} \rfloor \bmod m$相等

而式子 $\lfloor \frac{10^n \bmod m^2}{m} \rfloor \bmod m$ 可以用[快速幂](https://www.luogu.com.cn/problem/P1226)算法求解

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int m; 
long long ksm(long long x,long long y,int z){
	x%=z;
	if(y==1)return x;
	if(y&1)
		return ksm(x*x,y>>1,z)*x%z;
	return ksm(x*x,y>>1,z)%z;
}
int main(){
	cin>>n>>m;
	int t=ksm(10,n,m*m);
	cout<<(t/m)%m;
	return 0;
}

```


---

## 作者：yzx3195 (赞：0)

# 题目大意
给定两个数 $n$ 和 $m$。
输出 
$$\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$$
的值。
# 思路
看到 $n$ 的范围，一看快速幂，但是，又没有模数，考虑将后面那个模数提到里面去。怎么提？

我们知道，模数不能与除数相模，所以我们将它与除数结合一下，即：
$$ \left\lfloor\frac{10^n \bmod m^2}{m}\right\rfloor $$

~~快速幂模板~~。
# Code
```cpp

#include<bits/stdc++.h>
using namespace std;

#define int long long

int n;

int m;

int bin_pow(int a,int b,int mod)
{
	int res = 1;
	while(b > 0)
	{
		if(b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res % mod;
}

signed main()
{
	scanf("%lld%lld", &n, &m);
	
	printf("%lld", bin_pow(10, n, m * m) / m);
	
	return 0;
}
```

---

## 作者：Guizy (赞：0)

看到题目一眼 [快速幂](https://www.luogu.com.cn/problem/P1226)。兴奋地打……

然后发现 $\lfloor\frac{10^n}{m}\rfloor$ 很不好求……

于是就考虑怎么转换。

单独看 $\lfloor\frac{10^n}{m}\rfloor$，看了很久也没有结论，然后就想是否是和式子后半部分的 $\mod n$ 有关，于是想到了：

$$\lfloor\frac{10^n}{m}\rfloor\equiv\lfloor\frac{10^n}{m}\rfloor-km\equiv\lfloor\frac{10^n-km^2}{m}\rfloor\equiv\lfloor\frac{10^n\bmod m^2}{m}\rfloor(\bmod m)$$

于是得出结论：快速幂模板，计算时对 $m^2$ 取模。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll n,m;

ll ksm(ll a,ll n,ll p){
	ll ans=1;
	while(n){
		if(n&1) ans=(ans*a)%p;
		a=(a*a)%p;
		n>>=1;
	}
	return ans%p;
}

int main(){
	
	cin>>n>>m;
	cout<<(ksm(10,n,m*m)/m)%m;
	
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

给你两个数 $n$ 和 $m$ ，让你求出 $\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$ 的值。

## 解题思路

这道题第一眼就知道是数学结论题，如果直接使用快速幂会炸掉。

所以我们将这个式子化简一下：

$\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n}{m}\right\rfloor-km \bmod m$

$\large=\left\lfloor\frac{10^n}{m}-km\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n-k m^2}{m}\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor \bmod m$

这时候我们就可以直接用快速幂来做了。

时间复杂度 $\mathcal O(\log n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, ans;
long long qpow(long long x, long long y, long long mod) {
	if(x == 0) {
		return 0;
	}
	if(y == 0) {
		return 1;
	}
	long long s = 1;
	while(y) {
		if(y & 1) {
			s = (s * x) % mod;
		}
		x = x * x % mod;
		y /= 2;
	}
	return s % mod;
}
int main() {
	cin >> n >> m;
	int ans = qpow(10, n, m * m);
	ans = (ans / m) % m;
	cout << ans;
	return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc111_a [ARC111A] Simple Math 2

### Description

给定两个数 $n$ 和 $m$， 输出 $\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$ 的值。

### Solution

因为 $n<10^{18}$，所以暴力枚举肯定不行。但直接求也不好求，所以我们考虑将原式变形。

在此，我先介绍一个公式：$(a-km)≡a(\bmod m)$

证明也很简单：$(a-km)\bmod m=a\bmod m-km\bmod m=a\bmod m-0=a\bmod m$

带入原式，则有 $\large\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n}{m}\right\rfloor-km \bmod m$

$\large=\left\lfloor\frac{10^n}{m}-km\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n-k m^2}{m}\right\rfloor \bmod m$

再对分子部分使用上述公式，则有：

$\large\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n-km^2}{m}\right\rfloor \bmod m$

$\large=\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor \bmod m$

而这个算式则可以使用[快速幂](https://oi-wiki.org/math/binary-exponentiation/)计算。

总时间复杂度 $O(\log n)$。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int zyass(int a,int b,int p){
	int ans=1;
	while(b>0){
		if(b%2==1){
			ans=ans*a%p;
		}
		a=a*a%p;
		b/=2;
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	cout<<zyass(10,n,m*m)/m;
	return 0;
}



---

## 作者：Frictional (赞：0)

## 思路
一看，$n\leqslant 10^{18}$ 那这肯定是道数学。题目给定 $m,n$ 让我们求 $\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$ 的值。显然 $10^n$ 可能会是个极大的值，所以考虑取模。

首先根据取模的意义，这个式子可以转换为 $\left\lfloor\frac{10^n}{m}\right\rfloor -km$ 再将 $-km$ 放到分子上。就可以得到 $\left\lfloor\frac{10^n-km^2}{m}\right\rfloor$ 之后再变成取模的形式就可以得到 $\left\lfloor\frac{10^n\bmod m^2}{m}\right\rfloor$。这样就可以套用快速幂了。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(a,b,c) for(int a=b;a<=c;a++)
#define ROF(a,b,c) for(int a=b;a>=c;a--)
#define se second 
#define fi first
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define debug(x) cerr<<#x<<'='<<x<<endl
int rd(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' or ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
int n,m;
int power(int x,int y,int mod){
    int res=1;
    while(y){
        if(y&1) res=(res*x)%mod;
        x*=x;
        x%=mod;
        y>>=1;
    }
    return res;
}
int temp;
signed main(){
    n=rd(),m=rd();
    temp=power(10,n,m*m);
    cout<<temp/m;
    return 0;
}

```


---

## 作者：So_noSlack (赞：0)

[洛谷连接](https://www.luogu.com.cn/problem/AT_arc111_a)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc111_a)

## 题目简述

给定两个数 $n$ 和 $m$，输出 $\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m$ 的值。

数据范围：$n \le 10^{18},m \le 10^4$

## 思路

首先看到数据范围还是很大的，直接快速幂会炸，所以需要一些优化操作。

推理如下：

$$\left\lfloor\frac{10^n}{m}\right\rfloor \bmod m \equiv \left\lfloor\frac{10^n}{m}\right\rfloor - k \times m \bmod m \equiv \left\lfloor\frac{10^n - k \times m^2}{m}\right\rfloor \bmod m \equiv \left\lfloor\frac{10^n \bmod m^2}{m}\right\rfloor \bmod m$$

经过以上推理，可以发现，仅需用快速幂求 $10^n \bmod m^2$ 的值即可，时间复杂度 $O(\log n)$，可以通过。

其中快速幂的代码可以用循环实现（本人觉得比较好用）。

```cpp
long long qpow(long long a, long long b, long long p) {
	long long ans = 1;
	while(b) {
		if(b & 1) ans *= (a % p), ans %= p;
		a = (a * a % p);
		b /= 2;
	}
	return ans;
}
```

解决快速幂后，此题就非常简单了，代码如下：

```cpp
#include<iostream>
using namespace std;

long long n, m, ans = 0;

long long qpow(long long a, long long b, long long p) {
	ans = 1;
	while(b) {
		if(b & 1) ans *= (a % p), ans %= p;
		a = (a * a % p);
		b /= 2;
	}
	return ans;
}

int main() {
	cin >> n >> m;
	cout << qpow(10, n, m * m) / m << endl;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/126321425)

$$\texttt{The end!}$$

---

## 作者：zxh923 (赞：0)

# AT_arc111_a [ARC111A] Simple Math 2 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc111_a)

### 引理

$\lfloor \frac{10^n-k \times m^2}{m} \rfloor \pmod m$

$\equiv \lfloor \frac{10^n}{m} \rfloor -k\times m \pmod m$

$\equiv\lfloor \frac{10^n}{m} \rfloor \pmod m$

我们同时可以发现，如果一个数对 $m$ 取余，那就相当于把这个数减去 $k \times m$，这也就等价于一开始的式子。

原式中减去 $k \times m^2$ 的原因是，要把分母上的 $m$ 抵消掉。

### 思路

由引理不难得出，我们可以把原式的分子一直对 $m^2$ 进行取余，这样可以保证它不会爆掉。

但是这个数据范围一个一个乘肯定会时间超限，所以我们要用快速幂。

快速幂就是，如果当前的指数为 $a^{2\times k}$，就分成 $a^k \times a^k$，否则分为 $a^k \times a^k \times a$。

快速幂板子点[这里](https://www.luogu.com.cn/paste/3b4mevsb)。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
int quick_power(int x,int y,int mod){//快速幂板子
	ans=1;
	while(y){
		if(y&1){
			ans*=(x%mod);
			ans%=mod;//记得及时取余
		}
		x=(x*x%mod);
		y/=2;
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	cout<<quick_power(10,n,m*m)/m;
	return 0;
} 
```


---

