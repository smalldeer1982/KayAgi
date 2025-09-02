# Calendar Ambiguity

## 题目描述

Berland year consists of $ m $ months with $ d $ days each. Months are numbered from $ 1 $ to $ m $ . Berland week consists of $ w $ days. The first day of the year is also the first day of the week. Note that the last week of the year might be shorter than $ w $ days.

A pair $ (x, y) $ such that $ x < y $ is ambiguous if day $ x $ of month $ y $ is the same day of the week as day $ y $ of month $ x $ .

Count the number of ambiguous pairs.

## 说明/提示

Here are the pairs for the first test case:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1389E/6a0ee9ce628b44306135f6834937af49e302ba2c.png)

## 样例 #1

### 输入

```
5
6 7 4
10 7 12
12 30 7
1 1 1
3247834 10298779 625324```

### 输出

```
6
9
5
0
116461800```

# 题解

## 作者：Dzhao (赞：7)

一道比较有趣的数学题，但是个人觉得放在 Div 2 的 E 题是不是有点水了？

没看过题目的[点这里](https://www.luogu.com.cn/problem/CF1389E)

看到这种题目，不要多想，拿起笔，直接算！

将题意可以转换为这个式子：

$$(x-1)d+y \equiv (y-1) d+x \ (\!\!\!\!\!\!\!\; \mod w)$$

经过几步移项和消元，我们可以将式子化简，如下：

$$xd+y \equiv yd+x  \ (\!\!\!\!\!\!\!\; \mod w)$$
$$yd-y-xd+x \equiv 0  \ (\!\!\!\!\!\!\!\; \mod w)$$
$$(y-x)(d-1) \equiv 0  \ (\!\!\!\!\!\!\!\; \mod w)$$
于是我们可以得到：
$$w|(y-x)(d-1)$$
进一步化简，将：
$w' \leftarrow \dfrac{w}{\gcd(w,d)},d' \leftarrow \dfrac{d-1}{\gcd(w,d-1)}$

则此时 $w' \bot \ d'$，则式子可以化简为 $w'|(y-x)$，那么现在问提就变成了统计有多少对正整数对 $(x,y)$ 使得 $w'$ 是 $y-x$ 的因数。

我们可以假设$y-x=kw'$，那么我们可以枚举 $k$ 进行求解，但显然这是会超时的，所以我们需要较快的统计。

我们发现 $y$ 最大为 $\min(m,d)$，因为要满足 $y$ 月存在，也要满足 $y$ 天存在。而 $x$ 的最小值为 $1$，所以对于每个 $k$，$y$ 的最小值为 $kw+1$。

我们可以得到一个不等式 $\min(m,d) \geq kw+1$

所以 $k \leq \dfrac{\min(m,d)-1}{w}$
所以 $k_{max}=\lfloor \dfrac{\min(m,d)-1}{w}\rfloor$

而答案就是:

$$\sum\limits_{i=1}^{k_{max}} {\min(m,d)-iw}$$

我们把他分离了式子就变成：

$$\sum_{i=1}^{k_{max}} {\min(m,d)}-\sum_{i=1}^{k_{max}} {iw}$$

前面那一部分是常数项，后面那一部分可以用等差数列求和解决，化简为：

$$k_{max}\times\min(m,d)-\frac{(1+k_{max})k_{max}}{2}w$$

然后这道题就解决了。

$\mathcal{View \ \ Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll x,ll y) {return y==0?x:gcd(y,x%y);}
int T;
ll ans,m,d,w;

int main()
{   
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&m,&d,&w);
		int mn=min(m,d);d--;
		ll Gcd=gcd(d,w);
		d/=Gcd,w/=Gcd;
		ll k=(mn-1)/w;
		ans=mn*k-(1+k)*k/2*w;
		printf("%lld\n",ans);
	}
	return 0;
} 
```

$Thanks \ for\ watching$

---

## 作者：_•́へ•́╬_ (赞：6)

### 思路

不按题意来，把星期数用零下标，这样方便使用 $\bmod$。

把文字语言转换成数学语言：
$$
(x-1)+d(y-1)\equiv(y-1)+d(x-1)\pmod w
$$

$$
x-1+dy-d\equiv y-1+dx-d\pmod w
$$

$$
x+dy\equiv y+dx\pmod w
$$

$$
-y+x+dy-dx\equiv 0\pmod w
$$

$$
w|-(y-x)+d(y-x)
$$

$$
w|(d-1)(y-x)
$$

$$
\texttt{设}(d-1)\times(y-x)=k\times w
$$

$$
y-x=k\times\frac{w}{d-1}
$$

$$
\texttt{约分}\frac{w}{d-1}\texttt{，得到}\frac{a}{b}
$$

$$
y-x=k\times\frac{a}{b}
$$

$$
\texttt{方程左右均为正整数，}\therefore b|k
$$

$$
\texttt{设}k=i\times b
$$

$$
y-x=i\times a
$$

$$
\texttt{设}mn=\min(m,d),mx=\frac{mn-1}{a}
$$

$$
\texttt{还有}1\leq x<y\leq mn
$$

$$
\therefore 1\leq y-x\leq mn
$$

$$
\therefore i\leq mx
$$

如果我们知道 $i$，那么 $(x,y)$ 的个数为 $mn-i\times a$。（$x=1,2,\cdots,mn-i\times a$，$y=i\times a+1,i\times a+2,\cdots,mn$

所以我们要求的就是 $\huge\sum\limits_{i=1}^{mx}mn-i\times a$。

然后我们希望 $O(1)$ 求出它的值。

把它拆开：$\sum\limits_{i=1}^{mx}mn-\sum\limits_{i=1}^{mx}i\times a$。

显然：$mx\times mn-a\times\sum\limits_{i=1}^{mx}i$。

运用某求和公式：$\huge mx\times mn-a\times\frac{(1+mx)\times mx}{2}$。

然后，就没有然后了。

### $code$

```cpp
#include<bits/stdc++.h>
#define min(x,y) ((x)<(y)?(x):(y))
using namespace std;
inline int gcd(const int&x,const int&y){return y?gcd(y,x%y):x;}
main()
{
	register int t,m,d,w,a,b,g,mn,mx;
	for(cin>>t;t--;)
	{
		cin>>m>>d>>w;mn=min(m,d);
		if(d==1){puts("0");continue;}
		a=w;b=d-1;g=gcd(a,b);a/=g;b/=g;
		mx=(mn-1)/a;//i*a<mn
		printf("%I64d\n",1ll*mn*mx-1ll*(1+mx)*mx/2*a);//mn-i*a
	}
}
```



---

## 作者：lzx2005 (赞：3)

这道题的大致意思：

定义 $1$ 年有 $m$ 个月，$1$ 个月有 $d$ 天，$1$ 个星期有 $w$ 天。

求多少个日期 $x$ 月 $y$ 日和 $y$ 月 $x$ 日在一个星期里的排名相同。

首先，我们发现由于单位的不同，我们不便于研究数据的性质。

所以，我们将日期转化为一年的第几天的形式。那么，问题就变成：有多少个无序数对 $(x,y)$ 使得 $x\times d+y\equiv y\times d+x(\mod w)$，移项得：$(x-y)\times (d-1)\equiv0(\mod w)$，即 $w|(x-y)\times (d-1)$ 。 

我们考虑如何满足这个条件：设 $q=\frac{(x-y)\times (d-1)}{w}$。由于我们已知 $w$ 和 $d$，所以我们可以通过辗转相除法求出 $\gcd(w,d-1)$。那么，显然有 

$\large q=\frac{\frac{(x-y)\times (d-1)}{\gcd(w,d-1)}}{\frac{w}{\gcd(w,d-1)}}=\frac{(x-y)\times \frac{d-1}{\gcd(w,d-1)}}{\frac{w}{\gcd(w,d-1)}}$。由于 $q=\frac{(x-y)\times (d-1)}{w}$，且 $w|(x-y)\times (d-1)$ 所以 $q$ 是正整数。所以$\frac{w}{\gcd(w,d-1)}|(x-y)\times \frac{d-1}{gcd(w,d-1)}$。显然，$\gcd(\frac{w}{\gcd(w,d-1)},\frac{d-1}{gcd(w,d-1)})=1$。所以 $\frac{w}{\gcd(w,d-1)}|(x-y)$。

显然，$\frac{w}{\gcd(w,d-1)}$ 可以直接求出。考虑如何确定 $x,y$。

首先，我们找出 $x,y$ 的上界：$p=\min(m,d)$（$x,y$ 显然不能超过$\min(m,d)$，否则日期中就不会出现 $x$ 月 $y$ 日或 $y$ 月 $x$ 日）。

设 $x>y$，令 $x-y=i\times \frac{w}{\gcd(w,d-1)}$,对于每一个合法的 $i$，它对答案的贡献就是 $p-i\times \frac{w}{\gcd(w,d-1)}$（因为 $x$ 显然可以取 $i\times \frac{w}{\gcd(w,d-1)}+1\sim p$ 之间的任意整数，且每一个 $x$ 都有唯一的 $y$ 与之对应）。所有的 $i$ 对答案的贡献之和即为结果。

但是 $i$ 的取值范围很大，在 $1\sim \lfloor\frac{p-1}{\frac{w}{\gcd(w,d-1)}}\rfloor$ 之间，直接枚举显然会导致超时，所以，我们需要进一步的优化。

研究一下答案的式子 $ans=\large \sum \limits ^{\large\lfloor\frac{p-1}{\frac{w}{\gcd(w,d-1)}}\rfloor}_{i=1} (p-i\times \frac{w}{\gcd(w,d-1)})$。不难发现，减号两侧的 部分可以分开考虑：关于 $p$ 的项的和显然就是 $p\times \lfloor\frac{p-1}{\frac{w}{\gcd(w,d-1)}}\rfloor$。而对于后面的项，显然所有的系数 $i$  构成等差数列，利用等差数列求和公式可得：$(\large \frac{(1+\lfloor\frac{p-1}{\frac{w}{\gcd(w,d-1)}}\rfloor)\times \lfloor\frac{p-1}{\frac{w}{\gcd(w,d-1)}}\rfloor}{2})\times \frac{w}{\gcd(w,d-1)}$。将两项相减即可。

时间复杂度瓶颈在于求 $\gcd(w,d-1)$，总时间复杂度 $O(t\times \log(w+d-1))$。可以通过本题。

参考程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
inline ll read()
{
	ll f=1,lzx=0;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();}
	while(c<='9'&&c>='0'){lzx=lzx*10+c-'0';c=getchar();}
	return lzx*f;
}
inline ll GCD(ll a,ll b)//辗转相除法求GCD
{
	if(a<b)swap(a,b);
	if(b==0)return a;
	return GCD(b,a%b);
}
int main()
{
	int T=read();
	while(T--)
	{
		ll m=read(),d=read(),w=read(),gcdd=w/GCD(d-1,w);
		ll p=min(m,d),ans=
		(p-1)/gcdd*p-((1+(p-1)/gcdd )*((p-1)/gcdd)/2*gcdd);
		printf("%lld\n",ans);
	} 
	return 0;
}
```



