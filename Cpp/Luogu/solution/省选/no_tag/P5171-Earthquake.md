# Earthquake

## 题目描述

给定 $a,\,b,\,c$ ，求满足方程 $ax+by \leqslant c$ 的非负整数解个数。

## 说明/提示

**样例解释：**

若以 $(x,\,y)$ 表示一组合法解，样例的 $12$ 组合法解如下：

$(0,\,0)$，$(0,\,1)$，$(0,\,2)$，$(0,\,3)$，$(1,\,0)$，$(1,\,1)$，$(1,\,2)$，$(2,\,0)$，$(2,\,1)$，$(3,\,0)$，$(3,\,1)$，$(4,\,0)$ 。

**数据规模：**

||||
|:-:|:-:|:-:|
|测试点编号|$a,\,b$|$c$|
|$1 \sim 5$|$\leqslant 10$|$\leqslant 10$|
|$6 \sim 10$|$\leqslant 10^5$|$\leqslant 10^9$|
|$11 \sim 25$|$\leqslant 10^9$|$\leqslant 10^{18}$|

对于所有数据，$1 \leqslant a,\,b \leqslant 10^9,\ 0 \leqslant c \leqslant \min(a,\,b) \times 10^9$ 。

## 样例 #1

### 输入

```
3 4 13```

### 输出

```
12```

# 题解

## 作者：Aw顿顿 (赞：15)

## 前置知识