---

## 作者：huayucaiji (赞：3)

**UPD1：2020.7.31 修正一处笔误（望管理大大通过）**

----------

我们会发现这个题目只有一个可以入手的点，其他都是定义类条件。

>A pair (x,y) such that x<y is ambiguous if day x of month y is the same day of the week as day y of month x.

用数学方法表示也就是 

$$xd+y\equiv yd+x\ (\operatorname{mod}\ w)\\xd+y-(yd+x)\equiv 0\ (\operatorname{mod}\ w)\\(d-1)(x-y)\equiv 0\ (\operatorname{mod}\ w)$$

而 $d-1$ 是一个定值。我们只需要关注 $x-y$。但是注意了，我们的 $d-1$ 和 $w$ 可能有相同的质因子，这些就没有必要再在 $x-y$ 包含了。所以我们令 $w'=\frac{w}{\gcd(d-1,w)}$。我们要求的就是有多少对 $(x,y)$ 满足 $x-y\equiv 0\ (\operatorname{mod}\ w')$。

为了求解这个问题，我们可以考虑弱化条件。假设我们现在求解有多少对 $(x,y)$ 满足 $x-y=k\cdot w'$。那么我们可以用数学方法来解决，就有 $\min(d,m)-k\cdot w'$ 对。~~这个应该十分好理解。~~ 我们再把条件还原，我们就可以枚举 $k$，在累加答案。由于 $x-y\leq \min(m,d)$所以最后的答案就是：

$$\sum\limits_{k=1}^{\lfloor\frac{\min(m,d)}{w'}\rfloor} \min(m,d)-k\cdot w'$$

聪明的小伙伴可能会发现，这样的时间复杂度实在太大，到了 $O(t\cdot\lfloor\frac{\min(m,d)}{w'}\rfloor)$ 应该是过不了的，大家可以试一试。那么我们就要想如何优化。我们再次观察这个式子，发现是一个等差数列,公差是 $-w'$。我们用高斯公式就可以解决这个问题。首项为 $\min(d,m)-w'$，末项为 $\min(d,m)-\lfloor\frac{\min(m,d)}{w'}\rfloor\cdot w'$，项数为 $\lfloor\frac{\min(m,d)}{w'}\rfloor$。所以最终答案为：

$$\frac{(2\min(d,m)-\lfloor\frac{\min(m,d)}{w'}\rfloor\cdot w'-w')\times\lfloor\frac{\min(m,d)}{w'}\rfloor}2$$

这样时间复杂度为 $O(\log(m+d))$。

~~时间复杂度的大户竟是计算 $\gcd$ 你敢相信？~~

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int m,d,w;

int gcd(int x,int y) {
	return y==0? x:gcd(y,x%y);
}

signed main() {
	int t=read();
	while(t--) {
		m=read();d=read();w=read();
		
		w=w/gcd(w,d-1);
		int n=min(m,d);
		int num=n/w;
		int ans=(2*n-w*num-w)*num/2;
		
		cout<<ans<<endl; 
	}
	return 0;
}

```

---

## 作者：gyh20 (赞：2)

转成数学语言，即为求满足如下式子的 $x,y$ 的对数

$1.x,y$ 均为正整数。

$2.x,y\leq min(m,d)$

$3.(x-1)\times d+y \equiv(y-1)\times d + x (\bmod w) $

变一下最后的一个式子。

$(x-y)d+y-x\equiv 0(\bmod w)$

$(d-1)(x-y)\equiv 0(\bmod w)$

$x-y\equiv 0(\bmod \dfrac{w}{\gcd(w,d-1)})$

联系上之前的式子，，令 $x$ 为 $\gcd(w,d-1)$：

$\sum\limits_{i=1}^{\min(m,d)}\sum\limits_{j=1}^{\min(m,d)}[(j-i)\mod x=0]$

假设我们直接枚举 $j$，那么直接可以得出 $i$ 的个数为 $\lfloor \dfrac{j-1}{x}\rfloor$

如果把所有的 $j+1$ 得到：

$\sum\limits_{j=1}^{\min(m,d)-1}\lfloor \dfrac{j}{x}\rfloor$

处理一下边界，再把枚举的数除以 $x$，就变成了等差数列求和。

代码：

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
} 
using namespace std;
int n,m,a,b,c,d,t,ans,lim;
inline int gcd(re int x,re int y){
	return y?gcd(y,x%y):x;
}
signed main(){
	t=read();
	while(t--){
		a=read(),b=read(),c=read();ans=0;
		lim=min(a,b)-1;c/=gcd(c,b-1);
		d=lim-lim%c-1;ans+=(lim-d)*(lim/c);
		ans+=(1+d/c)*(d/c)/2*c;
		printf("%lld\n",ans);
	}
}
```


---

## 作者：jr_inf (赞：1)

注：与题面不同，此处 $x>y$

由题意得 $(x-1)d+y \equiv (y-1)d+x \pmod{w}$

化简得 $(d-1)(x-y) \equiv 0 \pmod{w}$

设 $d>1$。让 $(d-1)$ 和 $w$ 同时除以 $\gcd(d-1,w)$，那么当且仅当 $w\mid(x-y)$ 时，原式成立。

再考虑 $x,y$ 的取值范围，有
$$\begin{cases}
x\leq \min(m,d)\\
(x-1)d+y\leq md\\
(y-1)d+x\leq md
\end{cases}$$

不难发现，当 $\begin{cases}x=m\\y=m-1\end{cases}$ 或 $\begin{cases}x=d\\y=d-1\end{cases}$ 时，后两条不等式恒成立，所以限制条件只有 $x\leq \min(m,d)$。

设 $x-y=kw$，那么满足条件的 $(x,y)$ 共有 $\min(m,d)-kw$ 个，所以总答案为 $\sum_{i=1}^{\min(m,d)-iw\geq0} \min(m,d)-iw$，利用等差数列求和可以做到 $O(1)$。总时间复杂度 $O(\log d)$，瓶颈在于求 $\gcd$。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define int long long
using namespace std;
int t,m,d,w,r;
int gcd(int x,int y){return y?gcd(y,x%y):x;}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>m>>d>>w;
		r=min(m,d);
		d--;
		if(!d)
		{
			cout<<min(d,w)*(min(d,w)-1)/2<<endl;
			continue;
		}
		w/=gcd(d,w);
		int rr=r/w;
		cout<<r*rr-rr*(rr+1)/2*w<<endl;
	}
}
```

---

## 作者：fsy_juruo (赞：1)

### 题意简述

略... （其实是我翻译的不满意）

### 题解

* 撇开题目中花哨的 Berland 历法，将问题形式化描述：

> 给定 $m, d, w$，求得满足下列条件的 $(x,y)$ 数对个数：
> * $1 \leq x \leq \min(m, d)$
> * $1 \leq y \leq \min(m, d)$
> * $x < y$
> * $(x-1) \times d + y \equiv (y-1) \times d + x \pmod w$ 

* 化简条件四可得 $(x-y)(d-1) \equiv 0 \pmod w$，$(x-y)(d-1)+wk=0 \; (k \in \mathbb{Z})$
* $(d-1)$、$w$ 均为定值，设 $g = \gcd(d-1, w)$，则可得一组解（由于 $x < y$ 所以 $x-y$ 取负值）：

$$\begin{cases} x-y = -\frac{w}{g} \\ k = \frac{d-1}{g}\end{cases}$$

* 并可得到通解（$k_1 \in \mathbb{N}^+$）：

$$\begin{cases} x-y = k_1 \times (-\frac{w}{g}) \\ k = k_1 \times \frac{d-1}{g}\end{cases}$$

* 由条件一、二、三得 $x-y$ 的取值范围：$1 - \min(m, d) \leq x-y < 0$，

* 考虑 $x-y = \Delta$ 时的解数：

$x - y = \Delta \rightarrow x = \Delta + y$

$\rightarrow \begin{cases} 1 \leq y + \Delta \leq \min(m, d) \\ 1 \leq y \leq \min(m, d) \end{cases}$

$\rightarrow 1 - \Delta \leq y \leq \min(m, d)$

* 可以看出，$x-y = \Delta$ 时，相应解数就会减少 $|\Delta|$ 个。

* 而 $\Delta = 0$ 时的解数我们可以轻易得到，$|\Delta|$ 的变化又是 **等差** 的，公差为 $\frac{w}{g}$，这部分的贡献可以使用等差数列求和解决。

* 项数 $x = \left\lfloor \frac{1 - \min(m, d)}{\frac{-w}{g}} \right\rfloor$，故答案即为：$x \times \min(m, d) - \frac{x \times (x + 1) \times |\Delta|}{2}$。

### 代码

```cpp
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define LD long double
#define reg register
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
template <typename T>
inline void read(T &x) {
	x = 0; T f = (T) 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) {if(c == '-') f = -f;}
	for(; isdigit(c); c = getchar()) x = x * 10 + c - 48;
	x *= f;
}
template <typename T, typename... Args>
inline void read(T& x, Args&... args) {
    read(x); read(args...);
}
template <typename T>
inline void write(T x) {
	if(x < 0) {x = -x; putchar('-');}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = ' ') {write(x); putchar(sp);}