**[【提高数学】类欧几里得算法的盛宴](https://www.luogu.com.cn/blog/AlanWalkerWilson/Akin-Euclidean-algorithm-Basis)**

## 题意简述

给定 $a,b,c$，求 $ax+by \le c$ 非负整数解的个数，我们可以转换：

$$ax+by \le c\ \to\ by\le c-ax$$


$$by\le c-ax\ \to\ y\le\left\lfloor{\dfrac{c-ax}{b}}\right\rfloor$$

对于 $y$，合法的 $x$ 的个数是 $\left\lfloor{\dfrac{c-ax}{b}}\right\rfloor+1$，之所以要 $+1$ 是因为符号是 $\le$。

令 $y=0$，此时存在 $ax\le c$，即 $x\le\left\lfloor\dfrac{c}{a}\right\rfloor$，那么我们需要枚举的 $x$ 范围是 $0\sim\left\lfloor\dfrac{c}{a}\right\rfloor$。

进一步将要求的量表述出来，即在每一个 $x$ 的情况下，计算存在多少个合法解，即：

$$\sum\limits_{x=0}^{\left\lfloor\frac{c}{a}\right\rfloor}\left\lfloor{\dfrac{c-ax}{b}}\right\rfloor+1$$

诶，长得，是不是有点像类欧？然而你也不能直接把 $-b$ 代入计算，那么我们转换，用类似于 JZP 题解的方式，在分子加入 $bx$，在外部减去 $\left\lfloor{\dfrac{bx}{b}}\right\rfloor$，即 $x$，式子就变成：

$$\sum\limits_{x=0}^{\left\lfloor\frac{c}{a}\right\rfloor}\left\lfloor{\dfrac{(b-a)x+c}{b}}\right\rfloor-x+1$$

为了能用类欧，我们需要让 $b-a>0$，那么就在 $b<a$ 时使用 $\text{swap}(a,b)$，这样就处理完毕。对于式子的第一部分：

$$\sum\limits_{x=0}^{\left\lfloor\frac{c}{a}\right\rfloor}\left\lfloor{\dfrac{(b-a)x+c}{b}}\right\rfloor$$

已经可以用 $\text{Akin\ Euclidean}(b-a,c,b,\frac{a}{c})$ 来解决了。

但我们发现这个 $x$ 不好处理，于是我们单独拿出来：

$$\sum\limits_{x=0}^{\left\lfloor\frac{c}{a}\right\rfloor}-x+1$$

用基本的等差数列来求和得到：

$$\dfrac{\left(0+\left\lfloor\frac{c}{a}\right\rfloor\right)\times\left(\left\lfloor\frac{c}{a}\right\rfloor+1\right)}{2}+\left\lfloor\frac{c}{a}\right\rfloor$$

其中，大概是这样：

- $0$ 是首项

- $\left\lfloor\frac{c}{a}\right\rfloor$ 是末项

- 项数是 $\left\lfloor\frac{c}{a}\right\rfloor+1$

- 在这个式子后的那个 $\left\lfloor\frac{c}{a}\right\rfloor$ 是 $1$ 对整个求和式子的贡献

那么我们直接套到原式当中就是：

$$\left(\sum\limits_{x=0}^{\left\lfloor\frac{c}{a}\right\rfloor}\left\lfloor{\dfrac{(b-a)x+c}{b}}\right\rfloor\right)+\dfrac{\left\lfloor\frac{c}{a}\right\rfloor\left(\left\lfloor\frac{c}{a}\right\rfloor+1\right)}{2}+\left\lfloor\frac{c}{a}\right\rfloor$$

那么推导结束。

## 代码实现

如下，其中的 $f$ 函数就是类欧几里得函数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a,b,c,s;
int f(int a,int b,int c,int n){
    if(a==0)return((b/c)*(n+1));
    if(a>=c||b>=c)return f(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
    int m=(a*n+b)/c;
    return n*m-f(c,c-b-1,a,m-1);
}signed main() {
	cin>>a>>b>>c;if(b<a)swap(b,a);
	cout<<f(b-a,c,b,c/a)-(c/a)*(c/a+1)/2+(c/a)+1<<endl;
	return 0;
}
```

---

## 作者：xgzc (赞：10)

~~本题解适合公式恐惧症患者~~

我们先把样例画出来：

![Gr1.png](https://i.loli.net/2019/11/07/MwryDtnRv54HAkc.png)

看到它是一个减函数感觉很烦，考虑把函数转过来一下：

![Gr2.png](https://i.loli.net/2019/11/07/U4qPK9HySQAvwsj.png)

转过来的函数通过推导可得为：
$$
y = \frac abx + \frac {c \bmod a}b
$$
于是问题变为了求函数 $y = \frac {ax + b} c \quad (x \leq n)$下面的整点数。

讨论两种情况：

#### $c \leq a$ 或 $c \leq b$

此时斜率或者截距是 $\geq 1$ 的，考虑将它的斜率或者截距减小。

每次当斜率减小 $1$ 时，$x = 1$ 这个位置就会少算 $1$ 个点，$x = 2$ 这个位置就会少算 $2$ 个点,依此类推,可以得出少算的整点数为 $\sum_{i=0}^n i = \frac {n(n + 1)}2$。

截距减 $1$ 同理，可以算出少算的整点数为 $\sum_{i=0}^n 1 = n + 1$。

于是我们就可以将斜率和截距减小到 $< 1$ 的级别了。

可以对着这张图理解一下：

![Gr3.png](https://i.loli.net/2019/11/07/BSPfFlLrA7bWV6y.png)

#### $c > a$ 且 $c > b$

考虑补全成一个矩形，拿总点数减去多出来的三角形个数：

![G1.png](https://i.loli.net/2019/11/07/CJc6vHlB81MTFG4.png)

将这个三角形沿着直线 $y = x$ 翻折一下，可以得出直线 $y = \frac {ax + b}c$ 沿直线 $y = x$ 翻折后的直线为 $y = \frac {cx - b} a$：

![G2.png](https://i.loli.net/2019/11/07/Hb6LieDun7ITqo3.png)

发现这条直线的截距出现了负数，考虑怎么将截距变成正数。

将直线向左平移 $1$ 个单位即可，可以知道这样做不会对答案有影响。

![G3.png](https://i.loli.net/2019/11/07/bjxpLoXrKB2GHUl.png)

还有一个问题，就是边界线上的点是不能被减掉的，但是我们却把它减掉了。

把截距扰动一下即可，具体来说就是给截距减掉一个较小的数 $\frac 1a$，这样就不会算到边界了。

所以这条直线的解析式就变成了 $y = \frac ca x + \frac {c-b-1}a$，和代数方法推出来的式子是一样的。如下图所示：

![G4.png](https://i.loli.net/2019/11/07/3xlshZfNmLX7dqg.png)

这样我们就可以不用公式~~而是大量的图片~~来解决这题了。

~~不过貌似没有什么扩展性？~~

---

## 作者：⚡Sagimune⚡ (赞：6)

#### 类欧几里得算法
$$ax+by-c\le 0$$
等价于求 $y={c-ax\over b}$ 在第一象限及$x,y$非负半轴上的整点数

设 $n=\lfloor{\frac ca}\rfloor$

$\because$ 线段 $y={c-ax\over b}$ 两端点坐标分别为 $(0,\frac cb),(n,{c-an\over b})$

将两端点对换，使$f(x)$成为增函数 ，分别为$(0,{c-an\over b}),(n,\frac cb)$

则$f(x)=\frac abx + {c-an\over b}=\frac abx + {c-a{\lfloor{\frac ca}\rfloor}\over b}={ax+{c\%a}\over b}$

$\sum {f(x)}=\sum_{i=0}^n\{{\lfloor{ai+{c\%a}\over b}\rfloor+1\}}$

$\therefore$
代入为 $$f(a,c\%a,b,\lfloor{\frac ca}\rfloor)+\lfloor{\frac ca}\rfloor+1$$

其中$f(a,b,c,n)=\sum_{i=0}^n{\lfloor {ai+b\over c}\rfloor}$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,c;
ll calc(ll a,ll b,ll c,ll n)
{
    if(!a) return b/c*(n+1);
    if(a>=c||b>=c) return n*(n+1)/2*(a/c)+(n+1)*(b/c)+calc(a%c,b%c,c,n);
    ll m=(a*n+b)/c;
    return m*n-calc(c,c-b-1,a,m-1);
}
int main()
{
    scanf("%lld%lld%lld",&a,&b,&c);
    printf("%lld",calc(a,c%a,b,c/a)+c/a+1);
    return 0;
}
```

---

## 作者：nagisa_kun (赞：4)

~~类欧咱们是学不会的了~~

作为蒟蒻只能考虑套万能欧几里了Orz

按照这题的正常解法，我们还是要变形：
要求的是：
$$\begin{aligned}
\sum_{x=0}^{\lfloor{\frac{a}{c}}\rfloor}{\lfloor\frac{c-ax}{b}\rfloor+1}&=\sum_{x=0}^{\lfloor{\frac{a}{c}}\rfloor}{\lfloor\frac{(b-a)x+c}{b}\rfloor-x+1}\\
&=-\frac{\lfloor{\frac{a}{c}}\rfloor(\lfloor{\frac{a}{c}}\rfloor+1)}{2}+\lfloor\frac{a}{c}\rfloor+\sum_{x=0}^{\lfloor{\frac{a}{c}}\rfloor}{\lfloor\frac{(b-a)x+c}{b}\rfloor}
\end{aligned}
$$
后面的式子类欧算，和模板题一样。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ck(x)((x)>=mod?(x)-=mod:(x))
#define kc(x) ((x)<0?(x)+=mod:(x))
#define IOS                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
#define rep(i, a, n) for (int i = a; i <= n; ++i)
#define per(i, a, n) for (int i = n; i >= a; --i)
//#define ONLINE_JUDGE
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
template<typename T>void write(T x)
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

template<typename T> void read(T &x)
{
    x = 0;char ch = getchar();ll f = 1;
    while(!isdigit(ch)){if(ch == '-')f*=-1;ch=getchar();}
    while(isdigit(ch)){x = x*10+ch-48;ch=getchar();}x*=f;
}
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) { return a / gcd(a, b) * b; };
ll ksm(ll a, ll n)
{
    ll ans = 1;
    while (n)
    {
        if (n & 1)
            ans = (ans * a) % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans % mod;
}
//==============================================================
struct node{
    ll cntu,cntv,ans;
    node(){cntu=cntv=ans=0;}
    friend node operator+(const node&a,const node&b){
        //cerr<<"enter"<<endl;
        node res;
        res.cntu=a.cntu+b.cntu;
        res.cntv=a.cntv+b.cntv;
        res.ans=a.ans+b.ans+a.cntu*b.cntv;
        //cerr<<"exit"<<endl;
        return res;
    }
    friend node operator*(node a,ll x){
        node res;
        while(x){
            if(x&1)res=res+a;
            a=a+a;
            x>>=1;
        }
        return res;
    }
};

node f(ll P, ll Q, ll R, ll L, node A, node B) {
    ll x = (P * L + R) / Q;

    if (!x)
        return B * L;

    if (P >= Q) {
        return f(P % Q, Q, R, L, A, A * (P / Q) + B);
    }

    return B * ((Q - R - 1) / P) + A + f(Q, P, (Q - R - 1) % P, x - 1, B,
                                         A) + B * (L - ((ll)Q * x + P - R - 1) / P + 1);
}
ll a,b,c;
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin)!=nullptr;
    freopen("out.txt", "w", stdout)!=nullptr;
#endif
    //clock_t c1 = clock();
    //===========================================================
    cin>>a>>b>>c;
    if(b-a<0)swap(a,b);
    node u,v;
    u.cntu=1;
    v.cntv=1;
    auto res=u*(c/b)+f(b-a,b,c%b,c/a,u,v);
    ll ans=res.ans;
    ans+=c/b;
    ans-=1ll*(c/a)*(c/a+1)/2;
    ans+=c/a;
    ans+=1;
    cout<<ans<<endl;
    //===========================================================
    //std::cerr << "Time:" << clock() - c1 << "ms" << std::endl;
    return 0;
}