int main() {
	int t, m, d, w;
	read(t);
	while(t--) {
		read(m, d, w);
		if(d == 1) {
			writesp(0, '\n');
			continue;
		}
		int q = d - 1; int g = std::__gcd(q, w); 
		int f = -w / g, h = q / g;
		int limit = 1 - std::min(m, d);
		int k = limit / f;
	//	std::cout << q << " " << g << " " << f << " " << h << " " << limit << " " << k << " " << std::endl;
		writesp(1ll * k * std::min(m, d) - (1ll * (k + 1) * (-f) * k) / 2, '\n');
	}
	return 0;
}
 
```

---

## 作者：__3E24AC7002AD9292__ (赞：1)

萌新打 VP 赛场切的题，但是这真的有 $2200$？

注意到 $x,y\leq\min\{d,m\}$，考虑如果 $y>d$，那么第 $x$ 月第 $y$ 天不存在；如果 $y>m$，则第 $y$ 月不存在。

把 $m$ 与 $d$ 取个 $\min$，然后愉快地列式子：

$$(x-1)d+y\equiv(y-1)d+x\pmod w$$

因为第 $x$ 个月并没有满，所以左边式子 $d$ 的系数是 $(x-1)$，右边同理。

考虑移项：

$$(y-x)d\equiv y-x\pmod w$$
$$(y-x)(d-1)\equiv0\pmod w$$
$$w\mid(y-x)(d-1)$$

令 $g=\gcd\{w,d-1\}$，到这里比较显然的是，$\frac{w}{g}\mid (y-x)$，那么实际上要求的就是满足上面要求的 $x,y$ 对数。

不难发现 $y-x=t$ 时其可能出现对数为 $m-t$，那么答案所求的就是：

$$\sum_{\frac{w}{g}\mid t,t<m}m-t$$

把两项拆开，求 $m$ 的和比较显然，求 $t$ 的和等差数列求和公式，就做完了。

```cpp
m=min(m,d);
int g=__gcd(d-1,w),c=(m-1)/(w/g);
cout<<c*m-c*(c+1)/2*(w/g)<<'\n';
```

---

## 作者：yuheng_wang080904 (赞：1)

## 题意

Berland 的一年有 $m$ 月，每个月有 $d$ 天，每周有 $w$ 天。保证一年的第一天一定是周一。

求数对 $(x,y)$ 的个数，使得 $x<y$ 且 $x$ 月的第 $y$ 天和 $y$ 月的第 $x$ 天在一周中是同一天。

## 思路

假设有数对 $(x,y)$ 满足条件，则 $dx+y\equiv dy+x\pmod w$，简单化简即可得 $(y-x)(d-1)\equiv 0\pmod w$，因此 $y-x\equiv 0\pmod \frac{w}{\gcd(w.d-1)}$，这样因为 $w,d$ 都是已知的，因此 $\frac{w}{\gcd(w.d-1)}$ 可以 $O(1)$ 算出，我们只需要看有多少组 $(x,y)$ 符合这一条件。

为了叙述方便，我们设 $\frac{w}{\gcd(w.d-1)}=g$，因为 $y>x>0$，因此 $y>g$。当 $g<y\le2g$ 时，每个 $y$ 都有一个 $x$ 与之对应，共有 $g$ 组 $(x,y)$。当 $2g<y\le3g$ 时，每个 $y$ 都有两个 $x$ 与之对应，共有 $2g$ 组 $(x,y)$。当 $3g<y\le4g$ 时，每个 $y$ 都有三个 $x$ 与之对应，共有 $3g$ 组 $(x,y)$……

由题意 $x,y\le \min(m,d)$，假设 $\lfloor \frac{\min(m,d)}{g} \rfloor=k$，则当 $0<y\le kg$ 时，共有 $\sum_{i=1}^{k-1}ig=\frac{kg(k-1)}{2}$。当 $kg<y\le \min(m,d)$ 时，共有 $k(\min(m,d)-kg)$。因此总共是 $\frac{kg(k-1)}{2}+k(\min(m,d)-kg)$ 组 $(x,y)$ 满足条件。

## 代码

接下来放上我的简短代码。时间复杂度为 $O(t)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
int t;
ll m,d,w;
int main(){
	cin>>t;
	while(t--){
		cin>>m>>d>>w;
		ll g=w/gcd(w,d-1);
		ll k=min(m,d)/g;
		ll ans=k*(k-1)*g/2+k*(min(m,d)-k*g);
		cout<<ans<<"\n";
	}
	return 0;
}

```


---

## 作者：Sakura_Emilia (赞：0)

# 一道数论推公式的题目

基本上就是结论题，主要难点就在于推公式，代码反而没有多少东西。

## 题意

Berland 的重新定义了一年中的月份数目、每月天数、每周天数。规定一年有 $m$ 个月，每个月有 $d$ 天，每周有 $w$ 天。已知每年第一天一定是一周的第一天，问有多少个数对 $(x, y)$，$x<y$，使得第 $x$ 月的第 $y$ 天与第 $y$ 月的第 $x$ 天是一周中的同一天。

## 思路分析

捕捉到题干中的关键点：**一周中的同一天**。

由此马上想到**同余**，首先尝试根据题意写出同余方程：
$$
(d-1)x+y\equiv (d-1)y+x \pmod w
$$
化简同余方程可得：
$$
(d-1)(y-x) \equiv 0 \pmod w
$$
对于这种右端为 0 的同余方程，为了更加直观，常常写为整除形式：
$$
w \mid (d-1)(y-x)
$$
由于 $d-1$ 本身是一个直接读入的常数，为了直观起见，令 $c=d-1$，上式可简写为：
$$
w \mid c(y-x)
$$
对于这种被除数为两数乘积的整除式，在数论中有一种常用的化简技巧~~套路~~。首先计算最大公因数，令：
$$
d_0=\gcd(w,\; c)
$$
事实上由于 $w$ 和 $d$ 均已知，故可以使用欧几里得算法快速地计算出 $d_0$ 的值。再进行如下换元：
$$
w=w_0 d_0 \\
c=c_0 d_0 \\
此时且满足条件: \:\: \gcd(c_0,\; w_0) = 1
$$
将换元后的结果代入原整除式可得：
$$
w_0d_0 \mid c_0d_0(y-x)
$$
这里借助整除运算的两点性质：