```


---

## 作者：jiazhaopeng (赞：3)

不会类欧的可以看[这里](https://oi-wiki.org/math/euclidean/)

枚举 $x$，那么合法的 $y$ 的个数为 $\lfloor \dfrac{c - ax}{b} \rfloor+1$。那么题目要求的就是：
$$
\sum_{x=0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{c-ax}b \rfloor+1
$$
发现和类欧的唯一区别是 $x$ 的系数是负数。但是我们可以在分子上加一个 $bx$ 即可。这里假设 $b \ge a$，当 $b < a$ 的时候可以交换 $a,b$。
$$
\begin{aligned}
\sum_{x=0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{(b-a)x+c}{b} \rfloor - x + 1\\
= \sum_{x=0}^{\lfloor \frac{c}{a}\rfloor} \lfloor \frac{(b-a)x+c}b \rfloor - \frac{\lfloor \frac{c}{a}\rfloor (\lfloor \frac{c}{a} \rfloor + 1)}2+\lfloor \frac{c}{a} \rfloor + 1
\end{aligned}
$$
然后直接用类欧算即可。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
typedef long long ll;
template <typename T> inline void read(T &x) {
	x = 0; char c = getchar(); bool flag = false;
	while (!isdigit(c)) { if (c == '-')	flag = true; c = getchar(); }
	while (isdigit(c)) { x = (x << 1) + (x << 3) + (c ^ 48); c = getchar(); }
	if (flag)	x = -x;
}
using namespace std;
inline ll sol(ll a, ll b, ll c, ll n) {
	if (!a)	return (n + 1) * (b / c);
	if (a >= c || b >= c) {
		return n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c) + sol(a % c, b % c, c, n);
	}
	ll m = (a * n + b) / c;
	return n * m - sol(c, c - b - 1, a, m - 1);
}

int main() {
	ll a, b, c; read(a), read(b), read(c);
	if (b < a)	swap(b, a);
	ll res = 0;
	res += sol(b - a, c, b, c / a);
	res -= (c / a) * (c / a + 1) / 2;
	res += c / a;
	++res;
	cout << res << endl;
	return 0;
}
```