1. 若 $ab\mid bc$，则有 $a\mid c$；
2. 若 $a\mid bc$，且 $\gcd(a,\;b)=1$，则有 $a\mid c$。

上式化简为：
$$
w_0 \mid y-x
$$
写回同余形式为：
$$
x \equiv y\pmod{w_0}
$$
至此数论推理的部分基本完成，下面的内容就是算法设计层面的分析。

------

由于 $w_0$ 是一个比较容易被计算出的常数，而满足题意的数对 $y$ 和 $x$ 需要相差 $w_0$ 的整数倍。尝试去逐个枚举统计。

## 这里有一个坑点需要注意！！！

注意 $y$ 和 $x$ 的有效取值范围是什么。因为 $y$ 和 $x$ 要轮流作为**月份**和**日期**，因此取值范围应当是从 $1$ 开始，但它的上界为 $\min(d,\;m)$，不然一交换，就构造出了不存在的月份或者是一个月中不存在的日期。

由于分析的时候是按照同余关系写的式子，出于数论中的习惯，从同余类的角度来进行枚举，也就是从 0 开始枚举，$y$ 和 $x$ 可能的取值范围为 $[0,\; n]$，其中 $n=\min(d-1,\;m-1)$。

首先观察下面的模 $d$ 或模 $m$ 的同余类：
$$
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-1,\;\;n
$$
现在需要将这个模数较大的同余类，转换为模数较小的同余类。也就是模 $t*w_0$ 的同余类，其中 $t \in N^*$。

上面的 $n$ 个数中，需要至少保证 2 个数在这样的某个同余类中，讨论该同余类才有意义。可以来确定 $t$ 的上界 $k=[\frac{n}{w_0}]$，这里的中括号表示下取整的高斯函数，也就是 C 语言中的两整数直接相除。



下面开始统计，这些同余类中最多可以包含多少个不同的数对 $x$ 和 $y$。

我们首先枚举每一个同余类，再来从左往右枚举每一个数 $x$。

比如说对于同余类 $w_0$ 得到一列数：
$$
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-w_0-1,\;\;n-w_0
$$
对于这一列数，其中的每一个数 $x$，在它的右侧，都存在一个 $y=x+w_0$ 不超出范围，使得 $(x, y)$ 为一对符合题目条件的数对。

以此类推，可以继续得到一列数：
$$
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-2w_0-1,\;\;n-2 w_0
$$
对于这一列数，其中的每一个数 $x$，在它的右侧，都存在一个 $y=x+2 w_0$ 不超出范围，使得 $(x, y)$ 为一对符合题目条件的数对。

依次可得一列列的数：
$$
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-3 w_0-1,\;\;n-3 w_0 \\
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-4 w_0-1,\;\;n-4 w_0 \\
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-5 w_0-1,\;\;n-5 w_0 \\
\vdots \\
0,\;\;1,\;\;2,\;\;3,\;\;4,\;\;5,\;\;6,\;\;\dots,\;\;n-k w_0-1,\;\;n-k w_0
$$
事实上上面的分析，本质上就是在从左往右枚举所有可能的 $x$，并以不同的跨度来确定 $y$。

统计上述多个式子所包含的元素个数即可。即 $(n-w_0) + (n-2 \times w_0) + (n-3 \times w_0) + \dots +(n-k \times w_0)$，由简单的等差数列求和公式即可化简得到：
$$
结果 = (n+1)\times k-\frac{k(k+1)}{2} \times w_0
$$
直接输出这个结果即可。

完整的代码实现如下：

## AC代码