---

## 作者：qinyiyang2012 (赞：1)

### 思路分析

求方程 $ax+by \leqslant c$ 的非负整数解个数。

考虑 $x$ 的范围：

- 最大值显然在 $y = 0$ 时取到，为 $\lfloor \frac{c}{a} \rfloor$
- 最小值显然为 $0$

当我们确定好 $x$ 的值后，$y$ 的范围也就求出来了。

由 $ax+by \leqslant c$，得 $by \leqslant c-ax$，结合题目要求得 $0 \leqslant y \leqslant \frac{c - ax}{b}$。所以在 $x$ 确定时，$y$ 有 $\frac{c - ax}{b} + 1$ 个可能取值。

那么式子也就出来了，即

$$\sum_{x = 0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{c - ax}{b} \rfloor + 1$$

把加一放在外面，变成

$$(\sum_{x = 0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{c - ax}{b} \rfloor) + \lfloor \frac{c}{a} \rfloor + 1$$

注意到 $-a$ 是负数，无法使用类欧，我们考虑在分子上加上 $bx$，在外面减去 $x$，这里我们默认 $b > a$，于是有

$$(\sum_{x = 0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{c + (b - a)x}{b} \rfloor - x) + \lfloor \frac{c}{a} \rfloor + 1$$

把 $-x$ 也提出去，得

$$(\sum_{x = 0}^{\lfloor \frac{c}{a} \rfloor} \lfloor \frac{c + (b - a)x}{b} \rfloor) - \lfloor \frac{c}{a} \rfloor \times (\lfloor \frac{c}{a} \rfloor + 1) / 2 + \lfloor \frac{c}{a} \rfloor + 1$$

前面的用类欧解决即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f(int a,int b,int c,int n){
	if(a>=c||b>=c)return a/c*n*(n+1)/2+b/c*(n+1)+f(a%c,b%c,c,n);
	int m=(a*n+b)/c;
	if(!m)return 0;
	return n*m-f(c,c-b-1,a,m-1);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int a,b,c;
	cin>>a>>b>>c;
	if(b<a)swap(a,b);
	cout<<f(b-a,c,b,c/a)+c/a+1-(c/a)*(c/a+1)/2;
	return 0;
}
```

---