```cpp
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int T, m, d, w, d0, w0, n, k;

inline void solve() {
    cin >> m >> d >> w;
    d0 = gcd(w, d - 1);
    w0 = w / d0;
    n = min(m - 1, d - 1);
    k = n / w0;
    cout << (n + 1) * k - k * (k + 1) / 2 * w0 << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

666，不会真的有人推式子的时候能抄错了吧。

根据题目给出的条件，轻松列出式子：

$xd+y\equiv yd+x\mod w$，需满足 $x<y,y<\min(d,m)$。移项得 $(y-x)(d-1)\equiv 0$。

$d-1$ 为常数，于是取 $z=\gcd(d-1,w)$，将式子改写为 $(y-x)\frac{d-1}{z}\equiv0\mod \frac{w}{z}$，此时 $\frac{d-1}{z},\frac{w}{z}$ 互质，直接扔掉。

最后的式子是 $(y-x)\equiv0\mod\frac{w}{z}$，枚举 $f=y-x$，对于一个 $f$，合法的 $x,y$ 对数是 $\min(m,d)-f+1$，同时要求 $f$ 是 $\frac{w}{z}$ 的倍数，这个很显然是个等差数列求和，注意下边界就行了。

```cpp
#include<iostream>
#include<numeric>
int main(){
    long long t, m, d, w, k, lm, rs;
    std::cin >> t; while(t--){
        std::cin >> m >> d >> w;
        lm = std::min(m, d);
        w /= std::gcd(w, d - 1);
        k = (lm - 1) / w;
        std::cout << k*lm-(1+k)*k/2*w << '\n';
    }
}
```

---

## 作者：Z_X_D_ (赞：0)

~~这么水的蓝题怎么没什么人写~~

## 思路
首先，第 $x$ 月的第 $y$ 天与第 $y$ 月的第 $x$ 天在一个星期中属于同一天，即：

$(x-1)d+y \equiv (y-1)d+x \pmod w$。

由于同余方程性质，可以在两边分别加一个 $d$，得：

$xd+y \equiv yd+x \pmod w$，

$yd+x-xd-y \equiv 0 \pmod w$，

化简可得：

$(y-x)(d-1) \equiv 0 \pmod w$，

即：

$w|(y-x)(d-1)$。

$d-1$ 显然是确定的，因此可以先求 $\gcd(d-1,w)$，记作 $g$，再将 $\frac{(d-1)}{g}$、$\frac{w}{g}$ 分别记作$d'$、$w'$，可得：

$w'|(y-x)d'$。

又因为$d'$，$w'$是互质的，所以：

$w'|(y-x)$

其中，$x<y \le \min(d,m)$。

先记 $mi= \min(d,m)$，对于一个 $x$，其对应的 $y$ 有 $\lfloor \frac{mi-x}{w'}\rfloor$。由此可知，在 $mi$ 范围内从第 $ (mi \bmod w')+1$ 个数开始，每 $w'$ 个 $x$ 所对应 $y$ 的个数都是一样的，所以用等差数列计算结果。

记 $k=\lfloor \frac{mi}{w'}\rfloor$，因为 $k$ 可能为 $0$，所以计算结果还要对 $0$ 取 $\max$。

$ans = \max(0,\frac{(k-1)* k}{2} \times w')+(mi \bmod w') \times k$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int gcd(int a,int b){return a%b?gcd(b,a%b):b;}
signed main()
{
	int t,m,d,w,g,ans,k;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&m,&d,&w);
		g=gcd(d-1,w);
		w/=g;
		m=min(m,d);
		k=m/w;
		ans=max(0ll,(k-1)*k/2*w)+(m%w)*k;
		printf("%lld\n",ans);
	}
	return 0;
}

```
~~由于你谷 Rrmote Judge 炸了所以~~这边挂个[CF的提交记录](https://codeforces.com/contest/1389/submission/222420754)。

---

## 作者：Φρανκ (赞：0)

题意：设一年有有 $m$ 月，每月 $d$ 天，每周 $w$ 天，求满足 $x$ 月 $y$ 日与 $y$ 月 $x$ 日在星期中相同的方法数。

核心思想：同余

解：

发现题目条件等价于 $xd+y\equiv yd+x\pmod w$，即 $x(d-1)\equiv y(d-1)\pmod m$，即 $x\equiv y\pmod \frac{w}{\gcd(w, d-1)}$。

已知 $x,y\le \min(m, d)$，设 $\min(m, d)=a\frac{w}{\gcd(w, d-1)}+b\:(b<\frac{w}{\gcd(w, d-1)})$，则总方法数即为 $bC^2_{a+1}+(\frac{w}{\gcd(w, d-1)}-b)C^2_a$，求算即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
long long t, m, d, w;
long long sol(long long x, long long y, long long z)
{
	long long t1=min(x, y);
	long long t2=z/__gcd(z, y-1);
	long long t3=t1/t2;
	long long t4=t1%t2;//带余除法
	return t4*(t3+1)*t3/2+(t2-t4)*t3*(t3-1)/2;//计算
}
int main()
{
	cin>>t;
	for(int i=1; i<=t; i++)
	{
		cin>>m>>d>>w;
		cout<<sol(m, d, w)<<endl;
	}
	return 0;
}

```

---

## 作者：PragmaGCC (赞：0)

由题意列出同余方程 $dx+y \equiv dy + x \pmod w$，移项得到 $(d-1)(x-y) \equiv 0 \pmod w$。

将 $w$ 去掉 $\gcd(d-1, w)$ 得到 $w'$，于是 $x \equiv y \pmod {w'}$。

题目变成：在 $[1,R=\min(d,m)]$ 中寻找两个模 $w'$ 同余的数。

将 $R$ 划分成若干个同余类，每个同余类里面任意两个数组成的数对都满足条件，直接通过同余类的大小用组合数求解即可。

```cpp
#include <algorithm>
#include <cstdio>
#define int long long
using namespace std;
int T, m, d, w;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
signed main(void) {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld%lld", &m, &d, &w);
        int lim = min(m, d); // 上限
        w /= gcd(w, d - 1); // 去掉 d-1 包含的因数
        int a = lim / w, b = lim % w; //对于余数部分同余类大小+1，分开算
        int cnt1 = b * (a + 1) * a / 2;
        int cnt2 = (w - b) * a * (a - 1) / 2;
        printf("%lld\n", cnt1 + cnt2);
    }
    return 0;
}
```

---

## 作者：dead_X (赞：0)

# 题意
给定 $n,m,d$ 求出无序数对 $(x,y)$ 满足 $x\times d+y\equiv y\times d+x\pmod w$ ，且$1\leq x,y\leq min(m,d)$。
# 思路
$x\times d+y\equiv y\times d+x\pmod w$ 

可以推到

$w|(x-y)(d-1)$

那么 $(x-y)$ 只需要满足 $\Large\frac{w}{gcd(w,d-1)}|(x-y)$ 即可。

注意到 $(x-y)$ 为定值时共有 $min(m,d)-(x-y)$ 对，所以我们可以枚举 $\Large\frac{w}{gcd(w,d-1)}$ 。

但这样最坏情况是 $O(min(m,d))$ 的，会被卡。

于是我们考虑每一次的值，显然是等差数列，一波求和就搞定了。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
long long gcd(long long p,long long q)
{
	if(p>q) swap(p,q);
	while(p)
	{
		q%=p,swap(p,q);
	}
	return q;
}
int main()
{
	int T=read();
	while(T--)
	{
		long long x=read(),y=read(),z=read(),w=z/gcd(z,y-1);
		long long tmp=(min(x,y)-1)/w;
		long long ans=tmp*min(x,y)-tmp*(tmp+1)/2*w;
		//for(long long t=1; t*w<min(x,y); t++) ans+=min(x,y)-(t*w);
		printf("%lld\n",ans);		
	}//w|(x-y)
 
    return 0;
}
```

---

